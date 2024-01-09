/*390:*/
#line 7700 "hint.w"

#ifndef _HINT_H_
#define _HINT_H_

typedef uint16_t pointer;
typedef int scaled;

/*44:*/
#line 768 "hint.w"

extern void hrestore_param_list(void);
/*:44*//*49:*/
#line 823 "hint.w"

typedef struct{
pointer p,t;
}Stream;
extern Stream*streams;
/*:49*//*64:*/
#line 1040 "hint.w"

extern void hfill_page_template(void);
/*:64*//*85:*/
#line 1333 "hint.w"

void hget_content(void);
/*:85*//*89:*/
#line 1385 "hint.w"

extern void hteg_content(void);
/*:89*//*166:*/
#line 2676 "hint.w"

extern void hprune_unwanted_nodes(void);
/*:166*//*176:*/
#line 2872 "hint.w"

extern void set_line_break_params(void);
/*:176*//*178:*/
#line 2913 "hint.w"

extern void hget_par_node(uint32_t offset);
/*:178*//*183:*/
#line 3013 "hint.w"

extern void hteg_par_node(uint32_t offset);
/*:183*//*211:*/
#line 3388 "hint.w"

extern pointer*pointer_def[32];
extern scaled*dimen_def;
extern int32_t*integer_def;
/*:211*//*212:*/
#line 3443 "hint.w"

extern Stream*streams;
extern bool flush_pages(uint32_t pos);
extern pointer skip(uint8_t n);
extern pointer*box_ptr(uint8_t n);
extern int count(uint8_t n);
extern scaled dimen(uint8_t n);
/*:212*//*215:*/
#line 3500 "hint.w"

extern void hpage_init(void);
/*:215*//*217:*/
#line 3517 "hint.w"

extern void hflush_contribution_list(void);
/*:217*//*237:*/
#line 3920 "hint.w"

#define HINT_NO_LOC 0xFFFFFFFFFFFFFFFF
#define PAGE_LOC(POS0,OFF) (((uint64_t)((POS0)+(OFF))<<32) + (uint64_t)(OFF))
#define LOC_POS(P) ((P)>>32) 
#define LOC_OFF(P) ((P)&0xFFFFFFFF) 
#define LOC_POS0(P) (LOC_POS(P)-LOC_OFF(P)) 
/*:237*//*240:*/
#line 3957 "hint.w"

extern uint64_t page_loc[];
extern int cur_loc;
/*:240*//*242:*/
#line 4006 "hint.w"

extern void hloc_clear(void);
extern bool hloc_next(void);
extern bool hloc_prev(void);
extern uint64_t hlocation(pointer p);
/*:242*//*247:*/
#line 4124 "hint.w"

extern void hloc_init(void);
extern void store_map(pointer p,uint32_t pos,uint32_t offset);
extern uint32_t hposition(pointer p);
extern void hloc_set(uint64_t h);
extern void hloc_set_next(pointer p);
/*:247*//*249:*/
#line 4195 "hint.w"

extern int hint_begin(void);
extern void hint_end(void);
extern bool hint_map(void);
extern void hint_unmap(void);
/*:249*//*254:*/
#line 4319 "hint.w"

extern bool hint_forward(void);
extern bool hint_backward(void);
/*:254*//*257:*/
#line 4350 "hint.w"

extern scaled hvsize,hhsize;
/*:257*//*280:*/
#line 4908 "hint.w"

typedef struct{
uint64_t pos;
uint8_t depth;
uint8_t where;
int p;
char*title;
}hint_Outline;
extern hint_Outline*hint_outlines;
/*:280*//*281:*/
#line 4926 "hint.w"

#define LABEL_UNDEF 0
#define LABEL_TOP 1
#define LABEL_BOT 2
#define LABEL_MID 3
/*:281*//*285:*/
#line 4985 "hint.w"

extern int hint_get_outline_max(void);
extern hint_Outline*hint_get_outlines(void);
extern uint64_t hint_outline_page(int i);
/*:285*//*287:*/
#line 5100 "hint.w"

extern void trv_init(void(*f)(uint32_t c));
extern void trv_vlist(pointer p);
extern void trv_hlist(pointer p);
/*:287*//*316:*/
#line 5632 "hint.w"

typedef struct{
uint64_t pos;
uint8_t where;
scaled top,bottom,left,right;
}hint_Link;
extern hint_Link*hint_links;
extern int max_link;
/*:316*//*321:*/
#line 5795 "hint.w"

extern int hint_find_link(scaled x,scaled y,scaled precission);
extern uint64_t hint_link_page(int i);
/*:321*//*389:*/
#line 7683 "hint.w"

extern void leak_in(pointer p,int s);
extern void leak_out(pointer p,int s);
/*:389*/
#line 7707 "hint.w"


#endif
/*:390*/
