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



\null

\font\largetitlefont=cmssbx10 scaled\magstep4
\font\Largetitlefont=cmssbx10 at 40pt
\font\hugetitlefont=cmssbx10 at 48pt
\font\smalltitlefontit=cmbxti10 scaled\magstep3
\font\smalltitlefont=cmssbx10 scaled\magstep3

%halftitle
\def\raggedleft{\leftskip=0pt plus 5em\parfillskip=0pt
\spaceskip=.3333em \xspaceskip=0.5em \emergencystretch=1em\relax
\hyphenpenalty=1000\exhyphenpenalty=1000\pretolerance=10000\linepenalty=5000
}
\hbox{}
\vskip 0pt plus 1fill
{ \baselineskip=60pt
  \hugetitlefont\hfill HINT\par
  \Largetitlefont\raggedleft The Viewer\par
}
\vskip 0pt plus 2fill
\eject
% verso of half title
\titletrue
\null
\vfill
\eject

% title
\titletrue
\hbox{}
\vskip 1in
{
  \baselineskip=1cm\parindent=0pt
  \leftline{\largetitlefont\raggedright HINT}
  \vskip 0.5in
  \leftline{\smalltitlefont The Viewer} 
  \vskip 1.5in
  \rightline{\it F\"ur Beatriz \hskip 2cm}
  \vfill
  \raggedright\baselineskip=12pt
  {\bf MARTIN RUCKERT} \ {\it Munich University of Applied Sciences}\par
  \bigskip
  \leftline{First edition}
  \bigskip
%  \leftline{\bf Eigendruck im Selbstverlag}
%  \bigskip
}
\eject

% verso of title
% copyright page (ii)
\titletrue
\begingroup
\figrm
\parindent=0pt
%\null
{\raggedright\advance\rightskip 3.5pc
The author has taken care in the preparation of this book,
but makes no expressed or implied warranty of any kind and assumes no
responsibility for errors or omissions. No liability is assumed for
incidental or consequential damages in connection with or arising out
of the use of the information or programs contained herein.

\bigskip
{\figtt\obeylines\obeyspaces\baselineskip=11pt
Ruckert, Martin.
  HINT
  Includes index.
  ISBN 1-548-58234-4
}
\bigskip

{\raggedright\advance\rightskip 3.5pc
\def\:{\discretionary{}{}{}}
Internet page  {\tt http:\://hint.\:userweb.\:mwn.\:de/\:hint/\:format.html}
may contain current information about this book, downloadable software,
and news. 

\vfill
Copyright $\copyright$ 2019 by Martin Ruckert
\smallskip
All rights reserved.
Printed using CreateSpace.
This publication is protected by copyright, and permission must be
obtained prior to any prohibited reproduction, storage in
a~retrieval system, or transmission in any form or by any means, electronic,
mechanical, photocopying, recording, or likewise. 
To obtain permission to use material from this work, please submit a written 
request to Martin Ruckert, 
Hochschule M\"unchen, 
Fakult\"at f\"ur Informatik und Mathematik,
Lothstrasse 64, 
80335 M\"unchen, 
Germany.
\medskip
{\tt ruckert\:@@cs.hm.edu}
\medskip
ISBN-10: 0-000-00000-0

ISBN-13: 000-0000000000
\medskip
First printing, August 2019\par
\medskip
Last commit: \input lastcommit.tex
\par
}
}
\endgroup


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
The first part reads a \HINT\ file\cite{MR:format} and reconstructs
\TeX's contribution list\cite{Knuth:tex}.  The routines found in this
part translate data structures found in a \HINT\ file into \TeX's
internal data structures.  Some data structures, notably paragraph
nodes, will require substantial processing before moving the results
to the contribution list; for example, paragraph nodes are transformed
into a sequence of lines by using \TeX's line breaking routine.

The line breaking routine is an example of code that belongs to the
second part of this program: routines that are taken from
\TeX\cite{Knuth:tex} with little or no modification.  These routines
are extracted using a change file (see~\cite{Knuth:cweb}) from a
translation of \TeX's sources to {\tt
cweb}\cite{MR:webtocweb}\cite{MR:web2w}.  For debugging purposes, even
\TeX's output routines can be used to produce normal {\tt dvi} files
as output. In general, however, the output is generated by the
routines of part three.

The third and final part of this program consists of routines that
display ``the page'', a data structure produced by \TeX's page builder
(or variations of it), on a computer screen. The core of part three is
written in OpenGL and can be used with slight modifications on a
variety of operating systems.
Further routines let the user manipulate what is shown on the screen;
These routines are highly system dependent. They need to
be rewritten for different operating systems.

Part One

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
the parameter number is less or equal to |max_ref| which is set in
|hget_max_definitions|.


\subsection{Definitions}
The following function reads a single definition and stores it.
By default, we store definitions as pointers to \TeX's data structures.

@<get functions@>=
static void hget_def_node(void)
{ Kind k;
  int n;
  @<read the start byte |a|@>@;
  k=KIND(a);
  if (k==unknown_kind && INFO(a)==b100)
  {  hget_unknown_def();
     @<read and check the end byte |z|@>@;
     return;
  }
  if (k==label_kind && (INFO(a)&b001)) HGET16(n);
  else n=HGET8;
  if (max_fixed[k]>max_default[k]) 
  { MESSAGE("Definitions for kind %s not supported\n", definition_name[k]);
    while (hpos<hend && *hpos!=a) hpos++;
    @<read and check the end byte |z|@>@;
    return;
  }
  if (k!=range_kind) REF_RNG(k,n);
  DBG(DBGTAGS,"Defining %s %d\n", definition_name[KIND(a)],n);
  switch(KIND(a))
  { case language_kind: { char *t;  HGET_STRING(t); (void)t; break; }
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
    case color_kind: hget_color_def(INFO(a),n); break;
    default:  pointer_def[KIND(a)][n]=hget_definition(a); break;
  }
  if(n>max_ref[k] || n <= max_fixed[k]) 
    QUIT("Definition %d for %s out of range [%d - %d]",@|
         n, definition_name[k],max_fixed[k]+1,max_ref[k]);
  @<read and check the end byte |z|@>@;
}

static pointer hset_glue(Glue *g)
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

static void hset_default_definitions(void)
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
  hset_default_colors();
}

static void free_definitions(void)
{ @<free definitions@>@;
}

static void hget_definition_section(void)
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
static pointer *pointer_def[32]={NULL};
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
static void hget_unknown_def(void);
static void hget_font_metrics(void);
static void hget_color_def(uint8_t a, int n);
static pointer hget_definition(uint8_t a);
static int hget_label_ref(void);
static int hget_link_color(void);
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
static int32_t *integer_def;
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
static scaled *dimen_def;
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
static Xdimen *xdimen_def;
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
\HINT\ never allocates an extended dimension node, the following function will suffice:
|void print_xdimen(pointer p){}|.
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
static BaselineSkip *baseline_def=NULL;
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

static void hget_baseline_ref(uint8_t n)
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
\TeX\ gets ist knowlegde about fonts from font metric files. \HINT\
will not need all of that information, but for now, the complete \TeX\
font metric file is included inside the \HINT\ file.
The procedure |read_font_info| of \TeX\ is modified to load
only those parts that are needed.

When rendering fonts, we will need to find the section containing the
actual glyphs. For OpenType and TrueType fonts,
there might be no font metric file. For these files the metric
data is extracted from the same font file that contains the glyphs
using the FreeType library.

We store the font name |n|, the section number for the font metrics
|m| and the glyphs |q|, the ``at size'' |s| (which might be different
from the design size), the pointer to the font glue |g|, the pointer
to the font hyphen |h|, and the font parameters |p|.

@<\HINT\ private types@>=
typedef struct {
char *n;
uint16_t m,q;
scaled s;
pointer g;
pointer h;
pointer p[MAX_FONT_PARAMS+1];
} FontDef;
@

@<\HINT\ variables@>=
static FontDef *font_def;
@

@<allocate definitions@>=
ALLOCATE(font_def, max_ref[font_kind]+1, FontDef);
@

@<free definitions@>=
free(font_def); font_def=NULL;
@

The function |hget_font_def| is called with two different values of
|INFO(a)|: If the value is |b000|, there is also a section for the
\.{.TFM} file; otherwise, the font metrics need to be extracted from
the same section as the glyphs. In the latter case, we set the section
number |m| for the font metrics and the |width_base| for the font to
zero.  Either value can be tested to see whether traditional font
metrcis are available or not.
Freetype font faces were loaded in the \HINT\ viewer only when
the first glyph from the font face was needed by the renderer.
This is now possibly too late because the font metrics are
needed much earlier.
Because the viewer only displays a single page, we still will
do ``on demand'' loading of font file information.
After a font face is loaded the |font_face| array contains
a valid |FT_Face| pointer. 



@<\HINT\ auxiliar functions@>=
static void hget_font_def(uint8_t a, uint8_t i)
{ char *t;
  FontDef *f=font_def+i;
  HGET_STRING(t);f->n=strdup(t); 
  DBG(DBGDEF,"Font %d: %s\n", i, t); 
  HGET32(f->s); @+RNG("Font size",f->s,1,0x7fffffff);
  if (INFO(a)==b000)
  {  HGET16(f->m); @+RNG("Font metrics",f->m,3,max_section_no);}
  else width_base[i]=f->m=0;
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

After reading the definition section, we need to move the information
from the \TeX\ font metric files included into \TeX's data
structures. Here we only load the font metric information from \.{.TFM}
files, while the font faces from extended fonts are loaded on demand.
If the ``on demand'' loading works, this should also be done for
the \.{.TFM} files.

@<\HINT\ auxiliar functions@>=
static void hget_font_metrics(void)
{ int f;
  font_ptr=max_ref[font_kind];
  for (f=0; f<=max_ref[font_kind]; f++)
    if (font_def[f].m!=0)
    { hget_section(font_def[f].m);
      read_font_info(f,font_def[f].n,font_def[f].s);
    }
    else
      font_size[f]=font_def[f].s;
}
@

The above code sets the |font_ptr| variable needed by \TeX.

@<\HINT\ |static|@>=
static uint8_t font_ptr;
@


We export the font section and at-size using two functions
to be used in {\tt hfonts.c}, as well as the |font_nom| for
use in printing font names.

@<render functions@>=
static uint16_t hglyph_section(uint8_t f)
{   return font_def[f].q;
}

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
static ParamDef **param_def;
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

static ParamDef *hget_param_list_node(void)
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

static void hset_param_list(ParamDef *p)
{ hset_param(SAVE_BOUNDARY,0,0);
  while (p!=NULL)
  { hset_param(p->p.k,p->p.n,p->p.v);
    p=p->next;
  }
}

static void hrestore_param_list(void)
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
@<\HINT\ |static|@>=
static void hrestore_param_list(void);
@

\subsection{Page Ranges}
@<\HINT\ variables@>=
typedef struct {
 uint8_t pg;
 uint32_t f,t;
} RangeDef;
static RangeDef *range_def;
@
@<allocate definitions@>=
ALLOCATE(range_def, max_ref[range_kind]+1, RangeDef);
max_range=-1;
@

@<free definitions@>=
free(range_def); range_def=NULL;
@

@<\HINT\ auxiliar functions@>=
static void hget_range_def(uint8_t a, uint8_t pg)
{ uint32_t f, t;
  max_range++;
  REF_RNG(page_kind,pg);
  REF_RNG(range_kind,max_range);
  if (INFO(a)&b100) @+
  { @+ if (INFO(a)&b001) HGET32(f); @+else HGET16(f); @+}
  else f=0;
  if (INFO(a)&b010) @+
  { @+if (INFO(a)&b001) HGET32(t); @+else HGET16(t); @+}
  else t=HINT_NO_POS;
  range_def[max_range].pg=pg;
  range_def[max_range].f=f;
  range_def[max_range].t=t;
  DBG(DBGRANGE,"Range *%d from 0x%x\n",pg,f);
  DBG(DBGRANGE,"Range *%d to 0x%x\n",pg,t);
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

@<\HINT\ |static|@>=
typedef struct {
pointer p, t; /* head and tail */
} Stream;
static Stream *streams;
@

@<\HINT\ variables@>=
static Stream *streams;
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
static PageDef *page_def;
static PageDef *cur_page;
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
static void hfill_page_template(void)
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

@<\HINT\ |static|@>=
static void hfill_page_template(void);
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
static int outline_no=-1;
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
static void hget_outline_or_label_def(Info i, int n)
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
   pos=((uint64_t)labels[n].pos0<<32);
   /* offsets still dont work in all cases and need fixing */
#endif
}
@


The function |hlist_to_string| is defined in section~\secref{listtraversal}.

\subsection{Colors}
To store colors, we use the same data type that is used for the
|color_defaults| and give it the name |ColorSet|.

@<\HINT\ |static|@>=
typedef uint32_t ColorSet[12];
extern ColorSet color_defaults[];
@



We define a dynamic array for color sets based on |max_ref[color_kind]|.

@<\HINT\ variables@>=
static ColorSet *color_def=color_defaults;
static bool first_color=true;
@

@<allocate definitions@>=
if (color_def!=color_defaults) { free(color_def); color_def=color_defaults; }
ALLOCATE(color_def,max_ref[color_kind]+1, ColorSet);
first_color=true;
@

@<free definitions@>=
if (color_def!=color_defaults) { free(color_def); color_def=color_defaults; }
@

Now we can copy the color defaults to |color_def|.

@<\HINT\ auxiliar functions@>=
static void hset_default_colors(void)
{ int i;
  for (i=0; i<=MAX_COLOR_DEFAULT; i++)
    memcpy(color_def+i,color_defaults+i,sizeof(ColorSet));
}
@

From now on the colors in |color_def[0]| serve as default colors.
Whenever a page is rendered, the rendering starts with the colors from
|color_def[0]| and the background of the entire page is painted
with the  background color for normal text in |color_def[0]|.

All color definitions, including  |color_def[0]|, can be changed
by the definitions in  the \HINT\ file. If you change |color_def[0]|
it must come first.

@<get functions@>=
static void hget_color_def(uint8_t a, int i)
{@+int j,k;
  if (INFO(a)!=b000)
    QUIT("Color Definition %d with Info value %d!=000",i,INFO(a));
  k=HGET8;
  if (k!=6) 
    QUIT("Definition %d of color set needs 6 color pairs %d given\n",i,k);
  if (i==0 && !first_color)
    QUIT("Definition of color 0 must come first");
  first_color=false;  
  for (j=0;j<6*2;j++)
    HGET32(color_def[i][j]);
}
@

Because glyphs, rules, and images must be rendered on top of the
background, we have to consider the order in which we render things.
If we render glyphs first and then render the background as a
rectangle with an opaque color over it, the glyphes will just
disappear under the background.  There are several ways to approach
this problem.  Let us discuss the alternatives for the case of single
colored word text in an horizontal box. The other cases are similar.

Any color change in an horizontal list is restricted to that list.  It
is caused by a |color_node|, a |link_node|, an |end_color_node|, or an
|end_link_node|. We exemplify the effects of such a color change
considering a |color_node|.

When the renderer encounters the |color node| it knows the height and
depth of the enclosing box, which is equal to the height and depth of
the background change, but the width of the background change, which
is equal to the distance between the first |color_node| and the next
|color_node| is still unknown.  It is possible to traverse the node
list up to the next |color_node| and compute its position using the
same method that the renderer uses to compute all positions. Computing
the width of glue nodes requires the use of the |glue_ratio| of the
enclosing box; all other width-calculations are quite simple. While
computing the distance is not difficult, it is an unwanted overhead,
and other more performant alternatives exist.

For example, it is possible to cache the information about which
glyphs and rules to write at which locations in an array until the
next |color_node| is found. Then we can first render the background
and after that pass the whole array in a single write operation to the
graphic card. Writing a large chunk of information to the graphic card
is usually faster than writing many small chunks of data.

To summarize:
The first method requires traversing the node list twice.  The code is
lengthy but it is just a simplified variation of the normal rendering
procedure.  The runtime overhead is small but not zero.  The second
method would even improve the performance, but requires a more complex
code in the native rendering engine.  Unless one is willing to
implement the changes in the native renderer because of its better
performance, the first method is probably the better alternative.

% Using the depth buffer on the graphics card does not work,
% because it would descard entire fragments and not just pixels.
% Using the stencil buffer will not work because there is no
% blending of forground and background alongh the outline of the glyph. 

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

static pointer hget_color_ref(uint8_t n) 
{@+pointer p;
  p=get_node(color_node_size);
  type(p)=whatsit_node;
  if (n==0xFF) subtype(p)=end_color_node;
  else
  { subtype(p)=color_node; REF_RNG(color_kind,n);
  }
  color_ref(p)=n;
  return p;
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

\subsection{Unknown Extensions}
@<get functions@>=
static void hget_unknown_def(void)
{ Tag t; signed char i;
  t=HGET8;
  i=HGET8;
  if (i==0)
    QUIT("Zero not allowed for unknown node size at 0x%x\n",(uint32_t)(hpos-hstart-2));
  if (hnode_size[t]==0)
  { hnode_size[t]=i;
    DBG(DBGTAGS,"Defining node size %d,%d for tag 0x%x (%s)\n",NODE_HEAD(i),NODE_TAIL(i),t,content_name[KIND(t)]);
  }
}
@

The |hget_unknown| funktion tries to process a unknown node with the help of
an entry in the |hnode_size| array. The definition section can be used to provide
this extra information. If successful the function returns 1 else 0.

@<get functions@>=
int hget_unknown(Tag a)
{ DBG(DBGTAGS,"Trying unknown tag 0x%x at 0x%x\n",a,(uint32_t)(hpos-hstart-1));
  hpos--;
  hff_hpos();
  hpos--;
  return 1;
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
if (a!=z) tag_mismatch(a,z,node_pos, (uint32_t)(hpos-hstart-1));
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

For nodes that can cause a page break, the function |store_map| is called to
store their position in the input file, which later may become the start of the
next page. This is also done for box and rule nodes because in rare cases,
for example if the page is filled with insertions, the topskip
glue inserted before them might cause a page break. The page builder will then
associate the position of the box or rule node with the start of the new page.

@<\HINT\ functions@>=

static void hget_node(uint8_t a)
{ @+switch (a)@/
  {@+ 
    @<cases to get content@>@;@t\1@>@/
    default:
      if (!hget_unknown(a))
        TAGERR(a);
      break;@t\2@>@/
  }
}

static void hget_content(void)
{ @+@<read the start byte |a|@>@;
  node_pos=(hpos-hstart)-1;
  hget_node(a);
  @<read and check the end byte |z|@>@;
  if (nest_ptr==0 && tail!=head &&
       (type(tail)==penalty_node || type(tail)==glue_node || type(tail)==kern_node ||
        type(tail)==hlist_node || type(tail)==vlist_node || type(tail)==rule_node) 
     )
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

@<\HINT\ |static|@>=
static void hget_content(void);
@

Now let's turn to the backwards version.
The primitive reading operations are taken from {\tt get.h}.

The next macros read and check start and end byte.

@<read the end byte |z|@>=
  uint8_t a,z; /* the start and the end byte*/
  z=HTEG8;DBGTAG(z,hpos);
@

@<read and check the start byte |a|@>=
  a=HTEG8;DBGTAG(a,hpos);
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

static void hteg_content(void)
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

@<\HINT\ |static|@>=
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
static scaled hteg_xdimen(uint8_t a)
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

static scaled hteg_xdimen_node(void)
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
static pointer hget_rule_node(void)
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

static pointer hteg_list_pointer(void)
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
static pointer hget_hbox_node(void)
{ @+  @<read the start byte |a|@>@;
   if (KIND(a)!=hbox_kind)  tag_expected(TAG(hbox_kind,0),a,node_pos);
   { @+pointer p;
    HGET_BOX(INFO(a));@/
    @<read and check the end byte |z|@>@;
    return p;
   }
}


static pointer hget_vbox_node(void)
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

static void vset(pointer p, uint8_t sto, scaled st,
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
{ pointer p;@+ scaled x, s=0, d; @+ uint8_t m; \
 p=hteg_list_pointer();\
 if ((I)&b100) x=hteg_xdimen_node();@+  else x=hget_xdimen_ref(HTEG8);\
 if (K==vpack_kind) HTEG32(d); \
 if ((I)&b010) HTEG32(s);\
 if ((I)&b001) m=additional; else m=exactly; \
 node_pos=hpos-hstart-1;\
 if (K==vpack_kind)  { if (d<=MAX_DIMEN && d>=-MAX_DIMEN) p=vpackage(p,x,m,d); else p=vtop(p,x,m,d); } \
 else p=hpack(p,x,m);\
 shift_amount(p)=s;\
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
#if 0
static pointer hteg_disc_node(void)
{  @+@<read the end byte |z|@>@;
   if (KIND(z)!=disc_kind || INFO(z)==b000) 
     tag_expected(TAG(disc_kind,1),z,node_pos); 
   { @+
   HTEG_DISC(INFO(z));
   @<read and check the start byte |a|@>@;
   return p;
   }
}
#endif
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
@<\HINT\ |static|@>=
static void hprune_unwanted_nodes(void);
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
  int par_color,par_label_ref;
  @<prepare for reading the paragraph list@>@;
  @<check for a color change in the initial section of the paragraph@>@;
  hpos=from; to=list_end;
  @<read the paragraph list@>@;
  if (link(head)!=null && !is_char_node(link(head)))
  { if (type(link(head))==disc_node)
      transplant_post_break_list();
    else
      hprune_unwanted_nodes(); 
  }
  @<finalize reading the  the paragraph list@>@;
  @<add a color change node if necessary@>@;
  return par_ptr;
}
@

In the initial paragraph there might be a color change, which might affect
the color in the remaining paragraph. So we scan for it and set |par_color|
acoordingly.

@<check for a color change in the initial section of the paragraph@>=
par_color=-1; par_label_ref=-1;
while (hpos<from)
{ if (hpos[0]==TAG(color_kind,b000)) par_color=hpos[1];
  else if (KIND(hpos[0])==link_kind)
  { if (INFO(hpos[0]) & b010)
    { par_label_ref=hget_label_ref();par_color=hget_link_color(); }
    else
    { par_color=hget_link_color();
      par_label_ref=-1;
    }
  }
  if (par_color==0xFF) par_color=-1;
  hff_hpos();
}
@

If a color change was found we add a copy to the begin of the remaining
paragraph.

@<add a color change node if necessary@>=
if (par_ptr!=null)
{@+if (par_label_ref>=0)
  {@+pointer p;
    p=get_node(link_node_size);  type(p)=whatsit_node;
    subtype(p)=start_link_node; label_ref(as_label(p))=par_label_ref;
    link(p)=par_ptr;
    if (par_color>=0) color_ref(as_color(p))=par_color;
    else color_ref(as_color(p))=0xFF; /* this should not happen */
    par_ptr=p;
  }
  else if (par_color>=0)
  {@+pointer p;
    p=get_node(color_node_size);
    type(p)=whatsit_node; subtype(p)=color_node;
    color_ref(p)=par_color;
    link(p)=par_ptr;
    par_ptr=p;
  }
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
static void set_line_break_params(void)
{ hset_param_list(line_break_params);
}
@
@<\HINT\ |static|@>=
static void set_line_break_params(void);
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
@

@<render functions@>=
static void hget_par_node(uint32_t offset)
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
@<\HINT\ |static|@>=
#if 0
static void hget_par_node(uint32_t offset);
#endif
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
static void hteg_paragraph(Info i)
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



@<render functions@>=
static void hteg_par_node(uint32_t offset)
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
if (w==0 || h==0) {MESSAGE("Incomplete dimensions in image %d",image_no(p));\
  if (w!=0) h=w; else if (h!=0) w=h; else w=h=100*ONE; }\
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
if (w==0 || h==0) {MESSAGE("Incomplete dimensions in image %d",image_no(p));\
  if (w!=0) h=w; else if (h!=0) w=h; else w=h=100*ONE; }\
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

\subsection{Colors}
@<cases to get content@>=
case TAG(color_kind,b000): @+ tail_append(hget_color_ref(HGET8)); @+break;
@
@<cases to teg content@>=
case TAG(color_kind,b000): @+ tail_append(hget_color_ref(HTEG8)); @+break;
@

\subsection{Links}

Here are the cases for link nodes:

@<cases to get content@>=
case TAG(link_kind,b000): @+ HGET_LINK(b000); break;
case TAG(link_kind,b001): @+ HGET_LINK(b001); break;
case TAG(link_kind,b010): @+ HGET_LINK(b010); break;
case TAG(link_kind,b011): @+ HGET_LINK(b011); break;
case TAG(link_kind,b100): @+ HGET_LINK(b100); break;
case TAG(link_kind,b101): @+ HGET_LINK(b101); break;
case TAG(link_kind,b110): @+ HGET_LINK(b110); break;
case TAG(link_kind,b111): @+ HGET_LINK(b111); break;
@
@<cases to teg content@>=
case TAG(link_kind,b000): @+ HTEG_LINK(b000); break;
case TAG(link_kind,b001): @+ HTEG_LINK(b001); break;
case TAG(link_kind,b010): @+ HTEG_LINK(b010); break;
case TAG(link_kind,b011): @+ HTEG_LINK(b011); break;
case TAG(link_kind,b100): @+ HTEG_LINK(b100); break;
case TAG(link_kind,b101): @+ HTEG_LINK(b101); break;
case TAG(link_kind,b110): @+ HTEG_LINK(b110); break;
case TAG(link_kind,b111): @+ HTEG_LINK(b111); break;
@

We use the following macros. Note that |label_has_name(p)| is
set to zero, because the label names are not stored as token lists.

@<GET macros@>=
#define @[HGET_LINK(I)@] @/\
{ @+pointer p;\
  p=get_node(link_node_size);  type(p)=whatsit_node;\
  if (I&b010) subtype(p)=start_link_node; else subtype(p)=end_link_node;\
  if (I&b001) HGET16(label_ref(as_label(p)));@+ else label_ref(as_label(p))=HGET8; \
  if (I&b100) color_ref(as_color(p))=HGET8; else color_ref(as_color(p))=(I&b010)?1:0xFF;\
  RNG("label",label_ref(as_label(p)),0,max_ref[label_kind]);\
  if (color_ref(as_color(p))!=0xFF)\
    RNG("label color",color_ref(as_color(p)),0,max_ref[color_kind]);\
  tail_append(p);}
@

@<TEG macros@>=
#define @[HTEG_LINK(I)@] @/\
{ @+pointer p;\
  p=get_node(link_node_size);  type(p)=whatsit_node;\
  if (I&b010) subtype(p)=start_link_node; else subtype(p)=end_link_node;\
  if (I&b100) color_ref(as_color(p))=HTEG8; else color_ref(as_color(p))=(I&b010)?1:0xFF;\
  if (I&b001) HTEG16(label_ref(as_label(p)));@+ else label_ref(as_label(p))=HTEG8; \
  RNG("label",label_ref(as_label(p)),0,max_ref[label_kind]);\
  if (color_ref(as_color(p))!=0xFF)\
    RNG("label color",color_ref(as_color(p)),0,max_ref[color_kind]);\
  tail_append(p);}
@

When links are lengthy texts, they may be broken accross line and
page boundaries.
In this case, the node starting the link needs to be replicated on
the start of the new line or page.
For this case we have the following function
reading the reference to the label from a link node at |hpos|.

@<\HINT\ auxiliar functions@>=
static int hget_label_ref(void)
{ if (INFO(hpos[0])&b001) return (hpos[1]<<8)+hpos[2];
  else return hpos[1];
}
static int hget_link_color(void)
{ if (INFO(hpos[0]&b100))
  { if (INFO(hpos[0]&b001)) return hpos[3];
    else return hpos[2];
  }
  else
  { if (INFO(hpos[0]&b010)) return 1; else return 0xFF; }
}
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
%\changestyle{texdef.tex}

\subsection{Parameters}

\TeX's table of equivalents is no longer needed since \HINT\ will never change
any assignments. The functions of \TeX, however, use several of \TeX's variables
as parameters. These are now found as part of \HINT's definitions.
We modify the corresponding macros accordingly.

%\changestyle{params.tex}

The variables containing the parameter definitions are declared |extern|.

@<\HINT\ |static|@>=
static pointer*pointer_def[32];
static scaled*dimen_def;
static int32_t*integer_def;
@


\subsection{Diagnostic Output}

%\changestyle{hprint.tex}

\subsection{Arithmetic}

%\changestyle{harith.tex}

\subsection{Memory}
\TeX's main data structure is the |mem| array. In this section, we will extract the
|mem| variable and the routines to allocate and deallocate nodes.
 
%\changestyle{hmem.tex}

\subsection{Boxes and Friends}

In this section we will export the functions that create structures in |mem|: boxes, rules, ligatures and more such things.

%\changestyle{hbox.tex}

\subsection{Lists and Nesting}
Most of \TeX's operations are performed on the ``current list''. 
When \HINT\ reads nodes from the input file, it will follow this principle and add nodes
to the current list. Lists can be nested and the list on the outermost level is the contribution list which we encounter again in section~\secref{texbuildpage}. 
Now lets consider the modifications to \TeX's list handling.
 
%\changestyle{hlist.tex}

\subsection{Line Breaking}

%\changestyle{hlinebreak.tex}

\subsection{Displayed Formulas}
%\changestyle{hdisplay.tex}

\subsection{Packing Boxes}
%\changestyle{hpack.tex}

\subsection{Page Building}\label{texbuildpage}

%\changestyle{hbuildpage.tex}


Above, we have used several variables and functions
that are yet undefined. Here is a list of all of them
which we will put into a header file to force the compiler
to check for consistent use accross compilation units.

@<\HINT\ |static|@>=
static Stream *streams;
static bool flush_pages(uint32_t pos); 
static pointer skip(uint8_t n);
static pointer *box_ptr(uint8_t n);
static int count(uint8_t n);
static scaled dimen(uint8_t n);
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
static void hpage_init(void)
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

@<\HINT\ |static|@>=
static void hpage_init(void);
@

When the viewer does not follow the natural sequence of pages but wants to
move to an arbitrary location in the \HINT\ file, the contribution list needs to be flushed. 
The rest is done by |hpage_init|.

@<\HINT\ functions@>=
static void hflush_contribution_list(void)
{ if (link(contrib_head)!=null)
  { flush_node_list(link(contrib_head));
    link(contrib_head)=null; tail=contrib_head; 
  }
}
@

@<\HINT\ |static|@>=
static void hflush_contribution_list(void);
@

\subsection{Insertions}\label{texinsertions}
To handle insertions in the page building process we extract code from \TeX.

%\changestyle{hinsert.tex}

\subsection{Font Metric Files}
In section~\secref{fonts} we mentioned the \TeX\ function  |read_font_info|. 
Now we see how to extract and modify this function from the \TeX\ sources.

%\changestyle{hfont.tex}


Part Two
\begingroup
% This program is copyright (C) 1982 by D. E. Knuth; all rights are reserved.
% Unlimited copying and redistribution of this file are permitted as long
% as this file is not modified. Modifications are permitted, but only if
% the resulting file is not named tex.web. (The WEB system provides
% for alterations via an auxiliary file; the master file should stay intact.)
% See Appendix H of the WEB manual for hints on how to install this program.
% And see Appendix A of the TRIP manual for details about how to validate it.

% TeX is a trademark of the American Mathematical Society.
% METAFONT is a trademark of Addison-Wesley Publishing Company.

% Version 0 was released in September 1982 after it passed a variety of tests.
% Version 1 was released in November 1983 after thorough testing.
% Version 1.1 fixed ``disappearing font identifiers'' et alia (July 1984).
% Version 1.2 allowed `0' in response to an error, et alia (October 1984).
% Version 1.3 made memory allocation more flexible and local (November 1984).
% Version 1.4 fixed accents right after line breaks, et alia (April 1985).
% Version 1.5 fixed \the\toks after other expansion in \edefs (August 1985).
% Version 2.0 (almost identical to 1.5) corresponds to "Volume B" (April 1986).
% Version 2.1 corrected anomalies in discretionary breaks (January 1987).
% Version 2.2 corrected "(Please type...)" with null \endlinechar (April 1987).
% Version 2.3 avoided incomplete page in premature termination (August 1987).
% Version 2.4 fixed \noaligned rules in indented displays (August 1987).
% Version 2.5 saved cur_order when expanding tokens (September 1987).
% Version 2.6 added 10sp slop when shipping leaders (November 1987).
% Version 2.7 improved rounding of negative-width characters (November 1987).
% Version 2.8 fixed weird bug if no \patterns are used (December 1987).
% Version 2.9 made \csname\endcsname's "relax" local (December 1987).
% Version 2.91 fixed \outer\def\a0{}\a\a bug (April 1988).
% Version 2.92 fixed \patterns, also file names with complex macros (May 1988).
% Version 2.93 fixed negative halving in allocator when mem_min<0 (June 1988).
% Version 2.94 kept open_log_file from calling fatal_error (November 1988).
% Version 2.95 solved that problem a better way (December 1988).
% Version 2.96 corrected bug in "Infinite shrinkage" recovery (January 1989).
% Version 2.97 corrected blunder in creating 2.95 (February 1989).
% Version 2.98 omitted save_for_after at outer level (March 1989).
% Version 2.99 caught $$\begingroup\halign..$$ (June 1989).
% Version 2.991 caught .5\ifdim.6... (June 1989).
% Version 2.992 introduced major changes for 8-bit extensions (September 1989).
% Version 2.993 fixed a save_stack synchronization bug et alia (December 1989).
% Version 3.0 fixed unusual displays; was more \output robust (March 1990).
% Version 3.1 fixed nullfont, disabled \write{\the\prevgraf} (September 1990).
% Version 3.14 fixed unprintable font names and corrected typos (March 1991).
% Version 3.141 more of same; reconstituted ligatures better (March 1992).
% Version 3.1415 preserved nonexplicit kerns, tidied up (February 1993).
% Version 3.14159 allowed fontmemsize to change; bulletproofing (March 1995).
% Version 3.141592 fixed \xleaders, glueset, weird alignments (December 2002).
% Version 3.1415926 was a general cleanup with minor fixes (February 2008).
% Version 3.14159265 was similar (January 2014).
% Version 3.141592653 was similar but more extensive (January 2021).

% A reward of $327.68 will be paid to the first finder of any remaining bug.

% Although considerable effort has been expended to make the TeX program
% correct and reliable, no warranty is implied; the author disclaims any
% obligation or liability for damages, including but not limited to
% special, indirect, or consequential damages arising out of or in
% connection with the use or performance of this software. This work has
% been a ``labor of love'' and the author hopes that users enjoy it.

% Here is TeX material that gets inserted after \input webmac
\def\hang{\hangindent 3em\noindent\ignorespaces}
\def\hangg#1 {\hang\hbox{#1 }}
\def\textindent#1{\hangindent2.5em\noindent\hbox to2.5em{\hss#1 }\ignorespaces}
\font\ninerm=cmr9
\let\mc=\ninerm % medium caps for names like SAIL
\def\PASCAL{Pascal}
\def\ph{\hbox{Pascal-H}}
\def\pct!{{\char`\%}} % percent sign in ordinary text
\font\logo=logo10 % font used for the METAFONT logo
\def\MF{{\logo META}\-{\logo FONT}}
\def\<#1>{$\langle#1\rangle$}
\def\section{\mathhexbox278}

\def\(#1){} % this is used to make section names sort themselves better
\def\9#1{} % this is used for sort keys in the index via @@:sort key}{entry@@>

\let\@@=\relax % we want to be able to \write a \?

\def\title{\TeX82}
\def\topofcontents{\hsize 5.5in
  \vglue 0pt plus 1fil minus 1.5in
  \def\@@##1]{\hbox to 1in{\hfil##1.\ }}
  }
\def\botofcontents{\vskip 0pt plus 1fil minus 1.5in}
\pageno=3
\def\glob{13} % this should be the section number of "<Global...>"
\def\gglob{20, 26} % this should be the next two sections of "<Global...>"

\def\.#1{\leavevmode\hbox{\tentex % typewriter type for strings
  \let\\=\BS % backslash in a string
  \let\'=\RQ % right quote in a string
  \let\`=\LQ % left quote in a string
  \let\{=\LB % left brace in a string
  \let\}=\RB % right brace in a string
  \let\~=\TL % tilde in a string
  \let\ =\SP % space in a string
  \let\_=\UL % underline in a string
  \let\&=\AM % ampersand in a string
  #1\kern.05em}}
\def\&#1{\leavevmode\hbox{\bf\def\_{\UL}%
  #1\/\kern.05em}} % boldface type for reserved words
\def\\#1{\leavevmode\hbox{\it\def\_{\UL}%
  #1\/\kern.05em}} % italic type for identifiers
\def\vb#1{{\rm #1}}
\def\^{\ifmmode\mathchar"222 \else\char`^ \fi} % pointer or hat
\def\LQ{{\tt\char'22}} % left quote in a string
\def\RQ{{\tt\char'23}} % right quote in a string
\def\UL{{\tt\char`\_}} % underline character in a C identifier
\def\dotdot{\mathrel{.\,.}} % double dot, used only in math mode
@s dotdot TeX
@s alpha_file int
@s byte_file int
@s word_file int
@* Introduction.
This is \TeX, a document compiler intended to produce typesetting of high
quality.
The \PASCAL\ program that follows is the definition of \TeX82, a standard
@:PASCAL}{\PASCAL@>
@!@:TeX82}{\TeX82@>
version of \TeX\ that is designed to be highly portable so that identical output
will be obtainable on a great variety of computers.

The main purpose of the following program is to explain the algorithms of \TeX\
as clearly as possible. As a result, the program will not necessarily be very
efficient when a particular \PASCAL\ compiler has translated it into a
particular machine language. However, the program has been written so that it
can be tuned to run efficiently in a wide variety of operating environments
by making comparatively few changes. Such flexibility is possible because
the documentation that follows is written in the \.{WEB} language, which is
at a higher level than \PASCAL; the preprocessing step that converts \.{WEB}
to \PASCAL\ is able to introduce most of the necessary refinements.
Semi-automatic translation to other languages is also feasible, because the
program below does not make extensive use of features that are peculiar to
\PASCAL.

A large piece of software like \TeX\ has inherent complexity that cannot
be reduced below a certain level of difficulty, although each individual
part is fairly simple by itself. The \.{WEB} language is intended to make
the algorithms as readable as possible, by reflecting the way the
individual program pieces fit together and by providing the
cross-references that connect different parts. Detailed comments about
what is going on, and about why things were done in certain ways, have
been liberally sprinkled throughout the program.  These comments explain
features of the implementation, but they rarely attempt to explain the
\TeX\ language itself, since the reader is supposed to be familiar with
{\sl The \TeX book}.
@.WEB@>
@:TeXbook}{\sl The \TeX book@>

@ The present implementation has a long ancestry, beginning in the summer
of~1977, when Michael~F. Plass and Frank~M. Liang designed and coded
a prototype
@^Plass, Michael Frederick@>
@^Liang, Franklin Mark@>
@^Knuth, Donald Ervin@>
based on some specifications that the author had made in May of that year.
This original proto\TeX\ included macro definitions and elementary
manipulations on boxes and glue, but it did not have line-breaking,
page-breaking, mathematical formulas, alignment routines, error recovery,
or the present semantic nest; furthermore,
it used character lists instead of token lists, so that a control sequence
like \.{\\halign} was represented by a list of seven characters. A
complete version of \TeX\ was designed and coded by the author in late
1977 and early 1978; that program, like its prototype, was written in the
{\mc SAIL} language, for which an excellent debugging system was
available. Preliminary plans to convert the {\mc SAIL} code into a form
somewhat like the present ``web'' were developed by Luis Trabb~Pardo and
@^Trabb Pardo, Luis Isidoro@>
the author at the beginning of 1979, and a complete implementation was
created by Ignacio~A. Zabala in 1979 and 1980. The \TeX82 program, which
@^Zabala Salelles, Ignacio Andr\'es@>
was written by the author during the latter part of 1981 and the early
part of 1982, also incorporates ideas from the 1979 implementation of
@^Guibas, Leonidas Ioannis@>
@^Sedgewick, Robert@>
@^Wyatt, Douglas Kirk@>
\TeX\ in {\mc MESA} that was written by Leonidas Guibas, Robert Sedgewick,
and Douglas Wyatt at the Xerox Palo Alto Research Center.  Several hundred
refinements were introduced into \TeX82 based on the experiences gained with
the original implementations, so that essentially every part of the system
has been substantially improved. After the appearance of ``Version 0'' in
September 1982, this program benefited greatly from the comments of
many other people, notably David~R. Fuchs and Howard~W. Trickey.
A final revision in September 1989 extended the input character set to
eight-bit codes and introduced the ability to hyphenate words from
different languages, based on some ideas of Michael~J. Ferguson.
@^Fuchs, David Raymond@>
@^Trickey, Howard Wellington@>
@^Ferguson, Michael John@>

No doubt there still is plenty of room for improvement, but the author
is firmly committed to keeping \TeX82 ``frozen'' from now on; stability
and reliability are to be its main virtues.

On the other hand, the \.{WEB} description can be extended without changing
the core of \TeX82 itself, and the program has been designed so that such
extensions are not extremely difficult to make.
The |banner| string defined here should be changed whenever \TeX\
undergoes any modifications, so that it will be clear which version of
\TeX\ might be the guilty party when a problem arises.
@^extensions to \TeX@>
@^system dependencies@>

If this program is changed, the resulting system should not be called
`\TeX'; the official name `\TeX' by itself is reserved
for software systems that are fully compatible with each other.
A special test suite called the ``\.{TRIP} test'' is available for
helping to determine whether a particular implementation deserves to be
known as `\TeX' [cf.~Stanford Computer Science report CS1027,
November 1984].

@d Xbanner "This is TeX, Version 3.141592653 (HINT)" /*printed when \TeX\ starts*/

@ Different \PASCAL s have slightly different conventions, and the present
@!@:PASCAL H}{\ph@>
program expresses \TeX\ in terms of the \PASCAL\ that was
available to the author in 1982. Constructions that apply to
this particular compiler, which we shall call \ph, should help the
reader see how to make an appropriate interface for other systems
if necessary. (\ph\ is Charles Hedrick's modification of a compiler
@^Hedrick, Charles Locke@>
for the DECsystem-10 that was originally developed at the University of
Hamburg; cf.\ {\sl Software---Practice and Experience \bf6} (1976),
29--42. The \TeX\ program below is intended to be adaptable, without
extensive changes, to most other versions of \PASCAL, so it does not fully
use the admirable features of \ph. Indeed, a conscious effort has been
made here to avoid using several idiosyncratic features of standard
\PASCAL\ itself, so that most of the code can be translated mechanically
into other high-level languages. For example, the `\&{with}' and `\\{new}'
features are not used, nor are pointer types, set types, or enumerated
scalar types; there are no `\&{var}' parameters, except in the case of files;
there are no tag fields on variant records; there are no assignments
|double=int|; no procedures are declared local to other procedures.)

The portions of this program that involve system-dependent code, where
changes might be necessary because of differences between \PASCAL\ compilers
and/or differences between
operating systems, can be identified by looking at the sections whose
numbers are listed under `system dependencies' in the index. Furthermore,
the index entries for `dirty \PASCAL' list all places where the restrictions
of \PASCAL\ have not been followed perfectly, for one reason or another.
@!@^system dependencies@>
@!@^dirty \PASCAL@>

Incidentally, \PASCAL's standard |round| function can be problematical,
because it disagrees with the IEEE floating-point standard.
Many implementors have
therefore chosen to substitute their own home-grown rounding procedure.

@ The following is an outline of the program, whose
components will be filled in later, using the conventions of \.{WEB}.
@.WEB@>
For example, the portion of the program called `\X\glob:Global
variables\X' below will be replaced by a sequence of variable declarations
that starts in $\section\glob$ of this documentation. In this way, we are able
to define each individual global variable when we are prepared to
understand what it means; we do not have to define all of the globals at
once.  Cross references in $\section\glob$, where it says ``See also
sections \gglob, \dots,'' also make it possible to look at the set of
all global variables, if desired.  Similar remarks apply to the other
portions of the program.

@<\TeX\ functions@>=
@<Selected global variables@>@;
@#
#ifdef HINTTYPE
@<Basic printing procedures@>@;
#endif
@<Basic error handling procedures@>@;

@ The overall \TeX\ program begins with the heading just shown, after which
comes a bunch of procedure declarations and function declarations.
Finally we will get to the main program, which begins with the
comment `|start_here|'. If you want to skip down to the
main program now, you can look up `|start_here|' in the index.
But the author suggests that the best way to understand this program
is to follow pretty much the order of \TeX's components as they appear in the
\.{WEB} description you are now reading, since the present ordering is
intended to combine the advantages of the ``bottom up'' and ``top down''
approaches to the problem of understanding a somewhat complicated system.


@ Some of the code below is intended to be used only when diagnosing the
strange behavior that sometimes occurs when \TeX\ is being installed or
when system wizards are fooling around with \TeX\ without quite knowing
what they are doing. Such code will not normally be compiled; it is
delimited by the codewords `$|@t\#\&{ifdef} \.{DEBUG}@>|\ldots|@t\#\&{endif}@>|$', with apologies
to people who wish to preserve the purity of English.

Similarly, there is some conditional code delimited by
`$|@t\#\&{ifdef} \.{STAT}@>|\ldots|@t\#\&{endif}@>|$' that is intended for use when statistics are to be
kept about \TeX's memory usage.  The |@t\#\&{ifdef} \.{STAT}@>| $\ldots$ |@t\#\&{endif}@>| code also
implements diagnostic information for \.{\\tracingparagraphs},
\.{\\tracingpages}, and \.{\\tracingrestores}.
@^debugging@>

@ Most of the external declarations needed are included using standard
header files.

@s uint8_t int
@s int16_t int
@s uint16_t int
@s int32_t int
@s uint32_t int
@s halfword int
@s nonnegative_integer int
@s small_number int
@s glue_ratio double
@s in TeX
@s line normal
@s to   do


@ Further it is necessary to define some build in primitives of
\PASCAL\ that are otherwise not available in~\CEE/.
@:PASCAL H}{\ph@>

@d odd(X)       ((X)&1)
@d abs(X)       ((X)>-(X)?(X):-(X))
@d round(X)     ((int)((X)>=0.0?floor((X)+0.5):ceil((X)-0.5)))

@ The following parameters can be changed at compile time to extend or
reduce \TeX's capacity. They may have different values in \.{INITEX} and
in production versions of \TeX.
@.INITEX@>
@^system dependencies@>

@<Constants...@>=
@!mem_max=65534, /*greatest index in \TeX's internal |mem| array;
  must be strictly less than |max_halfword|;
  must be equal to |mem_top| in \.{INITEX}, otherwise | >= mem_top|*/
@!mem_min=0, /*smallest index in \TeX's internal |mem| array;
  must be |min_halfword| or more;
  must be equal to |mem_bot| in \.{INITEX}, otherwise | <= mem_bot|*/
@!buf_size=2048, /*maximum number of characters simultaneously present in
  current lines of open files and in control sequences between
  \.{\\csname} and \.{\\endcsname}; must not exceed |max_halfword|*/
@!error_line=72, /*width of context lines on terminal error messages*/
@!half_error_line=42, /*width of first lines of contexts in terminal
  error messages; should be between 30 and |error_line-15|*/
@!max_print_line=79, /*width of longest text lines output; should be at least 60*/
@!stack_size=200, /*maximum number of simultaneous input sources*/
@!max_in_open=6, /*maximum number of input files and error insertions that
  can be going on simultaneously*/
@!font_max=255, /*maximum internal font number; must not exceed |max_quarterword|
  and must be at most |font_base+256|*/
@!font_mem_size=65535, /*number of words of |font_info| for all fonts*/
@!param_size=60, /*maximum number of simultaneous macro parameters*/
@!nest_size=400, /*maximum number of semantic levels simultaneously active*/
@!max_strings=30000, /*maximum number of strings; must not exceed |max_halfword|*/
@!string_vacancies=75000, /*the minimum number of characters that should be
  available for the user's control sequences and font names,
  after \TeX's own error messages are stored*/
@!pool_size=400000, /*maximum number of characters in strings, including all
  error messages and help texts, and the names of all fonts and
  control sequences; must exceed |string_vacancies| by the total
  length of \TeX's own strings, which is currently about 23000*/
@!save_size=600, /*space for saving values outside of current group; must be
  at most |max_halfword|*/
@!trie_size=65534, /*space for hyphenation patterns; should be larger for
  \.{INITEX} than it is in production versions of \TeX*/
@!trie_op_size=65534, /*space for ``opcodes'' in the hyphenation patterns*/
@!dvi_buf_size=8, /*size of the output buffer; must be a multiple of 8*/
@!file_name_size=1024, /*file names shouldn't be longer than this*/
@!empty_string=256 /*the empty string follows after 256 characters*/

@ Like the preceding parameters, the following quantities can be changed
at compile time to extend or reduce \TeX's capacity. But if they are changed,
it is necessary to rerun the initialization program \.{INITEX}
@.INITEX@>
to generate new tables for the production \TeX\ program.
One can't simply make helter-skelter changes to the following constants,
since certain rather complex initialization
numbers are computed from them. They are defined here using
\.{WEB} macros, instead of being put into \PASCAL's |const| list, in order to
emphasize this distinction.

@d mem_bot 0 /*smallest index in the |mem| array dumped by \.{INITEX};
  must not be less than |mem_min|*/
@d mem_top mem_max /*largest index in the |mem| array dumped by \.{INITEX};
  must be substantially larger than |mem_bot|
  and not greater than |mem_max|*/
@d font_base 0 /*smallest internal font number; must not be less
  than |min_quarterword|*/
@^system dependencies@>

@ Labels are given symbolic names by the following definitions, so that
occasional |goto| statements will be meaningful. We insert the label
`|end|' just before the `\ignorespaces|} |\unskip' of a procedure in
which we have used the `|goto end|' statement defined below; the label
`|restart|' is occasionally used at the very beginning of a procedure; and
the label `|reswitch|' is occasionally used just prior to a |case|
statement in which some cases change the conditions and we wish to branch
to the newly applicable case.  Loops that are set up with the |loop|
construction defined below are commonly exited by going to `|done|' or to
`|found|' or to `|not_found|', and they are sometimes repeated by going to
`|resume|'.  If two or more parts of a subroutine start differently but
end up the same, the shared code may be gathered together at
`|common_ending|'.

Incidentally, this program never declares a label that isn't actually used,
because some fussy \PASCAL\ compilers will complain about redundant labels.

@ Here are some macros for common programming idioms.

@d incr(A) A=A+1 /*increase a variable by unity*/
@d decr(A) A=A-1 /*decrease a variable by unity*/
@d negate(A) A=-A /*change the sign of a variable*/
@d loop @+while (true) @+ /*repeat over and over until a |goto| happens*/
@f loop else
   /*\.{WEB}'s |else| acts like `\ignorespaces|while true do|\unskip'*/
@d do_nothing  /*empty statement*/
@d empty 0 /*symbolic name for a null constant*/

@* The character set.
In order to make \TeX\ readily portable to a wide variety of
computers, all of its input text is converted to an internal eight-bit
code that includes standard ASCII, the ``American Standard Code for
Information Interchange.''  This conversion is done immediately when each
character is read in. Conversely, characters are converted from ASCII to
the user's external representation just before they are output to a
text file.

Such an internal code is relevant to users of \TeX\ primarily because it
governs the positions of characters in the fonts. For example, the
character `\.A' has ASCII code $65=0101$, and when \TeX\ typesets
this letter it specifies character number 65 in the current font.
If that font actually has `\.A' in a different position, \TeX\ doesn't
know what the real position is; the program that does the actual printing from
\TeX's device-independent files is responsible for converting from ASCII to
a particular font encoding.
@^ASCII code@>

\TeX's internal code also defines the value of constants
that begin with a reverse apostrophe; and it provides an index to the
\.{\\catcode}, \.{\\mathcode}, \.{\\uccode}, \.{\\lccode}, and \.{\\delcode}
tables.

@ Characters of text that have been converted to \TeX's internal form
are said to be of type |ASCII_code|, which is a subrange of the integers.

@<Types...@>=
typedef uint8_t ASCII_code; /*eight-bit numbers*/

@ The original \PASCAL\ compiler was designed in the late 60s, when six-bit
character sets were common, so it did not make provision for lowercase
letters. Nowadays, of course, we need to deal with both capital and small
letters in a convenient way, especially in a program for typesetting;
so the present specification of \TeX\ has been written under the assumption
that the \PASCAL\ compiler and run-time system permit the use of text files
with more than 64 distinguishable characters. More precisely, we assume that
the character set contains at least the letters and symbols associated
with ASCII codes 040 through 0176; all of these characters are now
available on most computer terminals.

Since we are dealing with more characters than were present in the first
\PASCAL\ compilers, we have to decide what to call the associated data
type. Some \PASCAL s use the original name |unsigned char| for the
characters in text files, even though there now are more than 64 such
characters, while other \PASCAL s consider |unsigned char| to be a 64-element
subrange of a larger data type that has some other name.

In order to accommodate this difference, we shall use the name |text_char|
to stand for the data type of the characters that are converted to and
from |ASCII_code| when they are input and output. We shall also assume
that |text_char| consists of the elements |chr(first_text_char)| through
|chr(last_text_char)|, inclusive. The following definitions should be
adjusted if necessary.
@^system dependencies@>

@s text_char char
@d text_char unsigned char /*the data type of characters in text files*/

@* Input and output.
The bane of portability is the fact that different operating systems treat
input and output quite differently, perhaps because computer scientists
have not given sufficient attention to this problem. People have felt somehow
that input and output are not part of ``real'' programming. Well, it is true
that some kinds of programming are more fun than others. With existing
input/output conventions being so diverse and so messy, the only sources of
joy in such parts of the code are the rare occasions when one can find a
way to make the program a little less bad than it might have been. We have
two choices, either to attack I/O now and get it over with, or to postpone
I/O until near the end. Neither prospect is very attractive, so let's
get it over with.

The basic operations we need to do are (1)~inputting and outputting of
text, to or from a file or the user's terminal; (2)~inputting and
outputting of eight-bit bytes, to or from a file; (3)~instructing the
operating system to initiate (``open'') or to terminate (``close'') input or
output from a specified file; (4)~testing whether the end of an input
file has been reached.

\TeX\ needs to deal with two kinds of files.
We shall use the term |alpha_file| for a file that contains textual data,
and the term |byte_file| for a file that contains eight-bit binary information.
These two types turn out to be the same on many computers, but
sometimes there is a significant distinction, so we shall be careful to
distinguish between them. Standard protocols for transferring
such files from computer to computer, via high-speed networks, are
now becoming available to more and more communities of users.

The program actually makes use also of a third kind of file, called a
|word_file|, when dumping and reloading base information for its own
initialization.  We shall define a word file later; but it will be possible
for us to specify simple operations on word files before they are defined.

@<Types...@>=
typedef uint8_t eight_bits; /*unsigned one-byte quantity*/
typedef struct {@+FILE *f;@+text_char@,d;@+} alpha_file; /*files that contain textual data*/
typedef struct {@+FILE *f;@+eight_bits@,d;@+} byte_file; /*files that contain binary data*/


@* String handling.
Control sequence names and diagnostic messages are variable-length strings
of eight-bit characters. Since \PASCAL\ does not have a well-developed string
mechanism, \TeX\ does all of its string processing by homegrown methods.

Elaborate facilities for dynamic strings are not needed, so all of the
necessary operations can be handled with a simple data structure.
The array |str_pool| contains all of the (eight-bit) ASCII codes in all
of the strings, and the array |str_start| contains indices of the starting
points of each string. Strings are referred to by integer numbers, so that
string number |s| comprises the characters |str_pool[j]| for
|str_start[s] <= j < str_start[s+1]|. Additional integer variables
|pool_ptr| and |str_ptr| indicate the number of entries used so far
in |str_pool| and |str_start|, respectively; locations
|str_pool[pool_ptr]| and |str_start[str_ptr]| are
ready for the next string to be allocated.

String numbers 0 to 255 are reserved for strings that correspond to single
ASCII characters. This is in accordance with the conventions of \.{WEB},
@.WEB@>
which converts single-character strings into the ASCII code number of the
single character involved, while it converts other strings into integers
and builds a string pool file. Thus, when the string constant \.{"."} appears
in the program below, \.{WEB} converts it into the integer 46, which is the
ASCII code for a period, while \.{WEB} will convert a string like \.{"hello"}
into some integer greater than~255. String number 46 will presumably be the
single character `\..'; but some ASCII codes have no standard visible
representation, and \TeX\ sometimes needs to be able to print an arbitrary
ASCII character, so the first 256 strings are used to specify exactly what
should be printed for each of the 256 possibilities.

Elements of the |str_pool| array must be ASCII codes that can actually
be printed; i.e., they must have an |xchr| equivalent in the local
character set. (This restriction applies only to preloaded strings,
not to those generated dynamically by the user.)

Some \PASCAL\ compilers won't pack integers into a single byte unless the
integers lie in the range |-128 dotdot 127|. To accommodate such systems
we access the string pool only via macros that can easily be redefined.
@^system dependencies@>

@d so(A) A /*convert from |packed_ASCII_code| to |ASCII_code|*/

@<Types...@>=
typedef int32_t pool_pointer; /*for variables that point into |str_pool|*/
typedef int16_t str_number; /*for variables that point into |str_start|*/
typedef uint8_t packed_ASCII_code; /*elements of |str_pool| array*/

@ The first 128 strings will contain 95 standard ASCII characters, and the
other 33 characters will be printed in three-symbol form like `\.{\^\^A}'
unless a system-dependent change is made here. Installations that have
an extended character set, where for example |xchr[032]==@t\.{\'^^Z\'}@>|,
would like string 032 to be the single character 032 instead of the
three characters 0136, 0136, 0132 (\.{\^\^Z}). On the other hand,
even people with an extended character set will want to represent string
015 by \.{\^\^M}, since 015 is |carriage_return|; the idea is to
produce visible strings instead of tabs or line-feeds or carriage-returns
or bell-rings or characters that are treated anomalously in text files.

Unprintable characters of codes 128--255 are, similarly, rendered
\.{\^\^80}--\.{\^\^ff}.

The boolean expression defined here should be |true| unless \TeX\
internal code number~|k| corresponds to a non-troublesome visible
symbol in the local character set.  An appropriate formula for the
extended character set recommended in {\sl The \TeX book\/} would, for
example, be `|k in[0, 010 dotdot 012, 014, 015, 033, 0177 dotdot 0377]|'.
If character |k| cannot be printed, and |k < 0200|, then character |k+0100| or
|k-0100| must be printable; moreover, ASCII codes |[041 dotdot 046,
060 dotdot 071, 0136, 0141 dotdot 0146, 0160 dotdot 0171]| must be printable.
Thus, at least 80 printable characters are needed.
@:TeXbook}{\sl The \TeX book@>
@^character set dependencies@>
@^system dependencies@>

@* On-line and off-line printing.

@ Macro abbreviations for output to the terminal and to the log file are
defined here for convenience. Some systems need special conventions
for terminal output, and it is possible to adhere to those conventions
by changing |wterm|, |wterm_ln|, and |wterm_cr| in this section.
@^system dependencies@>

@<Basic printing procedures@>=
#define @[put(F)@]    @[fwrite(&((F).d)@],@[sizeof((F).d),1,(F).f)@]@;
#define @[get(F)@]    @[(void)fread(&((F).d),sizeof((F).d),1,(F).f)@]

#define @[reset(F,N,M)@]   @[((F).f=fopen((char *)(N)+1,M),\
                                 (F).f!=NULL?get(F):0)@]
#define @[rewrite(F,N,M)@] @[((F).f=fopen((char *)(N)+1,M))@]
#define @[pascal_close(F)@]    @[fclose((F).f)@]
#define @[eof(F)@]    @[feof((F).f)@]
#define @[eoln(F)@]    @[((F).d=='\n'||eof(F))@]
#define @[erstat(F)@]   @[((F).f==NULL?-1:ferror((F).f))@]

#define @[pascal_read(F,X)@] @[((X)=(F).d,get(F))@]
#define @[read_ln(F)@]  do get(F); while (!eoln(F))

#define @[pascal_write(F, FMT,...)@]    @[fprintf(F.f,FMT,## __VA_ARGS__)@]
#define @[write_ln(F,...)@]    @[pascal_write(F,__VA_ARGS__"\n")@]

#define @[wterm(FMT,...)@] @[pascal_write(term_out,FMT, ## __VA_ARGS__)@]
#define @[wterm_ln(FMT,...)@] @[wterm(FMT "\n", ## __VA_ARGS__)@]
#define wterm_cr         @[pascal_write(term_out,"\n")@]

#define @[wlog(FMT, ...)@]    @[fprintf(hlog,FMT, ## __VA_ARGS__)@]
#define @[wlogc(C)@]          @[putc(C,hlog)@]
#define @[wlog_ln(FMT, ...)@]  @[wlog(FMT "\n", ## __VA_ARGS__)@]
#define wlog_cr           @[wlogc('\n')@]

static int @!tally=0; /*the number of characters recently printed*/
static int @!file_offset=0;/*the number of characters on the current file line*/
static int @!depth_threshold; /*maximum nesting depth in box displays*/
static int @!breadth_max; /*maximum number of items shown at the same list level*/
static int depth_level=0; /*current nesting level of |show_node_list|*/
static int nl_char='\n';


static void print_ln(void) /*prints an end-of-line*/
{ @+wlog_cr; file_offset=0;
}

static void print_char(ASCII_code @!s) /*prints a single character*/
{@+if (s==nl_char)
  {@+print_ln();return;
  }
  wlogc(s); file_offset++;
  if (file_offset==max_print_line) print_ln();
  tally++;
}

static void print(char *s) /* the simple version */
{ while (*s!=0) print_char(*s++);@+
}

static void print_nl(char *@!s) /*prints string |s| at beginning of line*/
{@+if (file_offset > 0) print_ln();
  print(s);
}

static void print_esc(char *@!s) /*prints escape character, then |s|*/
{@+print_char('\\');
  print(s);
}

static void print_int(int @!n) /*prints an integer in decimal form*/
{ file_offset+=fprintf(hlog,"%d",n);
}

static void begin_diagnostic(void) {}
static void end_diagnostic(bool b){}


@ Old versions of \TeX\ needed a procedure called |print_ASCII| whose function
is now subsumed by |print|. We retain the old name here as a possible aid to
future software arch\ae ologists.

@d print_lc_hex(A)
  if ((A) < 10) print_char((A)+'0');@+else print_char((A)-10+'a')
@d print_ASCII(k)
   if ( (k < ' ')||(k > '~'))
    {@+print("^^");
      if (k < 0100) print_char(k+0100);
      else if (k < 0200) print_char(k-0100);
      else {@+print_lc_hex(k/16);print_lc_hex(k%16); }
    }
    else print_char(k)

@ The |print| subroutine will not print a string that is still being
created. The following procedure will.

@<Basic printing procedures@>=
static void print_current_string(void) /*prints a yet-unmade string*/
{@+int i;
   for(i=0;i<depth_level;i++) @+
     print_char('.');
}

@* Reporting errors.

@ Since errors can be detected almost anywhere in \TeX, we want to declare the
error procedures near the beginning of the program. But the error procedures
in turn use some other procedures, which need to be declared |forward|
before we get to |error| itself.

It is possible for |error| to be called recursively if some error arises
when |get_token| is being used to delete a token, and/or if some fatal error
occurs while \TeX\ is trying to fix a non-fatal one. But such recursion
@^recursion@>
is never more than two levels deep.

@ The |jump_out| procedure just cuts across all active procedure levels and
goes to |end_of_TEX|. This is the only nontrivial |@!goto| statement in the
whole program. It is used when there is no recovery from a particular error.

Some \PASCAL\ compilers do not implement non-local |goto| statements.
@^system dependencies@>
In such cases the body of |jump_out| should simply be
`|close_files_and_terminate|;\thinspace' followed by a call on some system
procedure that quietly terminates the program.

@ Here is the most dreaded error message.

@<Basic error handling procedures@>=
static void overflow(char *@!s, int @!n) /*stop due to finiteness*/
{@+ QUIT("Capacity exceeded, sorry [%s=%d=0x%X]\n",s,n,n);@+
}

@ The program might sometime run completely amok, at which point there is
no choice but to stop. If no previous error has been detected, that's bad
news; a message is printed that is really intended for the \TeX\
maintenance person instead of the user (unless the user has been
particularly diabolical).  The index entries for `this can't happen' may
help to pinpoint the problem.
@^dry rot@>

@<Basic error handling procedures@>=
static void confusion(char *@!s)
   /*consistency check violated; |s| tells where*/
{@+ QUIT("This can't happen(%s)",s);@+ }


@* Arithmetic with scaled dimensions.
The principal computations performed by \TeX\ are done entirely in terms of
integers less than $2^{31}$ in magnitude; and divisions are done only when both
dividend and divisor are nonnegative. Thus, the arithmetic specified in this
program can be carried out in exactly the same way on a wide variety of
computers, including some small ones. Why? Because the arithmetic
calculations need to be spelled out precisely in order to guarantee that
\TeX\ will produce identical output on different machines. If some
quantities were rounded differently in different implementations, we would
find that line breaks and even page breaks might occur in different places.
Hence the arithmetic of \TeX\ has been designed with care, and systems that
claim to be implementations of \TeX82 should follow precisely the
@:TeX82}{\TeX82@>
calculations as they appear in the present program.

(Actually there are three places where \TeX\ uses |/| with a possibly negative
numerator. These are harmless; see |/| in the index. Also if the user
sets the \.{\\time} or the \.{\\year} to a negative value, some diagnostic
information will involve negative-numerator division. The same remarks
apply for |%| as well as for |/|.)

@ Here is a routine that calculates half of an integer, using an
unambiguous convention with respect to signed odd numbers.

@<\TeX\ functions@>=

static int half(int @!x)
{@+if (odd(x)) return(x+1)/2;
else return x/2;
}

@ Fixed-point arithmetic is done on {\sl scaled integers\/} that are multiples
of $2^{-16}$. In other words, a binary point is assumed to be sixteen bit
positions from the right end of a binary computer word.

@d unity 0200000 /*$2^{16}$, represents 1.00000*/
@d two 0400000 /*$2^{17}$, represents 2.00000*/

@<Types...@>=
typedef int scaled; /*this type is used for scaled integers*/
typedef int32_t nonnegative_integer; /*$0\le x<2^{31}$*/
typedef int8_t small_number; /*this type is self-explanatory*/


@ Conversely, here is a procedure analogous to |print_int|. If the output
of this procedure is subsequently read by \TeX\ and converted by the
|round_decimals| routine above, it turns out that the original value will
be reproduced exactly; the ``simplest'' such decimal number is output,
but there is always at least one digit following the decimal point.

The invariant relation in the \&{repeat} loop is that a sequence of
decimal digits yet to be printed will yield the original number if and only if
they form a fraction~$f$ in the range $s-\delta\le 10\cdot2^{16}f<s$.
We can stop if and only if $f=0$ satisfies this condition; the loop will
terminate before $s$ can possibly become zero.

@<Basic printing procedures@>=
static void print_scaled(scaled @!s) /*prints scaled real, rounded to five
  digits*/
{@+scaled delta; /*amount of allowable inaccuracy*/
if (s < 0)
  {@+print_char('-');negate(s); /*print the sign, if negative*/
  }
print_int(s/unity); /*print the integer part*/
print_char('.');
s=10*(s%unity)+5;delta=10;
@/do@+{if (delta > unity) s=s+0100000-50000; /*round the last digit*/
print_char('0'+(s/unity));s=10*(s%unity);delta=delta*10;
}@+ while (!(s <= delta));
}

static void print_xdimen(pointer p)
{ print_scaled(xdimen_width(p));
  if (xdimen_hfactor(p)!=0)
  { print_char('+');print_scaled(xdimen_hfactor(p));print("*hsize");}
  if (xdimen_vfactor(p)!=0)
  { print_char('+');print_scaled(xdimen_vfactor(p));print("*vsize");}
}

static void print_label(pointer p)
{ print("goto *"); print_int(label_ref(p));
}

@ Physical sizes that a \TeX\ user specifies for portions of documents are
represented internally as scaled points. Thus, if we define an `sp' (scaled
@^sp@>
point) as a unit equal to $2^{-16}$ printer's points, every dimension
inside of \TeX\ is an integer number of sp. There are exactly
4,736,286.72 sp per inch.  Users are not allowed to specify dimensions
larger than $2^{30}-1$ sp, which is a distance of about 18.892 feet (5.7583
meters); two such quantities can be added without overflow on a 32-bit
computer.

The present implementation of \TeX\ does not check for overflow when
@^overflow in arithmetic@>
dimensions are added or subtracted. This could be done by inserting a
few dozen tests of the form `\ignorespaces|if (x >= 010000000000)|
\\{report\_overflow}', but the chance of overflow is so remote that
such tests do not seem worthwhile.

\TeX\ needs to do only a few arithmetic operations on scaled quantities,
other than addition and subtraction, and the following subroutines do most of
the work. A single computation might use several subroutine calls, and it is
desirable to avoid producing multiple error messages in case of arithmetic
overflow; so the routines set the global variable |arith_error| to |true|
instead of reporting errors directly to the user. Another global variable,
|rem|, holds the remainder after a division.

@<\TeX\ functions@>=
static bool @!arith_error; /*has arithmetic overflow occurred recently?*/
static scaled @!rem; /*amount subtracted to get an exact division*/

@ We also need to divide scaled dimensions by integers.

@<\TeX\ functions@>=
static scaled x_over_n(scaled @!x, int @!n)
{@+bool negative; /*should |rem| be negated?*/
scaled x_over_n;
negative=false;
if (n==0)
  {@+arith_error=true;x_over_n=0;rem=x;
  }
else{@+if (n < 0)
    {@+negate(x);negate(n);negative=true;
    }
  if (x >= 0)
    {@+x_over_n=x/n;rem=x%n;
    }
  else{@+x_over_n=-((-x)/n);rem=-((-x)%n);
    }
  }
if (negative) negate(rem);
return x_over_n;}

@ Then comes the multiplication of a scaled number by a fraction |n/(double)d|,
where |n| and |d| are nonnegative integers | <= @t$2^{16}$@>| and |d| is
positive. It would be too dangerous to multiply by~|n| and then divide
by~|d|, in separate operations, since overflow might well occur; and it
would be too inaccurate to divide by |d| and then multiply by |n|. Hence
this subroutine simulates 1.5-precision arithmetic.

@<\TeX\ functions@>=
static scaled xn_over_d(scaled @!x, int @!n, int @!d)
{@+bool positive; /*was |x >= 0|?*/
nonnegative_integer @!t, @!u, @!v; /*intermediate quantities*/
scaled xn_over_d;
if (x >= 0) positive=true;
else{@+negate(x);positive=false;
  }
t=(x%0100000)*n;
u=(x/0100000)*n+(t/0100000);
v=(u%d)*0100000+(t%0100000);
if (u/d >= 0100000) arith_error=true;
else u=0100000*(u/d)+(v/d);
if (positive)
  {@+xn_over_d=u;rem=v%d;
  }
else{@+xn_over_d=-u;rem=-(v%d);
  }
return xn_over_d;}

@ The next subroutine is used to compute the ``badness'' of glue, when a
total~|t| is supposed to be made from amounts that sum to~|s|.  According
to {\sl The \TeX book}, the badness of this situation is $100(t/s)^3$;
however, badness is simply a heuristic, so we need not squeeze out the
last drop of accuracy when computing it. All we really want is an
approximation that has similar properties.
@:TeXbook}{\sl The \TeX book@>

The actual method used to compute the badness is easier to read from the
program than to describe in words. It produces an integer value that is a
reasonably close approximation to $100(t/s)^3$, and all implementations
of \TeX\ should use precisely this method. Any badness of $2^{13}$ or more is
treated as infinitely bad, and represented by 10000.

It is not difficult to prove that $$\hbox{|badness(t+1, s) >= badness(t, s)
 >= badness(t, s+1)|}.$$ The badness function defined here is capable of
computing at most 1095 distinct values, but that is plenty.

@d inf_bad 10000 /*infinitely bad value*/

@<\TeX\ functions@>=
static halfword badness(scaled @!t, scaled @!s) /*compute badness, given |t >= 0|*/
{@+int r; /*approximation to $\alpha t/s$, where $\alpha^3\approx
  100\cdot2^{18}$*/
if (t==0) return 0;
else if (s <= 0) return inf_bad;
else{@+if (t <= 7230584) r=(t*297)/s; /*$297^3=99.94\times2^{18}$*/
  else if (s >= 1663497) r=t/(s/297);
  else r=t;
  if (r > 1290) return inf_bad; /*$1290^3<2^{31}<1291^3$*/
  else return(r*r*r+0400000)/01000000;
  }  /*that was $r^3/2^{18}$, rounded to the nearest integer*/
}

@ When \TeX\ ``packages'' a list into a box, it needs to calculate the
proportionality ratio by which the glue inside the box should stretch
or shrink. This calculation does not affect \TeX's decision making,
so the precise details of rounding, etc., in the glue calculation are not
of critical importance for the consistency of results on different computers.

We shall use the type |glue_ratio| for such proportionality ratios.
A glue ratio should take the same amount of memory as an
|int| (usually 32 bits) if it is to blend smoothly with \TeX's
other data structures. Thus |glue_ratio| should be equivalent to
|short_real| in some implementations of \PASCAL. Alternatively,
it is possible to deal with glue ratios using nothing but fixed-point
arithmetic; see {\sl TUGboat \bf3},1 (March 1982), 10--27. (But the
routines cited there must be modified to allow negative glue ratios.)
@^system dependencies@>

@d set_glue_ratio_zero(A) A=0.0 /*store the representation of zero ratio*/
@d set_glue_ratio_one(A) A=1.0 /*store the representation of unit ratio*/
@d unfix(A) ((double)(A)) /*convert from |glue_ratio| to type |double|*/
@d fix(A) ((glue_ratio)(A)) /*convert from |double| to type |glue_ratio|*/
@d float_constant(A) ((double)(A)) /*convert |int| constant to |double|*/

@<Types...@>=
#if __SIZEOF_FLOAT__==4
typedef float float32_t;
#else
#error  @=float type must have size 4@>
#endif
typedef float @!glue_ratio; /*one-word representation of a glue expansion factor*/

@* Packed data.
In order to make efficient use of storage space, \TeX\ bases its major data
structures on a |memory_word|, which contains either a (signed) integer,
possibly scaled, or a (signed) |glue_ratio|, or a small number of
fields that are one half or one quarter of the size used for storing
integers.

If |x| is a variable of type |memory_word|, it contains up to four
fields that can be referred to as follows:
$$\vbox{\halign{\hfil#&#\hfil&#\hfil\cr
|x|&.|i|&(an |int|)\cr
|x|&.|sc|\qquad&(a |scaled| integer)\cr
|x|&.|gr|&(a |glue_ratio|)\cr
|x.hh.lh|, |x.hh|&.|rh|&(two halfword fields)\cr
|x.hh.b0|, |x.hh.b1|, |x.hh|&.|rh|&(two quarterword fields, one halfword
  field)\cr
|x.qqqq.b0|, |x.qqqq.b1|, |x.qqqq|&.|b2|, |x.qqqq.b3|\hskip-100pt
  &\qquad\qquad\qquad(four quarterword fields)\cr}}$$
This is somewhat cumbersome to write, and not very readable either, but
macros will be used to make the notation shorter and more transparent.
The \PASCAL\ code below gives a formal definition of |memory_word| and
its subsidiary types, using packed variant records. \TeX\ makes no
assumptions about the relative positions of the fields within a word.

Since we are assuming 32-bit integers, a halfword must contain at least
16 bits, and a quarterword must contain at least 8 bits.
@^system dependencies@>
But it doesn't hurt to have more bits; for example, with enough 36-bit
words you might be able to have |mem_max| as large as 262142, which is
eight times as much memory as anybody had during the first four years of
\TeX's existence.

N.B.: Valuable memory space will be dreadfully wasted unless \TeX\ is compiled
by a \PASCAL\ that packs all of the |memory_word| variants into
the space of a single integer. This means, for example, that |glue_ratio|
words should be |short_real| instead of |double| on some computers. Some
\PASCAL\ compilers will pack an integer whose subrange is `|0 dotdot 255|' into
an eight-bit field, but others insist on allocating space for an additional
sign bit; on such systems you can get 256 values into a quarterword only
if the subrange is `|-128 dotdot 127|'.

The present implementation tries to accommodate as many variations as possible,
so it makes few assumptions. If integers having the subrange
`|min_quarterword dotdot max_quarterword|' can be packed into a quarterword,
and if integers having the subrange `|min_halfword dotdot max_halfword|'
can be packed into a halfword, everything should work satisfactorily.

It is usually most efficient to have |min_quarterword==min_halfword==0|,
so one should try to achieve this unless it causes a severe problem.
The values defined here are recommended for most 32-bit computers.

@d min_quarterword 0 /*smallest allowable value in a |quarterword|*/
@d min_halfword 0 /*smallest allowable value in a |halfword|*/
@d max_halfword 65535 /*largest allowable value in a |halfword|*/


@ The operation of adding or subtracting |min_quarterword| occurs quite
frequently in \TeX, so it is convenient to abbreviate this operation
by using the macros |qi| and |qo| for input and output to and from
quarterword format.

The inner loop of \TeX\ will run faster with respect to compilers
that don't optimize expressions like `|x+0|' and `|x-0|', if these
macros are simplified in the obvious way when |min_quarterword==0|.
@^inner loop@>@^system dependencies@>

@d qi(A) A+min_quarterword
   /*to put an |eight_bits| item into a quarterword*/
@d qo(A) A-min_quarterword
   /*to take an |eight_bits| item out of a quarterword*/

@ The reader should study the following definitions closely:
@^system dependencies@>

@d sc i /*|scaled| data is equivalent to |int|*/

@<Types...@>=
typedef uint8_t quarterword; /*1/4 of a word*/
typedef uint16_t halfword; /*1/2 of a word*/
typedef int8_t two_choices; /*used when there are two variants in a record*/
typedef int8_t four_choices; /*used when there are four variants in a record*/
typedef struct { @;@/
  halfword @!rh;
  union {
  halfword @!lh;
  struct { quarterword @!b0;quarterword @!b1;} ;
  };} two_halves;
typedef struct { @;@/
  quarterword @!b0;
  quarterword @!b1;
  quarterword @!b2;
  quarterword @!b3;
  } four_quarters;
typedef struct { @;@/
  union {
  int @!i;
  glue_ratio @!gr;
  two_halves @!hh;
  four_quarters @!qqqq;
  };} memory_word;
typedef struct {@+FILE *f;@+memory_word@,d;@+} word_file;


@* Dynamic memory allocation.
The \TeX\ system does nearly all of its own memory allocation, so that it
can readily be transported into environments that do not have automatic
facilities for strings, garbage collection, etc., and so that it can be in
control of what error messages the user receives. The dynamic storage
requirements of \TeX\ are handled by providing a large array |mem| in
which consecutive blocks of words are used as nodes by the \TeX\ routines.

Pointer variables are indices into this array, or into another array
called |eqtb| that will be explained later. A pointer variable might
also be a special flag that lies outside the bounds of |mem|, so we
allow pointers to assume any |halfword| value. The minimum halfword
value represents a null pointer. \TeX\ does not assume that |mem[null]| exists.

@s pointer int
@d pointer halfword /*a flag or a location in |mem| or |eqtb|*/
@d null min_halfword /*the null pointer*/

@<Selected global variables@>=
static pointer @!temp_ptr; /*a pointer variable for occasional emergency use*/

@ The |mem| array is divided into two regions that are allocated separately,
but the dividing line between these two regions is not fixed; they grow
together until finding their ``natural'' size in a particular job.
Locations less than or equal to |lo_mem_max| are used for storing
variable-length records consisting of two or more words each. This region
is maintained using an algorithm similar to the one described in exercise
2.5--19 of {\sl The Art of Computer Programming}. However, no size field
appears in the allocated nodes; the program is responsible for knowing the
relevant size when a node is freed. Locations greater than or equal to
|hi_mem_min| are used for storing one-word records; a conventional
\.{AVAIL} stack is used for allocation in this region.

Locations of |mem| between |mem_bot| and |mem_top| may be dumped as part
of preloaded format files, by the \.{INITEX} preprocessor.
@.INITEX@>
Production versions of \TeX\ may extend the memory at both ends in order to
provide more space; locations between |mem_min| and |mem_bot| are always
used for variable-size nodes, and locations between |mem_top| and |mem_max|
are always used for single-word nodes.

The key pointers that govern |mem| allocation have a prescribed order:
$$\advance\thickmuskip-2mu
\hbox{|null <= mem_min <= mem_bot < lo_mem_max <
  hi_mem_min < mem_top <= mem_end <= mem_max|.}$$

Empirical tests show that the present implementation of \TeX\ tends to
spend about 9\pct! of its running time allocating nodes, and about 6\pct!
deallocating them after their use.

@<Selected global variables@>=
static memory_word @!mem0[mem_max-mem_min+1], *const @!mem = @!mem0-mem_min; /*the big dynamic storage area*/
static pointer @!lo_mem_max; /*the largest location of variable-size memory in use*/
static pointer @!hi_mem_min; /*the smallest location of one-word memory in use*/

@ In order to study the memory requirements of particular applications, it
is possible to prepare a version of \TeX\ that keeps track of current and
maximum memory usage. When code between the delimiters |
#ifdef @!STAT
| $\ldots$
|@t\#\&{endif}@>| is not ``commented out,'' \TeX\ will run a bit slower but it will
report these statistics when |tracing_stats| is sufficiently large.

@<Selected global variables@>=
static int @!var_used, @!dyn_used; /*how much memory is in use*/
#ifdef @!STAT
#define incr_dyn_used @[incr(dyn_used)@]
#define decr_dyn_used @[decr(dyn_used)@]
#else
#define incr_dyn_used
#define decr_dyn_used
#endif

@ Let's consider the one-word memory region first, since it's the
simplest. The pointer variable |mem_end| holds the highest-numbered location
of |mem| that has ever been used. The free locations of |mem| that
occur between |hi_mem_min| and |mem_end|, inclusive, are of type
|two_halves|, and we write |info(p)| and |link(p)| for the |lh|
and |rh| fields of |mem[p]| when it is of this type. The single-word
free locations form a linked list
$$|avail|,\;\hbox{|link(avail)|},\;\hbox{|link(link(avail))|},\;\ldots$$
terminated by |null|.

@d link(A) mem[A].hh.rh /*the |link| field of a memory word*/
@d info(A) mem[A].hh.lh /*the |info| field of a memory word*/

@d mem_end mem_top
@<Selected global variables@>=
static pointer @!avail; /*head of the list of available one-word nodes*/

@ The function |get_avail| returns a pointer to a new one-word node whose
|link| field is null. However, \TeX\ will halt if there is no more room left.
@^inner loop@>

If the available-space list is empty, i.e., if |avail==null|,
we try first to increase |mem_end|. If that cannot be done, i.e., if
|mem_end==mem_max|, we try to decrease |hi_mem_min|. If that cannot be
done, i.e., if |hi_mem_min==lo_mem_max+1|, we have to quit.

@<\TeX\ functions@>=
static pointer get_avail(void) /*single-word node allocation*/
{@+pointer p; /*the new node being got*/
p=avail; /*get top location in the |avail| stack*/
if (p!=null) avail=link(avail); /*and pop it off*/
else{@+decr(hi_mem_min);p=hi_mem_min;
  if (hi_mem_min <= lo_mem_max)
    {@+
    overflow("main memory size", mem_max+1-mem_min);
       /*quit; all one-word nodes are busy*/
@:TeX capacity exceeded main memory size}{\quad main memory size@>
    }
  }
link(p)=null; /*provide an oft-desired initialization of the new node*/
#ifdef @!STAT
incr(dyn_used);
#endif
@; /*maintain statistics*/
return p;
}

@ Conversely, a one-word node is recycled by calling |free_avail|.
This routine is part of \TeX's ``inner loop,'' so we want it to be fast.
@^inner loop@>

@d free_avail(A)  /*single-word node liberation*/
  {@+link(A)=avail;avail=A;
  decr_dyn_used;
  }


@ The available-space list that keeps track of the variable-size portion
of |mem| is a nonempty, doubly-linked circular list of empty nodes,
pointed to by the roving pointer |rover|.

Each empty node has size 2 or more; the first word contains the special
value |max_halfword| in its |link| field and the size in its |info| field;
the second word contains the two pointers for double linking.

Each nonempty node also has size 2 or more. Its first word is of type
|two_halves|\kern-1pt, and its |link| field is never equal to |max_halfword|.
Otherwise there is complete flexibility with respect to the contents
of its other fields and its other words.

(We require |mem_max < max_halfword| because terrible things can happen
when |max_halfword| appears in the |link| field of a nonempty node.)

@d empty_flag max_halfword /*the |link| of an empty variable-size node*/
@d is_empty(A) (link(A)==empty_flag) /*tests for empty node*/
@d node_size(A) info(A) /*the size field in empty variable-size nodes*/
@d llink(A) info(A+1) /*left link in doubly-linked list of empty nodes*/
@d rlink(A) link(A+1) /*right link in doubly-linked list of empty nodes*/

@<Selected global variables@>=
static pointer @!rover; /*points to some node in the list of empties*/

@ A call to |get_node| with argument |s| returns a pointer to a new node
of size~|s|, which must be 2~or more. The |link| field of the first word
of this new node is set to null. An overflow stop occurs if no suitable
space exists.

If |get_node| is called with $s=2^{30}$, it simply merges adjacent free
areas and returns the value |max_halfword|.

@<\TeX\ functions@>=
static pointer get_node(int @!s) /*variable-size node allocation*/
{@+
pointer p; /*the node currently under inspection*/
pointer @!q; /*the node physically after node |p|*/
int @!r; /*the newly allocated node, or a candidate for this honor*/
int @!t; /*temporary register*/
restart: p=rover; /*start at some free node in the ring*/
@/do@+{@<Try to allocate within node |p| and its physical successors, and
|goto found| if allocation was possible@>;
@^inner loop@>
p=rlink(p); /*move to the next node in the ring*/
}@+ while (!(p==rover)); /*repeat until the whole list has been traversed*/
if (s==010000000000)
  {@+return max_halfword;
  }
if (lo_mem_max+2 < hi_mem_min) if (lo_mem_max+2 <= mem_bot+max_halfword)
  @<Grow more variable-size memory and |goto restart|@>;
overflow("main memory size", mem_max+1-mem_min);
   /*sorry, nothing satisfactory is left*/
@:TeX capacity exceeded main memory size}{\quad main memory size@>
found: link(r)=null; /*this node is now nonempty*/
#ifdef @!STAT
var_used=var_used+s; /*maintain usage statistics*/
#endif
@;@/
leak_in(r,s);
return r;
}

@ The lower part of |mem| grows by 1000 words at a time, unless
we are very close to going under. When it grows, we simply link
a new node into the available-space list. This method of controlled
growth helps to keep the |mem| usage consecutive when \TeX\ is
implemented on ``virtual memory'' systems.
@^virtual memory@>

@<Grow more variable-size memory and |goto restart|@>=
{@+if (hi_mem_min-lo_mem_max >= 1998) t=lo_mem_max+1000;
else t=lo_mem_max+1+(hi_mem_min-lo_mem_max)/2;
   /*|lo_mem_max+2 <= t < hi_mem_min|*/
p=llink(rover);q=lo_mem_max;rlink(p)=q;llink(rover)=q;@/
if (t > mem_bot+max_halfword) t=mem_bot+max_halfword;
rlink(q)=rover;llink(q)=p;link(q)=empty_flag;node_size(q)=t-lo_mem_max;@/
lo_mem_max=t;link(lo_mem_max)=null;info(lo_mem_max)=null;
rover=q;goto restart;
}

@ Empirical tests show that the routine in this section performs a
node-merging operation about 0.75 times per allocation, on the average,
after which it finds that |r > p+1| about 95\pct! of the time.

@<Try to allocate...@>=
q=p+node_size(p); /*find the physical successor*/
@^inner loop@>
while (is_empty(q))  /*merge node |p| with node |q|*/
  {@+t=rlink(q);
  if (q==rover) rover=t;
  llink(t)=llink(q);rlink(llink(q))=t;@/
  q=q+node_size(q);
  }
r=q-s;
if (r > p+1) @<Allocate from the top of node |p| and |goto found|@>;
if (r==p) if (rlink(p)!=p)
  @<Allocate entire node |p| and |goto found|@>;
node_size(p)=q-p /*reset the size in case it grew*/

@ @<Allocate from the top...@>=
{@+node_size(p)=r-p; /*store the remaining size*/
@^inner loop@>
rover=p; /*start searching here next time*/
goto found;
}

@ Here we delete node |p| from the ring, and let |rover| rove around.

@<Allocate entire...@>=
{@+rover=rlink(p);t=llink(p);
llink(rover)=t;rlink(t)=rover;
goto found;
}

@ Conversely, when some variable-size node |p| of size |s| is no longer needed,
the operation |free_node(p, s)| will make its words available, by inserting
|p| as a new empty node just before where |rover| now points.
@^inner loop@>

@<\TeX\ functions@>=
static void free_node(pointer @!p, halfword @!s) /*variable-size node
  liberation*/
{@+pointer q; /*|llink(rover)|*/
leak_out(p,s);
store_map(p,0,0);
node_size(p)=s;link(p)=empty_flag;
q=llink(rover);llink(p)=q;rlink(p)=rover; /*set both links*/
llink(rover)=p;rlink(q)=p; /*insert |p| into the ring*/
#ifdef @!STAT
var_used=var_used-s;
#endif
@; /*maintain statistics*/
}

@* Data structures for boxes and their friends.
From the computer's standpoint, \TeX's chief mission is to create
horizontal and vertical lists. We shall now investigate how the elements
of these lists are represented internally as nodes in the dynamic memory.

A horizontal or vertical list is linked together by |link| fields in
the first word of each node. Individual nodes represent boxes, glue,
penalties, or special things like discretionary hyphens; because of this
variety, some nodes are longer than others, and we must distinguish different
kinds of nodes. We do this by putting a `|type|' field in the first word,
together with the link and an optional `|subtype|'.

@d type(A) mem[A].hh.b0 /*identifies what kind of node this is*/
@d subtype(A) mem[A].hh.b1 /*secondary identification in some cases*/

@ A |@!char_node|, which represents a single character, is the most important
kind of node because it accounts for the vast majority of all boxes.
Special precautions are therefore taken to ensure that a |char_node| does
not take up much memory space. Every such node is one word long, and in fact
it is identifiable by this property, since other kinds of nodes have at least
two words, and they appear in |mem| locations less than |hi_mem_min|.
This makes it possible to omit the |type| field in a |char_node|, leaving
us room for two bytes that identify a |font| and a |character| within
that font.

Note that the format of a |char_node| allows for up to 256 different
fonts and up to 256 characters per font; but most implementations will
probably limit the total number of fonts to fewer than 75 per job,
and most fonts will stick to characters whose codes are
less than 128 (since higher codes
are more difficult to access on most keyboards).

Extensions of \TeX\ intended for oriental languages will need even more
than $256\times256$ possible characters, when we consider different sizes
@^oriental characters@>@^Chinese characters@>@^Japanese characters@>
and styles of type.  It is suggested that Chinese and Japanese fonts be
handled by representing such characters in two consecutive |char_node|
entries: The first of these has |font==font_base|, and its |link| points
to the second;
the second identifies the font and the character dimensions.
The saving feature about oriental characters is that most of them have
the same box dimensions. The |character| field of the first |char_node|
is a ``\\{charext}'' that distinguishes between graphic symbols whose
dimensions are identical for typesetting purposes. (See the \MF\ manual.)
Such an extension of \TeX\ would not be difficult; further details are
left to the reader.

In order to make sure that the |character| code fits in a quarterword,
\TeX\ adds the quantity |min_quarterword| to the actual code.

Character nodes appear only in horizontal lists, never in vertical lists.

@d is_char_node(A) (A >= hi_mem_min)
   /*does the argument point to a |char_node|?*/
@d font(A) type(A) /*the font code in a |char_node|*/
@d character(A) subtype(A) /*the character code in a |char_node|*/

@ An |hlist_node| stands for a box that was made from a horizontal list.
Each |hlist_node| is seven words long, and contains the following fields
(in addition to the mandatory |type| and |link|, which we shall not
mention explicitly when discussing the other node types): The |height| and
|width| and |depth| are scaled integers denoting the dimensions of the
box.  There is also a |shift_amount| field, a scaled integer indicating
how much this box should be lowered (if it appears in a horizontal list),
or how much it should be moved to the right (if it appears in a vertical
list). There is a |list_ptr| field, which points to the beginning of the
list from which this box was fabricated; if |list_ptr| is |null|, the box
is empty. Finally, there are three fields that represent the setting of
the glue:  |glue_set(p)| is a word of type |glue_ratio| that represents
the proportionality constant for glue setting; |glue_sign(p)| is
|stretching| or |shrinking| or |normal| depending on whether or not the
glue should stretch or shrink or remain rigid; and |glue_order(p)|
specifies the order of infinity to which glue setting applies (|normal|,
|fil|, |fill|, or |filll|). The |subtype| field is not used.

@d hlist_node 0 /*|type| of hlist nodes*/
@d box_node_size 9 /*number of words to allocate for a box, set, or pack node*/
@d width_offset 1 /*position of |width| field in a box node*/
@d depth_offset 2 /*position of |depth| field in a box node*/
@d height_offset 3 /*position of |height| field in a box node*/
@d width(A) mem[A+width_offset].sc /*width of the box, in sp*/
@d depth(A) mem[A+depth_offset].sc /*depth of the box, in sp*/
@d height(A) mem[A+height_offset].sc /*height of the box, in sp*/
@d shift_amount(A) mem[A+4].sc /*repositioning distance, in sp*/
@d list_offset 5 /*position of |list_ptr| field in a box node*/
@d list_ptr(A) link(A+list_offset) /*beginning of the list inside the box*/
@d glue_order(A) subtype(A+list_offset) /*applicable order of infinity*/
@d glue_sign(A) type(A+list_offset) /*stretching or shrinking*/
@d normal 0 /*the most common case when several cases are named*/
@d stretching 1 /*glue setting applies to the stretch components*/
@d shrinking 2 /*glue setting applies to the shrink components*/
@d glue_offset 6 /*position of |glue_set| in a box node*/
@d glue_set(A) mem[A+glue_offset].gr
   /*a word of type |glue_ratio| for glue setting*/

@ The |new_null_box| function returns a pointer to an |hlist_node| in
which all subfields have the values corresponding to `\.{\\hbox\{\}}'.
(The |subtype| field is set to |min_quarterword|, for historic reasons
that are no longer relevant.)

@<\TeX\ functions@>=
static pointer new_null_box(void) /*creates a new box node*/
{@+pointer p; /*the new node*/
p=get_node(box_node_size);type(p)=hlist_node;
subtype(p)=min_quarterword;
width(p)=0;depth(p)=0;height(p)=0;shift_amount(p)=0;list_ptr(p)=null;
glue_sign(p)=normal;glue_order(p)=normal;set_glue_ratio_zero(glue_set(p));
return p;
}

@ A |vlist_node| is like an |hlist_node| in all respects except that it
contains a vertical list.

@d vlist_node 1 /*|type| of vlist nodes*/

@ A |rule_node| stands for a solid black rectangle; it has |width|,
|depth|, and |height| fields just as in an |hlist_node|. However, if
any of these dimensions is $-2^{30}$, the actual value will be determined
by running the rule up to the boundary of the innermost enclosing box.
This is called a ``running dimension.'' The |width| is never running in
an hlist; the |height| and |depth| are never running in a~vlist.

@d rule_node 2 /*|type| of rule nodes*/
@d rule_node_size 4 /*number of words to allocate for a rule node*/
@d null_flag -010000000000 /*$-2^{30}$, signifies a missing item*/
@d is_running(A) (A==null_flag) /*tests for a running dimension*/

@ A new rule node is delivered by the |new_rule| function. It
makes all the dimensions ``running,'' so you have to change the
ones that are not allowed to run.

@<\TeX\ functions@>=
static pointer new_rule(void)
{@+pointer p; /*the new node*/
p=get_node(rule_node_size);type(p)=rule_node;
subtype(p)=0; /*the |subtype| is not used*/
width(p)=null_flag;depth(p)=null_flag;height(p)=null_flag;
return p;
}

@ Insertions are represented by |ins_node| records, where the |subtype|
indicates the corresponding box number. For example, `\.{\\insert 250}'
leads to an |ins_node| whose |subtype| is |250+min_quarterword|.
The |height| field of an |ins_node| is slightly misnamed; it actually holds
the natural height plus depth of the vertical list being inserted.
The |depth| field holds the |split_max_depth| to be used in case this
insertion is split, and the |split_top_ptr| points to the corresponding
|split_top_skip|. The |float_cost| field holds the |floating_penalty| that
will be used if this insertion floats to a subsequent page after a
split insertion of the same class.  There is one more field, the
|ins_ptr|, which points to the beginning of the vlist for the insertion.

@d ins_node 3 /*|type| of insertion nodes*/
@d ins_node_size 5 /*number of words to allocate for an insertion*/
@d float_cost(A) mem[A+1].i /*the |floating_penalty| to be used*/
@d ins_ptr(A) info(A+4) /*the vertical list to be inserted*/
@d split_top_ptr(A) link(A+4) /*the |split_top_skip| to be used*/

@ A |mark_node| has a |mark_ptr| field that points to the reference count
of a token list that contains the user's \.{\\mark} text.
This field occupies a full word instead of a halfword, because
there's nothing to put in the other halfword; it is easier in \PASCAL\ to
use the full word than to risk leaving garbage in the unused half.

@d mark_node 4 /*|type| of a mark node*/
@d small_node_size 2 /*number of words to allocate for most node types*/
@d mark_ptr(A) mem[A+1].i /*head of the token list for a mark*/

@ An |adjust_node|, which occurs only in horizontal lists,
specifies material that will be moved out into the surrounding
vertical list; i.e., it is used to implement \TeX's `\.{\\vadjust}'
operation.  The |adjust_ptr| field points to the vlist containing this
material.

@d adjust_node 5 /*|type| of an adjust node*/
@d adjust_ptr(A) mark_ptr(A) /*vertical list to be moved out of horizontal list*/

@ A |ligature_node|, which occurs only in horizontal lists, specifies
a character that was fabricated from the interaction of two or more
actual characters.  The second word of the node, which is called the
|lig_char| word, contains |font| and |character| fields just as in a
|char_node|. The characters that generated the ligature have not been
forgotten, since they are needed for diagnostic messages and for
hyphenation; the |lig_ptr| field points to a linked list of character
nodes for all original characters that have been deleted. (This list
might be empty if the characters that generated the ligature were
retained in other nodes.)

The |subtype| field is 0, plus 2 and/or 1 if the original source of the
ligature included implicit left and/or right boundaries.

@d ligature_node 6 /*|type| of a ligature node*/
@d lig_char(A) A+1 /*the word where the ligature is to be found*/
@d lig_ptr(A) link(lig_char(A)) /*the list of characters*/

@ The |new_ligature| function creates a ligature node having given
contents of the |font|, |character|, and |lig_ptr| fields. We also have
a |new_lig_item| function, which returns a two-word node having a given
|character| field. Such nodes are used for temporary processing as ligatures
are being created.

@<\TeX\ functions@>=
static pointer new_ligature(quarterword @!f, quarterword @!c, pointer @!q)
{@+pointer p; /*the new node*/
p=get_node(small_node_size);type(p)=ligature_node;
font(lig_char(p))=f;character(lig_char(p))=c;lig_ptr(p)=q;
subtype(p)=0;return p;
}
@#

@ A |disc_node|, which occurs only in horizontal lists, specifies a
``dis\-cretion\-ary'' line break. If such a break occurs at node |p|, the text
that starts at |pre_break(p)| will precede the break, the text that starts at
|post_break(p)| will follow the break, and text that appears in the next
|replace_count(p)| nodes will be ignored. For example, an ordinary
discretionary hyphen, indicated by `\.{\\-}', yields a |disc_node| with
|pre_break| pointing to a |char_node| containing a hyphen, |post_break==null|,
and |replace_count==0|. All three of the discretionary texts must be
lists that consist entirely of character, kern, box, rule, and ligature nodes.

If |pre_break(p)==null|, the |ex_hyphen_penalty| will be charged for this
break.  Otherwise the |hyphen_penalty| will be charged.  The texts will
actually be substituted into the list by the line-breaking algorithm if it
decides to make the break, and the discretionary node will disappear at
that time; thus, the output routine sees only discretionaries that were
not chosen.

@d disc_node 7 /*|type| of a discretionary node*/
@d replace_count(A) (subtype(A)&0x7F) /*how many subsequent nodes to replace*/
@d set_replace_count(A,B) (subtype(A)=(B)&0x7F)
@d set_auto_disc(A) (subtype(A)|=0x80)
@d is_auto_disc(A) (subtype(A)&0x80)
@d pre_break(A) llink(A) /*text that precedes a discretionary break*/
@d post_break(A) rlink(A) /*text that follows a discretionary break*/

@<\TeX\ functions@>=
static pointer new_disc(void) /*creates an empty |disc_node|*/
{@+pointer p; /*the new node*/
p=get_node(small_node_size);type(p)=disc_node;
subtype(p)=0;pre_break(p)=null;post_break(p)=null;
return p;
}

@ A |whatsit_node| is a wild card reserved for extensions to \TeX. The
|subtype| field in its first word says what `\\{whatsit}' it is, and
implicitly determines the node size (which must be 2 or more) and the
format of the remaining words. When a |whatsit_node| is encountered
in a list, special actions are invoked; knowledgeable people who are
careful not to mess up the rest of \TeX\ are able to make \TeX\ do new
things by adding code at the end of the program. For example, there
might be a `\TeX nicolor' extension to specify different colors of ink,
@^extensions to \TeX@>
and the whatsit node might contain the desired parameters.

The present implementation of \TeX\ treats the features associated with
`\.{\\write}' and `\.{\\special}' as if they were extensions, in order to
illustrate how such routines might be coded. We shall defer further
discussion of extensions until the end of this program.

@d whatsit_node 8 /*|type| of special extension nodes*/

@ A |math_node|, which occurs only in horizontal lists, appears before and
after mathematical formulas. The |subtype| field is |before| before the
formula and |after| after it. There is a |width| field, which represents
the amount of surrounding space inserted by \.{\\mathsurround}.

@d math_node 9 /*|type| of a math node*/
@d before 0 /*|subtype| for math node that introduces a formula*/
@d after 1 /*|subtype| for math node that winds up a formula*/

@<\TeX\ functions@>=
static pointer new_math(scaled @!w, small_number @!s)
{@+pointer p; /*the new node*/
p=get_node(small_node_size);type(p)=math_node;
subtype(p)=s;width(p)=w;return p;
}

@ \TeX\ makes use of the fact that |hlist_node|, |vlist_node|,
|rule_node|, |ins_node|, |mark_node|, |adjust_node|, |ligature_node|,
|disc_node|, |whatsit_node|, and |math_node| are at the low end of the
type codes, by permitting a break at glue in a list if and only if the
|type| of the previous node is less than |math_node|. Furthermore, a
node is discarded after a break if its type is |math_node| or~more.

@d precedes_break(A) (type(A) < math_node)
@d non_discardable(A) (type(A) < math_node)

@ A |glue_node| represents glue in a list. However, it is really only
a pointer to a separate glue specification, since \TeX\ makes use of the
fact that many essentially identical nodes of glue are usually present.
If |p| points to a |glue_node|, |glue_ptr(p)| points to
another packet of words that specify the stretch and shrink components, etc.

Glue nodes also serve to represent leaders; the |subtype| is used to
distinguish between ordinary glue (which is called |normal|) and the three
kinds of leaders (which are called |a_leaders|, |c_leaders|, and |x_leaders|).
The |leader_ptr| field points to a rule node or to a box node containing the
leaders; it is set to |null| in ordinary glue nodes.

Many kinds of glue are computed from \TeX's ``skip'' parameters, and
it is helpful to know which parameter has led to a particular glue node.
Therefore the |subtype| is set to indicate the source of glue, whenever
it originated as a parameter. We will be defining symbolic names for the
parameter numbers later (e.g., |line_skip_code==0|, |baseline_skip_code==1|,
etc.); it suffices for now to say that the |subtype| of parametric glue
will be the same as the parameter number, plus~one.

In math formulas there are two more possibilities for the |subtype| in a
glue node: |mu_glue| denotes an \.{\\mskip} (where the units are scaled \.{mu}
instead of scaled \.{pt}); and |cond_math_glue| denotes the `\.{\\nonscript}'
feature that cancels the glue node immediately following if it appears
in a subscript.

@d glue_node 10 /*|type| of node that points to a glue specification*/
@d mu_glue 99 /*|subtype| for math glue*/
@d a_leaders 100 /*|subtype| for aligned leaders*/
@d c_leaders 101 /*|subtype| for centered leaders*/
@d x_leaders 102 /*|subtype| for expanded leaders*/
@d glue_ptr(A) llink(A) /*pointer to a glue specification*/
@d leader_ptr(A) rlink(A) /*pointer to box or rule node for leaders*/

@ A glue specification has a halfword reference count in its first word,
@^reference counts@>
representing |null| plus the number of glue nodes that point to it (less one).
Note that the reference count appears in the same position as
the |link| field in list nodes; this is the field that is initialized
to |null| when a node is allocated, and it is also the field that is flagged
by |empty_flag| in empty nodes.

Glue specifications also contain three |scaled| fields, for the |width|,
|stretch|, and |shrink| dimensions. Finally, there are two one-byte
fields called |stretch_order| and |shrink_order|; these contain the
orders of infinity (|normal|, |fil|, |fill|, or |filll|)
corresponding to the stretch and shrink values.

@d glue_spec_size 4 /*number of words to allocate for a glue specification*/
@d glue_ref_count(A) link(A) /*reference count of a glue specification*/
@d stretch(A) mem[A+2].sc /*the stretchability of this glob of glue*/
@d shrink(A) mem[A+3].sc /*the shrinkability of this glob of glue*/
@d stretch_order(A) type(A) /*order of infinity for stretching*/
@d shrink_order(A) subtype(A) /*order of infinity for shrinking*/
@d fil 1 /*first-order infinity*/
@d fill 2 /*second-order infinity*/
@d filll 3 /*third-order infinity*/

@<Types...@>=
typedef int8_t glue_ord; /*infinity to the 0, 1, 2, or 3 power*/

@ Here is a function that returns a pointer to a copy of a glue spec.
The reference count in the copy is |null|, because there is assumed
to be exactly one reference to the new specification.

@<\TeX\ functions@>=
static pointer new_spec(pointer @!p) /*duplicates a glue specification*/
{@+pointer q; /*the new spec*/
q=get_node(glue_spec_size);@/
mem[q]=mem[p];glue_ref_count(q)=null;@/
width(q)=width(p);stretch(q)=stretch(p);shrink(q)=shrink(p);
return q;
}

@ Glue nodes that are more or less anonymous are created by |new_glue|,
whose argument points to a glue specification.

@<\TeX\ functions@>=
static pointer new_glue(pointer @!q)
{@+pointer p; /*the new node*/
p=get_node(small_node_size);type(p)=glue_node;subtype(p)=normal;
leader_ptr(p)=null;glue_ptr(p)=q;incr(glue_ref_count(q));
return p;
}

@ A |kern_node| has a |width| field to specify a (normally negative)
amount of spacing. This spacing correction appears in horizontal lists
between letters like A and V when the font designer said that it looks
better to move them closer together or further apart. A kern node can
also appear in a vertical list, when its `|width|' denotes additional
spacing in the vertical direction. The |subtype| is either |normal| (for
kerns inserted from font information or math mode calculations) or |explicit|
(for kerns inserted from \.{\\kern} and \.{\\/} commands) or |acc_kern|
(for kerns inserted from non-math accents) or |mu_glue| (for kerns
inserted from \.{\\mkern} specifications in math formulas).

@d kern_node 11 /*|type| of a kern node*/
@d explicit 1 /*|subtype| of kern nodes from \.{\\kern} and \.{\\/}*/
@d acc_kern 2 /*|subtype| of kern nodes from accents*/

@ The |new_kern| function creates a kern node having a given width.

@<\TeX\ functions@>=
static pointer new_kern(scaled @!w)
{@+pointer p; /*the new node*/
p=get_node(small_node_size);type(p)=kern_node;
subtype(p)=normal;
width(p)=w;
return p;
}

@ A |penalty_node| specifies the penalty associated with line or page
breaking, in its |penalty| field. This field is a fullword integer, but
the full range of integer values is not used: Any penalty | >= 10000| is
treated as infinity, and no break will be allowed for such high values.
Similarly, any penalty | <= -10000| is treated as negative infinity, and a
break will be forced.

@d penalty_node 12 /*|type| of a penalty node*/
@d inf_penalty inf_bad /*``infinite'' penalty value*/
@d eject_penalty (-inf_penalty) /*``negatively infinite'' penalty value*/
@d penalty(A) mem[A+1].i /*the added cost of breaking a list here*/

@ Anyone who has been reading the last few sections of the program will
be able to guess what comes next.

@<\TeX\ functions@>=
static pointer new_penalty(int @!m)
{@+pointer p; /*the new node*/
p=get_node(small_node_size);type(p)=penalty_node;
subtype(p)=0; /*the |subtype| is not used*/
penalty(p)=m;return p;
}

@ You might think that we have introduced enough node types by now. Well,
almost, but there is one more: An |unset_node| has nearly the same format
as an |hlist_node| or |vlist_node|; it is used for entries in \.{\\halign}
or \.{\\valign} that are not yet in their final form, since the box
dimensions are their ``natural'' sizes before any glue adjustment has been
made. The |glue_set| word is not present; instead, we have a |glue_stretch|
field, which contains the total stretch of order |glue_order| that is
present in the hlist or vlist being boxed.
Similarly, the |shift_amount| field is replaced by a |glue_shrink| field,
containing the total shrink of order |glue_sign| that is present.
The |subtype| field is called |span_count|; an unset box typically
contains the data for |qo(span_count)+1| columns.
Unset nodes will be changed to box nodes when alignment is completed.

@d unset_node 13 /*|type| for an unset node*/
@d glue_stretch(A) mem[A+glue_offset].sc /*total stretch in an unset node*/
@d glue_shrink(A) shift_amount(A) /*total shrink in an unset node*/
@d span_count(A) subtype(A) /*indicates the number of spanned columns*/

@ In fact, there are still more types coming. When we get to math formula
processing we will see that a |style_node| has |type==14|; and a number
of larger type codes will also be defined, for use in math mode only.

@ Warning: If any changes are made to these data structure layouts, such as
changing any of the node sizes or even reordering the words of nodes,
the |copy_node_list| procedure and the memory initialization code
below may have to be changed. Such potentially dangerous parts of the
program are listed in the index under `data structure assumptions'.
@!@^data structure assumptions@>
However, other references to the nodes are made symbolically in terms of
the \.{WEB} macro definitions above, so that format changes will leave
\TeX's other algorithms intact.
@^system dependencies@>

@* Memory layout.
Some areas of |mem| are dedicated to fixed usage, since static allocation is
more efficient than dynamic allocation when we can get away with it. For
example, locations |mem_bot| to |mem_bot+3| are always used to store the
specification for glue that is `\.{0pt plus 0pt minus 0pt}'. The
following macro definitions accomplish the static allocation by giving
symbolic names to the fixed positions. Static variable-size nodes appear
in locations |mem_bot| through |lo_mem_stat_max|, and static single-word nodes
appear in locations |hi_mem_stat_min| through |mem_top|, inclusive. It is
harmless to let |lig_trick| and |garbage| share the same location of |mem|.

@d zero_glue mem_bot /*specification for \.{0pt plus 0pt minus 0pt}*/
@d lo_mem_stat_max zero_glue+glue_spec_size-1 /*largest statically allocated word in the variable-size |mem|*/
@#
@d page_ins_head mem_top /*list of insertion data for current page*/
@d contrib_head mem_top-1 /*vlist of items not yet on current page*/
@d page_head mem_top-2 /*vlist for current page*/
@d temp_head mem_top-3 /*head of a temporary list of some kind*/
@d hold_head mem_top-4 /*head of a temporary list of another kind*/
@d adjust_head mem_top-5 /*head of adjustment list returned by |hpack|*/
@d active mem_top-7 /*head of active list in |line_break|, needs two words*/
@d lig_trick mem_top-12 /*a ligature masquerading as a |char_node|*/
@d hi_mem_stat_min mem_top-13 /*smallest statically allocated word in
  the one-word |mem|*/
@d hi_mem_stat_usage 14 /*the number of one-word nodes always present*/


@ @<\TeX\ functions@>=
static void mem_init(void)
{ @+ int k;
  @<Initialize |mem|@>@;
}

@ @<Initialize |mem|@>=
for (k=mem_bot+1; k<=lo_mem_stat_max; k++) mem[k].sc=0;
   /*all glue dimensions are zeroed*/
@^data structure assumptions@>
k=mem_bot;@+while (k <= lo_mem_stat_max)
     /*set first words of glue specifications*/
  {@+glue_ref_count(k)=null+1;
  stretch_order(k)=normal;shrink_order(k)=normal;
  k=k+glue_spec_size;
  }
rover=lo_mem_stat_max+1;
link(rover)=empty_flag; /*now initialize the dynamic memory*/
node_size(rover)=1000; /*which is a 1000-word available node*/
llink(rover)=rover;rlink(rover)=rover;@/
lo_mem_max=rover+1000;link(lo_mem_max)=null;info(lo_mem_max)=null;@/
for (k=hi_mem_stat_min; k<=mem_top; k++)
  mem[k]=mem[lo_mem_max]; /*clear list heads*/
@<Initialize the special list heads and constant nodes@>;
avail=null;
hi_mem_min=hi_mem_stat_min; /*initialize the one-word memory*/
var_used=lo_mem_stat_max+1-mem_bot;dyn_used=hi_mem_stat_usage;
   /*initialize statistics*/


@* Displaying boxes.
We can reinforce our knowledge of the data structures just introduced
by considering two procedures that display a list in symbolic form.
The first of these, called |short_display|, is used in ``overfull box''
messages to give the top-level description of a list. The other one,
called |show_node_list|, prints a detailed description of exactly what
is in the data structure.

The philosophy of |short_display| is to ignore the fine points about exactly
what is inside boxes, except that ligatures and discretionary breaks are
expanded. As a result, |short_display| is a recursive procedure, but the
recursion is never more than one level deep.
@^recursion@>

A global variable |font_in_short_display| keeps track of the font code that
is assumed to be present when |short_display| begins; deviations from this
font will be printed.

@<Basic printing procedures@>=
static int @!font_in_short_display; /*an internal font number*/

@ Boxes, rules, inserts, whatsits, marks, and things in general that are
sort of ``complicated'' are indicated only by printing `\.{[]}'.

@<Basic printing procedures@>=
static void short_display(int @!p) /*prints highlights of list |p|*/
{@+int n; /*for replacement counts*/
while (p > mem_min)
  {@+if (is_char_node(p))
    {@+if (p <= mem_end)
      {@+if (font(p)!=font_in_short_display)
        {@+if ((font(p) < font_base)||(font(p) > font_max))
          print_char('*');
@.*\relax@>
        else@<Print the font identifier for |font(p)|@>;
        print_char(' ');font_in_short_display=font(p);
        }
      print_ASCII(qo(character(p)));
      }
    }
  else@<Print a short indication of the contents of node |p|@>;
  p=link(p);
  }
}

@ @<Print a short indication of the contents of node |p|@>=
switch (type(p)) {
case hlist_node: case vlist_node: case ins_node:
  case whatsit_node: case mark_node: case adjust_node:
  case unset_node: print("[]");@+break;
case rule_node: print_char('|');@+break;
case glue_node: if (glue_ptr(p)!=zero_glue) print_char(' ');@+break;
case math_node: print_char('$');@+break;
case ligature_node: short_display(lig_ptr(p));@+break;
case disc_node: {@+short_display(pre_break(p));
  short_display(post_break(p));@/
  n=replace_count(p);
  while (n > 0)
    {@+if (link(p)!=null) p=link(p);
    decr(n);
    }
  } @+break;
default:do_nothing;
}

@ The |show_node_list| routine requires some auxiliary subroutines: one to
print a font-and-character combination, one to print a token list without
its reference count, and one to print a rule dimension.

@<Basic printing procedures@>=
static void print_font_and_char(int @!p) /*prints |char_node| data*/
{@+if (p > mem_end) print_esc("CLOBBERED.");
else{@<Print the font identifier for |font(p)|@>;
  print_char(' ');print_ASCII(character(p));
  }
}
@#
static void print_mark(int @!p) /*prints token list data in braces*/
{@+print_char('{');print_char('}');@+
}
@#
static void print_rule_dimen(scaled @!d) /*prints dimension in rule node*/
{@+if (is_running(d)) print_char('*');else print_scaled(d);
@.*\relax@>
}

@ Then there is a subroutine that prints glue stretch and shrink, possibly
followed by the name of finite units:

@<Basic printing procedures@>=
   static void print_glue(scaled @!d, int @!order, char *@!s)
   /*prints a glue component*/
{@+print_scaled(d);
if ((order < normal)||(order > filll)) print("foul");
else if (order > normal)
  {@+print("fil");
  while (order > fil)
    {@+print_char('l');decr(order);
    }
  }
else if (s!=0) print(s);
}

@ The next subroutine prints a whole glue specification.

@<Basic printing procedures@>=
  static void print_spec(int @!p, char *@!s)
   /*prints a glue specification*/
{@+if ((p < mem_min)||(p >= lo_mem_max)) print_char('*');
@.*\relax@>
else{@+print_scaled(width(p));
  if (s!=0) print(s);
  if (stretch(p)!=0)
    {@+print(" plus ");print_glue(stretch(p), stretch_order(p), s);
    }
  if (shrink(p)!=0)
    {@+print(" minus ");print_glue(shrink(p), shrink_order(p), s);
    }
  }
}


@ Since boxes can be inside of boxes, |show_node_list| is inherently recursive,
@^recursion@>
up to a given maximum number of levels.  The history of nesting is indicated
by the current string, which will be printed at the beginning of each line;
the length of this string, namely |cur_length|, is the depth of nesting.

Recursive calls on |show_node_list| therefore use the following pattern:

@d node_list_display(A)
  {@+depth_level++;show_node_list(A);depth_level--;
  }

@ Now we are ready for |show_node_list| itself. This procedure has been
written to be ``extra robust'' in the sense that it should not crash or get
into a loop even if the data structures have been messed up by bugs in
the rest of the program. You can safely call its parent routine
|show_box(p)| for arbitrary values of |p| when you are debugging \TeX.
However, in the presence of bad data, the procedure may
@^dirty \PASCAL@>@^debugging@>
fetch a |memory_word| whose variant is different from the way it was stored;
for example, it might try to read |mem[p].hh| when |mem[p]|
contains a scaled integer, if |p| is a pointer that has been
clobbered or chosen at random.

@ @<Basic printing procedures@>=
static void show_node_list(int @!p) /*prints a node list symbolically*/
{@+
int n; /*the number of items already printed at this level*/
double @!g; /*a glue ratio, as a floating point number*/
if (depth_level > depth_threshold)
  {@+if (p > null) print(" []");
     /*indicate that there's been some truncation*/
  return;
  }
n=0;
while (p > mem_min)
  {@+print_ln();print_current_string(); /*display the nesting history*/
  if (p > mem_end)  /*pointer out of range*/
    {@+print("Bad link, display aborted.");return;
@.Bad link...@>
    }
  incr(n);if (n > breadth_max)  /*time to stop*/
    {@+print("etc.");return;
@.etc@>
    }
  @<Display node |p|@>;
  p=link(p);
  }

}

@ @<Display node |p|@>=
if (is_char_node(p)) print_font_and_char(p);
else switch (type(p)) {
  case hlist_node: case vlist_node: case unset_node: @<Display box |p|@>@;@+break;
  case rule_node: @<Display rule |p|@>@;@+break;
  case ins_node: @<Display insertion |p|@>@;@+break;
  case whatsit_node: @<Display the whatsit node |p|@>@;@+break;
  case glue_node: @<Display glue |p|@>@;@+break;
  case kern_node: @<Display kern |p|@>@;@+break;
  case math_node: @<Display math node |p|@>@;@+break;
  case ligature_node: @<Display ligature |p|@>@;@+break;
  case penalty_node: @<Display penalty |p|@>@;@+break;
  case disc_node: @<Display discretionary |p|@>@;@+break;
  case adjust_node: @<Display adjustment |p|@>@;@+break;
  default:print("Unknown node type!");
  }

@ @<Display box |p|@>=
{@+if (type(p)==hlist_node) print_esc("h");
else if (type(p)==vlist_node) print_esc("v");
else print_esc("unset");
print("box(");print_scaled(height(p));print_char('+');
print_scaled(depth(p));print(")x");print_scaled(width(p));
if (type(p)==unset_node)
  @<Display special fields of the unset node |p|@>@;
else{@+@<Display the value of |glue_set(p)|@>;
  if (shift_amount(p)!=0)
    {@+print(", shifted ");print_scaled(shift_amount(p));
    }
  }
node_list_display(list_ptr(p)); /*recursive call*/
}

@ @<Display special fields of the unset node |p|@>=
{@+if (span_count(p)!=min_quarterword)
  {@+print(" (");print_int(qo(span_count(p))+1);
  print(" columns)");
  }
if (glue_stretch(p)!=0)
  {@+print(", stretch ");print_glue(glue_stretch(p), glue_order(p), 0);
  }
if (glue_shrink(p)!=0)
  {@+print(", shrink ");print_glue(glue_shrink(p), glue_sign(p), 0);
  }
}

@ The code will have to change in this place if |glue_ratio| is
a structured type instead of an ordinary |double|. Note that this routine
should avoid arithmetic errors even if the |glue_set| field holds an
arbitrary random value. The following code assumes that a properly
formed nonzero |double| number has absolute value $2^{20}$ or more when
it is regarded as an integer; this precaution was adequate to prevent
floating point underflow on the author's computer.
@^system dependencies@>
@^dirty \PASCAL@>

@<Display the value of |glue_set(p)|@>=
g=unfix(glue_set(p));
if ((g!=float_constant(0))&&(glue_sign(p)!=normal))
  {@+print(", glue set ");
  if (glue_sign(p)==shrinking) print("- ");
  if (abs(mem[p+glue_offset].i) < 04000000) print("?.?");
  else if (abs(g) > float_constant(20000))
    {@+if (g > float_constant(0)) print_char('>');
    else print("< -");
    print_glue(20000*unity, glue_order(p), 0);
    }
  else print_glue(round(unity*g), glue_order(p), 0);
@^real multiplication@>
  }

@ @<Display rule |p|@>=
{@+print_esc("rule(");print_rule_dimen(height(p));print_char('+');
print_rule_dimen(depth(p));print(")x");print_rule_dimen(width(p));
}

@ @<Display insertion |p|@>=
{@+print_esc("insert");print_int(qo(subtype(p)));
print(", natural size ");print_scaled(height(p));
print("; split(");print_spec(split_top_ptr(p), 0);
print_char(',');print_scaled(depth(p));
print("); float cost ");print_int(float_cost(p));
node_list_display(ins_ptr(p)); /*recursive call*/
}

@ @<Display glue |p|@>=
if (subtype(p) >= a_leaders) @<Display leaders |p|@>@;
else{@+print_esc("glue "); print_spec(glue_ptr(p), 0);@+ }

@ @<Display leaders |p|@>=
{@+print_esc("");
if (subtype(p)==c_leaders) print_char('c');
else if (subtype(p)==x_leaders) print_char('x');
print("leaders ");print_spec(glue_ptr(p), 0);
node_list_display(leader_ptr(p)); /*recursive call*/
}

@ An ``explicit'' kern value is indicated implicitly by an explicit space.

@<Display kern |p|@>=
if (subtype(p)!=mu_glue)
  {@+print_esc("kern");
  print_char(' ');
  print_scaled(width(p));
  if (subtype(p)==acc_kern) print(" (for accent)");
@.for accent@>
  }
else{@+print_esc("mkern");print_scaled(width(p));print("mu");
  }

@ @<Display math node |p|@>=
{@+print_esc("math");
if (subtype(p)==before) print("on");
else print("off");
if (width(p)!=0)
  {@+print(", surrounded ");print_scaled(width(p));
  }
}

@ @<Display ligature |p|@>=
{@+print_font_and_char(lig_char(p));print(" (ligature ");
if (subtype(p) > 1) print_char('|');
font_in_short_display=font(lig_char(p));short_display(lig_ptr(p));
if (odd(subtype(p))) print_char('|');
print_char(')');
}

@ @<Display penalty |p|@>=
{@+print_esc("penalty ");print_int(penalty(p));
}

@ The |post_break| list of a discretionary node is indicated by a prefixed
`\.{\char'174}' instead of the `\..' before the |pre_break| list.

@<Display discretionary |p|@>=
{@+print_esc("discretionary");
if (replace_count(p) > 0)
  {@+print(" replacing ");print_int(replace_count(p));
  }
node_list_display(pre_break(p)); /*recursive call*/
node_list_display(post_break(p)); /*recursive call*/
}


@ @<Display adjustment |p|@>=
{@+print_esc("vadjust");node_list_display(adjust_ptr(p)); /*recursive call*/
}

@ The recursive machinery is started by calling |show_box|.
@^recursion@>

@<Basic printing procedures@>=
static void show_box(pointer @!p)
{@+depth_threshold=200; breadth_max=200;
show_node_list(p); /*the show starts at |p|*/
print_ln();
}

@* Destroying boxes.
When we are done with a node list, we are obliged to return it to free
storage, including all of its sublists. The recursive procedure
|flush_node_list| does this for us.

@ First, however, we shall consider two non-recursive procedures that do
simpler tasks. The first of these, |delete_token_ref|, is called when
a pointer to a token list's reference count is being removed. This means
that the token list should disappear if the reference count was |null|,
otherwise the count should be decreased by one.
@^reference counts@>

@d token_ref_count(A) info(A) /*reference count preceding a token list*/

@ Similarly, |delete_glue_ref| is called when a pointer to a glue
specification is being withdrawn.
@^reference counts@>
@d fast_delete_glue_ref(A) @t@>@;@/
  {@+if (glue_ref_count(A)==null) free_node(A, glue_spec_size);
  else decr(glue_ref_count(A));
  }

@<\TeX\ functions@>=
static void delete_glue_ref(pointer @!p) /*|p| points to a glue specification*/
fast_delete_glue_ref(p)
static void delete_xdimen_ref(pointer @!p) /*|p| points to a xdimen specification*/
{@+if (p==null) return;
  if (xdimen_ref_count(p)==null) free_node(p, xdimen_node_size);
  else decr(xdimen_ref_count(p));
}

@ Now we are ready to delete any node list, recursively.
In practice, the nodes deleted are usually charnodes (about 2/3 of the time),
and they are glue nodes in about half of the remaining cases.
@^recursion@>

@<\TeX\ functions@>=
static void flush_node_list(pointer @!p) /*erase list of nodes starting at |p|*/
{@+ /*go here when node |p| has been freed*/
pointer q; /*successor to node |p|*/
while (p!=null)
@^inner loop@>
  {@+q=link(p);
  if (is_char_node(p)) free_avail(p)@;
  else{@+switch (type(p)) {
    case hlist_node: case vlist_node:
  case unset_node: {@+flush_node_list(list_ptr(p));
      free_node(p, box_node_size);goto done;
      }
    case rule_node: {@+free_node(p, rule_node_size);goto done;
      }
    case ins_node: {@+flush_node_list(ins_ptr(p));
      delete_glue_ref(split_top_ptr(p));
      free_node(p, ins_node_size);goto done;
      }
    case whatsit_node: @<Wipe out the whatsit node |p| and |goto done|@>@;
    case glue_node: {@+fast_delete_glue_ref(glue_ptr(p));
      if (leader_ptr(p)!=null) flush_node_list(leader_ptr(p));
      } @+break;
    case kern_node: case math_node: case penalty_node: do_nothing;@+break;
    case ligature_node: flush_node_list(lig_ptr(p));@+break;
    case disc_node: {@+flush_node_list(pre_break(p));
      flush_node_list(post_break(p));
      } @+break;
    case adjust_node: flush_node_list(adjust_ptr(p));@+break;
    default:QUIT("Confusion while flushing node list");
@:this can't happen flushing}{\quad flushing@>
    } @/
    free_node(p, small_node_size);
    done: ;}
  p=q;
  }
}

@* Copying boxes.
Another recursive operation that acts on boxes is sometimes needed: The
procedure |copy_node_list| returns a pointer to another node list that has
the same structure and meaning as the original. Note that since glue
specifications and token lists have reference counts, we need not make
copies of them. Reference counts can never get too large to fit in a
halfword, since each pointer to a node is in a different memory address,
and the total number of memory addresses fits in a halfword.
@^recursion@>
@^reference counts@>

(Well, there actually are also references from outside |mem|; if the
|save_stack| is made arbitrarily large, it would theoretically be possible
to break \TeX\ by overflowing a reference count. But who would want to do that?)

@d add_token_ref(A) incr(token_ref_count(A)) /*new reference to a token list*/
@d add_glue_ref(A) incr(glue_ref_count(A)) /*new reference to a glue spec*/
@d add_xdimen_ref(A) if (A!=null) incr(xdimen_ref_count(A)) /*new reference to an xdimen*/

@ The copying procedure copies words en masse without bothering
to look at their individual fields. If the node format changes---for
example, if the size is altered, or if some link field is moved to another
relative position---then this code may need to be changed too.
@^data structure assumptions@>

@<\TeX\ functions@>=
static pointer copy_node_list(pointer @!p) /*makes a duplicate of the
  node list that starts at |p| and returns a pointer to the new list*/
{@+pointer h; /*temporary head of copied list*/
pointer @!q; /*previous position in new list*/
pointer @!r; /*current node being fabricated for new list*/
int @!words; /*number of words remaining to be copied*/
h=get_avail();q=h;
while (p!=null)
  {@+@<Make a copy of node |p| in node |r|@>;
  link(q)=r;q=r;p=link(p);
  }
link(q)=null;q=link(h);free_avail(h);
return q;
}

@ @<Make a copy of node |p|...@>=
words=1; /*this setting occurs in more branches than any other*/
if (is_char_node(p)) r=get_avail();
else@<Case statement to copy different types and set |words| to the number
of initial words not yet copied@>;
while (words > 0)
  {@+decr(words);mem[r+words]=mem[p+words];
  }

@ @<Case statement to copy...@>=
switch (type(p)) {
case hlist_node: case vlist_node: case unset_node: {@+r=get_node(box_node_size);
  mem[r+6]=mem[p+6];mem[r+5]=mem[p+5]; /*copy the last two words*/
  list_ptr(r)=copy_node_list(list_ptr(p)); /*this affects |mem[r+5]|*/
  words=5;
  } @+break;
case rule_node: {@+r=get_node(rule_node_size);words=rule_node_size;
  } @+break;
case ins_node: {@+r=get_node(ins_node_size);mem[r+4]=mem[p+4];
  add_glue_ref(split_top_ptr(p));
  ins_ptr(r)=copy_node_list(ins_ptr(p)); /*this affects |mem[r+4]|*/
  words=ins_node_size-1;
  } @+break;
case whatsit_node: @<Make a partial copy of the whatsit node |p| and make
|r| point to it; set |words| to the number of initial words not yet copied@>@;@+break;
case glue_node: {@+r=get_node(small_node_size);add_glue_ref(glue_ptr(p));
  glue_ptr(r)=glue_ptr(p);leader_ptr(r)=copy_node_list(leader_ptr(p));
  } @+break;
case kern_node: case math_node: case penalty_node: {@+r=get_node(small_node_size);
  words=small_node_size;
  } @+break;
case ligature_node: {@+r=get_node(small_node_size);
  mem[lig_char(r)]=mem[lig_char(p)]; /*copy |font| and |character|*/
  lig_ptr(r)=copy_node_list(lig_ptr(p));
  } @+break;
case disc_node: {@+r=get_node(small_node_size);
  pre_break(r)=copy_node_list(pre_break(p));
  post_break(r)=copy_node_list(post_break(p));
  } @+break;
case mark_node: {@+r=get_node(small_node_size);add_token_ref(mark_ptr(p));
  words=small_node_size;
  } @+break;
case adjust_node: {@+r=get_node(small_node_size);
  adjust_ptr(r)=copy_node_list(adjust_ptr(p));
  } @+break; /*|words==1==small_node_size-1|*/
default:confusion("copying");
@:this can't happen copying}{\quad copying@>
}

@* The command codes.
Before we can go any further, we need to define symbolic names for the internal
code numbers that represent the various commands obeyed by \TeX. These codes
are somewhat arbitrary, but not completely so. For example, the command
codes for character types are fixed by the language, since a user says,
e.g., `\.{\\catcode \`\\\${} = 3}' to make \.{\char'44} a math delimiter,
and the command code |math_shift| is equal to~3. Some other codes have
been made adjacent so that |case| statements in the program need not consider
cases that are widely spaced, or so that |case| statements can be replaced
by |if| statements.

At any rate, here is the list, for future reference. First come the
``catcode'' commands, several of which share their numeric codes with
ordinary commands when the catcode cannot emerge from \TeX's scanning routine.


@d relax 0 /*do nothing ( \.{\\relax} )*/

@ Next are the ordinary run-of-the-mill command codes.  Codes that are
|min_internal| or more represent internal quantities that might be
expanded by `\.{\\the}'.

@d insert 37 /*vlist inserted in box ( \.{\\insert} )*/
@d accent 45 /*attach accent in text ( \.{\\accent} )*/

@ The next codes are special; they all relate to mode-independent
assignment of values to \TeX's internal registers or tables.
Codes that are |max_internal| or less represent internal quantities
that might be expanded by `\.{\\the}'.

@d max_command 100 /*the largest command code seen at |big_switch|*/

@ The remaining command codes are extra special, since they cannot get through
\TeX's scanner to the main control routine. They have been given values higher
than |max_command| so that their special nature is easily discernible.
The ``expandable'' commands come first.

@d the (max_command+9) /*expand an internal quantity ( \.{\\the} )*/
@d data (max_command+20) /*the equivalent is simply a halfword number*/

@* The semantic nest.
\TeX\ is typically in the midst of building many lists at once. For example,
when a math formula is being processed, \TeX\ is in math mode and
working on an mlist; this formula has temporarily interrupted \TeX\ from
being in horizontal mode and building the hlist of a paragraph; and this
paragraph has temporarily interrupted \TeX\ from being in vertical mode
and building the vlist for the next page of a document. Similarly, when a
\.{\\vbox} occurs inside of an \.{\\hbox}, \TeX\ is temporarily
interrupted from working in restricted horizontal mode, and it enters
internal vertical mode.  The ``semantic nest'' is a stack that
keeps track of what lists and modes are currently suspended.

At each level of processing we are in one of six modes:

\yskip\hang|vmode| stands for vertical mode (the page builder);

\hang|hmode| stands for horizontal mode (the paragraph builder);

\hang|mmode| stands for displayed formula mode;

\hang|-vmode| stands for internal vertical mode (e.g., in a \.{\\vbox});

\hang|-hmode| stands for restricted horizontal mode (e.g., in an \.{\\hbox});

\hang|-mmode| stands for math formula mode (not displayed).

\yskip\noindent The mode is temporarily set to zero while processing \.{\\write}
texts.

Numeric values are assigned to |vmode|, |hmode|, and |mmode| so that
\TeX's ``big semantic switch'' can select the appropriate thing to
do by computing the value |abs(mode)+cur_cmd|, where |mode| is the current
mode and |cur_cmd| is the current command code.

@d vmode 1 /*vertical mode*/
@d hmode (vmode+max_command+1) /*horizontal mode*/

@ The state of affairs at any semantic level can be represented by
five values:

\yskip\hang|mode| is the number representing the semantic mode, as
just explained.

\yskip\hang|head| is a |pointer| to a list head for the list being built;
|link(head)| therefore points to the first element of the list, or
to |null| if the list is empty.

\yskip\hang|tail| is a |pointer| to the final node of the list being
built; thus, |tail==head| if and only if the list is empty.

\yskip\hang|prev_graf| is the number of lines of the current paragraph that
have already been put into the present vertical list.

\yskip\hang|aux| is an auxiliary |memory_word| that gives further information
that is needed to characterize the situation.

\yskip\noindent
In vertical mode, |aux| is also known as |prev_depth|; it is the scaled
value representing the depth of the previous box, for use in baseline
calculations, or it is | <= -1000|pt if the next box on the vertical list is to
be exempt from baseline calculations.  In horizontal mode, |aux| is also
known as |space_factor| and |clang|; it holds the current space factor used in
spacing calculations, and the current language used for hyphenation.
(The value of |clang| is undefined in restricted horizontal mode.)
In math mode, |aux| is also known as |incompleat_noad|; if
not |null|, it points to a record that represents the numerator of a
generalized fraction for which the denominator is currently being formed
in the current list.

There is also a sixth quantity, |mode_line|, which correlates
the semantic nest with the user's input; |mode_line| contains the source
line number at which the current level of nesting was entered. The negative
of this line number is the |mode_line| at the level of the
user's output routine.

In horizontal mode, the |prev_graf| field is used for initial language data.

The semantic nest is an array called |nest| that holds the |mode|, |head|,
|tail|, |prev_graf|, |aux|, and |mode_line| values for all semantic levels
below the currently active one. Information about the currently active
level is kept in the global quantities |mode|, |head|, |tail|, |prev_graf|,
|aux|, and |mode_line|, which live in a \PASCAL\ record that is ready to
be pushed onto |nest| if necessary.

@d ignore_depth -65536000 /*|prev_depth| value that is ignored*/

@<Types...@>=
typedef struct { int16_t @!mode_field;@+
  pointer @!head_field, @!tail_field;
 int pg_field;
 pointer bs_field,ls_field; /* baseline skip and line skip */
 scaled lsl_field; /* line skip limit */
 uint8_t *bs_pos; /* position of baseline skip node */
 scaled hs_field; /* horizontal size */
 scaled ds_field, dw_field, di_field; /*display size, width, and indent */
 scaled ht_field; /* height of last box added to the list */
 uint32_t np_field; /* position of current node */
  memory_word @!aux_field;
  } list_state_record;

@ @d mode cur_list.mode_field /*current mode*/
@d head cur_list.head_field /*header node of current list*/
@d tail cur_list.tail_field /*final node on current list*/
@d prev_graf cur_list.pg_field /*number of paragraph lines accumulated*/
@d aux cur_list.aux_field /*auxiliary data about the current list*/
@d prev_depth aux.sc /*the name of |aux| in vertical mode*/
@d cur_bs cur_list.bs_field /*baseline skip glue specification*/
@d cur_ls cur_list.ls_field /*line skip glue specification*/
@d cur_lsl cur_list.lsl_field /*line skip limit*/
@d needs_bs (cur_list.bs_pos!=NULL) /*is a baseline skip needed?*/
@d prev_height cur_list.ht_field /* height of previous box */
@d node_pos cur_list.np_field /*node position in the \HINT/ file or |NULL|*/
@d node_pos1 (nest_ptr==0?0:nest[nest_ptr-1].np_field) /*position of enclosing node*/

@<List variables@>=
static list_state_record @!nest[nest_size+1];
static int @!nest_ptr; /*first unused location of |nest|*/
static int @!max_nest_stack; /*maximum of |nest_ptr| when pushing*/
static list_state_record @!cur_list; /*the ``top'' semantic state*/

@ Here is a common way to make the current list grow:

@d tail_append(A) {@+link(tail)=A;tail=link(tail);
  }

@ We will see later that the vertical list at the bottom semantic level is split
into two parts; the ``current page'' runs from |page_head| to |page_tail|,
and the ``contribution list'' runs from |contrib_head| to |tail| of
semantic level zero. The idea is that contributions are first formed in
vertical mode, then ``contributed'' to the current page (during which time
the page-breaking decisions are made). For now, we don't need to know
any more details about the page-building process.

@<\TeX\ functions@>=

@<List variables@>@;

static void list_init(void)
{@+
nest_ptr=0;max_nest_stack=0;@/
memset(&cur_list,0,sizeof(cur_list));
mode=vmode;head=contrib_head;tail=contrib_head;
prev_height=prev_depth=ignore_depth;
}

@ When \TeX's work on one level is interrupted, the state is saved by
calling |push_nest|. This routine changes |head| and |tail| so that
a new (empty) list is begun; it does not change |mode| or |aux|.

@s line mode_line
@<\TeX\ functions@>=
static void push_nest(void) /*enter a new semantic level, save the old*/
{@+if (nest_ptr > max_nest_stack)
  {@+max_nest_stack=nest_ptr;
  if (nest_ptr==nest_size) overflow("semantic nest size", nest_size);
@:TeX capacity exceeded semantic nest size}{\quad semantic nest size@>
  }
nest[nest_ptr]=cur_list; /*stack the record*/
incr(nest_ptr);head=get_avail();tail=head;prev_graf=0;
cur_list.bs_pos=NULL; cur_bs=baseline_skip; cur_ls=line_skip; cur_lsl=line_skip_limit;
}

@ Conversely, when \TeX\ is finished on the current level, the former
state is restored by calling |pop_nest|. This routine will never be
called at the lowest semantic level, nor will it be called unless |head|
is a node that should be returned to free memory.

@<\TeX\ functions@>=
static void pop_nest(void) /*leave a semantic level, re-enter the old*/
{@+free_avail(head);decr(nest_ptr);cur_list=nest[nest_ptr];
}

@* The table of equivalents.

@ Region 3 of |eqtb| contains the 256 \.{\\skip} registers, as well as the
glue parameters defined here. It is important that the ``muskip''
parameters have larger numbers than the others.

@d right_skip_code 8 /*glue at right of justified lines*/
@#
@d line_skip pointer_def[glue_kind][line_skip_no]
@d baseline_skip pointer_def[glue_kind][baseline_skip_no]
@d left_skip pointer_def[glue_kind][left_skip_no]
@d right_skip pointer_def[glue_kind][right_skip_no]
@d top_skip pointer_def[glue_kind][top_skip_no]
@d split_top_skip pointer_def[glue_kind][split_top_skip_no]


@ Region 4 of |eqtb| contains the local quantities defined here. The
bulk of this region is taken up by five tables that are indexed by eight-bit
characters; these tables are important to both the syntactic and semantic
portions of \TeX. There are also a bunch of special things like font and
token parameters, as well as the tables of \.{\\toks} and \.{\\box}
registers.

@d par_shape_ptr null
@d box(A) (*box_ptr(A))


@ Region 5 of |eqtb| contains the integer parameters and registers defined
here, as well as the |del_code| table. The latter table differs from the
|cat_code dotdot math_code| tables that precede it, since delimiter codes are
fullword integers while the other kinds of codes occupy at most a
halfword. This is what makes region~5 different from region~4. We will
store the |eq_level| information in an auxiliary array of quarterwords
that will be defined later.

@d pretolerance integer_def[pretolerance_no]
@d tolerance integer_def[tolerance_no]
@d line_penalty integer_def[line_penalty_no]
@d hyphen_penalty integer_def[hyphen_penalty_no]
@d ex_hyphen_penalty integer_def[ex_hyphen_penalty_no]
@d club_penalty integer_def[club_penalty_no]
@d display_widow_penalty integer_def[display_widow_penalty_no]
@d broken_penalty integer_def[broken_penalty_no]
@d pre_display_penalty integer_def[pre_display_penalty_no]
@d post_display_penalty integer_def[post_display_penalty_no]
@d inter_line_penalty integer_def[inter_line_penalty_no]
@d double_hyphen_demerits integer_def[double_hyphen_demerits_no]
@d final_hyphen_demerits integer_def[final_hyphen_demerits_no]
@d adj_demerits integer_def[adj_demerits_no]
@d looseness integer_def[looseness_no]
@d tracing_paragraphs (debugflags&DBGTEX)
@d tracing_pages (debugflags&DBGPAGE)
@d hang_after integer_def[hang_after_no]


@ The final region of |eqtb| contains the dimension parameters defined
here, and the 256 \.{\\dimen} registers.

@d line_skip_limit dimen_def[line_skip_limit_no]
@d max_depth dimen_def[max_depth_no]
@d pre_display_size cur_list.ds_field
@d display_width cur_list.dw_field
@d display_indent cur_list.di_field
@d hang_indent dimen_def[hang_indent_no]
@d emergency_stretch dimen_def[emergency_stretch_no]


@* The hash table.




@ We will deal with the other primitives later, at some point in the program
where their |eq_type| and |equiv| values are more meaningful.  For example,
the primitives for math mode will be loaded when we consider the routines
that deal with formulas. It is easy to find where each particular
primitive was treated by looking in the index at the end; for example, the
section where |"radical"| entered |eqtb| is listed under `\.{\\radical}
primitive'. (Primitives consisting of a single nonalphabetic character,
@!like `\.{\\/}', are listed under `Single-character primitives'.)
@!@^Single-character primitives@>

Meanwhile, this is a convenient place to catch up on something we were unable
to do before the hash table was defined:

@<Print the font identifier for |font(p)|@>=
print_esc(font_def[font(p)].n);

@* Saving and restoring equivalents.

@ Here are the group codes that are used to discriminate between different
kinds of groups. They allow \TeX\ to decide what special actions, if any,
should be performed when a group ends.
\def\grp{\.{\char'173...\char'175}}

Some groups are not supposed to be ended by right braces. For example,
the `\.\$' that begins a math formula causes a |math_shift_group| to
be started, and this should be terminated by a matching `\.\$'. Similarly,
a group that starts with \.{\\left} should end with \.{\\right}, and
one that starts with \.{\\begingroup} should end with \.{\\endgroup}.


@<Types...@>=
typedef int8_t group_code; /*|save_level| for a level boundary*/




@* Token lists.
A \TeX\ token is either a character or a control sequence, and it is
@^token@>
represented internally in one of two ways: (1)~A character whose ASCII
code number is |c| and whose command code is |m| is represented as the
number $2^8m+c$; the command code is in the range |1 <= m <= 14|. (2)~A control
sequence whose |eqtb| address is |p| is represented as the number
|cs_token_flag+p|. Here |cs_token_flag==@t$2^{12}-1$@>| is larger than
$2^8m+c$, yet it is small enough that |cs_token_flag+p < max_halfword|;
thus, a token fits comfortably in a halfword.

A token |t| represents a |left_brace| command if and only if
|t < left_brace_limit|; it represents a |right_brace| command if and only if
we have |left_brace_limit <= t < right_brace_limit|; and it represents a |match| or
|end_match| command if and only if |match_token <= t <= end_match_token|.
The following definitions take care of these token-oriented constants
and a few others.

@* Introduction to the syntactic routines.

@* Input stacks and states.

@ Let's look more closely now at the control variables
(|state|,~|index|,~|start|,~|loc|,~|limit|,~|name|),
assuming that \TeX\ is reading a line of characters that have been input
from some file or from the user's terminal. There is an array called
|buffer| that acts as a stack of all lines of characters that are
currently being read from files, including all lines on subsidiary
levels of the input stack that are not yet completed. \TeX\ will return to
the other lines when it is finished with the present input file.

(Incidentally, on a machine with byte-oriented addressing, it might be
appropriate to combine |buffer| with the |str_pool| array,
letting the buffer entries grow downward from the top of the string pool
and checking that these two tables don't bump into each other.)

The line we are currently working on begins in position |start| of the
buffer; the next character we are about to read is |buffer[loc]|; and
|limit| is the location of the last character present.  If |loc > limit|,
the line has been completely read. Usually |buffer[limit]| is the
|end_line_char|, denoting the end of a line, but this is not
true if the current line is an insertion that was entered on the user's
terminal in response to an error message.

The |name| variable is a string number that designates the name of
the current file, if we are reading a text file. It is zero if we
are reading from the terminal; it is |n+1| if we are reading from
input stream |n|, where |0 <= n <= 16|. (Input stream 16 stands for
an invalid stream number; in such cases the input is actually from
the terminal, under control of the procedure |read_toks|.)

The |state| variable has one of three values, when we are scanning such
files:
$$\baselineskip 15pt\vbox{\halign{#\hfil\cr
1) |state==mid_line| is the normal state.\cr
2) |state==skip_blanks| is like |mid_line|, but blanks are ignored.\cr
3) |state==new_line| is the state at the beginning of a line.\cr}}$$
These state values are assigned numeric codes so that if we add the state
code to the next character's command code, we get distinct values. For
example, `|mid_line+spacer|' stands for the case that a blank
space character occurs in the middle of a line when it is not being
ignored; after this case is processed, the next value of |state| will
be |skip_blanks|.

@ However, all this discussion about input state really applies only to the
case that we are inputting from a file. There is another important case,
namely when we are currently getting input from a token list. In this case
|state==token_list|, and the conventions about the other state variables
are different:

\yskip\hang|loc| is a pointer to the current node in the token list, i.e.,
the node that will be read next. If |loc==null|, the token list has been
fully read.

\yskip\hang|start| points to the first node of the token list; this node
may or may not contain a reference count, depending on the type of token
list involved.

\yskip\hang|token_type|, which takes the place of |index| in the
discussion above, is a code number that explains what kind of token list
is being scanned.

\yskip\hang|name| points to the |eqtb| address of the control sequence
being expanded, if the current token list is a macro.

\yskip\hang|param_start|, which takes the place of |limit|, tells where
the parameters of the current macro begin in the |param_stack|, if the
current token list is a macro.

\yskip\noindent The |token_type| can take several values, depending on
where the current token list came from:

\yskip\hang|parameter|, if a parameter is being scanned;

\hang|u_template|, if the \<u_j> part of an alignment
template is being scanned;

\hang|v_template|, if the \<v_j> part of an alignment
template is being scanned;

\hang|backed_up|, if the token list being scanned has been inserted as
`to be read again';

\hang|inserted|, if the token list being scanned has been inserted as
the text expansion of a \.{\\count} or similar variable;

\hang|macro|, if a user-defined control sequence is being scanned;

\hang|output_text|, if an \.{\\output} routine is being scanned;

\hang|every_par_text|, if the text of \.{\\everypar} is being scanned;

\hang|every_math_text|, if the text of \.{\\everymath} is being scanned;

\hang|every_display_text|, if the text of \.{\\everydisplay} is being scanned;

\hang|every_hbox_text|, if the text of \.{\\everyhbox} is being scanned;

\hang|every_vbox_text|, if the text of \.{\\everyvbox} is being scanned;

\hang|every_job_text|, if the text of \.{\\everyjob} is being scanned;

\hang|every_cr_text|, if the text of \.{\\everycr} is being scanned;

\hang|mark_text|, if the text of a \.{\\mark} is being scanned;

\hang|write_text|, if the text of a \.{\\write} is being scanned.

\yskip\noindent
The codes for |output_text|, |every_par_text|, etc., are equal to a constant
plus the corresponding codes for token list parameters |output_routine_loc|,
|every_par_loc|, etc.  The token list begins with a reference count if and
only if |token_type >= macro|.
@^reference counts@>

@d inserted 4 /*|token_type| code for inserted texts*/



@ Here it is necessary to explain a little trick. We don't want to store a long
string that corresponds to a token list, because that string might take up
lots of memory; and we are printing during a time when an error message is
being given, so we dare not do anything that might overflow one of \TeX's
tables. So `pseudoprinting' is the answer: We enter a mode of printing
that stores characters into a buffer of length |error_line|, where character
$k+1$ is placed into \hbox{|trick_buf[k%error_line]|} if
|k < trick_count|, otherwise character |k| is dropped. Initially we set
|tally=0| and |trick_count=1000000|; then when we reach the
point where transition from line 1 to line 2 should occur, we
set |first_count=tally| and |trick_count=@tmax@>(error_line,
tally+1+error_line-half_error_line)|. At the end of the
pseudoprinting, the values of |first_count|, |tally|, and
|trick_count| give us all the information we need to print the two lines,
and all of the necessary text is in |trick_buf|.

Namely, let |l| be the length of the descriptive information that appears
on the first line. The length of the context information gathered for that
line is |k==first_count|, and the length of the context information
gathered for line~2 is $m=\min(|tally|, |trick_count|)-k$. If |l+k <= h|,
where |h==half_error_line|, we print |trick_buf[0 dotdot k-1]| after the
descriptive information on line~1, and set |n=l+k|; here |n| is the
length of line~1. If $l+k>h$, some cropping is necessary, so we set |n=h|
and print `\.{...}' followed by
$$\hbox{|trick_buf[(l+k-h+3)dotdot k-1]|,}$$
where subscripts of |trick_buf| are circular modulo |error_line|. The
second line consists of |n|~spaces followed by |trick_buf[k dotdot(k+m-1)]|,
unless |n+m > error_line|; in the latter case, further cropping is done.
This is easier to program than to explain.


@* Maintaining the input stacks.

@* Getting the next token.


@ The present point in the program is reached only when the |expand|
routine has inserted a special marker into the input. In this special
case, |info(loc)| is known to be a control sequence token, and |link(loc)==null|.


@ Since |get_next| is used so frequently in \TeX, it is convenient
to define three related procedures that do a little more:

\yskip\hang|get_token| not only sets |cur_cmd| and |cur_chr|, it
also sets |cur_tok|, a packed halfword version of the current token.

\yskip\hang|get_x_token|, meaning ``get an expanded token,'' is like
|get_token|, but if the current token turns out to be a user-defined
control sequence (i.e., a macro call), or a conditional,
or something like \.{\\topmark} or \.{\\expandafter} or \.{\\csname},
it is eliminated from the input by beginning the expansion of the macro
or the evaluation of the conditional.

\yskip\hang|x_token| is like |get_x_token| except that it assumes that
|get_next| has already been called.

\yskip\noindent
In fact, these three procedures account for almost every use of |get_next|.

@* Expanding the next token.

@* Basic scanning subroutines.

@ Inside an \.{\\output} routine, a user may wish to look at the page totals
that were present at the moment when output was triggered.

@d max_dimen 07777777777 /*$2^{30}-1$*/


@* Building token lists.

@* Conditional processing.

@* File names.
It's time now to fret about file names.  Besides the fact that different
operating systems treat files in different ways, we must cope with the
fact that completely different naming conventions are used by different
groups of people. The following programs show what is required for one
particular operating system; similar routines for other systems are not
difficult to devise.
@^fingers@>
@^system dependencies@>

\TeX\ assumes that a file name has three parts: the name proper; its
``extension''; and a ``file area'' where it is found in an external file
system.  The extension of an input file or a write file is assumed to be
`\.{.tex}' unless otherwise specified; it is `\.{.log}' on the
transcript file that records each run of \TeX; it is `\.{.tfm}' on the font
metric files that describe characters in the fonts \TeX\ uses; it is
`\.{.dvi}' on the output files that specify typesetting information; and it
is `\.{.fmt}' on the format files written by \.{INITEX} to initialize \TeX.
The file area can be arbitrary on input files, but files are usually
output to the user's current area.  If an input file cannot be
found on the specified area, \TeX\ will look for it on a special system
area; this special area is intended for commonly used input files like
\.{webmac.tex}.

Simple uses of \TeX\ refer only to file names that have no explicit
extension or area. For example, a person usually says `\.{\\input} \.{paper}'
or `\.{\\font\\tenrm} \.= \.{helvetica}' instead of `\.{\\input}
\.{paper.new}' or `\.{\\font\\tenrm} \.= \.{<csd.knuth>test}'. Simple file
names are best, because they make the \TeX\ source files portable;
whenever a file name consists entirely of letters and digits, it should be
treated in the same way by all implementations of \TeX. However, users
need the ability to refer to other files in their environment, especially
when responding to error messages concerning unopenable files; therefore
we want to let them use the syntax that appears in their favorite
operating system.

The following procedures don't allow spaces to be part of
file names; but some users seem to like names that are spaced-out.
System-dependent changes to allow such things should probably
be made with reluctance, and only when an entire file name that
includes spaces is ``quoted'' somehow.



@ The first 24 bytes (6 words) of a \.{TFM} file contain twelve 16-bit
integers that give the lengths of the various subsequent portions
of the file. These twelve integers are, in order:
$$\vbox{\halign{\hfil#&$\null=\null$#\hfil\cr
|lf|&length of the entire file, in words;\cr
|lh|&length of the header data, in words;\cr
|bc|&smallest character code in the font;\cr
|ec|&largest character code in the font;\cr
|nw|&number of words in the width table;\cr
|nh|&number of words in the height table;\cr
|nd|&number of words in the depth table;\cr
|ni|&number of words in the italic correction table;\cr
|nl|&number of words in the lig/kern table;\cr
|nk|&number of words in the kern table;\cr
|ne|&number of words in the extensible character table;\cr
|np|&number of font parameter words.\cr}}$$
They are all nonnegative and less than $2^{15}$. We must have |bc-1 <= ec <= 255|,
and
$$\hbox{|lf==6+lh+(ec-bc+1)+nw+nh+nd+ni+nl+nk+ne+np|.}$$
Note that a font may contain as many as 256 characters (if |bc==0| and |ec==255|),
and as few as 0 characters (if |bc==ec+1|).

Incidentally, when two or more 8-bit bytes are combined to form an integer of
16 or more bits, the most significant bytes appear first in the file.
This is called BigEndian order.
@!@^BigEndian order@>

@ The rest of the \.{TFM} file may be regarded as a sequence of ten data
arrays having the informal specification
$$\def\arr$[#1]#2${\&{array} $[#1]$ \&{of} #2}
\def\PB#1{\arr#1}
\vbox{\halign{\hfil\\{#}&$\,:\,$#\hfil\cr
header&|[0 dotdot lh-1]@t\\{stuff}@>|\cr
char\_info&|[bc dotdot ec]char_info_word|\cr
width&|[0 dotdot nw-1]fix_word|\cr
height&|[0 dotdot nh-1]fix_word|\cr
depth&|[0 dotdot nd-1]fix_word|\cr
italic&|[0 dotdot ni-1]fix_word|\cr
lig\_kern&|[0 dotdot nl-1]lig_kern_command|\cr
kern&|[0 dotdot nk-1]fix_word|\cr
exten&|[0 dotdot ne-1]extensible_recipe|\cr
param&|[1 dotdot np]fix_word|\cr}}$$
The most important data type used here is a |@!fix_word|, which is
a 32-bit representation of a binary fraction. A |fix_word| is a signed
quantity, with the two's complement of the entire word used to represent
negation. Of the 32 bits in a |fix_word|, exactly 12 are to the left of the
binary point; thus, the largest |fix_word| value is $2048-2^{-20}$, and
the smallest is $-2048$. We will see below, however, that all but two of
the |fix_word| values must lie between $-16$ and $+16$.

@ The first data array is a block of header information, which contains
general facts about the font. The header must contain at least two words,
|header[0]| and |header[1]|, whose meaning is explained below.
Additional header information of use to other software routines might
also be included, but \TeX82 does not need to know about such details.
For example, 16 more words of header information are in use at the Xerox
Palo Alto Research Center; the first ten specify the character coding
scheme used (e.g., `\.{XEROX text}' or `\.{TeX math symbols}'), the next five
give the font identifier (e.g., `\.{HELVETICA}' or `\.{CMSY}'), and the
last gives the ``face byte.'' The program that converts \.{DVI} files
to Xerox printing format gets this information by looking at the \.{TFM}
file, which it needs to read anyway because of other information that
is not explicitly repeated in \.{DVI}~format.

\yskip\hang|header[0]| is a 32-bit check sum that \TeX\ will copy into
the \.{DVI} output file. Later on when the \.{DVI} file is printed,
possibly on another computer, the actual font that gets used is supposed
to have a check sum that agrees with the one in the \.{TFM} file used by
\TeX. In this way, users will be warned about potential incompatibilities.
(However, if the check sum is zero in either the font file or the \.{TFM}
file, no check is made.)  The actual relation between this check sum and
the rest of the \.{TFM} file is not important; the check sum is simply an
identification number with the property that incompatible fonts almost
always have distinct check sums.
@^check sum@>

\yskip\hang|header[1]| is a |fix_word| containing the design size of
the font, in units of \TeX\ points. This number must be at least 1.0; it is
fairly arbitrary, but usually the design size is 10.0 for a ``10 point''
font, i.e., a font that was designed to look best at a 10-point size,
whatever that really means. When a \TeX\ user asks for a font
`\.{at} $\delta$ \.{pt}', the effect is to override the design size
and replace it by $\delta$, and to multiply the $x$ and~$y$ coordinates
of the points in the font image by a factor of $\delta$ divided by the
design size.  {\sl All other dimensions in the\/ \.{TFM} file are
|fix_word|\kern-1pt\ numbers in design-size units}, with the exception of
|param[1]| (which denotes the slant ratio). Thus, for example, the value
of |param[6]|, which defines the \.{em} unit, is often the |fix_word| value
$2^{20}=1.0$, since many fonts have a design size equal to one em.
The other dimensions must be less than 16 design-size units in absolute
value; thus, |header[1]| and |param[1]| are the only |fix_word|
entries in the whole \.{TFM} file whose first byte might be something
besides 0 or 255.

@ Next comes the |char_info| array, which contains one |@!char_info_word|
per character. Each word in this part of the file contains six fields
packed into four bytes as follows.

\yskip\hang first byte: |@!width_index| (8 bits)\par
\hang second byte: |@!height_index| (4 bits) times 16, plus |@!depth_index|
  (4~bits)\par
\hang third byte: |@!italic_index| (6 bits) times 4, plus |@!tag|
  (2~bits)\par
\hang fourth byte: |@!rem| (8 bits)\par
\yskip\noindent
The actual width of a character is \\{width}|[width_index]|, in design-size
units; this is a device for compressing information, since many characters
have the same width. Since it is quite common for many characters
to have the same height, depth, or italic correction, the \.{TFM} format
imposes a limit of 16 different heights, 16 different depths, and
64 different italic corrections.

@!@^italic correction@>
The italic correction of a character has two different uses.
(a)~In ordinary text, the italic correction is added to the width only if
the \TeX\ user specifies `\.{\\/}' after the character.
(b)~In math formulas, the italic correction is always added to the width,
except with respect to the positioning of subscripts.

Incidentally, the relation $\\{width}[0]=\\{height}[0]=\\{depth}[0]=
\\{italic}[0]=0$ should always hold, so that an index of zero implies a
value of zero.  The |width_index| should never be zero unless the
character does not exist in the font, since a character is valid if and
only if it lies between |bc| and |ec| and has a nonzero |width_index|.



@ The final portion of a \.{TFM} file is the |param| array, which is another
sequence of |fix_word| values.

\yskip\hang|param[1]==slant| is the amount of italic slant, which is used
to help position accents. For example, |slant==.25| means that when you go
up one unit, you also go .25 units to the right. The |slant| is a pure
number; it's the only |fix_word| other than the design size itself that is
not scaled by the design size.

\hang|param[2]==space| is the normal spacing between words in text.
Note that character |' '| in the font need not have anything to do with
blank spaces.

\hang|param[3]==space_stretch| is the amount of glue stretching between words.

\hang|param[4]==space_shrink| is the amount of glue shrinking between words.

\hang|param[5]==x_height| is the size of one ex in the font; it is also
the height of letters for which accents don't have to be raised or lowered.

\hang|param[6]==quad| is the size of one em in the font.

\hang|param[7]==extra_space| is the amount added to |param[2]| at the
ends of sentences.

\yskip\noindent
If fewer than seven parameters are present, \TeX\ sets the missing parameters
to zero. Fonts used for math symbols are required to have
additional parameter information, which is explained later.

@d quad_code 6

@ So that is what \.{TFM} files hold. Since \TeX\ has to absorb such information
about lots of fonts, it stores most of the data in a large array called
|font_info|. Each item of |font_info| is a |memory_word|; the |fix_word|
data gets converted into |scaled| entries, while everything else goes into
words of type |four_quarters|.

When the user defines \.{\\font\\f}, say, \TeX\ assigns an internal number
to the user's font~\.{\\f}. Adding this number to |font_id_base| gives the
|eqtb| location of a ``frozen'' control sequence that will always select
the font.

@<Types...@>=
typedef uint8_t internal_font_number; /*|font| in a |char_node|*/
typedef uint16_t font_index; /*index into |font_info|*/

@

@s font_index int
@s str_number int
@<\TeX\ functions@>=
static memory_word @!font_info[font_mem_size+1];
   /*the big collection of font data*/
static font_index @!fmem_ptr=0; /*first unused word of |font_info|*/

static void hclear_fonts(void)
{ fmem_ptr=0;
}
static internal_font_number @!font_ptr; /*largest internal font number in use*/
static scaled @!font_size0[font_max-font_base+1],
  *const @!font_size = @!font_size0-font_base; /*``at'' size*/
static eight_bits @!font_bc0[font_max-font_base+1],
  *const @!font_bc = @!font_bc0-font_base;
   /*beginning (smallest) character code*/
static eight_bits @!font_ec0[font_max-font_base+1],
  *const @!font_ec = @!font_ec0-font_base;
   /*ending (largest) character code*/
static pointer @!font_glue0[font_max-font_base+1],
  *const @!font_glue = @!font_glue0-font_base;
   /*glue specification for interword space, |null| if not allocated*/
static int @!hyphen_char0[font_max-font_base+1],
  *const @!hyphen_char = @!hyphen_char0-font_base;
   /*current \.{\\hyphenchar} values*/

@ Besides the arrays just enumerated, we have directory arrays that make it
easy to get at the individual entries in |font_info|. For example, the
|char_info| data for character |c| in font |f| will be in
|font_info[char_base[f]+c].qqqq|; and if |w| is the |width_index|
part of this word (the |b0| field), the width of the character is
|font_info[width_base[f]+w].sc|. (These formulas assume that
|min_quarterword| has already been added to |c| and to |w|, since \TeX\
stores its quarterwords that way.)

@<\TeX\ functions@>=
static int @!char_base0[font_max-font_base+1],
  *const @!char_base = @!char_base0-font_base;
   /*base addresses for |char_info|*/
static int @!width_base0[font_max-font_base+1],
  *const @!width_base = @!width_base0-font_base;
   /*base addresses for widths*/
static int @!height_base0[font_max-font_base+1],
  *const @!height_base = @!height_base0-font_base;
   /*base addresses for heights*/
static int @!depth_base0[font_max-font_base+1],
  *const @!depth_base = @!depth_base0-font_base;
   /*base addresses for depths*/
static int @!param_base0[font_max-font_base+1],
  *const @!param_base = @!param_base0-font_base;
   /*base addresses for font parameters*/


@ Of course we want to define macros that suppress the detail of how font
information is actually packed, so that we don't have to write things like
$$\hbox{|font_info[width_base[f]+font_info[char_base[f]+c].qqqq.b0].sc|}$$
too often. The \.{WEB} definitions here make |char_info(f)(c)| the
|four_quarters| word of font information corresponding to character
|c| of font |f|. If |q| is such a word, |char_width(f)(q)| will be
the character's width; hence the long formula above is at least
abbreviated to
$$\hbox{|char_width(f)(char_info(f)(c))|.}$$
Usually, of course, we will fetch |q| first and look at several of its
fields at the same time.

The italic correction of a character will be denoted by
|char_italic(f)(q)|, so it is analogous to |char_width|.  But we will get
at the height and depth in a slightly different way, since we usually want
to compute both height and depth if we want either one.  The value of
|height_depth(q)| will be the 8-bit quantity
$$b=|height_index|\times16+|depth_index|,$$ and if |b| is such a byte we
will write |char_height(f)(b)| and |char_depth(f)(b)| for the height and
depth of the character |c| for which |q==char_info(f)(c)|. Got that?

The tag field will be called |char_tag(q)|; the remainder byte will be
called |rem_byte(q)|, using a macro that we have already defined above.

Access to a character's |width|, |height|, |depth|, and |tag| fields is
part of \TeX's inner loop, so we want these macros to produce code that is
as fast as possible under the circumstances.
@^inner loop@>

@d char_info(A, B) font_info[char_base[A]+B].qqqq
@d char_width(A, B) (width_base[A]!=0?
   font_info[width_base[A]+char_info(A,B).b0].sc:x_char_width(A,B))
@d char_exists(A) (A.b0 > min_quarterword)
@d height_depth(A) qo(A.b1)
@d char_height(A, B) font_info[height_base[A]+(B)/16].sc
@d char_depth(A, B) font_info[depth_base[A]+(B)%16].sc


@ Font parameters are referred to as |slant(f)|, |space(f)|, etc.

@d param_end(A) param_base[A]].sc
@d param(A) font_info[A+param_end
@d quad param(quad_code) /*one em*/

@ \TeX\ checks the information of a \.{TFM} file for validity as the
file is being read in, so that no further checks will be needed when
typesetting is going on. The somewhat tedious subroutine that does this
is called |read_font_info|. It has four parameters: the user font
identifier~|u|, the file name and area strings |nom| and |aire|, and the
``at'' size~|s|. If |s|~is negative, it's the negative of a scale factor
to be applied to the design size; |s==-1000| is the normal case.
Otherwise |s| will be substituted for the design size; in this
case, |s| must be positive and less than $2048\rm\,pt$
(i.e., it must be less than $2^{27}$ when considered as an integer).

The subroutine opens and closes a global file variable called |tfm_file|.
It returns the value of the internal font number that was just loaded.
If an error is detected, an error message is issued and no font
information is stored; |null_font| is returned in this case.

@d abort goto bad_tfm /*do this when the \.{TFM} data is wrong*/

@<\TeX\ functions@>=
static void read_font_info(int f, char *@!nom, scaled @!s)
{@+
int k; /*index into |font_info|*/
halfword @!lf, @!lh, @!bc, @!ec, @!nw, @!nh, @!nd, @!ni, @!nl, @!nk, @!ne, @!np;
   /*sizes of subfiles*/
eight_bits @!a, @!b, @!c, @!d; /*byte variables*/
four_quarters @!qw;scaled @!sw; /*accumulators*/
scaled @!z; /*the design size or the ``at'' size*/
int @!alpha;int @!beta;
   /*auxiliary quantities used in fixed-point multiplication*/
@<Read and check the font data; |abort| if the \.{TFM} file is malformed;
if there's no room for this font, say so and |goto done|; otherwise |incr(font_ptr)|
and |goto done|@>;
bad_tfm:  QUIT("Bad tfm file: %s\n", nom);
done:;
}

@ @<Read and check...@>=
@<Read the {\.{TFM}} size fields@>;
@<Use size fields to allocate font information@>;
@<Read the {\.{TFM}} header@>;
@<Read character data@>;
@<Read box dimensions@>;
@<Read ligature/kern program@>;
@<Read extensible character recipes@>;
@<Read font parameters@>;
@<Make final adjustments and |goto done|@>@;

@ Note: A malformed \.{TFM} file might be shorter than it claims to be;
thus |eof(tfm_file)| might be true when |read_font_info| refers to
|tfm_file.d| or when it says |get(tfm_file)|. If such circumstances
cause system error messages, you will have to defeat them somehow,
for example by defining |fget| to be `\ignorespaces|{@+get(tfm_file);|
|if (eof(tfm_file)) abort;} |\unskip'.
@^system dependencies@>

@d fget (hpos++)
@d fskip(A) (hpos+=A)
@d fskip_four fskip(4)
@d fbyte (*hpos)
@d read_sixteen(A) {@+A=fbyte;
  if (A > 127) abort;
  fget;A=A*0400+fbyte;
  }
@d store_four_quarters(A) {@+fget;a=fbyte;qw.b0=qi(a);
  fget;b=fbyte;qw.b1=qi(b);
  fget;c=fbyte;qw.b2=qi(c);
  fget;d=fbyte;qw.b3=qi(d);
  A=qw;
  }

@ @<Read the {\.{TFM}} size fields@>=
{@+read_sixteen(lf);
fget;read_sixteen(lh);
fget;read_sixteen(bc);
fget;read_sixteen(ec);
if ((bc > ec+1)||(ec > 255)) abort;
if (bc > 255)  /*|bc==256| and |ec==255|*/
  {@+bc=1;ec=0;
  }
fget;read_sixteen(nw);
fget;read_sixteen(nh);
fget;read_sixteen(nd);
fget;read_sixteen(ni);
fget;read_sixteen(nl);
fget;read_sixteen(nk);
fget;read_sixteen(ne);
fget;read_sixteen(np);
if (lf!=6+lh+(ec-bc+1)+nw+nh+nd+ni+nl+nk+ne+np) abort;
if ((nw==0)||(nh==0)||(nd==0)||(ni==0)) abort;
}

@ The preliminary settings of the index-offset variables |char_base|,
|width_base|, |lig_kern_base|, |kern_base|, and |exten_base| will be
corrected later by subtracting |min_quarterword| from them; and we will
subtract 1 from |param_base| too. It's best to forget about such anomalies
until later.

@<Use size fields to allocate font information@>=
lf=lf-6-lh; /*|lf| words should be loaded into |font_info|*/
if (np < 7) lf=lf+7-np; /*at least seven parameters will appear*/
if ((font_ptr==font_max)||(fmem_ptr+lf > font_mem_size))
QUIT("Not enough room left for font %s\n",nom);
char_base[f]=fmem_ptr-bc;
width_base[f]=char_base[f]+ec+1;
height_base[f]=width_base[f]+nw;
depth_base[f]=height_base[f]+nh;
param_base[f]=depth_base[f]+nd

@ Only the first two words of the header are needed by \TeX82.

@<Read the {\.{TFM}} header@>=
{@+if (lh < 2) abort;
fskip_four;
fget;read_sixteen(z); /*this rejects a negative design size*/
fget;z=z*0400+fbyte;fget;z=(z*020)+(fbyte/020);
if (z < unity) abort;
while (lh > 2)
  {@+fget;fget;fget;fget;decr(lh); /*ignore the rest of the header*/
  }
if (s!=-1000)
{ if (s >= 0) z=s;
  else z=xn_over_d(z,-s, 1000);
}
font_size[f]=z;
}

@ @<Read character data@>=
for (k=fmem_ptr; k<=width_base[f]-1; k++)
  {@+store_four_quarters(font_info[k].qqqq);
  if ((a >= nw)||(b/020 >= nh)||(b%020 >= nd))
     abort;
  }

@ A |fix_word| whose four bytes are $(a,b,c,d)$ from left to right represents
the number
$$x=\left\{\vcenter{\halign{$#$,\hfil\qquad&if $#$\hfil\cr
b\cdot2^{-4}+c\cdot2^{-12}+d\cdot2^{-20}&a=0;\cr
-16+b\cdot2^{-4}+c\cdot2^{-12}+d\cdot2^{-20}&a=255.\cr}}\right.$$
(No other choices of |a| are allowed, since the magnitude of a number in
design-size units must be less than 16.)  We want to multiply this
quantity by the integer~|z|, which is known to be less than $2^{27}$.
If $|z|<2^{23}$, the individual multiplications $b\cdot z$,
$c\cdot z$, $d\cdot z$ cannot overflow; otherwise we will divide |z| by 2,
4, 8, or 16, to obtain a multiplier less than $2^{23}$, and we can
compensate for this later. If |z| has thereby been replaced by
$|z|^\prime=|z|/2^e$, let $\beta=2^{4-e}$; we shall compute
$$\lfloor(b+c\cdot2^{-8}+d\cdot2^{-16})\,z^\prime/\beta\rfloor$$
if $a=0$, or the same quantity minus $\alpha=2^{4+e}z^\prime$ if $a=255$.
This calculation must be done exactly, in order to guarantee portability
of \TeX\ between computers.

@d store_scaled(A) {@+fget;a=fbyte;fget;b=fbyte;
  fget;c=fbyte;fget;d=fbyte;@/
  sw=(((((d*z)/0400)+(c*z))/0400)+(b*z))/beta;
  if (a==0) A=sw;@+else if (a==255) A=sw-alpha;@+else abort;
  }

@<Read box dimensions@>=
{@+@<Replace |z| by $|z|^\prime$ and compute $\alpha,\beta$@>;
for (k=width_base[f]; k<=depth_base[f]+nd-1; k++)
  store_scaled(font_info[k].sc);
if (font_info[width_base[f]].sc!=0) abort; /*\\{width}[0] must be zero*/
if (font_info[height_base[f]].sc!=0) abort; /*\\{height}[0] must be zero*/
if (font_info[depth_base[f]].sc!=0) abort; /*\\{depth}[0] must be zero*/
}
fskip(4*ni)

@ @<Replace |z|...@>=
{@+alpha=16;
while (z >= 040000000)
  {@+z=z/2;alpha=alpha+alpha;
  }
beta=256/alpha;alpha=alpha*z;
}

@ @<Read ligature/kern program@>=
fskip(4*(nl+nk));

@ @<Read extensible character recipes@>=
fskip(4*ne);

@ We check to see that the \.{TFM} file doesn't end prematurely; but
no error message is given for files having more than |lf| words.

@<Read font parameters@>=
{@+for (k=1; k<=np; k++)
  if (k==1)  /*the |slant| parameter is a pure number*/
    {@+fget;sw=fbyte;if (sw > 127) sw=sw-256;
    fget;sw=sw*0400+fbyte;fget;sw=sw*0400+fbyte;
    fget;font_info[param_base[f]].sc=
      (sw*020)+(fbyte/020);
    }
  else store_scaled(font_info[param_base[f]+k-1].sc);
if (hpos>=hend) abort;
for (k=np+1; k<=7; k++) font_info[param_base[f]+k-1].sc=0;
}

@ Now to wrap it up, we have checked all the necessary things about the \.{TFM}
file, and all we need to do is put the finishing touches on the data for
the new font.

@d adjust(A) A[f]=qo(A[f])
   /*correct for the excess |min_quarterword| that was added*/

@<Make final adjustments...@>=
hyphen_char[f]=-1;
font_bc[f]=bc;font_ec[f]=ec;font_glue[f]=null;
adjust(char_base);adjust(width_base);
decr(param_base[f]);
fmem_ptr=fmem_ptr+lf; goto done

@ Here is a function that returns a pointer to a character node for a
given character in a given font. If that character doesn't exist,
|null| is returned instead.

@<\TeX\ functions@>=
static pointer new_character(internal_font_number @!f, eight_bits @!c)
{@+ pointer p; /*newly allocated node*/
#ifdef DEBUG
if (font_bc[f] > c || font_ec[f] < c ||
 (width_base[f]!=0 && ! char_exists(char_info(f, qi(c)))) ||
 (width_base[f]==0 && ! ft_exists(font_face[f], c)))
  DBG(DBGFONT,"Warning: Character 0x%0X in font %d does not exist\n",c,f);
#endif
p=get_avail();font(p)=f;character(p)=qi(c);
return p;
}

@* Device-independent file format.
The most important output produced by a run of \TeX\ is the ``device
independent'' (\.{DVI}) file that specifies where characters and rules
are to appear on printed pages. The form of these files was designed by
David R. Fuchs in 1979. Almost any reasonable typesetting device can be
@^Fuchs, David Raymond@>
@:DVI\_files}{\.{DVI} files@>
driven by a program that takes \.{DVI} files as input, and dozens of such
\.{DVI}-to-whatever programs have been written. Thus, it is possible to
print the output of \TeX\ on many different kinds of equipment, using \TeX\
as a device-independent ``front end.''

A \.{DVI} file is a stream of 8-bit bytes, which may be regarded as a
series of commands in a machine-like language. The first byte of each command
is the operation code, and this code is followed by zero or more bytes
that provide parameters to the command. The parameters themselves may consist
of several consecutive bytes; for example, the `|set_rule|' command has two
parameters, each of which is four bytes long. Parameters are usually
regarded as nonnegative integers; but four-byte-long parameters,
and shorter parameters that denote distances, can be
either positive or negative. Such parameters are given in two's complement
notation. For example, a two-byte-long distance parameter has a value between
$-2^{15}$ and $2^{15}-1$. As in \.{TFM} files, numbers that occupy
more than one byte position appear in BigEndian order.

A \.{DVI} file consists of a ``preamble,'' followed by a sequence of one
or more ``pages,'' followed by a ``postamble.'' The preamble is simply a
|pre| command, with its parameters that define the dimensions used in the
file; this must come first.  Each ``page'' consists of a |bop| command,
followed by any number of other commands that tell where characters are to
be placed on a physical page, followed by an |eop| command. The pages
appear in the order that \TeX\ generated them. If we ignore |nop| commands
and \\{fnt\_def} commands (which are allowed between any two commands in
the file), each |eop| command is immediately followed by a |bop| command,
or by a |post| command; in the latter case, there are no more pages in the
file, and the remaining bytes form the postamble.  Further details about
the postamble will be explained later.

Some parameters in \.{DVI} commands are ``pointers.'' These are four-byte
quantities that give the location number of some other byte in the file;
the first byte is number~0, then comes number~1, and so on. For example,
one of the parameters of a |bop| command points to the previous |bop|;
this makes it feasible to read the pages in backwards order, in case the
results are being directed to a device that stacks its output face up.
Suppose the preamble of a \.{DVI} file occupies bytes 0 to 99. Now if the
first page occupies bytes 100 to 999, say, and if the second
page occupies bytes 1000 to 1999, then the |bop| that starts in byte 1000
points to 100 and the |bop| that starts in byte 2000 points to 1000. (The
very first |bop|, i.e., the one starting in byte 100, has a pointer of~$-1$.)

@ The \.{DVI} format is intended to be both compact and easily interpreted
by a machine. Compactness is achieved by making most of the information
implicit instead of explicit. When a \.{DVI}-reading program reads the
commands for a page, it keeps track of several quantities: (a)~The current
font |f| is an integer; this value is changed only
by \\{fnt} and \\{fnt\_num} commands. (b)~The current position on the page
is given by two numbers called the horizontal and vertical coordinates,
|h| and |v|. Both coordinates are zero at the upper left corner of the page;
moving to the right corresponds to increasing the horizontal coordinate, and
moving down corresponds to increasing the vertical coordinate. Thus, the
coordinates are essentially Cartesian, except that vertical directions are
flipped; the Cartesian version of |(h, v)| would be |(h,-v)|.  (c)~The
current spacing amounts are given by four numbers |w|, |x|, |y|, and |z|,
where |w| and~|x| are used for horizontal spacing and where |y| and~|z|
are used for vertical spacing. (d)~There is a stack containing
|(h, v, w, x, y, z)| values; the \.{DVI} commands |push| and |pop| are used to
change the current level of operation. Note that the current font~|f| is
not pushed and popped; the stack contains only information about
positioning.

The values of |h|, |v|, |w|, |x|, |y|, and |z| are signed integers having up
to 32 bits, including the sign. Since they represent physical distances,
there is a small unit of measurement such that increasing |h| by~1 means
moving a certain tiny distance to the right. The actual unit of
measurement is variable, as explained below; \TeX\ sets things up so that
its \.{DVI} output is in sp units, i.e., scaled points, in agreement with
all the |scaled| dimensions in \TeX's data structures.

@ Here is a list of all the commands that may appear in a \.{DVI} file. Each
command is specified by its symbolic name (e.g., |bop|), its opcode byte
(e.g., 139), and its parameters (if any). The parameters are followed
by a bracketed number telling how many bytes they occupy; for example,
`|p[4]|' means that parameter |p| is four bytes long.

\yskip\hang|set_char_0| 0. Typeset character number~0 from font~|f|
such that the reference point of the character is at |(h, v)|. Then
increase |h| by the width of that character. Note that a character may
have zero or negative width, so one cannot be sure that |h| will advance
after this command; but |h| usually does increase.

\yskip\hang\\{set\_char\_1} through \\{set\_char\_127} (opcodes 1 to 127).
Do the operations of |set_char_0|; but use the character whose number
matches the opcode, instead of character~0.

\yskip\hang|set1| 128 |c[1]|. Same as |set_char_0|, except that character
number~|c| is typeset. \TeX82 uses this command for characters in the
range |128 <= c < 256|.

\yskip\hang|@!set2| 129 |c[2]|. Same as |set1|, except that |c|~is two
bytes long, so it is in the range |0 <= c < 65536|. \TeX82 never uses this
command, but it should come in handy for extensions of \TeX\ that deal
with oriental languages.
@^oriental characters@>@^Chinese characters@>@^Japanese characters@>

\yskip\hang|@!set3| 130 |c[3]|. Same as |set1|, except that |c|~is three
bytes long, so it can be as large as $2^{24}-1$. Not even the Chinese
language has this many characters, but this command might prove useful
in some yet unforeseen extension.

\yskip\hang|@!set4| 131 |c[4]|. Same as |set1|, except that |c|~is four
bytes long. Imagine that.

\yskip\hang|set_rule| 132 |a[4]| |b[4]|. Typeset a solid black rectangle
of height~|a| and width~|b|, with its bottom left corner at |(h, v)|. Then
set |h=h+b|. If either |a <= 0| or |b <= 0|, nothing should be typeset. Note
that if |b < 0|, the value of |h| will decrease even though nothing else happens.
See below for details about how to typeset rules so that consistency with
\MF\ is guaranteed.

\yskip\hang|@!put1| 133 |c[1]|. Typeset character number~|c| from font~|f|
such that the reference point of the character is at |(h, v)|. (The `put'
commands are exactly like the `set' commands, except that they simply put out a
character or a rule without moving the reference point afterwards.)

\yskip\hang|@!put2| 134 |c[2]|. Same as |set2|, except that |h| is not changed.

\yskip\hang|@!put3| 135 |c[3]|. Same as |set3|, except that |h| is not changed.

\yskip\hang|@!put4| 136 |c[4]|. Same as |set4|, except that |h| is not changed.

\yskip\hang|put_rule| 137 |a[4]| |b[4]|. Same as |set_rule|, except that
|h| is not changed.

\yskip\hang|nop| 138. No operation, do nothing. Any number of |nop|'s
may occur between \.{DVI} commands, but a |nop| cannot be inserted between
a command and its parameters or between two parameters.

\yskip\hang|bop| 139 $c_0[4]$ $c_1[4]$ $\ldots$ $c_9[4]$ $p[4]$. Beginning
of a page: Set |(h, v, w, x, y, z)=(0, 0, 0, 0, 0, 0)| and set the stack empty. Set
the current font |f| to an undefined value.  The ten $c_i$ parameters hold
the values of \.{\\count0} $\ldots$ \.{\\count9} in \TeX\ at the time
\.{\\shipout} was invoked for this page; they can be used to identify
pages, if a user wants to print only part of a \.{DVI} file. The parameter
|p| points to the previous |bop| in the file; the first
|bop| has $p=-1$.

\yskip\hang|eop| 140.  End of page: Print what you have read since the
previous |bop|. At this point the stack should be empty. (The \.{DVI}-reading
programs that drive most output devices will have kept a buffer of the
material that appears on the page that has just ended. This material is
largely, but not entirely, in order by |v| coordinate and (for fixed |v|) by
|h|~coordinate; so it usually needs to be sorted into some order that is
appropriate for the device in question.)

\yskip\hang|push| 141. Push the current values of |(h, v, w, x, y, z)| onto the
top of the stack; do not change any of these values. Note that |f| is
not pushed.

\yskip\hang|pop| 142. Pop the top six values off of the stack and assign
them respectively to |(h, v, w, x, y, z)|. The number of pops should never
exceed the number of pushes, since it would be highly embarrassing if the
stack were empty at the time of a |pop| command.

\yskip\hang|right1| 143 |b[1]|. Set |h=h+b|, i.e., move right |b| units.
The parameter is a signed number in two's complement notation, |-128 <= b < 128|;
if |b < 0|, the reference point moves left.

\yskip\hang|@!right2| 144 |b[2]|. Same as |right1|, except that |b| is a
two-byte quantity in the range |-32768 <= b < 32768|.

\yskip\hang|@!right3| 145 |b[3]|. Same as |right1|, except that |b| is a
three-byte quantity in the range |@t$-2^{23}$@> <= b < @t$2^{23}$@>|.

\yskip\hang|@!right4| 146 |b[4]|. Same as |right1|, except that |b| is a
four-byte quantity in the range |@t$-2^{31}$@> <= b < @t$2^{31}$@>|.

\yskip\hang|w0| 147. Set |h=h+w|; i.e., move right |w| units. With luck,
this parameterless command will usually suffice, because the same kind of motion
will occur several times in succession; the following commands explain how
|w| gets particular values.

\yskip\hang|w1| 148 |b[1]|. Set |w=b| and |h=h+b|. The value of |b| is a
signed quantity in two's complement notation, |-128 <= b < 128|. This command
changes the current |w|~spacing and moves right by |b|.

\yskip\hang|@!w2| 149 |b[2]|. Same as |w1|, but |b| is two bytes long,
|-32768 <= b < 32768|.

\yskip\hang|@!w3| 150 |b[3]|. Same as |w1|, but |b| is three bytes long,
|@t$-2^{23}$@> <= b < @t$2^{23}$@>|.

\yskip\hang|@!w4| 151 |b[4]|. Same as |w1|, but |b| is four bytes long,
|@t$-2^{31}$@> <= b < @t$2^{31}$@>|.

\yskip\hang|x0| 152. Set |h=h+x|; i.e., move right |x| units. The `|x|'
commands are like the `|w|' commands except that they involve |x| instead
of |w|.

\yskip\hang|x1| 153 |b[1]|. Set |x=b| and |h=h+b|. The value of |b| is a
signed quantity in two's complement notation, |-128 <= b < 128|. This command
changes the current |x|~spacing and moves right by |b|.

\yskip\hang|@!x2| 154 |b[2]|. Same as |x1|, but |b| is two bytes long,
|-32768 <= b < 32768|.

\yskip\hang|@!x3| 155 |b[3]|. Same as |x1|, but |b| is three bytes long,
|@t$-2^{23}$@> <= b < @t$2^{23}$@>|.

\yskip\hang|@!x4| 156 |b[4]|. Same as |x1|, but |b| is four bytes long,
|@t$-2^{31}$@> <= b < @t$2^{31}$@>|.

\yskip\hang|down1| 157 |a[1]|. Set |v=v+a|, i.e., move down |a| units.
The parameter is a signed number in two's complement notation, |-128 <= a < 128|;
if |a < 0|, the reference point moves up.

\yskip\hang|@!down2| 158 |a[2]|. Same as |down1|, except that |a| is a
two-byte quantity in the range |-32768 <= a < 32768|.

\yskip\hang|@!down3| 159 |a[3]|. Same as |down1|, except that |a| is a
three-byte quantity in the range |@t$-2^{23}$@> <= a < @t$2^{23}$@>|.

\yskip\hang|@!down4| 160 |a[4]|. Same as |down1|, except that |a| is a
four-byte quantity in the range |@t$-2^{31}$@> <= a < @t$2^{31}$@>|.

\yskip\hang|y0| 161. Set |v=v+y|; i.e., move down |y| units. With luck,
this parameterless command will usually suffice, because the same kind of motion
will occur several times in succession; the following commands explain how
|y| gets particular values.

\yskip\hang|y1| 162 |a[1]|. Set |y=a| and |v=v+a|. The value of |a| is a
signed quantity in two's complement notation, |-128 <= a < 128|. This command
changes the current |y|~spacing and moves down by |a|.

\yskip\hang|@!y2| 163 |a[2]|. Same as |y1|, but |a| is two bytes long,
|-32768 <= a < 32768|.

\yskip\hang|@!y3| 164 |a[3]|. Same as |y1|, but |a| is three bytes long,
|@t$-2^{23}$@> <= a < @t$2^{23}$@>|.

\yskip\hang|@!y4| 165 |a[4]|. Same as |y1|, but |a| is four bytes long,
|@t$-2^{31}$@> <= a < @t$2^{31}$@>|.

\yskip\hang|z0| 166. Set |v=v+z|; i.e., move down |z| units. The `|z|' commands
are like the `|y|' commands except that they involve |z| instead of |y|.

\yskip\hang|z1| 167 |a[1]|. Set |z=a| and |v=v+a|. The value of |a| is a
signed quantity in two's complement notation, |-128 <= a < 128|. This command
changes the current |z|~spacing and moves down by |a|.

\yskip\hang|@!z2| 168 |a[2]|. Same as |z1|, but |a| is two bytes long,
|-32768 <= a < 32768|.

\yskip\hang|@!z3| 169 |a[3]|. Same as |z1|, but |a| is three bytes long,
|@t$-2^{23}$@> <= a < @t$2^{23}$@>|.

\yskip\hang|@!z4| 170 |a[4]|. Same as |z1|, but |a| is four bytes long,
|@t$-2^{31}$@> <= a < @t$2^{31}$@>|.

\yskip\hang|fnt_num_0| 171. Set |f=0|. Font 0 must previously have been
defined by a \\{fnt\_def} instruction, as explained below.

\yskip\hang\\{fnt\_num\_1} through \\{fnt\_num\_63} (opcodes 172 to 234). Set
|f=1|, \dots, \hbox{|f=63|}, respectively.

\yskip\hang|fnt1| 235 |k[1]|. Set |f=k|. \TeX82 uses this command for font
numbers in the range |64 <= k < 256|.

\yskip\hang|@!fnt2| 236 |k[2]|. Same as |fnt1|, except that |k|~is two
bytes long, so it is in the range |0 <= k < 65536|. \TeX82 never generates this
command, but large font numbers may prove useful for specifications of
color or texture, or they may be used for special fonts that have fixed
numbers in some external coding scheme.

\yskip\hang|@!fnt3| 237 |k[3]|. Same as |fnt1|, except that |k|~is three
bytes long, so it can be as large as $2^{24}-1$.

\yskip\hang|@!fnt4| 238 |k[4]|. Same as |fnt1|, except that |k|~is four
bytes long; this is for the really big font numbers (and for the negative ones).

\yskip\hang|xxx1| 239 |k[1]| |x[k]|. This command is undefined in
general; it functions as a $(k+2)$-byte |nop| unless special \.{DVI}-reading
programs are being used. \TeX82 generates |xxx1| when a short enough
\.{\\special} appears, setting |k| to the number of bytes being sent. It
is recommended that |x| be a string having the form of a keyword followed
by possible parameters relevant to that keyword.

\yskip\hang|@!xxx2| 240 |k[2]| |x[k]|. Like |xxx1|, but |0 <= k < 65536|.

\yskip\hang|@!xxx3| 241 |k[3]| |x[k]|. Like |xxx1|, but |0 <= k < @t$2^{24}$@>|.

\yskip\hang|xxx4| 242 |k[4]| |x[k]|. Like |xxx1|, but |k| can be ridiculously
large. \TeX82 uses |xxx4| when sending a string of length 256 or more.

\yskip\hang|fnt_def1| 243 |k[1]| |c[4]| |s[4]| |d[4]| |a[1]| |l[1]| |n[a+l]|.
Define font |k|, where |0 <= k < 256|; font definitions will be explained shortly.

\yskip\hang|@!fnt_def2| 244 |k[2]| |c[4]| |s[4]| |d[4]| |a[1]| |l[1]| |n[a+l]|.
Define font |k|, where |0 <= k < 65536|.

\yskip\hang|@!fnt_def3| 245 |k[3]| |c[4]| |s[4]| |d[4]| |a[1]| |l[1]| |n[a+l]|.
Define font |k|, where |0 <= k < @t$2^{24}$@>|.

\yskip\hang|@!fnt_def4| 246 |k[4]| |c[4]| |s[4]| |d[4]| |a[1]| |l[1]| |n[a+l]|.
Define font |k|, where |@t$-2^{31}$@> <= k < @t$2^{31}$@>|.

\yskip\hang|pre| 247 |i[1]| |num[4]| |den[4]| |mag[4]| |k[1]| |x[k]|.
Beginning of the preamble; this must come at the very beginning of the
file. Parameters |i|, |num|, |den|, |mag|, |k|, and |x| are explained below.

\yskip\hang|post| 248. Beginning of the postamble, see below.

\yskip\hang|post_post| 249. Ending of the postamble, see below.

\yskip\noindent Commands 250--255 are undefined at the present time.

@ Font definitions for a given font number |k| contain further parameters
$$\hbox{|c[4]| |s[4]| |d[4]| |a[1]| |l[1]| |n[a+l]|.}$$
The four-byte value |c| is the check sum that \TeX\ found in the \.{TFM}
file for this font; |c| should match the check sum of the font found by
programs that read this \.{DVI} file.
@^check sum@>

Parameter |s| contains a fixed-point scale factor that is applied to
the character widths in font |k|; font dimensions in \.{TFM} files and
other font files are relative to this quantity, which is called the
``at size'' elsewhere in this documentation. The value of |s| is
always positive and less than $2^{27}$. It is given in the same units
as the other \.{DVI} dimensions, i.e., in sp when \TeX82 has made the
file.  Parameter |d| is similar to |s|; it is the ``design size,'' and
(like~|s|) it is given in \.{DVI} units. Thus, font |k| is to be used
at $|mag|\cdot s/1000d$ times its normal size.

The remaining part of a font definition gives the external name of the font,
which is an ASCII string of length |a+l|. The number |a| is the length
of the ``area'' or directory, and |l| is the length of the font name itself;
the standard local system font area is supposed to be used when |a==0|.
The |n| field contains the area in its first |a| bytes.

Font definitions must appear before the first use of a particular font number.
Once font |k| is defined, it must not be defined again; however, we
shall see below that font definitions appear in the postamble as well as
in the pages, so in this sense each font number is defined exactly twice,
if at all. Like |nop| commands, font definitions can
appear before the first |bop|, or between an |eop| and a |bop|.

@ Sometimes it is desirable to make horizontal or vertical rules line up
precisely with certain features in characters of a font. It is possible to
guarantee the correct matching between \.{DVI} output and the characters
generated by \MF\ by adhering to the following principles: (1)~The \MF\
characters should be positioned so that a bottom edge or left edge that is
supposed to line up with the bottom or left edge of a rule appears at the
reference point, i.e., in row~0 and column~0 of the \MF\ raster. This
ensures that the position of the rule will not be rounded differently when
the pixel size is not a perfect multiple of the units of measurement in
the \.{DVI} file. (2)~A typeset rule of height $a>0$ and width $b>0$
should be equivalent to a \MF-generated character having black pixels in
precisely those raster positions whose \MF\ coordinates satisfy
|0 <= x < @t$\alpha$@>b| and |0 <= y < @t$\alpha$@>a|, where $\alpha$ is the number
of pixels per \.{DVI} unit.
@:METAFONT}{\MF@>
@^alignment of rules with characters@>
@^rules aligning with characters@>

@ The last page in a \.{DVI} file is followed by `|post|'; this command
introduces the postamble, which summarizes important facts that \TeX\ has
accumulated about the file, making it possible to print subsets of the data
with reasonable efficiency. The postamble has the form
$$\vbox{\halign{\hbox{#\hfil}\cr
  |post| |p[4]| |num[4]| |den[4]| |mag[4]| |l[4]| |u[4]| |s[2]| |t[2]|\cr
  $\langle\,$font definitions$\,\rangle$\cr
  |post_post| |q[4]| |i[1]| 223's$[{\G}4]$\cr}}$$
Here |p| is a pointer to the final |bop| in the file. The next three
parameters, |num|, |den|, and |mag|, are duplicates of the quantities that
appeared in the preamble.

Parameters |l| and |u| give respectively the height-plus-depth of the tallest
page and the width of the widest page, in the same units as other dimensions
of the file. These numbers might be used by a \.{DVI}-reading program to
position individual ``pages'' on large sheets of film or paper; however,
the standard convention for output on normal size paper is to position each
page so that the upper left-hand corner is exactly one inch from the left
and the top. Experience has shown that it is unwise to design \.{DVI}-to-printer
software that attempts cleverly to center the output; a fixed position of
the upper left corner is easiest for users to understand and to work with.
Therefore |l| and~|u| are often ignored.

Parameter |s| is the maximum stack depth (i.e., the largest excess of
|push| commands over |pop| commands) needed to process this file. Then
comes |t|, the total number of pages (|bop| commands) present.

The postamble continues with font definitions, which are any number of
\\{fnt\_def} commands as described above, possibly interspersed with |nop|
commands. Each font number that is used in the \.{DVI} file must be defined
exactly twice: Once before it is first selected by a \\{fnt} command, and once
in the postamble.

@ The last part of the postamble, following the |post_post| byte that
signifies the end of the font definitions, contains |q|, a pointer to the
|post| command that started the postamble.  An identification byte, |i|,
comes next; this currently equals~2, as in the preamble.

The |i| byte is followed by four or more bytes that are all equal to
the decimal number 223 (i.e., 0337 in octal). \TeX\ puts out four to seven of
these trailing bytes, until the total length of the file is a multiple of
four bytes, since this works out best on machines that pack four bytes per
word; but any number of 223's is allowed, as long as there are at least four
of them. In effect, 223 is a sort of signature that is added at the very end.
@^Fuchs, David Raymond@>

This curious way to finish off a \.{DVI} file makes it feasible for
\.{DVI}-reading programs to find the postamble first, on most computers,
even though \TeX\ wants to write the postamble last. Most operating
systems permit random access to individual words or bytes of a file, so
the \.{DVI} reader can start at the end and skip backwards over the 223's
until finding the identification byte. Then it can back up four bytes, read
|q|, and move to byte |q| of the file. This byte should, of course,
contain the value 248 (|post|); now the postamble can be read, so the
\.{DVI} reader can discover all the information needed for typesetting the
pages. Note that it is also possible to skip through the \.{DVI} file at
reasonably high speed to locate a particular page, if that proves
desirable. This saves a lot of time, since \.{DVI} files used in production
jobs tend to be large.

Unfortunately, however, standard \PASCAL\ does not include the ability to
@^system dependencies@>
access a random position in a file, or even to determine the length of a file.
Almost all systems nowadays provide the necessary capabilities, so \.{DVI}
format has been designed to work most efficiently with modern operating systems.
But if \.{DVI} files have to be processed under the restrictions of standard
\PASCAL, one can simply read them from front to back, since the necessary
header information is present in the preamble and in the font definitions.
(The |l| and |u| and |s| and |t| parameters, which appear only in the
postamble, are ``frills'' that are handy but not absolutely necessary.)

@* Shipping pages out.

@ @d billion float_constant(1000000000)
@d vet_glue(A) glue_temp=A;
  if (glue_temp > billion)
           glue_temp=billion;
  else if (glue_temp < -billion)
           glue_temp=-billion

@* Packaging.
We're essentially done with the parts of \TeX\ that are concerned with
the input (|get_next|) and the output (|ship_out|). So it's time to
get heavily into the remaining part, which does the real work of typesetting.

After lists are constructed, \TeX\ wraps them up and puts them into boxes.
Two major subroutines are given the responsibility for this task: |hpack|
applies to horizontal lists (hlists) and |vpack| applies to vertical lists
(vlists). The main duty of |hpack| and |vpack| is to compute the dimensions
of the resulting boxes, and to adjust the glue if one of those dimensions
is pre-specified. The computed sizes normally enclose all of the material
inside the new box; but some items may stick out if negative glue is used,
if the box is overfull, or if a \.{\\vbox} includes other boxes that have
been shifted left.

The subroutine call |hpack(p, w, m)| returns a pointer to an |hlist_node|
for a box containing the hlist that starts at |p|. Parameter |w| specifies
a width; and parameter |m| is either `|exactly|' or `|additional|'.  Thus,
|hpack(p, w, exactly)| produces a box whose width is exactly |w|, while
|hpack(p, w, additional)| yields a box whose width is the natural width plus
|w|.  It is convenient to define a macro called `|natural|' to cover the
most common case, so that we can say |hpack(p, natural)| to get a box that
has the natural width of list |p|.

Similarly, |vpack(p, w, m)| returns a pointer to a |vlist_node| for a
box containing the vlist that starts at |p|. In this case |w| represents
a height instead of a width; the parameter |m| is interpreted as in |hpack|.

@d exactly 0 /*a box dimension is pre-specified*/
@d additional 1 /*a box dimension is increased from the natural one*/
@d natural 0, additional /*shorthand for parameters to |hpack| and |vpack|*/

@ To figure out the glue setting, |hpack| and |vpack| determine how much
stretchability and shrinkability are present, considering all four orders
of infinity. The highest order of infinity that has a nonzero coefficient
is then used as if no other orders were present.

For example, suppose that the given list contains six glue nodes with
the respective stretchabilities 3pt, 8fill, 5fil, 6pt, $-3$fil, $-8$fill.
Then the total is essentially 2fil; and if a total additional space of 6pt
is to be achieved by stretching, the actual amounts of stretch will be
0pt, 0pt, 15pt, 0pt, $-9$pt, and 0pt, since only `fil' glue will be
considered. (The `fill' glue is therefore not really stretching infinitely
with respect to `fil'; nobody would actually want that to happen.)

The arrays |total_stretch| and |total_shrink| are used to determine how much
glue of each kind is present. A global variable |last_badness| is used
to implement \.{\\badness}.

@<Selected global variables@>=
static scaled @!total_stretch0[filll-normal+1],
  *const @!total_stretch = @!total_stretch0-normal,
  @!total_shrink0[filll-normal+1], *const @!total_shrink = @!total_shrink0-normal;
   /*glue found by |hpack| or |vpack|*/

@ If the global variable |adjust_tail| is non-null, the |hpack| routine
also removes all occurrences of |ins_node|, |mark_node|, and |adjust_node|
items and appends the resulting material onto the list that ends at
location |adjust_tail|.

@<Selected global variables@>=
static pointer @!adjust_tail=null; /*tail of adjustment list*/


@ Here now is |hpack|, which contains few if any surprises.

@<\TeX\ functions@>=
static pointer hpack(pointer @!p, scaled @!w, small_number @!m)
{@+
pointer r; /*the box node that will be returned*/
pointer @!q; /*trails behind |p|*/
scaled @!h, @!d, @!x; /*height, depth, and natural width*/
scaled @!s; /*shift amount*/
pointer @!g; /*points to a glue specification*/
glue_ord @!o; /*order of infinity*/
internal_font_number @!f; /*the font in a |char_node|*/
four_quarters @!i; /*font information about a |char_node|*/
eight_bits @!hd; /*height and depth indices for a character*/
r=get_node(box_node_size);type(r)=hlist_node;
subtype(r)=min_quarterword;shift_amount(r)=0;
q=r+list_offset;link(q)=p;@/
h=0;@<Clear dimensions to zero@>;
while (p!=null) @<Examine node |p| in the hlist, taking account of its effect
on the dimensions of the new box, or moving it to the adjustment list; then
advance |p| to the next node@>;
if (adjust_tail!=null) link(adjust_tail)=null;
height(r)=h;depth(r)=d;@/
@<Determine the value of |width(r)| and the appropriate glue setting; then
|return| or |goto common_ending|@>;
end: return r;
}

@ @<Clear dimensions to zero@>=
d=0;x=0;
total_stretch[normal]=0;total_shrink[normal]=0;
total_stretch[fil]=0;total_shrink[fil]=0;
total_stretch[fill]=0;total_shrink[fill]=0;
total_stretch[filll]=0;total_shrink[filll]=0

@ @<Examine node |p| in the hlist, taking account of its effect...@>=
@^inner loop@>
{@+reswitch: while (is_char_node(p))
  @<Incorporate character dimensions into the dimensions of the hbox that
will contain~it, then move to the next node@>;
if (p!=null)
  {@+switch (type(p)) {
  case hlist_node: case vlist_node: case rule_node:
  case unset_node:
    @<Incorporate box dimensions into the dimensions of the hbox that will
contain~it@>@;@+break;
  case ins_node: case mark_node: case adjust_node: if (adjust_tail!=null)
    @<Transfer node |p| to the adjustment list@>@;@+break;
  case whatsit_node: @<Incorporate a whatsit node into an hbox@>;@+break;
  case glue_node: @<Incorporate glue into the horizontal totals@>@;@+break;
  case kern_node: case math_node: x=x+width(p);@+break;
  case ligature_node: @<Make node |p| look like a |char_node| and |goto reswitch|@>@;
  default:do_nothing;
  } @/
  p=link(p);
  }
}


@ @<Make node |p| look like a |char_node| and |goto reswitch|@>=
{@+mem[lig_trick]=mem[lig_char(p)];link(lig_trick)=link(p);
p=lig_trick;goto reswitch;
}

@ The code here implicitly uses the fact that running dimensions are
indicated by |null_flag|, which will be ignored in the calculations
because it is a highly negative number.

@<Incorporate box dimensions into the dimensions of the hbox...@>=
{@+x=x+width(p);
if (type(p) >= rule_node) s=0;@+else s=shift_amount(p);
if (height(p)-s > h) h=height(p)-s;
if (depth(p)+s > d) d=depth(p)+s;
}

@ The following code is part of \TeX's inner loop; i.e., adding another
character of text to the user's input will cause each of these instructions
to be exercised one more time.
@^inner loop@>

@<Incorporate character dimensions into the dimensions of the hbox...@>=
{@+f=font(p);
 if (width_base[f]!=0)
 { i=char_info(f, character(p));hd=height_depth(i);
   x=x+char_width(f, character(p));
   s=char_height(f, hd);@+if (s > h) h=s;
   s=char_depth(f, hd);@+if (s > d) d=s;
 }
 else
 { scaled ch, cd;
   FT_Face ft_face=font_face[f];
   if (ft_face==NULL)
     ft_face=hload_font_face(f);
   if (ft_face!=NULL)
   { FT_UInt ft_gid = FT_Get_Char_Index(ft_face, character(p));
     if (ft_gid!=0)
     x=x+ft_glyph_width(ft_face, ft_gid,font_size[f]);
     ft_glyph_height_depth(ft_face, ft_gid, &ch, &cd, font_size[f]);
     if (ch > h) h=ch;
     if (cd > d) d=cd;
   }
 }
p=link(p);
}

@ Although node |q| is not necessarily the immediate predecessor of node |p|,
it always points to some node in the list preceding |p|. Thus, we can delete
nodes by moving |q| when necessary. The algorithm takes linear time, and the
extra computation does not intrude on the inner loop unless it is necessary
to make a deletion.
@^inner loop@>

@<Transfer node |p| to the adjustment list@>=
{@+while (link(q)!=p) q=link(q);
if (type(p)==adjust_node)
  {@+link(adjust_tail)=adjust_ptr(p);
  while (link(adjust_tail)!=null) adjust_tail=link(adjust_tail);
  p=link(p);free_node(link(q), small_node_size);
  }
else{@+link(adjust_tail)=p;adjust_tail=p;p=link(p);
  }
link(q)=p;p=q;
}

@ @<Incorporate glue into the horizontal totals@>=
{@+g=glue_ptr(p);x=x+width(g);@/
o=stretch_order(g);total_stretch[o]=total_stretch[o]+stretch(g);
o=shrink_order(g);total_shrink[o]=total_shrink[o]+shrink(g);
if (subtype(p) >= a_leaders)
  {@+g=leader_ptr(p);
  if (height(g) > h) h=height(g);
  if (depth(g) > d) d=depth(g);
  }
}

@ When we get to the present part of the program, |x| is the natural width
of the box being packaged.

@<Determine the value of |width(r)| and the appropriate glue setting...@>=
if (m==additional) w=x+w;
width(r)=w;x=w-x; /*now |x| is the excess to be made up*/
if (x==0)
  {@+glue_sign(r)=normal;glue_order(r)=normal;
  set_glue_ratio_zero(glue_set(r));
  goto end;
  }
else if (x > 0) @<Determine horizontal glue stretch setting, then |return|
or \hbox{|goto common_ending|}@>@;
else@<Determine horizontal glue shrink setting, then |return| or \hbox{|goto
common_ending|}@>@;

@ @<Determine horizontal glue stretch setting...@>=
{@+@<Determine the stretch order@>;
glue_order(r)=o;glue_sign(r)=stretching;
if (total_stretch[o]!=0) glue_set(r)=fix(x/(double)total_stretch[o]);
@^real division@>
else{@+glue_sign(r)=normal;
  set_glue_ratio_zero(glue_set(r)); /*there's nothing to stretch*/
  }
goto end;
}

@ @<Determine the stretch order@>=
if (total_stretch[filll]!=0) o=filll;
else if (total_stretch[fill]!=0) o=fill;
else if (total_stretch[fil]!=0) o=fil;
else o=normal

@ @<Determine horizontal glue shrink setting...@>=
{@+@<Determine the shrink order@>;
glue_order(r)=o;glue_sign(r)=shrinking;
if (total_shrink[o]!=0) glue_set(r)=fix((-x)/(double)total_shrink[o]);
@^real division@>
else{@+glue_sign(r)=normal;
  set_glue_ratio_zero(glue_set(r)); /*there's nothing to shrink*/
  }
if ((total_shrink[o] < -x)&&(o==normal)&&(list_ptr(r)!=null))
  set_glue_ratio_one(glue_set(r)); /*use the maximum shrinkage*/
goto end;
}

@ @<Determine the shrink order@>=
if (total_shrink[filll]!=0) o=filll;
else if (total_shrink[fill]!=0) o=fill;
else if (total_shrink[fil]!=0) o=fil;
else o=normal


@ The |vpack| subroutine is actually a special case of a slightly more
general routine called |vpackage|, which has four parameters. The fourth
parameter, which is |max_dimen| in the case of |vpack|, specifies the
maximum depth of the page box that is constructed. The depth is first
computed by the normal rules; if it exceeds this limit, the reference
point is simply moved down until the limiting depth is attained.

@d vpack(A,B) @[vpackage(A,B, max_dimen)@] /*special case of unconstrained depth*/

@<\TeX\ functions@>=
static pointer vpackage(pointer @!p, scaled @!h, small_number @!m, scaled @!l)
{@+
pointer r; /*the box node that will be returned*/
scaled @!w, @!d, @!x; /*width, depth, and natural height*/
scaled @!s; /*shift amount*/
pointer @!g; /*points to a glue specification*/
glue_ord @!o; /*order of infinity*/
r=get_node(box_node_size);type(r)=vlist_node;
subtype(r)=min_quarterword;shift_amount(r)=0;
list_ptr(r)=p;@/
w=0;@<Clear dimensions to zero@>;
while (p!=null) @<Examine node |p| in the vlist, taking account of its effect
on the dimensions of the new box; then advance |p| to the next node@>;
width(r)=w;
if (d > l)
  {@+x=x+d-l;depth(r)=l;
  }
else depth(r)=d;
@<Determine the value of |height(r)| and the appropriate glue setting; then
|return| or |goto common_ending|@>;
end: return r;
}

@ @<Examine node |p| in the vlist, taking account of its effect...@>=
{@+if (is_char_node(p)) confusion("vpack");
@:this can't happen vpack}{\quad vpack@>
else switch (type(p)) {
  case hlist_node: case vlist_node: case rule_node:
  case unset_node:
    @<Incorporate box dimensions into the dimensions of the vbox that will
contain~it@>@;@+break;
  case whatsit_node: @<Incorporate a whatsit node into a vbox@>;@+break;
  case glue_node: @<Incorporate glue into the vertical totals@>@;@+break;
  case kern_node: {@+x=x+d+width(p);d=0;
    } @+break;
  default:do_nothing;
  }
p=link(p);
}

@ @<Incorporate box dimensions into the dimensions of the vbox...@>=
{@+x=x+d+height(p);d=depth(p);
if (type(p) >= rule_node) s=0;@+else s=shift_amount(p);
if (width(p)+s > w) w=width(p)+s;
}

@ @<Incorporate glue into the vertical totals@>=
{@+x=x+d;d=0;@/
g=glue_ptr(p);x=x+width(g);@/
o=stretch_order(g);total_stretch[o]=total_stretch[o]+stretch(g);
o=shrink_order(g);total_shrink[o]=total_shrink[o]+shrink(g);
if (subtype(p) >= a_leaders)
  {@+g=leader_ptr(p);
  if (width(g) > w) w=width(g);
  }
}

@ When we get to the present part of the program, |x| is the natural height
of the box being packaged.

@<Determine the value of |height(r)| and the appropriate glue setting...@>=
if (m==additional) h=x+h;
height(r)=h;x=h-x; /*now |x| is the excess to be made up*/
if (x==0)
  {@+glue_sign(r)=normal;glue_order(r)=normal;
  set_glue_ratio_zero(glue_set(r));
  goto end;
  }
else if (x > 0) @<Determine vertical glue stretch setting, then |return| or
\hbox{|goto common_ending|}@>@;
else@<Determine vertical glue shrink setting, then |return| or \hbox{|goto
common_ending|}@>@;

@ @<Determine vertical glue stretch setting...@>=
{@+@<Determine the stretch order@>;
glue_order(r)=o;glue_sign(r)=stretching;
if (total_stretch[o]!=0) glue_set(r)=fix(x/(double)total_stretch[o]);
@^real division@>
else{@+glue_sign(r)=normal;
  set_glue_ratio_zero(glue_set(r)); /*there's nothing to stretch*/
  }
goto end;
}


@ @<Determine vertical glue shrink setting...@>=
{@+@<Determine the shrink order@>;
glue_order(r)=o;glue_sign(r)=shrinking;
if (total_shrink[o]!=0) glue_set(r)=fix((-x)/(double)total_shrink[o]);
@^real division@>
else{@+glue_sign(r)=normal;
  set_glue_ratio_zero(glue_set(r)); /*there's nothing to shrink*/
  }
if ((total_shrink[o] < -x)&&(o==normal)&&(list_ptr(r)!=null))
  set_glue_ratio_one(glue_set(r)); /*use the maximum shrinkage*/
goto end;
}


@ When a box is being appended to the current vertical list, the
baselineskip calculation is handled by the |append_to_vlist| routine.

@<Declare subprocedures for |line_break|@>=
static pointer happend_to_vlist(pointer b);
static void append_to_vlist(pointer @!b, uint32_t offset)
{@+scaled d; /*deficiency of space between baselines*/
pointer @!p; /*a new glue node*/
if (prev_depth > ignore_depth)
  {@+d=width(baseline_skip)-prev_depth-height(b);
  if (d < line_skip_limit) p=new_glue(line_skip);
  else{@+temp_ptr=new_spec(baseline_skip);
       p=new_glue(temp_ptr);glue_ref_count(temp_ptr)=null;
    width(temp_ptr)=d; /*|temp_ptr==glue_ptr(p)|*/
    }
   store_map(p, node_pos,offset);
  link(tail)=p;tail=p;
  }
link(tail)=b;tail=b;prev_depth=depth(b);
}

@* Data structures for math mode.

@* Subroutines for math mode.


@d math_quad dimen_def[math_quad_no] /*\.{18mu}*/



@* Alignment.

@* Breaking paragraphs into lines.
We come now to what is probably the most interesting algorithm of \TeX:
the mechanism for choosing the ``best possible'' breakpoints that yield
the individual lines of a paragraph. \TeX's line-breaking algorithm takes
a given horizontal list and converts it to a sequence of boxes that are
appended to the current vertical list. In the course of doing this, it
creates a special data structure containing three kinds of records that are
not used elsewhere in \TeX. Such nodes are created while a paragraph is
being processed, and they are destroyed afterwards; thus, the other parts
of \TeX\ do not need to know anything about how line-breaking is done.

The method used here is based on an approach devised by Michael F. Plass and
@^Plass, Michael Frederick@>
@^Knuth, Donald Ervin@>
the author in 1977, subsequently generalized and improved by the same two
people in 1980. A detailed discussion appears in {\sl Software---Practice
and Experience \bf11} (1981), 1119--1184, where it is shown that the
line-breaking problem can be regarded as a special case of the problem of
computing the shortest path in an acyclic network. The cited paper includes
numerous examples and describes the history of line breaking as it has been
practiced by printers through the ages. The present implementation adds two
new ideas to the algorithm of 1980: Memory space requirements are considerably
reduced by using smaller records for inactive nodes than for active ones,
and arithmetic overflow is avoided by using ``delta distances'' instead of
keeping track of the total distance from the beginning of the paragraph to the
current point.

@ The |line_break| procedure should be invoked only in horizontal mode; it
leaves that mode and places its output into the current vlist of the
enclosing vertical mode (or internal vertical mode).
There is one explicit parameter:  |final_widow_penalty| is the amount of
additional penalty to be inserted before the final line of the paragraph.

There are also a number of implicit parameters: The hlist to be broken
starts at |link(head)|, and it is nonempty. The value of |prev_graf| in the
enclosing semantic level tells where the paragraph should begin in the
sequence of line numbers, in case hanging indentation or \.{\\parshape}
is in use; |prev_graf| is zero unless this paragraph is being continued
after a displayed formula.  Other implicit parameters, such as the
|par_shape_ptr| and various penalties to use for hyphenation, etc., appear
in |eqtb|.

After |line_break| has acted, it will have updated the current vlist and the
value of |prev_graf|. Furthermore, the global variable |just_box| will
point to the final box created by |line_break|, so that the width of this
line can be ascertained when it is necessary to decide whether to use
|above_display_skip| or |above_display_short_skip| before a displayed formula.

@<Selected global variables@>=
static pointer @!just_box; /*the |hlist_node| for the last line of the new paragraph*/
static int @!just_color; /* the color at the end of a packed hbox */
static int @!just_label; /* the label reference at the end of a packed hbox */

@ Since |line_break| is a rather lengthy procedure---sort of a small world unto
itself---we must build it up little by little, somewhat more cautiously
than we have done with the simpler procedures of \TeX. Here is the
general outline.

@<\TeX\ functions@>=

@<Declare subprocedures for |line_break|@>@;

static void line_break(int final_widow_penalty, pointer par_ptr)
{@+ scaled x=cur_list.hs_field; /* the |hsize| for this paragraph */
@<Local variables for line breaking@>@;
set_line_break_params(); just_color=-1; just_label=-1;
@<Get ready to start line breaking@>;
@<Find optimal breakpoints@>;
@<Break the paragraph at the chosen breakpoints, justify the resulting lines
to the correct widths, and append them to the current vertical list@>;
@<Clean up the memory by removing the break nodes@>;
hrestore_param_list();
}

@ The first task is to move the list from |head| to |temp_head| and go
into the enclosing semantic level. We also append the \.{\\parfillskip}
glue to the end of the paragraph, removing a space (or other glue node) if
it was there, since spaces usually precede blank lines and instances of
`\.{\$\$}'. The |par_fill_skip| is preceded by an infinite penalty, so
it will never be considered as a potential breakpoint.

This code assumes that a |glue_node| and a |penalty_node| occupy the
same number of |mem|~words.
@^data structure assumptions@>

@<Get ready to start...@>=
link(temp_head)=par_ptr;

@ When looking for optimal line breaks, \TeX\ creates a ``break node'' for
each break that is {\sl feasible}, in the sense that there is a way to end
a line at the given place without requiring any line to stretch more than
a given tolerance. A break node is characterized by three things: the position
of the break (which is a pointer to a |glue_node|, |math_node|, |penalty_node|,
or |disc_node|); the ordinal number of the line that will follow this
breakpoint; and the fitness classification of the line that has just
ended, i.e., |tight_fit|, |decent_fit|, |loose_fit|, or |very_loose_fit|.

@d tight_fit 3 /*fitness classification for lines shrinking 0.5 to 1.0 of their
  shrinkability*/
@d loose_fit 1 /*fitness classification for lines stretching 0.5 to 1.0 of their
  stretchability*/
@d very_loose_fit 0 /*fitness classification for lines stretching more than
  their stretchability*/
@d decent_fit 2 /*fitness classification for all other lines*/

@ The algorithm essentially determines the best possible way to achieve
each feasible combination of position, line, and fitness. Thus, it answers
questions like, ``What is the best way to break the opening part of the
paragraph so that the fourth line is a tight line ending at such-and-such
a place?'' However, the fact that all lines are to be the same length
after a certain point makes it possible to regard all sufficiently large
line numbers as equivalent, when the looseness parameter is zero, and this
makes it possible for the algorithm to save space and time.

An ``active node'' and a ``passive node'' are created in |mem| for each
feasible breakpoint that needs to be considered. Active nodes are three
words long and passive nodes are two words long. We need active nodes only
for breakpoints near the place in the paragraph that is currently being
examined, so they are recycled within a comparatively short time after
they are created.

@ An active node for a given breakpoint contains six fields:

\yskip\hang|link| points to the next node in the list of active nodes; the
last active node has |link==last_active|.

\yskip\hang|break_node| points to the passive node associated with this
breakpoint.

\yskip\hang|line_number| is the number of the line that follows this
breakpoint.

\yskip\hang|fitness| is the fitness classification of the line ending at this
breakpoint.

\yskip\hang|type| is either |hyphenated| or |unhyphenated|, depending on
whether this breakpoint is a |disc_node|.

\yskip\hang|total_demerits| is the minimum possible sum of demerits over all
lines leading from the beginning of the paragraph to this breakpoint.

\yskip\noindent
The value of |link(active)| points to the first active node on a linked list
of all currently active nodes. This list is in order by |line_number|,
except that nodes with |line_number > easy_line| may be in any order relative
to each other.

@d active_node_size 3 /*number of words in active nodes*/
@d fitness(A) subtype(A) /*|very_loose_fit dotdot tight_fit| on final line for this break*/
@d break_node(A) rlink(A) /*pointer to the corresponding passive node*/
@d line_number(A) llink(A) /*line that begins at this breakpoint*/
@d total_demerits(A) mem[A+2].i /*the quantity that \TeX\ minimizes*/
@d unhyphenated 0 /*the |type| of a normal active break node*/
@d hyphenated 1 /*the |type| of an active node that breaks at a |disc_node|*/
@d last_active active /*the active list ends where it begins*/

@ @<Initialize the special list heads...@>=
type(last_active)=hyphenated;line_number(last_active)=max_halfword;
subtype(last_active)=0; /*the |subtype| is never examined by the algorithm*/

@ The passive node for a given breakpoint contains only four fields:

\yskip\hang|link| points to the passive node created just before this one,
if any, otherwise it is |null|.

\yskip\hang|cur_break| points to the position of this breakpoint in the
horizontal list for the paragraph being broken.

\yskip\hang|prev_break| points to the passive node that should precede this
one in an optimal path to this breakpoint.

\yskip\hang|serial| is equal to |n| if this passive node is the |n|th
one created during the current pass. (This field is used only when
printing out detailed statistics about the line-breaking calculations.)

\yskip\noindent
There is a global variable called |passive| that points to the most
recently created passive node. Another global variable, |printed_node|,
is used to help print out the paragraph when detailed information about
the line-breaking computation is being displayed.

@d passive_node_size 2 /*number of words in passive nodes*/
@d cur_break(A) rlink(A) /*in passive node, points to position of this breakpoint*/
@d prev_break(A) llink(A) /*points to passive node that should precede this one*/
@d serial(A) info(A) /*serial number for symbolic identification*/

@<Selected global variables@>=
static pointer @!passive; /*most recent node on passive list*/
static pointer @!printed_node; /*most recent node that has been printed*/
static halfword @!pass_number; /*the number of passive nodes allocated on this pass*/

@ The active list also contains ``delta'' nodes that help the algorithm
compute the badness of individual lines. Such nodes appear only between two
active nodes, and they have |type==delta_node|. If |p| and |r| are active nodes
and if |q| is a delta node between them, so that |link(p)==q| and |link(q)==r|,
then |q| tells the space difference between lines in the horizontal list that
start after breakpoint |p| and lines that start after breakpoint |r|. In
other words, if we know the length of the line that starts after |p| and
ends at our current position, then the corresponding length of the line that
starts after |r| is obtained by adding the amounts in node~|q|. A delta node
contains six scaled numbers, since it must record the net change in glue
stretchability with respect to all orders of infinity. The natural width
difference appears in |mem[q+1].sc|; the stretch differences in units of
pt, fil, fill, and filll appear in |mem[q+2 dotdot q+5].sc|; and the shrink difference
appears in |mem[q+6].sc|. The |subtype| field of a delta node is not used.

@d delta_node_size 7 /*number of words in a delta node*/
@d delta_node 2 /*|type| field in a delta node*/

@ As the algorithm runs, it maintains a set of six delta-like registers
for the length of the line following the first active breakpoint to the
current position in the given hlist. When it makes a pass through the
active list, it also maintains a similar set of six registers for the
length following the active breakpoint of current interest. A third set
holds the length of an empty line (namely, the sum of \.{\\leftskip} and
\.{\\rightskip}); and a fourth set is used to create new delta nodes.

When we pass a delta node we want to do operations like
$$\hbox{\ignorespaces|for
k=1 to 6 do cur_active_width[k]=cur_active_width[k]+mem[q+k].sc|};$$ and we
want to do this without the overhead of |for| loops. The |do_all_six|
macro makes such six-tuples convenient.

@d do_all_six(A) A(1);A(2);A(3);A(4);A(5);A(6)

@<Selected global variables@>=
static scaled @!active_width0[6], *const @!active_width = @!active_width0-1;
   /*distance from first active node to~|cur_p|*/
static scaled @!cur_active_width0[6],
  *const @!cur_active_width = @!cur_active_width0-1; /*distance from current active node*/
static scaled @!background0[6], *const @!background = @!background0-1; /*length of an ``empty'' line*/
static scaled @!break_width0[6], *const @!break_width = @!break_width0-1; /*length being computed after current break*/

@ Let's state the principles of the delta nodes more precisely and concisely,
so that the following programs will be less obscure. For each legal
breakpoint~|p| in the paragraph, we define two quantities $\alpha(p)$ and
$\beta(p)$ such that the length of material in a line from breakpoint~|p|
to breakpoint~|q| is $\gamma+\beta(q)-\alpha(p)$, for some fixed $\gamma$.
Intuitively, $\alpha(p)$ and $\beta(q)$ are the total length of material from
the beginning of the paragraph to a point ``after'' a break at |p| and to a
point ``before'' a break at |q|; and $\gamma$ is the width of an empty line,
namely the length contributed by \.{\\leftskip} and \.{\\rightskip}.

Suppose, for example, that the paragraph consists entirely of alternating
boxes and glue skips; let the boxes have widths $x_1\ldots x_n$ and
let the skips have widths $y_1\ldots y_n$, so that the paragraph can be
represented by $x_1y_1\ldots x_ny_n$. Let $p_i$ be the legal breakpoint
at $y_i$; then $\alpha(p_i)=x_1+y_1+\cdots+x_i+y_i$, and $\beta(p_i)=
x_1+y_1+\cdots+x_i$. To check this, note that the length of material from
$p_2$ to $p_5$, say, is $\gamma+x_3+y_3+x_4+y_4+x_5=\gamma+\beta(p_5)
-\alpha(p_2)$.

The quantities $\alpha$, $\beta$, $\gamma$ involve glue stretchability and
shrinkability as well as a natural width. If we were to compute $\alpha(p)$
and $\beta(p)$ for each |p|, we would need multiple precision arithmetic, and
the multiprecise numbers would have to be kept in the active nodes.
\TeX\ avoids this problem by working entirely with relative differences
or ``deltas.'' Suppose, for example, that the active list contains
$a_1\,\delta_1\,a_2\,\delta_2\,a_3$, where the |a|'s are active breakpoints
and the $\delta$'s are delta nodes. Then $\delta_1=\alpha(a_1)-\alpha(a_2)$
and $\delta_2=\alpha(a_2)-\alpha(a_3)$. If the line breaking algorithm is
currently positioned at some other breakpoint |p|, the |active_width| array
contains the value $\gamma+\beta(p)-\alpha(a_1)$. If we are scanning through
the list of active nodes and considering a tentative line that runs from
$a_2$ to~|p|, say, the |cur_active_width| array will contain the value
$\gamma+\beta(p)-\alpha(a_2)$. Thus, when we move from $a_2$ to $a_3$,
we want to add $\alpha(a_2)-\alpha(a_3)$ to |cur_active_width|; and this
is just $\delta_2$, which appears in the active list between $a_2$ and
$a_3$. The |background| array contains $\gamma$. The |break_width| array
will be used to calculate values of new delta nodes when the active
list is being updated.

@ Glue nodes in a horizontal list that is being paragraphed are not supposed to
include ``infinite'' shrinkability; that is why the algorithm maintains
four registers for stretching but only one for shrinking. If the user tries to
introduce infinite shrinkability, the shrinkability will be reset to finite
and an error message will be issued. A boolean variable |no_shrink_error_yet|
prevents this error message from appearing more than once per paragraph.

@d check_shrinkage(A) if ((shrink_order(A)!=normal)&&(shrink(A)!=0))
  {@+A=finite_shrink(A);
  }

@<Selected global variables@>=
static bool @!no_shrink_error_yet; /*have we complained about infinite shrinkage?*/

@ @<Declare subprocedures for |line_break|@>=
static pointer finite_shrink(pointer @!p) /*recovers from infinite shrinkage*/
{@+pointer q; /*new glue specification*/
  QUIT("Infinite glue shrinkage found in a paragraph");
q=new_spec(p);shrink_order(q)=normal;
delete_glue_ref(p);return q;
}

@ @<Get ready to start...@>=
no_shrink_error_yet=true;@/
check_shrinkage(left_skip);check_shrinkage(right_skip);@/
q=left_skip;r=right_skip;background[1]=width(q)+width(r);@/
background[2]=0;background[3]=0;background[4]=0;background[5]=0;@/
background[2+stretch_order(q)]=stretch(q);@/
background[2+stretch_order(r)]=@|background[2+stretch_order(r)]+stretch(r);@/
background[6]=shrink(q)+shrink(r);

@ A pointer variable |cur_p| runs through the given horizontal list as we look
for breakpoints. This variable is global, since it is used both by |line_break|
and by its subprocedure |try_break|.

Another global variable called |threshold| is used to determine the feasibility
of individual lines: Breakpoints are feasible if there is a way to reach
them without creating lines whose badness exceeds |threshold|.  (The
badness is compared to |threshold| before penalties are added, so that
penalty values do not affect the feasibility of breakpoints, except that
no break is allowed when the penalty is 10000 or more.) If |threshold|
is 10000 or more, all legal breaks are considered feasible, since the
|badness| function specified above never returns a value greater than~10000.

Up to three passes might be made through the paragraph in an attempt to find at
least one set of feasible breakpoints. On the first pass, we have
|threshold==pretolerance| and |second_pass==final_pass==false|.
If this pass fails to find a
feasible solution, |threshold| is set to |tolerance|, |second_pass| is set
|true|, and an attempt is made to hyphenate as many words as possible.
If that fails too, we add |emergency_stretch| to the background
stretchability and set |final_pass==true|.

@<Selected global variables@>=
static pointer @!cur_p; /*the current breakpoint under consideration*/
static bool @!second_pass; /*is this our second attempt to break this paragraph?*/
static bool @!final_pass; /*is this our final attempt to break this paragraph?*/
static int @!threshold; /*maximum badness on feasible lines*/

@ The heart of the line-breaking procedure is `|try_break|', a subroutine
that tests if the current breakpoint |cur_p| is feasible, by running
through the active list to see what lines of text can be made from active
nodes to~|cur_p|.  If feasible breaks are possible, new break nodes are
created.  If |cur_p| is too far from an active node, that node is
deactivated.

The parameter |pi| to |try_break| is the penalty associated
with a break at |cur_p|; we have |pi==eject_penalty| if the break is forced,
and |pi==inf_penalty| if the break is illegal.

The other parameter, |break_type|, is set to |hyphenated| or |unhyphenated|,
depending on whether or not the current break is at a |disc_node|. The
end of a paragraph is also regarded as `|hyphenated|'; this case is
distinguishable by the condition |cur_p==null|.

@d copy_to_cur_active(A) cur_active_width[A]=active_width[A]
@<Declare subprocedures for |line_break|@>=
static void try_break(int @!pi, small_number @!break_type)
{@+
pointer r; /*runs through the active list*/
pointer @!prev_r; /*stays a step behind |r|*/
halfword @!old_l; /*maximum line number in current equivalence class of lines*/
bool @!no_break_yet; /*have we found a feasible break at |cur_p|?*/
@<Other local variables for |try_break|@>@;
@<Make sure that |pi| is in the proper range@>@;
no_break_yet=true;prev_r=active;old_l=0;
do_all_six(copy_to_cur_active);
loop@+{@+resume: r=link(prev_r);
  @<If node |r| is of type |delta_node|, update |cur_active_width|, set |prev_r|
and |prev_prev_r|, then |goto continue|@>;
  @<If a line number class has ended, create new active nodes for the best
feasible breaks in that class; then |return| if |r=last_active|, otherwise
compute the new |line_width|@>;
  @<Consider the demerits for a line from |r| to |cur_p|; deactivate node
|r| if it should no longer be active; then |goto continue| if a line from
|r| to |cur_p| is infeasible, otherwise record a new feasible break@>;
  }
end: ;
#ifdef @!STAT
@<Update the value of |printed_node| for symbolic displays@>;
#endif
@;
}

@ @<Other local variables for |try_break|@>=
pointer @!prev_prev_r=null; /*a step behind |prev_r|, if |type(prev_r)==delta_node|*/
pointer @!s; /*runs through nodes ahead of |cur_p|*/
pointer @!q; /*points to a new node being created*/
pointer @!v; /*points to a glue specification or a node ahead of |cur_p|*/
int @!t; /*node count, if |cur_p| is a discretionary node*/
internal_font_number @!f; /*used in character width calculation*/
halfword @!l; /*line number of current active node*/
bool @!node_r_stays_active; /*should node |r| remain in the active list?*/
scaled @!line_width=0; /*the current line will be justified to this width*/
int @!fit_class; /*possible fitness class of test line*/
halfword @!b; /*badness of test line*/
int @!d; /*demerits of test line*/
bool @!artificial_demerits; /*has |d| been forced to zero?*/
#ifdef @!STAT
pointer @!save_link; /*temporarily holds value of |link(cur_p)|*/
#endif
scaled @!shortfall; /*used in badness calculations*/

@ @<Make sure that |pi| is in the proper range@>=
if (abs(pi) >= inf_penalty)
{ if (pi > 0) goto end; /*this breakpoint is inhibited by infinite penalty*/
  else pi=eject_penalty; /*this breakpoint will be forced*/
}

@ The following code uses the fact that |type(last_active)!=delta_node|.

@d update_width(A) @|
  cur_active_width[A]=cur_active_width[A]+mem[r+A].sc

@<If node |r|...@>=
@^inner loop@>
if (type(r)==delta_node)
  {@+do_all_six(update_width);
  prev_prev_r=prev_r;prev_r=r;goto resume;
  }

@ As we consider various ways to end a line at |cur_p|, in a given line number
class, we keep track of the best total demerits known, in an array with
one entry for each of the fitness classifications. For example,
|minimal_demerits[tight_fit]| contains the fewest total demerits of feasible
line breaks ending at |cur_p| with a |tight_fit| line; |best_place[tight_fit]|
points to the passive node for the break before~|cur_p| that achieves such
an optimum; and |best_pl_line[tight_fit]| is the |line_number| field in the
active node corresponding to |best_place[tight_fit]|. When no feasible break
sequence is known, the |minimal_demerits| entries will be equal to
|awful_bad|, which is $2^{30}-1$. Another variable, |minimum_demerits|,
keeps track of the smallest value in the |minimal_demerits| array.

@d awful_bad 07777777777 /*more than a billion demerits*/

@<Selected global variables@>=
static int @!minimal_demerits0[tight_fit-very_loose_fit+1],
  *const @!minimal_demerits = @!minimal_demerits0-very_loose_fit; /*best total
  demerits known for current line class and position, given the fitness*/
static int @!minimum_demerits; /*best total demerits known for current line class
  and position*/
static pointer @!best_place0[tight_fit-very_loose_fit+1],
  *const @!best_place = @!best_place0-very_loose_fit; /*how to achieve
  |minimal_demerits|*/
static halfword @!best_pl_line0[tight_fit-very_loose_fit+1],
  *const @!best_pl_line = @!best_pl_line0-very_loose_fit; /*corresponding
  line number*/

@ @<Get ready to start...@>=
minimum_demerits=awful_bad;
minimal_demerits[tight_fit]=awful_bad;
minimal_demerits[decent_fit]=awful_bad;
minimal_demerits[loose_fit]=awful_bad;
minimal_demerits[very_loose_fit]=awful_bad;

@ The first part of the following code is part of \TeX's inner loop, so
we don't want to waste any time. The current active node, namely node |r|,
contains the line number that will be considered next. At the end of the
list we have arranged the data structure so that |r==last_active| and
|line_number(last_active) > old_l|.
@^inner loop@>

@<If a line number class...@>=
{@+l=line_number(r);
if (l > old_l)
  {@+ /*now we are no longer in the inner loop*/
  if ((minimum_demerits < awful_bad)&&@|
      ((old_l!=easy_line)||(r==last_active)))
    @<Create new active nodes for the best feasible breaks just found@>;
  if (r==last_active) goto end;
  @<Compute the new line width@>;
  }
}

@ It is not necessary to create new active nodes having |minimal_demerits|
greater than
|minimum_demerits+abs(adj_demerits)|, since such active nodes will never
be chosen in the final paragraph breaks. This observation allows us to
omit a substantial number of feasible breakpoints from further consideration.

@<Create new active nodes...@>=
{@+if (no_break_yet) @<Compute the values of |break_width|@>;
@<Insert a delta node to prepare for breaks at |cur_p|@>;
if (abs(adj_demerits) >= awful_bad-minimum_demerits)
  minimum_demerits=awful_bad-1;
else minimum_demerits=minimum_demerits+abs(adj_demerits);
for (fit_class=very_loose_fit; fit_class<=tight_fit; fit_class++)
  {@+if (minimal_demerits[fit_class] <= minimum_demerits)
    @<Insert a new active node from |best_place[fit_class]| to |cur_p|@>;
  minimal_demerits[fit_class]=awful_bad;
  }
minimum_demerits=awful_bad;
@<Insert a delta node to prepare for the next active node@>;
}

@ When we insert a new active node for a break at |cur_p|, suppose this
new node is to be placed just before active node |a|; then we essentially
want to insert `$\delta\,|cur_p|\,\delta^\prime$' before |a|, where
$\delta=\alpha(a)-\alpha(|cur_p|)$ and $\delta^\prime=\alpha(|cur_p|)-\alpha(a)$
in the notation explained above.  The |cur_active_width| array now holds
$\gamma+\beta(|cur_p|)-\alpha(a)$; so $\delta$ can be obtained by
subtracting |cur_active_width| from the quantity $\gamma+\beta(|cur_p|)-
\alpha(|cur_p|)$. The latter quantity can be regarded as the length of a
line ``from |cur_p| to |cur_p|''; we call it the |break_width| at |cur_p|.

The |break_width| is usually negative, since it consists of the background
(which is normally zero) minus the width of nodes following~|cur_p| that are
eliminated after a break. If, for example, node |cur_p| is a glue node, the
width of this glue is subtracted from the background; and we also look
ahead to eliminate all subsequent glue and penalty and kern and math
nodes, subtracting their widths as well.

Kern nodes do not disappear at a line break unless they are |explicit|.

@d set_break_width_to_background(A) break_width[A]=background[A]

@<Compute the values of |break...@>=
{@+no_break_yet=false;do_all_six(set_break_width_to_background);
s=cur_p;
if (break_type > unhyphenated) if (cur_p!=null)
  @<Compute the discretionary |break_width| values@>;
while (s!=null)
  {@+if (is_char_node(s)) goto done;
  switch (type(s)) {
  case glue_node: @<Subtract glue from |break_width|@>@;@+break;
  case penalty_node: do_nothing;@+break;
  case math_node: break_width[1]=break_width[1]-width(s);@+break;
  case kern_node: if (subtype(s)!=explicit) goto done;
    else break_width[1]=break_width[1]-width(s);@+break;
  default:goto done;
  } @/
  s=link(s);
  }
done: ;}

@ @<Subtract glue from |break...@>=
{@+v=glue_ptr(s);break_width[1]=break_width[1]-width(v);
break_width[2+stretch_order(v)]=break_width[2+stretch_order(v)]-stretch(v);
break_width[6]=break_width[6]-shrink(v);
}

@ When |cur_p| is a discretionary break, the length of a line ``from |cur_p| to
|cur_p|'' has to be defined properly so that the other calculations work out.
Suppose that the pre-break text at |cur_p| has length $l_0$, the post-break
text has length $l_1$, and the replacement text has length |l|. Suppose
also that |q| is the node following the replacement text. Then length of a
line from |cur_p| to |q| will be computed as $\gamma+\beta(q)-\alpha(|cur_p|)$,
where $\beta(q)=\beta(|cur_p|)-l_0+l$. The actual length will be the background
plus $l_1$, so the length from |cur_p| to |cur_p| should be $\gamma+l_0+l_1-l$.
If the post-break text of the discretionary is empty, a break may also
discard~|q|; in that unusual case we subtract the length of~|q| and any
other nodes that will be discarded after the discretionary break.

The value of $l_0$ need not be computed, since |line_break| will put
it into the global variable |disc_width| before calling |try_break|.

@<Selected global variables@>=
static scaled @!disc_width; /*the length of discretionary material preceding a break*/

@ @<Compute the discretionary |break...@>=
{@+t=replace_count(cur_p);v=cur_p;s=post_break(cur_p);
while (t > 0)
  {@+decr(t);v=link(v);
  @<Subtract the width of node |v| from |break_width|@>;
  }
while (s!=null)
  {@+@<Add the width of node |s| to |break_width|@>;
  s=link(s);
  }
break_width[1]=break_width[1]+disc_width;
if (post_break(cur_p)==null) s=link(v);
           /*nodes may be discardable after the break*/
}

@ Replacement texts and discretionary texts are supposed to contain
only character nodes, kern nodes, ligature nodes, and box or rule nodes.

@<Subtract the width of node |v|...@>=
if (is_char_node(v))
  {@+f=font(v);
  break_width[1]=break_width[1]-char_width(f, character(v));
  }
else switch (type(v)) {
  case ligature_node: {@+f=font(lig_char(v));@/
    break_width[1]=@|break_width[1]-
      char_width(f, character(lig_char(v)));
    } @+break;
  case hlist_node: case vlist_node: case rule_node:
  case kern_node:
    break_width[1]=break_width[1]-width(v);@+break;
  default:confusion("disc1");
@:this can't happen disc1}{\quad disc1@>
  }

@ @<Add the width of node |s| to |b...@>=
if (is_char_node(s))
  {@+f=font(s);
  break_width[1]=@|break_width[1]+char_width(f, character(s));
  }
else switch (type(s)) {
  case ligature_node: {@+f=font(lig_char(s));
    break_width[1]=break_width[1]+
      char_width(f, character(lig_char(s)));
    } @+break;
  case hlist_node: case vlist_node: case rule_node:
  case kern_node:
    break_width[1]=break_width[1]+width(s);@+break;
  default:confusion("disc2");
@:this can't happen disc2}{\quad disc2@>
  }

@ We use the fact that |type(active)!=delta_node|.

@d convert_to_break_width(A) @|
  mem[prev_r+A].sc=@|@t\hskip10pt@>mem[prev_r+A].sc
  -cur_active_width[A]+break_width[A]
@d store_break_width(A) active_width[A]=break_width[A]
@d new_delta_to_break_width(A) @|
  mem[q+A].sc=break_width[A]-cur_active_width[A]

@<Insert a delta node to prepare for breaks at |cur_p|@>=
if (type(prev_r)==delta_node)  /*modify an existing delta node*/
  {@+do_all_six(convert_to_break_width);
  }
else if (prev_r==active)  /*no delta node needed at the beginning*/
  {@+do_all_six(store_break_width);
  }
else{@+q=get_node(delta_node_size);link(q)=r;type(q)=delta_node;@/
  subtype(q)=0; /*the |subtype| is not used*/
  do_all_six(new_delta_to_break_width);
  link(prev_r)=q;prev_prev_r=prev_r;prev_r=q;
  }

@ When the following code is performed, we will have just inserted at
least one active node before |r|, so |type(prev_r)!=delta_node|.

@d new_delta_from_break_width(A) @|mem[q+A].sc=
    cur_active_width[A]-break_width[A]

@<Insert a delta node to prepare for the next active node@>=
if (r!=last_active)
  {@+q=get_node(delta_node_size);link(q)=r;type(q)=delta_node;@/
  subtype(q)=0; /*the |subtype| is not used*/
  do_all_six(new_delta_from_break_width);
  link(prev_r)=q;prev_prev_r=prev_r;prev_r=q;
  }

@ When we create an active node, we also create the corresponding
passive node.

@<Insert a new active node from |best_place[fit_class]| to |cur_p|@>=
{@+q=get_node(passive_node_size);
link(q)=passive;passive=q;cur_break(q)=cur_p;
#ifdef @!STAT
incr(pass_number);serial(q)=pass_number;
#endif
@;@/
prev_break(q)=best_place[fit_class];@/
q=get_node(active_node_size);break_node(q)=passive;
line_number(q)=best_pl_line[fit_class]+1;
fitness(q)=fit_class;type(q)=break_type;
total_demerits(q)=minimal_demerits[fit_class];
link(q)=r;link(prev_r)=q;prev_r=q;
#ifdef @!STAT
if (tracing_paragraphs > 0)
  @<Print a symbolic description of the new break node@>;
#endif
@;@/
}

@ @<Print a symbolic description of the new break node@>=
{@+print_nl("@@@@");print_int(serial(passive));
@.\AT\AT@>
print(": line ");print_int(line_number(q)-1);
print_char('.');print_int(fit_class);
if (break_type==hyphenated) print_char('-');
print(" t=");print_int(total_demerits(q));
print(" -> @@@@");
if (prev_break(passive)==null) print_char('0');
else print_int(serial(prev_break(passive)));
}

@ The length of lines depends on whether the user has specified
\.{\\parshape} or \.{\\hangindent}. If |par_shape_ptr| is not null, it
points to a $(2n+1)$-word record in |mem|, where the |info| in the first
word contains the value of |n|, and the other $2n$ words contain the left
margins and line lengths for the first |n| lines of the paragraph; the
specifications for line |n| apply to all subsequent lines. If
|par_shape_ptr==null|, the shape of the paragraph depends on the value of
|n==hang_after|; if |n >= 0|, hanging indentation takes place on lines |n+1|,
|n+2|, \dots, otherwise it takes place on lines 1, \dots, $\vert
n\vert$. When hanging indentation is active, the left margin is
|hang_indent|, if |hang_indent >= 0|, else it is 0; the line length is
$|hsize|-\vert|hang_indent|\vert$. The normal setting is
|par_shape_ptr==null|, |hang_after==1|, and |hang_indent==0|.
Note that if |hang_indent==0|, the value of |hang_after| is irrelevant.
@^length of lines@> @^hanging indentation@>

@<Selected global variables@>=
static halfword @!easy_line; /*line numbers | > easy_line| are equivalent in break nodes*/
static halfword @!last_special_line; /*line numbers | > last_special_line| all have
  the same width*/
static scaled @!first_width; /*the width of all lines | <= last_special_line|, if
  no \.{\\parshape} has been specified*/
static scaled @!second_width; /*the width of all lines | > last_special_line|*/
static scaled @!first_indent; /*left margin to go with |first_width|*/
static scaled @!second_indent; /*left margin to go with |second_width|*/

@ We compute the values of |easy_line| and the other local variables relating
to line length when the |line_break| procedure is initializing itself.

@<Get ready to start...@>=
if (par_shape_ptr==null)
  if (hang_indent==0)
    {@+last_special_line=0;second_width=x;
    second_indent=0;
    }
  else@<Set line length parameters in preparation for hanging indentation@>@;
else QUIT("parshape not yet implemented");
if (looseness==0) easy_line=last_special_line;
else easy_line=max_halfword

@ @<Set line length parameters in preparation for hanging indentation@>=
{@+last_special_line=abs(hang_after);
if (hang_after < 0)
  {@+first_width=x-abs(hang_indent);
  if (hang_indent >= 0) first_indent=hang_indent;
  else first_indent=0;
  second_width=x;second_indent=0;
  }
else{@+first_width=x;first_indent=0;
  second_width=x-abs(hang_indent);
  if (hang_indent >= 0) second_indent=hang_indent;
  else second_indent=0;
  }
}

@ When we come to the following code, we have just encountered the first
active node~|r| whose |line_number| field contains |l|. Thus we want to
compute the length of the $l\mskip1mu$th line of the current paragraph. Furthermore,
we want to set |old_l| to the last number in the class of line numbers
equivalent to~|l|.

@<Compute the new line width@>=
if (l > easy_line)
  {@+line_width=second_width;old_l=max_halfword-1;
  }
else{@+old_l=l;
  if (l > last_special_line) line_width=second_width;
  else if (par_shape_ptr==null) line_width=first_width;
  else line_width=mem[par_shape_ptr+2*l@,].sc;
  }

@ The remaining part of |try_break| deals with the calculation of
demerits for a break from |r| to |cur_p|.

The first thing to do is calculate the badness, |b|. This value will always
be between zero and |inf_bad+1|; the latter value occurs only in the
case of lines from |r| to |cur_p| that cannot shrink enough to fit the necessary
width. In such cases, node |r| will be deactivated.
We also deactivate node~|r| when a break at~|cur_p| is forced, since future
breaks must go through a forced break.

@<Consider the demerits for a line from |r| to |cur_p|...@>=
{@+artificial_demerits=false;@/
@^inner loop@>
shortfall=line_width-cur_active_width[1]; /*we're this much too short*/
if (shortfall > 0)
  @<Set the value of |b| to the badness for stretching the line, and compute
the corresponding |fit_class|@>@;
else@<Set the value of |b| to the badness for shrinking the line, and compute
the corresponding |fit_class|@>;
if ((b > inf_bad)||(pi==eject_penalty))
  @<Prepare to deactivate node~|r|, and |goto deactivate| unless there is
a reason to consider lines of text from |r| to |cur_p|@>@;
else{@+prev_r=r;
  if (b > threshold) goto resume;
  node_r_stays_active=true;
  }
@<Record a new feasible break@>;
if (node_r_stays_active) goto resume; /*|prev_r| has been set to |r|*/
deactivate: @<Deactivate node |r|@>;
}

@ When a line must stretch, the available stretchability can be found in the
subarray |cur_active_width[2 dotdot 5]|, in units of points, fil, fill, and filll.

The present section is part of \TeX's inner loop, and it is most often performed
when the badness is infinite; therefore it is worth while to make a quick
test for large width excess and small stretchability, before calling the
|badness| subroutine.
@^inner loop@>

@<Set the value of |b| to the badness for stretching...@>=
if ((cur_active_width[3]!=0)||(cur_active_width[4]!=0)||@|
  (cur_active_width[5]!=0))
  {@+b=0;fit_class=decent_fit; /*infinite stretch*/
  }
else{@+if (shortfall > 7230584) if (cur_active_width[2] < 1663497)
    {@+b=inf_bad;fit_class=very_loose_fit;goto done1;
    }
  b=badness(shortfall, cur_active_width[2]);
  if (b > 12)
    if (b > 99) fit_class=very_loose_fit;
    else fit_class=loose_fit;
  else fit_class=decent_fit;
  done1: ;
  }

@ Shrinkability is never infinite in a paragraph;
we can shrink the line from |r| to |cur_p| by at most |cur_active_width[6]|.

@<Set the value of |b| to the badness for shrinking...@>=
{@+if (-shortfall > cur_active_width[6]) b=inf_bad+1;
else b=badness(-shortfall, cur_active_width[6]);
if (b > 12) fit_class=tight_fit;@+else fit_class=decent_fit;
}

@ During the final pass, we dare not lose all active nodes, lest we lose
touch with the line breaks already found. The code shown here makes sure
that such a catastrophe does not happen, by permitting overfull boxes as
a last resort. This particular part of \TeX\ was a source of several subtle
bugs before the correct program logic was finally discovered; readers
who seek to ``improve'' \TeX\ should therefore think thrice before daring
to make any changes here.
@^overfull boxes@>

@<Prepare to deactivate node~|r|, and |goto deactivate| unless...@>=
{@+if (final_pass&&(minimum_demerits==awful_bad)&&@|
   (link(r)==last_active)&&
   (prev_r==active))
  artificial_demerits=true; /*set demerits zero, this break is forced*/
else if (b > threshold) goto deactivate;
node_r_stays_active=false;
}

@ When we get to this part of the code, the line from |r| to |cur_p| is
feasible, its badness is~|b|, and its fitness classification is |fit_class|.
We don't want to make an active node for this break yet, but we will
compute the total demerits and record them in the |minimal_demerits| array,
if such a break is the current champion among all ways to get to |cur_p|
in a given line-number class and fitness class.

@<Record a new feasible break@>=
if (artificial_demerits) d=0;
else@<Compute the demerits, |d|, from |r| to |cur_p|@>;
#ifdef @!STAT
if (tracing_paragraphs > 0)
  @<Print a symbolic description of this feasible break@>;
#endif
@;@/
d=d+total_demerits(r); /*this is the minimum total demerits
  from the beginning to |cur_p| via |r|*/
if (d <= minimal_demerits[fit_class])
  {@+minimal_demerits[fit_class]=d;
  best_place[fit_class]=break_node(r);best_pl_line[fit_class]=l;
  if (d < minimum_demerits) minimum_demerits=d;
  }

@ @<Print a symbolic description of this feasible break@>=
{@+if (printed_node!=cur_p)
  @<Print the list between |printed_node| and |cur_p|, then set |printed_node:=cur_p|@>;
print_nl("@@");
@.\AT@>
if (cur_p==null) print_esc("par");
else if (type(cur_p)!=glue_node)
  {@+if (type(cur_p)==penalty_node) print_esc("penalty");
  else if (type(cur_p)==disc_node) print_esc("discretionary");
  else if (type(cur_p)==kern_node) print_esc("kern");
  else print_esc("math");
  }
print(" via @@@@");
if (break_node(r)==null) print_char('0');
else print_int(serial(break_node(r)));
print(" b=");
if (b > inf_bad) print_char('*');@+else print_int(b);
@.*\relax@>
print(" p=");print_int(pi);print(" d=");
if (artificial_demerits) print_char('*');@+else print_int(d);
}

@ @<Print the list between |printed_node| and |cur_p|...@>=
{@+print_nl("");
if (cur_p==null) short_display(link(printed_node));
else{@+save_link=link(cur_p);
  link(cur_p)=null;print_nl("");short_display(link(printed_node));
  link(cur_p)=save_link;
  }
printed_node=cur_p;
}

@ When the data for a discretionary break is being displayed, we will have
printed the |pre_break| and |post_break| lists; we want to skip over the
third list, so that the discretionary data will not appear twice.  The
following code is performed at the very end of |try_break|.

@<Update the value of |printed_node|...@>=
if (cur_p==printed_node) if (cur_p!=null) if (type(cur_p)==disc_node)
  {@+t=replace_count(cur_p);
  while (t > 0)
    {@+decr(t);printed_node=link(printed_node);
    }
  }

@ @<Compute the demerits, |d|, from |r| to |cur_p|@>=
{@+d=line_penalty+b;
if (abs(d) >= 10000) d=100000000;@+else d=d*d;
if (pi!=0)
{ if (pi > 0) d=d+pi*pi;
  else if (pi > eject_penalty) d=d-pi*pi; }
if ((break_type==hyphenated)&&(type(r)==hyphenated))
{ if (cur_p!=null) d=d+double_hyphen_demerits;
  else d=d+final_hyphen_demerits; }
if (abs(fit_class-fitness(r)) > 1) d=d+adj_demerits;
}

@ When an active node disappears, we must delete an adjacent delta node if the
active node was at the beginning or the end of the active list, or if it
was surrounded by delta nodes. We also must preserve the property that
|cur_active_width| represents the length of material from |link(prev_r)|
to~|cur_p|.

@d combine_two_deltas(A) @|mem[prev_r+A].sc=mem[prev_r+A].sc+mem[r+A].sc
@d downdate_width(A) @|cur_active_width[A]=cur_active_width[A]-
  mem[prev_r+A].sc

@<Deactivate node |r|@>=
link(prev_r)=link(r);free_node(r, active_node_size);
if (prev_r==active) @<Update the active widths, since the first active node
has been deleted@>@;
else if (type(prev_r)==delta_node)
  {@+r=link(prev_r);
  if (r==last_active)
    {@+do_all_six(downdate_width);
    link(prev_prev_r)=last_active;
    free_node(prev_r, delta_node_size);prev_r=prev_prev_r;
    }
  else if (type(r)==delta_node)
    {@+do_all_six(update_width);
    do_all_six(combine_two_deltas);
    link(prev_r)=link(r);free_node(r, delta_node_size);
    }
  }

@ The following code uses the fact that |type(last_active)!=delta_node|. If the
active list has just become empty, we do not need to update the
|active_width| array, since it will be initialized when an active
node is next inserted.

@d update_active(A) active_width[A]=active_width[A]+mem[r+A].sc

@<Update the active widths,...@>=
{@+r=link(active);
if (type(r)==delta_node)
  {@+do_all_six(update_active);
  do_all_six(copy_to_cur_active);
  link(active)=link(r);free_node(r, delta_node_size);
  }
}

@* Breaking paragraphs into lines, continued.
So far we have gotten a little way into the |line_break| routine, having
covered its important |try_break| subroutine. Now let's consider the
rest of the process.

The main loop of |line_break| traverses the given hlist,
starting at |link(temp_head)|, and calls |try_break| at each legal
breakpoint. A variable called |auto_breaking| is set to true except
within math formulas, since glue nodes are not legal breakpoints when
they appear in formulas.

The current node of interest in the hlist is pointed to by |cur_p|. Another
variable, |prev_p|, is usually one step behind |cur_p|, but the real
meaning of |prev_p| is this: If |type(cur_p)==glue_node| then |cur_p| is a legal
breakpoint if and only if |auto_breaking| is true and |prev_p| does not
point to a glue node, penalty node, explicit kern node, or math node.

The following declarations provide for a few other local variables that are
used in special calculations.

@<Local variables for line breaking@>=
bool @!auto_breaking; /*is node |cur_p| outside a formula?*/
pointer @!prev_p; /*helps to determine when glue nodes are breakpoints*/
pointer @!q, @!r, @!s; /*miscellaneous nodes of temporary interest*/
internal_font_number @!f; /*used when calculating character widths*/

@ The `\ignorespaces|loop|\unskip' in the following code is performed at most
thrice per call of |line_break|, since it is actually a pass over the
entire paragraph.

@<Find optimal breakpoints@>=
threshold=pretolerance;
if (threshold >= 0)
  {
#ifdef @!STAT
if (tracing_paragraphs > 0)
    {@+print_nl("@@firstpass");@+} @;
#endif
@;@/
  second_pass=false;final_pass=false;
  }
else{@+threshold=tolerance;second_pass=true;
  final_pass=(emergency_stretch <= 0);
#ifdef @!STAT
#endif
@;
  }
loop@+{@+if (threshold > inf_bad) threshold=inf_bad;
  @<Create an active breakpoint representing the beginning of the paragraph@>;
  cur_p=link(temp_head);auto_breaking=true;@/
  prev_p=cur_p; /*glue at beginning is not a legal breakpoint*/
  while ((cur_p!=null)&&(link(active)!=last_active))
    @<Call |try_break| if |cur_p| is a legal breakpoint; on the second pass,
also try to hyphenate the next word, if |cur_p| is a glue node; then advance
|cur_p| to the next node of the paragraph that could possibly be a legal breakpoint@>;
  if (cur_p==null)
    @<Try the final line break at the end of the paragraph, and |goto done|
if the desired breakpoints have been found@>;
  @<Clean up the memory by removing the break nodes@>;
  if (!second_pass)
    {
#ifdef @!STAT
if (tracing_paragraphs > 0) print_nl("@@secondpass");@;
#endif
    threshold=tolerance;second_pass=true;final_pass=(emergency_stretch <= 0);
    }  /*if at first you don't succeed, \dots*/
  else{
#ifdef @!STAT
if (tracing_paragraphs > 0)
      print_nl("@@emergencypass");@;
#endif
    background[2]=background[2]+emergency_stretch;final_pass=true;
    }
  }
done:
#ifdef @!STAT
#endif

@ The active node that represents the starting point does not need a
corresponding passive node.

@d store_background(A) active_width[A]=background[A]

@<Create an active breakpoint representing the beginning of the paragraph@>=
q=get_node(active_node_size);
type(q)=unhyphenated;fitness(q)=decent_fit;
link(q)=last_active;break_node(q)=null;
line_number(q)=prev_graf+1;total_demerits(q)=0;link(active)=q;
do_all_six(store_background);@/
passive=null;printed_node=temp_head;pass_number=0;

@ @<Clean...@>=
q=link(active);
while (q!=last_active)
  {@+cur_p=link(q);
  if (type(q)==delta_node) free_node(q, delta_node_size);
  else free_node(q, active_node_size);
  q=cur_p;
  }
q=passive;
while (q!=null)
  {@+cur_p=link(q);
  free_node(q, passive_node_size);
  q=cur_p;
  }

@ Here is the main switch in the |line_break| routine, where legal breaks
are determined. As we move through the hlist, we need to keep the |active_width|
array up to date, so that the badness of individual lines is readily calculated
by |try_break|. It is convenient to use the short name |act_width| for
the component of active width that represents real width as opposed to glue.

@d act_width active_width[1] /*length from first active node to current node*/
@d kern_break {@+if (!is_char_node(link(cur_p))&&auto_breaking)
    if (type(link(cur_p))==glue_node) try_break(0, unhyphenated);
  act_width=act_width+width(cur_p);
  }

@<Call |try_break| if |cur_p| is a legal breakpoint...@>=
{@+if (is_char_node(cur_p))
  @<Advance \(c)|cur_p| to the node following the present string of characters@>;
switch (type(cur_p)) {
case hlist_node: case vlist_node: case rule_node: act_width=act_width+width(cur_p);@+break;
case whatsit_node: @<Advance \(p)past a whatsit node in the \(l)|line_break|
loop@>@;@+break;
case glue_node: {@+@<If node |cur_p| is a legal breakpoint, call |try_break|;
then update the active widths by including the glue in |glue_ptr(cur_p)|@>;
  } @+break;
case kern_node: if (subtype(cur_p)==explicit) kern_break@;
  else act_width=act_width+width(cur_p);@+break;
case ligature_node: {@+f=font(lig_char(cur_p));
  act_width=act_width+char_width(f, character(lig_char(cur_p)));
  } @+break;
case disc_node: @<Try to break after a discretionary fragment, then |goto
done5|@>@;
case math_node: {@+auto_breaking=(subtype(cur_p)==after);kern_break;
  } @+break;
case penalty_node: try_break(penalty(cur_p), unhyphenated);@+break;
case mark_node: case ins_node: case adjust_node: do_nothing;@+break;
default:confusion("paragraph");
@:this can't happen paragraph}{\quad paragraph@>
} @/
prev_p=cur_p;cur_p=link(cur_p);
done5: ;}

@ The code that passes over the characters of words in a paragraph is
part of \TeX's inner loop, so it has been streamlined for speed. We use
the fact that `\.{\\parfillskip}' glue appears at the end of each paragraph;
it is therefore unnecessary to check if |link(cur_p)==null| when |cur_p| is a
character node.
@^inner loop@>

@<Advance \(c)|cur_p| to the node following the present string...@>=
{@+prev_p=cur_p;
@/do@+{f=font(cur_p);
act_width=act_width+char_width(f, character(cur_p));
cur_p=link(cur_p);
}@+ while (!(!is_char_node(cur_p)));
}

@ When node |cur_p| is a glue node, we look at |prev_p| to see whether or not
a breakpoint is legal at |cur_p|, as explained above.

@<If node |cur_p| is a legal breakpoint, call...@>=
if (auto_breaking)
  {@+if (is_char_node(prev_p)) try_break(0, unhyphenated);
  else if (precedes_break(prev_p)) try_break(0, unhyphenated);
  else if ((type(prev_p)==kern_node)&&(subtype(prev_p)!=explicit))
    try_break(0, unhyphenated);
  }
check_shrinkage(glue_ptr(cur_p));q=glue_ptr(cur_p);
act_width=act_width+width(q);@|
active_width[2+stretch_order(q)]=@|
  active_width[2+stretch_order(q)]+stretch(q);@/
active_width[6]=active_width[6]+shrink(q)

@ The following code knows that discretionary texts contain
only character nodes, kern nodes, box nodes, rule nodes, and ligature nodes.

@<Try to break after a discretionary fragment...@>=
{@+if (!is_auto_disc(cur_p) || second_pass || final_pass)
  {@+s=pre_break(cur_p);disc_width=0;
if (s==null) try_break(ex_hyphen_penalty, hyphenated);
else{@+@/do@+{@<Add the width of node |s| to |disc_width|@>;
    s=link(s);
  }@+ while (!(s==null));
  act_width=act_width+disc_width;
  try_break(hyphen_penalty, hyphenated);
  act_width=act_width-disc_width;
  }
}
r=replace_count(cur_p);s=link(cur_p);
while (r > 0)
  {@+@<Add the width of node |s| to |act_width|@>;
  decr(r);s=link(s);
  }
prev_p=cur_p;cur_p=s;goto done5;
}

@ @<Add the width of node |s| to |disc_width|@>=
if (is_char_node(s))
  {@+f=font(s);
  disc_width=disc_width+char_width(f, character(s));
  }
else switch (type(s)) {
  case ligature_node: {@+f=font(lig_char(s));
    disc_width=disc_width+
      char_width(f, character(lig_char(s)));
    } @+break;
  case hlist_node: case vlist_node: case rule_node:
  case kern_node:
    disc_width=disc_width+width(s);@+break;
  default:confusion("disc3");
@:this can't happen disc3}{\quad disc3@>
  }

@ @<Add the width of node |s| to |act_width|@>=
if (is_char_node(s))
  {@+f=font(s);
  act_width=act_width+char_width(f, character(s));
  }
else switch (type(s)) {
  case ligature_node: {@+f=font(lig_char(s));
    act_width=act_width+
      char_width(f, character(lig_char(s)));
    } @+break;
  case hlist_node: case vlist_node: case rule_node:
  case kern_node:
    act_width=act_width+width(s);@+break;
  default:confusion("disc4");
@:this can't happen disc4}{\quad disc4@>
  }

@ The forced line break at the paragraph's end will reduce the list of
breakpoints so that all active nodes represent breaks at |cur_p==null|.
On the first pass, we insist on finding an active node that has the
correct ``looseness.'' On the final pass, there will be at least one active
node, and we will match the desired looseness as well as we can.

The global variable |best_bet| will be set to the active node for the best
way to break the paragraph, and a few other variables are used to
help determine what is best.

@<Selected global variables@>=
static pointer @!best_bet; /*use this passive node and its predecessors*/
static int @!fewest_demerits; /*the demerits associated with |best_bet|*/
static halfword @!best_line; /*line number following the last line of the new paragraph*/
static int @!actual_looseness; /*the difference between |line_number(best_bet)|
  and the optimum |best_line|*/
static int @!line_diff; /*the difference between the current line number and
  the optimum |best_line|*/

@ @<Try the final line break at the end of the paragraph...@>=
{@+try_break(eject_penalty, hyphenated);
if (link(active)!=last_active)
  {@+@<Find an active node with fewest demerits@>;
  if (looseness==0) goto done;
  @<Find the best active node for the desired looseness@>;
  if ((actual_looseness==looseness)||final_pass) goto done;
  }
}

@ @<Find an active node...@>=
r=link(active);fewest_demerits=awful_bad;
@/do@+{if (type(r)!=delta_node) if (total_demerits(r) < fewest_demerits)
  {@+fewest_demerits=total_demerits(r);best_bet=r;
  }
r=link(r);
}@+ while (!(r==last_active));
best_line=line_number(best_bet)

@ The adjustment for a desired looseness is a slightly more complicated
version of the loop just considered. Note that if a paragraph is broken
into segments by displayed equations, each segment will be subject to the
looseness calculation, independently of the other segments.

@<Find the best active node...@>=
{@+r=link(active);actual_looseness=0;
@/do@+{if (type(r)!=delta_node)
  {@+line_diff=line_number(r)-best_line;
  if (((line_diff < actual_looseness)&&(looseness <= line_diff))||@|
  ((line_diff > actual_looseness)&&(looseness >= line_diff)))
    {@+best_bet=r;actual_looseness=line_diff;
    fewest_demerits=total_demerits(r);
    }
  else if ((line_diff==actual_looseness)&&@|
    (total_demerits(r) < fewest_demerits))
    {@+best_bet=r;fewest_demerits=total_demerits(r);
    }
  }
r=link(r);
}@+ while (!(r==last_active));
best_line=line_number(best_bet);
}

@ Once the best sequence of breakpoints has been found (hurray), we call on the
procedure |post_line_break| to finish the remainder of the work.
(By introducing this subprocedure, we are able to keep |line_break|
from getting extremely long.)

@<Break the paragraph at the chosen...@>=
post_line_break(final_widow_penalty)

@ The total number of lines that will be set by |post_line_break|
is |best_line-prev_graf-1|. The last breakpoint is specified by
|break_node(best_bet)|, and this passive node points to the other breakpoints
via the |prev_break| links. The finishing-up phase starts by linking the
relevant passive nodes in forward order, changing |prev_break| to
|next_break|. (The |next_break| fields actually reside in the same memory
space as the |prev_break| fields did, but we give them a new name because
of their new significance.) Then the lines are justified, one by one.

@d next_break prev_break /*new name for |prev_break| after links are reversed*/

@<Declare subprocedures for |line_break|@>=
static void post_line_break(int @!final_widow_penalty)
{@+
pointer q, @!r, @!s; /*temporary registers for list manipulation*/
bool @!disc_break; /*was the current break at a discretionary node?*/
bool @!post_disc_break; /*and did it have a nonempty post-break part?*/
bool @!first_line=true; /*Is this the first line of the paragraph?*/
uint32_t line_offset, next_offset; /*The first and next offset of the line. */
scaled @!cur_width; /*width of line number |cur_line|*/
scaled @!cur_indent; /*left margin of line number |cur_line|*/
quarterword @!t; /*used for replacement counts in discretionary nodes*/
int @!pen; /*use when calculating penalties between lines*/
halfword @!cur_line; /*the current line number being justified*/
@<Reverse the links of the relevant passive nodes, setting |cur_p| to the
first breakpoint@>;
cur_line=prev_graf+1;
next_offset=hposition(link(temp_head));
if (next_offset>node_pos)
  next_offset=next_offset-node_pos;
else
  next_offset=0;
@/do@+{
line_offset=next_offset;
{ pointer q=cur_break(cur_p);
  if (q==null)
    next_offset=(hpos-hstart); /*necessary if the paragraph has a display at |hpos|*/
  else
    next_offset= hposition(q);
  if (next_offset>node_pos)
    next_offset=next_offset-node_pos;
  else
    next_offset=0;
}
@<Justify the line ending at breakpoint |cur_p|, and append it to the current
vertical list, together with associated penalties and other insertions@>;
incr(cur_line);cur_p=next_break(cur_p);
if (cur_p!=null) if (!post_disc_break)
  @<Prune unwanted nodes at the beginning of the next line@>;
if (cur_p!=null)
{  if (just_label>=0)
  { q = get_node(link_node_size);
    type(q)=whatsit_node; subtype(q)=start_link_node;
    label_ref(as_label(q))=just_label;
    if (just_color>=0) color_ref(as_color(q))=just_color;
    else  color_ref(as_color(q))=0xFF; /* this should not happen*/
    link(q)=link(temp_head);
    link(temp_head)=q;
  }
  else if (just_color>=0)
  { q = get_node(color_node_size);
    type(q)=whatsit_node; subtype(q)=color_node;
    color_ref(q)=just_color;
    link(q)=link(temp_head);
    link(temp_head)=q;
  }

}
}@+ while (!(cur_p==null));
if ((cur_line!=best_line)||(link(temp_head)!=null))
  confusion("line breaking");
@:this can't happen line breaking}{\quad line breaking@>
prev_graf=best_line-1;
}

@ The job of reversing links in a list is conveniently regarded as the job
of taking items off one stack and putting them on another. In this case we
take them off a stack pointed to by |q| and having |prev_break| fields;
we put them on a stack pointed to by |cur_p| and having |next_break| fields.
Node |r| is the passive node being moved from stack to stack.

@<Reverse the links of the relevant passive nodes...@>=
q=break_node(best_bet);cur_p=null;
@/do@+{r=q;q=prev_break(q);next_break(r)=cur_p;cur_p=r;
}@+ while (!(q==null))

@ Glue and penalty and kern and math nodes are deleted at the beginning of
a line, except in the anomalous case that the node to be deleted is actually
one of the chosen breakpoints. Otherwise
the pruning done here is designed to match
the lookahead computation in |try_break|, where the |break_width| values
are computed for non-discretionary breakpoints.

@<Prune unwanted nodes at the beginning of the next line@>=
{@+r=temp_head;
loop@+{@+q=link(r);
  if (q==cur_break(cur_p)) goto done1;
     /*|cur_break(cur_p)| is the next breakpoint*/
   /*now |q| cannot be |null|*/
  if (is_char_node(q)) goto done1;
  if (non_discardable(q)) goto done1;
  if (type(q)==kern_node) if (subtype(q)!=explicit) goto done1;
  r=q; /*now |type(q)==glue_node|, |kern_node|, |math_node|, or |penalty_node|*/
  }
done1: if (r!=temp_head)
  {@+link(r)=null;flush_node_list(link(temp_head));
  link(temp_head)=q;
  }
}

@ The current line to be justified appears in a horizontal list starting
at |link(temp_head)| and ending at |cur_break(cur_p)|. If |cur_break(cur_p)| is
a glue node, we reset the glue to equal the |right_skip| glue; otherwise
we append the |right_skip| glue at the right. If |cur_break(cur_p)| is a
discretionary node, we modify the list so that the discretionary break
is compulsory, and we set |disc_break| to |true|. We also append
the |left_skip| glue at the left of the line, unless it is zero.

@<Justify the line ending at breakpoint |cur_p|, and append it...@>=
@<Modify the end of the line to reflect the nature of the break and to include
\.{\\rightskip}; also set the proper value of |disc_break|@>;
@<Put the \(l)\.{\\leftskip} glue at the left and detach this line@>;
@<Call the packaging subroutine, setting |just_box| to the justified box@>;
@<Append the new box to the current vertical list, followed by the list of
special nodes taken out of the box by the packager@>;
@<Append a penalty node, if a nonzero penalty is appropriate@>@;

@ At the end of the following code, |q| will point to the final node on the
list about to be justified.

@<Modify the end of the line...@>=
q=cur_break(cur_p);disc_break=false;post_disc_break=false;
if (q!=null)  /*|q| cannot be a |char_node|*/
  if (type(q)==glue_node)
    {@+delete_glue_ref(glue_ptr(q));
    glue_ptr(q)=right_skip;
    subtype(q)=right_skip_code+1;add_glue_ref(right_skip);
    goto done;
    }
  else{@+if (type(q)==disc_node)
      @<Change discretionary to compulsory and set |disc_break:=true|@>@;
    else if ((type(q)==math_node)||(type(q)==kern_node)) width(q)=0;
    }
else{@+q=temp_head;
  while (link(q)!=null) q=link(q);
  }
@<Put the \(r)\.{\\rightskip} glue after node |q|@>;
done:

@ @<Change discretionary to compulsory...@>=
{@+pointer pre_q = pre_break(q);
pointer post_q = post_break(q);
t=replace_count(q);
type(q)=whatsit_node;
subtype(q)=ignore_node;
ignore_info(q)=1;
@<Keep the |t| nodes following |q|, and make |r| point to the following node@>;
s=get_node(ignore_node_size);
type(s)=whatsit_node;
subtype(s)=ignore_node;
ignore_info(s)=0;
ignore_list(s)=null;
link(s)=r; r=s;
if (post_q!=null) @<Transplant the post-break list@>;
if (pre_q!=null) @<Transplant the pre-break list@>;
link(q)=r;disc_break=true;
}

@ @<Keep the |t| nodes following |q|...@>=
if (t==0) {ignore_list(q)=null; r=link(q);}
else{@+r=q;
  while (t > 1)
    {@+r=link(r);decr(t);
    }
  s=link(r);
  r=link(s);link(s)=null;
  ignore_list(q)=link(q);
  }

@ We move the post-break list from inside node |q| to the main list by
re\-attaching it just before the present node |r|, then resetting |r|.

@<Transplant the post-break list@>=
{@+s=post_q;
while (link(s)!=null) s=link(s);
link(s)=r;r=post_q;post_disc_break=true;
}

@ We move the pre-break list from inside node |q| to the main list by
re\-attaching it just after the present node |q|, then resetting |q|.

@<Transplant the pre-break list@>=
{@+s=pre_q;link(q)=s;
while (link(s)!=null) s=link(s);
q=s;
}

@ @<Put the \(r)\.{\\rightskip} glue after node |q|@>=
r=new_glue(right_skip);link(r)=link(q);link(q)=r;q=r

@ The following code begins with |q| at the end of the list to be
justified. It ends with |q| at the beginning of that list, and with
|link(temp_head)| pointing to the remainder of the paragraph, if any.

@<Put the \(l)\.{\\leftskip} glue at the left...@>=
r=link(q);link(q)=null;q=link(temp_head);link(temp_head)=r;
if (left_skip!=zero_glue)
  {@+r=new_glue(left_skip);
  link(r)=q;q=r;
  }

@ @<Append the new box to the current vertical list...@>=
if (first_line)
{ pointer p=happend_to_vlist(just_box);
  if (p!=null)
    store_map(p,node_pos,line_offset);
  store_map(just_box,node_pos,line_offset);
  first_line=false;
}
else
{  append_to_vlist(just_box,line_offset);
 store_map(just_box,node_pos,line_offset);
}
if (adjust_head!=adjust_tail)
  {@+link(tail)=link(adjust_head);tail=adjust_tail;
   }
adjust_tail=null

@ Now |q| points to the hlist that represents the current line of the
paragraph. We need to compute the appropriate line width, pack the
line into a box of this size, and shift the box by the appropriate
amount of indentation.

@<Call the packaging subroutine...@>=
if (cur_line > last_special_line)
  {@+cur_width=second_width;cur_indent=second_indent;
  }
else if (par_shape_ptr==null)
  {@+cur_width=first_width;cur_indent=first_indent;
  }
else{@+cur_width=mem[par_shape_ptr+2*cur_line].sc;
  cur_indent=mem[par_shape_ptr+2*cur_line-1].sc;
  }
adjust_tail=adjust_head;just_box=hpack(q, cur_width, exactly);
shift_amount(just_box)=cur_indent

@ Penalties between the lines of a paragraph come from club and widow lines,
from the |inter_line_penalty| parameter, and from lines that end at
discretionary breaks.  Breaking between lines of a two-line paragraph gets
both club-line and widow-line penalties. The local variable |pen| will
be set to the sum of all relevant penalties for the current line, except
that the final line is never penalized.

@<Append a penalty node, if a nonzero penalty is appropriate@>=
if (cur_line+1!=best_line)
  {@+pen=inter_line_penalty;
  if (cur_line==prev_graf+1) pen=pen+club_penalty;
  if (cur_line+2==best_line) pen=pen+final_widow_penalty;
  if (disc_break) pen=pen+broken_penalty;
  if (pen!=0)
    {@+r=new_penalty(pen); store_map(r, node_pos, next_offset);
    link(tail)=r;tail=r;
    }
  }


@* Breaking vertical lists into pages.
The |vsplit| procedure, which implements \TeX's \.{\\vsplit} operation,
is considerably simpler than |line_break| because it doesn't have to
worry about hyphenation, and because its mission is to discover a single
break instead of an optimum sequence of breakpoints.  But before we get
into the details of |vsplit|, we need to consider a few more basic things.

@ A subroutine called |prune_page_top| takes a pointer to a vlist and
returns a pointer to a modified vlist in which all glue, kern, and penalty nodes
have been deleted before the first box or rule node. However, the first
box or rule is actually preceded by a newly created glue node designed so that
the topmost baseline will be at distance |split_top_skip| from the top,
whenever this is possible without backspacing.

In this routine and those that follow, we make use of the fact that a
vertical list contains no character nodes, hence the |type| field exists
for each node in the list.
@^data structure assumptions@>

\noindent
@<\TeX\ functions@>=

#define ensure_vbox(N) /* no longer needed */@#

static pointer prune_page_top(pointer @!p) /*adjust top after page break*/
{@+pointer prev_p; /*lags one step behind |p|*/
pointer @!q; /*temporary variable for list manipulation*/
prev_p=temp_head;link(temp_head)=p;
while (p!=null)
  switch (type(p)) {
  case hlist_node: case vlist_node: case rule_node: @<Insert glue for |split_top_skip|
and set~|p:=null|@>@;@+break;
  case whatsit_node: case mark_node: case ins_node: {@+prev_p=p;p=link(prev_p);
    } @+break;
  case glue_node: case kern_node: case penalty_node: {@+q=p;p=link(q);link(q)=null;
    link(prev_p)=p;flush_node_list(q);
    } @+break;
  default:confusion("pruning");
@:this can't happen pruning}{\quad pruning@>
  }
return link(temp_head);
}

@ @<Insert glue for |split_top_skip|...@>=
{@+temp_ptr=new_spec(pointer_def[glue_kind][split_top_skip_no]);
q=new_glue(temp_ptr);glue_ref_count(temp_ptr)=null;link(prev_p)=q;link(q)=p;
   /*now |temp_ptr==glue_ptr(q)|*/
if (width(temp_ptr) > height(p)) width(temp_ptr)=width(temp_ptr)-height(p);
else width(temp_ptr)=0;
p=null;
}

@ The next subroutine finds the best place to break a given vertical list
so as to obtain a box of height~|h|, with maximum depth~|d|.
A pointer to the beginning of the vertical list is given,
and a pointer to the optimum breakpoint is returned. The list is effectively
followed by a forced break, i.e., a penalty node with the |eject_penalty|;
if the best break occurs at this artificial node, the value |null| is returned.

An array of six |scaled| distances is used to keep track of the height
from the beginning of the list to the current place, just as in |line_break|.
In fact, we use one of the same arrays, only changing its name to reflect
its new significance.

@d active_height active_width /*new name for the six distance variables*/
@d cur_height active_height[1] /*the natural height*/
@d set_height_zero(A) active_height[A]=0 /*initialize the height to zero*/
@#
@<\TeX\ functions@>=
static pointer vert_break(pointer @!p, scaled @!h, scaled @!d)
   /*finds optimum page break*/
{@+
pointer prev_p; /*if |p| is a glue node, |type(prev_p)| determines
  whether |p| is a legal breakpoint*/
pointer @!q, @!r; /*glue specifications*/
int @!pi; /*penalty value*/
int @!b; /*badness at a trial breakpoint*/
int @!least_cost; /*the smallest badness plus penalties found so far*/
pointer @!best_place=p; /*the most recent break that leads to |least_cost|*/
scaled @!prev_dp; /*depth of previous box in the list*/
small_number @!t; /*|type| of the node following a kern*/
prev_p=p; /*an initial glue node is not a legal breakpoint*/
least_cost=awful_bad;do_all_six(set_height_zero);prev_dp=0;
loop@+{@+@<If node |p| is a legal breakpoint, check if this break is the best
known, and |goto done| if |p| is null or if the page-so-far is already too
full to accept more stuff@>;
  prev_p=p;p=link(prev_p);
  }
done: return best_place;
}

@ A global variable |best_height_plus_depth| will be set to the natural size
of the box that corresponds to the optimum breakpoint found by |vert_break|.
(This value is used by the insertion-splitting algorithm of the page builder.)

@<Selected global variables@>=
static scaled @!best_height_plus_depth; /*height of the best box, without stretching or
  shrinking*/

@ A subtle point to be noted here is that the maximum depth~|d| might be
negative, so |cur_height| and |prev_dp| might need to be corrected even
after a glue or kern node.

@<If node |p| is a legal breakpoint, check...@>=
if (p==null) pi=eject_penalty;
else@<Use node |p| to update the current height and depth measurements; if
this node is not a legal breakpoint, |goto not_found| or |update_heights|,
otherwise set |pi| to the associated penalty at the break@>;
@<Check if node |p| is a new champion breakpoint; then \(go)|goto done| if
|p| is a forced break or if the page-so-far is already too full@>;
if ((type(p) < glue_node)||(type(p) > kern_node)) goto not_found;
update_heights: @<Update the current height and depth measurements with respect
to a glue or kern node~|p|@>;
not_found: if (prev_dp > d)
    {@+cur_height=cur_height+prev_dp-d;
    prev_dp=d;
    }

@ @<Use node |p| to update the current height and depth measurements...@>=
switch (type(p)) {
case hlist_node: case vlist_node: case rule_node: {@+@t@>@;@/
  cur_height=cur_height+prev_dp+height(p);prev_dp=depth(p);
  goto not_found;
  }
case whatsit_node: @<Process whatsit |p| in |vert_break| loop, |goto not_found|@>;
case glue_node: if (precedes_break(prev_p)) pi=0;
  else goto update_heights;@+break;
case kern_node: {@+if (link(p)==null) t=penalty_node;
  else t=type(link(p));
  if (t==glue_node) pi=0;@+else goto update_heights;
  } @+break;
case penalty_node: pi=penalty(p);@+break;
case mark_node: case ins_node: goto not_found;
default:confusion("vertbreak");
@:this can't happen vertbreak}{\quad vertbreak@>
}

@ @d deplorable 100000 /*more than |inf_bad|, but less than |awful_bad|*/

@<Check if node |p| is a new champion breakpoint; then \(go)...@>=
if (pi < inf_penalty)
  {@+@<Compute the badness, |b|, using |awful_bad| if the box is too full@>;
  if (b < awful_bad)
  { if (pi <= eject_penalty) b=pi;
    else if (b < inf_bad) b=b+pi;
      else b=deplorable;
  }
  if (b <= least_cost)
    {@+best_place=p;least_cost=b;
    best_height_plus_depth=cur_height+prev_dp;
    }
  if ((b==awful_bad)||(pi <= eject_penalty)) goto done;
  }

@ @<Compute the badness, |b|, using |awful_bad| if the box is too full@>=
if (cur_height < h)
  if ((active_height[3]!=0)||(active_height[4]!=0)||
    (active_height[5]!=0)) b=0;
  else b=badness(h-cur_height, active_height[2]);
else if (cur_height-h > active_height[6]) b=awful_bad;
else b=badness(cur_height-h, active_height[6])

@ Vertical lists that are subject to the |vert_break| procedure should not
contain infinite shrinkability, since that would permit any amount of
information to ``fit'' on one page.

@<Update the current height and depth measurements with...@>=
if (type(p)==kern_node) q=p;
else{@+q=glue_ptr(p);
  active_height[2+stretch_order(q)]=@|
    active_height[2+stretch_order(q)]+stretch(q);@/
  active_height[6]=active_height[6]+shrink(q);
  if ((shrink_order(q)!=normal)&&(shrink(q)!=0))
    {@+@t@>@;@/
    DBG(DBGTEX,"Infinite glue shrinkage found in box being split");
    r=new_spec(q);shrink_order(r)=normal;delete_glue_ref(q);
    glue_ptr(p)=r;q=r;
    }
  }
cur_height=cur_height+prev_dp+width(q);prev_dp=0


@* The page builder.
When \TeX\ appends new material to its main vlist in vertical mode, it uses
a method something like |vsplit| to decide where a page ends, except that
the calculations are done ``on line'' as new items come in.
The main complication in this process is that insertions must be put
into their boxes and removed from the vlist, in a more-or-less optimum manner.

We shall use the term ``current page'' for that part of the main vlist that
is being considered as a candidate for being broken off and sent to the
user's output routine. The current page starts at |link(page_head)|, and
it ends at |page_tail|.  We have |page_head==page_tail| if this list is empty.
@^current page@>

Utter chaos would reign if the user kept changing page specifications
while a page is being constructed, so the page builder keeps the pertinent
specifications frozen as soon as the page receives its first box or
insertion.  The global variable |page_contents| is |empty| when the
current page contains only mark nodes and content-less whatsit nodes; it
is |inserts_only| if the page contains only insertion nodes in addition to
marks and whatsits.  Glue nodes, kern nodes, and penalty nodes are
discarded until a box or rule node appears, at which time |page_contents|
changes to |box_there|.  As soon as |page_contents| becomes non-|empty|,
the current |vsize| and |max_depth| are squirreled away into |page_goal|
and |page_max_depth|; the latter values will be used until the page has
been forwarded to the user's output routine. The \.{\\topskip} adjustment
is made when |page_contents| changes to |box_there|.

Although |page_goal| starts out equal to |vsize|, it is decreased by the
scaled natural height-plus-depth of the insertions considered so far, and by
the \.{\\skip} corrections for those insertions. Therefore it represents
the size into which the non-inserted material should fit, assuming that
all insertions in the current page have been made.

The global variables |best_page_break| and |least_page_cost| correspond
respectively to the local variables |best_place| and |least_cost| in the
|vert_break| routine that we have already studied; i.e., they record the
location and value of the best place currently known for breaking the
current page. The value of |page_goal| at the time of the best break is
stored in |best_size|.

@d inserts_only 1
   /*|page_contents| when an insert node has been contributed, but no boxes*/
@d box_there 2 /*|page_contents| when a box or rule has been contributed*/

@<Selected global variables@>=
static pointer @!page_tail; /*the final node on the current page*/
static int @!page_contents; /*what is on the current page so far?*/
static scaled @!page_max_depth; /*maximum box depth on page being built*/
static pointer @!best_page_break; /*break here to get the best page known so far*/
static int @!least_page_cost; /*the score for this currently best page*/
static scaled @!best_size; /*its |page_goal|*/

@ The page builder has another data structure to keep track of insertions.
This is a list of four-word nodes, starting and ending at |page_ins_head|.
That is, the first element of the list is node |r@t$\_1$@>==link(page_ins_head)|;
node $r_j$ is followed by |r@t$\_{j+1}$@>==link(r@t$\_j$@>)|; and if there are
|n| items we have |r@t$\_{n+1}$@>==page_ins_head|. The |subtype| field of
each node in this list refers to an insertion number; for example, `\.{\\insert
250}' would correspond to a node whose |subtype| is |qi(250)|
(the same as the |subtype| field of the relevant |ins_node|). These |subtype|
fields are in increasing order, and |subtype(page_ins_head)==
qi(255)|, so |page_ins_head| serves as a convenient sentinel
at the end of the list. A record is present for each insertion number that
appears in the current page.

The |type| field in these nodes distinguishes two possibilities that
might occur as we look ahead before deciding on the optimum page break.
If |type(r)==inserting|, then |height(r)| contains the total of the
height-plus-depth dimensions of the box and all its inserts seen so far.
If |type(r)==split_up|, then no more insertions will be made into this box,
because at least one previous insertion was too big to fit on the current
page; |broken_ptr(r)| points to the node where that insertion will be
split, if \TeX\ decides to split it, |broken_ins(r)| points to the
insertion node that was tentatively split, and |height(r)| includes also the
natural height plus depth of the part that would be split off.

In both cases, |last_ins_ptr(r)| points to the last |ins_node|
encountered for box |qo(subtype(r))| that would be at least partially
inserted on the next page; and |best_ins_ptr(r)| points to the last
such |ins_node| that should actually be inserted, to get the page with
minimum badness among all page breaks considered so far. We have
|best_ins_ptr(r)==null| if and only if no insertion for this box should
be made to produce this optimum page.

The data structure definitions here use the fact that the |@!height| field
appears in the fourth word of a box node.
@^data structure assumptions@>

@d page_ins_node_size 4 /*number of words for a page insertion node*/
@d inserting 0 /*an insertion class that has not yet overflowed*/
@d split_up 1 /*an overflowed insertion class*/
@d broken_ptr(A) link(A+1)
   /*an insertion for this class will break here if anywhere*/
@d broken_ins(A) info(A+1) /*this insertion might break at |broken_ptr|*/
@d last_ins_ptr(A) link(A+2) /*the most recent insertion for this |subtype|*/
@d best_ins_ptr(A) info(A+2) /*the optimum most recent insertion*/

@<Initialize the special list heads...@>=
subtype(page_ins_head)=qi(255);
type(page_ins_head)=split_up;link(page_ins_head)=page_ins_head;

@ An array |page_so_far| records the heights and depths of everything
on the current page. This array contains six |scaled| numbers, like the
similar arrays already considered in |line_break| and |vert_break|; and it
also contains |page_goal| and |page_depth|, since these values are
all accessible to the user via |set_page_dimen| commands. The
value of |page_so_far[1]| is also called |page_total|.  The stretch
and shrink components of the \.{\\skip} corrections for each insertion are
included in |page_so_far|, but the natural space components of these
corrections are not, since they have been subtracted from |page_goal|.

The variable |page_depth| records the depth of the current page; it has been
adjusted so that it is at most |page_max_depth|. The variable
|last_glue| points to the glue specification of the most recent node
contributed from the contribution list, if this was a glue node; otherwise
|last_glue==max_halfword|. (If the contribution list is nonempty,
however, the value of |last_glue| is not necessarily accurate.)
The variables |last_penalty| and |last_kern| are similar.  And
finally, |insert_penalties| holds the sum of the penalties associated with
all split and floating insertions.

@d page_goal page_so_far[0] /*desired height of information on page being built*/
@d page_total page_so_far[1] /*height of the current page*/
@d page_shrink page_so_far[6] /*shrinkability of the current page*/
@d page_depth page_so_far[7] /*depth of the current page*/

@<Selected global variables@>=
static scaled @!page_so_far[8]; /*height and glue of the current page*/
static int @!insert_penalties; /*sum of the penalties for insertions
  that were held over*/

@ @d print_plus(A, B) if (page_so_far[A]!=0)
  {@+print(" plus ");print_scaled(page_so_far[A]);print(B);@+}

@<Basic printing procedures@>=
static void print_totals(void)
{@+print_scaled(page_total);
print_plus(2,"");
print_plus(3,"fil");
print_plus(4,"fill");
print_plus(5,"filll");
if (page_shrink!=0)
  {@+print(" minus ");print_scaled(page_shrink);
  }
}

@ Here is a procedure that is called when the |page_contents| is changing
from |empty| to |inserts_only| or |box_there|.

@d set_page_so_far_zero(A) page_so_far[A]=0

@<\TeX\ functions@>=
static void freeze_page_specs(small_number @!s)
{@+page_contents=s;
page_goal=hvsize;page_max_depth=max_depth;
page_depth=0;do_all_six(set_page_so_far_zero);
least_page_cost=awful_bad;
#ifdef @!STAT
if (tracing_pages > 0)
  {@+begin_diagnostic();
  print_nl("%% goal height=");print_scaled(page_goal);
@.goal height@>
  print(", max depth=");print_scaled(page_max_depth);
  end_diagnostic(false);
  } @;
#endif
@;@/
}

@ Pages are built by appending nodes to the current list in \TeX's
vertical mode, which is at the outermost level of the semantic nest. This
vlist is split into two parts; the ``current page'' that we have been
talking so much about already, and the ``contribution list'' that receives
new nodes as they are created.  The current page contains everything that
the page builder has accounted for in its data structures, as described
above, while the contribution list contains other things that have been
generated by other parts of \TeX\ but have not yet been
seen by the page builder.
The contribution list starts at |link(contrib_head)|, and it ends at the
current node in \TeX's vertical mode.

When \TeX\ has appended new material in vertical mode, it calls the procedure
|build_page|, which tries to catch up by moving nodes from the contribution
list to the current page. This procedure will succeed in its goal of
emptying the contribution list, unless a page break is discovered, i.e.,
unless the current page has grown to the point where the optimum next
page break has been determined. In the latter case, the nodes after the
optimum break will go back onto the contribution list, and control will
effectively pass to the user's output routine.

We make |type(page_head)==glue_node|, so that an initial glue node on
the current page will not be considered a valid breakpoint.

@<Initialize the special list...@>=
type(page_head)=glue_node;subtype(page_head)=normal;

@ \TeX\ is not always in vertical mode at the time |build_page|
is called; the current mode reflects what \TeX\ should return to, after
the contribution list has been emptied. A call on |build_page| should
be immediately followed by `|goto big_switch|', which is \TeX's central
control point.

@<\TeX\ functions@>=
static bool hbuild_page(void) /*append contributions to the current page*/
{@+
pointer p; /*the node being appended*/
pointer @!q, @!r; /*nodes being examined*/
int @!b, @!c; /*badness and cost of current page*/
int @!pi; /*penalty to be added to the badness*/
if (link(contrib_head)==null) return false;
@/do@+{resume: p=link(contrib_head);@/
@<Move node |p| to the current page; if it is time for a page break, put the
nodes following the break back onto the contribution list, and |return| to
the user's output routine if there is one@>;
}@+ while (!(link(contrib_head)==null));
@<Make the contribution list empty by setting its tail to |contrib_head|@>;
return false;
}

@ @d contrib_tail nest[0].tail_field /*tail of the contribution list*/

@<Make the contribution list empty...@>=
if (nest_ptr==0) tail=contrib_head; /*vertical mode*/
else contrib_tail=contrib_head /*other modes*/

@ The code here is an example of a many-way switch into routines that
merge together in different places. Some people call this unstructured
programming, but the author doesn't see much wrong with it, as long as
@^Knuth, Donald Ervin@>
the various labels have a well-understood meaning.

@<Move node |p| to the current page;...@>=
@<If the current page is empty and node |p| is to be deleted, |goto done1|;
otherwise use node |p| to update the state of the current page; if this node
is an insertion, |goto contribute|; otherwise if this node is not a legal
breakpoint, |goto contribute| or |update_heights|; otherwise set |pi| to the
penalty associated with this breakpoint@>;
@<Check if node |p| is a new champion breakpoint; then \(if)if it is time
for a page break, prepare for output, and either fire up the user's output
routine and |return| or ship out the page and |goto done|@>;
if ((type(p) < glue_node)||(type(p) > kern_node)) goto contribute;
update_heights: @<Update the current page measurements with respect to the
glue or kern specified by node~|p|@>;
contribute: @<Make sure that |page_max_depth| is not exceeded@>;
@<Link node |p| into the current page and |goto done|@>;
done1: @<Recycle node |p|@>;
done:

@ @<Link node |p| into the current page and |goto done|@>=
link(page_tail)=p;page_tail=p;
link(contrib_head)=link(p);link(p)=null;goto done

@ @<Recycle node |p|@>=
link(contrib_head)=link(p);link(p)=null;flush_node_list(p)

@ The title of this section is already so long, it seems best to avoid
making it more accurate but still longer, by mentioning the fact that a
kern node at the end of the contribution list will not be contributed until
we know its successor.

@<If the current page is empty...@>=
switch (type(p)) {
case hlist_node: case vlist_node: case rule_node: if (page_contents < box_there)
    @<Initialize the current page, insert the \.{\\topskip} glue ahead of
|p|, and |goto continue|@>@;
  else@<Prepare to move a box or rule node to the current page, then |goto
contribute|@>@;@+break;
case whatsit_node: @<Prepare to move whatsit |p| to the current page, then
|goto contribute|@>;
case glue_node: if (page_contents < box_there) goto done1;
  else if (precedes_break(page_tail) &&
           !(type(page_tail)==whatsit_node && subtype(page_tail)==color_node))
	 pi=0;
  else goto update_heights;@+break;
case kern_node: if (page_contents < box_there) goto done1;
  else if (link(p)==null) return false;
  else if (type(link(p))==glue_node) pi=0;
  else goto update_heights;@+break;
case penalty_node: if (page_contents < box_there) goto done1;@+else pi=penalty(p);@+break;
case mark_node: goto contribute;
case ins_node: happend_insertion(p); goto contribute;
default:confusion("page");
@:this can't happen page}{\quad page@>
}

@ @<Initialize the current page, insert the \.{\\topskip} glue...@>=
{@+if (page_contents==empty) freeze_page_specs(box_there);
else page_contents=box_there;
temp_ptr=new_spec(pointer_def[glue_kind][top_skip_no]);
q=new_glue(temp_ptr);glue_ref_count(temp_ptr)=null;
{ uint64_t h=hlocation(p); store_map(q,LOC_POS0(h),LOC_OFF(h)); }
if (width(temp_ptr) > height(p)) width(temp_ptr)=width(temp_ptr)-height(p);
else width(temp_ptr)=0;
link(q)=p;link(contrib_head)=q;goto resume;
}

@ @<Prepare to move a box or rule node to the current page...@>=
{@+page_total=page_total+page_depth+height(p);
page_depth=depth(p);
goto contribute;
}

@ @<Make sure that |page_max_depth| is not exceeded@>=
if (page_depth > page_max_depth)
  {@+page_total=@|
    page_total+page_depth-page_max_depth;@/
  page_depth=page_max_depth;
  }

@ @<Update the current page measurements with respect to the glue...@>=
if (type(p)==kern_node) q=p;
else{@+q=glue_ptr(p);
  page_so_far[2+stretch_order(q)]=@|
    page_so_far[2+stretch_order(q)]+stretch(q);@/
  page_shrink=page_shrink+shrink(q);
  if ((shrink_order(q)!=normal)&&(shrink(q)!=0))
    {@+@t@>@;@/
     DBG(DBGTEX,"Infinite glue shrinkage found on current page");
    r=new_spec(q);shrink_order(r)=normal;fast_delete_glue_ref(q);
    glue_ptr(p)=r;q=r;
    }
  }
page_total=page_total+page_depth+width(q);page_depth=0

@ @<Check if node |p| is a new champion breakpoint; then \(if)...@>=
if (pi < inf_penalty)
  {@+@<Compute the badness, |b|, of the current page, using |awful_bad| if
the box is too full@>;
  if (b < awful_bad)
    if (pi <= eject_penalty) c=pi;
    else if (b < inf_bad) c=b+pi+insert_penalties;
      else c=deplorable;
  else c=b;
  if (insert_penalties >= 10000) c=awful_bad;
#ifdef @!STAT
  if (tracing_pages > 0) @<Display the page break cost@>;
#endif
@;@/
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
{ hloc_set_next(best_page_break);
  if (p==best_page_break) best_page_break=null;
  hpack_page();
  hfill_page_template();
  return true;
}
  }

@ @<Display the page break cost@>=
{@+begin_diagnostic();print_nl("%");
print(" t=");print_totals();@/
print(" g=");print_scaled(page_goal);@/
print(" b=");
if (b==awful_bad) print_char('*');@+else print_int(b);
@.*\relax@>
print(" p=");print_int(pi);
print(" c=");
if (c==awful_bad) print_char('*');@+else print_int(c);
if (c <= least_page_cost) print_char('#');
end_diagnostic(false);
}

@ @<Compute the badness, |b|, of the current page...@>=
if (page_total < page_goal)
  if ((page_so_far[3]!=0)||(page_so_far[4]!=0)||@|
    (page_so_far[5]!=0)) b=0;
  else b=badness(page_goal-page_total, page_so_far[2]);
else if (page_total-page_goal > page_shrink) b=awful_bad;
else b=badness(page_total-page_goal, page_shrink)

@ @<\TeX\ functions@>=
static void happend_insertion(pointer p)@/
{ uint8_t @!n; /*insertion box number*/
  scaled @!delta, @!h, @!w; /*sizes used for insertion calculations*/
  pointer q,r;
  if (page_contents==empty) freeze_page_specs(inserts_only);
n=subtype(p);r=page_ins_head;
while (n >= subtype(link(r))) r=link(r);
n=qo(n);
if (subtype(r)!=qi(n))
  @<Create a page insertion node with |subtype(r)=qi(n)|, and include the
glue correction for box |n| in the current page state@>;
if (type(r)==split_up) insert_penalties=insert_penalties+float_cost(p);
else{@+last_ins_ptr(r)=p;
  delta=page_goal-page_total-page_depth+page_shrink;
     /*this much room is left if we shrink the maximum*/
  if (count(n)==1000) h=height(p);
  else h=x_over_n(height(p), 1000)*count(n); /*this much room is needed*/
  if (((h <= 0)||(h <= delta))&&(height(p)+height(r) <= dimen(n)))
    {@+page_goal=page_goal-h;height(r)=height(r)+height(p);
    }
  else@<Find the best way to split the insertion, and change |type(r)| to
|split_up|@>;
  }
}

@ We take note of the value of \.{\\skip} |n| and the height plus depth
of \.{\\box}~|n| only when the first \.{\\insert}~|n| node is
encountered for a new page. A user who changes the contents of \.{\\box}~|n|
after that first \.{\\insert}~|n| had better be either extremely careful
or extremely lucky, or both.

@<Create a page insertion node...@>=
{@+q=get_node(page_ins_node_size);link(q)=link(r);link(r)=q;r=q;
subtype(r)=qi(n);type(r)=inserting;ensure_vbox(n);
if (box(n)==null) height(r)=0;
else height(r)=height(box(n))+depth(box(n));
best_ins_ptr(r)=null;@/
q=skip(n);
if (count(n)==1000) h=height(r);
else h=x_over_n(height(r), 1000)*count(n);
page_goal=page_goal-h-width(q);@/
page_so_far[2+stretch_order(q)]=@|page_so_far[2+stretch_order(q)]+stretch(q);@/
page_shrink=page_shrink+shrink(q);
if ((shrink_order(q)!=normal)&&(shrink(q)!=0))
  DBG(DBGTEX,"Infinite glue shrinkage inserted from stream %d",n);
}

@ Here is the code that will split a long footnote between pages, in an
emergency. The current situation deserves to be recapitulated: Node |p|
is an insertion into box |n|; the insertion will not fit, in its entirety,
either because it would make the total contents of box |n| greater than
\.{\\dimen} |n|, or because it would make the incremental amount of growth
|h| greater than the available space |delta|, or both. (This amount |h| has
been weighted by the insertion scaling factor, i.e., by \.{\\count} |n|
over 1000.) Now we will choose the best way to break the vlist of the
insertion, using the same criteria as in the \.{\\vsplit} operation.

@<Find the best way to split the insertion...@>=
{@+if (count(n) <= 0) w=max_dimen;
else{@+w=page_goal-page_total-page_depth;
  if (count(n)!=1000) w=x_over_n(w, count(n))*1000;
  }
if (w > dimen(n)-height(r)) w=dimen(n)-height(r);
q=vert_break(ins_ptr(p), w, depth(p));
height(r)=height(r)+best_height_plus_depth;
#ifdef @!STAT
if (tracing_pages > 0) @<Display the insertion split cost@>;
#endif
@;@/
if (count(n)!=1000)
  best_height_plus_depth=x_over_n(best_height_plus_depth, 1000)*count(n);
page_goal=page_goal-best_height_plus_depth;
type(r)=split_up;broken_ptr(r)=q;broken_ins(r)=p;
if (q==null) insert_penalties=insert_penalties+eject_penalty;
else if (type(q)==penalty_node) insert_penalties=insert_penalties+penalty(q);
}

@ @<Display the insertion split cost@>=
{@+begin_diagnostic();print_nl("% split");print_int(n);
@.split@>
print(" to ");print_scaled(w);
print_char(',');print_scaled(best_height_plus_depth);@/
print(" p=");
if (q==null) print_int(eject_penalty);
else if (type(q)==penalty_node) print_int(penalty(q));
else print_char('0');
end_diagnostic(false);
}

@ @<\TeX\ functions@>=
static void hpack_page(void)
{
pointer p, @!q, @!r, @!s; /*nodes being examined and/or changed*/
pointer @!prev_p; /*predecessor of |p|*/
uint8_t @!n; /*insertion box number*/
bool @!wait; /*should the present insertion be held over?*/
pointer @!save_split_top_skip; /*saved value of |split_top_skip|*/
#if 0
     print_str("\npage_head:\n");
     show_box(link(page_head));
     print_str("\nstream 0:\n");
     show_box(streams[0].p);
     print_str("\nstream 1:\n");
     show_box(streams[1].p);
#endif
if (box(0)!=null)
{ flush_node_list(box(0)); box(0)=null; }
insert_penalties=0; /*this will count the number of insertions held over*/
save_split_top_skip=split_top_skip;
@<Prepare all the boxes involved in insertions to act as queues@>;
q=hold_head;link(q)=null;prev_p=page_head;p=link(prev_p);
while (p!=best_page_break)
  {@+if (type(p)==ins_node)
    {@<Either insert the material specified by node |p| into the appropriate box,
or hold it for the next page; also delete node |p| from the current page@>;
  }
  prev_p=p;p=link(prev_p);
  }
split_top_skip=save_split_top_skip;
@<Break the current page at node |p|, put it in box~255, and put the remaining nodes
on the contribution list@>;
@<Delete \(t)the page-insertion nodes@>;
}

@ When the following code is executed, the current page runs from node
|link(page_head)| to node |prev_p|, and the nodes from |p| to |page_tail|
are to be placed back at the front of the contribution list. Furthermore
the heldover insertions appear in a list from |link(hold_head)| to |q|; we
will put them into the current page list for safekeeping while the user's
output routine is active.  We might have |q==hold_head|; and |p==null| if
and only if |prev_p==page_tail|. Error messages are suppressed within
|vpackage|, since the box might appear to be overfull or underfull simply
because the stretch and shrink from the \.{\\skip} registers for inserts
are not actually present in the box.

@<Break the current page at node |p|, put it...@>=
if (p!=null)
  {@+if (link(contrib_head)==null)
    { if (nest_ptr==0) tail=page_tail;
      else contrib_tail=page_tail; }
  link(page_tail)=link(contrib_head);
  link(contrib_head)=p;
  link(prev_p)=null;
  }
streams[0].p=link(page_head); link(page_head)=null; page_tail=page_head;
streams[0].t=prev_p;
if (q!=hold_head)
  {@+link(q)=link(contrib_head);
     link(contrib_head)=link(hold_head);
  }

@ If many insertions are supposed to go into the same box, we want to know
the position of the last node in that box, so that we don't need to waste time
when linking further information into it. The |last_ins_ptr| fields of the
page insertion nodes are therefore used for this purpose during the
packaging phase.

@<Prepare all the boxes involved in insertions to act as queues@>=
{@+r=link(page_ins_head);
while (r!=page_ins_head)
  {@+if (best_ins_ptr(r)!=null)
    {@+n=qo(subtype(r));ensure_vbox(n);
    if (box(n)==null) box(n)=new_null_box();
    p=box(n)+list_offset;
    while (link(p)!=null) p=link(p);
    last_ins_ptr(r)=p;
    }
  r=link(r);
  }
}

@ @<Delete \(t)the page-insertion nodes@>=
r=link(page_ins_head);
while (r!=page_ins_head)
  {@+q=link(r);free_node(r, page_ins_node_size);r=q;
  }
link(page_ins_head)=page_ins_head

@ We will set |best_ins_ptr=null| and package the box corresponding to
insertion node~|r|, just after making the final insertion into that box.
If this final insertion is `|split_up|', the remainder after splitting
and pruning (if any) will be carried over to the next page.

@<Either insert the material specified by node |p| into...@>=
{@+r=link(page_ins_head);
while (subtype(r)!=subtype(p)) r=link(r);
if (best_ins_ptr(r)==null) wait=true;
else{@+wait=false;s=last_ins_ptr(r);link(s)=ins_ptr(p);
  if (best_ins_ptr(r)==p)
    @<Wrap up the box specified by node |r|, splitting node |p| if called
for; set |wait:=true| if node |p| holds a remainder after splitting@>@;
  else{@+while (link(s)!=null) s=link(s);
    last_ins_ptr(r)=s;
    }
  }
@<Either append the insertion node |p| after node |q|, and remove it from
the current page, or delete |node(p)|@>;
}

@ @<Wrap up the box specified by node |r|, splitting node |p| if...@>=
{@+if (type(r)==split_up)
  if ((broken_ins(r)==p)&&(broken_ptr(r)!=null))
    {@+while (link(s)!=broken_ptr(r)) s=link(s);
    link(s)=null;
    split_top_skip=split_top_ptr(p);
    ins_ptr(p)=prune_page_top(broken_ptr(r));
    if (ins_ptr(p)!=null)
      {@+temp_ptr=vpack(ins_ptr(p), natural);
      height(p)=height(temp_ptr)+depth(temp_ptr);
      free_node(temp_ptr, box_node_size);wait=true;
      }
    }
while (link(s)!=null) s=link(s);
best_ins_ptr(r)=null;
n=qo(subtype(r));
temp_ptr=list_ptr(box(n));
free_node(box(n), box_node_size);
streams[n].p=temp_ptr;
streams[n].t=s;
}

@ @<Either append the insertion node |p|...@>=
link(prev_p)=link(p);link(p)=null;
if (wait)
  {@+link(q)=p;q=p;incr(insert_penalties);
  }
else{@+delete_glue_ref(split_top_ptr(p));
  free_node(p, ins_node_size);
  }
p=prev_p

@* The chief executive.
We come now to the |main_control| routine, which contains the master
switch that causes all the various pieces of \TeX\ to do their things,
in the right order.

In a sense, this is the grand climax of the program: It applies all the
tools that we have worked so hard to construct. In another sense, this is
the messiest part of the program: It necessarily refers to other pieces
of code all over the place, so that a person can't fully understand what is
going on without paging back and forth to be reminded of conventions that
are defined elsewhere. We are now at the hub of the web, the central nervous
system that touches most of the other parts and ties them together.
@^brain@>

The structure of |main_control| itself is quite simple. There's a label
called |big_switch|, at which point the next token of input is fetched
using |get_x_token|. Then the program branches at high speed into one of
about 100 possible directions, based on the value of the current
mode and the newly fetched command code; the sum |abs(mode)+cur_cmd|
indicates what to do next. For example, the case `|vmode+letter|' arises
when a letter occurs in vertical mode (or internal vertical mode); this
case leads to instructions that initialize a new paragraph and enter
horizontal mode.

The big |case| statement that contains this multiway switch has been labeled
|reswitch|, so that the program can |goto reswitch| when the next token
has already been fetched. Most of the cases are quite short; they call
an ``action procedure'' that does the work for that case, and then they
either |goto reswitch| or they ``fall through'' to the end of the |case|
statement, which returns control back to |big_switch|. Thus, |main_control|
is not an extremely large procedure, in spite of the multiplicity of things
it must do; it is small enough to be handled by \PASCAL\ compilers that put
severe restrictions on procedure size.
@!@^action procedure@>

One case is singled out for special treatment, because it accounts for most
of \TeX's activities in typical applications. The process of reading simple
text and converting it into |char_node| records, while looking for ligatures
and kerns, is part of \TeX's ``inner loop''; the whole program runs
efficiently when its inner loop is fast, so this part has been written
with particular care.

@ The boolean variables of the main loop are normally false, and always reset
to false before the loop is left. That saves us the extra work of initializing
each time.


@* Building boxes and lists.
The most important parts of |main_control| are concerned with \TeX's
chief mission of box-making. We need to control the activities that put
entries on vlists and hlists, as well as the activities that convert
those lists into boxes. All of the necessary machinery has already been
developed; it remains for us to ``push the buttons'' at the right times.


@ Many of the actions related to box-making are triggered by the appearance
of braces in the input. For example, when the user says `\.{\\hbox}
\.{to} \.{100pt\{$\langle\,\hbox{\rm hlist}\,\rangle$\}}' in vertical mode,
the information about the box size (100pt, |exactly|) is put onto |save_stack|
with a level boundary word just above it, and |cur_group=adjusted_hbox_group|;
\TeX\ enters restricted horizontal mode to process the hlist. The right
brace eventually causes |save_stack| to be restored to its former state,
at which time the information about the box size (100pt, |exactly|) is
available once again; a box is packaged and we leave restricted horizontal
mode, appending the new box to the current list of the enclosing mode
(in this case to the current list of vertical mode), followed by any
vertical adjustments that were removed from the box by |hpack|.

The next few sections of the program are therefore concerned with the
treatment of left and right curly braces.


@* Building math lists.


@ When we enter display math mode, we need to call |line_break| to
process the partial paragraph that has just been interrupted by the
display. Then we can set the proper values of |display_width| and
|display_indent| and |pre_display_size|.

@<\TeX\ functions@>=
static void hdisplay(pointer p, pointer a, bool l)
{@+
scaled x; /* the |hsize| in the enclosing paragraph */
uint32_t offset=node_pos-node_pos1; /* offset of the display node in the current parragraph */
{scaled w; /*new or partial |pre_display_size|*/
scaled @!l; /*new |display_width|*/
scaled @!s; /*new |display_indent|*/
pointer @!p; /*current node when calculating |pre_display_size|*/
pointer @!q; /*glue specification when calculating |pre_display_size|*/
internal_font_number @!f; /*font in current |char_node|*/
int @!n; /*scope of paragraph shape specification*/
scaled @!v; /*|w| plus possible glue amount*/
scaled @!d; /*increment to |v|*/

if (head==tail)  /*`\.{\\noindent\$\$}' or `\.{\$\${ }\$\$}'*/
  {@+pop_nest();w=-max_dimen; x=cur_list.hs_field; offset=0;
  }
else{@+ pointer par_ptr;
     hprune_unwanted_nodes();
     par_ptr=link(head);
     pop_nest();
     store_map(par_ptr,node_pos,0);
     line_break(display_widow_penalty,par_ptr);@/
     x=cur_list.hs_field;
  @<Calculate the natural width, |w|, by which the characters of the final
line extend to the right of the reference point, plus two ems; or set |w:=max_dimen|
if the non-blank information on that line is affected by stretching or shrinking@>;
  }
 /*now we are in vertical mode, working on the list that will contain the display*/
@<Calculate the length, |l|, and the shift amount, |s|, of the display lines@>;
pre_display_size=w;@+display_width=l; display_indent=s;
}

@ @<Calculate the natural width, |w|, by which...@>=
v=shift_amount(just_box)+2*dimen_def[quad_no];w=-max_dimen;
p=list_ptr(just_box);
while (p!=null)
  {@+@<Let |d| be the natural width of node |p|; if the node is ``visible,''
|goto found|; if the node is glue that stretches or shrinks, set |v:=max_dimen|@>;
  if (v < max_dimen) v=v+d;
  goto not_found;
  found: if (v < max_dimen)
    {@+v=v+d;w=v;
    }
  else{@+w=max_dimen;goto done;
    }
  not_found: p=link(p);
  }
done:

@ @<Let |d| be the natural width of node |p|...@>=
reswitch: if (is_char_node(p))
  {@+f=font(p);d=char_width(f, character(p));
  goto found;
  }
switch (type(p)) {
case hlist_node: case vlist_node: case rule_node: {@+d=width(p);goto found;
  }
case ligature_node: @<Make node |p| look like a |char_node|...@>@;
case kern_node: case math_node: d=width(p);@+break;
case glue_node: @<Let |d| be the natural width of this glue; if stretching
or shrinking, set |v:=max_dimen|; |goto found| in the case of leaders@>@;@+break;
case whatsit_node: @<Let |d| be the width of the whatsit |p|@>;@+break;
default:d=0;
}

@ We need to be careful that |w|, |v|, and |d| do not depend on any |glue_set|
values, since such values are subject to system-dependent rounding.
System-dependent numbers are not allowed to infiltrate parameters like
|pre_display_size|, since \TeX82 is supposed to make the same decisions on all
machines.

@<Let |d| be the natural width of this glue...@>=
{@+q=glue_ptr(p);d=width(q);
if (glue_sign(just_box)==stretching)
  {@+if ((glue_order(just_box)==stretch_order(q))&&@|
     (stretch(q)!=0))
    v=max_dimen;
  }
else if (glue_sign(just_box)==shrinking)
  {@+if ((glue_order(just_box)==shrink_order(q))&&@|
     (shrink(q)!=0))
    v=max_dimen;
  }
if (subtype(p) >= a_leaders) goto found;
}

@ A displayed equation is considered to be three lines long, so we
calculate the length and offset of line number |prev_graf+2|.

@<Calculate the length, |l|,...@>=
if (par_shape_ptr==null)
  if ((hang_indent!=0)&&@|
   (((hang_after >= 0)&&(prev_graf+2 > hang_after))||@|
    (prev_graf+1 < -hang_after)))
    {@+l=x-abs(hang_indent);
    if (hang_indent > 0) s=hang_indent;@+else s=0;
    }
  else{@+l=x;s=0;
    }
else{@+n=info(par_shape_ptr);
  if (prev_graf+2 >= n) p=par_shape_ptr+2*n;
  else p=par_shape_ptr+2*(prev_graf+2);
  s=mem[p-1].sc;l=mem[p].sc;
  }

@ Primitive math operators like \.{\\mathop} and \.{\\underline} are given
the command code |math_comp|, supplemented by the noad type that they
generate.





@ We have saved the worst for last: The fussiest part of math mode processing
occurs when a displayed formula is being centered and placed with an optional
equation number.

@<Local variables for finishing...@>=
pointer @!b; /*box containing the equation*/
scaled @!w; /*width of the equation*/
scaled @!z; /*width of the line*/
scaled @!e; /*width of equation number*/
scaled @!q; /*width of equation number plus space to separate from equation*/
scaled @!d; /*displacement of equation in the line*/
scaled @!s; /*move the line right this much*/
small_number @!g1, @!g2; /*glue parameter codes for before and after*/
pointer @!r; /*kern node used to position the display*/
pointer @!t; /*tail of adjustment list*/

@ At this time |p| points to the mlist for the formula; |a| is either
|null| or it points to a box containing the equation number; and we are in
vertical mode (or internal vertical mode).

@<\TeX\ functions@>=
{@<Local variables for finishing a displayed formula@>@;
adjust_tail=adjust_head;b=hpack(p, natural);p=list_ptr(b);
t=adjust_tail;adjust_tail=null;@/
w=width(b);z=display_width;s=display_indent;
if (a==null)
  {@+e=0;q=0;
  }
else{@+e=width(a);q=e+math_quad;
  }
if (w+q > z)
  @<Squeeze the equation as much as possible; if there is an equation number
that should go on a separate line by itself, set~|e:=0|@>;
@<Determine the displacement, |d|, of the left edge of the equation, with
respect to the line size |z|, assuming that |l=false|@>;
@<Append the glue or equation number preceding the display@>;
@<Append the display and perhaps also the equation number@>;
@<Append the glue or equation number following the display@>;
prev_graf=prev_graf+3;
cur_list.bs_pos=hpos+node_pos;
push_nest();mode=hmode;
} /* end of \<Finish displayed math> */
} /* end of |hdisplay| */

@ The user can force the equation number to go on a separate line
by causing its width to be zero.

@<Squeeze the equation as much as possible...@>=
{@+if ((e!=0)&&((w-total_shrink[normal]+q <= z)||@|
   (total_shrink[fil]!=0)||(total_shrink[fill]!=0)||
   (total_shrink[filll]!=0)))
  {@+free_node(b, box_node_size);
  b=hpack(p, z-q, exactly);
  }
else{@+e=0;
  if (w > z)
    {@+free_node(b, box_node_size);
    b=hpack(p, z, exactly);
    }
  }
w=width(b);
}

@ We try first to center the display without regard to the existence of
the equation number. If that would make it too close (where ``too close''
means that the space between display and equation number is less than the
width of the equation number), we either center it in the remaining space
or move it as far from the equation number as possible. The latter alternative
is taken only if the display begins with glue, since we assume that the
user put glue there to control the spacing precisely.

@<Determine the displacement, |d|, of the left edge of the equation...@>=
d=half(z-w);
if ((e > 0)&&(d < 2*e))  /*too close*/
  {@+d=half(z-w-e);
  if (p!=null) if (!is_char_node(p)) if (type(p)==glue_node) d=0;
  }

@ If the equation number is set on a line by itself, either before or
after the formula, we append an infinite penalty so that no page break will
separate the display from its number; and we use the same size and
displacement for all three potential lines of the display, even though
`\.{\\parshape}' may specify them differently.

@<Append the glue or equation number preceding the display@>=
tail_append(new_penalty(pre_display_penalty));@/
store_map(tail, node_pos, offset);
if ((d+s <= pre_display_size)||l)  /*not enough clearance*/
  {@+g1=above_display_skip_no;g2=below_display_skip_no;
  }
else{@+g1=above_display_short_skip_no;
  g2=below_display_short_skip_no;
  }
if (l&&(e==0))  /*it follows that |type(a)==hlist_node|*/
  {@+shift_amount(a)=s;append_to_vlist(a,offset);
  tail_append(new_penalty(inf_penalty)); store_map(tail, node_pos, offset);
  }
else {tail_append(new_glue(pointer_def[glue_kind][g1])); store_map(tail, node_pos, offset); }

@ @<Append the display and perhaps also the equation number@>=
if (e!=0)
  {@+r=new_kern(z-w-e-d);
  if (l)
    {@+link(a)=r;link(r)=b;b=a;d=0;
    }
  else{@+link(b)=r;link(r)=a;
    }
  b=hpack(b, natural);
  }
shift_amount(b)=s+d;append_to_vlist(b,offset)

@ @<Append the glue or equation number following the display@>=
if ((a!=null)&&(e==0)&&!l)
  {@+tail_append(new_penalty(inf_penalty));
  shift_amount(a)=s+z-width(a);
  append_to_vlist(a,offset);
  g2=0;
  }
if (t!=adjust_head)  /*migrating material comes after equation number*/
  {@+link(tail)=link(adjust_head);tail=t;
  }
tail_append(new_penalty(post_display_penalty));
offset=(hpos-hstart)+1-node_pos; /*offset after the display*/
store_map(tail, node_pos,offset);
if (g2 > 0) { tail_append(new_glue(pointer_def[glue_kind][g2]));store_map(tail, node_pos, offset);}


@* Mode-independent processing.

@* Dumping and undumping the tables.

@* The main program.

@* Debugging.

@* Extensions.
The program above includes a bunch of ``hooks'' that allow further
capabilities to be added without upsetting \TeX's basic structure.
Most of these hooks are concerned with ``whatsit'' nodes, which are
intended to be used for special purposes; whenever a new extension to
\TeX\ involves a new kind of whatsit node, a corresponding change needs
to be made to the routines below that deal with such nodes,
but it will usually be unnecessary to make many changes to the
other parts of this program.

In order to demonstrate how extensions can be made, we shall treat
`\.{\\write}', `\.{\\openout}', `\.{\\closeout}', `\.{\\immediate}',
`\.{\\special}', and `\.{\\setlanguage}' as if they were extensions.
These commands are actually primitives of \TeX, and they should
appear in all implementations of the system; but let's try to imagine
that they aren't. Then the program below illustrates how a person
could add them.

Sometimes, of course, an extension will require changes to \TeX\ itself;
no system of hooks could be complete enough for all conceivable extensions.
The features associated with `\.{\\write}' are almost all confined to the
following paragraphs, but there are small parts of the |print_ln| and
|print_char| procedures that were introduced specifically to \.{\\write}
characters. Furthermore one of the token lists recognized by the scanner
is a |write_text|; and there are a few other miscellaneous places where we
have already provided for some aspect of \.{\\write}.  The goal of a \TeX\
extender should be to minimize alterations to the standard parts of the
program, and to avoid them completely if possible. He or she should also
be quite sure that there's no easy way to accomplish the desired goals
with the standard features that \TeX\ already has. ``Think thrice before
extending,'' because that may save a lot of work, and it will also keep
incompatible extensions of \TeX\ from proliferating.
@^system dependencies@>
@^extensions to \TeX@>

@ First let's consider the format of whatsit nodes that are used to represent
the data associated with \.{\\write} and its relatives. Recall that a whatsit
has |type==whatsit_node|, and the |subtype| is supposed to distinguish
different kinds of whatsits. Each node occupies two or more words; the
exact number is immaterial, as long as it is readily determined from the
|subtype| or other data.

We shall introduce five |subtype| values here, corresponding to the
control sequences \.{\\openout}, \.{\\write}, \.{\\closeout}, \.{\\special}, and
\.{\\setlanguage}. The second word of I/O whatsits has a |write_stream| field
that identifies the write-stream number (0 to 15, or 16 for out-of-range and
positive, or 17 for out-of-range and negative).
In the case of \.{\\write} and \.{\\special}, there is also a field that
points to the reference count of a token list that should be sent. In the
case of \.{\\openout}, we need three words and three auxiliary subfields
to hold the string numbers for name, area, and extension.

@d write_node_size 2 /*number of words in a write/whatsit node*/
@d open_node_size 3 /*number of words in an open/whatsit node*/
@d open_node 0 /*|subtype| in whatsits that represent files to \.{\\openout}*/
@d write_node 1 /*|subtype| in whatsits that represent things to \.{\\write}*/
@d close_node 2 /*|subtype| in whatsits that represent streams to \.{\\closeout}*/
@d special_node 3 /*|subtype| in whatsits that represent \.{\\special} things*/
@d language_node 4 /*|subtype| in whatsits that change the current language*/
@d what_lang(A) link(A+1) /*language number, in the range |0 dotdot 255|*/
@d what_lhm(A) type(A+1) /*minimum left fragment, in the range |1 dotdot 63|*/
@d what_rhm(A) subtype(A+1) /*minimum right fragment, in the range |1 dotdot 63|*/
@d write_tokens(A) link(A+1) /*reference count of token list to write*/

@d hitex_ext        language_node+1
@d param_node         hitex_ext /*|subtype| that records the change of a parameter*/
@d param_node_size 3 /* number of memory words in a |param_node| */
@d param_type(A) type(A+1) /* type of parameter */
@d glue_type  2 /* type of an |glue_par| node */
@d param_no(A) subtype(A+1) /* the parameter number */
@d param_value(A)  mem[A+2] /* the parameter value */@#

@d par_node        hitex_ext+1 /*|subtype|  that records a paragraph*/
@d par_node_size 5 /* number of memory words in a |par_node| */
@d par_penalty(A)  mem[A+1].i /* the final penalty */
@d par_extent(A)   link(A+3) /* the extent */@#
@d par_params(A)   info(A+4) /* list of parameter nodes */
@d par_list(A)     link(A+4) /* list of content nodes */

@d disp_node           hitex_ext+2 /*|subtype| that records a math display*/
@d disp_node_size    3 /* number of memory words in a |disp_node| */
@d display_left(A)    type(A+1) /* 1=left 0=right */
@d display_no_bs(A)    subtype(A+1) /* |prev_depth==ignore_depth| */
@d display_params(A)   link(A+1) /* list of parameter nodes */
@d display_formula(A)  link(A+2) /* formula list */
@d display_eqno(A)     info(A+2) /* box with equation number */@#

@d baseline_node    hitex_ext+3  /*|subtype| that records a |baseline_skip| */
@d baseline_node_size small_node_size /* This is 2; we will convert baseline nodes to glue nodes */

@d image_node    hitex_ext+4  /*|subtype| that records an image */
@d image_node_size 6 /* number of memory words in an |image_node| */
@d image_width(A)  mem[A+1].sc  /*width of image */
@d image_height(A) mem[A+2].sc  /*height of image */
@d image_no(A)     link(A+3)  /* the section number */
@d image_alt(A)    link(A+5)  /* alternative image description text */@#

@d hpack_node         hitex_ext+5 /* a hlist that needs to go to hpack */
@d vpack_node         hitex_ext+6 /* a vlist that needs to go to vpackage */
@d pack_node_size       box_node_size /* a box node up to |list_ptr|*/
@d pack_m(A)  type(A+list_offset) /* either additional or exactly */
@d pack_limit(A)        mem[(A)+1+list_offset].sc /* depth limit in |vpack| */
@d pack_extent(A) link(A+2+list_offset) /* extent */@#

@d hset_node         hitex_ext+7  /* represents a hlist that needs |glue_set| */
@d vset_node         hitex_ext+8  /* represents a vlist that needs |glue_set| */
@d set_node_size     box_node_size /* up to |list_ptr| like a box node */
@d set_stretch_order glue_sign
@d set_shrink_order  glue_order
@d set_stretch(A)    mem[(A)+1+list_offset].sc /* replaces |glue_set| */
@d set_extent(A)     pack_extent(A) /* extent */
@d set_shrink(A)     mem[(A)+3+list_offset].sc @#

@d align_node          hitex_ext+9 /* represents an alignment */
@d align_node_size     4
@d align_extent(A)     link(A+2) /* the extent of the alignment */
@d align_m(A)          type(A+2) /* either additional or exactly */
@d align_preamble(A)   info(A+3) /* the preamble */
@d align_list(A)       link(A+3) /* the unset rows/columns */

@d setpage_node       hitex_ext+10 /* represents a page template */
@d setpage_node_size  6
@d setpage_topskip(A) link(A+2)
@d setpage_height(A)  info(A+4) /* extended dimension number */
@d setpage_width(A)   link(A+4) /* extended dimension number */
@d setpage_list(A)    info(A+5) /* the template itself */
@d setpage_streams(A) link(A+5)   /* list of stream definitions */

@d setstream_node         hitex_ext+11 /* represents a stream definition */
@d setstream_node_size    6
@d setstream_max(A)       info(A+3) /* extended dimension number */
@d setstream_width(A)     link(A+3) /* extended dimension number */
@d setstream_topskip(A)   info(A+4)
@d setstream_height(A)    link(A+4)
@d setstream_before(A)    info(A+5)
@d setstream_after(A)     link(A+5)

@d stream_node     hitex_ext+12 /* represents a stream insertion point */
@d stream_node_size 2
@d stream_number(A)   type(A+1)
@d stream_insertion(A) subtype(A+1)


@d xdimen_node hitex_ext+15
@d xdimen_node_size    4
@d xdimen_ref_count(A) link(A)
@d xdimen_width(A)     mem[A+1].sc
@d xdimen_hfactor(A)   mem[A+2].sc
@d xdimen_vfactor(A)   mem[A+3].sc

@d ignore_node hitex_ext+16 /* ignored used to attach extra information */
@d ignore_node_size small_node_size /* same as |disc_node| */
@d ignore_info(A)    type(A+1)
@d ignore_list(A)    link(A+1)

@d color_node hitex_ext+17 /* represent a color node */
@d end_color_node hitex_ext+18 /* represent an end color node */
@d no_color_node  hitex_ext+22 /* a deleted end color node */
@d color_node_size small_node_size
@d color_ref(A)  type(A+1) /* reference to the color set */

@d label_node hitex_ext+23 /* represents a link to a another location */
@d label_node_size 2
@d label_ref(A) link(A+1) /* hint: a reference to a label */

@d start_link_node hitex_ext+24 /* represents a link to another location */
@d end_link_node hitex_ext+25 /* represents a link to another location */
@d link_node_size 3
@d as_color(A) (A)     /* second word like a |color_node| */
@d as_label(A) ((A)+1) /* third word like a |label_node| */

@d outline_node hitex_ext+26 /* represents an outline item */
@d outline_node_size 3 /* second word like a |label_node| */
@d outline_ptr(A)   link(A+2) /* text to be displayed */
@d outline_depth(A) info(A+2) /* depth of sub items */


@ Each new type of node that appears in our data structure must be capable
of being displayed, copied, destroyed, and so on. The routines that we
need for write-oriented whatsits are somewhat like those for mark nodes;
other extensions might, of course, involve more subtlety here.

@<Display the whatsit...@>=
switch (subtype(p)) {
case special_node: {@+print_esc("special");
  print_mark(write_tokens(p));
  } @+break;
case language_node: {@+print_esc("setlanguage");
  print_int(what_lang(p));print(" (hyphenmin ");
  print_int(what_lhm(p));print_char(',');
  print_int(what_rhm(p));print_char(')');
  } @+break;
case param_node: print_esc("parameter ");
  print_int(param_type(p));print_char(',');print_int(param_no(p));
  print_char(':');print_int(param_value(p).i);
  break;
case par_node: print_esc("paragraph(");
  print_xdimen(par_extent(p));
  print(", ");
  print_int(par_penalty(p));
  print_char(')');
  node_list_display(par_params(p));
  node_list_display(par_list(p));
  break;
case disp_node: print_esc("display ");
  node_list_display(display_eqno(p));
  if (display_left(p)) print("left "); else  print("right ");
  node_list_display(display_formula(p));
  node_list_display(display_params(p));
  break;
case hset_node: case vset_node:
  print_char('\\');
  print_char(subtype(p)==hset_node?'h':'v');
  print("set(");
  print_scaled(height(p)); print_char('+');
  print_scaled(depth(p)); print(")x"); print_scaled(width(p));
  if (shift_amount(p)!=0)
    {@+print(", shifted ");print_scaled(shift_amount(p));
    }
  if (set_stretch(p)!=0)
  {@+print(", stretch ");print_glue(set_stretch(p),set_stretch_order(p),"pt");
    }
  if (set_shrink(p)!=0)
  {@+print(", shrink ");print_glue(set_shrink(p),set_shrink_order(p),"pt");
    }
  print(", extent "); print_xdimen(set_extent(p));
  node_list_display(list_ptr(p)); /*recursive call*/
  break;
case hpack_node: case vpack_node:
  print_char('\\');
  print_char(subtype(p)==hpack_node?'h':'v');
  print("pack(");
  print(pack_m(p)==exactly?"exactly ":"additional ");
  print_xdimen(pack_extent(p));
  if (subtype(p)==vpack_node && pack_limit(p)!=max_dimen) { print(", limit "); print_scaled(pack_limit(p)); }
  print_char(')');
  node_list_display(list_ptr(p));
  break;
case image_node:
  print_esc("HINTimage(");
  print("width ");print_scaled(image_height(p));
  print(" height "); print_scaled(image_width(p));
  print("), section ");print_int(image_no(p));
  if (dir[image_no(p)].file_name!=NULL) {print(", "); print(dir[image_no(p)].file_name);}
  break;
case color_node:
  print_esc("HINTcolor ");print_int(color_ref(p));
  break;
case no_color_node:
  print_esc("HINTendcolor ignored");
  break;
case end_color_node:
  print_esc("HINTendcolor ");
  break;
case align_node:
  print_esc("align(");
  print(align_m(p)==exactly?"exactly ":"additional ");
  print_xdimen(align_extent(p));print_char(')');
  node_list_display(align_preamble(p));
  print_char(':');
  node_list_display(align_list(p));
  break;
case ignore_node:
  print_esc("ignore ");print_int(ignore_info(p));print_char(':');
  node_list_display(ignore_list(p));
  break;
case start_link_node:
  print_esc("HINTstartlink ");
  print_label(as_label(p));
  if (color_ref(as_color(p))!=1) { print("color "); print_int(color_ref(as_color(p))); }
  break;
case end_link_node:
  print_esc("HINTendlink ");
  if (color_ref(as_color(p))!=0xFF) { print("color "); print_int(color_ref(as_color(p))); }
  break;
case label_node:
  print_esc("HINTdest ");
  print_label(p);
  break;
case outline_node:
  print_esc("HINToutline");
  print_label(p);
  print(" depth "); print_int(outline_depth(p));
  if (outline_ptr(p)==null) print("{}"); else
  { print_ln();print_current_string();node_list_display(outline_ptr(p));}
  break;
case stream_node:
  print_esc("HINTstream");print_int(stream_insertion(p));
  print_char('(');print_int(stream_number(p));print_char(')');
  break;
default: print("whatsit?");
}

@ @<Make a partial copy of the whatsit...@>=
switch (subtype(p)) {
case open_node: {@+r=get_node(open_node_size);words=open_node_size;
  } @+break;
case write_node: case special_node: {@+r=get_node(write_node_size);
  add_token_ref(write_tokens(p));words=write_node_size;
  } @+break;
case close_node: case language_node: {@+r=get_node(small_node_size);
  words=small_node_size;
  } @+break;
case param_node:
{@+r=get_node(param_node_size);
  if (param_type(p)==glue_type) add_glue_ref(param_value(p).i);
  words=param_node_size;
  } @+break;
case par_node:
{@+r=get_node(par_node_size);
  add_xdimen_ref(par_extent(p));
  par_params(r)=copy_node_list(par_params(p));
  par_list(r)=copy_node_list(par_list(p));
  words=par_node_size-1;
  } @+break;
case disp_node:
{@+r=get_node(disp_node_size);
  display_left(r)=display_left(p);
  display_no_bs(r)=display_no_bs(p);
  display_eqno(r)=copy_node_list(display_eqno(p));
  display_formula(r)=copy_node_list(display_formula(p));
  display_params(r)=copy_node_list(display_params(p));
  words=disp_node_size-2;
  } @+break;
case baseline_node:
{@+r=get_node(baseline_node_size);
  words=baseline_node_size;
  } @+break;
case hpack_node: case vpack_node:
{@+r=get_node(pack_node_size);
  mem[r+7]=mem[p+7];mem[r+6]=mem[p+6];mem[r+5]=mem[p+5]; /*copy the last three words*/
  list_ptr(r)=copy_node_list(list_ptr(p));/*this affects |mem[r+5]|*/
  add_xdimen_ref(pack_extent(p));/*this affects |mem[r+7]|*/
  words=5;
  } @+break;
case hset_node: case vset_node:
{@+r=get_node(set_node_size);
  mem[r+8]=mem[p+8];mem[r+7]=mem[p+7];mem[r+6]=mem[p+6];mem[r+5]=mem[p+5]; /*copy the last four words*/
  list_ptr(r)=copy_node_list(list_ptr(p)); /*this affects |mem[r+5]|*/
  add_xdimen_ref(set_extent(p));/*this affects |mem[r+7]|*/
  words=5;
  } @+break;
case image_node:
    r=get_node(image_node_size);
    image_alt(r)=copy_node_list(image_alt(p));
    words=image_node_size-1;
    break;
case color_node:
case no_color_node:
case end_color_node:
    r=get_node(color_node_size);
    words=color_node_size;
    break;
case align_node:
  {@+r=get_node(align_node_size);
     align_preamble(r)=copy_node_list(align_preamble(p));
     align_list(r)=copy_node_list(align_list(p));
     add_xdimen_ref(align_extent(p));
     words=align_node_size-1;
  } @+break;
case setpage_node:
  {@+r=get_node(setpage_node_size);
     add_glue_ref(setpage_topskip(p));
     add_xdimen_ref(setpage_height(p));
     add_xdimen_ref(setpage_width(p));
     setpage_list(r)=copy_node_list(setpage_list(p));
     setpage_streams(r)=copy_node_list(setpage_streams(p));
     words=setpage_node_size-1;
  } @+break;
case setstream_node:
  {@+r=get_node(setstream_node_size);
     add_xdimen_ref(setstream_max(p));
     add_xdimen_ref(setstream_width(p));
     add_glue_ref(setstream_topskip(p));
     add_glue_ref(setstream_height(p));
    setstream_before(r)=copy_node_list(setstream_before(p));
    setstream_after(r)=copy_node_list(setstream_after(p));
    words=setstream_node_size-1;
  } @+break;
case ignore_node:
    r=get_node(ignore_node_size);
    ignore_info(r)=ignore_info(p);
    ignore_list(r)=copy_node_list(ignore_list(p));
    words=ignore_node_size-1;
  break;
case start_link_node:
    r=get_node(link_node_size);
    words=link_node_size;
    break;
case end_link_node:
    r=get_node(link_node_size);
    words=link_node_size;
    break;
case label_node:
    r=get_node(label_node_size);
    words=label_node_size;
    break;
case outline_node:
    r=get_node(outline_node_size);
    outline_ptr(r)=copy_node_list(outline_ptr(p));
    outline_depth(r)=outline_depth(p);
    words=outline_node_size-1;
    break;
case stream_node:
    r=get_node(stream_node_size);
    words=stream_node_size;
  break;
case xdimen_node:
    r=get_node(xdimen_node_size);
    words=xdimen_node_size;
  break;
default:confusion("ext2");
@:this can't happen ext2}{\quad ext2@>
}

@ @<Wipe out the whatsit...@>=
{@+switch (subtype(p)) {
case close_node: case language_node: free_node(p, small_node_size);@+break;
case param_node:
  if (param_type(p)==glue_type) fast_delete_glue_ref(param_value(p).i);
  free_node(p, param_node_size);@+break;
case par_node:
  delete_xdimen_ref(par_extent(p));
  flush_node_list(par_params(p));
  flush_node_list(par_list(p));
  free_node(p, par_node_size);@+break;
case disp_node:
  flush_node_list(display_eqno(p));
  flush_node_list(display_formula(p));
  flush_node_list(display_params(p));
  free_node(p, disp_node_size);@+break;
case  baseline_node:
  free_node(p, baseline_node_size);@+break;
case  hpack_node: case  vpack_node:
  delete_xdimen_ref(pack_extent(p));
  flush_node_list(list_ptr(p));
  free_node(p, pack_node_size);@+break;
case  hset_node: case  vset_node:
  delete_xdimen_ref(set_extent(p));
  flush_node_list(list_ptr(p));
  free_node(p, set_node_size);@+break;
case image_node:
  flush_node_list(image_alt(p));
  free_node(p,image_node_size);@+break;
case color_node:
case no_color_node:
case end_color_node:
  free_node(p,color_node_size);@+break;
case align_node:
  delete_xdimen_ref(align_extent(p));
  flush_node_list(align_preamble(p));
  flush_node_list(align_list(p));
  free_node(p, align_node_size);@+break;
case setpage_node:
  delete_glue_ref(setpage_topskip(p));
  delete_xdimen_ref(setpage_height(p));
  delete_xdimen_ref(setpage_width(p));
  flush_node_list(setpage_list(p));
  flush_node_list(setpage_streams(p));
  free_node(p, setpage_node_size);@+break;
case setstream_node:
  delete_xdimen_ref(setstream_max(p));
  delete_xdimen_ref(setstream_width(p));
  delete_glue_ref(setstream_topskip(p));
  delete_glue_ref(setstream_height(p));
  flush_node_list(setstream_before(p));
  flush_node_list(setstream_after(p));
  free_node(p,setstream_node_size); @+break;
case ignore_node:
  flush_node_list(ignore_list(p));
  free_node(p,ignore_node_size); @+break;
case start_link_node:
  free_node(p,link_node_size);@+break;
case end_link_node:
  free_node(p,link_node_size);@+break;
case label_node:
  free_node(p,label_node_size);@+break;
case outline_node:
  flush_node_list(outline_ptr(p));
  free_node(p,outline_node_size);@+break;
case stream_node:
  free_node(p,stream_node_size); @+break;
case xdimen_node:
  free_node(p,xdimen_node_size);
default:confusion("ext3");
@:this can't happen ext3}{\quad ext3@>
} @/
goto done;
}

@ @<Incorporate a whatsit node into a vbox@>=
if (subtype(p)==image_node)
{ if (image_width(p)> w) w= image_width(p);
  x= x+d+image_height(p);d=0;
}

@ @<Incorporate a whatsit node into an hbox@>=
if (subtype(p)==image_node)
{@+if (image_height(p)> h) h= image_height(p);
  x= x+image_width(p);
}
else if (subtype(p)==color_node)
  just_color=color_ref(p);
else if (subtype(p)==end_color_node)
  just_color=-1;
else if (subtype(p)==start_link_node)
{ just_label=label_ref(as_label(p)); just_color=color_ref(as_color(p));
  if (just_color==0xFF) just_color=-1;
}
else if (subtype(p)==end_link_node)
{ just_label=-1; just_color=color_ref(as_color(p));
  if (just_color==0xFF) just_color=-1;
}

@ @<Let |d| be the width of the whatsit |p|@>=
d=((subtype(p)==image_node)?image_width(p):0)

@ @d adv_past(A) {}

@<Advance \(p)past a whatsit node in the \(l)|line_break| loop@>=@+
if (subtype(cur_p)==image_node)act_width=act_width+image_width(cur_p);
adv_past(cur_p)

@ @<Prepare to move whatsit |p| to the current page, then |goto contribute|@>=
if (subtype(p)==image_node)
{@+page_total=page_total+page_depth+image_height(p);
page_depth=0;
}
goto contribute

@ @<Process whatsit |p| in |vert_break| loop, |goto not_found|@>=
goto not_found


@

\endgroup

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
  @<Check if node |p| is a new champion breakpoint for the top of page@>@;
contribute:
@<Prepend node |p| to the current page and |goto done|@>@;
done1: @<Recycle node |p|@>;
done: 
@

@<Prepend node |p| to the current page and |goto done|@>=
link(contrib_head)=link(p);
link(p)=link(page_head);
if (link(page_head)==null) page_tail=p;
link(page_head)=p;
goto done;
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

@<Check if node |p| is a new champion breakpoint for the top of page@>=
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
static void store_map(pointer p, uint32_t pos0, uint32_t offset)
{@+ map[p]=pos0;
  map[p+1]=offset;@+
}

uint32_t hposition(pointer p) 
{@+ return map[p];@+
}
@  

The function that takes information form the cache and converts it to a |uint64_t| location, as mentioned above, commes next. It returns |HINT_NO_LOC| if no information is in the cache.
This value is used to indicate that a variable contains no valid location.

@<\HINT\ |static|@>=
#define HINT_NO_LOC 0xFFFFFFFFFFFFFFFF
#define PAGE_LOC(POS0,OFF) (((uint64_t)((POS0)+(OFF))<<32) + (uint64_t)(OFF))
#define LOC_POS(P) ((P)>>32) /* the node position */
#define LOC_OFF(P) ((P)&0xFFFFFFFF) /* the distance to the top level node */
#define LOC_POS0(P) (LOC_POS(P)-LOC_OFF(P)) /* the top level position */
@

@<\HINT\ auxiliar functions@>=
uint64_t hlocation(pointer p)
{ @+ uint64_t h=PAGE_LOC(map[p],map[p+1]);
   while (h==0 && link(p)!=null) /* search the list if necessary */
   { p=link(p); h=PAGE_LOC(map[p],map[p+1]); }   
   return h;
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

static uint64_t page_loc[MAX_PAGE_POS];
static int cur_loc;
static int lo_loc, hi_loc;
@
@<\HINT\ |static|@>=
static uint64_t page_loc[];
static int cur_loc;
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
static void hloc_clear(void)
{ @+lo_loc=hi_loc=cur_loc;PREV_PAGE(lo_loc);NEXT_PAGE(hi_loc);@+
}
@

@<render functions@>=
static bool hloc_next(void)
{ @+int i=cur_loc;
  if (hstart+LOC_POS(page_loc[cur_loc])>=hend) 
    return false;
  NEXT_PAGE(i);
  if (i==hi_loc) 
    return false;
  cur_loc=i;
  return true;
}

static bool hloc_prev(void) 
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

@<\HINT\ |static|@>=
static void hloc_clear(void); /* keep only |cur_loc| in the cache */
static uint64_t hlocation(pointer p); /* map |p| to its file location */
@

After these preparations, we can turn our attention to the functions that manage
the page cache itself. We start with the initialization function:

@<\HINT\ functions@>=
static void hloc_init(void)
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

@<render functions@>=

static void hloc_set(uint64_t h)
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

static void hloc_set_next(pointer p)
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
static void hloc_set_prev(pointer p)
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

@<\HINT\ |static|@>=
static void hloc_init(void);
static void store_map(pointer p, uint32_t pos, uint32_t offset); /*store the location of |p|*/
static uint32_t hposition(pointer p); /* return the position of |p| or 0*/
static void hloc_set_next(pointer p);/* record the location of |p| as the start of the next page */
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
  ft_init();
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
  hint_clear_fonts(true);
  ft_destroy();
}
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
static double xdpi=600.0, ydpi=600.0;
@

@<\HINT\ functions@>=
void hint_resize(int px_h, int px_v, double x_dpi, double y_dpi)
{ double pt_h, pt_v;
#if 0
  /* this optimization causes the android viewer to display a blank page
     after opening a new file. To be investigated!
     using local static variables is discouraged.
  */
  static int old_px_h=0, old_px_v=0;
  static double old_xdpi=0.0, old_ydpi=0.0;
   if (old_px_h==px_h && old_px_v==px_v && old_xdpi==x_dpi && old_ydpi==y_dpi)
    return;
  old_px_h=px_h; old_px_v=px_v; old_xdpi=x_dpi; old_ydpi=y_dpi;
#endif
  xdpi=x_dpi; ydpi=y_dpi;
  pt_h = px_h * 72.27 / x_dpi;
  pt_v = px_v * 72.27 / y_dpi; 
  page_h = round(pt_h * (1 << 16));
  page_v = round(pt_v * (1 << 16));
  nativeSetSize(px_h, px_v, pt_h, pt_v);
  hloc_clear();
  hflush_contribution_list(); hpage_init();
  forward_mode=false;
  backward_mode=false;
}
@

The function tells the native renderer about the change, clears all locations
from the location cache, removes nodes from the contribution list,
and resets the rendering direction.

Once a \HINT\ file is loaded, the GUI might be interested to know the ``design size''
of the document. The following two functions will return the \.{\\hsize} and \.{\\vsize}
as given to Hi\TeX.

@<\HINT\ functions@>=
scaled hint_hsize(void)
{ if (dimen_def!=NULL) return dimen_def[hsize_dimen_no];
  else return 0;
}

scaled hint_vsize(void)
{ if (dimen_def!=NULL) return dimen_def[vsize_dimen_no];
  else return 0;
}
@



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
@<\HINT\ |static|@>=
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
static scaled hvsize, hhsize;
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
static int page_v, page_h, offset_v, offset_h;
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

To implement |hint_set_fpos| we use |hff_hpos| to ``fast forward''
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

@<\HINT\ variables@>=
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

@<\HINT\ |static|@>=
typedef struct { 
uint64_t pos;  
uint8_t depth; 
uint8_t where; 
int p; /* pointer to the list of title nodes */
char *title; /* title as sequence of utf8 character codes */
} hint_Outline;
hint_Outline *hint_outlines;
@

The |pos| field contains a ``position'' in the hint file 
(like the ones returned from and passed to functions like |hint_page_top|). 
The user interface can use it to
navigate to the desired position in the \HINT\ file.
The |where| field indicates where the
label should be placed on the page.
The values are:
@<\HINT\ |static|@>=
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
@<\HINT\ |static|@>=
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
static void trv_init(void (*f)(uint32_t c))
{trv_ignore=false;trv_skip_space=false; trv_stream=f;}

static void trv_char(uint32_t c)
{ if (c==0x20) trv_skip_space=true;
  else
  { if (trv_skip_space)
    { trv_skip_space=false; trv_stream(0x20);}
    trv_stream(c);
  }
}

static void trv_hlist(pointer p)
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

static void trv_vlist(pointer p)
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

@<\HINT\ |static|@>=
static void trv_init(void (*f)(uint32_t c));
static void trv_vlist(pointer p);
static void trv_hlist(pointer p);
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

static char *hlist_to_string(pointer p)
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
For searching, two styles are defined: |cur_style==1| for marked text
and |cur_style==2| for focus text.

Calling the function |hint_set_mark(char *m, int s)| will cause the
style to be one for all glyphs on the
current page that belong to a character string matching |m| of length
|s|.  If |m==NULL|, the style will be zero for all glyphs.  The
``focus'' can be associated with one occurence of the marked string;
its glyphs will use two as a style value.
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
static void hmark_page(void)
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

@<\HINT\ declarations@>=
static void hmark_page(void);
@

We need a dummy version for our test programs.
@<test functions@>=
static void hmark_page(void)
{return; }
@

When the renderer traverses the page more variables are needed.
@<render variables@>=
static bool c_ignore;
@

|cur_style| will be non zero while rendering a marked sequence
of characters and it will be zero while rendering non-marked
characters. |c_ignore| will be |true| while rendering characters that
do not count for matching or non-matching characters, for example characters
that were introduced by the pre- and post-lists of discretionary hyphens.
|m_d| will contain the number of characters left in the current stretch
of marked or unmarked characters.
|m_ptr| will point to the value in the |m_dist| array that we will need
for the next stretch of unmarked characters

At the start of the renderer, we set |m_ptr=0| and |cur_style=0|;
The distance |m_d| to the first marked glyph is set by calling |m_get()|.

@<initialize marking@>=
m_ptr=0; m_d=m_get(); c_ignore=false; cur_style=next_style=0;
@

Whenever the renderer encounters a character, it will need to
update |cur_style|.
The new value of |cur_style| is assigned to |next_style| and
the latter value is used when calling |render_char|. This is needed
because the call to render char is shared with a |goto render_c;|
when handling a ligature. The handling of the ligature might
then change the value of |next_char|. Whether this detour is realy
necessary remains unclear. It seems simpler to change the value of
|cur_style| directly when handling a ligature. But note that also
ignore nodes change the value of |next_style| and if the ignore node
preceeds a ligature node this change might be important. 


@<compute the |next_style|@>=
  next_style=cur_style;
  while (m_d==0)
  { next_style=next_style>0?0:1;
    if (next_style>0)
    { if (m_ptr==m_focus) next_style=2;
      m_d=m_chars;
    }
    else
      m_d=m_get();
  }
  m_d--;
@

When rendering a ligature, we consider for the purpose of marking
the characters which generated the ligature.
If any of these characters is marked, the whole ligature is marked.
@<account for the characters that generated the ligature@>=
if (!c_ignore)
{ pointer q;
  int s, max_s;
  s=cur_style;
  max_s=0;
  q=lig_ptr(p);
  while (q!=null)
  { if (is_char_node(q) && character(q)!=' ')
    { @<compute the |next_style|@>@;
      cur_style=next_style;
      if (next_style>max_s) max_s=next_style;
    }
    q=link(q);
  }
  if (s!=max_s)
    hSetColor(max_s);
  else
    cur_style=s;
}
@

When the renderer encounters an ignore node with |ignore_info(p)==1|
it should ignore all the following characters until
it encounters the matching ignore node with |ignore_info(p)==0|.
Instead, it uses the characters in |ignore_list(p)|.
This is done by setting |c_ignore|.

@<handle an ignore node@>=
if (ignore_info(p)==1)
{ next_style=0;
  c_ignore_list(ignore_list(p));
  c_ignore=true;
}
else
  c_ignore=false;
@

Instead of the ignored nodes, the renderer considers the characters
stored in the |ignore_list|.
Because there is no simple relation between the |ignore_list| and its replacement,
we will mark the whole replacement if any part of the ignore
list is marked.
Because the |ignore_list| may contain boxes, traversing it
is inherently recursive and we start with a function that
traverses a list of nodes accounting for |cur_style| changes
but without rendering them. We assume that the |ignore_list|
consists (recursively!) entirely of character, kern, box, rule, and ligature nodes.

@<render functions@>=
static void hSetColor(int c);

static void c_ignore_list(pointer p)
{ int s, max_s;
  s=cur_style;
  max_s=0;
  while(p!=null)
  { if (is_char_node(p) && character(p)!=' ')
    { @<compute the |next_style|@>@;
      cur_style=next_style;
      if (next_style>max_s) max_s=next_style;
    }
    else
    { switch(type(p)) 
      { case hlist_node:
        case vlist_node: c_ignore_list(list_ptr(p)); break;
        case ligature_node:
        { pointer q=lig_ptr(p);
          while (q!=null)
          { @<compute the |next_style|@>@;
            cur_style=next_style;
            if (next_style>max_s) max_s=next_style;
            q=link(q);
          }
        }
        break;
      }
    }
    p=link(p);
  }
  if (s!=max_s)
    hSetColor(max_s);
  else
    cur_style=s;
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
Characters that belong to a link usualy get a different color.

Because of line breaking, a link might be spread over multiple
lines or even pages. To detect an unfinished link
at the end of a horizontal list, the local variable |local_link| is used;
the current link is recorded in |cur_link|. If there is no current
link, |cur_link| is negative.
To collect data about all links on a page, the renderer calls |add_new_link|
when a link starts and |end_new_link| when it ends.
It is not allowed to nest links. So between two occurences of a start link
there must be an end link. If the end link is missing, it is silently assumed
that the second start link is preceeded by an end link. An extra end link
is silently ignored.

@<render variables@>=
static int cur_link=-1;
@

@<handle a start link node@>=
local_link=label_ref(as_label(p));
add_new_link(local_link,this_box,cur_h,cur_v);
{ uint32_t c = color_ref(as_color(p));
  if (c==0xFF) 
    hSetColor(list_color);
  else
    hSetColor(c);
}

@

@<handle an end link node@>=
end_new_link(local_link,this_box,cur_h,cur_v);
local_link=-1;
{ uint32_t c = color_ref(as_color(p));
  if (c==0xFF)
    hSetColor(list_color);
  else
    hSetColor(c);
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
the necessary information in the |hint_links| and |max_link| variables.
|hint_links| is a dynamic array, indexed from 0 to |max_link|.
If |max_links| is negative, no links are available.



@<\HINT\ |static|@>=
typedef struct { 
uint64_t pos;  
uint8_t where; 
scaled top, bottom, left, right;
} hint_Link;
extern hint_Link *hint_links;
static int max_link;
@

@<\HINT\ variables@>=
hint_Link *hint_links=NULL;
static int max_link=-1;
@

The |hint_links| array is filled with the necessary information
when the page is rendered.

@<render functions@>=
static int links_allocated=0;
static void add_new_link(int n, pointer p, scaled h, scaled v)
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
     DBG(DBGLABEL,"Links allocated %d\n",links_allocated);
  }
  t=hint_links+max_link;
  DBG(DBGLABEL,"Link add %d\n",max_link);
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

static void end_new_link(int n, pointer p, scaled h, scaled v)
{ hint_Link *t;
  if (max_link<0) return;
  t=hint_links+max_link;
  DBG(DBGLABEL,"Link end %d\n",max_link);
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

static int last_hit_link=-1;

int hint_find_link(scaled x, scaled y,scaled precission)
{ int i;
  hint_Link *t;
  if (max_link<0) return -1;
  if (last_hit_link<0 || last_hit_link>max_link) last_hit_link=max_link/2;
  i=last_hit_link;
  t=hint_links+i;
  DBG(DBGLABEL,"Link find %d\n",max_link);
  if (hlink_distance(x,y,t)<=precission)
    return i;
  else if (y<t->top) /* search up */
  { while (i>0)
    { i--;
      t=hint_links+i;
      DBG(DBGLABEL,"Link up %d\n",max_link);
      if(hlink_distance(x,y,t)<=precission)
      { last_hit_link=i;  return i; }
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
      DBG(DBGLABEL,"Link scan %d\n",max_link);
      d=hlink_distance(x,y,t);
      if (d<min_d)
      { min_d=d; min_i=i;}
    }
    last_hit_link=min_i;
    return last_hit_link;
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
  DBG(DBGLABEL,"Link page %d\n",max_link);
  h=hint_links[i].pos;
  w=hint_links[i].where;
  if (w==LABEL_TOP) return hint_page_top(h);
  else if (w==LABEL_BOT) return hint_page_bottom(h);
  else if (w==LABEL_MID) return hint_page_middle(h);
  else return  hint_page_get();
}
@

Here is a summary of the above functions:
@<\HINT\ |static|@>=
extern int hint_find_link(scaled x, scaled y, scaled precission);
extern uint64_t hint_link_page(int i);
@


\section{Rendering \HINT\ Files}
How to render a \HINT\ file on any specific device depends largely on the
operating system and its API encapsulating the device. Never the less, there
are some functions that can be shared accross many different operating systems
or at least can serve as a starting point for implementing operating system 
specific versions.

Most systems, for example, will need some code to initialize and to finalize
the rendering infrastructure. The system depenent functions will be implemented
in as |nativeInit| and |nativeClear|. To have a consistent interface accross
different graphical user interfaces. These are reexported as |hint_render_on|
and |hint_render_off|. |hint_render_on| must be called before any other
function that attempts to use the native rendering infrastructure.

@<render functions@>=
#define CUR_FG FG(CURCOLOR(cur_mode,cur_style,color_def[cur_color]))
#define CUR_BG BG(CURCOLOR(cur_mode,cur_style,color_def[cur_color]))

static void hSetColor(int c)
{ cur_color=c;
  cur_fg=CUR_FG;
  nativeSetForeground(cur_fg);
}

void hint_render_on(void)
{ nativeInit();
  hSetColor(0);
  hint_clear_fonts(true);
}

void hint_render_off(void)
{ nativeClear();
}
@

A function that is just forwarded is |nativeSetGamma|.

@<render functions@>=

void hint_dark(int dark)
{ cur_mode=dark?1:0;
  hSetColor(cur_color);
}

void hint_gamma(double gamma)
{ nativeSetGamma(gamma);
}
@

Prototypes of the three functions just defined are contained in
the {\tt hint.h} file where as the prototypes of the 
``native'' functions are part of {\tt rendernative.h}. The latter
file contains requirements: functions that need to be implemented
but are not defined here.
%Most implementations will avoid the
%inclusion of  {\tt rendernative.h} because it will need other include files,
%notably  {\tt hfonts.h} which defines the interface to the font cache.
{\tt hint.h} has almost no dependencies and avoids
cluttering the global name space by using the |hint_|\dots prefix.




\subsection{Fonts}
The \HINT\ file format supports four different types of fonts:
The traditional PK fonts\cite{TR:pkfile} and the more modern
PostScript Type1 fonts\cite{PST1} which are used by many \TeX\ engines, 
TrueType\cite{TTT:TT} fonts, and OpenType fonts\cite{MS:OTF}\cite{ISO:OTF}.
To render the latter, we use the FreeType Library\cite{freetype}
by David Turner, Werner Lemberg, and others.

@<\HINT\ types@>=
typedef	enum {@+ no_format, pk_format, ft_format@+ } FontFormat;
@


The features of a font are described in a |font_s| structure.  A major
part of the structure is the glyph cache that provides fast access to
the individual glyphs belonging to the font. Further, it includes an
|ff| field containing the font format and a variant part that differs
for the different font formats.


@<\HINT\ types@>=
@<definitions of |PKfont| and |FTfont| types@>@;

typedef struct font_s {
  unsigned char n; /* the font number */
  unsigned char *font_data; /* pointer to the font data in the HINT file */
  int data_size; /* the size of the font data in byte */
  double s; /* the size in pt */
  double hpxs,vpxs; /* the horizontal and vertical size of one pixel in pt */
  @<the glyph cache@>@;
  bool resize;
  FontFormat ff; /* the font format */
} Font;
@
The |fonts| table contains an entry for every possible font number.

@<\HINT\ variables@>=
static Font *fonts[0x100]={NULL}; 
@

Given a font number |f| the following function returns a pointer to the 
corresponding font structure, extracting the necessary information from the \HINT\ file if necessary.
@<render functions@>=
static struct font_s *hload_font(uint8_t f)
{ Font *fp;
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
    fp->resize=true;
  }
  fonts[f]=fp;
  fp->s=font_def[f].s/(double)(1<<16);
  @<determine the font format and unpack the font@>@;
  return fonts[f];
}
@

To initialize the |fonts| table and remove all fonts form memory, the
function |hint_clear_fonts|  is used with the |rm| parameter set to
|true|. If |rm| is set to |false| the action is less drastic: only the
function |nativeFreeTexture| is called for all glyphs in the glyph cache,
the |fonts| table and the glyph cache are retained.


@<font functions@>=
static void hfree_glyph_cache(Font *f, bool rm);

void hint_clear_fonts(bool rm)
{ int f;
  DBG(DBGFONT,rm?"Clear font data":"Clear native glyph data");
  for (f=0;f<=max_ref[font_kind];f++)
    if (fonts[f]!=NULL)
    { hfree_glyph_cache(fonts[f],rm);
      if (rm)@+ { @+ fonts[f]->resize=true;@+ }
    }
}
@

We need a dummy version for our test programs.
@<test functions@>=
/* replaces the values from hrender.c */
double xdpi=600.0,ydpi=600.0;
unsigned int nativeFreeTexture(unsigned int t)  {return 0;}
unsigned int nativeTexture(unsigned char *bits, int w, int h) {return 0;}
void nativeGlyph(double x,double y,double w,double h,
   unsigned int t)  {return;}
static void hfree_glyph_cache(Font *f, bool rm) {}
void nativeSetSize(int px_h, int px_v, double pt_x, double pt_v) {}
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
  Gcache **g0; /* $0 \le |g| < 2^7$ */
  Gcache ***g1;  /* $2^7 \le |g| < 2^{12}$ */
  Gcache ****g2; /* $2^{12} \le |g| < 2^{18}$ */
  Gcache *****g3; /* $2^{18} \le |g| < 2^{24}$ */@/
@t~@>
@


The glyphs are described using a |Gcache| structure. 
To look up the cached glyph data for font |f| and charactercode |cc|,
we use the function |g_lookup|.

@<render functions@>=
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

@<\HINT\ variables@>=
static Gcache g_undefined ={0};
@

@<render functions@>=
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
be deallocated. Otherwise only the function |nativeFreeTexture| will be called.
Together with the exported function |hint_clear_fonts| this offers
the native rendering engine a method to relase allocated resources
without the need to know the deatails of the glyph cache.
The construction of the functions |hfree_g0| to |hfree_g3| mirrors
the construction of |hnew_g0| to  |hnew_g3|

@<render functions@>=
static void hfree_g0(Gcache **g, bool rm)
{ int i;
  if (g==NULL) return;
  for (i=0;i<G0_SIZE;i++)
    if (g[i]!=NULL)
    { g[i]->OGLtexture=nativeFreeTexture(g[i]->OGLtexture);
      if (rm) {
      if (g[i]->bits!=NULL) free(g[i]->bits);
      free(g[i]); g[i]=NULL;@+ }
    }
}

static void hfree_g1(Gcache ***g, bool rm)
{ int i;
  if (g==NULL) return;
  for (i=0;i<G123_SIZE;i++)
	if (g[i]!=NULL)
	{ hfree_g0(g[i],rm);
      if (rm) {free(g[i]); g[i]=NULL;@+ }
	}
}

static void hfree_g2(Gcache ****g, bool rm)
{ int i;
  if (g==NULL) return;
  for (i=0;i<G123_SIZE;i++)
	if (g[i]!=NULL)
	{ hfree_g1(g[i],rm);
      if (rm) {free(g[i]); g[i]=NULL;@+ }
	}
}


static void hfree_g3(Gcache *****g, bool rm)
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



@<definitions of |PKfont| and |FTfont| types@>=
@<definitions of format specific types@>@;

typedef struct {
  int w,h; 
  int hoff,voff; 
  unsigned char *bits; 
  unsigned int OGLtexture;
  FontFormat ff; 
  union {@+
	  PKglyph pk;@+
	  FTglyph tt;@+
  };
} Gcache;
@
 

The above structure has an |OGLtexture| member. To speed up the
rendering of glyphs, the glyph bitmap is loaded into the graphics
cards as a texture and from then on identified by a single integer,
the |OGLtexture|.

Occasionaly, however, the front-end will change the OpenGL context and
the texture identifiers will loose their meaning. In this situation,
it is not necessary to wipe out the entire glyph cache with all the
extracted bitmaps but only the invalidation of the texture identifiers
is needed.  This effect can be achived by calling
|hint_clear_fonts(false)|. It will call |nativeFreeTexture| for all
glyphs and set the |OGLtexture| value to zero.


The top level function to access a glyph is |hload_glyph|. Given a font pointer |fp| 
and a character code |cc| it looks up the glyph in the glyph cache.
For PK fonts, all cache entries are made when initializing the font.
For FreeType fonts, a cache entry is made when the glyph is accessed the first time.
For both types of fonts, the unpacking is done just before the first use.

@<render functions@>=
static void ft_unpack_glyph(uint8_t f, Font *fp, Gcache *g, uint32_t cc);

static Gcache *hload_glyph(uint8_t f, Font *fp, unsigned int cc)
{
  Gcache *g=NULL;
  g=g_lookup(fp,cc);
  if (g==NULL)
  { if (fp->ff==ft_format)
      g=hnew_glyph(fp,cc);
    else  
      return NULL;
  }
  if (g->ff==no_format)           
  { if (fp->ff==pk_format) pkunpack_glyph(g);
    else if (fp->ff==ft_format) ft_unpack_glyph(f,fp,g,cc);
    else QUIT("Font format not supported");
  }
  return g;
}
@

Rendering a glyph is the most complex rendering procedure. But with
all the preparations, it boils down to a pretty short function to
display a glyph, given by its charcter code |cc|, its font |f|, and
its position and size |x|, |y|, and |s| given as scaled points.  Most
of the function deals with the conversion of \TeX's measuring system,
that is scaled points stored as 32 bit integers, into a representation
that is more convenient for non \TeX{nical} sytems, namely regular
points stored as |double| values. The latter is used by the native
rendering functions.
The conversion is done by the macro |SP2PT|.
Rounding the glyph coordinates to the closes pixel boundary
makes sense only if using the native dpi, if using a multiple its of not much use.
Further, we round to pixels only if pixel size in pt is above a threshold.
We might need to export these with a setter.
Note: The function |nativeGlyphs| requires the top/left position of the
texture. It is computed from the reference point $(x,y)$ the displacement
of the bitmap $(dx,dy)$ and the height $h$. 
Further the units are points.

@<render functions@>=
static bool round_to_pixel=0;
static double dpi_threshold= 100;

#define SP2PT(X) ((X)/(double)(1<<16))

void hint_round_position(bool r, double t)
{ round_to_pixel=r;
  dpi_threshold=t;
}

static void render_char(int x, int y, uint8_t f, uint32_t cc)

{ double w, h, dx, dy, top, left;
  Font *fp;
  Gcache *g;
  fp = fonts[f];
  if (fp==NULL|| fp->resize) fp=hload_font(f);
  if (fp==NULL) return;
  g=hload_glyph(f,fp,cc);
  if (g==NULL) return;

  dx=(double)g->hoff*fp->hpxs;
  dy=(double)g->voff*fp->vpxs;@/
  w =(double)g->w*fp->hpxs;
  h =(double)g->h*fp->vpxs;
  if (g->OGLtexture==0)
    g->OGLtexture=nativeTexture(g->bits,g->w,g->h);

  left=SP2PT(x)-dx;
  top=SP2PT(y)+h-dy;

  if (round_to_pixel)
  { double pxs;
    if (xdpi<dpi_threshold)
    { pxs = 72.27/xdpi; /* pixel size in point */
      left=left/pxs;
      left=floor(left+0.5);
      left=left*pxs;
    }
    if (ydpi<dpi_threshold)
    { pxs = 72.27/ydpi; /* pixel size in point */
      top=top/pxs;
      top=floor(top+0.5);
      top=top*pxs;
    }
  }
  nativeGlyph(left,top,w,h,g->OGLtexture);
}

@
\goodbreak

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
static void render_image(int x, int y, int w, int h, uint32_t n)
{ 
  uint8_t *spos, *sstart, *send;
  spos=hpos; sstart=hstart;send=hend;
  hget_section(n);
  nativeImage(SP2PT(x),SP2PT(y),SP2PT(w),SP2PT(h),hstart,hend);
  hpos=spos; hstart=sstart;hend=send;
}
@

\subsection{Colors}
When a color node occurs on a page, we pass the new color number
to the |hSetColor| function. The |hSetColor| function, will cache
the frequently used color variables, like the current foreground color |cur_fg|,
so it is necessary to call it whenever either |cur_mode| or |cur_style|
are changing as well.
Because the background is changing infrequently, the current
background color is not cached and calls to  |nativeBackground|
must be made whenever necessary.

@<native rendering definitions@>=
extern void nativeBackground(double x, double y, double h, double w, uint32_t bg);
@

Here are the variables:

@<render variables@>=
static int cur_style=0, cur_mode=0, cur_color=0, next_style=0;
static uint32_t cur_fg;
@

For the following code it might be simpler to get the current
background color from the native renderer instead of getting the
mode and computing it.

@<handle a horizontal change in the background color@>=
if (cur_color!=list_color && (CUR_BG&0xFF)>0)
{ scaled x,y,w,h;
  x=cur_h;
  y=cur_v+depth(this_box);
  w=hcolor_distance(link(p),g_sign,g_order,glue_set(this_box));
  h=height(this_box)+depth(this_box);
  if (w>0 && h>0)
    nativeBackground(SP2PT(x),SP2PT(y),SP2PT(w),SP2PT(h),CUR_BG);
}

@

@<handle a vertical change in the background color@>=
if (cur_color!=list_color && (CUR_BG&0xFF)>0)
{ scaled x,y,w,h;
  x=left_edge;
  h=vcolor_distance(link(p),g_sign,g_order,glue_set(this_box));
  y=cur_v+h;
  w=width(this_box);
  if (w>0 && h>0)
    nativeBackground(SP2PT(x),SP2PT(y),SP2PT(w),SP2PT(h),CUR_BG);
}
@


\subsection{Pages}
Let's start with the most simple case: an empty page. We simply forward this
task to the native rendering engine. The native renderer is not part of this
document, but its reponsibilities are listed in section~\secref{native}.

@<render functions@>=
uint64_t hint_blank(void)
{ hSetColor(0);
  nativeBlank(CUR_BG);
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
width of a rule that should be output next.
|cur_color| contains the current color set;
|cur_mode| contains the current color mode;
and |cur_style| the current color style.

@<render variables@>=
static scaled cur_h, cur_v;
static scaled rule_ht, rule_dp, rule_wd; 
@

@<render functions@>=
static void vlist_render(pointer this_box);
static scaled hcolor_distance(pointer p,
    uint8_t g_sign,glue_ord g_order,glue_ratio g_set);
static scaled vcolor_distance(pointer p,
    uint8_t g_sign,glue_ord g_order,glue_ratio g_set);
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
int list_color=cur_color;
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
      { @<compute the |next_style|@>@;
        if (next_style!=cur_style)
          hSetColor(next_style);
      }
render_c:        
#ifdef DEBUG
        if(f> max_ref[font_kind])
           QUIT("Undefined Font %d mem[0x%x]=0x%x\n",
                f,p,mem[p].i);
#endif
      render_char(cur_h, cur_v, f,c);
      cur_h= cur_h+char_width(f,  c);
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
       { int cur_c=cur_color;
         cur_v= base_line+shift_amount(p);
         edge= cur_h;
         if(type(p)==vlist_node) 
           vlist_render(p);
         else 
           hlist_render(p);
         if (cur_color!=cur_c)
           hSetColor(cur_c);
         cur_h= edge+width(p);cur_v= base_line;
       }
       break;
     case rule_node:
       rule_ht= height(p);rule_dp= depth(p);rule_wd= width(p);
       goto fin_rule;
     case whatsit_node:
       switch (subtype(p))
       { case ignore_node: @<handle an ignore node@>@;break;
 	 case color_node:
           hSetColor(color_ref(p));
           @<handle a horizontal change in the background color@>@;
	   break;
 	 case end_color_node:
           hSetColor(list_color);
	   break;
         case start_link_node:
	   @<handle a start link node@>@;
 	   @<handle a horizontal change in the background color@>@;
	   break;
         case end_link_node:
	   @<handle an end link node@>@;
	   @<handle a horizontal change in the background color@>@;
	   break;
         case image_node:
         { scaled h,w;
           w=image_width(p);
           h=image_height(p);
           render_image(cur_h, cur_v, w, h,image_no(p));
           cur_h= cur_h+w; 
         } break;
         default: break;
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
          { int cur_c=cur_color;
	    cur_v= base_line+shift_amount(leader_box);
	    h_save=cur_h;
            c_ignore=true;
	    if(type(leader_box)==vlist_node)
	      vlist_render(leader_box);
	    else 
	      hlist_render(leader_box);
            if (cur_color!=cur_c)
              hSetColor(cur_c);
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
int local_link=-1;
cur_g= 0;cur_glue= float_constant(0);
int list_color=cur_color;
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
	{ int cur_c=cur_color;
	  cur_v= cur_v+height(p);save_v= cur_v;
          cur_h= left_edge+shift_amount(p);
          if(type(p)==vlist_node)
	    vlist_render(p);
	  else
            hlist_render(p);
          if (cur_color!=cur_c)
            hSetColor(cur_c); 
          cur_v= save_v+depth(p);cur_h= left_edge;
        }
        break;
      case rule_node:
	    rule_ht= height(p);rule_dp= depth(p);rule_wd= width(p);
        goto fin_rule;
      case whatsit_node:
        switch (subtype(p))
        { case color_node:
	    hSetColor(color_ref(p));
            @<handle a vertical change in the background color@>@;
	    break;
 	  case end_color_node:
            hSetColor(list_color);
	    break;
	  case start_link_node:
	    @<handle a start link node@>@;
            @<handle a vertical change in the background color@>
	    break;
          case end_link_node:
	    @<handle an end link node@>@;
            @<handle a vertical change in the background color@>
	    break;
         case image_node:
          { scaled h,w;
	    w=image_width(p);
	    h=image_height(p);
	    cur_v= cur_v+h; 
  	    render_image(cur_h, cur_v, w, h, image_no(p));
	  }
          break;
          default: break;
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
		    { int cur_c=cur_color;
		      cur_h= left_edge+shift_amount(leader_box);
		      cur_v= cur_v+height(leader_box);save_v= cur_v;
                      c_ignore=true;
		      if (type(leader_box)==vlist_node) 
		        vlist_render(leader_box);
		      else 
		        hlist_render(leader_box);
		      if (cur_color!=cur_c)
         	        hSetColor(cur_c);
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
    p= link(p);
  } /* end |while| */
} /* end |vlist_render| */

@

A simplified version of |hlist_render| is used to determine
the distance to the next color change.

@<render functions@>=
static scaled hcolor_distance(pointer p,uint8_t g_sign,glue_ord g_order,glue_ratio g_set)
{ scaled dist=0; /* the distance */
  double cur_glue=0.0; /*glue seen so far*/
  scaled cur_g=0;  /*rounded equivalent of |cur_glue| times the glue ratio*/
  double glue_temp;  /*glue value before rounding*/
  uint8_t f;
  uint32_t c;
while(p!=null)
{ if(is_char_node(p))
  { do
    { f= font(p);
      c= character(p);
character_distance:        
      dist= dist+char_width(f, c);
      p= link(p);
    } while(is_char_node(p));
  }
  else
  { switch(type(p)) 
    { case hlist_node:
      case vlist_node:
      case rule_node:
      case kern_node:
      case math_node:
        dist= dist+width(p);
        break;
      case ligature_node:
        f= font(lig_char(p));
        c= character(lig_char(p));
        goto character_distance;
      case whatsit_node:
        switch (subtype(p))
        { case start_link_node: 
          case end_link_node: 
	  case color_node:
	  case end_color_node:
	    return dist;
          case image_node:
            dist= dist+image_width(p);
            break;
          default: break;
        }
        break;
      case glue_node:
      { pointer g;
        scaled wd;
        g=glue_ptr(p);wd= width(g)-cur_g;
        if(g_sign!=normal)
        { if(g_sign==stretching)
          { if(stretch_order(g)==g_order)
            { cur_glue= cur_glue+stretch(g);
              vet_glue(g_set*cur_glue);
              cur_g= round(glue_temp);
            }
          }
          else if(shrink_order(g)==g_order)
          { cur_glue= cur_glue-shrink(g);
            vet_glue(g_set*cur_glue);
            cur_g= round(glue_temp);
          }
        }
        wd= wd+cur_g;
        dist= dist+wd;
      }
      break;
      default:;
    }
    p= link(p);
  }
} /* end |while| */
return dist;
} /* end |hcolor_distance| */

@

@<render functions@>=
static scaled vcolor_distance(pointer p,uint8_t g_sign,glue_ord g_order,glue_ratio g_set)
{ scaled dist=0; /* the distance */
  double cur_glue=0.0; /*glue seen so far*/
  scaled cur_g=0;  /*rounded equivalent of |cur_glue| times the glue ratio*/
  double glue_temp;  /*glue value before rounding*/

while(p!=null)
{ if(is_char_node(p)) DBG(DBGTEX,"Glyph in vertical list ignored");
  else
  { switch(type(p)) 
    { case hlist_node:
      case vlist_node:
      case rule_node:
 	dist= dist+height(p)+depth(p);
        break;
      case kern_node:
 	dist= dist+width(p);
        break;
      case whatsit_node:
        switch (subtype(p))
        { case start_link_node: 
          case end_link_node: 
	  case color_node:
	  case end_color_node:
	    return dist;
          case image_node:
            dist= dist+image_height(p);
            break;
          default: break;
        }
        break;
      case glue_node:
      { pointer g;
        scaled wd;
        g=glue_ptr(p);wd= width(g)-cur_g;
        if(g_sign!=normal)
        { if(g_sign==stretching)
          { if(stretch_order(g)==g_order)
            { cur_glue= cur_glue+stretch(g);
              vet_glue(g_set*cur_glue);
              cur_g= round(glue_temp);
            }
          }
          else if(shrink_order(g)==g_order)
          { cur_glue= cur_glue-shrink(g);
            vet_glue(g_set*cur_glue);
            cur_g= round(glue_temp);
          }
        }
        wd= wd+cur_g;
        dist= dist+wd;
      }
      break;
      default:;
    }
    p= link(p);
  }
} /* end |while| */
return dist;
} /* end |hcolor_distance| */

@

We conclude this section with the function that must be called after the page builder has finished
the page: the |hint_render| function.
@<render functions@>=

void hint_render(void)
{  cur_style=0;
   hSetColor(0);
   nativeBlank(CUR_BG);
   if (streams==NULL || streams[0].p==null) return;
   cur_h= 0;
   cur_v= height(streams[0].p);
   cur_link=-1; max_link=-1; last_hit_link=-1;
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


To set the size of the drawing aerea in pixel and in point call |nativeSetSize|
@<native rendering definitions@>=
extern void nativeSetSize(int px_h, int px_v, double pt_x, double pt_v);
@ 

The native renderer may implement an optional procedure to switch between dark and light mode.
The other procedure may change the $\gamma$-value.
@<native rendering definitions@>=
extern void nativeSetForeground(uint32_t fg);
extern void nativeSetGamma(double gamma);
@

To  render an empty page make sure that |hSetColor| ist called to
establish a valid color schema and then call |nativeBlank|.
@<native rendering definitions@>=
extern void nativeBlank(uint32_t bg); 
@

In the following, if not otherwise stated, all dimensions are given as double values in point.
We have $72.27\,\hbox{pt} = 1\,\hbox{inch}$ and $1\,\hbox{inch} = 2.54\, \hbox{cm}$.


To render the texture |t| with the top left point at $(|x|,|y|)$ and
with width |w| and height |h| call:
@<native rendering definitions@>=
extern void nativeGlyph(double x, double y, double w, double h,
  unsigned int t);
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

For PK fonts and FreeType fonts we need a function to translate the
glyph bitmap in |g->bits| into a device dependent representation.
@<native rendering definitions@>=
extern unsigned int nativeTexture(unsigned char *bits, int w, int h);
@

To free any native resources associated with a cached glyph |g| call:

@<native rendering definitions@>=
unsigned int nativeFreeTexture(unsigned int t);
@
This function is also called for all glyphs by the function |hint_clear_fonts|.
If the |rm| parameter to that function is |false|, the glyph cache is not deallocated
only |nativeFreeTexture| is executed for all glyphs.


\section{Font Files}

\subsection{PK Fonts}

PK Files
contain a compressed representation of bitmap fonts  produced by \MF\ and {\tt gftopk}.
The definitions and algorithms that follow here can be found,
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
#define PK_READ_1_BYTE() (pk_data[i++])
#define PK_READ_2_BYTE() (k=PK_READ_1_BYTE(),k=k<<8,k=k+pk_data[i++],k)
#define PK_READ_3_BYTE() (k=PK_READ_2_BYTE(),k=k<<8,k=k+pk_data[i++],k)
#define PK_READ_4_BYTE() (k=PK_READ_3_BYTE(),k=k<<8,k=k+pk_data[i++],k)
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
int j; /* position of next nybble in |pk_data| */
int r; /* current repeat count */
int f; /* dynamic f value */
unsigned char *pk_data; /* array of data bytes */
} PKparse;
@
Given a parse state |P|, we read the next nybble
with the following macro:

@<PK font functions@>=
#define read_nybble(P) ((P).j&1?((P).pk_data[(P).j++>>1]&0xF):(((P).pk_data[(P).j++>>1]>>4)&0xF))
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
The |pk_data| array contains the run counts and repeat counts for a bitmap of height |g->h| and
width |g->w| as a top-down bitmap, where the first bit corresponds to the
top left pixel and the last bit to the bottom right pixel.
The function will produce a bottom-up bitmap with one byte per pixel
to conform to the format that is used by the FreeType library.
We traverse the |pk_data| nybbles sequentially in top-down order.
The horizontal position |x| and the vertical position |y| in the
target bitmap start at 0 and |g->h-1|.
@<PK font functions@>=
static void pk_runlength(Gcache *g, unsigned char *pk_data) {
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
    p.pk_data=pk_data; /* data bytes */
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
The |pk_data| array contains a 1 bit per pixel bitmap of height |g->h| and
width |g->w| as a top-down bitmap, where the first bit corresponds to the
top left pixel and the last bit to the bottom right pixel.
The function will produce a bottom-up bitmap with one byte per pixel
to conform to the format that is used by the FreeType library.
We traverse the |pk_data| bits sequentially in top-down order
using a |mask| to get the next bit and incrementing |pk_data| when necessary.
The horizontal position |x| and the vertical position |y| in the
target bitmap start at 0 and |g->h-1|.
@<PK font functions@>=
static void pk_bitmap(Gcache *g, unsigned char *pk_data) {
    unsigned char *bits; /* 1 bit per pixel */
    int x, y; /* position in target bitmap */
    unsigned char mask; /* bitmask for the next bit */
 
    g->bits = bits = (unsigned char *) calloc(g->w * g->h, 1);
    if (bits == NULL) {g->w = g->h = 0; return; } /* out of memory */
    mask=0x80;
    for (y=0; y<g->h; y++)
      for (x=0; x<g->w; x++)
        { if (*pk_data & mask)
            bits[y*g->w+x] = 0x00; /* black */
          else
            bits[y*g->w+x] = 0xFF; /* white */
          mask=mask>>1;
          if (mask==0) { pk_data++; mask=0x80; }
        }
}
@

The next function unpacks the glyphs meta data and calls one of the
unpacking functions just defined.
@<PK font functions@>=

static void pkunpack_glyph(Gcache *g)
{ int i,k;
  unsigned char *pk_data;
  if (g==NULL || g->pk.encoding==NULL) return; /* no glyph, no data */
  g->ff=pk_format;
  if (g->bits!=NULL) return; /* already unpacked */
#if 0  
  DBG(DBGRENDER,"Unpacking glyph %c (0x%x)",g->cc,g->cc);
#endif 
  pk_data=g->pk.encoding;
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
  if ((g->pk.flag>>4)==14) pk_bitmap(g,pk_data+i);
  else pk_runlength(g,pk_data+i);
  g->OGLtexture=nativeTexture(g->bits,g->w,g->h);
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


static int unpack_pk_file(Font *pk)
/* scan |pk->pk_data| and extract information. Do not unpack glyphs, these are unpacked on demand. */
{   int i,j;
    unsigned int k;
	unsigned char flag;
	unsigned char *pk_data;
    pk_data=pk->font_data;
    i=0;
	while (i< pk->data_size)
	  switch(flag=pk_data[i++])
	{ case PK_XXX1: j=PK_READ_1_BYTE(); i=i+j; break;
	  case PK_XXX2: j=PK_READ_2_BYTE(); i=i+j;  break;
	  case PK_XXX3: j=PK_READ_3_BYTE(); i=i+j;  break;
	  case PK_XXX4: j=PK_READ_4_BYTE(); i=i+j;  break;
	  case PK_YYY:  i=i+4; break;
	  case PK_NO_OP: break;
	  case PK_PRE:
	  { int csize;
            double ds; /* the design size in pt */
            unsigned char id; /* the id currently allways 89 */
	    id=PK_READ_1_BYTE();
            if (id!=PK_ID) return 0;
	    csize=PK_READ_1_BYTE();
            i=i+csize; /* skip comment */
            ds=PK_READ_4_BYTE()/(double)(1<<20); /*design size in pt*/
	    i=i+4; /* skip checksum */
	    pk->hpxs=(double)(1<<16)/PK_READ_4_BYTE(); /*scaled px/pt to pt/px*/
	    pk->vpxs=(double)(1<<16)/PK_READ_4_BYTE();
	    if (ds!=pk->s) 
	    { double m=pk->s/ds;
	      pk->hpxs*=m;
	      pk->vpxs*=m;
	    }
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
		g->pk.encoding=pk_data+i;
		g->bits=NULL;
		i=i+pl;
	  }
	  break;
	}
	return 1;
}

@


\subsection{PostScript Type 1, TrueType, and OpenType Fonts}

To access font metrics that are otherwise contained in a \.{.TFM} file,
there is a collection of functions that is shared with Hi\TeX.
Make shure that any changes here are also made in  Hi\TeX.

It defines some global varaibles:

@<\HINT\ variables@>=
static FT_Library ft_library=0;
static FT_Face font_face[0x100]={NULL};
static FT_Error ft_err;


@ To initialize and destroy the Free Type library
and the array of font faces, these functions are needed:

@<FreeType font functions@>=
static void ft_init(void)
{ int i;
  if (ft_library) return;
  ft_err =  FT_Init_FreeType(&ft_library);
  if (ft_err)
    QUIT("Unable to initialize the FreeType Library.");
  for (i=0; i<0x100;i++)
    font_face[i]=NULL;
}

static void ft_destroy(void)
{ int i;
  if (ft_library==NULL) return;
  for (i=0;i<0x100;i++)
    if (font_face[i]!=NULL)
    {  ft_err= FT_Done_Face(font_face[i]); font_face[i]=NULL; }
  ft_err =  FT_Done_FreeType(ft_library);
  if (ft_err)
    MESSAGE("Error releasing the FreeType Library.");
  ft_library=NULL;
  /* this should probably go somewhere else */
  for (i=0;i<0x100;i++)
  { free(fonts[i]); fonts[i]=NULL;} 
}
@

Once the library is initialized, it is possible to
create a font face from it either from a file
using |FT_New_Face| or from memory using |FT_New_Memory_Face|.
Both functions need an index to select a font face
in case the file or memory image contains multiple
faces. The functions that follow often have such a font face
as parameter.

The first example is a function to get the ``width'' of
a character. What \TeX\ calls the ``width'' of the character
is called the ``advance'' in freetype: it is the distance
from one character to the next character including the
space between the characters; while the ``width'' of the
character is the distance between the left and right egdge
of the characters glyph. The latter is not needed by \TeX.
We give two version, one will accept a character code, the
other assumes that the glyph id is already available.

@<\HINT\ auxiliar functions@>=
#if 0
static FT_UInt ft_glyph(FT_Face ft_face, int c)
{ FT_UInt ft_gid;
  ft_gid = FT_Get_Char_Index(ft_face, c);
  return ft_gid;
}
#endif

#ifdef DEBUG
static bool ft_exists(FT_Face ft_face, int c)
{ return FT_Get_Char_Index(ft_face, c)!=0;
}
#endif

static scaled ft_glyph_width(FT_Face ft_face, FT_UInt ft_gid, scaled s)
{ FT_Fixed a;
  scaled w;
  ft_err=FT_Get_Advance(ft_face, ft_gid, FT_LOAD_NO_SCALE, &a);
  if (ft_err!=0) return 0;
  w= (scaled)((double)s*(double)a/(double)ft_face->units_per_EM +0.5);
  return w;
}

static scaled ft_width(FT_Face ft_face, int c, scaled s)
{ FT_UInt ft_gid;
  ft_gid = FT_Get_Char_Index(ft_face, c);
  if (ft_gid==0) return 0;
  return ft_glyph_width(ft_face, ft_gid, s);
}
@

Finding the height and depth of a character is
slightly more complex. It requires loading the glyph
and retrieving its bounding box.
Since most of the time we need the height and the depth
together, we provide one function for both.
We use |FT_Glyph_Get_CBox| to get the control box which is supposed to be fast.
Because the glyph has been loaded with |FT_LOAD_NO_SCALE| we call
|FT_Glyph_Get_CBox| with mode |FT_GLYPH_BBOX_UNSCALED| and
get unscaled font units in 26.6 pixel format. 

@<\HINT\ auxiliar functions@>=
static FT_Error ft_glyph_bbox(FT_Face ft_face, FT_UInt ft_gid, FT_BBox *ft_bbox)
{ FT_Glyph ft_glyph;
  ft_err = FT_Load_Glyph(ft_face, ft_gid, FT_LOAD_NO_SCALE);
  if (ft_err!=0) return ft_err;
  ft_err = FT_Get_Glyph(ft_face->glyph, &ft_glyph);
  if (ft_err!=0) return ft_err;
  FT_Glyph_Get_CBox(ft_glyph, FT_GLYPH_BBOX_UNSCALED, ft_bbox);
  return 0;
}

static void ft_glyph_height_depth(FT_Face ft_face, FT_UInt ft_gid,
  scaled *h, scaled *d, scaled s)
{ FT_BBox ft_bbox;
  *h=*d=0;
  ft_err= ft_glyph_bbox(ft_face, ft_gid, &ft_bbox);
  if (ft_err!=0)
    return;
  if (ft_bbox.yMax>0)
   *h=(scaled)((double)s*(double)(ft_bbox.yMax)/(double)ft_face->units_per_EM +0.5);
  if (ft_bbox.yMin<0)
   *d= (scaled)((double)s*(double)(-ft_bbox.yMin)/(double)ft_face->units_per_EM +0.5);
}

@




The first character of a font can be obtained using
|FT_Get_First_Char|. For now, I do not know a way to determine
the last one.

@<Unused freetype file metric functions unused@>=
static int ft_last(FT_Face ft_face)
{ return 0x10FFFF; }

static int ft_first(FT_Face ft_face)
{ FT_UInt ft_gid;
  FT_ULong c;
  c = FT_Get_First_Char(ft_face,&ft_gid);
  if (ft_gid==0) /* charmap empty*/
    return ft_last(ft_face)+1;
  else
    return c;
}
@

To unpack these fonts, we use the FreeType library\cite{freetype}.

The data type for FreeType glyphs is still empty.
@<definitions of format specific types@>=
typedef struct
{ int dummy;
} FTglyph;
@

We use |FT_New_Memory_Face| to unpack the font and initialize the |Font| structure.
To determine the rendering size, we use the function |font_at_size| to
obtain the size of the font in scaled point and convert it; the variable |f->s| then
contains the size in point as a floating point value.
The resolution used to render the font's glyphs is based on the current setting
of |xdpi| and |ydpi|. If at a later time the resolution changes, for example
because of a scaling operation, it might be necessary to rerender the fonts.
This can be achived by calling |hint_clear_fonts(true)|.

The function |load_font_face(f)| is called only if |font_face[f]==NULL|
and should be called whenever |font_face[f]| is needed but not yet defined.


@<FreeType font functions@>=

static FT_Face hload_font_face(uint8_t f)
{ int ft_err;
  Font *fp=fonts[f];
  FT_Face ft_face;
  ft_err = FT_New_Memory_Face(ft_library,
                          fp->font_data, fp->data_size,0,&ft_face);                     
  if (ft_err)
  { LOG("Unable to create font %d\n",f);
    return NULL;
  }
  font_face[f]=ft_face;
  @<Select the correct encoding@>@;
  @<Set the required size@>@;
  FT_Set_Transform(ft_face,NULL,NULL);
  return ft_face;
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
 if (width_base[f]==0)
   ft_err =FT_Select_Charmap(ft_face,FT_ENCODING_UNICODE);
 else  
 { ft_err = FT_Select_Charmap(ft_face,FT_ENCODING_ADOBE_CUSTOM); 
   if (ft_err)  ft_err =FT_Select_Charmap(ft_face,FT_ENCODING_UNICODE);
 }
 if (ft_err)  LOG("Unable to select encoding for font %d\n",fp->n);
@

We use the FreeType library to render outline fonts.
These fonts can be rendered at any
size and we need to set the correct size.
Note that FreeType needs the size in ``big points''
not \TeX\ points.

@<Set the required size@>=
   ft_err = FT_Set_Char_Size(
            ft_face,    /* handle to face object           */
            0,       /* |char_width| in $1/64$th of points  */
            (FT_F26Dot6)(0.5+(fp->s*64.0*72.0/72.27)),  /* |char_height| in $1/64$th of points */
            72.27/fp->hpxs,     /* horizontal device resolution    */
            72.27/fp->vpxs);   /* vertical device resolution      */
  if (ft_err) QUIT("Unable to set FreeType glyph size"); 
 fp->resize=false;
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

@<render functions@>=
static void ft_unpack_glyph(uint8_t f, Font *fp, Gcache *g, uint32_t cc)
{ int e,i;
  FT_Face ft_face=font_face[f];
  if (ft_face==NULL)
    ft_face=hload_font_face(f);
  if (ft_face==NULL)
   QUIT("Unable to create FreeType face for font %d (%s)",f, font_def[f].n);
  if (fp->resize)
  { fp->hpxs=72.27/xdpi;
    fp->vpxs=72.27/ydpi;
    @<Set the required size@>@;
  }
  i = FT_Get_Char_Index( ft_face, cc);
  e = FT_Load_Glyph(
            ft_face,          /* handle to face object */
            i,   /* glyph index           */
            FT_LOAD_RENDER | FT_LOAD_TARGET_NORMAL );  /* load flags, see below */
  if (e) MESSAGE("0x%xUnable to render FreeType glyph '%c' (%u)",e,(char)cc,cc);

  g->w=ft_face->glyph->bitmap.width;
  g->h=ft_face->glyph->bitmap.rows;
  g->hoff=-ft_face->glyph->bitmap_left;
  g->voff=ft_face->glyph->bitmap_top-1;
  g->bits=calloc(g->w*g->h, 1);
  if (g->bits==NULL) QUIT("Out of memory for FreeType glyph %c (%u)",(char)cc,cc);
  memcpy(g->bits,ft_face->glyph->bitmap.buffer,g->w*g->h);

  g->ff=ft_format;
  g->OGLtexture=nativeTexture(g->bits,g->w, g->h);
}

@

If the font data does not specify a PK font file, we silently assume
that it is a font file that can be handled by free type.
Here we postpone the opening of the file which is done when the
font face is first needed, either to get font metrics or font glyphs.
Opening any specific page, we do not expect to find all the fonts
available in the \HINT\ file on it. So there is no point in loading
all of them in advance.

@<determine the font format and unpack the font@>=
  else
  { fp->ff=ft_format;
    fp->hpxs=72.27/xdpi;
    fp->vpxs=72.27/ydpi;
  }
@

We close with the functions to compute font metrics.

@<FreeType font functions@>=
scaled x_char_width(uint8_t f, int c)
{ FT_Face ft_face=font_face[f];
  if (ft_face==NULL)
    ft_face=hload_font_face(f);
  if (ft_face==NULL)
    return 0;
  return ft_width(ft_face, c, font_size[f]);
}
@


\appendix


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
So the following provides some  special solutions
for Windows, Apple, and Android followed by useful defaults.

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

#ifdef __APPLE__
extern void hint_log(const char*format,...);
extern void hint_message(const char*format,...);
extern int hint_error(const char*title,const char*msg);
#define LOG(...) hint_log(__VA_ARGS__)
#define MESSAGE(...) (snprintf(hint_error_string,MAX_HINT_ERROR-1,__VA_ARGS__),\
                      hint_error("Warning",hint_error_string))
#define ERROR_MESSAGE hint_error("ERROR",hint_error_string)
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

The following variables are required for the error handling.
The |hint_error_exit| variable should be initialized before using the functions
defined below in \.{hint.h}.

@<\HINT\ variables@>=
jmp_buf hint_error_exit;
char hint_error_string[MAX_HINT_ERROR];
@


\section{Testing \HINT}\label{testing}
\subsection{Comparing \HINT\ Output to \TeX\ Output}
One objective of \HINT\ is to make the following diagram commutative:
$$\includefig{diagram}$$ 
In order to test this property of \TeX, Hi\TeX, and \HINT, we write a
command line version of \HINT, called \.{hinttype}, and run it
together with \TeX\ and Hi\TeX\ against a collection of test
files. We use |show_box| to print a page description of every page and
compare them against the page descriptions produced by \TeX\ when 
{\tt tracingoutput} is enabled.  We expect to see no significant
differences.

With the ``\.{-b}'' command line option, the test program will
generate all pages in reverse order starting at the end of the file
until reaching the beginning.

The testfile also illustrates nicely how to use the different
functions of the \TeX\ library and the \HINT\ library. Here is the
main program:

@(hinttype.c@>=
#include "basetypes.h"
#include <math.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "error.h"
#include "format.h"
#include "get.h"
#include "hint.h"
#include "rendernative.h"


@<functions required by the \HINT\ backend@>@;

int main(int argc, char *argv[])
{ char *stem_name=NULL, *prog_name=argv[0];
  int stem_length=0;
  bool option_log=false;
  int page_count=0;
  bool option_backward=false;
  int px_h, px_v;
  HINT_TRY {
    @<process the command line@>@;
    @<open the log file@>@;
    if(!hint_begin()) goto explain_usage;
    @<set the window size to match \.{\\hsize} and \.{\\vsize}@>@;
    if (option_backward)
    { hpos=hend;
      while (hint_backward()) 
      { page_count--;
        fprintf(hlog,"\nCompleted box being shipped out [%d]",page_count);
        hint_show_page();
        fprintf(hlog,"\n");
      }
    }
    else
    { while (hint_forward())
      { page_count++;
        fprintf(hlog,"\nCompleted box being shipped out [%d]",page_count);
        hint_show_page();
        fprintf(hlog,"\n");
      }
    }
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

To make the output of Hi\TeX\ plus \.{hinttype} match the output of
\TeX, it is necessary to make sure \.{hinttype} is using the same
``page size'' as \TeX.
This is acieved by combining two steps:
First, the test files use a page template setting the margins to zero,
so that \.{\\hsize} and \.{\\vsize} are the same as the page dimensions.
The second step is calling |hint_resize| to make the window size equal 
to \.{\\hsize} and \.{\\vsize}. 
We can obtain  \.{\\hsize} and \.{\\vsize} in scaled points 
from the \HINT\ file using the functions |hint_hsize| and  |hint_hsize|.
|hint_resize| needs the window size in pixels at an arbitrary choice
of the resolution in dots per inch. Because one inch equals 72.27 of
\TeX's points, a resolution of 72.27 dpi is a good choice.
It means that one pixel measures exactly one point.

@<set the window size to match \.{\\hsize} and \.{\\vsize}@>=
    px_h=floor(0.5+(hint_hsize()/(double)ONE));
    px_v=floor(0.5+(hint_vsize()/(double)ONE));
    if (px_h!=0 && px_v!=0)
      hint_resize(px_h, px_v, 72.27, 72.27);
@


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
        case 'b': option_backward=true; @+break;
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
  "\t -b     \t generate pages in backward order\n"@/
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

@<functions required by the \HINT\ backend@>=

bool hint_map(void)
{ return hget_map();
}

void hint_unmap(void)
{ hget_unmap(); 
}
@

@<test functions@>=
void hint_show_page(void)
{ show_box(streams[0].p);
}
@


\section{Finding memory leaks}
To find memory leaks, we make a table big enough for all 16 bit values (pointers)
and record a pointer with the allocated size when allocated and remove it when deallocated.
We can then list the currently allocated records.

@<\HINT\ auxiliar functions@>=
#ifdef DEBUG
static pointer leaks[1<<16] = {0};
#endif

static void leak_clear(void)
{ 
#ifdef DEBUG
  int i;
  for (i=0;i<0x10000;i++)
     leaks[i]=0;
#endif
}

static void leak_in(pointer p, int s)
{
#ifdef DEBUG 
if (0!=leaks[p])
     fprintf(stderr,"ERROR leak in: p=%d, s in=%d, leaks[p]= %d != 0\n",p,s,leaks[p]);
leaks[p]=s; 
#endif
}

static void leak_out(pointer p, int s)
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

@<\HINT\ |static|@>=
static void leak_in(pointer p, int s);
static void leak_out(pointer p, int s);
@



\section{The Source Files}

\subsection{{\tt hint.c}}
@(hint.c@>=
#include "basetypes.h"
#include <string.h>
#include <math.h>
#include <zlib.h>
@#
#include <ft2build.h>
#include <freetype/tttags.h>
#include <freetype/tttables.h>
#include <freetype/ftglyph.h>
#include <freetype/ftadvanc.h>
#include FT_FREETYPE_H
@#
#include "error.h"
#include "format.h"
#include "hint.h"
#include "rendernative.h"
#include "get.h"


@h
enum {@+@<Constants in the outer block@>@+};
@<Types in the outer block@>@;

@<\HINT\ |static|@>@;

static void hpack_page(void);
static void happend_insertion(pointer p);

@<GET macros@>@;
@<TEG macros@>@;

@<\HINT\ types@>@;
@<\HINT\ private types@>@;
@<\HINT\ variables@>@;

@<\TeX\ functions@>@;

@<\HINT\ declarations@>@;
@<\HINT\ auxiliar functions@>@;

@<get functions@>@;
@<teg functions@>@;

@<FreeType font functions@>@;


@<font functions@>@;

#ifdef HINTTYPE
/* code required to support the command line interface */
@<test functions@>@;
#else
/* code required to support a GUI */
@<render variables@>@;
@<PK font functions@>@;
@<render functions@>@;
#endif


@<\HINT\ functions@>@;

@

\subsection{{\tt hint.h}}
@(hint.h@>=
#ifndef _HRENDER_H
#define _HRENDER_H

typedef int scaled;

/*Variables and functions provided by the \HINT\ backend*/

extern int hint_begin(void);
extern void hint_end(void);
extern uint64_t hint_blank(void);
extern void     hint_render(void);
extern bool hint_forward(void);
extern bool hint_backward(void);
extern uint64_t hint_page_get(void);
extern uint64_t hint_page_top(uint64_t h);
extern uint64_t hint_page_middle(uint64_t h);
extern uint64_t hint_page_bottom(uint64_t h);
extern uint64_t hint_page(void);
extern uint64_t hint_page_next(void);
extern uint64_t hint_page_prev(void);
extern uint64_t hint_page_home(void);
extern void hint_resize(int px_h, int px_v, double xdpi, double ydpi);
extern scaled hint_hsize(void);
extern scaled hint_vsize(void);
extern void hint_clear_fonts(bool rm);
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
extern int hint_find_link(scaled x, scaled y, scaled precission);
extern uint64_t hint_link_page(int i);
extern void hint_show_page(void);
extern void hint_round_position(bool r, double t);

/*Variables and functions expected by the \HINT\ backend*/

extern bool hint_map(void);
extern void hint_unmap(void);









#endif 
@

@ @<\HINT\ |static|@>=
#ifdef DEBUG
static bool ft_exists(FT_Face ft_face, int c);
#endif
static FT_Face font_face[];
static scaled x_char_width(uint8_t f, int c);
static FT_Face hload_font_face(uint8_t f);
static scaled ft_glyph_width(FT_Face ft_face, FT_UInt ft_gid, scaled s);
static void ft_glyph_height_depth(FT_Face ft_face, FT_UInt ft_gid,
  scaled *h, scaled *d, scaled s);
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
\bibliography{../hint.bib}
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
