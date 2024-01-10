/*393:*/
#line 7740 "hint.w"

#ifndef _HINT_H_
#define _HINT_H_

typedef uint16_t pointer;
typedef int scaled;

/*44:*/
#line 767 "hint.w"

extern void hrestore_param_list(void);
/*:44*//*49:*/
#line 822 "hint.w"

typedef struct{
pointer p,t;
}Stream;
extern Stream*streams;
/*:49*//*64:*/
#line 1039 "hint.w"

extern void hfill_page_template(void);
/*:64*//*87:*/
#line 1368 "hint.w"

void hget_content(void);
/*:87*//*91:*/
#line 1420 "hint.w"

extern void hteg_content(void);
/*:91*//*168:*/
#line 2711 "hint.w"

extern void hprune_unwanted_nodes(void);
/*:168*//*178:*/
#line 2907 "hint.w"

extern void set_line_break_params(void);
/*:178*//*180:*/
#line 2948 "hint.w"

extern void hget_par_node(uint32_t offset);
/*:180*//*185:*/
#line 3048 "hint.w"

extern void hteg_par_node(uint32_t offset);
/*:185*//*213:*/
#line 3423 "hint.w"

extern pointer*pointer_def[32];
extern scaled*dimen_def;
extern int32_t*integer_def;
/*:213*//*214:*/
#line 3478 "hint.w"

extern Stream*streams;
extern bool flush_pages(uint32_t pos);
extern pointer skip(uint8_t n);
extern pointer*box_ptr(uint8_t n);
extern int count(uint8_t n);
extern scaled dimen(uint8_t n);
/*:214*//*217:*/
#line 3535 "hint.w"

extern void hpage_init(void);
/*:217*//*219:*/
#line 3552 "hint.w"

extern void hflush_contribution_list(void);
/*:219*//*239:*/
#line 3955 "hint.w"

#define HINT_NO_LOC 0xFFFFFFFFFFFFFFFF
#define PAGE_LOC(POS0,OFF) (((uint64_t)((POS0)+(OFF))<<32) + (uint64_t)(OFF))
#define LOC_POS(P) ((P)>>32) 
#define LOC_OFF(P) ((P)&0xFFFFFFFF) 
#define LOC_POS0(P) (LOC_POS(P)-LOC_OFF(P)) 
/*:239*//*242:*/
#line 3992 "hint.w"

extern uint64_t page_loc[];
extern int cur_loc;
/*:242*//*244:*/
#line 4041 "hint.w"

extern void hloc_clear(void);
extern bool hloc_next(void);
extern bool hloc_prev(void);
extern uint64_t hlocation(pointer p);
/*:244*//*249:*/
#line 4159 "hint.w"

extern void hloc_init(void);
extern void store_map(pointer p,uint32_t pos,uint32_t offset);
extern uint32_t hposition(pointer p);
extern void hloc_set(uint64_t h);
extern void hloc_set_next(pointer p);
/*:249*//*251:*/
#line 4230 "hint.w"

extern int hint_begin(void);
extern void hint_end(void);
extern bool hint_map(void);
extern void hint_unmap(void);
/*:251*//*256:*/
#line 4354 "hint.w"

extern bool hint_forward(void);
extern bool hint_backward(void);
/*:256*//*259:*/
#line 4385 "hint.w"

extern scaled hvsize,hhsize;
/*:259*//*282:*/
#line 4943 "hint.w"

typedef struct{
uint64_t pos;
uint8_t depth;
uint8_t where;
int p;
char*title;
}hint_Outline;
extern hint_Outline*hint_outlines;
/*:282*//*283:*/
#line 4961 "hint.w"

#define LABEL_UNDEF 0
#define LABEL_TOP 1
#define LABEL_BOT 2
#define LABEL_MID 3
/*:283*//*287:*/
#line 5020 "hint.w"

extern int hint_get_outline_max(void);
extern hint_Outline*hint_get_outlines(void);
extern uint64_t hint_outline_page(int i);
/*:287*//*289:*/
#line 5135 "hint.w"

extern void trv_init(void(*f)(uint32_t c));
extern void trv_vlist(pointer p);
extern void trv_hlist(pointer p);
/*:289*//*318:*/
#line 5667 "hint.w"

typedef struct{
uint64_t pos;
uint8_t where;
scaled top,bottom,left,right;
}hint_Link;
extern hint_Link*hint_links;
extern int max_link;
/*:318*//*323:*/
#line 5830 "hint.w"

extern int hint_find_link(scaled x,scaled y,scaled precission);
extern uint64_t hint_link_page(int i);
/*:323*//*392:*/
#line 7723 "hint.w"

extern void leak_in(pointer p,int s);
extern void leak_out(pointer p,int s);
/*:392*/
#line 7747 "hint.w"


#endif
/*:393*/
