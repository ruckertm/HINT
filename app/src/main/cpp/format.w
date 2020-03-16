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

\input format.sty


%% defining how to display certain C identifiers

@s int8_t int
@s uint8_t int
@s int16_t int
@s uint16_t int
@s uint32_t int
@s int32_t int
@s uint64_t int
@s bool int

@

\makeindex
\maketoc
\makecode
%\makefigindex
\titletrue

\def\setrevision$#1: #2 ${\gdef\lastrevision{#2}}
\setrevision$Revision: 1879 $
\def\setdate$#1(#2) ${\gdef\lastdate{#2}}
\setdate$Date: 2020-03-16 16:31:21 +0100 (Mon, 16 Mar 2020) $

\null

\font\largetitlefont=cmssbx10 scaled\magstep4
\font\Largetitlefont=cmssbx10 at 40pt
\font\hugetitlefont=cmssbx10 at 48pt
\font\smalltitlefontit=cmbxti10 scaled\magstep3
\font\smalltitlefont=cmssbx10 scaled\magstep3

%halftitle
\hbox{}
\vskip 1in
{  \baselineskip=60pt
  \rightline{\hugetitlefont HINT:}
  \rightline{\hugetitlefont The File Format}
}
\vfill
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
  \baselineskip=1cm
  \leftline{\largetitlefont HINT: The File Format}
  \vskip 0.5in
  \leftline{\smalltitlefont Reflowable} 
  \vskip-3pt
  \leftline{\smalltitlefont Output} 
  \vskip-3pt
  \leftline{\smalltitlefont for \TeX}
  \vskip 0.5in
  \rightline{\it F\"ur meine Mutter\hskip 2cm}
  \vfill
  \leftline{\smalltitlefont Version 1.0}
  \bigskip
  \leftline{\bf MARTIN RUCKERT \ \it Munich University of Applied Sciences}
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
  HINT: The File Format
  Includes index.
  ISBN 978-1079481594
}
\bigskip

{\raggedright\advance\rightskip 3.5pc 
Internet page {\tt https://www.cs.hm.edu/\TL ruckert}
may contain current information about this book, downloadable software,
and news. 

\vfill
Copyright $\copyright$ 2019 by Martin Ruckert
\smallskip
All rights reserved.
Printed using Kindle Direct Publishing.
This publication is protected by copyright, and permission must be
obtained from the publisher prior to any prohibited reproduction, storage in
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
{\tt ruckert@@cs.hm.edu}
\medskip
%ISBN-10: 0-000-00000-0

ISBN-13: 978-1079481594
\medskip
First printing: August 2019\par
\medskip
Revision: \lastrevision,\quad Date: \lastdate\par
}
}
\endgroup


\frontmatter



\plainsection{Preface}
Late in summer 2017, with my new \CEE/ based {\tt cweb} implementation
of \TeX\cite{Knuth:tex} in hand\cite{MR:webtocweb}\cite{MR:tug38}, I started to write
the first prototype of the \HINT/ viewer. I basically made two copies
of \TeX: In the first copy, I replaced the |build_page| procedure by
an output routine which used more or less the printing routines
already available in \TeX. This was the beginning of the
\HINT/ file format.
In the second copy, I replaced \TeX's main loop by an input routine
that would feed the \HINT/ file more or less directly to \TeX's
|build_page| procedure. And after replacing \TeX's |ship_out|
procedure by a modified rendering routine of a dvi viewer that I had
written earlier for my experiments with \TeX's Computer Modern
fonts\cite{MR:tug37}, I had my first running \HINT/ viewer.  My
sabbatical during the following Fall term gave me time for ``rapid
prototyping'' various features that I considered necessary for
reflowable \TeX\ output\cite{MR:tug39}.

The textual output format derived from the original \TeX\ debugging
routines proved to be insufficient when I implemented a ``page up''
button because it did not support reading the page content
``backwards''. As a consequence, I developed a compact binary file
format that could be parsed easily in both directions. The \HINT/
short file format war born. I stopped an initial attempt at
eliminating the old textual format because it was so much nicer when
debugging. Instead, I converted the long textual format into the short
binary format as a preliminary step in the viewer. This was not a long
term solution.  When opening a big file, as produced from a 1000
pages \TeX\ file, the parsing took several seconds before the first
page would appear on screen. This delay, observed on a fast desktop
PC, is barley tolerable, and the delay one would expect on a low-cost,
low-power, mobile device seemed prohibitive.  The consequence is
simple: The viewer will need an input file in the short format; and to
support debugging (or editing), separate programs are needed to
translate the short format into the long format and back again.  But
for the moment, I did not bother to implement any of this but
continued with unrestricted experimentation.

With the beginning of the Spring term 2018, I stopped further
experiments with the \HINT/ viewer and decided that I have to write
down a clean design of the \HINT/ file format. Or of both file
formats?  Professors are supposed to do research, and hence I tried an
experiment: Instead of writing down a traditional language
specification, I decided to stick with the ``literate programming''
paradigm\cite{Knuth:lp} and write the present book.  It describes and implements
the \.{stretch} and \.{shrink} programs translating one file format
into the other.  As a side effect, it contains the underlying language
specification. Whether this experiment is a success as a language
specification remains to be seen, and you should see for yourself. But
the only important measure for the value of a scientific experiment is
how much you can learn form it---and I learned a lot.

The whole project turned out to be much more difficult than I had
expected.  Early on, I decided that I would use a recursive descent
parser for the short format and an LR($k$) parser for the long
format. Of course, I would use {\tt lex}/{\tt flex} and {\tt yacc}/{\tt bison}
to generate the LR($k$) parser, and so I had to extend the {\tt
cweb} tools\cite{Knuth:cweb} to support the corresponding source files.

About in mid May, after writing down about 100 pages, the first
problems emerged that could not be resolved with my current
approach. I had started to describe font definitions containing
definitions of the inter-word glue and the default hyphen, and the
declarative style of my exposition started to conflict with the
sequential demands of writing an output file. So it was time for a
first complete redesign.  Two more passes over the whole book were
necessary to find the concepts and the structure that would allow me
to go forward and complete the book as you see it now.

While rewriting was on its way, many ``nice ideas'' were pruned from
the book. For example, the initial idea of optimizing the \HINT/ file
while translating it was first reduced to just gathering statistics
and then disappeared completely.  The added code and complexity was
just too distracting.

What you see before you is still a snapshot of the \HINT/ file format
because its development is still under way.  We will know what
features are needed for a reflowable \TeX\ file format only after many
people have started using the format. To use the format, the end-user
will need implementations, and the implementer will need a language
specification.  The present book is the first step in an attempt to
solve this ``chicken or egg'' dilemma.


\vskip 1cm
\noindent {\it M\"unchen\hfil\break
August 20, 2019 \hfill Martin Ruckert}


\tableofcontent
%\thefigindex


\mainmatter

\section{Introduction}\label{intro}
This book defines a file format for reflowable text.
Actually it describes two file formats: a long format 
that optimizes readability for human beings, and 
a short format that optimizes readability for machines 
and storage space. Both formats use the concept of nodes and lists of 
nodes to describe the file content. Programs that process these nodes
will likely want to convert the compressed binary representation of a 
node---the short format---or the lengthy textual representation of a 
node---the long format---into a convenient internal representation.
So most of what follows is just a description of these nodes: their short format,
their long format and sometimes their internal representation.
Where as the description of the long and short external format is part
of the file specification, the description of the internal representation
is just informational. Different internal representations can be chosen
based on the individual needs of the program.

While defining the format, I illustrate the processing of long and short format 
files by implementing two utilities: \.{shrink} and \.{stretch}. 
\.{shrink} converts the long format into the short format and \.{stretch}
goes the other way.

There is also a prototype viewer for this
file format and a special version of \TeX\cite{DK:texbook} to produce output
in this format. Both are not described here; a survey describing
them can be found in \cite{MR:tug39}.

\subsection{Glyphs}
Let's start with a simple and very common kind of node: a node describing
a character.
Because we describe a format that is used to display text,
we are not so much interested in the
character itself but we are interested in the specific glyph\index{glyph}.
In typography, a glyph is a unique mark to be placed on the page representing
a character. For example the glyph representing the character `a' can have
many forms among them `{\it a\/}', `{\bf a}', or `{\tenss a}'.
Such glyphs come in collections, called fonts, representing every character
of the alphabet in a consistent way. 

The long format of a node describing the glyph `a'
 might look like this:`` \.{<glyph} \.{97} \.{*1>}''.
Here ``\.{97}'' is the character code which
happens to be the ASCII code of the letter `a' and ``{\tt *1}'' is a font reference
that stands for ``Computer Modern Roman 10pt''. 
Reference numbers, as you can see, 
start with an asterisk reminiscent of references in the \CEE/ programming language.
The Astrix enables us to distinguish between ordinary numbers like ``\.{1}'' and references like ``{\tt *1}''.

To make this node more readable, we will see in section~\secref{chars} that it is also 
possible to write `` \.{<glyph 'a' (cmr10) *1>}''.
The latter form uses a comment ``\.{(cmr10)}'', enclosed in parentheses, to
give an indication of what kind of font happens to be font 1, and it uses ``\.{'a'}'',
the character enclosed in single quotes to denote the ASCII code of `a'. 
But let's keep things simple for now and stick with the decimal notation of the character code.

The rest is common for all nodes: a keyword, here ``\.{glyph}'', and a pair of pointed brackets ``\.{<}\dots\.{>}''.

Internally, we represent a glyph by the font number
and the character number or character code. 
To store the internal representation of a glyph node, 
we define an appropriate structure type, named after the node with a trailing {\dots\bf\_t}.
@<hint types@>=
typedef struct {@+ uint32_t c;@+ uint8_t f; @+} glyph_t;
@

Let us now look at the program \.{shrink} and see how it will convert the long format description 
to the internal representation of the glyph and finally to a short format description.


\subsection{Scanning the Long Format}
First, \.{shrink} reads the input file and extract a sequence of tokens. This is called ``scanning''\index{scanning}.
We generate the procedure to do the scanning using the program \.{flex}\cite{JL:flexbison}\index{flex+{\tt flex}} which is the 
GNU version of the common UNIX tool \.{lex}\cite{JL:lexyacc}\index{lex+{\tt lex}}.

The input to \.{flex} is a list of pattern/\kern -1pt action rules where the pattern is a regular
expression and the action is a piece of \CEE/ code. 
Most of the time, the \CEE/ code is very simple: it just returns the right token\index{token} number
to the parser which we consider shortly.

The code that defines the tokens will be marked with a line ending in ``\redsymbol''.
This symbol\index{symbol} stands for ``{\it Reading the long format\/}''. 
These code sequences define the syntactical elements of the long format and at the same time
implement the reading process. All sections where that happens are preceded by a similar heading
and for reference they are conveniently listed together starting on page~\pageref{codeindex}.

\codesection{\redsymbol}{Reading the Long Format}\redindex{1}{2}{Glyphs}
@s START symbol
@s END   symbol
@s GLYPH  symbol
@s UNSIGNED   symbol
@s REFERENCE symbol

@<symbols@>=
%token START    "<"
%token END      ">"
%token GLYPH     "glyph"
%token <u> UNSIGNED
%token <u> REFERENCE   
@
You might notice that a small caps font is used for |START|, |END| or |GLYPH|.
These are  ``terminal symbols'' or ``tokens''.
Next are the scanning rules which define the connection between tokens and their
textual representation.

@<scanning rules@>=
::@="<"@>              :<     SCAN_START; return START;    >:
::@=">"@>              :<     SCAN_END; return END;      >:
::@=glyph@>             :<     return GLYPH;     >:
::@=0|[1-9][0-9]*@>    :<     SCAN_UDEC(yytext); return UNSIGNED; >:
::@=\*(0|[1-9][0-9]*)@>  :< SCAN_UDEC(yytext+1); return REFERENCE; >:
::@=[[:space:]]@>      :< ; >:
::@=\([^()\n]*[)\n]@>  :< ; >:
@

As we will see later, the macros starting with |SCAN_|\dots\ are scanning macros.
Here |SCAN_UDEC| is a macro that converts the decimal representation 
that did match the given pattern to an unsigned integer value; it is explained in
section~\secref{integers}. 
The macros |SCAN_START| and |SCAN_END| are explained in section~\secref{text}.


The action ``{\tt ;}'' is a ``do nothing'' action; here it causes spaces or comments\index{comment} 
to be ignored. Comments start with an opening parenthesis and are terminated by a 
closing parenthesis or the end of line character.
The pattern ``\.{[\^()\\n]}'' is a negated
character class that matches all characters except parentheses and the newline
character. These are not allowed inside comments. For detailed information about
the patterns used in a \.{flex} program, see the \.{flex} user manual\cite{JL:flexbison}.

\subsection{Parsing the Long Format}
\label{parse_glyph}
Next, the tokens produced by the scanner are assembled into larger entities. 
This is called ``parsing''\index{parsing}.
We generate the procedure to do the parsing using the program \.{bison}\cite{JL:flexbison}\index{bison+{\tt bison}} which is
the GNU version of the common UNIX tool \.{yacc}\cite{JL:lexyacc}\index{yacc+{\tt yacc}}.

The input to \.{bison} is a list of parsing rules, called a ``grammar''\index{grammar}.
The rules describe how to build larger entities from smaller entities.
For a simple glyph node like `` \.{<glyph 97 *1>}'', we need just these rules:
\codesection{\redsymbol}{Reading the Long Format}%\redindex{1}{2}{Glyphs}
@s content_node symbol
@s node symbol
@s glyph symbol
@s glyph_t int
@s start symbol
@<symbols@>=
%type <u> start
%type <c> glyph
@

@<parsing rules@>=@/
glyph: UNSIGNED REFERENCE  @/{ $$.c=$1; REF(font_kind,$2); $$.f=$2; };
content_node: start GLYPH glyph END { hput_tags($1,hput_glyph(&($3))); };
start: START {HPUTNODE; $$=(uint32_t)(hpos++-hstart);}
@

You might notice that a slanted font is used for |glyph|, |content_node|, or |start|. 
These are ``nonterminal symbols' and occur on the left hand side of a rule. On the
right hand side of a rule you find nonterminal symbols, as well as terminal\index{terminal symbol} symbols 
and \CEE/ code enclosed in braces.

Within the \CEE/ code, the expressions |$1| and |$2| refer to the variables on the parse stack
that are associated with the first and second symbol on the right hand side of the rule.
In the case of our glyph node, these will be the values 97 and 1, respectively, as produced 
by the macro |SCAN_UDEC|.  
|$$| refers to the variable associated with the left hand side of the rule. 
These variables contain the internal representation of the object in question. 
The type of the variable is specified by a mandatory {\bf token} or optional {\bf type} clause 
when we define the symbol. 
In the above {\bf type} clause for |start| and |glyph| , the identifiers |u| and |c| refer to 
the |union| declaration of the parser (see page~\pageref{union})
where we find |uint32_t u| and |glyph_t c|. The macro |REF| tests a reference number for
its valid range.


Reading a node is usually split into the following sequence of steps: 
\itemize
\item Reading the node specification, here a |glyph| 
      consisting of an |UNSIGNED| value and a |REFERENCE| value.
\item Creating the internal representation in the variable |$$|
      based on the values of |$1|, |$2|, \dots\ Here the character
      code field |c| is initialized using  the |UNSIGNED| value
       stored in |$1| and the font field |f| is initialized using
      |$2| after checking the reference number for the proper range.
\item A |content_node| rule explaining that |start| is followed by |GLYPH|, 
      the keyword that directs the parser  to |glyph|, the 
      node specification, and a final |END|.
\item Parsing |start|, which is defined as the token |START| will assign 
      to the corresponding variable |p| on the parse stack the current
      position |hpos| in the output and increments that position
      to make room for the start byte, which we will discuss shortly.
\item At the end of the |content_node| rule, the \.{shrink} program calls
      a {\it hput\_\dots\/} function, here |hput_glyph|, to write the short
      format of the node as given by its internal representation to the output
      and return the correct tag value.
\item Finally the |hput_tags| function will add the tag as a start byte and end byte 
      to the output stream.
\enditemize

Now let's see how writing the short format works in detail.

  
\subsection{Writing the Short Format}
A content node in short form begins with a start\index{start byte} byte. It tells us what kind of node it is.
To describe the content of a short \HINT/ file, 32 different kinds\index{kind} of nodes are defined.
Hence the kind of a node can be stored in 5 bits and the remaining bits of the start byte
can be used to contain a 3 bit ``info''\index{info} value. 

We define an enumeration type to give symbolic names to the kind values.
The exact numerical values are of no specific importance;
we will see in section~\secref{text}, however, that the assignment chosen below,
has certain advantages.
 
Because the usage of kind values in content nodes is 
slightly different from the usage in definition nodes, we define alternative names for some kind values.
To display readable names instead of numerical values when debugging,
we define two arrays of strings as well. Keeping the definitions consistent
is achieved by creating all definitions from the same list
of identifiers using different definitions of the macro |DEF_KIND|.

@<hint basic types@>=
#define DEF_KIND(C,D,N) @[C##_kind=N@]
typedef enum {@+@<kinds@>@+,@+ @<alternative kind names@> @+} kind_t;
#undef DEF_KIND
@

@<define |content_name| and |definition_name|@>=
#define DEF_KIND(C,D,N) @[#C@]
const char *content_name[32]=@+{@+@<kinds@>@;@+}@+;
#undef DEF_KIND@#
printf("const char *content_name[32]={");
for (k=0; k<= 31;k++)
{ printf("\"%s\"",content_name[k]);
  if (k<31) printf(", ");
}
printf("};\n\n");

#define DEF_KIND(C,D,N) @[#D@]
const char *definition_name[0x20]=@+{@+@<kinds@>@;@+}@+;
#undef DEF_KIND
printf("const char *definition_name[32]={");
for (k=0; k<= 31;k++)
{ printf("\"%s\"",definition_name[k]);
  if (k<31) printf(", ");
}
printf("};\n\n");

@ 

\goodbreak
\index{glyph kind+\\{glyph\_kind}}
\index{font kind+\\{font\_kind}}
\index{penalty kind+\\{penalty\_kind}}
\index{int kind+\\{int\_kind}}
\index{kern kind+\\{kern\_kind}}
\index{xdimen kind+\\{xdimen\_kind}}
\index{ligature kind+\\{ligature\_kind}}
\index{hyphen kind+\\{hyphen\_kind}}
\index{glue kind+\\{glue\_kind}}
\index{math kind+\\{math\_kind}}
\index{rule kind+\\{rule\_kind}}
\index{image kind+\\{image\_kind}}
\index{baseline kind+\\{baseline\_kind}}
\index{dimen kind+\\{dimen\_kind}}
\index{hbox kind+\\{hbox\_kind}}
\index{vbox kind+\\{vbox\_kind}}
\index{par kind+\\{par\_kind}}
\index{display kind+\\{display\_kind}}
\index{table kind+\\{table\_kind}}
\index{item kind+\\{item\_kind}}
\index{hset kind+\\{hset\_kind}}
\index{vset kind+\\{vset\_kind}}
\index{hpack kind+\\{hpack\_kind}}
\index{vpack kind+\\{vpack\_kind}}
\index{stream kind+\\{stream\_kind}}
\index{page kind+\\{page\_kind}}
\index{range kind+\\{range\_kind}}
\index{adjust kind+\\{adjust\_kind}}
\index{param kind+\\{param\_kind}}
\index{text kind+\\{text\_kind}}
\index{list kind+\\{list\_kind}}
\label{kinddef}
@<kinds@>=
DEF_KIND(t@&ext,t@&ext,0),@/
DEF_KIND(l@&ist,l@&ist,1),@/
DEF_KIND(p@&aram,p@&aram,2),@/
DEF_KIND(x@&dimen,x@&dimen,3),@/
DEF_KIND(a@&djust,a@&djust,4),@/
DEF_KIND(g@&lyph, f@&ont,5),@/
DEF_KIND(k@&ern,d@&imen,6),@/
DEF_KIND(g@&lue,g@&lue,7),@/
DEF_KIND(l@&igature,l@&igature,8),@/
DEF_KIND(h@&yphen,h@&yphen,9),@/
DEF_KIND(m@&ath,m@&ath,10),@/
DEF_KIND(r@&ule,r@&ule,11),@/
DEF_KIND(i@&mage,i@&mage,12),@/
DEF_KIND(l@&eaders,l@&eaders,13),@/
DEF_KIND(b@&aseline,b@&aseline,14),@/
DEF_KIND(h@&b@&ox,h@&b@&ox,15),@/
DEF_KIND(v@&b@&ox,v@&b@&ox,16),@/
DEF_KIND(p@&ar,p@&ar,17),@/
DEF_KIND(d@&isplay,d@&isplay,18),@/
DEF_KIND(t@&able,t@&able,19),@/
DEF_KIND(i@&tem,i@&tem,20),@/
DEF_KIND(h@&set,h@&set,21),@/
DEF_KIND(v@&set,v@&set,22),@/
DEF_KIND(h@&pack,h@&pack,23),@/
DEF_KIND(v@&pack,v@&pack,24),@/
DEF_KIND(s@&tream,s@&tream,25),@/
DEF_KIND(p@&age,p@&age,26),@/
DEF_KIND(r@&ange,r@&ange,27),@/
DEF_KIND(u@&ndefined1,u@&ndefined1,28),@/
DEF_KIND(u@&ndefined2,u@&ndefined2,29),@/
DEF_KIND(u@&ndefined3,u@&ndefined3,30),@/
DEF_KIND(p@&enalty, i@&nt,31)
@t@>
@

For a few kind values we have
alternative names; we will use them in the definition section 
to express different intentions when using them.
@<alternative kind names@>=
font_kind=glyph_kind,int_kind=penalty_kind, dimen_kind=kern_kind@/@t{}@>
@

The info\index{info value} values can be used to represent numbers in the range 0 to 7; for an example
see the |hput_glyph| function later in this section.
Mostly, however, the individual bits are used as flags indicating the presence
or absence of immediate parameter values. If the info bit is set, it
means the corresponding parameter is present as an immediate value; if it
is zero, it means that there is no immediate parameter value present, and
the node specification will reveal what value to use instead.
In some cases there is a common default value that can be used, in other
cases a one byte reference number is used to select a predefined value. 

To make the binary
representation of the info bits more readable, we define an
enumeration type.

\index{b000+\\{b000}}
\index{b001+\\{b001}}
\index{b010+\\{b010}}
\index{b011+\\{b011}}
\index{b100+\\{b100}}
\index{b101+\\{b101}}
\index{b110+\\{b110}}
\index{b111+\\{b111}}
@<hint basic types@>=
typedef enum {@+ b000=0,b001=1,b010=2,b011=3,b100=4,b101=5,b110=6,b111=7@+ } info_t;
@


After the start byte follows the node content and it is the purpose of
the start byte to reveal the exact syntax and semantics of the node
content. Because we want to be able to read the short form of a \HINT/
file in forward direction and in backward direction, the start byte is
duplicated after the content as an end\index{end byte} byte.


We store a kind and an info value in one byte and call this a tag.
The following macros are used to assemble and disassemble tags:\index{TAG+\.{TAG}}
@<hint macros@>=
#define @[KIND(T)@]      (((T)>>3)&0x1F)
#define @[NAME(T)@]      @[content_name[KIND(T)]@]
#define @[INFO(T)@]      ((T)&0x7)
#define @[TAG(K,I)@]     (((K)<<3)|(I))
@

Writing a  short format \HINT/ file is implemented by a collection of {\it hput\_\kern 1pt\dots\/}  functions; 
they follow most of the time the same schema:
\itemize
\item First, we define a variable for |info|.
\item Then follows the main part of the function body, where we 
decide on the output format, do the actual output and set the |info| value accordingly.
\item We combine the info value with the kind value and return the correct tag.
\item The tag value will be passed to |hput_tags| which generates
debugging information, if requested, and stores the tag before and after the node content.
\enditemize


After these preparations, we turn our attention again to the |hput_glyph| function.

The font number in a glyph node is between 0 and 255 and fits nicely in one byte,
but the character code is more difficult: we want to store the most common character
codes as a single byte and less frequent codes with two, three, or even four byte. 
Naturally, we use the |info| bits to store the number of bytes needed for the character code. 

\codesection{\putsymbol}{Writing the Short Format}\putindex{1}{2}{Glyphs}
@<put functions@>=
uint8_t hput_glyph(glyph_t *g)
{ info_t info;
  if (g->c<=0xFF) @+
  {@+HPUT8(g->c);@+ info=1;@+}
  else if (g->c<=0xFFFF) @+
  {@+HPUT16(g->c);@+ info=2;@+}
  else if (g->c<=0xFFFFFF)@+ 
  {@+HPUT24(g->c);@+ info=3;@+}
  else @+
  {@+HPUT32(g->c);@+ info=4;@+}
  HPUT8(g->f);@/
  return TAG(glyph_kind,info);
}
@
The |hput_tags| function is called after the node content has been written to the
stream. It gets a the position of the start byte and the tag. With this information
it writes the start byte at the given position and the end byte at the current stream position.
@<put functions@>=
void hput_tags(uint32_t pos, uint8_t tag)
{ DBGTAG(tag,hstart+pos);DBGTAG(tag,hpos);
  HPUTX(1); *(hstart+pos)=*(hpos++)=tag; @+
}
@



The variables |hpos| and |hstart|, the 
macros  |HPUT8|, |HPUT16|, |HPUT24|, |HPUT32|, and  |HPUTX| are all defined in section~\secref{HPUT};
they put 8, 16, 24, or 32 bits into the output stream and check for sufficient space in the output buffer.
The macro |DBGTAG| writes debugging output; its definition is found in section~\secref{error_section}.

Now that we have seen the general outline of the \.{shrink} program, starting with a long format file
and ending with a short format file, we will look at the program \.{stretch} that reverses this transformation.


\subsection{Parsing the Short Format}
The inverse of writing the short format with a {\it hput\_\kern 1pt\dots\/}  function
is reading the short format with a {\it hget\_\kern 1pt\dots\/}  function.

The schema of  {\it hget\_\kern 1pt\dots\/}  functions reverse the schema of  {\it hput\_\kern 1pt\dots\/}  functions.
Here is the code for the initial and final part of a get function:

@<read the start byte |a|@>=
uint8_t a,z; /* the start and the end byte*/
uint32_t node_pos=hpos-hstart;
if (hpos>=hend) QUIT("Attempt to read a start byte at the end of the section");
HGETTAG(a);
@

@<read and check the end byte |z|@>=
HGETTAG(z);@+
if (a!=z)
  QUIT(@["Tag mismatch [%s,%d]!=[%s,%d] at 0x%x to " SIZE_F "\n"@],@|
    NAME(a),INFO(a),NAME(z),INFO(z),@|node_pos, hpos-hstart-1);
@


The central routine to parse\index{parsing} the content section of a short format
file is the function |hget_content_node| which calls |hget_content| to
do most of the processing.

|hget_content_node| will read a content node in short format and write
it out in long format: It reads the start\index{start byte} byte |a|, writes the |START|
token using the function |hwrite_start|, and based on |KIND(a)|, it
writes the nodes' keyword found in the |content_name| array.  Then it
calls |hget_content| to read the nodes content and write it out.
Finally it reads the end\index{end byte} byte, checks it against the start byte, and
finishes up the content node by writing the |END| token using the
|hwrite_end| function.

|hget_content| uses the start byte |a|, passed as a parameter, to
branch directly to the reading routine for the given combination of
kind and info value.  The reading routine will read the data and store
its internal representation in a variable.  All that the \.{stretch}
program needs to do with this internal representation is writing it in
the long format. As we will see, the call to the proper 
{\it hwrite\_\kern 1pt\dots} function is included as final part of the the
reading routine (avoiding another switch statement).


\codesection{\getsymbol}{Reading the Short Format}\getindex{1}{2}{Content Nodes}
@<get functions@>=
void hget_content_node(void)
{ @<read the start byte |a|@>@;@+ hwrite_start();
  hwritef("%s",content_name[KIND(a)]);
  hget_content(a);
  @<read and check the end byte |z|@>@;@+ hwrite_end();
}

void hget_content(uint8_t a)
{@+  uint32_t node_pos=hpos-hstart;
  switch (a)@/
  { 
    @<cases to get content@>@;@t\1@>@/
    default:
      TAGERR(a);
      break;@t\2@>@/
  }
}
@

We implement the code to read a glyph node in two stages.
First we define a general reading macro |HGET_GLYPH(I,G)| that reads a glyph node with info value |I| into
a |glyph_t| variable |G|; then we insert this macro
in the above switch statement for all cases where it applies.
Knowing the function |hput_glyph|, the macro |HGET_GLYPH| should not be a surprise.
It reverses |hput_glyph|, storing the glyph node in its internal representation.
After that, the \.{stretch} program calls |hwrite_glyph| to produce the glyph
node in long format.

\codesection{\getsymbol}{Reading the Short Format}\getindex{1}{2}{Glyphs}
@<get macros@>=
#define @[HGET_GLYPH(I,G)@] \
  if (I==1) (G).c=HGET8;\
  else if (I==2) HGET16((G).c);\
  else if (I==3) HGET24((G).c);\
  else if (I==4) HGET32((G).c);\
  (G).f=HGET8; @+REF(font_kind,(G).f);@/\
  hwrite_glyph(&(G));\
@

@<cases to get content@>=
case TAG(glyph_kind,1): @+{@+glyph_t g;@+ HGET_GLYPH(1,g);@+}@+break;
case TAG(glyph_kind,2): @+{@+glyph_t g;@+ HGET_GLYPH(2,g);@+}@+break;
case TAG(glyph_kind,3): @+{@+glyph_t g;@+ HGET_GLYPH(3,g);@+}@+break;
case TAG(glyph_kind,4): @+{@+glyph_t g;@+ HGET_GLYPH(4,g);@+}@+break;
@

If this two stage method seems strange to you, consider what the \CEE/ compiler will
do with it. It will expand the |HGET_GLYPH| macro four times inside the switch
statement. The macro is, however, expanded with a constant |I| value, so the expansion
of the |if| statement in |HGET_GLYPH(1,g)|, for example, 
will become ``|if (1==1)| \dots\ |else if (1==2)| \dots'' 
and the compiler will have no difficulties eliminating the constant tests and
the dead branches altogether. This is the most effective use of the switch statement:
a single jump takes you to a specialized code to handle just the given combination
of kind and info value.

Last not least, we implement the function |hwrite_glyph| to write a
glyph node in long form---that is: in a form that is as readable as possible.

\subsection{Writing the Long Format}

The |hwrite_glyph| function inverts the scanning and parsing process we have described
at the very beginning of this chapter.
To implement the |hwrite_glyph| function, we use the function |hwrite_charcode|
to write the character code.
Besides writing the character code as a decimal number, this function can handle also other
representations of character codes as fully explained in section~\secref{chars}.
We split off the writing of the opening and the closing pointed bracket, because
we will need this function very often and because it will keep track of the |nesting|
of nodes and indent them accordingly. The |hwrite_range| function used in |hwrite_end|
is discussed in section~\secref{range}.

\codesection{\wrtsymbol}{Writing the Long Format}\wrtindex{1}{2}{Glyphs}
@<write functions@>=
int nesting=0;
void hwrite_nesting(void)
{ int i;
  hwritec('\n');
  for (i=0;i<nesting;i++) hwritec(' ');
}

void hwrite_start(void)
{ @+hwrite_nesting();@+  hwritec('<');@+ nesting++;
}

void hwrite_end(void)
{ nesting--; hwritec('>'); 
 if (nesting==0 && section_no==2) hwrite_range();
}

void hwrite_comment(char *str)
{ char c;
  if (str==NULL) return;
  hwritef(" (");
  while ((c=*str++)!=0)
   if (c=='(' || c==')') hwritec('_');
   else if (c=='\n') hwritef("\n(");
   else hwritec(c);
  hwritec(')');
}

void hwrite_glyph(glyph_t *g)
{ char *n=hfont_name[g->f];
  hwrite_charcode(g->c);
  hwritef(" *%d",g->f);
  if (n!=NULL) hwrite_comment(n);
}
@

Now that we have completed the round trip of shrinking and stretching
glyph nodes, we continue the description of the \HINT/ file formats
in a more systematic way. 


\section{Data Types}\hascode
\subsection{Integers}
\label{integers}
We have already seen the pattern/\kern -1pt action rule for unsigned decimal\index{decimal number} numbers. It remains
to define the macro |SCAN_UDEC| which converts a string containing an unsigned\index{unsigned} decimal 
number into an unsigned integer\index{integer}.
We use the \CEE/ library function | strtoul|:
\readcode
@<scanning macros@>=
#define @[SCAN_UDEC(S)@] @[yylval.u=strtoul(S,NULL,10)@]
@

Unsigned integers can be given in hexadecimal\index{hexadecimal} notation as well. 
@<scanning definitions@>=
::@=HEX@>  :<  @=[0-9A-F]@>  >:
@

@<scanning rules@>=
::@=0x{HEX}+@>           :<     SCAN_HEX(yytext+2); return UNSIGNED; >:
@

Note that the pattern above allows only upper case letters in the 
hexadecimal notation for integers.

@<scanning macros@>=
#define @[SCAN_HEX(S)@] @[yylval.u=strtoul(S,NULL,16)@]
@

Last not least, we add rules for signed\index{signed integer} integers.
@s SIGNED   symbol
@s number   symbol
@s integer  symbol

@<symbols@>=
%token <i> SIGNED
%type <i> integer
@

@<scanning rules@>=
::@=[+-](0|[1-9][0-9]*)@>    :<     SCAN_DEC(yytext); return SIGNED; >:
@

@<scanning macros@>=
#define @[SCAN_DEC(S)@] @[yylval.i=strtol(S,NULL,10)@]
@

@<parsing rules@>=
integer: SIGNED @+| UNSIGNED { RNG("number",$1,0,INT32_MAX);};
@

To preserve the ``signedness'' of an integer also for positive signed integers
in the long format, we implement the function |hwrite_signed|.

\writecode
@<write functions@>=
void hwrite_signed(int32_t i)
{ if (i<0) hwritef(" -%d",-i);
  else hwritef(" +%d",+i);
}
@

Reading and writing integers in the short format is done directly with the {\tt HPUT} and {\tt HGET}
macros.


\subsection{Strings}
\label{strings}
Strings\index{string} are needed in the definition part of a \HINT/ 
file to specify names of objects, and in the long file format, we also use them for file\index{file name} names.
In the long format, strings are sequences of characters delimited by single quote\index{single quote} characters; 
for example: ``\.{'Hello'}'' or ``\.{'cmr10-600dpi.tfm'}''; in the short format, strings are
byte sequences terminated by a zero byte.
Because file names are system dependent, we no not allow arbitrary characters in strings 
but only printable ASCII codes which we can reasonably expect to be available on most operating systems. 
If your file names in a long format \HINT/ file are supposed to be portable, 
you should probably be even more restrictive. For example you should avoid characters like
``\.{\\}'' or ``\.{/}'' which are used in different ways for directories.

The internal representation of a string is a simple zero terminated \CEE/ string.
When scanning a string, we copy it to the |str_buffer| keeping track
of its length in |str_length|. When done,
we make a copy for permanent storage and return the pointer to the parser.
To operate on the |str_buffer|, we define a few macros.
The constant |MAX_STR| determines the maximum size of a string (including the zero byte) to be $2^{10}$ byte.
This restriction is part of the \HINT/ file format specification.

@<scanning macros@>=
#define MAX_STR    (1<<10) /* $2^{10}$ Byte or 1kByte */
static char str_buffer[MAX_STR];
static int str_length;
#define STR_START      @[(str_length=0)@]
#define @[STR_PUT(C)@] @[(str_buffer[str_length++]=(C))@]
#define @[STR_ADD(C)@] @[STR_PUT(C);RNG("String length",str_length,0,MAX_STR-1)@]
#define STR_END        @[str_buffer[str_length]=0@]
#define SCAN_STR       @[yylval.s=str_buffer@]
@


To scan a string, we switch the scanner to |STR| mode when we find a quote character,
then we scan bytes in the range |0x20| to |0x7E|, which is the range of printable ASCII
characters, until we find the closing single\index{single quote} quote. Quote characters inside the string
are written as two consecutive single quote characters.

\readcode
@s STRING symbol
@s STR symbol
@s INITIAL symbol

@<scanning definitions@>=
%x STR
@

@<symbols@>=
%token <s> STRING
@

@<scanning rules@>=
::@='@>       :< STR_START; BEGIN(STR); >:
<STR>{
::@='@>             :< STR_END; SCAN_STR; BEGIN(INITIAL); return STRING; >:
::@=''@>            :< STR_ADD('\''); >:
::@=[\x20-\x7E]@>   :< STR_ADD(yytext[0]); >:
::@=.|\n@>          :< RNG("String character",yytext[0],0x20,0x7E); >:
}
@

The function |hwrite_string| reverses this process; it must take care of the quote symbols.
\writecode
@<write functions@>=
void hwrite_string(char *str)
{@+hwritec(' '); 
  if (str==NULL) hwritef("''");
  else@/
  { hwritec('\''); 
    while (*str!=0)@/
    { @+if (*str=='\'') hwritec('\'');
      hwritec(*str++);
    }
    hwritec('\''); 
  } 
}
@

In the short format, a string is just a byte sequence terminated by a zero byte.
This makes the function |hput_string|, to write a string, and the macro |HGET_STRING|,
to read a string in short format, very simple. Note that after writing an unbounded
string to the output buffer, the macro |HPUTNODE| will make sure that there is enough
space left to write the remainder of the node.

\putcode
@<put functions@>=
void hput_string(char *str)
{ char *s=str;
  if (s!=NULL)
  { do {
      HPUTX(1);
      HPUT8(*s);
    } while (*s++!=0);
    HPUTNODE;
  }
  else HPUT8(0);
}
@ 

\getcode
@<get file macros@>=
#define @[HGET_STRING(S)@] @[S=(char*)hpos;\
 while(hpos<hend && *hpos!=0) { RNG("String character",*hpos,0x20,0x7E); hpos++;}\
 hpos++;
@

\subsection{Character Codes}
\label{chars}    
We have already seen in the introduction that character\index{character code} codes can be written as decimal numbers
and section~\secref{integers} adds the possibility to use hexadecimal numbers as well.

It is, however, in most cases more readable if we represent character codes directly
using the characters themselves. Writing ``\.{a}'' is just so much better than writing ``\.{97}''.
To distinguish the character ``\.{9}'' from the number ``\.{9}'', we use the common technique
of enclosing characters within single\index{single quote} quotes. So ``\.{'9'}'' is the character code and
``\.{9}'' is the number. 
Therefore we will define |CHARCODE| tokens and complement the parsing rules of section~\secref{parse_glyph}
with the following rule:
\readcode
@<parsing rules@>=
glyph: CHARCODE REFERENCE  @|{ $$.c=$1; REF(font_kind,$2); $$.f=$2; };
@



If the character codes are small, we can represent them using
ASCII character codes. We do not offer a special notation for very small
character codes that map to the non-printable ASCII control codes; for them, the decimal
or hexadecimal notation will suffice.
For larger character codes, we use the multibyte encoding scheme known from UTF8\index{UTF8} as
follows. Given a character code~|c|:

\itemize
\item
Values in the range |0x00| to |0x7f| are encoded as a single byte with a leading bit of 0.

@<scanning definitions@>=
::@=UTF8_1@>  :<  @=[\x00-\x7F]@>  >:
@
@<scanning macros@>=
#define @[SCAN_UTF8_1(S)@]   @[yylval.u=((S)[0]&0x7F)@]
@


\item
Values in the range |0x80| to |0x7ff| are encoded in two byte with the first byte
having three high bits |110|, indicating a two byte sequence, and the lower five bits equal
to the five high bits of |c|. It is followed by a continuation byte having two high bits |10|
and the lower six bits
equal to the lower six bits of |c|.

@<scanning definitions@>=
::@=UTF8_2@>  :<  @=[\xC0-\xDF][\x80-\xBF]@>  >:
@

@<scanning macros@>=
#define @[SCAN_UTF8_2(S)@]   @[yylval.u=(((S)[0]&0x1F)<<6)+((S)[1]&0x3F)@]
@

\item
Values in the range |0x800| to |0xFFFF| are encoded in three byte with the first byte
having the high bits |1110| indicating a three byte sequence followed by two continuation bytes.

@<scanning definitions@>=
::@=UTF8_3@>  :< @=[\xE0-\xEF][\x80-\xBF][\x80-\xBF]@> >:
@

@<scanning macros@>=
#define @[SCAN_UTF8_3(S)@]   @[yylval.u=(((S)[0]&0x0F)<<12)+(((S)[1]&0x3F)<<6)+((S)[2]&0x3F)@]
@

\item
Values in the range |0x1000| to |0x1FFFFF| are encoded in four byte with the first byte
having the high bits |11110| indicating a four byte sequence followed by three continuation bytes.

@<scanning definitions@>=
::@=UTF8_4@>  :< @=[\xF0-\xF7][\x80-\xBF][\x80-\xBF][\x80-\xBF]@> >:
@

@<scanning macros@>=
#define @[SCAN_UTF8_4(S)@]   @[yylval.u=(((S)[0]&0x03)<<18)+(((S)[1]&0x3F)<<12)+@|(((S)[2]&0x3F)<<6)+((S)[3]&0x3F)@]
@

\enditemize

In the long format file, we enclose a character code in single\index{single quote} quotes, just as we do for strings.
This is convenient but it has the downside that we must exercise special care when giving the 
scanning rules in order
not to confuse character codes with strings. Further we must convert character codes back into strings
in the rare case where the parser expects a string and gets a character code because the string
was only a single character long. 

Let's start with the first problem:
The scanner might confuse a string\index{string} and a character code if the first or second
character of the string is a quote character which is written as two consecutive quotes.
For example \.{'a''b'} is a string with three characters, ``\.{a}'',
``\.{'}'', and ``\.{b}''. Two character codes would need a space to separate
them like this: \.{'a' 'b'}.


@s CHARCODE  symbol
@<symbols@>=
%token <u> CHARCODE      
@

@<scanning rules@>=
::@='''@>          :< STR_START; STR_PUT('\''); BEGIN(STR); >:
::@=''''@>         :< SCAN_UTF8_1(yytext+1); return CHARCODE; >: 
::@='[\x20-\x7E]''@>   :< STR_START; STR_PUT(yytext[1]); STR_PUT('\''); BEGIN(STR); >:
::@='''''@>        :< STR_START; STR_PUT('\''); STR_PUT('\''); BEGIN(STR); >:
::@='{UTF8_1}'@>   :< SCAN_UTF8_1(yytext+1); return CHARCODE; >: 
::@='{UTF8_2}'@>   :< SCAN_UTF8_2(yytext+1); return CHARCODE; >: 
::@='{UTF8_3}'@>   :< SCAN_UTF8_3(yytext+1); return CHARCODE; >: 
::@='{UTF8_4}'@>   :< SCAN_UTF8_4(yytext+1); return CHARCODE; >: 
@

If needed, the parser can convert character codes back to single character strings.

@s string symbol

@<symbols@>=
%type <s> string
@

@<parsing rules@>=
string: STRING @+ | CHARCODE { static char s[2]; 
                   RNG("String element",$1,0x20,0x7E); 
                   s[0]=$1; s[1]=0; $$=s;};
@


The function |hwrite_charcode| will write a character code. While ASCII codes are handled directly,
larger character codes are passed to the function |hwrite_utf8|.
It returns the number of characters written.

\writecode
@<write functions@>=
int hwrite_utf8(uint32_t c)
{@+ if (c<0x80) 
  {  hwritec(c); return 1; }
  else if (c<0x800)
  { hwritec(0xC0|(c>>6));@+ hwritec(0x80|(c&0x3F));@+ return 2;} 
  else if (c<0x10000)@/
  { hwritec(0xE0|(c>>12)); hwritec(0x80|((c>>6)&0x3F));@+ hwritec(0x80|(c&0x3F)); return 3; } 
  else if (c<0x200000)@/
  { hwritec(0xF0|(c>>18));@+ hwritec(0x80|((c>>12)&0x3F)); 
    hwritec(0x80|((c>>6)&0x3F));@+ hwritec(0x80|(c&0x3F)); return 4;} 
  else
   RNG("character code",c,0,0x1FFFFF);
  return 0;
} 

void hwrite_charcode(uint32_t c)
{ @+if (c < 0x20) 
  { if (option_hex) hwritef(" 0x%02X",c); /* non printable ASCII */
    else  hwritef(" %u",c);
  }
  else if (c=='\'') hwritef(" ''''");
  else if (c<=0x7E) hwritef(" \'%c\'",c); /* printable ASCII */
  else if (option_utf8) { hwritef(" \'"); @+ hwrite_utf8(c); @+ hwritec('\'');@+}
  else if (option_hex)  hwritef(" 0x%04X",c); 
  else  hwritef(" %u",c);
}
@

\getcode
@<get functions@>=
#define @[HGET_UTF8C(X)@]  (X)=HGET8;@+ if ((X&0xC0)!=0x80) \
  QUIT(@["UTF8 continuation byte expected at " SIZE_F " got 0x%02X\n"@],hpos-hstart-1,X)@;

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
\putcode
@<put functions@>=
void hput_utf8(uint32_t c)
{ @+HPUTX(4); 
  if (c<0x80) 
    HPUT8(c);
  else if (c<0x800)
  { HPUT8(0xC0|(c>>6));@+ HPUT8(0x80|(c&0x3F));@+ } 
  else if (c<0x10000)@/
  { HPUT8(0xE0|(c>>12)); HPUT8(0x80|((c>>6)&0x3F));@+ HPUT8(0x80|(c&0x3F)); } 
  else if (c<0x200000)@/
  { HPUT8(0xF0|(c>>18));@+ HPUT8(0x80|((c>>12)&0x3F)); 
    HPUT8(0x80|((c>>6)&0x3F));@+ HPUT8(0x80|(c&0x3F)); } 
  else
   RNG("character code",c,0,0x1FFFFF);
}
@

\subsection{Floating Point Numbers}
You know a floating point numbers\index{floating point number} when you see it because it features a radix\index{radix point} point.
The optional exponent\index{exponent} allows you to ``float'' the point.

\readcode
@s FPNUM symbol
@s number symbol

@<symbols@>=
%token <f> FPNUM
%type <f> number
@
@<scanning rules@>=
::@=[+-]?[0-9]+\.[0-9]+(e[+-]?[0-9])?@>  :< SCAN_DECFLOAT; return FPNUM;  >:
@

The layout of floating point variables of type |double| 
or |float| typically follows the IEEE754\index{IEEE754} standard\cite{IEEE754-1985}\cite{IEEE754-2008}. 
We use the following definitions:

\index{float32 t+\&{float32\_t}}
\index{float64 t+\&{float64\_t}}

@<hint basic types@>=

#define FLT_M_BITS 23
#define FLT_E_BITS 8
#define FLT_EXCESS 127

#define DBL_M_BITS 52
#define DBL_E_BITS 11
#define DBL_EXCESS 1023

@


We expect a variable of type |float64_t| to have a binary representation using 64 bit.
The most significant bit is the sign bit, then follow $|DBL_E_BITS|=11$ bits for
the exponent\index{exponent}, and  $|DBL_M_BITS|=52$ bits for the mantissa\index{mantissa}.
The sign\index{sign bit} bit is 1 for a negative number and 0 for a positive number.
A floating point number is stored in normalized\index{normalization} form which means that
the mantissa is shifted such that it has exactly 52+1 bit not counting leading zeros.
The leading bit is then always 1 and there is no need to store it. So 52 bits suffice.
To store the exponent, the excess $q=1023$ is added and the result is stored as an
unsigned 11 bit number.
For example if we regard the exponent bits and the mantissa bits as unsigned binary numbers 
$e$ and $m$ then the absolute value of such a floating point number can be expressed 
as $(1+m*2^{-52})\cdot2^{e-1023}$.
We make similar assumptions about variables of type |float32_t| using the constants as defined above.





To convert the decimal representation of a floating point number to binary values of type |float64_t|,
we use a \CEE/ library function.

@<scanning macros@>=
#define SCAN_DECFLOAT       @[yylval.f=atof(yytext)@]
@

When the parser expects a floating point number and gets an integer number,
it converts it. So whenever in the long format a floating point number is expected,
an integer number will do as well.

@<parsing rules@>=
number: UNSIGNED {$$=(float64_t)$1; } | SIGNED {$$=(float64_t)$1; } | FPNUM;
@

Unfortunately the decimal representation is not optimal for floating point numbers
since even simple numbers in decimal notation like $0.1$ do not have an exact 
representation as a binary floating point number.
So if we want a notation that allows an exact representation
of binary floating point numbers, we must use a hexadecimal\index{hexadecimal} representation.
Hexadecimal floating point numbers start with an optional sign, then as usual the two characters ``{\tt 0x}'',
then follows a sequence of hex digits, a radix point, more hex digits, and an optional exponent.
The optional exponent starts with the character ``{\tt x}'', followed by an optional sign, and some more
hex digits. The hexadecimal exponent is given as a base 16 number and it is interpreted as an exponent
with the base 16. As an example an exponent of ``{\tt x10}'', would multiply the mantissa by $16^{16}$.
In other words it would shift any mantissa |0x10| hexadecimal digits to the left. Here are the exact rules:

@<scanning rules@>=
::@=[+-]?0x{HEX}+\.{HEX}+(x[+-]?{HEX}+)?@>  :< SCAN_HEXFLOAT; return FPNUM;  >:
@

@<scanning macros@>=
#define SCAN_HEXFLOAT       @[yylval.f=xtof(yytext)@]
@
There is no function in the \CEE/ library for hexadecimal floating point notation
so we have to write our own conversion routine.
The function |xtof| converts a string matching the above regular expression to
its binary representation. Its outline is very simple:

@<scanning functions@>=

float64_t xtof(char *x)
{ int sign, digits, exp;
  uint64_t mantissa=0;
  DBG(DBGFLOAT,"converting %s:\n",x);
  @<read the optional sign@>@;
  x=x+2; /* skip ``\.{0x}'' */
  @<read the mantissa@>@;
  @<normalize the mantissa@>@;
  @<read the optional exponent@>@;
  @<return the binary representation@>@;
}
@

Now the pieces:

@<read the optional sign@>=
  if (*x=='-') { sign=-1;@+ x++;@+ }
  else if (*x=='+') { sign=+1;@+ x++;@+ }
  else @+sign=+1;
  DBG(DBGFLOAT,"\tsign=%d\n",sign);
@

When we read the mantissa, we use the temporary variable |mantissa|, keep track
of the number of digits, and adjust the exponent while reading the fractional part.
@<read the mantissa@>=
  digits=0;
  while (*x=='0') x++; /*ignore leading zeros*/
  while (*x!='.')@/
  { mantissa=mantissa<<4;
    if (*x<'A') mantissa=mantissa+*x-'0';
    else  mantissa=mantissa+*x-'A'+10;
    x++;
    digits++;
  }
  x++; /* skip ``\.{.}'' */
  exp=0;
  while (*x!=0 && *x!='x')@/
  { mantissa=mantissa<<4;
    exp=exp-4;
    if (*x<'A') mantissa=mantissa+*x-'0';
    else  mantissa=mantissa+*x-'A'+10;
    x++;
    digits++;
  } 
  DBG(DBGFLOAT,"\tdigits=%d mantissa=0x%" PRIx64 ", exp=%d\n",@|digits,mantissa,exp);
@

To normalize the mantissa, first we shift it to place exactly one nonzero hexadecimal
digit to the left of the radix point. Then we shift it right bit-wise until there is
just a single 1 bit to the left of the radix point.
To compensate for the shifting, we adjust the exponent accordingly.
Finally we remove the most significant bit because it is
not stored.

@<normalize the mantissa@>=
if (mantissa==0) return 0.0;
{ int s;
  s = digits-DBL_M_BITS/4;
  if (s>1) 
   mantissa=mantissa>>(4*(s-1));
  else if (s<1)
   mantissa=mantissa<<(4*(1-s)); 
  exp=exp+4*(digits-1); 
  DBG(DBGFLOAT,"\tdigits=%d mantissa=0x%" PRIx64 ", exp=%d\n",@|digits,mantissa,exp);
  while ((mantissa>>DBL_M_BITS)>1)@/  { mantissa=mantissa>>1; @+ exp++;@+ }
  DBG(DBGFLOAT,"\tdigits=%d mantissa=0x%" PRIx64 ", exp=%d\n",@|digits,mantissa,exp);
  mantissa=mantissa&~((uint64_t)1<<DBL_M_BITS); 
  DBG(DBGFLOAT,"\tdigits=%d mantissa=0x%" PRIx64 ", exp=%d\n",@|digits,mantissa,exp);
}
@

In the printed representation, 
the exponent is an exponent with base 16. For example, an exponent of 2 shifts
the hexadecimal mantissa two hexadecimal digits to the left, which corresponds to a 
multiplication by ${16}^2$.

@<read the optional exponent@>=
  if (*x=='x')@/
  { int  s;
    x++; /* skip the ``\.{x}'' */
    if (*x=='-') {s=-1;@+x++;@+}
    else if (*x=='+') {s=+1;@+x++;@+}
    else s=+1;
    DBG(DBGFLOAT,"\texpsign=%d\n",s);
    DBG(DBGFLOAT,"\texp=%d\n",exp);
    while (*x!=0 )
    { if (*x<'A') exp=exp+4*s*(*x-'0');
      else exp=exp+4*s*(*x-'A'+10);
      x++;
      DBG(DBGFLOAT,"\texp=%d\n",exp);
    }
  }
  RNG("Floating point exponent",@|exp,-DBL_EXCESS,DBL_EXCESS);
@

To assemble the binary representation, we use a |union| of a |float64_t| and |uint64_t|.


@<return the binary representation@>=
{ union {@+float64_t d; @+uint64_t bits; @+} u;
  if (sign<0) sign=1;@+ else@+ sign=0; /* the sign bit */
  exp=exp+DBL_EXCESS; /* the exponent bits */
  u.bits=((uint64_t)sign<<63)@/ 
        | ((uint64_t)exp<<DBL_M_BITS) | mantissa;
  DBG(DBGFLOAT," return %f\n",u.d);
  return u.d;
}
@

The inverse function is |hwrite_float64|. It strives to print floating point numbers
as readable as possible. So numbers without fractional part are written as integers.
Numbers that can be represented exactly in decimal notation are represented in
decimal notation. All other values are written as hexadecimal floating point numbers. 
We avoid an exponent if it can be avoided by using up to |MAX_HEX_DIGITS|

\writecode
@<write functions@>=
#define MAX_HEX_DIGITS 12
void hwrite_float64(float64_t d)
{ uint64_t bits, mantissa;
  int exp, digits;
  hwritec(' '); 
  if (floor(d)==d) 
  { hwritef("%d",(int)d);@+ return;@+}
  if (floor(10000.0*d)==10000.0*d)
  { hwritef("%g",d); @+return;@+}
  DBG(DBGFLOAT,"Writing hexadecimal float %f\n",d);
  if (d<0) { hwritec('-');@+ d=-d;@+}
  hwritef("0x");
  @<extract mantissa and exponent@>@;
  if (exp>MAX_HEX_DIGITS)
    @<write large numbers@>@;
  else if (exp>=0) @<write medium numbers@>@;
  else  @<write small numbers@>@;
}
@

The extraction just reverses the creation of the binary representation. 

@<extract mantissa and exponent@>=
{  union {@+float64_t d; @+ uint64_t bits; @+} u;
   u.d=d; @+ bits=u.bits;
}
  mantissa= bits&(((uint64_t)1<<DBL_M_BITS)-1); 
  mantissa=mantissa+((uint64_t)1<<DBL_M_BITS);
  exp= ((bits>>DBL_M_BITS)&((1<<DBL_E_BITS)-1))-DBL_EXCESS;
  digits=DBL_M_BITS+1; 
  DBG(DBGFLOAT,"\tdigits=%d mantissa=0x%" PRIx64 " binary exp=%d\n",@|digits,mantissa,exp);
@

After we have obtained the binary exponent, 
we round it down, and convert it to a hexadecimal
exponent.
@<extract mantissa and exponent@>=
  { int r;
    if (exp>=0)
    { r= exp%4; 
      if (r>0)
      { mantissa=mantissa<<r; @+exp=exp-r; @+digits=digits+r; @+}
    }
    else
    { r=(-exp)%4;
      if (r>0)
      { mantissa=mantissa>>r; @+exp=exp+r; @+digits=digits-r;@+}
    }
  }
  exp=exp/4;
  DBG(DBGFLOAT,"\tdigits=%d mantissa=0x%" PRIx64 " hex exp=%d\n",@|digits,mantissa,exp);
@

In preparation for writing, 
we shift the mantissa to the left so that the leftmost hexadecimal
digit of it will occupy the 4 leftmost bits of the variable |bits| .

@<extract mantissa and exponent@>=
  mantissa=mantissa<<(64-DBL_M_BITS-4); /* move leading digit to leftmost nibble */
@

If the exponent is larger than |MAX_HEX_DIGITS|, we need to 
use an exponent even if the mantissa uses only a few digits.
When we use an exponent, we always write exactly one digit preceding the radix point.

@<write large numbers@>=
{ DBG(DBGFLOAT,"writing large number\n");
  hwritef("%X.",(uint8_t)(mantissa>>60));
  mantissa=mantissa<<4;
  do {
	  hwritef("%X",(uint8_t)(mantissa>>DBL_M_BITS)&0xF);
	  mantissa=mantissa<<4;
  } while (mantissa!=0);
  hwritef("x+%X",exp);
}
@
If the exponent is small and non negative, we can write the
number without an exponent by writing the radix point at the
appropriate place.
 @<write medium numbers@>=
  {  DBG(DBGFLOAT,"writing medium number\n");
     do {
	  hwritef("%X",(uint8_t)(mantissa>>60));
	  mantissa=mantissa<<4;
	  if (exp--==0) hwritec('.');
	} while (mantissa!=0 || exp>=-1);
  }
@
Last non least, we write numbers that would require additional zeros after the
radix point with an exponent, because it keeps the mantissa shorter.
@<write small numbers@>=
   { DBG(DBGFLOAT,"writing small number\n");
	hwritef("%X.",(uint8_t)(mantissa>>60));
	mantissa=mantissa<<4;
	do {
	  hwritef("%X",(uint8_t)(mantissa>>60));
	  mantissa=mantissa<<4;
	} while (mantissa!=0);
	hwritef("x-%X",-exp);
  } 
@

Compared to the complications of long format floating point numbers,
the short format is very simple because we just use the binary representation.
Since 32 bit floating point numbers offer sufficient precision we use only 
the |float32_t| type.
It is however not possible to just write |HPUT32(d)| for a |float32_t| variable |d|
or |HPUT32((uint32_t)d)| because in the \CEE/ language this would imply
rounding the floating point number to the nearest integer.
But we have seen how to convert floating point values to bit pattern before.

@<put functions@>=
void hput_float32(float32_t d)
{  union {@+float32_t d; @+ uint32_t bits; @+} u;
   u.d=d; @+ HPUT32(u.bits);
}
@

@<get functions@>=
float32_t hget_float32(void)
{  union {@+float32_t d; @+ uint32_t bits; @+} u;
   HGET32(u.bits);
   return u.d;
}
@

\subsection{Fixed Point Numbers}
\TeX\ internally represents most real numbers as fixed\index{fixed point number} point numbers or ``scaled integers''\index{scaled integer}.
The type {\bf scaled\_t} is defined as a signed 32 bit integer, but we consider it as a fixed point number
with the binary radix point just in the middle with sixteen bits before and sixteen bits after it.
To convert an integer into a scaled number, we multiply it by |ONE|; to convert a floating point number
into a scaled number, we multiply it by |ONE| and |ROUND| the result to the nearest integer; 
to convert a scaled number to a floating point number we divide it by |(float64_t)ONE|.

\noindent
@<hint basic types@>=
typedef int32_t scaled_t;
#define ONE ((scaled_t)(1<<16))
@

@<hint macros@>=
#define ROUND(X)     ((int)((X)>=0.0?floor((X)+0.5):ceil((X)-0.5)))
@

\writecode
@<write functions@>=
void hwrite_scaled(scaled_t x)
{ hwrite_float64(x/(float64_t)ONE);
}
@

\subsection{Dimensions}
In the long format, 
the dimensions\index{dimension} of characters, boxes, and other things can be given 
in three units:  \.{pt}, \.{in}, and \.{mm}.

\readcode
@s PT symbol
@s MM symbol
@s INCH symbol
@s dimension symbol
@s DIMEN symbol
@<symbols@>=
%token DIMEN "dimen"
%token PT "pt"
%token MM "mm" 
%token INCH "in"
%type <d> dimension
@

@<scanning rules@>=
::@=dimen@>  :< return DIMEN; >:
::@=pt@>  :< return PT; >:
::@=mm@>  :< return MM; >:
::@=in@>  :< return INCH; >:
@

The unit \.{pt} is a printers point\index{point}\index{pt+{\tt pt}}. 
The unit ``\.{in}'' stands for inches\index{inch}\index{in+{\tt in}} and we have $1\.{in}= 72.27\,\.{pt}$.
The unit ``\.{mm}'' stands for millimeter\index{millimeter}\index{mm+{\tt mm}} and we have $1\.{in}= 25.4\,\.{mm}$.

The definition of a printers\index{printers point} point given above follows the definition used in 
\TeX\ which is slightly larger than the official definition of a printer's
point which was defined to equal exactly 0.013837\.{in} by the American Typefounders
Association in~1886\cite{DK:texbook}.

We follow the tradition of \TeX\ and 
store dimensions as ``scaled points''\index{scaled point} that is a dimension of $d$ points is
stored as $d\cdot2^{16}$ rounded to the nearest integer. 
The maximum absolute value of a dimension is $(2^{30}-1)$ scaled points. 

@<hint basic types@>=
typedef scaled_t dimen_t;
#define MAX_DIMEN ((dimen_t)(0x3FFFFFFF))
@

@<parsing rules@>=
dimension: number PT @|{$$=ROUND($1*ONE); RNG("Dimension",$$,-MAX_DIMEN,MAX_DIMEN); } 
         | number INCH @|{$$=ROUND($1*ONE*72.27); RNG("Dimension",$$,-MAX_DIMEN,MAX_DIMEN);@+}
         | number MM @|{$$=ROUND($1*ONE*(72.27/25.4)); RNG("Dimension",$$,-MAX_DIMEN,MAX_DIMEN);@+};
@

When \.{stretch} is writing dimensions in the long format, 
for simplicity it always uses the unit ``\.{pt}''.
\writecode
@<write functions@>=
void hwrite_dimension(dimen_t x)
{ hwrite_scaled(x);
  hwritef("pt");
}
@

In the short format, dimensions are stored as 32 bit scaled point values without conversion.
\getcode
@<get functions@>=
void hget_dimen(void)
{ uint32_t d;
  HGET32(d); hwrite_dimension(d);
}
@

\putcode
@<put functions@>=

uint8_t hput_dimen(dimen_t d)
{ HPUT32(d);
  return TAG(dimen_kind, b001);
}
@



\subsection{Extended Dimensions}\index{extended dimension}\index{hsize+{\tt hsize}}\index{vsize+{\tt vsize}}
The dimension that is probably used most frequently in a \TeX\ file is {\tt hsize}:
the ho\-ri\-zon\-tal size of a line of text. Common are also assignments
like \.{\\hsize=0.5\\hsize} \.{\\advance\\hsize by -10pt}, for example to
get two columns with lines almost half as wide as usual, leaving a small gap
between left and right column. Similar considerations apply to {\tt vsize}.

Because we aim at a reflowable format for \TeX\ output, we have to postpone 
such computations until the values of \.{hsize} and \.{vsize} are known in the viewer.
Until then, we do symbolic computations on linear functions\index{linear function} of \.{hsize} and \.{vsize}.
We call such a linear function $w+h\cdot\.{hsize}+v\cdot\.{vsize}$
an extended dimension and represent it by the three numbers $w$, $h$, and $v$.

@<hint basic types@>=
typedef struct {@+
dimen_t w; @+ float32_t h, v; @+
} xdimen_t;
@
Since very often a component of an extended dimension is zero, we
store in the short format only the nonzero components and use the
info bits to mark them: |b100| implies $|w|\ne0$,
|b010| implies $|h|\ne 0$, and |b001| implies  $|v|\ne 0$.

\readcode
@s XDIMEN symbol
@s xdimen symbol
@s xdimen_node symbol
@s H symbol
@s V symbol
@<symbols@>=
%token XDIMEN "xdimen"
%token H "h"
%token V "v"
%type <xd> xdimen
@
@<scanning rules@>=
::@=xdimen@>  :< return XDIMEN; >:
::@=h@>  :< return H; >:
::@=v@>  :< return V; >:
@


@<parsing rules@>=
xdimen: dimension number H number V { $$.w=$1; @+$$.h=$2; @+$$.v=$4; }
      | dimension number H          { $$.w=$1; @+$$.h=$2; @+$$.v=0.0; }
      | dimension number V          { $$.w=$1; @+$$.h=0.0; @+$$.v=$2; }
      | dimension                   { $$.w=$1; @+$$.h=0.0; @+$$.v=0.0; };



xdimen_node: start XDIMEN xdimen END { hput_tags($1,hput_xdimen(&($3))); };
@

\writecode
@<write functions@>=
void hwrite_xdimen(xdimen_t *x)
{ hwrite_dimension(x->w); 
  if (x->h!=0.0) {hwrite_float64(x->h); @+hwritec('h');@+}  
  if (x->v!=0.0) {hwrite_float64(x->v); @+hwritec('v');@+}
}

void hwrite_xdimen_node(xdimen_t *x)
{ hwrite_start(); hwritef("xdimen"); hwrite_xdimen(x); hwrite_end();}
@

\getcode

@<get macros@>=
#define @[HGET_XDIMEN(I,X)@] \
  if((I)&b100) HGET32((X).w);@+ else (X).w=0;\
  if((I)&b010) (X).h=hget_float32(); @+ else (X).h=0.0;\
  if((I)&b001) (X).v=hget_float32(); @+else (X).v=0.0;
@

@<get functions@>=
void hget_xdimen(uint8_t a, xdimen_t *x)
{ switch(a)
  { 
#if 0
/* currently the info value 0 is not supported */
case TAG(xdimen_kind,b000): /* see section~\secref{reference} */
    {@+ REF(xdimen_kind,HGET8); @+}@+ break;
#endif
    case TAG(xdimen_kind,b001): HGET_XDIMEN(b001,*x);@+break;
    case TAG(xdimen_kind,b010): HGET_XDIMEN(b010,*x);@+break;
    case TAG(xdimen_kind,b011): HGET_XDIMEN(b011,*x);@+break;
    case TAG(xdimen_kind,b100): HGET_XDIMEN(b100,*x);@+break;
    case TAG(xdimen_kind,b101): HGET_XDIMEN(b101,*x);@+break;
    case TAG(xdimen_kind,b110): HGET_XDIMEN(b110,*x);@+break;
    case TAG(xdimen_kind,b111): HGET_XDIMEN(b111,*x);@+break;
    default:
     QUIT("Extent expected got [%s,%d]",NAME(a),INFO(a));
  }
 }

void hget_xdimen_node(xdimen_t *x)
{ @<read the start byte |a|@>@;
  if (KIND(a)==xdimen_kind)
    hget_xdimen(a,x);
  else
     QUIT("Extent expected at 0x%x got %s",node_pos,NAME(a));
  @<read and check the end byte |z|@>@;
}
@



\putcode
@<put functions@>=
uint8_t hput_xdimen(xdimen_t *x)
{ info_t info=b000;
  if (x->w==0 && x->h==0.0 && x->v==0.0) HPUT8(zero_xdimen_no);
  else
  { if (x->w!=0) { HPUT32(x->w); @+info|=b100; @+} 
    if (x->h!=0.0) { hput_float32(x->h); @+info|=b010; @+} 
    if (x->v!=0.0) {  hput_float32(x->v); @+info|=b001; @+} 
  }
  return TAG(xdimen_kind,info);
}
void hput_xdimen_node(xdimen_t *x)
{ uint32_t p=hpos++-hstart;
  hput_tags(p, hput_xdimen(x));
}


@



\subsection{Stretch and Shrink}\label{stretch}
In section~\secref{glue}, we will consider glue\index{glue} which
is something that can stretch  and  shrink.
The stretchability\index{stretchability} and shrinkability\index{shrinkability} of the
glue can be given in ``\.{pt}'' like a dimension,
but there are three more units: \.{fil}, \.{fill}, and \.{filll}.
A glue with a stretchability of $1\,\hbox{\tt fil}$ will stretch infinitely more
than a glue with a stretchability of $1\,\hbox{\tt pt}$. So if you stretch both glues
together, the first glue will do all the stretching and the latter will not stretch
at all. The ``\.{fil}'' glue has simply a higher order of infinity.
You might guess that ``\.{fill}'' glue and ``\.{filll}'' glue have even higher
orders of infinite stretchability. 
The order of infinity is 0 for \.{pt}, 1 for \.{fil}, 2 for \.{fill}, and 3 for \.{filll}.

The internal representation of a stretch is a variable of type |stretch_t|.
It stores the floating point value and the order of infinity separate as a |float64_t| and a |uint8_t|. 


The short format tries to be space efficient and because it is not necessary to give the 
stretchability with a precision exceeding about six decimal digits, 
we use a single 32 bit floating point value.
To write a |float32_t| value and an order value as one 32 bit value, 
we round the two lowest bit of the |float32_t| variable to zero
using ``round to even'' and store the order of infinity in these bits.
We define a union type \&{stch\_t} to simplify conversion.

@<hint basic types@>=
typedef enum { @+ normal_o=0, fil_o=1, fill_o=2, filll_o=3@+} order_t;
typedef struct {@+  float64_t f;@+ order_t o; @+} stretch_t;
typedef union {@+float32_t f; @+ uint32_t u; @+} stch_t;
@

\putcode
@<put functions@>=
void hput_stretch(stretch_t *s)
{ uint32_t mantissa, lowbits, sign, exponent;
  stch_t st;
  st.f=s->f;
  DBG(DBGFLOAT,"joining %f->%f(0x%X),%d:",s->f,st.f,st.u,s->o);
  mantissa = st.u &(((uint32_t)1<<FLT_M_BITS)-1);
  lowbits = mantissa&0x7; /* lowest 3 bits */
  exponent=(st.u>>FLT_M_BITS)&(((uint32_t)1<<FLT_E_BITS)-1);
  sign=st.u & ((uint32_t)1<<(FLT_E_BITS+FLT_M_BITS));
  DBG(DBGFLOAT,"s=%d e=0x%x m=0x%x",sign, exponent, mantissa);
  switch (lowbits) /* round to even */
  { @+case 0: break; /* no change */
    case 1: mantissa = mantissa -1; @+break;/* round down */
    case 2: mantissa = mantissa -2;  @+break;/* round down to even */
    case 3: mantissa = mantissa +1;  @+break; /* round up */
    case 4: break; /* no change */
    case 5: mantissa = mantissa -1;  @+break;/* round down */
    case 6: mantissa = mantissa +1; /* round up to even, fall through */
    case 7: mantissa = mantissa +1; /* round up to even */
            if (mantissa >= ((uint32_t)1<<FLT_M_BITS))@/
            {exponent++; /* adjust exponent */
             RNG("Float32 exponent",exponent,1,2*FLT_EXCESS);
             @+mantissa=mantissa>>1;
            } 
            break;
  }
  DBG(DBGFLOAT," round s=%d e=0x%x m=0x%x",sign, exponent, mantissa);
  st.u=sign| (exponent<<FLT_M_BITS) | mantissa | s->o;
  DBG(DBGFLOAT,"float %f hex 0x%x\n",st.f, st.u);
  HPUT32(st.u);
}
@

\getcode
@<get macros@>=
#define @[HGET_STRETCH(S)@] { stch_t st; @+ HGET32(st.u);@+ S.o=st.u&3;  st.u&=~3; S.f=st.f; @+}
@

\readcode
@s FIL symbol
@s FILL symbol
@s FILLL symbol
@s order symbol

@<symbols@>=
%token FIL "fil" 
%token FILL "fill"
%token FILLL "filll"
%type <st> stretch
%type <o> order
@

@<scanning rules@>=
::@=fil@>  :< return FIL; >:
::@=fill@>  :< return FILL; >:
::@=filll@>  :< return FILLL; >:
@

@s stretch symbol
@s stretch_t int
@<parsing rules@>=

order: PT {$$=normal_o;} | FIL  {$$=fil_o;}  @+| FILL  {$$=fill_o;} @+| FILLL  {$$=filll_o;};

stretch: number order { $$.f=$1; $$.o=$2; };
@

\writecode

@<write functions@>=
void hwrite_order(order_t o)
{ switch (o)
  { case normal_o: hwritef("pt"); @+break;
    case fil_o: hwritef("fil"); @+break;
    case fill_o: hwritef("fill"); @+break;
    case filll_o: hwritef("filll"); @+break;
    default: QUIT("Illegal order %d",o); @+ break;
  }
}

void hwrite_stretch(stretch_t *s)
{ hwrite_float64(s->f);
  hwrite_order(s->o);
}
@ 

\section{Simple Nodes}\hascode
\label{simple}
\subsection{Penalties}
Penalties\index{penalty} are very simple nodes. They specify the cost of breaking a
line or page at the present position. For the internal representation
we use an |int32_t|. The full range of integers is, however, not
used. Instead penalties must be between -20000 and +20000.
(\TeX\ specifies a range of -10000 to +10000, but plain \TeX\ uses the value -20000 
when it defines the supereject control sequence.)  
The more general node is called an integer node; 
it shares the same kind value |int_kind=penalty_kind|
but allows the full range of values.  
The info value of a penalty node is 1 or 2 and indicates the number of bytes
used to store the integer. The info value 4 can be used for general
integers (see section~\secref{definitions}) that need four byte of storage.

\readcode
@s PENALTY symbol
@s INTEGER symbol
@s penalty symbol
@<symbols@>=
%token PENALTY "penalty"
%token INTEGER     "int"
%type <i> penalty
@

@<scanning rules@>=
::@=penalty@>       :< return PENALTY; >:
::@=int@>           :< return INTEGER; >:
@

@<parsing rules@>=
penalty:  integer {RNG("Penalty",$1,-20000,+20000);$$=$1;};
content_node: start PENALTY penalty END { hput_tags($1,hput_int($3));@+};
@

\getcode
@<cases to get content@>=
case TAG(penalty_kind,1):  @+{int32_t p;@+ HGET_PENALTY(1,p);@+} @+break;
case TAG(penalty_kind,2):  @+{int32_t p;@+ HGET_PENALTY(2,p);@+} @+break;
@

@<get macros@>=
#define @[HGET_PENALTY(I,P)@] \
if (I==1) {int8_t n=HGET8;  @+P=n;@+ } \
else {int16_t n;@+ HGET16(n);@+RNG("Penalty",n,-20000,+20000); @+ P=n; @+}\
hwrite_signed(P);
@

\putcode
@<put functions@>=
uint8_t hput_int(int32_t n)
{ info_t info;
  if (n>=0) @/
  { @+if (n<0x80) { @+HPUT8(n); @+info=1;@+ }
    else if (n<0x8000)  {@+ HPUT16(n);@+ info=2;@+ }
    else  {@+ HPUT32(n);@+ info=4;@+ }
  }
  else@/
  {@+ if (n>=-0x80) {@+ HPUT8(n);@+ info=1;@+ }
    else if (n>=-0x8000)  {@+ HPUT16(n);@+ info=2;@+ }
    else  {@+ HPUT32(n);@+ info=4;@+ }
  }
  return TAG(int_kind,info);
}
@




\subsection{Mathematics}
Being able to handle mathematics\index{mathematics} nicely is one of the primary features of \TeX\ and
so you should expect the same from \HINT/.
A math node occurs before ($|info|=|b100|$)
and after  ($|info|=|b010|$) a mathematical formula in a horizontal list. 
A math node also features a width which represents the amount of 
surrounding space. A zero width can be omitted. In the short format,
the |b001| bit is set if the width is present.

@<hint types@>=
typedef struct {@+
bool on;@+
dimen_t w;@+ 
} math_t;
@

\readcode
@s MATH symbol
@s math symbol
@s ON symbol
@s OFF symbol
@<symbols@>=
%token MATH "math"
%token ON "on"
%token OFF "off"
%type <m> math
@

@<scanning rules@>=
::@=math@>  :< return MATH; >:
::@=on@>  :< return ON; >:
::@=off@>  :< return OFF; >:
@

@<parsing rules@>=
math: ON  dimension { $$.on=true; $$.w=$2; };
math: OFF dimension { $$.on=false; $$.w=$2; };
math: ON  { $$.on=true; $$.w=0; };
math: OFF { $$.on=false; $$.w=0; };
content_node: start MATH math END { hput_tags($1,hput_math(&($3)));};
@

\writecode
@<write functions@>=
void  hwrite_math(math_t *m)
{ @+if (m->on) hwritef(" on"); @+else  hwritef(" off"); 
  if (m->w!=0) hwrite_dimension(m->w);
}
@
\getcode

@<cases to get content@>=
case TAG(math_kind,b100):  { math_t m; @+ HGET_MATH(b100,m);@+ hwrite_math(&m);@+}@+break;
case TAG(math_kind,b010):  { math_t m; @+ HGET_MATH(b010,m);@+ hwrite_math(&m);@+}@+break;
case TAG(math_kind,b101):  { math_t m; @+ HGET_MATH(b101,m);@+ hwrite_math(&m);@+}@+break;
case TAG(math_kind,b011):  { math_t m; @+ HGET_MATH(b011,m);@+ hwrite_math(&m);@+}@+break;
@
@<get macros@>=
#define @[HGET_MATH(I,M)@]  \
if ((I)&b001) HGET32(M.w); @+else M.w=0; \
if ((I)&b100) M.on=true; \
if ((I)&b010) M.on=false;
@

\putcode
@<put functions@>=
uint8_t hput_math(math_t *m)
{ info_t info;
  if (m->on) info=b100; @+else info=b010;
  if (m->w!=0) { @+HPUT32(m->w); @+ info|=b001; @+}
  return TAG(math_kind,info);
}
@


\subsection{Rules}
Rules\index{rule} are simply black rectangles having a height, a depth, and a
width.  All of these dimensions can also be negative but a rule will
not be visible unless its width is positive and its height plus depth
is positive.

As a specialty, rules can have ``running dimensions''\index{running dimension}. If any of the
three dimensions is a running dimension, its actual value will be
determined by running the rule up to the boundary of the innermost
enclosing box.  The width is never running in an horizontal\index{horizontal list} list; the
height and depth are never running in a vertical\index{vertical list} list.  In the long
format, we use a vertical bar ``{\tt \VB}'' or a horizontal bar
``{\tt \_}'' (underscore character) to indicate a running
dimension. Of course the vertical bar is meant to indicate a running
height or depth while the horizontal bar stands for a running
width. The parser, however, makes no distinction between the two and
you can use either of them.  In the short format, we follow \TeX\ and
implement a running dimension by using the special value
$-2^{30}=|0xC0000000|$.


@<hint macros@>=
#define RUNNING_DIMEN 0xC0000000
@

It could have been possible to allow extended dimensions in a rule node,
but in most circumstances, the mechanism of running dimensions is sufficient
and simpler to use. If a rule is needed that requires an extended dimension as
its length, it is always possible to put it inside a suitable box and use a
running dimension.


To make the short format encoding more compact, the first info bit
|b100| will be zero to indicate a running height, bit |b010| will be
zero to indicate a running depth, and bit |b001| will be zero to
indicate a running width.

Because leaders\index{leaders} (see section~\secref{leaders}) may contain a rule
node, we also provide functions to read and write a complete rule
node. While parsing the symbol ``{\sl rule\/}'' will just initialize a variable of type
\&{rule\_t} (the writing is done with a separate routine),
parsing a {\sl rule\_node\/} will always include writing it.

% Currently no predefined rules.
%Further, a {\sl rule\_node} will permit the
%use of a predefined rule (see section~\secref{reference}), 


@<hint types@>=
typedef struct {@+
dimen_t h,d,w; @+
} rule_t;
@

\readcode
@s RULE symbol
@s RUNNING symbol
@s rule_dimension symbol
@s rule symbol
@s rule_node symbol
@<symbols@>=
%token RULE "rule"
%token RUNNING "|"
%type <d> rule_dimension
%type <r> rule
@

@<scanning rules@>=
::@=rule@>  :< return RULE; >:
::@="|"@>  :< return RUNNING; >:
::@="_"@>  :< return RUNNING; >:
@

@<parsing rules@>=
rule_dimension: dimension@+ | RUNNING {$$=RUNNING_DIMEN;};
rule: rule_dimension rule_dimension rule_dimension @/
  { $$.h=$1; @+ $$.d=$2; @+ $$.w=$3;  
    if ($3==RUNNING_DIMEN && ($1==RUNNING_DIMEN || $2==RUNNING_DIMEN))
  QUIT("Incompatible running dimensions 0x%x 0x%x 0x%x",@|$1,$2,$3); };
rule_node: start RULE rule END  { hput_tags($1,hput_rule(&($3))); };
content_node: rule_node;
@

\writecode
@<write functions@>=
static void  hwrite_rule_dimension(dimen_t d, char c)
{ @+if (d==RUNNING_DIMEN) hwritef(" %c",c);
  else hwrite_dimension(d);
}

void  hwrite_rule(rule_t *r)
{ @+hwrite_rule_dimension(r->h,'|'); 
  hwrite_rule_dimension(r->d,'|'); 
  hwrite_rule_dimension(r->w,'_'); 
}
@
\getcode
@<cases to get content@>=
case TAG(rule_kind,b011): @+ {rule_t r;@+ HGET_RULE(b011,r); @+hwrite_rule(&(r));@+ } break;
case TAG(rule_kind,b101): @+ {rule_t r;@+ HGET_RULE(b101,r); @+hwrite_rule(&(r));@+ } break;
case TAG(rule_kind,b001): @+ {rule_t r;@+ HGET_RULE(b001,r); @+hwrite_rule(&(r));@+ } break;
case TAG(rule_kind,b110): @+ {rule_t r;@+ HGET_RULE(b110,r); @+hwrite_rule(&(r));@+ } break;
case TAG(rule_kind,b111): @+ {rule_t r;@+ HGET_RULE(b111,r); @+hwrite_rule(&(r));@+ } break;
@

@<get macros@>=
#define @[HGET_RULE(I,R)@]@/\
if ((I)&b100) HGET32((R).h); @+else (R).h=RUNNING_DIMEN;\
if ((I)&b010) HGET32((R).d); @+else (R).d=RUNNING_DIMEN;\
if ((I)&b001) HGET32((R).w); @+else (R).w=RUNNING_DIMEN;
@

@<get functions@>=
void hget_rule_node(void)
{ @<read the start byte |a|@>@;
  if (KIND(a)==rule_kind) @/
  { @+rule_t r; @+HGET_RULE(INFO(a),r); @/
    hwrite_start();@+ hwritef("rule"); @+hwrite_rule(&r); @+hwrite_end();
  }
  else
    QUIT("Rule expected at 0x%x got %s",node_pos,NAME(a));
  @<read and check the end byte |z|@>@;
}
@

\putcode
@<put functions@>=
uint8_t hput_rule(rule_t *r)
{ info_t info=b000;
  if (r->h!=RUNNING_DIMEN) { HPUT32(r->h); @+info|=b100; @+} 
  if (r->d!=RUNNING_DIMEN) { HPUT32(r->d); @+info|=b010; @+} 
  if (r->w!=RUNNING_DIMEN) { HPUT32(r->w); @+info|=b001; @+} 
  return TAG(rule_kind,info);
}
@

\subsection{Glue}\label{glue}

%Glue considerations

%So what are the cases:
%\itemize
%\item reference to a dimen (common)
%\item reference to a xdimen
%\item reference to a dimen plus and minus
%\item reference to a xdimen plus and minus
%\item reference to a dimen plus 
%\item reference to a xdimen plus 
%\item reference to a dimen  minus
%\item reference to a xdimen minus
%\item dimen
%\item xdimen
%\item dimen plus and minus
%\item xdimen plus and minus (covers all other cases)
%\item dimen plus 
%\item xdimen plus 
%\item dimen  minus
%\item xdimen minus
%\item plus and minus
%\item plus
%\item minus
%\item zero glue (rare, can be replaced by a reference to the zero glue)
%\item reference to a predefined glue (common)
%\enditemize
%This is a total of 21 cases. Can we use the info bits to specify 7 common
%cases and one catch all? First the use of an extended dimension in a glue
%is probably not very common. More typically is the use of a fill glue
%that extends to the boundaries of the enclosing box.

%Here is the statistics for ctex:
%total 58937 glue entries
%total 49 defined glues (so 200 still available)
%There are three font specific glues defined for each font used in texts.
%The explicit glue nodes are the following:
%\itemize
%\item 35\% is predefined zero glue
%\item 30\% are 39 other predefined glue most of them less than 1%
%\item 8\% (4839) is one glue with 25pt pure stretch with order 0
%\item 25\% (14746) is one glue with 100pt stretch and 10pt shrink with order 0
%\item 2\% (1096) is one glue with 10pt no stretch and shrink
%\item 0\% (13) are 7 different glues with no stretch and shrink
%\item 0\% (3) different glues with width!=0 and some stretch of order 0
%\item 0\% (27) 20 different glues with stretch and shrink
%\enditemize

%Some more glue with 1fil is insider 55  leaders
%one vset has an extent 1 no stretch and shrink
%56 hset specify an extent 2 and 1 fil stretch


We have seen in section~\secref{stretch} how to deal with 
stretchability\index{stretchability} and shrinkability\index{shrinkability} and we will need this now.
Glue\index{glue}  has a natural width---which in general can be an extended dimension---and 
in addition it can stretch and shrink. 
It might have been possible to allow an extended dimension also for the stretch\-ability or shrink\-ability 
of a glue, but this seems of little practical relevance and so simplicity won over generality.
Even with that restriction, it is an understatement to regard glue nodes as "simple" nodes, 
and we could equally well list them in section~\secref{composite} as composite nodes.

To use the info bits in the short format wisely, I collected some statistical data using the
\TeX book as an example. It turns out that about 99\% of all the 58937 glue nodes 
(not counting the inter word glues used inside texts) could be covered with only 43
predefined glues.
So this is by far the most common case; we reserve the info value |b000| 
to cover it and postpone the description of such glue nodes until we describe references in 
section~\secref{reference}.

We expect the remaining cases to contribute not too much to the file size,
and hence, simplicity is a more important aspect than efficiency when allocating the remaining
info values.

Looking at the glues in more detail, we find that the most common cases are those where 
either one, two, or all three glue components are zero. We use the two lowest bits to indicate
the presence of a nonzero stretchability or shrinkability and reserve the info values 
|b001|, |b010|, and |b011| for those cases where the width of the glue is zero.
The zero glue, where all components are zero, is defined as a fixed, predefined glue instead 
of reserving a special info value for it.  The cost of one extra byte when encoding it seems 
not too high a price to pay. 
After reserving the info value |b111| for the most general case of a glue, we have
only three more info values left: |b100|, |b101|, and |b110|.
Keeping things simple implies using the two lowest info bits---as before---to indicate
a nonzero stretchability or shrinkability. For the width, three choices remain: using a reference
to a dimension, using a reference to an extended dimension, or using an immediate value. 
Since references to glues are already supported, an immediate width seems best for
glues that are not frequently reused, avoiding the overhead of references. 
% It also makes parsing simpler because we avoid the confusion between references to dimensions
% and references to glues and references to extended dimensions.

Here is a summary of the info bits and the implied layout of glue nodes in the short format:
\itemize
\item |b000|: reference to a predefined glue
\item |b001|: zero width and nonzero shrinkability
\item |b010|: zero width and nonzero stretchability
\item |b011|: zero width and nonzero stretchability and  shrinkability
\item |b100|: nonzero width
\item |b101|: nonzero width and nonzero shrinkability
\item |b110|: nonzero width and nonzero stretchability
\item |b111|: extended dimension and nonzero stretchability and  shrinkability
\enditemize


@<hint basic types@>=
typedef struct {@+
xdimen_t w; @+
stretch_t p, m;@+  
} glue_t;
@


To test for a zero glue,
we implement a macro:
@<hint macros@>=
#define @[ZERO_GLUE(G)@] ((G).w.w==0  && (G).w.h==0.0  && (G).w.v==0.0  && (G).p.f==0.0 && (G).m.f==0.0)
@

Because other nodes (leaders, baselines, and fonts)
contain glue nodes as parameters, we provide functions 
to read and write a complete glue node in the same way as we did
for rule nodes.
Further, such an internal {\sl glue\_node\/} has the special property that  
a node for the zero glue might be omitted entirely.

   
\readcode
@s GLUE symbol
@s glue symbol
@s glue_node symbol
@s PLUS symbol
@s MINUS symbol
@s plus symbol
@s minus symbol

@<symbols@>=
%token GLUE "glue"
%token PLUS  "plus"
%token MINUS   "minus"
%type <g> glue
%type <b> glue_node
%type <st> plus minus
@

@<scanning rules@>=
::@=glue@>  :< return GLUE; >:
::@=plus@>       :< return PLUS; >:
::@=minus@>       :< return MINUS; >:
@

@<parsing rules@>=
plus: { $$.f=0.0; $$.o=0; } | PLUS stretch {$$=$2;};
minus: { $$.f=0.0; $$.o=0; } | MINUS stretch {$$=$2;};
glue: xdimen plus minus {$$.w=$1; $$.p=$2; $$.m=$3; };
content_node: start GLUE glue END {if (ZERO_GLUE($3)) {HPUT8(zero_skip_no);
 hput_tags($1,TAG(glue_kind,0)); } else hput_tags($1,hput_glue(&($3)));  }; 
glue_node: start GLUE glue END @/
           {@+ if (ZERO_GLUE($3)) { hpos--; $$=false;@+}@/
                 else { hput_tags($1,hput_glue(&($3))); $$=true;@+}@+ }; 
@

\writecode
@<write functions@>=
void hwrite_plus(stretch_t *p)
{ @+if (p->f!=0.0) {  hwritef(" plus");@+hwrite_stretch(p); @+}
}
void hwrite_minus(stretch_t *m)
{@+ if (m->f!=0.0) {  hwritef(" minus");@+hwrite_stretch(m); @+}
}
 
void hwrite_glue(glue_t *g)
{ hwrite_xdimen(&(g->w)); @+
  hwrite_plus(&g->p); @+hwrite_minus(&g->m);
}

void hwrite_glue_node(glue_t *g)
{@+ 
    if (ZERO_GLUE(*g)) hwrite_ref_node(glue_kind,zero_skip_no);
    else @+{  hwrite_start(); @+hwritef("glue"); @+hwrite_glue(g); @+hwrite_end();@+}
}
@

\getcode
@<cases to get content@>=
case TAG(glue_kind,b001): { glue_t g;@+ HGET_GLUE(b001,g);@+ hwrite_glue(&g);@+}@+break;
case TAG(glue_kind,b010): { glue_t g;@+ HGET_GLUE(b010,g);@+ hwrite_glue(&g);@+}@+break;
case TAG(glue_kind,b011): { glue_t g;@+ HGET_GLUE(b011,g);@+ hwrite_glue(&g);@+}@+break;
case TAG(glue_kind,b100): { glue_t g;@+ HGET_GLUE(b100,g);@+ hwrite_glue(&g);@+}@+break;
case TAG(glue_kind,b101): { glue_t g;@+ HGET_GLUE(b101,g);@+ hwrite_glue(&g);@+}@+break;
case TAG(glue_kind,b110): { glue_t g;@+ HGET_GLUE(b110,g);@+ hwrite_glue(&g);@+}@+break;
case TAG(glue_kind,b111): { glue_t g;@+ HGET_GLUE(b111,g);@+ hwrite_glue(&g);@+}@+break;
@

@<get macros@>=
#define @[HGET_GLUE(I,G)@] {\
  if(I==b111) hget_xdimen_node(&((G).w)); \
  else @/{@+(G).w.h=0.0;@+(G).w.v=0.0;\
    if((I)&b100) HGET32((G).w.w);@+ else (G).w.w=0;@+ }\
  if((I)&b010) HGET_STRETCH((G).p) @+else (G).p.f=0.0, (G).p.o=0;\
  if((I)&b001) HGET_STRETCH((G).m) @+else  (G).m.f=0.0, (G).m.o=0;@+}
@

@<get functions@>=
void hget_glue_node(void)
{ @<read the start byte |a|@>@;
  if (KIND(a)!=glue_kind)@+ {@+ hpos--;@+ return; @+}
  if (INFO(a)==b000)
  { @+hwrite_ref_node(glue_kind,HGET8); @+}
  else
  { @+glue_t g; @+HGET_GLUE(INFO(a),g);@+ hwrite_glue_node(&g);@+}
  @<read and check the end byte |z|@>@;
}
@


\putcode
@<put functions@>=
uint8_t hput_glue(glue_t *g)
{ info_t info=b000;
  if (ZERO_GLUE(*g)) { HPUT32(g->w.w); @+ info=b100; } /* this is not a reference */
  else if ( (g->w.w==0 && g->w.h==0.0 && g->w.v==0.0)) 
  { if (g->p.f!=0.0) { hput_stretch(&g->p); @+info|=b010; @+} 
    if (g->m.f!=0.0) { hput_stretch(&g->m); @+info|=b001; @+} 
  }
  else if ( g->w.h==0.0 && g->w.v==0.0 && (g->p.f==0.0 || g->m.f==0.0))
  { HPUT32(g->w.w); @+ info=b100;
    if (g->p.f!=0.0) { hput_stretch(&g->p); @+info|=b010; @+} 
    if (g->m.f!=0.0) { hput_stretch(&g->m); @+info|=b001; @+} 
  }
  else@/
  { hput_xdimen_node(&(g->w));
    hput_stretch(&g->p);@+ hput_stretch(&g->m);
    info=b111;   
  }
  return TAG(glue_kind,info);
}
@

\section{Lists}\hascode\label{lists}
When a node contains multiple other nodes, we package these nodes into a list\index{list} node.
It is important to note that list nodes never occur as individual nodes, 
they only occur as parts of other nodes.
In total, we have four different types of lists: plain lists that use the
kind value |list_kind|, text\index{text} lists that use the kind value |text_kind|,
adjustments that use the kind value |adjust_kind|,
and parameter\index{parameter} lists that use the kind value |param_kind|.
A description of the first two types of lists follows here.
Adjustments\index{adjustment} are just plain lists of vertical material described in section~\secref{adjust}, and
parameter lists are described in section~\secref{paramlist}.

Because lists are of variable size, it is not possible in the short format
to tell from the kind and info bits of a tag byte the size of the list node.
So advancing from the beginning of a list node to the next node after the list is not as
simple as usual. 
To solve this problem, we  store the size of the list immediately after
the start byte and before the end byte.
Alternatively we could require programs to traverse the
entire list.
The latter solution is more compact but inefficient for list with many
nodes; our solution will cost some extra bytes, but the amount
of extra bytes will only grow logarithmically with the size of the \HINT/ file.
It would be possible to allow both methods so that a \HINT/ file could balance size 
and time tradeoffs by making small lists---where the size can be
determined easily by reading the entire list---without size information and making large lists
with size information so that they can be skipped easily without
reading them. But the added complexity seems too high a price to pay.
 

Now consider the problem of reading a content stream starting at an arbitrary
position $i$ in the middle of the stream. This situation occurs
naturally when resynchronizing\index{resynchronization} a content stream after 
an error has been detected, but implementing links poses a similar problem.
We can inspect the byte at position $i$ and see
if it is a valid tag. If yes, we are faced with the problem of
verifying that this is not a mere coincidence. 
So we determine the size $s$ of the node. If the byte in question is a start byte,
we should find a matching byte $s$ bytes later in the stream; if it is an end byte,
we should find the matching byte $s$ bytes earlier in the stream; if we
find no matching byte, this was neither a start nor an end byte. 
If we find exactly one matching byte, we can be quite confident (error
probability 1/256 if assuming equal probability of all byte values) 
that we have found a tag, and we know whether
it is the beginning or the end tag. If we find two matching byte, we
have most likely the start or the end of a node, but we do not know which
of the two. To find out which of the two possibilities is true 
or to reduce the probability of an error, we can
check the start and end byte of the node immediately preceding a start byte or
immediately following an end byte in a similar way.
By testing two more byte, this additional check will reduce the error
probability further to $1/2^{24}$ (under the same assumption as before). So 
checking more nodes is rarely necessary.  This whole schema
would, however, not work if we happen to find a tag byte that indicated
either the begin or the end of a list without specifying the size
of the list. Sure, we can verify the bytes before and after it to
find out whether the byte following it is the begin of a node and the
byte preceding it is the end of a node, but we still don't know if the
byte itself starts a node list or ends a node list. Even reading along
in either direction until finding a matching tag will not answer the
question. The situation is better if we specify a
size: we can read the suspected size after or before the tag and check if we
find a matching tag and size at the position indicated. 
In the short format, we use the |info| value to indicate the number of
byte used to store the list size: A list with $0<|info|\le 5$ 
uses $|info|-1$ byte to store the size.
The info value zero is reserved for references to predefined lists
(which are currently not implemented).

Storing the list size immediately preceding the end tag creates a new
problem: If we try to recover from an error, we might not know the
size of the list and searching for the end of a list, we might be
unable to tell the difference between the bytes that encode the list
size and the start tag of a possible next node.  If we parse the
content backward, the problem is completely symmetric.

To solve the problem, we insert an additional byte immediately before
the final size and after the initial size marking the size boundary.
We choose the byte values |0xFF|, |0xFE|, |0xFD|, and |0xFC| which can
not be confused with valid tag bytes and indicate that the size is
stored using 1, 2, 3, or 4 byte respectively.  Under regular
circumstances, these bytes are simply skipped.  When searching for the
list end (or start) these bytes would correspond to
|TAG(penalty_kind,i)| with $7 \ge \hbox{|i|} \ge 4$ and can not be
confused with valid penalty nodes which use only the info values 0, 1,
and~2.


We are a bit lazy when it comes to the internal representation of a list.
Since we need the representation as a short format byte sequence anyway, 
it consists of the position |p| of the start of the byte sequence 
combined with an integer |s| giving the size of the byte sequence.
If the list is empty, |s| is zero.

@<hint types@>=
typedef struct {@+
kind_t k; @+
uint32_t p;@+
uint32_t s;@+
} list_t;
@

The major drawback of his choice of representation is that it ties
together the reading of the long format and the writing of the short
format; these are no longer independent.  
So starting with the present section, we have to take the short format
representation of a node into account already when we parse the long
format representation.


In the long format, we may start a list node with an
estimate\index{estimate} of the size needed to store the list in the
short format. We do not want to require the exact size because this
would make editing of long format \HINT/ files almost impossible. Of
course this makes it also impossible to derive the exact |s| value of
the internal representation from the long format
representation. Therefore we start by parsing the estimate of the list
size and use it to reserve the necessary number of byte to store the
size.  Then we parse the |content_list|. As a side effect---and this
is an important point---this will write the list content in short
format into the output buffer.  As mentioned above, whenever a node
contains a list, we need to consider this side effect when we give the
parsing rules.  We will see examples for this in
section~\secref{composite}.

The function |hput_list| will be called {\it after} the short format
of the list is written to the output.  Before we pass the internal
representation of the list to the |hput_list|
function, we update |s| and |p|. Further, we pass the position in the stream where the
list size and its boundary mark is supposed to be. 
Before |hput_list| is called, space for the tag, the size, and the boundary mark
is allocated based on the estimate. The function
|hsize_bytes| computes the number of byte required to store the list
size, and the function |hput_list_size| will later write the list
size.  If the estimate turns out to be wrong, the list data can be moved
to make room for a larger or smaller size field.


If the long format does not specify a size estimate, a suitable default must be chosen.
A statistical analysis shows 
%
%statistics about list sizes using my old prototype
%
%name        type size_byte list_count total_size
%hello.hnt  text 1         6          748
%            text 2         2          1967
%            list 1         65         3245
%            list 2         1          352
%web2w.hnt  text 1         1043       121925
%            text 2         1344       859070
%            list 1         19780      725514
%            list 2         487        199243
%ctex.hnt   text 1         9121       4241128
%            text 2         12329      7872687
%            text 3         1          75010
%            list 1         121557     4600743
%            list 2         222        147358
%
that most plain lists need only a single byte to store the size; and even the 
total amount of data contained in these lists exceeds the amount of data stored
in longer lists by a factor of about 3. Hence if we do not have an estimate, 
we reserve only a single byte to store the size of a list.
The statistics looks different for lists stored as a text: The number of texts
that require two byte for the size is slightly larger than the number of texts that 
need only one byte, and the total amount of data stored in these texts is larger by a factor of 2 to 7
than the total amount of data found in all other texts.
Hence as a default, we reserve two byte to store the size for texts.


\subsection{Plain Lists}\label{plainlists}
Plain list nodes start and end with a tag of kind |list_kind| or |adjust_kind|.

Not uncommon are empty\index{empty list} lists; these are the only lists that can be
stored using $|info|=1$; such a list has zero bytes of size
information, and implicitly its size is zero. The |info| value 0
is not used since we do not use predefined plain lists.

Writing the long format uses the fact that the function
|hget_content_node|, as implemented in the \.{stretch} program, will
output the node in the long format.

\readcode
@s list symbol
@s content_list symbol
@s estimate symbol
@s position symbol

@<symbols@>=
%type <l>  list
%type <u> position content_list
@

@<parsing rules@>=
position: {$$=hpos-hstart;};
content_list: @+ position @+
            | content_list content_node;
estimate: {hpos+=2; } @+
        | UNSIGNED  {hpos+=hsize_bytes($1)+1; } ;
list: start estimate content_list END @/
          {@+$$.k=list_kind;@+ $$.p=$3; @+ $$.s=(hpos-hstart)-$3;
           hput_tags($1,hput_list($1+1, &($$)));@+};
@

\writecode
@<write functions@>=
void hwrite_list(list_t *l)
{ uint32_t h=hpos-hstart, e=hend-hstart; /* save |hpos| and |hend| */
  hpos=l->p+hstart;@+ hend=hpos+l->s;
  if (l->k==list_kind ) @<write a list@>@;
  else if (l->k==text_kind)  @<write a text@>@;
  else QUIT("List expected got %s", content_name[l->k]);
  hpos=hstart+h;@+  hend=hstart+e; /* restore  |hpos| and |hend| */
}
@

@<write a list@>=
{@+if (l->s==0) hwritef(" <>");@/
   else@/
   {@+DBG(DBGNODE,"Write list at 0x%x size=%u\n", l->p, l->s); 
    @+hwrite_start();@+
     if (l->s>0xFF) hwritef("%d",l->s); 
     while(hpos<hend)
       hget_content_node();
     hwrite_end();
   }
}
@
\getcode
@<get functions@>=
void hget_size_boundary(info_t info)
{ uint32_t n;
  if (info<2) return;
  n=HGET8;
  if (n-1!=0x100-info) QUIT(@["Size boundary byte 0x%x with info value %d at " SIZE_F@],
                            n, info,hpos-hstart-1);
}

uint32_t hget_list_size(info_t info)
{ uint32_t n;  
  if (info==1) return 0;
  else if (info==2) n=HGET8;
  else if (info==3) HGET16(n);
  else if (info==4) HGET24(n);
  else if (info==5) HGET32(n);
  else QUIT("List info %d must be 1, 2, 3, 4, or 5",info);
  return n;
} 

void hget_list(list_t *l)
{ @+if (KIND(*hpos)!=list_kind && KIND(*hpos)!=adjust_kind && @/
        KIND(*hpos)!=text_kind  &&@| KIND(*hpos)!=param_kind) @/
  {@+ l->p=hpos-hstart;@+ l->s=0;@+ l->k=list_kind;@+ } 
   else
  {@+
    @<read the start byte |a|@>@;
    l->k=KIND(a);
    HGET_LIST(INFO(a),*l);
    @<read and check the end byte |z|@>@;
    DBG(DBGNODE,"Get list at 0x%x size=%u\n", l->p, l->s);
  }
}
@

@<get macros@>=
#define @[HGET_LIST(I,L)@] \
    (L).s=hget_list_size(I); hget_size_boundary(I);\
    (L).p=hpos-hstart; \
    hpos=hpos+(L).s; hget_size_boundary(I);\
    { uint32_t s=hget_list_size(I); \
      if (s!=(L).s) \
      QUIT(@["List sizes at 0x%x and " SIZE_F " do not match 0x%x != 0x%x"@],node_pos+1,hpos-hstart-I-1,(L).s,s);}
@

\putcode

@<put functions@>=
uint8_t hsize_bytes(uint32_t n)
{ @+if (n==0)  return 0;
  else if (n<0x100)  return 1;
  else if (n<0x10000)  return 2;
  else if (n<0x1000000)  return 3;
  else return 4;
}

void hput_list_size(uint32_t n, int i)
{ @+if (i==0) ;
  else if (i==1) HPUT8(n);
  else if (i==2) HPUT16(n);
  else if (i==3) HPUT24(n);
  else  HPUT32(n);
}

uint8_t hput_list(uint32_t start_pos, list_t *l)
{ @+if (l->s==0)
  { hpos=hstart+start_pos; return TAG(l->k,1);@+}
  else@/
  { uint32_t list_end=hpos-hstart;
    info_t i=l->p -start_pos-1; /* number of byte allocated for size */
    info_t j=hsize_bytes(l->s); /* number of byte needed for size */
    DBG(DBGNODE,"Put list at 0x%x size=%u\n", l->p, l->s);
    if (i>j && l->s> 0x100) j=i; /* avoid moving large lists */
    if (i!=j)@/
    { int d= j-i;
      DBG(DBGNODE,"Moving %u byte by %d\n", l->s,d);
      memmove(hstart+l->p+d,hstart+l->p,l->s);
      l->p=l->p+d;@+
      list_end=list_end+d;
    }
    hpos=hstart+start_pos; @+  hput_list_size(l->s,j);@+ HPUT8(0x100-j);
    hpos=hstart+list_end;@+  HPUT8(0x100-j);@+ hput_list_size(l->s,j);
    return TAG(l->k,j+1);
  }
}

@



\subsection{Texts}\label{text}
A Text\index{text} is a list of nodes with a representation optimized for character nodes.
In the long format, a sequence of characters like \.{Hello} is written
\.{<glyph 'H'} \.{*0>} \.{<glyph} \.{'e'} \.{*0>} \.{<glyph 'l' *0>} 
\.{<glyph 'l' *0>} \.{<glyph 'o' *0>}, and even in the short
format it requires 4 byte per character! As a text, the same sequence is written  \.{"Hello"} in the
long format and the short format requires usually just 1 byte per character.
Indeed except the bytes with values from |0x00| to |0x20|, which are considered 
control\index{control code} codes, all bytes and all \hbox{UTF-8}\index{UTF8} multibyte sequences
are simply considered character\index{character code} codes. They are equivalent to a glyph node 
in the ``current font''. The current\index{current font} font\index{font}
is font number 0 at the beginning of a text
and it can be changed using the control codes. We introduce the concept of a ``current font''
because we do not expect the font to change too often, and it allows for a more compact
representation if we do not store the font with every character code. It has an
important disadvantage though: storing only font changes prevents us from parsing
a text backwards; we always have to start at the beginning of the text, where the
font is known to be font number 0.

Defining a second format for encoding lists of nodes adds another difficulty to the problem we had
discussed at the beginning of section~\secref{lists}. When we try to recover from an error and
start reading a content stream
at an arbitrary position, the first thing we need to find out is whether at this position we have
the tag byte of an ordinary node or whether we have a position inside a text.

Inside a text, character nodes start with a byte in the range |0x21|--|0xF7|. This is a wide range
and it overlaps considerably with the range of valid tag bytes. It is however possible to choose
the kind values in such a way that the control codes do not overlap with the valid tag bytes that
start a node. For this reason, the values |text_kind==0|, |list_kind==1|, |param_kind==2|,
|xdimen_kind==3|, and |adjust_kind==4| were chosen on page~\pageref{kinddef}.
Texts, lists, parameter lists, and extended dimensions occur only {\it inside} of content nodes, but
are not content nodes in their own right; so the values |0x00| to |0x1F| are not used as tag bytes
of content nodes. The value |0x20| would, as a tag byte, indicate an adjust node (|adjust_kind==4|)
with info value zero. Because there are no predefined adjustments,  |0x20| is not used as a tag byte either.
(An alternative choice would be to use the kind value 4 for paragraph nodes because there are no
predefined paragraphs.)

The largest byte that starts an UTF8 code is |0xF7|; hence, there are eight possible control codes,
from |0xF8| to |0xFF|, available.
The first three values  |0xF8|, |0xF9|, and |0xFA| are actually used for penalty nodes
with info values, 0, 1, and 2. The last four  |0xFC|,  |0xFD|,  |0xFE|, and  |0xFF| are
used as boundary marks for the text size and therefore we use only |0xFB| as control code.

In the long format, we do not provide a syntax for specifying a size estimate\index{estimate} as we
did for plain lists, because we expect text to be quite short. We allocate two byte
for the size and hope that this will prove to be sufficient most of the time.
Further, we will disallow the use of non-printable
ASCII codes, because these are---by definition---not very readable, and we will
give special meaning to some of the printable ASCII codes because we will need
a notation for the beginning and ending of a text, for nodes inside a text, 
and the control codes.

Here are the details:
\itemize

\item In the long format, a text starts and ends with a double\index{double quote} quote character ``\.{"}''.
In the short format, texts are encoded similar to lists using the kind value |text_kind|.

\item Arbitrary nodes can be embedded inside a text. In the long format, they are enclosed
in pointed brackets  \.{<} \dots \.{>} as usual. In the short format, an arbitrary node 
can follow the control code $|txt_node|=|0x1E|$. Because text may occur in nodes, the scanner needs
to be able to parse texts nested inside nodes nested inside nodes nested inside texts \dots\ To
accomplish this, we use the ``stack'' option of \.{flex} and 
include the popping and pushing the
stack in the macros |SCAN_START| and |SCAN_END|.

\item The space\index{space character} character ``\.{\ }'' with ASCII value |0x20| stands in both formats for the 
font specific inter word glue node (control code |txt_glue|).

\item The hyphen\index{hyphen character} character ``\.{-}'' in the long format 
and the control code $|txt_hyphen|=|0x1F|$ in the short format
stand for the font specific hyphen node.

\item In the long format, the backslash\index{backslash} character ``\.{\\}'' is used as an escape character.
It is used to introduce notations for control codes, as described below, and to access
the character codes of those ASCII characters that otherwise carry a special meaning.
For example ``\.{\\"}'' denotes the character code of the double quote character ``\.{"}'';
and similarly ``\.{\\<}'', ``\.{\\>}'', ``\.{\\\ }'', and ``\.{\\-}'' 
denote the character codes of ``\.{<}'', ``\.{>}'', ``\.{\ }'',  and ``\.{-}'' respectively.


\item In the long format, a TAB-character (ASCII code |0x09|)\index{tab character}
is silently converted to a space\index{space character} character (ASCII code |0x20|);
a NL-character\index{newline character} (ASCII code |0x0A|), together with surrounding
spaces, TAB-characters, and CR-characters\index{carriage return character}  (ASCII code |0x0D|), is silently converted
to a single space character. 
All other ASCII characters in the range |0x00| to |0x1F| 
are not allowed inside a text. This rule avoids the problems arising from ``invisible''
characters embedded in a text and it allows to break texts into lines, even with indentation\index{indentation},
at word boundaries.

To allow breaking a text into lines without inserting spaces,  
a NL-character together with surrounding
spaces, TAB-characters, and CR-characters is completely ignored
if the whole group of spaces, TAB-characters, CR-characters, and the NL-character is
preceded by a backslash character. 

For example, the text ``\.{"There\ is\ no\ more\ gas\ in\ the\ tank."}''\hfil\break
can be written as 
\medskip
 
\qquad\vbox{\hsize=0.5\hsize\noindent
\.{"There\ is\ }\hfil\break
\.{\hbox to 2em {$\rightarrow$\hfill}no more g\\\ \ }\hfil\break
\.{\hbox to 2em {$\rightarrow$\hfill}as in the tank."}
}\hss

To break long lines when writing a long format file, we use the variable |txt_length|
to keep track of the approximate length of the current line.

\item The control codes  $|txt_font|=|0x00|$, |0x01|, |0x02|, \dots, and |0x07| are used to 
change the current font to 
font number 0, 1, 2, \dots, and 7. In the long format these control codes are written
\.{\\0}, \.{\\1}, \.{\\2}, \dots, and \.{\\7}.

\item The control code $|txt_global|=|0x08|$ is followed by a second parameter byte. If the value
of the parameter byte is $n$, it will set the current font to font number $n$.
In the long format, the two byte sequence is written
``\.{\\F}$n$\.{\\}''  where $n$ is the decimal representation of the font number.


\item The control codes |0x09|, |0x0A|, |0x0B|, |0x0C|, |0x0E|, |0x0E|, |0x0F|, and |0x10| 
are also followed by a second parameter byte. They are used to reference 
the global definitions of penalty\index{penalty}, kern\index{kern}, ligature\index{ligature}, hyphen\index{hyphen}, glue\index{glue}, math\index{math}, rule\index{rule}, and image\index{image} nodes.
The parameter byte contains the reference number. 
For example, the byte sequence  |0x09| |0x03|  is equivalent to the node \.{<penalty *3>}.
In the long format these two-byte sequences are written,
``\.{\\P}$n$\.{\\}'' (penalty),
``\.{\\K}$n$\.{\\}'' (kern),
``\.{\\L}$n$\.{\\}'' (ligature),
``\.{\\H}$n$\.{\\}'' (hyphen),
``\.{\\G}$n$\.{\\}'' (glue),
``\.{\\M}$n$\.{\\}'' (math),
``\.{\\R}$n$\.{\\}'' (rule), and
``\.{\\I}$n$\.{\\}'' (image), where $n$ is the decimal representation of the parameter value.


\item The control codes from  $|txt_local|=|0x11|$ to |0x1C| are used to reference
one of the 12 font specific parameters\index{font parameter}. In the long format they are
written ``\.{\\a}'', ``\.{\\b}'', ``\.{\\c}'', \dots,  ``\.{\\j}'', ``\.{\\k}'', ``\.{\\l}''. 


\item  The control code $|txt_cc|=|0x1D|$ is used as a prefix for an arbitrary 
character code represented as an UTF-8 multibyte sequence. 
Its main purpose is providing a method for including character codes
less or equal to |0x20| which otherwise would be considered control
codes.  In the long format, the byte sequence is written
``\.{\\C}$n$\.{\\}'' where $n$ is the decimal representation of the
character code.


\item The control code $|txt_node|=|0x1E|$ is used as a prefix for an arbitrary node in short format.
In the long format, it is  written ``\.{<}'' and is followed by the node content 
in long format terminated by  ``\.{>}''.

\item The control code $|txt_hyphen|=|0x1F|$  is used to access the font specific discretionary hyphen\index{hyphen}.
In the long format it is simply written as ``\.{-}''. 

\item The control code $|txt_glue|=|0x20|$ is the space character, it is used to access the font specific
inter-word\index{inter-word glue} glue. In the long format, we use the space character\index{space character} ``\.{\ }'' as well.

\item The control code $|txt_ignore|=|0xFB|$ is ignored, its position can be used in a link to specify a position
between two characters. In the long format it is written as ``\.{\\@@}''.

\enditemize
For the control codes, we define an enumeration type and for references a reference type.
@<hint types@>=
typedef enum { @+txt_font=0x00, txt_global=0x08, txt_local=0x11, txt_cc=0x1D, txt_node=0x1E,
txt_hyphen=0x1F, txt_glue=0x20, txt_ignore=0xFB} txt_t;
@

\readcode
@s TXT symbol
@s TXT_START symbol
@s TXT_END symbol
@s TXT_FONT symbol
@s TXT_LOCAL symbol
@s TXT_GLOBAL symbol
@s TXT_FONT_GLUE symbol
@s TXT_FONT_HYPHEN symbol
@s TXT_CC symbol
@s TXT_IGNORE symbol
@s text symbol
@<scanning definitions@>=
%x TXT
@

@<symbols@>=
%token TXT_START TXT_END TXT_IGNORE
%token TXT_FONT_GLUE TXT_FONT_HYPHEN 
%token <u> TXT_FONT TXT_LOCAL
%token <rf> TXT_GLOBAL
%token <u> TXT_CC 
%type <u> text
@

@<scanning rules@>=
::@=\"@>            :< SCAN_TXT_START; return TXT_START; >:

<TXT>{ 
::@=\"@>            :< SCAN_TXT_END; return TXT_END; >:

::@="<"@>           :< SCAN_START; return START; >:
::@=">"@>           :< QUIT("> not allowed in text mode");>:

::@=\\\"@>          :< yylval.u='"'; return TXT_CC; >:
::@=\\"<"@>         :< yylval.u='<'; return TXT_CC; >:
::@=\\">"@>         :< yylval.u='>'; return TXT_CC; >:
::@=\\" "@>         :< yylval.u=' '; return TXT_CC; >:
::@=\\"-"@>         :< yylval.u='-'; return TXT_CC; >:
::@=\\"@@"@>        :< return TXT_IGNORE; >:

::@=[ \t\r]*(\n[ \t\r]*)+@>  :< return TXT_FONT_GLUE; >:
::@=\\[ \t\r]*\n[ \t\r]*@>   :< ; >:

::@=\\[0-7]@>       :< yylval.u=yytext[1]-'0'; return TXT_FONT;

::@=\\F[0-9]+\\@>   :< SCAN_REF(font_kind); return TXT_GLOBAL; >:
::@=\\P[0-9]+\\@>   :< SCAN_REF(penalty_kind); return TXT_GLOBAL; >:
::@=\\K[0-9]+\\@>   :< SCAN_REF(kern_kind); return TXT_GLOBAL; >:
::@=\\L[0-9]+\\@>   :< SCAN_REF(ligature_kind); return TXT_GLOBAL; >:
::@=\\H[0-9]+\\@>   :< SCAN_REF(hyphen_kind); return TXT_GLOBAL; >:
::@=\\G[0-9]+\\@>   :< SCAN_REF(glue_kind); return TXT_GLOBAL; >:
::@=\\M[0-9]+\\@>   :< SCAN_REF(math_kind); return TXT_GLOBAL; >:
::@=\\R[0-9]+\\@>   :< SCAN_REF(rule_kind); return TXT_GLOBAL; >:
::@=\\I[0-9]+\\@>   :< SCAN_REF(image_kind); return TXT_GLOBAL; >:


::@=\\C[0-9]+\\@>   :< SCAN_UDEC(yytext+2); return TXT_CC; >:

::@=\\[a-l]@>       :< yylval.u=yytext[1]-'a'; return TXT_LOCAL; >:
::@=" "@>           :< return TXT_FONT_GLUE; >:
::@="-"@>           :< return TXT_FONT_HYPHEN; >:

::@={UTF8_1}@>            :< SCAN_UTF8_1(yytext); return TXT_CC; >:
::@={UTF8_2}@>            :< SCAN_UTF8_2(yytext); return TXT_CC; >:
::@={UTF8_3}@>            :< SCAN_UTF8_3(yytext); return TXT_CC; >:
::@={UTF8_4}@>            :< SCAN_UTF8_4(yytext); return TXT_CC; >:
}
@

@<scanning macros@>=
#define @[SCAN_REF(K)@] @[yylval.rf.k=K;@+ yylval.rf.n=atoi(yytext+2)@;@]
static int scan_level=0;
#define SCAN_START          @[yy_push_state(INITIAL);@+scan_level++;@]
#define SCAN_END            @[if (scan_level--) yy_pop_state(); @/else QUIT("Too many '>' in line %d",yylineno)@]
#define SCAN_TXT_START      @[BEGIN(TXT)@;@]
#define SCAN_TXT_END        @[BEGIN(INITIAL)@;@]
@
@s txt symbol

@<parsing rules@>=
list: TXT_START position @|
          {hpos+=4;  /* start byte, two size byte, and boundary byte */ }
           text TXT_END@|
          { $$.k=text_kind;$$.p=$4; $$.s=(hpos-hstart)-$4;
            hput_tags($2,hput_list($2+1, &($$)));@+};
text: position @+| text txt;

txt: TXT_CC { hput_txt_cc($1); }
   | TXT_FONT {  REF(font_kind,$1); hput_txt_font($1); }
   | TXT_GLOBAL { REF($1.k,$1.n); hput_txt_global(&($1)); }
   | TXT_LOCAL  { RNG("Font parameter",$1,0,11); hput_txt_local($1); }
   | TXT_FONT_GLUE { HPUTX(1); HPUT8(txt_glue); }
   | TXT_FONT_HYPHEN {  HPUTX(1);HPUT8(txt_hyphen); }
   | TXT_IGNORE {  HPUTX(1);HPUT8(txt_ignore); }
   | { HPUTX(1); HPUT8(txt_node);} content_node;
@

The following function keeps track of the position in the current line.
It the line gets too long it will break the text at the next space
character. If no suitable space character comes along,
the line will be broken after any regular character.

\writecode
@<write a text@>=
{@+if (l->s==0) hwritef(" \"\"");
   else@/
   { int pos=nesting+20; /* estimate */
     hwritef(" \"");
    while(hpos<hend)@/
    { int i=hget_txt();
      if (i<0)
      { if (pos++<70) hwritec(' '); 
        else hwrite_nesting(), pos=nesting;
      } 
      else if (i==1 && pos>=100)@/
      { hwritec('\\'); @+hwrite_nesting(); @+pos=nesting; @+}
      else
        pos+=i;
    }
    hwritec('"');
   }
}
@


The function returns the number of characters written 
because this information is needed in |hget_txt| below.

@<write functions@>=
int hwrite_txt_cc(uint32_t c)
{@+ if (c<0x20)
    return hwritef("\\C%d\\",c);
  else@+
  switch(c)
  { case '"': return hwritef("\\\"");
    case '<': return hwritef("\\<");
    case '>': return hwritef("\\>");
    case ' ': return hwritef("\\ ");
    case '-': return hwritef("\\-");
    default: if (option_utf8) return hwrite_utf8(c); else return hwritef("\\C%d\\",c);
  }
}
@

\getcode
@<get macros@>=
#define @[HGET_GREF(K,S)@] {uint8_t n=HGET8;@+ REF(K,n); @+ return hwritef("\\" S "%d\\",n);@+} 

@

The function |hget_txt| reads a text element and writes it immediately.
To enable the insertion of line breaks when writing a text, we need to keep track
of the number of characters in the current line. For this purpose
the function |hget_txt| returns the number of characters written.
It returns $-1$ if a space character needs to be written
providing a good opportunity for a break.

@<get functions@>=
int hget_txt(void)
{@+ if (*hpos>=0x80 && *hpos<=0xF7)
  { if (option_utf8) 
     return hwrite_utf8(hget_utf8());
    else
     return hwritef("\\C%d\\",hget_utf8());
  }
  else @/
  { uint8_t a;
    a=HGET8; 
    switch (a)
    { case txt_font+0: return hwritef("\\0");
      case txt_font+1: return hwritef("\\1");
      case txt_font+2: return hwritef("\\2");
      case txt_font+3: return hwritef("\\3");
      case txt_font+4: return hwritef("\\4");
      case txt_font+5: return hwritef("\\5");
      case txt_font+6: return hwritef("\\6");
      case txt_font+7: return hwritef("\\7");
      case txt_global+0: HGET_GREF(font_kind,"F");
      case txt_global+1: HGET_GREF(penalty_kind,"P");
      case txt_global+2: HGET_GREF(kern_kind,"K");
      case txt_global+3: HGET_GREF(ligature_kind,"L");
      case txt_global+4: HGET_GREF(hyphen_kind,"H");
      case txt_global+5: HGET_GREF(glue_kind,"G");
      case txt_global+6: HGET_GREF(math_kind,"M");
      case txt_global+7: HGET_GREF(rule_kind,"R");
      case txt_global+8: HGET_GREF(image_kind,"I");
      case txt_local+0: return hwritef("\\a");
      case txt_local+1: return hwritef("\\b");
      case txt_local+2: return hwritef("\\c");
      case txt_local+3: return hwritef("\\d");
      case txt_local+4: return hwritef("\\e");
      case txt_local+5: return hwritef("\\f");
      case txt_local+6: return hwritef("\\g");
      case txt_local+7: return hwritef("\\h");
      case txt_local+8: return hwritef("\\i");
      case txt_local+9: return hwritef("\\j");
      case txt_local+10: return hwritef("\\k");
      case txt_local+11: return hwritef("\\l");
      case txt_cc: return hwrite_txt_cc(hget_utf8()); 
      case txt_node: { int i;
                        @<read the start byte |a|@>@;
                        i=hwritef("<%s",content_name[KIND(a)]);@+ hget_content(a);
                        @<read and check the end byte |z|@>@;
                        hwritec('>');@+ return i+10; /* just an estimate */
                     }
      case txt_hyphen: hwritec('-'); @+return 1;
      case txt_glue: return -1;
      case '<': return hwritef("\\<");
      case '>': return hwritef("\\>");
      case '"': return hwritef("\\\"");
      case '-': return hwritef("\\-");
      case txt_ignore: return hwritef("\\@@");
      default: hwritec(a); @+return 1;
    }
  }
}

@


\putcode
@<put functions@>=

void hput_txt_cc(uint32_t c)
{ @+ if (c<=0x20) {  HPUTX(2); HPUT8(txt_cc);@+ HPUT8(c); @+ }
  else  hput_utf8(c);
}

void hput_txt_font(uint8_t f)
{@+ if (f<8)  HPUTX(1),HPUT8(txt_font+f);
  else QUIT("Use \\F%d\\ instead of \\%d for font %d in a text",f,f,f); 
}

void hput_txt_global(ref_t *d)
{ @+ HPUTX(2);
  switch (d->k)
  { case font_kind:   HPUT8(txt_global+0);@+ break;
    case penalty_kind:   HPUT8(txt_global+1);@+ break;
    case kern_kind:   HPUT8(txt_global+2);@+ break;
    case ligature_kind:   HPUT8(txt_global+3);@+ break;
    case hyphen_kind:   HPUT8(txt_global+4);@+ break;
    case glue_kind:   HPUT8(txt_global+5);@+ break;
    case math_kind:   HPUT8(txt_global+6);@+ break;
    case rule_kind:   HPUT8(txt_global+7);@+ break;
    case image_kind:   HPUT8(txt_global+8);@+ break;
    default: QUIT("Kind %s not allowed as a global reference in a text",NAME(d->k));
  }
  HPUT8(d->n);
}

void hput_txt_local(uint8_t n)
{ HPUTX(1);
  HPUT8(txt_local+n);
}


@

@<hint types@>=
typedef struct { @+kind_t k; @+uint8_t n; @+} ref_t;
@


\section{Composite Nodes}\hascode
\label{composite}
The nodes that we consider in this section contain other nodes for example
a glue node or a list of node. When we implement the parsing\index{parsing} routines
for composite nodes in the long format, we have to take into account 
that parsing such a glue node or list node  will already write the glue or list node
to the output. So we split the parsing of composite nodes into several parts
and store the parts immediately after parsing them. On the parse stack we will only
keep track of the info value.
This new strategy is not as transparent as  our previous strategy used for 
simple nodes where we had a clean separation of reading and writing:
reading would store the internal representation of a node and writing the internal
representation to output would start only after reading is completed.
The new strategy, however, makes it easier to reuse 
the grammar\index{grammar} rules for the component nodes.

\subsection{Boxes}
The central structuring elements of \TeX\ are boxes\index{box}.
Boxes have a height |h|, a depth |d|, and a width |w|. 
The shift amount |a| shifts the contents of the box, the glue ratio\index{glue ratio} |r| is a factor
applied to the glue inside the box, the glue order |o| is its order of stretchability\index{stretchability},
and the glue sign |s| is $-1$ for shrinking\index{shrinkability}, 0 for rigid, and $+1$ for stretching.
Most importantly, a box contains a list |l| of elements inside the box.


@<hint types@>=
typedef struct @/{@+ dimen_t h,d,w,a;@+ float32_t r;@+ int8_t s,o; @+list_t l; @+} box_t;
@

There are two types of boxes: horizontal\index{horizontal box} boxes 
and vertical\index{vertical box} boxes.
The difference between the two is simple: 
a horizontal box aligns the reference\index{reference point}
points of its elements horizontally, the shift amount\index{shift amount} |a| 
shifts the box down; 
a vertical box aligns\index{alignment} the reference\index{reference point} 
points vertically,  the shift amount |a| shifts the box right.

Not all box parameters are used frequently. In the short format, we use the info bits
to indicated which of the parameters are used.
Where as the width of a horizontal box is most of the time (80\%) nonzero, 
other parameters are most of the time zero, 
like the shift amount (99\%) or the glue settings (99.8\%). 
The depth is zero in about 77\%, the height in about 53\%, 
and both together are zero in about 47\%. The results for vertical boxes, 
which constitute about 20\% of all boxes, are similar, 
except that the depth is zero in about 89\%, 
but the height and width are almost never zero.
For this reason we use bit |b001| to indicate a nonzero depth,
bit |b010|  for a nonzero shift amount, and |b100| for nonzero glue settings.
Glue sign and glue order can be packed as two nibbles in a single byte.
% A different use of the info bits for vertical and horizontal boxes is possible, 
% but does not warrant the added complexity.



\goodbreak
\readcode
@s HBOX symbol
@s VBOX symbol
@s box symbol
@s boxparams symbol
@s hbox_node symbol
@s vbox_node symbol
@s box_dimen symbol
@s box_shift symbol
@s box_glue_set symbol
@<symbols@>=
%token HBOX     "hbox"
%token VBOX     "vbox"
%type <info> box box_dimen box_shift box_glue_set

@
@<scanning rules@>=
::@=hbox@>       :< return HBOX; >:
::@=vbox@>       :< return VBOX; >:
@

@<parsing rules@>=@/

box_dimen: dimension dimension dimension @/
           {$$= hput_box_dimen($1,$2,$3); };
box_shift: {$$=b000;} @+ 
   | dimension {$$=hput_box_shift($1);};

box_glue_set:  {$$=b000;}
        | PLUS stretch { $$=hput_box_glue_set(+1,$2.f,$2.o); }
        | MINUS stretch  { $$=hput_box_glue_set(-1,$2.f,$2.o); }; 


box: box_dimen box_shift box_glue_set list  {$$=$1|$2|$3; };

hbox_node: start HBOX box END { hput_tags($1, TAG(hbox_kind,$3)); };
vbox_node: start VBOX box END { hput_tags($1, TAG(vbox_kind,$3)); };
content_node: hbox_node @+ | vbox_node;
@

\writecode
@<write functions@>=
void hwrite_box(box_t *b)
{ hwrite_dimension(b->h); 
  hwrite_dimension(b->d); 
  hwrite_dimension(b->w);
  if (b->a!=0)  { hwritef(" (shifted)"); @+hwrite_dimension(b->a); @+}
  if (b->r!=0.0 && b->s!=0  )@/ 
  { @+if (b->s>0) @+hwritef(" plus"); @+else @+hwritef(" minus");
    @+hwrite_float64(b->r); @+hwrite_order(b->o);
  }
  hwrite_list(&(b->l));
}
@

\getcode

@<cases to get content@>=
case TAG(hbox_kind,b000): @+{box_t b; @+HGET_BOX(b000,b); @+hwrite_box(&b);@+} @+ break;
case TAG(hbox_kind,b001): @+{box_t b; @+HGET_BOX(b001,b); @+hwrite_box(&b);@+} @+ break;
case TAG(hbox_kind,b010): @+{box_t b; @+HGET_BOX(b010,b); @+hwrite_box(&b);@+} @+ break;
case TAG(hbox_kind,b011): @+{box_t b; @+HGET_BOX(b011,b); @+hwrite_box(&b);@+} @+ break;
case TAG(hbox_kind,b100): @+{box_t b; @+HGET_BOX(b100,b); @+hwrite_box(&b);@+} @+ break;
case TAG(hbox_kind,b101): @+{box_t b; @+HGET_BOX(b101,b); @+hwrite_box(&b);@+} @+ break;
case TAG(hbox_kind,b110): @+{box_t b; @+HGET_BOX(b110,b); @+hwrite_box(&b);@+} @+ break;
case TAG(hbox_kind,b111): @+{box_t b; @+HGET_BOX(b111,b); @+hwrite_box(&b);@+} @+ break;
case TAG(vbox_kind,b000): @+{box_t b; @+HGET_BOX(b000,b); @+hwrite_box(&b);@+} @+ break;
case TAG(vbox_kind,b001): @+{box_t b; @+HGET_BOX(b001,b); @+hwrite_box(&b);@+} @+ break;
case TAG(vbox_kind,b010): @+{box_t b; @+HGET_BOX(b010,b); @+hwrite_box(&b);@+} @+ break;
case TAG(vbox_kind,b011): @+{box_t b; @+HGET_BOX(b011,b); @+hwrite_box(&b);@+} @+ break;
case TAG(vbox_kind,b100): @+{box_t b; @+HGET_BOX(b100,b); @+hwrite_box(&b);@+} @+ break;
case TAG(vbox_kind,b101): @+{box_t b; @+HGET_BOX(b101,b); @+hwrite_box(&b);@+} @+ break;
case TAG(vbox_kind,b110): @+{box_t b; @+HGET_BOX(b110,b); @+hwrite_box(&b);@+} @+ break;
case TAG(vbox_kind,b111): @+{box_t b; @+HGET_BOX(b111,b); @+hwrite_box(&b);@+} @+ break;
@

@<get macros@>=
#define @[HGET_BOX(I,B)@] \
HGET32(B.h);\
if ((I)&b001) HGET32(B.d); @+ else B.d=0;\ 
HGET32(B.w);\
if ((I)&b010) HGET32(B.a); @+else B.a=0;\ 
if ((I)&b100) @/{ B.r=hget_float32();@+ B.s=HGET8; @+ B.o=B.s&0xF; @+B.s=B.s>>4;@+ }\
else {  B.r=0.0;@+ B.o=B.s=0;@+ }\
hget_list(&(B.l));
@

@<get functions@>=
void hget_hbox_node(void)
{ box_t b;
  @<read the start byte |a|@>@;
   if (KIND(a)!=hbox_kind) QUIT("Hbox expected at 0x%x got %s",node_pos,NAME(a));
   HGET_BOX(INFO(a),b);@/
   @<read and check the end byte |z|@>@;
   hwrite_start();@+
   hwritef("hbox");@+
   hwrite_box(&b);@+
   hwrite_end();
}


void hget_vbox_node(void)
{ box_t b;
  @<read the start byte |a|@>@;
  if (KIND(a)!=vbox_kind) QUIT("Vbox expected at 0x%x got %s",node_pos,NAME(a));
  HGET_BOX(INFO(a),b);@/
  @<read and check the end byte |z|@>@;
  hwrite_start();@+
  hwritef("vbox");@+
  hwrite_box(&b);@+
  hwrite_end();
}
@

\putcode
@<put functions@>=

info_t hput_box_dimen(dimen_t h, dimen_t d, dimen_t w)
{ info_t i; 
 @+HPUT32(h);
  if (d!=0) { HPUT32(d); @+i=b001;@+ } @+else@+ i=b000; 
  HPUT32(w);
  return i;
}
info_t hput_box_shift(dimen_t a)
{ @+if (a!=0) { @+ HPUT32(a);  @+return @+ b010;@+} @+ else  @+return b000;
}

info_t hput_box_glue_set(int8_t s, float32_t r, order_t o)
{ @+if (r!=0.0 && s!=0 ) 
  { hput_float32(r);@+
    HPUT8((s<<4)|o);@+
    return b100;@+
  }
  else return b000;
}

@

\subsection{Extended Boxes}
Hi\TeX\ produces two kinds of extended\index{extended box} horizontal
boxes, |hpack_kind| and |hset_kind|, and the same for vertical boxes
using |vpack_kind| and |vset_kind|.  Let us focus on horizontal boxes;
the handling of vertical boxes is completely parallel.

The \\{hpack} procedure of Hi\TeX\ produces an extended box if it is
given an extended\index{extended dimension} dimension as its width or
if it discovers that the width of its content is an extended
dimension.  After the final width of the box has been computed in the
viewer, it just remains to set the glue; a very simple operation
indeed.

If the \\{hpack} procedure of Hi\TeX\ can not determine the natural
dimensions of the box content because it contains
paragraphs\index{paragraph} or other extended boxes, it produces a box
of |hpack_kind|.  Now the viewer needs to traverse the list of content
nodes to determine the natural\index{natural dimension}
dimensions. Even the amount of stretchability\index{stretchability}
and shrinkability\index{shrinkability} has to be determined in the
viewer. For example the final stretchability of a paragraph with some
stretchability in the baseline\index{baseline skip} skip will depend
on its number of lines which, in turn, depends on \.{hsize}.  It is
not possible to merge this traversals of the box content with the
traversal necessary when displaying the box. The latter needs to
convert glue nodes into positioning instructions which requires a
fixed glue\index{glue ratio} ratio. The computation of the glue ratio,
however, requires a complete traversal of the content.

In the short format of a box of type |hset_kind| or |vset_kind|, 
info bit |b100| indicates if set, a complete extended dimension, and if unset, 
a reference to a predefined extended dimension for the target size;
info bit |b010| indicates a nonzero shift amount,
and info bit |b001| indicates a nonzero depth.

In the short format of a box of type |hpack_kind| or |vset_kind|, 
info bit |b100| indicates if set, a complete extended dimension, and if unset, 
a reference to a predefined extended dimension for the target size;
info bit |b010| indicates if set, an additional target size, and if unset an exact target size; and
info bit |b001| indicates a maximum depth less than |MAX_DIMEN| 
(this is used only for vertical lists).

\readcode
@s xbox symbol
@s hpack symbol
@s vpack symbol
@s box_goal symbol
@s HPACK symbol
@s HSET symbol
@s VPACK symbol
@s VSET symbol
@s TO symbol
@s ADD symbol
@s box_flex symbol
@<symbols@>=
%token HPACK "hpack"
%token HSET  "hset"
%token VPACK "vpack"
%token VSET  "vset"

%token ADD "add"
%token TO "to"
%type <info> xbox box_goal hpack vpack
@

@<scanning rules@>=
::@=hpack@>  :< return HPACK; >:
::@=hset@>  :< return HSET; >:
::@=vpack@>  :< return VPACK; >:
::@=vset@>  :< return VSET; >:
::@=add@>  :< return ADD; >:
::@=to@>  :< return TO; >:
@

@<parsing rules@>=
box_flex: plus minus { hput_stretch(&($1));hput_stretch(&($2)); };
xbox: xdimen_ref  box_dimen box_shift box_flex list {$$=$2|$3;} 
     | xdimen_node box_dimen box_shift box_flex list {$$=$2|$3|b100;};

box_goal: TO xdimen_ref {$$=b000;} 
      | ADD xdimen_ref  {$$=b010;} 
      | TO xdimen_node {$$=b100;} 
      | ADD xdimen_node {$$=b110;}; 

hpack: box_goal list;
vpack: box_goal list 
     | box_goal dimension @+{@+ if ($2!=MAX_DIMEN) HPUT32($2);@+ } list @/
       {@+if ($2!=MAX_DIMEN) $$=$1|b001; @+ else $$=$1;@+ }; 

content_node: start HSET xbox END   { hput_tags($1, TAG(hset_kind,$3)); }
            | start HPACK hpack END  { hput_tags($1, TAG(hpack_kind,$3)); }
            | start VSET xbox END   { hput_tags($1, TAG(vset_kind,$3)); }
            | start VPACK vpack END  { hput_tags($1, TAG(vpack_kind,$3)); };
@

\getcode
@<cases to get content@>=
case TAG(hset_kind,b000): HGET_SET(b000); @+ break;
case TAG(hset_kind,b001): HGET_SET(b001); @+ break;
case TAG(hset_kind,b010): HGET_SET(b010); @+ break;
case TAG(hset_kind,b011): HGET_SET(b011); @+ break;
case TAG(hset_kind,b100): HGET_SET(b100); @+ break;
case TAG(hset_kind,b101): HGET_SET(b101); @+ break;
case TAG(hset_kind,b110): HGET_SET(b110); @+ break;
case TAG(hset_kind,b111): HGET_SET(b111); @+ break;@#

case TAG(vset_kind,b000): HGET_SET(b000); @+ break;
case TAG(vset_kind,b001): HGET_SET(b001); @+ break;
case TAG(vset_kind,b010): HGET_SET(b010); @+ break;
case TAG(vset_kind,b011): HGET_SET(b011); @+ break;
case TAG(vset_kind,b100): HGET_SET(b100); @+ break;
case TAG(vset_kind,b101): HGET_SET(b101); @+ break;
case TAG(vset_kind,b110): HGET_SET(b110); @+ break;
case TAG(vset_kind,b111): HGET_SET(b111); @+ break;@#

case TAG(hpack_kind,b000): HGET_PACK(b000); @+ break;
case TAG(hpack_kind,b010): HGET_PACK(b010); @+ break;
case TAG(hpack_kind,b100): HGET_PACK(b100); @+ break;
case TAG(hpack_kind,b110): HGET_PACK(b110); @+ break;@#

case TAG(vpack_kind,b000): HGET_PACK(b000); @+ break;
case TAG(vpack_kind,b010): HGET_PACK(b010); @+ break;
case TAG(vpack_kind,b100): HGET_PACK(b100); @+ break;
case TAG(vpack_kind,b110): HGET_PACK(b110); @+ break;
case TAG(vpack_kind,b001): HGET_PACK(b001); @+ break;
case TAG(vpack_kind,b011): HGET_PACK(b011); @+ break;
case TAG(vpack_kind,b101): HGET_PACK(b101); @+ break;
case TAG(vpack_kind,b111): HGET_PACK(b111); @+ break;
@


@<get macros@>=
#define @[HGET_SET(I)@] @/\
 if ((I)&b100) {xdimen_t x; hget_xdimen_node(&x); @+hwrite_xdimen_node(&x);@+} else HGET_REF(xdimen_kind)@;\
 { dimen_t h; @+HGET32(h); @+hwrite_dimension(h);@+} \
 { dimen_t d; @+if ((I)&b001) HGET32(d); @+ else d=0;@+hwrite_dimension(d); @+}\ 
 { dimen_t w; @+HGET32(w); @+hwrite_dimension(w);@+} \
if ((I)&b010)  { dimen_t a; @+HGET32(a);@+hwrite_dimension(a);@+} \
 { stretch_t p; @+HGET_STRETCH(p);@+hwrite_plus(&p);@+}\
 { stretch_t m; @+HGET_STRETCH(m);@+hwrite_minus(&m);@+}\
 { list_t l; @+hget_list(&l);@+ hwrite_list(&l); @+} 
@#

#define @[HGET_PACK(I)@] @/\
 if ((I)&b010) hwritef(" add");@+ else hwritef(" to");\
 if ((I)&b100) {xdimen_t x; hget_xdimen_node(&x); @+hwrite_xdimen_node(&x);@+} @+ else HGET_REF(xdimen_kind);\
 if ((I)&b001)  { dimen_t d; @+HGET32(d); @+hwrite_dimension(d);  @+ }\
 { list_t l; @+hget_list(&l);@+ hwrite_list(&l); @+} 
@


\subsection{Kerns}
A kern\index{kern} is a bit of white space with a certain length. If the kern is part of a
horizontal list, the length is measured in the horizontal direction,
if it is part of a vertical list, it is measured in the vertical
direction. The length of a kern is mostly given as a dimension
but provisions are made to use extended dimensions as well.

The typical
use of a kern is its insertion between two characters to make the natural 
distance between them a bit wider or smaller. In the latter case, the kern
has a negative length. The typographic optimization just described is called
``kerning'' and has given the kern node its name. 
Kerns inserted from font information or math mode calculations are normal kerns, 
while kerns inserted from \TeX's {\tt \BS kern} or {\tt \BS/} 
commands are explicit kerns. 
Kern nodes do not disappear at a line break unless they are explicit\index{explicit kern}.

In the long format, explicit kerns are marked with an ``!'' sign
and in the short format with the |b100| info bit.
The two low order info bits are: 0 for a reference to a dimension, 1 for a reference to
an extended dimension, 2 for an immediate dimension, and 3 for an immediate extended dimension node.
To distinguish in the long format between a reference to a dimension and a reference to an extended dimension,
the latter is prefixed with the keyword ``{\tt xdimen}'' (see section~\secref{reference}).

@<hint types@>=
typedef struct {@+
bool x;@+
xdimen_t d;@+ 
} kern_t;
@

\readcode
@s KERN symbol
@s EXPLICIT symbol
@s kern symbol
@s explicit symbol
@<symbols@>=
%token KERN "kern"
%token EXPLICIT "!"
%type <b> explicit 
%type <kt> kern
@

@<scanning rules@>=
::@=kern@>  :< return KERN; >:
::@=!@>     :< return EXPLICIT; >:
@

@<parsing rules@>=
explicit: {$$=false;} @+| EXPLICIT {$$=true;};
kern: explicit xdimen {$$.x=$1; $$.d=$2;};
content_node: start KERN kern END { hput_tags($1,hput_kern(&($3)));}
@

\writecode
@<write functions@>=
void hwrite_explicit(bool x)
{ @+if (x) hwritef(" !"); @+}

void hwrite_kern(kern_t *k)
{ @+hwrite_explicit(k->x);
  if (k->d.h==0.0 && k->d.v==0.0 && k->d.w==0) hwrite_ref(zero_dimen_no);
  else hwrite_xdimen(&(k->d));
} 
@

\getcode
@<cases to get content@>=
case TAG(kern_kind,b010): @+  {@+kern_t k; @+HGET_KERN(b010,k);@+ } @+break;
case TAG(kern_kind,b011): @+  {@+kern_t k; @+HGET_KERN(b011,k);@+ } @+break;
case TAG(kern_kind,b110): @+  {@+kern_t k; @+HGET_KERN(b110,k);@+ } @+break;
case TAG(kern_kind,b111): @+  {@+kern_t k; @+HGET_KERN(b111,k);@+ } @+break;
@

@<get macros@>=
#define @[HGET_KERN(I,K)@] \
K.x=(I)&b100;\
if (((I)&b011)==2) {HGET32(K.d.w);@+ K.d.h=K.d.v=0.0;@+}\
else if (((I)&b011)==3) hget_xdimen_node(&(K.d));\
hwrite_kern(&k);
@

\putcode
@<put functions@>=
uint8_t hput_kern(kern_t *k)
{ info_t info;
  if (k->x) info=b100; @+else info=b000;
  if (k->d.h==0.0 && k->d.v==0.0)
  { if (k->d.w==0) HPUT8(zero_dimen_no);
    else {HPUT32(k->d.w); info=info|2;@+}
  }
  else {hput_xdimen_node(&(k->d));info=info|3;@+}
  return TAG(kern_kind,info);
}
@


\subsection{Leaders}\label{leaders}
Leaders\index{leaders} are a special type of glue that is best explained by a few
examples.  
Where as ordinary glue fills its designated space with \hfil\ whiteness,\break 
leaders fill their designated space with either a rule \xleaders\hrule\hfil\ or\break 
some sort of repeated\leaders\hbox to 15pt{$\hss.\hss$}\hfil content.\break 
In multiple leaders, the dots\leaders\hbox to 15pt{$\hss.\hss$}\hfil are usually aligned\index{alignment} across lines,\break 
as in the last\leaders\hbox to 15pt{$\hss.\hss$}\hfil three lines.\break
Unless you specify centered\index{centered}\cleaders\hbox to 15pt{$\hss.\hss$}\hfil leaders\break 
or you specify expanded\index{expanded}\xleaders\hbox to 15pt{$\hss.\hss$}\hfil leaders.\break 
The former pack the repeated content tight and center
the repeated content in the available space, the latter distributes
the extra space between all the repeated instances. 

In the short format, the two lowest info bits store the type
of leaders: 1 for aligned, 2 for centered, and 3 for expanded. 


\readcode
@s LEADERS symbol
@s ALIGN symbol
@s CENTER symbol
@s EXPAND symbol
@s leaders symbol
@s ltype symbol
@<symbols@>=
%token LEADERS "leaders"
%token ALIGN "align"
%token CENTER "center"
%token EXPAND "expand"
%type <info> leaders
%type <info> ltype
@

@<scanning rules@>=
::@=leaders@>       :< return LEADERS; >:
::@=align@>         :< return ALIGN; >:
::@=center@>        :< return CENTER; >:
::@=expand@>        :< return EXPAND; >:
@
@<parsing rules@>=
ltype: {$$=1;} | ALIGN {$$=1;} @+| CENTER {$$=2;} @+| EXPAND {$$=3;};
leaders: glue_node ltype rule_node {$$=$2;}
       | glue_node ltype hbox_node {$$=$2;}
       | glue_node ltype vbox_node {$$=$2;};
content_node: start LEADERS leaders END { hput_tags($1, TAG(leaders_kind, $3));}
@

\writecode
@<write functions@>=
void  hwrite_leaders_type(int t)
{@+ 
  if (t==2) hwritef(" center");
  else if (t==3) hwritef(" expand");
}
@

\getcode

@<cases to get content@>=
case TAG(leaders_kind,1):        @+ HGET_LEADERS(1); @+break;
case TAG(leaders_kind,2):        @+ HGET_LEADERS(2); @+break;
case TAG(leaders_kind,3):        @+ HGET_LEADERS(3); @+break;
@
@<get macros@>=
#define @[HGET_LEADERS(I)@]@/ \
hget_glue_node();\
hwrite_leaders_type((I)&b011);\
if (KIND(*hpos)==rule_kind) hget_rule_node(); \
else if (KIND(*hpos)==hbox_kind) hget_hbox_node(); \
else  hget_vbox_node();
@

\subsection{Baseline Skips}
Baseline\index{baseline skip} skips are small amounts of glue inserted between two consecutive lines
of text. To get nice looking pages, the amount of glue\index{glue} inserted must take into
account the depth of the line above the glue and the height of the line below the
glue to achieve a constant distance of the baselines. For example, if we have the lines
\medskip

\qquad\vbox{\hsize=0.5\hsize\noindent
``There is no\hfil\break
more gas\hfil\break
in the tank.''
}\hss

\medskip\noindent
\TeX\ will insert 7.69446pt of baseline skip between the first and the second line and
3.11111pt of baseline skip between the second and the third line. This is due to the
fact that the first line has no descenders, its depth is zero, the second line
has no ascenders but the ``g'' descends below the baseline, and the third line
has ascenders (``t'', ``h'',\dots) so it is higher than the second line. 
\TeX's choice of baseline skips ensures that the baselines are exactly 12pt apart
in both cases.

Things get more complicated if the text contains mathematical formulas because then
a line can get so high or deep that it is impossible to keep the distance between
baselines constant without two adjacent lines touching each other. In such cases,
\TeX\ will insert a small minimum line skip glue\index{line skip glue}.

For the whole computation, \TeX\ uses three parameters: {\tt baselineskip},
{\tt line\-skip\-limit},\index{line skip limit} and {\tt lineskip}.
\.{baselineskip} is a glue value; its size is the normal distance of two baselines.
\TeX\ adjusts the size of the \.{baselineskip} glue for the height and the depth of
the two lines and then checks the result against \.{lineskiplimit}.
If the result is smaller than \.{lineskiplimit} it will use the \.{lineskip} glue
instead.

Because the depth and the height of lines depend on the outcome of the line breaking\index{line breaking}
routine, baseline computations must be done in the viewer.
The situation gets even more complicated because \TeX\ can manipulate the insertion
of baseline skips in various ways. Therefore \HINT/ requires the insertion of 
baseline nodes wherever the viewer is supposed to perform a baseline skip
computation.

In the short format of a baseline definition, we store only the nonzero components and use the
info bits to mark them: |b100| implies $|bs|\ne0$,
|b010| implies $|ls|\ne 0$, and |b001| implies  $|lslimit|\ne 0$.
If the baseline has only zero components, we put a reference to baseline number 0
in the output.

@<hint basic types@>=
typedef struct {@+
glue_t bs, ls;@+
dimen_t lsl;@+
} baseline_t;
@



\readcode
@s BASELINE symbol
@s baseline symbol
@<symbols@>=
%token BASELINE "baseline"
%type <info> baseline
@
@<scanning rules@>=
::@=baseline@>  :< return BASELINE; >:
@

@<parsing rules@>=
baseline: glue_node glue_node dimension @/{ $$=b000;
                                            if ($1) $$|=b100;
                                            if ($2) $$|=b010;
                                            if ($3!=0) {HPUT32($3);$$|=b001;@+}@+};
content_node: start BASELINE baseline END @/
{ @+if ($3==b000) HPUT8(0); @+hput_tags($1,TAG(baseline_kind, $3)); };
@

\getcode

@<cases to get content@>=
case TAG(baseline_kind,b001): @+{ baseline_t b;@+ HGET_BASELINE(b001,b);@+ }@+break;
case TAG(baseline_kind,b010): @+{ baseline_t b;@+ HGET_BASELINE(b010,b);@+ }@+break;
case TAG(baseline_kind,b011): @+{ baseline_t b;@+ HGET_BASELINE(b011,b);@+ }@+break;
case TAG(baseline_kind,b100): @+{ baseline_t b;@+ HGET_BASELINE(b100,b);@+ }@+break;
case TAG(baseline_kind,b101): @+{ baseline_t b;@+ HGET_BASELINE(b101,b);@+ }@+break;
case TAG(baseline_kind,b110): @+{ baseline_t b;@+ HGET_BASELINE(b110,b);@+ }@+break;
case TAG(baseline_kind,b111): @+{ baseline_t b;@+ HGET_BASELINE(b111,b);@+ }@+break;
@

@<get macros@>=
#define @[HGET_BASELINE(I,B)@] \
  if((I)&b100) hget_glue_node(); \
  else {B.bs.p.o=B.bs.m.o=B.bs.w.w=0; @+B.bs.w.h=B.bs.w.v=B.bs.p.f=B.bs.m.f=0.0; @+hwrite_glue_node(&(B.bs));@+}\
  if((I)&b010) hget_glue_node(); \
  else {B.ls.p.o=B.ls.m.o=B.ls.w.w=0; @+B.ls.w.h=B.ls.w.v=B.ls.p.f=B.ls.m.f=0.0; @+hwrite_glue_node(&(B.ls));@+}\
  if((I)&b001) HGET32((B).lsl); @+else B.lsl=0; \
  hwrite_dimension(B.lsl); 
@


\putcode
@<put functions@>=
uint8_t hput_baseline(baseline_t *b)
{ info_t info=b000;
  if (!ZERO_GLUE(b->bs)) @+info|=b100;
  if (!ZERO_GLUE(b->ls)) @+ info|=b010; 
  if (b->lsl!=0) { @+ HPUT32(b->lsl); @+info|=b001; @+} 
  return TAG(baseline_kind,info);
}
@



\subsection{Ligatures}
Ligatures\index{ligature} occur only in horizontal lists.  They specify characters
that combines the glyphs of several characters into one specialized
glyph. For example in the word ``{\it difficult\/}'' the three letters
``{\it f{}f{}i\/}'' are combined into the ligature ``{\it ffi\/}''.
Hence, a ligature is very similar to a simple glyph node; the
characters that got replaced are, however, retained in the ligature
because they might be needed for example to support searching. Since
ligatures are therefore only specialized list of characters and since
we have a very efficient way to store such lists of characters, namely
as a |text|, input and output of ligatures is quite simple.

The info value zero is reserved for references to a ligature.  If the
info value is between 1 and 6, it gives the number of bytes used to encode
the characters in UTF8.  Note that a ligature will always include a
glyph byte, so the minimum size is 1. A typical ligature like ``{\it fi\/}'' 
will need 3 byte: the ligature character ``{\it fi\/}'', and
the replacement characters ``f'' and ''i''. More byte might be
required if the character codes exceed |0x7F|, since we use the UTF8
encoding scheme for larger character codes.  If the info value is 7,
an additional byte following the font byte and preceding the end byte
gives the total size needed for the character codes.  In the long
format, we give the font, the character code, and then the replacement
characters coded in utf8.

@<hint types@>=
typedef struct{@+uint8_t f; @+list_t l;@+} lig_t;
@

\readcode
@s LIGATURE  symbol
@s ligature symbol
@s replace_cc symbol
@s lig_cc symbol
@<symbols@>=
%token LIGATURE     "ligature"
%type <u>  lig_cc 
%type <lg> ligature
@
@<scanning rules@>=
::@=ligature@>              :<     return LIGATURE;    >:
@

@<parsing rules@>=@/
replace_cc:@+ | replace_cc TXT_CC { hput_utf8($2); };
lig_cc:  UNSIGNED {$$=hpos-hstart; hput_utf8($1); };
lig_cc:  CHARCODE {$$=hpos-hstart; hput_utf8($1); };
ligature:  REFERENCE { REF(font_kind,$1); HPUT8($1);}   lig_cc TXT_START replace_cc TXT_END @/
          { $$.f=$1; $$.l.p=$3; $$.l.s=(hpos-hstart)-$3; 
            RNG("Ligature size",$$.l.s,0,255);};
content_node: start LIGATURE ligature END {hput_tags($1,hput_ligature(&($3)));};
@

\writecode
@<write functions@>=
void hwrite_ligature(lig_t *l)
{ uint32_t pos=hpos-hstart;
  hwritef(" *%d",l->f);
  hpos=l->l.p+hstart;
  hwrite_charcode(hget_utf8());
  hwritef(" \"");
  while (hpos<hstart+l->l.p+l->l.s)
    hwrite_txt_cc(hget_utf8());
  hwritec('"');
  hpos=hstart+pos;
}
@

\getcode
@<cases to get content@>=
case TAG(ligature_kind,1):@+ {lig_t l; @+HGET_LIG(1,l);@+} @+break;
case TAG(ligature_kind,2):@+ {lig_t l; @+HGET_LIG(2,l);@+} @+break;
case TAG(ligature_kind,3):@+ {lig_t l; @+HGET_LIG(3,l);@+} @+break;
case TAG(ligature_kind,4):@+ {lig_t l; @+HGET_LIG(4,l);@+} @+break;
case TAG(ligature_kind,5):@+ {lig_t l; @+HGET_LIG(5,l);@+} @+break;
case TAG(ligature_kind,6):@+ {lig_t l; @+HGET_LIG(6,l);@+} @+break;
case TAG(ligature_kind,7):@+ {lig_t l; @+HGET_LIG(7,l);@+} @+break;
@
@<get macros@>=
#define @[HGET_LIG(I,L)@] @/\
(L).f=HGET8;\
if ((I)==7) (L).l.s=HGET8;@+else (L).l.s=(I);\
(L).l.p=hpos-hstart; @+ hpos+=(L).l.s; \
if ((I)==7)@/\
{ uint8_t n=HGET8; \
  if(n!=(L).l.s) @/\
  QUIT("Sizes in ligature don't match %d!=%d",(L).l.s,n);}\
hwrite_ligature(&(L));
@

\putcode
@<put functions@>=
uint8_t hput_ligature(lig_t *l)
{ @+if (l->l.s < 7) return TAG(ligature_kind,l->l.s);
  else@/
  { memmove(hstart+l->l.p+1,hstart+l->l.p,l->l.s);@+ hpos++;
    *(hstart+l->l.p)=*hpos++=l->l.s;
     return TAG(ligature_kind,7);
  }
}
@


\subsection{Hyphenation}\label{hyphen}\index{hyphen}
\HINT/ is capable to break lines into paragraphs. It does this primarily at inter-word
spaces but it might also break a line in the middle of a word if it finds a discretionary\index{discretionary break}
line break there. These discretionary breaks are usually provided by an automatic hyphenation
algorithm but they might be also explicitly\index{explicit hyphen} inserted by the author of a document.

When a line break occurs at such a discretionary break, the line before the break ends
with a |pre_break| list of nodes, the line after the break starts with a |post_break|
list of nodes, and the next |replace_count| nodes after the discretionary break will
be ignored. Both lists must consist entirely of glyphs\index{glyph}, kerns\index{kern}, boxes\index{box}, rules\index{rule}, or ligatures\index{ligature}.
For example, an ordinary discretionary hyphen will have a |pre_break| list 
containing ``-'', an empty |post_break| list, and a |replace_count| of zero.

The long format starts with an optional ``{\tt !}'' indicating an explicit hyphen,
followed by the  |pre_break| list, then comes the replace-count followed
by the  |post_break| list. An empty  |pre_break| or |post_break| list may be omitted.

In the short format, the three components of a hyphen node are stored in this order: 
|pre_break| list, |post_break| list, and  |replace_count|. 
The |b100| bit in the info value indicates the presence of a 
|pre_break| list, the |b010| bit the presence of a |post_break| list, and
the |b001| bit the presence of a replace-count.
Since the info value |b000| is
reserved for references, at least one of these must be specified; so we represent
a node with empty lists and a replace\index{replace count} count of zero using the info value |b001|
and a zero byte for the replace count.

Replace counts must be in the range 0 to 31; so the short format can set the high bit 
of the replace count to indicate an explicit hyphen.

@<hint types@>= typedef struct hyphen_t@+ {@+ bool x; @+list_t p,q;@+ uint8_t r;@+ } hyphen_t; @


\readcode
@s HYPHEN  symbol
@s hyphen  symbol
@s hyphen_node  symbol
@s opt_list symbol
@<symbols@>=
%token HYPHEN     "hyphen"
%type <hy> hyphen hyphen_node
%type <l>  opt_list
@
@<scanning rules@>=
::@=hyphen@>              :<     return HYPHEN;    >:
@

@<parsing rules@>=@/
opt_list: {$$.p=hpos-hstart; $$.s=0; $$.k=list_kind; } | list {@+if ($1.s==0) hpos=hpos-2; @+$$=$1;};
hyphen: explicit opt_list UNSIGNED opt_list @/
       { $$.x=$1;   $$.p=$2; RNG("Replace count",$3,0,31);  $$.r=$3; $$.q=$4; };
hyphen_node: start HYPHEN hyphen END @/
       {hput_tags($1,hput_hyphen(&($3)));$$=$3;};
content_node: hyphen_node;
@

\writecode
@<write functions@>=
void  hwrite_hyphen(hyphen_t *h)
{ @+hwrite_explicit(h->x);
    if (h->p.s!=0) hwrite_list(&(h->p));
    hwritef(" %d",h->r);
    if (h->q.s!=0) hwrite_list(&(h->q));
}
void hwrite_hyphen_node(hyphen_t *h)
{ @+ hwrite_start(); @+hwritef("hyphen"); @+ hwrite_hyphen(h); @+hwrite_end();}
@

\getcode
@<cases to get content@>=
case TAG(hyphen_kind,b001): {hyphen_t h; @+HGET_HYPHEN(b001,h);@+ hwrite_hyphen(&h); @+} @+break;
case TAG(hyphen_kind,b010): {hyphen_t h; @+HGET_HYPHEN(b010,h);@+ hwrite_hyphen(&h); @+} @+break;
case TAG(hyphen_kind,b011): {hyphen_t h; @+HGET_HYPHEN(b011,h);@+ hwrite_hyphen(&h); @+} @+break;
case TAG(hyphen_kind,b100): {hyphen_t h; @+HGET_HYPHEN(b100,h);@+ hwrite_hyphen(&h); @+} @+break;
case TAG(hyphen_kind,b101): {hyphen_t h; @+HGET_HYPHEN(b101,h);@+ hwrite_hyphen(&h); @+} @+break;
case TAG(hyphen_kind,b110): {hyphen_t h; @+HGET_HYPHEN(b110,h);@+ hwrite_hyphen(&h); @+} @+break;
case TAG(hyphen_kind,b111): {hyphen_t h; @+HGET_HYPHEN(b111,h);@+ hwrite_hyphen(&h); @+} @+break;
@

@<get macros@>=
#define @[HGET_HYPHEN(I,Y)@]\
if ((I)&b100) hget_list(&((Y).p)); else { (Y).p.p=hpos-hstart; @+(Y).p.s=0; @+(Y).p.k=list_kind; @+}\
if ((I)&b010) hget_list(&((Y).q)); else { (Y).q.p=hpos-hstart; @+(Y).q.s=0; @+(Y).q.k=list_kind; @+}\
if ((I)&b001) {uint8_t r=HGET8; (Y).r=r&0x7F; @+ RNG("Replace count",(Y).r,0,31); @+(Y).x=(r&0x80)!=0; @+}\
@+else { (Y).r=0; @+ (Y).x=false;@+}
@

@<get functions@>=
void hget_hyphen_node(hyphen_t *h)
{ @<read the start byte |a|@>@;
   if (KIND(a)!=hyphen_kind || INFO(a)==b000) 
      QUIT("Hyphen expected at 0x%x got %s,%d",node_pos,NAME(a),INFO(a));
   HGET_HYPHEN(INFO(a),*h);
   @<read and check the end byte |z|@>@;
}
@

\putcode
@<put functions@>=
uint8_t hput_hyphen(hyphen_t *h)
{ info_t info=b000;
  if(h->p.s>0) info|=b100;
  if(h->q.s>0) info|=b010;
  if (h->x || h->r!=0 || info==b000)  @/{ @+info|=b001; @+HPUT8(h->r|(h->x?0x80:0x00));@+}
  return TAG(hyphen_kind,info);
}
@
\subsection{Paragraphs}
The most important procedure that the \HINT/ viewer inherits from \TeX\ is the
line breaking routine. If the horizontal size of the paragraph is not known,
breaking the paragraph\index{paragraph} into lines must be postponed and this is done by creating
a paragraph node. The paragraph node must contain all information that \TeX's
line breaking\index{line breaking} algorithm needs to do its job.

Besides the horizontal list describing the content of the paragraph and 
the xdimen describing the horizontal size,
this is the set of parameters that guide the line breaking algorithm:

\itemize 
\item
Integer parameters:\hfill\break
{\tt pretolerance} (badness tolerance before hyphenation),\hfill\break
{\tt tolerance} (badness tolerance after hyphenation),\hfill\break
{\tt line\_penalty} (added to the badness of every line, increase to get fewer lines),\hfill\break
{\tt hy\-phen\_pe\-nal\-ty} (penalty for break after discretionary hyphen),\hfill\break
{\tt ex\_hy\-phen\_pe\-nal\-ty} (penalty for break after explicit hyphen),\hfill\break
{\tt doub\-le\_hy\-phen\_de\-merits} (demerits for double hyphen break),\hfill\break
{\tt final\_hyphen\_de\-me\-rits} (demerits for final hyphen break),\hfill\break
{\tt adj\_demerits} (demerits for adjacent incompatible lines),\hfill\break
{\tt looseness} (make the paragraph that many lines longer than its optimal size),\hfill\break
{\tt inter\_line\_penalty} (additional penalty between lines),\hfill\break
{\tt club\_pe\-nal\-ty} (penalty for creating a club line),\hfill\break
{\tt widow\_penalty} (penalty for creating a widow line),\hfill\break
{\tt display\_widow\_penalty} (ditto, just before a display),\hfill\break
{\tt bro\-ken\_pe\-nal\-ty} (penalty for breaking a page at a broken line),\hfill\break
{\tt hang\_af\-ter} (start/end hanging indentation at this line).
\item
Dimension parameters:\hfill\break
{\tt line\_skip\_limit} (threshold for {\tt line\_skip} instead of {\tt base\-line\_skip}),\hfill\break
{\tt hang\_in\-dent} (amount of hanging indentation),\hfill\break
{\tt emergency\_stretch} (stretchability added to every line in the final pass of line breaking).
\item
Glue parameters:\hfill\break
{\tt baseline\_skip} (desired glue between baselines),\hfill\break
{\tt line\_skip} (interline glue if {\tt baseline\_skip} is infeasible),\hfill\break
{\tt left\_skip} (glue at left of justified lines),\hfill\break
{\tt right\_skip} (glue at right of justified lines),\hfill\break
{\tt par\_fill\_skip} (glue on last line of paragraph).
\enditemize


For a detailed explanation of these parameters and how they influence line breaking, you should consult the  {\TeX}book\cite{DK:texbook}; \TeX's {\tt parshape} feature is currently not implemented.
There are default values for all of these parameters (see section~\secref{defaults}); and therefore
it might not be necessary to specify any of them. Any local adjustments
are contained in a list of parameters contained in the paragraph node.

A further complication is a displayed\index{displayed formula} formula that interrupts a paragraph. 
Displays are described in the next section. 

To summarize, a paragraph node in the long format specifies an extended dimension, an
optional node list, and an optional parameter list. 
The extended dimension is given either as a reference or as an |xdimen| node (info bit |b100|);
the same holds for the parameter list (info bit |b010|).


\readcode
@s PAR symbol
@s par symbol
@s xdimen_ref symbol
@s param_ref symbol


@<symbols@>=
%token PAR "par"
%type <info> par
@

@<scanning rules@>=
::@=par@>       :< return PAR; >:
@

@<parsing rules@>=
par: xdimen_ref param_ref list {$$=b000;}
   | xdimen_ref param_list_node list { $$=b010;}
   | xdimen_ref list { $$=b010;}
   | xdimen_node param_ref list { $$=b100;}
   | xdimen_node param_list_node list { $$=b110;}
   | xdimen_node list { $$=b110;};

content_node: start PAR par END { hput_tags($1,TAG(par_kind,$3));};
@

\getcode
@<cases to get content@>=
case TAG(par_kind,b000): @+HGET_PAR(b000);@+break;
case TAG(par_kind,b010): @+HGET_PAR(b010);@+break;
case TAG(par_kind,b100): @+HGET_PAR(b100);@+break;
case TAG(par_kind,b110): @+HGET_PAR(b110);@+break;
@

@<get macros@>=
#define @[HGET_PAR(I)@] @/\
 if ((I)&b100)  {xdimen_t x; hget_xdimen_node(&x); @+hwrite_xdimen_node(&x);@+}  else HGET_REF(xdimen_kind);\
 if ((I)&b010) { list_t l; @+hget_param_list_node(&l); @+hwrite_param_list_node(&l); @+} \
  else HGET_REF(param_kind);\
  { list_t l; @+hget_list(&l);@+ hwrite_list(&l); @+} 
@


\subsection{Displays}\index{displayed formula}
Displayed equations occur inside a paragraph\index{paragraph} node. They interrupt normal processing of the paragraph
and the paragraph processing is resumed after the display. Positioning of the display depends on several
parameters, the shape of the paragraph, and the length of the last line preceding the display.
Displayed formulas often feature an equation number which can be placed either left or right of the formula.
Also the size of the equation number will influence the placement of the formula.

In a \HINT/ file, the parameter list is followed by a list of content nodes, representing the formula, and 
an optional horizontal box containing the equation number. 

In the sort format, we use the info bit |b100| to indicate the
presence of a parameter list (which might be empty---so it's actually the absence of a 
reference to a parameter list); the info bit |b010| to indicate the presence of 
a left equation number; and the info bit |b001| for a right equation\index{equation number} number.


In the long format, we use ``{\tt eqno}'' or ``{\tt left eqno}'' to indicate presence and  placement of
the equation number.

\readcode
@s DISPLAY symbol
@s display symbol
@<symbols@>=
%token DISPLAY "display"
%type <info> display 
@

@<scanning rules@>=
::@=display@>       :< return DISPLAY; >:
@

@<parsing rules@>=
display: list {$$=b100;} 
       | list hbox_node {$$=b101;} 
       | hbox_node list {$$=b110;} 
       | param_ref  list {$$=b000;}
       | param_ref  list hbox_node {$$=b001;}
       | param_ref  hbox_node list {$$=b010;}
       | param_list_node list {$$=b100;} 
       | param_list_node list hbox_node {$$=b101;} 
       | param_list_node hbox_node list {$$=b110;};

content_node: start DISPLAY display END @/{ hput_tags($1,TAG(display_kind,$3));};
@

\getcode
@<cases to get content@>=
case TAG(display_kind,b000): HGET_DISPLAY(b000); @+ break;
case TAG(display_kind,b001): HGET_DISPLAY(b001); @+ break;
case TAG(display_kind,b010): HGET_DISPLAY(b010); @+ break;
case TAG(display_kind,b100): HGET_DISPLAY(b100); @+ break;
case TAG(display_kind,b101): HGET_DISPLAY(b101); @+ break;
case TAG(display_kind,b110): HGET_DISPLAY(b110); @+ break;
@

@<get macros@>=
#define @[HGET_DISPLAY(I)@] \
if ((I)&b100) { list_t l; @+hget_param_list_node(&l); @+hwrite_param_list_node(&l); @+} \
else HGET_REF(param_kind);\
if ((I)&b010) hget_hbox_node(); \
{ list_t l; @+hget_list(&l);@+ hwrite_list(&l); @+} \
if ((I)&b001) hget_hbox_node();
@

\subsection{Adjustments}\label{adjust}
An adjustment\index{adjustment} occurs only in paragraphs\index{paragraph}.
When the line breaking\index{line breaking} routine finds an adjustment, it inserts
the vertical material contained in the adjustment node right after the current line.
Adjustments are implemented as just another type of list node.

\readcode
@s ADJUST symbol
@s adjustment symbol
@<symbols@>=
%token ADJUST "adjust"
%type <l> adjustment
@

@<scanning rules@>=
::@=adjust@>       :< return ADJUST; >:
@

@<parsing rules@>=
adjustment: estimate content_list  {@+$$.k=adjust_kind;@+ $$.p=$2; @+ $$.s=(hpos-hstart)-$2;};
content_node: start ADJUST adjustment END { hput_tags($1,hput_list($1+1,&($3)));};
@

\getcode
@<cases to get content@>=
case TAG(adjust_kind,1):  { list_t l;@+HGET_LIST(1,l);@+l.k=adjust_kind;@+ hwrite_adjustments(&l); @+} @+ break;
case TAG(adjust_kind,2):  { list_t l;@+HGET_LIST(2,l);@+l.k=adjust_kind;@+ hwrite_adjustments(&l); @+} @+ break;
case TAG(adjust_kind,3):  { list_t l;@+HGET_LIST(3,l);@+l.k=adjust_kind;@+ hwrite_adjustments(&l); @+} @+ break;
case TAG(adjust_kind,4):  { list_t l;@+HGET_LIST(4,l);@+l.k=adjust_kind;@+ hwrite_adjustments(&l); @+} @+ break;
case TAG(adjust_kind,5):  { list_t l;@+HGET_LIST(5,l);@+l.k=adjust_kind;@+ hwrite_adjustments(&l); @+} @+ break;
@



I guess the following should be incorporated into |hwrite_list|.
\writecode
@<write functions@>=
void hwrite_adjustments(list_t *l)
{  if (l->s==0) return;
   else
   {@+uint32_t h=hpos-hstart, e=hend-hstart; /* save |hpos| and |hend| */
     hpos=l->p+hstart;@+ hend=hpos+l->s;
       if (l->s>0xFF) hwritef(" %d",l->s); 
     while(hpos<hend)
       hget_content_node();
     hpos=hstart+h;@+  hend=hstart+e; /* restore  |hpos| and |hend| */
   }
}
@

\subsection{Tables}\index{alignment}
As long as a table contains no dependencies on \.{hsize} and \.{vsize},
Hi\TeX\ can expand an alignment into a set of nested horizontal and
vertical boxes and no special processing is required in the viewer.

As long as only the size of the table itself but neither the tabskip
glues nor the table content depends on \.{hsize} or \.{vsize} the table
just needs an outer node of type |hset_kind| or |vset_kind|. If there
is non aligned material inside the table that depends on \.{hsize} or
\.{vsize} a vpack or hpack node is still sufficient.

While it is reasonable to restrict the tabskip glues to be ordinary
glue values without \.{hsize} or \.{vsize} dependencies, it might be
desirable to have content in the table that does depend on \.{hsize} or
\.{vsize}. For the latter case, we need a special kind of table
node. Here is why:

As soon as the dimension of an item in the table is an extended
dimension, it is no longer possible to compute the maximum natural with
of a column, because it is not possible to compare extended dimensions
without knowing \.{hsize} and \.{vsize}.  Hence the computation of maximum
widths needs to be done in the viewer.  After knowing the width of the columns,
the setting of tabskip glues is easy to compute.

To implement these extended tables, we will need a table node that
specifies a direction, either horizontal or vertical; a list of
tabskip glues, with the provision that the last tabskip glue in the
list is repeated as long as necessary; and a list of table content.
The table's content consists of nonaligned content, for example extra glue 
or rules, and aligned content called items.
The table's content is stacked, either vertical or
horizontal, orthogonal to the alignment direction of the table.
The aligned content of a table is packed in an outer item node,
that contains a list of inner item nodes.
An inner item contains a box node (of kind |hbox_kind|, |vbox_kind|,
|hset_kind|, |vset_kind|, |hpack_kind|, or |vpack_kind|) followed by
an optional span count.

The glue of the boxes in the inner items will be reset so that all boxes in the same
column reach the same maximum column with.  The span counts will be replaced by
the appropriate amount of empty boxes and tabskip glues.  Finally the
glue in the outer item will be set to obtain the desired size
of the table.

The definitions below specify just a |list| for the list of tabskip glues and the
list of inner table items. This is just for convenience; the first list must contain glue
nodes and the second list must contain inner item nodes. 

We reuse the |H| and |V| tokens, defined as part of the specification of extended dimensions,
to indicate the alignment direction of the table. To tell a reference to an extended dimension
from a reference to an ordinary dimension, we prefix the former with an |XDIMEN| token;
for the latter, the |DIMEN| token is optional. The scanner will recognize not only ``item'' as
an |ITEM| token but also ``row'' and ''column''. This allows a more readable notation,
for example by marking the outer items as rows and the inner items as columns.

In the short format, the |b001| bit is used to mark a vertical table and the |b110| bits indicate
how the table size is specified;
an outer item node has the info value |b000|, an inner item node with info value |b111|
contains an extra byte for the span count, otherwise the info value is equal to the span count.






\readcode
@s TABLE symbol
@s ITEM symbol
@s table symbol
@

@<symbols@>=
%token TABLE "table"
%token ITEM "item"
%type <info> table
@

@<scanning rules@>=
::@=table@>       :< return TABLE; >:
::@=item@>        :< return ITEM; >:
::@=row@>        :< return ITEM; >:
::@=column@>        :< return ITEM; >:
@

@<parsing rules@>=
content_node: start ITEM content_node END { hput_tags($1,hput_item(1));};
content_node: start ITEM content_node UNSIGNED END { hput_tags($1,hput_item($4));};
content_node: start ITEM list END { hput_tags($1,TAG(item_kind,b000));};

table: H box_goal list list {$$=$2;}
table: V box_goal list list {$$=$2|b001;}

content_node: start TABLE table END { hput_tags($1,TAG(table_kind,$3));};
@

\getcode
@<cases to get content@>=
case TAG(table_kind,b000): @+ HGET_TABLE(b000); @+ break;
case TAG(table_kind,b001): @+ HGET_TABLE(b001); @+ break;
case TAG(table_kind,b010): @+ HGET_TABLE(b010); @+ break;
case TAG(table_kind,b011): @+ HGET_TABLE(b011); @+ break;
case TAG(table_kind,b100): @+ HGET_TABLE(b100); @+ break;
case TAG(table_kind,b101): @+ HGET_TABLE(b101); @+ break;
case TAG(table_kind,b110): @+ HGET_TABLE(b110); @+ break;
case TAG(table_kind,b111): @+ HGET_TABLE(b111); @+ break;@#

case TAG(item_kind,b000):  @+{@+ list_t l;@+ hget_list(&l);@+ hwrite_list(&l);@+ } @+ break;
case TAG(item_kind,b001):  hget_content_node(); @+ break;
case TAG(item_kind,b010):  hget_content_node(); @+hwritef(" 2");@+ break;
case TAG(item_kind,b011):  hget_content_node(); @+hwritef(" 3");@+ break;
case TAG(item_kind,b100):  hget_content_node(); @+hwritef(" 4");@+ break;
case TAG(item_kind,b101):  hget_content_node(); @+hwritef(" 5");@+ break;
case TAG(item_kind,b110):  hget_content_node(); @+hwritef(" 6");@+ break;
case TAG(item_kind,b111):  hget_content_node(); @+hwritef(" %u",HGET8);@+ break;
@

@<get macros@>=
#define @[HGET_TABLE(I)@] \
if(I&b001) hwritef(" v"); @+else hwritef(" h"); \
if ((I)&b010) hwritef(" add");@+ else hwritef(" to");\
if ((I)&b100) {xdimen_t x; hget_xdimen_node(&x); @+hwrite_xdimen_node(&x);@+} else HGET_REF(xdimen_kind)@;\
{@+ list_t l; @+hget_list(&l);@+ hwrite_list(&l);@+ } /* tabskip */ \
{@+ list_t l; @+hget_list(&l);@+ hwrite_list(&l);@+ }  /* items */
@


\putcode
@<put functions@>=
uint8_t hput_item(uint32_t n)
{ if (n==0) QUIT("Span count in item must not be zero");
  else if (n<7) return TAG(item_kind,n);
  else if (n>0xFF)  QUIT("Span count %d must be less than 255",n);
  else
  { HPUT8(n); return TAG(item_kind,7); }
}
@
\section{Extensions to \TeX}\hascode

\subsection{Images}
Images behave pretty much like glue\index{glue}. They can stretch (or shrink)
together with the surrounding glue to fill a horizontal or vertical box.
Like glue, they stretch in the horizontal direction when filling an horizontal box
and they stretch in the vertical direction as part of a vertical box.
Stretchability and shrinkability are optional parts of an image node.

Unlike glue, images have both a width and a height.
The relation of height to width, the aspect ratio, is preserved by stretching and shrinking.

While glue often has a zero width, images usually have a nonzero natural size and making
them much smaller is undesirable. 
The natural width and height of an image are optional parts of an image node;
typically however, this information is contained in the image data.

The only required part of an image node is the number of the auxiliary section 
where the image data can be found. 

@<hint types@>=
typedef struct {@+
uint16_t n;@+
dimen_t w,h;@+
stretch_t p,m;@+
} image_t;
@


\readcode
@s IMAGE symbol
@s image symbol
@s image_dimen symbol
@<symbols@>=
%token IMAGE "image"
%type <x> image image_dimen
@

@<scanning rules@>=
::@=image@>       :< return IMAGE; >:
@

@<parsing rules@>=
image_dimen: dimension dimension {$$.w=$1; $$.h=$2;} | {$$.w=$$.h=0; };
image: UNSIGNED image_dimen plus minus { $$.w=$2.w; $$.h=$2.h; $$.p=$3; $$.m=$4;  RNG("Section number",$1,3,max_section_no);$$.n=$1; };
content_node: start IMAGE image END { hput_tags($1,hput_image(&($3)));}
@

\writecode
@<write functions@>=
void hwrite_image(image_t *x)
{ hwritef(" %u",x->n);
  if (x->w!=0 ||x->h!=0) { hwrite_dimension(x->w); hwrite_dimension(x->h);}
  hwrite_plus(&x->p);
  hwrite_minus(&x->m);
}
@

\getcode

@<cases to get content@>=
case TAG(image_kind,b100): @+ { image_t x;@+HGET_IMAGE(b100,x);@+}@+break;
case TAG(image_kind,b101): @+ { image_t x;@+HGET_IMAGE(b101,x);@+}@+break;
case TAG(image_kind,b110): @+ { image_t x;@+HGET_IMAGE(b110,x);@+}@+break;
case TAG(image_kind,b111): @+ { image_t x;@+HGET_IMAGE(b111,x);@+}@+break;
@

@<get macros@>=
#define @[HGET_IMAGE(I,X)@] @/\
HGET16((X).n);RNG("Section number",(X).n,3,max_section_no);  \
if (I&b010) {HGET32((X).w);HGET32((X).h);@+} \
else (X).w=(X).h=0;\
if (I&b001) {HGET_STRETCH((X).p);HGET_STRETCH((X).m);@+}\
else { (X).p.f=(X).m.f=0.0; (X).p.o=(X).m.o=normal_o;@+}\
hwrite_image(&(X));
@


\putcode
@<put functions@>=
uint8_t hput_image(image_t *x)
{ info_t i=b100;
  HPUT16(x->n);
  if (x->w!=0 || x->h!=0)@+  {HPUT32(x->w); HPUT32(x->h); i|=b010; }
  if (x->p.f!=0.0 || x->m.f!=0.0)@+  {hput_stretch(&x->p); hput_stretch(&x->m); i|=b001; }
  return TAG(image_kind,i);
}
@

\subsection{Colors}
Colors\index{color} are certainly one of the features you will find in the final \HINT/ file format.
Here some remarks must suffice.

A \HINT/ viewer must be capable of rendering a page given just any valid
position inside the content section. Therefore \HINT/ files are stateless;
there is no need to search for preceding commands that might change a state
variable.
As a consequence, we can not just define a ``color change node''.
Colors could be specified as an optional parameter of a glyph node, but the
amount of data necessary would be considerable. In texts, on the other hand,
a color change control code would be possible because we parse texts only in forward
direction. The current font  would then become a current color and font with the appropriate
changes for positions.  

A more attractive alternative would be to specify colored fonts. 
This would require an optional
color argument for a font. For example one could have a cmr10 font in black as
font number 3, and a cmr10 font in blue as font number 4. Having 256 different fonts,
this is definitely a possibility because rarely you would need that many fonts 
or that many colors. If necessary and desired, one could allow 16 bit font numbers
of overcome the problem.

Background colors could be associated with boxes as an optional parameter.

\subsection{Positions, Links, and Labels}\index{position}\index{link}\index{label}
A viewer can usually not display the entire content section of
a \HINT/ file. Instead it will display a page of content and will give
its user various means to change the page. This might be as simple as
a ``page down'' or ``page up'' button (or gesture) and as
sophisticated as searching using regular expressions.  More
traditional ways to navigate the content include the use of a table of
content or an index of keywords. All these methods of changing a page
have in common that a part of the content that fits nicely in the
screen area provided by the output device must be rendered given a
position inside the content section.


Let's assume that the viewer uses a \HINT/ file in short
format---after all that's the format designed for precisely this use.
A position inside the content section is then the position of the
starting byte of a node. Such a position can be stored as a 32 bit
number.  To render a page starting at that position is not difficult:
We just read content nodes, starting at the given position and feed
them to \TeX's page builder until the page is complete. To implement a
``clickable'' table of content this is good enough. We store with
every entry in the table of content the position of the section
header, and when the user clicks the entry, the viewer can display a
new page starting exactly with that section header.

Things are slightly more complex if we want to implement a ``page
down'' button. If we press this button, we want the next page to 
start exactly where the current page has ended.  This is
typically in the middle of a paragraph node, and it might even be in
the middle of an hyphenated word in that paragraph. Fortunately,
paragraph and table nodes are the only nodes that can be broken across page
boundaries. But broken paragraph nodes are a common case non the less, 
and unless we want to search for the enclosing node, we need to
augment in this case the primary 32 bit position inside the content
section with a secondary position. Most of the
time, 16 bit will suffice for this secondary position if we give it
relative to the primary position. Further, if the list of nodes forming the
paragraph is given as a text, we need to know the current font at the
secondary position. Of course, the viewer can find it by scanning the
initial part of the text, but when we think of a page down button, the
viewer might already know it from rendering the previous page.

Similar is the case of a ``page up'' button. Only here we need a page
that ends precisely where our current page starts. Possibly even with
the initial part of a hyphenated word. Here we need a reverse version
of \TeX's page builder that assembles a ``good'' page from the bottom
up instead of from the top down.  Sure the viewer can cache the start
position of the previous page (or the rendering of the entire page) if
the reader has reached the current page using the page down
button. But this is not possible in all cases. The reader might have
reached the current page using the table of content or even an index
or a search form.

This is the most complex case to consider: a link from an index or a
search form to the position of a keyword in the main text. Lets assume
someone looks up the word ``M\"unchen''.  Should the viewer then
generate a page that starts in the middle of a sentence with the word
``M\"unchen''? Probably not! We want a page that shows at least the whole sentence if
not the whole paragraph.  Of course the program that generates the
link could specify the position of the start of the paragraph instead
of the position of the word. But that will not solve the problem. Just
imagine reading the groundbreaking masterpiece of a German philosopher
on a small hand-held device: the paragraph will most likely be very
long and perhaps only part of the first sentence will fit on the small
screen. So the desired keyword might not be found on the page that
starts with the beginning of the paragraph; it might not even be on
the next or next to next page. Only the viewer can decide what is the
best fragment of content to display around the position of the given
keyword.

To summarize, we need three different ways to render a page for a given position:
\itemize
\item A page that starts exactly at the give position.
\item A page that ends exactly at the give position.
\item The ``best'' page that contains the given position somewhere in the middle.
\enditemize

A possible way to find the ``best'' page for the latter case could be the following:
\itemize
\item If the position is inside a paragraph, break the paragraph into lines. One line will contain
the target position. Let's call this the target line.
\item If the paragraph will not fit entirely on the page, start the page with the beginning of the 
paragraph if that will place the target line on the page, otherwise
display an equal amount of lines before and after the target line. 
\item Else traverse the content list backward for about $2/3$ of the page height and forward for about $2/3$
of the page height, searching for the smallest negative penalty node. 
Use the  penalty node found as either the beginning
or ending of the page. 
\item If there are several equally low negative penalty nodes. Prefer penalties preceding the target line
over penalty nodes following it. A good page start is more important than a good page end.
\item If there are are still several equally low negative penalty nodes, choose the one whose distance
to the target line is closest to $1/2$ of the page height.
\item If no negative penalty nodes could be found, start the page with the paragraph containing the target line.
\item Once the page start (or end) is found, use \TeX's page builder (or its reverse variant) to complete the page.
\enditemize

We call nodes that reference a position inside the content section a
link node.  As with other nodes, we can use predefined links. The
first 256 of them can be referenced by a single byte.  We should
reserve reference number 0 for a link to the beginning of the content
and reference number 1 for a link to the end of the content.  Probably
having only 256 links would be a severe restriction, hence we will
allow also 16 bit reference numbers.  If still more links are needed,
links can be embedded directly in the content stream.  We need two
types of links, a start link and an end link such that the content
between the two will constitute the visible part of the link.


In the short format, we will use the |b100| bit of the info value to
distinguish them: 1 indicates start link, 0 indicates end link. The
two low bits of the info value will be 0 for an 8 bit reference
number, 1 for a 16 bit reference number,  2 for an immediate
link without secondary position and current font, and  3 for an immediate
link with 32 bit secondary position and current font. 
The link itself consists of a primary position, an optional
secondary position, an optional current font, and a position type. The
position type is 0 for the exact page top, 1 for the exact page
bottom, and 2 for the approximate middle as described above. 

In the long format, a position can not be expressed as a byte
position; instead we use labels.  A label is identified by a unique
name expressed as a string. For example we can write
\.{<label} \.{'label10'>} and then we can use \.{'label10'} as a 
symbolic reference to the position of the node
that follows the label node. When translating the long format to the
short format, these label nodes will disappear. To keep readable label
names, the links in the short format may specify an optional name that
is used for labels. If no name is given, a label name is
generated. When translating the short format to the long format, we
test just before writing a new node whether there is a link to this
node and insert a label if so. Because we write nodes in ascending
order of positions, we can sort the labels in ascending order of
position and compare |hpos| with the position of the next label in
this order.  Immediate back links pose a problem for this translation
because the node has already been written without a label when we
encounter the link node that refers to it. If we encounter such a link
we must resort to a two pass translation: We log the information
about the back link and continue with the translation.  After the
whole file is translated, we check the log, and if unresolved back
links where found, we sort them into the previously incomplete list of
links and repeat the translation.

When translating the long format to the short format, immediate
forward links pose a similar problem: We can not encode the links
position because we have not yet encountered the label. In case we
have unused reference numbers for predefined links, we will convert the immediate link into a
predefined link. Predefined links can be completed with positions when
we find the labels, all we need to know to encode the link itself is the
reference number. If all 16 bit numbers are already in use, we reserve
the maximum amount of memory ( 8 bit for the type information,
32 bit for the primary position, 32 bit for the secondary position, and 8 bit for the font number) in the stream and keep a linked list of
positions for the given label (the reserved space in the link nodes
can be used of that purpose) and fill in the information once we find
the corresponding label.

Links and Labels are not yet implemented.
 
\section{Replacing \TeX's Page Building Process}

\TeX\ uses an output\index{output routine} routine to finalize the page. It uses the accumulated material
from the page builder, found in box255, attaches headers, footers, and floating material
like figures, tables, and footnotes. The latter material is specified by insert nodes
while headers and footers are often constructed using mark nodes.
Running an output routine requires the full power of the \TeX\ engine and will not be
part of the \HINT/ viewer. Therefore, \HINT/ replaces output routines by page templates\index{template}.
As \TeX\ can use different output routines for different parts of a book--for example
the index might use a different output routine than the main body of text---\HINT/ will allow multiple page templates. To support different output media, the page
templates will be named and a suitable user interface may offer the user a selection
of possible page layouts. In this way, the page layout remains in the hands of the
book designer, and the user has still the opportunity to pick a layout that best fits
the display device.

\TeX\ uses insertions to describe floating content that is not necessarily displayed 
where it is specified. Three examples may illustrate this:
\itemize
\item Footnotes\footnote*{Like this one.}  are specified in the middle of the text but are displayed at the
bottom of the page. Long footnotes may even be split and displayed at the
bottom of the next page.  Several
footnotes\index{footnote} on the same page are collected and displayed together. The
page layout may specify a short rule to separate footnotes from the
main text, and if there are many short footnotes, it may use two columns
to display them.  In extreme cases, the page layout may demand a
footnote to be split and continued on the next page.

\item Illustrations\index{illustration} may be displayed exactly where specified if there is enough
room on the page, but may move to the top of the page, the bottom of the page,
the top of next page, or a separate page at the end of the chapter.

\item Margin notes\index{margin note} are displayed in the margin on the same page starting at the top
of the margin.
\enditemize

\HINT/ uses page templates and content streams to achieve similar effects.
But before I describe the page building\index{page building} mechanisms of \HINT/, let me summarize \TeX's
method.

\TeX's page builder ignores leading glue\index{glue}, kern\index{kern}, and penalty\index{penalty} nodes until the first
box\index{box} or rule\index{rule} is encountered; 
whatsit\index{whatsit node} nodes do not really contribute anything to a page; mark\index{mark node} nodes are recorded for later use.
Once the first box, rule, or insert\index{insert node} arrives, \TeX\ makes copies of all parameters
that influence the page building process and uses these copies. These parameters
are the |page_goal| and the |page_max_depth|; further the parameters 
|page_total|, |page_shrink|, |page_stretch|, |page_depth|,
and {\it insert\_pe\-nal\-ties\/} are initialized to zero.
The top skip\index{top skip} adjustment is made
when the first box or rule arrives---possibly after an insert.

Now the page builder accumulates material: normal material goes into box255\index{box255},
inserts specify an insert class $n$ and go into box$n$.
Material that goes into box255 will change |page_total|, |page_shrink|, 
|page_stretch|, and |page_depth|. The latter is adjusted so that 
is does not exceed |page_max_depth|.

The handling of inserts\index{insert node} is more complex.
\TeX\ creates an insert class using \.{newinsert}. This reserves a number $n$
and four registers: box$n$ for the inserted material, count$n$ for the
magnification factor $f$, dimen$n$ for the maximum size per page $d$, and skip$n$ for the
extra space needed on a page if there are any insertions of class $n$.

For example plain \TeX\ allocates $n=254$ for footnotes\index{footnote} and sets
count254 to 1000, dimen254 to 8in, and skip254 to bigskipamount.

An insertion node will specify the insertion class $n$, some vertical material,
its natural height plus depth $x$, a {\it split\-\_top\-\_skip}, a {\it split\-\_max\_depth},
and a {\it floa\-ting\-\_pe\-nal\-ty}. 


Now assume that an insert node with subtype 254 arrives at the page builder.
If this is the first such insert, \TeX\ will decrease the |page_goal|
by the width of skip254 and adds its stretchability and shrinkability
to the total stretchability and shrinkability of the page. Later,
the output routine will add some space and the footnote rule to fill just that
much space and add just that much shrinkability and stretchability to the page.
Then \TeX\ will normally add the vertical material in the insert node to
box254 and decrease the |page_goal| by $x\times f/1000$.

Special processing is required if \TeX\ detects that there is not enough space on
the current page to accommodate the complete insertion.
If already a previous insert did not fit on the page, simply the |floating_penalty|
as given in the insert node is added to the total |insert_penalties|.
Otherwise \TeX\ will test that the total natural height plus depth of box254 
including $x$ does not exceed the maximum size $d$ and that the 
$|page_total| + |page_depth| + x\times f/1000 - |page_shrink| \le |page_goal|$.
If one of these tests fails, the current insertion
is split in such a way as to make the size of the remaining insertions just pass the tests
just stated.

Whenever a glue node, or penalty node, or a kern node that is followed by glue arrives
at the page builder, it rates the current position as a possible end of the page based on
the shrinkability of the page and the difference between |page_total| and |page_goal|.
As the page fills, the page breaks tend to become better and better until the
page starts to get overfull and the page breaks get worse and worse until
they reach the point where they become |awful_bad|. At that point,
the page builder returns to the best page break found so far and fires up the 
output routine.

Let's look next at the problems that show up when implementing a replacement mechanism for \HINT/.

\enumerate
\item 
An insertion node can not always specify its height $x$ because insertions may contain paragraphs that need
to be broken in lines and the height of a paragraph depends in some non obvious way on
its width. 

\item 
Before the viewer can compute $x$ it needs to know the width of the insertion. Just imagine
displaying footnotes in two columns or setting notes in the margin. Knowing the width, it
can pack the vertical material and derive its height and depth.

\item
\TeX's plain format provides an insert macro that checks whether there is still space
on the current page, and if so, it creates a contribution to the main text body, otherwise it
creates a topinsert. Such a decision needs to be postponed to the \HINT/ viewer.

\item
There is no output routine that would specify something like the space and the rule preceding the footnote.

\item 
\TeX's output routines have the ability to inspect the content of the boxes,
split them, and distribute the content over the page.
For example, the output routine for an index set in two column format might
expect a box containing index entries up to a height of $2\times\.{vsize}$.
It will split this box in the middle and display the top part in the left
column and the bottom part in the right column. With this approach, the
last page will show two partly filled columns of about equal size.

\item
There are no mark nodes that could be used to create page headers or footers.
Marks, like output routines, contain token lists and need the full \TeX\ interpreter
for processing them. Hence, \HINT/ does not support mark nodes.
\endenumerate

Here now is the solution I have chosen for \HINT/:

Instead of output routines, \HINT/ will use page templates.
Page templates are basically vertical boxes with placeholders marking the 
positions where the content of the box registers, filled by the page builder,
should appear. 
To output the page, the viewer traverses the page template,
replaces the placeholders by the appropriate box content, and 
sets the glue. Inside the page template, we can use insert nodes to act
as placeholders.

It is only natural to treat the page's main body, the
inserts, and the marks using the same mechanism. We call this
mechanism a content stream\index{stream}. 
Content streams are identified by a stream number in the range 0 to 254;
the number 255 is used to indicate an invalid stream number.
The stream number 0 is reserved for the main content stream; it is always defined.
Besides the main content stream, there are three types of streams:
\itemize
\item normal streams correspond to \TeX's inserts and accumulate content on the page,
\item first\index{first stream} streams correspond to \TeX's first marks and will contain only the first insertion of the page,
\item last\index{last stream} streams correspond to \TeX's bottom marks and will contain only the last insertion of the page, and
\item top\index{top stream} streams correspond to \TeX's top marks. Top streams are not yet implemented.
\enditemize

Nodes from the content section are considered contributions to stream 0 except
for insert nodes which will specify the stream number explicitly. 
If the stream is not defined or is not used in the current page template, its content is simply ignored.

The page builder needs a mechanism to redirect contributions from one content
stream to another content stream based on the availability of space.
Hence a \HINT/ content stream can optionally specify a preferred stream number,
where content should go if there is still space available, a next stream number,
where content should go if the present stream has no more space available, and
a split ratio if the content is to be split between these two streams before
filling in the template.

Various stream parameters govern the treatment of contributions to the stream
and the page building process.

\itemize
\item The magnification factor $f$: Inserting a box of height $h$ to this stream will contribute $h\times f/1000$
to the height of the page under construction. For example, a stream
that uses a two column format will have an $f$ value of 500; a stream
that specifies notes that will be displayed in the page margin will
have an $f$ value of zero.

\item The height $h$: The extended dimension $h$ gives the maximum height this 
stream is allowed to occupy on the current page.
To continue the previous example, a stream that will be split into two columns
will have $h=2\cdot\.{vsize}$ , and a stream that specifies
notes that will be displayed in the page margin will have
$h=1\cdot\.{vsize}$.  You can restrict the amount of space occupied by
footnotes to the bottom quarter by setting the corresponding $h$ value
to $h=0.25\cdot\.{vsize}$.

\item The depth $d$: The dimension $d$ gives the maximum depth this 
stream is allowed to have after formatting.

\item The width $w$: The extended dimension $w$ gives the width of this stream 
when formatting its content. For example margin notes
should have the width of the margin less some surrounding space.

\item The ``before'' list $b$: If there are any contributions to this
stream on the current page, the material in list $b$
is inserted {\it before\/} the material from the stream itself. For
example, the short line that separates the footnotes from the main
page will go, together with some surrounding space, into the list $b$.

\item The top skip glue $g$: This glue is inserted between the material
from list $b$ and the first box of the stream, reduced
by the height of the first box. Hence it specifies the distance between
the material in $b$ and the first baseline of the stream content.

\item The ``after'' list $a$: The list $a$ is treated like list $b$ but
its material is placed {\it after\/} the  material from the stream itself.

\item The ``preferred'' stream number $p$:  If $p\ne 255$, it is the number of 
the {\it preferred\/} stream. If stream $p$ has still
enough room to accommodate the current contribution, move the
contribution to stream $p$, otherwise keep it.  For example, you can
move an illustration to the main content stream, provided there is
still enough space for it on the current page, by setting $p=0$.

\item The ``next'' stream number $n$: If $n\ne 255$, it is the number of the 
{\it next\/} stream. If a contribution can not be
accommodated in stream $p$ nor in the current stream, treat it as an
insertion to stream $n$.  For example, you can move contributions to
the next column after the first column is full, or move illustrations
to a separate page at the end of the chapter.

\item The split ratio\index{split ratio} $r$: If $r$ is positive, both $p$ and $n$ must 
be valid stream numbers and contents is not immediately moved to stream $p$ or $n$ as described before.
Instead the content is kept in the stream itself until the current page is complete.
Then, before inserting the streams into the page template, the content of
this stream is formatted as a vertical box, the vertical box is
split into a top fraction and a bottom fraction in the ratio $r/1000$
for the top and $(1000-r)/1000$ for the bottom, and finally the top
fraction is moved to stream $p$ and the bottom fraction to stream
$n$. You can use this feature for example to implement footnotes
arranged in two columns of about equal size. By collecting all the
footnotes in one stream and then splitting the footnotes with $r=500$
before placing them on the page into a right and left column.  Even
three or more columns can be implemented by cascades of streams using
this mechanism.
\enditemize

\subsection{Stream Definitions}
Stream\index{stream} definitions occur only in page templates. 
They start with stream number and stream type.
There are four types of streams:  normal streams that work like \TeX's inserts;
and first, last, and top streams that work like \TeX's marks.
For the latter  types, the long format uses a matching keyword and the
short format the two least significant info bits.
For normal streams, a stream definition specifies
 the maximum insertion height,
 the magnification factor, 
 and optional information about splitting the stream.
 In the short format, the info bit |b100| indicates the presence of splitting information.
 It consists of: a preferred stream, a next stream, and a split ratio.
 An asterisk indicates a missing stream reference, in the
 short format the stream number 255 serves the same purpose;
All stream definitions finish with the material that goes before a nonempty stream, 
 an extended dimension node, specifying the width of the inserted material, 
the top skip glue, and the material that goes after a nonempty stream.

\readcode
@s TOP symbol
@s FIRST symbol
@s LAST symbol
@s NOREFERENCE symbol
@s stream_type symbol
@s stream_split symbol
@s stream_def symbol
@s stream_link symbol

@<symbols@>=
%token FIRST "first"
%token LAST "last"
%token TOP "top"
%token NOREFERENCE "*"
%type <info> stream_type stream_split stream_def 
@

@<scanning rules@>=
::@=first@>  :< return FIRST; >:
::@=last@>  :< return LAST; >:
::@=top@>  :< return TOP; >:
::@=\*@>  :< return NOREFERENCE; >:
@

@<parsing rules@>=
stream_type: FIRST {$$=1;} @+ | LAST {$$=2;} @+ |TOP {$$=3;} 
           | xdimen_node  integer {HPUT16($2);} stream_split {$$=$4+0;} ;
stream_link: stream_ref @+| NOREFERENCE {HPUT8(255);};
stream_split: {$$=b000;} 
            | stream_link stream_link UNSIGNED @/{RNG("split ratio",$3,0,1000); HPUT16($3); $$=b100;};
stream_def: start STREAM  stream_ref  stream_type  @/ 
   list xdimen_node glue_node list END @/ 
   {hput_tags($1,TAG(stream_kind,$4));};
@

\getcode

@<get functions@>=
static void hget_stream_split(void)
{ uint8_t n; int r;
  n=HGET8; if (n==255) hwritef(" *"); else { REF(stream_kind,n);@+hwritef(" *%d",n);@+}
  n=HGET8; if (n==255) hwritef(" *"); else { REF(stream_kind,n);@+hwritef(" *%d",n);@+}
  HGET16(r); RNG("split ratio",r,0,1000); hwritef(" %d",r);
} 
void hget_stream_def(void)
{ if (KIND(*hpos)!=stream_kind) return;
  else
  { info_t i;
    list_t l; 
    xdimen_t x;
    @<read the start byte |a|@>@;
    i=INFO(a);
    hwrite_start(); @+hwritef("stream");
    HGET_REF(stream_kind);
    if ((i&b011)==0) 
    { uint16_t f;
      hget_xdimen_node(&x); @+hwrite_xdimen_node(&x); 
      HGET16(f); @+RNG("magnification factor",f,0,1000);@+ hwritef(" %d",f);
      if (i&b100) hget_stream_split();
    }
    else if ((i&b011)==1) hwritef(" first");
    else if((i&b011)==2) hwritef(" last");
    else if ((i&b011)==3) hwritef(" top");
    hget_list(&l);@+ hwrite_list(&l);  
    hget_xdimen_node(&x); @+hwrite_xdimen_node(&x); 
    hget_glue_node();
    hget_list(&l);@+ hwrite_list(&l);
    hwrite_end();
    @<read and check the end byte |z|@>@;
  }
}
@


\subsection{Stream Nodes}
Stream\index{stream} nodes occur in the content section where they must not be
inside other nodes except toplevel paragraph\index{paragraph} nodes. 
(As we will see in section~\secref{page}, they occur with a different meaning 
also in page templates\index{template}.)
A complete stream node contains in this order: the stream reference number, the |height|
(|b100|), the |floating_penalty| (|b010|), the |split_max_depth| followed by the |split_top_skip| (|b010|), and the content list. 
All these components, except the stream reference number and the content list, are optional. 
In the short format, the presence of the optional parameters is indicated by the info bits shown above in
parentheses.
If the height is missing, it can be computed from the
content list, and the global values of |floating_penalty|, |split_max_depth|, and |split_top_skip|
serve as substitutes for other missing parameters.


\putcode
\readcode
@s STREAM symbol
@s stream symbol
@s float_info symbol
@s stream_ref symbol
@s stream_height symbol
@<symbols@>=
%token STREAM "stream"
%type <info> float_info stream_height stream 
@

@<scanning rules@>=
::@=stream@>  :< return STREAM; >:
@
@<parsing rules@>=

float_info:  penalty dimension {HPUT16($1);@+HPUT32($2);} @/ glue_node {$$=b011;}
   | penalty {HPUT16($1);$$=b010;}
   | dimension {HPUT32($1);} glue_node {$$=b001;}
   | {$$=b000;};

stream_height: {$$=b000;} @+| TO dimension {HPUT32($2);$$=b100;};

stream: stream_ref stream_height float_info list {$$=$2|$3;};

content_node: start STREAM stream END @/{@+hput_tags($1,TAG(stream_kind,$3)); @+}; 
@

\writecode
\getcode
@<cases to get content@>=
case TAG(stream_kind,b000): HGET_STREAM(b000); @+ break;
case TAG(stream_kind,b001): HGET_STREAM(b001); @+ break;
case TAG(stream_kind,b010): HGET_STREAM(b010); @+ break;
case TAG(stream_kind,b011): HGET_STREAM(b011); @+ break;
case TAG(stream_kind,b100): HGET_STREAM(b100); @+ break;
case TAG(stream_kind,b101): HGET_STREAM(b101); @+ break;
case TAG(stream_kind,b110): HGET_STREAM(b110); @+ break;
case TAG(stream_kind,b111): HGET_STREAM(b111); @+ break;
@

@<get macros@>=
#define @[HGET_STREAM(I)@] @/\
HGET_REF(stream_kind);\
if ((I)&b100) { scaled_t h; @+HGET32(h); @+hwritef(" to"); @+hwrite_dimension(h);@+}\
if ((I)&b010) @/{ int16_t p;@+ HGET16(p); @+RNG("Penalty",p,-10000,+10000); @+hwrite_signed(p);@+ }\
if ((I)&b001) @/{ scaled_t d; @+HGET32(d); @+hwrite_dimension(d);@+hget_glue_node();@+}\
{ list_t l; @+hget_list(&l);@+ hwrite_list(&l); @+} 
@




\subsection{Page Templates}\label{page}
A \HINT/ file can define multiple page templates\index{template}. Not only
might an index demand a different page layout than the main body of text,
also the front page or the chapter headings might use their own page templates.
Further, the author of a \HINT/ file might define a two column format as
an alternative to a single column format to be used if the display area
is wide enough.

To help in selecting the right page template, page templates start with
a name and an optional priority\index{priority}; the default priority is 1.
The names might appear in a menu from which the user
can select a page layout that best fits her taste.
Without user interaction, the
system can pick the template with the highest priority. Of course,
a user interface might provide means to alter priorities. Future
versions might include sophisticated feature-vectors that 
identify templates that are good for large or small displays,
landscape or portrait mode, etc \dots

The main part of a page template is a list of vertical material.
To construct the page, this list will just be placed
into a vertical box, but of course before doing so, the viewer will
scan the list, replace all stream nodes found
inside by the appropriate content streams, and set the glue.

Let's call the vertical box obtained this way ``the page''.
The page will fill the entire display area top to bottom and left to right. 
It defines not only the appearance of the main body of text 
but also the margins, the header, and the footer.
Because the \.{vsize} and  \.{hsize} variables of \TeX\ are used for 
the vertical and horizontal dimension of the main body of text---they 
do not include the margins---the page will usually be wider than \.{hsize}
and taller than \.{vsize}. The dimensions of the page are part
of the page template. The viewer, knowing the actual dimensions
of the display area, can derive from them the actual values of \.{hsize}
and \.{vsize}.

At the end of the page template, a list of stream definitions
provides information about the streams that are
mentioned in the page's list of vertical material. In addition
it might define streams that merely distribute content to other streams
or streams that just accumulate material to be used on later pages.

The page template with number 0 is always defined and has priority 0.
It will display just the main content stream. It puts a small margin 
of $\.{hsize}/8 -4.5\hbox{pt}$ all around it.
Given a letter size page, 8.5 inch wide, this formula yields a margin of 1 inch,
matching \TeX's plain format. The margin will be positive as long as
the page is wider than $1/2$ inch. For narrower pages, there will be no
margin at all. In general, the \HINT/ viewer will never set {\tt hsize} larger
than the width of the page and {\tt vsize} larger than its height.

%8.5 in should give 1 inch margin 2/17
%612pt should give 72pt margin
%72pt = 612/8-4.5pt
%This would give a positive margin starting at 36pt or 1/2 inch

\readcode

@s PAGE symbol
@s page_streams symbol
@s page_priority symbol
@s page symbol

@<symbols@>=
%token PAGE "page"
@

@<scanning rules@>=
::@=page@>  :< return PAGE; >:
@

@<parsing rules@>=
page_priority: { HPUT8(1); } 
             | UNSIGNED { RNG("page priority",$1,0,255); HPUT8($1); };
page_streams: @+ | page_streams stream_def;
page: string { hput_string($1);} page_priority @/ VBOX xdimen_node HBOX xdimen_node list 
      page_streams;

@

\getcode
@<get functions@>=
void hget_page(void)
{ char *n; uint8_t p;  list_t l; xdimen_t x;
  HGET_STRING(n);@+ hwrite_string(n);
  p=HGET8; @+ if (p!=1) hwritef(" %d",p);
  hwritef(" vbox ");@+  {@+hget_xdimen_node(&x); @+hwrite_xdimen_node(&x);@+} 
  hwritef(" hbox ");@+  {@+hget_xdimen_node(&x); @+hwrite_xdimen_node(&x);@+} 
  hget_list(&l);@+ hwrite_list(&l);
  while (KIND(*hpos)==stream_kind) hget_stream_def();
} 
@

\subsection{Page Ranges}\label{range}\index{page range}
Not every template\index{template} is necessarily valid for the entire content
section.  A page range specifies a start position $a$ and an end
position $b$ in the content section and the page template is valid if
the start position $p$ of the page is within that range: $a\le p < b$.
If paging backward this definition might cause problems because the
start position of the page is known only after the page has been
build.  In this case, the viewer might choose a page template based on
the position at the bottom of the page. If it turns out that this ``bottom template''
is no longer valid when the page builder has found the start of the
page, the viewer might display the page anyway with the bottom
template, it might just display the page with the new ``top
template'', or rerun the whole page building process using this time
the ``top template''.  Neither of these alternatives is guaranteed to
produce a perfect result because changing the page template might
change the amount of material that fits on the page. A good page
template design should take this into account.

The representation of page ranges differs significantly for the short
format and the long format.  The short format will include a list of page
ranges in the definition section which consist of a page template number, 
a start position, and an end position. In the long format, the start 
and end position of a page
range is marked with a page range node switching the availability of a
page template on and off.  It is an error, to switch a page template
off that was not switched on, or to switch a page template on that was
already switched on.  It is permissible to omit switching off a page
template at the very end of the content section.

While we parse a long format \HINT/ file, we store page ranges and generate
the short format after reaching the end of the content section.
While we parse a short format \HINT/ file, 
we check at the end of each top level node whether we should insert a
page range node into the output.
For the \.{shrink} program, it is best
to store the start and end positions of all page ranges
in an array sorted by the position\footnote*{For a \HINT/ viewer,
a data structure which allows fast retrieval of all
valid page templates for a given position is needed.}.
To check the restrictions on the switching of page templates, we
maintain for every page template an index into the range array
which identifies the position where the template was switched on.
A zero value instead of an index will identify templates that
are currently invalid. When switching a range off again, we 
link the two array entries using this index. These links
are useful when producing the range nodes in short format.

A range node in short format contains the template number, the
start position and the end position.

A zero start position
is not stored, the info bit |b100| indicates a nonzero start position.
An end position equal to |0xFFFFFFFFF| is not stored, 
the info bit |b010| indicates a smaller end position.
The info bit |b001| indicates that positions are stored using 2 byte
otherwise 4 byte are used for the positions.

@<hint types@>=
typedef
struct {@+uint8_t pg; @+uint32_t pos; @+ bool on; @+int link;@+} range_pos_t;
@

@<common variables@>=
range_pos_t *range_pos;
int next_range=1, max_range;
int *page_on; 
@

@<allocate data@>=
ALLOCATE(page_on,max_ref[page_kind]+1,int);
ALLOCATE(range_pos,2*(max_ref[range_kind]+1),range_pos_t);
@

@<hint macros@>=
#define @[ALLOCATE(R,S,T)@] @/((R)=@[calloc((S),sizeof(T)),\
        (((R)==NULL)?QUIT("Out of memory for " #R):0))
#define @[REALLOCATE(R,S,T)@] @/((R)=@[realloc((R),(S)*sizeof(T)),\
        (((R)==NULL)?QUIT("Out of memory for " #R):0))
@

\readcode
@s RANGE symbol
@<symbols@>=
%token RANGE "range"
@

@<scanning rules@>=
::@=range@>          :< return RANGE; >:
@
@<parsing rules@>=

content_node: START RANGE REFERENCE ON  END @/{  REF(page_kind,$3);hput_range($3,true);}
            | START RANGE REFERENCE OFF END @/{  REF(page_kind,$3);hput_range($3,false);}; 
@


\writecode
@<write functions@>=
void hwrite_range(void) /* called in |hwrite_end| */
{ uint32_t p=hpos-hstart;
  DBG(DBGRANGE,"Range check at pos 0x%x next at 0x%x\n",p,range_pos[next_range].pos);
  while (next_range<max_range && range_pos[next_range].pos <= p)
  { hwrite_start();
    hwritef("range *%d ",range_pos[next_range].pg);
    if (range_pos[next_range].on) hwritef("on"); else  hwritef("off");
    nesting--; @+hwritec('>'); /* avoid a recursive call to |hwrite_end| */
    next_range++; 
  }
}
@

\getcode
@<get functions@>=
void hget_range(info_t info, uint8_t pg)
{ uint32_t from, to; 
  REF(page_kind,pg);
  REF(range_kind,(next_range-1)/2);
  if (info&b100) @+
  { @+ if (info&b001) HGET32(from); @+else HGET16(from); @+}
  else from=0;
  if (info&b010) @+
  { @+if (info&b001) HGET32(to); @+else HGET16(to); @+}
  else to=0xFFFFFFFF;
  range_pos[next_range].pg=pg;
  range_pos[next_range].on=true;
  range_pos[next_range].pos=from;
  DBG(DBGRANGE,"Range *%d from 0x%x\n",pg,from);
  DBG(DBGRANGE,"Range *%d to 0x%x\n",pg,to);
  next_range++;
  if (to!=0xFFFFFFFF) @/
  { range_pos[next_range].pg=pg;
    range_pos[next_range].on=false;
    range_pos[next_range].pos=to;
    next_range++;
  }
}

void hsort_ranges(void) /* simple insert sort by position */
{ int i;
  DBG(DBGRANGE,"Range sorting %d positions\n",next_range-1);
  for(i=3; i<next_range; i++)@/
  { int j = i-1;
    if (range_pos[i].pos < range_pos[j].pos) @/
    { range_pos_t t;
      t= range_pos[i];
       do {
        range_pos[j+1] = range_pos[j];
        j--;
      } while (range_pos[i].pos < range_pos[j].pos);
      range_pos[j+1] = t;
    }
  }
  max_range=next_range; @+next_range=1; /* prepare for |hwrite_range| */
} 
@

\putcode
@<put functions@>=
void hput_range(uint8_t pg, bool on)
{ REF(range_kind,(next_range-1)/2);
  if (on && page_on[pg]!=0)
    QUIT(@["Template %d is switched on at 0x%x and " SIZE_F@],@|
           pg, range_pos[page_on[pg]].pos, hpos-hstart);
  else if (!on && page_on[pg]==0)
    QUIT(@["Template %d is switched off at " SIZE_F " but was not on"@],@|
           pg, hpos-hstart);
  DBG(DBGRANGE,@["Range *%d %s at " SIZE_F "\n"@],pg,on?"on":"off",hpos-hstart);
  range_pos[next_range].pg=pg;
  range_pos[next_range].pos=hpos-hstart;
  range_pos[next_range].on=on;
  if (on) page_on[pg]=next_range;
  else @/{ range_pos[next_range].link =page_on[pg]; 
         range_pos[page_on[pg]].link=next_range;
         page_on[pg]=0; }
  next_range++;
}
extern void hput_definitions_end(void);
void hput_range_defs(void)
{ int i;
  section_no=1;
  hstart=dir[1].buffer;
  hend=hstart+ dir[1].bsize;
  hpos=hstart+dir[1].size;
  for (i=1; i< next_range;i++)
    if (range_pos[i].on)@/
    { info_t info=b000;
      uint32_t p=hpos++-hstart;
      uint32_t from, to;
      HPUT8(range_pos[i].pg);
      from= range_pos[i].pos;
      if (range_pos[i].link!=0) to = range_pos[range_pos[i].link].pos;
      else to=0xFFFFFFFF;
      if (from!=0) @/
      { info=info|b100;@+ if (from>0xFFFF) @+ info=info|b001;@+}
      if (to!=0xFFFFFFFF) @/
      { info=info|b010;@+ if (to>0xFFFF) info=info|b001;@+ }
      if (info & b100) @/
      { @+if (info & b001) HPUT32(from); @+else HPUT16(from); @+}
      if (info & b010) @/
      { @+if (info & b001) HPUT32(to); @+else HPUT16(to); @+}
      DBG(DBGRANGE,"Range *%d from 0x%x to 0x%x\n",@|range_pos[i].pg,from, to);
      hput_tags(p,TAG(range_kind,info));
    }
  hput_definitions_end();
 }
@


\section{File Structure}\hascode
All \HINT/ files\index{file} start with a banner\index{banner} as
described below.  After that, they contain three mandatory
sections\index{section}: the directory\index{directory section}
section, the definition\index{definition section} section, and the
content\index{content section} section.  Usually, further
optional\index{optional section} sections follow.  In short format
files, these contain auxiliary\index{auxiliary file} files
(fonts\index{font}, images\index{image}, \dots) necessary for
rendering the content. In long format files, the directory section
will simply list the file names of the auxiliary files.



\subsection{Banner}
All \HINT/ files start with a banner\index{banner}. The banner contains only
printable ASCII characters and spaces; 
its end is marked with a newline character\index{newline character}.  
The first four byte are the ``magic'' number by which you recognize a \HINT/
file. It consists of the four ASCII codes `{\tt H}', `{\tt I}', `{\tt N}',
and `{\tt T}' in the long format and `{\tt h}', `{\tt i}', `{\tt n}',
and `{\tt t}' in the short format.  Then follows a space, then
the version number, a dot, the sub-version number, and another
space. Both numbers are encoded as decimal ASCII strings.  The
remainder of the banner is simply ignored but may be used to contain
other useful information about the file.  The maximum size of the
banner is 256 byte.
@<hint macros@>=
#define MAX_BANNER 256
@

\goodbreak
To check the banner, we have the function |hcheck_banner|; 
it returns |true| if successful.


@<function to check the banner@>=
int version=1, subversion=0;
char hbanner[MAX_BANNER+1];
bool hcheck_banner(char *magic)
{ int hbanner_size=0;
  char *t;
  t=hbanner;
  if (strncmp(magic,hbanner,4)!=0) QUIT("This is not a %s file",magic);
  else t+=4;
  hbanner_size=(int)strnlen(hbanner,MAX_BANNER);
  if(hbanner[hbanner_size-1]!='\n') QUIT("Banner exceeds maximum size=0x%x",MAX_BANNER);
  if (*t!=' ') QUIT("Space expected after %s",magic);
  else t++;
  version=strtol(t,&t,10);
  if (*t!='.') QUIT("Dot expected after version number %d",version);
  else t++;
  subversion=strtol(t,&t,10);
  if (*t!=' ' && *t!='\n') QUIT("Space expected after subversion number %d",subversion);
  LOG("%s file version %d.%d:%s",magic,version, subversion, t);
  DBG(DBGDIR,"banner size=0x%x\n",hbanner_size);
  return true;
}
@

To read a short format file, we use the macro |HGET8|. It returns a single byte.
We read the banner knowing that it ends with a newline character
and is at most |MAX_BANNER| byte long.

\getcode
@<get file functions@>=
void hget_banner(void)
{ int i;
  for (i=0;i<MAX_BANNER;i++)
  { hbanner[i]=HGET8;
    if (hbanner[i]=='\n') break;
  } 
  hbanner[++i]=0;
}
@

To read a long format file, we use the function |fgetc|.
\readcode
@<read the banner@>=
{ int i=0,c;
  do {
    c =fgetc(hin);
    if (c!=EOF) hbanner[i++]=(char)c; else break;
  } while (c!='\n' && i<MAX_BANNER);
  hbanner[i]=0;
}
@

Writing the banner to a short format file is accomplished by calling
|hput_banner| with the ``magic'' string |"hint"| as a first argument
and a (short) comment as the second argument.
\putcode
@<function to write the banner@>=
extern int version, subversion;
static size_t hput_banner(char *magic, char *s)
{ return fprintf(hout,"%s %d.%d %s\n",magic,version,subversion,s);
}
@


\writecode
Writing the banner of a long format file is essentialy the same as for short
format file calling |hput_banner| with |"HINT"| as a first argument.

\subsection{Long Format Files}\gdef\subcodetitle{Banner}%

After reading and checking the banner, reading a long format file is
simply done by calling |yyparse|. The following rule gives the big picture:
\readcode
@s hint symbol
@s content_section symbol

@<parsing rules@>=
hint: directory_section definition_section content_section ;
@


\subsection{Short Format Files}\gdef\subcodetitle{Primitives}%
A short format\index{short format} file starts with the banner and continues
with a list of sections. Each section has a maximum size
of $2^{32}$ byte or 4GByte. This restriction ensures that positions\index{position}
inside a section can be stored as 32 bit integers, a feature that
we will need only for the so called ``content'' section, but it
is also nice for implementers to know in advance what sizes to expect.
The big picture is captured by the |put_hint| function:

@<put functions@>=
static size_t hput_root(void);
static size_t hput_section(uint16_t n);
static void hput_optional_sections(void);

void hput_hint(char * str)
{ size_t s;
  DBG(DBGBASIC,"Writing hint output %s\n",str); 
  s=hput_banner("hint",str);
  DBG(DBGDIR,@["Root Entry at " SIZE_F "\n"@],s);
  s+=hput_root();
  DBG(DBGDIR,@["Directory section at " SIZE_F "\n"@],s);
  s+=hput_section(0);
  DBG(DBGDIR,@["Definition section at " SIZE_F "\n"@],s);
  s+=hput_section(1);
  DBG(DBGDIR,@["Content section at " SIZE_F "\n"@],s);
  s+=hput_section(2);
  DBG(DBGDIR,@["Auxiliary sections at " SIZE_F "\n"@],s);
  hput_optional_sections();
}
@


When we work on a section, we will have the entire section in
memory and use three variables to access it:  |hstart|
points to the first byte of the section, |hend| points
to the byte after the last byte of the section, and |hpos| points to the 
current position inside the section.\label{hpos}

@<common variables@>=
uint8_t *hpos=NULL, *hstart=NULL, *hend=NULL;
@

There are two sets of macros that read or write binary data at the current position
and advance the stream position accordingly.\label{HPUT}\label{HGET}

\getcode

@<get file macros@>=
#define HGET_ERROR QUIT(@["HGET overrun in section %d at " SIZE_F "\n"@],section_no,hpos-hstart)
#define @[HEND@]   @[((hpos<=hend)?0:(HGET_ERROR,0))@]

#define @[HGET8@]      ((hpos<hend)?*(hpos++):(HGET_ERROR,0))
#define @[HGET16(X)@] ((X)=(hpos[0]<<8)+hpos[1],hpos+=2,HEND)
#define @[HGET24(X)@] ((X)=(hpos[0]<<16)+(hpos[1]<<8)+hpos[2],hpos+=3,HEND)
#define @[HGET32(X)@] ((X)=(hpos[0]<<24)+(hpos[1]<<16)+(hpos[2]<<8)+hpos[3],hpos+=4,HEND)
#define @[HGETTAG(A)@] @[A=HGET8,DBGTAG(A,hpos-1)@]
@

\putcode
@<put functions@>=
void hput_error(void)
{if (hpos<hend) return;
 QUIT("HPUT overrun section %d pos=" SIZE_F "\n"@],section_no,hpos-hstart);
}
@

@<put macros@>=
extern void hput_error(void);
#define @[HPUT8(X)@]       (hput_error(),*(hpos++)=(X))
#define @[HPUT16(X)@]      (HPUT8(((X)>>8)&0xFF),HPUT8((X)&0xFF))
#define @[HPUT24(X)@]      (HPUT8(((X)>>16)&0xFF),HPUT8(((X)>>8)&0xFF),HPUT8((X)&0xFF))
#define @[HPUT32(X)@]      (HPUT8(((X)>>24)&0xFF),HPUT8(((X)>>16)&0xFF),HPUT8(((X)>>8)&0xFF),HPUT8((X)&0xFF))
@

The above macros test for buffer overruns\index{buffer overrun};
allocating sufficient buffer space is done separately.

Before writing a node, we will insert a test and increase the buffer if necessary.
@<put macros@>=
void  hput_increase_buffer(uint32_t n);
#define @[HPUTX(N)@] @[(((hend-hpos) < (N))? hput_increase_buffer(N):(void)0)@]
#define HPUTNODE  @[HPUTX(MAX_TAG_DISTANCE)@]
#define @[HPUTTAG(K,I)@] @[(HPUTNODE,@+DBGTAG(TAG(K,I),hpos),@+HPUT8(TAG(K,I)))@]
@ 

Fortunately the only data types that have an unbounded size are strings\index{string} and texts\index{text}.
For these we insert specific tests. For all other cases a relatively
small upper bound on the maximum distance between two tags can be determined.

% My guess from grep "subq" skip.s | grep hpos | sort -n is 25
@<hint macros@>=
#define MAX_TAG_DISTANCE 32 /* This is a guess; I need a tight upper bound. */
@

\subsection{Mapping a Short Format File}
Since modern computers with 64bit hardware have a huge address space,
mapping the entire file into virtual memory is the most efficient way
to read a large file.  ``Mapping'' is not the same as ``reading'' and it is
not the same as allocating precious memory, all that is done by the
operating system when needed. Mapping just reserves adresses.

The following functions map and unmap a short format input 
file at address |hbase|.\label{map}


@<map functions@>=
@<|mmap| and |munmap| declarations@>@;
static size_t hbase_size;
uint8_t *hbase=NULL;
extern char *in_name;
void hget_map(void)
{ struct stat st;
  int fd;
  fd = open(in_name, O_RDONLY, 0);
  if (fd<0) QUIT("Unable to open file %s", in_name);
  if (fstat(fd, &st)<0) QUIT("Unable to get file size");
  hbase_size=st.st_size;
  hbase= mmap(NULL,hbase_size,PROT_READ,MAP_PRIVATE,fd, 0);
  if (hbase==MAP_FAILED) 
  { hbase=NULL;hbase_size=0;
    QUIT("Unable to map file into memory");
  }
  close(fd);
  hpos=hstart=hbase;
  hend=hstart+hbase_size;
}


void hget_unmap(void)
{ munmap(hbase,hbase_size);
  hbase=NULL;
  hbase_size=0;
  hpos=hstart=hend=NULL;
}
@
A small complication arrises from the fact that the |mmap| and
|munmap| functions and the associated header files are not available
under the Windows operating system and not even under MinGW.

So we need to implement our own version of these functions.  We do not
implement general purpose replacements but only a replacement for the
calls with the parameters used above.  We start with the function
|_get_osfhandle| to obtain a Windows |HANDLE| for the given file
descriptor, then use |GetFileSize|, |CreateFileMapping|, and finally
|MapViewOfFile|.  The file is closed with |CloseHandle|.


@<|mmap| and |munmap| declarations@>=
#ifdef WIN32
#include <windows.h>
#include <io.h>
#define PROT_READ   0x1
#define MAP_PRIVATE 0x02
#define MAP_FAILED   ((void *) -1)
static HANDLE hMap;
void *mmap(void *addr, size_t length, int prot, int flags,
                  int fd, off_t offset)
{ HANDLE hFile=(HANDLE)_get_osfhandle(fd);
  if (hFile==INVALID_HANDLE_VALUE) QUIT("Unable to get file handle");
  hMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
  if (hMap == NULL) QUIT("Unable to map file into memory");
  addr = MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);
  if (addr==NULL) QUIT("Unable to obtain address of file mapping");
  CloseHandle(hFile);
  return addr;
}

int munmap(void *addr, size_t length)
{ UnmapViewOfFile(addr);
  CloseHandle(hMap);
  hMap=NULL;
  return 0;
}
#else
#include <sys/mman.h>
#endif
@


After mapping the file at address |hbase|, access to sections of the
file is provided by setting the three pointers |hpos|, |hstart|, and
|hend|. The value |hbase==NULL| indicates, that no file is open.


\gdef\subcodetitle{Sections}%
To read sections of a short format input file, we use the function |hget_section|. 

\getcode
%\codesection{\getsymbol}\getindex{1}{3}{Files}
@<get file functions@>=
@<|hdecompress| function@>@;

void hget_section(uint16_t n)
{ DBG(DBGDIR,"Reading section %d\n",n);
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

To write a short format file, we allocate for each of the first three sections a 
suitable buffer\index{buffer}, then fill these buffers, and finally write them
out in sequential order.

@<put functions@>=
#define BUFFER_SIZE 0x400
void new_output_buffers(void)
{ dir[0].bsize=dir[1].bsize=dir[2].bsize=BUFFER_SIZE;
  DBG(DBGBUFFER,"Allocating output buffer size=0x%x, margin=0x%x\n",BUFFER_SIZE,MAX_TAG_DISTANCE);
  ALLOCATE(dir[0].buffer,dir[0].bsize+MAX_TAG_DISTANCE,uint8_t);
  ALLOCATE(dir[1].buffer,dir[1].bsize+MAX_TAG_DISTANCE,uint8_t);
  ALLOCATE(dir[2].buffer,dir[2].bsize+MAX_TAG_DISTANCE,uint8_t);
}

void  hput_increase_buffer(uint32_t n)
{  size_t bsize;
   uint32_t pos;
   const double buffer_factor=1.4142136; /* $\sqrt 2$ */
   pos=hpos-hstart;
   bsize=dir[section_no].bsize*buffer_factor+0.5;
   if (bsize<pos+n) bsize=pos+n;
   if (bsize>=0xFFFFFFFF) bsize=0xFFFFFFFF;
   if (bsize<pos+n)  QUIT(@["Unable to increase buffer size " SIZE_F " by 0x%x byte"@],@|hpos-hstart,n);
   DBG(DBGBUFFER,@["Reallocating output buffer "@|" for section %d from 0x%x to " SIZE_F " byte\n"@],
       section_no,dir[section_no].bsize,bsize);
   REALLOCATE(dir[section_no].buffer,bsize,uint8_t);
   dir[section_no].bsize=(uint32_t)bsize;
   hstart=dir[section_no].buffer;
   hend=hstart+bsize;
   hpos=hstart+pos;
}


static size_t hput_data(uint16_t n, uint8_t *buffer, uint32_t size)
{ size_t s;
  s=fwrite(buffer,1,size,hout);
  if (s!=size)
    QUIT(@["short write " SIZE_F " < %d in section %d"@],s,size,n);
  return s;
}

static size_t hput_section(uint16_t n)
{ return hput_data(n, dir[n].buffer,dir[n].size);
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

@<|hdecompress| function@>=

static void hdecompress(uint16_t n)
{ z_stream z; /* decompression stream */
  uint8_t *buffer;
  int i;

  DBG(DBGCOMPRESS,"Decompressing section %d from 0x%x to 0x%x byte\n",@|n, dir[n].size, dir[n].xsize);
  z.zalloc = (alloc_func)0;@+
  z.zfree = (free_func)0;@+
  z.opaque = (voidpf)0;
  z.next_in  = hstart;
  z.avail_in = hend-hstart;
  if (inflateInit(&z)!=Z_OK)
    QUIT("Unable to initialize decompression: %s",z.msg);
  ALLOCATE(buffer,dir[n].xsize+MAX_TAG_DISTANCE,uint8_t);
  DBG(DBGBUFFER,"Allocating output buffer size=0x%x, margin=0x%x\n",dir[n].xsize,MAX_TAG_DISTANCE);
  z.next_out = buffer;           
  z.avail_out =dir[n].xsize+MAX_TAG_DISTANCE;
  i= inflate(&z, Z_FINISH);
  DBG(DBGCOMPRESS,"in: avail/total=0x%x/0x%lx "@|"out: avail/total=0x%x/0x%lx, return %d;\n",@|
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

@<|hcompress| function@>=
static void hcompress(uint16_t n)
{ z_stream z; /* compression stream */
  uint8_t *buffer;
  int i;
  if (dir[n].size==0)   { dir[n].xsize=0; return; }
  DBG(DBGCOMPRESS,"Compressing section %d of size 0x%x\n",n, dir[n].size);
  z.zalloc = (alloc_func)0;@+
  z.zfree = (free_func)0;@+
  z.opaque = (voidpf)0;
  if (deflateInit(&z,Z_DEFAULT_COMPRESSION)!=Z_OK)
    QUIT("Unable to initialize compression: %s",z.msg);
  ALLOCATE(buffer,dir[n].size+MAX_TAG_DISTANCE,uint8_t);
  z.next_out = buffer;
  z.avail_out = dir[n].size+MAX_TAG_DISTANCE;
  z.next_in = dir[n].buffer;
  z.avail_in = dir[n].size;
  i=deflate(&z, Z_FINISH);
  DBG(DBGCOMPRESS,"deflate in: avail/total=0x%x/0x%lx out: avail/total=0x%x/0x%lx, return %d;\n",@|
    z.avail_in,z.total_in, z.avail_out, z.total_out,i);
  if (z.avail_in != 0) 
    QUIT("Compression missed input data");
  if (i!=Z_STREAM_END)
    QUIT("Compression incomplete: %s",z.msg);
  if (deflateEnd(&z)!=Z_OK)
    QUIT("Unable to finalize compression: %s",z.msg);
  DBG(DBGCOMPRESS,"Compressed 0x%lx byte to 0x%lx byte\n",@|z.total_in,z.total_out);
  free(dir[n].buffer);
  dir[n].buffer=buffer;
  dir[n].bsize=dir[n].size+MAX_TAG_DISTANCE;
  dir[n].xsize=dir[n].size;
  dir[n].size=z.total_out;
}
@



\section{Directory Section}
A \HINT/ file is subdivided in sections and 
each section can be identified by its section number.
The first three sections, numbered 0, 1, and 2, are mandatory: 
directory\index{directory section} section, definition section,  and content section. 
The directory section, which we explain now, lists all sections
that make up a \HINT/ file. 

A document will often contain not only plain text but also other media
for example illustrations. Illustrations are produced with specialized
tools and stored in specialized files. Because a \HINT/ file in short format
should be self contained, these special files are embedded in the \HINT/ file
as optional sections.
Because a \HINT/ file in long format should be readable, these special files 
are written to disk and only the file names are retained in the directory.
Writing special files to disk has also the advantage that you can modify
them individually before embedding them in a short format file.


\subsection{Directories in Long Format}\gdef\subcodetitle{Directory Section}%
The directory\index{directory section} section of a long format \HINT/ file starts
with the  ``\.{directory}'' keyword; then follows the maximum section number used and 
a list of directory entries, one for each optional section numbered 3 and above.
Each entry consists of the keyword ``\.{section}'' followed by the
section number, followed by the file name.
The section numbers must be unique and fit into 16 bit.
The directory entries must be ordered with strictly increasing section numbers.
Keeping section numbers consecutive is recommended because it reduces the
memory footprint if directories are stored as arrays indexed by the section
number as we will do below.

\readcode
@s directory_section symbol
@s entry_list symbol 
@s entry symbol
@s DIRECTORY symbol
@s SECTION symbol

@<symbols@>=
%token DIRECTORY "directory"
%token SECTION "entry"
@

@<scanning rules@>=
::@=directory@>     :< return DIRECTORY; >:
::@=section@>     :< return SECTION; >:
@

@<parsing rules@>=
directory_section: START DIRECTORY UNSIGNED @|{new_directory($3+1); new_output_buffers();} entry_list END ;
entry_list: @,@+ | entry_list entry;
entry: START SECTION UNSIGNED string END @/
    {  RNG("Section number",$3,3,max_section_no); hset_entry(&(dir[$3]), $3,0,0,$4);};
@



We use a dynamically allocated array
of directory entries to store the directory.

@<directory entry type@>=
typedef struct {
uint64_t pos;
uint32_t size, xsize;
uint16_t section_no;
char *file_name;
uint8_t *buffer;
uint32_t bsize;
} entry_t;
@


The function |new_directory| allocates the directory.

@<directory functions@>=
entry_t *dir=NULL;
uint16_t section_no,  max_section_no;
void new_directory(uint32_t entries)
{ DBG(DBGDIR,"Creating directory with %d entries\n", entries);
  RNG("Directory entries",entries,3,0x10000);
  max_section_no=entries-1;
  ALLOCATE(dir,entries,entry_t);
  dir[0].section_no=0; @+ dir[1].section_no=1; @+ dir[2].section_no=2;
} 
@

The function |hset_entry| fills in the appropriate entry.
@<directory functions@>=
void hset_entry(entry_t *e, uint16_t i, uint32_t size, uint32_t xsize, @|char *file_name)
{ e->section_no=i;
  e->size=size; @+e->xsize=xsize;
  if (file_name==NULL || *file_name==0)
    e->file_name=NULL;
  else
    e->file_name=strdup(file_name);
  DBG(DBGDIR,"Creating entry %d: \"%s\" size=0x%x xsize=0x%x\n",@|i,file_name,size,xsize);
}
@


Writing the auxiliary files depends on the {\tt -f} and the {\tt -g}
option.

@<without {\tt -f} skip writing an existing file@>=
    if ( !option_force && access(file_name,F_OK)==0)
    { MESSAGE("File '%s' exists.\n"@| "To rewrite the file use the -f option.\n",
              file_name);
      continue;
    }
@

The above code uses the |access| function, and we need to make sure it is defined:
@<make sure |access| is defined@>=
#ifdef WIN32
#include <io.h>
#define @[access(N,M)@] @[_access(N, M )@] 
#define F_OK 0
#else
#include <unistd.h>
#endif
@

With the {\tt -g} option, filenames are considered global, and files
are written to the filesystem possibly overwriting the existing files.
For example a font embedded in a \HINT/ file might replace a font of
the same name in some operating systems font folder.
If the \HINT/ file is {\tt shrink}ed on one system and
{\tt stretch}ed on another system, this is usually not the desired behaviour.
Without the {\tt -g} option,\label{absrel} the files will be written in two local directories.
The names of these directories are derived from the output file name,
replacing the extension ``{\tt .HINT}'' with ``{\tt .abs}'' if the original
filename contained an absolute path, and  replacing it with ``{\tt .rel}''
if the original filename contained a relative path. Inside these directories,
the path as given in the filename is retained.
When {\tt shrink}ing a \HINT/ file without the {\tt -g} option,
the original filenames can be reconstructed.

@<without {\tt -g} compute a local |file_name|@>=
if (!option_global)
{ int path_length=(int)strlen(file_name);
  @<determine whether |file_name| is absolute or relative@>@;
  if (file_name_length<stem_length+ext_length+path_length)
  { file_name_length=stem_length+ext_length+path_length;
    REALLOCATE(stem_name, file_name_length+1,char);
  }
  strcpy(stem_name+stem_length,aux_ext[name_type]);
  strcpy(stem_name+stem_length+ext_length,file_name);
  DBG(DBGDIR,"Replacing auxiliar file name:\n\t%s\n->\t%s\n",file_name,stem_name);
  file_name=stem_name;
}
@

@<determine whether |file_name| is absolute or relative@>=
  enum {absolute=0, relative=1} name_type;
  char *aux_ext[2]={".abs/",".rel/"};
  int ext_length=5;
  if (file_name[0]=='/')
  {  name_type=absolute;
    file_name++; path_length--;
  }
  else if (path_length>3 && isalpha(file_name[0]) &&
           file_name[1]==':' && file_name[2]=='/')
  { name_type=absolute;
    file_name[1]='_';
  }      
  else
    name_type=relative;
@
It remains to create the direcories along the path we might have constructed.
@<make sure the path in |file_name| exists@>=
{ char *path_end;
  path_end=file_name+1;
  while (*path_end!=0)
  { if(*path_end=='/')
    { struct stat s;
     *path_end=0;   
      if (stat(file_name,&s)==-1)
      {
#ifdef WIN32
      if (mkdir(file_name)!=0)
#else
      if (mkdir(file_name,0777)!=0)
#endif
           QUIT("Unable to create directory %s",file_name);
         DBG(DBGDIR,"Creating directory %s\n",file_name);
      } else if (!S_ISDIR(s.st_mode))
        QUIT("Unable to create directory %s, file exists",file_name);
      *path_end='/';
    }
    path_end++;
  }
}
  
  
@

\writecode
@<write functions@>=
@<make sure |access| is defined@>@;
extern char *stem_name;
extern int stem_length;

void hwrite_aux_files(void)
{ int i;
  DBG(DBGDIR,"Writing %d aux files\n",max_section_no-2);
  for (i=3;i<=max_section_no;i++)
  { FILE *f;
    char * file_name=dir[i].file_name;
    int file_name_length=0;

    
    @<without {\tt -g} compute a local |file_name|@>@;
    @<without {\tt -f} skip writing an existing file@>@;
    @<make sure the path in |file_name| exists@>@;

    f=fopen(file_name,"wb");
    if (f==NULL) 
      QUIT("Unable to open file '%s' for writing",file_name);
    else
    { size_t s;
      hget_section(i);
      DBG(DBGDIR,"Writing file %s\n",file_name);
      s=fwrite(hstart,1,dir[i].size,f);
      if (s!=dir[i].size) QUIT("writing file %s",file_name);
      fclose(f);
    }
  }
}
@

We write the directory, and the directory entries
in long format using the following functions.
@<write functions@>=
static void hwrite_entry(int i)
{ hwrite_start();
  hwritef("section %u",dir[i].section_no);@+  hwrite_string(dir[i].file_name);
  hwrite_end();
}

void hwrite_directory(void)
{ int i;
  if (dir==NULL) QUIT("Directory not allocated");
  section_no=0;
  hwritef("<directory %u", max_section_no);@/
  for (i=3;i<=max_section_no;i++)
      hwrite_entry(i); 
  hwritef("\n>\n");
}
@

\subsection{Directories in Short Format}
The directory\index{directory section} section of a short format file contains entries 
for all sections including the directory section itself. After reading the
directory section, enough information---position and size---is available to
access any section directly. As usual, a directory entry starts and ends with
a tag byte. The kind part of an entry's tag is not used; it is always zero. 
The value $s$ of the two least significant bits of the info part indicate 
that sizes are stored using $s+1$ byte.  The most significant bit of the info
part is 1 if the section is stored in compressed\index{compression} form. In this case the size
of the section is followed by the size of the section after decompressing it.
After the tag byte follows the section number. In the short format file,
section numbers must be strictly increasing and consecutive. This is redundant but helps
with checking. Then follows the size---or the sizes---of the section. After the size
follows the file name terminated by a zero byte. The file name might be an empty
string in which case there is just the zero byte. After the zero byte follows
a copy of the tag byte.

Here is the macro and function to read a directory\index{directory entry} entry:
\gdef\subcodetitle{Directory Entries}%
\getcode

@<get file macros@>=
#define @[HGET_SIZE(I)@] \
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
  HGET16(i); HGET_SIZE(I); HGET_STRING(file_name); @/\
  hset_entry(&(E),i,s,xs,file_name); \
}
@

@<get file functions@>=
void hget_entry(entry_t *e)
{ @<read the start byte |a|@>@;
  DBG(DBGDIR,"Reading directory entry\n");
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
  DBG(DBGDIR,"entry %d: size=0x%x xsize=0x%x\n",@|e->section_no,e->size,e->xsize);
}
@

Because the first entry in the directory section describes the
directory section itself, we can not check its info bits in advance to determine
whether it is compressed or not. Therefore the directory section 
starts with a root entry, which is always uncompressed. It describes
the position and size of the remainder of the directory which
follows.
There are two differences between the root entry and a normal entry:
it starts with the maximum section number instead of the section number zero,
and its position describes the position of the
entry for section 1 (which might already be compressed).
The name of the directory section must be the empty string.
\gdef\subcodetitle{Directory Section}%
\getcode
@<get file functions@>=
static void hget_root(entry_t *root)
{ DBG(DBGDIR,"Get Root\n");
  hget_entry(root); 
  root->pos=hpos-hstart;
  max_section_no=root->section_no;
  root->section_no=0;
  if (max_section_no<2) QUIT("Sections 0, 1, and 2 are mandatory");
}

void hget_directory(void)
{ int i;
  entry_t root={0};
  hget_root(&root);
  DBG(DBGDIR,"Get Directory\n");
  new_directory(max_section_no+1);
  dir[0]=root;
  hget_section(0);
  for (i=1;i<=max_section_no;i++)@/
  { hget_entry(&(dir[i]));@+
    dir[i].pos=dir[i-1].pos +dir[i-1].size;@+
  }
  DBG(DBGDIR,"Directory at 0x%"PRIx64"\n",dir[0].pos);
  DBG(DBGDIR,"Definitions at 0x%"PRIx64"\n",dir[1].pos);
  DBG(DBGDIR,"Content at 0x%"PRIx64"\n",dir[2].pos);
}

void hclear_dir(void)
{ int i;
  if (dir==NULL) return;
  for (i=0;i<3;i++) /* currently the only compressed sections */
  if (dir[i].xsize>0 && dir[i].buffer!=NULL) free(dir[i].buffer);
  free(dir); dir=NULL;
}

@

When the \.{shrink} program writes the directory section in the short format,
it needs to know the sizes of all the  sections---including the optional sections.
These sizes are not provided in the long format because it is safer and more 
convenient to let the machine figure out the file sizes\index{file size}. 

@<set the file sizes for optional sections@>=
{ int i; 
  for (i=3;i<=max_section_no;i++)
    { struct stat s;
      if (stat(dir[i].file_name,&s)!=0)
        QUIT("Unable to obtain file size for '%s'",dir[i].file_name);
      dir[i].size=s.st_size;
      dir[i].xsize=0;
    }
}
@

The computation of the sizes of the mandatory sections will be 
explained later.
Armed with these preparations, we can put the directory into the \HINT/ file.

\gdef\subcodetitle{Directory Section}%
\putcode
@<put functions@>=
static void hput_entry(entry_t *e)
{ uint8_t b;
  if (e->size<0x100 && e->xsize<0x100) b=0;
  else if (e->size<0x10000 &&e->xsize<0x10000) b=1;
  else if (e->size<0x1000000 &&e->xsize<0x1000000) b=2;
  else b=3;
  if (e->xsize!=0) b =b|b100;
  DBG(DBGTAGS,"Directory entry no=%d size=0x%x xsize=0x%x\n",e->section_no, e->size, e->xsize);
  HPUTTAG(0,b);@/
  HPUT16(e->section_no);
  switch (b) {
  case 0: HPUT8(e->size);@+break;
  case 1: HPUT16(e->size);@+break;
  case 2: HPUT24(e->size);@+break;
  case 3: HPUT32(e->size);@+break;
  case b100|0: HPUT8(e->size);@+HPUT8(e->xsize);@+break;
  case b100|1: HPUT16(e->size);@+HPUT16(e->xsize);@+break;
  case b100|2: HPUT24(e->size);@+HPUT24(e->xsize);@+break;
  case b100|3: HPUT32(e->size);@+HPUT32(e->xsize);@+break;
  default: QUIT("Can't happen");@+ break;
  }
  hput_string(e->file_name);@/
  DBGTAG(TAG(0,b),hpos);@+HPUT8(TAG(0,b));
}

static void hput_directory_start(void)
{ DBG(DBGDIR,"Directory Section\n");
  section_no=0;
  hpos=hstart=dir[0].buffer;
  hend=hstart+dir[0].bsize;
}
static void hput_directory_end(void)
{ dir[0].size=hpos-hstart;
  DBG(DBGDIR,"End Directory Section size=0x%x\n",dir[0].size);
}

static size_t hput_root(void)
{ uint8_t buffer[MAX_TAG_DISTANCE];
  size_t s;
  hpos=hstart=buffer;
  hend=hstart+MAX_TAG_DISTANCE;
  dir[0].section_no=max_section_no;
  hput_entry(&dir[0]);
  s=hput_data(0, hstart,hpos-hstart);
  DBG(DBGDIR,@["Writing Root size=" SIZE_F "\n"@],s);
  return s;
}
@<|hcompress| function@>@;
extern bool option_compress;
void hput_directory(void)
{ int i;
  @<set the file sizes for optional sections@>@;
  if (option_compress) { hcompress(1); @+hcompress(2); @+}
  hput_directory_start();
  for (i=1; i<=max_section_no; i++)
  { dir[i].pos=dir[i-1].pos+dir[i-1].size;
    DBG(DBGDIR,"writing entry %u at 0x%" PRIx64 "\n",i,  dir[i].pos);
    hput_entry(&dir[i]);
  }
  hput_directory_end();
  if (option_compress) hcompress(0); 
}

@


To conclude this section, here is the function that  adds the files that
are described in the directory entries 3 and above to a \HINT/ file in short format.
Where these files are found depends on the {\tt -g} option.
With that option given, the file names of the directory entrys are used unchanged.
Without that option, the files are found in the {|in_name|\tt .abs} and  {|in_name|\tt .rel}
directories, as described in section~\secref{absrel}.

\gdef\subcodetitle{Optional Sections}%
\putcode
@<put functions@>=
static void hput_optional_sections(void)
{ int i;
  DBG(DBGDIR,"Optional Sections\n");
  for (i=3; i<=max_section_no; i++)@/
   { FILE *f;
     size_t fsize;
     char *file_name=dir[i].file_name;
     int file_name_length=0;
     DBG(DBGDIR,"file %d: %s\n",dir[i].section_no,file_name);
     if (dir[i].xsize!=0) @/
       DBG(DBGDIR,"Compressing of auxiliary files currently not supported");
     @<without {\tt -g} compute a local |file_name|@>
     f=fopen(file_name,"rb");
     if (f==NULL) QUIT("Unable to read section %d, file %s",
       dir[i].section_no,file_name);
     fsize=0;
     while (!feof(f))@/
     { size_t s,t;
       char buffer[1<<13]; /* 8kByte */       
       s=fread(buffer,1,1<<13,f);@/
       t=fwrite(buffer,1,s,hout);
       if (s!=t) QUIT("writing file %s",file_name);
       fsize=fsize+t;
     }
     fclose(f);
     if (fsize!=dir[i].size) 
       QUIT(@["File size " SIZE_F " does not match directory size %u"@],@|fsize,dir[i].size);
   }
}
@



\section{Definition Section}\index{definition section}
\label{definitions}
In a typical \HINT/ file, there are many things that are used over and over again.
For example the inter word glue of a specific font or the indentation of
the first line of a paragraph. The definition section contains this information so that 
it can be referenced in the content section by a simple reference number.
In addition there are a few parameters that guide the routines of \TeX.
An example is the ``above display skip'', which controls the amount of white space
inserted above a displayed equation, or the ``hyphen penalty'' that tells \TeX\
the ``\ae sthetic cost'' of ending a line with a hyphenated word. These parameters
also get their values in the definition section as explained in section~\secref{defaults}.


The most simple way to store these definitions is to store them in an array indexed by the
reference numbers.
To simplify the dynamic allocation of these arrays, the list of definitions
will always start with the list of maximum\index{maximum values} values: a list that contains
for each node type the maximum reference number used.

In the long format, the definition section starts with the keyword \.{definitions}, 
followed by the list of maximum values,
followed by the definitions proper. 

When writing the short format, we start by positioning the output stream at the beginning of
the definition buffer and we end with recording the size of the definition section
in the directory.

\readcode
@s definition_section symbol
@s definition_list symbol
@s definition symbol
@s DEFINITIONS symbol
@<symbols@>=
%token DEFINITIONS "definitions"
@

@<scanning rules@>=
::@=definitions@>   :< return DEFINITIONS; >:
@

@<parsing rules@>=
definition_section: START DEFINITIONS { hput_definitions_start();}@/
  max_definitions definition_list @/
  END {hput_definitions_end();};
definition_list: @+ | definition_list def_node {REF($2.k,$2.n);}; 
@

\writecode
@<write functions@>=
void hwrite_definitions_start(void)
{  section_no=1; @+hwritef("<definitions");
}

void hwrite_definitions_end(void)
{  hwritef("\n>\n");
}
@


@s def_t int

@<get functions@>=
void hget_definition_section(void)
{ DBG(DBGDEF,"Definitions\n");
  hget_section(1);
  hwrite_definitions_start();
  DBG(DBGDEF,"Reading list of maximum values\n");
  hget_max_definitions();
  @<allocate data@>@;
  hwrite_max_definitions();
  DBG(DBGDEF,"Reading list of definitions\n");
  while (hpos<hend) @/
  { def_t df; @+ hget_def_node(&df);
    if (max_fixed[df.k]>max_default[df.k]) 
      QUIT("Definitions for kind %s not supported", definition_name[df.k]);
    if(df.n>max_ref[df.k] || df.n <= max_fixed[df.k]) 
      QUIT("Definition %d for %s out of range [%d - %d]",@|
        df.n, definition_name[df.k],max_fixed[df.k]+1,max_ref[df.k]);
  }
  hwrite_definitions_end();
}
@

\putcode
@<put functions@>=
void hput_definitions_start(void)
{ DBG(DBGDEF,"Definition Section\n");
  section_no=1;
  hpos=hstart=dir[1].buffer;
  hend=hstart+dir[1].bsize;
}
void hput_definitions_end(void)
{ dir[1].size=hpos-hstart;
  DBG(DBGDEF,"End Definition Section size=0x%x\n",dir[1].size);
}
@
\gdef\codetitle{Definitions}
\hascode
\subsection{Maximum Values}\index{maximum values}
To help implementations allocating the right amount of memory for the
definitions, the definition section starts with a list of maximum
values.  For each kind of node, we store the maximum valid reference
number in the array |max_ref| which is indexed by the kind values.
For a reference number |n| and kind value $k$ we have 
$0\le n\le |max_ref[k]|$.  
To make sure that a hint file without any definitions
will work, some definitions have default values. 
The initialization of default and maximum values is described 
in section~\secref{defaults}. The maximum
reference number that has a default value is stored in the array
|max_default|.  We have $-1 \le |max_default[k]| \le |max_ref[k]| \le
255$.  Specifying maximum values that are lower than the
default\index{default value} values is not allowed in the short
format; in the long format, lower values are silently ignored.  Some
default values are permanently fixed; for example the zero glue with
reference number |zero_skip_no| must never change. The array
|max_fixed| stores the maximum reference number that is fixed for a
given kind.  Definitions with reference numbers lower than the
corresponding |max_fixed[k]| number are disallowed. Usually we have
$-1 \le |max_fixed[k]| \le |max_default[k]| $, but if for a kind value
$k$ no definitions, and hence no maximum values are allowed, we set
$|max_fixed[k]|=|0x100|>|max_default[k]| $.


We use the |max_ref| array whenever we find a
reference number in the input to check if it is within the proper range.

@<debug macros@>=
#define @[REF(K,N)@] if ((int)(N)>max_ref[K]) QUIT("Reference %d to %s out of range [0 - %d]",\
  (N),definition_name[K],max_ref[K])
@

In the long format file, the list of maximum values starts with
 ``\.{<max }'', then follow pairs of keywords and numbers like
 ``\.{<glue 57>}'', and it ends with ``\.{>}''.  In the short format,
 we start the list of maximums with a |list_kind| tag and end it with
 a |list_kind| tag.  Each maximum value is preceded and followed by a
 tag byte with the appropriate kind value. The info value is always 1
 because at present, reference numbers---and therefore maximum
 values---are restricted to the range 0 to 255 in order to fit into a
 single byte. Other info values are reserved for future extensions.
After reading the maximum values, we allocate data for the defininitions
that come next.


\readcode 
@s max_list symbol
@s max_value symbol
@s max_definitions symbol
@s MAX symbol
@<symbols@>=
%token MAX "max"
@

@<scanning rules@>=
::@=max@>          :< return MAX; >:
@
@<parsing rules@>=
max_definitions: START MAX max_list END @|
 { @<allocate data@>@; hput_max_definitions(); };
max_list:@+ | max_list START max_value END;

max_value: FONT UNSIGNED      { hset_max(font_kind,$2); }
         | INTEGER UNSIGNED       { hset_max(int_kind,$2); }
         | DIMEN UNSIGNED     { hset_max(dimen_kind,$2); }
         | LIGATURE UNSIGNED  { hset_max(ligature_kind,$2); }
         | HYPHEN UNSIGNED    { hset_max(hyphen_kind,$2); }
         | GLUE UNSIGNED      { hset_max(glue_kind,$2); }
         | MATH UNSIGNED      { hset_max(math_kind,$2); }
         | RULE UNSIGNED      { hset_max(rule_kind,$2); }
         | IMAGE UNSIGNED     { hset_max(image_kind,$2); }
         | LEADERS UNSIGNED   { hset_max(leaders_kind,$2); }
         | BASELINE UNSIGNED  { hset_max(baseline_kind,$2); }
         | XDIMEN UNSIGNED    { hset_max(xdimen_kind,$2); }
         | PARAM UNSIGNED     { hset_max(param_kind,$2); }
         | STREAM UNSIGNED    { hset_max(stream_kind,$2); }
         | PAGE UNSIGNED      { hset_max(page_kind,$2); }
         | RANGE UNSIGNED     { hset_max(range_kind,$2); };
@

@<parsing functions@>=
void hset_max(kind_t k, int n)
{ RNG("Maximum",n,max_fixed[k]+1,0xFF); 
  if (n>max_ref[k]) 
  { max_ref[k]=n; 
    DBG(DBGDEF,"Setting max %s to %d\n",definition_name[k],n);
  }
}
@

\writecode
@<write functions@>=
void hwrite_max_definitions(void)
{ kind_t k;
  hwrite_start();@+
  hwritef("max");
  for (k=0; k<32;k++)
    if (max_ref[k]>max_default[k])@/
    { hwrite_start();
      hwritef("%s %d",definition_name[k], max_ref[k]);
      hwrite_end();
    }
  hwrite_end();
}          
@

\getcode
@<get file functions@>=
void hget_max_definitions(void)
{ kind_t k;
  @<read the start byte |a|@>@;
  if (a!=TAG(list_kind,0)) QUIT("Start of maximum list expected");
  for(k= 0;k<32;k++)max_ref[k]= max_default[k];
  while (true) @/
  { uint8_t n;
    if (hpos>=hend) QUIT("Unexpected end of maximum list");
    node_pos=hpos-hstart;
    HGETTAG(a);
    if  (KIND(a)==list_kind) break;
    if (INFO(a)!=1) QUIT("Maximum info %d not supported",INFO(a));
    k=KIND(a);
    if (max_fixed[k]>max_default[k]) 
      QUIT("Maximum value for kind %s not supported",definition_name[k]);
    n=HGET8;
    RNG("Maximum number",n,max_ref[k],0xFF);
    max_ref[k]=n;
    DBG(DBGDEF,"max(%s) = %d\n",definition_name[k],max_ref[k]);
   @<read and check the end byte |z|@>@;
  }
  if (INFO(a)!=0) QUIT("End of maximum list with info %d", INFO(a));

}
@

\putcode

@<put functions@>=
void hput_max_definitions(void)
{ kind_t k;
  DBG(DBGDEF,"Max Definitions Begin\n");
  HPUTTAG(list_kind,0);
  for (k=0; k<32; k++)
    if (max_ref[k]>max_default[k])
    { DBG(DBGDEF,"max(%s) = %d\n",definition_name[k],max_ref[k]);
      HPUTTAG(k,1); 
      HPUT8(max_ref[k]);
      HPUTTAG(k,1); 
    }
  HPUTTAG(list_kind,0);
  DBG(DBGDEF,"Max Definitions End\n");
}
@


\subsection{Definitions}
A definition\index{definition section} associates a reference number with a content node.
Here is an example: A glue definition associates a glue number, for example 71,
with a glue specification. In the long format this might look like  
``{\tt \.{<}glue *71 4pt plus 5pt minus 0.5pt\.{>}}'' which makes glue number 71
refer to a 4pt glue with a stretchability of 5pt and a shrinkability of 0.5pt.
Whenever we need this glue in the content section, we can say ``{\tt \.{<}glue *71\.{>}}''.
Because we restrict the number of definitions for every node type to at most 256,
a single byte is sufficient to store the reference number.
The \.{shrink} and \.{stretch} programs will, however, not bother to 
store the definitions. Instead they will write them  in the new format immediately to the output.


Such a definition differs from a normal content node just by an extra byte value 
immediately following the keyword respectively  start byte. The parser will handle 
definitions in any order, but of course, it does not harm to present them 
in a systematic way. 

@<hint types@>=
typedef struct{@+kind_t k; @+ int n;@+} def_t;
@


\vskip 0pt plus 20pt
\goodbreak
\vskip 0pt plus -20pt
\putcode\penalty +1000\vskip -\baselineskip
\readcode
@s ref symbol
@s font symbol
@<symbols@>=
%type <u> ref
%type <df> def_node
@

@<parsing rules@>=
ref: REFERENCE {RNG("Reference",$1,0,255); HPUT8($1);};
def_node: 
  start FONT    ref font END  @| { DEF($$,font_kind,$3);@+   hput_tags($1,$4);@+} 
| start INTEGER     ref integer END   @| { DEF($$,int_kind,$3);@+   hput_tags($1,hput_int($4));@+} 
| start DIMEN   ref dimension END @| { DEF($$,dimen_kind,$3);@+   hput_tags($1,hput_dimen($4));} 
| start MATH ref math END         @| { DEF($$,math_kind,$3);@+    hput_tags($1,hput_math(&($4)));}
| start GLUE    ref glue END      @| { DEF($$,glue_kind,$3);@+    hput_tags($1,hput_glue(&($4)));} 
| start XDIMEN  ref xdimen END    @| { DEF($$,xdimen_kind,$3);@+  hput_tags($1,hput_xdimen(&($4)));} 
| start RULE    ref rule END      @| { DEF($$,rule_kind,$3);@+    hput_tags($1,hput_rule(&($4)));} 
| start LEADERS ref leaders END   @| { DEF($$,leaders_kind,$3);@+ hput_tags($1,TAG(leaders_kind, $4));} 
| start BASELINE ref baseline END @| { DEF($$,baseline_kind,$3);@+hput_tags($1,TAG(baseline_kind, $4));} 
| start LIGATURE ref ligature END @| { DEF($$,ligature_kind,$3);@+hput_tags($1,hput_ligature(&($4)));} 
| start HYPHEN ref hyphen END     @| { DEF($$,hyphen_kind,$3);@+  hput_tags($1,hput_hyphen(&($4)));} 
| start IMAGE  ref image END      @| { DEF($$,image_kind,$3);@+   hput_tags($1,hput_image(&($4)));}
| start PARAM  ref param_list END @| { DEF($$,param_kind,$3);@+   hput_tags($1,hput_list($1+2,&($4)));} 
| start PAGE   ref page END       @| { DEF($$,page_kind,$3);@+    hput_tags($1,TAG(page_kind,0));}; 
@

@<parsing functions@>=
#define @[DEF(D,K,N)@] (D).k=K;@+ (D).n=(N);@+RNG("Reference",N,max_fixed[K]+1,max_ref[K]);
@
\vskip 0pt plus 20pt
\goodbreak
\vskip 0pt plus -20pt
\writecode\penalty +1000\vskip -\baselineskip
\getcode
@<get functions@>=
void hget_def_node(def_t *df)
{ @<read the start byte |a|@>@;
  df->k=KIND(a);
  df->n=HGET8;
  DBG(DBGTAGS,"Defining %s %d\n", definition_name[df->k],df->n);
  if (df->k==range_kind)
    hget_range(INFO(a),df->n);
  else @/
  { hwrite_start(); @+hwritef("%s *%d", definition_name[df->k],df->n);
    if (df->k==font_kind) hget_font_def(INFO(a),df->n);
    else if (df->k==param_kind) @/
    {@+ list_t l; l.k=param_kind; @+HGET_LIST(INFO(a),l); @+hwrite_param_list(&l); @+} 
    else if (df->k==page_kind)
      hget_page();
    else if (df->k==dimen_kind)
      hget_dimen();
    else if (df->k==xdimen_kind)
    {@+ xdimen_t x;  hget_xdimen(a,&x); hwrite_xdimen(&x); }
    else hget_content(a);
    hwrite_end();
  }

  @<read and check the end byte |z|@>@;
}
@

\subsection{Parameter Lists}\label{paramlist}\index{parameter list}
Because the content section is a ``stateless'' list of nodes, the definitions we see in the
definition section can never change. It is however necessary to make occasionally local
modifications of some of these definitions, because some definitions are parameters of the 
algorithms borrowed from \TeX. Nodes that need such modifications, for example
the paragraph nodes that are passed to \TeX's line breaking algorithm, 
contain a list of local definitions called parameters.
Typically sets of related parameters are needed. 
To facilitate a simple reference to such a set of parameters, we allow
predefined parameter lists that can be referenced by a single number.
The parameters of \TeX's routines are quite basic: integers\index{integer}, 
dimensions\index{dimension}, and glues\index{glue}.
Therefore we restrict the definitions in parameter lists to such basic definitions.

@<parsing functions@>=
void check_param_def(def_t *df)
{ if(df->k!=int_kind && df->k!=dimen_kind &&  @| df->k!=glue_kind)
    QUIT("Kind %s not allowed in parameter list", definition_name[df->k]);
  REF(df->k,df->n);
}
@

The definitions below repeat the definitions we have seen for lists in section~\secref{plainlists} 
with small modifications. For example we use the kind value |param_kind|. An empty parameter list
is omitted in the long format as well as in the short format.


\vskip 0pt plus 20pt
\goodbreak
\vskip 0pt plus -20pt
\putcode\penalty +1000\vskip -\baselineskip
\readcode

@s PARAM symbol
@s def_list symbol
@s param_list_node symbol
@s def_node symbol
@s param_list symbol
@<symbols@>=
%token PARAM "param"
%type <u> def_list
%type <l> param_list param_list_node
@

@<scanning rules@>=
::@=param@>  :< return PARAM; >:
@
@<parsing rules@>=
def_list:  position @+
          | def_list def_node {check_param_def(&($2));};
param_list: estimate def_list { $$.p=$2; $$.k=param_kind; $$.s=(hpos-hstart)-$2;};
param_list_node: start PARAM param_list END @/
           { @+if ($3.s>0) hput_tags($1,hput_list($1+1,&($3)));@+};
@

\writecode
@<write functions@>=
void hwrite_param_list(list_t *l)
{ uint32_t h=hpos-hstart, e=hend-hstart; /* save |hpos| and |hend| */
  hpos=l->p+hstart;@+ hend=hpos+l->s;
  if (l->s>0xFF) hwritef(" %d",l->s); 
  while(hpos<hend)@/
    { def_t df;@+
      hget_def_node(&df);
    } 
  hpos=hstart+h;@+  hend=hstart+e; /* restore  |hpos| and |hend| */ 
}
void hwrite_param_list_node(list_t *l)
{ @+if (l->s!=0) @/
  { hwrite_start();@+
    hwritef("param"); 
    hwrite_param_list(l);
    hwrite_end();
  }
}
@

\getcode
@<get functions@>=
void hget_param_list_node(list_t *l)
{ @+if (KIND(*hpos)!=param_kind) @/
  {@+ l->p=hpos-hstart;@+ l->s=0;@+ l->k=param_kind;@+ } 
  else  hget_list(l);
}
@



\subsection{Fonts}\label{fonts}
Another definition that has no corresponding content node is the font\index{font} definition.
Fonts by themselves do not constitute content, instead they are used in glyph\index{glyph} nodes.
Fonts are also the only data, that never occur directly in a content node;
a font is always specified by its font number. This limits the number of fonts that
can be used in a \HINT/ file to at most 256.

A long format font definition starts with the keyword ``\.{font}'' and is followed
by the font number, as usual prefixed by an asterisk. Then comes the font specification with the optional font size, 
the font name,  the section number of the \TeX\ font metric file,
and the section number of the file containing the glyphs for the font.
Currently only \.{.pk} files are supported but the extension to \.{.ttf}
and \.{.otf} files is imminent. 
Further, a font must specify an inter word glue
and a default discretionary break. After that comes a list of up to 12 font specific 
parameters.

The optional font size specifies the desired font\index{font size} size. If omitted, we assign the value zero which implies
the design\index{design size} size of the font as stored in the \.{.tfm} file.

In the short format, the font specification is given in the same order as in the long format.
The info value will be |b001| if a font size is present, otherwise it is~|b000|.

Our internal representation of a font just stores the font name because in the long format we add the font name
as a comment to glyph nodes.


@<common variables@>=
char **hfont_name; /* dynamically allocated array of font names */
@

@<hint basic types@>=
#define MAX_FONT_PARAMS 11
@

@<allocate data@>=
ALLOCATE(hfont_name,max_ref[font_kind]+1,char *);
@



\readcode
@s FONT symbol
@s fref symbol
@s font_param_list symbol
@s font_param symbol
@s font_head symbol

@<symbols@>=
%token FONT     "font"
%type <info> font font_head
@

@<scanning rules@>=
::@=font@>  :< return FONT; >:
@

@<parsing rules@>=@/

font: font_head font_param_list;

font_head:string UNSIGNED UNSIGNED   @/
		 {uint8_t f=$<u>@&0; @+hfont_name[f]=strdup($1); $$=hput_font_head(f,hfont_name[f],0,$2,$3);}
| string dimension UNSIGNED UNSIGNED @/
  	 	 {uint8_t f=$<u>@&0; @+hfont_name[f]=strdup($1); $$=hput_font_head(f,hfont_name[f],$2,$3,$4);};

font_param_list: glue_node hyphen_node @+ | font_param_list font_param ;

font_param: @/
  start PENALTY fref penalty  END   { hput_tags($1,hput_int($4));} 
| start KERN    fref kern END  { hput_tags($1,hput_kern(&($4)));} 
| start LIGATURE fref ligature END  { hput_tags($1,hput_ligature(&($4)));} 
| start HYPHEN fref hyphen END      { hput_tags($1,hput_hyphen(&($4)));} 
| start GLUE    fref glue END       { hput_tags($1,hput_glue(&($4)));} 
| start MATH    fref math END       { hput_tags($1,hput_math(&($4)));} 
| start RULE    fref rule END       { hput_tags($1,hput_rule(&($4)));}
| start IMAGE   fref image END      { hput_tags($1,hput_image(&($4)));};

fref: REFERENCE @/{ RNG("Font parameter",$1,0,MAX_FONT_PARAMS); HPUT8($1); };
@

\vskip 0pt plus 20pt
\goodbreak
\vskip 0pt plus -20pt
\getcode\penalty +1000\vskip -\baselineskip
\writecode
@<get functions@>=
static void hget_font_params(void)
{ hyphen_t h;
  hget_glue_node(); 
  hget_hyphen_node(&(h));@+ hwrite_hyphen_node(&h); 
  DBG(DBGDEF,"Start font parameters\n");
  while (KIND(*hpos)!=font_kind)@/  
  { def_t df;
    @<read the start byte |a|@>@;
    df.k=KIND(a);
    df.n=HGET8;
    DBG(DBGDEF,"Reading font parameter %d: %s\n",df.n, definition_name[df.k]);
    if (df.k!=penalty_kind && df.k!=kern_kind && df.k!=ligature_kind && @|
        df.k!=hyphen_kind && df.k!=glue_kind && df.k!=math_kind && @| df.k!=rule_kind && df.k!=image_kind)
      QUIT("Font parameter %d has invalid type %s",df.n, content_name[df.n]);
    RNG("Font parameter",df.n,0,MAX_FONT_PARAMS);
    hwrite_start(); @+hwritef("%s *%d", content_name[df.k],df.n);
    hget_content(a);
    hwrite_end();
    @<read and check the end byte |z|@>@;
  }
  DBG(DBGDEF,"End font parameters\n");
}


void hget_font_def(info_t i, uint8_t f)
{ char *n; @+dimen_t s=0;@+uint16_t m,y; 
  HGET_STRING(n);@+ hwrite_string(n);@+  hfont_name[f]=strdup(n);
  if (i&b001) @+{ HGET32(s); @+if (s!=0) hwrite_dimension(s);@+}
  DBG(DBGDEF,"Font %s size 0x%x\n", n, s); 
  HGET16(m); @+RNG("Font metrics",m,3,max_section_no);
  HGET16(y); @+RNG("Font glyphs",y,3,max_section_no);
  hwritef(" %d %d",m,y);
  hget_font_params();
  DBG(DBGDEF,"End font definition\n");
}
@

\putcode
@<put functions@>=
uint8_t hput_font_head(uint8_t f,  char *n, dimen_t s, @| uint16_t m, uint16_t y)
{ info_t i=b000;
  DBG(DBGDEF,"Defining font %d\nFont %s size 0x%x\n", f, n, s); 
  hput_string(n);
  if (s!=0) {HPUT32(s);@+ i=b001;@+} 
  HPUT16(m); @+HPUT16(y); 
  return TAG(font_kind,i);
}
@



\subsection{References}\label{reference}
We have seen how to make definitions, now let's see how to reference\index{reference} them.
In the long form, we can simply write the reference number, after the keyword 
like this:  ``{\tt \.{<}glue *17\.{>}}''.
The asterisk\index{asterisk} is necessary to keep apart, for example, a
penalty with value 50, written  ``{\tt \.{<}penalty 50\.{>}}'', from
a penalty referencing the integer definition number 50, written ``{\tt \.{<}penalty *50\.{>}}''.

\vskip 0pt plus 20pt
\goodbreak
\vskip 0pt plus -20pt
\putcode\penalty +1000\vskip -\baselineskip
\readcode

@<parsing rules@>=
xdimen_ref: REFERENCE { REF(xdimen_kind,$1); @+HPUT8($1);};
param_ref: REFERENCE { REF(param_kind,$1);@+HPUT8($1); };
stream_ref: REFERENCE { REF(stream_kind,$1);@+HPUT8($1); };


content_node: 
 start PENALTY  REFERENCE END @/{ REF(penalty_kind,$3); @+HPUT8($3); @+ hput_tags($1,TAG(penalty_kind,0)); }
|start KERN  explicit REFERENCE END @/
      { REF(dimen_kind,$4); @+HPUT8($4);@+ hput_tags($1,TAG(kern_kind,($3)?b100:b000)); }
|start KERN  explicit XDIMEN   REFERENCE END @/
      { REF(xdimen_kind,$5); @+HPUT8($5);@+ hput_tags($1,TAG(kern_kind,($3)?b101:b001)); }
|start GLUE     REFERENCE END @/{ REF(glue_kind,$3); @+HPUT8($3);@+ hput_tags($1,TAG(glue_kind,0)); }
|start LIGATURE REFERENCE END @/{ REF(ligature_kind,$3); @+HPUT8($3);@+ hput_tags($1,TAG(ligature_kind,0)); }
|start HYPHEN   REFERENCE END @/{ REF(hyphen_kind,$3); @+HPUT8($3);@+ hput_tags($1,TAG(hyphen_kind,0)); }
|start MATH     REFERENCE END @/{ REF(math_kind,$3); @+HPUT8($3);@+ hput_tags($1,TAG(math_kind,0)); }
|start RULE     REFERENCE END @/{ REF(rule_kind,$3); @+HPUT8($3);@+ hput_tags($1,TAG(rule_kind,0)); }
|start IMAGE    REFERENCE END @/{ REF(image_kind,$3); @+HPUT8($3);@+ hput_tags($1,TAG(image_kind,0)); }
|start LEADERS  REFERENCE END @/{ REF(leaders_kind,$3); @+HPUT8($3);@+ hput_tags($1,TAG(leaders_kind,0)); }
|start BASELINE REFERENCE END @/{ REF(baseline_kind,$3); @+HPUT8($3);@+ hput_tags($1,TAG(baseline_kind,0)); };

glue_node: start GLUE REFERENCE END @/{ REF(glue_kind,$3); @+HPUT8($3);@+ hput_tags($1,TAG(glue_kind,0)); };

@

\getcode
@<cases to get content@>=
case TAG(penalty_kind,0): HGET_REF(penalty_kind); @+break;
case TAG(kern_kind,b000):  HGET_REF(dimen_kind); @+break;
case TAG(kern_kind,b100):  hwritef(" !"); @+HGET_REF(dimen_kind); @+break;
case TAG(kern_kind,b001):  hwritef(" xdimen");@+ HGET_REF(xdimen_kind); @+break;
case TAG(kern_kind,b101):  hwritef(" ! xdimen");@+ HGET_REF(xdimen_kind); @+break;
case TAG(ligature_kind,0):  HGET_REF(ligature_kind); @+break;
case TAG(hyphen_kind,0):  HGET_REF(hyphen_kind); @+break;
case TAG(glue_kind,0):  HGET_REF(glue_kind); @+break;
case TAG(math_kind,0):  HGET_REF(math_kind); @+break;
case TAG(rule_kind,0): HGET_REF(rule_kind); @+break;
case TAG(image_kind,0):   HGET_REF(image_kind); @+break;
case TAG(leaders_kind,0):  HGET_REF(leaders_kind); @+break;
case TAG(baseline_kind,0):  HGET_REF(baseline_kind); @+break;
@

@<get macros@>=
#define @[HGET_REF(K)@] {uint8_t n; @+ n=HGET8;@+ REF(K,n); @+hwritef(" *%d",n);@+} 
@
\writecode
@<write functions@>=
void hwrite_ref(uint8_t n)
{hwritef(" *%d",n);}
void hwrite_ref_node(uint8_t k, uint8_t n)
{ hwrite_start(); @+hwritef("%s",content_name[k]);@+ hwrite_ref(n); @+hwrite_end();}
@



\section{Defaults}\label{defaults}\index{default value}
Several of the predefined values found in the definition section are used 
as parameters for the routines borrowed from \TeX\ to display the content
of a \HINT/ file. These values must be defined, but it is inconvenient if
the same standard definitions must be placed in each and every \HINT/ file.
Therefore we specify in this chapter reasonable default values. 
As a consequence, even a \HINT/ file without any definitions should
produce sensible results when displayed.

The definitions that have default values are integers, dimensions, 
extended dimensions, glues, baselines, page templates, and page ranges. 
Each of these defaults has its own subsection below.
Actually the defaults for extended dimensions and baselines are not needed by \TeX's
routines, but it is nice to have default values for the extended dimensions that represent
\.{hsize}, \.{vsize}, or a zero baseline skip. 

The array |max_default| contains for each kind value the maximum number of
the default values. The function |hset_max| is used to initialize them.

The programs \.{shrink} and \.{stretch} actually do not use the defaults.
It is, however, possible to suppress definitions if the defined value
is the same as the default.

For maximum flexibility and efficiency, this chapter defines a 
header file {\tt hformat.h} and a \CEE/ program {\tt mkhformat}
that generates the corresponding {\tt hformat.c} file.
The latter contains constant arrays containing the respective default information.

\noindent
Here is the header file:
@(hformat.h@>=
#ifndef _HFORMAT_H_
#define _HFORMAT_H_
@<debug macros@>@;
@<debug constants@>@;
@<hint macros@>@;
@<hint basic types@>@;
@<default names@>@;


extern const char *content_name[32];
extern const char *definition_name[32];
extern unsigned int debugflags;
extern FILE *hlog;
extern int max_fixed[32], max_default[32], max_ref[32];
extern int32_t int_defaults[MAX_INT_DEFAULT+1];
extern dimen_t dimen_defaults[MAX_DIMEN_DEFAULT+1];
extern xdimen_t xdimen_defaults[MAX_XDIMEN_DEFAULT+1];
extern glue_t glue_defaults[MAX_GLUE_DEFAULT+1];
extern baseline_t baseline_defaults[MAX_BASELINE_DEFAULT+1];
#endif
@

\noindent
And here is the |main| program of {\tt mkhformat}:

@(mkhformat.c@>=
#include <stdio.h>
#include "basetypes.h"
#include "hformat.h"


int max_fixed[32], max_default[32];

int32_t int_defaults[MAX_INT_DEFAULT+1]={0};
dimen_t dimen_defaults[MAX_DIMEN_DEFAULT+1]={0};
xdimen_t xdimen_defaults[MAX_XDIMEN_DEFAULT+1]={{0}};
glue_t glue_defaults[MAX_GLUE_DEFAULT+1]={{{0}}};
baseline_t baseline_defaults[MAX_BASELINE_DEFAULT+1]={{{{0}}}};


int main(void)
{ kind_t k;
  int i;
  
  printf("#include \"basetypes.h\"\n"@/
         "#include \"hformat.h\"\n\n"@/
         @[@<variables in {\tt hformat.c}@>@]);
         
  @<define |content_name| and |definition_name|@>@;

  for (k=0; k<32; k++) max_default[k]=-1,max_fixed[k]=0x100;
  @<define |int_defaults|@>@;
  @<define |dimen_defaults|@>@;
  @<define |xdimen_defaults|@>@;
  @<define |baseline_defaults|@>@;
  @<define |page_defaults|@>@;
  @<define |range_defaults|@>@;

  @<define |max_ref|, |max_fixed| and |max_default|@>@;
 
  return 0;
}
@

Above, we have set |max_default| to $-1$, meaning no defaults, and |max_fixed| to |0x100|, meaning no definitions.
The following subsections will overwrite these values for all kinds of definitions that have defaults.
It remains to reset |max_fixed| to $-1$ for all those kinds that have no defaults but allow definitions.
Then we can print out both arrays.
@<define |max_ref|, |max_fixed| and |max_default|@>=
  max_fixed[font_kind]= max_fixed[ligature_kind]= max_fixed[hyphen_kind]
  = max_fixed[math_kind]=max_fixed[rule_kind]= max_fixed[image_kind]
  = max_fixed[leaders_kind]= max_fixed[param_kind]= max_fixed[stream_kind]=-1;@#
  printf("int max_fixed[32]= {");
  for (k=0; k<32; k++)@/
  { printf("%d",max_fixed[k]);@+
    if (k<31) printf(", ");@+
  }
  printf("};\n\n");@#
  printf("int max_default[32]= {");
  for (k=0; k<32; k++)@/
  { printf("%d",max_default[k]);@+
    if (k<31) printf(", ");@+
  }
  printf("};\n\n");
  printf("int max_ref[32]= {");
  for (k=0; k<32; k++)@/
  { printf("%d",max_default[k]);@+
    if (k<31) printf(", ");@+
  }
  printf("};\n\n");
@

\subsection{Integers}
Integers\index{integer} are very simple objects, and it might be tempting not to
use predefined integers at all. But the \TeX\ typesetting engine,
which is used by \HINT/ uses many integer parameters to fine tune
its operations. As we will see, all these integer parameters have a predefined
integer number that refers to an integer definition.

Integers and penalties\index{penalty} share the same kind value. So a penalty node that references
one of the predefined penalties, simply contains the integer number as a reference
number.

The following integer numbers are predefined.
The zero integer is fixed with integer number zero. It is never redefined.
The default values are taken from {\tt plain.tex}.

@<default names@>=
typedef enum {
        zero_int_no=0,
        pretolerance_no=1,
        tolerance_no=2,
        line_penalty_no=3,
        hyphen_penalty_no=4,
        ex_hyphen_penalty_no=5,
        club_penalty_no=6,
        widow_penalty_no=7,
        display_widow_penalty_no=8,
        broken_penalty_no=9,
        pre_display_penalty_no=10,
        post_display_penalty_no=11,
        inter_line_penalty_no=12,
        double_hyphen_demerits_no=13,
        final_hyphen_demerits_no=14,
        adj_demerits_no=15,
        looseness_no=16,
        time_no=17,
        day_no=18,
        month_no=19,
        year_no=20,
        hang_after_no=21,
} int_no_t;
#define MAX_INT_DEFAULT hang_after_no
@

@<define |int_defaults|@>=
max_default[int_kind]=MAX_INT_DEFAULT;
max_fixed[int_kind]=zero_int_no;@#

int_defaults[zero_int_no]=0;
int_defaults[pretolerance_no]=100;
int_defaults[tolerance_no]=200;
int_defaults[line_penalty_no]=10;
int_defaults[hyphen_penalty_no]=50;
int_defaults[ex_hyphen_penalty_no]=50;
int_defaults[club_penalty_no]=150;
int_defaults[widow_penalty_no]=150;
int_defaults[display_widow_penalty_no]=50;
int_defaults[broken_penalty_no]=100;
int_defaults[pre_display_penalty_no]=10000;
int_defaults[post_display_penalty_no]=0;
int_defaults[inter_line_penalty_no]=0;
int_defaults[double_hyphen_demerits_no]=10000;
int_defaults[final_hyphen_demerits_no]=5000;
int_defaults[adj_demerits_no]=10000;
int_defaults[looseness_no]=0;
int_defaults[time_no]=720;
int_defaults[day_no]=4;
int_defaults[month_no]=7;
int_defaults[year_no]=1776;
int_defaults[hang_after_no]=1;@#

printf("int32_t int_defaults[MAX_INT_DEFAULT+1]={");
for (i=0; i<= max_default[int_kind];i++)
{ printf("%d",int_defaults[i]);
  if (i<max_default[int_kind]) printf(", ");
}
printf("};\n\n");
@

\subsection{Dimensions}

Notice that there are default values for the two dimensions \.{hsize} and \.{vsize}.
These are the ``design sizes'' for the hint file. While it might not be possible
to display the \HINT/ file using these values of \.{hsize} and \.{vsize},
these are the authors recommendation for the best ``viewing experience''.

\noindent
@<default names@>=
typedef enum {
zero_dimen_no=0,
hsize_dimen_no=1,
vsize_dimen_no=2,
line_skip_limit_no=3,
max_depth_no=4,
hang_indent_no=5,
emergency_stretch_no=6,
quad_no=7,
math_quad_no=8
} dimen_no_t;
#define MAX_DIMEN_DEFAULT math_quad_no
@

@<define |dimen_defaults|@>=
max_default[dimen_kind]=MAX_DIMEN_DEFAULT;
max_fixed[dimen_kind]=zero_dimen_no;@#
dimen_defaults[zero_dimen_no]=0;
dimen_defaults[hsize_dimen_no]=6.5*72*ONE;
dimen_defaults[vsize_dimen_no]=8.9*72*ONE;
dimen_defaults[line_skip_limit_no]=0;
dimen_defaults[max_depth_no]=4*ONE;
dimen_defaults[hang_indent_no]=0;
dimen_defaults[emergency_stretch_no]=0;
dimen_defaults[quad_no]=10*ONE;
dimen_defaults[math_quad_no]=10*ONE;@#

printf("dimen_t dimen_defaults[MAX_DIMEN_DEFAULT+1]={");
for (i=0; i<= max_default[dimen_kind];i++)
{ printf("0x%x",dimen_defaults[i]);
  if (i<max_default[dimen_kind]) printf(", ");
}
printf("};\n\n");
@

\subsection{Extended Dimensions}
Extended dimensions\index{extended dimension} can be used in a variety of nodes for example
kern\index{kern} and box\index{box} nodes.
We define three fixed extended dimensions: zero, hsize, and vsize.
In contrast to the \.{hsize} and \.{vsize} dimensions defined in the previous
section, the extended dimensions defined here are linear functions that always evaluate
to the current horizontal and vertical size in the viewer.

@<default names@>=
typedef enum {
zero_xdimen_no=0,
hsize_xdimen_no=1,
vsize_xdimen_no=2
} xdimen_no_t;
#define MAX_XDIMEN_DEFAULT vsize_xdimen_no
@

@<define |xdimen_defaults|@>=
max_default[xdimen_kind]=MAX_XDIMEN_DEFAULT;
max_fixed[xdimen_kind]=vsize_xdimen_no;@#

printf("xdimen_t xdimen_defaults[MAX_XDIMEN_DEFAULT+1]={"@/
"{0x0, 0.0, 0.0}, {0x0, 1.0, 0.0}, {0x0, 0.0, 1.0}"@/
"};\n\n");
@

 
\subsection{Glue}

There are predefined glue\index{glue} numbers that correspond to the skip parameters of \TeX.
The default values are taken from {\tt plain.tex}.

@<default names@>=
typedef enum {
zero_skip_no=0,
fil_skip_no=1,
fill_skip_no=2,
line_skip_no=3,
baseline_skip_no=4,
above_display_skip_no=5,
below_display_skip_no=6,
above_display_short_skip_no=7,
below_display_short_skip_no=8,
left_skip_no=9,
right_skip_no=10,
top_skip_no=11,
split_top_skip_no=12,
tab_skip_no=13,
par_fill_skip_no=14
} glue_no_t;
#define MAX_GLUE_DEFAULT par_fill_skip_no
@

@<define |dimen_defaults|@>=
max_default[glue_kind]=MAX_GLUE_DEFAULT;
max_fixed[glue_kind]=fill_skip_no;

glue_defaults[fil_skip_no].p.f=1.0;
glue_defaults[fil_skip_no].p.o=fil_o;

glue_defaults[fill_skip_no].p.f=1.0;
glue_defaults[fill_skip_no].p.o=fill_o;@#

glue_defaults[line_skip_no].w.w=1*ONE;
glue_defaults[baseline_skip_no].w.w=12*ONE;

glue_defaults[above_display_skip_no].w.w=12*ONE;
glue_defaults[above_display_skip_no].p.f=3.0;
glue_defaults[above_display_skip_no].p.o=normal_o;
glue_defaults[above_display_skip_no].m.f=9.0;
glue_defaults[above_display_skip_no].m.o=normal_o;

glue_defaults[below_display_skip_no].w.w=12*ONE;
glue_defaults[below_display_skip_no].p.f=3.0;
glue_defaults[below_display_skip_no].p.o=normal_o;
glue_defaults[below_display_skip_no].m.f=9.0;
glue_defaults[below_display_skip_no].m.o=normal_o;

glue_defaults[above_display_short_skip_no].p.f=3.0;
glue_defaults[above_display_short_skip_no].p.o=normal_o;

glue_defaults[below_display_short_skip_no].w.w=7*ONE;
glue_defaults[below_display_short_skip_no].p.f=3.0;
glue_defaults[below_display_short_skip_no].p.o=normal_o;
glue_defaults[below_display_short_skip_no].m.f=4.0;
glue_defaults[below_display_short_skip_no].m.o=normal_o;

glue_defaults[top_skip_no].w.w=10*ONE;
glue_defaults[split_top_skip_no].w.w=10*ONE;

glue_defaults[par_fill_skip_no].p.f=1.0;
glue_defaults[par_fill_skip_no].p.o=fil_o;

#define @[PRINT_GLUE(G)@] \
        @[printf("{{0x%x, %f, %f},{%f, %d},{%f, %d}}",\
        G.w.w, G.w.h, G.w.v, G.p.f, G.p.o, G.m.f,G.m.o)@]@#

printf("glue_t glue_defaults[MAX_GLUE_DEFAULT+1]={\n");
for (i=0; i<= max_default[glue_kind];i++)@/
{ PRINT_GLUE(glue_defaults[i]); @+
  if (i<max_default[int_kind]) printf(",\n");
}
printf("};\n\n");
@

We fix the glue definition with number zero to be the ``zero glue'': a
glue with width zero and zero stretchability and shrinkability. Here
is the reason: In the short format, the info bits of a glue node
indicate which components of a glue are nonzero.  Therefore the zero
glue should have an info value of zero---which on the other hand is
reserved for a reference to a glue definition. Hence, the best way to
represent a zero glue is as a predefined glue.


\subsection{Baseline Skips}

The zero baseline\index{baseline skip} which inserts no baseline skip is predefined.

@<default names@>=
typedef enum {
zero_baseline_no=0
} baseline_no_t;
#define MAX_BASELINE_DEFAULT zero_baseline_no
@
@<define |baseline_defaults|@>=
max_default[baseline_kind]=MAX_BASELINE_DEFAULT;
max_fixed[baseline_kind]=zero_baseline_no;@#
{ baseline_t z={{{0}}};
  printf("baseline_t baseline_defaults[MAX_BASELINE_DEFAULT+1]={{");
  PRINT_GLUE(z.bs); @+printf(", "); @+PRINT_GLUE(z.ls); printf(", 0x%x}};\n\n",z.lsl);
}
@


\subsection{Page Templates}

The zero page template\index{template} is predefined, as well as stream 0 for the main content.
@<default names@>=
typedef enum {
zero_page_no=0
} page_no_t;
#define MAX_PAGE_DEFAULT zero_page_no
@

@<define |page_defaults|@>=
max_default[page_kind]=MAX_PAGE_DEFAULT;
max_fixed[page_kind]=zero_page_no;@#
max_default[stream_kind]=0;
max_fixed[stream_kind]=0;
@

\subsection{Page Ranges}

The page\index{page range} range for the zero page template is
the entire content section. It is predefined.

@<default names@>=
typedef enum {
zero_range_no=0
} range_no_t;
#define MAX_RANGE_DEFAULT zero_range_no
@

@<define |range_defaults|@>=
max_default[range_kind]=MAX_RANGE_DEFAULT;
max_fixed[range_kind]=zero_range_no;@#
@


\section{Content Section}
The content section\index{content section} is just a list of nodes. Within the \.{shrink} program,
reading a node in long format will trigger writing the node in short format.
Similarly within the \.{stretch} program, reading a node
in short form will cause writing it in long format. As a consequence,
the main task of writing the content section in long format is accomplished
by calling |get_content| and writing it in the short format
is accomplished by parsing the |content_list|.

%\readcode
\codesection{\redsymbol}{Reading the Long Format}\redindex{1}{6}{Content Section}
\label{content}%
@s CONTENT symbol
@<symbols@>=
%token CONTENT "content"
@

@<scanning rules@>=
::@=content@>       :< return CONTENT; >:
@


@<parsing rules@>=
content_section: START CONTENT @/
                 { hput_content_start(); } content_list END {hput_content_end();  hput_range_defs();};
@

%\writecode
\codesection{\wrtsymbol}{Writing the Long Format}\wrtindex{1}{6}{Content Section}

@<write functions@>=
void hwrite_content_section(void)
{ section_no=2;
  hwritef("<content");
  hsort_ranges();
  hget_content_section();
  hwritef("\n>\n");
}
@

%\getcode
\codesection{\getsymbol}{Reading the Short Format}\getindex{1}{6}{Content Section}
@<get functions@>=
void hget_content_section()
{ DBG(DBGDIR,"Content\n");
  hget_section(2);
  hwrite_range();
  while(hpos<hend)
    hget_content_node();
}
@

%\putcode
\codesection{\putsymbol}{Writing the Short Format}\putindex{1}{6}{Content Section}
@<put functions@>=
void hput_content_start(void)
{ DBG(DBGDIR,"Content Section\n");
  section_no=2;
  hpos=hstart=dir[2].buffer;
  hend=hstart+dir[2].bsize;

}
void hput_content_end(void)
{
  dir[2].size=hpos-hstart; /* Updating the directory entry */
  DBG(DBGDIR,"End Content Section, size=0x%x\n", dir[2].size);
}
@


\section{Processing the Command Line}
The following code explains the command line\index{command line} 
parameters and options\index{option}\index{debugging}.
It tells us what to expect in the rest of this section.
@<explain usage@>=
  fprintf(stderr,
  "Usage: %s [options] filename%s\n",prog_name, in_ext);@/
  fprintf(stderr,
  "Options:\n"@/
  "\t -o file\t specify an output file name\n"@/
  "\t -g     \t assume global names for auxiliar files\n"@/
  "\t -l     \t redirect stderr to a log file\n"@/
  "\t -u     \t enable writing utf8 character codes\n"@/
  "\t -x     \t enable writing hexadecimal character codes\n"@/
  "\t -c     \t enable compression of section 1 and 2\n");@/
#ifdef DEBUG
fprintf(stderr,"\t -d XXX \t hexadecimal value. OR together these values:\n");@/
fprintf(stderr,"\t\t\t XX=%03X   basic debugging\n", DBGBASIC);@/
fprintf(stderr,"\t\t\t XX=%03X   tag debugging\n", DBGTAGS);@/
fprintf(stderr,"\t\t\t XX=%03X   node debugging\n",DBGNODE);@/
fprintf(stderr,"\t\t\t XX=%03X   definition debugging\n", DBGDEF);@/
fprintf(stderr,"\t\t\t XX=%03X   directory debugging\n", DBGDIR);@/
fprintf(stderr,"\t\t\t XX=%03X   range debugging\n",DBGRANGE);@/
fprintf(stderr,"\t\t\t XX=%03X   float debugging\n", DBGFLOAT);@/
fprintf(stderr,"\t\t\t XX=%03X   compression debugging\n", DBGCOMPRESS);@/
fprintf(stderr,"\t\t\t XX=%03X   buffer debugging\n", DBGBUFFER);@/
fprintf(stderr,"\t\t\t XX=%03X   flex debugging\n", DBGFLEX);@/
fprintf(stderr,"\t\t\t XX=%03X   bison debugging\n", DBGBISON);@/
fprintf(stderr,"\t\t\t XX=%03X   TeX debugging\n", DBGTEX);@/
fprintf(stderr,"\t\t\t XX=%03X   Page debugging\n", DBGPAGE);@/
fprintf(stderr,"\t\t\t XX=%03X   Font debugging\n", DBGFONT);@/
fprintf(stderr,"\t\t\t XX=%03X   Render debugging\n", DBGRENDER);@/
#endif
@
We define constants for different debug flags.
@<debug constants@>=
#define DBGNONE     0x0 
#define DBGBASIC    0x1 
#define DBGTAGS     0x2
#define DBGNODE     0x4
#define DBGDEF      0x8
#define DBGDIR      0x10
#define DBGRANGE    0x20
#define DBGFLOAT    0x40
#define DBGCOMPRESS 0x80
#define DBGBUFFER   0X100
#define DBGFLEX     0x200
#define DBGBISON    0x400
#define DBGTEX      0x800
#define DBGPAGE     0x1000
#define DBGFONT     0x2000
#define DBGRENDER   0x4000
@

Next we define variables.
Some of these variables go into {\tt hformat.c} because
it enables us to reuse them in other programs.
Some are common variables that are
needed in all three programs defined here.
And some variables are just local variables in the |main| program.

The variable |in_name| is not local to |main| because it is
used in the function |hget_map| (see page\pageref{map}).
The variable |stem_name| contains the name of the input file
not including the extension. The space allocated for it
is large enough to append an extension with up to five characters.
It can be used with the extension {\tt .log} for the log file,
with {\tt .HINT} or {\tt .hnt} for the output file,
and with {\tt .abs} or {\tt .rel} when writing or reading the auxiliar sections.

The {\tt stretch} program will overwrite the |stem_name|
using the name of the output file if it is set with the {\tt -o}
option.

@<variables in {\tt hformat.c}@>=
"unsigned int debugflags=DBGNONE;\n"
@

@<common variables@>=
bool option_utf8=false;
bool option_hex=false;
bool option_force=false;
bool option_global=false;
bool option_compress=false;

char *in_name;
char *stem_name;
int stem_length=0;
@

@<local variables in |main|@>=
char *prog_name;
char *in_ext;
char *out_ext;

char *file_name=NULL;
int file_name_length=0;
bool option_log=false;
@ 

Processing the command line looks for options and then sets the
input file name\index{file name}.

@<process the command line@>=
  debugflags=DBGBASIC;
  prog_name=argv[0];
  if (argc < 2) goto explain_usage;
  argv++; /* skip the program name */
  while (*argv!=NULL)
  { if ((*argv)[0]=='-')
    { char option=(*argv)[1];
      switch(option)
      { default: goto explain_usage;
        case 'o': argv++;
          file_name_length=(int)strlen(*argv);
          ALLOCATE(file_name,file_name_length+6,char); /* extra space for extension */
          strcpy(file_name,*argv);@+  break; 
        case 'l': option_log=true; @+break;
        case 'u': option_utf8=true;@+break;
        case 'x': option_hex=true;@+break;
        case 'f': option_force=true; @+break;
        case 'g': option_global=true; @+break;
        case 'c': option_compress=true; @+break;
        case 'd': @/
          argv++; if (*argv==NULL) goto explain_usage;
          debugflags=strtol(*argv,NULL,16);
          break;
      }
    }
    else /* the input file name */
    { int path_length=(int)strlen(*argv);
      int ext_length=(int)strlen(in_ext);
      ALLOCATE(in_name,path_length+ext_length+1,char);
      strcpy(in_name,*argv);
      if (path_length<ext_length 
          || strncmp(in_name+path_length-ext_length,in_ext,ext_length)!=0)
      { strcat(in_name,in_ext);
        path_length+=ext_length;
      }
      stem_length=path_length-ext_length;
      ALLOCATE(stem_name,stem_length+6,char);
      strncpy(stem_name,in_name,stem_length);
      stem_name[stem_length]=0;
      if (*(argv+1)!=NULL) goto explain_usage;
    }
    argv++;
  }
@

After the command line has been processed, three file streams need to be opened:
The input file |hin|\index{input file} and the output file |hout|\index{output file}.
Further we need a log file |hlog|\index{log file} if debugging is enabled.
For technical reasons, the scanner\index{scanning} generated by \.{flex} needs
an input file |yyin|\index{input file} which is set to |hin|
and an output file |yyout| (which is not used).

@<common variables@>=
FILE *hin=NULL, *hout=NULL;
@
@<variables in {\tt hformat.c}@>=
"FILE *hlog=NULL;\n"
@

The log file is opened first because
this is the place where error messages\index{error message} 
should go while the other files are opened.
It inherits its name from the input file name.

@<open the log file@> =
#ifdef DEBUG
  if (option_log)
  { 
    strcat(stem_name,".log");
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

Once we have established logging, we can try to open the other files.
@<open the input file@>=
  hin=fopen(in_name,"rb");
  if (hin==NULL) QUIT("Unable to open input file %s",in_name);
@

@<open the output file@>=
  if (file_name!=NULL)
  { int ext_length=(int)strlen(out_ext);
    if (file_name_length<=ext_length 
          || strncmp(file_name+file_name_length-ext_length,out_ext,ext_length)!=0)
    { strcat(file_name,out_ext); file_name_length+=ext_length; }
  }
  else
  { file_name_length=stem_length+(int)strlen(out_ext);
    ALLOCATE(file_name,file_name_length+1,char);
    strcpy(file_name,stem_name);@+
    strcpy(file_name+stem_length,out_ext);
  }
  @<make sure the path in |file_name| exists@>@;
  hout=fopen(file_name,"wb");
  if (hout==NULL) QUIT("Unable to open output file %s",file_name);
@

The {\tt stretch} program will replace the |stem_name| using the stem of the
output file.
@<determine the |stem_name| from the output |file_name|@>=
stem_length=file_name_length-(int)strlen(out_ext);
ALLOCATE(stem_name,stem_length+6,char);
strncpy(stem_name,file_name,stem_length);
stem_name[stem_length]=0;
@

At the very end, we will close the files again.
@<close the input file@>=
if (in_name!=NULL) free(in_name);
if (hin!=NULL) fclose(hin);
@
@<close the output file@>=
if (file_name!=NULL) free(file_name);
if (hout!=NULL) fclose(hout);
@
@<close the log file@>=
if (hlog!=NULL) fclose(hlog);
if (stem_name!=NULL) free(stem_name);
@



\section{Error Handling and Debugging}\label{error_section}
There is no good program without good error handling\index{error message}\index{debugging}. 
To print messages\index{message} or indicate errors, I define the following macros:
\index{MESSAGE+\.{MESSAGE}}\index{QUIT+\.{QUIT}}

@(error.h@>=
#ifndef _ERROR_H
#define _ERROR_H
#include <stdlib.h>
#include <stdio.h>
extern FILE *hlog;
extern uint8_t *hpos, *hstart;
#define @[LOG(...)@] @[(fprintf(hlog,__VA_ARGS__),fflush(hlog))@]
#define @[MESSAGE(...)@] @[(fprintf(hlog,__VA_ARGS__),fflush(hlog))@]
#define @[QUIT(...)@]   (MESSAGE("ERROR: " __VA_ARGS__),fprintf(hlog,"\n"),exit(1))

#endif
@


The amount of debugging\index{debugging} depends on the debugging flags.
For portability, we first define the output specifier for expressions of type |size_t|.
\index{DBG+\.{DBG}}\index{SIZE F+\.{SIZE\_F}}\index{DBGTAG+\.{DBGTAG}}
\index{RNG+\.{RNG}}\index{TAGERR+\.{TAGERR}}
@<debug macros@>=
#ifdef WIN32
#define SIZE_F "0x%x"
#else
#define SIZE_F "0x%zx"
#endif
#ifdef DEBUG
#define @[DBG(FLAGS,...)@] ((debugflags & (FLAGS))?LOG(__VA_ARGS__):0)
#else
#define @[DBG(FLAGS,...)@] 0
#endif
#define @[DBGTAG(A,P)@] @[DBG(DBGTAGS,@["tag [%s,%d] at " SIZE_F "\n"@],@|NAME(A),INFO(A),(P)-hstart)@]

#define @[RNG(S,N,A,Z)@] @/\
  if ((int)(N)<(int)(A)||(int)(N)>(int)(Z)) QUIT(S@, " %d out of range [%d - %d]",N,A,Z)

#define @[TAGERR(A)@] @[QUIT(@["Unknown tag [%s,%d] at " SIZE_F "\n"@],NAME(A),INFO(A),hpos-hstart)@]
@

The \.{bison} generated parser will need a function |yyerror| for
error reporting. We can define it now:

@<parsing functions@>=
extern int yylineno;
int yyerror(const char *msg)
{ QUIT(" in line %d %s",yylineno,msg);
  return 0;
}
@

To enable the generation of debugging code \.{bison} needs also the following:
@<enable bison debugging@>=
#ifdef DEBUG
#define  YYDEBUG 1
extern int yydebug;
#else
#define YYDEBUG 0
#endif
@


\appendix

\section{Reading Short Format Files Backwards}
This section is not really part of the file format definition, but it illustrates
an important property of the content section in short format: it can be read in both
directions. This is important because we want to be able
to start at an arbitrary point in the content and from there move pagewise backward.

The program {\tt skip}\index{skip+{\tt skip}} described in this section does just that. As wee see in section~\secref{skip}
its |main| program is almost the same as the |main| program of the program {\tt stretch}.
The only difference is the removal of an output file and the replacement of the call to 
|hwrite_content_section| by |hskip_content_section|.

@<skip functions@>=
static void hskip_content_section(void)
{ DBG(DBGBASIC,"Skipping Content Section\n");
  hget_section(2);
  hpos=hend;
  while(hpos>hstart)
    hteg_content_node();
}
@

The function |hteg_content_node| used above is the reverse version of the function |hget_content_node|.
Many such ``reverse functions'' will follow now and we will consistently use the same
naming scheme: replacing ``{\it get\/}`` by ``{\it teg\/}'' or ``{\tt GET}'' by ``{\tt TEG}''.
There is of course no need for a long format file in reverse order, and hence, the
{\tt skip} program differs in another aspect from {\tt stretch}: it does not produce
any output and it does not do much input checking. It will just extract enough information
from a content node to skip a node and ``advance'' or better ``retreat'' to the previous node.

@<skip functions@>=
static void hteg_content_node(void)
{ @<skip the end byte |z|@>@;
  hteg_content(z);
  @<skip and check the start byte |a|@>@;
}

static void hteg_content(uint8_t z)
{@+ switch (z)@/
  { 
    @<cases to skip content@>@;@t\1@>@/
    default:
      TAGERR(z);
      break;@t\2@>@/
  }
}
@

The code to skip the end\index{end byte} byte |z| and to check the start\index{start byte} byte |a| is used repeatedly.

@<skip the end byte |z|@>=
  uint8_t a,z; /* the start and the end byte*/
  uint32_t node_pos=hpos-hstart;
  if (hpos<=hstart) return;
  HTEGTAG(z);
@

@<skip and check the start byte |a|@>=
  HTEGTAG(a);
  if (a!=z) QUIT(@["Tag mismatch [%s,%d]!=[%s,%d] at " SIZE_F " to 0x%x\n"@],@|NAME(a),INFO(a),NAME(z),INFO(z),@|
    hpos-hstart,node_pos-1);
@

We replace the ``{\tt GET}'' macros by the following ``{\tt TEG}'' macros:

@<skip macros@>=
#define @[HTEG8(X)@] (hpos-=1,(X)=hpos[0])
#define @[HTEG16(X)@] (hpos-=2,(X)=(hpos[0]<<8)+hpos[1])
#define @[HTEG24(X)@] (hpos-=3,(X)=(hpos[0]<<16)+(hpos[1]<<8)+hpos[2])
#define @[HTEG32(X)@] (hpos-=4,(X)=(hpos[0]<<24)+(hpos[1]<<16)+(hpos[2]<<8)+hpos[3])
#define @[HTEGTAG(X)@] @[HTEG8(X),DBGTAG(X,hpos)@]
@

Now we review step by step the different kinds of nodes.
\subsection{Floating Point Numbers}\index{floating point number}
\noindent
@<skip functions@>=
static float32_t hteg_float32(void)
{  union {@+float32_t d; @+ uint32_t bits; @+} u;
   HTEG32(u.bits);
   return u.d;
}
@


\subsection{Extended Dimensions}\index{extended dimension}
\noindent
@<skip macros@>=
#define @[HTEG_XDIMEN(I,X)@] \
  if((I)&b001) HTEG32((X).v); \
  if((I)&b010) HTEG32((X).h);\
  if((I)&b100) HTEG32((X).w);
@

@<skip functions@>=
static void hteg_xdimen_node(xdimen_t *x)
{ @<skip the end byte |z|@>@;
  switch(z)
  { 
#if 0
/*  currently the info value 0 is not supported */
case TAG(xdimen_kind,b000): /* see section~\secref{reference} */
    {uint8_t n;@+ HTEG8(n);} @+ break;
#endif
    case TAG(xdimen_kind,b001): HTEG_XDIMEN(b001,*x);@+break;
    case TAG(xdimen_kind,b010): HTEG_XDIMEN(b010,*x);@+break;
    case TAG(xdimen_kind,b011): HTEG_XDIMEN(b011,*x);@+break;
    case TAG(xdimen_kind,b100): HTEG_XDIMEN(b100,*x);@+break;
    case TAG(xdimen_kind,b101): HTEG_XDIMEN(b101,*x);@+break;
    case TAG(xdimen_kind,b110): HTEG_XDIMEN(b110,*x);@+break;
    case TAG(xdimen_kind,b111): HTEG_XDIMEN(b111,*x);@+break;
    default:
    QUIT("Extent expected at 0x%x got %s",node_pos,NAME(z)); @+ break;
  }
@<skip and check the start byte |a|@>@;
}
@


\subsection{Stretch and Shrink}\index{stretchability}\index{shrinkability}
\noindent
@<skip macros@>=
#define @[HTEG_STRETCH(S)@] { stch_t st; @+ HTEG32(st.u);@+ S.o=st.u&3;@+  st.u&=~3;@+ S.f=st.f; @+}
@

\subsection{Glyphs}\index{glyph}
\noindent
@<skip macros@>=
#define HTEG_GLYPH(I,G) \
  HTEG8((G).f); \
  if (I==1) HTEG8((G).c);\
  else if (I==2) HTEG16((G).c);\
  else if (I==3) HTEG24((G).c);\
  else if (I==4) HTEG32((G).c);
@

@<cases to skip content@>=
case TAG(glyph_kind,1): @+{@+glyph_t g;@+ HTEG_GLYPH(1,g);@+}@+break;
case TAG(glyph_kind,2): @+{@+glyph_t g;@+ HTEG_GLYPH(2,g);@+}@+break;
case TAG(glyph_kind,3): @+{@+glyph_t g;@+ HTEG_GLYPH(3,g);@+}@+break;
case TAG(glyph_kind,4): @+{@+glyph_t g;@+ HTEG_GLYPH(4,g);@+}@+break;
@


\subsection{Penalties}\index{penalty}
\noindent
@<skip macros@>=
#define @[HTEG_PENALTY(I,P)@] \
if (I==1) {int8_t n; @+HTEG8(n);  @+P=n;@+ } \
else {int16_t n;@+ HTEG16(n); @+ P=n; @+}\
@

@<cases to skip content@>=
case TAG(penalty_kind,1):  @+{int32_t p;@+ HTEG_PENALTY(1,p);@+} @+break;
case TAG(penalty_kind,2):  @+{int32_t p;@+ HTEG_PENALTY(2,p);@+} @+break;
@


\subsection{Kerns}\index{kern}
\noindent
@<skip macros@>=
#define @[HTEG_KERN(I,X)@] @[if (((I)&b011)==2) HTEG32(X.w); else if (((I)&b011)==3)  hteg_xdimen_node(&(X))@]
@

@<cases to skip content@>=
case TAG(kern_kind,b010): @+  {@+xdimen_t x; @+HTEG_KERN(b010,x);@+ } @+break;
case TAG(kern_kind,b011): @+  {@+xdimen_t x; @+HTEG_KERN(b011,x);@+ } @+break;
case TAG(kern_kind,b110): @+  {@+xdimen_t x; @+HTEG_KERN(b110,x);@+ } @+break;
case TAG(kern_kind,b111): @+  {@+xdimen_t x; @+HTEG_KERN(b111,x);@+ } @+break;
@

\subsection{Mathematics}\index{mathematics}
\noindent
@<skip macros@>=
#define @[HTEG_MATH(I,M)@]  \
if ((I)&b100) M.on=true; @+else  M.on=false;\
if ((I)&b001) HTEG32(M.w); @+else M.w=0; 
@

@<cases to skip content@>=
case TAG(math_kind,b100):@+  { math_t m; @+ HTEG_MATH(b100,m);@+}@+break;
case TAG(math_kind,b010):@+  { math_t m; @+ HTEG_MATH(b010,m);@+}@+break;
case TAG(math_kind,b101):@+  { math_t m; @+ HTEG_MATH(b101,m);@+}@+break;
case TAG(math_kind,b011):@+  { math_t m; @+ HTEG_MATH(b011,m);@+}@+break;
@

\subsection{Rules}\index{rule}
\noindent
@<skip macros@>=
#define @[HTEG_RULE(I,R)@]@/\
if ((I)&b001) HTEG32((R).w); @+else (R).w=RUNNING_DIMEN;\
if ((I)&b010) HTEG32((R).d); @+else (R).d=RUNNING_DIMEN;\
if ((I)&b100) HTEG32((R).h); @+else (R).h=RUNNING_DIMEN;
@

@<cases to skip content@>=
case TAG(rule_kind,b011): @+ {rule_t r;@+ HTEG_RULE(b011,r);@+ }@+ break;
case TAG(rule_kind,b101): @+ {rule_t r;@+ HTEG_RULE(b101,r);@+ }@+ break;
case TAG(rule_kind,b001): @+ {rule_t r;@+ HTEG_RULE(b001,r);@+ }@+ break;
case TAG(rule_kind,b110): @+ {rule_t r;@+ HTEG_RULE(b110,r);@+ }@+ break;
case TAG(rule_kind,b111): @+ {rule_t r;@+ HTEG_RULE(b111,r);@+ }@+ break;
@

@<skip functions@>=
static void hteg_rule_node(void)
{ @<skip the end byte |z|@>@;
  if (KIND(z)==rule_kind)   { @+rule_t r; @+HTEG_RULE(INFO(z),r); @+}
  else
    QUIT("Rule expected at 0x%x got %s",node_pos,NAME(z));
 @<skip and check the start byte |a|@>@;
}
@
\subsection{Glue}\index{glue}
\noindent
@<skip macros@>=
#define @[HTEG_GLUE(I,G)@] @/\
  if((I)&b001) HTEG_STRETCH((G).m) @+else  (G).m.f=0.0, (G).m.o=0; \
  if((I)&b010) HTEG_STRETCH((G).p) @+else (G).p.f=0.0, (G).p.o=0;\
  if(I==b111) hteg_xdimen_node(&((G).w)); \
  else @/{@+(G).w.h=0.0;@+(G).w.v=0.0;\
  if((I)&b100) HTEG32((G).w.w);@+ else (G).w.w=0;@+ }
@

@<cases to skip content@>=
case TAG(glue_kind,b001): @+{ glue_t g;@+ HTEG_GLUE(b001,g);@+}@+break;
case TAG(glue_kind,b010): @+{ glue_t g;@+ HTEG_GLUE(b010,g);@+}@+break;
case TAG(glue_kind,b011): @+{ glue_t g;@+ HTEG_GLUE(b011,g);@+}@+break;
case TAG(glue_kind,b100): @+{ glue_t g;@+ HTEG_GLUE(b100,g);@+}@+break;
case TAG(glue_kind,b101): @+{ glue_t g;@+ HTEG_GLUE(b101,g);@+}@+break;
case TAG(glue_kind,b110): @+{ glue_t g;@+ HTEG_GLUE(b110,g);@+}@+break;
case TAG(glue_kind,b111): @+{ glue_t g;@+ HTEG_GLUE(b111,g);@+}@+break;
@

@<skip functions@>=
static void hteg_glue_node(void)
{ @<skip the end byte |z|@>@;
  if (INFO(z)==b000) HTEG_REF(glue_kind);
  else
  { @+glue_t g; @+HTEG_GLUE(INFO(z),g);@+}
   @<skip and check the start byte |a|@>@;
}
@

\subsection{Boxes}\index{box}
\noindent
@<skip macros@>=
#define @[HTEG_BOX(I,B)@] \
hteg_list(&(B.l));\
if ((I)&b100) @/{ HTEG8(B.s); @+ B.r=hteg_float32();@+  B.o=B.s&0xF; @+B.s=B.s>>4;@+ }\
else {  B.r=0.0;@+ B.o=B.s=0;@+ }\
if ((I)&b010) HTEG32(B.a); @+else B.a=0;\ 
HTEG32(B.w);\
if ((I)&b001) HTEG32(B.d); @+ else B.d=0;\ 
HTEG32(B.h);\
@

@<cases to skip content@>=
case TAG(hbox_kind,b000): @+{box_t b; @+HTEG_BOX(b000,b);@+} @+ break;
case TAG(hbox_kind,b001): @+{box_t b; @+HTEG_BOX(b001,b);@+} @+ break;
case TAG(hbox_kind,b010): @+{box_t b; @+HTEG_BOX(b010,b);@+} @+ break;
case TAG(hbox_kind,b011): @+{box_t b; @+HTEG_BOX(b011,b);@+} @+ break;
case TAG(hbox_kind,b100): @+{box_t b; @+HTEG_BOX(b100,b);@+} @+ break;
case TAG(hbox_kind,b101): @+{box_t b; @+HTEG_BOX(b101,b);@+} @+ break;
case TAG(hbox_kind,b110): @+{box_t b; @+HTEG_BOX(b110,b);@+} @+ break;
case TAG(hbox_kind,b111): @+{box_t b; @+HTEG_BOX(b111,b);@+} @+ break;
case TAG(vbox_kind,b000): @+{box_t b; @+HTEG_BOX(b000,b);@+} @+ break;
case TAG(vbox_kind,b001): @+{box_t b; @+HTEG_BOX(b001,b);@+} @+ break;
case TAG(vbox_kind,b010): @+{box_t b; @+HTEG_BOX(b010,b);@+} @+ break;
case TAG(vbox_kind,b011): @+{box_t b; @+HTEG_BOX(b011,b);@+} @+ break;
case TAG(vbox_kind,b100): @+{box_t b; @+HTEG_BOX(b100,b);@+} @+ break;
case TAG(vbox_kind,b101): @+{box_t b; @+HTEG_BOX(b101,b);@+} @+ break;
case TAG(vbox_kind,b110): @+{box_t b; @+HTEG_BOX(b110,b);@+} @+ break;
case TAG(vbox_kind,b111): @+{box_t b; @+HTEG_BOX(b111,b);@+} @+ break;
@

@<skip functions@>=
static void hteg_hbox_node(void)
{ box_t b;
  @<skip the end byte |z|@>@;
  if (KIND(z)!=hbox_kind) QUIT("Hbox expected at 0x%x got %s",node_pos,NAME(z));
   HTEG_BOX(INFO(z),b);@/
 @<skip and check the start byte |a|@>@;
}

static void hteg_vbox_node(void)
{ box_t b;
  @<skip the end byte |z|@>@;
  if (KIND(z)!=vbox_kind) QUIT("Vbox expected at 0x%x got %s",node_pos,NAME(z));
   HTEG_BOX(INFO(z),b);@/
 @<skip and check the start byte |a|@>@;
}
@


\subsection{Extended Boxes}\index{extended box}
\noindent
@<skip macros@>=
#define @[HTEG_SET(I)@] @/\
{ list_t l; @+hteg_list(&l); @+} \
{ stretch_t m; @+HTEG_STRETCH(m);@+}\
{ stretch_t p; @+HTEG_STRETCH(p);@+}\
if ((I)&b010)  { dimen_t a; @+HTEG32(a);@+} \
 { dimen_t w; @+HTEG32(w);@+} \
 { dimen_t d; @+if ((I)&b001) HTEG32(d); @+ else d=0;@+}\ 
 { dimen_t h; @+HTEG32(h);@+} \
 if ((I)&b100) {xdimen_t x; hteg_xdimen_node(&x); @+} \
 else HTEG_REF(xdimen_kind);
@#

#define @[HTEG_PACK(I)@] @/\
 { list_t l; @+hteg_list(&l); @+} \
 if ((I)&b001)  { dimen_t d; @+HTEG32(d); @+ }\
 if ((I)&b100) {xdimen_t x; hteg_xdimen_node(&x);@+} @+ else HTEG_REF(xdimen_kind);
@

@<cases to skip content@>=
case TAG(hset_kind,b000): HTEG_SET(b000); @+ break;
case TAG(hset_kind,b001): HTEG_SET(b001); @+ break;
case TAG(hset_kind,b010): HTEG_SET(b010); @+ break;
case TAG(hset_kind,b011): HTEG_SET(b011); @+ break;
case TAG(hset_kind,b100): HTEG_SET(b100); @+ break;
case TAG(hset_kind,b101): HTEG_SET(b101); @+ break;
case TAG(hset_kind,b110): HTEG_SET(b110); @+ break;
case TAG(hset_kind,b111): HTEG_SET(b111); @+ break;@#

case TAG(vset_kind,b000): HTEG_SET(b000); @+ break;
case TAG(vset_kind,b001): HTEG_SET(b001); @+ break;
case TAG(vset_kind,b010): HTEG_SET(b010); @+ break;
case TAG(vset_kind,b011): HTEG_SET(b011); @+ break;
case TAG(vset_kind,b100): HTEG_SET(b100); @+ break;
case TAG(vset_kind,b101): HTEG_SET(b101); @+ break;
case TAG(vset_kind,b110): HTEG_SET(b110); @+ break;
case TAG(vset_kind,b111): HTEG_SET(b111); @+ break;@#

case TAG(hpack_kind,b000): HTEG_PACK(b000); @+ break;
case TAG(hpack_kind,b010): HTEG_PACK(b010); @+ break;
case TAG(hpack_kind,b100): HTEG_PACK(b100); @+ break;
case TAG(hpack_kind,b110): HTEG_PACK(b110); @+ break;@#

case TAG(vpack_kind,b000): HTEG_PACK(b000); @+ break;
case TAG(vpack_kind,b010): HTEG_PACK(b010); @+ break;
case TAG(vpack_kind,b100): HTEG_PACK(b100); @+ break;
case TAG(vpack_kind,b110): HTEG_PACK(b110); @+ break;
case TAG(vpack_kind,b001): HTEG_PACK(b001); @+ break;
case TAG(vpack_kind,b011): HTEG_PACK(b011); @+ break;
case TAG(vpack_kind,b101): HTEG_PACK(b101); @+ break;
case TAG(vpack_kind,b111): HTEG_PACK(b111); @+ break;
@


\subsection{Leaders}\index{leaders}
\noindent
@<skip macros@>=
#define @[HTEG_LEADERS(I)@]@/ \
if (KIND(hpos[-1])==rule_kind) hteg_rule_node(); \
else if (KIND(hpos[-1])==hbox_kind)  hteg_hbox_node();\
else  hteg_vbox_node();\
if (KIND(hpos[-1])==glue_kind) hteg_glue_node();
@

@<cases to skip content@>=
case TAG(leaders_kind,1):        @+ HTEG_LEADERS(1); @+break;
case TAG(leaders_kind,2):        @+ HTEG_LEADERS(2); @+break;
case TAG(leaders_kind,3):        @+ HTEG_LEADERS(3); @+break;
@

\subsection{Baseline Skips}\index{baseline skip}
\noindent
@<skip macros@>=
#define @[HTEG_BASELINE(I,B)@] \
  if((I)&b001) HTEG32((B).lsl); @+else B.lsl=0; \
  if((I)&b010) hteg_glue_node(); \
  else {B.ls.p.o=B.ls.m.o=B.ls.w.w=0; @+B.ls.w.h=B.ls.w.v=B.ls.p.f=B.ls.m.f=0.0;@+}\
  if((I)&b100) hteg_glue_node(); \
  else {B.bs.p.o=B.bs.m.o=B.bs.w.w=0; @+B.bs.w.h=B.bs.w.v=B.bs.p.f=B.bs.m.f=0.0;@+}
@

@<cases to skip content@>=
case TAG(baseline_kind,b001): @+{ baseline_t b;@+ HTEG_BASELINE(b001,b);@+ }@+break;
case TAG(baseline_kind,b010): @+{ baseline_t b;@+ HTEG_BASELINE(b010,b);@+ }@+break;
case TAG(baseline_kind,b011): @+{ baseline_t b;@+ HTEG_BASELINE(b011,b);@+ }@+break;
case TAG(baseline_kind,b100): @+{ baseline_t b;@+ HTEG_BASELINE(b100,b);@+ }@+break;
case TAG(baseline_kind,b101): @+{ baseline_t b;@+ HTEG_BASELINE(b101,b);@+ }@+break;
case TAG(baseline_kind,b110): @+{ baseline_t b;@+ HTEG_BASELINE(b110,b);@+ }@+break;
case TAG(baseline_kind,b111): @+{ baseline_t b;@+ HTEG_BASELINE(b111,b);@+ }@+break;
@
\subsection{Ligatures}\index{ligature}
\noindent
@<skip macros@>=
#define @[HTEG_LIG(I,L)@] @/\
if ((I)==7) @+ HTEG8((L).l.s); @+else (L).l.s=(I);\
 hpos-=(L).l.s; @+ (L).l.p=hpos-hstart; \
if ((I)==7) { uint8_t n;@+ HTEG8(n);\
  if(n!=(L).l.s)   QUIT("Sizes in ligature don't match %d!=%d",(L).l.s,n);}\
HTEG8((L).f);
@

@<cases to skip content@>=
case TAG(ligature_kind,1):@+ {lig_t l; @+HTEG_LIG(1,l);@+} @+break;
case TAG(ligature_kind,2):@+ {lig_t l; @+HTEG_LIG(2,l);@+} @+break;
case TAG(ligature_kind,3):@+ {lig_t l; @+HTEG_LIG(3,l);@+} @+break;
case TAG(ligature_kind,4):@+ {lig_t l; @+HTEG_LIG(4,l);@+} @+break;
case TAG(ligature_kind,5):@+ {lig_t l; @+HTEG_LIG(5,l);@+} @+break;
case TAG(ligature_kind,6):@+ {lig_t l; @+HTEG_LIG(6,l);@+} @+break;
case TAG(ligature_kind,7):@+ {lig_t l; @+HTEG_LIG(7,l);@+} @+break;
@


\subsection{Hyphenation}\index{hyphen}
\noindent
@<skip macros@>=
#define @[HTEG_HYPHEN(I,H)@]\
if ((I)&b001) HTEG8((H).r); @+else (H).r=0;\
if ((I)&b010) hteg_list(&((H).q)); else { (H).q.p=hpos-hstart; @+(H).q.s=0; @+(H).q.k=list_kind; @+}\
if ((I)&b100) hteg_list(&((H).p)); else { (H).p.p=hpos-hstart; @+(H).p.s=0; @+(H).p.k=list_kind; @+}
@
@<cases to skip content@>=
case TAG(hyphen_kind,b001): {hyphen_t h; @+HTEG_HYPHEN(b001,h); @+} @+break;
case TAG(hyphen_kind,b010): {hyphen_t h; @+HTEG_HYPHEN(b010,h); @+} @+break;
case TAG(hyphen_kind,b011): {hyphen_t h; @+HTEG_HYPHEN(b011,h); @+} @+break;
case TAG(hyphen_kind,b100): {hyphen_t h; @+HTEG_HYPHEN(b100,h); @+} @+break;
case TAG(hyphen_kind,b101): {hyphen_t h; @+HTEG_HYPHEN(b101,h); @+} @+break;
case TAG(hyphen_kind,b110): {hyphen_t h; @+HTEG_HYPHEN(b110,h); @+} @+break;
case TAG(hyphen_kind,b111): {hyphen_t h; @+HTEG_HYPHEN(b111,h); @+} @+break;
@


\subsection{Paragraphs}\index{paragraph}
\noindent
@<skip macros@>=
#define @[HTEG_PAR(I)@] @/\
 { list_t l; @+hteg_list(&l); @+} \
 if ((I)&b010) { list_t l; @+hteg_param_list_node(&l); @+}  else HTEG_REF(param_kind);\
 if ((I)&b100)  {xdimen_t x; @+ hteg_xdimen_node(&x); @+}  else HTEG_REF(xdimen_kind);
@

@<cases to skip content@>=
case TAG(par_kind,b000): @+HTEG_PAR(b000);@+break;
case TAG(par_kind,b010): @+HTEG_PAR(b010);@+break;
case TAG(par_kind,b100): @+HTEG_PAR(b100);@+break;
case TAG(par_kind,b110): @+HTEG_PAR(b110);@+break;
@


\subsection{Displays}\index{displayed formula}
\noindent
@<skip macros@>=
#define @[HTEG_DISPLAY(I)@] \
if ((I)&b001) hteg_hbox_node();\
{ list_t l; @+hteg_list(&l); @+} \
if ((I)&b010) hteg_hbox_node(); \
if ((I)&b100) { list_t l; @+hteg_param_list_node(&l); @+} @+ else HTEG_REF(param_kind);
@

@<cases to skip content@>=
case TAG(display_kind,b000): HTEG_DISPLAY(b000); @+ break;
case TAG(display_kind,b001): HTEG_DISPLAY(b001); @+ break;
case TAG(display_kind,b010): HTEG_DISPLAY(b010); @+ break;
case TAG(display_kind,b100): HTEG_DISPLAY(b100); @+ break;
case TAG(display_kind,b101): HTEG_DISPLAY(b101); @+ break;
case TAG(display_kind,b110): HTEG_DISPLAY(b110); @+ break;
@

\subsection{Images}\index{image}
\noindent
@<skip macros@>=
#define @[HTEG_IMAGE(I,X)@] @/\
if (I&b001) {HTEG_STRETCH((X).m);HTEG_STRETCH((X).p);@+}\
else { (X).p.f=(X).m.f=0.0; (X).p.o=(X).m.o=normal_o;@+}\
if (I&b010) {HTEG32((X).h);HTEG32((X).w);@+} \
else (X).w=(X).h=0;\
HTEG16((X).n);
@

@<cases to skip content@>=
case TAG(image_kind,b100): @+ { image_t x;@+HTEG_IMAGE(b100,x);@+}@+break;
case TAG(image_kind,b101): @+ { image_t x;@+HTEG_IMAGE(b101,x);@+}@+break;
case TAG(image_kind,b110): @+ { image_t x;@+HTEG_IMAGE(b110,x);@+}@+break;
case TAG(image_kind,b111): @+ { image_t x;@+HTEG_IMAGE(b111,x);@+}@+break;
@

\subsection{Plain Lists, Texts, and Parameter Lists}\index{list}
\noindent
@<skip functions@>=
static void hteg_size_boundary(info_t info)
{ uint32_t n;
  if (info<2) return;
  HTEG8(n);
  if (n-1!=0x100-info) QUIT(@["List size boundary byte 0x%x does not match info value %d at " SIZE_F@],
                            n, info,hpos-hstart);
}

static uint32_t hteg_list_size(info_t info)
{ uint32_t n;  
  if (info==1) return 0;
  else if (info==2) HTEG8(n);
  else if (info==3) HTEG16(n);
  else if (info==4) HTEG24(n);
  else if (info==5) HTEG32(n);
  else QUIT("List info %d must be 1, 2, 3, 4, or 5",info);
  return n;
} 

static void hteg_list(list_t *l)
{ @<skip the end byte |z|@>@,
  @+if (KIND(z)!=list_kind && KIND(z)!=text_kind  &&@| KIND(z)!=param_kind) @/
  {@+ hpos++; l->p=hpos-hstart;@+ l->s=0;@+ l->k=list_kind;@+ } 
   else
  { uint32_t s;
    l->k=KIND(z);
    l->s=hteg_list_size(INFO(z));
    hteg_size_boundary(INFO(z));
    hpos=hpos-l->s;
    l->p=hpos-hstart;
    hteg_size_boundary(INFO(z));
    s=hteg_list_size(INFO(z));
    if (s!=l->s) QUIT(@["List sizes at " SIZE_F " and 0x%x do not match 0x%x != 0x%x"@],
                        hpos-hstart,node_pos-1,s,l->s);
    @<skip and check the start byte |a|@>@;
  }
}

static void hteg_param_list_node(list_t *l)
{ @+if (KIND(*(hpos-1))!=param_kind) return;
  hteg_list(l);
}


@

\subsection{Adjustments}\index{adjustment}
\noindent
@<cases to skip content@>=
case TAG(adjust_kind,b001): @+ { list_t l; @+hteg_list(&l);@+ } @+ break;
@

\subsection{Tables}\index{table}
\noindent
@<skip macros@>=
#define @[HTEG_TABLE(I)@] \
{@+ list_t l; @+ hteg_list(&l);@+}\
{@+ list_t l; @+ hteg_list(&l);@+}\
if ((I)&b100) {xdimen_t x;@+ hteg_xdimen_node(&x);@+} else HTEG_REF(xdimen_kind)@;
@

@<cases to skip content@>=
case TAG(table_kind,b000): @+ HTEG_TABLE(b000); @+ break;
case TAG(table_kind,b001): @+ HTEG_TABLE(b001); @+ break;
case TAG(table_kind,b010): @+ HTEG_TABLE(b010); @+ break;
case TAG(table_kind,b011): @+ HTEG_TABLE(b011); @+ break;
case TAG(table_kind,b100): @+ HTEG_TABLE(b100); @+ break;
case TAG(table_kind,b101): @+ HTEG_TABLE(b101); @+ break;
case TAG(table_kind,b110): @+ HTEG_TABLE(b110); @+ break;
case TAG(table_kind,b111): @+ HTEG_TABLE(b111); @+ break;@#

case TAG(item_kind,b000):  @+{@+ list_t l; @+hteg_list(&l);@+ } @+ break;
case TAG(item_kind,b001):  hteg_content_node(); @+ break;
case TAG(item_kind,b010):  hteg_content_node(); @+ break;
case TAG(item_kind,b011):  hteg_content_node(); @+ break;
case TAG(item_kind,b100):  hteg_content_node(); @+ break;
case TAG(item_kind,b101):  hteg_content_node(); @+ break;
case TAG(item_kind,b110):  hteg_content_node(); @+ break;
case TAG(item_kind,b111):  hteg_content_node(); @+{uint8_t n;@+ HTEG8(n);@+}@+ break;
@



\subsection{Stream Nodes}\index{stream}
@<skip macros@>=
#define @[HTEG_STREAM(I)@] @/\
{ list_t l; @+hteg_list(&l); @+} \
if ((I)&b001) { scaled_t d; @+ hteg_glue_node();@+HTEG32(d);@+}\
if ((I)&b010) { int16_t p;@+ HTEG16(p);@+ }\
if ((I)&b100) { scaled_t h; @+HTEG32(h);@+}\
HTEG_REF(stream_kind);\
@

@<cases to skip content@>=
case TAG(stream_kind,b000): HTEG_STREAM(b000); @+ break;
case TAG(stream_kind,b001): HTEG_STREAM(b001); @+ break;
case TAG(stream_kind,b010): HTEG_STREAM(b010); @+ break;
case TAG(stream_kind,b011): HTEG_STREAM(b011); @+ break;
case TAG(stream_kind,b100): HTEG_STREAM(b100); @+ break;
case TAG(stream_kind,b101): HTEG_STREAM(b101); @+ break;
case TAG(stream_kind,b110): HTEG_STREAM(b110); @+ break;
case TAG(stream_kind,b111): HTEG_STREAM(b111); @+ break;
@



\subsection{References}\index{reference}
\noindent
@<skip macros@>=
#define @[HTEG_REF(K)@] do@+{uint8_t n; @+ HTEG8(n);@+} @+ while (false)
@

@<cases to skip content@>=
case TAG(penalty_kind,0): HTEG_REF(penalty_kind); @+break;
case TAG(kern_kind,b000):  HTEG_REF(dimen_kind); @+break;
case TAG(kern_kind,b100):  HTEG_REF(dimen_kind); @+break;
case TAG(kern_kind,b001):  HTEG_REF(xdimen_kind); @+break;
case TAG(kern_kind,b101):  HTEG_REF(xdimen_kind); @+break;
case TAG(ligature_kind,0):  HTEG_REF(ligature_kind); @+break;
case TAG(hyphen_kind,0):  HTEG_REF(hyphen_kind); @+break;
case TAG(glue_kind,0):  HTEG_REF(glue_kind); @+break;
case TAG(math_kind,0):  HTEG_REF(math_kind); @+break;
case TAG(rule_kind,0): HTEG_REF(rule_kind); @+break;
case TAG(image_kind,0):   HTEG_REF(image_kind); @+break;
case TAG(leaders_kind,0):  HTEG_REF(leaders_kind); @+break;
case TAG(baseline_kind,0):  HTEG_REF(baseline_kind); @+break;
@


\section{Code and Header Files}\index{code file}\index{header file}

\subsection{{\tt basetypes.h}}
To define basic types in a portable way, we create an include file.
The macro |_MSC_VER| (Microsoft Visual C Version) is defined only if
using the respective compiler.\index{false+\\{false}}\index{true+\\{true}}\index{bool+\&{bool}}
@(basetypes.h@>=
#ifndef __BASETYPES_H__
#define __BASETYPES_H__
#include <stdlib.h>
#include <stdio.h>
#ifndef _STDLIB_H
#define _STDLIB_H
#endif
#ifdef  _MSC_VER
#include <windows.h>
#define uint8_t UINT8
#define uint16_t UINT16
#define uint32_t UINT32
#define uint64_t UINT64
#define int8_t INT8
#define int16_t INT16
#define int32_t INT32
#define bool BOOL
#define true (0==0)
#define false (!true)
#define __SIZEOF_FLOAT__ 4
#define __SIZEOF_DOUBLE__ 8
typedef float float32_t;
typedef double float64_t;
#define INT32_MAX              (2147483647)
#define PRIx64 "I64x"
#pragma  @[warning( disable : @[4244@]@t @> @[4996@]@t @> @[4127@])@]
#else 
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
typedef float float32_t;
typedef double float64_t;
#ifdef WIN32
#include <io.h>
#endif
#endif
#if __SIZEOF_FLOAT__!=4
#error  @=float32 type must have size 4@>
#endif
#if __SIZEOF_DOUBLE__!=8
#error  @=float64 type must have size 8@>
#endif
#endif
@



\subsection{{\tt hformat.h}}
The \.{hformat.c} file contains variables and functions that are needed
in other compilation units. Together with the required type and macro
definitions, the necessary information is contained in the \.{hformat.h}
header file.


@<write function declarations@>=
#define @[hwritec(c)@] @[putc(c,hout)@]
#define @[hwritef(...)@] @[fprintf(hout,__VA_ARGS__)@]
extern void hwrite_range(void);
extern void hwrite_charcode(uint32_t c);
extern void hwrite_ref_node(uint8_t k, uint8_t n);
extern void hwrite_ref(uint8_t n);
extern void hsort_ranges(void); 
@


\subsection{{\tt hget.h}}\index{hget.h+{\tt hget.h}}
The \.{hget.h} file contains function prototypes for all the functions
that read the short format.

@<get function declarations@>=
extern void hget_content_node(void);
extern int txt_length;
extern int hget_txt(void);
extern uint32_t hget_utf8(void);
extern void hget_def_node(def_t *df);
extern void hget_content_section(void);
extern void hget_content(uint8_t a);
extern void hget_xdimen_node(xdimen_t *x);
extern float32_t hget_float32(void);
extern void hget_list(list_t *l);
extern void hget_glue_node(void);
extern void hget_rule_node(void);
extern void hget_hbox_node(void);
extern void hget_vbox_node(void);
extern void hget_param_list_node(list_t *l);
extern uint32_t hget_list_size(info_t info);
extern void hget_size_boundary(info_t info);
extern void hget_max_definitions(void);
extern void hget_font_def(info_t i, uint8_t f);
@

@(hget.h@>=

@<get file macros@>@;
@<directory entry type@>@;
extern entry_t *dir;
extern uint16_t section_no,  max_section_no;
extern uint8_t *hpos, *hstart, *hend;

extern void hget_map(void);
extern void hget_unmap(void);

extern void new_directory(uint32_t entries);
extern void hset_entry(entry_t *e, uint16_t i, uint32_t size, uint32_t xsize, @|char *file_name);

extern void hget_banner(void);
extern void hget_section(uint16_t n);
extern void hget_entry(entry_t *e);
extern void hget_directory(void);
extern void hclear_dir(void);
extern bool hcheck_banner(char *magic);

extern void hget_max_definitions(void);
@



\subsection{{\tt hget.c}}\index{hget.c+{\tt hget.c}}
@(hget.c@>=
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


uint8_t *hpos=NULL, *hstart=NULL, *hend=NULL;


@<map functions@>@;
@<function to check the banner@>@;
@<directory functions@>@;
@<get file macros@>@;
@<get file functions@>@;


@

\subsection{{\tt hput.h}}\index{hput.h+{\tt hput.h}}
The \.{hput.h} file contains function prototypes for all the functions
that write the short format.


@(hput.h@>=
@<put macros@>@;
@<hint macros@>@;
@<hint types@>@;
@<directory entry type@>@;
extern entry_t *dir;
extern uint16_t section_no,  max_section_no;
extern uint8_t *hpos, *hstart, *hend;
extern int next_range;
extern range_pos_t *range_pos;
extern int *page_on; 

extern FILE *hout;
extern void new_directory(uint32_t entries);
extern void new_output_buffers(void);

/* declarations for the parser */
extern void hput_definitions_start(void);
extern void hput_definitions_end(void);
extern void hput_content_start(void);
extern void hput_content_end(void);

extern void hput_tags(uint32_t pos, uint8_t tag);
extern uint8_t hput_glyph(glyph_t *g);
extern uint8_t hput_xdimen(xdimen_t *x);
extern uint8_t hput_int(int32_t p);
extern uint8_t hput_math(math_t *m);
extern uint8_t hput_rule(rule_t *r);
extern uint8_t hput_glue(glue_t *g);
extern uint8_t hput_list(uint32_t size_pos, list_t *y);
extern uint8_t hsize_bytes(uint32_t n);
extern void hput_txt_cc(uint32_t c);
extern void hput_txt_font(uint8_t f);
extern void hput_txt_global(ref_t *d);
extern void hput_txt_local(uint8_t n);
extern info_t hput_box_dimen(dimen_t h, dimen_t d, dimen_t w);
extern info_t hput_box_shift(dimen_t a);
extern info_t hput_box_glue_set(int8_t s, float32_t r, order_t o);
extern void hput_stretch(stretch_t *s);
extern uint8_t hput_kern(kern_t *k);
extern void hput_utf8(uint32_t c);
extern uint8_t hput_ligature(lig_t *l);
extern uint8_t hput_hyphen(hyphen_t *h);
extern uint8_t hput_item(uint32_t n);
extern uint8_t hput_image(image_t *x);
extern void hput_string(char *str);
extern void hput_range(uint8_t pg, bool on);
extern void hput_max_definitions(void);
extern uint8_t hput_dimen(dimen_t d);
extern uint8_t hput_font_head(uint8_t f,  char *n, dimen_t s, uint16_t m, uint16_t y);
extern void hput_range_defs(void);
/* declarations for HiTeX */
extern void hput_xdimen_node(xdimen_t *x);
extern void hput_directory(void);
extern void hput_hint(char * str);
extern void hput_list_size(uint32_t n, int i);
@


\subsection{{\tt hput.c}}\label{writeshort}\index{hput.c+{\tt hput.c}}
\noindent
@(hput.c@>=
#include "basetypes.h"
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <zlib.h>
#include "error.h"
#include "hformat.h"
#include "hput.h"

uint8_t *hpos=NULL, *hstart=NULL, *hend=NULL;
FILE *hout;
int version=1, subversion=0;
bool option_compress=false;
bool option_global=false;
int next_range;
range_pos_t *range_pos;
int *page_on; 
char *stem_name=NULL;
int stem_length=0;


@<directory functions@>@;
@<function to write the banner@>@;
@<put functions@>@;
@

\subsection{{\tt shrink.l}}\index{shrink.l+{\tt shrink.l}}\index{scanning}
The definitions for lex are collected in the file {\tt shrink.l}

@(shrink.l@>=
%{
#include "basetypes.h"
#include <unistd.h>
#include "error.h"
#include "hformat.h"
@<hint types@>@;
@<enable bison debugging@>@;
#include "shrink.tab.h"

@<scanning macros@>@;
@<scanning functions@>@;
int yywrap (void ){ return 1;}
#ifdef _MSC_VER
#pragma  warning( disable : 4267)
#endif
%}

%option yylineno batch stack
%option debug 
%option  nounistd nounput noinput noyy_top_state

@<scanning definitions@>@/



%%

@<scanning rules@>@/
::@=[a-z]+@>     :< QUIT("Unexpected keyword '%s' in line %d",@|yytext,yylineno); >:
::@=.@>    :< QUIT("Unexpected character '%c' (0x%02X) in line %d",@|yytext[0]>' '?yytext[0]:' ',yytext[0],yylineno); >:

%%
@



\subsection{{\tt shrink.y}}\index{shrink.y+{\tt shrink.y}}\index{parsing}

The grammar rules for bison are collected in the file  {\tt shrink.y}.
% for the option %token-table use the command line parameter -k


@(shrink.y@>=
%{
#include "basetypes.h"
#include <string.h>
#include <math.h>
#include "error.h"
#include "hformat.h"
#include "hput.h"
char **hfont_name;

extern void hset_entry(entry_t *e, uint16_t i, uint32_t size, uint32_t xsize, @|char *file_name);

@<enable bison debugging@>@;
extern int yylex(void);

@<parsing functions@>@;

%}


@t{\label{union}\index{union}\index{parsing}}@>


%union {uint32_t u; @+ int32_t i; @+ char *s; @+ float64_t f; @+ glyph_t c; 
        @+  dimen_t d; @+ stretch_t st; @+ xdimen_t xd; @+ kern_t kt;
        @+ rule_t r; @+ glue_t g; @+ math_t m; @+ @+ image_t x; 
        @+ list_t l; @+ box_t h;  @+ hyphen_t hy; @+ lig_t lg;
        @+ ref_t rf; @+ info_t info; @+ order_t o;@+bool b;@+ def_t df; @+ 
   }

@t{}@>

%error_verbose
%start hint

@t@>
@<symbols@>@/
@t@>
%%

@<parsing rules@>@;
%%
@

\subsection{{\tt shrink.c}}\index{shrink.c+{\tt shrink.c}}

\.{shrink} is a \CEE/ program translating a \HINT/ file in long format into a \HINT/ file in short format.

@(shrink.c@>=
#include "basetypes.h"
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <zlib.h>
#include "error.h"
#include "hformat.h"
@<hint types@>@;
#include "shrink.tab.h"

extern void yyset_debug(int lex_debug);
extern int yylineno;
extern FILE *yyin, *yyout;
extern int yyparse(void);

@<put macros@>@;

@<common variables@>@;

@<function to check the banner@>@;
@<directory entry type@>@;
@<directory functions@>@;
@<function to write the banner@>@;
@<put functions@>@;

int main(int argc, char *argv[])
{ @<local variables in |main|@>@;
   in_ext=".HINT";
   out_ext=".hnt";
  @<process the command line@>@;

  if (debugflags&DBGFLEX) yyset_debug(1); else  yyset_debug(0);  
#if YYDEBUG
  if (debugflags&DBGBISON) yydebug=1; 
  else yydebug=0;
#endif
  @<open the log file@>@;
  @<open the input file@>@;
  @<open the output file@>@;

  yyin=hin;
  yyout=hlog;
  @<read the banner@>@;
  hcheck_banner("HINT");
  yylineno++;
  DBG(DBGBISON|DBGFLEX,"Parsing Input\n");
  yyparse();

  hput_directory();

  hput_hint("shrink");
  
  @<close the output file@>@;
  @<close the input file@>@;
  @<close the log file@>@;
  return 0;
explain_usage:
  @<explain usage@>@;
  return 1;
}
@



\subsection{{\tt stretch.c}}\index{stretch.y+{\tt stretch.y}}
\.{stretch} is a \CEE/ program translating a \HINT/ file in short 
format into a \HINT/ file in long format.

@(stretch.c@>=
#include "basetypes.h"
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <zlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "error.h"
#include "hformat.h"
@<hint types@>@;

@<common variables@>@;

@<map functions@>@;
@<function to check the banner@>@;
@<function to write the banner@>@;
@<directory entry type@>@;
@<directory functions@>@;
@<get file macros@>@;
@<get file functions@>@;
@<write function declarations@>@>
@<get function declarations@>@;

@<write functions@>@;

@<get macros@>@;

@<get functions@>@;



int main(int argc, char *argv[])
{ @<local variables in |main|@>@;
   in_ext=".hnt";
   out_ext=".HINT";

  @<process the command line@>@;
  @<open the log file@>@;
  @<open the output file@>@;
  @<determine the |stem_name| from the output |file_name|@>@;
  hget_map();
  hget_banner();
  hcheck_banner("hint");
  hput_banner("HINT","stretch");
  hget_directory();
  hwrite_directory();
  hget_definition_section();
  hwrite_content_section();
  hwrite_aux_files();
  hget_unmap();
  @<close the output file@>@;
  @<close the log file@>@;
  return 0;
explain_usage:
  @<explain usage@>@;
  return 1;}
@

\subsection{{\tt hteg.h}}\index{hteg.h+{\tt hteg.h}}
\noindent
@<skip function declarations@>=
static void hteg_content_node(void);
static void hteg_content(uint8_t z);
static void hteg_xdimen_node(xdimen_t *x);
static void hteg_list(list_t *l);
static void hteg_param_list_node(list_t *l);
static float32_t hteg_float32(void);
static void hteg_rule_node(void);
static void hteg_hbox_node(void);
static void hteg_vbox_node(void);
static void hteg_glue_node(void);
@

\subsection{{\tt skip.c}}\label{skip}\index{skip.c+{\tt skip.c}}
\.{skip} is a \CEE/ program reading the content section of a \HINT/ file in short format 
backwards.

@(skip.c@>=
#include "basetypes.h"
#include <string.h>
#include <zlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "error.h"
#include "hformat.h"
@<hint types@>@;

@<common variables@>@;

@<map functions@>@;
@<function to check the banner@>@;
@<directory entry type@>@;
@<directory functions@>@;
@<get file macros@>@;
@<get file functions@>@;

@<skip macros@>@;
@<skip function declarations@>@;
@<skip functions@>@;

int main(int argc, char *argv[])
{ @<local variables in |main|@>@;
   in_ext=".hnt";
   out_ext=".bak";

  @<process the command line@>@;
  @<open the log file@>@;
  hget_map();
  hget_banner();
  hcheck_banner("hint");
  hget_directory();
  hskip_content_section();
  hget_unmap();
  @<close the log file@>@;
  return 0;
explain_usage:
  @<explain usage@>@;
  return 1;
}
@

\thecodeindex


\plainsection{Cross Reference of Code}
\crosssections



\plainsection{References}

{\baselineskip=11pt
\def\bfblrm{\small\rm}%
\def\bblem{\small\it}%
\bibliography{hint}
\bibliographystyle{plain}
}

\plainsection{Index}
{
\def\_{{\tt \UL}} % underline in a string
\catcode`\_=\active \let_=\_ % underline is a letter
\input format.ind
}

  \write\cont{} % ensure that the contents file isn't empty
%  \write\cont{\catcode `\noexpand\@=12\relax}   % \makeatother
  \closeout\cont% the contents information has been fully gathered
