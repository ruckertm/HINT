#define FILE_MARKER "TEX PROF" \

#define unknown_file 0
#define system_file 1
#define terminal_file 2
#define DIR_SEPARATOR '/' \

#define active_base 1
#define single_base (active_base+256) 
#define null_cs (single_base+256) 
#define hash_base (null_cs+1) 
#define hash_size 45000 \

#define frozen_control_sequence (hash_base+hash_size) 
#define frozen_null_font (frozen_control_sequence+11) 
#define undefined_control_sequence (frozen_null_font+257) 
#define output_text 6
#define every_eof_text 15 \

#define POP_BIT 0x80 \

#define VERSION_STR "texprofile version 1.0" \

#define max_command 100 \

#define system_cmd (max_command+1) 
#define system_profile_on (system_cmd+1) 
#define system_profile_off (system_cmd+2) 
#define system_macro_push (system_cmd+3) 
#define system_macro_pop (system_cmd+4) 
#define system_macro_pop_small (system_cmd+5) 
#define system_macro_pop_0 (system_cmd+6)  \

/*1:*/
#line 200 "texprofile.w"
#include<stdlib.h> 
#include <stdio.h> 
#include <stdint.h> 
#include <stdbool.h> 
#include <ctype.h> 
#include <string.h> 
/*2:*/
#line 222 "texprofile.w"

static char*input_file_name= NULL;
static FILE*in= NULL;
/*:2*//*6:*/
#line 296 "texprofile.w"

static unsigned int file_num,
file_name_num,
macro_num,
macro_name_num,
stamp_num,
depth_num;
/*:6*//*9:*/
#line 330 "texprofile.w"

static char**full_file_names,**file_names,*file_name_buffer;
#define ALLOCATE(V,S) V =  calloc(S,sizeof(*V));\
                      if (V==NULL) error("Out of memory for " #V "[" #S "]");
/*:9*//*12:*/
#line 382 "texprofile.w"

static char*macro_name_buffer,**macro_names;
static uint16_t*macro_stack;
static struct map
{uint16_t n;
uint16_t m;
}*macro_map;
/*:12*//*16:*/
#line 473 "texprofile.w"

struct stamp{
uint8_t c;
uint8_t f;
uint16_t l;
uint16_t d;
uint16_t m;
uint32_t t;
}*stamps;

struct macro_def{
uint16_t n;
uint8_t f;
uint16_t l;
uint16_t link;
int a;
int count;
uint16_t e;
uint64_t t;
uint64_t T;
uint64_t s;
}*macro_defs;

int macro_def_num;
int macro_def_count;
/*:16*//*20:*/
#line 584 "texprofile.w"

bool opt_macro_id= false;
/*:20*//*24:*/
#line 615 "texprofile.w"

uint64_t total_time;
uint32_t total_num;
uint64_t*file_time,*cmd_time;
int*file_line;
int*cmd_freq;
int cur_depth;
/*:24*//*29:*/
#line 780 "texprofile.w"

bool opt_raw= false;
bool opt_raw_stack= false;
bool opt_raw_num= false;
/*:29*//*35:*/
#line 844 "texprofile.w"

bool opt_stack= false;
/*:35*//*39:*/
#line 883 "texprofile.w"

bool opt_summary= true;
/*:39*//*43:*/
#line 916 "texprofile.w"

bool opt_machine= false;
#define Mprintf(...) opt_machine?(void)0:printf(__VA_ARGS__)
/*:43*//*48:*/
#line 966 "texprofile.w"

bool opt_files= false;
/*:48*//*52:*/
#line 1000 "texprofile.w"

bool opt_cmd= false;
/*:52*//*57:*/
#line 1058 "texprofile.w"

bool opt_macro= false;
/*:57*//*66:*/
#line 1183 "texprofile.w"

int line_num= 0;
/*:66*//*68:*/
#line 1205 "texprofile.w"

static uint64_t*line_time= NULL;
static int*line_freq= NULL;
/*:68*//*70:*/
#line 1242 "texprofile.w"

double percent_limit= 1.0;
bool opt_lines= false;
/*:70*//*75:*/
#line 1309 "texprofile.w"

static uint64_t*tt_time;
static int*tt_file,*tt_line;
static int tt= 10+1,tt_count;;
bool opt_top_ten;
/*:75*//*82:*/
#line 1441 "texprofile.w"

struct edge{
uint16_t child,sibling;
int count,a;
uint64_t T,L,ts,Ts;
}*edges;
int edges_count,edges_num;
/*:82*//*88:*/
#line 1547 "texprofile.w"

bool opt_graph= false;
/*:88*//*106:*/
#line 1797 "texprofile.w"

static char*cmd_name[]= {
"relax",
"left_brace",
"right_brace",
"math_shift",
"tab_mark",
"car_ret/"
"out_param",
"mac_param",
"sup_mark",
"sub_mark",
"ignore/"
"endv",
"spacer",
"letter",
"other_char",
"active/"
"par/"
"match",
"comment/"
"end_match/"
"stop",
"invalid_char/"
"delim_num",

"char_num",
"math_char_num",
"mark",
"xray",
"make_box",
"hmove",
"vmove",
"un_hbox",
"un_vbox",

"remove_item",
"hskip",
"vskip",
"mskip",
"kern",
"mkern",
"leaders/shipout",
"halign",
"valign",
"no_align",
"vrule",
"hrule",
"insert",
"vadjust",
"ignore_spaces",
"after_assignment",
"after_group",
"break_penalty",
"start_par",
"ital_corr",
"accent",
"math_accent",
"discretionary",
"eq_no",
"left_right",
"math_comp",
"limit_switch",
"above",
"math_style",
"math_choice",
"non_script",
"vcenter",
"case_shift",
"message",
"extension",
"in_stream",
"begin_group",
"end_group",
"omit",
"ex_space",
"no_boundary",
"radical",
"end_cs_name",
"min_internal/"
"char_given",
"math_given",
"last_item",

"toks_register",
"assign_toks",
"assign_int",
"assign_dimen",
"assign_glue",
"assign_mu_glue",
"assign_font_dimen",
"assign_font_int",
"set_aux",
"set_prev_graf",
"set_page_dimen",
"set_page_int",
"set_box_dimen",
"set_shape",
"def_code",
"def_family",
"set_font",
"def_font",
"internal_register",
"advance",
"multiply",
"divide",
"prefix",
"let",
"shorthand_def",
"read_to_cs",
"def",
"set_box",
"hyph_data",
"set_interaction",

"system",
"profile on",
"profile off",
"call",
"pop",
"pop n",
"pop 0",
"pop 1",
"pop 2",
"pop 3",
"pop 4",
"pop 5",
"pop 6",
"pop 7",
"pop 8",
"pop 9",
"pop 10",
"unknown"
};

static const int cmd_num= sizeof(cmd_name)/sizeof(*cmd_name);

#define CMD_NAME(N) ((N)<cmd_num?cmd_name[N]:"unknown")

static char*line_name[]= {
"unknown",
"start",
"end",
"shipout",
"linebrk",
"initrie",
"buildpg",
"inputln",
"insert",
};

static char*every_name[]= {
"output",
"everypar",
"everymath",
"everydisplay",
"everyhbox",
"everyvbox",
"everyjob",
"everycr",
"mark",
"everyeof"
};

static const int sys_line_num= sizeof(line_name)/sizeof(*line_name);
/*:106*/
#line 206 "texprofile.w"

/*103:*/
#line 1744 "texprofile.w"

int error(char*msg)
{fprintf(stderr,"texprofile: %s\n",msg);
exit(1);
return 0;
}
/*:103*//*104:*/
#line 1755 "texprofile.w"

int commandline_error(char*msg)
{fprintf(stderr,"texprofile: %s\n",msg);
fprintf(stderr,"Try 'texprofile --help' for more information.\n");
exit(1);
return 0;
}
/*:104*/
#line 207 "texprofile.w"

/*5:*/
#line 270 "texprofile.w"

static uint8_t fget1(void)
{unsigned char buf[1];
if(fread(buf,1,1,in)!=1)
error("Unexpected end of input");
return(uint8_t)buf[0];
}

static uint16_t fget2(void)
{unsigned char buf[2];
if(fread(buf,1,2,in)!=2)
error("Unexpected end of input");
return((uint16_t)buf[0]<<8)+buf[1];
}

static uint32_t fget4(void)
{unsigned char buf[4];
if(fread(buf,1,4,in)!=4)
error("Unexpected end of input");
return((((((uint32_t)buf[0]<<8)+buf[1])<<8)+buf[2])<<8)+buf[3];
}
/*:5*//*15:*/
#line 445 "texprofile.w"

void print_cs(int n)
{if(n<hash_base)
{if(n<single_base)
{int c= n-active_base;
if(c<0)printf("File");
else if(isprint(c))printf("%c",c);else printf("0x%02x",c);
}
else if(n<null_cs)
{int c= n-single_base;
if(isprint(c))printf("\\%c",c);else printf("\\0x%02x",c);
}
else printf("Empty");
}
else if(n>=macro_num+hash_base)
printf("\\%s",every_name[n-hash_base-macro_num-output_text]);
else
printf("\\%s",macro_names[n-hash_base]);
}
/*:15*//*18:*/
#line 513 "texprofile.w"

#define REALLOC(A,C,N) \
  { N= N*1.4142136+0.5; \
    A= realloc(A,N*sizeof(*A));\
    if (A==NULL) error("Out of memory"); \
    memset(A+C,0,(N-C)*sizeof(*A)); \
  }

int new_macro_def(void)
{if(macro_def_count<macro_def_num)
return macro_def_count++;
REALLOC(macro_defs,macro_def_count,macro_def_num);
return macro_def_count++;
}
/*:18*//*19:*/
#line 547 "texprofile.w"

int get_macro_def(int f,int l,int c)
{int m= macro_map[c].m;
if(m==0)
{m= new_macro_def();
macro_map[c].m= m;
}
else
{loop:
if(macro_defs[m].f==f&&macro_defs[m].l==l)
return m;
else if(macro_defs[m].link==0)
{int n= new_macro_def();
macro_defs[m].link= n;
m= n;
}
else
{m= macro_defs[m].link;
goto loop;
}
}
if(c<hash_base)
macro_defs[m].n= c;
else
macro_defs[m].n= hash_base+macro_map[c].n;
macro_defs[m].f= f;
macro_defs[m].l= l;
macro_defs[m].link= 0;
return m;
}
/*:19*//*23:*/
#line 596 "texprofile.w"

void print_macro(int i)
{print_cs(macro_defs[i].n);
if(opt_macro_id)printf(" [%d,%d]",macro_defs[i].f,macro_defs[i].l);
}
/*:23*//*46:*/
#line 930 "texprofile.w"

char*time_str(double t)
{static char str[20];
if(opt_machine)
snprintf(str,20,"%12ld",(long)t);
else
{if(t<1000.0)
snprintf(str,20,"  %7.2f ns",t);
else if(t<1000000.0)
snprintf(str,20,"  %7.2f us",t/1000.0);
else if(t<1000000000.0)
snprintf(str,20,"  %7.2f ms",t/1000000.0);
else
snprintf(str,20,"  %7.2f s",t/1000000000.0);
}
return str;
}
/*:46*//*47:*/
#line 952 "texprofile.w"

void print_fl(int f,int l)
{if(f==system_file&&!opt_machine)
printf("system\t%7s",line_name[l]);
else
printf("%4d\t%5d",f,l);
}
/*:47*//*63:*/
#line 1119 "texprofile.w"

void sort_edges(uint16_t p)
{int i,j,k;
edges[0].sibling= 0;
i= macro_defs[p].e;
while(i!=0)
{uint64_t Ti= edges[i].T;
k= 0;
while((j= edges[k].sibling)!=0)
{uint64_t Tj= edges[j].T;
if(Ti<Tj)
k= j;
else
break;
}
edges[k].sibling= i;
k= i;
i= edges[i].sibling;
edges[k].sibling= j;
}
macro_defs[p].e= edges[0].sibling;
}
/*:63*//*65:*/
#line 1149 "texprofile.w"

void sort_macros(void)
{int i,k,j;
static bool sorted= false;
if(sorted)return;
macro_defs[0].link= 0;
sort_edges(0);
for(i= 1;i<macro_def_count;i++)
{uint64_t Ti= macro_defs[i].T;
k= 0;
while((j= macro_defs[k].link)!=0)
{uint64_t Tj= macro_defs[j].T;
if(Ti<Tj)
k= j;
else
break;
}
macro_defs[i].link= j;
macro_defs[k].link= i;
sort_edges(i);
}
sorted= true;
}
/*:65*//*69:*/
#line 1217 "texprofile.w"

void collect_line_time(void)
{int i,cur_f= -1,cur_l= -1;
if(line_time!=NULL)return;
/*67:*/
#line 1188 "texprofile.w"

line_num= 0;
for(i= 0;i<file_num;i++)
{int fl= file_line[i];
file_line[i]= line_num;
line_num= line_num+fl+1;
}
file_line[file_num]= line_num;
/*:67*/
#line 1222 "texprofile.w"

ALLOCATE(line_time,line_num);
ALLOCATE(line_freq,line_num);
for(i= 0;i<stamp_num;i++)
{/*34:*/
#line 835 "texprofile.w"

uint32_t t= stamps[i].t;
uint16_t l= stamps[i].l;
uint8_t f= stamps[i].f;
uint8_t c= stamps[i].c;
/*:34*/
#line 1226 "texprofile.w"

if(c<=system_profile_off)
{line_time[file_line[f]+l]+= t;
if(cur_f!=f||cur_l!=l)
{line_freq[file_line[f]+l]++;
cur_f= f;cur_l= l;
}
}
}
}
/*:69*//*84:*/
#line 1459 "texprofile.w"

uint16_t new_edge(void)
{if(edges_count<edges_num)
return edges_count++;
REALLOC(edges,edges_count,edges_num);
return edges_count++;
}
/*:84*//*85:*/
#line 1477 "texprofile.w"

void start_child(int p,int c)
{int e= macro_defs[p].e;
if(e==0)
{e= new_edge();
macro_defs[p].e= e;
edges[e].child= c;
goto found;
}
do
{if(edges[e].child==c)
goto found;
else if(edges[e].sibling==0)
{int s= new_edge();
edges[e].sibling= s;
e= s;
edges[e].child= c;
goto found;
}
else
e= edges[e].sibling;
}while(true);
found:
edges[e].a++;
edges[e].count++;
if(edges[e].a==1)
{uint16_t i;
edges[e].ts= total_time;
edges[e].Ts= macro_defs[p].t;
for(i= macro_defs[p].e;i!=0;i= edges[i].sibling)
if(i!=e)
edges[e].Ts+= edges[i].T;
}
}
/*:85*//*86:*/
#line 1517 "texprofile.w"

void end_child(int p,int c)
{uint16_t e= macro_defs[p].e;
while(e!=0)
{if(edges[e].child==c)
goto found;
else
e= edges[e].sibling;
}
found:
if(edges[e].a==1)
{uint16_t i;
uint64_t dt;
uint64_t dT;
dT= macro_defs[p].t;
for(i= macro_defs[p].e;i!=0;i= edges[i].sibling)
if(i!=e)
dT+= edges[i].T;
dt= total_time-edges[e].ts;
dT= dT-edges[e].Ts;
edges[e].L+= dT;
edges[e].T+= dt-dT;
}
edges[e].a--;
}
/*:86*//*96:*/
#line 1681 "texprofile.w"

void explain_usage(void)
{fprintf(stderr,
"Use: "
"texprofile [-options] <input file>\n"
"options:\n"
/*98:*/
#line 1706 "texprofile.w"

"-?        display this help and exit\n"
"--help    display this help and exit\n"
/*:98*//*102:*/
#line 1736 "texprofile.w"

"--version output version information and exit\n"
/*:102*/
#line 1687 "texprofile.w"

"\n"
/*31:*/
#line 792 "texprofile.w"

"-R    show the table of raw time stamps\n"
/*:31*//*37:*/
#line 852 "texprofile.w"

"-S    show the table of macro stack changes\n"
/*:37*//*41:*/
#line 891 "texprofile.w"

"-N    do not show the table of global information\n"
/*:41*//*50:*/
#line 974 "texprofile.w"

"-F    show all files\n"
/*:50*//*54:*/
#line 1008 "texprofile.w"

"-C    show table of command summaries\n"
/*:54*//*59:*/
#line 1066 "texprofile.w"

"-M    show the table of all macros called\n"
/*:59*//*72:*/
#line 1259 "texprofile.w"

"-L    show the table of times per input line\n"
/*:72*//*77:*/
#line 1329 "texprofile.w"

"-T    show the table of the top 10 input lines\n"
/*:77*//*90:*/
#line 1555 "texprofile.w"

"-G    show the table of the  macro call graph\n"
/*:90*//*93:*/
#line 1636 "texprofile.w"

"-A    show all tables (equal to -TGFC) tables\n"
/*:93*/
#line 1689 "texprofile.w"

"\n"
/*22:*/
#line 592 "texprofile.w"

"-i    add the macros file and line numbers after the macro name\n"
/*:22*//*32:*/
#line 794 "texprofile.w"

"-s    show the changes of the macro stack\n"
"-n    show the time stamp numbers\n"
/*:32*//*45:*/
#line 925 "texprofile.w"

"-m    optimize output for machine readability\n"
/*:45*//*73:*/
#line 1261 "texprofile.w"

"-p<n> don't show information for items with cumulative time below <n> percent\n"
/*:73*//*78:*/
#line 1331 "texprofile.w"

"-t<n> replace 10 by n (2<=n<=100, default 10) for the top 10 input lines\n"
/*:78*/
#line 1691 "texprofile.w"

"\n"
);
exit(1);
}
/*:96*//*105:*/
#line 1770 "texprofile.w"

void check_file_marker(char*msg)
{char marker[8];
if(fread(marker,1,8,in)!=8)
error("Unexpected end of input");
if(strncmp(marker,FILE_MARKER,8)!=0)
error(msg);
}
/*:105*/
#line 208 "texprofile.w"


int main(int argc,char*argv[])
{int i,k;
/*95:*/
#line 1656 "texprofile.w"

i= 1;
while(i<argc)
{char*option;
if(argv[i][0]=='-')
{option= argv[i]+1;
while(*option!=0)
{switch(*option)
{/*21:*/
#line 588 "texprofile.w"

case'i':opt_macro_id= true;break;
/*:21*//*30:*/
#line 786 "texprofile.w"

case'R':opt_raw= true;break;
case's':opt_raw_stack= true;break;
case'n':opt_raw_num= true;break;
/*:30*//*36:*/
#line 848 "texprofile.w"

case'S':opt_stack= true;break;
/*:36*//*40:*/
#line 887 "texprofile.w"

case'N':opt_summary= false;break;
/*:40*//*44:*/
#line 921 "texprofile.w"

case'm':opt_machine= true;opt_summary= false;break;
/*:44*//*49:*/
#line 970 "texprofile.w"

case'F':opt_files= true;break;
/*:49*//*53:*/
#line 1004 "texprofile.w"

case'C':opt_cmd= true;break;
/*:53*//*58:*/
#line 1062 "texprofile.w"

case'M':opt_macro= true;break;
/*:58*//*71:*/
#line 1247 "texprofile.w"

case'L':opt_lines= true;break;
case'p':{char*endptr;
percent_limit= strtod(option+1,&endptr);
if(endptr==option+1)
commandline_error("-p<n> without a numeric argument <n>");
else
option= endptr-1;
}
break;
/*:71*//*76:*/
#line 1316 "texprofile.w"

case'T':opt_top_ten= true;break;
case't':{char*endptr;
tt= strtol(option+1,&endptr,10)+1;
if(endptr==option+1)
commandline_error("-t<n> without a numeric argument <n>");
else if(tt<2||tt> 101)
commandline_error("-t<n> with <n> out of bounds");
option= endptr-1;
}
break;
/*:76*//*89:*/
#line 1551 "texprofile.w"

case'G':opt_graph= true;break;
/*:89*//*92:*/
#line 1630 "texprofile.w"

case'A':opt_files= opt_summary= 
opt_cmd= opt_top_ten= 
opt_graph= true;break;
/*:92*//*97:*/
#line 1701 "texprofile.w"

case'h':
case'?':explain_usage();break;
/*:97*//*99:*/
#line 1713 "texprofile.w"

case'-':
option++;
/*100:*/
#line 1721 "texprofile.w"

if(strcmp(option,"help")==0)explain_usage();
/*:100*//*101:*/
#line 1729 "texprofile.w"

if(strcmp(option,"version")==0)
{printf(VERSION_STR"\n");
exit(1);
}
/*:101*/
#line 1716 "texprofile.w"

else commandline_error("unknown long option");
break;
/*:99*/
#line 1664 "texprofile.w"

default:commandline_error("unknown option");
}
option++;
}
}
else if(input_file_name==NULL)
input_file_name= argv[i];
else
commandline_error("multiple input files given");
i++;
}
/*:95*/
#line 212 "texprofile.w"

/*3:*/
#line 234 "texprofile.w"

if(input_file_name==NULL)
commandline_error("no input file given");
in= fopen(input_file_name,"rb");
if(in==NULL)
{char*tmp= malloc(strlen(input_file_name)+7);
if(tmp!=NULL)
{strcpy(tmp,input_file_name);
strcat(tmp,".tprof");
input_file_name= tmp;
in= fopen(input_file_name,"rb");
}
}
if(in==NULL)
error("Unable to open input file");
check_file_marker("The input file does not seem to contain TeX profile data");
/*:3*//*4:*/
#line 255 "texprofile.w"

/*7:*/
#line 305 "texprofile.w"

file_num= fget2();
file_name_num= fget2();
stamp_num= fget4();
if(stamp_num==0)
error("The input file contains no time samples");
macro_num= fget2();
macro_name_num= fget4();
depth_num= fget2();
/*:7*//*8:*/
#line 319 "texprofile.w"

/*10:*/
#line 336 "texprofile.w"

ALLOCATE(full_file_names,file_num);
ALLOCATE(file_names,file_num);
ALLOCATE(file_name_buffer,file_name_num);
/*:10*//*13:*/
#line 391 "texprofile.w"

ALLOCATE(macro_names,macro_num);
ALLOCATE(macro_name_buffer,macro_name_num);
ALLOCATE(macro_map,undefined_control_sequence+every_eof_text+1);
ALLOCATE(macro_stack,depth_num+1);
/*:13*//*17:*/
#line 506 "texprofile.w"

ALLOCATE(stamps,stamp_num);
macro_def_num= 16;
macro_def_count= 1;
ALLOCATE(macro_defs,macro_def_num);
/*:17*//*83:*/
#line 1453 "texprofile.w"

edges_num= 1024;
edges_count= 1;
ALLOCATE(edges,edges_num);
/*:83*/
#line 320 "texprofile.w"

/*:8*/
#line 256 "texprofile.w"

check_file_marker("Invalid size data");
/*11:*/
#line 358 "texprofile.w"

i= k= 0;
while(k<file_num)
{char c;
full_file_names[k]= file_names[k]= file_name_buffer+i;
do{c= fget1();
if(i>=file_name_num)error("File name buffer overflow");
file_name_buffer[i++]= c;
if(c==DIR_SEPARATOR)file_names[k]= file_name_buffer+i;
}while(c!=0);
k++;
}
/*:11*/
#line 258 "texprofile.w"

check_file_marker("Invalid file names");
/*14:*/
#line 398 "texprofile.w"

i= 0;k= 0;
while(k<macro_num)
{int j;
char c;
j= fget2();
macro_map[j].n= k;
macro_map[j].m= 0;
macro_names[k++]= macro_name_buffer+i;
do{c= fget1();
if(i>=macro_name_num)error("Name buffer overflow");
macro_name_buffer[i++]= c;
}while(c!=0);
}
for(i= 1;i<=every_eof_text;i++)
{macro_map[undefined_control_sequence+i].n= macro_num+i;
macro_map[undefined_control_sequence+i].m= 0;
}

/*:14*/
#line 260 "texprofile.w"

check_file_marker("Invalid macro names");
/*26:*/
#line 628 "texprofile.w"

ALLOCATE(file_time,file_num);
ALLOCATE(cmd_time,cmd_num);
ALLOCATE(file_line,file_num+1);
ALLOCATE(cmd_freq,cmd_num);


cur_depth= -1;
total_time= 0;
total_num= 0;
macro_defs[0].a= 1;
i= 0;
{fget1();
/*28:*/
#line 743 "texprofile.w"

int f,l,n,m;
f= fget1();
l= fget2();
n= fget2();
m= get_macro_def(f,l,n);
stamps[i].c= system_macro_push;
stamps[i].f= f;
stamps[i].l= l;
stamps[i].d= cur_depth;
stamps[i].m= m;
#ifdef DEBUG
printf("[%d:%d<%d:",i,cur_depth,cur_depth+1);
print_macro(m);
printf("]\n");
#endif
#line 759 "texprofile.w"
 i++;
/*:28*/
#line 641 "texprofile.w"

/*60:*/
#line 1073 "texprofile.w"

cur_depth++;
macro_stack[cur_depth]= m;
macro_defs[m].count++;
macro_defs[m].a++;
if(macro_defs[m].a==1)
{macro_defs[m].s= total_time;
}
/*:60*/
#line 642 "texprofile.w"

}
while(i<stamp_num)
{uint8_t c= fget1();
switch(c)
{case system_macro_pop_0:break;
case system_macro_pop_0+1:
case system_macro_pop_0+2:
case system_macro_pop_0+3:
case system_macro_pop_0+4:
case system_macro_pop_0+5:
case system_macro_pop_0+6:
case system_macro_pop_0+7:
case system_macro_pop_0+8:
case system_macro_pop_0+9:
case system_macro_pop_0+10:
{int d= c-system_macro_pop_0;
/*27:*/
#line 732 "texprofile.w"

stamps[i].c= system_macro_pop;
stamps[i].d= cur_depth-d;
#ifdef DEBUG
printf("{%d:%d:%d>%d}\n",i,system_macro_pop,cur_depth+d,cur_depth);
#endif
#line 738 "texprofile.w"
/*61:*/
#line 1085 "texprofile.w"

while(cur_depth> stamps[i].d)
{int m= macro_stack[cur_depth];
if(macro_defs[m].a==1)
macro_defs[m].T+= total_time-macro_defs[m].s;
end_child(macro_stack[cur_depth-1],m);
macro_defs[m].a--;
cur_depth--;
}

/*:61*/
#line 738 "texprofile.w"

i++;
/*:27*/
#line 659 "texprofile.w"

break;
}
case system_macro_pop_small:
{int d= fget1();
/*27:*/
#line 732 "texprofile.w"

stamps[i].c= system_macro_pop;
stamps[i].d= cur_depth-d;
#ifdef DEBUG
printf("{%d:%d:%d>%d}\n",i,system_macro_pop,cur_depth+d,cur_depth);
#endif
#line 738 "texprofile.w"
/*61:*/
#line 1085 "texprofile.w"

while(cur_depth> stamps[i].d)
{int m= macro_stack[cur_depth];
if(macro_defs[m].a==1)
macro_defs[m].T+= total_time-macro_defs[m].s;
end_child(macro_stack[cur_depth-1],m);
macro_defs[m].a--;
cur_depth--;
}

/*:61*/
#line 738 "texprofile.w"

i++;
/*:27*/
#line 664 "texprofile.w"

break;
}
case system_macro_pop:
{int d= fget2();
/*27:*/
#line 732 "texprofile.w"

stamps[i].c= system_macro_pop;
stamps[i].d= cur_depth-d;
#ifdef DEBUG
printf("{%d:%d:%d>%d}\n",i,system_macro_pop,cur_depth+d,cur_depth);
#endif
#line 738 "texprofile.w"
/*61:*/
#line 1085 "texprofile.w"

while(cur_depth> stamps[i].d)
{int m= macro_stack[cur_depth];
if(macro_defs[m].a==1)
macro_defs[m].T+= total_time-macro_defs[m].s;
end_child(macro_stack[cur_depth-1],m);
macro_defs[m].a--;
cur_depth--;
}

/*:61*/
#line 738 "texprofile.w"

i++;
/*:27*/
#line 669 "texprofile.w"

break;
}
case system_macro_push:
{/*28:*/
#line 743 "texprofile.w"

int f,l,n,m;
f= fget1();
l= fget2();
n= fget2();
m= get_macro_def(f,l,n);
stamps[i].c= system_macro_push;
stamps[i].f= f;
stamps[i].l= l;
stamps[i].d= cur_depth;
stamps[i].m= m;
#ifdef DEBUG
printf("[%d:%d<%d:",i,cur_depth,cur_depth+1);
print_macro(m);
printf("]\n");
#endif
#line 759 "texprofile.w"
 i++;
/*:28*/
#line 673 "texprofile.w"

cur_depth++;
macro_stack[cur_depth]= m;
macro_defs[m].count++;
macro_defs[m].a++;
if(macro_defs[m].a==1)
{macro_defs[m].s= total_time;
}
start_child(macro_stack[cur_depth-1],m);
}
break;
default:
if(c&POP_BIT)
{int d= 1;
/*27:*/
#line 732 "texprofile.w"

stamps[i].c= system_macro_pop;
stamps[i].d= cur_depth-d;
#ifdef DEBUG
printf("{%d:%d:%d>%d}\n",i,system_macro_pop,cur_depth+d,cur_depth);
#endif
#line 738 "texprofile.w"
/*61:*/
#line 1085 "texprofile.w"

while(cur_depth> stamps[i].d)
{int m= macro_stack[cur_depth];
if(macro_defs[m].a==1)
macro_defs[m].T+= total_time-macro_defs[m].s;
end_child(macro_stack[cur_depth-1],m);
macro_defs[m].a--;
cur_depth--;
}

/*:61*/
#line 738 "texprofile.w"

i++;
/*:27*/
#line 687 "texprofile.w"

c= c&~POP_BIT;
}
{uint8_t f= fget1();
uint16_t l= fget2();
uint32_t t= fget4();
uint16_t m= macro_stack[cur_depth];
if(f>=file_num)error("File number out of range");
if(c>=cmd_num)error("Command number out of range");
stamps[i].c= c;
stamps[i].f= f;
if(l> file_line[f])
file_line[f]= l;
stamps[i].l= l;
stamps[i].t= t;
total_time+= t;
file_time[f]+= t;
macro_defs[m].t+= t;
cmd_time[c]+= t;
cmd_freq[c]++;
total_num++;
stamps[i].d= cur_depth;
stamps[i].m= m;
}
i++;
#ifdef DEBUG
printf("<%d:%d:%d> %s\n",i-1,c,cur_depth,cmd_name[c]);
#endif
#line 715 "texprofile.w"
 break;
}
}
macro_defs[macro_stack[0]].T= total_time;
macro_defs[0].count= 0;
macro_defs[0].T= 0;
macro_defs[0].f= 0;
macro_defs[0].l= 0;


#ifdef DEBUG
printf("Finished reading %d commands, depth=%d\n",i,cur_depth);
#endif
#line 728 "texprofile.w"
/*:26*/
#line 262 "texprofile.w"

check_file_marker("Invalid timing data");
fclose(in);
/*:4*/
#line 213 "texprofile.w"

/*94:*/
#line 1640 "texprofile.w"

/*33:*/
#line 805 "texprofile.w"

if(opt_raw)
{Mprintf("\nAll time stamps in order of appearance:\n");
if(opt_raw_num)Mprintf("number\t");
Mprintf("file\t line\ttime/ns\tcommand\t                level\tmacro\n");
for(i= 1;i<stamp_num;i++)
{int m= stamps[i].m;
/*34:*/
#line 835 "texprofile.w"

uint32_t t= stamps[i].t;
uint16_t l= stamps[i].l;
uint8_t f= stamps[i].f;
uint8_t c= stamps[i].c;
/*:34*/
#line 812 "texprofile.w"

if(c<=system_profile_off)
{if(opt_raw_num)printf("%6d\t",i);
print_fl(f,l);
printf("\t%7u\t%-23s\t%5d\t",t,CMD_NAME(c),stamps[i].d);
print_macro(m);
printf("\n");
}
else if(opt_raw_stack)
{if(opt_raw_num)printf("%6d\t",i);
printf("\t\t\t%-23s\t%5d\t",CMD_NAME(c),stamps[i].d);
if(c==system_macro_push)
print_macro(m);
printf("\n");
}
}
}
/*:33*/
#line 1641 "texprofile.w"

/*38:*/
#line 856 "texprofile.w"

if(opt_stack)
{int c,d,m;
Mprintf("\nThe macro stack and its nesting:\n"
"command\tdepth\tname [id]\n");
for(i= 0;i<stamp_num;i++)
{c= stamps[i].c;
if(c<system_macro_push)
continue;
d= stamps[i].d;
m= stamps[i].m;
printf("%5d\t%s\t",d,CMD_NAME(c));
if(c==system_macro_push)
print_macro(m);
printf("\n");
}
}
/*:38*/
#line 1642 "texprofile.w"

/*55:*/
#line 1013 "texprofile.w"

if(opt_cmd)
{int*cmd_link= NULL;
/*56:*/
#line 1039 "texprofile.w"

ALLOCATE(cmd_link,cmd_num+1);
cmd_link[cmd_num]= -1;
for(i= 0;i<cmd_num;i++)
{int l= cmd_num;
uint32_t t= cmd_time[i];
while(cmd_link[l]>=0&&cmd_time[cmd_link[l]]> t)
l= cmd_link[l];
cmd_link[i]= cmd_link[l];
cmd_link[l]= i;
}
/*:56*/
#line 1016 "texprofile.w"

Mprintf("\nCommand summary:\n");
Mprintf(" cmd\t        time\t time%%\t  freq\t      average\tname\n");
for(i= cmd_link[cmd_num];i>=0;i= cmd_link[i])
if(cmd_freq[i]> 0)
{printf("%4d\t%s\t%5.2f%%",
i,time_str(cmd_time[i]),
(100.0*cmd_time[i])/total_time);
printf("\t%6d\t %s\t%s\n",
cmd_freq[i],time_str(cmd_time[i]/cmd_freq[i]),
CMD_NAME(i));
}
free(cmd_link);
}
/*:55*/
#line 1643 "texprofile.w"

/*51:*/
#line 981 "texprofile.w"

if(opt_files)
{Mprintf("\nFiles in the order of appearance:\n");
Mprintf("  file\t lines\tpercent\t     absolute"
"\tname\n");
for(i= 0;i<file_num;i++)
{double p= (100.0*file_time[i])/total_time;
if(p>=percent_limit)
printf("%6d\t%6d\t%6.2f%%\t%s\t%s\n",
i,file_line[i],
p,time_str(file_time[i]),
full_file_names[i]);
}
}
/*:51*/
#line 1644 "texprofile.w"

/*74:*/
#line 1266 "texprofile.w"

if(opt_lines)
{uint64_t limit= total_time*percent_limit/100.0;
int k;
collect_line_time();
Mprintf("\nLine summary:\n");
if(percent_limit> 0)
Mprintf("Only files and lines above %.2f%%:\n",percent_limit);
for(k= i= 0;i<file_num;i++)
{if(file_time[i]<=limit)
k= file_line[i+1];
else
{printf("%s\n",file_names[i]);
printf("  file\t  line\tpercent\t     absolute"
"\t count\t     average\n");
printf("%6d\t\t%6.2f%%\t%s\n",
i,(100.0*file_time[i])/total_time,time_str(file_time[i]));

for(;k<file_line[i+1];k++)
{uint64_t t= line_time[k];
if(line_freq[k]> 0&&t>=limit)
{if(i==system_file)
printf("\t%7s",line_name[k-file_line[i]]);
else
printf("\t%6d",k-file_line[i]);
printf("\t%6.2f%%\t%s",
100.0*t/total_time,time_str(t));
printf("\t%6d\t%s",line_freq[k],time_str(t/line_freq[k]));
printf("\n");
}
}
printf("\n");
}
}
}
/*:74*/
#line 1645 "texprofile.w"

/*81:*/
#line 1376 "texprofile.w"

if(opt_top_ten)
{collect_line_time();
/*79:*/
#line 1336 "texprofile.w"

ALLOCATE(tt_time,tt);
ALLOCATE(tt_file,tt);
ALLOCATE(tt_line,tt);
tt_time[0]= 0xFFFFFFFFFFFFFFFF;
tt_file[0]= 0;
tt_line[0]= 0;
tt_time[1]= 0;
tt_file[1]= 0;
tt_line[1]= 0;
tt_count= 2;
{int f,l;
for(f= l= 0;f<file_num;f++)
{for(;l<file_line[f+1];l++)
{uint32_t t= line_time[l];
if(t> tt_time[tt_count-1])
/*80:*/
#line 1360 "texprofile.w"

{
if(tt_count<tt)tt_count++;
i= tt_count-1;
while(tt_time[i-1]<t)
{i--;
tt_time[i+1]= tt_time[i];
tt_file[i+1]= tt_file[i];
tt_line[i+1]= tt_line[i];
}
tt_time[i]= t;
tt_file[i]= f;
tt_line[i]= l-file_line[f];
}
/*:80*/
#line 1352 "texprofile.w"

}
}
}
/*:79*/
#line 1379 "texprofile.w"

Mprintf("\nThe top ten lines:\n");
Mprintf("  file\t  line\tpercent\t     absolute"
"\t count\t     average\tfile\n");
for(i= 1;i<tt_count;i++)
{int freq= line_freq[tt_line[i]+file_line[tt_file[i]]];
uint32_t t= tt_time[i];
if(t> 0&&freq> 0)
{print_fl(tt_file[i],tt_line[i]);
printf("\t%6.2f%%\t%s",100.0*t/total_time,time_str(t));
printf("\t%6d\t%s\t%s\n",freq,time_str(t/freq),file_names[tt_file[i]]);
}
}
}
/*:81*/
#line 1646 "texprofile.w"

/*62:*/
#line 1097 "texprofile.w"

if(opt_macro)
{sort_macros();
Mprintf("\nMacros profiled:\n");
Mprintf(" file\t line\tcalls\t time direct\t  cumulative\tname\n");
i= 0;
do
{printf("%5d\t%5d\t",macro_defs[i].f,macro_defs[i].l);
printf("%5d\t%s",macro_defs[i].count,time_str(macro_defs[i].t));
printf("\t%s\t",time_str(macro_defs[i].T));
print_macro(i);
printf("\n");
i= macro_defs[i].link;
}while(i!=0);
}
/*:62*/
#line 1647 "texprofile.w"

/*91:*/
#line 1559 "texprofile.w"

if(opt_graph)
{sort_macros();
Mprintf("\nThe macro call graph:\n"
"        time\t        loop\tpercent\t count/total\tchild\n");
i= macro_defs[0].link;
do
{int e;
uint64_t Ti= macro_defs[i].T;
if(100.0*Ti/total_time<percent_limit)
break;
print_macro(i);
printf("\n");
printf("%s\t        \t%6.2f%%\t",
time_str(Ti),100.0*Ti/total_time);
if(opt_machine)
printf("\t%6d\t",macro_defs[i].count);
else
printf("      *      \t");
print_macro(i);
printf("\n");
printf("%s\t        \t",time_str(macro_defs[i].t));
if(Ti!=0)
printf("%6.2f%%\t",100.0*macro_defs[i].t/Ti);
else
printf("\t");
if(opt_machine)
printf("%6d\t\t",macro_defs[i].count);
else
printf("%7d      \t",macro_defs[i].count);
print_macro(i);
printf("\n");
e= macro_defs[i].e;
while(e!=0)
{int c= edges[e].child;
int n= edges[e].count;
int m= macro_defs[c].count;
uint64_t Te= edges[e].T;
int64_t L= edges[e].L;
double p= 100.0*Te/Ti;
if(p>=percent_limit)
{printf("%s\t",time_str(Te));
if(L==0&&!opt_machine)
printf("        \t");
else
printf("%s\t",time_str(L));
if(Ti!=0)
printf("%6.2f%%\t",p);
else
printf("\t");
if(opt_machine)
printf("%6d\t%6d\t",n,m);
else
printf("%6d/%-6d\t",n,m);
print_macro(c);
printf("\n");
}
e= edges[e].sibling;
}
printf("\n");
i= macro_defs[i].link;
}while(i!=0);
}
/*:91*/
#line 1648 "texprofile.w"

/*42:*/
#line 896 "texprofile.w"

if(opt_summary)
{printf("\n"
"Total time measured:       %s\n",time_str(total_time));
printf("Total number of samples:      %6d\n",total_num);
if(total_num> 0)
printf("Average time per sample:   %s\n",time_str(total_time/total_num));
printf("Total number of files:         %5d\n",file_num);
printf("Total number of macros:        %5d\n",macro_num);
printf("Maximum stack nesting depth:   %5d\n",depth_num);
}
/*:42*/
#line 1649 "texprofile.w"

/*:94*/
#line 214 "texprofile.w"

return 0;
}
/*:1*/
