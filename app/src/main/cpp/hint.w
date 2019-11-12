% This file is part of HINT
% Copyright 2017 Martin Ruckert
% 
% HINT is free software: you can redistribute it and/or modify
% it under the terms of the GNU General Public License as published by
% the Free Software Foundation, either version 3 of the License, or
% (at your option) any later version.
% 
% HINT is distributed in the hope that it will be useful,
% but WITHOUT ANY WARRANTY; without even the implied warranty of
% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
% GNU General Public License for more details.
% 
% You should have received a copy of the GNU General Public License
% along with HINT.  If not, see <http://www.gnu.org/licenses/>.
%  
% Martin Ruckert, Hochschule Muenchen, Lothstrasse 64, 80336 Muenchen
% 
\input hint.sty
\input changefile.sty

@i symbols.w
\makeindex
\maketoc

%\makefigindex
\titletrue

\def\lastrevision{${}$Revision: 1750 ${}$}
\def\lastdate{${}$Date: 2019-11-04 14:40:59 +0100 (Mon, 04 Nov 2019) ${}$}

\input titlepage.tex


\frontmatter

@

\plainsection{Preface}
To be written

\vskip 1cm
\noindent {\it M\"unchen\hfil\break
August 20, 2019 \hfill Martin Ruckert}


\tableofcontent
%\thefigindex


\mainmatter

\section{Introduction}\label{intro}
This program has three main parts:
The first part reads a \HINT/ file\cite{MR:format} and reconstructs \TeX's contribution list\cite{Knuth:tex}.
The routines found in this part translate data structures found in a \HINT/ file 
into \TeX's internal data structures. 
Some data structures, notably paragraph nodes, will require substantial
processing before moving the results to the contribution list; for example, paragraph nodes
are transformed into a sequence of lines by using \TeX's line breaking routine.

The line breaking routine is an example of code that belongs to the second part of this program:
routines that are taken from \TeX\cite{Knuth:tex} with little or no modification.
These routines are extracted using a change file (see~\cite{Knuth:cweb}) 
from a translation of \TeX's sources to {\tt cweb}\cite{MR:webtocweb}\cite{MR:web2w}.
For debugging purposes, even \TeX's output routines can be used to produce 
normal {\tt dvi} files as output. In general, however, the output is generated
by the routines of part three.

The third and final part of this program consists of routines that display ``the page'',
a data structure produced by \TeX's page builder (or variations of it) on a computer screen.
Further routines  let the user manipulate what is shown on the screen.
All routines in this third part of the program are highly system dependent. 
They need to be rewritten for different operating systems 
and different API's of the graphics subsystem. The present implementation
is based on the Windows\raise.5ex\hbox{\registered} operating system and its 32 Bit API\cite{ECMA-234}.


\section{Reading the Directory}
This chapter is a reimplementation of the parser for
short format \HINT/ files as described in ``\HINT/: The File Format''\cite{MR:format}
which constitutes the definitive specification of this format.
Where as the latter uses an internal represenation that is
completely independent of \TeX\ and therefore does not need any knowlegde of
\TeX's implementation, the implementation that follows here depends heavily on
the implementation of \TeX. To make the presentation short, 
it is assumed that the reader is familiar with the specification just mentioned and with
``\TeX: The Program''\cite{Knuth:tex}.

The primitive operations to read data from a \HINT/ file are defined by the following macros:
@<GET macros@>=
#define @[HQUIT@] @[QUIT("HGET overrun at " SIZE_F "\n",@+hpos-hstart)@]
#define @[HEND@]   @[((hpos<=hend)?0:HQUIT)@]

#define @[HGET8@]      ((hpos<hend)?hpos+=1,*(hpos-1):(HQUIT,0))
#define @[HGET16(X)@] ((X)=(hpos[0]<<8)+hpos[1],hpos+=2,HEND)
#define @[HGET24(X)@] ((X)=(hpos[0]<<16)+(hpos[1]<<8)+hpos[2],hpos+=3,HEND)
#define @[HGET32(X)@] ((X)=(hpos[0]<<24)+(hpos[1]<<16)+(hpos[2]<<8)+hpos[3],hpos+=4,HEND)
#define @[HGETTAG(A)@] @[A=HGET8,DBGTAG(A,hpos-1)@]
@


\subsection{Directory Entries}
This is taken directly from~\cite{MR:format}

@<GET macros@>=
#define @[HGET_SIZE(S,X,I)@] \
  if ((I)&b100) { \
    if (((I)&b011)==0) s=HGET8,xs=HGET8; \
    else if (((I)&b011)==1) HGET16(s),HGET16(xs); \
    else if (((I)&b011)==2) HGET24(s),HGET24(xs); \
    else if (((I)&b011)==3) HGET32(s),HGET32(xs); \
   } \
  else { \
    if (((I)&b011)==0) s=HGET8; \
    else if (((I)&b011)==1) HGET16(s); \
    else if (((I)&b011)==2) HGET24(s); \
    else if (((I)&b011)==3) HGET32(s); \
   } 

#define @[HGET_ENTRY(I,E)@] \
{ uint16_t i; \
  uint32_t s=0,xs=0; \
  char *name; \
  HGET16(i); HGET_SIZE(s,xs,I); HGET_STRING(name); @/\
  hset_entry(&(E),i,s,xs,name); \
}
@

@<get functions@>=
void hget_entry(entry_t *e)
{ @<read the start byte |a|@>@;
  DBG(dbgdir,"Reading directory entry\n");
  switch(a)
  { case TAG(0,b000+0): HGET_ENTRY(b000+0,*e);@+ break;
    case TAG(0,b000+1): HGET_ENTRY(b000+1,*e);@+ break;
    case TAG(0,b000+2): HGET_ENTRY(b000+2,*e);@+ break;
    case TAG(0,b000+3): HGET_ENTRY(b000+3,*e);@+ break;
    case TAG(0,b100+0): HGET_ENTRY(b100+0,*e);@+ break;
    case TAG(0,b100+1): HGET_ENTRY(b100+1,*e);@+ break;
    case TAG(0,b100+2): HGET_ENTRY(b100+2,*e);@+ break;
    case TAG(0,b100+3): HGET_ENTRY(b100+3,*e);@+ break;
    default:  TAGERR(a); @+ break; 
  }
  @<read and check the end byte |z|@>@;
  DBG(dbgdir,"entry %d: size=0x%x xsize=0x%x\n",@|e->section_no,e->size,e->xsize);
}
@


\subsection{Files and Sections}
Since modern computers with 64bit hardware have a huge address space,
mapping the entire file into virtual memory is the most efficient way to read a large file.
Mapping is not the same as reading and it is not the same as allocating precious memory,
all that is done by the operating system when needed. Mapping just reserves adresses.

After mapping the file to the address |hbase|, access to sections of the file is provided by setting the
three pointers |hpos|, |hstart|, and |hend|.

@<get variables@>=
uint8_t *hbase, *hpos, *hstart, *hend;

@
@<get functions@>=
void hopen_file(const char *in_name)
{ 
#ifdef WIN32
  HANDLE hFile, hMap; 
  uint64_t s;
  hFile = CreateFile(in_name,FILE_READ_DATA,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
  if (hFile==INVALID_HANDLE_VALUE)
    QUIT("Unable to open file %s", in_name);
  { DWORD hs,ls;
    ls=GetFileSize(hFile,&hs); 
    s=hs;
    s=s<<32;
    s=s+ls; 
  }
  if (s==0) QUIT("File %s is empty", in_name);
  hMap = CreateFileMapping( 
           hFile, // use paging file
           NULL,                 // no security attributes
           PAGE_READONLY,       // read/write access
           0,                    // size: high 32-bits
           0,            // size: low 32-bits
           NULL);     // name of map object
  if (hMap == NULL) QUIT("Unable to map file into memory");
  hbase = MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);  
  if (hbase==NULL)
    QUIT("Unable to obtain address of mapping for file %s", in_name);
  CloseHandle(hFile);
  hpos=hstart=hbase;
  hend=hstart+s;
#else 
  struct stat st;
  int fd;
  fd = open(in_name, O_RDONLY, 0);
  if (fd<0) QUIT("Unable to open file %s", in_name);
  if (fstat(fd, &st)<0) QUIT("Unable to get file size");
  hbase= mmap(NULL,st.st_size,PROT_READ,MAP_PRIVATE,fd, 0);
  if (hbase==MAP_FAILED) QUIT("Unable to map file into memory");
  close(fd);
  hpos=hstart=hbase;
  hend=hstart+st.st_size;
#endif
}
@

A \HINT/ file starts with a file banner\index{banner}. 
To read the banner, we have the function |hread_banner|; it returns |true| if successful.

@<get functions@>=
bool hget_banner(void)
{ char *t;
  int i;
  for (i=0;i<MAX_BANNER;i++)
  { banner[i]=HGET8;
    if (banner[i]=='\n') break;
  } 
  banner[++i]=0;
  t=banner;
  if (strncmp("hint",banner,4)!=0) QUIT("This is not a hint file");
  else t+=4;
  banner_size=(int)strlen(banner);
  if(banner[banner_size-1]!='\n') QUIT("Banner exceeds maximum size=0x%x",MAX_BANNER);
  if (*t!=' ') QUIT("Space expected after hint");
  else t++;
  version=strtol(t,&t,10);
  if (*t!='.') QUIT("Dot expected after version number %d",version);
  else t++;
  subversion=strtol(t,&t,10);
  if (*t!=' ' && *t!='\n') QUIT("Space expected after subversion number %d",subversion);
  MESSAGE("hint file version %d.%d:%s",version, subversion, t);
  DBG(dbgdir,"banner size=0x%x\n",banner_size);
  return true;
}

@
To read a short format input file, we use the function |hget_section|. 
Unlike the version of that routine in~\cite{MR:format}, we use |mmap|
to map the entire file into memory and then just need to adjust the |hpos| pointer.
Further buffer management is needed only for compressed sections.

@<get functions@>=
void hget_section(uint16_t n)
{ DBG(dbgbasic,"Reading section %d\n",n);
  RNG("Section number",n,0,max_section_no);
  if (dir[n].buffer!=NULL && dir[n].xsize>0)
  { hpos=hstart=dir[n].buffer;
    hend=hstart+dir[n].xsize;
  }
  else
  { hpos=hstart=hbase+dir[n].pos; 
    hend=hstart+dir[n].size;
    if (dir[n].xsize>0) hdecompress(n);
  }
}
@


\subsection{Compression}
The short file format offers the possibility to store sections in
compressed\index{compression} form. We use the {\tt zlib}\index{zlib+{\tt zlib}} compression library\cite{zlib}\cite{RFC1950}
to deflate\index{deflate} and inflate\index{inflate} individual sections.  When one of the following
functions is called, we can get the section buffer, the buffer size
and the size actually used from the directory entry.  If a section
needs to be inflated, its size after decompression is found in the
|xsize| field; if a section needs to be deflated, its size after
compression will be known after deflating it.

@s z_stream int
@<get functions@>=
void hdecompress(uint16_t n)
{ z_stream z; /* decompression stream */
  uint8_t *buffer;
  int i;

  DBG(dbgcompress,"Decompressing section %d from 0x%x to 0x%x byte\n",@|n, dir[n].size, dir[n].xsize);
  z.zalloc = (alloc_func)0;@+
  z.zfree = (free_func)0;@+
  z.opaque = (voidpf)0;
  z.next_in  = hstart;
  z.avail_in = hend-hstart;
  if (inflateInit(&z)!=Z_OK)
    QUIT("Unable to initialize decompression: %s",z.msg);
  ALLOCATE(buffer,dir[n].xsize+SAFETY_MARGIN,uint8_t);
  DBG(dbgbuffer,"Allocating output buffer size=0x%x, margin=0x%x\n",dir[n].xsize,SAFETY_MARGIN);
  z.next_out = buffer;           
  z.avail_out =dir[n].xsize+SAFETY_MARGIN;
  i= inflate(&z, Z_FINISH);
  DBG(dbgcompress,"in: avail/total=0x%x/0x%lx "@|"out: avail/total=0x%x/0x%lx, return %d;\n",@|
    z.avail_in,z.total_in, z.avail_out, z.total_out,i);
  if (i!=Z_STREAM_END)
    QUIT("Unable to complete decompression: %s",z.msg);
  if (z.avail_in != 0) 
    QUIT("Decompression missed input data");
  if (z.total_out != dir[n].xsize)
    QUIT("Decompression output size missmatch 0x%lx != 0x%x",z.total_out, dir[n].xsize );
  if (inflateEnd(&z)!=Z_OK)
    QUIT("Unable to finalize decompression: %s",z.msg);
  dir[n].buffer=buffer;
  dir[n].bsize=dir[n].xsize;
  hpos=hstart=buffer;
  hend=hstart+dir[n].xsize;
}
@


\subsection{Directory Section}
Except for the computation of the position, this is taken directly from~\cite{MR:format}.
@<get functions@>=
void hget_root(entry_t *root)
{ DBG(dbgbasic,"Get Root\n");
  hget_entry(root); 
  root->pos=hpos-hstart;
  max_section_no=root->section_no;
  root->section_no=0;
  if (max_section_no<2) QUIT("Sections 0, 1, and 2 are mandatory");
}

void hget_directory_section(void)
{ int i;
  entry_t root={0};
  hget_root(&root);
  DBG(dbgbasic,"Get Directory\n");
  new_directory(max_section_no+1);
  dir[0]=root;
  hget_section(0);
  for (i=1;i<=max_section_no;i++)@/
  { hget_entry(&(dir[i]));@+
    dir[i].pos=dir[i-1].pos +dir[i-1].size;@+
  }
}

@

\section{Reading Definitions}
Definitions occur in the definition section and in parameter lists, where parameter lists
can be parts of content nodes or part of a font description.

A parameter has three parts: a parameter number, a parameter value, and a parameter kind.
The parameter number and  parameter kind have different restrictions depending on the parameters occurence.

In parameter lists only integers, dimensions, extended dimensions, and glues are allowed.
In font descriptions, we have penalties, kerns, ligatures, hyphens, glue, math, rule, and image nodes.
In the definition section, pretty much everything is allowed, we just test if the parameter number is
less or equal to |max_ref| and set |max_ref| accordingly in |hget_max_definitions|.

\subsection{Maximum Values}
@<get functions@>=
void hallocate_definitions(void)
{ kind_t k;
  @<allocate definitions@>@;
}

void hget_max_definitions(void)
{ kind_t k;
  @<read the start byte |a|@>@;
  if (a!=TAG(list_kind,0)) QUIT("Start of maximum list expected");
  @<free definitions@>@;
  hset_max();
  while (true) @/
  { uint8_t n;
    if (hpos>=hend) QUIT("Unexpected end of maximum list");
    node_pos=hpos-hstart;
    HGETTAG(a);
    if  (KIND(a)==list_kind) break;
    if (INFO(a)!=1) QUIT("Maximum info %d not supported",INFO(a));
    k=KIND(a);
   if (max_fixed[k]>max_default[k]) QUIT("Maximum value for kind %s not supported",definition_name[k]);
    n=HGET8;
    RNG("Maximum number",n,max_ref[k],0xFF);
    max_ref[k]=n;
    DBG(dbgdef,"max(%s) = %d\n",definition_name[k],max_ref[k]);
   @<read and check the end byte |z|@>@;
  }
  if (INFO(a)!=0) QUIT("End of maximum list with info %d", INFO(a));
  hallocate_definitions(); 
}
@
\subsection{Definitions}
The following function reads a single definition and stores it.
By default, we store definitions as pointers to \TeX's data structures.

@<get functions@>=
void hget_def_node(void)
{ @+uint8_t n;
  @<read the start byte |a|@>@;
  n=HGET8;
  if (max_fixed[KIND(a)]>max_default[KIND(a)]) 
      QUIT("Definitions for kind %s not supported", definition_name[KIND(a)]);
    if(n>max_ref[KIND(a)] || n <= max_fixed[KIND(a)]) 
      QUIT("Definition %d for %s out of range [%d - %d]",@|
        n, definition_name[KIND(a)],max_fixed[KIND(a)]+1,max_ref[KIND(a)]);

  if (KIND(a)!=range_kind) REF(KIND(a),n);
  DBG(dbgtags,"Defining %s %d\n", definition_name[KIND(a)],n);
  if (KIND(a)==font_kind) hget_font_def(a,n);
  else if (KIND(a)==int_kind) integer_def[n]=hget_integer_def(a);
  else if (KIND(a)==dimen_kind) dimen_def[n]=hget_dimen_def();
  else if (KIND(a)==xdimen_kind) hget_xdimen_def(a,n);
  else if (KIND(a)==baseline_kind) hget_baseline_def(a,n);
  else if (KIND(a)==glue_kind) pointer_def[glue_kind][n]=hget_glue_def(a);
  else if (KIND(a)==param_kind)  param_def[n]=hget_param_list(a);
  else if (KIND(a)==range_kind) hget_range_def(a,n);
  else if (KIND(a)==page_kind) hget_page_def(a,n);
  else  pointer_def[KIND(a)][n]=hget_definition(a);
  @<read and check the end byte |z|@>@;
}

pointer hset_glue(glue_t *g)
{ if (ZERO_GLUE(*g)) 
     return zero_glue;
  else
  { pointer p=get_node(glue_spec_size);
    width(p)=g->w.w; /* we ignore the horizontal and vertical factor */
    stretch(p)=round(g->p.f*ONE); stretch_order(p)=g->p.o;
    shrink(p)=round(g->m.f*ONE); shrink_order(p)=g->m.o;
    return p; 
  } 
}

void hset_default_definitions(void)
{ int i;
  for (i=0; i<=MAX_INT_DEFAULT; i++) integer_def[i]= int_defaults[i];
  for (i=0; i<=MAX_DIMEN_DEFAULT; i++) dimen_def[i]= dimen_defaults[i];
  for (i=0; i<=MAX_XDIMEN_DEFAULT; i++) xdimen_def[i]= xdimen_defaults[i];
  for (i=0; i<=MAX_GLUE_DEFAULT; i++) pointer_def[glue_kind][i]=hset_glue(&(glue_defaults[i]));
  for (i=0; i<=MAX_BASELINE_DEFAULT; i++)
  { baseline_def[i].bs=hset_glue(&(baseline_defaults[i].bs));
    baseline_def[i].ls=hset_glue(&(baseline_defaults[i].ls));
    baseline_def[i].lsl=baseline_defaults[i].lsl;
  }
}


void hget_definition_section(void)
{ DBG(dbgbasic,"Definitions\n");
  hget_section(1);
  DBG(dbgdef,"Reading list of maximum values\n");
  hget_max_definitions();
  hset_default_definitions();
  DBG(dbgdef,"Reading list of definitions\n");
  while (hpos<hend) @/
    hget_def_node();
  hget_font_metrics();
  hvsize=dimen_def[vsize_dimen_no];
  hhsize=dimen_def[hsize_dimen_no];
}
@

@<get variables@>=
pointer *pointer_def[32]={NULL};
@

@<\TeX\ declarations@>=
extern pointer *pointer_def[32];
extern scaled hhsize, hvsize;
@

@<get declarations@>=
static void hget_font_def(uint8_t a, uint8_t n);
static int32_t hget_integer_def(uint8_t a);
static scaled hget_dimen_def(void);
static void hget_xdimen_def(uint8_t a, uint8_t n);
static pointer hget_glue_def(uint8_t a);
static void hget_baseline_def(uint8_t a, uint8_t n);
static param_def_t *hget_param_list(uint8_t a);
static void hget_range_def(uint8_t a, uint8_t pg);
static void hget_page_def(uint8_t a, uint8_t n);
static void hget_font_metrics();
static pointer hget_definition(uint8_t a);
@


@<allocate definitions@>=
for (k=0;k<32;k++)
{ if (k==font_kind || k==int_kind|| k==dimen_kind||k==xdimen_kind||k==glue_kind||k==baseline_kind|| k==range_kind||k==page_kind||k==param_kind) continue;
  if (max_ref[k]>=0 && max_ref[k]<=256)
  { DBG(dbgdef,"Allocating Definitions for %s=%d: %d entries of " SIZE_F " byte each\n",definition_name[k],k,max_ref[k]+1,sizeof(pointer));
    ALLOCATE(pointer_def[k],max_ref[k]+1,pointer);
  }
}
@

@<free definitions@>=
for (k=0;k<32;k++)
{ free(pointer_def[k]); pointer_def[k]=NULL; }
@


Now lets consider the few exceptions where definitions are not stored as pointers.
We start with the simple ones.
\subsubsection{Integers}

@<get variables@>=
int32_t *integer_def;
@

@<\TeX\ declarations@>=
extern int32_t *integer_def;
@


@<allocate definitions@>=
ALLOCATE(integer_def, max_ref[int_kind]+1, int32_t);
@

@<free definitions@>=
free(integer_def); integer_def=NULL;
@

@<get functions@>=
static int32_t hget_integer_def(uint8_t a)
{ if (INFO(a)==1) { int8_t n=HGET8; return n;}
  else  if (INFO(a)==2) { int16_t n; HGET16(n); return n;}
  else if (INFO(a)==4) {int32_t n; HGET32(n); return n;}
  else TAGERR(a);
  return 0;
}

int32_t hget_integer_ref(uint8_t n)
{ @+REF(int_kind,n);
  return integer_def[n];
}
@

\subsubsection{Dimensions}
@<\TeX\ types@>=
typedef int32_t scaled;
@

@<get variables@>=
scaled *dimen_def;
@

@<allocate definitions@>=
ALLOCATE(dimen_def,max_ref[dimen_kind]+1, dimen_t);
@

@<free definitions@>=
free(dimen_def); dimen_def=NULL;
@

@<get functions@>=
static scaled hget_dimen_def(void)
{ scaled d; HGET32(d); return d;
}

scaled hget_dimen_ref(uint8_t n)
{ @+REF(dimen_kind,n);
  return dimen_def[n];
}
@

@<\TeX\ declarations@>=
extern scaled *dimen_def;
@

\subsubsection{Extended Dimensions}

@<get variables@>=
xdimen_t *xdimen_def;
@

@<allocate definitions@>=
ALLOCATE(xdimen_def, max_ref[xdimen_kind]+1, xdimen_t);
@
@<free definitions@>=
free(xdimen_def); xdimen_def=NULL;
@
@<\TeX\ declarations@>=
extern void print_xdimen(int i);
@

@<get functions@>=
static void hget_xdimen_def(uint8_t a, uint8_t n)
{ HGET_XDIMEN(INFO(a),xdimen_def[n]);
}

scaled hget_xdimen_ref(uint8_t n)
{ @+REF(xdimen_kind,n);
  return  xdimen_def[n].w+xdimen_def[n].h*hhsize+xdimen_def[n].v*hvsize;  
}
@

\subsubsection{Glues}

@<get functions@>=
static pointer hget_glue_def(uint8_t a)
{ pointer p;
  HGET_GLUE(INFO(a));
  return p;
}

pointer hget_glue_ref(uint8_t n)
{ @+REF(glue_kind,n);
  return  pointer_def[glue_kind][n];
}

pointer hget_param_glue(uint8_t n)
{ @+REF(glue_kind,n);
  return  new_glue(pointer_def[glue_kind][n]);
}
@

@<\TeX\ declarations@>=
extern pointer hget_param_glue(uint8_t n);
@

@<\TeX\ types@>=
typedef uint16_t pointer;
@

@<allocate definitions@>=
ALLOCATE(pointer_def[glue_kind],max_ref[glue_kind]+1, pointer);
@


@<\TeX\ macros@>=
#define null 0
@

\subsection{Baseline Skips}
Baseline skip specifications are stored using variables of type |bs_t|.
Baseline skips are allowed only in vertical lists and
the actual baseline skip glue will be inserted just before appending the next hbox or vbox to
the list. Until then we keep a possible baseline specification on a stack that parallels \TeX's
semantic nest.

@<\TeX\ types@>=
typedef struct { pointer bs, ls; scaled lsl;} bs_t;
@

@<get variables@>=
bs_t *baseline_def=NULL;
@

@<allocate definitions@>=
ALLOCATE(baseline_def, max_ref[baseline_kind]+1, bs_t);
@

@<free definitions@>=
free(baseline_def); baseline_def=NULL;
@

@<get functions@>=
static void hget_baseline_def(uint8_t a, uint8_t n)
{ HGET_BASELINE(INFO(a),baseline_def[n]);
}

void hget_baseline_ref(uint8_t n, bs_t *b)
{ REF(baseline_kind,n);
  *b=baseline_def[n];
}



pointer happend_to_vlist(pointer @!b)
{@+scaled d; /*deficiency of space between baselines*/ 
pointer @!p=null; /*a new glue node*/ 

if (needs_bs && prev_depth > ignore_depth) 
  {@+d=width(cur_bs)-prev_depth-height(b);
  if (d < cur_lsl) p=new_glue(cur_ls);
  else{@+p=new_spec(cur_bs);
    width(p)=d; p=new_glue(p);
    } 
  link(tail)=p;tail=p;
  if (nest_ptr==0)
    store_map(p,node_pos,0,0);
  } 
link(tail)=b;tail=b;prev_depth=depth(b);
needs_bs=false;
return p;
} 
@
@<\TeX\ declarations@>=
extern void print_baseline_skip(int i);
extern pointer happend_to_vlist(pointer b);
@


\subsection{Fonts}\label{fonts}
\TeX\ gets ist knowlegde about fonts from font metric files. \HINT/ will not need all of that
information, but for now, the complete \TeX\ font metric file is included inside the \HINT/ file,
and we can load all that information by calling the procedure |read_font_info| defined by \TeX.
Because \TeX\ reads the font metric file using a special |fget| macro, only a few modifications,
as explained below, are necessary.

When rendering fonts, we will need to find the section containing the actual glyphs.

So we store the font name |n|, the section number |i|, 
the optional ``at size'' |s|, the pointer to the font glue |g|,
the pointer to the font hyphen |h|, and the font parameters.

@<get types@>=
typedef struct {
char *n;
uint16_t m,q;
scaled s;
pointer g;
pointer h;
pointer p[MAX_FONT_PARAMS+1];
} font_def_t;
@

@<get variables@>=
font_def_t *font_def;
@

@<allocate definitions@>=
ALLOCATE(font_def, max_ref[font_kind]+1, font_def_t);
@

@<free definitions@>=
free(font_def); font_def=NULL;
@
@<get functions@>=
static void hget_font_def(uint8_t a, uint8_t n)
{ char *t;
  HGET_STRING(t);font_def[n].n=strdup(t); 
  DBG(dbgdef,"Font %d: %s\n", n, t); 
  if (INFO(a)&b001)  HGET32(font_def[n].s); else font_def[n].s=0;
  hget_font_params(n,&(font_def[n]));
}

static void hget_font_params(uint8_t n, font_def_t *f)
{@+HGET16(f->m); @+RNG("Font metrics",f->m,3,max_section_no);
  HGET16(f->q); @+RNG("Font glyphs",f->q,3,max_section_no);
  f->g=hget_glue_node(); 
  f->h=hget_hyphen_node();
  DBG(dbgdef,"Start font parameters\n");
  while (KIND(*hpos)!=font_kind)@/  
  { kind_t k;
    uint8_t n;
    @<read the start byte |a|@>@;
    k=KIND(a);
    n=HGET8;
    DBG(dbgdef,"Reading font parameter %d: %s\n",n, definition_name[k]);
    if (k!=penalty_kind && k!=kern_kind && k!=ligature_kind && @|
        k!=hyphen_kind && k!=glue_kind && k!=math_kind && @| k!=rule_kind && k!=image_kind)
      QUIT("Font parameter %d has invalid type %s",n, content_name[n]);
    RNG("Font parameter",n,0,MAX_FONT_PARAMS);
    f->p[n]=hget_definition(a);
    @<read and check the end byte |z|@>@;
  }
  DBG(dbgdef,"End font definition\n");
}

static void hget_font_metrics(void)
{ int i;
  for (i=0; i<=max_ref[font_kind]; i++)
    if (font_def[i].m!=0)
    { hget_section(font_def[i].m);
      read_font_info(i,font_def[i].n,font_def[i].s);
    }
}
@

@<\TeX\ types@>=

extern void read_font_info(int f, char *n, scaled s);
@

\subsection{Parameter Lists}\label{getparamlist}
There are three types of data that we allow in parameter lists: integers, dimensions,
and glue. Hence, for each parameter, we store the parameter number |n|, its kind |k|, and its value |i|, |d|, or |g|.
To form linked lists of parameter definitions, we add a |next| pointer. The variable |param_def| contains the dynamically allocated 
array of lists of parameter definitions.
@<get types@>=
typedef struct param_t {
uint8_t n,k;
union {@+ int32_t i;@+
        scaled  d;@+
        pointer g;@+};
     } param_t;@#

typedef struct param_def_t {
struct param_def_t *next;@+
param_t p; } param_def_t;
@


@<get variables@>=
param_def_t **param_def;
@

@<allocate definitions@>=
ALLOCATE(param_def, max_ref[param_kind]+1, param_def_t);
@

@<free definitions@>=
if (param_def!=NULL)
{ int i;
  for (i=0; i<=max_ref[param_kind]; i++)
    free_param_list(param_def[i]);
}  
free(param_def); param_def=NULL;
@

@<get functions@>=
void free_param_list(param_def_t *p)
{ while (p!=NULL)
  { param_def_t *q=p;
    p=p->next;
    free(q);
  } 
} 
@

Next we implement reading a parameter list from a \HINT/ file.

@<get functions@>=
static param_def_t *hget_param_list(uint8_t a)
{ uint32_t s,t;
  param_def_t *p=NULL;
  uint8_t *list_start,*list_end;
  list_start=hpos;
  s=hget_list_size(INFO(a)); 
  hget_size_boundary(INFO(a));
  list_end=hpos+s;
  if (list_end>=hend) 
    QUIT("list end after before stream end\n"); 
  while (hpos<list_end)
  { @+param_def_t *r; param_t *q;
    @<read the start byte |a|@>@;
    ALLOCATE(r,1,param_def_t);
    q=&(r->p);
    q->n=HGET8;
    q->k=KIND(a);
    DBG(dbgtags,"Defining %s %d\n", definition_name[KIND(a)],q->n);
    if (KIND(a)==int_kind) q->i=hget_integer_def(a);
    else if (KIND(a)==dimen_kind) q->d=hget_dimen_def();
    else if (KIND(a)==glue_kind) q->g=hget_glue_def(a);
    else TAGERR(a);
    @<read and check the end byte |z|@>@;
    r->next=p;
    p=r;
  }
  hget_size_boundary(INFO(a));
  t=hget_list_size(INFO(a)); 
  if (t!=s) 
    QUIT("List sizes at " SIZE_F " and " SIZE_F " do not match 0x%x != 0x%x",list_start-hstart,list_end-hstart,s,t);
  return p;
}

param_def_t *hget_param_list_node(void)
{ @+if (KIND(*hpos)!=param_kind) return NULL;
  else 
  { @+param_def_t *p;
    @<read the start byte |a|@>@;
    p=hget_param_list(a);
    @<read and check the end byte |z|@>@;
    return p;
  }
}

param_def_t *hget_param_list_ref(uint8_t n)
{@+ REF(param_kind,n);
  return param_def[n];
}
@

Finaly, here are two functions that set and restore global parameters
based on  a parameter list.

@<get functions@>=
#define MAX_SAVE 100
static param_t par_save[MAX_SAVE];
static int par_save_ptr;

void hset_param_list(param_def_t *p)
{ par_save_ptr=0;
  while (p!=NULL)
  { param_t *q;
    if (par_save_ptr>= MAX_SAVE) QUIT("Parameter save stack overflow");
    q=&(par_save[par_save_ptr++]);
    q->k=p->p.k;
    q->n=p->p.n;
    if (q->k==int_kind)
    { q->i= integer_def[q->n];@+ integer_def[q->n] =p->p.i; }
    else if (q->k==dimen_kind)
    { q->d=  dimen_def[q->n];@+ dimen_def[q->n]=p->p.d; }
    else if (q->k==glue_kind)
    { q->g=  pointer_def[glue_kind][q->n];@+ pointer_def[glue_kind][q->n]=p->p.g; }
    p=p->next;
  }
}

void hrestore_param_list(void)
{
  while (par_save_ptr>0)
  { param_t *q;
    q=&(par_save[--par_save_ptr]);
    if (q->k==int_kind)
    { integer_def[q->n] =q->i; }
    else if (q->k==dimen_kind)
    { dimen_def[q->n]=q->d; }
    else if (q->k==glue_kind)
    { pointer_def[glue_kind][q->n]=q->g; }
  }
  par_save_ptr=0;
}
@

\subsection{Page Ranges}
@<get variables@>=
typedef struct {
 uint8_t pg;
 uint32_t f,t;
} range_def_t;
range_def_t *range_def;
@
@<allocate definitions@>=
ALLOCATE(range_def, max_ref[range_kind]+1, range_def_t);
@

@<free definitions@>=
free(range_def); range_def=NULL;
@

@<get functions@>=
static void hget_range_def(uint8_t a, uint8_t pg)
{ static uint8_t n=0;
  uint32_t f, t; 
  REF(page_kind,pg);
  REF(range_kind,n);
  if (INFO(a)&b100) @+
  { @+ if (INFO(a)&b001) HGET32(f); @+else HGET16(f); @+}
  else f=0;
  if (INFO(a)&b010) @+
  { @+if (INFO(a)&b001) HGET32(t); @+else HGET16(t); @+}
  else t=0xFFFFFFFF;
  range_def[n].pg=pg;
  range_def[n].f=f;
  range_def[n].t=t;
  DBG(dbgrange,"Range *%d from 0x%x\n",pg,f);
  DBG(dbgrange,"Range *%d to 0x%x\n",pg,t);
  n++;
}

uint8_t hget_page_ref(uint32_t pos)
{ @+int i;
  for (i=1;i<=max_ref[range_kind]; i++)
    if (range_def[i].f<=pos && pos <range_def[i].t) return range_def[i].pg;
  return 0;
}
@

\subsection{Streams}
Not yet implemented.

\subsection{Page Templates}
Not yet implemented.
@<get variables@>=
typedef struct {
  pointer p;
} page_def_t;
page_def_t *page_def;
@

@<allocate definitions@>=
ALLOCATE(page_def, max_ref[page_kind]+1, page_def_t);
@

@<free definitions@>=
free(page_def); page_def=NULL;
@

@<get functions@>=
static void hget_page_def(uint8_t a, uint8_t n)
{ page_def[n].p=null;
}
@



\subsection{References}
There are only a few functions that still need to be defined.
@<get functions@>=
pointer hget_ligature_ref(uint8_t n)
{ @+REF(ligature_kind,n);
  return copy_node_list(pointer_def[ligature_kind][n]);
}

pointer hget_math_ref(uint8_t n)
{ @+REF(math_kind,n);
  return copy_node_list(pointer_def[math_kind][n]);
}

pointer hget_rule_ref(uint8_t n)
{ @+REF(rule_kind,n);
  return copy_node_list(pointer_def[rule_kind][n]);
}

pointer hget_image_ref(uint16_t n)
{ @+REF(image_kind,n);
  return copy_node_list(pointer_def[image_kind][n]);
}

pointer hget_hyphen_ref(uint8_t n)
{ @+REF(hyphen_kind,n);
  return copy_node_list(pointer_def[hyphen_kind][n]);
}

pointer hget_leaders_ref(uint8_t n)
{ @+REF(leaders_kind,n);
  return copy_node_list(pointer_def[leaders_kind][n]);
}




@

\section{Reading Content Nodes}
The following section explains how to read the content section and convert the \HINT/
representation of the content to the \TeX\ representation. While in the future we might have
a renderer that does not use the \TeX\ representation, which was designed about 50 years ago,
at present the reuse of \TeX's functions and data structure saves development time.

Because we will need to read the content section in both directions, almost all code
in this chapter is given in two symetric versions: 
The forward version will start reading
a node with |hpos| pointing to the first byte of the data and ends with |hpos| pointing
past the last byte of the data; these functions or macros have the word |get| or |GET| in their
name. 
The backward version will start reading
a node with |hpos| pointing past the last byte of the data and ends with |hpos| pointing 
to the first byte of the data; these functions or macros have the word |teg| or |TEG| in their
name.

\subsection{The Content Section}
To position the input stream on the content section we use the following function:
@<get functions@>=
void hget_content_section()
{ @+DBG(dbgbasic,"Get Content\n");
  hget_section(2);@+
}
@
There is no separate ``|teg|'' function in this case. If necessary, one can set |hpos=hend|.


The basic data structure of a \HINT/ file is a node. We distinguish content- and definition-nodes. 
In both cases, a node consists of a start byte followed by
the content or the definition and a matching end byte.
 

@<read the start byte |a|@>=
uint8_t a,z; /* the start and the end byte*/
HGETTAG(a);
@

@<read and check the end byte |z|@>=
HGETTAG(z);@+
if (a!=z) TAGSERR(a,z);@/@t~@>
@

The |hget_node| function gets the next node from the input based on the tag byte |a|
and adds it to the current list. The function is used in |hget_content| to read a content node
but also in the function |hget_definition| to get the content of a definition. 

@<get functions@>=

static void hget_node(uint8_t a)
{ @+switch (a)@/
  {@+ 
    @<cases to get content@>@;@t\1@>@/
    default:
      TAGERR(a);@t\2@>@/
  }
}

void hget_content(void)
{ @+@<read the start byte |a|@>@;
  node_pos=(hpos-hstart)-1;
  hget_node(a);
  @<read and check the end byte |z|@>@;
  if (nest_ptr==0 && tail!=head && (type(tail)==penalty_node || type(tail)==glue_node || type(tail)==kern_node))
      store_map(tail,node_pos,0,0);
}

static pointer hget_definition(uint8_t a)
{@+pointer p;
  if (link(head)!=null) QUIT("Calling get_node with nonempty curent list");
  hget_node(a);
  p=link(head);
  if (p!=null && link(p)!=null) QUIT("get_node returns multiple nodes");
  link(head)=null;
  tail=head;
  return p;
}
@

Now let's turn to the backwards version.
The primitive reading operations are defined by the following macros:
@<TEG macros@>=
#define @[HBACK(X)@] @[((hpos-(X)<hstart)?(QUIT("HTEG underflow\n"),NULL):(hpos-=(X)))@]

#define @[HTEG8@]     (HBACK(1),*(hpos))
#define @[HTEG16(X)@] (HBACK(2),(X)=(hpos[0]<<8)+hpos[1])
#define @[HTEG24(X)@] (HBACK(3),(X)=(hpos[0]<<16)+(hpos[1]<<8)+hpos[2])
#define @[HTEG32(X)@] (HBACK(4),(X)=(hpos[0]<<24)+(hpos[1]<<16)+(hpos[2]<<8)+hpos[3])
@

The next macros read and check start and end byte.

@<read the end byte |z|@>=
  uint8_t a,z; /* the start and the end byte*/
  z=HTEG8,DBGTAG(z,hpos);
@

@<read and check the start byte |a|@>=
  a=HTEG8,DBGTAG(a,hpos);
  if (z!=a) 
    QUIT(@["Tag mismatch [%s,%d]!=[%s,%d] at " SIZE_F " to 0x%x\n"@],@|
         NAME(a),INFO(a),NAME(z),INFO(z),hpos-hstart,node_pos);

@

We conclude the section with the equivalents of |hget_node| and |hget_content|.
 The |node_pos| points to
the end byte while reading the node and points to the start byte when reading the node is done.

@<teg functions@>=
static void hteg_node(uint8_t z)
{ @+switch (z)@/
  {@+ 
    @<cases to teg content@>@;@t\1@>@/
    default:
      TAGERR(z);@t\2@>@/
  }
}

void hteg_content(void)
{ @+@<read the end byte |z|@>@;
  node_pos=hpos-hstart;
  hteg_node(z);
  @<read and check the start byte |a|@>@;
  node_pos=hpos-hstart;
  if (nest_ptr==0 && tail!=head && (type(tail)==penalty_node || type(tail)==glue_node || type(tail)==kern_node))
      store_map(tail,node_pos,0,0);
}
@


We need the following definitions from \TeX:
@<\TeX\ macros@>=
#define is_char_node(X)	(X >= hi_mem_min)   /*does the argument point to a |char_node|?*/ 
#define disc_node	7 /*|type| of a discretionary node*/ 
#define glue_node	10 /*|type| of node that points to a glue specification*/ 
#define kern_node	11 /*|type| of a kern node*/ 
#define penalty_node	12 /*|type| of a penalty node*/ 
#define empty_flag 0xFFFF
@

Next we continue with basic data types and then progress from the most simple to 
the most complex nodes.

\subsection{Testing the Backwards Reading}
The following code  is similar to the code for the {\tt skip} program described in \cite{MR:format}.

@(hteg.h@>=
extern void hteg_content(void);
#if 0
extern void hteg_content(uint8_t z);
extern void hteg_xdimen_node(xdimen_t *x);
extern void hteg_list(list_t *l);
extern float32_t hteg_float32(void);
extern void hteg_rule_node(void);
extern void hteg_hbox_node(void);
extern void hteg_vbox_node(void);
extern void hteg_glue_node(void);
#endif
@

@(back.c@>=
#include <stdio.h>
#include <string.h>
#include "htex.h"
#include "hformat.h"
#include "hget.h"
#include "hteg.h"

@<command line variables@>@;

@<command line functions@>@;

int main(int argc, char *argv[])
{ char stem_name[MAX_NAME];
  int stem_length=0, path_length=0;
  bool option_log=false;

  @<process the command line@>@;
  @<open the log file@>@;
  hmem_init();
  hlist_init();
  hopen_file(in_name);
  hget_banner();
  hget_directory_section();
  hget_definition_section();
  hget_content_section();
  hpage_init();
  hpos=hend;
  while (hpos>hstart)
  { hteg_content();
    while (hbuild_page_up())  
    { hship_out(stream[0].p); stream[0].p=0; hresume_after_output(); hpage_init();}
  }
  if (!hits_all_over())
  { if (hbuild_page_up()) 
    { hship_out(stream[0].p); stream[0].p=0;}
  }
  @<close the log file@>@;
  return 0;
}

@

\subsection{Strings}
\noindent
@<GET macros@>=
#define @[HGET_STRING(S)@] @[S=(char*)hpos;\
 while(hpos<hend && *hpos!=0) { RNG("String character",*hpos,0x20,0x7E); hpos++;}\
 hpos++;
@
Strings occur only in the definition section. Hence, there is no need to parse strings in the backward direction.

\subsection{UTF8 Character Codes}
@<GET macros@>=
#define @[HGET_UTF8C(X)@]  (X)=HGET8;@+ if ((X&0xC0)!=0x80) \
  QUIT("UTF8 continuation byte expected at " SIZE_F " got 0x%02X\n",hpos-hstart-1,X)@;
@

@<get functions@>=
uint32_t hget_utf8(void)
{ uint8_t a;
  a=HGET8;
  if (a<0x80) return a;
  else
  { if ((a&0xE0)==0xC0) @/
    { uint8_t b; @+ HGET_UTF8C(b);
      return ((a&~0xE0)<<6)+(b&~0xC0);
    }
    else if ((a&0xF0)==0xE0) @/
    { uint8_t b,c;  @+ HGET_UTF8C(b); @+ HGET_UTF8C(c);
      return ((a&~0xF0)<<12)+((b&~0xC0)<<6)+(c&~0xC0);
    }
    else if ((a&0xF8)==0xF0) @/
    { uint8_t b,c,d;  @+ HGET_UTF8C(b); @+ HGET_UTF8C(c); @+ HGET_UTF8C(d);
      return ((a&~0xF8)<<18)@|+ ((b&~0xC0)<<12)+((c&~0xC0)<<6)+(d&~0xC0);
    }
    else QUIT("UTF8 byte sequence expected");
  }
}
@
We will parse UTF-8 codes only in forward direction.

\subsection{Floating Point Numbers}
We need a way to read binary floating point numbers.

@<get functions@>=
float32_t hget_float32(void)
{  @+union {@+float32_t d; @+ uint32_t bits; @+} u;
   HGET32(u.bits);
   return u.d;
}
@

@<teg auxiliar functions@>=
float32_t hteg_float32(void)
{  @+union {@+float32_t d; @+ uint32_t bits; @+} u;
   HTEG32(u.bits);
   return u.d;
}
@

\subsection{Extended dimensions}
The viewer can convert extended dimensions immediately to regular dimensions
because |hsize| and |vsize| are known.

@<GET macros@>=
#define @[HGET_XDIMEN(I,X)@] \
{ if((I)&b100) HGET32((X).w);@+ else (X).w=0;\
  if((I)&b010) (X).h=hget_float32(); @+ else (X).h=0.0;\
  if((I)&b001) (X).v=hget_float32(); @+else (X).v=0.0;\
}
@

@<TEG macros@>=
#define @[HTEG_XDIMEN(I,X)@] \
  if((I)&b001) (X).v=hteg_float32(); @+else (X).v=0.0;\
  if((I)&b010) (X).h=hteg_float32(); @+ else (X).h=0.0;\
  if((I)&b100) HTEG32((X).w);@+ else (X).w=0;\
@

@<get functions@>=
scaled hget_xdimen(uint8_t a)
{ @+xdimen_t x;
  switch(a)
  { 
    case TAG(xdimen_kind,b000): return hget_xdimen_ref(HGET8);
    case TAG(xdimen_kind,b001): HGET_XDIMEN(b001,x);@+break;
    case TAG(xdimen_kind,b010): HGET_XDIMEN(b010,x);@+break;
    case TAG(xdimen_kind,b011): HGET_XDIMEN(b011,x);@+break;
    case TAG(xdimen_kind,b100): HGET_XDIMEN(b100,x);@+break;
    case TAG(xdimen_kind,b101): HGET_XDIMEN(b101,x);@+break;
    case TAG(xdimen_kind,b110): HGET_XDIMEN(b110,x);@+break;
    case TAG(xdimen_kind,b111): HGET_XDIMEN(b111,x);@+break;
    default:
     x.w=0;x.h=x.v=0.0;
     QUIT("Extent expected got [%s,%d]",NAME(a),INFO(a));
  }
  return  x.w+x.h*hhsize+x.v*hvsize;  
 }

scaled hget_xdimen_node(void)
{ @+scaled x=0;
  @<read the start byte |a|@>@;
  if (KIND(a)==xdimen_kind)
    x=hget_xdimen(a);
  else
     QUIT("Extent expected at 0x%x got %s",node_pos,NAME(a));
  @<read and check the end byte |z|@>@;
  return x;
}
@

@<teg auxiliar  functions@>=
scaled hteg_xdimen(uint8_t a)
{ @+xdimen_t x;
  switch(a)
  { 
    case TAG(xdimen_kind,b000): return hget_xdimen_ref(HTEG8);
    case TAG(xdimen_kind,b001): HTEG_XDIMEN(b001,x);@+break;
    case TAG(xdimen_kind,b010): HTEG_XDIMEN(b010,x);@+break;
    case TAG(xdimen_kind,b011): HTEG_XDIMEN(b011,x);@+break;
    case TAG(xdimen_kind,b100): HTEG_XDIMEN(b100,x);@+break;
    case TAG(xdimen_kind,b101): HTEG_XDIMEN(b101,x);@+break;
    case TAG(xdimen_kind,b110): HTEG_XDIMEN(b110,x);@+break;
    case TAG(xdimen_kind,b111): HTEG_XDIMEN(b111,x);@+break;
    default:
     x.w=0;x.h=x.v=0.0;
     QUIT("Extent expected got [%s,%d]",NAME(a),INFO(a));
  }
  return  x.w+x.h*hhsize+x.v*hvsize;  
 }

scaled hteg_xdimen_node(void)
{ @+scaled x=0;
  @<read the end byte |z|@>@;
  if (KIND(z)==xdimen_kind)
    x=hteg_xdimen(z);
  else
     QUIT("Extent expected at 0x%x got %s",node_pos,NAME(z));
  @<read and check the start byte |a|@>@;
  return x;
}
@

@<get declarations@>=
static scaled hget_xdimen_node(void);
@

@<teg declarations@>=
static scaled hteg_xdimen_node(void);
@



\subsection{Stretch and Shrink}
@<hint types@>=
typedef union {@+float32_t f; @+ uint32_t u; @+} stch_t;
@

@<GET macros@>=
#define @[HGET_STRETCH(F,O)@] @+{@+ stch_t _st; @+ HGET32(_st.u);@/ (O)=_st.u&3;  _st.u&=~3; (F)=(scaled)(_st.f*ONE); @+}
@
@<TEG macros@>=
#define @[HTEG_STRETCH(F,O)@] @+{@+ stch_t _st; @+ HTEG32(_st.u);@/ (O)=_st.u&3;  _st.u&=~3; (F)=(scaled)(_st.f*ONE); @+}
@


\subsection{Glyphs}

\noindent
@<GET macros@>=
#define @[HGET_GLYPH(I)@] \
{@+uint8_t f; @+uint32_t c;\
  if (I==1) c=HGET8;\
  else if (I==2) HGET16(c);\
  else if (I==3) HGET24(c);\
  else if (I==4) HGET32(c);\
  f=HGET8; @+REF(font_kind,f);@/\
  tail_append(new_character(f,c));\
}
@

@<TEG macros@>=
#define @[HTEG_GLYPH(I)@] \
{@+uint8_t f; @+uint32_t c;\
  f=HTEG8; @+REF(font_kind,f);@/\
  if (I==1) c=HTEG8;\
  else if (I==2) HTEG16(c);\
  else if (I==3) HTEG24(c);\
  else if (I==4) HTEG32(c);\
  tail_append(new_character(f,c));\
}
@

@<cases to get content@>=
case TAG(glyph_kind,1): @+HGET_GLYPH(1);@+break;
case TAG(glyph_kind,2): @+HGET_GLYPH(2);@+break;
case TAG(glyph_kind,3): @+HGET_GLYPH(3);@+break;
case TAG(glyph_kind,4): @+HGET_GLYPH(4);@+break;
@
@<cases to teg content@>=
case TAG(glyph_kind,1): @+HTEG_GLYPH(1);@+break;
case TAG(glyph_kind,2): @+HTEG_GLYPH(2);@+break;
case TAG(glyph_kind,3): @+HTEG_GLYPH(3);@+break;
case TAG(glyph_kind,4): @+HTEG_GLYPH(4);@+break;
@

@<\TeX\ declarations@>=
extern pointer new_character(uint8_t f, uint8_t c);
@


\subsection{Penalties}
\noindent
@<cases to get content@>=
case TAG(penalty_kind,0): @+ tail_append(new_penalty(hget_integer_ref(HGET8))); @+break;
case TAG(penalty_kind,1): @+ {@+tail_append(new_penalty(HGET8));@+} @+break;
case TAG(penalty_kind,2): @+ {@+int16_t n;@+ HGET16(n);@+RNG("Penalty",n,-20000,+20000); @+tail_append(new_penalty(n)); @+} @+break;
@

@<cases to teg content@>=
case TAG(penalty_kind,0):  @+ tail_append(new_penalty(hget_integer_ref(HTEG8))); @+break;
case TAG(penalty_kind,1):  @+ {@+tail_append(new_penalty(HTEG8));@+} @+break;
case TAG(penalty_kind,2):  @+{@+int16_t n;@+ HTEG16(n);@+RNG("Penalty",n,-20000,+20000); @+tail_append(new_penalty(n)); @+} @+break;
@

@<\TeX\ declarations@>=
extern pointer new_penalty(int m);
@



\subsection{Mathematics}
I recently was pointed to the problem of accessibility. While the \HINT/ format makes a big contribution
for the visual impaired because font sizes can scale without degrading the layout, it does not support
text to speech conversion in multiple languages. Hence, \HINT/ should be extended to contain language 
information which is present in \TeX\ sources. The math node can be easily modified to provide not only
the switch between text and math, it can also provide language information.  The IETF has specified in BCP 47\cite{rfc5646} a set of language tags. Language tags can be stored in the
definition section and referenced from the content section using a single byte value.



@<GET macros@>=
#define @[HGET_MATH(I,M)@]  \
{ @+scaled w;\
if ((I)&b001) HGET32(w); @+else w=0; \
if ((I)&b100)  tail_append(new_math(w,before)); \
if ((I)&b010)  tail_append(new_math(w,after)); }
@

@<TEG macros@>=
#define @[HTEG_MATH(I,M)@]  \
{ @+scaled w;\
if ((I)&b001) HTEG32(w); @+else w=0; \
if ((I)&b100)  tail_append(new_math(w,before)); \
if ((I)&b010)  tail_append(new_math(w,after)); }
@

@<cases to get content@>=
case TAG(math_kind,b000):  @+tail_append(hget_math_ref(HGET8));@+break;
case TAG(math_kind,b100):  @+HGET_MATH(b100,m);@+break;
case TAG(math_kind,b010):  @+HGET_MATH(b010,m);@+break;
case TAG(math_kind,b101):  @+HGET_MATH(b101,m);@+break;
case TAG(math_kind,b011):  @+HGET_MATH(b011,m);@+break;
@
@<cases to teg content@>=
case TAG(math_kind,b000):  @+tail_append(hget_math_ref(HTEG8));@+break;
case TAG(math_kind,b100):  @+HTEG_MATH(b100,m);@+break;
case TAG(math_kind,b010):  @+HTEG_MATH(b010,m);@+break;
case TAG(math_kind,b101):  @+HTEG_MATH(b101,m);@+break;
case TAG(math_kind,b011):  @+HTEG_MATH(b011,m);@+break;
@

The second parameter of |new_math| is 0 for before and 1 for after the formula.
@<\TeX\ macros@>=
#define before 0
#define after 1
@

@<\TeX\ types@>=
typedef uint8_t small_number; /*this type is self-explanatory*/ 
@

@<\TeX\ declarations@>=
extern pointer new_math(scaled w, small_number s);
@
\subsection{Rules}
\noindent


@<GET macros@>=
#define @[HGET_RULE(I)@]@/\
{ pointer p=new_rule();\
if ((I)&b100) HGET32(height(p)); @+else height(p)=null_flag;\
if ((I)&b010) HGET32(depth(p)); @+else depth(p)=null_flag;\
if ((I)&b001) HGET32(width(p)); @+else width(p)=null_flag;\
tail_append(p);}
@


@<TEG macros@>=
#define @[HTEG_RULE(I)@]@/\
{ pointer p=new_rule();\
if ((I)&b001) HTEG32(width(p)); @+else width(p)=null_flag;\
if ((I)&b010) HTEG32(depth(p)); @+else depth(p)=null_flag;\
if ((I)&b100) HTEG32(height(p)); @+else height(p)=null_flag;\
tail_append(p);}
@

@<cases to get content@>=
case TAG(rule_kind,b000): @+ tail_append(hget_rule_ref(HGET8));	prev_depth=ignore_depth; @+break;
case TAG(rule_kind,b011): @+ HGET_RULE(b011); 	prev_depth=ignore_depth; break;
case TAG(rule_kind,b101): @+ HGET_RULE(b101);	prev_depth=ignore_depth; break;
case TAG(rule_kind,b001): @+ HGET_RULE(b001);	prev_depth=ignore_depth; break;
case TAG(rule_kind,b110): @+ HGET_RULE(b110);	prev_depth=ignore_depth; break;
case TAG(rule_kind,b111): @+ HGET_RULE(b111);	prev_depth=ignore_depth; break;
@

@<cases to teg content@>=
case TAG(rule_kind,b000): @+ tail_append(hget_rule_ref(HTEG8));	prev_depth=ignore_depth; @+break;
case TAG(rule_kind,b011): @+ HTEG_RULE(b011); 	prev_depth=ignore_depth; break;
case TAG(rule_kind,b101): @+ HTEG_RULE(b101);	prev_depth=ignore_depth; break;
case TAG(rule_kind,b001): @+ HTEG_RULE(b001);	prev_depth=ignore_depth; break;
case TAG(rule_kind,b110): @+ HTEG_RULE(b110);	prev_depth=ignore_depth; break;
case TAG(rule_kind,b111): @+ HTEG_RULE(b111);	prev_depth=ignore_depth; break;
@


@<get functions@>=
pointer hget_rule_node(void)
{ @+ pointer p=null;
  @<read the start byte |a|@>@;
  if (KIND(a)==rule_kind) { HGET_RULE(INFO(a));}
  else  QUIT("Rule expected at 0x%x got %s",node_pos,NAME(a));
  @<read and check the end byte |z|@>@;
  return p;
}
@

@<teg auxiliar functions@>=
pointer hteg_rule_node(void)
{ @+ pointer p=null;
  @<read the end byte |z|@>@;
  if (KIND(z)==rule_kind) { HTEG_RULE(INFO(z));}
  else  QUIT("Rule expected at 0x%x got %s",node_pos,NAME(z));
  @<read and check the start byte |a|@>@;
  return p;
}
@

@<\TeX\ macros@>=
#define null_flag	-010000000000 /*$-2^{30}$, signifies a missing item*/
#define prev_depth aux.sc /*the name of |aux| in vertical mode*/
#define ignore_depth	-65536000 /*|prev_depth| value that is ignored*/
@



@<\TeX\ macros@>=
#ifdef @!DEBUG
#define incr_dyn_used @[(dyn_used++)@]
#define decr_dyn_used @[(dyn_used--)@]
#else
#define incr_dyn_used
#define decr_dyn_used
#endif
#define width_offset 1
#define depth_offset 2
#define height_offset 3
#define sc i  /* really not nice but \TeX\ uses the |i| field for scaled values*/
#define width(X) mem[X+width_offset].i
#define depth(X) mem[X+depth_offset].i
#define height(X) mem[X+height_offset].i


@

\subsection{Glue}
\noindent

@<GET macros@>=
#define @[HGET_GLUE(I)@] @/\
  p= get_node(glue_spec_size); \
  if(I==b111) width(p)=hget_xdimen_node(); \
  else {@+ width(p)=0; @+if((I)&b100) HGET32(width(p));@+} \
  if((I)&b010) HGET_STRETCH(stretch(p),stretch_order(p))@; else stretch(p)=0, stretch_order(p)=normal;\
  if((I)&b001) HGET_STRETCH(shrink(p),shrink_order(p))@; else shrink(p)=0, shrink_order(p)=normal;
@

@<TEG macros@>=
#define @[HTEG_GLUE(I)@] @/\
  p= get_node(glue_spec_size); \
  if((I)&b001) HTEG_STRETCH(shrink(p),shrink_order(p))@; else shrink(p)=0, shrink_order(p)=normal;\
  if((I)&b010) HTEG_STRETCH(stretch(p),stretch_order(p))@; else stretch(p)=0, stretch_order(p)=normal;\
  if(I==b111) width(p)=hteg_xdimen_node(); \
  else {@+ width(p)=0; @+if((I)&b100) HTEG32(width(p));@+} 
@


@<cases to get content@>=
case TAG(glue_kind,b000): @+tail_append(new_glue(hget_glue_ref(HGET8)));@+  break;
case TAG(glue_kind,b001): {@+pointer p;@+HGET_GLUE(b001);@+  tail_append(new_glue(p));@+}@+break;
case TAG(glue_kind,b010): {@+pointer p;@+HGET_GLUE(b010);@+  tail_append(new_glue(p));@+}@+break;
case TAG(glue_kind,b011): {@+pointer p;@+HGET_GLUE(b011);@+  tail_append(new_glue(p));@+}@+break;
case TAG(glue_kind,b100): {@+pointer p;@+HGET_GLUE(b100);@+  tail_append(new_glue(p));@+}@+break;
case TAG(glue_kind,b101): {@+pointer p;@+HGET_GLUE(b101);@+  tail_append(new_glue(p));@+}@+break;
case TAG(glue_kind,b110): {@+pointer p;@+HGET_GLUE(b110);@+  tail_append(new_glue(p));@+}@+break;
case TAG(glue_kind,b111): {@+pointer p;@+HGET_GLUE(b111);@+  tail_append(new_glue(p));@+}@+break;
@


@<cases to teg content@>=
case TAG(glue_kind,b000): @+tail_append(new_glue(hget_glue_ref(HTEG8)));@+  break;
case TAG(glue_kind,b001): {@+pointer p;@+HTEG_GLUE(b001);@+  tail_append(new_glue(p));@+}@+break;
case TAG(glue_kind,b010): {@+pointer p;@+HTEG_GLUE(b010);@+  tail_append(new_glue(p));@+}@+break;
case TAG(glue_kind,b011): {@+pointer p;@+HTEG_GLUE(b011);@+  tail_append(new_glue(p));@+}@+break;
case TAG(glue_kind,b100): {@+pointer p;@+HTEG_GLUE(b100);@+  tail_append(new_glue(p));@+}@+break;
case TAG(glue_kind,b101): {@+pointer p;@+HTEG_GLUE(b101);@+  tail_append(new_glue(p));@+}@+break;
case TAG(glue_kind,b110): {@+pointer p;@+HTEG_GLUE(b110);@+  tail_append(new_glue(p));@+}@+break;
case TAG(glue_kind,b111): {@+pointer p;@+HTEG_GLUE(b111);@+  tail_append(new_glue(p));@+}@+break;
@


We used the following definitions:
@<\TeX\ macros@>=
#define glue_order(X)	subtype(X+list_offset) /*applicable order of infinity*/ 
#define glue_sign(X)	type(X+list_offset) /*stretching or shrinking*/ 
#define glue_spec_size 4
#define normal	0 /*the most common case when several cases are named*/ 
#define stretching	1 /*glue setting applies to the stretch components*/ 
#define shrinking	2 /*glue setting applies to the shrink components*/ 
@


@<\TeX\ types@>=
typedef uint8_t glue_ord; /*infinity to the 0, 1, 2, or 3 power*/ 
typedef float32_t @!glue_ratio; /*one-word representation of a glue expansion factor*/ 
@

@<get functions@>=
pointer hget_glue_spec(void)
{ @+pointer p=null;
  uint8_t a,z; /* the start and the end byte*/
  if (hpos>=hend) return null;
  if (KIND(*hpos)!=glue_kind) return null;
  node_pos=hpos-hstart;
  HGETTAG(a);
  if (INFO(a)==b000) p=hget_glue_ref(HGET8);
  else
  { @+HGET_GLUE(INFO(a));@+}
  @<read and check the end byte |z|@>@;
  return p;
}


pointer hget_glue_node(void)
{ @+pointer p=hget_glue_spec();
  if (p!=null) p=new_glue(p);
  return p;
}
@

@<teg auxiliar functions@>=
pointer hteg_glue_spec(void)
{ @+pointer p=null;
  uint8_t a,z; /* the start and the end byte*/
  if (hpos<=hstart) return null;
  if (KIND(*(hpos-1))!=glue_kind) return null;
  z=HTEG8,DBGTAG(z,hpos);
  if (INFO(z)==b000) p=hget_glue_ref(HTEG8);
  else
  { @+HTEG_GLUE(INFO(z));@+}
  @<read and check the start byte |a|@>@;
  return p;
}


pointer hteg_glue_node(void)
{ @+pointer p=hteg_glue_spec();
  if (p!=null) p=new_glue(p);
  return p;
}
@





@<\TeX\ macros@>=
#define glue_spec_size 4

#define type(X) mem[X].hh.b0
#define subtype(X) mem[X].hh.b1 

#define stretch(X) mem[X+2].i
#define shrink(X) mem[X+3].i
#define stretch_order type
#define shrink_order subtype
@

@<\TeX\ declarations@>=
extern pointer new_glue(pointer q);
extern pointer get_node(int s);
extern pointer avail;
extern pointer get_avail(void);
@

\subsection{Lists}
Nodes are recursive data structures because nodes may contain lists of other nodes.
To construct such lists we usualy just add one node at a time; but there are exceptions.
For example, if we find a paragraph node, we first read the list of nodes
that makes up the paragraphs content before we call the line breaking routine.
(Note that the content list might contain again paragraph nodes.)

The line breaking routine then splits the content in to a sequence of horizontal boxes, the lines,
and glue nodes, the baseline skips. Therefore we need a convenient way manage
the construction of lists and to add boxes to the ``current list''.

For now, we use \TeX's features:


@<GET macros@>=
#define @[IS_LIST(X)@]  (KIND(X)==list_kind || KIND(X)==adjust_kind || @/\
        KIND(X)==text_kind  ||@| KIND(X)==param_kind)
@
@<TEG macros@>=
#define @[IS_LIST(X)@]  (KIND(X)==list_kind || KIND(X)==adjust_kind || @/\
        KIND(X)==text_kind  ||@| KIND(X)==param_kind)
@

@<get functions@>=
void hget_size_boundary(info_t info)
{ @+uint32_t n;
  if (info<2) return;
  n=HGET8;
  if (n-1!=0x100-info) QUIT(@["Size boundary byte 0x%x with info value %d at " SIZE_F@],
                            n, info,hpos-hstart-1);
}

uint32_t hget_list_size(info_t info)
{ @+uint32_t n;  
  if (info==1) return 0;
  else if (info==2) n=HGET8;
  else if (info==3) HGET16(n);
  else if (info==4) HGET24(n);
  else if (info==5) HGET32(n);
  else QUIT("List info %d must be 1, 2, 3, 4, or 5",info);
  return n;
} 

pointer hget_node_list(uint32_t s)
{ @+ uint8_t *list_end=hpos+s;
  pointer p;
  push_nest();
    needs_bs=false;
  while (hpos<list_end)
    hget_content();
  if (needs_bs) 
    QUIT("Unexpected trailing baseline node");
  p=link(head);
  pop_nest();
  return p;  
}

pointer hget_text_list(uint32_t s)
{@+  QUIT("Text not implemented");
  return null;
}

pointer hget_list(void)
{ @+if (!IS_LIST(*hpos)) return null;
  else
  {@+pointer p;
    uint32_t s, t;
    @<read the start byte |a|@>@;
    s=hget_list_size(INFO(a)); 
    hget_size_boundary(INFO(a));
    if (KIND(a)==list_kind)
      p=hget_node_list(s);
    else if (KIND(a)==text_kind)
      p=hget_text_list(s);
    hget_size_boundary(INFO(a));
    t=hget_list_size(INFO(a)); 
    if (t!=s) 
     QUIT("List sizes at 0x%x and " SIZE_F " do not match 0x%x != 0x%x",node_pos+1,hpos-hstart-s-1,s,t);
    @<read and check the end byte |z|@>@;
   return p;
  }
}
@

When we need to parse a list backwards that is part of a node. We still want the resulting list
in forward order. The simplest way to do this, is moving to the beginning of the list and then
parsing it in forward order.

@<teg auxiliar functions@>=
#if 0
void hteg_size_boundary(info_t info)
{ @+uint32_t n;
  if (info<2) return;
  n=HTEG8;
  if (n-1!=0x100-info) QUIT(@["Size boundary byte 0x%x with info value %d at " SIZE_F@],
                            n, info,hpos-hstart);
}
#endif

uint32_t hteg_list_size(info_t info)
{ @+uint32_t n;  
  if (info==1) return 0;
  else if (info==2) n=HTEG8;
  else if (info==3) HTEG16(n);
  else if (info==4) HTEG24(n);
  else if (info==5) HTEG32(n);
  else QUIT("List info %d must be 1, 2, 3, 4, or 5",info);
  return n;
} 

#if 0
pointer hteg_node_list(uint32_t s)
{ @+ uint8_t *list_start=hpos-s;
  pointer p;
  push_nest();
  needs_bs=false;
  while (hpos>list_start)
    hteg_content();
  if (needs_bs) 
    QUIT("Unexpected trailing baseline node");
  p=link(head);
  pop_nest();
  return p;  
}
#endif

void hskip_list()
{ uint8_t z; 
  uint32_t s;
  if (!IS_LIST(*(hpos-1))) return;
  z=HTEG8;
  s=hteg_list_size(INFO(z)); 
  hpos = hpos - (1+ s + 1+ (INFO(z)-1) +1); /*boundary tag+s+boundary tag+size+tag*/
}

pointer hteg_list(void)
{ uint8_t *list_start;
  pointer p;
  hskip_list();
  list_start=hpos;
  p=hget_list();
  hpos=list_start;
  return p;
}
@

\subsection{Parameter Lists}

We have defined a function to read parameter lists in section~\secref{getparamlist}.
Here we define the function that reads parameter lists backwards. Having seen how to read regular lists backwards,
the function should contain no surprises. We start with a simple functions to read an integer definition.


@<teg auxiliar functions@>=
#if 0
static int32_t hteg_integer_def(uint8_t z)
{ if (INFO(z)==1) { int8_t n=HTEG8; return n;}
  else  if (INFO(z)==2) { int16_t n; HTEG16(n); return n;}
  else if (INFO(z)==4) {int32_t n; HTEG32(n); return n;}
  else TAGERR(z);
  return 0;
}

static param_def_t *hteg_param_list(uint8_t z)
{ uint32_t s,t;
  param_def_t *p=NULL;
  uint8_t *list_start,*list_end;
  list_end=hpos;
  s=hteg_list_size(INFO(z)); 
  hteg_size_boundary(INFO(z));
  list_start=hpos-s;
  if (list_start<=hstart) 
    QUIT("list start before stream start\n"); 
  while (list_start < hpos)
  { @+param_def_t *r; param_t *q;
    @<read the end byte |z|@>@;
    ALLOCATE(r,1,param_def_t);
    q=&(r->p);
    q->k=KIND(z);
    if (KIND(z)==int_kind) q->i=hteg_integer_def(a);
    else if (KIND(a)==dimen_kind) HTEG32(q->d);
    else if (KIND(a)==glue_kind) { pointer p;  HTEG_GLUE(INFO(z)); q->g=p;}
    else TAGERR(a);
    q->n=HTEG8;
    DBG(dbgtags,"Defining %s %d\n", definition_name[KIND(z)],q->n);
    @<read and check the start byte |a|@>@;
    r->next=p;
    p=r;
  }
  hteg_size_boundary(INFO(z));
  t=hteg_list_size(INFO(z)); 
  if (t!=s) 
    QUIT("List sizes at " SIZE_F " and " SIZE_F " do not match 0x%x != 0x%x",list_start-hstart,list_end-hstart,s,t);
  return p;
}
#endif

static param_def_t *hteg_param_list_node(void)
{ param_def_t *p;
  uint8_t *list_start;
  hskip_list();
  list_start=hpos;
  p=hget_param_list_node();
  hpos=list_start;
  return p;
}
@


\subsection{Texts}
not yet implemented.

\subsection{Boxes}
\noindent
@<GET macros@>=
#define @[HGET_BOX(I)@] \
pointer p=new_null_box();\
HGET32(height(p));\
if ((I)&b001) HGET32(depth(p));\ 
HGET32(width(p));\
if ((I)&b010) HGET32(shift_amount(p));\ 
if ((I)&b100) @/{@+uint8_t x; glue_set(p)=hget_float32();@/\
  x=HGET8; @+ glue_order(p)=x&0xF; @+glue_sign(p)=x>>4;@+ }\
list_ptr(p)=hget_list();
@

@<TEG macros@>=
#define @[HTEG_BOX(I)@] \
pointer p=new_null_box();\
list_ptr(p)=hteg_list();\
if ((I)&b100) @/{@+uint8_t x=HTEG8;@+ glue_order(p)=x&0xF; @+glue_sign(p)=x>>4; glue_set(p)=hteg_float32(); }\
if ((I)&b010) HTEG32(shift_amount(p));\ 
HTEG32(width(p));\
if ((I)&b001) HTEG32(depth(p));\ 
HTEG32(height(p));
@



@<get declarations@>=
static float32_t hget_float32(void);
@


@<cases to get content@>=
case TAG(hbox_kind,b000): @+{@+HGET_BOX(b000);@+happend_to_vlist(p);@+}@+ break;
case TAG(hbox_kind,b001): @+{@+HGET_BOX(b001);@+happend_to_vlist(p);@+}@+ break;
case TAG(hbox_kind,b010): @+{@+HGET_BOX(b010);@+happend_to_vlist(p);@+}@+ break;
case TAG(hbox_kind,b011): @+{@+HGET_BOX(b011);@+happend_to_vlist(p);@+}@+ break;
case TAG(hbox_kind,b100): @+{@+HGET_BOX(b100);@+happend_to_vlist(p);@+}@+ break;
case TAG(hbox_kind,b101): @+{@+HGET_BOX(b101);@+happend_to_vlist(p);@+}@+ break;
case TAG(hbox_kind,b110): @+{@+HGET_BOX(b110);@+happend_to_vlist(p);@+}@+ break;
case TAG(hbox_kind,b111): @+{@+HGET_BOX(b111);@+happend_to_vlist(p);@+}@+ break;
case TAG(vbox_kind,b000): @+{HGET_BOX(b000);@+type(p)=vlist_node;@+happend_to_vlist(p);@+} @+ break;
case TAG(vbox_kind,b001): @+{HGET_BOX(b001);@+type(p)=vlist_node;@+happend_to_vlist(p);@+} @+ break;
case TAG(vbox_kind,b010): @+{HGET_BOX(b010);@+type(p)=vlist_node;@+happend_to_vlist(p);@+} @+ break;
case TAG(vbox_kind,b011): @+{HGET_BOX(b011);@+type(p)=vlist_node;@+happend_to_vlist(p);@+} @+ break;
case TAG(vbox_kind,b100): @+{HGET_BOX(b100);@+type(p)=vlist_node;@+happend_to_vlist(p);@+} @+ break;
case TAG(vbox_kind,b101): @+{HGET_BOX(b101);@+type(p)=vlist_node;@+happend_to_vlist(p);@+} @+ break;
case TAG(vbox_kind,b110): @+{HGET_BOX(b110);@+type(p)=vlist_node;@+happend_to_vlist(p);@+} @+ break;
case TAG(vbox_kind,b111): @+{HGET_BOX(b111);@+type(p)=vlist_node;@+happend_to_vlist(p);@+} @+ break;
@

@<cases to teg content@>=
case TAG(hbox_kind,b000): @+{@+HTEG_BOX(b000);@+happend_to_vlist(p);@+}@+ break;
case TAG(hbox_kind,b001): @+{@+HTEG_BOX(b001);@+happend_to_vlist(p);@+}@+ break;
case TAG(hbox_kind,b010): @+{@+HTEG_BOX(b010);@+happend_to_vlist(p);@+}@+ break;
case TAG(hbox_kind,b011): @+{@+HTEG_BOX(b011);@+happend_to_vlist(p);@+}@+ break;
case TAG(hbox_kind,b100): @+{@+HTEG_BOX(b100);@+happend_to_vlist(p);@+}@+ break;
case TAG(hbox_kind,b101): @+{@+HTEG_BOX(b101);@+happend_to_vlist(p);@+}@+ break;
case TAG(hbox_kind,b110): @+{@+HTEG_BOX(b110);@+happend_to_vlist(p);@+}@+ break;
case TAG(hbox_kind,b111): @+{@+HTEG_BOX(b111);@+happend_to_vlist(p);@+}@+ break;
case TAG(vbox_kind,b000): @+{HTEG_BOX(b000);@+type(p)=vlist_node;@+happend_to_vlist(p);@+} @+ break;
case TAG(vbox_kind,b001): @+{HTEG_BOX(b001);@+type(p)=vlist_node;@+happend_to_vlist(p);@+} @+ break;
case TAG(vbox_kind,b010): @+{HTEG_BOX(b010);@+type(p)=vlist_node;@+happend_to_vlist(p);@+} @+ break;
case TAG(vbox_kind,b011): @+{HTEG_BOX(b011);@+type(p)=vlist_node;@+happend_to_vlist(p);@+} @+ break;
case TAG(vbox_kind,b100): @+{HTEG_BOX(b100);@+type(p)=vlist_node;@+happend_to_vlist(p);@+} @+ break;
case TAG(vbox_kind,b101): @+{HTEG_BOX(b101);@+type(p)=vlist_node;@+happend_to_vlist(p);@+} @+ break;
case TAG(vbox_kind,b110): @+{HTEG_BOX(b110);@+type(p)=vlist_node;@+happend_to_vlist(p);@+} @+ break;
case TAG(vbox_kind,b111): @+{HTEG_BOX(b111);@+type(p)=vlist_node;@+happend_to_vlist(p);@+} @+ break;
@

@<get functions@>=
pointer hget_hbox_node(void)
{ @+  @<read the start byte |a|@>@;
   if (KIND(a)!=hbox_kind) QUIT("Hbox expected at 0x%x got %s",node_pos,NAME(a));
   { @+  
    HGET_BOX(INFO(a));@/
    @<read and check the end byte |z|@>@;
    return p;
   }
}


pointer hget_vbox_node(void)
{@+
  @<read the start byte |a|@>@;
  if (KIND(a)!=vbox_kind) QUIT("Vbox expected at 0x%x got %s",node_pos,NAME(a));
  {@+
  HGET_BOX(INFO(a));@/
  @<read and check the end byte |z|@>@;
  type(p)=vlist_node; 
  return p;
}
}
@

@<teg auxiliar functions@>=
pointer hteg_hbox_node(void)
{ @+  @<read the end byte |z|@>@;
   if (KIND(z)!=hbox_kind) QUIT("Hbox expected at 0x%x got %s",node_pos,NAME(z));
   { @+  
    HTEG_BOX(INFO(z));@/
    @<read and check the start byte |a|@>@;
    return p;
   }
}
pointer hteg_vbox_node(void)
{ @+  @<read the end byte |z|@>@;
   if (KIND(z)!=vbox_kind) QUIT("Vbox expected at 0x%x got %s",node_pos,NAME(z));
   { @+  
    HTEG_BOX(INFO(z));@/
    @<read and check the start byte |a|@>@;
   type(p)=vlist_node; 
   return p;
   }
}

@

@<\TeX\ macros@>=
#define vlist_node 1 

#define link(X) mem[X].hh.rh /*the |link| field of a memory word*/ 

#define shift_amount(X) mem[X+4].i
#define list_offset 5
#define list_ptr(X) link(X+list_offset) 
#define glue_offset 6
#define glue_set(X) mem[X+glue_offset].gr
#define glue_order(X) subtype(X+list_offset) 
#define glue_sign(X) type(X+list_offset) 
@

@<\TeX\ declarations@>=
extern pointer new_null_box(void);
@

\subsection{Extended Boxes}
We start with boxes that just need their glue to be set.

@<GET macros@>=
#define @[HGET_SET(I)@] @/\
 scaled x, st, sh; @+uint8_t sto, sho; \
 p=new_null_box();\
 if ((I)&b100) x= hget_xdimen_node();  else x=hget_xdimen_ref(HGET8);\
 HGET32(height(p)); if ((I)&b001) HGET32(depth(p)); HGET32(width(p));\
 if ((I)&b010) HGET32(shift_amount(p));\
 HGET_STRETCH(st,sto); @+  HGET_STRETCH(sh,sho);@/\
 list_ptr(p)=hget_list();
@

@<TEG macros@>=
#define @[HTEG_SET(I)@] @/\
  scaled x, st, sh; @+uint8_t sto, sho; \
  p=new_null_box();\
  list_ptr(p)=hteg_list();\
  HTEG_STRETCH(sh,sho);@+HTEG_STRETCH(st,sto);\
  if ((I)&b010) HTEG32(shift_amount(p)); \
  HTEG32(width(p));@+if ((I)&b001) HTEG32(depth(p));@+HTEG32(height(p)); \
  if ((I)&b100) x=hteg_xdimen_node(); else x=hget_xdimen_ref(HTEG8);
@


@<cases to get content@>=
case TAG(hset_kind,b000): @+{@+pointer p;HGET_SET(b000); @+hset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+break;
case TAG(hset_kind,b001): @+{@+pointer p;HGET_SET(b001); @+hset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;
case TAG(hset_kind,b010): @+{@+pointer p;HGET_SET(b010); @+hset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;
case TAG(hset_kind,b011): @+{@+pointer p;HGET_SET(b011); @+hset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;
case TAG(hset_kind,b100): @+{@+pointer p;HGET_SET(b100); @+hset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;
case TAG(hset_kind,b101): @+{@+pointer p;HGET_SET(b101); @+hset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;
case TAG(hset_kind,b110): @+{@+pointer p;HGET_SET(b110); @+hset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;
case TAG(hset_kind,b111): @+{@+pointer p;HGET_SET(b111); @+hset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;@#

case TAG(vset_kind,b000): @+{@+pointer p;HGET_SET(b000); @+vset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;
case TAG(vset_kind,b001): @+{@+pointer p;HGET_SET(b001); @+vset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;
case TAG(vset_kind,b010): @+{@+pointer p;HGET_SET(b010); @+vset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;
case TAG(vset_kind,b011): @+{@+pointer p;HGET_SET(b011); @+vset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;
case TAG(vset_kind,b100): @+{@+pointer p;HGET_SET(b100); @+vset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;
case TAG(vset_kind,b101): @+{@+pointer p;HGET_SET(b101); @+vset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;
case TAG(vset_kind,b110): @+{@+pointer p;HGET_SET(b110); @+vset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;
case TAG(vset_kind,b111): @+{@+pointer p;HGET_SET(b111); @+vset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;
@


@<cases to teg content@>=
case TAG(hset_kind,b000): @+{@+pointer p;HTEG_SET(b000); @+hset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+break;
case TAG(hset_kind,b001): @+{@+pointer p;HTEG_SET(b001); @+hset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;
case TAG(hset_kind,b010): @+{@+pointer p;HTEG_SET(b010); @+hset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;
case TAG(hset_kind,b011): @+{@+pointer p;HTEG_SET(b011); @+hset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;
case TAG(hset_kind,b100): @+{@+pointer p;HTEG_SET(b100); @+hset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;
case TAG(hset_kind,b101): @+{@+pointer p;HTEG_SET(b101); @+hset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;
case TAG(hset_kind,b110): @+{@+pointer p;HTEG_SET(b110); @+hset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;
case TAG(hset_kind,b111): @+{@+pointer p;HTEG_SET(b111); @+hset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;@#

case TAG(vset_kind,b000): @+{@+pointer p;HTEG_SET(b000); @+vset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;
case TAG(vset_kind,b001): @+{@+pointer p;HTEG_SET(b001); @+vset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;
case TAG(vset_kind,b010): @+{@+pointer p;HTEG_SET(b010); @+vset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;
case TAG(vset_kind,b011): @+{@+pointer p;HTEG_SET(b011); @+vset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;
case TAG(vset_kind,b100): @+{@+pointer p;HTEG_SET(b100); @+vset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;
case TAG(vset_kind,b101): @+{@+pointer p;HTEG_SET(b101); @+vset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;
case TAG(vset_kind,b110): @+{@+pointer p;HTEG_SET(b110); @+vset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;
case TAG(vset_kind,b111): @+{@+pointer p;HTEG_SET(b111); @+vset(p,sto,st,sho,sh,x);@+happend_to_vlist(p);@+}@+ break;
@

The function |hset| computes |glue_set(p)| of a hlist node
depending on the available stretch, shrink, and the target width |x|;
the function |vset| does the equivalent for vlist nodes.
@<\TeX\ functions@>=
void hset(pointer p,@/
          uint8_t sto, scaled st,uint8_t sho,scaled sh, scaled w)
{ @+scaled x;
  x =width(p); /* natural width */ 
  width(p)=w; /* target width */

  x = w-x; /*now |x| is the excess to be made up*/ 
  if (x==0)@/
    { @+glue_sign(p)= normal; glue_order(p)= normal;
      glue_set(p)=0.0;@+
    }
  else if (x>0)
  { glue_order(p)= sto; glue_sign(p)= stretching;
    if (st!=0)
	  glue_set(p)= (float32_t)(x/(double)st);
    else
	{ @+glue_sign(p)= normal;
	  glue_set(p)=0.0;@+
	}
  }
  else 
  { glue_order(p)= sho; glue_sign(p)= shrinking;
    if (sh!=0) 
      glue_set(p)= (float32_t)((-x)/(double)sh);
    else
	{ @+glue_sign(p)= normal;
	  glue_set(p)=0.0;@+
	}
	if((sh<-x)&&(sho==normal)&&(list_ptr(p)!=null))
      glue_set(p)=1.0;
  }
}




void vset(pointer p, uint8_t sto, scaled st,
					uint8_t sho,scaled sh, scaled h)
{ @+scaled x;
  type(p)=vlist_node;
  x =height(p); /* natural height adjusted such that depth <= limit */ 
  height(p)=h;
  x = h-x; /*now |x| is the excess to be made up*/ 
  if (x==0)
    { glue_sign(p)= normal; glue_order(p)= normal;
      glue_set(p)=0.0;
    }
  else if (x>0)
  { glue_order(p)= sto; glue_sign(p)= stretching;
    if (st!=0)
	  glue_set(p)= (float32_t)(x/(double)st);
    else
	{ @+glue_sign(p)= normal;
	  glue_set(p)=0.0;@+
	}
  }
  else 
  { glue_order(p)= sho; glue_sign(p)= shrinking;
    if (sh!=0) 
      glue_set(p)= (float32_t)((-x)/(double)sh);
    else
	{ @+glue_sign(p)= normal;
	  glue_set(p)=0.0;@+
	}
  }
}
@

If the natural dimensions of a box are not known, we
need to traverse the content list before we can set the glue.

@<GET macros@>=
#define @[HGET_PACK(I)@] @/\
 pointer p; scaled x, d; @+ uint8_t m; \
 if ((I)&b100) x= hget_xdimen_node();  else x=hget_xdimen_ref(HGET8);\
 if ((I)&b010) m=additional; else m=exactly; \
 if ((I)&b001) HGET32(d); else d= MAX_DIMEN; \
 p=hget_list();
@

@<TEG macros@>=
#define @[HTEG_PACK(I)@] @/\
 pointer p; scaled x, d; @+ uint8_t m; \
 p=hteg_list();\
 if ((I)&b001)  @+HTEG32(d); else d= MAX_DIMEN; \
 if ((I)&b010) m=additional; else m=exactly; \
 if ((I)&b100) x=hteg_xdimen_node();@+  else x=hget_xdimen_ref(HTEG8);
@

@<cases to get content@>=
case TAG(hpack_kind,b000): @+{@+HGET_PACK(b000);@+ p=hpack(p,x,m);@+happend_to_vlist(p);@+} @+ break;
case TAG(hpack_kind,b010): @+{@+HGET_PACK(b010);@+ p=hpack(p,x,m);@+happend_to_vlist(p);@+} @+ break;
case TAG(hpack_kind,b100): @+{@+HGET_PACK(b100);@+ p=hpack(p,x,m);@+happend_to_vlist(p);@+} @+ break;
case TAG(hpack_kind,b110): @+{@+HGET_PACK(b110);@+ p=hpack(p,x,m);@+happend_to_vlist(p);@+} @+ break;@#

case TAG(vpack_kind,b000): @+{@+HGET_PACK(b000);@+ p=vpackage(p,x,m,d);@+happend_to_vlist(p); @+} @+ break;
case TAG(vpack_kind,b010): @+{@+HGET_PACK(b010);@+ p=vpackage(p,x,m,d);@+happend_to_vlist(p); @+} @+ break;
case TAG(vpack_kind,b100): @+{@+HGET_PACK(b100);@+ p=vpackage(p,x,m,d);@+happend_to_vlist(p); @+} @+ break;
case TAG(vpack_kind,b110): @+{@+HGET_PACK(b110);@+ p=vpackage(p,x,m,d);@+happend_to_vlist(p); @+} @+ break;
case TAG(vpack_kind,b001): @+{@+HGET_PACK(b001);@+ p=vpackage(p,x,m,d);@+happend_to_vlist(p); @+} @+ break;
case TAG(vpack_kind,b011): @+{@+HGET_PACK(b011);@+ p=vpackage(p,x,m,d);@+happend_to_vlist(p); @+} @+ break;
case TAG(vpack_kind,b101): @+{@+HGET_PACK(b101);@+ p=vpackage(p,x,m,d);@+happend_to_vlist(p); @+} @+ break;
case TAG(vpack_kind,b111): @+{@+HGET_PACK(b111);@+ p=vpackage(p,x,m,d);@+happend_to_vlist(p); @+} @+ break;
@
@<cases to teg content@>=
case TAG(hpack_kind,b000): @+{@+HTEG_PACK(b000);@+ p=hpack(p,x,m);@+happend_to_vlist(p);@+} @+ break;
case TAG(hpack_kind,b010): @+{@+HTEG_PACK(b010);@+ p=hpack(p,x,m);@+happend_to_vlist(p);@+} @+ break;
case TAG(hpack_kind,b100): @+{@+HTEG_PACK(b100);@+ p=hpack(p,x,m);@+happend_to_vlist(p);@+} @+ break;
case TAG(hpack_kind,b110): @+{@+HTEG_PACK(b110);@+ p=hpack(p,x,m);@+happend_to_vlist(p);@+} @+ break;@#

case TAG(vpack_kind,b000): @+{@+HTEG_PACK(b000);@+ p=vpackage(p,x,m,d);@+happend_to_vlist(p); @+} @+ break;
case TAG(vpack_kind,b010): @+{@+HTEG_PACK(b010);@+ p=vpackage(p,x,m,d);@+happend_to_vlist(p); @+} @+ break;
case TAG(vpack_kind,b100): @+{@+HTEG_PACK(b100);@+ p=vpackage(p,x,m,d);@+happend_to_vlist(p); @+} @+ break;
case TAG(vpack_kind,b110): @+{@+HTEG_PACK(b110);@+ p=vpackage(p,x,m,d);@+happend_to_vlist(p); @+} @+ break;
case TAG(vpack_kind,b001): @+{@+HTEG_PACK(b001);@+ p=vpackage(p,x,m,d);@+happend_to_vlist(p); @+} @+ break;
case TAG(vpack_kind,b011): @+{@+HTEG_PACK(b011);@+ p=vpackage(p,x,m,d);@+happend_to_vlist(p); @+} @+ break;
case TAG(vpack_kind,b101): @+{@+HTEG_PACK(b101);@+ p=vpackage(p,x,m,d);@+happend_to_vlist(p); @+} @+ break;
case TAG(vpack_kind,b111): @+{@+HTEG_PACK(b111);@+ p=vpackage(p,x,m,d);@+happend_to_vlist(p); @+} @+ break;
@


@<\TeX\ macros@>=
#define exactly 0
#define additional 1
@

@<\TeX\ declarations@>=
extern pointer hpack(pointer @!p, scaled @!w, small_number @!m);
@

\subsection{Kerns}

@<GET macros@>=
#define @[HGET_KERN(I)@] \
pointer p; @+scaled x; \
if (((I)&b011)==0) x=hget_dimen_ref(HGET8);\
else if (((I)&b011)==1) x=hget_xdimen_ref(HGET8);\
else if (((I)&b011)==2) HGET32(x);\
else if (((I)&b011)==3) x=hget_xdimen_node();\
p=new_kern(x);\
if ((I)&b100) subtype(p)=explicit;\
tail_append(p);
@


@<TEG macros@>=
#define @[HTEG_KERN(I)@] \
pointer p; @+scaled x; \
if (((I)&b011)==0) x=hget_dimen_ref(HTEG8);\
else if (((I)&b011)==1) x=hget_xdimen_ref(HTEG8);\
else if (((I)&b011)==2) HTEG32(x);\
else if (((I)&b011)==3) x=hteg_xdimen_node();\
p=new_kern(x);\
if ((I)&b100) subtype(p)=explicit;\
tail_append(p);
@


@<cases to get content@>=
case TAG(kern_kind,b000): @+  { @+HGET_KERN(b000);@+ } @+break;
case TAG(kern_kind,b001): @+  { @+HGET_KERN(b001);@+ } @+break;
case TAG(kern_kind,b010): @+  { @+HGET_KERN(b010);@+ } @+break;
case TAG(kern_kind,b011): @+  { @+HGET_KERN(b011);@+ } @+break;
case TAG(kern_kind,b100): @+  { @+HGET_KERN(b100);@+ } @+break;
case TAG(kern_kind,b101): @+  { @+HGET_KERN(b101);@+ } @+break;
case TAG(kern_kind,b110): @+  { @+HGET_KERN(b110);@+ } @+break;
case TAG(kern_kind,b111): @+  { @+HGET_KERN(b111);@+ } @+break;
@

@<cases to teg content@>=
case TAG(kern_kind,b000): @+  { @+HTEG_KERN(b000);@+ } @+break;
case TAG(kern_kind,b001): @+  { @+HTEG_KERN(b001);@+ } @+break;
case TAG(kern_kind,b010): @+  { @+HTEG_KERN(b010);@+ } @+break;
case TAG(kern_kind,b011): @+  { @+HTEG_KERN(b011);@+ } @+break;
case TAG(kern_kind,b100): @+  { @+HTEG_KERN(b100);@+ } @+break;
case TAG(kern_kind,b101): @+  { @+HTEG_KERN(b101);@+ } @+break;
case TAG(kern_kind,b110): @+  { @+HTEG_KERN(b110);@+ } @+break;
case TAG(kern_kind,b111): @+  { @+HTEG_KERN(b111);@+ } @+break;
@


@<\TeX\ macros@>=
#define explicit 1
@

@<\TeX\ declarations@>=
extern pointer new_kern(scaled w);
@


\subsection{Leaders}

@<GET macros@>=
#define @[HGET_LEADERS(I)@]@/ \
{@+pointer p=hget_glue_node();@+subtype(p)=a_leaders+((I)&b011)-1;\
if (KIND(*hpos)==rule_kind) leader_ptr(p)=hget_rule_node(); \
else if (KIND(*hpos)==hbox_kind) leader_ptr(p)=hget_hbox_node(); \
else  leader_ptr(p)=hget_vbox_node();\
tail_append(p);}
@

@<TEG macros@>=
#define @[HTEG_LEADERS(I)@]@/ \
{@+pointer p=hteg_glue_node();@+subtype(p)=a_leaders+((I)&b011)-1;\
if (KIND(*(hpos-1))==rule_kind) leader_ptr(p)=hteg_rule_node(); \
else if (KIND(*(hpos-1))==hbox_kind) leader_ptr(p)=hteg_hbox_node(); \
else  leader_ptr(p)=hteg_vbox_node();\
tail_append(p);}
@

@<cases to get content@>=
case TAG(leaders_kind,0):        @+ tail_append(hget_leaders_ref(HGET8)); @+break;
case TAG(leaders_kind,1):        @+ HGET_LEADERS(1); @+break;
case TAG(leaders_kind,2):        @+ HGET_LEADERS(2); @+break;
case TAG(leaders_kind,3):        @+ HGET_LEADERS(3); @+break;
@
@<cases to teg content@>=
case TAG(leaders_kind,0):        @+ tail_append(hget_leaders_ref(HTEG8)); @+break;
case TAG(leaders_kind,1):        @+ HTEG_LEADERS(1); @+break;
case TAG(leaders_kind,2):        @+ HTEG_LEADERS(2); @+break;
case TAG(leaders_kind,3):        @+ HTEG_LEADERS(3); @+break;
@




@<\TeX\ macros@>=
#define a_leaders 100
#define leader_ptr(X) link(X+1) 
@

\subsection{Baseline Skips}

@<GET macros@>=
#define @[HGET_BASELINE(I,B)@] \
  if((I)&b100) (B).bs=hget_glue_spec(); else (B).bs=zero_glue; \
  if((I)&b010) (B).ls=hget_glue_spec(); else (B).ls=zero_glue; \
  if((I)&b001) HGET32((B).lsl); @+else (B).lsl=0; \
@

@<TEG macros@>=
#define @[HTEG_BASELINE(I,B)@] \
  if((I)&b001) HTEG32((B).lsl); @+else B.lsl=0; \
  if((I)&b010) hteg_glue_spec(); else (B).ls=zero_glue; \
  if((I)&b100) hteg_glue_spec(); else (B).bs=zero_glue; 
@



@<cases to get content@>=
case TAG(baseline_kind,b000): @+{@+ hget_baseline_ref(HGET8,&cur_list.bs_field);@+ needs_bs=true;@+ }@+break;
case TAG(baseline_kind,b010): @+{@+ HGET_BASELINE(b010,cur_list.bs_field);@+ needs_bs=true;@+}@+break;
case TAG(baseline_kind,b011): @+{@+ HGET_BASELINE(b011,cur_list.bs_field);@+ needs_bs=true;@+}@+break;
case TAG(baseline_kind,b100): @+{@+ HGET_BASELINE(b100,cur_list.bs_field);@+ needs_bs=true;@+}@+break;
case TAG(baseline_kind,b101): @+{@+ HGET_BASELINE(b101,cur_list.bs_field);@+ needs_bs=true;@+}@+break;
case TAG(baseline_kind,b110): @+{@+ HGET_BASELINE(b110,cur_list.bs_field);@+ needs_bs=true;@+}@+break;
case TAG(baseline_kind,b111): @+{@+ HGET_BASELINE(b111,cur_list.bs_field);@+ needs_bs=true;@+}@+break;
@

@<cases to teg content@>=
case TAG(baseline_kind,b000): @+{@+ hget_baseline_ref(HTEG8,&cur_list.bs_field);@+ needs_bs=true;@+ }@+break;
case TAG(baseline_kind,b010): @+{@+ HTEG_BASELINE(b010,cur_list.bs_field);@+ needs_bs=true;@+}@+break;
case TAG(baseline_kind,b011): @+{@+ HTEG_BASELINE(b011,cur_list.bs_field);@+ needs_bs=true;@+}@+break;
case TAG(baseline_kind,b100): @+{@+ HTEG_BASELINE(b100,cur_list.bs_field);@+ needs_bs=true;@+}@+break;
case TAG(baseline_kind,b101): @+{@+ HTEG_BASELINE(b101,cur_list.bs_field);@+ needs_bs=true;@+}@+break;
case TAG(baseline_kind,b110): @+{@+ HTEG_BASELINE(b110,cur_list.bs_field);@+ needs_bs=true;@+}@+break;
case TAG(baseline_kind,b111): @+{@+ HTEG_BASELINE(b111,cur_list.bs_field);@+ needs_bs=true;@+}@+break;
@

@<\TeX\ macros@>=
#define zero_glue 0
@

\subsection{Ligatures}
We ignore the replacement characters because we do not need them for the display.
@<GET macros@>=
#define @[HGET_LIG(I)@] @/\
{@+pointer p;@+uint8_t f;@+ uint32_t c; @+uint8_t s,*t;\
f=HGET8;\
if ((I)==7) s=HGET8;@+else s=(I);\
t=hpos+s; c=hget_utf8(); hpos=t;\
if ((I)==7)@/\
{ @+uint8_t t;@+ t=HGET8; \
  if(t!=s) @/\
  QUIT("Sizes in ligature don't match %d!=%d",s,t);}\
p=new_ligature(f, c, null); tail_append(p); \
}
@

@<TEG macros@>=
#define @[HTEG_LIG(I)@] @/\
{@+pointer p;@+uint8_t f;@+ uint32_t c; @+uint8_t s,*t;\
if ((I)==7) @+s=HTEG8; @+else s=(I);\
t=hpos-s; hpos=t; c=hget_utf8(); hpos=t;\
if ((I)==7) { uint8_t n;@+ n=HTEG8;\
  if(n!=s)   QUIT("Sizes in ligature don't match %d!=%d",s,n);}\
f=HTEG8;\
p=new_ligature(f, c, null); tail_append(p); \
}
@


@<cases to get content@>=
case TAG(ligature_kind,0):@+ tail_append(hget_ligature_ref(HGET8)); @+break;
case TAG(ligature_kind,1):@+ HGET_LIG(1); @+break;
case TAG(ligature_kind,2):@+ HGET_LIG(2); @+break;
case TAG(ligature_kind,3):@+ HGET_LIG(3); @+break;
case TAG(ligature_kind,4):@+ HGET_LIG(4); @+break;
case TAG(ligature_kind,5):@+ HGET_LIG(5); @+break;
case TAG(ligature_kind,6):@+ HGET_LIG(6); @+break;
case TAG(ligature_kind,7):@+ HGET_LIG(7); @+break;
@

@<cases to teg content@>=
case TAG(ligature_kind,0):@+ tail_append(hget_ligature_ref(HTEG8)); @+break;
case TAG(ligature_kind,1):@+ HTEG_LIG(1); @+break;
case TAG(ligature_kind,2):@+ HTEG_LIG(2); @+break;
case TAG(ligature_kind,3):@+ HTEG_LIG(3); @+break;
case TAG(ligature_kind,4):@+ HTEG_LIG(4); @+break;
case TAG(ligature_kind,5):@+ HTEG_LIG(5); @+break;
case TAG(ligature_kind,6):@+ HTEG_LIG(6); @+break;
case TAG(ligature_kind,7):@+ HTEG_LIG(7); @+break;
@

@<\TeX\ declarations@>=
extern pointer new_ligature(uint8_t f, uint8_t c,pointer q);
@

\subsection{Hyphenation}
The high bit in the replace count indicates an explicit hyphen. 
If it is zero we set the |auto_disc| flag in the 
new node.

@<GET macros@>=
#define @[HGET_HYPHEN(I)@]\
  pointer p=new_disc(); \
  if ((I)&b100) pre_break(p)=hget_list(); \
  if ((I)&b010) post_break(p)=hget_list(); \
  if ((I)&b001) {uint8_t r; @+r=HGET8; set_replace_count(p,r); \
                 if ((r&0x80)==0) set_auto_disc(p); @+}\
  else  set_auto_disc(p);
@

@<TEG macros@>=
#define @[HTEG_HYPHEN(I)@]\
  pointer p=new_disc(); \
  if ((I)&b001) {uint8_t r; @+r=HTEG8; set_replace_count(p,r); \
                 if ((r&0x80)==0) set_auto_disc(p); @+}\
  else  set_auto_disc(p);\
  if ((I)&b010) post_break(p)=hteg_list(); \
  if ((I)&b100) pre_break(p)=hteg_list(); 
@



@<cases to get content@>=
case TAG(hyphen_kind,b000): @+tail_append(hget_hyphen_ref(HGET8));  @+break;
case TAG(hyphen_kind,b001): @+{@+HGET_HYPHEN(b001);@+tail_append(p);@+} @+break;
case TAG(hyphen_kind,b010): @+{@+HGET_HYPHEN(b010);@+tail_append(p);@+} @+break;
case TAG(hyphen_kind,b011): @+{@+HGET_HYPHEN(b011);@+tail_append(p);@+} @+break;
case TAG(hyphen_kind,b100): @+{@+HGET_HYPHEN(b100);@+tail_append(p);@+} @+break;
case TAG(hyphen_kind,b101): @+{@+HGET_HYPHEN(b101);@+tail_append(p);@+} @+break;
case TAG(hyphen_kind,b110): @+{@+HGET_HYPHEN(b110);@+tail_append(p);@+} @+break;
case TAG(hyphen_kind,b111): @+{@+HGET_HYPHEN(b111);@+tail_append(p);@+} @+break;
@
@<cases to teg content@>=
case TAG(hyphen_kind,b000): @+tail_append(hget_hyphen_ref(HTEG8));  @+break;
case TAG(hyphen_kind,b001): @+{@+HTEG_HYPHEN(b001);@+tail_append(p);@+} @+break;
case TAG(hyphen_kind,b010): @+{@+HTEG_HYPHEN(b010);@+tail_append(p);@+} @+break;
case TAG(hyphen_kind,b011): @+{@+HTEG_HYPHEN(b011);@+tail_append(p);@+} @+break;
case TAG(hyphen_kind,b100): @+{@+HTEG_HYPHEN(b100);@+tail_append(p);@+} @+break;
case TAG(hyphen_kind,b101): @+{@+HTEG_HYPHEN(b101);@+tail_append(p);@+} @+break;
case TAG(hyphen_kind,b110): @+{@+HTEG_HYPHEN(b110);@+tail_append(p);@+} @+break;
case TAG(hyphen_kind,b111): @+{@+HTEG_HYPHEN(b111);@+tail_append(p);@+} @+break;
@


@<get functions@>=
pointer hget_hyphen_node(void)
{  @+@<read the start byte |a|@>@;
   if (KIND(a)!=hyphen_kind || INFO(a)==b000) 
      QUIT("Hyphen expected at 0x%x got %s,%d",node_pos,NAME(a),INFO(a));
   { @+
   HGET_HYPHEN(INFO(a));
   @<read and check the end byte |z|@>@;
   return p;
   }
}
@

@<teg functions@>=
pointer hteg_hyphen_node(void)
{  @+@<read the end byte |z|@>@;
   if (KIND(z)!=hyphen_kind || INFO(z)==b000) 
      QUIT("Hyphen expected at 0x%x got %s,%d",node_pos,NAME(z),INFO(z));
   { @+
   HTEG_HYPHEN(INFO(z));
   @<read and check the start byte |a|@>@;
   return p;
   }
}
@



@<\TeX\ macros@>=
#define set_replace_count(X,Y) (mem[X].hh.b1= (Y) &0x7F) 
#define replace_count(X)   (mem[X].hh.b1&0x7F) 
#define set_auto_disc(X) (mem[X].hh.b1|= 0x80) 
#define is_auto_disc(X)  (mem[X].hh.b1 & 0x80) 
#define pre_break llink
#define post_break rlink 
#define info(X) mem[X].hh.lh 
#define llink(X) info(X+1) 
#define rlink(X) link(X+1)  
extern pointer new_disc(void);
@


\subsection{Paragraphs}

@<GET macros@>=
#define @[HGET_PAR(I)@] @/\
{ @+scaled x=0;\
  param_def_t *q;\
  if ((I)&b100) x=hget_xdimen_node(); else x=hget_xdimen_ref(HGET8);\
  if ((I)&b010) q=hget_param_list_node(); else q=hget_param_list_ref(HGET8);\
  hget_paragraph(x,q,0);\
}
@

@<cases to get content@>=
case TAG(par_kind,b000): @+HGET_PAR(b000);@+break;
case TAG(par_kind,b010): @+HGET_PAR(b010);@+break;
case TAG(par_kind,b100): @+HGET_PAR(b100);@+break;
case TAG(par_kind,b110): @+HGET_PAR(b110);@+break;
@



The function |hget_paragraph| uses \TeX's |line_break| routine.
If a page is broken in the middle of a paragraph,
we will need the exact position of the line that starts
the new page. Since break nodes always point to a |kern_node|, |glue_node|, |math_node|, |penalty_node|, or |disc_node|,
we record the positions of these nodes. By the way, glue nodes are not legal breakpoints when they appear
in formulas and when the previous node is not a glue node, penalty node, math node, or explicit kern node.
In the latter case, the explicit kern node preceeding the glue is a legal breakpoint.
% see section 888 in TeX the program
It should be possible to store all these positions in a local table and clear it once the lines
are appended to the main list and the positions are set for the inter line glues. But for the
sake of simplicity, we stick with one big global table for now.

It is possible to call |hget_paragraph| with an |offset| to obtain only the trailing lines
of the paragraphs. This feature is used when a page starts in the middle of a paragraph.
Currently only the remainder of the paragraph is passed to the |line_break| routine.
It might be better to generate the whole paragraph, forcing a line break at the position
indicated by the offset, because this would allow a simple implementation of correct hanging
indentation and the parshape feature of \TeX.
If the offset is positive, unwanted nodes are pruned from the beginning of the list
in the same way \TeX\ does it. We also transplant the post-break list of a discretionary hyphen.

@<get functions@>=
static void transplant_post_break_list(void)
{ @+pointer r, q=link(head);
  int t=replace_count(q);
  pointer s=post_break(q);
  r=q;
  while (t>0) {@+ r=link(r); t--;@+ }
  if (s!=null)
  { while (link(s)!=null) s=link(s);
    link(s)=link(r);link(r)=post_break(q); post_break(q)=null; 
  }
  q=link(r);
  if (r!=head) 
  {@+link(r)=null;flush_node_list(link(head));
    link(head)=q;
  }
}

static void hprune_unwanted_nodes(void)
{ @+pointer q, r=head;
  while (true)@+{@+q=link(r);
  if (q==null) goto done;
  if (is_char_node(q)) goto done;
  if (non_discardable(q)) goto done;
  if (type(q)==kern_node && subtype(q)!=explicit) goto done;
  r=q; /*now |type(q)==glue_node|, |kern_node|, |math_node| or |penalty_node|*/ 
  } 
done: if (r!=head) 
  {@+link(r)=null;flush_node_list(link(head));
  link(head)=q;
  } 
} 

void hget_paragraph(scaled x, param_def_t *q, uint32_t offset)
{ @+uint32_t s, t;
  uint8_t a,z; /* the start and the end byte*/
  if (!IS_LIST(*hpos)) return;
  HGETTAG(a);
  s=hget_list_size(INFO(a));
  hget_size_boundary(INFO(a)); 
  if (KIND(a)==list_kind)
  { uint8_t *list_end=hpos+s;
    cur_list.hs_field=x;
    hset_param_list(q); 
    push_nest();
    needs_bs=false;
    if (offset>0) hpos=hstart+node_pos1+offset;
    while (hpos<list_end)
    { hget_content();
      if (nest_ptr==1) 
      { pointer p=tail;
         if (p!=head && !is_char_node(p) && 
         (type(p)==glue_node || type(p)==kern_node || type(p)==penalty_node || type(p)==disc_node || type(p)==math_node))
           store_map(p,node_pos,0,0);
      }
    }
    hget_size_boundary(INFO(a));
    t=hget_list_size(INFO(a)); 
    if (t!=s) 
      QUIT("List sizes at 0x%x and " SIZE_F " do not match 0x%x != 0x%x",node_pos+1,hpos-hstart-s-1,s,t);
    @<read and check the end byte |z|@>@;
    if (offset>0 && link(head)!=null && !is_char_node(link(head)))
    { if (type(link(head))==disc_node)
        transplant_post_break_list();
      else
        hprune_unwanted_nodes(); 
    }
    if (needs_bs) 
      QUIT("Unexpected trailing baseline node");
    if (head==tail) 
      pop_nest(); /*null paragraphs are ignored*/
    else
    { store_map(link(head),node_pos1,0,0); 
      line_break(hget_integer_ref(widow_penalty_no));
    }
    hrestore_param_list();
  }
  else QUIT("Text in paragraph not yet implemented");
}

void hget_par_node(uint32_t offset)
{ @+ scaled x=0;
  param_def_t *q;
  @<read the start byte |a|@>@;
  node_pos=(hpos-hstart)-1;
  if (INFO(a)&b100) x=hget_xdimen_node(); else x=hget_xdimen_ref(HGET8);
  if (INFO(a)&b010) q=hget_param_list_node(); else q=hget_param_list_ref(HGET8);
  hget_paragraph(x,q,offset);
  @<read and check the end byte |z|@>@;
}
@

When we need to read a paragraph node backwards, we simply skip to the beginning and read the node
in forward direction. The function |hteg_paragraph| therefore simply returns a ponter to the
start of the paragraph node.


@<cases to teg content@>=
case TAG(par_kind,b000): @+hteg_paragraph(b000,0);@+break;
case TAG(par_kind,b010): @+hteg_paragraph(b010,0);@+break;
case TAG(par_kind,b100): @+hteg_paragraph(b100,0);@+break;
case TAG(par_kind,b110): @+hteg_paragraph(b110,0);@+break;
@

@<teg auxiliar functions@>=
void hteg_paragraph(info_t i, uint32_t offset)
{@+scaled x=0;
  param_def_t *q;
  uint8_t *list_start, *par_start;
  hskip_list();
  list_start=hpos;
  if (INFO(i)&b010) q=hteg_param_list_node(); else q=hget_param_list_ref(HTEG8);
  if (INFO(i)&b100) x=hteg_xdimen_node(); else x=hget_xdimen_ref(HTEG8);
  par_start=hpos;
  hpos=list_start;
  hget_paragraph(x,q,0);
  hpos=par_start;
}
@

@<\TeX\ declarations@>=
extern void line_break(int final_widow_penalty);
extern pointer @!just_box; /*the |hlist_node| for the last line of the new paragraph*/ 
extern void pop_nest(void); /*leave a semantic level, re-enter the old*/ 
@

@<\TeX\ macros@>=
#define math_node	9 /*|type| of a math node*/ 
#define non_discardable(X)	(type(X) < math_node)
@

\subsection{Displays}
@<GET macros@>=
#define @[HGET_DISPLAY(I)@] \
{@+ param_def_t *q;@+ pointer p=null, a=null;\
if ((I)&b100) q=hget_param_list_node(); else q=hget_param_list_ref(HGET8);\
if ((I)&b010) a=hget_hbox_node(); \
p=hget_list(); \
if ((I)&b001) a=hget_hbox_node();\
hset_param_list(q); hdisplay(p,a,((I)&b010)!=0); hrestore_param_list();\
}
@

@<TEG macros@>=
#define @[HTEG_DISPLAY(I)@] \
{@+ param_def_t *q;@+ pointer p=null, a=null;\
if ((I)&b001) a=hteg_hbox_node();\
p=hteg_list(); \
if ((I)&b010) a=hteg_hbox_node(); \
if ((I)&b100) q=hteg_param_list_node(); else q=hget_param_list_ref(HTEG8);\
hset_param_list(q); hdisplay(p,a,((I)&b010)!=0); hrestore_param_list();\
}
@


@<cases to get content@>=
case TAG(display_kind,b000): HGET_DISPLAY(b000); @+ break;
case TAG(display_kind,b001): HGET_DISPLAY(b001); @+ break;
case TAG(display_kind,b010): HGET_DISPLAY(b010); @+ break;
case TAG(display_kind,b100): HGET_DISPLAY(b100); @+ break;
case TAG(display_kind,b101): HGET_DISPLAY(b101); @+ break;
case TAG(display_kind,b110): HGET_DISPLAY(b110); @+ break;
@

@<cases to teg content@>=
case TAG(display_kind,b000): HTEG_DISPLAY(b000); @+ break;
case TAG(display_kind,b001): HTEG_DISPLAY(b001); @+ break;
case TAG(display_kind,b010): HTEG_DISPLAY(b010); @+ break;
case TAG(display_kind,b100): HTEG_DISPLAY(b100); @+ break;
case TAG(display_kind,b101): HTEG_DISPLAY(b101); @+ break;
case TAG(display_kind,b110): HTEG_DISPLAY(b110); @+ break;
@

The |hdisplay| function now needs to do all the things we have skipped
while running Hi\TeX: the code in \<Go into display math mode> and \<Finish displayed math>.
We terminate the present paragraph and pass the list so far to
the line breaking routine, observe the dimensions of the
final line of the preceeding paragraph, position the display
and continue with reading the paragraph. To make shure the paragraph following
the display gets the proper baseline skip, we modify the current list.



\subsection{Adjustments}
Vertical adjustments are inside horizontal lists. They migrate to the enclosing vertical list
where they are unpacked and added after the horizontal material.
Inside a paragraph, this means the adjustment comes after the line that contains the adjustment.
Outside a paragraph, \TeX\ will do the moving and unpacking even before the adjustment has a
chance to get into the \HINT/ file. If we parse paragraphs in forward direction, we do not 
need to parse adjustments in backward direction.

@<GET macros@>=
#define @[HGET_ADJUST(I)@] @/\ 
{ @+pointer p; uint32_t s,t;\
  p=get_node(small_node_size); type(p)=adjust_node; subtype(p)=normal;\
  s=hget_list_size(I); hget_size_boundary(I); \
  adjust_ptr(p)=hget_node_list(s);\
  tail_append(p);\
  hget_size_boundary(I);  t=hget_list_size(I); \
  if (t!=s) QUIT("List sizes at " SIZE_F " do not match 0x%x != 0x%x",hpos-hstart-1,s,t);\
}
@

@<\TeX\ macros@>=
#define adjust_node 5
#define adjust_ptr(X) mem[X+1].i
#define small_node_size	2 /*number of words to allocate for most node types*/
@

@<cases to get content@>=
case TAG(adjust_kind,1):  @+HGET_ADJUST(1); @+ break;
case TAG(adjust_kind,2):  @+HGET_ADJUST(2); @+ break;
case TAG(adjust_kind,3):  @+HGET_ADJUST(3); @+ break;
case TAG(adjust_kind,4):  @+HGET_ADJUST(4); @+ break;
case TAG(adjust_kind,5):  @+HGET_ADJUST(5); @+ break;
@


\subsection{Images}
@<GET macros@>=
#define @[HGET_IMAGE(I)@] @/\
{ @+pointer p;\
  p=get_node(image_node_size);  type(p)=whatsit_node; subtype(p)=image_node;\
  HGET16(image_no(p));RNG("Section number",image_no(p),3,max_section_no);  \
  if (I&b010) {@+HGET32(image_width(p)); @+HGET32(image_height(p));@+} \
  else image_width(p)=image_height(p)=0;\
  if (I&b001) {HGET_STRETCH(image_stretch(p),image_stretch_order(p)); \
               HGET_STRETCH(image_shrink(p),image_shrink_order(p));@+}\
  else { image_stretch(p)=image_shrink(p)=0;image_stretch_order(p)=image_shrink_order(p)=normal;@+}\
  tail_append(p);}
@

@<TEG macros@>=
#define @[HTEG_IMAGE(I)@] @/\
{ @+pointer p;\
  p=get_node(image_node_size);  type(p)=whatsit_node; subtype(p)=image_node;\
  if (I&b001) {HTEG_STRETCH(image_shrink(p),image_shrink_order(p));\
               HTEG_STRETCH(image_stretch(p),image_stretch_order(p)); @+}\
  else { image_stretch(p)=image_shrink(p)=0;image_stretch_order(p)=image_shrink_order(p)=normal;@+}\
  if (I&b010) {@+@+HTEG32(image_height(p)); HTEG32(image_width(p)); @+} \
  else image_width(p)=image_height(p)=0;\
  HTEG16(image_no(p));RNG("Section number",image_no(p),3,max_section_no);  \
  tail_append(p);}
@

@<cases to get content@>=
case TAG(image_kind,b000): @+ hget_image_ref(HGET8); @+break;
case TAG(image_kind,b100): @+ HGET_IMAGE(b100);@+break;
case TAG(image_kind,b101): @+ HGET_IMAGE(b101);@+break;
case TAG(image_kind,b110): @+ HGET_IMAGE(b110);@+break;
case TAG(image_kind,b111): @+ HGET_IMAGE(b111);@+break;
@
@<cases to teg content@>=
case TAG(image_kind,b000): @+ hget_image_ref(HTEG8); @+break;
case TAG(image_kind,b100): @+ HTEG_IMAGE(b100);@+break;
case TAG(image_kind,b101): @+ HTEG_IMAGE(b101);@+break;
case TAG(image_kind,b110): @+ HTEG_IMAGE(b110);@+break;
case TAG(image_kind,b111): @+ HTEG_IMAGE(b111);@+break;
@




@<\TeX\ macros@>=
#define whatsit_node	8 /*|type| of special extension nodes*/
#define image_node 10
#define image_node_size 11
#define image_width(X) width(X) 
#define image_height(X) height(X) 
#define image_depth(X) depth(X) 
#define image_no(X) mem[X+4].u
#define image_stretch(X) mem[X+7].i
#define image_shrink(X) mem[X+8].i
#define image_stretch_order(X) stretch_order(X+9) 
#define image_shrink_order(X) shrink_order(X+9) 
@



\section{Routines from \TeX}
\subsection{The {\tt texdef.h} Header File}
The program \TeX\ uses many, many macros, even definitions like ``|#define sc i|''
that make it danagerous to use variables named ``|sc|'' because they are renamed into ``|i|''
are found among \TeX's macros. For code that we extract in the following directly 
from \TeX's sources it is, however, convenient to have all these macro definitions in a
header file, the file {\tt texdef.h}.

\changestyle{texdef.tex}

A small subset of these definitions are used in the code that we define here.
We list them as |@<\TeX\ macros@>| and we can include them where needed by using the 
file {\tt htexdef.h}

@(htexdef.h@>=
@<\TeX\ macros@>@;
@

\subsection{The {\tt textypes.h} Header File}
In the following we will extract functions from \TeX\ that will need access to
\TeX's internals and the most readable and convenient way to gain this access 
is using the numerous macros that \TeX\ defines for this purpose.
The {\tt types.ch} change files will take care of writing these macros into 
the  header file {\tt textypes.h}.
There are two related header files: {\tt texvars.h} and {\tt texfuncs.h}
that contain prototypes for the global variables and functions of \TeX.
These are not generated from the \TeX\ sources but listed in sections~\secref{texvars}
and~\secref{texfuncs} of the Appendix. But back to the generation of  {\tt textypes.h}.

\changestyle{types.tex}

\subsection{Auxiliar functions}
\changestyle{harith.tex}


@<\TeX\ macros@>=
#define inf_bad 10000
#define odd(X)       ((X)&1)
#define chr(X)       ((unsigned char)(X))
#define ord(X)       ((int)(X))
#define abs(X)       ((X)>-(X)?(X):-(X))
#define round(X)     ((int)((X)>=0.0?floor((X)+0.5):ceil((X)-0.5)))
@

@<\TeX\ declarations@>=
extern int half(int x);
extern scaled x_over_n(scaled x,int n);
extern scaled xn_over_d(scaled x, int n, int d);
extern halfword badness(scaled t,scaled s);
@

\subsection{Reading Font Metric Files}
In section~\secref{fonts} me mentioned the \TeX\ function  |read_font_info|. Now we see how to extract
this function from the \TeX\ sources and make modifications. We do this using the {\tt hfont.ch}
change file.

\changestyle{hfont.tex}


@<\TeX\ declarations@>=
extern memory_word @!font_info[];
extern char **const font_name;
extern int *const @!width_base; /*base addresses for widths*/
extern int *const @!height_base;  /*base addresses for heights*/
extern int *const @!depth_base; /*base addresses for depths*/ 
extern int *const @!char_base;  /*base addresses for |char_info|*/ 
extern int *const @!param_base; /*base addresses for font parameters*/ 

extern eight_bits *const font_bc,*const font_ec;
@

\subsection{\TeX's Memory}
\TeX's main data structure is the |mem| array. In this section, we will extract the
|mem| variable and the routines to allocate and deallocate nodes.
 
\changestyle{hmem.tex}

@<\TeX\ types@>=
typedef uint8_t quarterword; /*1/4 of a word*/ 
typedef uint16_t halfword; /*1/2 of a word*/ 
typedef uint8_t eight_bits;
typedef halfword pointer;
typedef int32_t scaled;

typedef struct{
  uint16_t rh;
  union{
    uint16_t lh;
    struct {uint8_t b0; uint8_t b1;};
  };}two_halves;
typedef struct{uint8_t b0,b1,b2,b3;}four_quarters;
typedef union{
    int32_t i;
    uint32_t u;
    float32_t gr;
    two_halves hh;
    four_quarters qqqq;
} memory_word;

enum{mem_max= 30000};
enum{mem_min= 0};
@

@<\TeX\ declarations@>=
extern memory_word *const mem; /*the big dynamic storage area*/ 
extern pointer temp_ptr;  /*a pointer variable for occasional emergency use*/ 
extern pointer @!lo_mem_max; /*the largest location of variable-size memory in use*/ 
extern pointer hi_mem_min; /*the smallest location of one-word memory in use*/ 
extern pointer @!mem_end; /*the last one-word node used in |mem|*/ 
extern void free_node(pointer @!p, halfword @!s); /*variable-size node liberation*/ 
extern void flush_node_list(pointer @!p); /*erase list of nodes starting at |p|*/ 
extern void hmem_init(void);
@


\subsection{\TeX's Boxes and their friends}

\changestyle{hbox.tex}

@<\TeX\ declarations@>=
extern void delete_glue_ref(pointer @!p); /*|p| points to a glue specification*/ 
extern pointer copy_node_list(pointer @!p); /*makes a duplicate of the
  node list that starts at |p| and returns a pointer to the new list*/ 
@

\subsection{\TeX's current list}


\changestyle{hlist.tex}

We add three new fields to \TeX's |list_state_record|: a boolean |insert_bs| that is true
if the next box added needs a baseline skip, a |bs_field| that contains the 
necessary information about the baselien skip, and the |np_field| that contains the
position of the node in the content section.

@<\TeX\ types@>=
typedef struct{int16_t mode_field;
 pointer head_field,tail_field;
 int pg_field,ml_field;
 memory_word aux_field;
 bs_t bs_field;
 bool insert_bs;
 scaled ds_field, dw_field, di_field,hs_field;
 uint32_t np_field;
}list_state_record;
@


@<\TeX\ declarations@>=
extern list_state_record cur_list;
extern pointer new_rule(void);
extern pointer get_node(int s);  /*variable-size node allocation*/ 
extern void hlist_init(void);

extern int @!var_used, @!dyn_used;

enum{nest_size= 40};
extern list_state_record nest[nest_size+1];
extern uint8_t nest_ptr;
extern uint8_t max_nest_stack;

extern void push_nest(void);
extern void pop_nest(void);
@

@<\TeX\ macros@>=
#define mode	cur_list.mode_field /*current mode*/
#define head	cur_list.head_field /*header node of current list*/
#define tail	cur_list.tail_field /*final node on current list*/
#define prev_graf	cur_list.pg_field /*number of paragraph lines accumulated*/
#define aux	cur_list.aux_field /*auxiliary data about the current list*/
#define cur_bs 	cur_list.bs_field.bs 
#define cur_ls 	cur_list.bs_field.ls 
#define cur_lsl	cur_list.bs_field.lsl
#define needs_bs cur_list.insert_bs
#define node_pos cur_list.np_field
#define node_pos1 (nest_ptr==0?0:nest[nest_ptr-1].np_field)
#define tail_append(X)	{@+link(tail)=X;tail=link(tail); } 
@

@<\TeX\ functions@>=
void hlist_init(void)
{ nest_ptr=0;max_nest_stack=0;
mode=vmode;head=contrib_head;tail=contrib_head;
prev_depth=ignore_depth;
prev_graf=0;
hpage_init();
}
@


\subsection{\TeX's printing routines}

\changestyle{hprint.tex}
@<\TeX\ declarations@>=
extern void print_ln(void); /*prints an end-of-line*/ 
extern int @!font_in_short_display; /*an internal font number*/ 
@


\subsection{\TeX's page builder}\label{texbuildpage}

\changestyle{hbuildpage.tex}

@<\TeX\ types@>=
typedef struct {
pointer p;
int i;
pointer g;
scaled s;
} stream_t;
@


@<\TeX\ functions@>=

void hpage_init(void)
{
prev_depth=ignore_depth; prev_graf=0;
page_contents=empty;page_tail=page_head;link(page_head)=null;@/
page_depth=0;page_max_depth=0;
}


void hresume_after_output(void)
{
  if (link(page_head)!=null) 
  {@+if (link(contrib_head)==null) 
    if (nest_ptr==0) tail=page_tail;@+else contrib_tail=page_tail;
  else link(page_tail)=link(contrib_head);
  link(contrib_head)=link(page_head);
  link(page_head)=null;page_tail=page_head;
  } 
}

@

@<\TeX\ declarations@>=
extern scaled *const @!total_stretch,*const @!total_shrink;
extern stream_t stream[256];
extern bool hbuild_page(void);
extern bool hits_all_over(void);
extern void hpage_init(void);
extern void hresume_after_output(void);
extern uint8_t page_contents;
extern scaled page_depth, page_max_depth;
extern int insert_penalties;
extern pointer best_page_break;
extern scaled best_size;
@

@<\TeX\ variables@>=
scaled page_depth, page_max_depth;
pointer page_tail=page_head; /*the final node on the current page*/ 
uint8_t @!page_contents; /*what is on the current page so far?*/ 

scaled hvsize, hhsize;
@

@<\TeX\ macros@>=

#define mem_top	30000 
#define contrib_head	mem_top-1 
#define page_head	mem_top-2 /*vlist for current page*/ 
#define vmode	1 /*vertical mode*/ 
#define empty	0 /*symbolic name for a null constant*/ 
#define contrib_tail	nest[0].tail_field /*tail of the contribution list*/
#define max_depth      dimen_par(max_depth_code)
@


\subsection{\TeX's line breaking routine}

\changestyle{hlinebreak.tex}


@<\TeX\ declarations@>=
extern scaled *const active_width;   /*distance from first active node to~|cur_p|*/ 
@

\subsection{\TeX's box packing routines}
\changestyle{hpack.tex}

@<\TeX\ declarations@>=
extern  pointer hpack(pointer @!p, scaled @!w, small_number @!m);
#define @[vpack(...)@]	@[vpackage(__VA_ARGS__, max_dimen)@]  /*special case of unconstrained depth*/ 
extern pointer vpackage(pointer @!p, scaled @!h, small_number @!m, scaled @!l);
extern pointer @!adjust_tail; /*tail of adjustment list*/ 
@

\subsection{Displayed formulas}
\changestyle{hdisplay.tex}

@<\TeX\ declarations@>=
extern void hdisplay(pointer p, pointer a, bool l);
@

\subsection{Packing boxes}
We need to write the following stuff:

@(htex.c@>=
#include "htex.h"

@<\TeX\ macros@>@;

@<\TeX\ variables@>@;

@<\TeX\ functions@>@;


@

@<\TeX\ declarations@>=
extern pointer new_spec(pointer @!p); /*duplicates a glue specification*/ 
extern void append_to_vlist(pointer @!b, uint32_t offset);
@



\subsection{Page positions}

@(hpage.c@>=
#include "htex.h"
#include "hpos.h"
@



\section{Building Pages Bottom Up}
\TeX's page builder (see section~\secref{texbuildpage}) moves nodes from the contribution list 
to the current page, filling it from top to bottom, and finds an optimal page break to end the page.
When a \HINT/ viewer needs to move to the previous page, only the start of the present page 
might be known. In this situation, the start of the present page determines the end of the
previous page and the \HINT/ page builder needs to find an optimal page break to start the previous page.

We have seen already, how parsing the \HINT/ file backwards will fill the contribution list,
moving the current position backwards, and adding new nodes at the end of the list.
Now we need to construct a page builder, that
moves these nodes from the head of the contribution list to the top of the current page,
building it from the bottom up until the optimal
page start is found. It is clear that optimizing different objectives will produce different
outcomes. So the pages \HINT/ finds in backward direction might be different from the ones
\TeX\ or \HINT/ find when paging forward. Therefore complete compatibility with \TeX\ is
not an issue. Still we want to do a good job and therefore the following exposition follows
closely the exposition of \TeX's page builder in part 45 of {\it \TeX: The Program\/}\cite{Knuth:tex}.

So here is the outline of the function |hbuild_page_up|
@(hbuildpageup.c@>=
#include <string.h>
#include "htex.h"
#include "hformat.h"
#include "hdefaults.h"
#include "texdef.h"

scaled page_max_height;

bool hbuild_page_up(void) /*append contributions to the current page*/ 
{@+
static scaled page_height;
static scaled top_so_far[8];
pointer p; /*the node being appended*/ 
pointer @!q; /*nodes being examined*/ 
int @!b, @!c; /*badness and cost of current page*/ 
int @!pi; /*penalty to be added to the badness*/ 
/* |uint8_t n;| insertion box number*/ 
/* |scaled delta, h, w;| sizes used for insertion calculations*/ 
if (link(contrib_head)==null) return false;
@/do@+{ p=link(contrib_head);@/
@<Prepend node |p| to the current page; if it is time for a page break, |fire_up| the renderer@>;
}@+ while (!(link(contrib_head)==null));
tail=contrib_head;
return false;
} 
@

@<\TeX\ declarations@>=
extern bool hbuild_page_up(void);
@
We deleted references to |output_active| and output routines as well as the code to update
the values of |last_glue|, |last_penalty|, and |last_kern|.

Before we consider the core of this routine, let's start at the beginning and look at the
variables |page_contents| and |page_total|


The variable |page_contents| is |empty| when the
current page contains only mark nodes and content-less whatsit nodes; it
is |inserts_only| if the page contains only insertion nodes in addition to
marks and whatsits, penalties, kern, and glue.  At the bottom of a page, only penalty nodes are
discarded until |page_contents| is no longer |empty|.
(At the page bottom, glue is not discarded!) 
As soon as |page_contents| becomes non-|empty|,
the current |vsize| and |max_depth| are squirreled away into |page_goal|
and |page_max_depth|; the latter values will be used until the page has
been forwarded to the renderer. The \.{\\topskip} adjustment
is made when |page_contents| changes to |box_there|.


The variable |page_total| is supposed to reflect the size of the page so far from the
top of the page down to the baseline of the last item on the page. Not included is the
depth of the last item on the page as long as it does not exceed |page_max_depth|.
If it does, the excess is included in the |page_total|.
Also the natural size of the topskip glue is included in the |page_total| and its value is
set asside in the variable |page_max_height|. When we add a box or rule, we keep the height
of it in the variable |page_height| and make sure it does not exceed |page_max_height|.
If it does, the excess is again included in the |page_total|. 
Before we ship out the page, we add the topskip glue and
 then the height plus depth of the page shoud be less or equal to
$|page_total|+|max_page_depth|$, and it should be less only by the amount that the depth of the
last node on the page is less than |page_max_depth|.

We judge the goodness of a page break amoung other things by the amount of material
that is supposed to fill the page. But \TeX\ discards penalties, glues and kerns at the top of a
page. So we do not incorporate these nodes immediately into the |page_so_far| variables
but keep track of them in the |top_so_far| variables. Whenever we add a node that makes the
accumulated nodes at the top non-discardable, we add them to the |page_so_far| variables.

Now we consider how to prepend the different types of nodes.
We start with nodes that have height and depth.

\subsection{Boxes and Rules}

@<Prepend a box or rule node to the current page@>=
if (page_contents==empty) 
{ @<Freeze page specs@>@;
  if(depth(p)> page_max_depth)
    page_total=depth(p)-page_max_depth;
  depth(p)=0;
}
if (page_contents<box_there)  
  @<Account for the insertion of the \.{\\topskip} glue@>@;
page_contents=box_there;
@<Add in the |top_so_far|@>@;
page_total+= page_height+depth(p);
if (height(p)>page_max_height)
{ page_total=page_total+height(p)-page_max_height;
  page_height=page_max_height;
}
else
  page_height= height(p);
@

Here we used

@<Freeze page specs@>=
memset(page_so_far,0,sizeof(page_so_far));
memset(top_so_far,0,sizeof(top_so_far));
page_goal= hvsize;
page_max_depth= max_depth;
page_height= 0;
least_page_cost= awful_bad;
@


@<Account for the insertion of the \.{\\topskip} glue@>=
{ page_max_height=width(pointer_def[glue_kind][top_skip_no]);
  page_total=page_total+page_max_height;
}
@

@<Add in the |top_so_far|@>=
{ int i;
  for (i=1; i<=6; i++)
  { page_so_far[i]+=top_so_far[i];
    top_so_far[i]=0;
  } 
}
@

@<\TeX\ declarations@>=
extern scaled page_so_far[8];
extern int least_page_cost;
@

\subsection{Stacking up the Page}

This is (more or less) \TeX's way of building the page: 
If the current page is empty and node |p| is to be deleted, |goto done1|; otherwise
use node |p| to update the state of the current page; if this node is an insertion,
|goto contribute|; otherwise if this node is not a legal breakpoint, |goto contribute|
or |update_heights|; otherwise set |pi| to the penalty associated with this breakpoint.
Check if node |p| is a new champion breakpoint; then if it is time for a page
break, prepare for output, fire up the renderer, and |return|.

And here is our new code:

@<Prepend node |p| to the current page;...@>=
switch (type(p)) {
case hlist_node: case vlist_node: case rule_node: 
    @<Prepend a box or rule node to the current page@>@; goto contribute;
case whatsit_node: goto contribute;
case glue_node: @<Prepend a glue node to the current page@>@; break;
case kern_node: @<Prepend a kern node to the current page@>@; break;

case penalty_node: if (page_contents == empty) goto done1;@+else pi=penalty(p);@+break;
case mark_node: goto contribute;
case ins_node: @<Prepend an insertion to the current page and |goto contribute|@>@;
default: MESSAGE("Unexpected node type %d in build_page_up ignored\n",type(p));
} 
if (pi < inf_penalty) 
  @<Check if node |p| is a new champion breakpoint@>@;
contribute:
@<Prepend node |p| to the current page and |goto done|@>@;
done1: @<Recycle node |p|@>@;
done: 
@

@<Prepend node |p| to the current page and |goto done|@>=
link(contrib_head)=link(p);
link(p)=link(page_head);
link(page_head)=p;
goto done;
@

@<Recycle node |p|@>=
link(contrib_head)=link(p);link(p)=null;flush_node_list(p);
@
\subsection{Glues and Kerns}

Page breaks are possible at a glue node, it the node just above the glue node is a
|hlist_node|, |vlist_node|,
|rule_node|, |ins_node|, |mark_node|, |adjust_node|, |ligature_node|,
|disc_node|, or |whatsit_node|. We test this with the |precedes_break| macro.
We silently return if the node above the glue is not yet known.


@<Prepend a glue node to the current page@>=
if(link(p)==null) return false;
if (page_contents==empty) 
{ @<Freeze page specs@>@;
  page_contents=inserts_only;
}
@<Add glue to |top_so_far|@>@;
if (!precedes_break(link(p))) goto contribute;
pi=0;
@

@<Add glue to |top_so_far|@>=
#define top_shrink top_so_far[6]
#define top_total top_so_far[1]

{ pointer q=glue_ptr(p);
  top_so_far[2+stretch_order(q)]+=stretch(q);
  top_shrink+=shrink(q);
  if((shrink_order(q)!=normal)&&(shrink(q)!=0))
    MESSAGE("Infinite glue shrinkage found on current page");
  top_total+=width(q);
}
@

Handling kern nodes is similar.A kern node is a possible page break if the 
node below it is a glue node.

@<Prepend a kern node to the current page@>=
if (page_contents==empty) 
{ @<Freeze page specs@>@;
  page_contents=inserts_only;
}
top_total+=width(p);
if (page_contents < box_there) goto done1;
  else if (link(page_head)==null) return false;
  else if (type(link(page_head))!=glue_node)
  goto contribute;
pi=0;
@

\subsection{Insertions}
@<Prepend an insertion to the current page and |goto contribute|@>=
QUIT("Prepending insertions not yet implemented\n");
@


\subsection{Checking Breakpoints}
At this point |p| is a possible breakpoint and |pi| is the penalty associated with it.
First we compute |c|, the cost or badness of the current page.

@<Compute the cost |c| of a possible break at |p|@>=
@<Compute the badness, |b|, of the current page, using |awful_bad| if the box is too full@>;
if (b < awful_bad) 
{ if (pi <= eject_penalty) c=pi;
  else if (b < inf_bad) c=b+pi+insert_penalties;
  else c=deplorable;
}
else c=b;
if (insert_penalties >= 10000) c=awful_bad;
@

@<Compute the badness, |b|, of the current page...@>=
if (page_total < page_goal) 
{  if ((page_so_far[3]!=0)||(page_so_far[4]!=0)||(page_so_far[5]!=0)) b=0;
  else b=badness(page_goal-page_total, page_so_far[2]);
}
else if (page_total-page_goal > page_shrink) b=awful_bad;
else b=badness(page_total-page_goal, page_shrink)
@

@<Check if node |p| is a new champion breakpoint@>=
{@+@<Compute the cost |c| of a possible break at |p|@>@;
  if (c <= least_page_cost) 
  {@+best_page_break=p;best_size=page_goal;
    least_page_cost=c;
#if 0
    r=link(page_ins_head);
    while (r!=page_ins_head) 
      {@+best_ins_ptr(r)=last_ins_ptr(r);
      r=link(r);
      }
#endif 
  } 
  if ((c==awful_bad)||(pi <= eject_penalty)) 
  {@+@<Replace leading white-space by the topskip glue@>@;
     @<Put the \(o)optimal current page into box 255@>@; 
     return true;
  } 
} 
@

@<Replace leading white-space by the topskip glue@>=
while (true) {
  q=link(page_head);
  if (q==null) return false; /* empty page */
  else if (type(q)==penalty_node || type(q)==glue_node || type(q)==kern_node)
  { link(page_head)=link(q);link(q)=null;flush_node_list(q); }
  else break;
}  
temp_ptr= new_spec(pointer_def[glue_kind][top_skip_no]);
q= new_glue(temp_ptr);glue_ref_count(temp_ptr)= null;
if(width(temp_ptr)> page_height) width(temp_ptr)= width(temp_ptr)-page_height;
else width(temp_ptr)= 0;
link(q)=link(page_head);
link(page_head)=q;
@

@<Put the \(o)optimal current page into box 255@>=
if(box(0)!=null)QUIT("Box 0 must be empty");
box(0)=vpackage(link(page_head), best_size, exactly, 0x100000);
@<clean up the lists used while building the page@>@;
@


@<clean up the lists used while building the page@>=
@



\section{The Command Line Interface}

Here we describe the central parts of \HINT/, connecting the \HINT/ file with the different routines
of \TeX\ and the backend. There are actually two backends: The command line version of hint is
non interactive and features only control output that mimics the output you can get from \TeX.
Since the missing interactivity makes this program behave deterministically it offers a convenient
way for debuging and regession tests.
The interactive version just offers a collection of key routines that are used by a GUI
program as described in section~\secref{gui}.


Here comes the |main| program:

@(main.c@>=
#include <stdio.h>
#include <string.h>
#include "htex.h"
#include "hformat.h"
#include "hget.h"

@<command line variables@>@;

@<command line functions@>@;

int main(int argc, char *argv[])
{ char stem_name[MAX_NAME];
  int stem_length=0, path_length=0;
  bool option_log=false;

  @<process the command line@>@;
  @<open the log file@>@;
  hmem_init();
  hlist_init();
  hopen_file(in_name);
  hget_banner();
  hget_directory_section();
  hget_definition_section();
  hget_content_section();
  hpage_init();
  while (hpos<hend)
  { hget_content();
    while (hbuild_page())  
    { hship_out(stream[0].p); stream[0].p=0; hresume_after_output();}
  }
  if (!hits_all_over())
  { if (hbuild_page()) 
    { hship_out(stream[0].p); stream[0].p=0;}
  }
  @<close the log file@>@;
  return 0;
}
@
\goodbreak

Processing of the command line is straight forward:

@<process the command line@>=
  debugflags=dbgbasic;
  strncpy(prog_name,argv[0],MAX_NAME);
  if (argc < 2) usage();
  argv++; /* skip the program name */
  while (*argv!=NULL)
  { if ((*argv)[0]=='-')
    { char option=(*argv)[1];
      switch(option)
      {
        case 'l': option_log=true; @+break;
        case 'd': @/
          argv++; if (*argv==NULL) usage();
          debugflags=strtol(*argv,NULL,16);
          break;
        default: usage();
      }
    }
    else /* the input file name */
    { strncpy(in_name,*argv,MAX_NAME);
      path_length=(int)strlen(in_name);
      if (path_length<4 
          || strncmp(in_name+path_length-4,".hnt",4)!=0)
        strncat(in_name,".hnt",MAX_NAME-1);
      stem_length=(int)strlen(in_name)-4;
      strncpy(stem_name,in_name,stem_length);
      stem_name[stem_length]=0;
      if (*(argv+1)!=NULL) usage();
    }
    argv++;
  }
@

The |usage| function explains command line\index{command line} 
parameters and options\index{option}\index{debugging}.
@<command line functions@>=
void usage(void)
 { fprintf(stderr,
  "Usage: %s [options] filename.hnt\n",prog_name);@/
  fprintf(stderr,
  "Options:\n"@/
  "\t -o file\t specify an output file name\n"@/
  "\t -l     \t redirect stderr to a log file\n");@/
#ifdef DEBUG
fprintf(stderr,"\t -d XXX \t hexadecimal value. OR together these values:\n");@/
fprintf(stderr,"\t\t\t XX=%03X   basic debugging\n", dbgbasic);@/
fprintf(stderr,"\t\t\t XX=%03X   tag debugging\n", dbgtags);@/
fprintf(stderr,"\t\t\t XX=%03X   definition debugging\n", dbgdef);@/
fprintf(stderr,"\t\t\t XX=%03X   directory debugging\n", dbgdir);@/
fprintf(stderr,"\t\t\t XX=%03X   range debugging\n",dbgrange);@/
fprintf(stderr,"\t\t\t XX=%03X   compression debugging\n", dbgcompress);@/
fprintf(stderr,"\t\t\t XX=%03X   buffer debugging\n", dbgbuffer);@/
#endif
exit(1);
}
@

Processing the command line looks for options and then sets the
input file name\index{file name}.

The log file gets the extension {\tt .hlg}, short for \HINT/ log file.

@<open the log file@> =
#ifdef DEBUG
  if (option_log)
  { 
    strncat(stem_name,".hlg",MAX_NAME);
    hlog=freopen(stem_name,"w",stderr);
    if (hlog==NULL)
    { fprintf(stderr,"Unable to open logfile %s",stem_name);
      hlog=stderr;
    }
    stem_name[stem_length]=0;
  }
  else
    hlog=stderr;
#else
    hlog=stderr; 
#endif
@



@<close the log file@>=
if (hlog!=NULL) fclose(hlog);
@



@<command line variables@>=

#define MAX_NAME 1024
char prog_name[MAX_NAME];
char in_name[MAX_NAME];

FILE *hlog;
@


@<command line functions@>=
void hship_out(pointer p)
{ static int page_count=0;
  page_count++;
  DBG(dbgbasic,"\nCompleted box being shipped out [%d]",page_count);
  show_box(p);
  DBG(dbgbasic,"\n");
  flush_node_list(p);
}


@


@<\TeX\ declarations@>=
extern void show_box(pointer p);
@

\section{Rendering \HINT/ Files}
How to render a \HINT/ file on any specific device depends largely on the
operating system and its API encapsulating the device. Never the less, there
are some functions that can be shared accross many different operating systems
or at least can serve as a starting point for implementing operating system specific
versions.

In the following, we show functions that were used on Windows using the WIN32 API
and on Android using OpenGL~2.0 to implement such renderers.  

\subsection{Rendering Glyphs}
Currently only so called PK files are supported. Here we describe how these are used 
on the WIN32 operatig system using its API.

PK Files\cite{TR:pkfile}
contain a compressed representation of bitmap fonts  produced by METAFONT and gftopk.
After unpacking these fonts, we obtain a device independent bitmap for each glyph
which can be displayed on a Device Context using the |StretchDIBits|.
This function is used to display the character on a memory device context given
by the handle |hmem|. 
This function is capable of stretching or shrinking and hence can adjust the
resolution. The resolution of the bitmap in the pk file is given be the 
two parameters |hppp| (horizonttap pixel per point) and vppp (vertical pixel per point) which
are found in the preamble of the pk file.

For the memory device context we maintain its width, height as well as its
horizontal and vertical resolution in dpi (dots per inch).
Given the pixel position $(x,y)$ on |hmem|, the offset |d_h| and |d_v| of the hotspot of the
glyph, and |w| and |h| the width and height of the glyph, we can compute the necessary
parameters to display the glyph on |hmem| using the function |StretchDIBits|.

With the assembled page on |hmem| in the correct size and resolutio ends the job of the
user interface independent part of the hint viewer and the user interface takes over.

The user interface knows the size of the client window (in pixel) and its resolution. 
From this information, it can compute the true size in scaled point of the client window
and the desired resolution of |hmem|. The user interface for the WIN32 viewer makes the
resolution of |hmem| by a ceratin factor, called |render_factor| bigger. This has two advantages:
scaling a high resolution black and white image down produces grey pixels around the border
which makes the glyphs appear smoother; further, positions of glyphs are rounded to whole
pixels when rendering them on |hmem| and these positions translate to sub-pixel position when scaling
down. The user factor can also use a scale factor to display the page larger or smaller than its
true size. For example with a scale factor of 2, a glyph 10pt high would measure 20pt on the screen.
To make the enlaged page fit on the window, the user interface would request a window of only
half the actual width and height, but would double the render factor. The image it receives
cann then be displayed stretching it only be half the render factor thus obtaining an image
that is scaled down by exactly the render factor filling the complete client window.



\appendix

\section{The Source Files}

\subsection{{\tt hint.h}}\index{hint.h+{\tt hint.h}}
We need types from \TeX.


We need functions from hint:
@<get declarations@>=
static void hget_font_params(uint8_t n, font_def_t *f);
extern pointer hget_node_list(uint32_t s);
extern pointer hget_list(void);
extern pointer hget_text_list(uint32_t s);
extern pointer hget_rule_node(void);
extern pointer hget_glue_node(void);
extern pointer hget_glue_spec(void);
extern pointer hget_hyphen_node(void);
extern pointer hget_hbox_node(void);
extern pointer hget_vbox_node(void);



static void free_param_list(param_def_t *p);
@




We need a few global variables:
@<\TeX\ declarations@>=
#if 0
extern scaled hsize, vsize;
#endif
@



\subsection{{\tt hget.h}}\index{hget.h+{\tt hget.h}}
The \.{hget.h} file contains function prototypes for the functions that form
the interface to the \HINT/ file.
@(hget.h@>=

@<get types@>@;

extern font_def_t *font_def;
extern void hset_default_definitions(void);
extern int32_t hget_integer_ref(uint8_t n);
extern scaled  hget_dimen_ref(uint8_t n);
extern pointer hget_rule_ref(uint8_t n);
extern pointer hget_math_ref(uint8_t n);
extern pointer hget_glue_ref(uint8_t n);
extern pointer hget_leaders_ref(uint8_t n);
extern scaled hget_xdimen_ref(uint8_t n);
extern pointer hget_hyphen_ref(uint8_t n);
extern pointer hget_ligature_ref(uint8_t n);
extern void hget_baseline_ref(uint8_t n, bs_t *b);
extern pointer hget_image_ref(uint16_t n);
extern uint32_t hget_utf8(void);
extern param_def_t *hget_param_list_ref(uint8_t n);
extern void hset_param_list(param_def_t *p);
extern void hrestore_param_list(void);
extern void hopen_file(const char *in_name);
extern bool hget_banner(void);
extern void hget_section(uint16_t n);
extern void hget_directory_section(void);
extern void hallocate_definitions(void);
extern void hget_definition_section(void);
extern void hget_content_section(void);
extern void hget_content(void);
extern void hget_size_boundary(info_t info);
extern uint32_t hget_list_size(info_t info);
extern pointer hget_list(void);
extern void hget_par_node(uint32_t offset);
extern void hget_paragraph(scaled x, param_def_t *q, uint32_t offset);
extern void hset(pointer p, uint8_t sto, scaled st,
					uint8_t sho,scaled sh, scaled w);
extern void vset(pointer p, uint8_t sto, scaled st,
					uint8_t sho,scaled sh, scaled h);

extern param_def_t *hget_param_list_node(void);
@

@

\subsection{{\tt hget.c}}
@(hget.c@>=
#ifndef WIN32
#include <sys/mman.h>
#else
#include <windows.h>
#endif
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include <zlib.h>
#include "htex.h"
#include "hformat.h"
#include "hdefaults.h"
#include "hpos.h"
#include "hget.h"
@<\TeX\ macros@>

@<GET macros@>@;

@<get variables@>@;

@<get declarations@>@;

@<get functions@>@;
@

\subsection{{\tt hteg.c}}
@(hteg.c@>=
#ifndef WIN32
#include <sys/mman.h>
#else
#include <windows.h>
#endif
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include <zlib.h>
#include "htex.h"
#include "hformat.h"
#include "hdefaults.h"
#include "hpos.h"
#include "hget.h"
#include "hteg.h"
@<\TeX\ macros@>

@<TEG macros@>@;

@<teg auxiliar functions@>@;

@<teg functions@>@;
@



\subsection{{\tt htex.h}}
@<\TeX\ types@>=
extern uint8_t *hpos, *hend;

enum{font_mem_size= 20000};
typedef uint16_t font_index;
typedef uint8_t internal_font_number;
enum{font_max= 75};
typedef uint16_t font_index;
@

all the definitions from \TeX, that we need in \HINT/ go into this header file.
The header file is also included in the files that we extract directly from \TeX\
to make sure that the definitions given there agree with the definitions given here.

@(htex.h@>=
#include "basetypes.h"
#include "error.h"
@<\TeX\ types@>@;
@<\TeX\ declarations@>@;
@

\subsection{{\tt hint.h}}
@(hint.h@>=

@



\plainsection{Crossreference of Code}
\crosssections



\plainsection{References}

{\baselineskip=11pt
\rightskip 0pt plus 1fil
\def\bfblrm{\small\rm}%
\def\bblem{\small\it}%
\bibliography{hint}
\bibliographystyle{plain}
}

\plainsection{Index}
{
\def\_{{\tt \UL}} % underline in a string
\catcode`\_=\active \let_=\_ % underline is a letter
\input hint.ind
}

  \write\cont{} % ensure that the contents file isn't empty
%  \write\cont{\catcode `\noexpand\@=12\relax}   % \makeatother
  \closeout\cont% the contents information has been fully gathered
