/*294:*/
#line 5550 "hint.w"

#ifndef _HINT_H_
#define _HINT_H_

extern void hget_definition_section(void);
extern void hget_content_section(void);
extern void hget_content(void);

extern void clear_map(void);
extern void hpage_init(void);
extern bool hbuild_page_up(void);


/*38:*/
#line 561 "hint.w"

extern uint16_t hglyph_section(uint8_t f);
extern int32_t font_at_size(uint8_t f);

/*:38*//*154:*/
#line 2514 "hint.w"

extern void hget_par_node(uint32_t offset);
/*:154*//*159:*/
#line 2615 "hint.w"

extern void hteg_par_node(uint32_t offset);
/*:159*//*183:*/
#line 3006 "hint.w"

extern void hclear_page(void);
/*:183*//*209:*/
#line 3466 "hint.w"

extern uint64_t page_loc[];
extern int cur_loc;
/*:209*//*211:*/
#line 3515 "hint.w"

extern void hloc_clear(void);
extern bool hloc_next(void);
extern bool hloc_prev(void);
/*:211*//*218:*/
#line 3689 "hint.w"

extern void hint_begin(void);
extern void hint_end(void);
extern void hint_map(void);
extern uint8_t*hbase;
extern void hint_unmap(void);
/*:218*//*221:*/
#line 3760 "hint.w"

extern bool hint_forward(void);
extern bool hint_backward(void);
/*:221*/
#line 5563 "hint.w"


#endif
/*:294*/
