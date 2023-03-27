% This file is part of HINT
% Copyright 2017-2021 Martin Ruckert, Hochschule Muenchen, Lothstrasse 64, 80336 Muenchen
%
% Permission is hereby granted, free of charge, to any person obtaining a copy
% of this software and associated documentation files (the "Software"), to deal
% in the Software without restriction, including without limitation the rights
% to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
% copies of the Software, and to permit persons to whom the Software is
% furnished to do so, subject to the following conditions:
%
% The above copyright notice and this permission notice shall be
% included in all copies or substantial portions of the Software.
%
% THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
% IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
% FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
% COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
% WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
% OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
% THE SOFTWARE.
%
% Except as contained in this notice, the name of the copyright holders shall
% not be used in advertising or otherwise to promote the sale, use or other
% dealings in this Software without prior written authorization from the
% copyright holders.

\input btxmac.tex
\input hintmac.tex
\input changefile.sty
\input epsf.tex

@i symbols.w

@

\makeindex
\maketoc
%\makecode
%\makefigindex
\titletrue


\def\setrevision$#1: #2 ${\gdef\lastrevision{#2}}
\setrevision$Revision: 2846 $
\def\setdate$#1(#2) ${\gdef\lastdate{#2}}
\setdate$Date: 2023-02-15 16:11:38 +0100 (Wed, 15 Feb 2023) $

\null

\input titlepage.tex


\frontmatter

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
The first part reads a \HINT\ file\cite{MR:format} and reconstructs \TeX's contribution list\cite{Knuth:tex}.
The routines found in this part translate data structures found in a \HINT\ file 
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


\section{Reading Definitions}
This chapter starts with the reimplementation of the parser for
short format \HINT\ files as described in {\it HINT: The File Format}\cite{MR:format}
which constitutes the definitive specification of this format.
Where as the latter uses an internal represenation that is
completely independent of \TeX\ and therefore does not need any knowlegde of
\TeX's implementation, the implementation that follows here depends heavily on
the implementation of \TeX. To make the presentation short, 
it is assumed that the reader is familiar with the specification just mentioned and with
{\it \TeX: The Program}\cite{Knuth:tex}.

Definitions occur in the definition section and in parameter lists,
where parameter lists can be parts of content nodes or part of a font
description.

A parameter has three parts: a parameter number, a parameter value,
and a parameter kind.  The parameter number and parameter kind have
different restrictions depending on the parameters occurence.

In parameter lists only integers, dimensions, extended dimensions, and
glues are allowed.  In font descriptions, we have penalties, kerns,
ligatures, hyphens, glue, math, rule, and image nodes.  In the
definition section, pretty much everything is allowed, we just test if
the parameter number is less or equal to |max_ref| and set |max_ref|
accordingly in |hget_max_definitions|.


\subsection{Definitions}
The following function reads a single definition and stores it.
By default, we store definitions as pointers to \TeX's data structures.

@<get functions@>=
void hget_def_node(void)
{ Kind k;
  int n;
  @<read the start byte |a|@>@;
  k=KIND(a);
  if (k==label_kind && (INFO(a)&b001)) HGET16(n);
  else n=HGET8; 
  if (k!=range_kind) REF_RNG(k,n);
  DBG(DBGTAGS,"Defining %s %d\n", definition_name[KIND(a)],n);
  switch(KIND(a))
  { case language_kind: { char *t;  HGET_STRING(t); break; }
    case font_kind: hget_font_def(a,n); break;
    case int_kind: integer_def[n]=hget_integer_def(a); break;
    case dimen_kind: dimen_def[n]=hget_dimen_def(a); break;
    case xdimen_kind: hget_xdimen_def(INFO(a),&(xdimen_def[n])); break;
    case baseline_kind: hget_baseline_def(a,n); break;
    case glue_kind: pointer_def[glue_kind][n]=hget_glue_def(a); break;
    case param_kind:  param_def[n]=hget_param_list(a); break;
    case range_kind: hget_range_def(a,n); break;
    case page_kind: hget_page_def(a,n); break;
    case label_kind: hget_outline_or_label_def(INFO(a),n); break;
    default:  pointer_def[KIND(a)][n]=hget_definition(a); break;
  }
  if (max_fixed[k]>max_default[k]) 
    QUIT("Definitions for kind %s not supported", definition_name[k]);
  if(n>max_ref[k] || n <= max_fixed[k]) 
    QUIT("Definition %d for %s out of range [%d - %d]",@|
        n, definition_name[k],max_fixed[k]+1,max_ref[k]);
  @<read and check the end byte |z|@>@;
}

pointer hset_glue(Glue *g)
{ if (ZERO_GLUE(*g)) 
  { add_glue_ref(zero_glue); 
    return zero_glue;
  }
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

void free_definitions(void)
{ @<free definitions@>@;
}

void hget_definition_section(void)
{ DBG(DBGDEF,"Definitions\n");
  hget_section(1);
  DBG(DBGDEF,"Reading list of maximum values\n");
  free_definitions();
  hget_max_definitions();
  @<allocate definitions@>@;
  hset_default_definitions();
  DBG(DBGDEF,"Reading list of definitions\n");
  while (hpos<hend) @/
    hget_def_node();
  hget_font_metrics();
  @<initialize the default page template@>@;
}
@


@<\HINT\ variables@>=
pointer *pointer_def[32]={NULL};
@


@<\HINT\ declarations@>=
static void hget_font_def(uint8_t a, uint8_t n);
static int32_t hget_integer_def(uint8_t a);
static scaled hget_dimen_def(uint8_t a);
static pointer hget_glue_def(uint8_t a);
static void hget_baseline_def(uint8_t a, uint8_t n);
static ParamDef *hget_param_list(uint8_t a);
static void hget_range_def(uint8_t a, uint8_t pg);
static void hget_page_def(uint8_t a, uint8_t n);
static void hget_outline_or_label_def(Info i, int n);
static void hget_font_metrics();
static pointer hget_definition(uint8_t a);
@


@<allocate definitions@>=
{ Kind k;
  for (k=0;k<32;k++)
  { if (k==font_kind || k==int_kind|| k==dimen_kind||k==xdimen_kind||
        k==glue_kind||k==baseline_kind|| k==range_kind||k==page_kind||k==param_kind||k==stream_kind||k==label_kind)
       continue;
    if (max_ref[k]>=0 && max_ref[k]<=256)
    { DBG(DBGDEF,"Allocating definitions for %s (kind %d): %d entries of " SIZE_F " byte each\n",
          definition_name[k],k,max_ref[k]+1,sizeof(pointer));
      ALLOCATE(pointer_def[k],max_ref[k]+1,pointer);
    }
  }
}
@

@<free definitions@>=
{ int k;
for (k=0;k<32;k++)
{ free(pointer_def[k]); pointer_def[k]=NULL; }
}
@


Now lets consider the few exceptions where definitions are not stored as pointers.
We start with the data types.

\subsection{Data Types}
\subsubsection{Integers}
\noindent
@<\HINT\ variables@>=
int32_t *integer_def;
@


@<allocate definitions@>=
ALLOCATE(integer_def, max_ref[int_kind]+1, int32_t);
@

@<free definitions@>=
free(integer_def); integer_def=NULL;
@

@<\HINT\ auxiliar functions@>=
static int32_t hget_integer_def(uint8_t a)
{@+ if (INFO(a)==1) {@+ int8_t n=HGET8; @+return n;@+}
  else  if (INFO(a)==2) {@+ int16_t n;@+ HGET16(n);@+ return n;@+}
  else if (INFO(a)==4) {@+int32_t n;@+ HGET32(n);@+ return n;@+}
  else TAGERR(a);
  return 0;
}

static int32_t hget_integer_ref(uint8_t n)
{ @+REF_RNG(int_kind,n);
  return integer_def[n];@+
}
@

\subsubsection{Dimensions}

@<\HINT\ variables@>=
scaled *dimen_def;
@

@<allocate definitions@>=
ALLOCATE(dimen_def,max_ref[dimen_kind]+1, Dimen);
@

@<free definitions@>=
free(dimen_def); dimen_def=NULL;
@

@<get functions@>=
scaled hget_dimen_ref(uint8_t n)
{ @+REF_RNG(dimen_kind,n);
  return dimen_def[n];
}

static scaled hget_dimen_def(uint8_t a)
{@+ if (INFO(a)==b000)
    return hget_dimen_ref(HGET8);
  else  
  {@+ scaled d; @+HGET32(d); return d; @+}
}
@



\subsubsection{Extended Dimensions}

@<\HINT\ variables@>=
Xdimen *xdimen_def;
@

@<allocate definitions@>=
ALLOCATE(xdimen_def, max_ref[xdimen_kind]+1, Xdimen);
@
@<free definitions@>=
free(xdimen_def); xdimen_def=NULL;
@

@<\HINT\ auxiliar functions@>=
static scaled xdimen(Xdimen *x)
{ @+return round(x->w+(double)x->h*(double)hhsize+@|(double)x->v*(double)hvsize);
}
static scaled hget_xdimen_ref(uint8_t n)
{ @+REF_RNG(xdimen_kind,n);
  return  xdimen(xdimen_def+n);@+
}
@

The printing routine for whatsit nodes requires a function to print extended dimensions. Since
\HINT\ never allocates a extended dimension node, the following function will suffice:
@<\HINT\ functions@>=
void print_xdimen(int i)
{}
@


\subsection{Glues}
\noindent
@<\HINT\ auxiliar functions@>=

static pointer hget_glue_ref(uint8_t n)
{ @+REF_RNG(glue_kind,n);
  return  pointer_def[glue_kind][n];@+
}

static pointer hget_glue_def(uint8_t a)
{@+ pointer p;
  if (INFO(a)==b000)
  {@+ p= hget_glue_ref(HGET8);
    add_glue_ref(p);@+
  }
  else
  { HGET_GLUE(INFO(a)); }
  return p;
}

pointer hget_param_glue(uint8_t n)
{ @+REF_RNG(glue_kind,n);
  return  new_glue(pointer_def[glue_kind][n]);@+
}
@

@<allocate definitions@>=
ALLOCATE(pointer_def[glue_kind],max_ref[glue_kind]+1, pointer);
@

\subsection{Baseline Skips}
Baseline skip specifications are stored using variables of type
|BaselineSkip|.  Baseline skips are allowed only in vertical lists and the
actual baseline skip glue will be inserted just before appending the
next hbox or vbox to the list. Until then we keep a possible baseline
specification on a stack that parallels \TeX's semantic nest.

@<\HINT\ types@>=
typedef struct { pointer bs, ls; scaled lsl;} BaselineSkip;
@

@<\HINT\ variables@>=
BaselineSkip *baseline_def=NULL;
@

@<allocate definitions@>=
ALLOCATE(baseline_def, max_ref[baseline_kind]+1, BaselineSkip);
@

@<free definitions@>=
free(baseline_def); baseline_def=NULL;
@

@<get functions@>=
static void hget_baseline_def(uint8_t a, uint8_t n)
{ @+HGET_BASELINE(INFO(a));
  baseline_def[n].bs=cur_bs;add_glue_ref(cur_bs);
  baseline_def[n].ls=cur_ls;add_glue_ref(cur_ls);
  baseline_def[n].lsl=cur_lsl;
}

void hget_baseline_ref(uint8_t n)
{ REF_RNG(baseline_kind,n);
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


When we build pages from the bottom up, we need a routine similar to
|happend_to_vlist| which is called |hprepend_to_vlist|.
The name is actually a misnomer, because nodes are still added at the tail end of the
vertical list. When we use this function, however, the first node in the vertical list
is at the bottom of the page and the tail node is closer to the to the top of the page,
so in a sense it is a previous node in reading-order.

For |happend_to_vlist| we kee track of the depth of the last box and the latest baselineskip
parameters on the current list. When we encounter a new box |b|, we insert a baselineskip
that accounts for the height of box |b| and the depth of the previous box according to
the lateste baselineskip information.
For |hprepend_to_vlist| we kee track of the height of the last box and the latest baselineskip
parameters on the current list. When we encounter a new box |b|, we insert a baselineskip
that accounts for the depth of box |b| and the height of the previous box according to
the lateste baselineskip information.



@<get functions@>=
static pointer hprepend_to_vlist(pointer @!b)
{@+scaled d; /*deficiency of space between baselines*/ 
pointer @!p=null; /*a new glue node*/ 

if (needs_bs && prev_height > ignore_depth) 
{@+d=width(cur_bs)-prev_height-depth(b);
  if (d < cur_lsl) p=new_glue(cur_ls);
  else{@+pointer q=new_spec(cur_bs);
    width(q)=d; p=new_glue(q);glue_ref_count(q)=null;
    } 
  link(tail)=p;tail=p;
  if (nest_ptr==0)
    store_map(p,cur_list.bs_pos-hstart,0);
  } 
link(tail)=b;tail=b;prev_height=height(b);
cur_list.bs_pos=NULL;
return p;
} 
@

@<\HINT\ declarations@>=
static pointer hprepend_to_vlist(pointer b);
@


\subsection{Fonts}\label{fonts}
\TeX\ gets ist knowlegde about fonts from font metric files. \HINT\ will not need all of that
information, but for now, the complete \TeX\ font metric file is included inside the \HINT\ file,
and we can load all that information by calling the procedure |read_font_info| defined by \TeX.
Because \TeX\ reads the font metric file using a special |fget| macro, only a few modifications,
as explained below, are necessary.

When rendering fonts, we will need to find the section containing the actual glyphs.

So we store the font name |n|, the section number for the font metrics |m| and the glyphs |q|, 
the ``at size'' |s| (which might be different from the design size),
the pointer to the font glue |g|,
the pointer to the font hyphen |h|, and the font parameters |p|.

@<\HINT\ types@>=
typedef struct {
char *n;
uint16_t m,q;
scaled s;
pointer g;
pointer h;
pointer p[MAX_FONT_PARAMS+1];
} FontDef;
extern FontDef *font_def;
@

@<\HINT\ variables@>=
FontDef *font_def;
@

@<allocate definitions@>=
ALLOCATE(font_def, max_ref[font_kind]+1, FontDef);
@

@<free definitions@>=
free(font_def); font_def=NULL;
@


@<\HINT\ auxiliar functions@>=
static void hget_font_def(uint8_t a, uint8_t n)
{ char *t;
  FontDef *f=font_def+n;
  HGET_STRING(t);f->n=strdup(t); 
  DBG(DBGDEF,"Font %d: %s\n", n, t); 
  HGET32(f->s); @+RNG("Font size",f->s,1,0x7fffffff);
  HGET16(f->m); @+RNG("Font metrics",f->m,3,max_section_no);
  HGET16(f->q); @+RNG("Font glyphs",f->q,3,max_section_no);
  f->g=hget_glue_spec(); 
  f->h=hget_disc_node();
  DBG(DBGDEF,"Start font parameters\n");
  while (KIND(*hpos)!=font_kind)@/  
  { Kind k;
    uint8_t n;
    @<read the start byte |a|@>@;
    k=KIND(a);
    n=HGET8;
    DBG(DBGDEF,"Reading font parameter %d: %s\n",n, definition_name[k]);
    if (k!=penalty_kind && k!=kern_kind && k!=ligature_kind && @|
        k!=disc_kind && k!=glue_kind && k!=language_kind && @| k!=rule_kind && k!=image_kind)
      QUIT("Font parameter %d has invalid type %s",n, content_name[n]);
    RNG("Font parameter",n,0,MAX_FONT_PARAMS);
    f->p[n]=hget_definition(a);
    @<read and check the end byte |z|@>@;
  }
  DBG(DBGDEF,"End font definition\n");
}
@

After reading the definition section, we need to move the information from the \TeX\ font metric
files included into \TeX's data structures.

@<\HINT\ auxiliar functions@>=
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
@

We export the font section and at-size using two functions
to be used in {\tt hfonts.c}.

@<\HINT\ functions@>=
uint16_t hglyph_section(uint8_t f)
{   return font_def[f].q;
}

int32_t font_at_size(uint8_t f)
{  return font_def[f].s; /* at size */
}
@

@<\HINT\ font access functions@>=
extern uint16_t hglyph_section(uint8_t f);
extern int32_t font_at_size(uint8_t f);
@

We used:

@<\HINT\ declarations@>=
static pointer hget_glue_spec(void);
static pointer hget_disc_node(void);
@

\subsection{Parameter Lists}\label{getparamlist}
There are three types of data that we allow in parameter lists: integers, dimensions,
and glue. Hence, for each parameter, we store the parameter number |n|, its kind |k|, and its value |v|.
Since all values are integer types, a single integer type, large enough for |int32_t|, |scaled| and |pointer| values
is sufficient. 
To form linked lists of parameter definitions, we add a |next| pointer. The variable |param_def| contains the dynamically allocated 
array of lists of parameter definitions.
@<\HINT\ types@>=
typedef struct {
uint8_t n,k;@+
int32_t v;@+
      } Param;@#

typedef struct ParamDef {
struct ParamDef *next;@+
Param p; } ParamDef;
@


@<\HINT\ variables@>=
ParamDef **param_def;
@

@<allocate definitions@>=
ALLOCATE(param_def, max_ref[param_kind]+1, ParamDef*);
@

@<free definitions@>=
if (param_def!=NULL)
{ int i;
  for (i=0; i<=max_ref[param_kind]; i++)
    free_param_list(param_def[i]);
}  
free(param_def); param_def=NULL;
@

@<\HINT\ auxiliar functions@>=
static void free_param_list(ParamDef *p)
{ while (p!=NULL)
  { ParamDef *q=p;
    p=p->next;
    free(q);
  } 
} 
@

Next we implement reading a parameter list from a \HINT\ file.

@<\HINT\ auxiliar functions@>=
static ParamDef *hget_param_list(uint8_t a)
{ uint32_t s,t;
  ParamDef *p=NULL;
  uint8_t *list_start,*list_end;
  list_start=hpos;
  s=hget_list_size(INFO(a)); 
  hget_size_boundary(INFO(a));
  list_end=hpos+s;
  if (list_end>=hend) 
    QUIT("list end after before stream end\n"); 
  while (hpos<list_end)
  { @+ParamDef *r; Param *q;
    @<read the start byte |a|@>@;
    ALLOCATE(r,1,ParamDef);
    q=&(r->p);
    q->n=HGET8;
    q->k=KIND(a);
    DBG(DBGTAGS,"Defining %s %d\n", definition_name[KIND(a)],q->n);
    if (KIND(a)==int_kind) q->v=hget_integer_def(a);
    else if (KIND(a)==dimen_kind) q->v=hget_dimen_def(a);
    else if (KIND(a)==glue_kind) q->v=hget_glue_def(a);
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

ParamDef *hget_param_list_node(void)
{ @+if (KIND(*hpos)!=param_kind) return NULL;
  else 
  { @+ParamDef *p;
    @<read the start byte |a|@>@;
    p=hget_param_list(a);
    @<read and check the end byte |z|@>@;
    return p;
  }
}

ParamDef *hget_param_list_ref(uint8_t n)
{@+ REF_RNG(param_kind,n);
  return param_def[n];
}
@

Finaly, here are two functions that set and restore global parameters
based on a parameter list.  Parameter lists are actually not nested,
because every parameter list records the differences of the parameter
settings compared to the settings in the definition section. Still
there are situations where we want to combine two parameter
settings. The parameters for displayed equations and for line breaking
of a paragraph are disjoint sets. Since displayed equations are
embedded in paragraphs, we want to set and restore the parameter
settings for the displayed equation without affecting the settings for
line breaking. To do so, we use the special kind value |0xFF| to
record the boundary between two sets of parameters on the |par_save|
stack.

There are two cases to distinguish: If the parameter list is
given by a reference to the definition section, we have to increase
the reference counts for glues. If the parameter list is given explicitely,
the newly created glue nodes already have the correct reference count.
Currently, we do neither increase reference counts nor decrease them
after use. This means that glues might get deallocated while still
set as a global parameter and that glues on an explicit parameter list
are never deallocated after use and hence cause a memory leak.
Fortunately, up to now, parameter lists allocated by hitex
are most probably predefined; still this needs to be fixed.

@<\HINT\ auxiliar functions@>=
#define MAX_SAVE 100
#define SAVE_BOUNDARY 0xFF
static Param par_save[MAX_SAVE];
static int par_save_ptr=0;

static void hset_param(uint8_t k, uint8_t n, int32_t v)
{ Param *q;
  if (par_save_ptr>= MAX_SAVE) QUIT("Parameter save stack overflow");
  q=&(par_save[par_save_ptr++]);
  q->k=k;
  q->n=n;
  if (q->k==int_kind)
  { q->v= integer_def[q->n];@+ integer_def[q->n] =v; }
  else if (q->k==dimen_kind)
  { q->v=  dimen_def[q->n];@+ dimen_def[q->n]=(scaled)v; }
  else if (q->k==glue_kind)
  { q->v=  pointer_def[glue_kind][q->n];@+ pointer_def[glue_kind][q->n]=(pointer)v; }
}

void hset_param_list(ParamDef *p)
{ hset_param(SAVE_BOUNDARY,0,0);
  while (p!=NULL)
  { hset_param(p->p.k,p->p.n,p->p.v);
    p=p->next;
  }
}

void hrestore_param_list(void)
{
  while (par_save_ptr>0)
  { Param *q;
    q=&(par_save[--par_save_ptr]);
    if (q->k==SAVE_BOUNDARY) return;
    if (q->k==int_kind)
    { integer_def[q->n] =q->v; }
    else if (q->k==dimen_kind)
    { dimen_def[q->n]=(scaled)q->v; }
    else if (q->k==glue_kind)
    { pointer_def[glue_kind][q->n]=(pointer)q->v; }
  } 
  QUIT("Parameter save stack flow");
}
@
@<\HINT\ |extern|@>=
extern void hrestore_param_list(void);
@

\subsection{Page Ranges}
@<\HINT\ variables@>=
typedef struct {
 uint8_t pg;
 uint32_t f,t;
} RangeDef;
RangeDef *range_def;
@
@<allocate definitions@>=
ALLOCATE(range_def, max_ref[range_kind]+1, RangeDef);
@

@<free definitions@>=
free(range_def); range_def=NULL;
@

@<\HINT\ auxiliar functions@>=
static void hget_range_def(uint8_t a, uint8_t pg)
{ static uint8_t n=0;
  uint32_t f, t; 
  REF_RNG(page_kind,pg);
  REF_RNG(range_kind,n);
  if (INFO(a)&b100) @+
  { @+ if (INFO(a)&b001) HGET32(f); @+else HGET16(f); @+}
  else f=0;
  if (INFO(a)&b010) @+
  { @+if (INFO(a)&b001) HGET32(t); @+else HGET16(t); @+}
  else t=HINT_NO_POS;
  range_def[n].pg=pg;
  range_def[n].f=f;
  range_def[n].t=t;
  DBG(DBGRANGE,"Range *%d from 0x%x\n",pg,f);
  DBG(DBGRANGE,"Range *%d to 0x%x\n",pg,t);
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

\subsection{Stream Definitions}
The variable |streams| is used to contain the stream records
that store the main content and the content of insertions.
These records replace the box registers of \TeX.

@<\HINT\ |extern|@>=
typedef struct { /* should go to hint.h */
pointer p, t; /* head and tail */
} Stream;
extern Stream *streams;
@

@<\HINT\ variables@>=
Stream *streams;
@
 
@<allocate definitions@>=
ALLOCATE(streams, max_ref[stream_kind]+1, Stream);
@

@<free definitions@>=
free(streams); streams=NULL;
@


We put a stream definition into avariable of type |StreamDef|.
@<\HINT\ variables@>=
typedef struct {
  Xdimen x; /* maximum height */
  int f; /* factor */
  int p, n, r; /* preferred and next stream: split ratio */
  pointer b, a; /* before and after list */
  Xdimen w; /* width */
  pointer g; /* top skip glue */
  pointer h; /* total height, stretch, and shrink of |a| and |b| */
} StreamDef;
@

We define a function to read a stream definition 
which we use when reading page templates.
We pass in the pointer to the array of stream definitions
belonging to the current page.

@<\HINT\ auxiliar functions@>=
static void hget_xdimen_def_node(Xdimen *x);

static bool hget_stream_def(StreamDef *s)
{ if (KIND(*hpos)!=stream_kind || !(INFO(*hpos)&b100))
    return false;
  else
  { uint8_t n;
    @<read the start byte |a|@>@;
    DBG(DBGDEF,"Defining stream %d at " SIZE_F "\n",*hpos,hpos-hstart-1);
    n=HGET8;@+ REF_RNG(stream_kind,n); 
    s=s+n;
    if (n>0) 
    { if (INFO(a)==b100) @<get stream information for normal streams@>@;
      else if (INFO(a)==b101) QUIT("first stream not yet implemented");
      else if(INFO(a)==b110) QUIT("last stream not yet implemented");
      else if (INFO(a)==b111) QUIT("top stream not yet implemented");
      s->b=hget_list_pointer();
      hget_xdimen_def_node(&(s->w));
      s->g=hget_glue_spec();
      s->a=hget_list_pointer();
      s->h=hget_glue_spec();
   }
   @<read and check the end byte |z|@>@;
   return true;
  }
}
@

The information associated with a normal stream is read like this:

@<get stream information for normal streams@>=
{ DBG(DBGDEF,"Defining normal stream %d at " SIZE_F "\n",*(hpos-1),hpos-hstart-2);
  hget_xdimen_def_node(&(s->x)); 
  HGET16(s->f); @+RNG("magnification factor",s->f,0,1000);
  s->p=HGET8; if (s->p!=255) REF_RNG(stream_kind,s->p);
  s->n=HGET8; if (s->n!=255) REF_RNG(stream_kind,s->n);
  HGET16(s->r); RNG("split ratio",s->r,0,1000); 
}
@



Stream definitions are part of the page templates which we read using the
same functions that we use for content nodes. Here we replace them by the
appropriate stream content.



@<cases to get content@>=
case TAG(stream_kind,b100): hinsert_stream(HGET8); @+ break;
@

\subsection{Page Templates}


@<\HINT\ variables@>=
typedef struct {
  char *n; /* name */
  Dimen d; /* max page depth */
  pointer g; /* top skip glue */
  uint8_t p; /* priority */
  uint32_t t; /* the template position*/
  Xdimen v,h; /* the dimensions of the page */
  StreamDef *s; /* stream definitions */
} PageDef;
PageDef *page_def;
PageDef *cur_page;
@

@<allocate definitions@>=
ALLOCATE(page_def, max_ref[page_kind]+1, PageDef);
@

@<initialize the default page template@>=
page_def[0].d=max_depth;
page_def[0].g=top_skip; add_glue_ref(top_skip);
page_def[0].p=0;
page_def[0].n=strdup("default");
page_def[0].v.w=-9*ONE;
page_def[0].v.h=0.0;
page_def[0].v.v=1.25;
page_def[0].h.w=-9*ONE;
page_def[0].h.h=1.25;
page_def[0].h.v=0.0;
page_def[0].t=0;
ALLOCATE(page_def[0].s, max_ref[stream_kind]+1, StreamDef);
cur_page=&(page_def[0]);
@

@<free definitions@>=
if (page_def!=NULL)
{ int k;
  for (k=0;k<=max_ref[page_kind];k++) 
  {  free(page_def[k].s); free(page_def[k].n); 
  }
  free(page_def); page_def=NULL;cur_page=NULL;
}
@

@<\HINT\ auxiliar functions@>=

static void hset_cur_page(void)
{ int i;
  cur_page=&(page_def[0]);
  for (i=1; i<=max_ref[page_kind]; i++)
    if (page_def[i].p>= cur_page->p)
       cur_page=&(page_def[i]);
}

static void hskip_list(void);
static void hget_page_def(uint8_t a, uint8_t i)
{ char *n; /* name */
  cur_page=&(page_def[i]);
  ALLOCATE(cur_page->s, max_ref[stream_kind]+1, StreamDef);
  HGET_STRING(n); cur_page->n=strdup(n);
  cur_page->p=HGET8;
  cur_page->g=hget_glue_spec();  
  HGET32(cur_page->d);
  hget_xdimen_def_node(&(cur_page->v)); 
  hget_xdimen_def_node(&(cur_page->h)); 
  cur_page->t=hpos-hstart;
  hskip_list();
  while (hget_stream_def(cur_page->s)) continue;
}
@


@<\HINT\ functions@>=
static void hinsert_stream(uint8_t n)
{ REF_RNG(stream_kind,n);
  if (streams[n].p==null) return;
  DBG(DBGPAGE,"Filling in stream %d\n",n);
  if (n>0 && cur_page->s[n].b!=0)
  { pointer p= copy_node_list(cur_page->s[n].b);
    link(tail)=p;      
    while (link(p)!=null) p=link(p);
    tail=p;
    DBG(DBGPAGE,"Filling in before list %d\n",n);
  }
  link(tail)=streams[n].p;
  tail=streams[n].t;
  if (tail==null) QUIT("Tail of nonempty stream %d is null\n",n);
  streams[n].p=streams[n].t=null;
  DBG(DBGPAGE,"Filling in content list %d\n",n);
  if (n>0 && cur_page->s[n].a!=0)
  { pointer p= copy_node_list(cur_page->s[n].a);
    link(tail)=p;      
    while (link(p)!=null) p=link(p);
    tail=p;
    DBG(DBGPAGE,"Filling in after list %d\n",n);
  }
}
@


Now comes the top level function to fill a template:

@<\HINT\ functions@>=
void hfill_page_template(void)
{ pointer p;
  if (cur_page->t!=0)
  {
    uint8_t *spos=hpos, *sstart=hstart, *send=hend;
    hget_section(1);
    hpos=hpos+cur_page->t;
    p=hget_list_pointer();
    hpos=spos,hstart=sstart,hend=send;
    if (streams[0].p!=null) flush_node_list(streams[0].p);
  }
  else
  { p =streams[0].p;
  }
  streams[0].p=streams[0].t=null;
  houtput_template(p);
  hmark_page();
}
@

@<\HINT\ |extern|@>=
extern void hfill_page_template(void);
@

\subsection{Labels and Outlines}\label{labels}
We store labels in the |labels| variable provided by {\tt hget.c}.
Because we will expose outlines to the \HINT\ viewer, we choose
a representation that fits the viewer's requirements; it is explaned in
section~\secref{outlines}. Here we declare, allocate/deallocate,
and initialize the variable |hint_outlines| together with the 
variable |labels|.

@<\HINT\ variables@>=
hint_Outline *hint_outlines=NULL;
int outline_no=-1;
@

@<allocate definitions@>=
if (max_ref[label_kind]>=0)
ALLOCATE(labels, max_ref[label_kind]+1, Label);
if (max_outline>=0)
ALLOCATE(hint_outlines, max_outline+1, hint_Outline);
@

@<free definitions@>=
free(labels); labels=NULL;
{ int k;
  for (k=0;k<=max_outline;k++) free(hint_outlines[k].title);
}
free(hint_outlines); hint_outlines=NULL; outline_no=-1;
max_outline=-1;
@

The function |hget_outline_or_label_def| reads a label or outline
definition from the definition section. The |b100| bit tells the
difference.

@<get functions@>=
void hget_outline_or_label_def(Info i, int n)
{ @+if (i&b100)
   @<get and store an outline@>@;
  else
    @<get and store a label@>@;
}
@

@<get and store a label@>=
{@+ Label *t=labels+n;
  HGET32(t->pos);
  t->where=HGET8;
  if (t->where>LABEL_MID) t->where=LABEL_UNDEF;
  if (i&b010) /* secondary position */
  {@+ HGET32(t->pos0); t->f=HGET8;@+}
  else t->pos0=t->pos;
   DBG(DBGDEF,"Label 0x%x+0x%x where=%d font=%d\n",t->pos0,t->pos,t->where,t->f);
}
@

@<get and store an outline@>=
{@+hint_Outline *t;
   uint64_t pos;
   uint8_t where;
   outline_no++;
   RNG("Outline",outline_no,0,max_outline);
   t=hint_outlines+outline_no;
   t->depth=HGET8;
   t->p=hget_list_pointer();
   t->title=strdup(hlist_to_string(t->p));
   @<get |where| and |pos| from label |n|@>@;
   t->where=where;
   t->pos=pos;
}
@

@<get |where| and |pos| from label |n|@>=
if (labels==NULL || n>max_ref[label_kind])
{ where= LABEL_TOP; pos=0; }
else
{   where=labels[n].where;
#if 1   
   pos=((uint64_t)labels[n].pos<<32)+@|(labels[n].pos-labels[n].pos0);
#else
   pos=((uint64_t)labels[n].pos0<<32); /* offsets still dont work in all cases and need fixing */
#endif
}
@


The function |hlist_to_string| is defined in section~\secref{listtraversal}.

\subsection{References}
There are only a few functions that still need to be defined.
@<\HINT\ auxiliar functions@>=
static pointer hget_ligature_ref(uint8_t n)
{ @+REF_RNG(ligature_kind,n);
  return copy_node_list(pointer_def[ligature_kind][n]);
}

static pointer hget_rule_ref(uint8_t n)
{ @+REF_RNG(rule_kind,n);
  return copy_node_list(pointer_def[rule_kind][n]);
}

static pointer hget_image_ref(uint16_t n)
{ @+REF_RNG(image_kind,n);
  return copy_node_list(pointer_def[image_kind][n]);
}

static pointer hget_hyphen_ref(uint8_t n)
{ @+REF_RNG(disc_kind,n);
  return copy_node_list(pointer_def[disc_kind][n]);
}

static pointer hget_leaders_ref(uint8_t n)
{ @+REF_RNG(leaders_kind,n);
  return copy_node_list(pointer_def[leaders_kind][n]);
}




@

\section{Reading Content Nodes}
The following section explains how to read the content section and convert
the \HINT\ representation of the content to the \TeX\ representation. While in the future we might have
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
static void hget_content_section()
{ @+DBG(DBGDIR,"Reading Content Section\n");
  hget_section(2);@+
}
@
There is no separate ``|teg|'' function in this case. If necessary, one can set |hpos=hend|.


The basic data structure of a \HINT\ file is a node. We distinguish content- and definition-nodes. 
In both cases, a node consists of a start byte followed by
the content or the definition and a matching end byte.
 

@<read the start byte |a|@>=
uint8_t a,z; /* the start and the end byte*/
HGETTAG(a);
@

@<read and check the end byte |z|@>=
HGETTAG(z);@+
if (a!=z) tag_mismatch(a,z,node_pos, hpos-hstart-1);
@

The identifier |node_pos| is defined as a macro; it denotes a field on
the current list record containig the position of the tag of the node
currently processed.

The |tag_mismatch| function is defined as follows:
@<\HINT\ auxiliar  functions@>=
static void tag_mismatch(uint8_t a, uint8_t z, uint32_t a_pos, uint32_t z_pos)
{   QUIT(@["Tag mismatch [%s,%d]!=[%s,%d] at 0x%x to 0x%x\n"@],@|
    NAME(a),INFO(a),NAME(z),INFO(z),@|a_pos, z_pos);
}
@

@<\HINT\ declarations@>=
static void tag_mismatch(uint8_t a, uint8_t z, uint32_t a_pos, uint32_t z_pos);
@



The |hget_node| function gets the next node from the input based on the tag byte |a|
and adds it to the current list. The function is used in |hget_content| to read a content node
but also in the function |hget_definition| to get the content of a definition. 

@<\HINT\ functions@>=

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

@<\HINT\ |extern|@>=
void hget_content(void);
@

Now let's turn to the backwards version.
The primitive reading operations are taken from {\tt get.h}.

The next macros read and check start and end byte.

@<read the end byte |z|@>=
  uint8_t a,z; /* the start and the end byte*/
  z=HTEG8,DBGTAG(z,hpos);
@

@<read and check the start byte |a|@>=
  a=HTEG8,DBGTAG(a,hpos);
  if (z!=a) tag_mismatch(a,z,hpos-hstart,node_pos);
@

We conclude the section with the equivalents of |hget_node| and |hget_content|.
 The |node_pos| points to
the end byte while reading the node and points to the start byte when reading the node is done. WE record the node position for all nodes on nesting level zero,
because after a penalty, the page can start with pretty much any node type,
and it is better to err on the save side.

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
  if (nest_ptr==0 && tail!=head
#if 0
  && (type(tail)==penalty_node || type(tail)==glue_node
  || type(tail)==hlist_node || type(tail)==vlist_node
  || type(tail)==kern_node)
#endif
)
      store_map(tail,node_pos,0);
}
@

@<\HINT\ |extern|@>=
extern void hteg_content(void);
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


\subsection{Extended Dimensions}
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

@<\HINT\ auxiliar functions@>=

static void hget_xdimen_def(Info i, Xdimen *x)
{ switch(i)
  { 
    case b000: 
    { int n=HGET8;
     @+REF_RNG(xdimen_kind,n);
     x->w=xdimen_def[n].w;
     x->h=xdimen_def[n].h;
     x->v=xdimen_def[n].v;
     break;
    }  
    case b001: HGET_XDIMEN(b001,*x);@+break;
    case b010: HGET_XDIMEN(b010,*x);@+break;
    case b011: HGET_XDIMEN(b011,*x);@+break;
    case b100: HGET_XDIMEN(b100,*x);@+break;
    case b101: HGET_XDIMEN(b101,*x);@+break;
    case b110: HGET_XDIMEN(b110,*x);@+break;
    case b111: HGET_XDIMEN(b111,*x);@+break;
    default:
     x->w=0;x->h=x->v=0.0;
  }
}
static scaled hget_xdimen(Info i)
{ @+Xdimen x;
  hget_xdimen_def(i, &x);
  return  xdimen(&x);
 }
 
static void tag_expected(uint8_t b, uint8_t a, uint32_t a_pos)
{ QUIT("%s expected at 0x%x got [%s,%d]",NAME(b),a_pos,NAME(a),INFO(a));
}

static scaled hget_xdimen_node(void)
{ @+scaled x=0;
  @<read the start byte |a|@>@;
  if (KIND(a)==xdimen_kind)
    x=hget_xdimen(INFO(a));
  else tag_expected(TAG(xdimen_kind,0),a,node_pos);
  @<read and check the end byte |z|@>@;
  return x;
}

static void hget_xdimen_def_node(Xdimen *x)
{ @<read the start byte |a|@>@;
  if (KIND(a)==xdimen_kind)
    hget_xdimen_def(INFO(a),x);
  else  tag_expected(TAG(xdimen_kind,0),a,node_pos);
  @<read and check the end byte |z|@>@;
}
@

@<\HINT\ auxiliar  functions@>=
scaled hteg_xdimen(uint8_t a)
{ @+Xdimen x;
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
     tag_expected(TAG(xdimen_kind,0),a,node_pos);
   }
  return  xdimen(&x);
 }

scaled hteg_xdimen_node(void)
{ @+scaled x=0;
  @<read the end byte |z|@>@;
  if (KIND(z)==xdimen_kind)
    x=hteg_xdimen(z);
  else
     tag_expected(TAG(xdimen_kind,0),z,node_pos);
  @<read and check the start byte |a|@>@;
  return x;
}
@



\subsection{Stretch and Shrink}
@<GET macros@>=
#define @[HGET_STRETCH(F,O)@] @+{@+ Stch _st; @+ HGET32(_st.u);@/ (O)=_st.u&3;  _st.u&=~3; (F)=(scaled)(_st.f*ONE); @+}
@
@<TEG macros@>=
#define @[HTEG_STRETCH(F,O)@] @+{@+ Stch _st; @+ HTEG32(_st.u);@/ (O)=_st.u&3;  _st.u&=~3; (F)=(scaled)(_st.f*ONE); @+}
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
  f=HGET8; @+REF_RNG(font_kind,f);@/\
  tail_append(new_character(f,c));\
}
@

@<TEG macros@>=
#define @[HTEG_GLYPH(I)@] \
{@+uint8_t f; @+uint32_t c;\
  f=HTEG8; @+REF_RNG(font_kind,f);@/\
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

\subsection{Languages}
When rendering \HINT\ files, the language information can be ignored.
@<cases to get content@>=
case TAG(language_kind,b000):(void)HGET8; 
case TAG(language_kind,1): 
case TAG(language_kind,2): 
case TAG(language_kind,3): 
case TAG(language_kind,4): 
case TAG(language_kind,5): 
case TAG(language_kind,6): 
case TAG(language_kind,7): @+break;
@


@<cases to teg content@>=
case TAG(language_kind,b000): (void)HTEG8; 
case TAG(language_kind,1): 
case TAG(language_kind,2): 
case TAG(language_kind,3): 
case TAG(language_kind,4): 
case TAG(language_kind,5): 
case TAG(language_kind,6): 
case TAG(language_kind,7): @+break;
@



\subsection{Rules}



@<GET macros@>=
#define @[HGET_RULE(I)@]@/\
pointer p=new_rule();\
if ((I)&b100) HGET32(height(p)); @+else height(p)=null_flag;\
if ((I)&b010) HGET32(depth(p)); @+else depth(p)=null_flag;\
if ((I)&b001) HGET32(width(p)); @+else width(p)=null_flag;
@


@<TEG macros@>=
#define @[HTEG_RULE(I)@]@/\
pointer p=new_rule();\
if ((I)&b001) HTEG32(width(p)); @+else width(p)=null_flag;\
if ((I)&b010) HTEG32(depth(p)); @+else depth(p)=null_flag;\
if ((I)&b100) HTEG32(height(p)); @+else height(p)=null_flag;
@

@<cases to get content@>=
case TAG(rule_kind,b000): @+ tail_append(hget_rule_ref(HGET8));	prev_depth=ignore_depth; @+break;
case TAG(rule_kind,b011): @+{@+ HGET_RULE(b011); tail_append(p); prev_depth=ignore_depth;@+} break;
case TAG(rule_kind,b101): @+{@+ HGET_RULE(b101); tail_append(p); prev_depth=ignore_depth;@+} break;
case TAG(rule_kind,b001): @+{@+ HGET_RULE(b001); tail_append(p); prev_depth=ignore_depth;@+} break;
case TAG(rule_kind,b110): @+{@+ HGET_RULE(b110); tail_append(p); prev_depth=ignore_depth;@+} break;
case TAG(rule_kind,b111): @+{@+ HGET_RULE(b111); tail_append(p); prev_depth=ignore_depth;@+} break;
@

@<cases to teg content@>=
case TAG(rule_kind,b000): @+ tail_append(hget_rule_ref(HTEG8));	prev_height=ignore_depth; @+break;
case TAG(rule_kind,b011): @+{@+ HTEG_RULE(b011); tail_append(p); prev_height=ignore_depth;@+} break;
case TAG(rule_kind,b101): @+{@+ HTEG_RULE(b101); tail_append(p); prev_height=ignore_depth;@+} break;
case TAG(rule_kind,b001): @+{@+ HTEG_RULE(b001); tail_append(p); prev_height=ignore_depth;@+} break;
case TAG(rule_kind,b110): @+{@+ HTEG_RULE(b110); tail_append(p); prev_height=ignore_depth;@+} break;
case TAG(rule_kind,b111): @+{@+ HTEG_RULE(b111); tail_append(p); prev_height=ignore_depth;@+} break;
@


@<get functions@>=
pointer hget_rule_node(void)
{ @+ pointer q=null;
  @<read the start byte |a|@>@;
  if (KIND(a)==rule_kind) { HGET_RULE(INFO(a));q=p;}
  else  tag_expected(TAG(rule_kind,0),a,node_pos); 
  @<read and check the end byte |z|@>@;
  return q;
}
@

@<\HINT\ auxiliar functions@>=
static pointer hteg_rule_node(void)
{ @+ pointer q=null;
  @<read the end byte |z|@>@;
  if (KIND(z)==rule_kind) { HTEG_RULE(INFO(z));q=p;}
  else  tag_expected(TAG(rule_kind,0),z,node_pos);
  @<read and check the start byte |a|@>@;
  return q;
}
@


\subsection{Glue}
\noindent

@<GET macros@>=
#define @[HGET_GLUE(I)@] @/\
  p= get_node(glue_spec_size); \
  if((I)!=b111) { if ((I)&b100) HGET32(width(p));@+ else width(p)=0; }\
  if((I)&b010) HGET_STRETCH(stretch(p),stretch_order(p))@; else stretch(p)=0, stretch_order(p)=normal;\
  if((I)&b001) HGET_STRETCH(shrink(p),shrink_order(p))@; else shrink(p)=0, shrink_order(p)=normal;\
  if(I==b111) width(p)=hget_xdimen_node();
@

@<\HINT\ declarations@>=
static scaled hget_xdimen_node(void);
@

@<TEG macros@>=
#define @[HTEG_GLUE(I)@] @/\
  p= get_node(glue_spec_size); \
  if(I==b111) width(p)=hget_xdimen_node();\
  if((I)&b001) HTEG_STRETCH(shrink(p),shrink_order(p))@; else shrink(p)=0, shrink_order(p)=normal;\
  if((I)&b010) HTEG_STRETCH(stretch(p),stretch_order(p))@; else stretch(p)=0, stretch_order(p)=normal;\
  if((I)!=b111) { if ((I)&b100) HGET32(width(p));@+ else width(p)=0; } 
@


@<cases to get content@>=
case TAG(glue_kind,b000): @+tail_append(new_glue(hget_glue_ref(HGET8)));@+  break;
case TAG(glue_kind,b001): {@+pointer p;@+HGET_GLUE(b001);@+  tail_append(spec2glue(p));@+}@+break;
case TAG(glue_kind,b010): {@+pointer p;@+HGET_GLUE(b010);@+  tail_append(spec2glue(p));@+}@+break;
case TAG(glue_kind,b011): {@+pointer p;@+HGET_GLUE(b011);@+  tail_append(spec2glue(p));@+}@+break;
case TAG(glue_kind,b100): {@+pointer p;@+HGET_GLUE(b100);@+  tail_append(spec2glue(p));@+}@+break;
case TAG(glue_kind,b101): {@+pointer p;@+HGET_GLUE(b101);@+  tail_append(spec2glue(p));@+}@+break;
case TAG(glue_kind,b110): {@+pointer p;@+HGET_GLUE(b110);@+  tail_append(spec2glue(p));@+}@+break;
case TAG(glue_kind,b111): {@+pointer p;@+HGET_GLUE(b111);@+  tail_append(spec2glue(p));@+}@+break;
@


@<cases to teg content@>=
case TAG(glue_kind,b000): @+tail_append(new_glue(hget_glue_ref(HTEG8)));@+  break;
case TAG(glue_kind,b001): {@+pointer p;@+HTEG_GLUE(b001);@+  tail_append(spec2glue(p));@+}@+break;
case TAG(glue_kind,b010): {@+pointer p;@+HTEG_GLUE(b010);@+  tail_append(spec2glue(p));@+}@+break;
case TAG(glue_kind,b011): {@+pointer p;@+HTEG_GLUE(b011);@+  tail_append(spec2glue(p));@+}@+break;
case TAG(glue_kind,b100): {@+pointer p;@+HTEG_GLUE(b100);@+  tail_append(spec2glue(p));@+}@+break;
case TAG(glue_kind,b101): {@+pointer p;@+HTEG_GLUE(b101);@+  tail_append(spec2glue(p));@+}@+break;
case TAG(glue_kind,b110): {@+pointer p;@+HTEG_GLUE(b110);@+  tail_append(spec2glue(p));@+}@+break;
case TAG(glue_kind,b111): {@+pointer p;@+HTEG_GLUE(b111);@+  tail_append(spec2glue(p));@+}@+break;
@

The function |hget_glue_spec| returns a new pointer to a glue specification.
\TeX\ shares glue specification between different glue nodes and uses a reference count
to know when to deallocate it. So it is important to manage the reference counts correctly.
If no glue specification is found, a reference to the |zero_glue| is returned. Even in this
case, it is important to maintain a correct reference count.
Once the reference count is correct, the function |spec2glue| can be used to create a
glue node using the new pointer.

@<\HINT\ auxiliar functions@>=
static pointer hget_glue_spec(void)
{ @+pointer p=null;
  uint8_t a,z; /* the start and the end byte*/
  if (hpos>=hend || KIND(*hpos)!=glue_kind) 
  { p=zero_glue; incr(glue_ref_count(p)); }
  else
  { node_pos=hpos-hstart;
    HGETTAG(a);
    if (INFO(a)==b000) 
    { p=hget_glue_ref(HGET8); incr(glue_ref_count(p)); }    
    else
    { @+HGET_GLUE(INFO(a));@+}
    @<read and check the end byte |z|@>@;
  }
  return p;
}

static pointer spec2glue(pointer q)
{@+pointer p; 
p=get_node(small_node_size);type(p)=glue_node;subtype(p)=normal;
leader_ptr(p)=null;glue_ptr(p)=q;
return p;
}

static pointer hget_glue_node(void)
{ return spec2glue(hget_glue_spec());
}
@

@<\HINT\ auxiliar functions@>=
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
  if (p!=null) return spec2glue(p);
  else return new_glue(zero_glue);
}
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

@<\HINT\ auxiliar functions@>=
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

static pointer hget_text_list(uint32_t s);
static pointer hget_list_pointer(void)
{@+pointer p=null;
  uint32_t s, t;
  if (KIND(*hpos)==list_kind)
  { @<read the start byte |a|@>@;
    if ((INFO(a)&b011)==0) 
       HGET8; /* the empty list */
    else
    { s=hget_list_size(INFO(a)); 
      hget_size_boundary(INFO(a));
      if ((INFO(a)&b100)==0)
        p=hget_node_list(s);
      else
        p=hget_text_list(s);
      hget_size_boundary(INFO(a));
      t=hget_list_size(INFO(a)); 
      if (t!=s) 
        QUIT("List sizes at 0x%x and " SIZE_F " do not match 0x%x != 0x%x",
          node_pos+1,hpos-hstart-s-1,s,t);
    }
    @<read and check the end byte |z|@>@;
  }
  return p;
}
@

When we need to parse a list backwards that is part of a node. We
still want the resulting list in forward order. The simplest way to do
this, is moving to the beginning of the list and then parsing it in
forward order.

@<\HINT\ auxiliar functions@>=

static void hskip_list(void)
{ if (KIND(*hpos)==list_kind ||KIND(*hpos)==param_kind  )
  { Info i;
    uint8_t a;
    HGETTAG(a);
    i=INFO(a)&0x3;
    if (i==0) hpos=hpos+2; /* reference+tag */
    else
    { uint32_t s=hget_list_size(INFO(a));
      if (i==3) i=4; /* number of bytes for size */
      hpos = hpos + (1 + s + 1 + i + 1); 
    }
  }
}

static void hskip_list_back(void)
{ if (KIND(*(hpos-1))==list_kind || KIND(*(hpos-1))==param_kind)
  { Info i;
    uint8_t z; 
    z=HTEG8;
    i=INFO(z)&0x3;
    if (i==0) hpos=hpos-2;
    else
    { uint32_t s=hteg_list_size(INFO(z)); 
      if (i==3) i=4;
      hpos = hpos - (1+ s + 1+ i + 1); /*boundary tag+s+boundary tag+size+tag*/
    }
  }
}

pointer hteg_list_pointer(void)
{ uint8_t *list_start;
  pointer p;
  hskip_list_back();
  list_start=hpos;
  p=hget_list_pointer();
  hpos=list_start;
  return p;
}
@

\subsection{Parameter Lists}

We have defined a function to read parameter lists in section~\secref{getparamlist}.
Here we define the function that reads parameter lists backwards. Having seen how to read regular lists backwards,
the function should contain no surprises. We start with a simple functions to read an integer definition.


@<\HINT\ auxiliar functions@>=
#if 0
static int32_t hteg_integer_def(uint8_t z)
{ if (INFO(z)==1) { int8_t n=HTEG8; return n;}
  else  if (INFO(z)==2) { int16_t n; HTEG16(n); return n;}
  else if (INFO(z)==4) {int32_t n; HTEG32(n); return n;}
  else TAGERR(z);
  return 0;
}

static ParamDef *hteg_param_list(uint8_t z)
{ uint32_t s,t;
  ParamDef *p=NULL;
  uint8_t *list_start,*list_end;
  list_end=hpos;
  s=hteg_list_size(INFO(z)); 
  hteg_size_boundary(INFO(z));
  list_start=hpos-s;
  if (list_start<=hstart) 
    QUIT("list start before stream start\n"); 
  while (list_start < hpos)
  { @+ParamDef *r; Param *q;
    @<read the end byte |z|@>@;
    ALLOCATE(r,1,ParamDef);
    q=&(r->p);
    q->k=KIND(z);
    if (KIND(z)==int_kind) q->i=hteg_integer_def(a);
    else if (KIND(a)==dimen_kind) HTEG32(q->d);
    else if (KIND(a)==glue_kind) { pointer p;  HTEG_GLUE(INFO(z)); q->g=p;}
    else TAGERR(a);
    q->n=HTEG8;
    DBG(DBGTAGS,"Defining %s %d\n", definition_name[KIND(z)],q->n);
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

static ParamDef *hteg_param_list_node(void)
{ ParamDef *p;
  uint8_t *list_start;
  hskip_list_back();
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
p=new_null_box();\
HGET32(height(p));\
if ((I)&b001) HGET32(depth(p));\ 
HGET32(width(p));\
if ((I)&b010) HGET32(shift_amount(p));\ 
if ((I)&b100) @/{@+int8_t x; glue_set(p)=hget_float32();@/\
  x=HGET8; @+ glue_order(p)=x&0xF;\ 
  x=x>>4; glue_sign(p)=(x<0?shrinking:(x>0?stretching:normal));}\
list_ptr(p)=hget_list_pointer();
@

@<TEG macros@>=
#define @[HTEG_BOX(I)@] \
p=new_null_box();\
list_ptr(p)=hteg_list_pointer();\
if ((I)&b100) @/{@+int8_t x=HTEG8;@+ glue_order(p)=x&0xF;\ 
   x=x>>4; glue_sign(p)=(x<0?shrinking:(x>0?stretching:normal));\
   glue_set(p)=hteg_float32(); }\
if ((I)&b010) HTEG32(shift_amount(p));\ 
HTEG32(width(p));\
if ((I)&b001) HTEG32(depth(p));\ 
HTEG32(height(p));\
node_pos=hpos-hstart-1;
@



@<\HINT\ declarations@>=
static pointer hget_list_pointer(void);
static pointer hteg_list_pointer(void);
@


@<cases to get content@>=
case TAG(hbox_kind,b000): @+{@+pointer p;@+HGET_BOX(b000);@+happend_to_vlist(p);@+}@+ break;
case TAG(hbox_kind,b001): @+{@+pointer p;@+HGET_BOX(b001);@+happend_to_vlist(p);@+}@+ break;
case TAG(hbox_kind,b010): @+{@+pointer p;@+HGET_BOX(b010);@+happend_to_vlist(p);@+}@+ break;
case TAG(hbox_kind,b011): @+{@+pointer p;@+HGET_BOX(b011);@+happend_to_vlist(p);@+}@+ break;
case TAG(hbox_kind,b100): @+{@+pointer p;@+HGET_BOX(b100);@+happend_to_vlist(p);@+}@+ break;
case TAG(hbox_kind,b101): @+{@+pointer p;@+HGET_BOX(b101);@+happend_to_vlist(p);@+}@+ break;
case TAG(hbox_kind,b110): @+{@+pointer p;@+HGET_BOX(b110);@+happend_to_vlist(p);@+}@+ break;
case TAG(hbox_kind,b111): @+{@+pointer p;@+HGET_BOX(b111);@+happend_to_vlist(p);@+}@+ break;
case TAG(vbox_kind,b000): @+{pointer p;@+HGET_BOX(b000);@+type(p)=vlist_node;@+happend_to_vlist(p);@+} @+ break;
case TAG(vbox_kind,b001): @+{pointer p;@+HGET_BOX(b001);@+type(p)=vlist_node;@+happend_to_vlist(p);@+} @+ break;
case TAG(vbox_kind,b010): @+{pointer p;@+HGET_BOX(b010);@+type(p)=vlist_node;@+happend_to_vlist(p);@+} @+ break;
case TAG(vbox_kind,b011): @+{pointer p;@+HGET_BOX(b011);@+type(p)=vlist_node;@+happend_to_vlist(p);@+} @+ break;
case TAG(vbox_kind,b100): @+{pointer p;@+HGET_BOX(b100);@+type(p)=vlist_node;@+happend_to_vlist(p);@+} @+ break;
case TAG(vbox_kind,b101): @+{pointer p;@+HGET_BOX(b101);@+type(p)=vlist_node;@+happend_to_vlist(p);@+} @+ break;
case TAG(vbox_kind,b110): @+{pointer p;@+HGET_BOX(b110);@+type(p)=vlist_node;@+happend_to_vlist(p);@+} @+ break;
case TAG(vbox_kind,b111): @+{pointer p;@+HGET_BOX(b111);@+type(p)=vlist_node;@+happend_to_vlist(p);@+} @+ break;
@

@<cases to teg content@>=
case TAG(hbox_kind,b000): @+{@+pointer p;@+HTEG_BOX(b000);@+hprepend_to_vlist(p);@+}@+ break;
case TAG(hbox_kind,b001): @+{@+pointer p;@+HTEG_BOX(b001);@+hprepend_to_vlist(p);@+}@+ break;
case TAG(hbox_kind,b010): @+{@+pointer p;@+HTEG_BOX(b010);@+hprepend_to_vlist(p);@+}@+ break;
case TAG(hbox_kind,b011): @+{@+pointer p;@+HTEG_BOX(b011);@+hprepend_to_vlist(p);@+}@+ break;
case TAG(hbox_kind,b100): @+{@+pointer p;@+HTEG_BOX(b100);@+hprepend_to_vlist(p);@+}@+ break;
case TAG(hbox_kind,b101): @+{@+pointer p;@+HTEG_BOX(b101);@+hprepend_to_vlist(p);@+}@+ break;
case TAG(hbox_kind,b110): @+{@+pointer p;@+HTEG_BOX(b110);@+hprepend_to_vlist(p);@+}@+ break;
case TAG(hbox_kind,b111): @+{@+pointer p;@+HTEG_BOX(b111);@+hprepend_to_vlist(p);@+}@+ break;
case TAG(vbox_kind,b000): @+{pointer p;@+HTEG_BOX(b000);@+type(p)=vlist_node;@+hprepend_to_vlist(p);@+} @+ break;
case TAG(vbox_kind,b001): @+{pointer p;@+HTEG_BOX(b001);@+type(p)=vlist_node;@+hprepend_to_vlist(p);@+} @+ break;
case TAG(vbox_kind,b010): @+{pointer p;@+HTEG_BOX(b010);@+type(p)=vlist_node;@+hprepend_to_vlist(p);@+} @+ break;
case TAG(vbox_kind,b011): @+{pointer p;@+HTEG_BOX(b011);@+type(p)=vlist_node;@+hprepend_to_vlist(p);@+} @+ break;
case TAG(vbox_kind,b100): @+{pointer p;@+HTEG_BOX(b100);@+type(p)=vlist_node;@+hprepend_to_vlist(p);@+} @+ break;
case TAG(vbox_kind,b101): @+{pointer p;@+HTEG_BOX(b101);@+type(p)=vlist_node;@+hprepend_to_vlist(p);@+} @+ break;
case TAG(vbox_kind,b110): @+{pointer p;@+HTEG_BOX(b110);@+type(p)=vlist_node;@+hprepend_to_vlist(p);@+} @+ break;
case TAG(vbox_kind,b111): @+{pointer p;@+HTEG_BOX(b111);@+type(p)=vlist_node;@+hprepend_to_vlist(p);@+} @+ break;
@

@<get functions@>=
pointer hget_hbox_node(void)
{ @+  @<read the start byte |a|@>@;
   if (KIND(a)!=hbox_kind)  tag_expected(TAG(hbox_kind,0),a,node_pos);
   { @+pointer p;
    HGET_BOX(INFO(a));@/
    @<read and check the end byte |z|@>@;
    return p;
   }
}


pointer hget_vbox_node(void)
{@+
  @<read the start byte |a|@>@;
  if (KIND(a)!=vbox_kind)  tag_expected(TAG(vbox_kind,0),a,node_pos);
  {@+pointer p;
  HGET_BOX(INFO(a));@/
  @<read and check the end byte |z|@>@;
  type(p)=vlist_node; 
  return p;
}
}
@

@<\HINT\ auxiliar functions@>=
static pointer hteg_hbox_node(void)
{ @+  @<read the end byte |z|@>@;
   if (KIND(z)!=hbox_kind)  tag_expected(TAG(hbox_kind,0),z,node_pos);
   { @+pointer p;@+
    HTEG_BOX(INFO(z));@/
    @<read and check the start byte |a|@>@;
    return p;
   }
}
static pointer hteg_vbox_node(void)
{ @+  @<read the end byte |z|@>@;
   if (KIND(z)!=vbox_kind)  tag_expected(TAG(vbox_kind,0),z,node_pos);
   { @+pointer p;@+
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
 HGET32(height(p)); if ((I)&b001) HGET32(depth(p)); HGET32(width(p));\
 if ((I)&b010) HGET32(shift_amount(p));\
 HGET_STRETCH(st,sto); @+  HGET_STRETCH(sh,sho);@/\
 if ((I)&b100) x= hget_xdimen_node();  else x=hget_xdimen_ref(HGET8);\
 list_ptr(p)=hget_list_pointer();
@


@<TEG macros@>=
#define @[HTEG_SET(I)@] @/\
  scaled x, st, sh; @+uint8_t sto, sho; \
  p=new_null_box();\
  list_ptr(p)=hteg_list_pointer();\
  if ((I)&b100) x=hteg_xdimen_node(); else x=hget_xdimen_ref(HTEG8);\
  HTEG_STRETCH(sh,sho);@+HTEG_STRETCH(st,sto);\
  if ((I)&b010) HTEG32(shift_amount(p)); \
  HTEG32(width(p));@+if ((I)&b001) HTEG32(depth(p));@+HTEG32(height(p)); \
  node_pos=hpos-hstart-1;
@
@<\HINT\ declarations@>=
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
case TAG(hset_kind,b000): @+{@+pointer p;HTEG_SET(b000); @+hset(p,sto,st,sho,sh,x);@+hprepend_to_vlist(p);@+}@+break;
case TAG(hset_kind,b001): @+{@+pointer p;HTEG_SET(b001); @+hset(p,sto,st,sho,sh,x);@+hprepend_to_vlist(p);@+}@+ break;
case TAG(hset_kind,b010): @+{@+pointer p;HTEG_SET(b010); @+hset(p,sto,st,sho,sh,x);@+hprepend_to_vlist(p);@+}@+ break;
case TAG(hset_kind,b011): @+{@+pointer p;HTEG_SET(b011); @+hset(p,sto,st,sho,sh,x);@+hprepend_to_vlist(p);@+}@+ break;
case TAG(hset_kind,b100): @+{@+pointer p;HTEG_SET(b100); @+hset(p,sto,st,sho,sh,x);@+hprepend_to_vlist(p);@+}@+ break;
case TAG(hset_kind,b101): @+{@+pointer p;HTEG_SET(b101); @+hset(p,sto,st,sho,sh,x);@+hprepend_to_vlist(p);@+}@+ break;
case TAG(hset_kind,b110): @+{@+pointer p;HTEG_SET(b110); @+hset(p,sto,st,sho,sh,x);@+hprepend_to_vlist(p);@+}@+ break;
case TAG(hset_kind,b111): @+{@+pointer p;HTEG_SET(b111); @+hset(p,sto,st,sho,sh,x);@+hprepend_to_vlist(p);@+}@+ break;@#

case TAG(vset_kind,b000): @+{@+pointer p;HTEG_SET(b000); @+vset(p,sto,st,sho,sh,x);@+hprepend_to_vlist(p);@+}@+ break;
case TAG(vset_kind,b001): @+{@+pointer p;HTEG_SET(b001); @+vset(p,sto,st,sho,sh,x);@+hprepend_to_vlist(p);@+}@+ break;
case TAG(vset_kind,b010): @+{@+pointer p;HTEG_SET(b010); @+vset(p,sto,st,sho,sh,x);@+hprepend_to_vlist(p);@+}@+ break;
case TAG(vset_kind,b011): @+{@+pointer p;HTEG_SET(b011); @+vset(p,sto,st,sho,sh,x);@+hprepend_to_vlist(p);@+}@+ break;
case TAG(vset_kind,b100): @+{@+pointer p;HTEG_SET(b100); @+vset(p,sto,st,sho,sh,x);@+hprepend_to_vlist(p);@+}@+ break;
case TAG(vset_kind,b101): @+{@+pointer p;HTEG_SET(b101); @+vset(p,sto,st,sho,sh,x);@+hprepend_to_vlist(p);@+}@+ break;
case TAG(vset_kind,b110): @+{@+pointer p;HTEG_SET(b110); @+vset(p,sto,st,sho,sh,x);@+hprepend_to_vlist(p);@+}@+ break;
case TAG(vset_kind,b111): @+{@+pointer p;HTEG_SET(b111); @+vset(p,sto,st,sho,sh,x);@+hprepend_to_vlist(p);@+}@+ break;
@

The function |hset| computes |glue_set(p)| of a hlist node
depending on the available stretch, shrink, and the target width |x|.
@<\HINT\ auxiliar functions@>=
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
@

The function |vset| does the equivalent for vlist nodes.
If the depth value is |MAX_DIMEN+1|, |vset| will also reset 
height and depth to move the reference point to the top of the
vertical list. If the first item in the vertical list is a box
or a rule, the reference point will be the baseline of that box
or rule; otherwise the reference point will be the exact top of
the vertical list.

@<\HINT\ auxiliar functions@>=

void vset(pointer p, uint8_t sto, scaled st,
					uint8_t sho,scaled sh, scaled h)
{ @+scaled x;
  type(p)=vlist_node;
  x =height(p); /* natural height adjusted such that depth <= limit */ 
  height(p)=h; /* target height */
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
  if (depth(p)==MAX_DIMEN+1)
  { if (list_ptr(p)!=null && (type(list_ptr(p))==hlist_node || type(list_ptr(p))==vlist_node || type(list_ptr(p))==rule_node))
    { h = height(list_ptr(p));
      depth(p)=height(p) -h;
      height(p)=h;
    }
    else
    {depth(p)=depth(p)+height(p); height(p)=0; }
    DBG(DBGTEX,"vset top node adjusted height=%f depth=%f\n",height(p)/(double)ONE, depth(p)/(double)ONE);
  }
}
@

If the natural dimensions of a box are not known, we
need to traverse the content list before we can set the glue.

@<GET macros@>=
#define @[HGET_PACK(K,I)@] @/\
{ pointer p; @+scaled x, s=0, d; @+ uint8_t m; \
 if ((I)&b001) m=additional; else m=exactly; \
 if ((I)&b010) HGET32(s);\
 if (K==vpack_kind) HGET32(d); \
 if ((I)&b100) x= hget_xdimen_node();  else x=hget_xdimen_ref(HGET8);\
 p=hget_list_pointer(); \
 if (K==vpack_kind) { if (d<=MAX_DIMEN && d>=-MAX_DIMEN) p=vpackage(p,x,m,d); else p=vtop(p,x,m,d); } \
 else p=hpack(p,x,m);\
 shift_amount(p)=s;\
 happend_to_vlist(p);@+}
@

@<TEG macros@>=
#define @[HTEG_PACK(K,I)@] @/\
{ pointer p;@+ scaled x, s, d; @+ uint8_t m; \
 p=hteg_list_pointer();\
 if ((I)&b100) x=hteg_xdimen_node();@+  else x=hget_xdimen_ref(HTEG8);\
 if (K==vpack_kind) HTEG32(d); \
 if ((I)&b010) HTEG32(s);\
 if ((I)&b001) m=additional; else m=exactly; \
 node_pos=hpos-hstart-1;\
 if (K==vpack_kind)  { if (d<=MAX_DIMEN && d>=-MAX_DIMEN) p=vpackage(p,x,m,d); else p=vtop(p,x,m,d); } \
 else p=hpack(p,x,m);\
 hprepend_to_vlist(p);@+} 
@

@<cases to get content@>=
case TAG(hpack_kind,b000): @+HGET_PACK(hpack_kind,b000);@+break;
case TAG(hpack_kind,b010): @+HGET_PACK(hpack_kind,b010);@+break;
case TAG(hpack_kind,b100): @+HGET_PACK(hpack_kind,b100);@+break;
case TAG(hpack_kind,b110): @+HGET_PACK(hpack_kind,b110);@+break;
case TAG(hpack_kind,b001): @+HGET_PACK(hpack_kind,b001);@+break;
case TAG(hpack_kind,b011): @+HGET_PACK(hpack_kind,b011);@+break;
case TAG(hpack_kind,b101): @+HGET_PACK(hpack_kind,b101);@+break;
case TAG(hpack_kind,b111): @+HGET_PACK(hpack_kind,b111);@+break;@#

case TAG(vpack_kind,b000): @+HGET_PACK(vpack_kind,b000);@+break;
case TAG(vpack_kind,b010): @+HGET_PACK(vpack_kind,b010);@+break;
case TAG(vpack_kind,b100): @+HGET_PACK(vpack_kind,b100);@+break;
case TAG(vpack_kind,b110): @+HGET_PACK(vpack_kind,b110);@+break;
case TAG(vpack_kind,b001): @+HGET_PACK(vpack_kind,b001);@+break;
case TAG(vpack_kind,b011): @+HGET_PACK(vpack_kind,b011);@+break;
case TAG(vpack_kind,b101): @+HGET_PACK(vpack_kind,b101);@+break;
case TAG(vpack_kind,b111): @+HGET_PACK(vpack_kind,b111);@+break;
@
@<cases to teg content@>=
case TAG(hpack_kind,b000): @+HTEG_PACK(hpack_kind,b000);@+break;
case TAG(hpack_kind,b010): @+HTEG_PACK(hpack_kind,b010);@+break;
case TAG(hpack_kind,b100): @+HTEG_PACK(hpack_kind,b100);@+break;
case TAG(hpack_kind,b110): @+HTEG_PACK(hpack_kind,b110);@+break;
case TAG(hpack_kind,b001): @+HTEG_PACK(hpack_kind,b001);@+break;
case TAG(hpack_kind,b011): @+HTEG_PACK(hpack_kind,b011);@+break;
case TAG(hpack_kind,b101): @+HTEG_PACK(hpack_kind,b101);@+break;
case TAG(hpack_kind,b111): @+HTEG_PACK(hpack_kind,b111);@+break;

case TAG(vpack_kind,b000): @+HTEG_PACK(vpack_kind,b000);@+break;
case TAG(vpack_kind,b010): @+HTEG_PACK(vpack_kind,b010);@+break;
case TAG(vpack_kind,b100): @+HTEG_PACK(vpack_kind,b100);@+break;
case TAG(vpack_kind,b110): @+HTEG_PACK(vpack_kind,b110);@+break;
case TAG(vpack_kind,b001): @+HTEG_PACK(vpack_kind,b001);@+break;
case TAG(vpack_kind,b011): @+HTEG_PACK(vpack_kind,b011);@+break;
case TAG(vpack_kind,b101): @+HTEG_PACK(vpack_kind,b101);@+break;
case TAG(vpack_kind,b111): @+HTEG_PACK(vpack_kind,b111);@+break;
@

@<\HINT\ auxiliar functions@>=
static pointer vtop(pointer @!p, scaled @!h, small_number @!m, scaled d)
{ d=d^0x40000000;
  p=vpackage(p,h,m,d);
  if (list_ptr(p)!=null && (type(list_ptr(p))==hlist_node || type(list_ptr(p))==vlist_node || type(list_ptr(p))==rule_node))
  { h = height(list_ptr(p));
    depth(p)=depth(p)+height(p) -h;
    height(p)=h;
  }
  else
  { depth(p)=depth(p)+height(p); height(p)=0; }
  DBG(DBGTEX,"vpack top node adjusted height=%f depth=%f\n",height(p)/(double)ONE, depth(p)/(double)ONE);
  return p;
}
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
{@+pointer p;\
 if ((I)&b100)p=hget_glue_node(); else {p=spec2glue(zero_glue); incr(glue_ref_count(zero_glue));} \
@+subtype(p)=a_leaders+((I)&b011)-1;\
if (KIND(*hpos)==rule_kind) leader_ptr(p)=hget_rule_node(); \
else if (KIND(*hpos)==hbox_kind) leader_ptr(p)=hget_hbox_node(); \
else  leader_ptr(p)=hget_vbox_node();\
tail_append(p);}
@

@<TEG macros@>=
#define @[HTEG_LEADERS(I)@]@/ \
{@+pointer p,q;\
if (KIND(*(hpos-1))==rule_kind) q=hteg_rule_node(); \
else if (KIND(*(hpos-1))==hbox_kind) q=hteg_hbox_node(); \
else  q=hteg_vbox_node();\
if ((I)&b100) p=hteg_glue_node(); else {p=spec2glue(zero_glue); incr(glue_ref_count(zero_glue));} \
leader_ptr(p)=q;@+subtype(p)=a_leaders+((I)&b011)-1;\
tail_append(p);}
@



@<cases to get content@>=
case TAG(leaders_kind,0):        @+ tail_append(hget_leaders_ref(HGET8)); @+break;
case TAG(leaders_kind,1):        @+ HGET_LEADERS(1); @+break;
case TAG(leaders_kind,2):        @+ HGET_LEADERS(2); @+break;
case TAG(leaders_kind,3):        @+ HGET_LEADERS(3); @+break;
case TAG(leaders_kind,b100|1):        @+ HGET_LEADERS(b100|1); @+break;
case TAG(leaders_kind,b100|2):        @+ HGET_LEADERS(b100|2); @+break;
case TAG(leaders_kind,b100|3):        @+ HGET_LEADERS(b100|3); @+break;
@
@<cases to teg content@>=
case TAG(leaders_kind,0):        @+ tail_append(hget_leaders_ref(HTEG8)); @+break;
case TAG(leaders_kind,1):        @+ HTEG_LEADERS(1); @+break;
case TAG(leaders_kind,2):        @+ HTEG_LEADERS(2); @+break;
case TAG(leaders_kind,3):        @+ HTEG_LEADERS(3); @+break;
case TAG(leaders_kind,b100|1):        @+ HTEG_LEADERS(b100|1); @+break;
case TAG(leaders_kind,b100|2):        @+ HTEG_LEADERS(b100|2); @+break;
case TAG(leaders_kind,b100|3):        @+ HTEG_LEADERS(b100|3); @+break;
@


\subsection{Baseline Skips}

@<GET macros@>=
#define @[HGET_BASELINE(I)@] \
  cur_list.bs_pos=hpos-1; \
  if((I)&b001) HGET32(cur_lsl); @+else cur_lsl=0; \
  if((I)&b100) cur_bs=hget_glue_spec(); else cur_bs=zero_glue; \
  if((I)&b010) cur_ls=hget_glue_spec(); else cur_ls=zero_glue;
@

@<TEG macros@>=
#define @[HTEG_BASELINE(I)@] \
  if((I)&b010) cur_ls=hteg_glue_spec(); else cur_ls=zero_glue; \
  if((I)&b100) cur_bs=hteg_glue_spec(); else cur_bs=zero_glue; \
  if((I)&b001) HTEG32(cur_lsl); @+else cur_lsl=0; \
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
Ligatures are currently the only kind of node that uses lists of character codes
encoded as texts. So we define first a simplified version of |hget_text_list|.


@<\HINT\ auxiliar functions@>=
static pointer hget_text_list(uint32_t s)
{ pointer p=null;
  pointer *pp=&p;
  uint8_t *t=hpos+s;
  while (hpos<t) {*pp=new_character(0,hget_utf8()); pp=&link(*pp);}
  return p;
}
@


@<GET macros@>=
#define @[HGET_LIG(I)@] @/\
{@+pointer p,q;@+uint8_t f;\
f=HGET8;\
if ((I)==7) q=hget_list_pointer(); else q=hget_text_list(I);\
if (q==null) QUIT("Ligature with empty list");\
p=new_ligature(f, character(q), link(q)); tail_append(p);\
link(q)=null; flush_node_list(q);\
}
@

@<TEG macros@>=
#define @[HTEG_LIG(I)@] @/\
{@+pointer p,q;\
if ((I)==7) q=hteg_list_pointer();\
else {uint8_t *t=hpos; hpos=t-I; q=hget_text_list(I); hpos=t-I;}\
if (q==null) QUIT("Ligature with empty list");\
p=new_ligature(0, character(q), link(q)); tail_append(p);\
link(q)=null; flush_node_list(q);\
font(lig_char(p))=HTEG8;\
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
#define @[HGET_DISC(I)@]\
  pointer p=new_disc(); \
  if ((I)&b100) {uint8_t r; @+r=HGET8; set_replace_count(p,r); \
                 if ((r&0x80)==0) set_auto_disc(p); @+}\
  else  set_auto_disc(p); \
  if ((I)&b010) pre_break(p)=hget_list_pointer(); \
  if ((I)&b001) post_break(p)=hget_list_pointer();
@

@<TEG macros@>=
#define @[HTEG_DISC(I)@]\
  pointer p=new_disc(); \
  if ((I)&b001) post_break(p)=hteg_list_pointer(); \
  if ((I)&b010) pre_break(p)=hteg_list_pointer(); \
  if ((I)&b100) {uint8_t r; @+r=HTEG8; set_replace_count(p,r); \
                 if ((r&0x80)==0) set_auto_disc(p); @+}\
  else  set_auto_disc(p);
@



@<cases to get content@>=
case TAG(disc_kind,b000): @+tail_append(hget_hyphen_ref(HGET8));  @+break;
case TAG(disc_kind,b001): @+{@+HGET_DISC(b001);@+tail_append(p);@+} @+break;
case TAG(disc_kind,b010): @+{@+HGET_DISC(b010);@+tail_append(p);@+} @+break;
case TAG(disc_kind,b011): @+{@+HGET_DISC(b011);@+tail_append(p);@+} @+break;
case TAG(disc_kind,b100): @+{@+HGET_DISC(b100);@+tail_append(p);@+} @+break;
case TAG(disc_kind,b101): @+{@+HGET_DISC(b101);@+tail_append(p);@+} @+break;
case TAG(disc_kind,b110): @+{@+HGET_DISC(b110);@+tail_append(p);@+} @+break;
case TAG(disc_kind,b111): @+{@+HGET_DISC(b111);@+tail_append(p);@+} @+break;
@
@<cases to teg content@>=
case TAG(disc_kind,b000): @+tail_append(hget_hyphen_ref(HTEG8));  @+break;
case TAG(disc_kind,b001): @+{@+HTEG_DISC(b001);@+tail_append(p);@+} @+break;
case TAG(disc_kind,b010): @+{@+HTEG_DISC(b010);@+tail_append(p);@+} @+break;
case TAG(disc_kind,b011): @+{@+HTEG_DISC(b011);@+tail_append(p);@+} @+break;
case TAG(disc_kind,b100): @+{@+HTEG_DISC(b100);@+tail_append(p);@+} @+break;
case TAG(disc_kind,b101): @+{@+HTEG_DISC(b101);@+tail_append(p);@+} @+break;
case TAG(disc_kind,b110): @+{@+HTEG_DISC(b110);@+tail_append(p);@+} @+break;
case TAG(disc_kind,b111): @+{@+HTEG_DISC(b111);@+tail_append(p);@+} @+break;
@


@<\HINT\ auxiliar functions@>=
static pointer hget_disc_node(void)
{  @+@<read the start byte |a|@>@;
   if (KIND(a)!=disc_kind || INFO(a)==b000) 
     tag_expected(TAG(disc_kind,1),a,node_pos);
   { @+
   HGET_DISC(INFO(a));
   @<read and check the end byte |z|@>@;
   return p;
   }
}
@

@<teg functions@>=
pointer hteg_disc_node(void)
{  @+@<read the end byte |z|@>@;
   if (KIND(z)!=disc_kind || INFO(z)==b000) 
     tag_expected(TAG(disc_kind,1),z,node_pos); 
   { @+
   HTEG_DISC(INFO(z));
   @<read and check the start byte |a|@>@;
   return p;
   }
}
@


\subsection{Paragraphs}

@<GET macros@>=
#define @[HGET_PAR(I)@] @/\
{ @+scaled x=0;\
  ParamDef *q;\
  if ((I)==b100) q=hget_param_list_ref(HGET8);\
  if ((I)&b100) x=hget_xdimen_node(); else x=hget_xdimen_ref(HGET8);\
  if ((I)&b010) q=hget_param_list_node(); \
  else if ((I)!=b100) q=hget_param_list_ref(HGET8);\
  hget_paragraph(x,0,q);\
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
the new page. Since break nodes always point to a |kern_node|, |glue_node|, 
|math_node|, |penalty_node|, or |disc_node|,
we record the positions of these nodes. By the way, glue nodes are not
legal breakpoints when they appear in formulas and when the previous
node is not a glue node, penalty node, math node, or explicit kern
node.  In the latter case, the explicit kern node preceeding the glue
is a legal breakpoint.  % see section 888 in TeX the program 
It should
be possible to store all these positions in a local table and clear it
once the lines are appended to the main list and the positions are set
for the inter line glues. But for the sake of simplicity, we stick
with one big global table for now.

It is possible to call |hget_paragraph| with an |offset| to obtain
only the trailing lines of the paragraphs. This feature is used when a
page starts in the middle of a paragraph.  Currently only the
remainder of the paragraph is passed to the |line_break| routine.  It
might be better to generate the whole paragraph, forcing a line break
at the position indicated by the offset, because this would allow a
simple implementation of correct hanging indentation and the parshape
feature of \TeX.  If the offset is positive, unwanted nodes are pruned
from the beginning of the list in the same way \TeX\ does it. We also
transplant the post-break list of a discretionary hyphen.

@<\HINT\ auxiliar functions@>=
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


void hprune_unwanted_nodes(void)
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
@<\HINT\ |extern|@>=
extern void hprune_unwanted_nodes(void);
@

Because paragraphs can be broken accross pages, we need to obtain
parts of a paragraph.  For a page with a given starting point in the
middle of a paragraph, we need a paragraph broken into lines in such a
way that one of the lines starts exactly at the starting point of the
page.  For a page with a given end-point, we need a paragraph broken
into lines in such a way that one of the lines ends exactly at the
end-point of the page.  The combination is not needed because we are
always free to choose one end of the page.

I guess that the proper thing to do is: reading the entire paragraph,
modifying the line breaking routine to force a line break at a given
offset and then let the remaining program choose which parts of the
paragraph to use.

In the moment, however, I shy away from touching the line breaking
routine and just feed only part of the paragraph to the unmodified
line breaking routine.

The following functions retrieve either all of the paragraph or either
the initial or the final part of it.


We start with processing the entire paragraph.
Reading the node list inside the paragraph is similar to
what the function |hget_list_pointer| will do, but in addition
we store the position of horizontal nodes.

@<\HINT\ auxiliar functions@>=
pointer hget_paragraph_all(scaled x)
{@+uint8_t *to;
  @<prepare for reading the paragraph list@>@;
  to = list_end;
  @<read the paragraph list@>@;
  @<finalize reading the  the paragraph list@>@;
  return par_ptr;
}

@ Befor we scan the content of a paragraph, 
we check for a non empty list, get its size,
start a new nesting level, and set its horizontal size.

@<prepare for reading the paragraph list@>=
  pointer par_ptr=null;
  if (KIND(*hpos)==list_kind)
  { uint32_t s, t;
    @<read the start byte |a|@>@;
    if ((INFO(a)&b011)==0) 
      HGET8; /* the empty list */
    else if (INFO(a)&b100)
      QUIT("Text in paragraph not yet implemented");
    else
    { @+uint8_t *list_end;
      s=hget_list_size(INFO(a));
      hget_size_boundary(INFO(a)); 
      list_end=hpos+s;
      cur_list.hs_field=x;
      push_nest();
      cur_list.bs_pos=NULL;

@ Then we read the paragraph list and handle its end.

@<read the paragraph list@>=
      while (hpos<to)
      { hget_content();
        if (nest_ptr==1) 
        { pointer p=tail;
           if (p!=head && !is_char_node(p) && 
           (type(p)==glue_node || type(p)==kern_node || type(p)==penalty_node 
           || type(p)==disc_node || type(p)==math_node))
             store_map(p,node_pos,0); 
        }
      }

@ It remains to take the new list out of the nest and check the end byte.

@<finalize reading the  the paragraph list@>=
      if (head!=tail) 
      { par_ptr=link(head);
        store_map(par_ptr,node_pos,0); 
        if (needs_bs) 
          QUIT("Unexpected trailing baseline node");
      }
      pop_nest();      
    }
    hget_size_boundary(INFO(a));
    t=hget_list_size(INFO(a)); 
    if (t!=s) 
      QUIT("List sizes at 0x%x and " SIZE_F " do not match 0x%x != 0x%x",
        node_pos+1,hpos-hstart-s-1,s,t);
    @<read and check the end byte |z|@>@;
  }



@ Next we look at retrieving the final part staring at a 
given position |from| inside the paragraph.
We examine the start of the node list and replace a 
hyphen node by its post break list.
Otherwise we remove unwanted space from the beginning of the list.

@<\HINT\ auxiliar functions@>=
pointer hget_paragraph_final(scaled x, uint8_t *from)
{@+uint8_t *to;
  @<prepare for reading the paragraph list@>@;
  hpos=from; to=list_end;
  @<read the paragraph list@>@;
  if (link(head)!=null && !is_char_node(link(head)))
  { if (type(link(head))==disc_node)
      transplant_post_break_list();
    else
      hprune_unwanted_nodes(); 
  }
  @<finalize reading the  the paragraph list@>@;
  return par_ptr;
}
@

Getting the initial part of a paragraph again needs some small modifications
to take care of ending an incomplete paragraph.

@<get functions@>=
pointer hget_paragraph_initial(scaled x, uint8_t *to)
{ @+@<prepare for reading the paragraph list@>@;
    if (to>list_end) 
    { LOG("Value of to greater than list_end"); 
      to=list_end;
    }
    @<read the paragraph list@>@;
    if (KIND(*to)==disc_kind)
    { hget_content();
      store_map(tail,node_pos,0); 
      transplant_pre_break_list();
    }
    if (head!=tail)
      @<add the node that terminates an incomplete paragraph@>@;
    hpos=list_end;
    @<finalize reading the  the paragraph list@>@;
  return par_ptr;
}
@

\TeX\ normaly ends a paragraph  with a glue node by adding a parfill glue,
and it relies on this paragraph ending because it does not check for the end
of the list while processing character nodes. 
We generate the initial part of a paragraph because we need a page that ends
after that initial part of the paragraph. How to do that nicely is an 
open question. Here, we just add a penalty and a zero glue.

@<add the node that terminates an incomplete paragraph@>=
{ if (is_char_node(tail)) tail_append(new_penalty(inf_penalty))@;
  else if (type(tail)!=glue_node) tail_append(new_penalty(inf_penalty))@;
  else
  {@+type(tail)=penalty_node;delete_glue_ref(glue_ptr(tail));
     flush_node_list(leader_ptr(tail));penalty(tail)=inf_penalty;
  }
  tail_append(new_glue(zero_glue));
}
@


With every paragraph the \HINT\ file specifies a parameter list containing
those parameters of the line breaking algorithm that differ from the
parameter values in the definition section. These changes are relevant for line
breaking only, not for parsing the paragraphs content. On the contrary,
any glue value that might occur in the paragraph can refere to one of the
predefined glues in the definition section and the changes needed for line breaking
should not influnce these glues.
One difficulty arrises from displayed equations that are embedded inside
a paragraph: they interrupt the paragraph and call the line breaking routine
for the paragraph-so-far before placing the formula and continuing with the
remainder of the paragraph. Currently there is only one parameter list
for the entire paragraph with possibley multiple calls to |line_break|.
And while the |line_break| routine is never nested, paragraphs can be nested.
This makes it necessary to have access to the innermost paragraphs parameter list
while parsing the paragraphs content just in case there are one ore more
displayed equations inside.
When we parse a paragraph we put the current paragraph parameters in a global
variable, and save a possible outer parameter list in a local variable to restore
the global varaiable once the paragraph is finished.

@<\HINT\ variables@>=
static ParamDef *line_break_params=NULL;
@

We provide a functions to set the parameters from this special variable,
thus avoiding the export of the |ParamDef| type.

@<\HINT\ functions@>=
void set_line_break_params(void)
{ hset_param_list(line_break_params);
}
@
@<\HINT\ |extern|@>=
extern void set_line_break_params(void);
@


@<\HINT\ auxiliar functions@>=
pointer hget_paragraph(scaled x, uint32_t offset, ParamDef *q)
{ @+
  pointer p, par_head;
  ParamDef *save_lbp = line_break_params;
  par_head=tail; /* here the paragraph gets added */
  line_break_params=q;
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
  line_break_params=save_lbp;  
  return par_head;
}

void hget_par_node(uint32_t offset)
{ @+ scaled x=0;
  ParamDef *q;
  @<read the start byte |a|@>@;
  node_pos=(hpos-hstart)-1;
   if (KIND(a)!=par_kind)
    tag_expected(TAG(par_kind,0),a,node_pos);
  node_pos=(hpos-hstart)-1;
  if (INFO(a)==b100) q=hget_param_list_ref(HGET8);
  if (INFO(a)&b100) x=hget_xdimen_node(); else x=hget_xdimen_ref(HGET8);
  if (INFO(a)&b010) q=hget_param_list_node(); else q=hget_param_list_ref(HGET8);
  hget_paragraph(x,offset,q);
  @<read and check the end byte |z|@>@;
}
@
@<\HINT\ |extern|@>=
extern void hget_par_node(uint32_t offset);
@



@<cases to teg content@>=
case TAG(par_kind,b000): @+hteg_paragraph(b000);@+break;
case TAG(par_kind,b010): @+hteg_paragraph(b010);@+break;
case TAG(par_kind,b100): @+hteg_paragraph(b100);@+break;
case TAG(par_kind,b110): @+hteg_paragraph(b110);@+break;
@

When we need to read a paragraph node backwards, we simply skip to the beginning and read the node
in forward direction. To prevent the line breaking routine to insert a baseline skip
before the first line---this has to wait until we know the box that preceeds the
paragraph---the |bs_pos| is set to |NULL|. Further we store the value of |prev_height|
to be able to restore it after line breaking.

@<\HINT\ auxiliar functions@>=
void hteg_paragraph(Info i)
{@+scaled x=0;
  ParamDef *q=null;
  pointer par_head;
  uint8_t *bs_pos=cur_list.bs_pos; /* the possible baseline skip */ 
  scaled ph=prev_height; 
  uint8_t *list_start, *par_start;
  hskip_list_back();
  list_start=hpos;
  if (INFO(i)&b010) q=hteg_param_list_node(); 
  else if (INFO(i)!=b100) q=hget_param_list_ref(HTEG8);
  if (INFO(i)&b100) x=hteg_xdimen_node(); else x=hget_xdimen_ref(HTEG8);
  if (INFO(i)==b100) q=hget_param_list_ref(HTEG8);
  par_start=hpos;
  node_pos=par_start-hstart-1;
  hpos=list_start;
  cur_list.bs_pos=NULL;
  par_head=hget_paragraph(x,0,q);
  @<Turn the paragraph upside down@>@;
  hpos=par_start;
}
@
The |hget_paragraph| function adds the individual lines in top to
bottom order to the current list. Running the page builder in bottom
up direction requires, however, that the lines come in bottom to top
order. The following code, removes the lines of the paragraph from the
current list, reverses the links, and attaches the list again in the new order.
Before calling |hprepend_to_vlist|, we restore the position of the
baseline skip and the previous height.
At the end, we update the |tail| pointer and the |prev_height|.

@<Turn the paragraph upside down@>=
{ pointer p,r, par_tail;
  p=null;
  r=par_tail=link(par_head);
 
  tail=par_head;
  link(tail)=null;
  while (r!=null)
  { pointer q=link(r);
    link(r)=p;
    p=r;
    r=q;
  }
  cur_list.bs_pos=bs_pos;
  prev_height=ph; 
  hprepend_to_vlist(p);
  tail=par_tail;
  if (type(tail)==hlist_node || type(tail)==vlist_node)
     prev_height=height(tail);
}
@



@<teg functions@>=
void hteg_par_node(uint32_t offset)
{ @+ scaled x=0;
  ParamDef *save_lbp = line_break_params;
  pointer p;
  pointer par_head=tail; /* here the paragraph gets added */
  uint8_t *bs_pos=cur_list.bs_pos; /* the possible baseline skip */
  scaled ph=prev_height; /* the height of the preceeding box */
  @<read the start byte |a|@>@;
  node_pos=(hpos-hstart)-1;
  if (INFO(a)&b100) x=hget_xdimen_node(); else x=hget_xdimen_ref(HGET8);
  if (INFO(a)&b010) line_break_params=hget_param_list_node(); else line_break_params=hget_param_list_ref(HGET8);
  prev_graf=0;
  p=hget_paragraph_initial(x,hstart+node_pos+offset);
  @<read and check the end byte |z|@>@;
  cur_list.bs_pos=NULL; 
  if (p!=null) 
    line_break(hget_integer_ref(widow_penalty_no), p);   
  if (par_head!=tail)
    @<Turn the paragraph upside down@>@;    
  hpos=hstart+node_pos;
  line_break_params=save_lbp;  
}

@
@<\HINT\ |extern|@>=
extern void hteg_par_node(uint32_t offset);
@


\subsection{Mathematics}

@<GET macros@>=
#define @[HGET_MATH(I)@] \
{@+ ParamDef *q;@+ pointer p=null, a=null;\
if ((I)&b100) q=hget_param_list_node(); else q=hget_param_list_ref(HGET8);\
if ((I)&b010) a=hget_hbox_node(); \
p=hget_list_pointer(); \
if ((I)&b001) a=hget_hbox_node();\
hset_param_list(q); hdisplay(p,a,((I)&b010)!=0); hrestore_param_list();\
}
@

@<TEG macros@>=
#define @[HTEG_MATH(I)@] \
{@+ ParamDef *q;@+ pointer p=null, a=null;\
if ((I)&b001) a=hteg_hbox_node();\
p=hteg_list_pointer(); \
if ((I)&b010) a=hteg_hbox_node(); \
if ((I)&b100) q=hteg_param_list_node(); else q=hget_param_list_ref(HTEG8);\
hset_param_list(q); hdisplay(p,a,((I)&b010)!=0); hrestore_param_list();\
}
@


@<cases to get content@>=
case TAG(math_kind,b000): HGET_MATH(b000); @+ break;
case TAG(math_kind,b001): HGET_MATH(b001); @+ break;
case TAG(math_kind,b010): HGET_MATH(b010); @+ break;
case TAG(math_kind,b100): HGET_MATH(b100); @+ break;
case TAG(math_kind,b101): HGET_MATH(b101); @+ break;
case TAG(math_kind,b110): HGET_MATH(b110); @+ break;
@

@<cases to teg content@>=
case TAG(math_kind,b000): HTEG_MATH(b000); @+ break;
case TAG(math_kind,b001): HTEG_MATH(b001); @+ break;
case TAG(math_kind,b010): HTEG_MATH(b010); @+ break;
case TAG(math_kind,b100): HTEG_MATH(b100); @+ break;
case TAG(math_kind,b101): HTEG_MATH(b101); @+ break;
case TAG(math_kind,b110): HTEG_MATH(b110); @+ break;
@

The |hdisplay| function now needs to do all the things we have skipped
while running Hi\TeX: the code in \<Go into display math mode> and \<Finish displayed math>.
We terminate the present paragraph and pass the list so far to
the line breaking routine, observe the dimensions of the
final line of the preceeding paragraph, position the display
and continue with reading the paragraph. To make shure the paragraph following
the display gets the proper baseline skip, we modify the current list.


Here are the simple cases: switching math mode on and off.

@<cases to get content@>=
case TAG(math_kind,b111): tail_append(new_math(0,before));@+break;
case TAG(math_kind,b011):  tail_append(new_math(0,after));@+break;
@
@<cases to teg content@>=
case TAG(math_kind,b111): tail_append(new_math(0,before));@+break;
case TAG(math_kind,b011):  tail_append(new_math(0,after));@+break;
@

\subsection{Adjustments}
Vertical adjustments are inside horizontal lists. They migrate to the enclosing vertical list
where they are unpacked and added after the horizontal material.
Inside a paragraph, this means the adjustment comes after the line that contains the adjustment.
Outside a paragraph, \TeX\ will do the moving and unpacking even before the adjustment has a
chance to get into the \HINT\ file. If we parse paragraphs, we parse in forward direction;
hence, we do not need to parse adjustments in backward direction.

@<GET macros@>=
#define @[HGET_ADJUST(I)@] @/\ 
{ @+pointer p;\
  p=get_node(small_node_size); type(p)=adjust_node; subtype(p)=normal;\
  adjust_ptr(p)=hget_list_pointer(); \
  tail_append(p);\
}
@

@<cases to get content@>=
case TAG(adjust_kind,1):  @+HGET_ADJUST(1); @+ break;
@

\subsection{Tables}
Currently tables are not yet implemented. We skip table and item nodes

@<GET macros@>=
#define @[HGET_TABLE(I)@] \
if(I&b010) /* v */; @+else /* h */;\
if ((I)&b001) /* add */;@+ else /* to */;\
if ((I)&b100) hget_xdimen_node(); else hget_xdimen_ref(HGET8);\
hget_list_pointer(); /* tabskip */ \
hget_list_pointer(); /* items */
@

@<TEG macros@>=
#define @[HTEG_TABLE(I)@] \
if(I&b010) /* v */; @+else /* h */;\
if ((I)&b001) /* add */;@+ else /* to */;\
hteg_list_pointer();  /* items */ \
hteg_list_pointer(); /* tabskip */ \
if ((I)&b100) hteg_xdimen_node(); else hget_xdimen_ref(HTEG8);
@




@<cases to get content@>=
case TAG(table_kind,b000): @+ HGET_TABLE(b000); @+ break;
case TAG(table_kind,b001): @+ HGET_TABLE(b001); @+ break;
case TAG(table_kind,b010): @+ HGET_TABLE(b010); @+ break;
case TAG(table_kind,b011): @+ HGET_TABLE(b011); @+ break;
case TAG(table_kind,b100): @+ HGET_TABLE(b100); @+ break;
case TAG(table_kind,b101): @+ HGET_TABLE(b101); @+ break;
case TAG(table_kind,b110): @+ HGET_TABLE(b110); @+ break;
case TAG(table_kind,b111): @+ HGET_TABLE(b111); @+ break;@#

case TAG(item_kind,b000):  hget_list_pointer();@+@+ break;
case TAG(item_kind,b001):  hget_content();@+break;
case TAG(item_kind,b010):  hget_content();@+break;
case TAG(item_kind,b011):  hget_content();@+break;
case TAG(item_kind,b100):  hget_content();@+break;
case TAG(item_kind,b101):  hget_content();@+break;
case TAG(item_kind,b110):  hget_content();@+break;
case TAG(item_kind,b111):  (void)HGET8;@+hget_content();@+break;
@

@<cases to teg content@>=
case TAG(table_kind,b000): @+ HTEG_TABLE(b000); @+ break;
case TAG(table_kind,b001): @+ HTEG_TABLE(b001); @+ break;
case TAG(table_kind,b010): @+ HTEG_TABLE(b010); @+ break;
case TAG(table_kind,b011): @+ HTEG_TABLE(b011); @+ break;
case TAG(table_kind,b100): @+ HTEG_TABLE(b100); @+ break;
case TAG(table_kind,b101): @+ HTEG_TABLE(b101); @+ break;
case TAG(table_kind,b110): @+ HTEG_TABLE(b110); @+ break;
case TAG(table_kind,b111): @+ HTEG_TABLE(b111); @+ break;@#

case TAG(item_kind,b000):  hteg_list_pointer(); @+ break;
case TAG(item_kind,b001):  hteg_content(); @+ break;
case TAG(item_kind,b010):  hteg_content(); @+ break;
case TAG(item_kind,b011):  hteg_content(); @+ break;
case TAG(item_kind,b100):  hteg_content(); @+ break;
case TAG(item_kind,b101):  hteg_content(); @+ break;
case TAG(item_kind,b110):  hteg_content(); @+ break;
case TAG(item_kind,b111):  hteg_content(); @+(void)HTEG8;@+ break;
@
\subsection{Insertions and Stream Content}
Hi\TeX\ generates streams from insertion nodes and here we need to reverse
this process. While \TeX\ assigns insertion numbers starting at 254 and counting
down, \HINT\ assigns stream numbers in the order of appearance starting at 1
and counting up. We partly reverse this process here by mapping the
stream number $n$ to the insertion number $255-n$.

We start with a function to set fields of the insertion node from a
parameter list. 

@<\HINT\ auxiliar functions@>=
static void hset_stream_params(pointer p, ParamDef *q)
{ pointer s;
  hset_param_list(q);
  float_cost(p)=integer_def[floating_penalty_no];
  depth(p)=dimen_def[split_max_depth_no];
  split_top_ptr(p)= pointer_def[glue_kind][split_top_skip_no];
  add_glue_ref(split_top_ptr(p));
  hrestore_param_list();
  s =vpack(ins_ptr(p),natural);
  height(p)=height(s)+depth(s);
  ins_ptr(p)=list_ptr(s);
  list_ptr(s)=null; flush_node_list(s);
}
@


@<GET macros@>=
#define @[HGET_STREAM(I)@] @/\
{ ParamDef *q;@+  pointer p;\
  p=get_node(ins_node_size); type(p)=ins_node;\
  subtype(p)=HGET8;@+RNG("Stream",subtype(p),1,254); \
  if ((I)&b010) q=hget_param_list_node(); else q=hget_param_list_ref(HGET8); \
  ins_ptr(p)=hget_list_pointer(); \
  hset_stream_params(p,q); \
  tail_append(p);}
@

@<TEG macros@>=
#define @[HTEG_STREAM(I)@] @/\
{pointer p=get_node(ins_node_size); type(p)=ins_node;\
 ins_ptr(p)=hteg_list_pointer();\
 if ((I)&b010) {ParamDef *q=hteg_param_list_node();  hset_stream_params(p,q);}\
 else {ParamDef *q=hget_param_list_ref(HTEG8);  hset_stream_params(p,q);}\
 subtype(p)=HTEG8;@+RNG("Stream",subtype(p),1,254);\
 tail_append(p);}
@

@<cases to get content@>=
case TAG(stream_kind,b000): HGET_STREAM(b000); @+ break;
case TAG(stream_kind,b010): HGET_STREAM(b010); @+ break;
@

@<cases to teg content@>=
case TAG(stream_kind,b000): HTEG_STREAM(b000); @+ break;
case TAG(stream_kind,b010): HTEG_STREAM(b010); @+ break;
@

\subsection{Images}
@<GET macros@>=
#define @[HGET_IMAGE(I)@] @/\
{@+pointer p; float32_t a=0.0; scaled w,h;\
p=get_node(image_node_size);  type(p)=whatsit_node; subtype(p)=image_node;\
HGET16(image_no(p));RNG("Section number",image_no(p),3,max_section_no);  \
if ((I)&b100) { a=hget_float32();\
  if ((I)==b111) {w=hget_xdimen_node();h=hget_xdimen_node();}\
  else if ((I)==b110) {h=hget_xdimen_ref(HGET8);w=hget_xdimen_node();}\
  else if ((I)==b101) {w=hget_xdimen_ref(HGET8);h=hget_xdimen_node();}\
  else  {w=hget_xdimen_ref(HGET8);h=hget_xdimen_ref(HGET8);}\
  if (a!=0.0) { if (h==0) h=round(w/a); else if (w==0) w=round(h*a);\
  else if (w>round(h*a)) w=round(h*a); else if (h>round(w/a)) h=round(w/a);}}\
else if((I)==b011) {HGET32(w);HGET32(h);} \
else if((I)==b010) { a=hget_float32(); HGET32(w); h=round(w/a);}\
else if((I)==b001){ a=hget_float32(); HGET32(h); w=round(h*a);}\
if (w==0 || h==0) QUIT("Incomplete dimensions in image %d",image_no(p));\
image_width(p)=w; image_height(p)=h;\
image_alt(p)=hget_list_pointer();\
tail_append(p);}
@

@<TEG macros@>=
#define @[HTEG_IMAGE(I)@] @/\
{ @+pointer p; float32_t a=0.0; scaled w,h;\
p=get_node(image_node_size);  type(p)=whatsit_node; subtype(p)=image_node;\
image_alt(p)=hteg_list_pointer();\
if ((I)&b100) {\
  if ((I)==b111) {h=hteg_xdimen_node();w=hteg_xdimen_node();}\
  else if ((I)==b110) {w=hteg_xdimen_node();h=hget_xdimen_ref(HTEG8);}\
  else if ((I)==b101) {h=hteg_xdimen_node();w=hget_xdimen_ref(HTEG8);}\
  else  {h=hget_xdimen_ref(HTEG8);w=hget_xdimen_ref(HTEG8);}\
  a=hteg_float32();\
  if (a!=0.0) { if (h==0) h=round(w/a); else if (w==0) w=round(h*a);\
  else if (w>round(h*a)) w=round(h*a); else if (h>round(w/a)) h=round(w/a); }}\
else if((I)==b011) {HTEG32(h);HTEG32(w);} \
else if((I)==b010) {  HTEG32(w); a=hteg_float32(); h=round(w/a);}\
else if((I)==b001){ HTEG32(h); a=hteg_float32();  w=round(h*a);}\
HTEG16(image_no(p));RNG("Section number",image_no(p),3,max_section_no);  \
if (w==0 || h==0) QUIT("Incomplete dimensions in image %d",image_no(p));\
image_width(p)=w; image_height(p)=h;\
tail_append(p);}
@

@<cases to get content@>=
case TAG(image_kind,b000): @+ hget_image_ref(HGET8); @+break;
case TAG(image_kind,b001): @+ HGET_IMAGE(b001);@+break;
case TAG(image_kind,b010): @+ HGET_IMAGE(b010);@+break;
case TAG(image_kind,b011): @+ HGET_IMAGE(b011);@+break;
case TAG(image_kind,b100): @+ HGET_IMAGE(b100);@+break;
case TAG(image_kind,b101): @+ HGET_IMAGE(b101);@+break;
case TAG(image_kind,b110): @+ HGET_IMAGE(b110);@+break;
case TAG(image_kind,b111): @+ HGET_IMAGE(b111);@+break;
@
@<cases to teg content@>=
case TAG(image_kind,b000): @+ hget_image_ref(HTEG8); @+break;
case TAG(image_kind,b001): @+ HTEG_IMAGE(b001);@+break;
case TAG(image_kind,b010): @+ HTEG_IMAGE(b010);@+break;
case TAG(image_kind,b011): @+ HTEG_IMAGE(b011);@+break;
case TAG(image_kind,b100): @+ HTEG_IMAGE(b100);@+break;
case TAG(image_kind,b101): @+ HTEG_IMAGE(b101);@+break;
case TAG(image_kind,b110): @+ HTEG_IMAGE(b110);@+break;
case TAG(image_kind,b111): @+ HTEG_IMAGE(b111);@+break;
@

\subsection{Links}
@<GET macros@>=
#define @[HGET_LINK(I)@] @/\
{ @+pointer p;\
  p=get_node(link_node_size);  type(p)=whatsit_node;\
  if (I&b010) subtype(p)=start_link_node; else subtype(p)=end_link_node;\
  if (I&b001) HGET16(label_ref(p));@+ else label_ref(p)=HGET8; \
  RNG("label",label_ref(p),0,max_ref[label_kind]);\
  label_has_name(p)=0;\
  tail_append(p);}
@

@<TEG macros@>=
#define @[HTEG_LINK(I)@] @/\
{ @+pointer p;\
  p=get_node(link_node_size);  type(p)=whatsit_node;\
  if (I&b010) subtype(p)=start_link_node; else subtype(p)=end_link_node;\
  if (I&b001) HTEG16(label_ref(p));@+ else label_ref(p)=HTEG8; \
  RNG("label",label_ref(p),0,max_ref[label_kind]);\
  label_has_name(p)=0;\
  tail_append(p);}
@

@<cases to get content@>=
case TAG(link_kind,b000): @+ HGET_LINK(b000); break;
case TAG(link_kind,b001): @+ HGET_LINK(b001); break;
case TAG(link_kind,b010): @+ HGET_LINK(b010); break;
case TAG(link_kind,b011): @+ HGET_LINK(b011); break;
@
@<cases to teg content@>=
case TAG(link_kind,b000): @+ HTEG_LINK(b000); break;
case TAG(link_kind,b001): @+ HTEG_LINK(b001); break;
case TAG(link_kind,b010): @+ HTEG_LINK(b010); break;
case TAG(link_kind,b011): @+ HTEG_LINK(b011); break;
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

It lists |extern| declarations of variables and functions that are extracted from \TeX.
This file is not extracted form \TeX's source code, but when 
it is included in the extracted code, the
compiler will check the decalarations against the implementation.
Further the file will include declarations of a few items that are not
implemented but rather needed by the \TeX\ library.

The additional include file {\tt format.h} 
is necessary because it provides a replacement for
\TeX's table of equivalents. 
\TeX's table of equivalents is no longer needed because \HINT\ does not define
new values.
The include file {\tt format.h} depends on {\tt error.h}
and provides the usual \HINT\ debugging output macros.  
The file {\tt error.h} defines macros to implement error handling.

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

\TeX's table of equivalents is no longer needed since \HINT\ will never change
any assignments. The functions of \TeX, however, use several of \TeX's variables
as parameters. These are now found as part of \HINT's definitions.
We modify the corresponding macros accordingly.

\changestyle{params.tex}

The variables containing the parameter definitions are declared |extern|.

@<\HINT\ |extern|@>=
extern pointer*pointer_def[32];
extern scaled*dimen_def;
extern int32_t*integer_def;
@


\subsection{Diagnostic Output}

\changestyle{hprint.tex}

\subsection{Arithmetic}

\changestyle{harith.tex}

\subsection{Memory}
\TeX's main data structure is the |mem| array. In this section, we will extract the
|mem| variable and the routines to allocate and deallocate nodes.
 
\changestyle{hmem.tex}

\subsection{Boxes and Friends}

In this section we will export the functions that create structures in |mem|: boxes, rules, ligatures and more such things.

\changestyle{hbox.tex}

\subsection{Lists and Nesting}
Most of \TeX's operations are performed on the ``current list''. 
When \HINT\ reads nodes from the input file, it will follow this principle and add nodes
to the current list. Lists can be nested and the list on the outermost level is the contribution list which we encounter again in section~\secref{texbuildpage}. 
Now lets consider the modifications to \TeX's list handling.
 
\changestyle{hlist.tex}

\subsection{Line Breaking}

\changestyle{hlinebreak.tex}

\subsection{Displayed Formulas}
\changestyle{hdisplay.tex}

\subsection{Packing Boxes}
\changestyle{hpack.tex}

\subsection{Page Building}\label{texbuildpage}

\changestyle{hbuildpage.tex}


Above, we have used several variables and functions
that are yet undefined. Here is a list of all of them
which we will put into a header file to force the compiler
to check for consistent use accross compilation units.

@<\HINT\ |extern|@>=
extern Stream *streams;
extern bool flush_pages(uint32_t pos); 
extern pointer skip(uint8_t n);
extern pointer *box_ptr(uint8_t n);
extern int count(uint8_t n);
extern scaled dimen(uint8_t n);
@

@<\HINT\ functions@>=
pointer skip(uint8_t n)
{ return cur_page->s[n].g; }
pointer *box_ptr(uint8_t n)
{ return &streams[n].p; }
int count(uint8_t n)
{ return cur_page->s[n].f; }
scaled dimen(uint8_t n)
{ return xdimen(&cur_page->s[n].x); }

@

After |build_page| returns |true|, the finished current page is in |streams[0].p|
and the location of it is in |page_loc[cur_loc]|.

Material that may flow to the next page is still on the contribution list.
The |hpos| pointer points to the position in the content section where
parsing should continue if further material is needed for the next page.

The function |hpage_init| flushes the current page from |streams[0].p|
and the insertions from the other streams.
It initializes the variables used by the page builder to make it ready to start 
a new page.
% do not set |prev_depth=ignore_depth; prev_graf=0;| otherwise baseline skips do not work properly

@<\HINT\ functions@>=
void hpage_init(void)
{ int i;
  if (streams==NULL||cur_page==NULL) return;
   for (i=0; i<=max_ref[stream_kind]; i++)
    if (streams[i].p!=null) 
    { flush_node_list(streams[i].p);
      streams[i].p=streams[i].t=null; 
    }
  page_contents=empty;page_tail=page_head;link(page_head)=null;@/
  hset_cur_page();
  hset_margins();
  page_depth=page_height=0;
  memset(top_so_far,0,sizeof(top_so_far));
  max_depth=cur_page->d;
  if (top_skip!=cur_page->g)
  { delete_glue_ref(top_skip);
    top_skip=cur_page->g;
    add_glue_ref(top_skip);
  }
}
@

@<\HINT\ |extern|@>=
extern void hpage_init(void);
@

When the viewer does not follow the natural sequence of pages but wants to
move to an arbitrary location in the \HINT\ file, the contribution list needs to be flushed. 
The rest is done by |hpage_init|.

@<\HINT\ functions@>=
void hflush_contribution_list(void)
{ if (link(contrib_head)!=null)
  { flush_node_list(link(contrib_head));
    link(contrib_head)=null; tail=contrib_head; 
  }
}
@

@<\HINT\ |extern|@>=
extern void hflush_contribution_list(void);
@

\subsection{Insertions}\label{texinsertions}
To handle insertions in the page building process we extract code from \TeX.

\changestyle{hinsert.tex}

\subsection{Font Metric Files}
In section~\secref{fonts} we mentioned the \TeX\ function  |read_font_info|. 
Now we see how to extract and modify this function from the \TeX\ sources.

\changestyle{hfont.tex}

\section{Building Pages Bottom Up}
\TeX's page builder (see section~\secref{texbuildpage}) moves nodes from the contribution list 
to the current page, filling it from top to bottom, and finds an optimal page break to end the page.
When a \HINT\ viewer needs to move to the previous page, only the start of the present page 
might be known. In this situation, the start of the present page determines the end of the
previous page and the \HINT\ page builder needs to find an optimal page break to start the previous page.

We have seen already, how parsing the \HINT\ file backwards will fill the contribution list,
moving the current position backwards, and adding new nodes at the end of the list.
Now we need to construct a page builder, that
moves these nodes from the head of the contribution list to the top of the current page,
building it from the bottom up until the optimal
page start is found. It is clear that optimizing different objectives will produce different
outcomes. So the pages \HINT\ finds in backward direction might be different from the ones
\TeX\ or \HINT\ find when paging forward. Therefore complete compatibility with \TeX\ is
not an issue. Still we want to do a good job and therefore the following exposition follows
closely the exposition of \TeX's page builder in part 45 of {\it \TeX: The Program\/}\cite{Knuth:tex}.

So here is the outline of the function |hbuild_page_up|. 

@<\HINT\ functions@>=
static bool hbuild_page_up(void) /*append contributions to the current page*/ 
{@+
static scaled page_top_height;
pointer p; /*the node being appended*/ 
pointer @!q,@!r; /*nodes being examined*/ 
int @!b, @!c; /*badness and cost of current page*/ 
int @!pi=0; /*penalty to be added to the badness*/ 
if (link(contrib_head)==null) return false;
@/do@+{ p=link(contrib_head);@/
@<Prepend node |p| to the current page; if it is time for a page break, fill the page template and return |true|@>;
}@+ while (link(contrib_head)!=null);@/
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
set asside in the variable |page_top_height|. When we add a box or rule, we keep the height
of it in the variable |page_height| and make sure it does not exceed |page_top_height|.
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

@<\HINT\ variables@>=
static scaled page_height;
static scaled top_so_far[8];
@

Now we consider how to prepend the different types of nodes.
We start with nodes that have height and depth.

\subsection{Boxes and Rules}

@<Prepend a box or rule node to the current page@>=
if (page_contents < box_there)
{ if (page_contents==empty) freeze_page_specs(box_there);
  else  page_contents=box_there;
  if(depth(p)> page_max_depth)
    page_total=depth(p)-page_max_depth;
  depth(p)=0;
  @<Account for the insertion of the \.{\\topskip} glue@>@;
}
@<Add in the |top_so_far|@>@;
page_total+= page_height+depth(p);
if (height(p)>page_top_height)
{ page_total=page_total+height(p)-page_top_height;
  page_height=page_top_height;
}
else
  page_height= height(p);
@

To fix page parameters before it is too late, \TeX\ uses the function |freeze_page_specs|.

The necessary topskip glue is determined when the final box is inserted
into the page. Until then its natural height is included in the |page_total|
and the height of the the topmost box or rule is included only as far as it exceeds
the topskip glue.

@<Account for the insertion of the \.{\\topskip} glue@>=
{ page_top_height=width(top_skip);
  page_total=page_total+page_top_height;
}
@

Glue that gets added to the top of the page is collected in the |top_so_far|
array.  This glue will be discarded if it is not topped by a box or rule.
In the latter case it is added to the |page_so_far| array.
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
case ins_node: happend_insertion(p); goto contribute;
default: DBG(DBGTEX,"Unexpected node type %d in build_page_up ignored\n",type(p));
} 
  @<Check if node |p| is a new champion breakpoint@>@;
contribute:
@<Prepend node |p| to the current page and |goto done|@>@;
done1: @<Recycle node |p|@>@;
done: 
@

@<Prepend node |p| to the current page and |goto done|@>=
link(contrib_head)=link(p);
link(p)=link(page_head);
if (link(page_head)==null) page_tail=p;
link(page_head)=p;
goto done;
@

@<Recycle node |p|@>=
link(contrib_head)=link(p);link(p)=null;flush_node_list(p);
@
\subsection{Glues and Kerns}

Page breaks are possible at a glue node, if the node just above the glue node is a
|hlist_node|, |vlist_node|,
|rule_node|, |ins_node|, |mark_node|, |adjust_node|, |ligature_node|,
|disc_node|, or |whatsit_node|. We test this with the |precedes_break| macro.
We silently return if the node above the glue is not yet known and
we do not test for a page break if the page is still empty.

@<Prepend a glue node to the current page@>=
if(link(p)==null) return false;
@<Add glue to |top_so_far|@>@;
if (page_contents==empty || !precedes_break(link(p))) goto contribute;
pi=0;
@

@<Add glue to |top_so_far|@>=
#define top_shrink top_so_far[6]
#define top_total top_so_far[1]

{ pointer q=glue_ptr(p);
  top_so_far[2+stretch_order(q)]+=stretch(q);
  if((shrink_order(q)!=normal)&&(shrink(q)!=0))
    DBG(DBGTEX,"Infinite glue shrinkage found on current page");
  top_shrink+=shrink(q);
  top_total+=width(q);
}
@

Handling kern nodes is similar. A kern node is a possible page break if the 
node below it is a glue node.

@<Prepend a kern node to the current page@>=
top_total+=width(p);
if (page_contents ==empty ||
    link(page_head)==null || 
    type(link(page_head))!=glue_node)
  goto contribute;
pi=0;
@

\subsection{Checking Breakpoints}
At this point |p| is a possible breakpoint and |pi| is the penalty associated with it.
First we compute |c|, the cost or badness of the current page.
The following code it taken from \TeX\ with only small modifications.

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
if (pi < inf_penalty) 
{@+@<Compute the cost |c| of a possible break at |p|@>@;
  if (c <= least_page_cost) 
  {@+best_page_break=p;best_size=page_goal;
    least_page_cost=c;
    r=link(page_ins_head);
    while (r!=page_ins_head) 
      {@+best_ins_ptr(r)=last_ins_ptr(r);
      r=link(r);
      }
  } 
  if ((c==awful_bad)||(pi <= eject_penalty)) 
  {@+
     @<Move nodes preceeding the best page break back to the contribution list@>@;
     @<Replace leading white-space by the topskip glue@>@;
     hpack_page();
     hfill_page_template();
     return true;
  } 
} 
@


We have finaly found the best page break. If the best break is not the current node |p|,
we might have moved some material
preceeding this break already to the current page. Now we move it back to
the contribution list. 


@<Move nodes preceeding the best page break back to the contribution list@>=
if (p!=best_page_break)
{ while (link(page_head)!=best_page_break)
  { q=link(page_head);
    link(page_head)=link(q);
    link(q)=null;
    link(q)=link(head);
    link(head)=q;
  }
}
@

The following code starts with recording the newly found top of the
page in the page location cache.  For a discussion of why this location
should or should not be recorded see section~\secref{locsetprev}.
After we are done, the best page runs from
|link(page_head)| to |page_tail| and we set |best_page_break| to |null|.

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
temp_ptr= new_spec(top_skip);
q= new_glue(temp_ptr);glue_ref_count(temp_ptr)= null;
if(width(temp_ptr)> page_height) width(temp_ptr)= width(temp_ptr)-page_height;
else width(temp_ptr)= 0;
link(q)=link(page_head);
link(page_head)=q;
best_page_break=null;
@

\section{Recording Locations}
When a \HINT\ viewer needs to output a certain page, it must be able to position
the parser in the content section of the \HINT\ file.
For example when we want to go backwards to the previous page, 
we must position the parser where the current page starts and go backwards from there.
The start of the current page was determined
by the page builder. It is usually a penalty or glue node less often 
also a kern node. So the page builder knows the node where the page break occurs
and we simply need a way to determine the position in the content section from the
node. We could of course store the position inside each node. But this would make 
all nodes bigger and since (in the current implementation)
\TeX's pointers are limited to 16 bit, this is not a good idea.
A second alternative would be to generate the pages directly from
the node representations in the \HINT\ file. This is ultimatively the best solution
but requires rewriting \TeX's algorithms to work with that new representation---and I
simply don't have the time to do that.
So I choose a third alternative: 
I implement a table to map node pointers to positions.
Unfortunately, the position alone is not sufficient. Page breaks
often occur in the middle of a paragraph, and for the line breaking
algorithm, the information stored in the paragraph node is essential.
Therefore the table will store also an offset to the enclosing top level node.
(A text node---not implemented yet---will possibly need the current font.)
We call the complete information associated with the position a ``location''
and the location is what we store in the table.

When implementing a \HINT\ viewer, it will become necessary to store
positions inside a \HINT\ file for later use. For example, a \HINT\ viewer
may want to open a \HINT\ file exactly at the position where the user has
stopped reading last time. We do not want to burden such programs with
all the details of a {\bf Location} type. Hence we commit ourself to code
locations in an |uint64_t| value and will make sure that these
values contain enough information to position the \HINT\ file to
a unique and reproducible position.
The |uint64_t| type is an opaque type for the user interface,
but by storing the 32 bit position
inside the content section in the most significant bits, the user interface can compare
the 64 bit integers to find out if a location preceeds an other location. 

\subsection{Mapping node pointers to locations}
Since \TeX's pointers are only 16-bit integers the most simple
implementation of the location table is an array indexed by the
pointer values. Since we do not need locations for character nodes
and all other nodes have two or more memory words, we can use not only
the table entry at the pointer value |p| but also the table entry at $|p|+1$.
We use the first for the node position and the second for a node's offset
from the enclosing  paragraph node 
or other top level node that is split across pages.

@<\HINT\ variables@>=
static uint32_t map[0x10000];
@

The first function is the initialization function that clears the table. It 
sets all records to zero. 

@<\HINT\ functions@>=
static void clear_map(void)
{ @+memset(map,0,sizeof(map));@+
}
@

Next, we implement two
functions that operate on the table:
|store_map| stores or updates information inside the table,
and |hposition| returns for a given pointer the position inside the 
content section, or zero if no such position is known.
To delete an entry, simply call |store_map(p,0,0)|.

@<\HINT\ functions@>=
void store_map(pointer p, uint32_t pos0, uint32_t offset)
{@+ map[p]=pos0;
  map[p+1]=offset;@+
}

uint32_t hposition(pointer p) 
{@+ return map[p];@+
}
@  

The function that takes information form the cache and converts it to a |uint64_t| location, as mentioned above, commes next. It returns |HINT_NO_LOC| if no information is in the cache.
This value is used to indicate that a variable contains no valid location.

@<\HINT\ |extern|@>=
#define HINT_NO_LOC 0xFFFFFFFFFFFFFFFF
#define PAGE_LOC(POS0,OFF) (((uint64_t)((POS0)+(OFF))<<32) + (uint64_t)(OFF))
#define LOC_POS(P) ((P)>>32) /* the node position */
#define LOC_OFF(P) ((P)&0xFFFFFFFF) /* the distance to the top level node */
#define LOC_POS0(P) (LOC_POS(P)-LOC_OFF(P)) /* the top level position */
@

@<\HINT\ auxiliar functions@>=

uint64_t hlocation(pointer p)
{ @+return PAGE_LOC(map[p],map[p+1]);@+
}
@  

\subsection{Caching page locations}
The location table is complemented by a cache for page locations.
When we move trough a \HINT\ file by paging forward and then want to
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

@<\HINT\ variables@>=
#define MAX_PAGE_POS (1<<3) /* must be a power of 2 */

uint64_t page_loc[MAX_PAGE_POS];
int cur_loc;
static int lo_loc, hi_loc;
@
@<\HINT\ |extern|@>=
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

@<\HINT\ auxiliar functions@>=
#define @[NEXT_PAGE(X)@] (X=(X+1)&(MAX_PAGE_POS-1))
#define @[PREV_PAGE(X)@] (X=(X-1)&(MAX_PAGE_POS-1))
@#
void hloc_clear(void)
{ @+lo_loc=hi_loc=cur_loc;PREV_PAGE(lo_loc);NEXT_PAGE(hi_loc);@+
}

bool hloc_next(void)
{ @+int i=cur_loc;
  if (LOC_POS(page_loc[cur_loc])>=hend-hstart) 
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
@<\HINT\ |extern|@>=
extern void hloc_clear(void); /* keep only |cur_loc| in the cache */
extern bool hloc_next(void);  /* advance to the next page if possible */
extern bool hloc_prev(void);  /* advance to the previous page if possible */
extern uint64_t hlocation(pointer p); /* map |p| to its file location */
@

After these preparations, we can turn our attention to the functions that manage
the page cache itself. We start with the initialization function:

@<\HINT\ functions@>=
void hloc_init(void)
{@+cur_loc=0;
  hloc_clear();
  page_loc[cur_loc]=0;
  DBG(DBGPAGE,"loc_init: %d < %d < %d\n",lo_loc,cur_loc,hi_loc);
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
If the location of the current page is new, we do not know anything about the position
of following or preceeding pages and we have to clear the cache. 

@<\HINT\ auxiliar functions@>=

void hloc_set(uint64_t h)
{@+ int i;
  if (page_loc[cur_loc]==h) return;
  for (i=lo_loc,NEXT_PAGE(i); i!=hi_loc; NEXT_PAGE(i))
   if (page_loc[i]==h)
   { cur_loc=i;
     DBG(DBGPAGE,"loc_set: %d < %d < %d\n",lo_loc,cur_loc,hi_loc); 
     return;}
  page_loc[cur_loc]=h;
  hloc_clear();
  DBG(DBGPAGE,"loc_set: %d < %d < %d\n",lo_loc,cur_loc,hi_loc);
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
 
 
 @<\HINT\ auxiliar functions@>=

void hloc_set_next(pointer p)
{ @+int i=cur_loc;
  uint64_t h=hlocation(p); 
  if (h==page_loc[cur_loc]) return;

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
  DBG(DBGPAGE,"loc_set_next: %d < %d < %d\n",lo_loc,cur_loc,hi_loc);
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

@<\HINT\ auxiliar functions@>=
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
  DBG(DBGPAGE,"loc_set_prev: %d < %d < %d\n",lo_loc,cur_loc,hi_loc);
}
@

The following functions are called from the \TeX\ code:

@<\HINT\ |extern|@>=
extern void hloc_init(void);
extern void store_map(pointer p, uint32_t pos, uint32_t offset); /*store the location of |p|*/
extern uint32_t hposition(pointer p); /* return the position of |p| or 0*/
extern void hloc_set(uint64_t h);
extern void hloc_set_next(pointer p);/* record the location of |p| as the start of the next page */
@

\section{The Top-Level Interface}
The \HINT\ library seeks to provide a basis for the implementation of
\HINT\ viewers. For this purpose, it presents a top-level functional
interface which strives to be easy to use and yet exposes the
necessary functionality to allow different viewers on different
systems.

\subsection{Opening and Closing a \HINT\ File}
The first function an application needs to call is |hint_begin| and
the last function is |hint_end|.  The former initialized \TeX's
memory, maps the file, and prepares the system to be ready for all the
functions that follow; the latter will release all resources obtained
when calling one of the top level \HINT\ functions returning the
system to the state it had before calling |hint_begin|.  Since mapping
(and unmapping) the \HINT\ file to memory is system depended, the
functions |hint_begin| and |hint_end| delegate the work to two
functions, |hint_map| and |hint_unmap|, that must be implemented by
the framework using the \HINT\ backend.  If mapping the file fails,
the function |hint_map| should set |hin_addr| to |NULL| and return zero;
otherwise, it should set |hin_addr| to a valid memory address and return the number 
of byte mapped. 
The value of |hin_addr| can therefore be used to check whether a \HINT\ file is loaded.
|hint_begin| will return |1| if successful and |0| otherwise.
@<\HINT\ functions@>=
int hint_begin(void)
{ if (!hint_map()) return 0;
  hpos=hstart=hin_addr;
  hend=hstart+hin_size;
  hint_clear_fonts(true);
  hflush_contribution_list(); hpage_init();
  flush_node_list(link(page_head));
  free_definitions();
  mem_init();
  list_init(); 
  hclear_dir();
  hclear_fonts();@/
  hget_banner();@/
  if (!hcheck_banner("hint"))
  { hint_unmap(); return 0; }
  hget_directory();
  hget_definition_section();
  hvsize=dimen_def[vsize_dimen_no];
  hhsize=dimen_def[hsize_dimen_no];
  hget_content_section();
  leak_clear();
  clear_map();
  hloc_init();
  return 1;
}

void hint_end(void)
{ @+if (hin_addr==NULL) return;
  hint_unmap(); 
  hin_addr=hpos=hstart=hend=NULL;
  hflush_contribution_list(); hpage_init();
  flush_node_list(link(page_head));
  free_definitions();
  list_leaks();
  hclear_dir();
}
@


@<\HINT\ |extern|@>=
extern int hint_begin(void);
extern void hint_end(void);
extern bool hint_map(void);
extern void hint_unmap(void);
@


\subsection{Changing the Page Dimensions}
A central feature of a \HINT\ viewer is its ability to change the dimensions and the
resolution of the displayed pages. To do so the function |hint_resize| is called.
Using this function, the caller informs the rendering engine about the
physical properties of the display aerea, its size in pixels and its resolution in
dots per inch.
Here is an example: Suppose the screen area is 300 pixel wide and 400 pixel high,
and the resolution is 100 dpi in both directions (the screen has ``square'' pixels).
Then the rendering engine can assume that the display aerea is 3 inches wide and
4 inches high, and can render a 10pt font at exactly 10pt by computing the
size of a single pixel as $1/100\,$inch or $0.7227\,$pt.
If the user now wants the size scaled by a factor of 2, to make the small print of a contract
easier to read (not that it would make the contract any better), 
it is sufficient to set the resolution to 200 dpi.  The renderer would then
compute the size of a single pixel to be only $1/200$ of an inch and conclude that
the display aerea is only half as wide and half as high as it actually is.
In summary: As far as the renderer is concerned, the rendering on an 3 by 4 inch display at 100dpi
and a scale factor of 2 is equivalent to a rendering on a 1.5 by 2 inch display at 200dpi
and a scale factor 1. In both cases, the renderer will produce a 300 by 400 pixel bitmap
which would either fill the larger aerea at 100dpi or the smaler one at 200dpi.

@<render variables@>=
double xdpi=600.0, ydpi=600.0;
@

@<render functions@>=
void hint_resize(int px_h, int px_v, double x_dpi, double y_dpi)
{ 
#if 0
  /* this optimization causes the android viewer to display a blank page
     after opening a new file. To be investigated!
  */
  static int old_px_h=0, old_px_v=0;
  static double old_xdpi=0.0, old_ydpi=0.0;
   if (old_px_h==px_h && old_px_v==px_v && old_xdpi==x_dpi && old_ydpi==y_dpi)
    return;
  old_px_h=px_h; old_px_v=px_v; old_xdpi=x_dpi; old_ydpi=y_dpi;
#endif
  xdpi=x_dpi; ydpi=y_dpi;
  nativeSetSize(px_h, px_v, xdpi, ydpi);
  hloc_clear();
  hflush_contribution_list(); hpage_init();
  forward_mode=false;
  backward_mode=false;
}
@


The function tells the native renderer about the change, clears all locations
from the location cache, removes nodes from the contribution list,
and resets the rendering direction.


\subsection{Building Pages Forward and Backward}
After opening the \HINT\ file, \HINT\ viewers need a to be able to move forward to
the next page. Here is the function to do that.

@<\HINT\ functions@>=
bool hint_forward(void)
{@+ hpage_init();
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
This function attempts to produce a page in forward mode. If successful it returns |true|
and the caller can set the |forward_mode| variable to |true| to indicate that the current page
was produced in forward mode. If unsuccessfull, it returns false.
First the function |hpage_init| returns the ``old'' current page to
free storage and initializes the variables that control the page building process.
It is then assumed that any material still on the contribution list should fill the
new page top to bottom. The call to |hbuild_page| will move any such material 
to the new page. Further material is then taken from the \HINT\ file with parsing starting 
at |hpos| which should point to a top level node.
If the end-of-file is reached before the (nonempty) page is completed, a call to |flush_pages|
adds some glue and a penalty to eject the page.

The page builder usually considers material from the \HINT\ file until the page
becomes overfull before it backs up to the position of the best page break.
The extra material past this break is put back on the contribution list
in preparation for the next page. The |hpos| pointer to the \HINT\ file will then
point to the position where parsing should continue.
Last not least, the page builder will store the location of the page break
in the location cache as starting point for the next page.

To summarize: If the variable |forward_mode| is |true|, the |hint_forward| function
can be called to produce the next page reusing all the work already done while
producing the current page. After the call, we will have at least two enties in the location cache:
the top of the current page and the top of the next page.



Similarly, we implement paging backward.
 @<\HINT\ functions@>=
bool hint_backward(void)
{@+ hpage_init();
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
Here it is assumed that the material in the contribution list
belongs to the bottom of the preceeding page and |hpos| will
indicate where parsing should contine when producing the previous page.
 After the call, we will have at least two enties in the location cache:
the top of the current page and the top of the next page.
@<\HINT\ |extern|@>=
extern bool hint_forward(void);
extern bool hint_backward(void);
@

When the page builder has reached the end of the \HINT\ file, it must make sure that
the material that still is in the contribution list gets flushed out.
To do so the function |flush_pages| adds some space and a large negative penalty.
Calling one of the previous functions will then deliver the remaining pages.

@<\HINT\ functions@>=
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

@<\HINT\ variables@>=
scaled hvsize, hhsize;
@
@<\HINT\ |extern|@>=
extern scaled hvsize, hhsize;
@
The variables |hvsize| and |hhsize| give the vertical and horizontal
size of the main body of text. They are determined by subtracting the
margins from |page_v| and |page_h| as determined by the GUI.

The five functions defined so far constitute a minimal basis for
processing \HINT\ files.  Section~\secref{testing} presents two
programs, used to test the \HINT\ engine, which are implemented with
just these functions.

\subsection{Page Composition}
The page builder of \HINT, to tell the truth, is not building the
page, it is just assembling the material that should be displayed on
the page: the main body of text and floating material like footnotes
or illustrations.  To make a nice looking page, we need to combine the
material properly and put margins around all that.

The next function computes the margins.
Given the horizontal and vertical dimensions of the page as |page_h|
and |page_v|, it computes the horizontal and vertical dimensions of
the main body of text as well as the offset of its top/left
position. The dimensions are given in scaled points.

@<\HINT\ variables@>=
int page_v, page_h, offset_v, offset_h;
@

If no page template is defined, a default algorithm is used.
The formula use here will result in a 1 inch margin for a 
letter size page---that's the old default of plain \TeX---and decreases the magins for smaller pages
until the margin becomes zero for a page that is merely 1 inch wide.


@<\HINT\ auxiliar functions@>=
 static void hset_margins(void)
{  if (cur_page==&(page_def[0])) {
   offset_h=page_h/8- 0x48000;
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
   else
   { hhsize=round((double)(page_h-cur_page->h.w)/(double)cur_page->h.h);
     if (hhsize>page_h) hhsize=page_h;
     hvsize=round((double)(page_v-cur_page->v.w)/(double)cur_page->v.v);
     if (hvsize>page_v) hvsize=page_v;
     offset_h = (page_h-hhsize)/2;
     offset_v = (page_v-hvsize)/2;
   }
}
@



@
A more sophisticated page composition can be achived with page
templates.  Here is the build-in page template number 0 which attaches
the margins just computed to the box constructed by the page builder.

@<\HINT\ auxiliar functions@>=
static void houtput_template(pointer p)
{ pointer q,r;
 if (p==null) return;
  p=vpackage(p,hvsize,exactly,page_max_depth);
  if (offset_v!=0)
  { r=new_kern(offset_v);
    link(r)=p;
  }
  else
    r=p;
  q=new_null_box();
  type(q)=vlist_node;
  width(q)=width(p)+offset_h;
  height(q)=height(p)+offset_v; depth(q)=depth(p);
  list_ptr(q)=r;
  shift_amount(p)+=offset_h;
  streams[0].p= q;  
 }
@

\subsection{Moving around in the \HINT\ file}
The basic capability of \HINT\ is producing a page that starts at a given position in the
\HINT\ file. The function |hint_page_top| provides this capability.
If successful, it stores a pointer to the page it created in the variable |streams[0].p|.
As long as this pointer is not |null| it can be used to render the page or search
the page for content.

After a few checks, |hint_page_top| starts by clearing the contributions list 
from all traces left from building previous pages and computes |hhsize| and |hvsize|.
Then it parses a partial paragraph---if necessary---and calls |hint_forward| to build the page.

As all functions in this section, it returns the location of the new current page.
The viewer might store this location to be able to return to this page at a later time.

@<render functions@>=

uint64_t hint_page_top(uint64_t h)
{ if (hin_addr==NULL) return 0;
  hpos=hstart+LOC_POS0(h);
  if (hpos>=hend)
    return hint_page_bottom(hend-hstart);
  hflush_contribution_list();
  hloc_set(h);
  if (LOC_OFF(h))
    hget_par_node(LOC_OFF(h));
  hint_forward();
#if 0
  show_box(streams[0].p);
#endif
  forward_mode=true;
  backward_mode=false;
  return h;
}
@

If the viewer needs the position of the current page at a later time, it can
call |hint_page_get|.
@<render functions@>=
uint64_t hint_page_get(void)
{@+
 DBG(DBGPAGE,"page_get: %d : 0x%" PRIx64 "\n",cur_loc,page_loc[cur_loc]);
@/
if (hin_addr==NULL) return 0;
return page_loc[cur_loc];
 }
@


Using the previous functions, we implement |hint_page| which rerenders the current page.
If |streams[0].p!=null| a valid current page still exists and nothing needs to be done.
If |streams[0].p==null|, we obtain the current pages top position using |hint_page_get|
and pass the position to |hint_page_top|.

@<render functions@>=
uint64_t hint_page(void)
{ uint64_t i;
  if (streams==NULL) return 0;
  i = hint_page_get();
  if (streams[0].p!=null)
    return i;
  else
    return hint_page_top(i);
}
@
To display the first page simply call |hint_page_top(0)|.
An other page that a user may want to see is the document's ``home'' page.
Its position is stored in the zero label. It can be displayed by
calling |hint_page_home|.

@<render functions@>=
uint64_t hint_page_home(void)
{@+ uint64_t pos;
  uint8_t where;
  int n=zero_label_no;
  if (hin_addr==NULL) return 0;
  @<get |where| and |pos| from label |n|@>@;
  @<render the page at |pos| using |where| and return@>@; 
}
@

If a viewer caches file positions from one invocation to the next, which
is a convenient feature, it runs the risk that the file contents might
have changed in the meantime and the position is no longer valid.
This is especialy likely if the hint viewer is used for viewing a file
while editing its source. For these cases, a more robust approach is needed.
The functions |hint_get_fpos| and |hint_set_fpos| are provided for this
purpose. The first one returns a floating point number in the range $0.0$
to $1.0$ where $0.0$ corresponds to the first byte and $1.0$ to the last
byte in the content section. The second function accepts such a floating point number,
finds the closest position in the content section that can be used as
the top of a page, renders the page, and returns the position.
If between a call to |hint_get_fpos| and |hint_set_fpos| the file does not
change or changes only slightly, the displayed page should not change
or change only slightly. If the file changes significantly, of course,
also the displayed page might be completely different.

The simple part is |hint_get_fpos|.
@<render functions@>=
double hint_get_fpos(void)
{@+
 DBG(DBGPAGE,"get_fpos: %d : 0x%" PRIx64 "\n",cur_loc,page_loc[cur_loc]);
@/
if (hin_addr==NULL) return 0.0;
return (double)LOC_POS(page_loc[cur_loc])@|/(double)(hend-hstart);
 }
@

To implement |hint_set_fpos| we use |hff_pos| to ``fast forward''
to the desired position. If this position is inside a paragraph,
we compute the closest offset that is a possible line break.

@<render functions@>=
uint64_t hint_set_fpos(double fpos)
{@+uint32_t pos, pos0;
 uint8_t *p,*q;
 DBG(DBGPAGE,"set_fpos: %f\n",fpos);@/
 if (hin_addr==NULL) return 0;
 if (fpos<0.0) fpos=0.0;
 if (fpos>1.0) fpos=1.0;
 pos = round((hend-hstart)*fpos);
 p=hstart+pos;
 q=hpos=hstart;
 while (hpos<p)
 {@+ q=hpos; hff_hpos();@+ }
 if (hpos>p)
 { pos=pos0=q-hstart;
   if (KIND(*q)==par_kind && KIND(hff_tag)==list_kind && hff_list_size>0)
   { if (p>=hstart+hff_list_pos+hff_list_size)
        pos=pos0=hpos-hstart; /* first position after the par node */
     else
     { q=hpos=hstart+hff_list_pos;
       while (hpos<=p)
       { if (KIND(*hpos)==glue_kind ||@| KIND(*hpos)==penalty_kind ||@| KIND(*hpos)==disc_kind)
           q=hpos;
         hff_hpos();
       }
       pos=q-hstart;
     }
   }
 }
 else
   pos=pos0=hpos-hstart;
 return hint_page_top(PAGE_LOC(pos0,pos-pos0));
 }
@

Now let's consider moving to the next page. 
If we produced the current page using |hint_forward|, we can simply call
|hint_forward| again. For this reason, we use the variables  |forward_mode| and |backward_mode|
to keep track of the direction used to render the current page.
@<render variables@>=
static bool forward_mode=false, backward_mode=false;
@
If simply moving forward does not work---we might not know the position of the next page,
or are not in forward mode, or we might be at the end of the file---we just rerender the current page.
@<render functions@>=
uint64_t hint_page_next(void)
{ if (hin_addr==NULL) return 0;
  if (hloc_next()&& forward_mode)
  { if (!hint_forward())
	{ hloc_prev(); return hint_page(); }	
    forward_mode=true;
    backward_mode=false;
    return hint_page_get();
  }
  else
  { hflush_contribution_list(); hpage_init();
    return hint_page();
  }
}
@

Things are a bit more complex for paging backwards. The page that we produce here is usually
different from what \HINT\ will produce in forward mode.
First we check the location cache. If there is an entry for the preceeding page,
we will take the location and produce the page in forward mode, because this way the
reader can get the same page as seen before. If we do not have a cached page location,
we build the page based on its bottom position.
If we are lucky, we are in backward mode. In this case, we do not need to
throw away the information in the contribution list and we call |hint_backward|.
@<render functions@>=
uint64_t hint_page_prev(void)
{ if (hin_addr==NULL) return 0;
  if (hloc_prev())
  { hflush_contribution_list(); hpage_init();
    return hint_page();
  }
  else if (backward_mode)
  { if (!hint_backward())  return hint_page_top(0);
    backward_mode=true;
    forward_mode=false;
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
If successfull, it will set |cur_loc| to the current page.
Finally, we attach the margins, render the page,
and return the new location.
@<render functions@>=
uint64_t  hint_page_bottom(uint64_t h)
{ if (hin_addr==NULL) return 0;
  hloc_set(h);
  hflush_contribution_list(); 
  hpos=hstart+LOC_POS0(h);
  if (LOC_OFF(h))
    hteg_par_node(LOC_OFF(h));
  if (!hint_backward())  return hint_page();
  backward_mode=true;
  forward_mode=false;
  return hint_page_get();
}
@

A function to build a page centered around a given position completes
the set of page building functions.
If the given position points to a top level node, this node is a
candidate for the beginning of the new page.
If the position is inside a toplevel paragraph, we process the whole
paragraph and put it line by line on the contribution list. One of the
nodes on the contribution list will then contain the given
position. This node, called the target node, must be shown on the
page.
If the whole paragraph fits on the page, one possibility is to start
the page with the paragraph but we may improve the page
by adding material to the top of the page.
More complications arrise if that is not the case.  
Once the ``best'' starting point of the page is found, the
page is rendered in forward mode.

@<render functions@>=
uint64_t  hint_page_middle(uint64_t l)
{ uint32_t target_pos, pos0, offset;
  pointer p;
  scaled h=0,d=0, hp, dp, target_dist=0, break_dist=0;
  int pi=0;
  if (hin_addr==NULL) return 0;
  target_pos=LOC_POS(l);
  offset=LOC_OFF(l);
  pos0=LOC_POS0(l);
  if (hstart+pos0+offset>=hend)
    return hint_page_bottom(hend-hstart);
  hflush_contribution_list();
  hpos=hstart+pos0;
  hget_content();

  if (offset>0)
    @<if the page must start inside the paragraph, modify the contribution list and go to |found|@>@;
  @<try to improve the page break by adding material to the top of the page@>@;
found:
  hloc_set(PAGE_LOC(pos0,offset)); 
  if (!hint_forward()) return hint_page_top(0);
  forward_mode=true;
  backward_mode=false;
  return hint_page_get();
}
@

To determine if the page must start inside the paragraph, we determine
the natural distance |target_dist| from the top of the paragraph to
the bottom of node |target_q|, the node that links to the target node.
Then we determine the distance |break_dist| from this point down to
the first feasible page break.  If
|target_dist|+|break_dist| is smaller than the page height, the
beginning of the paragraph is a good page break. Otherwise if
|break_dist| is smaller than the page height, we remove nodes from the
contribution list until the remaining nodes will fit on the page.  We
then try to improve the page break by removing more nodes until the
target node is close to the middle of the page. If all fails, we start
the page with the target node.

@<if the page must start inside the paragraph, 
  modify the contribution list and go to |found|@>=
{ pointer q, target_q;
  @<determine |target_q|, |target_dist|, and |break_dist|@>@;
  if (target_dist+break_dist<=hvsize)
    offset=0;
  else
  { if (break_dist>=hvsize)
       q=target_q;
    else
      @<set |q| to the last line that must be removed from the 
        contribution list to make the target fit nicely on the page@>@;
    @<remove all nodes up to |q| from the contribution list@>@;
    goto found;
  }
}
@

@<determine |target_q|, |target_dist|, and |break_dist|@>=
  target_q=null;
  q=contrib_head; p=link(q);
  h=d=target_dist=break_dist=0;  
  while (p!=null)
  { pointer qq;
    @<compute height, depth, and penalty of |p|@>@;
    qq=q;
    q=p;
    p=link(p);
    if (target_q!=null)
    { if (pi<=0)
        break;
    }
    else if (p==null || LOC_POS(hlocation(p))>target_pos)
    { target_q=qq;
      target_dist=h+d;
      h=d=0;
    }
    h += d+hp;
    d=dp;
  }
  if (target_q==null)
  {  target_dist=h; break_dist=0; }
  else
    break_dist=h;
@


 @<remove all nodes up to |q| from the contribution list@>=
 { p=link(q);
   offset=LOC_OFF(hlocation(p));
   link(q)=null;
   flush_node_list(link(contrib_head));
   link(contrib_head)=p;
 }
@


When traversing the contribution list, either in upward or downward direction,
we are inserted in the height, the depth, and the penalties of the contributions.
The following code extracts these for the the contribution |p| in to |ph|, |pd|, and |pi|.
A positive value for |pi| indicates an unwanted page break.

@<compute height, depth, and penalty of |p|@>=
 switch (type(p))
    { case hlist_node: case vlist_node: case rule_node:
        hp=height(p); dp=depth(p);
        pi=inf_penalty;
        break;
      case glue_node:
        hp=width(glue_ptr(p)); dp=0; 
        pi=0;
        break;
      case kern_node:
        hp=width(p); dp=0;
        pi=inf_penalty;
        break;
      case penalty_node:
       hp=dp=0;
       pi=penalty(p);
       break;
      default:
       pi=hp=dp=0;
    }
@

Next we consider the case that |break_dist| is smaller than the page size. So there
is a feasible end of page after the target node.
While |target_dist|+|break_dist| is greater than the page size, we remove lines from the beginning of
the paragraph until |target_dist| gets as close to half the page size as possible.

@<set |q| to the last line that must be removed from the contribution 
  list to make the target fit nicely on the page@>=
{ scaled dh;
  dh=target_dist + break_dist -hvsize;
  if (target_dist-dh > hvsize/2) 
    dh = target_dist-hvsize/2;
  q=contrib_head;
  p = link(q);
  d = 0;
  while (p!=null && q!=target_q && dh>0)
 { @<compute height, depth, and penalty of |p|@>@;
   dh= dh-hp-d;
   d=dp;
   q=p;
   p=link(p);
 }
}
@


Sometimes the target is in a small paragraph just below a section heading or another
good point to start a page. In these situations, the page can be improved by adding
material above the target.

@<try to improve the page break by adding material to the top of the page@>=
{ pointer h_save=link(contrib_head);
  pointer t_save=tail;
  uint8_t *hpos_save=hpos;
  pointer best_p=null;
  int best_pi=0;
  link(contrib_head)=null; tail=contrib_head;
  hpos=hstart+pos0;
  h=target_dist+break_dist;
  d=0;
  p=tail;
  while (h<hvsize)
  { while (link(p)==null && hpos>hstart)
      hteg_content();
    if (link(p)==null) break;
    p=link(p);
    @<compute height, depth, and penalty of |p|@>@;
    if (hpos==hstart) pi=eject_penalty;
    if (h+hp+d> hvsize) 
      break;
    h = h+d+hp; d=dp;
    if (pi< best_pi)
    { best_pi=pi;
      best_p=p;
      if (best_pi<=eject_penalty) break;
    }
  }
  if (best_p==null)
  { flush_node_list(link(contrib_head));
    hpos=hstart+pos0;
    offset=0;
  }
  else
  { p=link(contrib_head);
    do { pointer q;
      q=link(p);
      link(p)=h_save;
      h_save=p;
      p=q;
    } while (h_save!=best_p);
    flush_node_list(p);
    pos0=LOC_POS0(hlocation(best_p));
    offset=0;
  }
  link(contrib_head)=h_save;
  if (t_save!=contrib_head)
    tail=t_save;
  hpos=hpos_save;
}    
@



\subsection{Outlines}\label{outlines}
A \HINT\ file may contain two types of links: internal links and outlines.
We look at outlines first and deal with internal links after we have seen outlines
and searching in section~\secref{search}.
Outlines are made available to the user interface 
which can display them for example
in a menu from which the user can select them to move to the desired location.

The first question the user interface will ask is: Are there any outline items
and if yes, how many? Outline items are numbered from 0 to |max_outline| and
the following function will answer the question:

@<\HINT\ functions@>=
int hint_get_outline_max(void)
{@+ return max_outline;@+}
@
If it returns a negative value, there are no outline links;
if it returns $n\ge 0$,
there are $n+1$ outline links numbered $0$ to $n$.

For the communication with the user interface, 
a simple data type is used for outlines.
It contains the information relevant to the 
user interface.

@<\HINT\ |extern|@>=
typedef struct { 
uint64_t pos;  
uint8_t depth; 
uint8_t where; 
int p; /* pointer to the list of title nodes */
char *title; /* title as sequence of utf8 character codes */
} hint_Outline;
extern hint_Outline *hint_outlines;
@

The |pos| field contains a ``position'' in the hint file 
(like the ones returned from and passed to functions like |hint_page_top|). 
The user interface can use it to
navigate to the desired position in the \HINT\ file.
The |where| field indicates where the
label should be placed on the page.
The values are:
@<\HINT\ |extern|@>=
#define LABEL_UNDEF 0
#define LABEL_TOP 1
#define LABEL_BOT 2
#define LABEL_MID 3
@

The user interface should pass the position to
|hint_page_top|, |hint_page_bottom|, or |hint_page_middle| to obtain
the desired page.
As a shortcut, it can call this function:
@<render functions@>=
 uint64_t hint_outline_page(int i)
{@+ uint64_t pos;
  uint8_t where;
  if (i<0||i>max_outline|| hint_outlines==NULL) return  hint_page_get();
  pos=hint_outlines[i].pos;
  where=hint_outlines[i].where;
  @<render the page at |pos| using |where| and return@>@; 
}
@

@<render the page at |pos| using |where| and return@>=
  if (where==LABEL_TOP) return hint_page_top(pos);
  else if (where==LABEL_BOT) return hint_page_bottom(pos);
  else if (where==LABEL_MID)  return hint_page_middle(pos);
  else return  hint_page_get();
@

The remainder of the record is used to organize and identify the outline links.
The |depth| is there so that the user interface
can organize the outline links in form of a tree. 
So the user interface may indent them or put them in
a sub menu.

Most importantly, an outline link has a title. The titel, for example
``Introduction'' or ``Chapter 1'', will tell the user what
to expect when moving to the place that carries this label.
In general, the title is a horizontal list of nodes.
The pointer to this list is stored in the |p| field.
The renderer can use this pointer to render the label.
If the user interface decides to use GUI components provided by
the host window manager, a representation of the title
as a utf-8 string might be more appropriate. The conversion
of node lists to utf-8 strings is explained in the next section. 

The user interface can call the following function to obtain
information about the outline links:

@<\HINT\ functions@>=
hint_Outline *hint_get_outlines(void)
{@+ return hint_outlines;
}
@
The function
returns a pointer to an array of type |hint_Outline[]|, that can be indexed
from 0 to |max_outline|.

Here is a summary of the above functions:
@<\HINT\ |extern|@>=
extern int hint_get_outline_max(void);
extern hint_Outline *hint_get_outlines(void);
extern uint64_t hint_outline_page(int i);
@


\subsection{Traversing node lists}\label{listtraversal}
The creation of a titel string for outlines and the implementation
of searching for a string within a page (see section~\secref{search})
both require traversing \TeX's node lists, ignoring all the typesetting 
stuff, just returning a stream of character codes.

The traversal is started with either one of two mutually
recursive functions: |trv_vlist| or |trv_hlist|.
Two state variables controll the traversal: |trv_ignore| and |trv_skip_space|.

|trv_ignore| will be true between two ignore nodes.
Ignore nodes are generated when words are hyphenated.
During hyphenation, the |replace_count| tells how many nodes
are to be ignored. These nodes are now moved to
the |ignore_list| of the ignore node. 
The content now contained in the |ignore_list|
is then replaced by the |pre_break| list, a line ending, and the
|post_break| list. In many cases, the |ignore_list| and
the |post_break| list are empty
and the |pre_break| list contains just a hyphen character.
In difficult cases, like ``\hbox{dif- ficult}'',
the ligature ``ffi'' is in the |ignore_list|, the |pre_break|
list contains ``f-'' and the |post_break| list contains
the ligature ``fi''.

|trv_skip_space| will be true immediately after observing
a ``space''  in the stream of characters until a non space will arrive,
thus reducing multiple spaces to a single space.
Spaces need some
extra care because on the page, glue nodes and line endings
play the role of spaces in addition to explicit space
characters for example when printing out \CEE/ strings
like |"Hello world"|.
Glues in horizontal lists, but not kerns, are considered spaces;
further the end of a horizontal list inside a vertical list is
considered a space; and characters with character code |0x20|
are considered spaces.

To initialize the traversal, call |trv_init|. Its parameter
is a function |f| that will receive the stream of characters.
During traversal, the function is stored in the variable |trv_stream|. 

@<\HINT\ functions@>=
static bool trv_ignore=false;
static bool trv_skip_space=false;
static void (*trv_stream)(uint32_t c);
void trv_init(void (*f)(uint32_t c))
{trv_ignore=false;trv_skip_space=false; trv_stream=f;}

static void trv_char(uint32_t c)
{ if (c==0x20) trv_skip_space=true;
  else
  { if (trv_skip_space)
    { trv_skip_space=false; trv_stream(0x20);}
    trv_stream(c);
  }
}

void trv_hlist(pointer p)
{ while(p!=null)
  { if(is_char_node(p))
    { if (!trv_ignore) trv_char(character(p));
    }
    else switch (type(p))
    { case hlist_node: if(list_ptr(p)!=null) trv_hlist(list_ptr(p)); break;
      case vlist_node:  if(list_ptr(p)!=null) trv_vlist(list_ptr(p)); break;
      case ligature_node:
      if (!trv_ignore)
      { pointer q=lig_ptr(p);
        while (q!=null)
        { trv_char(character(q));
          q=link(q);
        }
      }
      break;
      case glue_node: 
        if (!trv_ignore) trv_skip_space=true; 
        break;
      case whatsit_node:
        if (subtype(p)==ignore_node)
        { if (ignore_info(p)==1)
          { trv_hlist(ignore_list(p));
            trv_ignore=true;
          }
          else
            trv_ignore=false;          
        }
        break;
      default: break;
    }
    p= link(p);
  }
}

void trv_vlist(pointer p)
{ while(p!=null)
  { switch (type(p))
    { case hlist_node: if(list_ptr(p)!=null) trv_hlist(list_ptr(p));  
        if (!trv_ignore) trv_skip_space=true;
        break;
      case vlist_node:  if(list_ptr(p)!=null) trv_vlist(list_ptr(p)); break;
      default: break;
    }
    p= link(p);
  }
}
@

@<\HINT\ |extern|@>=
extern void trv_init(void (*f)(uint32_t c));
extern void trv_vlist(pointer p);
extern void trv_hlist(pointer p);
@

Using these functions we can now implement the function
|hlist_to_string|. Currently this function is used only
for outline titles and we limit the string size to 
at most 255, not counting the trailing zero.

@<\HINT\ auxiliar functions@>=
static int trv_string_size=0;
static char trv_string[256];
#define TRV_UTF8(C) (trv_string[trv_string_size++]=(C)) 
static void trv_string_collect(uint32_t c)
{ if (trv_string_size<256-5) /* enough space for c and the final zero byte */
  { if (c<0x80) 
      TRV_UTF8(c);
    else if (c<0x800)
    { TRV_UTF8(0xC0|(c>>6));@+ TRV_UTF8(0x80|(c&0x3F));@+ } 
    else if (c<0x10000)@/
    { TRV_UTF8(0xE0|(c>>12)); TRV_UTF8(0x80|((c>>6)&0x3F));@+ TRV_UTF8(0x80|(c&0x3F)); } 
    else if (c<0x200000)@/
    { TRV_UTF8(0xF0|(c>>18));@+ TRV_UTF8(0x80|((c>>12)&0x3F)); 
      TRV_UTF8(0x80|((c>>6)&0x3F));@+ TRV_UTF8(0x80|(c&0x3F)); } 
    else
     RNG("character code in outline",c,0,0x1FFFFF);
  }
}

char *hlist_to_string(pointer p)
{ trv_string_size=0;
  trv_init(trv_string_collect);
  trv_hlist(p);
  trv_string[trv_string_size]=0;
  return trv_string;
}
@

\subsection{Searching}\label{search}
Searching starts in the user interface with defining a string to
search for.
The variable |m_str| points to the given string and |m_length| is
its length. Further, |m_chars| keeps track of the number of characters,
not counting the spaces, in the search string for reasons explained below.
The |hint_set_mark| function can be used to initialize these variables
from a mark string |m| with length |s|.

@<render variables@>=
static char *m_str;
static int  m_length, m_chars;
@

@<render functions@>=
void hint_set_mark(char *m, int s)
{ m_str=m;
  m_length=s;
  @<remove unwanted spaces@>@;
  hmark_page();
}
@

Leading spaces are removed and
multiple spaces in the search string are reduced to a single space.
@<remove unwanted spaces@>=
if (m_length>0)
{ int i,j,k;
  for (i=j=k=0;i<m_length && m_str[i]==' ';i++) continue;
  for (;i<m_length;i++)
    if (m_str[i]!=' '|| m_str[i+1]!=' ')
    { m_str[k]=m_str[i];
      if (m_str[k]==' ') j++;
      k++;
    }
  m_str[k]=0;
  m_length=k;
  m_chars=m_length-j;
}
@

In its simplest form, searching is the marking of all
matching strings on the current page. The marking itself is the
responsibility of the graphical user interface.  The backend just needs
to indicate which glyphs must be marked.  For this
purpose, every call to |nativeGlyph| passes a style parameter.
For searching, two style bits are defined: |MARK_BIT| and |FOCUS_BIT|.
@<render definitions@>=
#define MARK_BIT 0x1
#define FOCUS_BIT 0x2
@

Calling the function |hint_set_mark(char *m, int s)| will cause the
|MARK_BIT| to be set in the style parameter for all glyphs on the
current page that belong to a character string matching |m| of length
|s|.  If |m==NULL|, the |MARK_BIT| will be zero for all glyphs.  The
``focus'' can be associated with one occurence of the marked string;
its glyphs will have the |FOCUS_BIT| set.
To set or to move the focus, two functions are available: 
|hint_next_mark| and |hint_prev_mark|.
|hint_next_mark| moves the focus to the next occurence, or to the
first one if currently no focus is set. If necessary,
the current page will move forward to contain another occurrence;
|hint_prev_mark| works the same way but searches in backward
direction.  |hint_next_mark| and |hint_prev_mark| will return |true|
if a new occurence was found and return |false| otherwise.
Note that both functions might change the current page even if no new
matching occurrence was found.


Marking will require two passes over the current page: the first pass
is triggered by calling the |hint_set_mark| function. It will traverse
the current page and find all occurrences of the given string. The
second pass is the rendering pass by the function |hint_render|.

The implementations of these functions need a data structure
to store these occurencies.
The array |m_dist| stores the distance to the next occurence.
If there is no next occurrence, the value $\infty$ is stored.
To keep the storage of distances compact,
a variable length encoding is used. The array limits the total size of such encodings
assuming that it is of no use to have thousands of marked words on a single page.

@<render variables@>=
#define MAX_M_DIST 512
static uint8_t m_dist[MAX_M_DIST+5]; /* space for a final 5 byte number and $\infty$ */
static int m_ptr, m_max; 
@

For the variable length encoding, the following convention is used:
The single byte |0xFF| means $\infty$.
Else if the most significant bit is set, the distance is given by
the remaining 7 bits.
Else if the most significant bit is not set, the remaining 7 bits
are added as most significant bits to
the number contained in the following bytes.

Using this convention, $\infty$ and all distances $0\le d < |0x7F|$
can be stored in a single byte. The first distance that needs two byte
is |0x7F|. It is stored as |0x00 0xFF| because setting the
most significant bit of |0x7F| gives |0xFF| which as a single byte is the encoding of
$\infty$.
With two byte, values up to $2^{14}$  can be stored. This should be sufficient
for most cases because 
a) with such large distances there can't be many occurrences
on a single page, and 
b) the current implementation uses 16 bit pointers
and that gives a strict upper bound on the number of characters.
All multibyte encodings start with a sequence of bytes that have a zeros as most significant bits
and terminate with a byte that has a one as most significant bit.
Because the \HINT\ file format limits the content section to $2^{32}$ byte
a 5 byte encoding is sufficient for any distance that could occur in any \HINT\ file.

Here are the functions, to manipulate the |m_dist| array.
The variable |m_ptr| points to the current position in the |m_dist|
array, the variable |m_max| points to the last entry in |m_dist|.
When reading the |m_dist| array, we can assume that the last entry in the 
|m_dist| array is $\infty$.
|m_put| writes distance |d| at position |m_ptr|; |m_get| reads and
returns the distance at position |m_ptr|; both advance |m_ptr|.

@<render variables@>=
static int m_ptr, m_max; 
@

@<render functions@>=
static void m_put(uint32_t d) /* write into |m_dist| */
{@+ if (m_ptr<MAX_M_DIST)
  { if (d==HINT_NO_POS) 
      m_dist[m_max=m_ptr]=0xFF;
   else if (d<0x7F)
      m_dist[m_ptr++]=0x80+d;
   else
   { if (d<(1<<14))
     {
        two_byte:     
        m_dist[m_ptr++]=d>>7;
        m_dist[m_ptr++]=0x80+(d&0x7F);
        return;
      }
      if (d>=(1<<28)) m_dist[m_ptr++]=d>>28;
      if (d>=(1<<21)) m_dist[m_ptr++]=(d>>21)&0x7F;
      if (d>=(1<<14)) m_dist[m_ptr++]=(d>>14)&0x7F;
      d=d&((1<<14)-1);
      goto two_byte;
    }
  }
}      

static uint32_t m_get(void)  /* read from |m_dist| */
{ uint32_t x,y;
  x=m_dist[m_ptr++];
  if (x==0xFF) return HINT_NO_POS;
  if (x&0x80) return x&0x7F;
  while (true)
  { y=m_dist[m_ptr++];
    if (y&0x80) return (x<<7)+(y&0x7F);
    x=(x<<7)+y;
  }
}
@

The next two functions are used to move the focus forward
or backwards. |i| points past the distance that
defined the current focus. It is moved forward or backward
over one entry in the |m_dist| array.
@<render functions@>=
static int m_next(int i) /* advance to next enty */
{ while ((0x80&m_dist[i])==0) i++;
  if (m_dist[i]==0xFF) return 0;
  else return i+1;
}

static int m_prev(int i) /* advance to previous entry */
{ if (i<=0) return m_max;
  i--;
  while (i>0 && (0x80&m_dist[i-1])==0) i--;
  return i;
}
@

The marking uses the page traversal functions defined in
section~\secref{listtraversal} to deliver a stream of characters to
the function |next_m_char|. The latter function finds matches
and writes distances.
The variable |m_state| records the total number of characters that
already matched; the variable |m_spaces| records the number of space characters
included in |m_state|.
To simplify rendering, the rendering will only count characters not spaces.
Therefor the distance |m_d|
between two matches is the number of non-space characters between the two matches.

@<render variables@>=
static int  m_state, m_spaces;
static uint32_t m_d;
@

@<render functions@>=
static void next_m_char(uint32_t c)
{
reconsider:
  if (m_state==0 && c!=m_str[0])
  { if (c!=' ')   
      m_d++;
  }
  else if (c==m_str[m_state])
  { if (m_state==0) m_spaces=0;
    m_state++;
    if (m_state==m_length)
    { m_put(m_d);
      m_d=0;
      m_state=0;
     }
  }
  else
   @<end of matching prefix@>@;
 

}
@

If we have matched |m_state| characters and then found a non matching
character, we should not continue the matching after the prefix but
we should go back to the second character of the prefix and try
starting there. While we can not rewind the traversal, we do have
the characters that we need to reconsider in the |m_str| itself.
After all the characters from the traversal did match the
characters in |m_str|. So we try matching |m_str| against |m_str+i|,
moving |i| forward as far as necessary. Then we jump back to
the beginning of the matching routine to reconsider matching |c|.

@<end of matching prefix@>=
  { int i=0,j=0;
    do {
      if (m_str[i]==' ') j++;
      i++;
    } while (i<m_state && strncmp(m_str,m_str+i,m_state-i)!=0);
    m_d=m_d+i-j;
    m_state=m_state-i;
    goto reconsider;
  }
@

After these preparations, we are ready to traverse the current page.

@<render variables@>=
static int m_focus;
static uint64_t m_page; /* the position of the page currently marked */
@

@<render functions@>=
void hmark_page(void)
{ if (streams==NULL || streams[0].p==null) return;
  m_ptr=0; 
  if (m_page!=page_loc[cur_loc])
  { m_page=page_loc[cur_loc]; 
    m_focus=0;
  }
  if (m_length>0)
  { m_d=0;
    m_state=0;
    trv_init(next_m_char);
    if(type(streams[0].p)==vlist_node)
       trv_vlist(list_ptr(streams[0].p));
    else
       trv_hlist(list_ptr(streams[0].p));
  }
  m_put(HINT_NO_POS); /* $\infty$ */
  if (m_focus>=m_max) m_focus=0;
}
@


We need a dummy version for our test programs.
@<test functions@>=
void hmark_page(void)
{return; }
@

When the renderer traverses the page two more variables are needed.
@<render variables@>=
static bool c_ignore;
static int m_style;
@
|m_style| will have the |MARK_BIT| set while rendering a marked sequence
of characters and it will be zero while rendering non-marked
characters. |c_ignore| will be |true| while rendering characters
that were introduced by the pre- and post-lists of discretionary hyphens.
|m_d| will contain the number of characters left in the current stretch
of marked or unmarked characters.
|m_ptr| will point to the value in the |m_dist| array that we will need
for the next stretch of unmarked characters

At the start of the renderer, we set |m_ptr=m_d=0| and |m_style=MARK_BIT|.
The renderer will then assume it is at the end of a marked sequence of glyphs,
read the first entry from |m_dist| (which might be zero) and starts with
the appropriate number of non-marked glyphs.

@<initialize marking@>=
m_ptr=0; m_d=0;m_style=MARK_BIT;c_ignore=false; cur_style=0;
@

Whenever the renderer encounters a character, it will need to
update |m_style|.

@<update |m_style|@>=
{ while (m_d==0)
  { m_style^=MARK_BIT;
    if (m_style&MARK_BIT)
    { if (m_ptr==m_focus) m_style|=FOCUS_BIT; else  m_style&=~FOCUS_BIT;
      m_d=m_chars;
    }
    else
    { m_style&=~FOCUS_BIT;
      m_d=m_get();
    }
  }
  m_d--;
}
@

When rendering a ligature, we consider for the purpose of marking
the characters that generated the ligature.
If any of these characters is marked, the whole ligature is marked.
@<account for the characters that generated the ligature@>=
if (!c_ignore)
{ pointer q;
  cur_style=cur_style&~(MARK_BIT|FOCUS_BIT);
  q=lig_ptr(p);
  while (q!=null)
  { @<update |m_style|@>@;
    cur_style|=m_style;
    q=link(q);
  }
}
@

When the renderer encounters an ignore node with |ignore_info(p)==1|
it should ignore all the following characters until
it encounters the matching ignore node with |ignore_info(p)==0|.
This is done by setting |c_ignore|.

@<handle an ignore node@>=
if (subtype(p)==ignore_node)
{ if (ignore_info(p)==1)
  { cur_style=cur_style&~(MARK_BIT|FOCUS_BIT);
    c_ignore_list(ignore_list(p));
    c_ignore=true;
  }
  else
    c_ignore=false;
}
@

Instead of the ignored nodes, the renderer considers the characters
stored in the |ignore_list|.
Because there is no simple relation between the |ignore_list| and its replacement,
we will mark the whole replacement if any part of the ignore
list is marked.
Because the |ignore_list| may contain boxes, traversing it
is inherently recursive and we start with a function that
traverses a list of nodes accounting for |m_style| changes
but without rendering them. We assume that the |ignore_list|
consists (recursively!) entirely of character, kern, box, rule, and ligature nodes.

@<render functions@>=
void c_ignore_list(pointer p)
{ while(p!=null)
  { if(is_char_node(p))
    { @<update |m_style|@>@;
      cur_style|=m_style;
    }
    else
    { switch(type(p)) 
      { case hlist_node:
        case vlist_node: c_ignore_list(list_ptr(p)); break;
        case ligature_node:
        { pointer q=lig_ptr(p);
          while (q!=null)
          { @<update |m_style|@>@;
            cur_style|=m_style;
            q=link(q);
          }
        }
        break;
      }
    }
    p=link(p);
  }
}
@



To search for a string within a page or in the entire document,
two further functions are necessary to move the ``focus''.
If there is no focus, |hint_next_mark| will set the focus to the first occurence
on the current page, if there is already a focus, it will move it forward to the next
occurence, possibly rendering the next page or some page further along in the document.
It will return |true| on success and |false| if there is no next occurence.
The function |hint_prev_mark| will again set the focus to the first occurence
on the current page if there is no focus yet, but otherwise will move the focus
backwards to the previous occurence, possibly rendering the previous page.
It will return |true| on success and |false| on failure.

The variable that captures the current focus is |m_focus|.
If there is no focus, it is zero. If it is positive,
|m_focus| points after the distance in the |m_dist| array that preceeds
the occurence that has the focus.



@<render functions@>=
bool hint_prev_mark(void)
{ m_focus=m_prev(m_focus);
  while (m_focus==0 && m_page>0)
  { hint_page_prev();
    m_focus=m_prev(0);
  }
  return (m_focus!=0);
}

bool hint_next_mark(void)
{ m_focus=m_next(m_focus);
  while (m_focus==0)
  { uint64_t p=m_page;
    if (p==hint_page_next()) break;
    m_focus=m_next(0);
  }  
  return (m_focus!=0);
}
@

\subsection{Links}\label{links}
Internal links are part of the displayed document and can be activated to
navigate to a different location in the document.
Similar to marked characters, characters that belong to a link get
a style bit set.
@<render definitions@>=
#define LINK_BIT 0x4
@
The renderer can switch the |LINK_BIT| on and off when it encounters a link node.
Because of line breaking, a link might be spread over multiple
lines or even pages. To detect an unfinished link
at the end of a horizontal list, the local variable |local_link| is used;
the current link is then recorded in |cur_link|.
To collect data about all links on a page, the renderer calls |add_new_link|
when a link starts and |end_new_link| when it ends.

@<render variables@>=
static int cur_link=-1;
@

@<handle a link node@>=
if (subtype(p)==start_link_node)
{ cur_style|=LINK_BIT;
  local_link=label_ref(p);
  add_new_link(local_link,this_box,cur_h,cur_v);
}
else if (subtype(p)==end_link_node)
{  cur_style&=~LINK_BIT;
   end_new_link(local_link,this_box,cur_h,cur_v);
   local_link=-1;
}
@

If at the end of a horizontal list |local_link| is |true| an additional
end link is signaled.

@<end an unfinished link@>=
if (local_link>=0)
{ end_new_link(local_link,this_box,cur_h,cur_v);
  cur_link=local_link;
}
@

And the call for another |add_new_link| is inserted at the
start of the next horizontal list.

@<start an unfinished link@>=
if (cur_link>=0)
{ add_new_link(cur_link,this_box,cur_h,cur_v);
  local_link=cur_link;
  cur_link=-1;
}
@

To enable the user interface to take action if a link is clicked or
if the mouse moves over a link, the backend supplies
the necessary information in the |hint_links| and |max_links| variables.
|hint_links| is a dynamic array, indexed from 0 to |max_links|.
If |max_links| is negative, no links are available.



@<\HINT\ |extern|@>=
typedef struct { 
uint64_t pos;  
uint8_t where; 
scaled top, bottom, left, right;
} hint_Link;
extern hint_Link *hint_links;
extern int max_link;
@

@<\HINT\ variables@>=
hint_Link *hint_links=NULL;
int max_link=-1;
@

The |hint_links| array is filled with the necessary information
when the page is rendered.

@<render functions@>=
static int links_allocated=0;
void add_new_link(int n, pointer p, scaled h, scaled v)
{ hint_Link *t;
   uint64_t pos;
   uint8_t where;
  max_link++;
  if (max_link>=links_allocated)
  {  if (links_allocated<=0)
     { links_allocated=32;
       ALLOCATE(hint_links,links_allocated,hint_Link);
     }
     else
     { links_allocated=links_allocated*1.4142136+0.5; /* $\sqrt 2$ */
        REALLOCATE(hint_links,links_allocated,hint_Link);
     }
  }
  t=hint_links+max_link;
  REF_RNG(label_kind,n);
  @<get |where| and |pos| from label |n|@>@;
  t->where=where;
  t->pos=pos;
  if (type(p)==hlist_node)
  { scaled hp=height(p), dp=depth(p);
    t->top=v-hp;
    t->bottom=v+dp;
    t->left=h;
    t->right=h;
  }
  else
  { t->top=v;
    t->bottom=v;
    t->left=h;
    t->right=h+width(p);
  }
}

void end_new_link(int n, pointer p, scaled h, scaled v)
{ hint_Link *t;
  t=hint_links+max_link;
  if (type(p)==hlist_node)
    t->right=h;
  else
    t->bottom=v;
}
@


Given the coordinates of a point on the page,
currently only a linear search for a matching link is implemented.
If many links are expected on a single page, for example in the index
of a large book where pages are full of keywords each having multiple
links to different positions in the book, a more sophisticated
search might be needed. If the links in the array are sorted
by increasing top boundaries, the search can stop early if the
y coordinate is above the top coordinate of a link; all following
links will have an equal or even larger top boundary.
If there is a chain of indices of links sorted by the bottom boundaries,
the search along the bottom boundaries can also terminate
early. Together this should limit the search to a short stretch of links.

The | precission| parameter allows to find links if their distance from
the given coordinates is smaller than the given |precission|.

The following function returns an index into the |hint_links|
array or $-1$ if no link is at the given position.

To speed up processing, it remembers the last hit.

@<render functions@>=
static scaled hlink_distance(scaled x,scaled y, hint_Link *t)
{ scaled d, dx=0, dy=0;
  d = t->top-y;
  if (d>0) dy=d;
  else
  { d= y-t->bottom;
    if (d>0) dy=d;
  }
  d = x-t->right;
  if (d>0) dx=d;
  else
  { d= t->left-x;
    if (d>0) dx=d;
  }
  if (dx>dy) return dx;
  else return dy;

}

int hint_find_link(scaled x, scaled y,scaled precission)
{ static int last_hit=-1;
  int i;
  hint_Link *t;
  if (max_link<0) return -1;
  if (last_hit<0 || last_hit>max_link) last_hit=max_link/2;
  i=last_hit;
  t=hint_links+i;
  if (hlink_distance(x,y,t)<=precission)
    return i;
  else if (y<t->top) /* search up */
  { while (i>0)
    { i--;
      t=hint_links+i;
      if(hlink_distance(x,y,t)<=precission)
      { last_hit=i;  return i; }
    }
    return -1;
  }
  else /* search all */
  { int k;
    scaled d, min_d=precission;
    int min_i=-1;
    for (k=0;k<=max_link;k++)
    { i=i+1;
      if (i>max_link) i=0;
      t=hint_links+i;
      d=hlink_distance(x,y,t);
      if (d<min_d)
      { min_d=d; min_i=i;}
    }
    last_hit=min_i;
    return last_hit;
  }
}
@
If a link is selected,
the user interface should pass the position to
|hint_page_top|, |hint_page_bottom|, or |hint_page_middle| to obtain
the desired page.
As a shortcut, it can call this function:
@<render functions@>=
 uint64_t hint_link_page(int i)
{@+ uint64_t h;
  uint8_t w;
  if (i<0||i>max_link) return  hint_page_get();
  h=hint_links[i].pos;
  w=hint_links[i].where;
  if (w==LABEL_TOP) return hint_page_top(h);
  else if (w==LABEL_BOT) return hint_page_bottom(h);
  else if (w==LABEL_MID) return hint_page_middle(h);
  else return  hint_page_get();
}
@

Here is a summary of the above functions:
@<\HINT\ |extern|@>=
extern int hint_find_link(scaled x, scaled y,scaled precission);
extern uint64_t hint_link_page(int i);
@


\section{Rendering \HINT\ Files}
How to render a \HINT\ file on any specific device depends largely on the
operating system and its API encapsulating the device. Never the less, there
are some functions that can be shared accross many different operating systems
or at least can serve as a starting point for implementing operating system specific
versions.

Most systems, for example, will need some code to initialize and to finalize
the rendering infrastructure. The system depenent functions will be implemented
in as |nativeInit| and |nativeClear|. To have a consistent interface accross
different graphical user interfaces. These are reexported as |hint_render_on|
and |hint_render_off|.

@<render functions@>=
void hint_render_on(void)
{ nativeInit();
}

void hint_render_off(void)
{ nativeClear();
}
@

Similar functions that are just forwarded are |nativeSetDark|
and |nativeSetGamma|

@<render functions@>=
void hint_dark(int dark)
{ nativeSetDark(dark);
}
void hint_gamma(double gamma)
{ nativeSetGamma(gamma);
}
@

Prototypes of the three functions just defined are contained in
the {\tt hrender.h} file where as the prototypes of the 
``native'' functions are part of {\tt rendernative.h}. The latter
file contains requirements: functions that need to be implemented
but are not defined here. Most implementations will avoid the
inclusion of  {\tt rendernative.h} because it will need other include files,
notably  {\tt hfonts.h} which defines the interface to the font cache.
In contrast, {\tt hrender.h} has almost no dependencies and avoids
cluttering the global name space by using the |hint_|\dots prefix.




\subsection{Fonts}
The \HINT\ file format supports four different types of fonts:
The traditional PK fonts\cite{TR:pkfile} and the more modern
PostScript Type1 fonts\cite{PST1} which are used by many \TeX\ engines, 
TrueType\cite{TTT:TT} fonts, and OpenType fonts\cite{MS:OTF}\cite{ISO:OTF}.
To render the latter, we use the FreeType Library\cite{freetype}
by David Turner, Werner Lemberg, and others.

@<font types@>=
typedef	enum {@+ no_format, pk_format, ft_format@+ } FontFormat;
@


The features of a font are described in a |font_s| structure.  A major
part of the structure is the glyph cache that provides fast access to
the individual glyphs belonging to the font. Further, it includes an
|ff| field containing the font format and a variant part that differs
for the different font formats.


@<font types@>=
@<definitions of |PKfont| and |FTfont| types@>@;

typedef struct font_s {
  unsigned char n; /* the font number */
  unsigned char *font_data; /* pointer to the font data in the HINT file */
  int data_size; /* the size of the font data in byte */
  double s; /* the size in pt */
  double hpxs,vpxs; /* the horizontal and vertical size of one pixel in pt */
  @<the glyph cache@>@;
  FontFormat ff; /* the font format */
  union {@+ PKfont pk; @+FTfont tt;@+  }; /* the font format specific parts */
} Font;
@
The |fonts| table contains an entry for every possible font number.

@<font variables@>=
static Font *fonts[0x100]={NULL}; 
@

Given a font number |f| the following function returns a pointer to the 
corresponding font structure, extracting the necessary information from the \HINT\ file if necessary.
@<font functions@>=
struct font_s *hget_font(unsigned char f)
{ Font *fp;
  if (fonts[f]!=NULL) return fonts[f];
  DBG(DBGFONT,"Decoding new font %d\n",f);
  if (f>max_ref[font_kind])
    QUIT("Undefined font %d\n",f);
  fp = calloc(1,sizeof(*fp));
  if (fp==NULL) 
    QUIT("Out of memory for font %d",f);
  else
  { unsigned char *spos, *sstart, *send;
    spos=hpos; sstart=hstart;send=hend;@/
    fp->n=f;
    hget_section(hglyph_section(f));@/
    fp->font_data=hstart;
    fp->data_size=hend-hstart;@/
    hpos=spos; hstart=sstart;hend=send;
  }
  fp->s=font_at_size(f)/(double)(1<<16);
  @<determine the font format and unpack the font@>@;
  fonts[f]=fp;
  return fonts[f];
}
@
This function is used in the renderer, so it is exported and returns an
opaque pointer type to the font structure.
@<font |extern|@>=
extern struct font_s *hget_font(unsigned char f);
@

To initialize the |fonts| table and remove all fonts form memory, the
function |hint_clear_fonts|  is used with the |rm| parameter set to
|true|. If |rm| is set to |false| the action is less drastic: only the
function |nativeFreeGlyph| is called for all glyphs in the glyph cache,
the |fonts| table and the glyph cache are retained.


@<font functions@>=
static void hfree_glyph_cache(Font *f, bool rm);

void hint_clear_fonts(bool rm)
{ int f;
  DBG(DBGFONT,rm?"Clear font data":"Clear native glyph data");
  for (f=0;f<=max_ref[font_kind];f++)
    if (fonts[f]!=NULL)
    { hfree_glyph_cache(fonts[f],rm);
      if (rm)@+ { @+ free(fonts[f]); fonts[f]=NULL;@+ }
    }
}
@

We need a dummy version for our test programs.
@<test functions@>=
void hint_clear_fonts(bool rm)
{return; }
@







\subsubsection{The Glyph Cache}
If possible, the glyphs belonging to a font are extracted only once from the font data,
converted into a format suitable for the native rendering engine, and then cached for repeated use.
The cached glyph representation for glyph |g| is stored in one of four trees. 
The order and depth of the trees reflects UTF-8 encoding.
   The first tree is of oder $2^7$ and only 1 level deep; its root is |g0|.
   The other trees, |g1|, |g2|, and |g3| are of order $2^6$ and have a depth
   of 2, 3, and 4 levels respectively.

@<the glyph cache@>=
  struct gcache_s **g0; /* $0 \le |g| < 2^7$ */
  struct gcache_s ***g1;  /* $2^7 \le |g| < 2^{12}$ */
  struct gcache_s ****g2; /* $2^{12} \le |g| < 2^{18}$ */
  struct gcache_s *****g3; /* $2^{18} \le |g| < 2^{24}$ */@/
@t~@>
@


The glyphs are described using a |gcache_s| structure. 
We use |Gcache| as a shorthand for |struct gcache_s|.
 
To look up the cached glyph data for font |f| and charactercode |cc|, we use the function |g_lookup|.

@<auxiliar font functions@>=
#define G0_BITS 7
#define G0_SIZE (1<<G0_BITS)
#define G0_MASK (G0_SIZE-1)
#define G123_BITS 6
#define G123_SIZE (1<<G123_BITS)
#define G123_MASK (G123_SIZE-1)

static Gcache *g_lookup(Font *f, unsigned int cc)

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
static Gcache g_undefined ={0};
@

@<auxiliar font functions@>=
static Gcache *hnew_g(Gcache **g)
{ if (*g==NULL)
    *g=calloc(1, sizeof(Gcache));
  if (*g==NULL) 
    return &g_undefined;
  (*g)->ff=no_format;
  return *g;
}

static Gcache *hnew_g0(Gcache ***g,unsigned int cc)
{ unsigned int cc0=cc&G0_MASK;
  if (*g==NULL)
    *g=calloc(G0_SIZE, sizeof(Gcache*));
  if (*g==NULL) 
    return &g_undefined;
  return hnew_g((*g)+cc0);
}
 
static Gcache *hnew_g1(Gcache ****g,unsigned int cc)
{ unsigned int cc1=(cc>>G0_BITS)&G123_MASK;
  if (*g==NULL)
    *g=calloc(G123_SIZE, sizeof(Gcache**));
  if (*g==NULL) 
    return &g_undefined;
  return hnew_g0((*g)+cc1,cc);
}
static Gcache *hnew_g2(Gcache *****g,unsigned int cc)
{ unsigned int cc2=(cc>>(G123_BITS+G0_BITS))&G123_MASK;
  if (*g==NULL)
    *g=calloc(G123_SIZE, sizeof(Gcache***));
  if (*g==NULL) 
    return &g_undefined;
  return hnew_g1((*g)+cc2,cc);
}
  
static Gcache *hnew_g3(Gcache ******g,unsigned int cc)
{ unsigned int cc3=(cc>>(G123_BITS+G123_BITS+G0_BITS))&G123_MASK;
  if (*g==NULL)
    *g=calloc(G123_SIZE, sizeof(Gcache****));
  if (*g==NULL) 
    return &g_undefined;
  return hnew_g2((*g)+cc3,cc);
}


static Gcache *hnew_glyph(Font *f, unsigned int cc)
{ if (cc<G0_SIZE) return hnew_g0(&(f->g0),cc);
  else if (cc<G123_SIZE*G0_SIZE) return hnew_g1(&(f->g1),cc);
  else if (cc<G123_SIZE*G123_SIZE*G0_SIZE) return hnew_g2(&(f->g2),cc);
  else if (cc<G123_SIZE*G123_SIZE*G123_SIZE*G0_SIZE) return hnew_g3(&(f->g3),cc);
  else return &g_undefined;
}
@

The next set of functions is used to clear the glyph cache.
If the boolean parameter |rm| is |true|, the complete cache will 
be deallocated. Otherwise only the function |nativeFreeGlyph| will be called.
Together with the exported function |hint_clear_fonts| this offers
the native rendering engine a method to relase allocated resources
without the need to know the deatails of the glyph cache.
The construction of the functions |hfree_g0| to |hfree_g3| mirrors
the construction of |hnew_g0| to  |hnew_g3|

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


static void hfree_glyph_cache(Font *f, bool rm)
{ if (f->g0!=NULL)
  { hfree_g0(f->g0,rm);
     if (rm) {@+free(f->g0); f->g0=NULL;@+}
  }
  if (f->g1!=NULL)
  { hfree_g1(f->g1,rm);
     if (rm) {@+free(f->g1); f->g1=NULL;@+}
  }
  if (f->g2!=NULL)
  { hfree_g2(f->g2,rm);
     if (rm) {@+free(f->g2); f->g2=NULL;@+}
  }
  if (f->g3!=NULL)
  { hfree_g3(f->g3,rm);
     if (rm) {@+free(f->g3); f->g3=NULL;@+}
  }
}
@
\subsection{Glyphs}
The |gcache_s| structure may depend on the font encoding but also on
the rendering engine that is used to display the glyphs. While the
dependency on the font encoding is dynamic, the dependency on the
rendering engine can be resolved at compile time.

Every |gcache_s| structure stores |w| and |h|, the width and height of
the minimum bounding box in pixel; |hoff| and |voff|, the horizontal
and vertical offset in pixel from the upper left pixel to the
reference pixel (right and down are positive), and then the array of bytes
that represents the gray values of the bitmap.

Next commes the
representation of the glyph that is most convenient for rendering on
the target sytem. For the Windows operating system, this is a handle to a
device dependent bitmap.  For the Android
operating system using Open~GLE~2.0 it's an identifier for the texture.
Then there is a last part
that is different for the different font encodings; it is taged by
the font format number |ff|. The information in this last part helps
with on-demand decoding of glyphs.


@<font types@>=
@<definitions of format specific types@>@;

struct gcache_s {
  int w,h; 
  int hoff,voff; 
  unsigned char *bits; 
  unsigned int GLtexture;
  FontFormat ff; 
  union {@+
	  PKglyph pk;@+
	  FTglyph tt;@+
  };
};
typedef struct gcache_s Gcache;
@
 

The above structure has a |GLtexture| member if rendering is done on
the Android operating system using Open~EGL 2.0. To speed up the
rendering of glyphs, the glyph bitmap is loaded into the graphics
cards as a texture and from then on identified by a single integer,
the |GLtexture|.

Occasionaly, however, the front-end will change the OpenGL context and
the texture identifiers will loose their meaning. In this situation,
it is not necessary to wipe out the entire glyph cache with all the
extracted bitmaps but only the invalidation of the texture identifiers
is needed.  This effect can be achived by calling
|hint_clear_fonts(false)|. It will call |nativeFreeGlyph| for all
glyphs and this function can set the |GLtexture| value to zero.


The top level function to access a glyph is |hget_glyph|. Given a font pointer |fp| 
and a character code |cc| it looks up the glyph in the glyph cache.
For PK fonts, all cache entries are made when initializing the font.
For FreeType fonts, a cache entry is made when the glyph is accessed the first time.
For both types of fonts, the unpacking is done just before the first use.

@<font functions@>=
Gcache *hget_glyph(Font *f, unsigned int cc)
{
  Gcache *g=NULL;
  g=g_lookup(f,cc);
  if (g==NULL)
  { if (f->ff==ft_format)
      g=hnew_glyph(f,cc);
    else  
      return NULL;
  }
  if (g->ff==no_format)           
  { if (f->ff==pk_format) pkunpack_glyph(g);
    else if (f->ff==ft_format) ft_unpack_glyph(f,g,cc);
    else QUIT("Font format not supported");
  }
  return g;
}
@

Rendering a glyph is the most complex rendering procedure. But with all the preparations,
it boils down to a pretty short function to display a glyph, given by its charcter code |cc|,
its font |f|, and its position and size  |x|, |y|, and |s| given as scaled points.
Most of the function deals with the conversion of \TeX's measuring system,
that is scaled points stored as 32 bit integers,
into a representation that is more convenient for non \TeX{nical} sytems,
namely regular points stored as |double| values. The latter is used by
the native rendering functions. Most of the conversion is done by the macro |SP2PT|.

@<render definitions@>=
#define SP2PT(X) ((X)/(double)(1<<16))
@
@<font functions@>=
void render_char(int x, int y, struct font_s *f, uint32_t cc, uint8_t s)

{ double w, h, dx, dy;
  Gcache *g=hget_glyph(f,cc);
  if (g==NULL) return;

  dx=(double)g->hoff*f->hpxs;
  dy=(double)g->voff*f->vpxs;@/
  w =(double)g->w*f->hpxs;
  h =(double)g->h*f->vpxs;
  nativeGlyph(SP2PT(x),dx,SP2PT(y),dy,w,h,g,s);
}

@
\goodbreak
@<font |extern|@>=
extern void render_char(int x, int y, struct font_s *f, uint32_t cc, uint8_t s);
@

\subsection{Rules}
Rendering rules, that is black rectangles, is simpler.

@<render functions@>=
static void render_rule(int x, int y, int w, int h)
{@+ if (w>0 &&  h>0)
  nativeRule(SP2PT(x),SP2PT(y),SP2PT(w),SP2PT(h));@+
}
@

\subsection{Images}
When we need to render an image, we should not bother the native
renderer with finding the image data in segment |n| of the \HINT\
file. Instead we pass a pointer to the first byte and a pointer past
the last byte. We also pass the position and size as we did for rules.
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

Now at last, we render pages. Two mutualy recursive procedures,
rendering vertical and horizontal lists, will accomplish the
rendering. The functions are more or less modifications of \TeX's
functions that write DVI files. They share a few global static
variables that implement the current state of the renderer: |cur_h|
and |cur_v| contain the current horizontal and vertical position;
|rule_ht|, |rule_dp|, and |rule_wd| contain the height, depth, and
width of a rule that should be output next; |cur_f| and |cur_fp|
contain the current font number and current font pointer.

@<render variables@>=
static scaled cur_h, cur_v;
static scaled rule_ht, rule_dp, rule_wd; 
static int cur_f; 
static struct font_s *cur_fp;
static uint8_t cur_style=0;
@

@<render functions@>=
static void vlist_render(pointer this_box);

static void hlist_render(pointer this_box)
{ scaled base_line;
scaled left_edge;
scaled h_save;
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
int local_link=-1;
uint8_t f;
uint32_t c;

cur_g= 0;
cur_glue= 0.0;
g_order= glue_order(this_box);
g_sign= glue_sign(this_box);
p= list_ptr(this_box);
#ifdef DEBUG
if(p==0xffff)
  QUIT("Undefined list pointer in hbox 0x%x-> mem[0x%x] -> 0x%x\n",
        this_box,mem[this_box].i,p);
#endif
base_line= cur_v;
left_edge= cur_h;
@<start an unfinished link@>@;
while(p!=null)
{
#ifdef DEBUG
if(p==0xffff)
        QUIT("Undefined pointer in hlist 0x%x\n",p);
if(link(p)==0xffff)
        QUIT("Undefined link in hlist mem[0x%x]=0x%x\n",p,mem[p].i);
#endif
  if(is_char_node(p))
  { do
    { f= font(p);
      c= character(p);
      if (!c_ignore && c!=' ')
      { cur_style=cur_style&~(MARK_BIT|FOCUS_BIT);
        @<update |m_style|@>@;
        cur_style|=m_style;
      }

render_c:        
      if(f!=cur_f)
      {
#ifdef DEBUG
        if(f> max_ref[font_kind])
           QUIT("Undefined Font %d mem[0x%x]=0x%x\n",
                f,p,mem[p].i);
#endif
        cur_fp=hget_font(f);
        cur_f= f;
      }
      render_char(cur_h, cur_v, cur_fp,c,cur_style);
      cur_h= cur_h+char_width(f, char_info(f, c));
#ifdef DEBUG
      if(link(p)==0xffff)
        QUIT("Undefined link in charlist mem[0x%x]=0x%x\n",p,mem[p].i);
#endif
      p= link(p);
    } while(is_char_node(p));
  }
  else
  { switch(type(p)) 
    { case hlist_node:
     case vlist_node:
#ifdef DEBUG     
        if(list_ptr(p)==0xffff)
          QUIT("Undefined list pointer in hlist mem[0x%x] = 0x%x -> 0x%x\n",
                p,mem[p].i,list_ptr(p));
#endif
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
       @<handle an ignore node@>@;
       else @<handle a link node@>@;
       else if (subtype(p)==image_node)
       { scaled h,w;
         w=image_width(p);
         h=image_height(p);
         render_image(cur_h, cur_v, w, h,image_no(p));
         cur_h= cur_h+w; 
       }
       break;
     case glue_node:
     { pointer g;
        g=glue_ptr(p);rule_wd= width(g)-cur_g;
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
            { h_save= cur_h;
              cur_h= left_edge+leader_wd*((cur_h-left_edge)/leader_wd);
              if(cur_h<h_save)cur_h= cur_h+leader_wd;
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
		    h_save=cur_h;
                    c_ignore=true;
			if(type(leader_box)==vlist_node)
				vlist_render(leader_box);
			else 
				hlist_render(leader_box);
                     c_ignore=false;
			cur_v= base_line;
			cur_h= h_save+leader_wd+lx;
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
      f= font(lig_char(p));
      c= character(lig_char(p));
      @<account for the characters that generated the ligature@>@;
      goto render_c;
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
   next_p:
#ifdef DEBUG
    if(link(p)==0xffff)
        QUIT("Undefined link in hlist mem[0x%x]=0x%x\n",p,mem[p].i);
#endif        
    p= link(p);
 }
} /* end |while| */
@<end an unfinished link@>@;
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
#ifdef DEBUG
if(p==0xffff)
  QUIT("Undefined list pointer in vbox 0x%x-> mem[0x%x] -> 0x%x\n",
        this_box,mem[this_box].i,p);
#endif
left_edge= cur_h;cur_v= cur_v-height(this_box);
top_edge= cur_v;
while(p!=null)
{ if(is_char_node(p)) DBG(DBGTEX,"Glyph in vertical list ignored");
  else
  { switch(type(p))
    { case hlist_node:
      case vlist_node:
#ifdef DEBUG
        if(list_ptr(p)==0xffff)
          QUIT("Undefined list pointer in vlist mem[0x%x] = 0x%x -> 0x%x\n",
                p,mem[p].i,list_ptr(p));
#endif                
        if(list_ptr(p)==null) cur_v= cur_v+height(p)+depth(p);
	    else
	    { cur_v= cur_v+height(p);save_v= cur_v;
          cur_h= left_edge+shift_amount(p);
          if(type(p)==vlist_node)vlist_render(p);
	  else
           hlist_render(p);
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
                      c_ignore=true;
		      if (type(leader_box)==vlist_node) 
				  vlist_render(leader_box);
			  else 
				  hlist_render(leader_box);
                      c_ignore=false;
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
  next_p:
#if 0
      if (link(p)==1 || link(p)==0xffff) {
        show_box(streams[0].p);
        QUIT("vertical node mem[0x%x] =0x%x ->linking to node 0x%x\n",
          p, mem[p].i, link(p));
    }
#endif    
    p= link(p);
  } /* end |while| */
} /* end |vlist_render| */

@


We conclude this section with the function that must be called after the page builder has finished
the page: the |hint_render| function.
@<render functions@>=

void hint_render(void)
{  nativeBlank();
   if (streams==NULL || streams[0].p==null) return;
   cur_h= 0;
   cur_v= height(streams[0].p);
   cur_f=-1;cur_fp=NULL;
   cur_link=-1; max_link=-1;
   @<initialize marking@>@;
   if(type(streams[0].p)==vlist_node)
     vlist_render(streams[0].p);
   else
     hlist_render(streams[0].p);
}
@

\subsection{Printing}\label{printing}
To print the content of a \HINT/ file, it is necessary to convert
the horizontal or vertical boxes representing the pages into a format
that can be understood by the printer driver. Future versions of this
document may, for example, contain a procedure to convert such boxes
to PostScript code in the same way as {\tt dvips} does it.

For now only a simpler approach is available: Two replacements
for |hint_render_on| and |hint_render_off| that sets things up
in such a way that the rendering will end up in a memory framebuffer
instead of on screen. And a third function, that transfers the
content of the framebuffer to a byte array.
Usually operating systems provide means to turn the byte array
into some form of image or canvas, that can be sent to the printer
driver. This method of printing produces large amount of data
and is not recommended when printing to a file (use one of the
many \TeX\ engines that produce pdf output if you need souch files),
but it provides a convenient way of obtaining paper copies of a few
pages.

@<render functions@>=
int hint_print_on(int w, int h, int bpr, int bpp, unsigned char *bits)
{ return nativePrintStart(w, h, bpr, bpp, bits);
}

int hint_print_off(void)
{ return nativePrintEnd();
}

int hint_print(unsigned char *bits)
{ return nativePrint(bits);
}
@





\section{Native Rendering}\label{native}
The {\tt rendernative.h} header file lists all functions that the native renderer must implement.

To initialize the renderer call |nativeInit|. To release all resorces allocated call |nativeClear|.
If the rendering is supposed to go to memory (see section~\secref{printing}) instead of the screen, use |nativePrintStart|
and |nativePrintEnd|. To transfer the memory content to a given byte array use |nativePrint| 

@<native rendering definitions@>=
extern void nativeInit(void); 
extern void nativeClear(void);
extern int nativePrintStart(int w, int h, int bpr, int bpp, unsigned char *bits);
extern int nativePrintEnd(void);
extern int nativePrint(unsigned char *bits);
@


To set the size of the drawing aerea in pixel and the resolution in dots (pixel) per inch call |nativeSetSize|
@<native rendering definitions@>=
extern void nativeSetSize(int px_h, int px_v, double xdpi, double ydpi);
@ 

The native renderer may implement an optional procedure to switch between dark and light mode.
The other procedure may change the $\gamma$-value.
@<native rendering definitions@>=
extern void nativeSetDark(int dark);
extern void nativeSetGamma(double gamma);
@

To  render an empty page call |nativeBlank|.
@<native rendering definitions@>=
extern void nativeBlank(void); 
@

In the following, if not otherwise stated, all dimensions are given as double values in point.
We have $72.27\,\hbox{pt} = 1\,\hbox{inch}$ and $1\,\hbox{inch} = 2.54\, \hbox{cm}$.


To render the glyph |g| with reference point at $(|dx|,|dy|)$
at position $(|x|,|y|)$ with width |w| and height |h| and style |s| call:
@<native rendering definitions@>=
typedef struct gcache_s *gcache_s_ptr;

extern void nativeGlyph(double x, double dx, double y, double dy, double w, double h, struct gcache_s *g, uint8_t s);
@
For an explanation of the style parameter see section~\secref{search}.



To render a black rectangle at position  $(|x|,|y|)$ with width |w| and height |h| call:

@<native rendering definitions@>=
void nativeRule(double x, double y, double w, double h);
@
To render an image at position  $(|x|,|y|)$ with width |w| and height |h|,
with the image data in memory from |istart| to (but not including) |iend| call:

@<native rendering definitions@>=
void nativeImage(double x, double y, double w, double h, unsigned char *istart, unsigned char *iend);
@

For PK fonts and FreeType fonts we need two functions to translate the
glyph bitmap in |g->bits| into a device dependent representation.
@<native rendering definitions@>= 
extern void nativeSetPK(struct gcache_s *g);
extern void nativeSetFreeType(struct gcache_s *g);
@

To free any native resources associated with a cached glyph |g| call:

@<native rendering definitions@>=
void nativeFreeGlyph(struct gcache_s *g);
@
This function is also called for all glyphs by the function |hint_clear_fonts|.
If the |rm| parameter to that function is |false|, the glyph cache is not deallocated
only |nativeFreeGlyph| is executed for all glyphs.


\section{Font Files}

\subsection{PK Fonts}

PK Files
contain a compressed representation of bitmap fonts  produced by \MF\ and {\tt gftopk}. The definitions and algorithms that follow here can be found,
along with a more detailed description, in \cite{TR:pkfile}. 

The first thing we need to know when a section of a \HINT\ file contains a font is
the font format. We know, it contains a PK font if the first two byte contain the
values |0xF7| and |0x59|.

@<determine the font format and unpack the font@>=
  if (fp->font_data[0]==0xF7 &&  fp->font_data[1]==0x59)
  { fp->ff=pk_format;
    if (!unpack_pk_file(fp)) { free(fp); fp=NULL; }
  }
@

%After unpacking these fonts, we obtain a (device independent) bitmap for each glyph.
%On Windows the bitmap can be displayed on a Device Context using the |StretchDIBits| function.
%This function is capable of stretching or shrinking and hence can adjust the
%resolution. The resolution of the bitmap in the pk file is given be the 
%two parameters |hppp| (horizonttap pixel per point) and vppp (vertical pixel per point) which
%are found in the preamble of the pk file.

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


The information in the PK file that is specific to a PK font is stored as a |PKfont| type:
@<definitions of |PKfont| and |FTfont| types@>=

typedef struct
{ unsigned char *pk_comment; /* the program that made the pk font */
  unsigned int cs; /* checksum */
  double ds; /* the design size in pt */
  unsigned char id; /* the id currently allways 89 */
} PKfont;
@

For every glyph, there is a |flag| byte in the PK file that tells how the corresponding glyph is
encoded and a pointer to the encoding itself.

@<definitions of format specific types@>=
typedef struct
{ unsigned char flag; /* encoding in the pk file */
  unsigned char *encoding;
} PKglyph;
@

Before we define two functions, one to unpack a single glyph when it is needed for the first time,
and one to unpack a font when it is needed for the first time, we define four primitive
reading operations as macros.

@<PK font functions@>=
#define PK_READ_1_BYTE() (data[i++])
#define PK_READ_2_BYTE() (k=PK_READ_1_BYTE(),k=k<<8,k=k+data[i++],k)
#define PK_READ_3_BYTE() (k=PK_READ_2_BYTE(),k=k<<8,k=k+data[i++],k)
#define PK_READ_4_BYTE() (k=PK_READ_3_BYTE(),k=k<<8,k=k+data[i++],k)
@

Here is the function to unpack a single glyph. 
To extract the actual bitmap it uses either
the function |pk_bitmap| or |pk_runlength|

To parse a PK font file, it is necessary to read numbers that are packed in a series of 
4 bit values called ``nybbles''.
The parse state therefore needs to be aware of positions inside a byte.
We store this state as a |PKparse|.

@<definitions of format specific types@>=
typedef struct {
int j; /* position of next nybble in data */
int r; /* current repeat count */
int f; /* dynamic f value */
unsigned char *data; /* array of data bytes */
} PKparse;
@
Given a parse state |P|, we read the next nybble
with the following macro:

@<PK font functions@>=
#define read_nybble(P) ((P).j&1?((P).data[(P).j++>>1]&0xF):(((P).data[(P).j++>>1]>>4)&0xF))
@

The pixel data stored in a PK file can be considered as a long sequence
of black and white pixels. Instead of storing individual pixels,
it is more space efficient to store run counts, that is the number of consecutive pixels
of the same color. And since with glyphs often the same pattern of white and
black pixels is repeated for several lines, it improves space efficiency if we
store also repeat counts.

Now here are the details of how run counts and repeat counts are stored
as a sequence of nybbles:
The value 15 indicates a repeat count of 1 (most common case).
The value 14 indicates that the next nybble stores the repeat count.
Values below 14 are dedicated to run counts.
If the value $a$ is in the range $14>a>|f|$, we read a second nybble $b$
and obtain the run count as $(a-|f|-1)*16+$b$+|f|+1$.
Note that we add $|f|+1$; this is possible because
the values from 1 to |f| are used directly as run counts.
A sequence of |k| nybbles with value zero is followed by |k| nybbles
that represent the run count---well, almost. We add the value of the
largest run cont that can be expressed using any of the other methods plus one.

The following function implements this procedure:

@<PK font functions@>=
static int packed_number(PKparse *p)
{ int i, k;
  i= read_nybble(*p);
  if (i==0)
  { do { k=read_nybble(*p); i++; } while (k==0);
    while (i-->0) k=k*16+read_nybble(*p);
	return k-15+(13-p->f)*16+p->f;
  }
  else if (i<=p->f) return i;
  else if (i<14) return (i-p->f-1)*16+read_nybble(*p)+p->f+1;
  else
  { if (i==14) p->r=packed_number(p);
    else p->r= 1;
    return packed_number(p);
  }
}
@

Now here is the function, that reads a bitmap encoded using
run counts and repeat counts.
The |data| array contains the run counts and repeat counts for a bitmap of height |g->h| and
width |g->w| as a top-down bitmap, where the first bit corresponds to the
top left pixel and the last bit to the bottom right pixel.
The function will produce a bottom-up bitmap with one byte per pixel
to conform to the format that is used by the FreeType library.
We traverse the |data| nybbles sequentially in top-down order.
The horizontal position |x| and the vertical position |y| in the
target bitmap start at 0 and |g->h-1|.
@<PK font functions@>=
static void pk_runlength(Gcache *g, unsigned char *data) {
    PKparse p;
    int x, y; /* position in target bitmap */
    unsigned char *bits; /* target bitmap */
    int n; /* number of pixel left in current run */
    unsigned char gray; /* whether pixel is white in current run */
    bits=g->bits = (unsigned char *) calloc(g->w * g->h, 1);
    if (bits == NULL) { g->w = g->h = 0;  return; } /* out of memory */
    p.j = 0; /* nybble position to start of data */
    p.r = 0; /* repeat count = 0 */
    p.f = g->pk.flag >> 4; /* dynamic f value */
    p.data=data; /* data bytes */
    n = 0;
    if ((g->pk.flag >> 3) & 1) gray=0x00;
    else gray=0xff;
    y = 0;
    while (y <g->h) {
        x = 0;
        while (x < (int) g->w) /* fill current line */
        { int d;
          if (n <= 0) {
                n = packed_number(&p);
                gray = ~gray;
          }
          d = g->w-x;
            if (d>n) d=n; /* remaining pixel in current run and current line */
            for (;d>0;d--,x++,n--)
              bits[y*g->w+x] = gray;
        }
        y++;
        while (p.r > 0 && y <g->h) /* copy previous line */
        { int k;
          for (k = 0; k < g->w; k++)
            bits[y*g->w+k] = bits[(y-1)*g->w+k];
          p.r--;
          y++;
        }
    }
}
@

Very small bitmaps can be encoded simply using one bit per pixel.
The |data| array contains a 1 bit per pixel bitmap of height |g->h| and
width |g->w| as a top-down bitmap, where the first bit corresponds to the
top left pixel and the last bit to the bottom right pixel.
The function will produce a bottom-up bitmap with one byte per pixel
to conform to the format that is used by the FreeType library.
We traverse the |data| bits sequentially in top-down order
using a |mask| to get the next bit and incrementing |data| when necessary.
The horizontal position |x| and the vertical position |y| in the
target bitmap start at 0 and |g->h-1|.
@<PK font functions@>=
static void pk_bitmap(Gcache *g, unsigned char *data) {
    unsigned char *bits; /* 1 bit per pixel */
    int x, y; /* position in target bitmap */
    unsigned char mask; /* bitmask for the next bit */
 
    g->bits = bits = (unsigned char *) calloc(g->w * g->h, 1);
    if (bits == NULL) {g->w = g->h = 0; return; } /* out of memory */
    mask=0x80;
    for (y=0; y<g->h; y++)
      for (x=0; x<g->w; x++)
        { if (*data & mask)
            bits[y*g->w+x] = 0x00; /* black */
          else
            bits[y*g->w+x] = 0xFF; /* white */
          mask=mask>>1;
          if (mask==0) { data++; mask=0x80; }
        }
}
@

The next function unpacks the glyphs meta data and calls one of the
unpacking functions just defined.
@<PK font functions@>=

static void pkunpack_glyph(Gcache *g)
{ int i,k;
  unsigned char *data;
  if (g==NULL || g->pk.encoding==NULL) return; /* no glyph, no data */
  g->ff=pk_format;
  if (g->bits!=NULL) return; /* already unpacked */
#if 0  
  DBG(DBGRENDER,"Unpacking glyph %c (0x%x)",g->cc,g->cc);
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
  if ((g->pk.flag>>4)==14) pk_bitmap(g,data+i);
  else pk_runlength(g,data+i);
  nativeSetPK(g);
}
@

We finish with unpacking the whole PK font file.

@<PK font functions@>=

static Gcache *hnew_glyph(Font *pk, unsigned int cc);


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


int unpack_pk_file(Font *pk)
/* scan |pk->data| and extract information. Do not unpack glyphs, these are unpacked on demand. */
{   int i,j;
    unsigned int k;
	unsigned char flag;
	unsigned char *data;
    data=pk->font_data;
    i=0;
	while (i< pk->data_size)
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
        pk->pk.ds=PK_READ_4_BYTE()/(double)(1<<20);
		pk->pk.cs=PK_READ_4_BYTE();
		pk->hpxs=(double)(1<<16)/PK_READ_4_BYTE();
		pk->vpxs=(double)(1<<16)/PK_READ_4_BYTE();
		if (pk->pk.ds!=pk->s) 
		{ double m=pk->s/pk->pk.ds;
		  pk->hpxs*=m;
		  pk->vpxs*=m;
		}
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
		Gcache *g;
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


\subsection{PostScript Type 1, TrueType, and OpenType Fonts}

To unpack these fonts, we use the FreeType library\cite{freetype}.
To use this library, we need a library variable and initialize it.


@<font variables@>=
static FT_Library  ft_library=NULL;
@

@<Initialize the FreeType library@>=
if (ft_library==NULL) 
{ int e=FT_Init_FreeType( &ft_library );
  if (e) QUIT("Unable to initialize the FreeType library");
}
@

Next we need a |FT_Face| variable, which we place in the |FTfont| type.
@<definitions of |PKfont| and |FTfont| types@>=
typedef struct
{ FT_Face face;
} FTfont;
@

The data type for FreeType glyphs is still empty.
@<definitions of |PKfont| and |FTfont| types@>=
typedef struct
{ int dummy;
} FTglyph;
@

We use |FT_New_Memory_Face| to unpack the font and initialize the |Font| structure.
To determine the rendering size, we use the function |font_at_size| to
obtain the size of the font in scaled point and convert it; the variable |f->s| then
contains the size in point as a floating point value.
The resolution used to render the font's glyphs is based on the current setting
of |xdpi| and |ydpi|. If at the later time the resolution changes, for example
because of a scaling operation, it might be necessary to rerender the fonts.
This can be achived by calling |hint_clear_fonts(true)|.

@<FreeType font functions@>=

int unpack_ft_file(Font *f)
{ int e;
  @<Initialize the FreeType library@>@;
  f->hpxs=72.27/xdpi;
  f->vpxs=72.27/ydpi;
  e = FT_New_Memory_Face( ft_library,
                          f->font_data, f->data_size,0,&(f->tt.face));                              
  if (e) return 0;
  @<Select the correct encoding@>@;
  @<Set the required size and transformation@>@;
  f->ff=ft_format;
  return 1;
}
@

A FreeType font file may contain different character encodings,
the most common beeing the Unicode encoding. \TeX's character
encoding is a very special encoding, but fortunately most
of the fonts used with \TeX\ contain the correct character map
marked as |FT_ENCODING_ADOBE_CUSTOM|. We do not check for 
errors, because it is better to use the font with the wrong
character map than to quit the program.

@<Select the correct encoding@>=
 e =FT_Select_Charmap(f->tt.face,FT_ENCODING_ADOBE_CUSTOM); 
 if (e) LOG("Unable to select custom encoding for font %d\n",f->n);    
@

We use the FreeType library to render outline fonts. These fonts can be rendered at any
size and we need to set the correct size. Note that FreeType needs the size in ``big points''
not \TeX\ points.
@<Set the required size and transformation@>=
   e = FT_Set_Char_Size(
            f->tt.face,    /* handle to face object           */
            0,       /* |char_width| in $1/64$th of points  */
            (FT_F26Dot6)(0.5+(f->s*64.0*72.0/72.27)),  /* |char_height| in $1/64$th of points */
            72.27/f->hpxs,     /* horizontal device resolution    */
            72.27/f->vpxs);   /* vertical device resolution      */
  if (e) QUIT("Unable to set FreeType glyph size"); 
  FT_Set_Transform(f->tt.face,0,0);
@

After translating the character code |cc| into the glyph index |i| using
the character map selected above, we render the bitmap using |FT_Load_Glyph|
with the |FT_LOAD_RENDER| flag. Instead of using |FT_LOAD_TARGET_NORMAL|
one could also use |FT_LOAD_TARGET_LIGHT| which will apply hinting only
to horizontal strokes, thereby keeping the character spacing undisturbed 
but using slightly fuzzier bitmaps.
We decrement the |bitmap_top| value by 1, mainly because {\tt dvips} does it,
but comparing pk fonts to FreeType fonts, one can observe that glyphs
in FreeType fonts are positioned slighly higher. Unfortunately the vertical
displacement is magnified for scaled fonts, so subtracting 1 is not enough
in this cases.

@<FreeType font functions@>=
static void ft_unpack_glyph(Font *f, Gcache *g, uint32_t cc)
{ int e,i;

  i = FT_Get_Char_Index( f->tt.face, cc);
  e = FT_Load_Glyph(
            f->tt.face,          /* handle to face object */
            i,   /* glyph index           */
            FT_LOAD_RENDER | FT_LOAD_TARGET_NORMAL );  /* load flags, see below */
  if (e) QUIT("Unable to render FreeType glyph %c (%u)",(char)cc,cc);

  g->w=f->tt.face->glyph->bitmap.width;
  g->h=f->tt.face->glyph->bitmap.rows;
  g->hoff=-f->tt.face->glyph->bitmap_left;
  g->voff=f->tt.face->glyph->bitmap_top-1;
  g->bits=calloc(g->w*g->h, 1);
  if (g->bits==NULL) QUIT("Out of memory for FreeType glyph %c (%u)",(char)cc,cc);
  memcpy(g->bits,f->tt.face->glyph->bitmap.buffer,g->w*g->h);

  g->ff=ft_format;
  nativeSetFreeType(g);
}

@

The function |unpack_ft_file| returns |false| if the font is not a FreeType font.

@<determine the font format and unpack the font@>=
  else if (unpack_ft_file(fp)) 
      fp->ff=ft_format;
  else
      { QUIT("Font format not supported for font %d\n",fp->n);
        free(fp); fp=NULL; 
      }
@



\section{Error Handling}\label{error_section}
There is no good program without good error handling
\index{error message}\index{debugging}.
The file {\tt error.h} is responsible for defining these macros:
\itemize
\item |LOG| to write out messages on a log file or a log window.
The primary use of this macro is for debugging purposes.
\item |MESSAGE| to give information to the user during regular use.
It might for example pop up a window and ask the user to confirm the message.
\item |ERROR| this is used in the |QUIT| macro to notify the user. It is only a local macro. 
\item |QUIT| to inform the user about a problen that can not be fixed.
Unlike the programs Hi\TeX\ or the \.{stretch} and \.{shrink}
programs, the code defined here is normaly only the backend of a much
larger program with a graphical user interface.  These programs should
not terminate unexpectedly with an error message but recover gracefully.
The |QUIT| macro will therefore write the error message into a character array
and invoke a |longjmp| to take an error exit.
\item |HINT_TRY| might be used in the front-end to define a point of recovery;
an |else| clause can then be used to catch and process errors.
\enditemize

The implementation of these macros is highly implementation dependent.
So the following provides some useful defaults and special solutions
for the Windows and the Android system.

\index{LOG+\.{LOG}}
\index{MESSAGE+\.{MESSAGE}}\index{QUIT+\.{QUIT}}
\index{HINT_TRY+\.{HINT_TRY}}
@(error.h@>=
#ifndef _ERROR_H
#define _ERROR_H
#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#define MAX_HINT_ERROR 1024
extern char hint_error_string[MAX_HINT_ERROR];
extern FILE *hlog;
extern void hint_end(void);
extern jmp_buf hint_error_exit;

#ifdef _MSC_VER /* MS Visual Studio C */
#define snprintf(S,N,F,...) _snprintf(S,N,F,__VA_ARGS__)
#ifndef _CONSOLE
#pragma warning(disable : 4996)
extern void hint_message(char *title, char *format, ...);
#define MESSAGE(...)  hint_message("HINT",__VA_ARGS__)

extern int hint_error(char *title, char *msg);
#define ERROR_MESSAGE  hint_error("HINT ERROR",hint_error_string)
#endif
#endif

#ifdef __ANDROID__ /* Android Studio C */
#include <android/log.h>

#define LOG(...)      __android_log_print(ANDROID_LOG_DEBUG,__FILE__,__VA_ARGS__)
#define MESSAGE(...)  __android_log_print(ANDROID_LOG_INFO,__FILE__, __VA_ARGS__)
#define ERROR_MESSAGE __android_log_print(ANDROID_LOG_ERROR,__FILE__,"ERROR: %s\n", hint_error_string)

#endif

#ifndef LOG
#define @[LOG(...)@] @[(fprintf(hlog,__VA_ARGS__),fflush(hlog))@]
#endif

#ifndef MESSAGE
#define MESSAGE(...)  (fprintf(stderr,__VA_ARGS__),fflush(stderr))
#endif

#ifndef ERROR_MESSAGE
#define ERROR_MESSAGE        fprintf(stderr,"ERROR: %s\n",hint_error_string)   
#endif

#ifndef QUIT
#define QUIT(...)    (snprintf(hint_error_string,MAX_HINT_ERROR-1,__VA_ARGS__),\
                     ERROR_MESSAGE,hint_end(),longjmp(hint_error_exit,1))
#endif


#ifndef HINT_TRY
#define HINT_TRY if ((hint_error_string[0]=0,setjmp(hint_error_exit)==0))
#endif

#endif
@


The following variables are required for the error handling: 
@<\HINT\ variables@>=
jmp_buf hint_error_exit;
char hint_error_string[MAX_HINT_ERROR];
@

\section{Testing \HINT}\label{testing}
\subsection{Comparing \HINT\ Output to \TeX\ Output}
One objective of \HINT\ is to make the following diagram commutative:
$$\includefig{diagram}$$
In order to test this property of \TeX, Hi\TeX, and \HINT, we write a command line
version of \HINT, called {\tt hintcl}, 
and run it together with \TeX\ and Hi\TeX\ against a collection
of test files. Since testing the equality of DVI files is not very convenient,
we use |show_box| to print a page description of every page and compare them
against the page descriptions produced by \TeX\  when {\tt tracingoutput} is enabled.
We expect to see no differences.

The testfile also illustrates nicely how to use the different functions of
the \TeX\ library and the \HINT\ library. Here is the main program:

@(main.c@>=
#include "basetypes.h"
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "error.h"
#include "format.h"
#include "get.h"
#include "htex.h"
#include "hint.h"
extern int page_h, page_v;



@<test variables@>@;

@<test functions@>@;

int main(int argc, char *argv[])
{ char *stem_name=NULL, *prog_name=argv[0];
  int stem_length=0;
  bool option_log=false;
  HINT_TRY {
    @<process the command line@>@;
    @<open the log file@>@;
    if(!hint_begin()) goto explain_usage;
    page_h=hhsize;
    page_v=hvsize;
    while (hint_forward())
      @<show the page@>@;
    hint_end();
    @<close the log file@>@;
    return 0;
explain_usage:
    @<explain usage@>@;
    return 1;
  }
  else
    return 1;
}
@
\goodbreak

Processing of the command line is straight forward:

@<process the command line@>=
  debugflags=DBGBASIC;
  if (argc < 2) goto explain_usage;
  argv++; /* skip the program name */
  while (*argv!=NULL)
  { if ((*argv)[0]=='-')
    { char option=(*argv)[1];
      switch(option)
      { case 'l': option_log=true; @+break;
        case 'd': @/
          argv++; if (*argv==NULL) goto explain_usage;
          debugflags=strtol(*argv,NULL,16);
          break;
        default: goto explain_usage;
      }
    }
    else /* the input file name */
    { int path_length=(int)strlen(*argv);
      ALLOCATE(hin_name,path_length+6,char);
      strcpy(hin_name,*argv);
       if (path_length<4 
          || strncmp(hin_name+path_length-4,".hnt",4)!=0)
      { strcat(hin_name,".hnt");
        path_length+=4;
      }
      stem_length=path_length-4;
      ALLOCATE(stem_name,stem_length+6,char);
      strncpy(stem_name,hin_name,stem_length);
      stem_name[stem_length]=0;
      if (*(argv+1)!=NULL) goto explain_usage;
    }
    argv++;
  }
@

The |usage| function explains command line\index{command line} 
parameters and options\index{option}\index{debugging}.
@<explain usage@>=
  fprintf(stderr,
  "Usage: %s [options] filename.hnt\n",prog_name);@/
  fprintf(stderr,
  "Options:\n"@/
  "\t -l     \t redirect stdout to a log file\n");@/
#ifdef DEBUG
fprintf(stderr,"\t -d XXX \t hexadecimal value. OR together these values:\n");@/
fprintf(stderr,"\t\t\t XX=%03X   basic debugging\n", DBGBASIC);@/
fprintf(stderr,"\t\t\t XX=%03X   tag debugging\n", DBGTAGS);@/
fprintf(stdout,"\t\t\t XX=%03X   node debugging\n",DBGNODE);@/
fprintf(stderr,"\t\t\t XX=%03X   definition debugging\n", DBGDEF);@/
fprintf(stderr,"\t\t\t XX=%03X   directory debugging\n", DBGDIR);@/
fprintf(stderr,"\t\t\t XX=%03X   range debugging\n",DBGRANGE);@/
fprintf(stderr,"\t\t\t XX=%03X   compression debugging\n", DBGCOMPRESS);@/
fprintf(stderr,"\t\t\t XX=%03X   buffer debugging\n", DBGBUFFER);@/
fprintf(stdout,"\t\t\t XX=%03X   TeX debugging\n", DBGTEX);@/
fprintf(stdout,"\t\t\t XX=%03X   Page debugging\n", DBGPAGE);@/
fprintf(stdout,"\t\t\t XX=%03X   Font debugging\n", DBGFONT);@/
fprintf(stdout,"\t\t\t XX=%03X   Render debugging\n", DBGRENDER);@/
fprintf(stdout,"\t\t\t XX=%03X   Label debugging\n", DBGLABEL);@/
#endif
@

Processing the command line looks for options and then sets the
input file name\index{file name}.

The log file gets the extension {\tt .hlg}, short for \HINT\ log file.

@<open the log file@> =
#ifdef DEBUG
  if (option_log)
  { 
    strcat(stem_name,".hlg");
    hlog=freopen(stem_name,"w",stdout);
    if (hlog==NULL)
    { fprintf(stderr,"Unable to open logfile %s\n",stem_name);
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

To map and unmap the input file, the function |hint_map| and
|hint_unmap| are needed. Here we use the default implementations.
Depending on the operating system, different implementations
may be supplied.

@<test functions@>=

bool hint_map(void)
{ return hget_map();
}

void hint_unmap(void)
{ hget_unmap(); 
}

@


@<test variables@>=
int page_count=0;
@


@<show the page@>=
{ page_count++;
  fprintf(hlog,"\nCompleted box being shipped out [%d]",page_count);
  show_box(streams[0].p);
  fprintf(hlog,"\n");
}


@
\subsection{Testing the Backwards Reading}
The following code  is similar to the code for the {\tt skip} program described in \cite{MR:format}. It test reading the \HINT\ file from end to start.

@(back.c@>=
#include "basetypes.h"
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "error.h"
#include "format.h"
#include "get.h"
#include "htex.h"
#include "hint.h"

@<test variables@>@;

@<test functions@>@;

int main(int argc, char *argv[])
{ char *stem_name=NULL, *prog_name=argv[0];
  int stem_length=0;
  bool option_log=false;
  HINT_TRY {
    @<process the command line@>@;
    @<open the log file@>@;
    if(!hint_begin()) goto explain_usage;
    hpos=hend;
    while (hint_backward()) continue;
    hint_end();
    @<close the log file@>@;
    return 0;
explain_usage:
    @<explain usage@>@;
    return 1;
  }
  else
    return 1;
}

@

\section{Finding memory leaks}
To find memory leaks, we make a table big enough for all 16 bit values (pointers)
and record a pointer with the allocated size when allocated and remove it when deallocated.
We can then list the currently allocated records.

@<\HINT\ auxiliar functions@>=
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
if (0!=leaks[p])
     fprintf(stderr,"ERROR leak in: p=%d, s in=%d, leaks[p]= %d != 0\n",p,s,leaks[p]);
leaks[p]=s; 
#endif
}

void leak_out(pointer p, int s)
{  
#ifdef DEBUG
   if (s!=leaks[p])
     fprintf(stderr,"ERROR: leak out: p=%d, s out=%d != %d = s in\n",p,s,leaks[p]);
   leaks[p]=0; 
#endif
}

static void list_leaks(void)
{ 
#ifdef DEBUG
  int i;
  for (i=0;i<0x10000;i++)
   if (leaks[i]!=0)
     fprintf(stderr,"ERROR:leak final: p=%d, s=%d\n",i,leaks[i]);
#endif
}
@ 

@<\HINT\ |extern|@>=
extern void leak_in(pointer p, int s);
extern void leak_out(pointer p, int s);
@

\appendix

\section{The Source Files}

\subsection{{\tt hint.h}}

The {\tt hint.h} file lists functions and variables exported from {\tt hint.c}.
Care was taken not to use \TeX's types but the |pointer| and |scaled| type
are still necessary. In case {\tt htex.h} is not included prior (nor after!)
{\tt hint.h}, both types are defined separately. The compiler will produce
error mesages it the definitions in {\tt hint.h} and {\tt htex.h} don't agree.

@(hint.h@>=
#ifndef _HINT_H_
#define _HINT_H_

typedef uint16_t pointer;
typedef int scaled;

@<\HINT\ |extern|@>@;

#endif
@

\subsection{{\tt hint.c}}
@(hint.c@>=
#include "basetypes.h"
#include <string.h>
#include <math.h>
#include <zlib.h>@#
#include "error.h"
#include "format.h"
#include "hrender.h"
#include "get.h"
#include "htex.h"
#include "hint.h"

@<GET macros@>@;
@<TEG macros@>@;

@<\HINT\ types@>@;


@<\HINT\ variables@>@;
@<\HINT\ declarations@>@;
@<\HINT\ auxiliar functions@>@;
@<get functions@>@;
@<teg functions@>@;

@<\HINT\ functions@>@;

@

\subsection{{\tt hrender.h}}
@(hrender.h@>=
#ifndef _HRENDER_H
#define _HRENDER_H
@<render definitions@>@;

extern int page_h, page_v;
extern double xdpi, ydpi;
extern uint64_t hint_blank(void);
extern void     hint_render(void);
extern uint64_t hint_page_get(void);
extern uint64_t hint_page_top(uint64_t h);
extern uint64_t hint_page_middle(uint64_t h);
extern uint64_t hint_page_bottom(uint64_t h);
extern uint64_t hint_page(void);
extern uint64_t hint_page_next(void);
extern uint64_t hint_page_prev(void);
extern uint64_t hint_page_home(void);
extern void hint_resize(int px_h, int px_v, double xdpi, double ydpi);
extern void hint_clear_fonts(bool rm);
extern void hmark_page(void);
extern void hint_set_mark(char *m, int s);
extern bool hint_prev_mark(void);
extern bool hint_next_mark(void);
extern double hint_get_fpos(void);
extern uint64_t hint_set_fpos(double fpos);
extern void hint_render_on(void);
extern void hint_render_off(void);
extern void hint_dark(int dark);
extern void hint_gamma(double gamma);
extern int hint_print_on(int w, int h,  int bpr, int bpp, unsigned char *bits);
extern int hint_print_off(void);
extern int hint_print(unsigned char *bits);
#endif 
@

\subsection{{\tt hrender.c}}
@(hrender.c@>=
#include "basetypes.h"
#include "error.h"
#include "format.h"
#include <string.h>
#include <math.h>
#include "get.h"
#include "hrender.h"
#include "rendernative.h"
#include "htex.h"
#include "hint.h"

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
#include "format.h"

#include "get.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "hfonts.h"
#include "hrender.h"
#include "rendernative.h"

@<font variables@>@;
@<\HINT\ font access functions@>@;
@<auxiliar font functions@>@;

@<FreeType font functions@>@;

@<PK font functions@>@;

@<font functions@>@;

@

\subsection{{\tt rendernative.h}}
This header file is included in the native rendering code and in \HINT's rendering code.
It makes sure that the implementation of the native functions matches the prototypes used in
the \HINT\ rendering functions.
@(rendernative.h@>=
#ifndef _RENDERNATIVE_H
#define _RENDERNATIVE_H

@<native rendering definitions@>@;

#endif 
@

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
