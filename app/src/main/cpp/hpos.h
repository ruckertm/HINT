#ifndef _HPOS_H_
#define _HPOS_H_
/* handle positions in the hstream */



typedef struct 
{ uint32_t pos; /* points to a level 0 node in the hstream */
  uint32_t offset; /* offset into a paragraph node (or other node that is split across pages */
  uint8_t f; /* the current font at offset if offset!=0 */
#if 0
  int lineno; /* if at hpos is a paragraph node, this is the number of the line starting at htext */
  bool broken; /* this is true if at htext is a discretionary hyphen and the line starts with the post_break list */ 
#endif
} hpos_t;


extern void hpos_init(void); /* initialize the page position buffer to the home position*/
extern void hpos_clear(void); /* clear the page position cache, except for the current position */
extern void hpos_home(void); /* position the current position at the beginning of the hstream */
extern bool hpos_next(void); /* advance to the next page if possible */
extern bool hpos_prev(void); /* advance to the previous page if possible */
extern int hpos_get_next(void); /* get the next index  into the page position cache after cur_pos. */
extern int hpos_get_prev(void); /* get the prev index  into the page position cache before cur_pos. */
extern int hpos_get_cur(void); /* get the index of the current page */
extern uint64_t hpos_get(void); /* return the start position and (offset<<32) of the current page */

extern void clear_map(void); /* clears the reverse mapping table */

extern void store_map(pointer p, uint32_t pos, uint32_t offset, uint8_t font);
/* for the node pointer p store the stream position */
extern void copy_map(pointer f, pointer t); /* copy the map from f to t */
extern uint32_t hmap(pointer p); /* return the position of p or 0*/

extern void hpos_set(pointer p, int i); /* set the position at index i using the start of node list p */
extern void hpos_set_next(pointer p); /* record the position of p as the start of the next page */

extern void hset_map_offset(pointer p, uint32_t offset); /* set the offset field for p */

#endif
