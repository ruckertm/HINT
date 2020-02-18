/*300:*/
#line 5630 ".\\hint.w"

#ifndef _HINT_H_
#define _HINT_H_

extern bool hget_banner(void);
extern void hget_section(uint16_t n);
extern void hget_directory_section(void);
extern void hclear_dir(void);
extern void hget_definition_section(void);
extern void hget_content_section(void);
extern void hget_content(void);
extern void hteg_content(void);

extern void clear_map(void);
extern void hpage_init(void);
extern bool hbuild_page_up(void);


/*45:*/
#line 749 ".\\hint.w"

extern uint16_t hglyph_section(uint8_t f);
extern int32_t font_at_size(uint8_t f);

/*:45*//*160:*/
#line 2679 ".\\hint.w"

extern void hget_par_node(uint32_t offset);
/*:160*//*164:*/
#line 2739 ".\\hint.w"

extern void hteg_par_node(uint32_t offset);
/*:164*//*189:*/
#line 3148 ".\\hint.w"

extern void hclear_page(void);
/*:189*//*215:*/
#line 3608 ".\\hint.w"

extern uint64_t page_loc[];
extern int cur_loc;
/*:215*//*217:*/
#line 3657 ".\\hint.w"

extern void hloc_clear(void);
extern bool hloc_next(void);
extern bool hloc_prev(void);
/*:217*//*224:*/
#line 3828 ".\\hint.w"

extern void hint_begin(void);
extern void hint_end(void);
extern void hint_map(void);
extern uint8_t*hbase;
extern void hint_unmap(void);
/*:224*//*230:*/
#line 3974 ".\\hint.w"

extern bool hint_forward(void);
extern bool hint_backward(void);
/*:230*/
#line 5648 ".\\hint.w"


#endif
/*:300*/
