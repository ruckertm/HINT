/*76:*/
#line 1178 ".\\hint.w"

#include <stdio.h> 
#include <string.h> 
#include "htex.h"
#include "hformat.h"
#include "hget.h"
#include "hteg.h"

/*244:*/
#line 3674 ".\\hint.w"


#define MAX_NAME 1024
char prog_name[MAX_NAME];
char in_name[MAX_NAME];

FILE*hlog;
/*:244*/
#line 1186 ".\\hint.w"


/*241:*/
#line 3620 ".\\hint.w"

void usage(void)
{fprintf(stderr,
"Usage: %s [options] filename.hnt\n",prog_name);
fprintf(stderr,
"Options:\n"
"\t -o file\t specify an output file name\n"
"\t -l     \t redirect stderr to a log file\n");
#ifdef DEBUG
fprintf(stderr,"\t -d XXX \t hexadecimal value. OR together these values:\n");
fprintf(stderr,"\t\t\t XX=%03X   basic debugging\n",dbgbasic);
fprintf(stderr,"\t\t\t XX=%03X   tag debugging\n",dbgtags);
fprintf(stderr,"\t\t\t XX=%03X   definition debugging\n",dbgdef);
fprintf(stderr,"\t\t\t XX=%03X   directory debugging\n",dbgdir);
fprintf(stderr,"\t\t\t XX=%03X   range debugging\n",dbgrange);
fprintf(stderr,"\t\t\t XX=%03X   compression debugging\n",dbgcompress);
fprintf(stderr,"\t\t\t XX=%03X   buffer debugging\n",dbgbuffer);
#endif
exit(1);
}
/*:241*//*245:*/
#line 3684 ".\\hint.w"

void hship_out(pointer p)
{static int page_count= 0;
page_count++;
DBG(dbgbasic,"\nCompleted box being shipped out [%d]",page_count);
show_box(p);
DBG(dbgbasic,"\n");
flush_node_list(p);
}


/*:245*/
#line 1188 ".\\hint.w"


int main(int argc,char*argv[])
{char stem_name[MAX_NAME];
int stem_length= 0,path_length= 0;
bool option_log= false;

/*240:*/
#line 3585 ".\\hint.w"

debugflags= dbgbasic;
strncpy(prog_name,argv[0],MAX_NAME);
if(argc<2)usage();
argv++;
while(*argv!=NULL)
{if((*argv)[0]=='-')
{char option= (*argv)[1];
switch(option)
{
case'l':option_log= true;break;
case'd':
argv++;if(*argv==NULL)usage();
debugflags= strtol(*argv,NULL,16);
break;
default:usage();
}
}
else
{strncpy(in_name,*argv,MAX_NAME);
path_length= (int)strlen(in_name);
if(path_length<4
||strncmp(in_name+path_length-4,".hnt",4)!=0)
strncat(in_name,".hnt",MAX_NAME-1);
stem_length= (int)strlen(in_name)-4;
strncpy(stem_name,in_name,stem_length);
stem_name[stem_length]= 0;
if(*(argv+1)!=NULL)usage();
}
argv++;
}
/*:240*/
#line 1195 ".\\hint.w"

/*242:*/
#line 3647 ".\\hint.w"

#ifdef DEBUG
if(option_log)
{
strncat(stem_name,".hlg",MAX_NAME);
hlog= freopen(stem_name,"w",stderr);
if(hlog==NULL)
{fprintf(stderr,"Unable to open logfile %s",stem_name);
hlog= stderr;
}
stem_name[stem_length]= 0;
}
else
hlog= stderr;
#else
hlog= stderr;
#endif
/*:242*/
#line 1196 ".\\hint.w"

hmem_init();
hlist_init();
hopen_file(in_name);
hget_banner();
hget_directory_section();
hget_definition_section();
hget_content_section();
hpage_init();
hpos= hend;
while(hpos> hstart)
{hteg_content();
while(hbuild_page_up())
{hship_out(stream[0].p);stream[0].p= 0;hresume_after_output();hpage_init();}
}
if(!hits_all_over())
{if(hbuild_page_up())
{hship_out(stream[0].p);stream[0].p= 0;}
}
/*243:*/
#line 3668 ".\\hint.w"

if(hlog!=NULL)fclose(hlog);
/*:243*/
#line 1215 ".\\hint.w"

return 0;
}

/*:76*/
