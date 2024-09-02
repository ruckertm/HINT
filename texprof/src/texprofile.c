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

#define max_command 100 \

#define system_cmd (max_command+1) 
#define system_profile_on (system_cmd+1) 
#define system_profile_off (system_cmd+2) 
#define system_macro_push (system_cmd+3) 
#define system_macro_pop (system_cmd+4) 
#define system_macro_pop_small (system_cmd+5) 
#define system_macro_pop_0 (system_cmd+6)  \

/*1:*/
#line 201 "texprofile.w"
#include<stdlib.h> 
#include <stdio.h> 
#include <stdint.h> 
#include <stdbool.h> 
#include <ctype.h> 
#include <string.h> 
/*2:*/
#line 223 "texprofile.w"

static char*input_file_name= NULL;
static FILE*in= NULL;
/*:2*//*6:*/
#line 297 "texprofile.w"

static unsigned int file_num,
file_name_num,
macro_num,
macro_name_num,
stamp_num,
depth_num;
/*:6*//*9:*/
#line 331 "texprofile.w"

static char**full_file_names,**file_names,*file_name_buffer;
#define ALLOCATE(V,S) V =  calloc(S,sizeof(*V));\
                      if (V==NULL) error("Out of memory for " #V "[" #S "]");
/*:9*//*12:*/
#line 383 "texprofile.w"

static char*macro_name_buffer,**macro_names;
static uint16_t*macro_stack;
static struct map
{uint16_t n;
uint16_t m;
}*macro_map;
/*:12*//*16:*/
#line 474 "texprofile.w"

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
#line 585 "texprofile.w"

bool opt_macro_id= false;
/*:20*//*24:*/
#line 616 "texprofile.w"

uint64_t total_time;
uint32_t total_num;
uint64_t*file_time,*cmd_time;
int*file_line;
int*cmd_freq;
int cur_depth;
/*:24*//*30:*/
#line 779 "texprofile.w"

bool opt_raw= false;
bool opt_raw_stack= false;
bool opt_raw_num= false;
/*:30*//*36:*/
#line 843 "texprofile.w"

bool opt_stack= false;
/*:36*//*40:*/
#line 882 "texprofile.w"

bool opt_summary= true;
/*:40*//*44:*/
#line 915 "texprofile.w"

bool opt_machine= false;
#define Mprintf(...) opt_machine?(void)0:printf(__VA_ARGS__)
/*:44*//*49:*/
#line 965 "texprofile.w"

bool opt_files= false;
/*:49*//*53:*/
#line 999 "texprofile.w"

bool opt_cmd= false;
/*:53*//*58:*/
#line 1057 "texprofile.w"

bool opt_macro= false;
/*:58*//*67:*/
#line 1182 "texprofile.w"

int line_num= 0;
/*:67*//*69:*/
#line 1204 "texprofile.w"

static uint64_t*line_time= NULL;
static int*line_freq= NULL;
/*:69*//*71:*/
#line 1241 "texprofile.w"

double percent_limit= 1.0;
bool opt_lines= false;
/*:71*//*76:*/
#line 1308 "texprofile.w"

static uint64_t*tt_time;
static int*tt_file,*tt_line;
static int tt= 10+1,tt_count;;
bool opt_top_ten;
/*:76*//*83:*/
#line 1440 "texprofile.w"

struct edge{
uint16_t child,sibling;
int count,a;
uint64_t T,L,ts,Ts;
}*edges;
int edges_count,edges_num;
/*:83*//*89:*/
#line 1546 "texprofile.w"

bool opt_graph= false;
/*:89*//*101:*/
#line 1743 "texprofile.w"

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
/*:101*/
#line 207 "texprofile.w"

/*98:*/
#line 1694 "texprofile.w"

int error(char*msg)
{fprintf(stderr,"ERROR: %s\n",msg);
exit(1);
return 0;
}
/*:98*/
#line 208 "texprofile.w"

/*5:*/
#line 271 "texprofile.w"

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
#line 446 "texprofile.w"

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
#line 514 "texprofile.w"

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
#line 548 "texprofile.w"

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
#line 597 "texprofile.w"

void print_macro(int i)
{print_cs(macro_defs[i].n);
if(opt_macro_id)printf(" [%d,%d]",macro_defs[i].f,macro_defs[i].l);
}
/*:23*//*47:*/
#line 929 "texprofile.w"

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
/*:47*//*48:*/
#line 951 "texprofile.w"

void print_fl(int f,int l)
{if(f==system_file&&!opt_machine)
printf("system\t%7s",line_name[l]);
else
printf("%4d\t%5d",f,l);
}
/*:48*//*64:*/
#line 1118 "texprofile.w"

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
/*:64*//*66:*/
#line 1148 "texprofile.w"

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
/*:66*//*70:*/
#line 1216 "texprofile.w"

void collect_line_time(void)
{int i,cur_f= -1,cur_l= -1;
if(line_time!=NULL)return;
/*68:*/
#line 1187 "texprofile.w"

line_num= 0;
for(i= 0;i<file_num;i++)
{int fl= file_line[i];
file_line[i]= line_num;
line_num= line_num+fl+1;
}
file_line[file_num]= line_num;
/*:68*/
#line 1221 "texprofile.w"

ALLOCATE(line_time,line_num);
ALLOCATE(line_freq,line_num);
for(i= 0;i<stamp_num;i++)
{/*35:*/
#line 834 "texprofile.w"

uint32_t t= stamps[i].t;
uint16_t l= stamps[i].l;
uint8_t f= stamps[i].f;
uint8_t c= stamps[i].c;
/*:35*/
#line 1225 "texprofile.w"

if(c<=system_profile_off)
{line_time[file_line[f]+l]+= t;
if(cur_f!=f||cur_l!=l)
{line_freq[file_line[f]+l]++;
cur_f= f;cur_l= l;
}
}
}
}
/*:70*//*85:*/
#line 1458 "texprofile.w"

uint16_t new_edge(void)
{if(edges_count<edges_num)
return edges_count++;
REALLOC(edges,edges_count,edges_num);
return edges_count++;
}
/*:85*//*86:*/
#line 1476 "texprofile.w"

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
/*:86*//*87:*/
#line 1516 "texprofile.w"

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
/*:87*//*99:*/
#line 1704 "texprofile.w"

void explain_usage(char*msg)
{fprintf(stderr,"ERROR: %s\n",msg);
fprintf(stderr,/*96:*/
#line 1656 "texprofile.w"

"Use: "
"texprofile [-options] <input file>\n"
"options:\n"
/*32:*/
#line 791 "texprofile.w"

"-R    show the table of raw time stamps\n"
/*:32*//*38:*/
#line 851 "texprofile.w"

"-S    show the table of macro stack changes\n"
/*:38*//*42:*/
#line 890 "texprofile.w"

"-N    do not show the table of global information\n"
/*:42*//*51:*/
#line 973 "texprofile.w"

"-F    show all files\n"
/*:51*//*55:*/
#line 1007 "texprofile.w"

"-C    show table of command summaries\n"
/*:55*//*60:*/
#line 1065 "texprofile.w"

"-M    show the table of all macros called\n"
/*:60*//*73:*/
#line 1258 "texprofile.w"

"-L    show the table of times per input line\n"
/*:73*//*78:*/
#line 1328 "texprofile.w"

"-T    show the table of the top 10 input lines\n"
/*:78*//*91:*/
#line 1554 "texprofile.w"

"-G    show the table of the  macro call graph\n"
/*:91*//*94:*/
#line 1635 "texprofile.w"

"-A    show all tables (equal to -TGFC) tables\n"
/*:94*/
#line 1660 "texprofile.w"

"\n"
/*22:*/
#line 593 "texprofile.w"

"-i    add the macros file and line numbers after the macro name\n"
/*:22*//*33:*/
#line 793 "texprofile.w"

"-s    show the changes of the macro stack\n"
"-n    show the time stamp numbers\n"
/*:33*//*46:*/
#line 924 "texprofile.w"

"-m    optimize output for machine readability\n"
/*:46*//*74:*/
#line 1260 "texprofile.w"

"-p<n> don't show information for items with cumulative time below <n> percent\n"
/*:74*//*79:*/
#line 1330 "texprofile.w"

"-t<n> replace 10 by n (2<=n<=100, default 10) for the top 10 input lines\n"
/*:79*/
#line 1662 "texprofile.w"

/*:96*/
#line 1707 "texprofile.w"
);
exit(1);
}
/*:99*//*100:*/
#line 1716 "texprofile.w"

void check_file_marker(char*msg)
{char marker[8];
if(fread(marker,1,8,in)!=8)
error("Unexpected end of input");
if(strncmp(marker,FILE_MARKER,8)!=0)
error(msg);
}
/*:100*/
#line 209 "texprofile.w"


int main(int argc,char*argv[])
{int i,k;
/*97:*/
#line 1665 "texprofile.w"

i= 1;
while(i<argc)
{char*option;
if(argv[i][0]=='-')
{option= argv[i]+1;
while(*option!=0)
{switch(*option)
{/*21:*/
#line 589 "texprofile.w"

case'i':opt_macro_id= true;break;
/*:21*//*31:*/
#line 785 "texprofile.w"

case'R':opt_raw= true;break;
case's':opt_raw_stack= true;break;
case'n':opt_raw_num= true;break;
/*:31*//*37:*/
#line 847 "texprofile.w"

case'S':opt_stack= true;break;
/*:37*//*41:*/
#line 886 "texprofile.w"

case'N':opt_summary= false;break;
/*:41*//*45:*/
#line 920 "texprofile.w"

case'm':opt_machine= true;opt_summary= false;break;
/*:45*//*50:*/
#line 969 "texprofile.w"

case'F':opt_files= true;break;
/*:50*//*54:*/
#line 1003 "texprofile.w"

case'C':opt_cmd= true;break;
/*:54*//*59:*/
#line 1061 "texprofile.w"

case'M':opt_macro= true;break;
/*:59*//*72:*/
#line 1246 "texprofile.w"

case'L':opt_lines= true;break;
case'p':{char*endptr;
percent_limit= strtod(option+1,&endptr);
if(endptr==option+1)
explain_usage("-pMM<n> without a numeric argument <n>");
else
option= endptr-1;
}
break;
/*:72*//*77:*/
#line 1315 "texprofile.w"

case'T':opt_top_ten= true;break;
case't':{char*endptr;
tt= strtol(option+1,&endptr,10)+1;
if(endptr==option+1)
explain_usage("-t<n> without a numeric argument <n>");
else if(tt<2||tt> 101)
explain_usage("-t<n> with n out of bounds");
option= endptr-1;
}
break;
/*:77*//*90:*/
#line 1550 "texprofile.w"

case'G':opt_graph= true;break;
/*:90*//*93:*/
#line 1629 "texprofile.w"

case'A':opt_files= opt_summary= 
opt_cmd= opt_top_ten= 
opt_graph= true;break;
/*:93*/
#line 1673 "texprofile.w"

default:explain_usage("unknown option");
}
option++;
}
}
else if(input_file_name==NULL)
input_file_name= argv[i];
else
explain_usage("multiple input files given");
i++;
}
/*:97*/
#line 213 "texprofile.w"

/*3:*/
#line 235 "texprofile.w"

if(input_file_name==NULL)
explain_usage("no input file given");
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
#line 256 "texprofile.w"

/*7:*/
#line 306 "texprofile.w"

file_num= fget2();
file_name_num= fget2();
stamp_num= fget4();
if(stamp_num==0)
error("The input file contains no time samples");
macro_num= fget2();
macro_name_num= fget4();
depth_num= fget2();
/*:7*//*8:*/
#line 320 "texprofile.w"

/*10:*/
#line 337 "texprofile.w"

ALLOCATE(full_file_names,file_num);
ALLOCATE(file_names,file_num);
ALLOCATE(file_name_buffer,file_name_num);
/*:10*//*13:*/
#line 392 "texprofile.w"

ALLOCATE(macro_names,macro_num);
ALLOCATE(macro_name_buffer,macro_name_num);
ALLOCATE(macro_map,undefined_control_sequence+every_eof_text+1);
ALLOCATE(macro_stack,depth_num+1);
/*:13*//*17:*/
#line 507 "texprofile.w"

ALLOCATE(stamps,stamp_num);
macro_def_num= 16;
macro_def_count= 1;
ALLOCATE(macro_defs,macro_def_num);
/*:17*//*84:*/
#line 1452 "texprofile.w"

edges_num= 1024;
edges_count= 1;
ALLOCATE(edges,edges_num);
/*:84*/
#line 321 "texprofile.w"

/*:8*/
#line 257 "texprofile.w"

check_file_marker("Invalid size data");
/*11:*/
#line 359 "texprofile.w"

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
#line 259 "texprofile.w"

check_file_marker("Invalid file names");
/*14:*/
#line 399 "texprofile.w"

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
#line 261 "texprofile.w"

check_file_marker("Invalid macro names");
/*26:*/
#line 627 "texprofile.w"

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
/*29:*/
#line 743 "texprofile.w"

int f= fget1();
int l= fget2();
int n= fget2();
int m= get_macro_def(f,l,n);
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
#line 758 "texprofile.w"
 i++;
/*:29*/
#line 640 "texprofile.w"

/*61:*/
#line 1072 "texprofile.w"

cur_depth++;
macro_stack[cur_depth]= m;
macro_defs[m].count++;
macro_defs[m].a++;
if(macro_defs[m].a==1)
{macro_defs[m].s= total_time;
}
/*:61*/
#line 641 "texprofile.w"

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
/*28:*/
#line 732 "texprofile.w"

stamps[i].c= system_macro_pop;
stamps[i].d= cur_depth-d;
#ifdef DEBUG
printf("{%d:%d:%d>%d}\n",i,system_macro_pop,cur_depth+d,cur_depth);
#endif
#line 738 "texprofile.w"
/*62:*/
#line 1084 "texprofile.w"

while(cur_depth> stamps[i].d)
{int m= macro_stack[cur_depth];
if(macro_defs[m].a==1)
macro_defs[m].T+= total_time-macro_defs[m].s;
end_child(macro_stack[cur_depth-1],m);
macro_defs[m].a--;
cur_depth--;
}

/*:62*/
#line 738 "texprofile.w"

i++;
/*:28*/
#line 658 "texprofile.w"

break;
}
case system_macro_pop_small:
{int d= fget1();
/*28:*/
#line 732 "texprofile.w"

stamps[i].c= system_macro_pop;
stamps[i].d= cur_depth-d;
#ifdef DEBUG
printf("{%d:%d:%d>%d}\n",i,system_macro_pop,cur_depth+d,cur_depth);
#endif
#line 738 "texprofile.w"
/*62:*/
#line 1084 "texprofile.w"

while(cur_depth> stamps[i].d)
{int m= macro_stack[cur_depth];
if(macro_defs[m].a==1)
macro_defs[m].T+= total_time-macro_defs[m].s;
end_child(macro_stack[cur_depth-1],m);
macro_defs[m].a--;
cur_depth--;
}

/*:62*/
#line 738 "texprofile.w"

i++;
/*:28*/
#line 663 "texprofile.w"

break;
}
case system_macro_pop:
{int d= fget2();
/*28:*/
#line 732 "texprofile.w"

stamps[i].c= system_macro_pop;
stamps[i].d= cur_depth-d;
#ifdef DEBUG
printf("{%d:%d:%d>%d}\n",i,system_macro_pop,cur_depth+d,cur_depth);
#endif
#line 738 "texprofile.w"
/*62:*/
#line 1084 "texprofile.w"

while(cur_depth> stamps[i].d)
{int m= macro_stack[cur_depth];
if(macro_defs[m].a==1)
macro_defs[m].T+= total_time-macro_defs[m].s;
end_child(macro_stack[cur_depth-1],m);
macro_defs[m].a--;
cur_depth--;
}

/*:62*/
#line 738 "texprofile.w"

i++;
/*:28*/
#line 668 "texprofile.w"

break;
}
case system_macro_push:
{/*29:*/
#line 743 "texprofile.w"

int f= fget1();
int l= fget2();
int n= fget2();
int m= get_macro_def(f,l,n);
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
#line 758 "texprofile.w"
 i++;
/*:29*/
#line 672 "texprofile.w"

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
/*28:*/
#line 732 "texprofile.w"

stamps[i].c= system_macro_pop;
stamps[i].d= cur_depth-d;
#ifdef DEBUG
printf("{%d:%d:%d>%d}\n",i,system_macro_pop,cur_depth+d,cur_depth);
#endif
#line 738 "texprofile.w"
/*62:*/
#line 1084 "texprofile.w"

while(cur_depth> stamps[i].d)
{int m= macro_stack[cur_depth];
if(macro_defs[m].a==1)
macro_defs[m].T+= total_time-macro_defs[m].s;
end_child(macro_stack[cur_depth-1],m);
macro_defs[m].a--;
cur_depth--;
}

/*:62*/
#line 738 "texprofile.w"

i++;
/*:28*/
#line 686 "texprofile.w"

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
#line 714 "texprofile.w"
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
#line 727 "texprofile.w"
/*:26*/
#line 263 "texprofile.w"

check_file_marker("Invalid timing data");
fclose(in);
/*:4*/
#line 214 "texprofile.w"

/*95:*/
#line 1639 "texprofile.w"

/*34:*/
#line 804 "texprofile.w"

if(opt_raw)
{Mprintf("\nAll time stamps in order of appearance:\n");
if(opt_raw_num)Mprintf("number\t");
Mprintf("file\t line\ttime/ns\tcommand\t                level\tmacro\n");
for(i= 1;i<stamp_num;i++)
{int m= stamps[i].m;
/*35:*/
#line 834 "texprofile.w"

uint32_t t= stamps[i].t;
uint16_t l= stamps[i].l;
uint8_t f= stamps[i].f;
uint8_t c= stamps[i].c;
/*:35*/
#line 811 "texprofile.w"

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
/*:34*/
#line 1640 "texprofile.w"

/*39:*/
#line 855 "texprofile.w"

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
/*:39*/
#line 1641 "texprofile.w"

/*56:*/
#line 1012 "texprofile.w"

if(opt_cmd)
{int*cmd_link= NULL;
/*57:*/
#line 1038 "texprofile.w"

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
/*:57*/
#line 1015 "texprofile.w"

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
/*:56*/
#line 1642 "texprofile.w"

/*52:*/
#line 980 "texprofile.w"

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
/*:52*/
#line 1643 "texprofile.w"

/*75:*/
#line 1265 "texprofile.w"

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
/*:75*/
#line 1644 "texprofile.w"

/*82:*/
#line 1375 "texprofile.w"

if(opt_top_ten)
{collect_line_time();
/*80:*/
#line 1335 "texprofile.w"

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
/*81:*/
#line 1359 "texprofile.w"

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
/*:81*/
#line 1351 "texprofile.w"

}
}
}
/*:80*/
#line 1378 "texprofile.w"

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
/*:82*/
#line 1645 "texprofile.w"

/*63:*/
#line 1096 "texprofile.w"

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
/*:63*/
#line 1646 "texprofile.w"

/*92:*/
#line 1558 "texprofile.w"

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
/*:92*/
#line 1647 "texprofile.w"

/*43:*/
#line 895 "texprofile.w"

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
/*:43*/
#line 1648 "texprofile.w"

/*:95*/
#line 215 "texprofile.w"

return 0;
}
/*:1*/
