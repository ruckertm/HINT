	/*433:*/
	#line 8551 "format.w"

#include "basetypes.h"
#include <stdio.h>
#include <string.h>
#include "error.h"
#include "hformat.h"
#include "hdefaults.h"


	/*7:*/
	#line 478 "format.w"

#define DEF_KIND(C,D,N) #C
const char*content_name[0x20]= {	/*8:*/
	#line 520 "format.w"

DEF_KIND(text,text,0),
DEF_KIND(list,list,1),
DEF_KIND(param,param,2),
DEF_KIND(xdimen,xdimen,3),
DEF_KIND(adjust,adjust,4),
DEF_KIND(glyph,font,5),
DEF_KIND(kern,dimen,6),
DEF_KIND(glue,glue,7),
DEF_KIND(ligature,ligature,8),
DEF_KIND(hyphen,hyphen,9),
DEF_KIND(math,math,10),
DEF_KIND(rule,rule,11),
DEF_KIND(image,image,12),
DEF_KIND(leaders,leaders,13),
DEF_KIND(baseline,baseline,14),
DEF_KIND(hbox,hbox,15),
DEF_KIND(vbox,vbox,16),
DEF_KIND(par,par,17),
DEF_KIND(display,display,18),
DEF_KIND(table,table,19),
DEF_KIND(item,item,20),
DEF_KIND(hset,hset,21),
DEF_KIND(vset,vset,22),
DEF_KIND(hpack,hpack,23),
DEF_KIND(vpack,vpack,24),
DEF_KIND(stream,stream,25),
DEF_KIND(page,page,26),
DEF_KIND(range,range,27),
DEF_KIND(undefined1,undefined1,28),
DEF_KIND(undefined2,undefined2,29),
DEF_KIND(undefined3,undefined3,30),
DEF_KIND(penalty,int,31)

	/*:8*/
	#line 480 "format.w"
};
#undef DEF_KIND

#define DEF_KIND(C,D,N) #D
const char*definition_name[0x20]= {	/*8:*/
	#line 520 "format.w"

DEF_KIND(text,text,0),
DEF_KIND(list,list,1),
DEF_KIND(param,param,2),
DEF_KIND(xdimen,xdimen,3),
DEF_KIND(adjust,adjust,4),
DEF_KIND(glyph,font,5),
DEF_KIND(kern,dimen,6),
DEF_KIND(glue,glue,7),
DEF_KIND(ligature,ligature,8),
DEF_KIND(hyphen,hyphen,9),
DEF_KIND(math,math,10),
DEF_KIND(rule,rule,11),
DEF_KIND(image,image,12),
DEF_KIND(leaders,leaders,13),
DEF_KIND(baseline,baseline,14),
DEF_KIND(hbox,hbox,15),
DEF_KIND(vbox,vbox,16),
DEF_KIND(par,par,17),
DEF_KIND(display,display,18),
DEF_KIND(table,table,19),
DEF_KIND(item,item,20),
DEF_KIND(hset,hset,21),
DEF_KIND(vset,vset,22),
DEF_KIND(hpack,hpack,23),
DEF_KIND(vpack,vpack,24),
DEF_KIND(stream,stream,25),
DEF_KIND(page,page,26),
DEF_KIND(range,range,27),
DEF_KIND(undefined1,undefined1,28),
DEF_KIND(undefined2,undefined2,29),
DEF_KIND(undefined3,undefined3,30),
DEF_KIND(penalty,int,31)

	/*:8*/
	#line 484 "format.w"
};
#undef DEF_KIND
	/*:7*/	/*30:*/
	#line 911 "format.w"

char scratch_buffer[MAX_SCRATCH];
	/*:30*/	/*142:*/
	#line 2840 "format.w"

int txt_length;
	/*:142*/	/*251:*/
	#line 5167 "format.w"

int*page_on;
range_pos_t*range_pos;
int next_range= 1,max_range;
	/*:251*/	/*262:*/
	#line 5357 "format.w"

int version= 1,subversion= 0;
char hbanner[MAX_BANNER+1];
int hbanner_size= 0;
	/*:262*/	/*265:*/
	#line 5419 "format.w"

uint8_t*hpos,*hstart,*hend;
	/*:265*/	/*281:*/
	#line 5730 "format.w"

entry_t*dir= NULL;
uint16_t section_no,max_section_no;
	/*:281*/	/*297:*/
	#line 6158 "format.w"

int max_ref[32];
	/*:297*/	/*319:*/
	#line 6490 "format.w"

char**hfont_name;
	/*:319*/	/*356:*/
	#line 7182 "format.w"

debugmode debugflags= dbgnone;
#define MAX_NAME 1024
char prog_name[MAX_NAME];
char in_name[MAX_NAME];
char*in_ext;
char*out_ext;
bool option_utf8= false;
bool option_hex= false;
bool option_force= false;
bool option_compress= false;
	/*:356*/	/*359:*/
	#line 7248 "format.w"

FILE*hin= NULL,*hout= NULL,*hlog= NULL;
	/*:359*/
	#line 8560 "format.w"


	/*263:*/
	#line 5367 "format.w"

bool hread_banner(char*magic)
{char*tail;
int i,c;
i= 0;
do{
c= fgetc(hin);
if(c!=EOF)
hbanner[i++]= (char)c;
}while(c!='\n'&&c!=EOF&&i<MAX_BANNER);
hbanner[i]= 0;
tail= hbanner;
if(strncmp(magic,hbanner,4)!=0)QUIT("This is not a %s file",magic);
else tail+= 4;
hbanner_size= (int)strlen(hbanner);
if(hbanner[hbanner_size-1]!='\n')QUIT("Banner exceeds maximum size=0x%x",MAX_BANNER);
if(*tail!=' ')QUIT("Space expected after %s",magic);
else tail++;
version= strtol(tail,&tail,10);
if(*tail!='.')QUIT("Dot expected after version number %d",version);
else tail++;
subversion= strtol(tail,&tail,10);
if(*tail!=' '&&*tail!='\n')QUIT("Space expected after subversion number %d",subversion);
MESSAGE("%s file version %d.%d:%s",magic,version,subversion,tail);
DBG(dbgdir,"banner size=0x%x\n",hbanner_size);
return true;
}
	/*:263*/	/*264:*/
	#line 5399 "format.w"

size_t hwrite_banner(char*magic)
{return fprintf(hout,"%s %d.%d %s\n",magic,version,subversion,"stretch&shrink");
}
	/*:264*/	/*273:*/
	#line 5528 "format.w"

#define BUFFER_SIZE 1024
void new_output_buffers(void)
{dir[0].bsize= dir[1].bsize= dir[2].bsize= BUFFER_SIZE;
DBG(dbgbuffer,"Allocating output buffer size=0x%x, margin=0x%x\n",BUFFER_SIZE,SAFETY_MARGIN);
ALLOCATE(dir[0].buffer,dir[0].bsize+SAFETY_MARGIN,uint8_t);
ALLOCATE(dir[1].buffer,dir[1].bsize+SAFETY_MARGIN,uint8_t);
ALLOCATE(dir[2].buffer,dir[2].bsize+SAFETY_MARGIN,uint8_t);
}
	/*:273*/	/*282:*/
	#line 5737 "format.w"

void new_directory(uint32_t entries)
{DBG(dbgbasic,"Creating directory with %d entries\n",entries);
RNG("Directory entries",entries,3,0x10000);
max_section_no= entries-1;
ALLOCATE(dir,entries,entry_t);
dir[0].section_no= 0;dir[1].section_no= 1;dir[2].section_no= 2;
}
	/*:282*/	/*283:*/
	#line 5748 "format.w"

void hset_entry(entry_t*e,uint16_t i,uint32_t size,uint32_t xsize,char*file_name)
{e->section_no= i;
e->size= size;e->xsize= xsize;
if(file_name==NULL||*file_name==0)
e->file_name= NULL;
else
e->file_name= strdup(file_name);
DBG(dbgdir,"Creating entry %d: \"%s\" size=0x%x xsize=0x%x\n",i,file_name,size,xsize);
}
	/*:283*/	/*298:*/
	#line 6162 "format.w"

void hset_max(void)
{kind_t k;
for(k= 0;k<32;k++)max_ref[k]= max_default[k];
}
	/*:298*/	/*300:*/
	#line 6191 "format.w"

void hallocate_data(void)
{	/*252:*/
	#line 5175 "format.w"

ALLOCATE(page_on,max_ref[page_kind]+1,int);
ALLOCATE(range_pos,2*(max_ref[range_kind]+1),range_pos_t);
	/*:252*/	/*321:*/
	#line 6498 "format.w"

ALLOCATE(hfont_name,max_ref[font_kind]+1,char*);
	/*:321*/
	#line 6193 "format.w"

}
	/*:300*/
	#line 8562 "format.w"


	/*:433*/
