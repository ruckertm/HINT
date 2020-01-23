/*311:*/
#line 5658 ".\\hint.w"

#ifndef _LIBHINT_H_
#define _LIBHINT_H_

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


/*47:*/
#line 813 ".\\hint.w"

extern uint16_t hglyph_section(uint8_t f);
extern int32_t font_at_size(uint8_t f);

/*:47*//*174:*/
#line 2861 ".\\hint.w"

extern void hget_par_node(uint32_t offset);
/*:174*//*178:*/
#line 2921 ".\\hint.w"

extern void hteg_par_node(uint32_t offset);
/*:178*//*208:*/
#line 3395 ".\\hint.w"

extern void hclear_page(void);
/*:208*//*236:*/
#line 3907 ".\\hint.w"

extern void hloc_clear(void);
extern bool hloc_next(void);
extern bool hloc_prev(void);
/*:236*//*238:*/
#line 3930 ".\\hint.w"

extern void hloc_init(void);
/*:238*//*240:*/
#line 3942 ".\\hint.w"

extern uint64_t hloc_get(void);
/*:240*//*244:*/
#line 4034 ".\\hint.w"

extern void hint_open(const char*file_name);
extern void hint_close(void);
/*:244*//*247:*/
#line 4101 ".\\hint.w"

extern bool hint_forward(void);
extern bool hint_backward(void);
/*:247*/
#line 5677 ".\\hint.w"


#endif
/*:311*/
