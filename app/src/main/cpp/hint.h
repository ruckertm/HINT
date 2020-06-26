/*319:*/
#line 6054 "hint.w"

#ifndef _HINT_H_
#define _HINT_H_

extern void hget_definition_section(void);
extern void hget_content_section(void);

extern void clear_map(void);
extern void hpage_init(void);
extern bool hbuild_page_up(void);


/*38:*/
#line 565 "hint.w"

extern uint16_t hglyph_section(uint8_t f);
extern int32_t font_at_size(uint8_t f);

/*:38*//*162:*/
#line 2764 "hint.w"

extern void hget_par_node(uint32_t offset);
/*:162*//*167:*/
#line 2864 "hint.w"

extern void hteg_par_node(uint32_t offset);
/*:167*//*204:*/
#line 3425 "hint.w"

extern void hclear_page(void);
/*:204*//*233:*/
#line 3900 "hint.w"

extern uint64_t page_loc[];
extern int cur_loc;
/*:233*//*235:*/
#line 3949 "hint.w"

extern void hloc_clear(void);
extern bool hloc_next(void);
extern bool hloc_prev(void);
/*:235*//*242:*/
#line 4127 "hint.w"

extern void hint_begin(void);
extern void hint_end(void);
extern void hint_map(void);
extern uint8_t*hbase;
extern void hint_unmap(void);
/*:242*//*245:*/
#line 4198 "hint.w"

extern bool hint_forward(void);
extern bool hint_backward(void);
/*:245*/
#line 6066 "hint.w"


#endif
/*:319*/
