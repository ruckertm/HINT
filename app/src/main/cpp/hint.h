/*298:*/
#line 5586 "hint.w"

#ifndef _HINT_H_
#define _HINT_H_

extern void hopen_file(const char*in_name);
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


/*46:*/
#line 809 "hint.w"

extern uint16_t hglyph_section(uint8_t f);
extern int32_t font_at_size(uint8_t f);

/*:46*//*161:*/
#line 2739 "hint.w"

extern void hget_par_node(uint32_t offset);
/*:161*//*165:*/
#line 2799 "hint.w"

extern void hteg_par_node(uint32_t offset);
/*:165*//*190:*/
#line 3208 "hint.w"

extern void hclear_page(void);
/*:190*//*216:*/
#line 3664 "hint.w"

extern uint64_t page_loc[];
extern int cur_loc;
/*:216*//*218:*/
#line 3713 "hint.w"

extern void hloc_clear(void);
extern bool hloc_next(void);
extern bool hloc_prev(void);
/*:218*//*225:*/
#line 3876 "hint.w"

extern void hint_open(const char*file_name);
extern void hint_close(void);
/*:225*//*228:*/
#line 3943 "hint.w"

extern bool hint_forward(void);
extern bool hint_backward(void);
/*:228*/
#line 5605 "hint.w"


#endif
/*:298*/
