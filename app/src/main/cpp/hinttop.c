#include <stdio.h>
#include <math.h>
#include "basetypes.h"
#include "hformat.h"
#include "htex.h"
#include "htexdef.h"
#include "hpos.h"
#include "hget.h"
#include "hrender.h"
#include "fonts.h"

int page_v, page_h; /* size of page in scaled points */

static void clean_list(pointer *p)
{  if (*p!=null)
   { flush_node_list(*p);
     *p=null;
   }
}

static void clean_nest(void)
{   do
   { clean_list(&link(head));
	 tail = head;
	 if (nest_ptr>0) 
	 { pop_nest(); continue; }
	 else
	   break;
   } while (nest_ptr!=0);
   nest_ptr=0;
   mode=vmode;head=contrib_head;tail=contrib_head;
}

static void clean_up_page(void)
{
  clean_list(&(link(contrib_head)));
  if (nest_ptr==0) 
  { link(head)=null; tail=head; }
  link(contrib_head)=null; contrib_tail=contrib_head; 
  clean_nest();
}



void hint_init(void)
{ hmem_init();
  hlist_init();
  hset_max();
  hallocate_definitions();
  hset_default_definitions();
}

int font_in_short_display=0;

void hclear_dir(void)
{ int i;
  if (dir==NULL) return;
  for (i=0;i<3;i++)
  if (dir[i].xsize>0) 
	  free(dir[i].buffer);
  free(dir); dir=NULL;
}

void hint_start(const char *file_name)
{ hmem_init();
  hlist_init(); 
  hclear_fonts();
  hclear_dir();
  hopen_file(file_name);
  hget_banner();
  hget_directory_section();
  hget_definition_section();
  hget_content_section();
  hpage_init();
  hpos_init();
}

void hint_close(void)
{
}


scaled h_offset, v_offset, hvsize, hhsize;

static void hset_margins(void)
/* set h_offset, v_offset, hhsize, and hvsize from page_v and page_h */
{  h_offset=page_h/8- 0x48000;
   if (h_offset<0) h_offset=0;
   v_offset=page_v/8- 0x48000;
   if (v_offset<0) v_offset=0;
   if (h_offset>v_offset) h_offset=v_offset;
   else v_offset=h_offset;
   hhsize=page_h-2*h_offset;
   hvsize=page_v-2*v_offset;
   if (hhsize<=0) hhsize=page_h,h_offset=0;
   if (hvsize<=0) hvsize=page_v,v_offset=0;
}

static void houtput_template0(void)
/* we build the template 0 vbox */
{ pointer p,q,t,b,l,r;
 if (stream[0].p==null) return;
  p=null;
  q=new_spec(zero_glue);  width(q)=h_offset;
  l=new_glue(q);
  r=new_glue(q);
  q=new_spec(zero_glue);  width(q)=v_offset;
  t=new_glue(q);
  b=new_glue(q);
  
  p=stream[0].p;
  link(p)=r;
  link(l)=p; 
  p=hpack(l,page_h,exactly);
  link(p)=b;
  link(t)=p;
  p=vpackage(t,page_v,exactly,0);
  hship_out(p);
  flush_node_list(p); stream[0].p=null; 
}

void hint_page(void)
/* This function displays one page. 
   It stores the newly found end of the page in the page cache.

   At the beginning we have leftovers from previous pages in
   the leftovers list, and the current position in the hint
   stream in cur_hint.
   We move the leftovers to the contribution list and call
   build page. If necessary, we read from the hint stream
   until build page signals that output is active.
   Then we run the output routine which causes the
   rendering of the page. The ship_out procedure will
   also release the page content.
   We move the contribution list (containing the
   new leftovers for the next page) to the "fridge"
   (not without cleaning the fridge beforehand).
   Bon appetite!
*/
{ uint64_t h;
  hset_margins();
  hpage_init();
  clean_up_page();
  clear_map();
  h=hpos_get();
  hpos=hstart+(h&0xffffffff);
  if (h>0xffffffff)
    hget_par_node(h>>32);

  do {
	 if (hpos<hend)
       hget_content(); /* get one node and add it to the current list */
	 else 
	   if (hits_all_over()) break;
  } while (!hbuild_page());
  
  MESSAGE("build page finished");
#ifdef NEXTDEBUG
	print_str("Page list:");print_ln();
	depth_threshold=10;
    breadth_max=300;
    show_node_list(box(0));print_ln();
    print_str("End page.");print_ln();
#endif
#ifdef NEXTDEBUG
  if (log_file.f!=NULL) 
  { wlog("End output %d %d:\n",dyn_used,var_used);  
	print_str("Remaining Contributions:");print_ln();
    show_node_list(link(contrib_head));print_ln();
  }
#endif
  houtput_template0();
  hresume_after_output();
}



void hint_home_page(void)
{ hpos_home();
  hint_page();
}

void hint_next_page(void)
{ 
  hpos_next(); /* the next page, if it exists, it is set by rendering the current page */
  hint_page();
}


void hint_prev_page(void)
{ 
  if (hpos_prev())
    hint_page(); /* display at the previous cached page position */
  else 
#if 0
    /* not yet implemented */
    hint_teg_page(); /* scan back from the current position */
#else
    hint_home_page();
#endif
}


void hint_stop(void)
{
}
