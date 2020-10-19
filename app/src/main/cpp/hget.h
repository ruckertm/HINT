	/*433:*/
	#line 8747 "format.w"


	/*35:*/
	#line 1016 "format.w"

#define HGET_STRING(S) S= (char*)hpos;\
 while(hpos<hend && *hpos!=0) { RNG("String character",*hpos,0x20,0x7E); hpos++;}\
 hpos++;
	/*:35*/	/*270:*/
	#line 5663 "format.w"

#define HGET_ERROR QUIT("HGET overrun in section %d at " SIZE_F "\n",section_no,hpos-hstart)
#define HEND   ((hpos<=hend)?0:(HGET_ERROR,0))

#define HGET8      ((hpos<hend)?*(hpos++):(HGET_ERROR,0))
#define HGET16(X) ((X)= (hpos[0]<<8)+hpos[1],hpos+= 2,HEND)
#define HGET24(X) ((X)= (hpos[0]<<16)+(hpos[1]<<8)+hpos[2],hpos+= 3,HEND)
#define HGET32(X) ((X)= (hpos[0]<<24)+(hpos[1]<<16)+(hpos[2]<<8)+hpos[3],hpos+= 4,HEND)
#define HGETTAG(A) A= HGET8,DBGTAG(A,hpos-1)
	/*:270*/	/*294:*/
	#line 6240 "format.w"

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
	/*:294*/
	#line 8749 "format.w"

	/*284:*/
	#line 6029 "format.w"

typedef struct{
uint64_t pos;
uint32_t size,xsize;
uint16_t section_no;
char*file_name;
uint8_t*buffer;
uint32_t bsize;
}entry_t;
	/*:284*/
	#line 8750 "format.w"

extern entry_t*dir;
extern uint16_t section_no,max_section_no;
extern uint8_t*hpos,*hstart,*hend;

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
	/*:433*/
