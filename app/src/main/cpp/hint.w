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
\input epsf.tex

@i symbols.w
\makeindex
\maketoc

%\makefigindex
\titletrue

\def\lastrevision{${}$Revision: 1818 ${}$}
\def\lastdate{${}$Date: 2020-02-03 18:23:51 +0100 (Mon, 03 Feb 2020) ${}$}

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
  char *file_name; \
  HGET16(i); HGET_SIZE(s,xs,I); HGET_STRING(file_name); @/\
  hset_entry(&(E),i,s,xs,file_name); \
}
@

@<get functions@>=
static bool hget_entry(entry_t *e)
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
    default:  MESSAGE("Illegal tag %d in directory entry\n",a); return false; 
  }
  HGETTAG(z);@+
  if (a!=z)
  { MESSAGE("Tag %d does not match end tag %d in directory entry %d\n",a,z,e->section_no); return false; }
  DBG(dbgdir,"entry %d: size=0x%x xsize=0x%x\n",@|e->section_no,e->size,e->xsize);
  return true;
}
@


\subsection{Files and Sections}
Since modern computers with 64bit hardware have a huge address space,
mapping the entire file into virtual memory is the most efficient way to read a large file.
Mapping is not the same as reading and it is not the same as allocating precious memory,
all that is done by the operating system when needed. Mapping just reserves adresses.
Still we provide the function |hclose_file| to release all resources that may be accquired when
calling |ħopen_file|.

After mapping the file to the address |hbase|, access to sections of the file is provided by setting the
three pointers |hpos|, |hstart|, and |hend|.

@<\HINT/ variables@>=
uint8_t *hpos, *hstart, *hend;
static uint8_t *hbase;
#ifdef WIN32
static HANDLE hMap; 
#else
static size_t hbase_size;
#endif
@
@<get functions@>=
bool hmap_file(int fd)
{ 
#ifdef WIN32
  HANDLE hFile;
  uint64_t s;
  hFile = CreateFile(in_name,FILE_READ_DATA,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_READONLY,NULL);
  if (hFile==INVALID_HANDLE_VALUE)
  {  MESSAGE("Unable to open file %s", in_name);
     return false;
  }
  { DWORD hs,ls;
    ls=GetFileSize(hFile,&hs); 
    s=hs;
    s=s<<32;
    s=s+ls; 
  }
  if (s==0) QUIT("File %s is empty", in_name);
  hMap = CreateFileMapping( 
           hFile, /* use paging file */
           NULL,                 /* no security attributes */
           PAGE_READONLY,       /* read only access */
           0,                    /* size: high 32-bits */
           0,            /* size: low 32-bits */
           NULL);     /* name of map object */
  if (hMap == NULL)
  { MESSAGE("Unable to map file into memory");
    CloseHandle(hFile);
    return false;
  }
  hbase = MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);  
  if (hbase==NULL)
  { MESSAGE("Unable to obtain address of mapping for file %s", in_name);
    CloseHandle(hFile);
    return false;
  }
  hpos=hstart=hbase;
  hend=hstart+s;
#else 
  struct stat st;
  if (fstat(fd, &st)<0)
  { MESSAGE("Unable to get file size");
    return false;
  }
  hbase_size=st.st_size;
  hbase= mmap(NULL,hbase_size,PROT_READ,MAP_PRIVATE,fd, 0);
  if (hbase==MAP_FAILED)
  { MESSAGE("Unable to map file into memory");
    return false;
  }
  hpos=hstart=hbase;
  hend=hstart+hbase_size;
#endif
  return true;
}

void hunmap_file(void)
{
#ifdef WIN32
 UnmapViewOfFile(hbase);
 CloseHandle(hMap);
 hMap=NULL;
#else
 munmap(hbase,hbase_size);
#endif
 hbase=NULL;
 hpos=hstart=hend=NULL;
}

@

A \HINT/ file starts with a file banner\index{banner}. 
To read the banner, we have the function |hread_banner|; it returns |true| if successful.

@<get functions@>=
bool hget_banner(void)
{ char *t;
  int i;
  for (i=0;i<MAX_BANNER;i++)
  { hbanner[i]=HGET8;
    if (hbanner[i]=='\n') break;
  } 
  hbanner[++i]=0;
  t=hbanner;
  if (strncmp("hint",hbanner,4)!=0)
  { MESSAGE("This is not a hint file");
    return false;
  }
  else t+=4;
  hbanner_size=(int)strlen(hbanner);
  if(hbanner[hbanner_size-1]!='\n')
  { MESSAGE("Banner exceeds maximum size=0x%x",MAX_BANNER);
    return false;
  }
  if (*t!=' ')
  { MESSAGE("Space expected after hint");
    return false;
  }
  else t++;
  version=strtol(t,&t,10);
  if (*t!='.')
  { MESSAGE("Dot expected after version number %d",version);
    return false;
  }
  else t++;
  subversion=strtol(t,&t,10);
  if (*t!=' ' && *t!='\n')
  { MESSAGE("Space expected after subversion number %d",subversion);
    return false;
  }
  MESSAGE("hint file version %d.%d:%s",version, subversion, t);
  DBG(dbgdir,"banner size=0x%x\n",hbanner_size);
  return true;
}

@
To read a short format input file, we use the function |hget_section|. 
Unlike the version of that routine in~\cite{MR:format}, we use |mmap|
to map the entire file into memory and then just need to adjust the |hpos| pointer.
Further buffer management is needed only for compressed sections.

@<get functions@>=
static bool hbdecompress(uint16_t n);
bool hget_section(uint16_t n)
{ DBG(dbgbasic,"Reading section %d\n",n);
  RNG("Section number",n,0,max_section_no);
  if (n>max_section_no)
  { MESSAGE("Section number %d out of range [0 %d]\n",n,max_section_no);
    return false;
  }
  if (dir[n].buffer!=NULL && dir[n].xsize>0)
  { hpos=hstart=dir[n].buffer;
    hend=hstart+dir[n].xsize;
  }
  else
  { hpos=hstart=hbase+dir[n].pos; 
    hend=hstart+dir[n].size;
    if (dir[n].xsize>0)
    { if (! hbdecompress(n)) return false; }
  }
  return true;
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
static bool hbdecompress(uint16_t n) /* the bool version should move to format.w */
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
  { MESSAGE("Unable to initialize decompression: %s",z.msg);
    return false;
  }
  ALLOCATE(buffer,dir[n].xsize+SAFETY_MARGIN,uint8_t);
  DBG(dbgbuffer,"Allocating output buffer size=0x%x, margin=0x%x\n",dir[n].xsize,SAFETY_MARGIN);
  z.next_out = buffer;           
  z.avail_out =dir[n].xsize+SAFETY_MARGIN;
  i= inflate(&z, Z_FINISH);
  DBG(dbgcompress,"in: avail/total=0x%x/0x%lx "@|"out: avail/total=0x%x/0x%lx, return %d;\n",@|
    z.avail_in,z.total_in, z.avail_out, z.total_out,i);
  if (i!=Z_STREAM_END)
  { MESSAGE("Unable to complete decompression: %s",z.msg);
    return false;
  }
  if (z.avail_in != 0) 
  { MESSAGE("Decompression missed input data");
    return false;
  }
  if (z.total_out != dir[n].xsize)
  { MESSAGE("Decompression output size missmatch 0x%lx != 0x%x",z.total_out, dir[n].xsize );
    return false;
  }
  if (inflateEnd(&z)!=Z_OK)
  { MESSAGE("Unable to finalize decompression: %s",z.msg);
    return false;
  }
  dir[n].buffer=buffer;
  dir[n].bsize=dir[n].xsize;
  hpos=hstart=buffer;
  hend=hstart+dir[n].xsize;
  return true;
}
@


\subsection{Directory Section}
Except for the computation of the position, this is taken directly from~\cite{MR:format}.
@<get functions@>=

static bool hget_root(entry_t *root)
{ DBG(dbgbasic,"Get Root\n");
  if (!hget_entry(root)) return false;
  root->pos=hpos-hstart;
  max_section_no=root->section_no;
  root->section_no=0;
  if (max_section_no<2)
  { MESSAGE("Sections 0, 1, and 2 are mandatory");
    return false;
  }
  return true;
}

bool hget_directory_section(void)
{ int i;
  entry_t root={0};
  if (!hget_root(&root)) return false;
  DBG(dbgbasic,"Get Directory\n");
  new_directory(max_section_no+1);
  dir[0]=root;
  if (!hget_section(0)) return false;
  for (i=1;i<=max_section_no;i++)@/
  { if (!hget_entry(&(dir[i]))) return false;
    dir[i].pos=dir[i-1].pos +dir[i-1].size;@+
  }
  return true;
}

void hclear_dir(void)
{ int i;
  if (dir==NULL) return;
  for (i=0;i<3;i++) /* currently the only compressed sections */
  if (dir[i].xsize>0) 
	  free(dir[i].buffer);
  free(dir); dir=NULL;
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

bool hget_max_definitions(void)
{ kind_t k;
  @<read the start byte |a|@>@;
  if (a!=TAG(list_kind,0))
  { MESSAGE("Start of maximum list expected");
    return false;
  }
  @<free definitions@>@;
  hset_max();
  while (true) @/
  { uint8_t n;
    if (hpos>=hend)
    { MESSAGE("Unexpected end of maximum list");
      return false;
    }
    node_pos=hpos-hstart;
    HGETTAG(a);
    if  (KIND(a)==list_kind) break;
    if (INFO(a)!=1)
    { MESSAGE("Maximum info %d not supported",INFO(a));
      return false;
    }
    k=KIND(a);
    if (max_fixed[k]>max_default[k])
    { MESSAGE("Maximum value for kind %s not supported",definition_name[k]);
      return false;
    }
    n=HGET8;
    RNG("Maximum number",n,max_ref[k],0xFF);
    max_ref[k]=n;
    DBG(dbgdef,"max(%s) = %d\n",definition_name[k],max_ref[k]);
   @<read and check the end byte |z|@>@;
  }
  if (INFO(a)!=0)
  { MESSAGE("End of maximum list with info %d", INFO(a));
    return false;
  }
  hallocate_definitions();
  return true;
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


bool hget_definition_section(void)
{ DBG(dbgbasic,"Definitions\n");
  if (!hget_section(1)) return false;
  DBG(dbgdef,"Reading list of maximum values\n");
  if (!hget_max_definitions()) return false;
  hset_default_definitions();
  DBG(dbgdef,"Reading list of definitions\n");
  while (hpos<hend) @/
    hget_def_node();
  hget_font_metrics();
  hvsize=dimen_def[vsize_dimen_no];
  hhsize=dimen_def[hsize_dimen_no];
  return true;
}
@

@<\HINT/ variables@>=
pointer *pointer_def[32]={NULL};
@


@<\HINT/ declarations@>=
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

@<\HINT/ variables@>=
int32_t *integer_def;
@


@<allocate definitions@>=
ALLOCATE(integer_def, max_ref[int_kind]+1, int32_t);
@

@<free definitions@>=
free(integer_def); integer_def=NULL;
@

@<\HINT/ auxiliar functions@>=
static int32_t hget_integer_def(uint8_t a)
{ if (INFO(a)==1) { int8_t n=HGET8; return n;}
  else  if (INFO(a)==2) { int16_t n; HGET16(n); return n;}
  else if (INFO(a)==4) {int32_t n; HGET32(n); return n;}
  else TAGERR(a);
  return 0;
}

static int32_t hget_integer_ref(uint8_t n)
{ @+REF(int_kind,n);
  return integer_def[n];
}
@

\subsubsection{Dimensions}

@<\HINT/ variables@>=
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



\subsubsection{Extended Dimensions}

@<\HINT/ variables@>=
xdimen_t *xdimen_def;
@

@<allocate definitions@>=
ALLOCATE(xdimen_def, max_ref[xdimen_kind]+1, xdimen_t);
@
@<free definitions@>=
free(xdimen_def); xdimen_def=NULL;
@
@<\TeX\ |extern|@>=
extern void print_xdimen(int i);
@

@<\HINT/ auxiliar functions@>=
static void hget_xdimen_def(uint8_t a, uint8_t n)
{ HGET_XDIMEN(INFO(a),xdimen_def[n]);
}

static scaled hget_xdimen_ref(uint8_t n)
{ @+REF(xdimen_kind,n);
  return  xdimen_def[n].w+xdimen_def[n].h*hhsize+xdimen_def[n].v*hvsize;  
}
@

The printing routine for whatsit nodes requires a function to print extended dimensions. Since
\HINT/ never allocates a extended dimension node, the following function will suffice:
@<\HINT/ functions@>=
void print_xdimen(int i)
{}
@


\subsubsection{Glues}

@<\HINT/ auxiliar functions@>=
static pointer hget_glue_def(uint8_t a)
{ pointer p;
  HGET_GLUE(INFO(a));
  return p;
}

static pointer hget_glue_ref(uint8_t n)
{ @+REF(glue_kind,n);
  return  pointer_def[glue_kind][n];
}

pointer hget_param_glue(uint8_t n)
{ @+REF(glue_kind,n);
  return  new_glue(pointer_def[glue_kind][n]);
}
@

@<\TeX\ |extern|@>=
extern pointer hget_param_glue(uint8_t n);
@

@<allocate definitions@>=
ALLOCATE(pointer_def[glue_kind],max_ref[glue_kind]+1, pointer);
@

\subsection{Baseline Skips}
Baseline skip specifications are stored using variables of type |bs_t|.
Baseline skips are allowed only in vertical lists and
the actual baseline skip glue will be inserted just before appending the next hbox or vbox to
the list. Until then we keep a possible baseline specification on a stack that parallels \TeX's
semantic nest.

@<\HINT/ types@>=
typedef struct { pointer bs, ls; scaled lsl;} bs_t;
@

@<\HINT/ variables@>=
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
{ HGET_BASELINE(INFO(a));
  baseline_def[n].bs=cur_bs;
  baseline_def[n].ls=cur_ls;
  baseline_def[n].lsl=cur_lsl;
}

void hget_baseline_ref(uint8_t n)
{ REF(baseline_kind,n);
  cur_bs=baseline_def[n].bs;
  cur_ls=baseline_def[n].ls;
  cur_lsl=baseline_def[n].lsl;
}



pointer happend_to_vlist(pointer @!b)
{@+scaled d; /*deficiency of space between baselines*/ 
pointer @!p=null; /*a new glue node*/ 

if (needs_bs && prev_depth > ignore_depth) 
{@+d=width(cur_bs)-prev_depth-height(b);
  if (d < cur_lsl) p=new_glue(cur_ls);
  else{@+pointer q=new_spec(cur_bs);
    width(q)=d; p=new_glue(q);glue_ref_count(q)=null;
    } 
  link(tail)=p;tail=p;
  if (nest_ptr==0)
    store_map(p,cur_list.bs_pos-hstart,0);
  } 
link(tail)=b;tail=b;prev_depth=depth(b);
cur_list.bs_pos=NULL;
return p;
} 
@
@<\TeX\ |extern|@>=
extern void print_baseline_skip(int i);
extern pointer happend_to_vlist(pointer b);
@

The printing routine for whatsit nodes requires a function to print baseline skips. Since
\HINT/ never allocates a baseline skip node. the following function will suffice:
@<\HINT/ functions@>=
void print_baseline_skip(int i)
{}
@



\subsection{Fonts}\label{fonts}
\TeX\ gets ist knowlegde about fonts from font metric files. \HINT/ will not need all of that
information, but for now, the complete \TeX\ font metric file is included inside the \HINT/ file,
and we can load all that information by calling the procedure |read_font_info| defined by \TeX.
Because \TeX\ reads the font metric file using a special |fget| macro, only a few modifications,
as explained below, are necessary.

When rendering fonts, we will need to find the section containing the actual glyphs.

So we store the font name |n|, the section number for the font metrics |m| and the glyphs |q|, 
the optional ``at size'' |s|, the pointer to the font glue |g|,
the pointer to the font hyphen |h|, and the font parameters |p|.

@<\HINT/ types@>=
typedef struct {
char *n;
uint16_t m,q;
scaled s;
pointer g;
pointer h;
pointer p[MAX_FONT_PARAMS+1];
} font_def_t;
extern font_def_t *font_def;
@

@<\HINT/ variables@>=
font_def_t *font_def;
@

@<allocate definitions@>=
ALLOCATE(font_def, max_ref[font_kind]+1, font_def_t);
@

@<free definitions@>=
free(font_def); font_def=NULL;
@

@<\HINT/ auxiliar functions@>=

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
static void hget_font_def(uint8_t a, uint8_t n)
{ char *t;
  HGET_STRING(t);font_def[n].n=strdup(t); 
  DBG(dbgdef,"Font %d: %s\n", n, t); 
  if (INFO(a)&b001)  HGET32(font_def[n].s); else font_def[n].s=0;
  hget_font_params(n,&(font_def[n]));
}

static void hget_font_metrics(void)
{ int i;
  for (i=0; i<=max_ref[font_kind]; i++)
    if (font_def[i].m!=0)
    { int s; /* optional at size */
      hget_section(font_def[i].m);
      s = font_def[i].s;
      if (s==0) s=-1000;
      read_font_info(i,font_def[i].n,s);
      font_def[i].s=font_size[i];
    }
}

uint16_t hglyph_section(uint8_t f)
{   return font_def[f].q;
}
int32_t font_at_size(uint8_t f)
{  return font_def[f].s; /* at size */
}

@

We used:

@<\HINT/ declarations@>=
static pointer hget_glue_node(void);
static pointer hget_hyphen_node(void);
@
and defined
@<\HINT/ |extern|@>=
extern uint16_t hglyph_section(uint8_t f);
extern int32_t font_at_size(uint8_t f);

@

\subsection{Parameter Lists}\label{getparamlist}
There are three types of data that we allow in parameter lists: integers, dimensions,
and glue. Hence, for each parameter, we store the parameter number |n|, its kind |k|, and its value |i|, |d|, or |g|.
To form linked lists of parameter definitions, we add a |next| pointer. The variable |param_def| contains the dynamically allocated 
array of lists of parameter definitions.
@<\HINT/ types@>=
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


@<\HINT/ variables@>=
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

@<\HINT/ auxiliar functions@>=
static void free_param_list(param_def_t *p)
{ while (p!=NULL)
  { param_def_t *q=p;
    p=p->next;
    free(q);
  } 
} 
@

Next we implement reading a parameter list from a \HINT/ file.

@<\HINT/ auxiliar functions@>=
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
We used:

@<\HINT/ declarations@>=
static uint32_t hget_list_size(info_t info);
static void hget_size_boundary(info_t info);
@

Finaly, here are two functions that set and restore global parameters
based on  a parameter list.

@<\HINT/ auxiliar functions@>=
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
@<\HINT/ variables@>=
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

@<\HINT/ auxiliar functions@>=
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
#if 0
/* currently not used */
static uint8_t hget_page_ref(uint32_t pos)
{ @+int i;
  for (i=1;i<=max_ref[range_kind]; i++)
    if (range_def[i].f<=pos && pos <range_def[i].t) return range_def[i].pg;
  return 0;
}
#endif
@

\subsection{Streams}
Not yet implemented.

\subsection{Page Templates}
Not yet implemented.
@<\HINT/ variables@>=
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

@<\HINT/ auxiliar functions@>=
static void hget_page_def(uint8_t a, uint8_t n)
{ page_def[n].p=null;
}
@



\subsection{References}
There are only a few functions that still need to be defined.
@<\HINT/ auxiliar functions@>=
static pointer hget_ligature_ref(uint8_t n)
{ @+REF(ligature_kind,n);
  return copy_node_list(pointer_def[ligature_kind][n]);
}

static pointer hget_math_ref(uint8_t n)
{ @+REF(math_kind,n);
  return copy_node_list(pointer_def[math_kind][n]);
}

static pointer hget_rule_ref(uint8_t n)
{ @+REF(rule_kind,n);
  return copy_node_list(pointer_def[rule_kind][n]);
}

static pointer hget_image_ref(uint16_t n)
{ @+REF(image_kind,n);
  return copy_node_list(pointer_def[image_kind][n]);
}

static pointer hget_hyphen_ref(uint8_t n)
{ @+REF(hyphen_kind,n);
  return copy_node_list(pointer_def[hyphen_kind][n]);
}

static pointer hget_leaders_ref(uint8_t n)
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
bool hget_content_section()
{ @+DBG(dbgbasic,"Get Content\n");
  return hget_section(2);@+
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

@<\HINT/ functions@>=

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
      store_map(tail,node_pos,0);
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

#define @[HTEG8@]     (HBACK(1),hpos[0])
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
      store_map(tail,node_pos,0);
}
@

Next we continue with basic data types and then progress from the most simple to 
the most complex nodes.



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

@<\HINT/ auxiliar functions@>=
static float32_t hget_float32(void)
{  @+union {@+float32_t d; @+ uint32_t bits; @+} u;
   HGET32(u.bits);
   return u.d;
}
@

@<\HINT/ auxiliar functions@>=
static float32_t hteg_float32(void)
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

@<\HINT/ auxiliar functions@>=
static scaled hget_xdimen(uint8_t a)
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

static scaled hget_xdimen_node(void)
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

@<\HINT/ auxiliar  functions@>=
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



\subsection{Stretch and Shrink}
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

@<\TeX\ |extern|@>=
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

@<\TeX\ |extern|@>=
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

@<\TeX\ |extern|@>=
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

@<\HINT/ auxiliar functions@>=
static pointer hteg_rule_node(void)
{ @+ pointer p=null;
  @<read the end byte |z|@>@;
  if (KIND(z)==rule_kind) { HTEG_RULE(INFO(z));}
  else  QUIT("Rule expected at 0x%x got %s",node_pos,NAME(z));
  @<read and check the start byte |a|@>@;
  return p;
}
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

@<\HINT/ declarations@>=
static scaled hget_xdimen_node(void);
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


@<\HINT/ auxiliar functions@>=
static pointer hget_glue_spec(void)
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


static pointer hget_glue_node(void)
{ @+pointer p=hget_glue_spec();
  if (p!=null) p=new_glue(p);
  return p;
}
@

@<\HINT/ auxiliar functions@>=
static pointer hteg_glue_spec(void)
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


static pointer hteg_glue_node(void)
{ @+pointer p=hteg_glue_spec();
  if (p!=null) p=new_glue(p);
  return p;
}
@




@<\TeX\ |extern|@>=
extern pointer new_glue(pointer q);
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

@<\HINT/ auxiliar functions@>=
static void hget_size_boundary(info_t info)
{ @+uint32_t n;
  if (info<2) return;
  n=HGET8;
  if (n-1!=0x100-info) QUIT(@["Size boundary byte 0x%x with info value %d at " SIZE_F@],
                            n, info,hpos-hstart-1);
}

static uint32_t hget_list_size(info_t info)
{ @+uint32_t n;  
  if (info==1) return 0;
  else if (info==2) n=HGET8;
  else if (info==3) HGET16(n);
  else if (info==4) HGET24(n);
  else if (info==5) HGET32(n);
  else QUIT("List info %d must be 1, 2, 3, 4, or 5",info);
  return n;
} 

static pointer hget_node_list(uint32_t s)
{ @+ uint8_t *list_end=hpos+s;
  pointer p;
  push_nest();
  cur_list.bs_pos=NULL;
  while (hpos<list_end)
    hget_content();
  if (needs_bs) 
    QUIT("Unexpected trailing baseline node");
  p=link(head);
  pop_nest();
  return p;  
}

static pointer hget_text_list(uint32_t s)
{@+  QUIT("Text not implemented");
  return null;
}

static pointer hget_list(void)
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

@<\HINT/ auxiliar functions@>=
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
  cur_list.bs_pos=NULL;
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
  if (s>0)
    hpos = hpos - (1+ s + 1+ (INFO(z)-1) +1); /*boundary tag+s+boundary tag+size+tag*/
  else
    hpos = hpos-1;  
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


@<\HINT/ auxiliar functions@>=
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
HTEG32(height(p));\
node_pos=hpos-hstart-1;
@



@<\HINT/ declarations@>=
static float32_t hget_float32(void);
static float32_t hteg_float32(void);
static pointer hget_list(void);
static pointer hteg_list(void);
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

@<\HINT/ auxiliar functions@>=
static pointer hteg_hbox_node(void)
{ @+  @<read the end byte |z|@>@;
   if (KIND(z)!=hbox_kind) QUIT("Hbox expected at 0x%x got %s",node_pos,NAME(z));
   { @+  
    HTEG_BOX(INFO(z));@/
    @<read and check the start byte |a|@>@;
    return p;
   }
}
static pointer hteg_vbox_node(void)
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
  if ((I)&b100) x=hteg_xdimen_node(); else x=hget_xdimen_ref(HTEG8);\
  node_pos=hpos-hstart-1;
@
@<\HINT/ declarations@>=
static scaled hget_xdimen_node(void);
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
@<\HINT/ auxiliar functions@>=
static void hset(pointer p,@/
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
 if ((I)&b100) x=hteg_xdimen_node();@+  else x=hget_xdimen_ref(HTEG8);\
 node_pos=hpos-hstart-1;
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


\subsection{Baseline Skips}

@<GET macros@>=
#define @[HGET_BASELINE(I)@] \
  cur_list.bs_pos=hpos-1; \
  if((I)&b100) cur_bs=hget_glue_spec(); else cur_bs=zero_glue; \
  if((I)&b010) cur_ls=hget_glue_spec(); else cur_ls=zero_glue; \
  if((I)&b001) HGET32(cur_lsl); @+else cur_lsl=0; \
@

@<TEG macros@>=
#define @[HTEG_BASELINE(I)@] \
  if((I)&b001) HTEG32(cur_lsl); @+else cur_lsl=0; \
  if((I)&b010) cur_ls=hteg_glue_spec(); else cur_ls=zero_glue; \
  if((I)&b100) cur_bs=hteg_glue_spec(); else cur_bs=zero_glue; \
  cur_list.bs_pos=hpos-1; 
@



@<cases to get content@>=
case TAG(baseline_kind,b000): @+{@+ cur_list.bs_pos=hpos-1;hget_baseline_ref(HGET8);@+}@+break;
case TAG(baseline_kind,b010): @+{@+ HGET_BASELINE(b010);@+}@+break;
case TAG(baseline_kind,b011): @+{@+ HGET_BASELINE(b011);@+}@+break;
case TAG(baseline_kind,b100): @+{@+ HGET_BASELINE(b100);@+}@+break;
case TAG(baseline_kind,b101): @+{@+ HGET_BASELINE(b101);@+}@+break;
case TAG(baseline_kind,b110): @+{@+ HGET_BASELINE(b110);@+}@+break;
case TAG(baseline_kind,b111): @+{@+ HGET_BASELINE(b111);@+}@+break;
@

@<cases to teg content@>=
case TAG(baseline_kind,b000): @+{@+ hget_baseline_ref(HTEG8);@+ cur_list.bs_pos=hpos-1;@+ }@+break;
case TAG(baseline_kind,b010): @+{@+ HTEG_BASELINE(b010);@+}@+break;
case TAG(baseline_kind,b011): @+{@+ HTEG_BASELINE(b011);@+}@+break;
case TAG(baseline_kind,b100): @+{@+ HTEG_BASELINE(b100);@+}@+break;
case TAG(baseline_kind,b101): @+{@+ HTEG_BASELINE(b101);@+}@+break;
case TAG(baseline_kind,b110): @+{@+ HTEG_BASELINE(b110);@+}@+break;
case TAG(baseline_kind,b111): @+{@+ HTEG_BASELINE(b111);@+}@+break;
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


@<\HINT/ auxiliar functions@>=
static pointer hget_hyphen_node(void)
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

@<\HINT/ auxiliar functions@>=
static void transplant_post_break_list(void)
{ @+pointer r, q=link(head);
  int t=replace_count(q);
  pointer s=post_break(q);
  r=q;
  while (t>0 && r!=null) {@+ r=link(r); t--;@+ }
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
static void transplant_pre_break_list(void)
{ @+pointer q=tail;
  set_replace_count(q,0);
  link(q)=pre_break(q);
  pre_break(q)=null;
  while (link(q)!=null) q=link(q);
  tail=q;
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
@

Because paragraphs can be broken accross pages, we need to obtain parts of a paragraph.
For a page with a given starting point in the middle of a paragraph, we need a paragraph broken into 
lines in such a way that one of the lines starts exactly at the starting point of the page.
For a page with a given end-point, we need a paragraph broken into
lines in such a way that one of the lines ends exactly at the end-point of the page.
The combination is not needed because we are always free to choose one end of the page.

I guess that the proper thing to do is: reading the entire paragraph, modifying the line
breaking routine to force a line break at a given offset and then let the remaining program
choose which parts of the paragraph to use.

In the moment, however, I shy away from touching the line breaking routine and just feed only
part of the paragraph to the unmodified line breaking routine.

The following functions retrieve either all of the paragraph or either the initial or the final part of it.


We start with processing the entire paragraph.

@<\HINT/ auxiliar functions@>=
pointer hget_paragraph_all(scaled x)
{ @+
  uint32_t s, t;
  uint8_t a,z; /* the start and the end byte*/
  if (!IS_LIST(*hpos)) return null;
  HGETTAG(a);
  s=hget_list_size(INFO(a));
  hget_size_boundary(INFO(a)); 
  if (KIND(a)==list_kind)
  { uint8_t *list_end=hpos+s;
    cur_list.hs_field=x;
    push_nest();
  cur_list.bs_pos=NULL;
#if 0
    if (offset>0) hpos=hstart+node_pos1+offset;
#endif
    while (hpos<list_end)
    { hget_content();
      if (nest_ptr==1) 
      { pointer p=tail;
         if (p!=head && !is_char_node(p) && 
         (type(p)==glue_node || type(p)==kern_node || type(p)==penalty_node || type(p)==disc_node || type(p)==math_node))
           store_map(p,node_pos,0); /* we store the position of horizontal nodes and compute the offset of vertical nodes later */
      }
    }
    hget_size_boundary(INFO(a));
    t=hget_list_size(INFO(a)); 
    if (t!=s) 
      QUIT("List sizes at 0x%x and " SIZE_F " do not match 0x%x != 0x%x",node_pos+1,hpos-hstart-s-1,s,t);
    @<read and check the end byte |z|@>@;
#if 0    
    if (offset>0 && link(head)!=null && !is_char_node(link(head)))
    { if (type(link(head))==disc_node)
        transplant_post_break_list();
      else
        hprune_unwanted_nodes(); 
    }
#endif
    if (needs_bs) 
      QUIT("Unexpected trailing baseline node");
    if (head==tail) 
    {  pop_nest(); /*null paragraphs are ignored*/
       return null;
    }
    else
    { pointer par_ptr=link(head);
      add_par_fill_skip();
      pop_nest();      
      store_map(par_ptr,node_pos,0); 
      return par_ptr;
    }
  }
  else 
    QUIT("Text in paragraph not yet implemented");
  return null;
}
@
Next we look at retrieving the final part staring at a given position inside the paragraph.
We examine the start of the node list and replace a hyphen node by its post break list.
Otherwise we remove unwanted space from the beginning of the list.

@<\HINT/ auxiliar functions@>=
pointer hget_paragraph_final(scaled x, uint8_t *from)
{ @+
  uint32_t s, t;
  uint8_t a,z; /* the start and the end byte*/
  if (!IS_LIST(*hpos)) return null;
  HGETTAG(a);
  s=hget_list_size(INFO(a));
  hget_size_boundary(INFO(a)); 
  if (KIND(a)==list_kind)
  { uint8_t *list_end=hpos+s;
    cur_list.hs_field=x;
    push_nest();
  cur_list.bs_pos=NULL;
    hpos=from;
    while (hpos<list_end)
    { hget_content();
      if (nest_ptr==1) 
      { pointer p=tail;
         if (p!=head && !is_char_node(p) && 
         (type(p)==glue_node || type(p)==kern_node || type(p)==penalty_node || type(p)==disc_node || type(p)==math_node))
           store_map(p,node_pos,0); /* we store the position of horizontal nodes and compute the offset of vertical nodes later */
      }
    }
    hget_size_boundary(INFO(a));
    t=hget_list_size(INFO(a)); 
    if (t!=s) 
      QUIT("List sizes at 0x%x and " SIZE_F " do not match 0x%x != 0x%x",node_pos+1,hpos-hstart-s-1,s,t);
    @<read and check the end byte |z|@>@;
    if (link(head)!=null && !is_char_node(link(head)))
    { if (type(link(head))==disc_node)
        transplant_post_break_list();
      else
        hprune_unwanted_nodes(); 
    }
    if (needs_bs) 
      QUIT("Unexpected trailing baseline node");
    if (head==tail) 
    {  pop_nest(); /*null paragraphs are ignored*/
       return null;
    }
    else
    { pointer par_ptr=link(head);
      add_par_fill_skip();
      pop_nest();      
      store_map(par_ptr,node_pos,0); 
      return par_ptr;
    }
  }
  else 
    QUIT("Text in paragraph not yet implemented");
  return null;
}
@

Getting the initial part of a paragraph is even simpler.
@<get functions@>=
pointer hget_paragraph_initial(scaled x, uint8_t *to)
{ @+
  uint8_t *node_start;
  uint32_t s, t;
  uint8_t a,z; /* the start and the end byte*/
  node_start=hpos;
  HGETTAG(a);
  if (!IS_LIST(a)) 
  { hpos=node_start; return null; }
  s=hget_list_size(INFO(a));
  hget_size_boundary(INFO(a)); 
  if (KIND(a)==list_kind)
  { uint8_t *list_end=hpos+s;;
    cur_list.hs_field=x;
    push_nest();
    cur_list.bs_pos=NULL;
    while (hpos<to)
    { hget_content();
      if (nest_ptr==1) 
      { pointer p=tail;
         if (p!=head && !is_char_node(p) && 
         (type(p)==glue_node || type(p)==kern_node || type(p)==penalty_node || type(p)==disc_node || type(p)==math_node))
           store_map(p,node_pos,0); /* we store the position of horizontal nodes and compute the offset of vertical nodes later */
      }
    }
    if (KIND(*to)==hyphen_kind)
    { hget_content();
      store_map(tail,node_pos,0); 
      transplant_pre_break_list();
    }
    hpos=list_end;
    hget_size_boundary(INFO(a));
    t=hget_list_size(INFO(a)); 
    if (t!=s) 
      QUIT("List sizes at 0x%x and " SIZE_F " do not match 0x%x != 0x%x",node_pos+1,hpos-hstart-s-1,s,t);
    @<read and check the end byte |z|@>@;
    if (needs_bs) 
      QUIT("Unexpected trailing baseline node");
    if (head==tail) 
    {  pop_nest(); /*null paragraphs are ignored*/
       return null;
    }
    else
    { pointer par_ptr=link(head);
      pop_nest();      
      store_map(par_ptr,node_pos,0); 
      return par_ptr;
    }
  }
  else 
    QUIT("Text in paragraph not yet implemented");
  return null;
}
@



@<\HINT/ auxiliar functions@>=
pointer hget_paragraph(scaled x, param_def_t *q, uint32_t offset)
{ @+
  pointer p, par_head;
  hset_param_list(q); 
  par_head=tail; /* here the paragraph gets added */
  if (offset==0)
  { prev_graf=0;
    p=hget_paragraph_all(x);
  }
  else
  { prev_graf=3; /* wild guess */
    p=hget_paragraph_final(x,hstart+node_pos+offset);
  }
  if (p!=null) 
      line_break(hget_integer_ref(widow_penalty_no), p);
  hrestore_param_list();
  return par_head;
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
@<\HINT/ |extern|@>=
extern void hget_par_node(uint32_t offset);
@

When we need to read a paragraph node backwards, we simply skip to the beginning and read the node
in forward direction. The function |hteg_paragraph| therefore simply returns a ponter to the
start of the paragraph node.


@<cases to teg content@>=
case TAG(par_kind,b000): @+hteg_paragraph(b000);@+break;
case TAG(par_kind,b010): @+hteg_paragraph(b010);@+break;
case TAG(par_kind,b100): @+hteg_paragraph(b100);@+break;
case TAG(par_kind,b110): @+hteg_paragraph(b110);@+break;
@

@<\HINT/ auxiliar functions@>=
void hteg_paragraph(info_t i)
{@+scaled x=0;
  param_def_t *q;
  pointer par_head;
  uint8_t *list_start, *par_start;
  hskip_list();
  list_start=hpos;
  if (INFO(i)&b010) q=hteg_param_list_node(); else q=hget_param_list_ref(HTEG8);
  if (INFO(i)&b100) x=hteg_xdimen_node(); else x=hget_xdimen_ref(HTEG8);
  par_start=hpos;
  node_pos=par_start-hstart-1;
  hpos=list_start;
  par_head=hget_paragraph(x,q,0);
  @<Turn the paragraph upside down@>@;
  hpos=par_start;
}
@


@<get functions@>=

void hteg_par_node(uint32_t offset)
{ @+ scaled x=0;
  param_def_t *q;
  pointer p;
  @<read the start byte |a|@>@;
  node_pos=(hpos-hstart)-1;
  if (INFO(a)&b100) x=hget_xdimen_node(); else x=hget_xdimen_ref(HGET8);
  if (INFO(a)&b010) q=hget_param_list_node(); else q=hget_param_list_ref(HGET8);  
  hset_param_list(q); 
  prev_graf=0;
  p=hget_paragraph_initial(x,hstart+node_pos+offset);
  @<read and check the end byte |z|@>@;
  if (p!=null) 
  { pointer par_head=tail; /* here the paragraph gets added */
    line_break(hget_integer_ref(widow_penalty_no), p);
    @<Turn the paragraph upside down@>@;
  }    
  hrestore_param_list();
  hpos=hstart+node_pos;
}

@
@<\HINT/ |extern|@>=
extern void hteg_par_node(uint32_t offset);
@

The |hget_paragraph| function adds the individual lines in top to
bottom oder to the current list. Running the page builder in bottom
up direction requires, however, that the lines come in bottom to top
oder. The following code, removes the lines of the paragraph from the
current list, reverses the links, and attaches the list again in the new order.

@<Turn the paragraph upside down@>=
{ pointer p,r, par_tail;
  p=null;
  r=par_tail=link(par_head);
  while (r!=null)
  { pointer q=link(r);
    link(r)=p;
    p=r;
    r=q;
  }
  link(par_head)=p;
  tail=par_tail;
}
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


\section{Routines from \TeX}
\subsection{Header Files and the \TeX\ Library}
In the following, we will extract code directly from \TeX's sources to form
the \TeX\ library. For this code, it is convenient to have all of \TeX's
macro definitions in a header file; 
this file is called {\tt texdefs.h}.

We extract also a second header file, called {\tt textypes.h} that
contains all of \TeX's type definitions, including the enumeration
types that are used to define \TeX's constants. This file is again
included in the code extracted from \TeX.
The file {\tt textypes.h} is dependent only on the definition of 
basic types as given in the file {\tt basetypes.h} which is defined in {\tt format.w}.

A third file, {\tt texextern.h}, is included in the code extracted from \TeX.
@(texextern.h@>=
#ifndef _TEXEXTERN_H_
#define _TEXEXTERN_H_
#include "basetypes.h"
#include "textypes.h"
#include "hformat.h"
#include "hdefaults.h"
#include "error.h"
@<\TeX\ |extern|@>@;
#endif
@
It lists |extern| declarations of variables and functions that are extracted from \TeX.
This file is not extracted form \TeX's source code, but when 
it is included in the extracted code, the
compiler will check the decalarations against the implementation.
Further the file will include declarations of a few items that are not
implemented but rather needed by the \TeX\ library.

The additional include files {\tt hformat.h} and{\tt hdefaults.h} 
are necessary because the latter provides a replacement for
\TeX's table of equivalents and depnds on the first. 
\TeX's table of equivalents is no longer needed because \HINT/ does not define
new values. The file {\tt error.h} defines common macros to implement error handling
and debugging output.

For complex types like |memory_word| or |list_state_record|, \TeX\ uses
macros to access the various fields in a readable way. Including
the file  {\tt texdefs.h} with \TeX's macro definitions is, however,
not always a good idea. \TeX\ uses many, many macros and for historical
reasons, \TeX\ uses lowercase letters for its macros unlike
traditional \CEE/ code where only uppercase letters are used.
This entails the risk of using a macro name in\-ad\-ver\-tent\-ly as a
variable, type, or field name.  For example, \TeX\ defines the macro
``\hbox{|#define|} |x0| |152|'' which makes it impossible to use a variable
named ``|x0|'' because it would be renamed into ``|152|''.


Now let's see how to extract code from \TeX.
\changestyle{texdef.tex}

\subsection{Parameters}

\TeX's table of equivalents is no longer needed since \HINT/ will never change
any assignments. The functions of \TeX, however, use several of \TeX's variables
as parameters. These are now found as part of \HINT/'s definitions.
We modify the corresponding macros accordingly.

\changestyle{params.tex}

The variables containing the parameter definitions are declared |extern|.

@<\TeX\ |extern|@>=
extern pointer*pointer_def[32];
extern scaled*dimen_def;
extern int32_t*integer_def;
@


\subsection{Printing}

\changestyle{hprint.tex}
These are the |extern| declarations:
@<\TeX\ |extern|@>=
extern void print_str(char *s);
extern void print_char(ASCII_code @!s);
extern void overflow(char *@!s, int @!n); /*stop due to finiteness*/ 
extern void show_box(pointer p);
extern void confusion(str_number @!s);  /*consistency check violated; |s| tells where*/ 
@

\subsection{Arithmetic}

\changestyle{harith.tex}

We add external declarations. 

@<\TeX\ |extern|@>=
extern int half(int x);
extern scaled x_over_n(scaled x,int n);
extern scaled xn_over_d(scaled x, int n, int d);
@


\subsection{Memory}
\TeX's main data structure is the |mem| array. In this section, we will extract the
|mem| variable and the routines to allocate and deallocate nodes.
 
\changestyle{hmem.tex}

The following declarations will suffice:

@<\TeX\ |extern|@>=
extern memory_word *const mem; /*the big dynamic storage area*/ 
extern pointer temp_ptr;  /*a pointer variable for occasional emergency use*/ 
extern pointer @!lo_mem_max; /*the largest location of variable-size memory in use*/ 
extern pointer hi_mem_min; /*the smallest location of one-word memory in use*/ 
extern pointer @!avail; /*head of the list of available one-word nodes*/ 
extern int @!var_used, @!dyn_used; /*how much memory is in use*/ 
extern pointer get_avail(void); /*single-word node allocation*/ 
extern  pointer get_node(int @!s); /*variable-size node allocation*/ 
extern void free_node(pointer @!p, halfword @!s); /*variable-size node liberation*/ 
extern void flush_node_list(pointer @!p); /*erase list of nodes starting at |p|*/ 
extern void mem_init(void); /*initialize the memory management*/
@


\subsection{Boxes and Friends}

In this section we will export the functions that create structures in |mem|: boxes, rules, ligatures and more such things.

\changestyle{hbox.tex}

The above functions are used throughout the \HINT/ and \TeX\ code.

@<\TeX\ |extern|@>=
extern pointer new_null_box(void); /*creates a new box node*/ 
extern pointer new_rule(void);
extern pointer new_disc(void); /*creates an empty |disc_node|*/ 
extern pointer new_kern(scaled w);
extern pointer new_spec(pointer @!p); /*duplicates a glue specification*/ 
extern pointer new_ligature(quarterword @!f, quarterword @!c, pointer @!q);
extern void delete_glue_ref(pointer @!p); /*|p| points to a glue specification*/ 
extern pointer copy_node_list(pointer @!p); /*makes a duplicate of the
  node list that starts at |p| and returns a pointer to the new list*/ 
@

\subsection{Lists and Nesting}
Most of \TeX's operations are performed on the ``current list''. 
When \HINT/ reads nodes from the input file, it will follow this principle and add nodes
to the current list. Lists can be nested and the list on the outermost level is the contribution list which we encounter again in section~\secref{texbuildpage}. 
Now lets consider the modifications to \TeX's list handling.
 
\changestyle{hlist.tex}

We conclude the section with the external declarations and necessary macros.

@<\TeX\ |extern|@>=
extern void list_init(void);
extern list_state_record cur_list;
extern list_state_record nest[];
extern uint8_t nest_ptr;
extern void push_nest(void);
extern void pop_nest(void);
@

\subsection{Line Breaking}

\changestyle{hlinebreak.tex}

Here are the declarations we need to be extern:

@<\TeX\ |extern|@>=
extern scaled *const active_width;   /*distance from first active node to~|cur_p|*/ 
extern void line_break(int final_widow_penalty, pointer par_ptr);
extern void add_par_fill_skip(void);
extern pointer @!just_box; /*the |hlist_node| for the last line of the new paragraph*/ 
extern pointer @!adjust_tail; /*tail of adjustment list*/ 
extern void append_to_vlist(pointer @!b, uint32_t offset);

@

\subsection{Displayed Formulas}
\changestyle{hdisplay.tex}


@<\TeX\ |extern|@>=
extern void hdisplay(pointer p, pointer a, bool l);
@

\subsection{Packing Boxes}
\changestyle{hpack.tex}

@<\TeX\ |extern|@>=
extern  pointer hpack(pointer @!p, scaled @!w, small_number @!m);
extern pointer vpackage(pointer @!p, scaled @!h, small_number @!m, scaled @!l);
scaled *const @!total_stretch, *const @!total_shrink;  /*glue found by |hpack| or |vpack|*/ 
@


\subsection{Page Building}\label{texbuildpage}

\changestyle{hbuildpage.tex}

@<\TeX\ |extern|@>=
extern stream_t stream[256];
extern bool hbuild_page(void);
extern halfword badness(scaled @!t, scaled @!s); /*compute badness, given |t >= 0|*/ 
extern bool flush_pages(uint32_t pos); /*do this to flush the last or first page*/ 
extern uint8_t page_contents; /*what is on the current page so far?*/ 
extern pointer @!page_tail; /*the final node on the current page*/ 
extern scaled @!page_max_depth; /*maximum box depth on page being built*/ 
extern scaled @!page_depth;	/*depth of the current page*/ 
extern scaled @!page_so_far[7]; /*height and glue of the current page*/ 
extern int @!least_page_cost; /*the score for this currently best page*/ 
extern int @!insert_penalties; /*sum of the penalties for held-over insertions*/
extern pointer @!best_page_break; /*break here to get the best page known so far*/ 
extern scaled @!best_size; /*its |page_goal|*/ 

@


After |build_page| returns |true|, the finished current page is in |stream[0].p|
and the location of it is in |page_loc[cur_loc]|.

Material that may go to the next page is still on the contribution list
and also insertions for the next page are possibly already in the respective streams.
The |hpos| pointer points to the position in the content section where
parsing should continue if further material is needed for the next page.

The function |hpage_init| flushes the current page from |stream[0].p|
and initializes the variables used by the page builder to make it ready to start 
a new page.
% do not set |prev_depth=ignore_depth; prev_graf=0;| otherwise baseline skips do not work properly
@<\HINT/ functions@>=

void hpage_init(void)
{ if (stream[0].p!=null) 
    flush_node_list(stream[0].p);
  stream[0].p=null; 
  page_contents=empty;page_tail=page_head;link(page_head)=null;@/
  page_depth=0;page_max_depth=0;
}
@

When the viewer does not follow the natural sequence of pages but wants to
move to an arbitrary location in the \HINT/ file, the contribution list and the
held over insertions need to be cleared. This is done be |hclear_page|.

@<\HINT/ functions@>=
void hclear_page(void)
{ int i;
  for (i=0; i<0x100; i++)
    if (stream[i].p!=null)
    { flush_node_list(stream[i].p);
      stream[i].p=null;
    } 
  if (link(contrib_head)!=null)
  { flush_node_list(link(contrib_head));
    link(contrib_head)=null; tail=contrib_head; 
  }
}
@

@<\HINT/ |extern|@>=
extern void hclear_page(void);
@




\subsection{Font Metric Files}
In section~\secref{fonts} we mentioned the \TeX\ function  |read_font_info|. 
Now we see how to extract and modify this function from the \TeX\ sources.

\changestyle{hfont.tex}


@<\TeX\ |extern|@>=
extern char **const font_name;
extern int *const @!width_base; /*base addresses for widths*/
extern int *const @!height_base;  /*base addresses for heights*/
extern int *const @!depth_base; /*base addresses for depths*/ 
extern void read_font_info(int f, char *n, scaled s); /*input a \.{TFM} file*/ 
extern memory_word @!font_info[];
extern int *const @!char_base;  /*base addresses for |char_info|*/ 
extern eight_bits *const font_bc;  /*beginning (smallest) character code*/
extern eight_bits *const font_ec; /*ending (largest) character code*/ 
extern scaled *const font_size; /*``at'' size*/
extern scaled *const font_dsize; /*``design'' size*/

extern void hclear_fonts(void); /*clear the font memory*/
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

So here is the outline of the function |hbuild_page_up|. 

@<\HINT/ functions@>=
bool hbuild_page_up(void) /*append contributions to the current page*/ 
{@+
static scaled page_max_height;
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
Before we render the page, we add the topskip glue and
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
  {@+@<Move nodes preceeding the best page break back to the contribution list@>@;
     @<Replace leading white-space by the topskip glue@>@;
     @<Put the \(o)optimal current page into box 0@>@; 
     return true;
  } 
} 
@

When we have finaly found the best page break. It the best break is not the current node |p|,
we might have moved some material
preceeding this break already to the current page. Now we move it back to
the contribution list.

@<Move nodes preceeding the best page break back to the contribution list@>=
if (p!=best_page_break)
{ while (link(page_head)!=best_page_break)
  { q=link(page_head);
    link(page_head)=link(q);
    link(q)=null;
    tail_append(q);
  }
}
@
The following code may start with recording the newly found top of the page in the page location cache.
For a dission of why this location should or should not be recorded see section~\secref{locsetprev}.
@<Replace leading white-space by the topskip glue@>= 
hloc_set_prev(link(page_head));
while (true) {
  q=link(page_head);
  if (q==null) return false; /* empty page */
  else if (q==best_page_break) /* dont remove the page break */
    break;
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

@<Put the \(o)optimal current page into box 0@>=
if(box(0)!=null)QUIT("Box 0 must be empty");
box(0)=vpackage(link(page_head), best_size, exactly, 0x100000);
@<clean up the lists used while building the page@>@;
@


@<clean up the lists used while building the page@>=
@

\section{Recording Locations}
When a \HINT/ viewer needs to output a certain page, it must be able to position
the parser in the content section of the \HINT/ file.
For example when we want to go backwards to the previous page, 
we must position the parser where the current page starts and go backwards from there.
The start of the current page was determined
by the page builder. It is usually a penalty or glue node less often 
also a kern node. So the page builder knows the node where the page break occurs
and we simply need a way to determine the position in the content section from the
node. We could of course store the position inside each node. But this would make 
all nodes bigger and since \TeX's pointers are limited to 16 bit this is not a good idea.
A second alternative would be to generate the pages directly from
the node representations in the \HINT/ file. This is ultimatively the best solution
but requires rewriting \TeX's algorithms to work with that new representation---and I
simply don't have the time to do that.
So I choose a third alternative: 
I implement a table to map node pointers to positions.
Unfortunately , the position alone is not sufficient. Page breaks
often occur in the middle of a paragraph, and for the line breaking
algorithm, the information stored in the paragraph node is essential.
Therefore the table will store also an offset to the enclosing top level node.
(A text node---not implemented yet---will possibly need the current font.)
We call the complete information associated with the position a ``location''
and the location is what we store in the table.

\subsection{Mapping node pointers to locations}
Since \TeX's pointers are only 16-bit integers the most simple
implementation of the location table is an array indexed by the
pointer values. Since we do not need locations for character nodes
and all other nodes have two or more memory words, we can use not only
the table entry at the pointer value |p| but also the table entry at $|p|+1$.
We use the first for the node position and the second for a node's offset
from the enclosing  paragraph node 
or other node that is split across pages.

@<\HINT/ variables@>=
static uint32_t map[0x10000];
@

The first function is the initialization function that clears the table. It 
sets all records to zero. 

@<\HINT/ functions@>=
void clear_map(void)
{ @+memset(map,0,sizeof(map));
}
@

Next, we implement two
functions that operate on the table:
|store_map| stores or updates information inside the table,
and |hposition| returns for a given pointer the position inside the 
content section, or zero if no such position is known.
To delete an entry, simply call |store_map(p,0,0)|.

@<\HINT/ functions@>=
void store_map(pointer p, uint32_t pos, uint32_t offset)
{ map[p]=pos;
  map[p+1]=offset;
}

uint32_t hposition(pointer p) 
{ return map[p];
}
@  

When implementing a \HINT/ viewer, it will become necessary to store
positions inside a \HINT/ file for later use. For example, a \HINT/ viewer
may want to open a \HINT/ file exactly at the position where the user has
stopped reading last time. We do not want to burden such programs with
all the details of a |location_t| type. Hence we commit ourself to code
locations in an |uint64_t| value and will make sure that these
values contain enough information to position the \HINT/ file to
a unique and reproducible position.
To do so, we simply code the position in the low 32 bits and the
offset in the high 32 bits.


@<\HINT/ auxiliar functions@>=
uint64_t hlocation(pointer p) /* return the location of |p| or 0*/
{ @+return (uint64_t)(map[p]) + (((uint64_t)map[p+1])<<32);
}
@  

\subsection{Caching page locations}
The location table is complemented by a cache for page locations.
When we move trough a \HINT/ file by paging forward and then want to
return to the previous page, we want to see the previous page exactly
as we just have seen it. Generating the previous page based on its
bottom location may, however, produce a completely different
result because the page builder optimizes
the start of the page where as previously it had optimized the end
of the page. To obtain the same page again, we need to cache the location
of the previous page and generate it again in forward mode.

We do not cache an arbitraty amount of pages, because readers will
not remember to many pages either. We keep a limited amount
of locations sorted by their position in a circular buffer.

@<\HINT/ variables@>=
#define MAX_PAGE_POS (1<<3) /* must be a power of 2 */

uint64_t page_loc[MAX_PAGE_POS];
int cur_loc;
static int lo_loc, hi_loc;
@
@<\HINT/ |extern|@>=
extern uint64_t page_loc[];
extern int cur_loc;
@

The location of the current page is found at |page_loc[cur_loc]| which
is always defined. Pages preceeding the current page may be found
in |page_loc| at an index $i$ that is strictly beween |lo_loc| and $|cur_loc|$ 
($|lo_loc| < i < |cur_loc|$). Of course with the usual meaning of  `between'' in a circular buffer.
Similarly, we have $|cur_loc| < i <|hi_loc|$ for the index of a page
following the current page.

So lets define routines to initialize and move around the indices
in the circular buffer. |hloc_clear| clears the page location cache
except for the current page. |hloc_next| moves the current location to the next page
if there is a next page in the cache. |hloc_prev| does the same for the preceeding page.

@<\HINT/ auxiliar functions@>=
#define @[NEXT_PAGE(X)@] (X=(X+1)&(MAX_PAGE_POS-1))
#define @[PREV_PAGE(X)@] (X=(X-1)&(MAX_PAGE_POS-1))
@#
void hloc_clear(void)
{ @+lo_loc=hi_loc=cur_loc;PREV_PAGE(lo_loc);NEXT_PAGE(hi_loc);@+
}

bool hloc_next(void)
{ @+int i=cur_loc;
  if ((page_loc[cur_loc]&0xffffffff)>=hend-hstart) 
    return false;
  NEXT_PAGE(i);
  if (i==hi_loc) 
    return false;
  cur_loc=i;
  return true;
}

bool hloc_prev(void) 
{ @+int i=cur_loc;
  if (page_loc[cur_loc]==0) 
    return false;
  PREV_PAGE(i);
  if (i==lo_loc) 
    return false;
  cur_loc=i;
  return true;
}


@
@<\HINT/ |extern|@>=
extern void hloc_clear(void); /* keep only |cur_loc| in the cache */
extern bool hloc_next(void);  /* advance to the next page if possible */
extern bool hloc_prev(void);  /* advance to the previous page if possible */
@

After these preparations, we can turn our attention to the functions that manage
the page cache itself. We start with the initialization function:

@<\HINT/ functions@>=
void hloc_init(void)
{ cur_loc=0;
  hloc_clear();
  page_loc[cur_loc]=0;
  MESSAGE("loc_init: %d < %d < %d\n",lo_loc,cur_loc,hi_loc);
}  
@ 

The function |hloc_set(h)| sets the location for the current page to 
the value |h|.
In many cases, |h| {\it is} the position of the current page.
For example if only the format of the page changes. Then no action is necessary.
In other cases, the new position is already somewhere in the page cache,
for example if we follow a link, and later return to the same position.
In this case we just change |cur_loc| to point to the new position in the cache.
A more drastic action needs to be taken if the value of |h| is not in the page location cache.
if the location of the current page is new, we do not know anything about the position
of following or preceeding pages and we have to clear the cache. 

@<\HINT/ auxiliar functions@>=

void hloc_set(uint64_t h)
{ int i;
  if (page_loc[cur_loc]==h) return;
  for (i=lo_loc,NEXT_PAGE(i); i!=hi_loc; NEXT_PAGE(i))
   if (page_loc[i]==h)
   { cur_loc=i; return;}
  page_loc[cur_loc]=h;
  hloc_clear();
  MESSAGE("loc_set: %d < %d < %d\n",lo_loc,cur_loc,hi_loc);
 }
 @
 
 When we generate new pages, we discover new page locations: When paging forward,
 the bottom of the current page is the top of the next page and similar for
 paging backward. The actions required when storing the location of the next page in the
 page location cache differ in two aspects from storing the location of the current page:
 first, we might need to allocate a new entry in the cache; and second,
 assuming that the location of the current page does not change, a new location
 for the next page will not affect the locations of preceeding pages and we can
 keep them in the cache.
 
 
 @<\HINT/ auxiliar functions@>=

void hloc_set_next(pointer p)
{ @+int i=cur_loc;
  uint64_t h=hlocation(p); 

  NEXT_PAGE(i);
  if (i==hi_loc) /* allocation needed */
  {@+ if (hi_loc==lo_loc) /* deallocation needed */
      NEXT_PAGE(lo_loc);
    NEXT_PAGE(hi_loc);
    page_loc[i]=h;
  }
  else if (h!=page_loc[i])
  { page_loc[i]=h;
    NEXT_PAGE(i);
    hi_loc=i;
  }
  MESSAGE("loc_set_next: %d < %d < %d\n",lo_loc,cur_loc,hi_loc);
}
@


After these preparations, setting the position of the previous page should be no surprise.
It is, however, questionable whether we should record these positions in the page 
location cache. Just consider the following:\label{locsetprev}
We discover new preceeding pages when paging backwards.
While doing so, we generate pages in backward mode, optimizing the start of the page.
When we later return to these pages, we are paging forward and therefore
generate pages in forward mode optimizing the bottom of the page.
Hence, the pages might still look different. 

Since the function |hloc_set_prev| is called only after generating a new page in backward
mode, we will set the current page to the new location and keep only the position of the 
old current page as position of the next page in the cache.

@<\HINT/ auxiliar functions@>=
void hloc_set_prev(pointer p)
{ @+int i=cur_loc;
  uint64_t h=hlocation(p); 
  PREV_PAGE(i);
  if (i==lo_loc) /* allocation needed */
  {@+ if (lo_loc==hi_loc) /* deallocation needed */
      PREV_PAGE(hi_loc);
    PREV_PAGE(lo_loc);
    page_loc[i]=h;
  }
  else if (h!=page_loc[i])
  { page_loc[i]=h;
    lo_loc=i;
    PREV_PAGE(lo_loc);
  }
  hi_loc=cur_loc;
  NEXT_PAGE(hi_loc);
  cur_loc=i;
  MESSAGE("loc_set_prev: %d < %d < %d\n",lo_loc,cur_loc,hi_loc);
}
@

The following functions are used inside the \TeX\ library:

@<\TeX\ |extern|@>=
extern void hloc_init(void);
extern void store_map(pointer p, uint32_t pos, uint32_t offset); /*store the location of |p|*/
extern uint32_t hposition(pointer p); /* return the position of |p| or 0*/
extern void hloc_set(uint64_t h);
extern void hloc_set_next(pointer p);/* record the location of |p| as the start of the next page */
@

\section{The Top-Level Interface}
The \HINT/ library seeks to provide a basis for the implementation of \HINT/ viewers. For this purpose,
it presents a top-level functional interface which strives to be easy to use and yet exposes 
the necessary functionality to allow different viewers on different systems.

\subsection{Opening and Closing a \HINT/ File}
The first function an application needs to call is |hint_begin| and the last function is |hint_end|.
The former opens the file and prepares the system to be ready for all the functions that follow;
the latter will release all resources obtained when calling one of the top level \HINT/ functions
returning the system to the state it had before calling |hint_begin|.

@<\HINT/ functions@>=
static bool hint_is_open=false;
int hint_begin(int fd)
{ if (hint_is_open) 
    hint_end();
  mem_init();
  list_init(); 
  hclear_dir();
  hclear_fonts();
  hloc_init();
  if (hmap_file(fd)&&
      hget_banner()&&
      hget_directory_section() &&
      hget_definition_section() &&
      hget_content_section())
  { leak_clear();
    clear_map();
    hint_is_open=true;
    return 1;
  }
  else
  { hstart=hpos=hend=NULL;
    return 0;
  }
}


void hint_end(void)
{ if (!hint_is_open) return;
  hclear_page();
  list_leaks();
  hunmap_file();
  hclear_dir();
  hint_is_open=false;
}
@


@<\HINT/ |extern|@>=
extern int hint_begin(int fd);
extern void hint_end(void);
@

\subsection{Building Pages Forward and Backward}
After opening the \HINT/ file, \HINT/ viewers need a to be able to move forward to
the next page. Here is the function to do that.

@<\HINT/ functions@>=
bool hint_forward(void)
{ hpage_init();
  if (hbuild_page()) return true;
  while (hpos<hend)
  { hget_content();
    if (hbuild_page()) return true;
  }
  while (!flush_pages(hend-hstart))
   if (hbuild_page()) return true;
return false;
}
@
The function sets the |forward_mode| variable to |true| to indicate that the current page
was produced in forward mode.
Then the function |hpage_init| returns the ``old'' current page, stored in |stream[0].p|, to
free storage and initializes the variables that control the page building process.
It is then assumed that any material still on the contribution list should fill the
new page top to bottom. The call to |hbuild_page| will move any such material 
to the new page. Further material is then taken from the \HINT/ file with parsing starting 
at |hpos| which should point to a top level node.
If the end-of-file is reached before the (nonempty) page is completed, a call to |flush_pages|
adds some glue and a penalty to eject the page.

The page builder usually considers material from the \HINT/ file until the page
becomes overfull before it backs up to the position of the best page break.
The extra material past this break is put back on the contribution list
in preparation for the next page. The |hpos| pointer to the \HINT/ file will then
point to the position where parsing should continue.
Last not least, the page builder will store the location of the page break
in the location cache as starting point for the next page.

To summarize: If the variable |forward_mode| is |true|, the |hint_forward| function
can be called to produce the next page reusing all the work already done while
producing the current page. In the location cache, we will have at least two enties: 
the top of the current page and the top of the next page.



Similarly, we implement paging backward.
 @<\HINT/ functions@>=
bool hint_backward(void)
{ hpage_init();
  if (hbuild_page_up()) return true;
  while (hpos>hstart)
  { hteg_content();
    if (hbuild_page_up()) return true;
  }
  while (!flush_pages(0x0))
    if (hbuild_page_up())  return true;
  return false;
}
@
Here the |backward_mode| variable is set to |true|. It imples that the material in the contribution list
belongs to the bottom of the preceeding page and |hpos| will
indicate where parsing should contine when producing the previous page.
Again in the location cache are at least two enties: the top of the current page and the top of the next page.

@<\HINT/ |extern|@>=
extern bool hint_forward(void);
extern bool hint_backward(void);
@

When the page builder has reached the end of the \HINT/ file, it must make sure that
the material that might still be in the contribution list gets flushed out.
To do so the function |flush_pages| adds some space and a large negative penalty.
Calling one of the previous functions will then deliver the remaining pages.
@<\HINT/ functions@>=
bool flush_pages(uint32_t pos)
{ pointer p=link(head);
  while (p!=null && 
         (type(p)==penalty_node || type(p)==glue_node || type(p)==kern_node)) 
     p=link(p);
  if (p==null && link(page_head)==null)  return true; /* nothing left */
  tail_append(new_null_box());
  width(tail)= hhsize;
  tail_append(hget_param_glue(fill_skip_no));
  store_map(tail,pos,0);
  tail_append(new_penalty(-010000000000));
  store_map(tail,pos,0);
  return false;
}
@
We needed:

@<\HINT/ variables@>=
scaled hvsize, hhsize;
@
@<\TeX\ |extern|@>=
extern scaled hvsize, hhsize;
@
The variables |hvsize| and |hhsize| give the vertical and horizontal size
of the main body of text. They are determined by subtracting the margins from
|page_v| and |page_h| as determined by the GUI.

The five functions defined so far consitute a minimal basis for processing \HINT/ files.
Section~\secref{testing} presents two programs, used to test the \HINT/ engine, which are
implemented with just these functions.

\subsection{Page Composition}
The page builder of \HINT/, to tell the truth, is not building the page, it is just assembling
the material that should be displayed on the page: the main body of text and floating material
like footnotes or illustrations.
To make a nice looking page, we need to combine the material properly and put margins around all that.

The next function is the default function to compute the margins.
Given the horizontal and vertical dimensions of the page as |page_h| and |page_v|,
it computes the horizontal and vertical dimensions of the main body of text 
as well as the offset of its top/left position. The dimensions are given in scaled points.

@<render variables@>=
int page_v, page_h, offset_v, offset_h;
@


The formula use here will result in a 1 inch margin for a 
letter size page---that's the old default of plain \TeX---and decreases the magins for smaller pages
until the margin becomes zero for a page that is merely 1 inch wide.


@<render functions@>=
 static void hset_margins(void)
{  offset_h=page_h/8- 0x48000;
   if (offset_h<0) offset_h=0;
   offset_v=page_v/8- 0x48000;
   if (offset_v<0) offset_v=0;
   if (offset_h>offset_v) offset_h=offset_v;
   else offset_v=offset_h;
   hhsize=page_h-2*offset_h;
   hvsize=page_v-2*offset_v;
   if (hhsize<=0) hhsize=page_h,offset_h=0;
   if (hvsize<=0) hvsize=page_v,offset_v=0;
}
@
A more sophisticated page composition can be achived with page templates (which are not yet
implemented). Here is the build-in page template number 0 which attaches the margins to
the box contructed by the page builder.

@<render functions@>=
static void houtput_template0(void)
{ pointer p,q,t,b,l,r;
 if (stream[0].p==null) return;
 
  q=new_spec(zero_glue);  width(q)=offset_h;
  l=new_glue(q);glue_ref_count(q)=null;
  r=new_glue(q);
  q=new_spec(zero_glue);  width(q)=offset_v;
  t=new_glue(q);glue_ref_count(q)=null;
  b=new_glue(q);
  
  p=stream[0].p;
  link(p)=r;
  link(l)=p; 
  p=hpack(l,page_h,exactly);
  link(p)=b;
  link(t)=p;
  p=vpackage(t,page_v,exactly,0);
  stream[0].p=p; 
 }
@

\subsection{Moving around in the \HINT/ file}
The basic capability of \HINT/ is rendering a page that starts at a given position in the
\HINT/ file. The function |hint_page_top| provides this capability.
It starts by clearing the memory from all traces left from building previous pages
and computes |hhsize| and |hvsize|.
Then it parses a partial paragraph---if necessary---and calls |hint_forward| to build the page.
It attaches the margins and renders it.
As all functions in this section, it returns the location of the new current page.
The viewer might store this location to be able to return to this page at a later time.

@<render functions@>=
static void hrender_page(pointer p);

uint64_t hint_page_top(uint64_t h)
{ if (hpos==NULL) return hint_blank();
  hloc_set(h);
  hclear_page();
  hset_margins();
  hpos=hstart+(h&0xffffffff);
  if (hpos>=hend)
    return hint_page_bottom(hend-hstart);
  if (h>0xffffffff)
    hget_par_node(h>>32);
  hint_forward();
  forward_mode=true;
  backward_mode=false;
  houtput_template0();
  hrender_page(stream[0].p);
  return h;
}
@

Using the previous function, we implement |hint_page| which rerenders the current page
possibly in a different format.
All we need to so is a function to obtain its top position: |hint_page_get|.

@<render functions@>=
uint64_t hint_page_get(void)
{@+
 MESSAGE("page_get: %d : 0x%" PRIx64 "\n",cur_loc,page_loc[cur_loc]);
@/ 
return page_loc[cur_loc];
 }

uint64_t hint_page(void)
{ return hint_page_top(hint_page_get());
}
@
To display the first page simply call |hint_page_top(0)|.

Now let's consider moving to the next page. 
If we produced the current page using |hint_forward|, we can simply call
|hint_forward| again. For this reason we use the variables  |forward_mode| and |backward_mode|
to keep track of the direction.
@<render variables@>=
static bool forward_mode=false, backward_mode=false;
@
If we are neither in forward nor backward mode, there is no current page and hence no next page.
In this case, we just render the first page.
@<render functions@>=
uint64_t hint_next_page(void)
{ if (hpos==NULL) return hint_blank();
  if (hloc_next()&& forward_mode)
  { hset_margins();
    if (!hint_forward())
	{ hloc_prev(); return hint_page(); }	
    forward_mode=true;
    backward_mode=false;
    houtput_template0();
    hrender_page(stream[0].p);
    return hint_page_get();
  }
  else 
    return hint_page();
}
@

Things are a bit more complex for paging backwards. The page that we produce here is usually
different from what \HINT/ will produce in forward mode.
First we check the location cache. If there is an entry for the preceeding page,
we will take the location and produce the page in forward mode, because this way the
reader can get the same page as seen before. If we do not have a cached page location,
we build the page based on its bottom position.
If we are lucky, we are in backward mode. In this case, we do not need to
throw away the information in the contribution list and we call |hint_backward|.
@<render functions@>=
uint64_t hint_prev_page(void)
{ if (hpos==NULL) return hint_blank();
  if (hloc_prev())
    return hint_page();
  else if (backward_mode)
  { hset_margins();
    if (!hint_backward())  return hint_page();
    backward_mode=true;
    forward_mode=false;
    houtput_template0();
    hrender_page(stream[0].p);
    return hint_page_get();
  }
  else
    return hint_page_bottom(hint_page_get());
}
@
In the worst case, we don't have a cached location and are not in backward mode. This is the
case handled by |hint_page_bottom|.

As we did in |hint_page_top|, we clear the memory from all traces left from building other pages,
compute the margins, parse a partial paragraph---if necessary---and call |hint_backward| 
to build the page.
If successfull, it will set |cur_loc| to the current page. Finally, we attach the margins, render the page,
and return the new location.
@<render functions@>=
uint64_t  hint_page_bottom(uint64_t h)
{ if (hpos==NULL) return hint_blank(); 
  hclear_page();
  hset_margins();
  hpos=hstart+(h&0xffffffff);
  if (h>0xffffffff)
    hteg_par_node(h>>32);
  if (!hint_backward())  return hint_page();
  backward_mode=true;
  forward_mode=false;
  houtput_template0();
  hrender_page(stream[0].p);
  return hint_page_get();
}
@
A function to build a page centered around a given location completes the set of
page building functions.
@<render functions@>=
uint64_t  hint_page_center(uint64_t h)
{ if (hpos==NULL) return hint_blank();
  QUIT("hint_page_center not yet implemented");
}
@


\subsection{Changing the page dimensions}
A central feature of a \HINT/ viewer is its ability to change the dimensions and the
resolution of the displayed pages. To do so the function |hint_resize| is called.
@<render functions@>=
void hint_resize(int px_h, int px_v, double dpi)
{ nativeSetSize(px_h, px_v, dpi);
  hloc_clear();
  hclear_page();
  forward_mode=false;
  backward_mode=false;
}
@
The function tells the native renderer about the change, clears all locations
from the location cache, removes nodes from the contribution list,
and resets the rendering direction.


\section{Rendering \HINT/ Files}
How to render a \HINT/ file on any specific device depends largely on the
operating system and its API encapsulating the device. Never the less, there
are some functions that can be shared accross many different operating systems
or at least can serve as a starting point for implementing operating system specific
versions.

\subsection{Fonts}
The \HINT/ file format supports four different types of fonts: The traditional PK fonts\cite{TR:pkfile},
PostScript Type1 fonts\cite{PST1} which are used by many \TeX\ engines, 
TrueType\cite{TTT:TT} fonts, and OpenType fonts\cite{MS:OTF}\cite{ISO:OTF}.

@<font types@>=
typedef	enum {@+ no_format, pk_format, t1_format, ot_format, tt_format@+ } font_format_t;
@


The features of a font are described in a |font_s| structure.
A major part of the structure is the glyph cache that provides fast access to the individual glyphs
belonging to the font. Further, it includes an |ff| field containing the font format and a variant part 
that differs for the different font formats.


@<font types@>=
@<definitions of |pk_t|, |t1_t|, |ot_t|, and |tt_t| types@>@;

typedef struct font_s {
  unsigned char n; /* the font number */
  unsigned char *font_data; /* pointer to the font data in the HINT file */
  int size; /* the size of the font data in byte */
  double ds; /* the design size in pt */
  double hppp,vppp; /* the horizontal and vertical pixel per point */
  @<the font cache@>@;
  font_format_t ff; /* the font format */
  union { /* the font format specific parts */
	  pk_t pk;
	  tt_t tt;
	  t1_t t1;
	  ot_t ot;
  };
} font_t;
@
The |fonts| table contains an entry for every possible font number.

@<font variables@>=
static font_t *fonts[0x100]={NULL}; 
@

Given a font number |f| the following function returns a pointer to the 
corresponding font structure, extracting the necessary information from the \HINT/
file if necessary.
@<font functions@>=
struct font_s *hget_font(unsigned char f)
{ font_t *fp;
  if (fonts[f]!=NULL) return fonts[f];
  fp = calloc(1,sizeof(*fp));
  if (fp==NULL) 
    QUIT("Out of memory for font %d",f);
  else
  { unsigned char *spos, *sstart, *send;
    spos=hpos; sstart=hstart;send=hend;
    fp->n=f;
    hget_section(hglyph_section(f));
    fp->size=hend-hstart;
    fp->font_data=hstart;
    hpos=spos; hstart=sstart;hend=send;
  }
  @<determine the font format and unpack the font@>@;
  fonts[f]=fp;
  return fonts[f];
}
@
This function is used in the renderer, so it is exported together with an
opaque pointer type to the font structure.
@<font |extern|@>=
typedef struct font_s *font_s_ptr;
extern struct font_s *hget_font(unsigned char f);
@

To initialize the |fonts| table and remove all fonts form memory, the |hint_clear_fonts| function is used
with the |rm| parameter set to |true|.

@<font functions@>=
static void hfree_glyph_cache(font_t *f, bool rm);

void hint_clear_fonts(bool rm)
{ int f;
  for (f=0;f<=max_ref[font_kind];f++)
    if (fonts[f]!=NULL)
    { hfree_glyph_cache(fonts[f],rm);
      if (rm) {  free(fonts[f]); fonts[f]=NULL; }
    }
}
@






\subsubsection{The Font Cache}
If possible, the glyphs belonging to a font are extracted only once from the font data,
converted into a format suitable for the native rendering engine, and then cached for repeated use.
The cached glyph representation for glyph |g| is stored in one of four trees. 
The order and depth of the trees reflects UTF-8 encoding.
   The first tree is of oder $2^7$ and only 1 level deep; its root is |g0|.
   The other trees, |g1|, |g2|, and |g3| are of order $2^6$ and have a depth
   of 2, 3, and 4 levels respectively.

@<the font cache@>=
  struct gcache_s **g0; /* $0 \le |g| < 2^7$ */
  struct gcache_s ***g1;  /* $2^7 \le |g| < 2^{12}$ */
  struct gcache_s ****g2; /* $2^{12} \le |g| < 2^{18}$ */
  struct gcache_s *****g3; /* $2^{18} \le |g| < 2^{24}$ */@/
@t~@>
@


The glyphs are described using a |gcache_s| structure. 
We use |gcache_t| as a shorthand for |struct gcache_s|.

@<font types@>=
typedef struct gcache_s gcache_t;
@
 
To look up the cached glyph data for font |f| and charactercode |cc|, we use the function |g_lookup|.

@<font functions@>=
#define G0_BITS 7
#define G0_SIZE (1<<G0_BITS)
#define G0_MASK (G0_SIZE-1)
#define G123_BITS 6
#define G123_SIZE (1<<G123_BITS)
#define G123_MASK (G123_SIZE-1)

static gcache_t *g_lookup(font_t *f, unsigned int cc)

{ if (cc >> G0_BITS) {
	unsigned int cc1= (cc>>G0_BITS);
	if (cc1>>G123_BITS) {
		unsigned int cc2= cc1>>G123_BITS;
		if (cc2>>G123_BITS) {
			unsigned int cc3=cc2>>G123_BITS;
			if (cc3>>G123_BITS) return NULL;
			else if (f->g3 && 
				f->g3[cc3&G123_MASK] && 
				f->g3[cc3&G123_MASK][cc2&G123_MASK] &&  
				f->g3[cc3&G123_MASK][cc2&G123_MASK][cc1&G123_MASK])  
			return f->g3[cc3&G123_MASK][cc2&G123_MASK][cc1&G123_MASK][cc&G0_MASK];
		}
		else if (f->g2 && f->g2[cc2&G123_MASK] && f->g2[cc2&G123_MASK][cc1&G123_MASK]) 
			return f->g2[cc2&G123_MASK][cc1&G123_MASK][cc&G0_MASK];
	}
	else if (f->g1 && f->g1[cc1&G123_MASK]) 
		return f->g1[cc1&G123_MASK][cc&G0_MASK];
  }
  else if (f->g0) 
	  return f->g0[cc];
  return NULL;
}
@

But of course, before we can look up entries, we have to allocate new entries.
The actual entries are allocated with |hnew_g|. The functions |hnew_g0| to
|hnew_g3| allocate the necessary path from the root to the leaf, and 
the function |hnew_glyph| provides the top level function:
Given a font and a charactercode it returns a pointer to the glyph,
allocating a glyph if none is yet allocated, and returning a pointer to ``the undefined glyph''
if no more memory is available.

@<font variables@>=
static gcache_t g_undefined ={0};
@

@<font functions@>=
static gcache_t *hnew_g(gcache_t **g)
{ if (*g==NULL)
    *g=calloc(1, sizeof(gcache_t));
  if (*g==NULL) 
    return &g_undefined;
  (*g)->ff=no_format;
  return *g;
}

static gcache_t *hnew_g0(gcache_t ***g,unsigned int cc)
{ unsigned int cc0=cc&G0_MASK;
  if (*g==NULL)
    *g=calloc(G0_SIZE, sizeof(gcache_t*));
  if (*g==NULL) 
    return &g_undefined;
  return hnew_g((*g)+cc0);
}
 
static gcache_t *hnew_g1(gcache_t ****g,unsigned int cc)
{ unsigned int cc1=(cc>>G0_BITS)&G123_MASK;
  if (*g==NULL)
    *g=calloc(G123_SIZE, sizeof(gcache_t**));
  if (*g==NULL) 
    return &g_undefined;
  return hnew_g0((*g)+cc1,cc);
}
static gcache_t *hnew_g2(gcache_t *****g,unsigned int cc)
{ unsigned int cc2=(cc>>(G123_BITS+G0_BITS))&G123_MASK;
  if (*g==NULL)
    *g=calloc(G123_SIZE, sizeof(gcache_t***));
  if (*g==NULL) 
    return &g_undefined;
  return hnew_g1((*g)+cc2,cc);
}
  
static gcache_t *hnew_g3(gcache_t ******g,unsigned int cc)
{ unsigned int cc3=(cc>>(G123_BITS+G123_BITS+G0_BITS))&G123_MASK;
  if (*g==NULL)
    *g=calloc(G123_SIZE, sizeof(gcache_t****));
  if (*g==NULL) 
    return &g_undefined;
  return hnew_g2((*g)+cc3,cc);
}


static gcache_t *hnew_glyph(font_t *pk, unsigned int cc)
{ if (cc<G0_SIZE) return hnew_g0(&(pk->g0),cc);
  else if (cc<G123_SIZE*G0_SIZE) return hnew_g1(&(pk->g1),cc);
  else if (cc<G123_SIZE*G123_SIZE*G0_SIZE) return hnew_g2(&(pk->g2),cc);
  else if (cc<G123_SIZE*G123_SIZE*G123_SIZE*G0_SIZE) return hnew_g3(&(pk->g3),cc);
  else return &g_undefined;
}
@

The next set of functions is used to clear the glyph cache.
If the boolean parameter |rm| is true, the complete cache will 
be deallocated.

@<font functions@>=
static void hfree_g0(struct gcache_s **g, bool rm)
{ int i;
  if (g==NULL) return;
  for (i=0;i<G0_SIZE;i++)
    if (g[i]!=NULL)
    { nativeFreeGlyph(g[i]);
      if (rm) {
      if (g[i]->bits!=NULL) free(g[i]->bits);
      free(g[i]); g[i]=NULL;@+ }
    }
}

static void hfree_g1(struct gcache_s ***g, bool rm)
{ int i;
  if (g==NULL) return;
  for (i=0;i<G123_SIZE;i++)
	if (g[i]!=NULL)
	{ hfree_g0(g[i],rm);
      if (rm) {free(g[i]); g[i]=NULL;@+ }
	}
}

static void hfree_g2(struct gcache_s ****g, bool rm)
{ int i;
  if (g==NULL) return;
  for (i=0;i<G123_SIZE;i++)
	if (g[i]!=NULL)
	{ hfree_g1(g[i],rm);
      if (rm) {free(g[i]); g[i]=NULL;@+ }
	}
}


static void hfree_g3(struct gcache_s *****g, bool rm)
{ int i;
  if (g==NULL) return;
  for (i=0;i<G123_SIZE;i++)
	if (g[i]!=NULL)
	{ hfree_g2(g[i],rm);
      if (rm) {free(g[i]); g[i]=NULL;@+ }
	}
}


static void hfree_glyph_cache(font_t *f, bool rm)
{ if (f->g0!=NULL)
  { hfree_g0(f->g0,rm);
     if (rm) {free(f->g0); f->g0=NULL;@+}
  }
  if (f->g1!=NULL)
  { hfree_g1(f->g1,rm);
     if (rm) {free(f->g1); f->g1=NULL;@+}
  }
  if (f->g2!=NULL)
  { hfree_g2(f->g2,rm);
     if (rm) {free(f->g2); f->g2=NULL;@+}
  }
  if (f->g3!=NULL)
  { hfree_g3(f->g3,rm);
     if (rm) {free(f->g3); f->g3=NULL;@+}
  }
}
@
\subsection{Glyphs}
The |gcache_s| structure may depend on the font encoding
but also on the rendering engine that is used to display the glyphs. While the dependency on the
font encoding is dynamic, the dependency on the rendering engine can be resolved at compile time.

Every |gcache_s| structure stores |w| and |h|, the width and height of the minimum bounding box in pixel;
 |hoff| and |voff|, the horizontal and vertical offset in pixel from the upper left pixel to the 
reference pixel (right and down are positive).
Then follows the representation of the glyph that is most convenient for rendering on the
target sytem. For the Windows operating system, this is a byte array containing a device independent bitmap.
For the Android operting system using OpenGLE 2.0 it's again a byte array for the bitmap and an identifier
for the texture.
Then there is a last part that is different for the different font encodings; it is prefixed
by the font format number |ff|. The information in this last part 
helps with on-demand decoding of glyphs.


@<font types@>=
@<definitions of |pkg_t|, |t1g_t|, |otg_t|, and |ttg_t| types@>@;

struct gcache_s {
  int w,h; 
  int hoff,voff; 
  unsigned char *bits; 
#ifdef __ANDROID__
   unsigned int GLtexture;
#endif
  font_format_t ff; 
  union {@+
	  pkg_t pk;
	  ttg_t tt;
	  t1g_t t1;
	  otg_t ot;@+
  };
};
@

The above structure has a |GLtexture| member if rendering is done on the Android operating system
using OpenEGL 2.0. To speed up the rendering of glyphs, the glyph bitmap is loaded into the graphics cards
as a texture and from then on identified by a single integer, the |GLtexture|.

Occasionaly, however, the front-end will change the OpenGL context and the texture identifiers
will loose their meaning. In this situation, it is not necessary to wipe out the entire glyph
cache with all the extracted bitmaps but only the invalidation of the texture identifiers is needed.
This effect can be achived by calling |hint_clear_fonts(false)|. It will call |nativeFreeGlyph|
for all glyphs and this function can set the |GLtexture| value to zero.


The top level function to access a glyph is |hget_glyph|. Given a font pointer |fp| 
and a character code |cc| it looks up the glyph in the font cache.
For PK fonts, all cache entries are made when initializing the font.
For TrueType fonts, a cache entry is made when the glyph is accessed the first time.
For both types of fonts, the unpacking is done just before the first use.

@<font functions@>=
gcache_t *hget_glyph(font_t *fp, unsigned int cc)
{
  gcache_t *g=NULL;
  g=g_lookup(fp,cc);
  if (g==NULL)
  { if (fp->ff==tt_format)
      g=hnew_glyph(fp,cc);
    else  
      return NULL;
  }
  if (g->ff==no_format)           
  { if (fp->ff==pk_format) pkunpack_glyph(g);
    else if (fp->ff==tt_format) ttunpack_glyph(fp,g,cc);
    else
                QUIT("tt t1 and ot formats not yet supported");
  }
  return g;
}
@

Rendering a glyph is the most complex rendering procedure. But with all the preparations,
it boils down to a pretty short function to display a glyph, given by its charcter code |cc|,
from font |f| at |x|, |y| in size |s|.
@<font functions@>=
void render_char(int x, int y, struct font_s *f, int32_t s, uint32_t cc)

{ double w, h, dx, dy, m;
  gcache_t *g=hget_glyph(f,cc);
  if (g==NULL) return;
  /* account for scaled fonts */
  if (s==0) m=1.0;
  else m=((double)s/(double)(1<<16))/f->ds; /* |s| is scaled by |1<<16| but |ds| is scaled by |1<<20| */
  dx=((double)g->hoff/f->hppp)*m;
  dy=((double)g->voff/f->vppp)*m;
  w =((double)g->w/f->hppp)*m;
  h =((double)g->h/f->vppp)*m;

  nativeGlyph(SP2PT(x)-dx,SP2PT(y)-dy,w,h,g);
}

@
@<font |extern|@>=
extern void render_char(int x, int y, struct font_s *f, int32_t s, uint32_t cc);
@

\subsection{Rules}
Rendering rules, that is black rectangles, is simpler.
The only task here is to convert \TeX's and \HINT/'s measuring system,
that is scaled points stored as 32 bit integers, into a representation that is more convenient for
non \TeX{nical} sytems, namely regular points stored as floating point values. The macro |SP2PT|
does the job.
@<render macros@>=
#define SP2PT(X) ((X)/(double)(1<<16))
@
Now we can render a rule:
@<render functions@>=
static void render_rule(int x, int y, int w, int h)
{ if (w<=0) return;
  if (h<=0) return;
  nativeRule(SP2PT(x),SP2PT(y),SP2PT(w),SP2PT(h));
}
@

\subsection{Images}
When we need to render an image, we should not bother the native renderer with finding the
image data in segment |n| of the \HINT/ file. Instead we pass a pointer to the first byte and a pointer
past the last byte. We also pass the position and size as we did for rules.
@<render functions@>=
void render_image(int x, int y, int w, int h, uint32_t n)
{ 
  uint8_t *spos, *sstart, *send;
  spos=hpos; sstart=hstart;send=hend;
  hget_section(n);
  nativeImage(SP2PT(x),SP2PT(y),SP2PT(w),SP2PT(h),hstart,hend);
  hpos=spos; hstart=sstart;hend=send;
}
@



\subsection{Lists}
Now at last, we can render vertical and horizontal list. Two mutualy recursive procedures will
accomplish the rendering. The functions are more or less modifications of \TeX's functions
that write DVI files. They share a few global static variables that implement the
current state of the renderer: |cur_h| and |cur_v| contain the current horizontal
and vertical position; 
|rule_ht|, |rule_dp|, and |rule_wd| contain the height, depth, and width of a rule that should
be output next;
|cur_f| and |cur_fp| contain the current font number and current font pointer.


@<render functions@>=
static scaled cur_h, cur_v;
static scaled rule_ht, rule_dp, rule_wd; 
static int cur_f; 
static struct font_s *cur_fp;
static int32_t cur_at_size; 

static void vlist_render(pointer this_box);

static void hlist_render(pointer this_box)
{ scaled base_line;
scaled left_edge;
scaled save_h;
glue_ord g_order;
uint8_t g_sign;
pointer p;
pointer leader_box;
scaled leader_wd;
scaled lx;
scaled edge;
double glue_temp;
double cur_glue;
scaled cur_g;

cur_g= 0;
cur_glue= 0.0;
g_order= glue_order(this_box);
g_sign= glue_sign(this_box);
p= list_ptr(this_box);
base_line= cur_v;
left_edge= cur_h;

while(p!=null)
{ reswitch:
  if(is_char_node(p))
  { do 
	{ uint8_t f= font(p);
	  uint32_t c= character(p);
      if(f!=cur_f)
      { cur_fp=hget_font(f);
	    cur_f= f;
	    cur_at_size=font_at_size(f);
      }
	  render_char(cur_h, cur_v, cur_fp, cur_at_size,c);
      cur_h= cur_h+char_width(f)(char_info(f)(c));
      p= link(p);
    } while(!(!is_char_node(p)));
  }
  else
  { switch(type(p)) 
    { case hlist_node:
     case vlist_node:
       if(list_ptr(p)==null) cur_h= cur_h+width(p);
       else
	   { cur_v= base_line+shift_amount(p);
         edge= cur_h;
         if(type(p)==vlist_node) 
			 vlist_render(p);
		 else 
			 hlist_render(p);
         cur_h= edge+width(p);cur_v= base_line;
       }
       break;
     case rule_node:
	   rule_ht= height(p);rule_dp= depth(p);rule_wd= width(p);
       goto fin_rule;
     case whatsit_node:
		if (subtype(p)==image_node)
		{ scaled h,w;
		  w=image_width(p);
		  h=image_height(p);
		  if(g_sign!=normal)
	      { if(g_sign==stretching)
	        { if(image_stretch_order(p)==g_order)
	          { vet_glue((double)(glue_set(this_box))*image_stretch(p));
       		    w=w+round(glue_temp);
	          }
	        }
	        else if(image_shrink_order(p)==g_order)
	        { vet_glue((double)(glue_set(this_box))*image_shrink(p));
	          w=w-round(glue_temp);
	        }
	      }
		  if (w!=image_width(p))
		  { double f;
		    f=(double)w/(double)image_width(p);
		    h=round((double)h*f);
		  }
  		  render_image(cur_h, cur_v, w, h,image_no(p));
          cur_h= cur_h+w; 
	    }
	    break;
     case glue_node:
     { pointer g= glue_ptr(p);rule_wd= width(g)-cur_g;
        if(g_sign!=normal)
        { if(g_sign==stretching)
          { if(stretch_order(g)==g_order)
            { cur_glue= cur_glue+stretch(g);
              vet_glue((double)(glue_set(this_box))*cur_glue);
              cur_g= round(glue_temp);
            }
          }
          else if(shrink_order(g)==g_order)
          { cur_glue= cur_glue-shrink(g);
            vet_glue((double)(glue_set(this_box))*cur_glue);
            cur_g= round(glue_temp);
          }
        }
        rule_wd= rule_wd+cur_g;
        if(subtype(p)>=a_leaders)
        { leader_box= leader_ptr(p);
          if(type(leader_box)==rule_node)
          { rule_ht= height(leader_box);rule_dp= depth(leader_box);
            goto fin_rule;
          }
          leader_wd= width(leader_box);
          if((leader_wd> 0)&&(rule_wd> 0))
          { rule_wd= rule_wd+10; /*compensate for floating-point rounding*/ 
            edge= cur_h+rule_wd;lx= 0;
			/*Let |cur_h| be the position of the first box,...*/
            if(subtype(p)==a_leaders)
            { save_h= cur_h;
              cur_h= left_edge+leader_wd*((cur_h-left_edge)/leader_wd);
              if(cur_h<save_h)cur_h= cur_h+leader_wd;
            }
            else 
			{ int lq= rule_wd/leader_wd;
              int lr= rule_wd%leader_wd;
              if(subtype(p)==c_leaders)cur_h= cur_h+(lr/2);
              else{lx= lr/(lq+1);
              cur_h= cur_h+((lr-(lq-1)*lx)/2);
            }
          }
          while(cur_h+leader_wd<=edge)
		  /*Output a leader box at |cur_h|,...*/
          { cur_v= base_line+shift_amount(leader_box);
		    save_h=cur_h;
			if(type(leader_box)==vlist_node)
				vlist_render(leader_box);
			else 
				hlist_render(leader_box);
			cur_v= base_line;
			cur_h= save_h+leader_wd+lx;
		  }
          cur_h= edge-10;goto next_p;
        }
      }
      goto move_past;
     }
     case kern_node:
	 case math_node:
	   cur_h= cur_h+width(p);
	   break;
     case ligature_node:
       mem[lig_trick]= mem[lig_char(p)];link(lig_trick)= link(p);
       p= lig_trick;
	   goto reswitch;
     default:;
   }
   goto next_p;
fin_rule:
   if(is_running(rule_ht))
 	 rule_ht= height(this_box);
   if(is_running(rule_dp))
     rule_dp= depth(this_box);
   rule_ht= rule_ht+rule_dp;
   if((rule_ht> 0)&&(rule_wd> 0))
   { cur_v= base_line+rule_dp;
     render_rule(cur_h, cur_v, rule_wd, rule_ht);
     cur_v= base_line;
   }
   move_past:cur_h= cur_h+rule_wd;
   next_p:p= link(p);
 }
} /* end |while| */
} /* end |hlist_render| */

static void vlist_render(pointer this_box)
{
scaled left_edge;
scaled top_edge;
scaled save_v;
glue_ord g_order;
uint8_t g_sign;
pointer p;
pointer leader_box;
scaled leader_ht;
scaled lx;
scaled edge;
double glue_temp;
double cur_glue;
scaled cur_g;

cur_g= 0;cur_glue= float_constant(0);
g_order= glue_order(this_box);
g_sign= glue_sign(this_box);p= list_ptr(this_box);
left_edge= cur_h;cur_v= cur_v-height(this_box);
top_edge= cur_v;
while(p!=null)
{ if(is_char_node(p)) MESSAGE("Glyph in vertical list ignored");
  else
  { switch(type(p))
    { case hlist_node:
      case vlist_node:
        if(list_ptr(p)==null) cur_v= cur_v+height(p)+depth(p);
	    else
	    { cur_v= cur_v+height(p);save_v= cur_v;
          cur_h= left_edge+shift_amount(p);
          if(type(p)==vlist_node)vlist_render(p);
	   	  else hlist_render(p);
          cur_v= save_v+depth(p);cur_h= left_edge;
        }
        break;
      case rule_node:
	    rule_ht= height(p);rule_dp= depth(p);rule_wd= width(p);
        goto fin_rule;
      case whatsit_node:
		if (subtype(p)==image_node)
		{ scaled h,w;
		  w=image_width(p);
		  h=image_height(p);
		  if(g_sign!=normal)
	      { if(g_sign==stretching)
	        { if(image_stretch_order(p)==g_order)
	          { vet_glue((double)(glue_set(this_box))*image_stretch(p));
       		    h=h+round(glue_temp);
	          }
	        }
	        else if(image_shrink_order(p)==g_order)
	        { vet_glue((double)(glue_set(this_box))*image_shrink(p));
	          h=h-round(glue_temp);
	        }
	      }
		  if (h!=image_height(p))
		  { double f;
		    f=(double)h/(double)image_height(p);
		    w=round((double)w*f);
		  }
		  cur_v= cur_v+h; 
  		  render_image(cur_h, cur_v, w, h,image_no(p));
		  }
        break;
      case glue_node:
	  { pointer g= glue_ptr(p);rule_ht= width(g)-cur_g;
	    if(g_sign!=normal)
	    { if(g_sign==stretching)
	      { if(stretch_order(g)==g_order)
	        { cur_glue= cur_glue+stretch(g);
	          vet_glue((double)(glue_set(this_box))*cur_glue);
       		  cur_g= round(glue_temp);
	        }
	      }
	      else if(shrink_order(g)==g_order)
	      { cur_glue= cur_glue-shrink(g);
	        vet_glue((double)(glue_set(this_box))*cur_glue);
	        cur_g= round(glue_temp);
	      }
	    }
	    rule_ht= rule_ht+cur_g;
	    if(subtype(p)>=a_leaders)
	    { leader_box= leader_ptr(p);
	      if(type(leader_box)==rule_node)
	      { rule_wd= width(leader_box);rule_dp= 0;
	        goto fin_rule;
	      }
	      leader_ht= height(leader_box)+depth(leader_box);
	      if((leader_ht> 0)&&(rule_ht> 0))
	      { rule_ht= rule_ht+10;
	        edge= cur_v+rule_ht;lx= 0;
            if(subtype(p)==a_leaders)
	        { save_v= cur_v;
	          cur_v= top_edge+leader_ht*((cur_v-top_edge)/leader_ht);
	          if(cur_v<save_v)cur_v= cur_v+leader_ht;
	        }
	        else
	        { int lq= rule_ht/leader_ht;
		      int lr= rule_ht%leader_ht;
		      if(subtype(p)==c_leaders)cur_v= cur_v+(lr/2);
		      else
		      { lx= lr/(lq+1);
		        cur_v= cur_v+((lr-(lq-1)*lx)/2);
		      }
		    }
		    while(cur_v+leader_ht<=edge)
		    { cur_h= left_edge+shift_amount(leader_box);
		      cur_v= cur_v+height(leader_box);save_v= cur_v;
		      if (type(leader_box)==vlist_node) 
				  vlist_render(leader_box);
			  else 
				  hlist_render(leader_box);
		      cur_h= left_edge;
		      cur_v= save_v-height(leader_box)+leader_ht+lx;
		    }
    		cur_v= edge-10;goto next_p;
		  }
	    }
	  }
	    goto move_past;
      case kern_node:
	    cur_v= cur_v+width(p);
        break;
      default: ;
    } /* end |switch| */
    goto next_p;

fin_rule:
    if(is_running(rule_wd))rule_wd= width(this_box);
    rule_ht= rule_ht+rule_dp;
    cur_v= cur_v+rule_ht;
    if((rule_ht> 0)&&(rule_wd> 0))
    { render_rule(cur_h, cur_v, rule_wd, rule_ht);
    }
    goto next_p;

move_past:
    cur_v= cur_v+rule_ht;
  } /* end |if| */
  next_p:p= link(p);
} /* end |while| */
} /* end |vlist_render| */

@

\subsection{Pages}
Let's start with the most simple case: an empty page. We simply forward this
task to the native rendering engine. The native renderer is not part of this
document, but its reponsibilities are listed in section~\secref{native}.

@<render functions@>=
uint64_t hint_blank(void)
{ nativeBlank();
  return 0;
}
@

We conclude this section with the function that is called after the page builder has finished
the page: the |hrender_page| function.
@<render functions@>=

static void hrender_page(pointer p)
{ nativeBlank();
  cur_h= 0;
  cur_v= height(p);
  cur_f=-1;cur_fp=NULL; 
  if(type(p)==vlist_node)
	  vlist_render(p);
  else 
	  hlist_render(p);
}
@


@
\section{Native Rendering}\label{native}
The {\tt rendernative.h} header file list all functions that the native renderer must implement.

To initialize the renderer call |nativeInit|. To release all resorces allocated call |nativeClear|.
@<native rendering definitions@>=
extern void nativeInit(void); 
extern void nativeClear(void);
@


To set the size of the drawing aerea in pixel and the resolution in dots (pixel) per inch call |nativeSetSize|
@<native rendering definitions@>=
extern void nativeSetSize(int px_h, int px_v, double dpi);
@ 

The native Renderer may implement an optional procedure to switch between Dark and light mode.
@<native rendering definitions@>=
extern void nativeSetDark(int dark);
@

To  render an empty page call |nativeBlank|.
@<native rendering definitions@>=
extern void nativeBlank(void); 
@

In the following, if not otherwise stated, all dimensions are given as double values in point.
We have $72.27\,\hbox{pt} = 1\,\hbox{inch}$ and $1\,\hbox{inch} = 2.54\, \hbox{cm}$.


To render the glyph |g| at position $(|x|,|y|)$ with width |w| and height |h| call:
@<native rendering definitions@>=
typedef struct gcache_s *gcache_s_ptr;
extern void nativeGlyph(double x, double y, double w, double h, struct gcache_s *g);
@

To render a black rectangle at position  $(|x|,|y|)$ with width |w| and height |h| call:
@<native rendering definitions@>=
void nativeRule(double x, double y, double w, double h);
@
To render an image at position  $(|x|,|y|)$ with width |w| and height |h|,
with the image data in memory from |istart| to (but not including) |iend| call:

@<native rendering definitions@>=
void nativeImage(double x, double y, double w, double h, unsigned char *istart, unsigned char *iend);
@

For PK fonts we need two functions, one to extract a runlength encoded
glyph and on the extract a glyph coded as a bitmap. For True4Type fonts,
we need just one to align the bitmap to |DWORD|s.
@<native rendering definitions@>= 
extern void nativeSetRunlength(struct gcache_s *g, unsigned char *g_data);
extern void nativeSetBitmaped(struct gcache_s *g, unsigned char *g_data);
extern void nativeSetTrueType(struct gcache_s *g);
@

Functions for PostScript Type 1 fonts and  OpenType fonts 
still need a specification.

To free any resources associated with a cached glyph |g| call:

@<native rendering definitions@>=
void nativeFreeGlyph(struct gcache_s *g);
@
This function is also called for all glyphs by the function |hint_clear_fonts|
If the |rm| parameter to that function is |false|, the glyph cache is not deallocated
only |nativeFreeGlyph| is executed for all glyphs.


\section{Font Encodings}

\subsection{PK Fonts}

PK Files\cite{TR:pkfile}
contain a compressed representation of bitmap fonts  produced by METAFONT and gftopk.
After unpacking these fonts, we obtain a (device independent) bitmap for each glyph.
On Windows the bitmap can be displayed on a Device Context using the |StretchDIBits| function.
This function is capable of stretching or shrinking and hence can adjust the
resolution. The resolution of the bitmap in the pk file is given be the 
two parameters |hppp| (horizonttap pixel per point) and vppp (vertical pixel per point) which
are found in the preamble of the pk file.

%For the memory device context we maintain its width, height as well as its
%horizontal and vertical resolution in dpi (dots per inch).
%Given the pixel position $(x,y)$ on |hmem|, the offset |d_h| and |d_v| of the hotspot of the
%glyph, and |w| and |h| the width and height of the glyph, we can compute the necessary
%parameters to display the glyph on |hmem| using the function |StretchDIBits|.

%With the assembled page on |hmem| in the correct size and resolutio ends the job of the
%user interface independent part of the hint viewer and the user interface takes over.

%The user interface knows the size of the client window (in pixel) and its resolution. 
%From this information, it can compute the true size in scaled point of the client window
%and the desired resolution of |hmem|. The user interface for the WIN32 viewer makes the
%resolution of |hmem| by a ceratin factor, called |render_factor| bigger. This has two advantages:
%scaling a high resolution black and white image down produces grey pixels around the border
%which makes the glyphs appear smoother; further, positions of glyphs are rounded to whole
%pixels when rendering them on |hmem| and these positions translate to sub-pixel position when scaling
%down. The user factor can also use a scale factor to display the page larger or smaller than its
%true size. For example with a scale factor of 2, a glyph 10pt high would measure 20pt on the screen.
%To make the enlaged page fit on the window, the user interface would request a window of only
%half the actual width and height, but would double the render factor. The image it receives
%cann then be displayed stretching it only be half the render factor thus obtaining an image
%that is scaled down by exactly the render factor filling the complete client window.

The first thing we need to know when a section of a \HINT/ file contains a font is
the font format. We know, it contains a PK font if the first two byte contain the
values |0xF7| and |0x59|.

@<determine the font format and unpack the font@>=
  if (fp->font_data[0]==0xF7 &&  fp->font_data[1]==0x59)
  { fp->ff=pk_format;
    if (!unpack_pkfile(fp)) { free(fp); fp=NULL; }
  }
@

There is some information in the PK font that is specific to a PK font.
@<definitions of |pk_t|, |t1_t|, |ot_t|, and |tt_t| types@>=

typedef struct
{ unsigned char *pk_comment; /* the program that made the pk font */
  unsigned int cs; /* checksum */
  unsigned char id; /* the id currently allways 89 */
} pk_t;
@

For every glyph, there is a |flag| byte in the PK file that tells how the corresponding glyph is
encoded and a pointer to the encoding itself.

@<definitions of |pkg_t|, |t1g_t|, |otg_t|, and |ttg_t| types@>=
typedef struct
{ unsigned char flag; /* encoding in the pk file */
  unsigned char *encoding;
} pkg_t;
@

Now we have two functions: one to unpack a single glyph when it is needed for the first time,
and one to unpack a font when it is needed for the first time.

@<PK font functions@>=
/* primitive operations */
#define PK_READ_1_BYTE() (data[i++])
#define PK_READ_2_BYTE() (k=PK_READ_1_BYTE(),k=k<<8,k=k+data[i++],k)
#define PK_READ_3_BYTE() (k=PK_READ_2_BYTE(),k=k<<8,k=k+data[i++],k)
#define PK_READ_4_BYTE() (k=PK_READ_3_BYTE(),k=k<<8,k=k+data[i++],k)



static void pkunpack_glyph(gcache_t *g)
/* unpack the data in the glyph into its internal representation */
{ int i,k;
  unsigned char *data;
  if (g==NULL || g->pk.encoding==NULL) return; /* no glyph, no data */
  g->ff=pk_format;
  if (g->bits!=NULL) return; /* already unpacked */
#if 0  
  MESSAGE("Unpacking glyph %c (0x%x)",g->cc,g->cc);
#endif 
  data=g->pk.encoding;
  i=0;
  if ((g->pk.flag&7)<4)  /* short form */
  { i=i+3; /* skip the TeX font metrics */
	i=i+1; /*escapement: |g->dy=0; g->dx=PK_READ_1_BYTE(); g->dx= g->dx<<16;| */
	g->w=PK_READ_1_BYTE();
	g->h=PK_READ_1_BYTE();
	g->hoff=(signed char)PK_READ_1_BYTE();
	g->voff=(signed char)PK_READ_1_BYTE();
  }
  else if ((g->pk.flag&7)<7) /* extended short form */
  {  i=i+3; /* skip the TeX font metrics */
	i=i+2; /*escapement: |g->dy=0; g->dx=PK_READ_2_BYTE(); g->dx= g->dx<<16;| */
	g->w=PK_READ_2_BYTE();
	g->h=PK_READ_2_BYTE();
	g->hoff=(signed short int)PK_READ_2_BYTE();
	g->voff=(signed short int)PK_READ_2_BYTE();
  }
  else /* long form */
  { i=i+4; /* skip the TeX font metrics */ 
	i=i+8; /*escapement: |g->dx=PK_READ_4_BYTE();g->dy=PK_READ_4_BYTE();| */
	g->w=PK_READ_4_BYTE();
	g->h=PK_READ_4_BYTE();
	g->hoff=(signed int)PK_READ_4_BYTE();
	g->voff=(signed int)PK_READ_4_BYTE();
  }
  if ((g->pk.flag>>4)==14) nativeSetBitmaped(g,data+i);
  else nativeSetRunlength(g,data+i);
#if 0
  MESSAGE("Unpacked glyph %c (0x%x) w=%d h=%d hoff=%d voff=%d",g->cc,g->cc, g->w, g->h, g-> hoff, g->voff);
#endif
}

static gcache_t *hnew_glyph(font_t *pk, unsigned int cc);


/* opcodes of pk files */
#define PK_XXX1 240
#define PK_XXX2 241
#define PK_XXX3 242
#define PK_XXX4 243
#define PK_YYY  244
#define PK_POST 245
#define PK_NO_OP 246
#define PK_PRE   247
#define PK_ID    89


int unpack_pkfile(font_t *pk)
/* scan |pk->data| and extract information. Do not unpack glyphs, these are unpacked on demand. */
{   int i,j;
    unsigned int k;
	unsigned char flag;
	unsigned char *data;
    data=pk->font_data;
    i=0;
	while (i< pk->size)
	  switch(flag=data[i++])
	{ case PK_XXX1: j=PK_READ_1_BYTE(); i=i+j; break;
	  case PK_XXX2: j=PK_READ_2_BYTE(); i=i+j;  break;
	  case PK_XXX3: j=PK_READ_3_BYTE(); i=i+j;  break;
	  case PK_XXX4: j=PK_READ_4_BYTE(); i=i+j;  break;
	  case PK_YYY:  i=i+4; break;
	  case PK_NO_OP: break;
	  case PK_PRE:
	  { int csize;
	    pk->pk.id=PK_READ_1_BYTE();
		if (pk->pk.id!=PK_ID) return 0;
		csize=PK_READ_1_BYTE();
		pk->pk.pk_comment=pk->font_data+i;
	    i=i+csize;
        pk->ds=PK_READ_4_BYTE()/(double)(1<<20);
		pk->pk.cs=PK_READ_4_BYTE();
		pk->hppp=PK_READ_4_BYTE()/(double)(1<<16);
		pk->vppp=PK_READ_4_BYTE()/(double)(1<<16);
#if 0    /* data is read only */
		pk->comment[csize]=0;  /* After reading the data insert zero byte to terminate comment */
#endif
	  }
        break;
	  case PK_POST: break;
	  case 248: case 249: case 250: case 251: case 252: case 253: case 254: case 255: break; /* undefined */
      default: /* the character codes */
	  {
		unsigned int pl;
	    unsigned int cc;
		gcache_t *g;
		if ((flag&7)==7) /* long form */
		{ pl=PK_READ_4_BYTE();
		  cc=PK_READ_4_BYTE();
		} else if ((flag&4)==4) /* extended short form */
		{ pl=PK_READ_2_BYTE();
		  cc=PK_READ_1_BYTE();
		  pl= pl+((flag&3)<<16);
		}else /* short form */
		{ pl=PK_READ_1_BYTE();
		  cc=PK_READ_1_BYTE();
		  pl= pl+((flag&3)<<8);
		}
		g = hnew_glyph(pk,cc);
		g->pk.flag=flag;
		g->pk.encoding=data+i;
		g->bits=NULL;
		i=i+pl;
	  }
	  break;
	}
	return 1;
}

@


\subsection{TrueType Fonts}


To unpack TrueType fonts, we use the {\tt stb\_truetype.h} single C header file library\cite{SB:truetype}
by Sean Barrett.

@<include the STB TrueType Implementation@>=
#define STB_TRUETYPE_IMPLEMENTATION
#define STBTT_STATIC
#include "stb_truetype.h"
@

The above header  file defines the proper data type for our |tt_t| type.
A dummy type is sufficient for the glyphs.

@<definitions of |pk_t|, |t1_t|, |ot_t|, and |tt_t| types@>=
typedef stbtt_fontinfo tt_t;
typedef struct
{ int dummy;
} ttg_t;
@

We use |stbtt_InitFont| to unpack the font and initialize the |font_t| structure
and we use |stbtt_GetCodepointBitmap| to obtain the bitmap for a glyph.
To determine the rendering size, we use the function |font_at_size| to
obtain the design size of the font in scaled point, and we set the resolution to 600dpi.
From the font size and the resolution, we get the size of one em and
the function |stbtt_ScaleForMappingEmToPixels| then computes
the right scale factor for the TrueType renderer.

@<TrueType font functions@>=
int unpack_ttfile(font_t *f)
{
  if (!stbtt_InitFont(&(f->tt),f->font_data,0))
    return 0;
f->ds=font_at_size(f->n)/(double)(1<<16); /* design size*/
f->hppp=f->vppp=600.0/72.27;
f->ff=tt_format;
return 1;
}


static void ttunpack_glyph(font_t *f, gcache_t *g, uint32_t cc)
{ float em =f->hppp*f->ds;
  float scale;
  scale =stbtt_ScaleForMappingEmToPixels(&(f->tt),em);
  g->bits=stbtt_GetCodepointBitmap(&(f->tt), scale, scale, cc, &(g->w), &(g->h), &(g->hoff),&(g->voff));
  g->ff=tt_format;
  nativeSetTrueType(g);
}

@

The function |unpack_ttfile| returns |false| if the font is not a TrueType font.

@<determine the font format and unpack the font@>=
  else if (unpack_ttfile(fp)) 
      fp->ff=tt_format;
  else
      { QUIT("Font format not supported for font %d\n",fp->n);
        free(fp); fp=NULL; 
      }
@


\subsection{PostScript Type 1 Fonts}
 
@
@<definitions of |pk_t|, |t1_t|, |ot_t|, and |tt_t| types@>=
typedef struct
{ int dummy;
} t1_t;
@
@<definitions of |pkg_t|, |t1g_t|, |otg_t|, and |ttg_t| types@>=
typedef struct
{ int dummy;
} t1g_t;
@

\subsection{OpenType Fonts}

@<definitions of |pk_t|, |t1_t|, |ot_t|, and |tt_t| types@>=
typedef struct
{ int dummy;
} ot_t;
@
@<definitions of |pkg_t|, |t1g_t|, |otg_t|, and |ttg_t| types@>=
typedef struct
{ int dummy;
} otg_t;
@

\section{Testing \HINT/}\label{testing}
One objective of \HINT/ is to make the following diagram is commutative:
$$\epsfbox{images/diagram.eps}$$
In order to test this property of \TeX, Hi\TeX, and \HINT/, we write a command line
version of \HINT/, called {\tt hintcl}, 
and run it together with \TeX\ and Hi\TeX\ against a collection
of test files. Since testing the equality of DVI files is not very convenient,
we use |show_box| to print a page description of every page and compare them
against the page descriptions produced by \TeX\  when {\tt tracingoutput} is enabled.
We expect to see no differences.

The testfile also illustrates nicely how to use the different functions of
the \TeX\ library and the \HINT/ library. Here is the main program:

@(main.c@>=
#include <stdio.h>
#include <string.h>
#include "texextern.h"
#include "hint.h"

@<test variables@>@;

@<test functions@>@;

int main(int argc, char *argv[])
{ char stem_name[MAX_NAME];
  int stem_length=0, path_length=0;
  bool option_log=false;

  @<process the command line@>@;
  @<open the log file@>@;
  hint_begin(0);
  while (hint_forward())
    @<show the page@>@;
  hint_end();
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
@<test functions@>=
void usage(void)
 { fprintf(stderr,
  "Usage: %s [options] filename.hnt\n",prog_name);@/
  fprintf(stderr,
  "Options:\n"@/
  "\t -l     \t redirect stdout to a log file\n");@/
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
  if (option_log)
  { 
    strncat(stem_name,".hlg",MAX_NAME);
    hlog=freopen(stem_name,"w",stdout);
    if (hlog==NULL)
    { fprintf(stderr,"Unable to open logfile %s",stem_name);
      hlog=stdout;
    }
    stem_name[stem_length]=0;
  }
  else
    hlog=stdout;
@



@<close the log file@>=
if (hlog!=NULL) fclose(hlog);
@

@<test variables@>=

#define MAX_NAME 1024
char prog_name[MAX_NAME];
char in_name[MAX_NAME];
int page_count=0;
FILE *hlog;
@


@<show the page@>=
{ page_count++;
  DBG(dbgbasic,"\nCompleted box being shipped out [%d]",page_count);
  show_box(stream[0].p);
  DBG(dbgbasic,"\n");
}


@
\subsection{Testing the Backwards Reading}
The following code  is similar to the code for the {\tt skip} program described in \cite{MR:format}. It test reading the \HINT/ file from end to start.



@(back.c@>=
#include <stdio.h>
#include <string.h>
#include "texextern.h"
#include "hint.h"

@<test variables@>@;

@<test functions@>@;

int main(int argc, char *argv[])
{ char stem_name[MAX_NAME];
  int stem_length=0, path_length=0;
  bool option_log=false;

  @<process the command line@>@;
  @<open the log file@>@;
  hint_begin(0);
  hpos=hend;
  while (hint_backward()) continue;
  hint_end();
  @<close the log file@>@;
  return 0;
}

@

\section{Finding memory leaks}
To find memory leaks, we make a table big enough for all 16 bit values (pointers)
and record a pointer with the allocated size when allocated and remove it when deallocated.
We can then list the currently allocated records.

@<\HINT/ auxiliar functions@>=
static pointer leaks[1<<16] = {0};

static void leak_clear(void)
{ 
#ifdef DEBUG
  int i;
  for (i=0;i<0x10000;i++)
     leaks[i]=0;
#endif
}

void leak_in(pointer p, int s)
{
#ifdef DEBUG 
leaks[p]=s; 
#endif
}

void leak_out(pointer p, int s)
{  
#ifdef DEBUG
   if (s!=leaks[p])
     fprintf(stderr,"p=%d, s out=%d != %d = s in\n",p,s,leaks[p]);
   leaks[p]=0; 
#endif
}

static void list_leaks(void)
{ 
#ifdef DEBUG
  int i;
  for (i=0;i<0x10000;i++)
   if (leaks[i]!=0)
     fprintf(stderr,"p=%d, s=%d\n",i,leaks[i]);
#endif
}
@ 

@<\TeX\ |extern|@>=
extern void leak_in(pointer p, int s);
extern void leak_out(pointer p, int s);
@

\appendix

\section{The Source Files}

\subsection{{\tt hint.h}}
@(hint.h@>=
#ifndef _HINT_H_
#define _HINT_H_

extern bool hmap_file(int fd);
extern bool hget_banner(void);
extern bool hget_section(uint16_t n);
extern bool hget_directory_section(void);
extern void hclear_dir(void);
extern bool hget_definition_section(void);
extern bool hget_content_section(void);
extern void hget_content(void);
extern void hteg_content(void);

extern void clear_map(void); /*clear the location table*/
extern void hpage_init(void);
extern bool hbuild_page_up(void); /*append contributions to the current page*/ 


@<\HINT/ |extern|@>@;

#endif
@

\subsection{{\tt hint.c}}
@(hint.c@>=
#ifndef WIN32
#include <sys/mman.h>
#else
#include <windows.h>
#endif
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include <zlib.h>@#

#include "texextern.h"
#include "hint.h"
#include "hrender.h"

#include "texdefs.h"

@<GET macros@>@;
@<TEG macros@>@;

@<\HINT/ types@>@;


@<\HINT/ variables@>@;
@<\HINT/ declarations@>@;
@<\HINT/ auxiliar functions@>@;
@<get functions@>@;
@<teg functions@>@;
@<\HINT/ functions@>@;

@

\subsection{{\tt hrender.h}}
@(hrender.h@>=
#ifndef _HRENDER_H
#define _HRENDER_H
@<render macros@>@;

extern int page_h, page_v;
extern uint64_t hint_blank(void);
extern uint64_t hint_page_get(void);
extern uint64_t hint_page_top(uint64_t h);
extern uint64_t hint_page_center(uint64_t h);
extern uint64_t hint_page_bottom(uint64_t h);
extern uint64_t hint_page(void);
extern uint64_t hint_next_page(void);
extern uint64_t hint_prev_page(void);
extern void hint_resize(int px_h, int px_v, double dpi);
extern void hint_clear_fonts(bool rm);

#endif 
@

\subsection{{\tt hrender.c}}
@(hrender.c@>=
#include <math.h>
#include "texextern.h"
#include "hint.h"
#include "hrender.h"
#include "rendernative.h"
#include "texdefs.h"

@<font |extern|@>@;

@<render variables@>@;
@<render functions@>@;
@


\subsection{{\tt hfonts.h}}
@(hfonts.h@>=
#ifndef _HFONTS_H
#define _HFONTS_H
@<font types@>@;


#endif
@

\subsection{{\tt hfonts.c}}
@(hfonts.c@>=
#include "basetypes.h"
#include "error.h"
#include "hformat.h"
#include "hint.h"
@<include the STB TrueType Implementation@>@;
#include "hfonts.h"
#include "hrender.h"
#include "rendernative.h"

@<font variables@>@;

@<TrueType font functions@>@;

@<PK font functions@>@;

@<font functions@>@;

@

\subsection{{\tt rendernative.h}}
This header file is included in the native rendering code and in \HINT/'s rendering code.
It makes sure that the implementation of the native functions matches the prototypes used in
the \HINT/ rendering functions.
@(rendernative.h@>=
#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H

@<native rendering definitions@>@;

#endif 
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
