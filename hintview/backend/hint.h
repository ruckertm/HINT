/*387:*/
#line 7652 "hint.w"

#ifndef _HINT_H_
#define _HINT_H_

typedef uint16_t pointer;
typedef int scaled;

/*44:*/
#line 758 "hint.w"

extern void hrestore_param_list(void);
/*:44*//*49:*/
#line 813 "hint.w"

typedef struct{
pointer p,t;
}Stream;
extern Stream*streams;
/*:49*//*64:*/
#line 1030 "hint.w"

extern void hfill_page_template(void);
/*:64*//*83:*/
#line 1293 "hint.w"

void hget_content(void);
/*:83*//*87:*/
#line 1345 "hint.w"

extern void hteg_content(void);
/*:87*//*164:*/
#line 2636 "hint.w"

extern void hprune_unwanted_nodes(void);
/*:164*//*174:*/
#line 2832 "hint.w"

extern void set_line_break_params(void);
/*:174*//*176:*/
#line 2873 "hint.w"

extern void hget_par_node(uint32_t offset);
/*:176*//*181:*/
#line 2973 "hint.w"

extern void hteg_par_node(uint32_t offset);
/*:181*//*209:*/
#line 3348 "hint.w"

extern pointer*pointer_def[32];
extern scaled*dimen_def;
extern int32_t*integer_def;
/*:209*//*210:*/
#line 3403 "hint.w"

extern Stream*streams;
extern bool flush_pages(uint32_t pos);
extern pointer skip(uint8_t n);
extern pointer*box_ptr(uint8_t n);
extern int count(uint8_t n);
extern scaled dimen(uint8_t n);
/*:210*//*213:*/
#line 3460 "hint.w"

extern void hpage_init(void);
/*:213*//*215:*/
#line 3477 "hint.w"

extern void hflush_contribution_list(void);
/*:215*//*235:*/
#line 3880 "hint.w"

#define HINT_NO_LOC 0xFFFFFFFFFFFFFFFF
#define PAGE_LOC(POS0,OFF) (((uint64_t)((POS0)+(OFF))<<32) + (uint64_t)(OFF))
#define LOC_POS(P) ((P)>>32) 
#define LOC_OFF(P) ((P)&0xFFFFFFFF) 
#define LOC_POS0(P) (LOC_POS(P)-LOC_OFF(P)) 
/*:235*//*238:*/
#line 3917 "hint.w"

extern uint64_t page_loc[];
extern int cur_loc;
/*:238*//*240:*/
#line 3966 "hint.w"

extern void hloc_clear(void);
extern bool hloc_next(void);
extern bool hloc_prev(void);
extern uint64_t hlocation(pointer p);
/*:240*//*245:*/
#line 4084 "hint.w"

extern void hloc_init(void);
extern void store_map(pointer p,uint32_t pos,uint32_t offset);
extern uint32_t hposition(pointer p);
extern void hloc_set(uint64_t h);
extern void hloc_set_next(pointer p);
/*:245*//*247:*/
#line 4155 "hint.w"

extern int hint_begin(void);
extern void hint_end(void);
extern bool hint_map(void);
extern void hint_unmap(void);
/*:247*//*252:*/
#line 4279 "hint.w"

extern bool hint_forward(void);
extern bool hint_backward(void);
/*:252*//*255:*/
#line 4310 "hint.w"

extern scaled hvsize,hhsize;
/*:255*//*278:*/
#line 4868 "hint.w"

typedef struct{
uint64_t pos;
uint8_t depth;
uint8_t where;
int p;
char*title;
}hint_Outline;
extern hint_Outline*hint_outlines;
/*:278*//*279:*/
#line 4886 "hint.w"

#define LABEL_UNDEF 0
#define LABEL_TOP 1
#define LABEL_BOT 2
#define LABEL_MID 3
/*:279*//*283:*/
#line 4945 "hint.w"

extern int hint_get_outline_max(void);
extern hint_Outline*hint_get_outlines(void);
extern uint64_t hint_outline_page(int i);
/*:283*//*285:*/
#line 5060 "hint.w"

extern void trv_init(void(*f)(uint32_t c));
extern void trv_vlist(pointer p);
extern void trv_hlist(pointer p);
/*:285*//*313:*/
#line 5595 "hint.w"

typedef struct{
uint64_t pos;
uint8_t where;
scaled top,bottom,left,right;
}hint_Link;
extern hint_Link*hint_links;
extern int max_link;
/*:313*//*318:*/
#line 5758 "hint.w"

extern int hint_find_link(scaled x,scaled y,scaled precission);
extern uint64_t hint_link_page(int i);
/*:318*//*386:*/
#line 7635 "hint.w"

extern void leak_in(pointer p,int s);
extern void leak_out(pointer p,int s);
/*:386*/
#line 7659 "hint.w"


#endif
/*:387*/
