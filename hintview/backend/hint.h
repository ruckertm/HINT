/*397:*/
#line 8060 "hint.w"

#ifndef _HINT_H_
#define _HINT_H_

typedef uint16_t pointer;
typedef int scaled;

/*44:*/
#line 875 "hint.w"

extern void hrestore_param_list(void);
/*:44*//*49:*/
#line 930 "hint.w"

typedef struct{
pointer p,t;
}Stream;
extern Stream*streams;
/*:49*//*64:*/
#line 1147 "hint.w"

extern void hfill_page_template(void);
/*:64*//*87:*/
#line 1515 "hint.w"

void hget_content(void);
/*:87*//*91:*/
#line 1567 "hint.w"

extern void hteg_content(void);
/*:91*//*168:*/
#line 2858 "hint.w"

extern void hprune_unwanted_nodes(void);
/*:168*//*180:*/
#line 3097 "hint.w"

extern void set_line_break_params(void);
/*:180*//*182:*/
#line 3138 "hint.w"

extern void hget_par_node(uint32_t offset);
/*:182*//*187:*/
#line 3238 "hint.w"

extern void hteg_par_node(uint32_t offset);
/*:187*//*216:*/
#line 3633 "hint.w"

extern pointer*pointer_def[32];
extern scaled*dimen_def;
extern int32_t*integer_def;
/*:216*//*217:*/
#line 3688 "hint.w"

extern Stream*streams;
extern bool flush_pages(uint32_t pos);
extern pointer skip(uint8_t n);
extern pointer*box_ptr(uint8_t n);
extern int count(uint8_t n);
extern scaled dimen(uint8_t n);
/*:217*//*220:*/
#line 3745 "hint.w"

extern void hpage_init(void);
/*:220*//*222:*/
#line 3762 "hint.w"

extern void hflush_contribution_list(void);
/*:222*//*242:*/
#line 4165 "hint.w"

#define HINT_NO_LOC 0xFFFFFFFFFFFFFFFF
#define PAGE_LOC(POS0,OFF) (((uint64_t)((POS0)+(OFF))<<32) + (uint64_t)(OFF))
#define LOC_POS(P) ((P)>>32) 
#define LOC_OFF(P) ((P)&0xFFFFFFFF) 
#define LOC_POS0(P) (LOC_POS(P)-LOC_OFF(P)) 
/*:242*//*245:*/
#line 4202 "hint.w"

extern uint64_t page_loc[];
extern int cur_loc;
/*:245*//*247:*/
#line 4251 "hint.w"

extern void hloc_clear(void);
extern bool hloc_next(void);
extern bool hloc_prev(void);
extern uint64_t hlocation(pointer p);
/*:247*//*252:*/
#line 4369 "hint.w"

extern void hloc_init(void);
extern void store_map(pointer p,uint32_t pos,uint32_t offset);
extern uint32_t hposition(pointer p);
extern void hloc_set(uint64_t h);
extern void hloc_set_next(pointer p);
/*:252*//*254:*/
#line 4440 "hint.w"

extern int hint_begin(void);
extern void hint_end(void);
extern bool hint_map(void);
extern void hint_unmap(void);
/*:254*//*259:*/
#line 4564 "hint.w"

extern bool hint_forward(void);
extern bool hint_backward(void);
/*:259*//*262:*/
#line 4595 "hint.w"

extern scaled hvsize,hhsize;
/*:262*//*285:*/
#line 5153 "hint.w"

typedef struct{
uint64_t pos;
uint8_t depth;
uint8_t where;
int p;
char*title;
}hint_Outline;
extern hint_Outline*hint_outlines;
/*:285*//*286:*/
#line 5171 "hint.w"

#define LABEL_UNDEF 0
#define LABEL_TOP 1
#define LABEL_BOT 2
#define LABEL_MID 3
/*:286*//*290:*/
#line 5230 "hint.w"

extern int hint_get_outline_max(void);
extern hint_Outline*hint_get_outlines(void);
extern uint64_t hint_outline_page(int i);
/*:290*//*292:*/
#line 5345 "hint.w"

extern void trv_init(void(*f)(uint32_t c));
extern void trv_vlist(pointer p);
extern void trv_hlist(pointer p);
/*:292*//*321:*/
#line 5877 "hint.w"

typedef struct{
uint64_t pos;
uint8_t where;
scaled top,bottom,left,right;
}hint_Link;
extern hint_Link*hint_links;
extern int max_link;
/*:321*//*326:*/
#line 6048 "hint.w"

extern int hint_find_link(scaled x,scaled y,scaled precission);
extern uint64_t hint_link_page(int i);
/*:326*//*396:*/
#line 8043 "hint.w"

extern void leak_in(pointer p,int s);
extern void leak_out(pointer p,int s);
/*:396*/
#line 8067 "hint.w"


#endif
/*:397*/
