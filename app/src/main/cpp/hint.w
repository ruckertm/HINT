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

\def\lastrevision{${}$Revision: 2064 ${}$}
\def\lastdate{${}$Date: 2020-10-05 18:26:42 +0200 (Mon, 05 Oct 2020) ${}$}

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


\section{Reading Definitions}
This chapter starts with the reimplementation of the parser for
short format \HINT/ files as described in {\it HINT: The File Format}\cite{MR:format}
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
{ @+uint8_t n;
  @<read the start byte |a|@>@;
  n=HGET8;
  if (max_fixed[KIND(a)]>max_default[KIND(a)]) 
      QUIT("Definitions for kind %s not supported", definition_name[KIND(a)]);
    if(n>max_ref[KIND(a)] || n <= max_fixed[KIND(a)]) 
      QUIT("Definition %d for %s out of range [%d - %d]",@|
        n, definition_name[KIND(a)],max_fixed[KIND(a)]+1,max_ref[KIND(a)]);

  if (KIND(a)!=range_kind) REF_RNG(KIND(a),n);
  DBG(DBGTAGS,"Defining %s %d\n", definition_name[KIND(a)],n);
  switch(KIND(a))
  { case language_kind: { char *t;  HGET_STRING(t); break; }
    case font_kind: hget_font_def(a,n); break;
    case int_kind: integer_def[n]=hget_integer_def(a); break;
    case dimen_kind: dimen_def[n]=hget_dimen_def(); break;
    case xdimen_kind: hget_xdimen_def(INFO(a),&(xdimen_def[n])); break;
    case baseline_kind: hget_baseline_def(a,n); break;
    case glue_kind: pointer_def[glue_kind][n]=hget_glue_def(a); break;
    case param_kind:  param_def[n]=hget_param_list(a); break;
    case range_kind: hget_range_def(a,n); break;
    case page_kind: hget_page_def(a,n); break;
    default:  pointer_def[KIND(a)][n]=hget_definition(a); break;
  }
  @<read and check the end byte |z|@>@;
}

pointer hset_glue(glue_t *g)
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


void hget_definition_section(void)
{ DBG(DBGDEF,"Definitions\n");
  hget_section(1);
  DBG(DBGDEF,"Reading list of maximum values\n");
  @<free definitions@>@;
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


@<\HINT/ variables@>=
pointer *pointer_def[32]={NULL};
@


@<\HINT/ declarations@>=
static void hget_font_def(uint8_t a, uint8_t n);
static int32_t hget_integer_def(uint8_t a);
static scaled hget_dimen_def(void);
static pointer hget_glue_def(uint8_t a);
static void hget_baseline_def(uint8_t a, uint8_t n);
static param_def_t *hget_param_list(uint8_t a);
static void hget_range_def(uint8_t a, uint8_t pg);
static void hget_page_def(uint8_t a, uint8_t n);
static void hget_font_metrics();
static pointer hget_definition(uint8_t a);
@


@<allocate definitions@>=
{ kind_t k;
  for (k=0;k<32;k++)
  { if (k==font_kind || k==int_kind|| k==dimen_kind||k==xdimen_kind||
        k==glue_kind||k==baseline_kind|| k==range_kind||k==page_kind||k==param_kind||k==stream_kind)
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
{ @+REF_RNG(int_kind,n);
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
{ @+REF_RNG(dimen_kind,n);
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
static scaled xdimen(xdimen_t *x)
{ return round(x->w+(double)x->h*(double)hhsize+(double)x->v*(double)hvsize);
}
static scaled hget_xdimen_ref(uint8_t n)
{ @+REF_RNG(xdimen_kind,n);
  return  xdimen(xdimen_def+n);
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

static pointer hget_glue_ref(uint8_t n)
{ @+REF_RNG(glue_kind,n);
  return  pointer_def[glue_kind][n];
}

static pointer hget_glue_def(uint8_t a)
{ pointer p;
  if (INFO(a)==b000)
  { p= hget_glue_ref(HGET8);
    add_glue_ref(p);
  }
  else
  { HGET_GLUE(INFO(a)); }
  return p;
}

pointer hget_param_glue(uint8_t n)
{ @+REF_RNG(glue_kind,n);
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
@<\TeX\ |extern|@>=
extern void print_baseline_skip(int i);
extern pointer happend_to_vlist(pointer b);
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

@<\HINT/ declarations@>=
static pointer hprepend_to_vlist(pointer b);
@

The printing routine for whatsit nodes requires a function to print baseline skips. Since
\HINT/ never allocates a baseline skip node, the following function will suffice:
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
the ``at size'' |s| (which might be different from the design size),
the pointer to the font glue |g|,
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
static void hget_font_def(uint8_t a, uint8_t n)
{ char *t;
  font_def_t *f=font_def+n;
  HGET_STRING(t);f->n=strdup(t); 
  DBG(DBGDEF,"Font %d: %s\n", n, t); 
  HGET32(f->s); @+RNG("Font size",f->s,1,0x7fffffff);
  HGET16(f->m); @+RNG("Font metrics",f->m,3,max_section_no);
  HGET16(f->q); @+RNG("Font glyphs",f->q,3,max_section_no);
  f->g=hget_glue_spec(); 
  f->h=hget_hyphen_node();
  DBG(DBGDEF,"Start font parameters\n");
  while (KIND(*hpos)!=font_kind)@/  
  { kind_t k;
    uint8_t n;
    @<read the start byte |a|@>@;
    k=KIND(a);
    n=HGET8;
    DBG(DBGDEF,"Reading font parameter %d: %s\n",n, definition_name[k]);
    if (k!=penalty_kind && k!=kern_kind && k!=ligature_kind && @|
        k!=hyphen_kind && k!=glue_kind && k!=language_kind && @| k!=rule_kind && k!=image_kind)
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

@<\HINT/ auxiliar functions@>=
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
static pointer hget_glue_spec(void);
static pointer hget_hyphen_node(void);
@
and defined
@<\HINT/ |extern|@>=
extern uint16_t hglyph_section(uint8_t f);
extern int32_t font_at_size(uint8_t f);

@

\subsection{Parameter Lists}\label{getparamlist}
There are three types of data that we allow in parameter lists: integers, dimensions,
and glue. Hence, for each parameter, we store the parameter number |n|, its kind |k|, and its value |v|.
Since all values are integer types, a single integer type, large enough for |int32_t|, |scaled| and |pointer| values
is sufficient. 
To form linked lists of parameter definitions, we add a |next| pointer. The variable |param_def| contains the dynamically allocated 
array of lists of parameter definitions.
@<\HINT/ types@>=
typedef struct param_t {
uint8_t n,k;@+
int32_t v;@+
      } param_t;@#

typedef struct param_def_t {
struct param_def_t *next;@+
param_t p; } param_def_t;
@


@<\HINT/ variables@>=
param_def_t **param_def;
@

@<allocate definitions@>=
ALLOCATE(param_def, max_ref[param_kind]+1, param_def_t*);
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
    DBG(DBGTAGS,"Defining %s %d\n", definition_name[KIND(a)],q->n);
    if (KIND(a)==int_kind) q->v=hget_integer_def(a);
    else if (KIND(a)==dimen_kind) q->v=hget_dimen_def();
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
{@+ REF_RNG(param_kind,n);
  return param_def[n];
}
@
We used:

@<\HINT/ declarations@>=
static uint32_t hget_list_size(info_t info);
static void hget_size_boundary(info_t info);
@

Finaly, here are two functions that set and restore global parameters
based on a parameter list.
Parameter lists are actually not nested, because every parameter list records
the differences of the parameter settings compared to the settings in the
definition section. Still there are situations where we want to combine two
parameter settings. The parameters for displayed equations and for line breaking
of a paragraph are disjoint sets. Since displayed equations are embedded in paragraphs,
we want to set and restore the parameter settings for the displayed equation
without affecting the settings for line breaking. To do so, we use the special kind value |0xFF|
to record the boundary between two sets of parameters on the |par_save| stack.

@<\HINT/ auxiliar functions@>=
#define MAX_SAVE 100
#define SAVE_BOUNDARY 0xFF
static param_t par_save[MAX_SAVE];
static int par_save_ptr=0;

static void hset_param(uint8_t k, uint8_t n, int32_t v)
{ param_t *q;
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

void hset_param_list(param_def_t *p)
{ hset_param(SAVE_BOUNDARY,0,0);
  while (p!=NULL)
  { hset_param(p->p.k,p->p.n,p->p.v);
    p=p->next;
  }
}

void hrestore_param_list(void)
{
  while (par_save_ptr>0)
  { param_t *q;
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
@<\TeX\ |extern|@>=
extern void hrestore_param_list(void);
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
  REF_RNG(page_kind,pg);
  REF_RNG(range_kind,n);
  if (INFO(a)&b100) @+
  { @+ if (INFO(a)&b001) HGET32(f); @+else HGET16(f); @+}
  else f=0;
  if (INFO(a)&b010) @+
  { @+if (INFO(a)&b001) HGET32(t); @+else HGET16(t); @+}
  else t=0xFFFFFFFF;
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

@<allocate definitions@>=
ALLOCATE(streams, max_ref[stream_kind]+1, stream_t);
@

@<free definitions@>=
free(streams); streams=NULL;
@


We put a stream definition into avariable of type |stream_def_t|.
@<\HINT/ variables@>=
typedef struct {
  xdimen_t x; /* maximum height */
  int f; /* factor */
  int p, n, r; /* prefered and next stream: split ratio */
  pointer b, a; /* before and after list */
  xdimen_t w; /* width */
  pointer g; /* top skip glue */
  pointer h; /* total height, stretch, and shrink of |a| and |b| */
} stream_def_t;
@

We define a function to read a stream definition 
which we use when reading page templates.
We pass in the pointer to the array of stream definitions
belonging to the current page.

@<\HINT/ auxiliar functions@>=
static void hget_xdimen_def_node(xdimen_t *x);

static bool hget_stream_def(stream_def_t *s)
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
      s->b=hget_list();
      hget_xdimen_def_node(&(s->w));
      s->g=hget_glue_spec();
      s->a=hget_list();
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


@<\HINT/ variables@>=
typedef struct {
  char *n; /* name */
  dimen_t d; /* max page depth */
  pointer g; /* top skip glue */
  uint8_t p; /* priority */
  uint32_t t; /* the template position*/
  xdimen_t v,h; /* the dimensions of the page */
  stream_def_t *s; /* stream definitions */
} page_def_t;
page_def_t *page_def;
page_def_t *cur_page;
@

@<allocate definitions@>=
ALLOCATE(page_def, max_ref[page_kind]+1, page_def_t);
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
ALLOCATE(page_def[0].s, max_ref[stream_kind]+1, stream_def_t);
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

@<\HINT/ auxiliar functions@>=

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
  ALLOCATE(cur_page->s, max_ref[stream_kind]+1, stream_def_t);
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


@<\HINT/ functions@>=
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

@<\HINT/ functions@>=
void hfill_page_template(void)
{ pointer p;
#if 0
     print_str("\npage_head:\n");
     show_box(link(page_head));
     print_str("\nstream 0:\n");
     show_box(streams[0].p);
     print_str("\nstream 1:\n");
     show_box(streams[1].p);
     print_str("\ncontributions:\n");
     show_box(link(contrib_head));
#endif
  if (cur_page->t!=0)
  {
    uint8_t *spos=hpos, *sstart=hstart, *send=hend;
    hget_section(1);
    hpos=hpos+cur_page->t;
    p=hget_list();
    hpos=spos,hstart=sstart,hend=send;
    streams[0].p=vpackage(p,page_v,exactly,page_max_depth);
  }
  else
  houtput_template0();
#if 0
streams[0].p=vpackage(streams[0].p,hvsize,exactly,page_max_depth);
#endif
}
@

\subsection{References}
There are only a few functions that still need to be defined.
@<\HINT/ auxiliar functions@>=
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
{ @+REF_RNG(hyphen_kind,n);
  return copy_node_list(pointer_def[hyphen_kind][n]);
}

static pointer hget_leaders_ref(uint8_t n)
{ @+REF_RNG(leaders_kind,n);
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
{ @+DBG(DBGDIR,"Reading Content Section\n");
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
if (a!=z)
  QUIT(@["Tag mismatch [%s,%d]!=[%s,%d] at 0x%x to " SIZE_F "\n"@],@|
    NAME(a),INFO(a),NAME(z),INFO(z),@|node_pos, hpos-hstart-1);
@
The identifier |node_pos| is defined as a macro; it denotes a field on
the current list record containig the position of the tag of the node
currently processed.


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

@<\HINT/ declarations@>=
static void hget_content(void);
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

@<\HINT/ declarations@>=
static void hteg_content(void);
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

static void hget_xdimen_def(info_t i, xdimen_t *x)
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
static scaled hget_xdimen(info_t i)
{ @+xdimen_t x;
  hget_xdimen_def(i, &x);
  return  xdimen(&x);
 }
 
static scaled hget_xdimen_node(void)
{ @+scaled x=0;
  @<read the start byte |a|@>@;
  if (KIND(a)==xdimen_kind)
    x=hget_xdimen(INFO(a));
  else
     QUIT("Extent expected at 0x%x got %s",node_pos,NAME(a));
  @<read and check the end byte |z|@>@;
  return x;
}

static void hget_xdimen_def_node(xdimen_t *x)
{ @<read the start byte |a|@>@;
  if (KIND(a)==xdimen_kind)
    hget_xdimen_def(INFO(a),x);
  else
     QUIT("Extent expected at 0x%x got %s",node_pos,NAME(a));
  @<read and check the end byte |z|@>@;
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
  return  xdimen(&x);
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

\subsection{Languages}
When rendering \HINT/ files, the language information can be ignored.
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
  else  QUIT("Rule expected at 0x%x got %s",node_pos,NAME(a));
  @<read and check the end byte |z|@>@;
  return q;
}
@

@<\HINT/ auxiliar functions@>=
static pointer hteg_rule_node(void)
{ @+ pointer q=null;
  @<read the end byte |z|@>@;
  if (KIND(z)==rule_kind) { HTEG_RULE(INFO(z));q=p;}
  else  QUIT("Rule expected at 0x%x got %s",node_pos,NAME(z));
  @<read and check the start byte |a|@>@;
  return q;
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

@<\HINT/ auxiliar functions@>=
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
  if (p!=null) return spec2glue(p);
  else return new_glue(zero_glue);
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

static uint32_t hteg_list_size(info_t info)
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

static void hskip_list()
{ if (IS_LIST(*hpos))
  { uint32_t s;
    uint8_t a;
    HGETTAG(a);
    s=hget_list_size(INFO(a)); 
    if (s>0)
      hpos = hpos + (1+ s + 1+ (INFO(a)-1) +1); /*(boundary tag)+s+(boundary tag)+size+tag*/
    else
      hpos = hpos+1;  
  }
}

static void hskip_list_back()
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
  hskip_list_back();
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

static param_def_t *hteg_param_list_node(void)
{ param_def_t *p;
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
list_ptr(p)=hget_list();
@

@<TEG macros@>=
#define @[HTEG_BOX(I)@] \
p=new_null_box();\
list_ptr(p)=hteg_list();\
if ((I)&b100) @/{@+int8_t x=HTEG8;@+ glue_order(p)=x&0xF;\ 
   x=x>>4; glue_sign(p)=(x<0?shrinking:(x>0?stretching:normal));\
   glue_set(p)=hteg_float32(); }\
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
   if (KIND(a)!=hbox_kind) QUIT("Hbox expected at 0x%x got %s",node_pos,NAME(a));
   { @+pointer p;
    HGET_BOX(INFO(a));@/
    @<read and check the end byte |z|@>@;
    return p;
   }
}


pointer hget_vbox_node(void)
{@+
  @<read the start byte |a|@>@;
  if (KIND(a)!=vbox_kind) QUIT("Vbox expected at 0x%x got %s",node_pos,NAME(a));
  {@+pointer p;
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
   { @+pointer p;@+
    HTEG_BOX(INFO(z));@/
    @<read and check the start byte |a|@>@;
    return p;
   }
}
static pointer hteg_vbox_node(void)
{ @+  @<read the end byte |z|@>@;
   if (KIND(z)!=vbox_kind) QUIT("Vbox expected at 0x%x got %s",node_pos,NAME(z));
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
#define @[HGET_PACK(K,I)@] @/\
{ pointer p; @+scaled x, s=0, d; @+ uint8_t m; \
 if ((I)&b100) x= hget_xdimen_node();  else x=hget_xdimen_ref(HGET8);\
 if ((I)&b001) m=additional; else m=exactly; \
 if ((I)&b010) HGET32(s);\
 if (K==vpack_kind) HGET32(d); \
 p=hget_list(); \
 if (K==vpack_kind) p=vpackage(p,x,m,d); else p=hpack(p,x,m);\
 shift_amount(p)=s;\
 happend_to_vlist(p);@+}
@

@<TEG macros@>=
#define @[HTEG_PACK(K,I)@] @/\
{ pointer p;@+ scaled x, s, d; @+ uint8_t m; \
 p=hteg_list();\
 if (K==vpack_kind) HTEG32(d); \
 if ((I)&b010) HTEG32(s);\
 if ((I)&b001) m=additional; else m=exactly; \
 if ((I)&b100) x=hteg_xdimen_node();@+  else x=hget_xdimen_ref(HTEG8);\
 node_pos=hpos-hstart-1;\
 if (K==vpack_kind) p=vpackage(p,x,m,d); else p=hpack(p,x,m);\
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
         (type(p)==glue_node || type(p)==kern_node || type(p)==penalty_node 
         || type(p)==disc_node || type(p)==math_node))
           store_map(p,node_pos,0); /* we store the position of horizontal 
                                      nodes and compute the offset of vertical nodes later */
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
  { uint8_t *list_end=hpos+s;  if (to>list_end) { LOG("Value of to greater than list_end"); to=list_end; }
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
      @<add the node that terminates an incomplete paragraph@>@;
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

\TeX\ normaly ends a paragraph  with a glue node by adding a parfill glue,
and it relies on this paragraph ending because it does not check for the end
of the list while processing character nodes. 
We generate the initial part of a paragraph because we need a page that ends
after that initial part of the paragraph. How to do that nicely is an 
open question. Here, we just add a penalty and a zero glue.

@<add the node that terminates an incomplete paragraph@>=
  if (is_char_node(tail)) tail_append(new_penalty(inf_penalty))@;
  else if (type(tail)!=glue_node) tail_append(new_penalty(inf_penalty))@;
  else
  {@+type(tail)=penalty_node;delete_glue_ref(glue_ptr(tail));
     flush_node_list(leader_ptr(tail));penalty(tail)=inf_penalty;
  }
  tail_append(new_glue(zero_glue));
@


With every paragraph the \HINT/ file specifies a parameter list containing
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

@<\HINT/ variables@>=
static param_def_t *line_break_params=NULL;
@

We provide a functions to set the parameters from this special variable,
thus avoiding the export of the |param_def_t| type.

@<\HINT/ functions@>=
void set_line_break_params(void)
{ hset_param_list(line_break_params);
}
@
@<\TeX\ |extern|@>=
extern void set_line_break_params(void);
@


@<\HINT/ auxiliar functions@>=
pointer hget_paragraph(scaled x, uint32_t offset, param_def_t *q)
{ @+
  pointer p, par_head;
  param_def_t *save_lbp = line_break_params;
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
  param_def_t *q;
  @<read the start byte |a|@>@;
  node_pos=(hpos-hstart)-1;
  if (INFO(a)&b100) x=hget_xdimen_node(); else x=hget_xdimen_ref(HGET8);
  if (INFO(a)&b010) q=hget_param_list_node(); else q=hget_param_list_ref(HGET8);
  hget_paragraph(x,offset,q);
  @<read and check the end byte |z|@>@;
}
@
@<\HINT/ |extern|@>=
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

@<\HINT/ auxiliar functions@>=
void hteg_paragraph(info_t i)
{@+scaled x=0;
  param_def_t *q;
  pointer par_head;
  uint8_t *bs_pos=cur_list.bs_pos; /* the possible baseline skip */ 
  scaled ph=prev_height; 
  uint8_t *list_start, *par_start;
  hskip_list_back();
  list_start=hpos;
  if (INFO(i)&b010) q=hteg_param_list_node(); else q=hget_param_list_ref(HTEG8);
  if (INFO(i)&b100) x=hteg_xdimen_node(); else x=hget_xdimen_ref(HTEG8);
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
oder. The following code, removes the lines of the paragraph from the
current list, reverses the links, and attaches the list again in the new order.
Before callling |hprepend_to_vlist|, we restore the position of the
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
  param_def_t *save_lbp = line_break_params;
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
@<\HINT/ |extern|@>=
extern void hteg_par_node(uint32_t offset);
@


\subsection{Mathematics}

@<GET macros@>=
#define @[HGET_MATH(I)@] \
{@+ param_def_t *q;@+ pointer p=null, a=null;\
if ((I)&b100) q=hget_param_list_node(); else q=hget_param_list_ref(HGET8);\
if ((I)&b010) a=hget_hbox_node(); \
p=hget_list(); \
if ((I)&b001) a=hget_hbox_node();\
hset_param_list(q); hdisplay(p,a,((I)&b010)!=0); hrestore_param_list();\
}
@

@<TEG macros@>=
#define @[HTEG_MATH(I)@] \
{@+ param_def_t *q;@+ pointer p=null, a=null;\
if ((I)&b001) a=hteg_hbox_node();\
p=hteg_list(); \
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

@<\TeX\ |extern|@>=
extern pointer new_math(scaled w, small_number s);

@

\subsection{Adjustments}
Vertical adjustments are inside horizontal lists. They migrate to the enclosing vertical list
where they are unpacked and added after the horizontal material.
Inside a paragraph, this means the adjustment comes after the line that contains the adjustment.
Outside a paragraph, \TeX\ will do the moving and unpacking even before the adjustment has a
chance to get into the \HINT/ file. If we parse paragraphs, we parse in forward direction;
hence, we do not need to parse adjustments in backward direction.

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

\subsection{Tables}
Currently tables are not yet implemented. We skip table and item nodes

@<GET macros@>=
#define @[HGET_TABLE(I)@] \
if(I&b010) /* v */; @+else /* h */;\
if ((I)&b001) /* add */;@+ else /* to */;\
if ((I)&b100) hget_xdimen_node(); else hget_xdimen_ref(HGET8);\
hget_list(); /* tabskip */ \
hget_list(); /* items */
@

@<TEG macros@>=
#define @[HTEG_TABLE(I)@] \
if(I&b010) /* v */; @+else /* h */;\
if ((I)&b001) /* add */;@+ else /* to */;\
hteg_list();  /* items */ \
hteg_list(); /* tabskip */ \
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

case TAG(item_kind,b000):  hget_list();@+@+ break;
case TAG(item_kind,b001):  hget_content();@+break;
case TAG(item_kind,b010):  hget_content();@+break;
case TAG(item_kind,b011):  hget_content();@+break;
case TAG(item_kind,b100):  hget_content();@+break;
case TAG(item_kind,b101):  hget_content();@+break;
case TAG(item_kind,b110):  hget_content();@+break;
case TAG(item_kind,b111):  hget_content();@+(void)HGET8;@+break;
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

case TAG(item_kind,b000):  hteg_list(); @+ break;
case TAG(item_kind,b001):  hteg_content(); @+ break;
case TAG(item_kind,b010):  hteg_content(); @+ break;
case TAG(item_kind,b011):  hteg_content(); @+ break;
case TAG(item_kind,b100):  hteg_content(); @+ break;
case TAG(item_kind,b101):  hteg_content(); @+ break;
case TAG(item_kind,b110):  hteg_content(); @+ break;
case TAG(item_kind,b111):  (void)HTEG8;@+hteg_content(); @+ break;
@
\subsection{Insertions and Stream Content}
Hi\TeX\ generates streams from insertion nodes and here we need to reverse
this process. While \TeX\ assigns insertion numbers starting at 254 and counting
down, \HINT/ assigns stream numbers in the order of appearance starting at 1
and counting up. We partly reverse this process here by mapping the
stream number $n$ to the insertion number $255-n$.

We start with a function to set fields of the insertion node from a
parameter list. There are two cases to distinguish: If the parameter list is
given by a reference to the definition section, we have to increase
the reference counts for glues. If the parameter list is given explicitely,
the newly created glue nodes already have the correct reference count.
The function parameter  |f| is set to |true| in the latter case.

@<\HINT/ auxiliar functions@>=
static void hset_stream_params(pointer p,bool f, param_def_t *q)
{ param_def_t *r;
  pointer s;
  while (q!=null)
  { r=q;
    if (q->p.k==int_kind && q->p.n==floating_penalty_no) float_cost(p)=q->p.v;
    else if (q->p.k==dimen_kind && q->p.n==split_max_depth_no) depth(p)=(scaled)q->p.v;
    else if (q->p.k==glue_kind && q->p.n==split_top_skip_no)  
    { split_top_ptr(p)=(pointer)q->p.v; if (!f) add_glue_ref(split_top_ptr(p)); }
    else QUIT("Unexpected parameter in stream");
    q=q->next;
    if (f) free(r);
  }
  s =vpack(ins_ptr(p),natural);
  height(p)=height(s)+depth(s);
  ins_ptr(p)=list_ptr(s);
  list_ptr(s)=null; flush_node_list(s);
}
@


@<GET macros@>=
#define @[HGET_STREAM(I)@] @/\
{ param_def_t *q;@+  pointer p;\
  p=get_node(ins_node_size); type(p)=ins_node;\
  subtype(p)=HGET8;@+RNG("Stream",subtype(p),1,254); \
  if ((I)&b010) q=hget_param_list_node(); else q=hget_param_list_ref(HGET8); \
  ins_ptr(p)=hget_list(); \
  if ((I)&b010) hset_stream_params(p,true,q); else hset_stream_params(p,false,q);\
  tail_append(p);}
@

@<TEG macros@>=
#define @[HTEG_STREAM(I)@] @/\
{pointer p=get_node(ins_node_size); type(p)=ins_node;\
 ins_ptr(p)=hteg_list();\
 if ((I)&b010) {param_def_t *q=hteg_param_list_node();  hset_stream_params(p,true,q);}\
 else {param_def_t *q=hget_param_list_ref(HTEG8);  hset_stream_params(p,false,q);}\
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
#include "error.h"
#include "hformat.h"

@<\TeX\ |extern|@>@;
#endif
@
It lists |extern| declarations of variables and functions that are extracted from \TeX.
This file is not extracted form \TeX's source code, but when 
it is included in the extracted code, the
compiler will check the decalarations against the implementation.
Further the file will include declarations of a few items that are not
implemented but rather needed by the \TeX\ library.

The additional include file {\tt hformat.h} 
is necessary because it provides a replacement for
\TeX's table of equivalents. 
\TeX's table of equivalents is no longer needed because \HINT/ does not define
new values.
The include file {\tt hformat.h} depends on {\tt error.h}
and provides the usual \HINT/ debugging output macros.  
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
extern void print_int(int n);
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
extern uint16_t nest_ptr;
extern void push_nest(void);
extern void pop_nest(void);
@

\subsection{Line Breaking}

\changestyle{hlinebreak.tex}

Here are the declarations we need to be extern:

@<\TeX\ |extern|@>=
extern scaled *const active_width;   /*distance from first active node to~|cur_p|*/ 
extern void line_break(int final_widow_penalty, pointer par_ptr);
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


Above, we have used several variables and functions
that are yet undefined. Here is a list of all of them
which we will put into a header file to force the compiler
to check for consistent use accross compilation units.

@<\TeX\ |extern|@>=
extern stream_t *streams;
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
extern void hfill_page_template(void);
extern pointer skip(uint8_t n);
extern pointer *box_ptr(uint8_t n);
extern int count(uint8_t n);
extern scaled dimen(uint8_t n);
@

@<\HINT/ functions@>=
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

@<\HINT/ functions@>=
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

When the viewer does not follow the natural sequence of pages but wants to
move to an arbitrary location in the \HINT/ file, the contribution list needs to be flushed. 
The rest is done by |hpage_init|.

@<\HINT/ functions@>=
void hflush_contribution_list(void)
{ if (link(contrib_head)!=null)
  { flush_node_list(link(contrib_head));
    link(contrib_head)=null; tail=contrib_head; 
  }
}
@

@<\HINT/ |extern|@>=
extern void hflush_contribution_list(void);
@

\subsection{Insertions}\label{texinsertions}
To handle insertions in the page building process we extract code from \TeX.

\changestyle{hinsert.tex}

@<\TeX\ |extern|@>=
extern void happend_insertion(pointer p);
extern void hpack_page(void);
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
static scaled page_top_height;
pointer p; /*the node being appended*/ 
pointer @!q,@!r; /*nodes being examined*/ 
int @!b, @!c; /*badness and cost of current page*/ 
int @!pi; /*penalty to be added to the badness*/ 
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

@<\HINT/ variables@>=
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
@<\TeX\ |extern|@>=
extern void freeze_page_specs(small_number s);
@

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

Handling kern nodes is similar.A kern node is a possible page break if the 
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
  DBG(DBGPAGE,"loc_set_prev: %d < %d < %d\n",lo_loc,cur_loc,hi_loc);
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
The \HINT/ library seeks to provide a basis for the implementation of
\HINT/ viewers. For this purpose, it presents a top-level functional
interface which strives to be easy to use and yet exposes the
necessary functionality to allow different viewers on different
systems.

\subsection{Opening and Closing a \HINT/ File}
The first function an application needs to call is |hint_begin| and
the last function is |hint_end|.  The former initialized \TeX's
memory, maps the file, and prepares the system to be ready for all the
functions that follow; the latter will release all resources obtained
when calling one of the top level \HINT/ functions returning the
system to the state it had before calling |hint_begin|.  Since mapping
(and unmapping) the \HINT/ file to memory is system depended, the
functions |hint_begin| and |hint_end| delegate the work to two
functions, |hint_map| and |hint_unmap|, that must be implemented by
the framework using the \HINT/ backend.  If mapping the file fails,
the function |hint_map| should not return; it should leave the
variables |hpos|, |hstart|, and |hend| untouched; and should set
|hbase| to |NULL| and |hbase_size| to zero; otherwise, it should set
these variables to the appropriate values.

@<\HINT/ functions@>=
static bool hint_is_open=false;
void hint_begin(void)
{ if (hint_is_open) 
    hint_end();
  mem_init();
  list_init(); 
  hclear_dir();
  hclear_fonts();
  hint_map();
  hget_banner();
  hcheck_banner("hint");
  hget_directory();
  hget_definition_section();
  hget_content_section();
  leak_clear();
  clear_map();
  hloc_init();
  hint_is_open=true;
}

void hint_end(void)
{ if (!hint_is_open) return;
  hflush_contribution_list(); hpage_init();
  flush_node_list(link(page_head));
  list_leaks();
  hint_unmap();
  hclear_dir();
  hint_is_open=false;
}
@


@<\HINT/ |extern|@>=
extern void hint_begin(void);
extern void hint_end(void);
extern void hint_map(void);
extern uint8_t *hbase;
extern void hint_unmap(void);
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
This function attempts to produce a page in forward mode. If successful it returns |true|
and the caller can set the |forward_mode| variable to |true| to indicate that the current page
was produced in forward mode. If unsuccessfull, it returns false.
First the function |hpage_init| returns the ``old'' current page, stored in |streams[0].p|, to
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
Here it is assumed that the material in the contribution list
belongs to the bottom of the preceeding page and |hpos| will
indicate where parsing should contine when producing the previous page.
In the location cache there are at least two enties: the top of the current page and the top of the next page.

@<\HINT/ |extern|@>=
extern bool hint_forward(void);
extern bool hint_backward(void);
@

When the page builder has reached the end of the \HINT/ file, it must make sure that
the material that still is in the contribution list gets flushed out.
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
The variables |hvsize| and |hhsize| give the vertical and horizontal
size of the main body of text. They are determined by subtracting the
margins from |page_v| and |page_h| as determined by the GUI.

The five functions defined so far constitute a minimal basis for
processing \HINT/ files.  Section~\secref{testing} presents two
programs, used to test the \HINT/ engine, which are implemented with
just these functions.

\subsection{Page Composition}
The page builder of \HINT/, to tell the truth, is not building the
page, it is just assembling the material that should be displayed on
the page: the main body of text and floating material like footnotes
or illustrations.  To make a nice looking page, we need to combine the
material properly and put margins around all that.

The next function computes the margins.
Given the horizontal and vertical dimensions of the page as |page_h|
and |page_v|, it computes the horizontal and vertical dimensions of
the main body of text as well as the offset of its top/left
position. The dimensions are given in scaled points.

@<\HINT/ variables@>=
int page_v, page_h, offset_v, offset_h;
@

If no page template is defined, a default algorithm is used.
The formula use here will result in a 1 inch margin for a 
letter size page---that's the old default of plain \TeX---and decreases the magins for smaller pages
until the margin becomes zero for a page that is merely 1 inch wide.


@<\HINT/ auxiliar functions@>=
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
   }
}
@



@
A more sophisticated page composition can be achived with page templates.
Here is the build-in page template number 0 which attaches the margins just computed
to the box constructed by the page builder.

@<\HINT/ auxiliar functions@>=
static void houtput_template0(void)
{ pointer p,q,r;
 if (streams[0].p==null) return;
  p=vpackage(streams[0].p,hvsize,exactly,page_max_depth);
  r=new_kern(offset_v);
  link(r)=p;
  q=new_null_box();
  type(q)=vlist_node;
  width(q)=width(p)+offset_h;
  height(q)=height(p)+offset_v; depth(q)=depth(p);
  list_ptr(q)=r;
  shift_amount(p)+=offset_h;
  streams[0].p= q;  
 }
@

\subsection{Moving around in the \HINT/ file}
The basic capability of \HINT/ is producing a page that starts at a given position in the
\HINT/ file. The function |hint_page_top| provides this capability.
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
{ if (hbase==NULL) return 0;
  hpos=hstart+(h&0xffffffff);
  if (hpos>=hend)
    return hint_page_bottom(hend-hstart);
  hflush_contribution_list();
  hloc_set(h);
  if (h>0xffffffff)
    hget_par_node(h>>32);
  hint_forward();
#ifdef DEBUG
  show_box(streams[0].p);
#endif
  forward_mode=true;
  backward_mode=false;
  return h;
}
@

Using the previous function, we implement |hint_page| which rerenders the current page.
If |streams[0].p!=null| a valid current page still exists and nothing needs to be done.
If |streams[0].p==null|, we obtain the current pages top position using |hint_page_get|
and pass the position to |hint_page_top|.

@<render functions@>=
uint64_t hint_page_get(void)
{@+
 DBG(DBGPAGE,"page_get: %d : 0x%" PRIx64 "\n",cur_loc,page_loc[cur_loc]);
@/ 
return page_loc[cur_loc];
 }

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

Now let's consider moving to the next page. 
If we produced the current page using |hint_forward|, we can simply call
|hint_forward| again. For this reason we use the variables  |forward_mode| and |backward_mode|
to keep track of the direction.
@<render variables@>=
static bool forward_mode=false, backward_mode=false;
@
If simply moving forward does not work---we might not know the position of the next page,
or are not in forward mode, or we might be at the end of the file---we just rerender the current page.
@<render functions@>=
uint64_t hint_next_page(void)
{ if (hbase==NULL) return 0;
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
different from what \HINT/ will produce in forward mode.
First we check the location cache. If there is an entry for the preceeding page,
we will take the location and produce the page in forward mode, because this way the
reader can get the same page as seen before. If we do not have a cached page location,
we build the page based on its bottom position.
If we are lucky, we are in backward mode. In this case, we do not need to
throw away the information in the contribution list and we call |hint_backward|.
@<render functions@>=
uint64_t hint_prev_page(void)
{ if (hbase==NULL) return 0;
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
If successfull, it will set |cur_loc| to the current page. Finally, we attach the margins, render the page,
and return the new location.
@<render functions@>=
uint64_t  hint_page_bottom(uint64_t h)
{ if (hbase==NULL) return 0;
  hflush_contribution_list(); 
  hpos=hstart+(h&0xffffffff);
  if (h>0xffffffff)
    hteg_par_node(h>>32);
  if (!hint_backward())  return hint_page();
  backward_mode=true;
  forward_mode=false;
  return hint_page_get();
}
@
A function to build a page centered around a given location completes the set of
page building functions.
@<render functions@>=
uint64_t  hint_page_center(uint64_t h)
{ if (hbase==NULL) return hint_blank();
  QUIT("hint_page_center not yet implemented");
}
@


\subsection{Changing the page dimensions}
A central feature of a \HINT/ viewer is its ability to change the dimensions and the
resolution of the displayed pages. To do so the function |hint_resize| is called.
@<render functions@>=
void hint_resize(int px_h, int px_v, double dpi)
{ static int old_px_h=0, old_px_v=0;
  static double old_dpi=0.0;
  nativeSetSize(px_h, px_v, dpi);
  if (old_px_h==px_h && old_px_v==px_v && old_dpi==dpi) return;
  old_px_h=px_h; old_px_v=px_v; old_dpi=dpi;
  hloc_clear();
  hflush_contribution_list(); hpage_init();
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
The \HINT/ file format supports four different types of fonts:
The traditional PK fonts\cite{TR:pkfile} and the more modern
PostScript Type1 fonts\cite{PST1} which are used by many \TeX\ engines, 
TrueType\cite{TTT:TT} fonts, and OpenType fonts\cite{MS:OTF}\cite{ISO:OTF}.
To render the latter, we use the FreeType Library\cite{freetype}
by David Turner, Werner Lemberg, and others.

@<font types@>=
typedef	enum {@+ no_format, pk_format, ft_format@+ } font_format_t;
@


The features of a font are described in a |font_s| structure.  A major
part of the structure is the glyph cache that provides fast access to
the individual glyphs belonging to the font. Further, it includes an
|ff| field containing the font format and a variant part that differs
for the different font formats.


@<font types@>=
@<definitions of |pk_t| and |ft_t| types@>@;

typedef struct font_s {
  unsigned char n; /* the font number */
  unsigned char *font_data; /* pointer to the font data in the HINT file */
  int data_size; /* the size of the font data in byte */
  double s; /* the size in pt */
  double hpxs,vpxs; /* the horizontal and vertical size of one pixel in pt */
  @<the glyph cache@>@;
  font_format_t ff; /* the font format */
  union {@+ pk_t pk; @+ft_t tt;@+  }; /* the font format specific parts */
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
static void hfree_glyph_cache(font_t *f, bool rm);

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
We use |gcache_t| as a shorthand for |struct gcache_s|.

@<font types@>=
typedef struct gcache_s gcache_t;
@
 
To look up the cached glyph data for font |f| and charactercode |cc|, we use the function |g_lookup|.

@<auxiliar font functions@>=
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

@<auxiliar font functions@>=
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


static gcache_t *hnew_glyph(font_t *f, unsigned int cc)
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


static void hfree_glyph_cache(font_t *f, bool rm)
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
#ifdef WIN32
  HBITMAP hbmp;
#endif
#ifdef __ANDROID__
   unsigned int GLtexture;
#endif
  font_format_t ff; 
  union {@+
	  pkg_t pk;@+
	  ftg_t tt;@+
  };
};
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
gcache_t *hget_glyph(font_t *f, unsigned int cc)
{
  gcache_t *g=NULL;
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

@<render macros@>=
#define SP2PT(X) ((X)/(double)(1<<16))
@
@<font functions@>=
void render_char(int x, int y, struct font_s *f, uint32_t cc)

{ double w, h, dx, dy;
  gcache_t *g=hget_glyph(f,cc);
  if (g==NULL) return;

  dx=(double)g->hoff*f->hpxs;
  dy=(double)g->voff*f->vpxs;@/
  w =(double)g->w*f->hpxs;
  h =(double)g->h*f->vpxs;

  nativeGlyph(SP2PT(x)-dx,SP2PT(y)-dy,w,h,g);
}

@
\goodbreak
@<font |extern|@>=
extern void render_char(int x, int y, struct font_s *f, uint32_t cc);
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



\subsection{Pages}
Now at last, we can render pages. Two mutualy recursive procedures,
rendering vertical and horizontal list, will accomplish the
rendering. The functions are more or less modifications of \TeX's
functions that write DVI files. They share a few global static
variables that implement the current state of the renderer: |cur_h|
and |cur_v| contain the current horizontal and vertical position;
|rule_ht|, |rule_dp|, and |rule_wd| contain the height, depth, and
width of a rule that should be output next; |cur_f| and |cur_fp|
contain the current font number and current font pointer.


@<render functions@>=
static scaled cur_h, cur_v;
static scaled rule_ht, rule_dp, rule_wd; 
static int cur_f; 
static struct font_s *cur_fp;

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
#ifdef DEBUG
if(p==0xffff)
  QUIT("Undefined list pointer in hbox 0x%x-> mem[0x%x] -> 0x%x\n",
        this_box,mem[this_box].i,p);
#endif
base_line= cur_v;
left_edge= cur_h;

while(p!=null)
{ reswitch:
#ifdef DEBUG
if(p==0xffff)
        QUIT("Undefined pointer in hlist 0x%x\n",p);
if(link(p)==0xffff)
        QUIT("Undefined link in hlist mem[0x%x]=0x%x\n",p,mem[p].i);
#endif
  if(is_char_node(p))
  { do {
      uint8_t f= font(p);
      uint32_t c= character(p);
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
      render_char(cur_h, cur_v, cur_fp,c);
      cur_h= cur_h+char_width(f)(char_info(f)(c));
#ifdef DEBUG
    if(link(p)==0xffff)
        QUIT("Undefined link in charlist mem[0x%x]=0x%x\n",p,mem[p].i);
#endif
p= link(p);
    } while(!(!is_char_node(p)));
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
   next_p:
#ifdef DEBUG
    if(link(p)==0xffff)
        QUIT("Undefined link in hlist mem[0x%x]=0x%x\n",p,mem[p].i);
#endif        
    p= link(p);
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
  next_p:
#ifdef DEBUG
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

We conclude this section with the function that must be called after the page builder has finished
the page: the |hint_render| function.
@<render functions@>=

void hint_render(void)
{  nativeBlank();
   if (streams==NULL || streams[0].p==null) return;
   cur_h= 0;
   cur_v= height(streams[0].p);
   cur_f=-1;cur_fp=NULL; 
   if(type(streams[0].p)==vlist_node)
     vlist_render(streams[0].p);
   else 
	 hlist_render(streams[0].p);
}
@


@
\section{Native Rendering}\label{native}
The {\tt rendernative.h} header file lists all functions that the native renderer must implement.

To initialize the renderer call |nativeInit|. To release all resorces allocated call |nativeClear|.
@<native rendering definitions@>=
extern void nativeInit(void); 
extern void nativeClear(void);
@


To set the size of the drawing aerea in pixel and the resolution in dots (pixel) per inch call |nativeSetSize|
@<native rendering definitions@>=
extern void nativeSetSize(int px_h, int px_v, double dpi);
@ 

The native renderer may implement an optional procedure to switch between dark and light mode.
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

The first thing we need to know when a section of a \HINT/ file contains a font is
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


The information in the PK file that is specific to a PK font is stored as a |pk_t| type:
@<definitions of |pk_t| and |ft_t| types@>=

typedef struct
{ unsigned char *pk_comment; /* the program that made the pk font */
  unsigned int cs; /* checksum */
  double ds; /* the design size in pt */
  unsigned char id; /* the id currently allways 89 */
} pk_t;
@

For every glyph, there is a |flag| byte in the PK file that tells how the corresponding glyph is
encoded and a pointer to the encoding itself.

@<definitions of format specific types@>=
typedef struct
{ unsigned char flag; /* encoding in the pk file */
  unsigned char *encoding;
} pkg_t;
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
We store this state as a |pk_parse_t|.

@<definitions of format specific types@>=
typedef struct {
int j; /* position of next nybble in data */
int r; /* current repeat count */
int f; /* dynamic f value */
unsigned char *data; /* array of data bytes */
} pk_parse_t;
@
Given a parse state |P|, we read the next nybble
with the following macro:

@<PK font functions@>=
#define read_nybble(P) ((P).j&1?((P).data[(P).j++>>1]&0xF):(((P).data[(P).j++>>1]>>4)&0xF))
@

The pixel data stored in a PK file can be considered as a long sequence
of black and white pixels. Insead of storing individual pixels,
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
static int packed_number(pk_parse_t *p)
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
static void pk_runlength(gcache_t *g, unsigned char *data) {
    pk_parse_t p;
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
static void pk_bitmap(gcache_t *g, unsigned char *data) {
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

static void pkunpack_glyph(gcache_t *g)
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


int unpack_pk_file(font_t *pk)
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

Next we need a |FT_Face| variable, which we place in the |ft_t| type.
@<definitions of |pk_t| and |ft_t| types@>=
typedef struct
{ FT_Face face;
} ft_t;
@

The data type for FreeType glyphs is still empty.
@<definitions of |pk_t| and |ft_t| types@>=
typedef struct
{ int dummy;
} ftg_t;
@

We use |FT_New_Memory_Face| to unpack the font and initialize the |font_t| structure.
To determine the rendering size, we use the function |font_at_size| to
obtain the size of the font in scaled point and convert it; the variable |f->s| 
contains the size in point as a floating point value.
Currently, we set the resolution to 600dpi because we render on a memory bitmap
with 600 dpi resolution before we do a bitblock transfer to the real screen.
This could---or should---perhaps change in the future.


@<FreeType font functions@>=

int unpack_ft_file(font_t *f)
{ int e;
  @<Initialize the FreeType library@>@;
  f->hpxs=f->vpxs=72.27/600.0;
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
static void ft_unpack_glyph(font_t *f, gcache_t *g, uint32_t cc)
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
#define MAX_HERROR 1024
extern char herror_string[MAX_HERROR];
extern FILE *hlog;
extern void hint_end(void);
extern jmp_buf error_exit;

#ifdef _MSC_VER /* MS Visual Studio C */
#define snprintf(S,N,F,...) _snprintf(S,N,F,__VA_ARGS__)
#ifndef _CONSOLE
#pragma warning(disable : 4996)
extern void hmessage(char *title, char *format, ...);
#define MESSAGE(...)  hmessage("HINT",__VA_ARGS__)

extern void herror(char *title, char *msg);
#define ERROR_MESSAGE  herror("HINT ERROR",herror_string)
#endif
#endif

#ifdef __ANDROID__ /* Android Studio C */
#include <android/log.h>

#define LOG(...)      __android_log_print(ANDROID_LOG_DEBUG,__FILE__,__VA_ARGS__)
#define MESSAGE(...)  __android_log_print(ANDROID_LOG_INFO,__FILE__, __VA_ARGS__)
#define ERROR_MESSAGE __android_log_print(ANDROID_LOG_ERROR,__FILE__,"ERROR: %s\n", herror_string)

#endif

#ifndef LOG
#define @[LOG(...)@] @[(fprintf(hlog,__VA_ARGS__),fflush(hlog))@]
#endif

#ifndef MESSAGE
#define MESSAGE(...)  (fprintf(stderr,__VA_ARGS__),fflush(stderr))
#endif

#ifndef ERROR_MESSAGE
#define ERROR_MESSAGE        fprintf(stderr,"ERROR: %s\n",herror_string)   
#endif

#ifndef QUIT
#define QUIT(...)    (snprintf(herror_string,MAX_HERROR-1,__VA_ARGS__),\
                     ERROR_MESSAGE,hint_end(),longjmp(error_exit,1))
#endif


#ifndef HINT_TRY
#define HINT_TRY if ((herror_string[0]=0,setjmp(error_exit)==0))
#endif

#endif
@


The following variables are required for the error handling: 
@<\HINT/ variables@>=
jmp_buf error_exit;
char herror_string[MAX_HERROR];
@

\section{Testing \HINT/}\label{testing}
\subsection{Comparing \HINT/ Output to \TeX\ Output}
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
#include "basetypes.h"
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "error.h"
#include "hformat.h"
#include "hget.h"

#include "texextern.h"
#include "hint.h"
extern int page_h, page_v;



@<test variables@>@;

@<test functions@>@;

int main(int argc, char *argv[])
{ char *stem_name=NULL;
  int stem_length=0;
  bool option_log=false;
  HINT_TRY {
    @<process the command line@>@;
    @<open the log file@>@;
    hint_begin();
    page_v=hvsize=dimen_def[vsize_dimen_no];
    page_h=hhsize=dimen_def[hsize_dimen_no];
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
      ALLOCATE(in_name,path_length+6,char);
      strcpy(in_name,*argv);
       if (path_length<4 
          || strncmp(in_name+path_length-4,".hnt",4)!=0)
      { strcat(in_name,".hnt");
        path_length+=4;
      }
      stem_length=path_length-4;
      ALLOCATE(stem_name,stem_length+6,char);
      strncpy(stem_name,in_name,stem_length);
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
  "Usage: %s [options] filename.hnt\n",argv[0]);@/
  fprintf(stderr,
  "Options:\n"@/
  "\t -l     \t redirect stdout to a log file\n");@/
#ifdef DEBUG
fprintf(stderr,"\t -d XXX \t hexadecimal value. OR together these values:\n");@/
fprintf(stderr,"\t\t\t XX=%03X   basic debugging\n", DBGBASIC);@/
fprintf(stderr,"\t\t\t XX=%03X   tag debugging\n", DBGTAGS);@/
fprintf(stderr,"\t\t\t XX=%03X   definition debugging\n", DBGDEF);@/
fprintf(stderr,"\t\t\t XX=%03X   directory debugging\n", DBGDIR);@/
fprintf(stderr,"\t\t\t XX=%03X   range debugging\n",DBGRANGE);@/
fprintf(stderr,"\t\t\t XX=%03X   compression debugging\n", DBGCOMPRESS);@/
fprintf(stderr,"\t\t\t XX=%03X   buffer debugging\n", DBGBUFFER);@/
#endif
@

Processing the command line looks for options and then sets the
input file name\index{file name}.

The log file gets the extension {\tt .hlg}, short for \HINT/ log file.

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
Under the windows operating system a different implementation
needs to be supplied.

@<test functions@>=
#ifndef _MSC_VER 
void hint_map(void)
{ hget_map(); }

void hint_unmap(void)
{ hget_unmap(); }
#endif
@


@<test variables@>=

char *in_name=NULL;
int page_count=0;
@


@<show the page@>=
{ page_count++;
  print_str("\nCompleted box being shipped out [");
  print_int(page_count);
  print_str("]");
  show_box(streams[0].p);
  print_str("\n");
}


@
\subsection{Testing the Backwards Reading}
The following code  is similar to the code for the {\tt skip} program described in \cite{MR:format}. It test reading the \HINT/ file from end to start.

@(back.c@>=
#include "basetypes.h"
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "texextern.h"
#include "error.h"
#include "hformat.h"
#include "hget.h"

#include "hint.h"

@<test variables@>@;

@<test functions@>@;

int main(int argc, char *argv[])
{ char *stem_name=NULL;
  int stem_length=0;
  bool option_log=false;
  HINT_TRY {
    @<process the command line@>@;
    @<open the log file@>@;
    hint_begin();
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

extern void hget_definition_section(void);
extern void hget_content_section(void);

extern void clear_map(void); /*clear the location table*/
extern void hpage_init(void);
extern bool hbuild_page_up(void); /*append contributions to the current page*/ 


@<\HINT/ |extern|@>@;

#endif
@

\subsection{{\tt hint.c}}
@(hint.c@>=
#include "basetypes.h"
#include <string.h>
#include <math.h>
#include <zlib.h>@#
#include "error.h"
#include "hformat.h"

#include "texextern.h"
#include "hint.h"
#include "hrender.h"

#include "texdefs.h"
#include "hget.h"

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
extern void     hint_render(void);
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
#include "hget.h"
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
#include "hget.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "hfonts.h"
#include "hrender.h"
#include "rendernative.h"

@<font variables@>@;

@<auxiliar font functions@>@;

@<FreeType font functions@>@;

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
