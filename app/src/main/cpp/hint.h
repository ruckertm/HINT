/*298:*/
#line 5675 "hint.w"

#ifndef _HINT_H_
#define _HINT_H_

extern bool hmap_file(int fd);
extern bool hget_banner(void);
extern bool hget_section(uint16_t n);
extern bool hget_directory_section(void);
extern void hclear_dir(void);
extern bool hget_definition_section(void);
extern bool hget_content_section(void);
extern void hget_content(void);
extern void hteg_content(void);

extern void clear_map(void);
extern void hpage_init(void);
extern bool hbuild_page_up(void);


/*46:*/
#line 884 "hint.w"

extern uint16_t hglyph_section(uint8_t f);
extern int32_t font_at_size(uint8_t f);

/*:46*//*161:*/
#line 2814 "hint.w"

extern void hget_par_node(uint32_t offset);
/*:161*//*165:*/
#line 2874 "hint.w"

extern void hteg_par_node(uint32_t offset);
/*:165*//*190:*/
#line 3283 "hint.w"

extern void hclear_page(void);
/*:190*//*216:*/
#line 3743 "hint.w"

extern uint64_t page_loc[];
extern int cur_loc;
/*:216*//*218:*/
#line 3792 "hint.w"

extern void hloc_clear(void);
extern bool hloc_next(void);
extern bool hloc_prev(void);
/*:218*//*225:*/
#line 3963 "hint.w"

extern int hint_begin(int fd);
extern void hint_end(void);
/*:225*//*228:*/
#line 4030 "hint.w"

extern bool hint_forward(void);
extern bool hint_backward(void);
/*:228*/
#line 5694 "hint.w"


#endif
/*:298*/
