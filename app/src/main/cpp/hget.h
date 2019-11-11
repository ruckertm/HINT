/*249:*/
#line 3793 ".\\hint.w"


/*44:*/
#line 697 ".\\hint.w"

typedef struct{
char*n;
uint16_t m,q;
scaled s;
pointer g;
pointer h;
pointer p[MAX_FONT_PARAMS+1];
}font_def_t;
/*:44*//*50:*/
#line 771 ".\\hint.w"

typedef struct param_t{
uint8_t n,k;
union{int32_t i;
scaled d;
pointer g;};
}param_t;

typedef struct param_def_t{
struct param_def_t*next;
param_t p;}param_def_t;
/*:50*/
#line 3795 ".\\hint.w"


extern font_def_t*font_def;
extern void hset_default_definitions(void);
extern int32_t hget_integer_ref(uint8_t n);
extern scaled hget_dimen_ref(uint8_t n);
extern pointer hget_rule_ref(uint8_t n);
extern pointer hget_math_ref(uint8_t n);
extern pointer hget_glue_ref(uint8_t n);
extern pointer hget_leaders_ref(uint8_t n);
extern scaled hget_xdimen_ref(uint8_t n);
extern pointer hget_hyphen_ref(uint8_t n);
extern pointer hget_ligature_ref(uint8_t n);
extern void hget_baseline_ref(uint8_t n,bs_t*b);
extern pointer hget_image_ref(uint16_t n);
extern uint32_t hget_utf8(void);
extern param_def_t*hget_param_list_ref(uint8_t n);
extern void hset_param_list(param_def_t*p);
extern void hrestore_param_list(void);
extern void hopen_file(const char*in_name);
extern bool hget_banner(void);
extern void hget_section(uint16_t n);
extern void hget_directory_section(void);
extern void hallocate_definitions(void);
extern void hget_definition_section(void);
extern void hget_content_section(void);
extern void hget_content(void);
extern void hget_size_boundary(info_t info);
extern uint32_t hget_list_size(info_t info);
extern pointer hget_list(void);
extern void hget_par_node(uint32_t offset);
extern void hget_paragraph(scaled x,param_def_t*q,uint32_t offset);
extern void hset(pointer p,uint8_t sto,scaled st,
uint8_t sho,scaled sh,scaled w);
extern void vset(pointer p,uint8_t sto,scaled st,
uint8_t sho,scaled sh,scaled h);

extern param_def_t*hget_param_list_node(void);
/*:249*/
