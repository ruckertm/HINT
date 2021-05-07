	/*463:*/
	#line 9420 "format.w"

	/*35:*/
	#line 1027 "format.w"

#define HGET_STRING(S) S= (char*)hpos;\
 while(hpos<hend && *hpos!=0) { RNG("String character",*hpos,0x20,0x7E); hpos++;}\
 hpos++;
	/*:35*/	/*295:*/
	#line 6260 "format.w"

#define HGET_ERROR QUIT("HGET overrun in section %d at " SIZE_F "\n",section_no,hpos-hstart)
#define HEND   ((hpos<=hend)?0:(HGET_ERROR,0))

#define HGET8      ((hpos<hend)?*(hpos++):(HGET_ERROR,0))
#define HGET16(X) ((X)= (hpos[0]<<8)+hpos[1],hpos+= 2,HEND)
#define HGET24(X) ((X)= (hpos[0]<<16)+(hpos[1]<<8)+hpos[2],hpos+= 3,HEND)
#define HGET32(X) ((X)= (hpos[0]<<24)+(hpos[1]<<16)+(hpos[2]<<8)+hpos[3],hpos+= 4,HEND)
#define HGETTAG(A) A= HGET8,DBGTAG(A,hpos-1)
	/*:295*/	/*319:*/
	#line 6839 "format.w"

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
	/*:319*/
	#line 9421 "format.w"

	/*1:*/
	#line 318 "format.w"

typedef struct{uint32_t c;uint8_t f;}glyph_t;
	/*:1*/	/*111:*/
	#line 2118 "format.w"

typedef struct{
dimen_t h,d,w;
}rule_t;
	/*:111*/	/*130:*/
	#line 2548 "format.w"

typedef struct{
kind_t k;
uint32_t p;
uint32_t s;
}list_t;
	/*:130*/	/*138:*/
	#line 2967 "format.w"

typedef enum{txt_font= 0x00,txt_global= 0x08,txt_local= 0x11,
txt_cc= 0x1D,txt_node= 0x1E,txt_hyphen= 0x1F,
txt_glue= 0x20,txt_ignore= 0xFB}txt_t;
	/*:138*/	/*149:*/
	#line 3234 "format.w"

typedef struct{kind_t k;int n;}ref_t;
	/*:149*/	/*150:*/
	#line 3264 "format.w"

typedef struct{dimen_t h,d,w,a;float32_t r;int8_t s,o;list_t l;}box_t;
	/*:150*/	/*164:*/
	#line 3617 "format.w"

typedef struct{
bool x;
xdimen_t d;
}kern_t;
	/*:164*/	/*185:*/
	#line 3899 "format.w"

typedef struct{uint8_t f;list_t l;}lig_t;
	/*:185*/	/*193:*/
	#line 4016 "format.w"
typedef struct hyphen_t{bool x;list_t p,q;uint8_t r;}hyphen_t;	/*:193*/	/*228:*/
	#line 4514 "format.w"

typedef struct{
uint16_t n;
dimen_t w,h;
stretch_t p,m;
}image_t;
	/*:228*/	/*237:*/
	#line 4755 "format.w"

typedef enum{l_ref16= b001,l_nested= b010,l_public= b100,
l_defined= 0x10,l_used= 0x20,l_pos= 0x40}l_flags_t;
typedef
struct{l_flags_t i;uint32_t pos;
uint8_t where;
int next;
uint32_t pos0;uint8_t f;
char*n;uint8_t major,minor;
}label_t;

	/*:237*/	/*275:*/
	#line 5933 "format.w"

typedef
struct{uint8_t pg;uint32_t pos;bool on;int link;}range_pos_t;
	/*:275*/
	#line 9422 "format.w"

	/*309:*/
	#line 6628 "format.w"

typedef struct{
uint64_t pos;
uint32_t size,xsize;
uint16_t section_no;
char*file_name;
uint8_t*buffer;
uint32_t bsize;
}entry_t;
	/*:309*/
	#line 9423 "format.w"

extern entry_t*dir;
extern uint16_t section_no,max_section_no;
extern uint8_t*hpos,*hstart,*hend,*hpos0;

extern uint64_t hget_map(void);
extern void hget_unmap(void);

extern void new_directory(uint32_t entries);
extern void hset_entry(entry_t*e,uint16_t i,uint32_t size,uint32_t xsize,char*file_name);

extern void hget_banner(void);
extern void hget_section(uint16_t n);
extern void hget_entry(entry_t*e);
extern void hget_directory(void);
extern void hclear_dir(void);
extern bool hcheck_banner(char*magic);

extern void hget_max_definitions(void);
	/*:463*/
