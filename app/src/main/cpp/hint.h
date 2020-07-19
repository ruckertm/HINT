/*323:*/
#line 6124 "hint.w"

#ifndef _HINT_H_
#define _HINT_H_

extern void hget_definition_section(void);
extern void hget_content_section(void);

extern void clear_map(void);
extern void hpage_init(void);
extern bool hbuild_page_up(void);


/*38:*/
#line 569 "hint.w"

extern uint16_t hglyph_section(uint8_t f);
extern int32_t font_at_size(uint8_t f);

/*:38*//*166:*/
#line 2826 "hint.w"

extern void hget_par_node(uint32_t offset);
/*:166*//*171:*/
#line 2924 "hint.w"

extern void hteg_par_node(uint32_t offset);
/*:171*//*208:*/
#line 3487 "hint.w"

extern void hflush_contribution_list(void);
/*:208*//*237:*/
#line 3962 "hint.w"

extern uint64_t page_loc[];
extern int cur_loc;
/*:237*//*239:*/
#line 4011 "hint.w"

extern void hloc_clear(void);
extern bool hloc_next(void);
extern bool hloc_prev(void);
/*:239*//*246:*/
#line 4189 "hint.w"

extern void hint_begin(void);
extern void hint_end(void);
extern void hint_map(void);
extern uint8_t*hbase;
extern void hint_unmap(void);
/*:246*//*249:*/
#line 4261 "hint.w"

extern bool hint_forward(void);
extern bool hint_backward(void);
/*:249*/
#line 6136 "hint.w"


#endif
/*:323*/
