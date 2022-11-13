/*373:*/
#line 7559 "hint.w"

#ifndef _HINT_H_
#define _HINT_H_

typedef uint16_t pointer;
typedef int scaled;

/*44:*/
#line 756 "hint.w"

extern void hrestore_param_list(void);
/*:44*//*49:*/
#line 811 "hint.w"

typedef struct{
pointer p,t;
}Stream;
extern Stream*streams;
/*:49*//*64:*/
#line 1028 "hint.w"

extern void hfill_page_template(void);
/*:64*//*77:*/
#line 1236 "hint.w"

void hget_content(void);
/*:77*//*81:*/
#line 1291 "hint.w"

extern void hteg_content(void);
/*:81*//*164:*/
#line 2797 "hint.w"

extern void set_line_break_params(void);
/*:164*//*166:*/
#line 2837 "hint.w"

extern void hget_par_node(uint32_t offset);
/*:166*//*171:*/
#line 2937 "hint.w"

extern void hteg_par_node(uint32_t offset);
/*:171*//*197:*/
#line 3304 "hint.w"

extern pointer*pointer_def[32];
extern scaled*dimen_def;
extern int32_t*integer_def;
/*:197*//*198:*/
#line 3359 "hint.w"

extern Stream*streams;
extern bool flush_pages(uint32_t pos);
extern pointer skip(uint8_t n);
extern pointer*box_ptr(uint8_t n);
extern int count(uint8_t n);
extern scaled dimen(uint8_t n);
/*:198*//*201:*/
#line 3416 "hint.w"

extern void hpage_init(void);
/*:201*//*203:*/
#line 3433 "hint.w"

extern void hflush_contribution_list(void);
/*:203*//*223:*/
#line 3836 "hint.w"

#define HINT_NO_LOC 0xFFFFFFFFFFFFFFFF
#define PAGE_LOC(POS0,OFF) (((uint64_t)((POS0)+(OFF))<<32) + (uint64_t)(OFF))
#define LOC_POS(P) ((P)>>32) 
#define LOC_OFF(P) ((P)&0xFFFFFFFF) 
#define LOC_POS0(P) (LOC_POS(P)-LOC_OFF(P)) 
/*:223*//*226:*/
#line 3873 "hint.w"

extern uint64_t page_loc[];
extern int cur_loc;
/*:226*//*228:*/
#line 3922 "hint.w"

extern void hloc_clear(void);
extern bool hloc_next(void);
extern bool hloc_prev(void);
extern uint64_t hlocation(pointer p);
/*:228*//*233:*/
#line 4038 "hint.w"

extern void hloc_init(void);
extern void store_map(pointer p,uint32_t pos,uint32_t offset);
extern uint32_t hposition(pointer p);
extern void hloc_set(uint64_t h);
extern void hloc_set_next(pointer p);
/*:233*//*235:*/
#line 4109 "hint.w"

extern int hint_begin(void);
extern void hint_end(void);
extern bool hint_map(void);
extern void hint_unmap(void);
/*:235*//*240:*/
#line 4233 "hint.w"

extern bool hint_forward(void);
extern bool hint_backward(void);
/*:240*//*243:*/
#line 4264 "hint.w"

extern scaled hvsize,hhsize;
/*:243*//*264:*/
#line 4775 "hint.w"

typedef struct{
uint64_t pos;
uint8_t depth;
uint8_t where;
int p;
char*title;
}hint_Outline;
extern hint_Outline*hint_outlines;
/*:264*//*265:*/
#line 4793 "hint.w"

#define LABEL_UNDEF 0
#define LABEL_TOP 1
#define LABEL_BOT 2
#define LABEL_MID 3
/*:265*//*269:*/
#line 4852 "hint.w"

extern int hint_get_outline_max(void);
extern hint_Outline*hint_get_outlines(void);
extern uint64_t hint_outline_page(int i);
/*:269*//*271:*/
#line 4967 "hint.w"

extern void trv_init(void(*f)(uint32_t c));
extern void trv_vlist(pointer p);
extern void trv_hlist(pointer p);
/*:271*//*299:*/
#line 5502 "hint.w"

typedef struct{
uint64_t pos;
uint8_t where;
scaled top,bottom,left,right;
}hint_Link;
extern hint_Link*hint_links;
extern int max_link;
/*:299*//*304:*/
#line 5665 "hint.w"

extern int hint_find_link(scaled x,scaled y,scaled precission);
extern uint64_t hint_link_page(int i);
/*:304*//*372:*/
#line 7542 "hint.w"

extern void leak_in(pointer p,int s);
extern void leak_out(pointer p,int s);
/*:372*/
#line 7566 "hint.w"


#endif
/*:373*/
