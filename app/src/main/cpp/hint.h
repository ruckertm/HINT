/*291:*/
#line 5468 "hint.w"

#ifndef _HINT_H_
#define _HINT_H_

extern void hget_definition_section(void);
extern void hget_content_section(void);
extern void hget_content(void);

extern void clear_map(void);
extern void hpage_init(void);
extern bool hbuild_page_up(void);


/*36:*/
#line 516 "hint.w"

extern uint16_t hglyph_section(uint8_t f);
extern int32_t font_at_size(uint8_t f);

/*:36*//*151:*/
#line 2452 "hint.w"

extern void hget_par_node(uint32_t offset);
/*:151*//*155:*/
#line 2512 "hint.w"

extern void hteg_par_node(uint32_t offset);
/*:155*//*180:*/
#line 2924 "hint.w"

extern void hclear_page(void);
/*:180*//*206:*/
#line 3384 "hint.w"

extern uint64_t page_loc[];
extern int cur_loc;
/*:206*//*208:*/
#line 3433 "hint.w"

extern void hloc_clear(void);
extern bool hloc_next(void);
extern bool hloc_prev(void);
/*:208*//*215:*/
#line 3607 "hint.w"

extern void hint_begin(void);
extern void hint_end(void);
extern void hint_map(void);
extern uint8_t*hbase;
extern void hint_unmap(void);
/*:215*//*218:*/
#line 3678 "hint.w"

extern bool hint_forward(void);
extern bool hint_backward(void);
/*:218*/
#line 5481 "hint.w"


#endif
/*:291*/
