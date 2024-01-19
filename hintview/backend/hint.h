/*400:*/
#line 8167 "hint.w"

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
/*:64*//*88:*/
#line 1538 "hint.w"

void hget_content(void);
/*:88*//*92:*/
#line 1590 "hint.w"

extern void hteg_content(void);
/*:92*//*169:*/
#line 2881 "hint.w"

extern void hprune_unwanted_nodes(void);
/*:169*//*181:*/
#line 3120 "hint.w"

extern void set_line_break_params(void);
/*:181*//*183:*/
#line 3161 "hint.w"

extern void hget_par_node(uint32_t offset);
/*:183*//*188:*/
#line 3261 "hint.w"

extern void hteg_par_node(uint32_t offset);
/*:188*//*217:*/
#line 3656 "hint.w"

extern pointer*pointer_def[32];
extern scaled*dimen_def;
extern int32_t*integer_def;
/*:217*//*218:*/
#line 3711 "hint.w"

extern Stream*streams;
extern bool flush_pages(uint32_t pos);
extern pointer skip(uint8_t n);
extern pointer*box_ptr(uint8_t n);
extern int count(uint8_t n);
extern scaled dimen(uint8_t n);
/*:218*//*221:*/
#line 3768 "hint.w"

extern void hpage_init(void);
/*:221*//*223:*/
#line 3785 "hint.w"

extern void hflush_contribution_list(void);
/*:223*//*243:*/
#line 4188 "hint.w"

#define HINT_NO_LOC 0xFFFFFFFFFFFFFFFF
#define PAGE_LOC(POS0,OFF) (((uint64_t)((POS0)+(OFF))<<32) + (uint64_t)(OFF))
#define LOC_POS(P) ((P)>>32) 
#define LOC_OFF(P) ((P)&0xFFFFFFFF) 
#define LOC_POS0(P) (LOC_POS(P)-LOC_OFF(P)) 
/*:243*//*246:*/
#line 4225 "hint.w"

extern uint64_t page_loc[];
extern int cur_loc;
/*:246*//*248:*/
#line 4274 "hint.w"

extern void hloc_clear(void);
extern bool hloc_next(void);
extern bool hloc_prev(void);
extern uint64_t hlocation(pointer p);
/*:248*//*253:*/
#line 4392 "hint.w"

extern void hloc_init(void);
extern void store_map(pointer p,uint32_t pos,uint32_t offset);
extern uint32_t hposition(pointer p);
extern void hloc_set(uint64_t h);
extern void hloc_set_next(pointer p);
/*:253*//*255:*/
#line 4463 "hint.w"

extern int hint_begin(void);
extern void hint_end(void);
extern bool hint_map(void);
extern void hint_unmap(void);
/*:255*//*260:*/
#line 4587 "hint.w"

extern bool hint_forward(void);
extern bool hint_backward(void);
/*:260*//*263:*/
#line 4618 "hint.w"

extern scaled hvsize,hhsize;
/*:263*//*286:*/
#line 5176 "hint.w"

typedef struct{
uint64_t pos;
uint8_t depth;
uint8_t where;
int p;
char*title;
}hint_Outline;
extern hint_Outline*hint_outlines;
/*:286*//*287:*/
#line 5194 "hint.w"

#define LABEL_UNDEF 0
#define LABEL_TOP 1
#define LABEL_BOT 2
#define LABEL_MID 3
/*:287*//*291:*/
#line 5253 "hint.w"

extern int hint_get_outline_max(void);
extern hint_Outline*hint_get_outlines(void);
extern uint64_t hint_outline_page(int i);
/*:291*//*293:*/
#line 5368 "hint.w"

extern void trv_init(void(*f)(uint32_t c));
extern void trv_vlist(pointer p);
extern void trv_hlist(pointer p);
/*:293*//*322:*/
#line 5905 "hint.w"

typedef struct{
uint64_t pos;
uint8_t where;
scaled top,bottom,left,right;
}hint_Link;
extern hint_Link*hint_links;
extern int max_link;
/*:322*//*327:*/
#line 6076 "hint.w"

extern int hint_find_link(scaled x,scaled y,scaled precission);
extern uint64_t hint_link_page(int i);
/*:327*//*399:*/
#line 8150 "hint.w"

extern void leak_in(pointer p,int s);
extern void leak_out(pointer p,int s);
/*:399*/
#line 8174 "hint.w"


#endif
/*:400*/
