/*395:*/
#line 7787 "hint.w"

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
/*:168*//*180:*/
#line 2937 "hint.w"

extern void set_line_break_params(void);
/*:180*//*182:*/
#line 2978 "hint.w"

extern void hget_par_node(uint32_t offset);
/*:182*//*187:*/
#line 3078 "hint.w"

extern void hteg_par_node(uint32_t offset);
/*:187*//*215:*/
#line 3453 "hint.w"

extern pointer*pointer_def[32];
extern scaled*dimen_def;
extern int32_t*integer_def;
/*:215*//*216:*/
#line 3508 "hint.w"

extern Stream*streams;
extern bool flush_pages(uint32_t pos);
extern pointer skip(uint8_t n);
extern pointer*box_ptr(uint8_t n);
extern int count(uint8_t n);
extern scaled dimen(uint8_t n);
/*:216*//*219:*/
#line 3565 "hint.w"

extern void hpage_init(void);
/*:219*//*221:*/
#line 3582 "hint.w"

extern void hflush_contribution_list(void);
/*:221*//*241:*/
#line 3985 "hint.w"

#define HINT_NO_LOC 0xFFFFFFFFFFFFFFFF
#define PAGE_LOC(POS0,OFF) (((uint64_t)((POS0)+(OFF))<<32) + (uint64_t)(OFF))
#define LOC_POS(P) ((P)>>32) 
#define LOC_OFF(P) ((P)&0xFFFFFFFF) 
#define LOC_POS0(P) (LOC_POS(P)-LOC_OFF(P)) 
/*:241*//*244:*/
#line 4022 "hint.w"

extern uint64_t page_loc[];
extern int cur_loc;
/*:244*//*246:*/
#line 4071 "hint.w"

extern void hloc_clear(void);
extern bool hloc_next(void);
extern bool hloc_prev(void);
extern uint64_t hlocation(pointer p);
/*:246*//*251:*/
#line 4189 "hint.w"

extern void hloc_init(void);
extern void store_map(pointer p,uint32_t pos,uint32_t offset);
extern uint32_t hposition(pointer p);
extern void hloc_set(uint64_t h);
extern void hloc_set_next(pointer p);
/*:251*//*253:*/
#line 4260 "hint.w"

extern int hint_begin(void);
extern void hint_end(void);
extern bool hint_map(void);
extern void hint_unmap(void);
/*:253*//*258:*/
#line 4384 "hint.w"

extern bool hint_forward(void);
extern bool hint_backward(void);
/*:258*//*261:*/
#line 4415 "hint.w"

extern scaled hvsize,hhsize;
/*:261*//*284:*/
#line 4973 "hint.w"

typedef struct{
uint64_t pos;
uint8_t depth;
uint8_t where;
int p;
char*title;
}hint_Outline;
extern hint_Outline*hint_outlines;
/*:284*//*285:*/
#line 4991 "hint.w"

#define LABEL_UNDEF 0
#define LABEL_TOP 1
#define LABEL_BOT 2
#define LABEL_MID 3
/*:285*//*289:*/
#line 5050 "hint.w"

extern int hint_get_outline_max(void);
extern hint_Outline*hint_get_outlines(void);
extern uint64_t hint_outline_page(int i);
/*:289*//*291:*/
#line 5165 "hint.w"

extern void trv_init(void(*f)(uint32_t c));
extern void trv_vlist(pointer p);
extern void trv_hlist(pointer p);
/*:291*//*320:*/
#line 5697 "hint.w"

typedef struct{
uint64_t pos;
uint8_t where;
scaled top,bottom,left,right;
}hint_Link;
extern hint_Link*hint_links;
extern int max_link;
/*:320*//*325:*/
#line 5860 "hint.w"

extern int hint_find_link(scaled x,scaled y,scaled precission);
extern uint64_t hint_link_page(int i);
/*:325*//*394:*/
#line 7770 "hint.w"

extern void leak_in(pointer p,int s);
extern void leak_out(pointer p,int s);
/*:394*/
#line 7794 "hint.w"


#endif
/*:395*/
