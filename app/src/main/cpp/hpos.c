#include <string.h>
#include "basetypes.h"
#include "hformat.h"
#include "htex.h"
#include "error.h"
#include "hpos.h"
#include "htexdef.h"


//#pragma warning(disable : 4127) 

/* THE PAGE POSITION CACHE */

#define MAX_PAGE_POS 16

static hpos_t page_pos[MAX_PAGE_POS];
static int first_pos=-1, cur_pos=-1, last_pos=-1, home_pos=-1; 

/* increment and decrement position with wrap arround */
#define incr_pos(X) {X++;if(X>=MAX_PAGE_POS)X=0;}
#define decr_pos(X) {X--;if(X<0)X=MAX_PAGE_POS-1;}

static void hpos_default(int i)
/* set position i to some reasonable default values */
{ page_pos[i].pos=0;
  page_pos[i].offset=0;
  page_pos[i].f=0;
}


void hpos_init(void)
/* initialize the page position buffer to the home position*/
{ first_pos=cur_pos=last_pos=home_pos=0;
  hpos_default(home_pos);
}

void hpos_clear(void)
/* clear the page position cache, except for the current position */
{ home_pos=-1;
  first_pos=last_pos=cur_pos;
}

int hpos_get_cur(void) /* get the index of the current page */
{ return cur_pos; }


uint64_t hpos_get(void)
/* return the start position of the current page and its offset shifted by 32bit*/
{ return (((uint64_t)page_pos[cur_pos].offset)<<32)+page_pos[cur_pos].pos;
}



int hpos_get_next(void)
/* get the next index  into the page position cache after cur_pos.
   Allocate if necessary */
{ int pos;
  pos=cur_pos;
  incr_pos(pos);
  if (cur_pos==last_pos) /* allocation needed */
  { if (pos==first_pos) /* deallocation needed */
      incr_pos(first_pos);
    incr_pos(last_pos);
  }
  hpos_default(pos);
  return pos;
}

int hpos_get_prev(void)
/* get the prev index  into the page position cache before cur_pos.
   Allocate if necessary */
{ int pos;
  pos=cur_pos;
  decr_pos(pos);
  if (cur_pos==first_pos) /* allocation needed */
  { if (pos==last_pos) /* deallocation needed */
      decr_pos(last_pos);
    decr_pos(first_pos);
  }
  hpos_default(pos);
  return pos;
}

void hpos_home(void)
/* position the current position at the beginning of the hstream */
{ if (home_pos>=0)
    cur_pos=home_pos;
  else
    hpos_init();
}



bool hpos_next(void) /* advance to the next page if possible */
{ if (cur_pos==last_pos) 
    return false;
  incr_pos(cur_pos);
  return true;
}

bool hpos_prev(void) /* advance to the previous page if possible */
{ if (cur_pos==first_pos) 
    return false;
  decr_pos(cur_pos);
  return true;
}


/* THE MAPPING OF NODES TO POSITIONS */

/* This implementation uses a very simple hash table.
   In a final implementation, the reverse mapping could be 
   included as part of the node 
 */

#define MAX_MAP 30103 /*prime 70001  1009 */
#define MAX_FILL 25000/* 80% 60000  800 */

typedef struct 
{ pointer p;
  hpos_t pos;
} map_entry;

static map_entry map[MAX_MAP];
static int map_fill=0;

static int hash_value(pointer p)
{ return p % MAX_MAP;
}

static hpos_t *insert_map(pointer p, uint32_t pos, uint32_t offset, uint8_t f)
/* for the node pointer p store the stream position */
{ int i;
  if (p==null) return NULL;
//  if (type(p)!=glue_node && type(p)!=penalty_node && type(p)!=kern_node) return NULL; 
  if (map_fill++>=MAX_FILL) QUIT("reverse mapping table too full");
  i= hash_value(p);
  do 
  { if (map[i].p==0)
    { map[i].p=p; 
      map[i].pos.pos=pos; 
	  map[i].pos.offset=offset;
//	  map[i].pos.f=f; 
	  return &map[i].pos; 
    }
    else if (map[i].p==p) return &map[i].pos;
	else 
	{ i--;
	  if (i<0) i=i+MAX_MAP;
	}
  } while (true);
}

void clear_map(void)
/* clears the reverse mapping table */
{ memset(map,0,sizeof(map));
  map_fill=0;
}

static map_entry *hmap_find(pointer p)
/* return a pointer to the map entry */
{ int i;
  i= hash_value(p);
  do 
  { if (map[i].p==p) return map+i;
    if (map[i].p==0) return NULL;
	i--;
	if (i<0) i=i+MAX_MAP;
  } while (true);
}

#if 0
static hpos_t *hget_map(pointer p)
/* returns the map entry (position in the hstream) for a given node pointer p */
{ map_entry *m=hmap_find(p);
  if (m==NULL) return NULL;
  else return &m->pos;
}
#endif

uint32_t hmap(pointer p) /* return the position of p or 0*/
{ map_entry *m=hmap_find(p);
  if (m==NULL) return 0;
  else return m->pos.pos;
}

void hset_map_offset(pointer p, uint32_t offset) /* set the offset field for p */
{ map_entry *m=hmap_find(p);
  if (m==NULL) return;
  m->pos.offset=offset;
}


#if 0

void copy_map(pointer f, pointer t)
{ hpos_t *p;
  p=hget_map(f);
  if (p==NULL) return;
  insert_map(t,p->pos,p->offset,p->f);
}

static hpos_t *find_hstream_node(pointer p)
/* given a node pointer from the remainder of the contribution list
   find the first node that was in the hstream.
   Set hstream_line, if this node is in the middle of a paragraph.
*/
  
{ while (p!=null)
    { hpos_t *u;
      u=hget_map(p);
      if (u!=NULL) return u;
      p=link(p);
    } 
  return NULL;
}

uint32_t hmap(pointer p); /* return the position of p or 0*/



void hpos_set(pointer q, int i)
/*  after rendering a page, the contibution list contains nodes
    - that where in the input stream or
    - glue or penalties added by the page builder
    - or hlists created by line breaking of a paragraph node.
    In this case we need to look into the hlist itself to 
    find a node that was in the input stream.
    We need to remember that this node was wraped in a paragraph node,
    because we will find the end of that paragraph node when we rescan it.

    Further, we have two kinds of node lists, ordinary lists of nodes or texts.
    And we need to remember which one we are in for rescaning.

    An easy solution is to use different node types for hlists that have
    texts as sublists. Currently it's simple: graf nodes have a sublist of type text.
    We record the necessary information in the next_page structure.
*/
{ 
  hpos_t *p;
  p = find_hstream_node(q);
  if (p==NULL) /* no input node in the contribution list */
  { page_pos[i].pos=hpos-hstart;
    page_pos[i].f=0; /* stream_font */
    page_pos[i].offset=0;
#ifdef STREAMDEBUG
      if (log_file.f!=NULL) wlog("Found stream node: empty\n");
#endif
  }
  else
  { 
#ifdef STREAMDEBUG
    wlog("Found stream node:");
    show_node_list(p);
    print_ln();
#endif
    page_pos[i].pos=p->pos;
    page_pos[i].f=p->f;
    page_pos[i].offset=p->offset;
  }
}
#endif

 
void store_map(pointer p, uint32_t pos, uint32_t offset, uint8_t f)
{ 
  insert_map(p,pos,offset,f);
}

void hpos_set_next(pointer p)
/* record the position of p as the start of the next page */
{ int i;
  map_entry *m=hmap_find(p);
  if (m==NULL) 
	  QUIT("Unable to find position of next page");
  if (m->pos.pos==0xffffffff)
	  return;
  i= hpos_get_next();
  page_pos[i].pos=m->pos.pos;
  page_pos[i].offset=m->pos.offset;
  page_pos[i].f=m->pos.f;
}
