@x
@p @<Header files and function declarations@>@;
@h
enum {@+@<Constants in the outer block@>@+};
@<Types in the outer block@>@;
@<Global variables@>@;
@#

static void initialize(void) /*this procedure gets things started properly*/
  {@+@<Local variables for initialization@>@;
  @<Initialize whatever \TeX\ might access@>;
  } @#
@<Basic printing procedures@>@;
@<Error handling procedures@>@;
@y
@(htex.c@>=
#ifndef _HETX_H_
#define _HTEX_H_

#include "basetypes.h"
#include <string.h>
#include <math.h>

#include "error.h"
#include "hformat.h"
#include "hget.h"
#include "htex.h"
#include "hint.h"
@<Selected global variables@>@;
@#
@<Basic error handling procedures@>@;
#endif
@z

@x
@d mem_top 65534 /*largest index in the |mem| array dumped by \.{INITEX};
  must be substantially larger than |mem_bot|
  and not greater than |mem_max|*/
@y
@d mem_top mem_max /*largest index in the |mem| array dumped by \.{INITEX};
  must be substantially larger than |mem_bot|
  and not greater than |mem_max|*/
@z

@x
#define wlog(FMT, ...) @[pascal_write(log_file,FMT, ## __VA_ARGS__)@]
#define wlog_ln(FMT, ...)   @[wlog(FMT "\n", ## __VA_ARGS__)@]
#define wlog_cr         @[pascal_write(log_file,"\n")@]
@y
@ @(hprint.c@>=
#include <stdio.h>
#include <math.h>
#include "basetypes.h"
#include "error.h"
#include "hformat.h"
#include "hget.h"
#include "htex.h"
#include "hint.h"


#define wlog(FMT, ...)    @[fprintf(hlog,FMT, ## __VA_ARGS__)@]
#define wlogc(C)          @[putc(C,hlog)@]
#define wlog_ln(FMT, ...) @[wlog(FMT "\n", ## __VA_ARGS__)@]
#define wlog_cr           @[wlogc('\n')@]

static int8_t @!dig[23]; /*digits in a number being output*/
static int @!tally=0; /*the number of characters recently printed*/
static int @!file_offset=0;/*the number of characters on the current file line*/
static int @!depth_threshold; /*maximum nesting depth in box displays*/
static int @!breadth_max; /*maximum number of items shown at the same list level*/
static int depth_level=0; /*current nesting level of |show_node_list|*/
static int nl_char='\n';

static void print_ln(void) /*prints an end-of-line*/
{ @+wlog_cr; file_offset=0;
}

static void print_char(ASCII_code @!s) /*prints a single character*/
{@+if (s==nl_char)
  {@+print_ln();return;
  }
  wlogc(s); file_offset++;
  if (file_offset==max_print_line) print_ln();
  tally++;
}

static void print(char *s) /* the simple version */
{ while (*s!=0) print_char(*s++);@+
}

void print_nl(char *@!s) /*prints string |s| at beginning of line*/
{@+if (file_offset > 0) print_ln();
  print(s);
}

void print_esc(char *@!s) /*prints escape character, then |s|*/
{@+print_char('\\');
  print(s);
}
@z

@x
static void print_the_digs(eight_bits @!k)
@y
@ @(hprint.c@>=
static void print_the_digs(eight_bits @!k)
@z

@x
static void print_int(int @!n) /*prints an integer in decimal form*/
@y
@ @(hprint.c@>=
static void print_int(int @!n) /*prints an integer in decimal form*/
@z

@x
@d print_ASCII printn
@y
@d print_lc_hex(A)
  if ((A) < 10) print_char((A)+'0');@+else print_char((A)-10+'a')
@d print_ASCII(k)
   if ( (k < ' ')||(k > '~'))
    {@+print("^^");
      if (k < 0100) print_char(k+0100);
      else if (k < 0200) print_char(k-0100);
      else {@+print_lc_hex(k/16);print_lc_hex(k%16); }
    }
    else print_char(k)
@z

@x
@ Here is the most dreaded error message.

@<Error hand...@>=
static void overflow(char *@!s, int @!n) /*stop due to finiteness*/
{@+normalize_selector();
print_err("TeX capacity exceeded, sorry [");
@.TeX capacity exceeded ...@>
print(s);print_char('=');print_int(n);print_char(']');
help2("If you really absolutely need more capacity,",@/
  "you can ask a wizard to enlarge me.");
succumb;
}
@y
@ Here is the most dreaded error message.

@<Basic error handling procedures@>=
void overflow(char *@!s, int @!n) /*stop due to finiteness*/
{@+ QUIT("Capacity exceeded, sorry [%s=%d=0x%X]\n",s,n,n);@+
}
@z

@x
@<Error hand...@>=
static void confusion(char *@!s)
   /*consistency check violated; |s| tells where*/
{@+normalize_selector();
if (history < error_message_issued)
  {@+print_err("This can't happen (");print(s);print_char(')');
@.This can't happen@>
  help1("I'm broken. Please show this to someone who can fix can fix");
  }
else{@+print_err("I can't go on meeting you like this");
@.I can't go on...@>
  help2("One of your faux pas seems to have wounded me deeply...",@/
    "in fact, I'm barely conscious. Please fix it and try again.");
  }
succumb;
}
@y
@<Basic error handling procedures@>=
void confusion(char *@!s)
   /*consistency check violated; |s| tells where*/
{@+ QUIT("This can't happen(%s)",s);@+ }
@z

@x
@p static int half(int @!x)
@y
@(htex.c@>=

static int half(int @!x)
@z

@x
@p static void print_scaled(scaled @!s) /*prints scaled real, rounded to five
  digits*/
@y
@(hprint.c@>=
static void print_scaled(scaled @!s) /*prints scaled real, rounded to five
  digits*/
@z

@x
}
@y
}

static void print_xdimen(pointer p)
{ print_scaled(xdimen_width(p));
  if (xdimen_hfactor(p)!=0)
  { print_char('+');print_scaled(xdimen_hfactor(p));print("*hsize");}
  if (xdimen_vfactor(p)!=0)
  { print_char('+');print_scaled(xdimen_vfactor(p));print("*vsize");}
}

static void print_label(pointer p)
{ print("goto *"); print_int(label_ref(p));
}
@z

@x
static bool @!arith_error; /*has arithmetic overflow occurred recently?*/
static scaled @!rem; /*amount subtracted to get an exact division*/
@y
@ @(htex.c@>=
static bool @!arith_error; /*has arithmetic overflow occurred recently?*/
static scaled @!rem; /*amount subtracted to get an exact division*/
@z

@x
@p static scaled x_over_n(scaled @!x, int @!n)
@y
@(htex.c@>=
static scaled x_over_n(scaled @!x, int @!n)
@z

@x
@p static scaled xn_over_d(scaled @!x, int @!n, int @!d)
@y
@(htex.c@>=
static scaled xn_over_d(scaled @!x, int @!n, int @!d)
@z

@x
@p halfword badness(scaled @!t, scaled @!s) /*compute badness, given |t >= 0|*/
@y
@(htex.c@>=
halfword badness(scaled @!t, scaled @!s) /*compute badness, given |t >= 0|*/
@z

@x
pointer @!temp_ptr; /*a pointer variable for occasional emergency use*/
@y
@ @<Selected global variables@>=
pointer @!temp_ptr; /*a pointer variable for occasional emergency use*/
@z

@x
@<Glob...@>=
memory_word @!mem0[mem_max-mem_min+1], *const @!mem = @!mem0-mem_min; /*the big dynamic storage area*/
pointer @!lo_mem_max; /*the largest location of variable-size memory in use*/
pointer @!hi_mem_min; /*the smallest location of one-word memory in use*/
@y
@<Selected global variables@>=
memory_word @!mem0[mem_max-mem_min+1], *const @!mem = @!mem0-mem_min; /*the big dynamic storage area*/
pointer @!lo_mem_max; /*the largest location of variable-size memory in use*/
pointer @!hi_mem_min; /*the smallest location of one-word memory in use*/
@z

@x
@<Glob...@>=
static int @!var_used, @!dyn_used; /*how much memory is in use*/
@y
@<Selected global variables@>=
static int @!var_used, @!dyn_used; /*how much memory is in use*/
@z

@x
@<Glob...@>=
static pointer @!avail; /*head of the list of available one-word nodes*/
static pointer @!mem_end; /*the last one-word node used in |mem|*/
@y
@d mem_end mem_top
@<Selected global variables@>=
static pointer @!avail; /*head of the list of available one-word nodes*/
@z

@x
@p static pointer get_avail(void) /*single-word node allocation*/
@y
@(htex.c@>=
static pointer get_avail(void) /*single-word node allocation*/
@z

@x
else if (mem_end < mem_max)  /*or go into virgin territory*/
  {@+incr(mem_end);p=mem_end;
  }
else{@+decr(hi_mem_min);p=hi_mem_min;
  if (hi_mem_min <= lo_mem_max)
    {@+runaway(); /*if memory is exhausted, display possible runaway text*/
@y
else{@+decr(hi_mem_min);p=hi_mem_min;
  if (hi_mem_min <= lo_mem_max)
    {@+
@z

@x
@p static void flush_list(pointer @!p) /*makes list of single-word nodes
  available*/
@y
@(htex.c@>=
static void flush_list(pointer @!p) /*makes list of single-word nodes
  available*/
@z

@x
@<Glob...@>=
static pointer @!rover; /*points to some node in the list of empties*/
@y
@<Selected global variables@>=
static pointer @!rover; /*points to some node in the list of empties*/
@z

@x
@p pointer get_node(int @!s) /*variable-size node allocation*/
@y
@(htex.c@>=
pointer get_node(int @!s) /*variable-size node allocation*/
@z

@x
return r;
@y
leak_in(r,s);
return r;
@z

@x
@p static void free_node(pointer @!p, halfword @!s) /*variable-size node
  liberation*/
{@+pointer q; /*|llink(rover)|*/
@y
@(htex.c@>=
static void free_node(pointer @!p, halfword @!s) /*variable-size node
  liberation*/
{@+pointer q; /*|llink(rover)|*/
leak_out(p,s);
store_map(p,0,0);
@z

@x
@d box_node_size 7 /*number of words to allocate for a box node*/
@y
@d box_node_size 9 /*number of words to allocate for a box, set, or pack node*/
@z

@x
@p pointer new_null_box(void) /*creates a new box node*/
@y
@(htex.c@>=
pointer new_null_box(void) /*creates a new box node*/
@z

@x
@p pointer new_rule(void)
@y
@(htex.c@>=
pointer new_rule(void)
@z

@x
@p pointer new_ligature(quarterword @!f, quarterword @!c, pointer @!q)
@y
@(htex.c@>=
pointer new_ligature(quarterword @!f, quarterword @!c, pointer @!q)
@z

@x
static pointer new_lig_item(quarterword @!c)
{@+pointer p; /*the new node*/
p=get_node(small_node_size);character(p)=c;lig_ptr(p)=null;
return p;
}
@y
@z

@x
@d replace_count(A) subtype(A) /*how many subsequent nodes to replace*/
@y
@d replace_count(A) (subtype(A)&0x7F) /*how many subsequent nodes to replace*/
@d set_replace_count(A,B) (subtype(A)=(B)&0x7F)
@d set_auto_disc(A) (subtype(A)|=0x80)
@d is_auto_disc(A) (subtype(A)&0x80)
@z

@x
@p pointer new_disc(void) /*creates an empty |disc_node|*/
@y
@(htex.c@>=
pointer new_disc(void) /*creates an empty |disc_node|*/
@z

@x
replace_count(p)=0;pre_break(p)=null;post_break(p)=null;
@y
subtype(p)=0;pre_break(p)=null;post_break(p)=null;
@z

@x
@p pointer new_math(scaled @!w, small_number @!s)
@y
@(htex.c@>=
pointer new_math(scaled @!w, small_number @!s)
@z

@x
@p pointer new_spec(pointer @!p) /*duplicates a glue specification*/
@y
@(htex.c@>=
pointer new_spec(pointer @!p) /*duplicates a glue specification*/
@z

@x
@p pointer new_glue(pointer @!q)
@y
@(htex.c@>=
pointer new_glue(pointer @!q)
@z

@x
@p pointer new_kern(scaled @!w)
@y
@(htex.c@>=
pointer new_kern(scaled @!w)
@z

@x
@p pointer new_penalty(int @!m)
@y
@(htex.c@>=
pointer new_penalty(int @!m)
@z

@x
@d zero_glue mem_bot /*specification for \.{0pt plus 0pt minus 0pt}*/
@d fil_glue zero_glue+glue_spec_size /*\.{0pt plus 1fil minus 0pt}*/
@d fill_glue fil_glue+glue_spec_size /*\.{0pt plus 1fill minus 0pt}*/
@d ss_glue fill_glue+glue_spec_size /*\.{0pt plus 1fil minus 1fil}*/
@d fil_neg_glue ss_glue+glue_spec_size /*\.{0pt plus -1fil minus 0pt}*/
@d lo_mem_stat_max fil_neg_glue+glue_spec_size-1 /*largest statically
  allocated word in the variable-size |mem|*/
@y
@d zero_glue mem_bot /*specification for \.{0pt plus 0pt minus 0pt}*/
@d lo_mem_stat_max zero_glue+glue_spec_size-1 /*largest statically allocated word in the variable-size |mem|*/
@z

@x
@ @<Initialize table entries...@>=
@y
@ @(htex.c@>=
void mem_init(void)
{ @+ int k;
  @<Initialize |mem|@>@;
}

@ @<Initialize |mem|@>=
@z

@x
stretch(fil_glue)=unity;stretch_order(fil_glue)=fil;@/
stretch(fill_glue)=unity;stretch_order(fill_glue)=fill;@/
stretch(ss_glue)=unity;stretch_order(ss_glue)=fil;@/
shrink(ss_glue)=unity;shrink_order(ss_glue)=fil;@/
stretch(fil_neg_glue)=-unity;stretch_order(fil_neg_glue)=fil;@/
@y
@z

@x
avail=null;mem_end=mem_top;
@y
avail=null;
@z

@x
@p static void print_font_and_char(int @!p) /*prints |char_node| data*/
{@+if (p > mem_end) print_esc("CLOBBERED.");
else{@+if ((font(p) < font_base)||(font(p) > font_max)) print_char('*');
@.*\relax@>
  else@<Print the font identifier for |font(p)|@>;
  print_char(' ');print_ASCII(qo(character(p)));
  }
}
@y
@(hprint.c@>=
static void print_font_and_char(int @!p) /*prints |char_node| data*/
{@+if (p > mem_end) print_esc("CLOBBERED.");
else{@<Print the font identifier for |font(p)|@>;
  print_char(' ');print_ASCII(character(p));
  }
}
@z

@x
static void print_mark(int @!p) /*prints token list data in braces*/
{@+print_char('{');
if ((p < hi_mem_min)||(p > mem_end)) print_esc("CLOBBERED.");
else show_token_list(link(p), null, max_print_line-10);
print_char('}');
}
@y
static void print_mark(int @!p) /*prints token list data in braces*/
{@+print_char('{');print_char('}');@+
}
@z

@x
@p static void print_glue(scaled @!d, int @!order, char *@!s)
@y
@ @(hprint.c@>=
   static void print_glue(scaled @!d, int @!order, char *@!s)
@z

@x
@p static void print_spec(int @!p, char *@!s)
@y
@ @(hprint.c@>=
  static void print_spec(int @!p, char *@!s)
@z

@x
@<Declare the procedure called |print_skip_param|@>@;
@y
@<Declare the procedure called |print_skip_param|@>@;
static void print_xdimen(pointer p)
{ print_scaled(xdimen_width(p));
  if (xdimen_hfactor(p)!=0)
  { print_char('+');print_scaled(xdimen_hfactor(p));print("*hsize");}
  if (xdimen_vfactor(p)!=0)
  { print_char('+');print_scaled(xdimen_vfactor(p));print("*vsize");}
}
extern void print_baseline_skip(int i);
@z

@x
@d node_list_display(A)
  {@+append_char('.');show_node_list(A);flush_char;
  }  /*|str_room| need not be checked; see |show_box| below*/
@y
@d node_list_display(A)
  {@+depth_level++;show_node_list(A);depth_level--;
  }
@d print_current_indent
  {@+int i;
     for(i=0;i<depth_level;i++) @+
       print_char('.');@+}
@z

@x
@p static void show_node_list(int @!p) /*prints a node list symbolically*/
@y
@ @(hprint.c@>=
static void show_node_list(int @!p) /*prints a node list symbolically*/
@z

@x
if (cur_length > depth_threshold)
@y
if (depth_level > depth_threshold)
@z

@x
  {@+print_ln();print_current_string(); /*display the nesting history*/
@y
  {@+print_ln();print_current_indent;
@z

@x
  case mark_node: @<Display mark |p|@>@;@+break;
  case adjust_node: @<Display adjustment |p|@>@;@+break;
  @t\4@>@<Cases of |show_node_list| that arise in mlists only@>@;
@y
  case adjust_node: @<Display adjustment |p|@>@;@+break;
@z

@x
else{@+print_esc("glue");
  if (subtype(p)!=normal)
    {@+print_char('(');
    if (subtype(p) < cond_math_glue)
      print_skip_param(subtype(p)-1);
    else if (subtype(p)==cond_math_glue) print_esc("nonscript");
    else print_esc("mskip");
    print_char(')');
    }
  if (subtype(p)!=cond_math_glue)
    {@+print_char(' ');
    if (subtype(p) < cond_math_glue) print_spec(glue_ptr(p), 0);
    else print_spec(glue_ptr(p),"mu");
    }
  }
@y
else{@+print_esc("glue "); print_spec(glue_ptr(p), 0);@+ }
@z

@x
  if (subtype(p)!=normal) print_char(' ');
@y
  print_char(' ');
@z

@x
font_in_short_display=font(lig_char(p));short_display(lig_ptr(p));
@y
node_list_display(lig_ptr(p));
@z

@x
append_char('|');show_node_list(post_break(p));flush_char; /*recursive call*/
@y
node_list_display(post_break(p)); /*recursive call*/
@z

@x
@p void show_box(pointer @!p)
{@+@<Assign the values |depth_threshold:=show_box_depth| and |breadth_max:=show_box_breadth|@>;
if (breadth_max <= 0) breadth_max=5;
if (pool_ptr+depth_threshold >= pool_size)
  depth_threshold=pool_size-pool_ptr-1;
   /*now there's enough room for prefix string*/
@y
@(hprint.c@>=
void show_box(pointer @!p)
{@+depth_threshold=200; breadth_max=200;
@z

@x
@p static void delete_token_ref(pointer @!p) /*|p| points to the reference count
  of a token list that is losing one reference*/
@y
@(htex.c@>=
static void delete_token_ref(pointer @!p) /*|p| points to the reference count
  of a token list that is losing one reference*/
@z

@x
@p void delete_glue_ref(pointer @!p) /*|p| points to a glue specification*/
fast_delete_glue_ref(p)
@y
@(htex.c@>=
void delete_glue_ref(pointer @!p) /*|p| points to a glue specification*/
fast_delete_glue_ref(p)
void delete_xdimen_ref(pointer @!p) /*|p| points to a xdimen specification*/
{@+if (xdimen_ref_count(p)==null) free_node(p, xdimen_node_size);
  else decr(xdimen_ref_count(p));
}
@z

@x
@p void flush_node_list(pointer @!p) /*erase list of nodes starting at |p|*/
@y
@(htex.c@>=
void flush_node_list(pointer @!p) /*erase list of nodes starting at |p|*/
@z

@x
    case mark_node: delete_token_ref(mark_ptr(p));@+break;
@y
@z

@x
    @t\4@>@<Cases of |flush_node_list| that arise in mlists only@>@;
    default:confusion("flushing");
@y
    default:QUIT("Confusion while flushing node list");
@z

@x
@d add_glue_ref(A) incr(glue_ref_count(A)) /*new reference to a glue spec*/
@y
@d add_glue_ref(A) incr(glue_ref_count(A)) /*new reference to a glue spec*/
@d add_xdimen_ref(A) incr(xdimen_ref_count(A)) /*new reference to an xdimen*/
@z

@x
@p pointer copy_node_list(pointer @!p) /*makes a duplicate of the
  node list that starts at |p| and returns a pointer to the new list*/
@y
@(htex.c@>=
pointer copy_node_list(pointer @!p) /*makes a duplicate of the
  node list that starts at |p| and returns a pointer to the new list*/
@z

@x
  int @!pg_field, @!ml_field;@+
@y
 int pg_field;
 pointer bs_field,ls_field; /* baseline skip and line skip */
 scaled lsl_field; /* line skip limit */
 uint8_t *bs_pos; /* position of baseline skip node */
 scaled hs_field; /* horizontal size */
 scaled ds_field, dw_field, di_field; /*display size, width, and indent */
 scaled ht_field; /* height of last box added to the list */
 uint32_t np_field; /* position of current node */
@z

@x
@d mode_line cur_list.ml_field /*source file line number at beginning of list*/
@y
@d cur_bs cur_list.bs_field /*baseline skip glue specification*/
@d cur_ls cur_list.ls_field /*line skip glue specification*/
@d cur_lsl cur_list.lsl_field /*line skip limit*/
@d needs_bs (cur_list.bs_pos!=NULL) /*is a baseline skip needed?*/
@d prev_height cur_list.ht_field /* height of previous box */
@d node_pos cur_list.np_field /*node position in the \HINT/ file or |NULL|*/
@d node_pos1 (nest_ptr==0?0:nest[nest_ptr-1].np_field) /*position of enclosing node*/
@z

@x
@<Glob...@>=
static list_state_record @!nest[nest_size+1];
int @!nest_ptr; /*first unused location of |nest|*/
static int @!max_nest_stack; /*maximum of |nest_ptr| when pushing*/
list_state_record @!cur_list; /*the ``top'' semantic state*/
static int @!shown_mode; /*most recent mode shown by \.{\\tracingcommands}*/
@y
@<List variables@>=
static list_state_record @!nest[nest_size+1];
int @!nest_ptr; /*first unused location of |nest|*/
static int @!max_nest_stack; /*maximum of |nest_ptr| when pushing*/
list_state_record @!cur_list; /*the ``top'' semantic state*/
@z

@x
@<Set init...@>=
nest_ptr=0;max_nest_stack=0;
mode=vmode;head=contrib_head;tail=contrib_head;
prev_depth=ignore_depth;mode_line=0;
prev_graf=0;shown_mode=0;
@y
@(htex.c@>=

@<List variables@>@;

void list_init(void)
{@+
nest_ptr=0;max_nest_stack=0;@/
memset(&cur_list,0,sizeof(cur_list));
mode=vmode;head=contrib_head;tail=contrib_head;
prev_height=prev_depth=ignore_depth;
}
@ @<Set init...@>=
list_init();
@z

@x
@p void push_nest(void) /*enter a new semantic level, save the old*/
@y
@s line mode_line
@(htex.c@>=
void push_nest(void) /*enter a new semantic level, save the old*/
@z

@x
incr(nest_ptr);head=get_avail();tail=head;prev_graf=0;mode_line=line;
@y
incr(nest_ptr);head=get_avail();tail=head;prev_graf=0;
cur_list.bs_pos=NULL; cur_bs=baseline_skip; cur_ls=line_skip; cur_lsl=line_skip_limit;
@z

@x
@p void pop_nest(void) /*leave a semantic level, re-enter the old*/
@y
@(htex.c@>=
void pop_nest(void) /*leave a semantic level, re-enter the old*/
@z

@x
@d skip(A) equiv(skip_base+A) /*|mem| location of glue specification*/
@y
@z

@x
@d line_skip glue_par(line_skip_code)
@d baseline_skip glue_par(baseline_skip_code)
@d par_skip glue_par(par_skip_code)
@d above_display_skip glue_par(above_display_skip_code)
@d below_display_skip glue_par(below_display_skip_code)
@d above_display_short_skip glue_par(above_display_short_skip_code)
@d below_display_short_skip glue_par(below_display_short_skip_code)
@d left_skip glue_par(left_skip_code)
@d right_skip glue_par(right_skip_code)
@d top_skip glue_par(top_skip_code)
@d split_top_skip glue_par(split_top_skip_code)
@d tab_skip glue_par(tab_skip_code)
@d space_skip glue_par(space_skip_code)
@d xspace_skip glue_par(xspace_skip_code)
@d par_fill_skip glue_par(par_fill_skip_code)
@y
@d line_skip pointer_def[glue_kind][line_skip_no]
@d baseline_skip pointer_def[glue_kind][baseline_skip_no]
@d above_display_skip pointer_def[glue_kind][above_display_skip_no]
@d below_display_skip pointer_def[glue_kind][below_display_skip_no]
@d above_display_short_skip pointer_def[glue_kind][above_display_short_skip_no]
@d below_display_short_skip pointer_def[glue_kind][below_display_short_skip_no]
@d left_skip pointer_def[glue_kind][left_skip_no]
@d right_skip pointer_def[glue_kind][right_skip_no]
@d top_skip pointer_def[glue_kind][top_skip_no]
@d split_top_skip pointer_def[glue_kind][split_top_skip_no]
@d tab_skip pointer_def[glue_kind][tab_skip_no]
@d par_fill_skip pointer_def[glue_kind][par_fill_skip_no]
@z

@x
@d par_shape_ptr equiv(par_shape_loc)
@y
@d par_shape_ptr null
@z

@x
@d box(A) equiv(box_base+A)
@y
@d box(A) (*box_ptr(A))
@z

@x
@d count(A) eqtb[count_base+A].i
@y
@z

@x
@d pretolerance int_par(pretolerance_code)
@d tolerance int_par(tolerance_code)
@d line_penalty int_par(line_penalty_code)
@d hyphen_penalty int_par(hyphen_penalty_code)
@d ex_hyphen_penalty int_par(ex_hyphen_penalty_code)
@d club_penalty int_par(club_penalty_code)
@d widow_penalty int_par(widow_penalty_code)
@d display_widow_penalty int_par(display_widow_penalty_code)
@d broken_penalty int_par(broken_penalty_code)
@d bin_op_penalty int_par(bin_op_penalty_code)
@d rel_penalty int_par(rel_penalty_code)
@d pre_display_penalty int_par(pre_display_penalty_code)
@d post_display_penalty int_par(post_display_penalty_code)
@d inter_line_penalty int_par(inter_line_penalty_code)
@d double_hyphen_demerits int_par(double_hyphen_demerits_code)
@d final_hyphen_demerits int_par(final_hyphen_demerits_code)
@d adj_demerits int_par(adj_demerits_code)
@d mag int_par(mag_code)
@d delimiter_factor int_par(delimiter_factor_code)
@d looseness int_par(looseness_code)
@d time int_par(time_code)
@d day int_par(day_code)
@d month int_par(month_code)
@d year int_par(year_code)
@y
@d pretolerance integer_def[pretolerance_no]
@d tolerance integer_def[tolerance_no]
@d line_penalty integer_def[line_penalty_no]
@d hyphen_penalty integer_def[hyphen_penalty_no]
@d ex_hyphen_penalty integer_def[ex_hyphen_penalty_no]
@d club_penalty integer_def[club_penalty_no]
@d widow_penalty integer_def[widow_penalty_no]
@d display_widow_penalty integer_def[display_widow_penalty_no]
@d broken_penalty integer_def[broken_penalty_no]
@d pre_display_penalty integer_def[pre_display_penalty_no]
@d post_display_penalty integer_def[post_display_penalty_no]
@d inter_line_penalty integer_def[inter_line_penalty_no]
@d double_hyphen_demerits integer_def[double_hyphen_demerits_no]
@d final_hyphen_demerits integer_def[final_hyphen_demerits_no]
@d adj_demerits integer_def[adj_demerits_no]
@d looseness integer_def[looseness_no]
@d time integer_def[time_no]
@d day integer_def[day_no]
@d month integer_def[month_no]
@d year integer_def[year_no]
@z

@x
@d tracing_paragraphs int_par(tracing_paragraphs_code)
@y
@d tracing_paragraphs (debugflags&DBGTEX)
@z

@x
@d hang_after int_par(hang_after_code)
@y
@d hang_after integer_def[hang_after_no]
@z

@x
@d holding_inserts int_par(holding_inserts_code)
@y
@z

@x
@d dimen(A) eqtb[scaled_base+A].sc
@y
@z

@x
@d line_skip_limit dimen_par(line_skip_limit_code)
@y
@d line_skip_limit dimen_def[line_skip_limit_no]
@z

@x
@d max_depth dimen_par(max_depth_code)
@y
@d max_depth dimen_def[max_depth_no]
@z

@x
@d pre_display_size dimen_par(pre_display_size_code)
@d display_width dimen_par(display_width_code)
@d display_indent dimen_par(display_indent_code)
@y
@d pre_display_size cur_list.ds_field
@d display_width cur_list.dw_field
@d display_indent cur_list.di_field
@z

@x
@d hang_indent dimen_par(hang_indent_code)
@y
@d hang_indent dimen_def[hang_indent_no]
@z

@x
@d emergency_stretch dimen_par(emergency_stretch_code)
@y
@d emergency_stretch dimen_def[emergency_stretch_no]
@z

@x
@<Print the font identifier for |font(p)|@>=
printn_esc(font_id_text(font(p)))
@y
@<Print the font identifier for |font(p)|@>=
if (font_name[font(p)]!=NULL) print_esc(font_name[font(p)]);else print_char('*');
@z

@x
memory_word @!font_info[font_mem_size+1];
   /*the big collection of font data*/
static font_index @!fmem_ptr; /*first unused word of |font_info|*/
@y
@
@s font_index int
@s str_number int
@(htex.c@>=
memory_word @!font_info[font_mem_size+1];
   /*the big collection of font data*/
static font_index @!fmem_ptr=0; /*first unused word of |font_info|*/

void hclear_fonts(void)
{ fmem_ptr=0;
}
@z

@x
str_number @!font_name0[font_max-font_base+1], *const @!font_name = @!font_name0-font_base; /*name of the font*/
static str_number @!font_area0[font_max-font_base+1], *const @!font_area = @!font_area0-font_base; /*area of the font*/
@y
char *font_name0[font_max-font_base+1], **const font_name = @!font_name0-font_base; /*name of the font*/
@z

@x
@<Glob...@>=
int @!char_base0[font_max-font_base+1], *const @!char_base = @!char_base0-font_base;
@y
@(htex.c@>=
int @!char_base0[font_max-font_base+1], *const @!char_base = @!char_base0-font_base;
@z

@x
@p internal_font_number read_font_info(pointer @!u, str_number @!nom, char *@!aire,
  scaled @!s) /*input a \.{TFM} file*/
@y
@(htex.c@>=
void read_font_info(int f, char *@!nom, scaled @!s)
@z

@x
internal_font_number @!f; /*the new font's number*/
internal_font_number @!g; /*the number to return*/
@y
@z

@x
g=null_font;@/
@y
@z

@x
bad_tfm: @<Report that the font won't be loaded@>;
done: if (file_opened) b_close(&tfm_file);
return g;
@y
bad_tfm:  QUIT("Bad tfm file: %s\n", nom);
done:;
@z

@x
@ @<Open |tfm_file| for input@>=
file_opened=false;
if (aire[0]==0) pack_file_name(nom, TEX_font_area,".tfm");
else pack_file_name(nom, aire,".tfm");
if (!b_open_in(&tfm_file)) abort;
file_opened=true
@y
@ @<Open |tfm_file| for input@>=
file_opened=true
@z

@x
@d fget get(tfm_file)
@d fbyte tfm_file.d
@y
@d fget (hpos++)
@d fbyte (*hpos)
@z

@x
  @<Apologize for not loading the font, |goto done|@>;
f=font_ptr+1;
@y
QUIT("Not enough room left for font %s\n",nom);
@z

@x
if (eof(tfm_file)) abort;
@y
if (hpos>=hend) abort;
@z

@x
hyphen_char[f]=default_hyphen_char;skew_char[f]=default_skew_char;
@y
hyphen_char[f]=skew_char[f]=-1;
@z

@x
font_area[f]=s_no(aire);
@y
@z

@x
fmem_ptr=fmem_ptr+lf;font_ptr=f;g=f;goto done
@y
fmem_ptr=fmem_ptr+lf; goto done
@z

@x
@p pointer new_character(internal_font_number @!f, eight_bits @!c)
{@+
pointer p; /*newly allocated node*/
if (font_bc[f] <= c) if (font_ec[f] >= c)
  if (char_exists(char_info(f, qi(c))))
    {@+p=get_avail();font(p)=f;character(p)=qi(c);
    return p;
    }
char_warning(f, c);
return null;
}
@y
@(htex.c@>=
pointer new_character(internal_font_number @!f, eight_bits @!c)
{@+ pointer p; /*newly allocated node*/
#ifdef DEBUG
if (font_bc[f] > c || font_ec[f] < c || ! char_exists(char_info(f, qi(c))))
  DBG(DBGFONT,"Warning: Character 0x%0X in font %d does not exist\n",c,f);
#endif
p=get_avail();font(p)=f;character(p)=qi(c);
return p;
}
@z

@x
static scaled @!total_stretch0[filll-normal+1], *const @!total_stretch = @!total_stretch0-normal, @!total_shrink0[filll-normal+1], *const @!total_shrink = @!total_shrink0-normal;
   /*glue found by |hpack| or |vpack|*/
static int @!last_badness; /*badness of the most recently packaged box*/
@y
@ @<Selected global variables@>=
static scaled @!total_stretch0[filll-normal+1], *const @!total_stretch = @!total_stretch0-normal, @!total_shrink0[filll-normal+1], *const @!total_shrink = @!total_shrink0-normal;
   /*glue found by |hpack| or |vpack|*/
@z

@x
pointer @!adjust_tail; /*tail of adjustment list*/
@y
@ @<Selected global variables@>=
pointer @!adjust_tail=null; /*tail of adjustment list*/
@z

@x
@p pointer hpack(pointer @!p, scaled @!w, small_number @!m)
@y
@(htex.c@>=
pointer hpack(pointer @!p, scaled @!w, small_number @!m)
@z

@x
last_badness=0;r=get_node(box_node_size);type(r)=hlist_node;
@y
r=get_node(box_node_size);type(r)=hlist_node;
@z

@x
common_ending: @<Finish issuing a diagnostic message for an overfull or underfull
hbox@>;
@y
@z

@x
if (o==normal) if (list_ptr(r)!=null)
  @<Report an underfull hbox and |goto common_ending|, if this box is sufficiently
bad@>;
@y
@z

@x
  {@+last_badness=1000000;
  set_glue_ratio_one(glue_set(r)); /*use the maximum shrinkage*/
  @<Report an overfull hbox and |goto common_ending|, if this box is sufficiently
bad@>;
  }
else if (o==normal) if (list_ptr(r)!=null)
  @<Report a tight hbox and |goto common_ending|, if this box is sufficiently bad@>;
@y
  set_glue_ratio_one(glue_set(r)); /*use the maximum shrinkage*/
@z

@x
#define vpack(...) @[vpackage(__VA_ARGS__, max_dimen)@] /*special case of unconstrained depth*/
pointer vpackage(pointer @!p, scaled @!h, small_number @!m, scaled @!l)
@y
@
@d vpack(A,B) @[vpackage(A,B, max_dimen)@] /*special case of unconstrained depth*/

@(htex.c@>=
pointer vpackage(pointer @!p, scaled @!h, small_number @!m, scaled @!l)
@z

@x
last_badness=0;r=get_node(box_node_size);type(r)=vlist_node;
@y
r=get_node(box_node_size);type(r)=vlist_node;
@z

@x
common_ending: @<Finish issuing a diagnostic message for an overfull or underfull
vbox@>;
@y
@z

@x
if (o==normal) if (list_ptr(r)!=null)
  @<Report an underfull vbox and |goto common_ending|, if this box is sufficiently
bad@>;
@y
@z

@x
  {@+last_badness=1000000;
  set_glue_ratio_one(glue_set(r)); /*use the maximum shrinkage*/
  @<Report an overfull vbox and |goto common_ending|, if this box is sufficiently
bad@>;
  }
else if (o==normal) if (list_ptr(r)!=null)
  @<Report a tight vbox and |goto common_ending|, if this box is sufficiently bad@>;
@y
  set_glue_ratio_one(glue_set(r)); /*use the maximum shrinkage*/
@z

@x
@p void append_to_vlist(pointer @!b)
@y
@<Declare subprocedures for |line_break|@>=
extern pointer happend_to_vlist(pointer b);
void append_to_vlist(pointer @!b, uint32_t offset)
@z

@x
  if (d < line_skip_limit) p=new_param_glue(line_skip_code);
  else{@+p=new_skip_param(baseline_skip_code);
    width(temp_ptr)=d; /*|temp_ptr==glue_ptr(p)|*/
    }
@y
  if (d < line_skip_limit) p=new_glue(line_skip);
  else{@+temp_ptr=new_spec(baseline_skip);
       p=new_glue(temp_ptr);glue_ref_count(temp_ptr)=null;
    width(temp_ptr)=d; /*|temp_ptr==glue_ptr(p)|*/
    }
   store_map(p, node_pos,offset);
@z

@x
@d math_quad mathsy(6) /*\.{18mu}*/
@y
@d math_quad dimen_def[math_quad_no] /*\.{18mu}*/
@z

@x
pointer @!just_box; /*the |hlist_node| for the last line of the new paragraph*/
@y
@ @<Selected global variables@>=
pointer @!just_box; /*the |hlist_node| for the last line of the new paragraph*/
@z

@x
@p @t\4@>@<Declare subprocedures for |line_break|@>@;
void line_break(int @!final_widow_penalty)
{@+
@y
@(htex.c@>=

@<Declare subprocedures for |line_break|@>@;

void line_break(int final_widow_penalty, pointer par_ptr)
{@+ scaled x=cur_list.hs_field; /* the |hsize| for this paragraph */
@z

@x
pack_begin_line=mode_line; /*this is for over/underfull box messages*/
@y
set_line_break_params();
@z

@x
pack_begin_line=0;
@y
hrestore_param_list();
@z

@x
@<Get ready to start...@>=
link(temp_head)=link(head);
if (is_char_node(tail)) tail_append(new_penalty(inf_penalty))@;
else if (type(tail)!=glue_node) tail_append(new_penalty(inf_penalty))@;
else{@+type(tail)=penalty_node;delete_glue_ref(glue_ptr(tail));
  flush_node_list(leader_ptr(tail));penalty(tail)=inf_penalty;
  }
link(tail)=new_param_glue(par_fill_skip_code);
init_cur_lang=prev_graf%0200000;
init_l_hyf=prev_graf/020000000;
init_r_hyf=(prev_graf/0200000)%0100;
pop_nest();
@y
@<Get ready to start...@>=
link(temp_head)=par_ptr;
@z

@x
static pointer @!passive; /*most recent node on passive list*/
@y
@ @<Selected global variables@>=
static pointer @!passive; /*most recent node on passive list*/
@z

@x
static scaled @!active_width0[6], *const @!active_width = @!active_width0-1;
@y
@ @<Selected global variables@>=
static scaled @!active_width0[6], *const @!active_width = @!active_width0-1;
@z

@x
static bool @!no_shrink_error_yet; /*have we complained about infinite shrinkage?*/
@y
@ @<Selected global variables@>=
static bool @!no_shrink_error_yet; /*have we complained about infinite shrinkage?*/
@z

@x
if (no_shrink_error_yet)
  {@+no_shrink_error_yet=false;
#ifdef @!STAT
  if (tracing_paragraphs > 0) end_diagnostic(true);
#endif
@;
  print_err("Infinite glue shrinkage found in a paragraph");
@.Infinite glue shrinkage...@>
  help5("The paragraph just ended includes some glue that has",@/
  "infinite shrinkability, e.g., `\\hskip 0pt minus 1fil'.",@/
  "Such glue doesn't belong there---it allows a paragraph",@/
  "of any length to fit on one line. But it's safe to proceed,",@/
  "since the offensive shrinkability has been made finite.");
  error();
#ifdef @!STAT
  if (tracing_paragraphs > 0) begin_diagnostic();
#endif
@;
  }
@y
  QUIT("Infinite glue shrinkage found in a paragraph");
@z

@x
static pointer @!cur_p; /*the current breakpoint under consideration*/
@y
@ @<Selected global variables@>=
static pointer @!cur_p; /*the current breakpoint under consideration*/
@z

@x
static int @!minimal_demerits0[tight_fit-very_loose_fit+1], *const @!minimal_demerits = @!minimal_demerits0-very_loose_fit; /*best total
  demerits known for current line class and position, given the fitness*/
@y
@ @<Selected global variables@>=
static int @!minimal_demerits0[tight_fit-very_loose_fit+1], *const @!minimal_demerits = @!minimal_demerits0-very_loose_fit; /*best total
  demerits known for current line class and position, given the fitness*/
@z

@x
static scaled @!disc_width; /*the length of discretionary material preceding a break*/
@y
@ @<Selected global variables@>=
static scaled @!disc_width; /*the length of discretionary material preceding a break*/
@z

@x
static halfword @!easy_line; /*line numbers | > easy_line| are equivalent in break nodes*/
@y
@ @<Selected global variables@>=
static halfword @!easy_line; /*line numbers | > easy_line| are equivalent in break nodes*/
@z

@x
    {@+last_special_line=0;second_width=hsize;
@y
    {@+last_special_line=0;second_width=x;
@z

@x
else{@+last_special_line=info(par_shape_ptr)-1;
  second_width=mem[par_shape_ptr+2*(last_special_line+1)].sc;
  second_indent=mem[par_shape_ptr+2*last_special_line+1].sc;
  }
@y
else QUIT("parshape not yet implemented");
@z

@x
  {@+first_width=hsize-abs(hang_indent);
@y
  {@+first_width=x-abs(hang_indent);
@z

@x
  second_width=hsize;second_indent=0;
  }
else{@+first_width=hsize;first_indent=0;
  second_width=hsize-abs(hang_indent);
@y
  second_width=x;second_indent=0;
  }
else{@+first_width=x;first_indent=0;
  second_width=x-abs(hang_indent);
@z

@x
pointer @!q, @!r, @!s, @!prev_s; /*miscellaneous nodes of temporary interest*/
@y
pointer @!q, @!r, @!s; /*miscellaneous nodes of temporary interest*/
@z

@x
if (tracing_paragraphs > 0)
    {@+begin_diagnostic();print_nl("@@firstpass");@+} @;
@y
if (tracing_paragraphs > 0)
    {@+print_nl("@@firstpass");@+} @;
@z

@x
  if (tracing_paragraphs > 0) begin_diagnostic();
@y
@z

@x
  if (second_pass) @<Initialize for hyphenating a paragraph@>;
@y
@z

@x
if (tracing_paragraphs > 0)
      print_nl("@@emergencypass");@;
@y
if (tracing_paragraphs > 0)
      print_nl("@@emergencypass");@;
@z

@x
if (tracing_paragraphs > 0)
  {@+end_diagnostic(true);normalize_selector();
  }
@y
@z

@x
font_in_short_display=null_font
@y
@z

@x
  if (second_pass&&auto_breaking)
    @<Try to hyphenate the following word@>;
@y
@z

@x
{@+s=pre_break(cur_p);disc_width=0;
@y
{@+if (!is_auto_disc(cur_p) || second_pass || final_pass)
  {@+s=pre_break(cur_p);disc_width=0;
@z

@x
r=replace_count(cur_p);s=link(cur_p);
@y
}
r=replace_count(cur_p);s=link(cur_p);
@z

@x
static pointer @!best_bet; /*use this passive node and its predecessors*/
@y
@ @<Selected global variables@>=
static pointer @!best_bet; /*use this passive node and its predecessors*/
@z

@x
bool @!post_disc_break; /*and did it have a nonempty post-break part?*/
@y
bool @!post_disc_break; /*and did it have a nonempty post-break part?*/
bool @!first_line=true; /*Is this the first line of the paragraph?*/
uint32_t line_offset, next_offset; /*The first and next offset of the line. */
@z

@x
@/do@+{@<Justify the line ending at breakpoint |cur_p|, and append it to the current
vertical list, together with associated penalties and other insertions@>;
@y
next_offset=hposition(link(temp_head));
if (next_offset>node_pos)
  next_offset=next_offset-node_pos;
else
  next_offset=0;
@/do@+{
line_offset=next_offset;
{ pointer q=cur_break(cur_p);
  if (q==null)
    next_offset=(hstart-hpos); /*necessary if the paragraph has a display at |hpos|*/
  else
    next_offset= hposition(q);
  if (next_offset>node_pos)
    next_offset=next_offset-node_pos;
  else
    next_offset=0;
}
@<Justify the line ending at breakpoint |cur_p|, and append it to the current
vertical list, together with associated penalties and other insertions@>;
@z

@x
@ @<Change discretionary to compulsory...@>=
{@+t=replace_count(q);
@<Destroy the |t| nodes following |q|, and make |r| point to the following node@>;
if (post_break(q)!=null) @<Transplant the post-break list@>;
if (pre_break(q)!=null) @<Transplant the pre-break list@>;
link(q)=r;disc_break=true;
}
@y
@ @<Change discretionary to compulsory...@>=
{@+pointer pre_q = pre_break(q);
pointer post_q = post_break(q);
t=replace_count(q);
type(q)=whatsit_node;
subtype(q)=ignore_node;
ignore_info(q)=1;
@<Keep the |t| nodes following |q|, and make |r| point to the following node@>;
s=get_node(ignore_node_size);
type(s)=whatsit_node;
subtype(s)=ignore_node;
ignore_info(s)=0;
ignore_list(s)=null;
link(s)=r; r=s;
if (post_q!=null) @<Transplant the post-break list@>;
if (pre_q!=null) @<Transplant the pre-break list@>;
link(q)=r;disc_break=true;
}
@z

@x
@ @<Destroy the |t| nodes following |q|...@>=
if (t==0) r=link(q);
else{@+r=q;
  while (t > 1)
    {@+r=link(r);decr(t);
    }
  s=link(r);
  r=link(s);link(s)=null;
  flush_node_list(link(q));replace_count(q)=0;
  }
@y
@ @<Keep the |t| nodes following |q|...@>=
if (t==0) {ignore_list(q)=null; r=link(q);}
else{@+r=q;
  while (t > 1)
    {@+r=link(r);decr(t);
    }
  s=link(r);
  r=link(s);link(s)=null;
  ignore_list(q)=link(q);
  }
@z

@x
@<Transplant the post-break list@>=
{@+s=post_break(q);
while (link(s)!=null) s=link(s);
link(s)=r;r=post_break(q);post_break(q)=null;post_disc_break=true;
}
@y
@<Transplant the post-break list@>=
{@+s=post_q;
while (link(s)!=null) s=link(s);
link(s)=r;r=post_q;post_disc_break=true;
}
@z

@x
@<Transplant the pre-break list@>=
{@+s=pre_break(q);link(q)=s;
while (link(s)!=null) s=link(s);
pre_break(q)=null;q=s;
}
@y
@<Transplant the pre-break list@>=
{@+s=pre_q;link(q)=s;
while (link(s)!=null) s=link(s);
q=s;
}
@z

@x
r=new_param_glue(right_skip_code);link(r)=link(q);link(q)=r;q=r
@y
r=new_glue(right_skip);link(r)=link(q);link(q)=r;q=r
@z

@x
  {@+r=new_param_glue(left_skip_code);
@y
  {@+r=new_glue(left_skip);
@z

@x
append_to_vlist(just_box);
@y
if (first_line)
{ pointer p=happend_to_vlist(just_box);
  uint32_t pos=hposition(p);
  store_map(p,pos,line_offset);
  first_line=false;
}
else
  append_to_vlist(just_box,line_offset);
@z

@x
    {@+r=new_penalty(pen);
@y
    {@+r=new_penalty(pen); store_map(r, node_pos, next_offset);
@z

@x
small_number @!j; /*an index into |hc| or |hu|*/
int @!c; /*character being considered for hyphenation*/
@y
@z

@x
@t\4@>@<Declare the function called |reconstitute|@>@;
@y
@ @p
@z

@x
@<Declare procedures for preprocessing hyphenation patterns@>@;
@y
@z

@x
@p static pointer prune_page_top(pointer @!p) /*adjust top after page break*/
@y
\noindent
@(htex.c@>=

#define ensure_vbox(N) /* no longer needed */@#

static pointer prune_page_top(pointer @!p) /*adjust top after page break*/
@z

@x
{@+q=new_skip_param(split_top_skip_code);link(prev_p)=q;link(q)=p;
@y
{@+temp_ptr=new_spec(pointer_def[glue_kind][split_top_skip_no]);
q=new_glue(temp_ptr);glue_ref_count(temp_ptr)=null;link(prev_p)=q;link(q)=p;
@z

@x
@p static pointer vert_break(pointer @!p, scaled @!h, scaled @!d)
@y
@(htex.c@>=
static pointer vert_break(pointer @!p, scaled @!h, scaled @!d)
@z

@x
scaled @!best_height_plus_depth; /*height of the best box, without stretching or
  shrinking*/
@y
@ @<Selected global variables@>=
scaled @!best_height_plus_depth; /*height of the best box, without stretching or
  shrinking*/
@z

@x
  if ((shrink_order(q)!=normal)&&(shrink(q)!=0))
    {@+@t@>@;@/
    print_err("Infinite glue shrinkage found in box being split");@/
@.Infinite glue shrinkage...@>
    help4("The box you are \\vsplitting contains some infinitely",@/
      "shrinkable glue, e.g., `\\vss' or `\\vskip 0pt minus 1fil'.",@/
      "Such glue doesn't belong there; but you can safely proceed,",@/
      "since the offensive shrinkability has been made finite.");
    error();r=new_spec(q);shrink_order(r)=normal;delete_glue_ref(q);
    glue_ptr(p)=r;q=r;
    }
@y
  if ((shrink_order(q)!=normal)&&(shrink(q)!=0))
    {@+@t@>@;@/
    DBG(DBGTEX,"Infinite glue shrinkage found in box being split");
    r=new_spec(q);shrink_order(r)=normal;delete_glue_ref(q);
    glue_ptr(p)=r;q=r;
    }
@z

@x
@<Glob...@>=
pointer @!page_tail; /*the final node on the current page*/
@y
@<Selected global variables@>=
pointer @!page_tail; /*the final node on the current page*/
@z

@x
@<Glob...@>=
scaled @!page_so_far[8]; /*height and glue of the current page*/
static pointer @!last_glue; /*used to implement \.{\\lastskip}*/
static int @!last_penalty; /*used to implement \.{\\lastpenalty}*/
static scaled @!last_kern; /*used to implement \.{\\lastkern}*/
@y
@<Selected global variables@>=
scaled @!page_so_far[8]; /*height and glue of the current page*/
@z

@x
@p void freeze_page_specs(small_number @!s)
@y
@(htex.c@>=
void freeze_page_specs(small_number @!s)
@z

@x
page_goal=vsize;page_max_depth=max_depth;
@y
page_goal=hvsize;page_max_depth=max_depth;
@z

@x
#ifdef @!STAT
if (tracing_pages > 0)
  {@+begin_diagnostic();
  print_nl("%% goal height=");print_scaled(page_goal);
@.goal height@>
  print(", max depth=");print_scaled(page_max_depth);
  end_diagnostic(false);
  } @;
#endif
@y
@z

@x
last_glue=max_halfword;last_penalty=0;last_kern=0;
@y
@z

@x
@p @t\4@>@<Declare the procedure called |fire_up|@>@;@/
static void build_page(void) /*append contributions to the current page*/
@y
@
@(htex.c@>=
bool hbuild_page(void) /*append contributions to the current page*/
@z

@x
int @!n; /*insertion box number*/
scaled @!delta, @!h, @!w; /*sizes used for insertion calculations*/
if ((link(contrib_head)==null)||output_active) return;
@y
if (link(contrib_head)==null) return false;
@z

@x
@<Update the values of |last_glue|, |last_penalty|, and |last_kern|@>;
@y
@z

@x
}
@y
return false;
}
@z

@x
  else if (link(p)==null) return;
@y
  else if (link(p)==null) return false;
@z

@x
case ins_node: @<Append an insertion to the current page and |goto contribute|@>@;
@y
case ins_node: happend_insertion(p); goto contribute;
@z

@x
q=new_skip_param(top_skip_code); /*now |temp_ptr==glue_ptr(q)|*/
@y
temp_ptr=new_spec(pointer_def[glue_kind][top_skip_no]);
q=new_glue(temp_ptr);glue_ref_count(temp_ptr)=null;
@z

@x
  if ((shrink_order(q)!=normal)&&(shrink(q)!=0))
    {@+@t@>@;@/
    print_err("Infinite glue shrinkage found on current page");@/
@.Infinite glue shrinkage...@>
    help4("The page about to be output contains some infinitely",@/
      "shrinkable glue, e.g., `\\vss' or `\\vskip 0pt minus 1fil'.",@/
      "Such glue doesn't belong there; but you can safely proceed,",@/
      "since the offensive shrinkability has been made finite.");
    error();
    r=new_spec(q);shrink_order(r)=normal;delete_glue_ref(q);
    glue_ptr(p)=r;q=r;
    }
@y
  if ((shrink_order(q)!=normal)&&(shrink(q)!=0))
    {@+@t@>@;@/
     DBG(DBGTEX,"Infinite glue shrinkage found on current page");
    r=new_spec(q);shrink_order(r)=normal;fast_delete_glue_ref(q);
    glue_ptr(p)=r;q=r;
    }
@z

@x
#ifdef @!STAT
  if (tracing_pages > 0) @<Display the page break cost@>;
#endif
@y
@z

@x
    {@+fire_up(p); /*output the current page at the best place*/
    if (output_active) return; /*user's output routine will act*/
    goto done; /*the page has been shipped out by default output routine*/
    }
@y
{ hloc_set_next(best_page_break);
  if (p==best_page_break) best_page_break=null;
  hpack_page();
  hfill_page_template();
  return true;
}
@z

@x
@ @<Append an insertion to the current page and |goto contribute|@>=
{@+if (page_contents==empty) freeze_page_specs(inserts_only);
@y
@ @(htex.c@>=
void happend_insertion(pointer p)@/
{ uint8_t @!n; /*insertion box number*/
  scaled @!delta, @!h, @!w; /*sizes used for insertion calculations*/
  pointer q,r;
  if (page_contents==empty) freeze_page_specs(inserts_only);
@z

@x
goto contribute;
@y
@z

@x
if ((shrink_order(q)!=normal)&&(shrink(q)!=0))
  {@+print_err("Infinite glue shrinkage inserted from ");print_esc("skip");
@.Infinite glue shrinkage...@>
  print_int(n);
  help3("The correction glue for page breaking with insertions",@/
    "must have finite shrinkability. But you may proceed,",@/
    "since the offensive shrinkability has been made finite.");
  error();
  }
@y
if ((shrink_order(q)!=normal)&&(shrink(q)!=0))
  DBG(DBGTEX,"Infinite glue shrinkage inserted from stream %d",n);
@z

@x
#ifdef @!STAT
if (tracing_pages > 0) @<Display the insertion split cost@>;
#endif
@y
@z

@x
@<Ensure that box 255 is empty before output@>;
insert_penalties=0; /*this will count the number of insertions held over*/
save_split_top_skip=split_top_skip;
if (holding_inserts <= 0)
  @<Prepare all the boxes involved in insertions to act as queues@>;
q=hold_head;link(q)=null;prev_p=page_head;p=link(prev_p);
while (p!=best_page_break)
  {@+if (type(p)==ins_node)
    {@+if (holding_inserts <= 0)
       @<Either insert the material specified by node |p| into the appropriate box,
or hold it for the next page; also delete node |p| from the current page@>;
    }
  else if (type(p)==mark_node) @<Update the values of |first_mark| and |bot_mark|@>;
  prev_p=p;p=link(prev_p);
  }
split_top_skip=save_split_top_skip;
@<Break the current page at node |p|, put it in box~255, and put the remaining nodes
on the contribution list@>;
@<Delete \(t)the page-insertion nodes@>@;
@y
hpack_page();

@ @(htex.c@>=
void hpack_page(void)
{
pointer p, @!q, @!r, @!s; /*nodes being examined and/or changed*/
pointer @!prev_p; /*predecessor of |p|*/
uint8_t @!n; /*insertion box number*/
bool @!wait; /*should the present insertion be held over?*/
pointer @!save_split_top_skip; /*saved value of |split_top_skip|*/
#if 0
     print_str("\npage_head:\n");
     show_box(link(page_head));
     print_str("\nstream 0:\n");
     show_box(streams[0].p);
     print_str("\nstream 1:\n");
     show_box(streams[1].p);
#endif
if (box(0)!=null)
{ flush_node_list(box(0)); box(0)=null; }
insert_penalties=0; /*this will count the number of insertions held over*/
save_split_top_skip=split_top_skip;
@<Prepare all the boxes involved in insertions to act as queues@>;
q=hold_head;link(q)=null;prev_p=page_head;p=link(prev_p);
while (p!=best_page_break)
  {@+if (type(p)==ins_node)
    {@<Either insert the material specified by node |p| into the appropriate box,
or hold it for the next page; also delete node |p| from the current page@>;
  }
  prev_p=p;p=link(prev_p);
  }
split_top_skip=save_split_top_skip;
@<Break the current page at node |p|, put it in box~255, and put the remaining nodes
on the contribution list@>;
@<Delete \(t)the page-insertion nodes@>;
}
@z

@x
save_vbadness=vbadness;vbadness=inf_bad;
save_vfuzz=vfuzz;vfuzz=max_dimen; /*inhibit error messages*/
box(255)=vpackage(link(page_head), best_size, exactly, page_max_depth);
vbadness=save_vbadness;vfuzz=save_vfuzz;
if (last_glue!=max_halfword) delete_glue_ref(last_glue);
@<Start a new current page@>; /*this sets |last_glue=max_halfword|*/
if (q!=hold_head)
  {@+link(page_head)=link(hold_head);page_tail=q;
  }
@y
streams[0].p=link(page_head); link(page_head)=null; page_tail=page_head;
streams[0].t=prev_p;
if (q!=hold_head)
  {@+link(q)=link(contrib_head);
     link(contrib_head)=link(hold_head);
  }
@z

@x
best_ins_ptr(r)=null;
@y
while (link(s)!=null) s=link(s);
best_ins_ptr(r)=null;
@z

@x
box(n)=vpack(temp_ptr, natural);
@y
streams[n].p=temp_ptr;
streams[n].t=s;
@z

@x
ship_out(box(255));box(255)=null;
@y
@z

@x
@<Go into display math mode@>=
{@+if (head==tail)  /*`\.{\\noindent\$\$}' or `\.{\$\${ }\$\$}'*/
  {@+pop_nest();w=-max_dimen;
  }
else{@+line_break(display_widow_penalty);@/
@y
@<Go into display math mode@>=
@ @(htex.c@>=
void hdisplay(pointer p, pointer a, bool l)
{@+
scaled x; /* the |hsize| in the enclosing paragraph */
uint32_t offset=node_pos-node_pos1; /* offset of the display node in the current parragraph */
{scaled w; /*new or partial |pre_display_size|*/
scaled @!l; /*new |display_width|*/
scaled @!s; /*new |display_indent|*/
pointer @!p; /*current node when calculating |pre_display_size|*/
pointer @!q; /*glue specification when calculating |pre_display_size|*/
internal_font_number @!f; /*font in current |char_node|*/
int @!n; /*scope of paragraph shape specification*/
scaled @!v; /*|w| plus possible glue amount*/
scaled @!d; /*increment to |v|*/

if (head==tail)  /*`\.{\\noindent\$\$}' or `\.{\$\${ }\$\$}'*/
  {@+pop_nest();w=-max_dimen; x=cur_list.hs_field; offset=0;
  }
else{@+ pointer par_ptr=link(head);
     pop_nest();
     store_map(par_ptr,node_pos,0);
     line_break(display_widow_penalty,par_ptr);@/
     x=cur_list.hs_field;
@z

@x
push_math(math_shift_group);mode=mmode;
eq_word_define(int_base+cur_fam_code,-1);@/
eq_word_define(dimen_base+pre_display_size_code, w);
eq_word_define(dimen_base+display_width_code, l);
eq_word_define(dimen_base+display_indent_code, s);
if (every_display!=null) begin_token_list(every_display, every_display_text);
if (nest_ptr==1) build_page();
@y
pre_display_size=w;@+display_width=l; display_indent=s;
@z

@x
v=shift_amount(just_box)+2*quad(cur_font);w=-max_dimen;
@y
v=shift_amount(just_box)+2*dimen_def[quad_no];w=-max_dimen;
@z

@x
    {@+l=hsize-abs(hang_indent);
@y
    {@+l=x-abs(hang_indent);
@z

@x
  else{@+l=hsize;s=0;
@y
  else{@+l=x;s=0;
@z

@x
@<Finish displayed math@>=
cur_mlist=p;cur_style=display_style;mlist_penalties=false;
mlist_to_hlist();p=link(temp_head);@/
adjust_tail=adjust_head;b=hpack(p, natural);p=list_ptr(b);
t=adjust_tail;adjust_tail=null;@/
w=width(b);z=display_width;s=display_indent;
@y
@<Finish displayed math@>=
@ @(htex.c@>=
{@<Local variables for finishing a displayed formula@>@;
adjust_tail=adjust_head;b=hpack(p, natural);p=list_ptr(b);
t=adjust_tail;adjust_tail=null;@/
w=width(b);z=display_width;s=display_indent;
@z

@x
if ((a==null)||danger)
@y
if (a==null)
@z

@x
else{@+e=width(a);q=e+math_quad(text_size);
@y
else{@+e=width(a);q=e+math_quad;
@z

@x
resume_after_display()
@y
prev_graf=prev_graf+3;
cur_list.bs_pos=hpos+node_pos;
push_nest();mode=hmode;
} /* end of \<Finish displayed math> */
} /* end of |hdisplay| */
@z

@x
tail_append(new_penalty(pre_display_penalty));@/
if ((d+s <= pre_display_size)||l)  /*not enough clearance*/
  {@+g1=above_display_skip_code;g2=below_display_skip_code;
  }
else{@+g1=above_display_short_skip_code;
  g2=below_display_short_skip_code;
  }
if (l&&(e==0))  /*it follows that |type(a)==hlist_node|*/
  {@+shift_amount(a)=s;append_to_vlist(a);
  tail_append(new_penalty(inf_penalty));
  }
else tail_append(new_param_glue(g1))
@y
tail_append(new_penalty(pre_display_penalty));@/
store_map(tail, node_pos, offset);
if ((d+s <= pre_display_size)||l)  /*not enough clearance*/
  {@+g1=above_display_skip_no;g2=below_display_skip_no;
  }
else{@+g1=above_display_short_skip_no;
  g2=below_display_short_skip_no;
  }
if (l&&(e==0))  /*it follows that |type(a)==hlist_node|*/
  {@+shift_amount(a)=s;append_to_vlist(a,offset);
  tail_append(new_penalty(inf_penalty)); store_map(tail, node_pos, offset);
  }
else {tail_append(new_glue(pointer_def[glue_kind][g1])); store_map(tail, node_pos, offset); }
@z

@x
shift_amount(b)=s+d;append_to_vlist(b)
@y
shift_amount(b)=s+d;append_to_vlist(b,offset)
@z

@x
  append_to_vlist(a);
@y
  append_to_vlist(a,offset);
@z

@x
tail_append(new_penalty(post_display_penalty));
if (g2 > 0) tail_append(new_param_glue(g2))
@y
tail_append(new_penalty(post_display_penalty));
offset=(hpos-hstart)+1-node_pos; /*offset after the display*/
store_map(tail, node_pos,offset);
if (g2 > 0) { tail_append(new_glue(pointer_def[glue_kind][g2]));store_map(tail, node_pos, offset);}
@z

@x
@d open_ext(A) link(A+2) /*string number of file extension for |open_name|*/
@y
@d open_ext(A) link(A+2) /*string number of file extension for |open_name|*/  @#

@d par_node         6 /*|subtype| that records the change of a parameter*/
@d par_node_size 3 /* number of memory words in a |par_node| */
@d par_type(A) type(A+1) /* type of parameter */
@d int_type   0 /* type of an |int_par| node */
@d dimen_type  1 /* type of an |dimen_par| node */
@d glue_type  2 /* type of an |glue_par| node */
@d par_number(A) subtype(A+1) /* the parameter number */
@d par_value(A)  mem[A+2] /* the parameter value */@#

@d graf_node        7 /*|subtype|  that records a paragraph*/
@d graf_node_size 5 /* number of memory words in a |graf_node| */
@d graf_penalty(A)  mem[A+1].i /* the final penalty */
@d graf_extent(A)   link(A+3) /* the extent */@#
@d graf_params(A)   info(A+4) /* list of parameter nodes */
@d graf_list(A)     link(A+4) /* list of content nodes */

@d disp_node           8 /*|subtype| that records a math display*/
@d disp_node_size    3 /* number of memory words in a |disp_node| */
@d display_left(A)    type(A+1) /* 1=left 0=right */
@d display_no_bs(A)    subtype(A+1) /* |prev_depth==ignore_depth| */
@d display_params(A)   link(A+1) /* list of parameter nodes */
@d display_formula(A)  link(A+2) /* formula list */
@d display_eqno(A)     info(A+2) /* box with equation number */@#

@d baseline_node    9  /*|subtype| that records a |baseline_skip| */
@d baseline_node_size small_node_size /* This is 2; we will convert baseline nodes to glue nodes */
@d baseline_node_no(A) mem[A+1].i /* baseline reference */@#

@d image_node    10 /*|subtype| that records an image */
@d image_node_size 9  /* width, depth, height, |shift_amount| like a hbox */
@d image_width(A)  width(A)  /*width of image */
@d image_height(A) height(A) /*height of image */
@d image_depth(A)  depth(A) /* depth of image==zero */
@d image_no(A)     mem[A+4].i   /* the section number */
@d image_stretch(A) mem[A+5].sc  /*stretchability of image */
@d image_shrink(A) mem[A+6].sc  /*shrinkability of image */
@d image_stretch_order(A) stretch_order(A+7)
@d image_shrink_order(A) shrink_order(A+7)
@d image_name(A)   link(A+7) /*string number of file name */
@d image_area(A)   info(A+8) /*string number of file area */
@d image_ext(A)    link(A+8) /*string number of file extension */@#

@d hpack_node         12 /* a hlist that needs to go to hpack */
@d vpack_node         13 /* a vlist that needs to go to vpackage */
@d pack_node_size       box_node_size /* a box node up to |list_ptr|*/
@d pack_m(A)  type(A+list_offset) /* either additional or exactly */
@d pack_limit(A)        mem[(A)+1+list_offset].sc /* depth limit in |vpack| */
@d pack_extent(A) link(A+2+list_offset) /* extent */@#

@d hset_node         14  /* represents a hlist that needs |glue_set| */
@d vset_node         15  /* represents a vlist that needs |glue_set| */
@d set_node_size     box_node_size /* up to |list_ptr| like a box node */
@d set_stretch_order glue_sign
@d set_shrink_order  glue_order
@d set_stretch(A)    mem[(A)+1+list_offset].sc /* replaces |glue_set| */
@d set_extent(A)     pack_extent(A) /* extent */
@d set_shrink(A)     mem[(A)+3+list_offset].sc @#

@d align_node          16 /* represents an alignment */
@d align_node_size     4
@d align_extent(A)     link(A+2) /* the extent of the alignment */
@d align_m(A)          type(A+2) /* either additional or exactly */
@d align_v(A)          subtype(A+2) /* true if vertical */
@d align_preamble(A)   info(A+3) /* the preamble */
@d align_list(A)       link(A+3) /* the unset rows/columns */

@d setpage_node       17 /* represents a page template */
@d setpage_node_size  6
@d setpage_name(A)    link(A+1)
@d setpage_number(A)  type(A+1) /* the \HINT/ number */
@d setpage_id(A)      subtype(A+1)  /* the \TeX\ number */
@d setpage_priority(A) info(A+2)
@d setpage_topskip(A) link(A+2)
@d setpage_depth(A)   mem[A+3].sc /* maximum depth */
@d setpage_height(A)  info(A+4) /* extended dimension number */
@d setpage_width(A)   link(A+4) /* extended dimension number */
@d setpage_list(A)    info(A+5) /* the template itself */
@d setpage_streams(A) link(A+5)   /* list of stream definitions */

@d setstream_node         18 /* represents a stream definition */
@d setstream_node_size    6
@d setstream_number(A)    type(A+1)
@d setstream_insertion(A) subtype(A+1)
@d setstream_mag(A)       link(A+1) /* magnification factor */
@d setstream_prefered(A)  type(A+2)
@d setstream_next(A)      subtype(A+2)
@d setstream_ratio(A)     link(A+2) /* split ratio */
@d setstream_max(A)       info(A+3) /* extended dimension number */
@d setstream_width(A)     link(A+3) /* extended dimension number */
@d setstream_topskip(A)   info(A+4)
@d setstream_height(A)    link(A+4)
@d setstream_before(A)    info(A+5)
@d setstream_after(A)     link(A+5)

@d stream_node     19 /* represents a stream insertion point */
@d stream_node_size 2
@d stream_number(A)   type(A+1)
@d stream_insertion(A) subtype(A+1)

@d stream_after_node  20 /* never allocated */
@d stream_before_node 21 /* never allocated */

@d xdimen_node 22
@d xdimen_node_size    4
@d xdimen_ref_count(A) link(A)
@d xdimen_width(A)     mem[A+1].sc
@d xdimen_hfactor(A)   mem[A+2].sc
@d xdimen_vfactor(A)   mem[A+3].sc

@d ignore_node 23 /* ignored used to attach extra information */
@d ignore_node_size small_node_size /* same as |disc_node| */
@d ignore_info(A)    type(A+1)
@d ignore_list(A)    link(A+1)

@d label_node 24 /* represents a link to a another location */
@d label_node_size 2
@d label_has_name(A)  type(A+1) /* 1 for a name , 0 for a number */
@d label_where(A)  subtype(A+1) /* 1 for top, 2 for bot, 3 for mid */
@d label_ptr(A) link(A+1) /* for a name the token list or the number */
@d label_ref(A) link(A+1) /*alternatively the label number */

@d start_link_node 25 /* represents a link to a another location */
@d end_link_node 26 /* represents a link to a another location */
@d link_node_size 2 /* second word like a |label_node| */

@d outline_node 27 /* represents an outline item */
@d outline_node_size 4 /* second word like a |label_node| */
@d outline_ptr(A)   link(A+2) /* text to be displayed */
@d outline_depth(A) mem[A+3].i /* depth of sub items */

@z

@x
  case special_node: print_esc("special");@+break;
@y
  case special_node: print_esc("special");@+break;
  case par_node: print("parameter");@+break;
  case graf_node: print("paragraf");@+break;
  case disp_node: print("display");@+break;
  case baseline_node: print("baselineskip");@+break;
  case hpack_node: print("hpack");@+break;
  case vpack_node: print("vpack");@+break;
  case hset_node: print("hset");@+break;
  case vset_node: print("vset");@+break;
  case image_node: print("image");@+break;
  case start_link_node: print("startlink");@+break;
  case end_link_node: print("endlink");@+break;
  case label_node: print("dest");@+break;
  case outline_node: print("outline");@+break;
  case align_node: print("align");@+break;
  case setpage_node: print("setpage");@+break;
  case setstream_node: print("setstream");@+break;
  case stream_node: print("stream");@+break;
  case xdimen_node: print("xdimen");@+break;
  case ignore_node: print("ignore");@+break;
@z

@x
case special_node: @<Implement \.{\\special}@>@;@+break;
@y
case special_node: @<Implement \.{\\special}@>@;@+break;
case par_node:
case graf_node:
case disp_node:
case baseline_node:
case hpack_node:
case vpack_node:
case hset_node:
case vset_node:
case align_node: @+break;@#
case image_node: break; /* see section~\secref{imageext}, page~\pageref{imageext} */
case label_node: /* see section~\secref{linkext}, page~\pageref{linkext} */
case outline_node:
case start_link_node: case end_link_node: @+break;@#
case setpage_node: break; /* see section~\secref{pageext}, page~\pageref{pageext} */
case stream_node:
case setstream_node:
case stream_before_node:
case stream_after_node:
case xdimen_node:
case ignore_node: @+break;
@z

@x
static void print_write_whatsit(char *@!s, pointer @!p)
@y
static void print_mark(int @!p);
static void print_label(pointer @!p)
{ print("goto ");
  if (label_has_name(p)) { print("name "); print_mark(label_ptr(p));}
  else { print("num "); print_int(label_ptr(p));}
}

static void print_write_whatsit(char *@!s, pointer @!p)
@z

@x
case open_node: {@+print_write_whatsit("openout", p);
  print_char('=');printn_file_name(open_name(p), open_area(p), open_ext(p));
  } @+break;
case write_node: {@+print_write_whatsit("write", p);
  print_mark(write_tokens(p));
  } @+break;
case close_node: print_write_whatsit("closeout", p);@+break;
@y
@z

@x
default:print("whatsit?");
}
@y
case par_node: print_esc("parameter ");
  print_int(par_type(p));print_char(',');print_int(par_number(p));
  print_char(':');print_int(par_value(p).i);
  break;
case graf_node: print_esc("paragraf(");
  print_int(graf_penalty(p));
  print_char(')');
  node_list_display(graf_params(p));
  node_list_display(graf_list(p));
  print_xdimen(graf_extent(p));
  break;
case disp_node: print_esc("display ");
  node_list_display(display_eqno(p));
  if (display_left(p)) print("left "); else  print("right ");
  node_list_display(display_formula(p));
  node_list_display(display_params(p));
  break;
case hset_node: case vset_node:
  print_char('\\');
  print_char(subtype(p)==hset_node?'h':'v');
  print("set(");
  print_scaled(height(p)); print_char('+');
  print_scaled(depth(p)); print(")x"); print_scaled(width(p));
  if (shift_amount(p)!=0)
    {@+print(", shifted ");print_scaled(shift_amount(p));
    }
  if (set_stretch(p)!=0)
  {@+print(", stretch ");print_glue(set_stretch(p),set_stretch_order(p),"pt");
    }
  if (set_shrink(p)!=0)
  {@+print(", shrink ");print_glue(set_shrink(p),set_shrink_order(p),"pt");
    }
  print(", extent "); print_xdimen(set_extent(p));
  node_list_display(list_ptr(p)); /*recursive call*/
  break;
case hpack_node: case vpack_node:
  print_char('\\');
  print_char(subtype(p)==hpack_node?'h':'v');
  print("pack(");
  print(pack_m(p)==exactly?"exactly ":"additional ");
  print_xdimen(pack_extent(p));
  if (subtype(p)==vpack_node && pack_limit(p)!=max_dimen) { print(", limit "); print_scaled(pack_limit(p)); }
  print_char(')');
  node_list_display(list_ptr(p));
  break;
case image_node:
  print_esc("image(");
  print_char('(');print_scaled(image_height(p));
   print_char('+'); print_scaled(image_depth(p));
   print(")x"); print_scaled(image_width(p));
  if (image_stretch(p)!=0) { print(" plus ");print_glue(image_stretch(p), image_stretch_order(p),"pt"); }
  if (image_shrink(p)!=0) { print(" minus ");print_glue(image_shrink(p), image_shrink_order(p), "pt"); }
  print(", section ");print_int(image_no(p));
  if (dir[image_no(p)].file_name!=NULL) {print(", "); print(dir[image_no(p)].file_name);}
  break;
case align_node:
  print_esc("align(");
  print(align_m(p)==exactly?"exactly ":"additional ");
  print_xdimen(align_extent(p));print_char(')');
  node_list_display(align_preamble(p));
  print_char(':');
  node_list_display(align_list(p));
  break;
case ignore_node:
  print_esc("ignore ");print_int(ignore_info(p));print_char(':');
  node_list_display(ignore_list(p));
  break;
case start_link_node:
  print_esc("startlink ");
  print_label(p);
  break;
case end_link_node:
  print_esc("endlink ");
  break;
case stream_node:
  print_esc("stream");print_int(stream_insertion(p));
  print_char('(');print_int(stream_number(p));print_char(')');
  break;
default: print("whatsit?");
}
@z

@x
default:confusion("ext2");
@y
case par_node:
{@+r=get_node(par_node_size);
  if (par_type(p)==glue_type) add_glue_ref(par_value(p).i);
  words=par_node_size;
  } @+break;
case graf_node:
{@+r=get_node(graf_node_size);
  add_xdimen_ref(graf_extent(p));
  graf_params(r)=copy_node_list(graf_params(p));
  graf_list(r)=copy_node_list(graf_list(p));
  words=graf_node_size-1;
  } @+break;
case disp_node:
{@+r=get_node(disp_node_size);
  display_left(r)=display_left(p);
  display_no_bs(r)=display_no_bs(p);
  display_eqno(r)=copy_node_list(display_eqno(p));
  display_formula(r)=copy_node_list(display_formula(p));
  display_params(r)=copy_node_list(display_params(p));
  words=disp_node_size-2;
  } @+break;
case baseline_node:
{@+r=get_node(baseline_node_size);
  words=baseline_node_size;
  } @+break;
case hpack_node: case vpack_node:
{@+r=get_node(pack_node_size);
  pack_m(r)=pack_m(p);
  list_ptr(r)=copy_node_list(list_ptr(p));
  add_xdimen_ref(pack_extent(p));
  pack_limit(r)=pack_limit(p);
  words=pack_node_size-3;
  } @+break;
case hset_node: case vset_node:
{@+r=get_node(set_node_size);
  mem[r+8]=mem[p+8];mem[r+7]=mem[p+7];mem[r+6]=mem[p+6];mem[r+5]=mem[p+5]; /*copy the last four words*/
  add_xdimen_ref(set_extent(p));
  list_ptr(r)=copy_node_list(list_ptr(p)); /*this affects |mem[r+5]|*/
  words=5;
  } @+break;
case image_node:
    r=get_node(image_node_size);
    words=image_node_size;
    break;
case align_node:
  {@+r=get_node(align_node_size);
     align_preamble(r)=copy_node_list(align_preamble(p));
     align_list(r)=copy_node_list(align_list(p));
     add_xdimen_ref(align_extent(p));
     words=align_node_size-1;
  } @+break;
case setpage_node:
  {@+r=get_node(setpage_node_size);
     add_glue_ref(setpage_topskip(p));
     add_xdimen_ref(setpage_height(p));
     add_xdimen_ref(setpage_width(p));
     setpage_list(r)=copy_node_list(setpage_list(p));
     setpage_streams(r)=copy_node_list(setpage_streams(p));
     words=setpage_node_size-1;
  } @+break;
case setstream_node:
  {@+r=get_node(setstream_node_size);
     add_xdimen_ref(setstream_max(p));
     add_xdimen_ref(setstream_width(p));
     add_glue_ref(setstream_topskip(p));
     add_glue_ref(setstream_height(p));
    setstream_before(r)=copy_node_list(setstream_before(p));
    setstream_after(r)=copy_node_list(setstream_after(p));
    words=setstream_node_size-1;
  } @+break;
case ignore_node:
    r=get_node(ignore_node_size);
    ignore_info(r)=ignore_info(p);
    ignore_list(r)=copy_node_list(ignore_list(p));
    words=ignore_node_size-1;
  break;
case start_link_node:
    r=get_node(link_node_size);
    if (label_has_name(p)) add_token_ref(label_ptr(p));
    words=link_node_size;
    break;
case end_link_node:
    r=get_node(link_node_size);
    words=link_node_size;
    break;
case label_node:
    r=get_node(label_node_size);
    if (label_has_name(p)) add_token_ref(label_ptr(p));
    words=label_node_size;
    break;
case outline_node:
    r=get_node(outline_node_size);
    if (label_has_name(p)) add_token_ref(label_ptr(p));
    outline_ptr(r)=copy_node_list(outline_ptr(p));
    words=outline_node_size-1;
    break;
case stream_node:
    r=get_node(stream_node_size);
    words=stream_node_size;
  break;
case xdimen_node:
    r=get_node(xdimen_node_size);
    words=xdimen_node_size;
  break;
default:confusion("ext2");
@z

@x
case open_node: free_node(p, open_node_size);@+break;
case write_node: case special_node: {@+delete_token_ref(write_tokens(p));
  free_node(p, write_node_size);goto done;
  }
case close_node: case language_node: free_node(p, small_node_size);@+break;
@y
case close_node: case language_node: free_node(p, small_node_size);@+break;
case par_node:
  if (par_type(p)==glue_type) fast_delete_glue_ref(par_value(p).i);
  free_node(p, par_node_size);@+break;
case graf_node:
  delete_xdimen_ref(graf_extent(p));
  flush_node_list(graf_params(p));
  flush_node_list(graf_list(p));
  free_node(p, graf_node_size);@+break;
case disp_node:
  flush_node_list(display_eqno(p));
  flush_node_list(display_formula(p));
  flush_node_list(display_params(p));
  free_node(p, disp_node_size);@+break;
case  baseline_node:
  free_node(p, baseline_node_size);@+break;
case  hpack_node: case  vpack_node:
  delete_xdimen_ref(pack_extent(p));
  flush_node_list(list_ptr(p));
  free_node(p, pack_node_size);@+break;
case  hset_node: case  vset_node:
  delete_xdimen_ref(set_extent(p));
  flush_node_list(list_ptr(p));
  free_node(p, set_node_size);@+break;
case image_node:
  free_node(p,image_node_size);@+break;
case align_node:
  delete_xdimen_ref(align_extent(p));
  flush_node_list(align_preamble(p));
  flush_node_list(align_list(p));
  free_node(p, align_node_size);@+break;
case setpage_node:
  delete_glue_ref(setpage_topskip(p));
  delete_xdimen_ref(setpage_height(p));
  delete_xdimen_ref(setpage_width(p));
  flush_node_list(setpage_list(p));
  flush_node_list(setpage_streams(p));
  free_node(p, setpage_node_size);@+break;
case setstream_node:
  delete_xdimen_ref(setstream_max(p));
  delete_xdimen_ref(setstream_width(p));
  delete_glue_ref(setstream_topskip(p));
  delete_glue_ref(setstream_height(p));
  flush_node_list(setstream_before(p));
  flush_node_list(setstream_after(p));
  free_node(p,setstream_node_size); @+break;
case ignore_node:
  flush_node_list(ignore_list(p));
  free_node(p,ignore_node_size); @+break;
case start_link_node:
  if (label_has_name(p)) delete_token_ref(label_ptr(p));
  free_node(p,link_node_size);@+break;
case end_link_node:
  free_node(p,link_node_size);@+break;
case label_node:
  if (label_has_name(p)) delete_token_ref(label_ptr(p));
  free_node(p,label_node_size);@+break;
case outline_node:
  if (label_has_name(p)) delete_token_ref(label_ptr(p));
  flush_node_list(outline_ptr(p));
  free_node(p,outline_node_size);@+break;
case stream_node:
  free_node(p,stream_node_size); @+break;
case xdimen_node:
  free_node(p,xdimen_node_size);
@z

@x
@ @<Incorporate a whatsit node into a vbox@>=do_nothing
@y
@ @<Incorporate a whatsit node into a vbox@>=
if (subtype(p)==image_node)
{ @+glue_ord o;
  if (image_width(p)> w) w= image_width(p);
  x= x+d+image_height(p);d=0;
  o= image_stretch_order(p);total_stretch[o]= total_stretch[o]+image_stretch(p);
  o= image_shrink_order(p);total_shrink[o]= total_shrink[o]+image_shrink(p);
}
@z

@x
@ @<Incorporate a whatsit node into an hbox@>=do_nothing
@y
@ @<Incorporate a whatsit node into an hbox@>=
if (subtype(p)==image_node)
{@+glue_ord o;
  if (image_height(p)> h) h= image_height(p);
  x= x+image_width(p);
  o= image_stretch_order(p);total_stretch[o]= total_stretch[o]+image_stretch(p);
  o= image_shrink_order(p);total_shrink[o]= total_shrink[o]+image_shrink(p);
}
@z

@x
@ @d adv_past(A) @+if (subtype(A)==language_node)
    {@+cur_lang=what_lang(A);l_hyf=what_lhm(A);r_hyf=what_rhm(A);@+}
@y
@ @d adv_past(A) {}
@z

@x
switch (subtype(p)) {
case open_node: case write_node: case close_node: @<Do some work that has been queued
up for \.{\\write}@>@;@+break;
case special_node: special_out(p);@+break;
case language_node: do_nothing;@+break;
default:confusion("ext4");
@:this can't happen ext4}{\quad ext4@>
}
@y
if (subtype(p)==open_node||subtype(p)==write_node||subtype(p)==close_node)
@<Do some work that has been queued up for \.{\\write}@>@;
@z

@x
@(bigtex.h@>=
@h
enum {@+@<Constants in the outer block@>@+};
@<Types in the outer block@>@;
@y
@(htex.h@>=
@h
enum {@+@<Constants in the outer block@>@+};
@<Types in the outer block@>@;
extern void list_init(void);
extern void hpack_page(void);
extern void happend_insertion(pointer p);
extern bool hbuild_page(void);
extern void hdisplay(pointer p, pointer a, bool l);
extern void mem_init(void);
@z

@x
extern str_number *const font_name;
extern internal_font_number read_font_info(pointer @!u, str_number @!nom, str_number @!aire,
  scaled @!s);
@y
extern char **const font_name;
extern void hclear_fonts(void);
extern void read_font_info(int f, char *@!nom, scaled @!s);
@z

@x
extern void append_to_vlist(pointer @!b);
@y
extern void append_to_vlist(pointer @!b, uint32_t offset);
@z

@x
extern void line_break(int @!final_widow_penalty);
@y
void line_break(int final_widow_penalty, pointer par_ptr);
@z
