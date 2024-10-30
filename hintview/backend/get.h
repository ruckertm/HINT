	/*548:*/
	#line 11404 "format.w"

	/*1:*/
	#line 326 "format.w"

typedef struct{uint32_t c;uint8_t f;}Glyph;
	/*:1*/	/*114:*/
	#line 2179 "format.w"

typedef struct{
Dimen h,d,w;
}Rule;
	/*:114*/	/*123:*/
	#line 2293 "format.w"

typedef struct{
bool x;
Xdimen d;
}Kern;
	/*:123*/	/*141:*/
	#line 2716 "format.w"

typedef struct{
Tag t;
uint32_t p;
uint32_t s;
}List;
	/*:141*/	/*149:*/
	#line 3142 "format.w"

typedef enum{txt_font= 0x00,txt_global= 0x08,txt_local= 0x11,
txt_cc= 0x1D,txt_node= 0x1E,txt_hyphen= 0x1F,
txt_glue= 0x20,txt_ignore= 0xFB}Txt;
	/*:149*/	/*160:*/
	#line 3442 "format.w"

typedef struct{Dimen h,d,w,a;float32_t r;int8_t s,o;List l;}Box;
	/*:160*/	/*187:*/
	#line 4027 "format.w"

typedef struct{uint8_t f;List l;}Lig;
	/*:187*/	/*195:*/
	#line 4144 "format.w"

typedef struct{bool x;List p,q;uint8_t r;}Disc;
	/*:195*/	/*228:*/
	#line 4699 "format.w"

typedef struct{
uint16_t n;
float32_t a;
Xdimen w,h;
uint8_t wr,hr;
}Image;
	/*:228*/	/*272:*/
	#line 5796 "format.w"

typedef struct{
uint8_t*t;
int s;
int d;
uint16_t r;
}Outline;
	/*:272*/	/*323:*/
	#line 7173 "format.w"

typedef
struct{uint8_t pg;uint32_t pos;bool on;int link;}RangePos;
	/*:323*/	/*412:*/
	#line 9196 "format.w"

typedef struct{Kind k;int n;}Ref;
	/*:412*/
	#line 11405 "format.w"

	/*357:*/
	#line 7917 "format.w"

typedef struct{
uint64_t pos;
uint32_t size,xsize;
uint16_t section_no;
char*file_name;
uint8_t*buffer;
uint32_t bsize;
}Entry;
	/*:357*/
	#line 11406 "format.w"

	/*38:*/
	#line 1075 "format.w"

#define HGET_STRING(S) S= (char*)hpos;\
 while(hpos<hend && *hpos!=0) { RNG("String character",*hpos,0x20,0x7E); hpos++;}\
 hpos++;
	/*:38*/	/*147:*/
	#line 2885 "format.w"

#define HGET_LIST(I,L) \
  if (((I)&0x3)==0) {uint8_t n= HGET8; REF_RNG(KIND((L).t),n); (L).s= 0;}\
  else { (L).s= hget_list_size(I); hget_size_boundary(I);\
    (L).p= hpos-hstart; \
    hpos= hpos+(L).s; hget_size_boundary(I);\
    { uint32_t s= hget_list_size(I); \
      if (s!=(L).s) \
      QUIT("List sizes at 0x%x and " SIZE_F " do not match 0x%x != 0x%x",node_pos+1,hpos-hstart-I-1,(L).s,s);}}
	/*:147*/	/*343:*/
	#line 7518 "format.w"

#define HGET_ERROR  QUIT("HGET overrun in section %d at " SIZE_F "\n",section_no,hpos-hstart)
#define HEND   ((hpos<=hend)?0:(HGET_ERROR,0))

#define HGET8      ((hpos<hend)?*(hpos++):(HGET_ERROR,0))
#define HGET16(X) ((X)= (hpos[0]<<8)+hpos[1],hpos+= 2,HEND)
#define HGET24(X) ((X)= (hpos[0]<<16)+(hpos[1]<<8)+hpos[2],hpos+= 3,HEND)
#define HGET32(X) ((X)= (hpos[0]<<24)+(hpos[1]<<16)+(hpos[2]<<8)+hpos[3],hpos+= 4,HEND)
#define HGETTAG(A) A= HGET8,DBGTAG(A,hpos-1)
	/*:343*/	/*368:*/
	#line 8146 "format.w"

#define HGET_SIZE(I) \
  if ((I)&b100) { \
    if (((I)&b011)==0) s= HGET8,xs= HGET8; \
    else if (((I)&b011)==1) HGET16(s),HGET16(xs); \
    else if (((I)&b011)==2) HGET24(s),HGET24(xs); \
    else if (((I)&b011)==3) HGET32(s),HGET32(xs); \
   } \
  else { \
    if (((I)&b011)==0) s= HGET8; \
    else if (((I)&b011)==1) HGET16(s); \
    else if (((I)&b011)==2) HGET24(s); \
    else if (((I)&b011)==3) HGET32(s); \
   }

#define HGET_ENTRY(I,E) \
{ uint16_t i; \
  uint32_t s= 0,xs= 0; \
  char *file_name; \
  HGET16(i); HGET_SIZE(I); HGET_STRING(file_name); \
  hset_entry(&(E),i,s,xs,file_name); \
}
	/*:368*/	/*495:*/
	#line 10627 "format.w"

#define HBACK(X) ((hpos-(X)<hstart)?(QUIT("HTEG underflow\n"),NULL):(hpos-= (X)))

#define HTEG8     (HBACK(1),hpos[0])
#define HTEG16(X) (HBACK(2),(X)= (hpos[0]<<8)+hpos[1])
#define HTEG24(X) (HBACK(3),(X)= (hpos[0]<<16)+(hpos[1]<<8)+hpos[2])
#define HTEG32(X) (HBACK(4),(X)= (hpos[0]<<24)+(hpos[1]<<16)+(hpos[2]<<8)+hpos[3])
#define HTEGTAG(X) X= HTEG8,DBGTAG(X,hpos)
	/*:495*/
	#line 11407 "format.w"


extern Entry*dir;
extern uint16_t section_no,max_section_no;
extern uint8_t*hpos,*hstart,*hend,*hpos0;
extern uint64_t hin_size,hin_time;
extern uint8_t*hin_addr;

extern Label*labels;
extern char*hin_name;
extern bool hget_map(void);
extern void hget_unmap(void);

extern void new_directory(uint32_t entries);
extern void hset_entry(Entry*e,uint16_t i,uint32_t size,uint32_t xsize,char*file_name);

extern void hget_banner(void);
extern void hget_section(uint16_t n);
extern void hget_entry(Entry*e);
extern void hget_directory(void);
extern void hclear_dir(void);
extern bool hcheck_banner(char*magic);
extern int max_range;

extern void hget_max_definitions(void);
extern uint32_t hget_utf8(void);
extern void hget_size_boundary(Info info);
extern uint32_t hget_list_size(Info info);
extern void hget_list(List*l);
extern float32_t hget_float32(void);
extern void hff_hpos(void);
extern uint32_t hff_list_pos,hff_list_size;
extern Tag hff_tag;
extern float32_t hteg_float32(void);
extern uint32_t hteg_list_size(Info info);


#if 0
extern void hteg_list(List*l);

extern void hteg_size_boundary(Info info);

#endif

	/*:548*/
