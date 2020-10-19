/*327:*/
#line 6321 ".\\hint.w"

#ifndef _HINT_H_
#define _HINT_H_

extern void hget_definition_section(void);
extern void hget_content_section(void);

extern void clear_map(void);
extern void hpage_init(void);
extern bool hbuild_page_up(void);


/*39:*/
#line 574 ".\\hint.w"

extern uint16_t hglyph_section(uint8_t f);
extern int32_t font_at_size(uint8_t f);

/*:39*//*167:*/
#line 2831 ".\\hint.w"

extern void hget_par_node(uint32_t offset);
/*:167*//*172:*/
#line 2929 ".\\hint.w"

extern void hteg_par_node(uint32_t offset);
/*:172*//*209:*/
#line 3492 ".\\hint.w"

extern void hflush_contribution_list(void);
/*:209*//*234:*/
#line 3947 ".\\hint.w"

extern uint64_t page_loc[];
extern int cur_loc;
/*:234*//*236:*/
#line 3996 ".\\hint.w"

extern void hloc_clear(void);
extern bool hloc_next(void);
extern bool hloc_prev(void);
/*:236*//*243:*/
#line 4175 ".\\hint.w"

extern void hint_begin(void);
extern void hint_end(void);
extern uint64_t hint_map(void);
extern uint8_t*hbase;
extern void hint_unmap(void);
/*:243*//*246:*/
#line 4247 ".\\hint.w"

extern bool hint_forward(void);
extern bool hint_backward(void);
/*:246*/
#line 6333 ".\\hint.w"


#endif
/*:327*/
