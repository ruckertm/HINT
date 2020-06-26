	/*433:*/
	#line 8755 "format.w"

#include "basetypes.h"
#include <string.h>
#include <math.h>
#include <zlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "error.h"
#include "hformat.h"
#include "hget.h"


uint8_t*hpos= NULL,*hstart= NULL,*hend= NULL;


	/*274:*/
	#line 5713 "format.w"

	/*275:*/
	#line 5755 "format.w"

#ifdef WIN32
#include <windows.h>
#include <io.h>
#define PROT_READ   0x1
#define MAP_PRIVATE 0x02
#define MAP_FAILED   ((void *) -1)
static HANDLE hMap;
void*mmap(void*addr,size_t length,int prot,int flags,
int fd,off_t offset)
{HANDLE hFile= (HANDLE)_get_osfhandle(fd);
if(hFile==INVALID_HANDLE_VALUE)QUIT("Unable to get file handle");
hMap= CreateFileMapping(hFile,NULL,PAGE_READONLY,0,0,NULL);
if(hMap==NULL)QUIT("Unable to map file into memory");
addr= MapViewOfFile(hMap,FILE_MAP_READ,0,0,0);
if(addr==NULL)QUIT("Unable to obtain address of file mapping");
CloseHandle(hFile);
return addr;
}

int munmap(void*addr,size_t length)
{UnmapViewOfFile(addr);
CloseHandle(hMap);
hMap= NULL;
return 0;
}
#else
#include <sys/mman.h>
#endif
	/*:275*/
	#line 5714 "format.w"

static size_t hbase_size;
uint8_t*hbase= NULL;
extern char*in_name;
void hget_map(void)
{struct stat st;
int fd;
fd= open(in_name,O_RDONLY,0);
if(fd<0)QUIT("Unable to open file %s",in_name);
if(fstat(fd,&st)<0)QUIT("Unable to get file size");
hbase_size= st.st_size;
hbase= mmap(NULL,hbase_size,PROT_READ,MAP_PRIVATE,fd,0);
if(hbase==MAP_FAILED)
{hbase= NULL;hbase_size= 0;
QUIT("Unable to map file into memory");
}
close(fd);
hpos= hstart= hbase;
hend= hstart+hbase_size;
}


void hget_unmap(void)
{munmap(hbase,hbase_size);
hbase= NULL;
hbase_size= 0;
hpos= hstart= hend= NULL;
}
	/*:274*/
	#line 8772 "format.w"

	/*262:*/
	#line 5528 "format.w"

int version= 1,subversion= 0;
char hbanner[MAX_BANNER+1];
bool hcheck_banner(char*magic)
{int hbanner_size= 0;
char*t;
t= hbanner;
if(strncmp(magic,hbanner,4)!=0)QUIT("This is not a %s file",magic);
else t+= 4;
hbanner_size= (int)strnlen(hbanner,MAX_BANNER);
if(hbanner[hbanner_size-1]!='\n')QUIT("Banner exceeds maximum size=0x%x",MAX_BANNER);
if(*t!=' ')QUIT("Space expected after %s",magic);
else t++;
version= strtol(t,&t,10);
if(*t!='.')QUIT("Dot expected after version number %d",version);
else t++;
subversion= strtol(t,&t,10);
if(*t!=' '&&*t!='\n')QUIT("Space expected after subversion number %d",subversion);
LOG("%s file version %d.%d:%s",magic,version,subversion,t);
DBG(DBGDIR,"banner size=0x%x\n",hbanner_size);
return true;
}
	/*:262*/
	#line 8773 "format.w"

	/*284:*/
	#line 6022 "format.w"

entry_t*dir= NULL;
uint16_t section_no,max_section_no;
void new_directory(uint32_t entries)
{DBG(DBGDIR,"Creating directory with %d entries\n",entries);
RNG("Directory entries",entries,3,0x10000);
max_section_no= entries-1;
ALLOCATE(dir,entries,entry_t);
dir[0].section_no= 0;dir[1].section_no= 1;dir[2].section_no= 2;
}
	/*:284*/	/*285:*/
	#line 6035 "format.w"

void hset_entry(entry_t*e,uint16_t i,uint32_t size,uint32_t xsize,char*file_name)
{e->section_no= i;
e->size= size;e->xsize= xsize;
if(file_name==NULL||*file_name==0)
e->file_name= NULL;
else
e->file_name= strdup(file_name);
DBG(DBGDIR,"Creating entry %d: \"%s\" size=0x%x xsize=0x%x\n",i,file_name,size,xsize);
}
	/*:285*/
	#line 8774 "format.w"

	/*35:*/
	#line 1016 "format.w"

#define HGET_STRING(S) S= (char*)hpos;\
 while(hpos<hend && *hpos!=0) { RNG("String character",*hpos,0x20,0x7E); hpos++;}\
 hpos++;
	/*:35*/	/*269:*/
	#line 5655 "format.w"

#define HGET_ERROR QUIT("HGET overrun in section %d at " SIZE_F "\n",section_no,hpos-hstart)
#define HEND   ((hpos<=hend)?0:(HGET_ERROR,0))

#define HGET8      ((hpos<hend)?*(hpos++):(HGET_ERROR,0))
#define HGET16(X) ((X)= (hpos[0]<<8)+hpos[1],hpos+= 2,HEND)
#define HGET24(X) ((X)= (hpos[0]<<16)+(hpos[1]<<8)+hpos[2],hpos+= 3,HEND)
#define HGET32(X) ((X)= (hpos[0]<<24)+(hpos[1]<<16)+(hpos[2]<<8)+hpos[3],hpos+= 4,HEND)
#define HGETTAG(A) A= HGET8,DBGTAG(A,hpos-1)
	/*:269*/	/*293:*/
	#line 6219 "format.w"

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
	/*:293*/
	#line 8775 "format.w"

	/*263:*/
	#line 5557 "format.w"

void hget_banner(void)
{int i;
for(i= 0;i<MAX_BANNER;i++)
{hbanner[i]= HGET8;
if(hbanner[i]=='\n')break;
}
hbanner[++i]= 0;
}
	/*:263*/	/*276:*/
	#line 5797 "format.w"

	/*278:*/
	#line 5874 "format.w"


static void hdecompress(uint16_t n)
{z_stream z;
uint8_t*buffer;
int i;

DBG(DBGCOMPRESS,"Decompressing section %d from 0x%x to 0x%x byte\n",n,dir[n].size,dir[n].xsize);
z.zalloc= (alloc_func)0;
z.zfree= (free_func)0;
z.opaque= (voidpf)0;
z.next_in= hstart;
z.avail_in= hend-hstart;
if(inflateInit(&z)!=Z_OK)
QUIT("Unable to initialize decompression: %s",z.msg);
ALLOCATE(buffer,dir[n].xsize+MAX_TAG_DISTANCE,uint8_t);
DBG(DBGBUFFER,"Allocating output buffer size=0x%x, margin=0x%x\n",dir[n].xsize,MAX_TAG_DISTANCE);
z.next_out= buffer;
z.avail_out= dir[n].xsize+MAX_TAG_DISTANCE;
i= inflate(&z,Z_FINISH);
DBG(DBGCOMPRESS,"in: avail/total=0x%x/0x%lx ""out: avail/total=0x%x/0x%lx, return %d;\n",
z.avail_in,z.total_in,z.avail_out,z.total_out,i);
if(i!=Z_STREAM_END)
QUIT("Unable to complete decompression: %s",z.msg);
if(z.avail_in!=0)
QUIT("Decompression missed input data");
if(z.total_out!=dir[n].xsize)
QUIT("Decompression output size missmatch 0x%lx != 0x%x",z.total_out,dir[n].xsize);
if(inflateEnd(&z)!=Z_OK)
QUIT("Unable to finalize decompression: %s",z.msg);
dir[n].buffer= buffer;
dir[n].bsize= dir[n].xsize;
hpos= hstart= buffer;
hend= hstart+dir[n].xsize;
}
	/*:278*/
	#line 5798 "format.w"


void hget_section(uint16_t n)
{DBG(DBGDIR,"Reading section %d\n",n);
RNG("Section number",n,0,max_section_no);
if(dir[n].buffer!=NULL&&dir[n].xsize>0)
{hpos= hstart= dir[n].buffer;
hend= hstart+dir[n].xsize;
}
else
{hpos= hstart= hbase+dir[n].pos;
hend= hstart+dir[n].size;
if(dir[n].xsize>0)hdecompress(n);
}
}
	/*:276*/	/*294:*/
	#line 6243 "format.w"

void hget_entry(entry_t*e)
{	/*14:*/
	#line 688 "format.w"

uint8_t a,z;
uint32_t node_pos= hpos-hstart;
if(hpos>=hend)QUIT("Attempt to read a start byte at the end of the section");
HGETTAG(a);
	/*:14*/
	#line 6245 "format.w"

DBG(DBGDIR,"Reading directory entry\n");
switch(a)
{case TAG(0,b000+0):HGET_ENTRY(b000+0,*e);break;
case TAG(0,b000+1):HGET_ENTRY(b000+1,*e);break;
case TAG(0,b000+2):HGET_ENTRY(b000+2,*e);break;
case TAG(0,b000+3):HGET_ENTRY(b000+3,*e);break;
case TAG(0,b100+0):HGET_ENTRY(b100+0,*e);break;
case TAG(0,b100+1):HGET_ENTRY(b100+1,*e);break;
case TAG(0,b100+2):HGET_ENTRY(b100+2,*e);break;
case TAG(0,b100+3):HGET_ENTRY(b100+3,*e);break;
default:TAGERR(a);break;
}
	/*15:*/
	#line 695 "format.w"

HGETTAG(z);
if(a!=z)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at 0x%x to "SIZE_F"\n",
NAME(a),INFO(a),NAME(z),INFO(z),node_pos,hpos-hstart-1);
	/*:15*/
	#line 6258 "format.w"

DBG(DBGDIR,"entry %d: size=0x%x xsize=0x%x\n",e->section_no,e->size,e->xsize);
}
	/*:294*/	/*295:*/
	#line 6276 "format.w"

static void hget_root(entry_t*root)
{DBG(DBGDIR,"Get Root\n");
hget_entry(root);
root->pos= hpos-hstart;
max_section_no= root->section_no;
root->section_no= 0;
if(max_section_no<2)QUIT("Sections 0, 1, and 2 are mandatory");
}

void hget_directory(void)
{int i;
entry_t root= {0};
hget_root(&root);
DBG(DBGDIR,"Get Directory\n");
new_directory(max_section_no+1);
dir[0]= root;
hget_section(0);
for(i= 1;i<=max_section_no;i++)
{hget_entry(&(dir[i]));
dir[i].pos= dir[i-1].pos+dir[i-1].size;
}
DBG(DBGDIR,"Directory at 0x%"PRIx64"\n",dir[0].pos);
DBG(DBGDIR,"Definitions at 0x%"PRIx64"\n",dir[1].pos);
DBG(DBGDIR,"Content at 0x%"PRIx64"\n",dir[2].pos);
}

void hclear_dir(void)
{int i;
if(dir==NULL)return;
for(i= 0;i<3;i++)
if(dir[i].xsize>0&&dir[i].buffer!=NULL)free(dir[i].buffer);
free(dir);dir= NULL;
}

	/*:295*/	/*311:*/
	#line 6655 "format.w"

void hget_max_definitions(void)
{kind_t k;
	/*14:*/
	#line 688 "format.w"

uint8_t a,z;
uint32_t node_pos= hpos-hstart;
if(hpos>=hend)QUIT("Attempt to read a start byte at the end of the section");
HGETTAG(a);
	/*:14*/
	#line 6658 "format.w"

if(a!=TAG(list_kind,0))QUIT("Start of maximum list expected");
for(k= 0;k<32;k++)max_ref[k]= max_default[k];
while(true)
{uint8_t n;
if(hpos>=hend)QUIT("Unexpected end of maximum list");
node_pos= hpos-hstart;
HGETTAG(a);
if(KIND(a)==list_kind)break;
if(INFO(a)!=1)QUIT("Maximum info %d not supported",INFO(a));
k= KIND(a);
if(max_fixed[k]>max_default[k])
QUIT("Maximum value for kind %s not supported",definition_name[k]);
n= HGET8;
RNG("Maximum number",n,max_ref[k],0xFF);
max_ref[k]= n;
DBG(DBGDEF,"max(%s) = %d\n",definition_name[k],max_ref[k]);
	/*15:*/
	#line 695 "format.w"

HGETTAG(z);
if(a!=z)
QUIT("Tag mismatch [%s,%d]!=[%s,%d] at 0x%x to "SIZE_F"\n",
NAME(a),INFO(a),NAME(z),INFO(z),node_pos,hpos-hstart-1);
	/*:15*/
	#line 6675 "format.w"

}
if(INFO(a)!=0)QUIT("End of maximum list with info %d",INFO(a));

}
	/*:311*/
	#line 8776 "format.w"



	/*:433*/
