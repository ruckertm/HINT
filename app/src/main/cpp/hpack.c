/*667:*/
#line 12938 ".\\dummy.w"

#include "htex.h"
#include "hformat.h"
#include "hdefaults.h"
#include "texdef.h"

/*665:*/
#line 12931 ".\\dummy.w"

pointer adjust_tail;

/*:665*/
#line 12944 ".\\dummy.w"


pointer hpack(pointer p,scaled w,small_number m)
{
pointer r;
pointer q;
scaled h,d,x;
scaled s;
pointer g;
glue_ord o;
internal_font_number f;
four_quarters i;
eight_bits hd;
r= get_node(box_node_size);type(r)= hlist_node;
subtype(r)= min_quarterword;shift_amount(r)= 0;
q= r+list_offset;link(q)= p;
h= 0;/*668:*/
#line 12971 ".\\dummy.w"

d= 0;x= 0;
total_stretch[normal]= 0;total_shrink[normal]= 0;
total_stretch[fil]= 0;total_shrink[fil]= 0;
total_stretch[fill]= 0;total_shrink[fill]= 0;
total_stretch[filll]= 0;total_shrink[filll]= 0

/*:668*/
#line 12960 ".\\dummy.w"
;
while(p!=null)/*669:*/
#line 12978 ".\\dummy.w"


{reswitch:while(is_char_node(p))
/*672:*/
#line 13021 ".\\dummy.w"

{f= font(p);i= char_info(f)(character(p));hd= height_depth(i);
x= x+char_width(f)(i);
s= char_height(f)(hd);if(s> h)h= s;
s= char_depth(f)(hd);if(s> d)d= s;
p= link(p);
}

/*:672*/
#line 12982 ".\\dummy.w"
;
if(p!=null)
{switch(type(p)){
case hlist_node:case vlist_node:case rule_node:case unset_node:
/*671:*/
#line 13009 ".\\dummy.w"

{x= x+width(p);
if(type(p)>=rule_node)s= 0;else s= shift_amount(p);
if(height(p)-s> h)h= height(p)-s;
if(depth(p)+s> d)d= depth(p)+s;
}

/*:671*/
#line 12986 ".\\dummy.w"
break;
case ins_node:case mark_node:case adjust_node:if(adjust_tail!=null)
/*673:*/
#line 13036 ".\\dummy.w"

{while(link(q)!=p)q= link(q);
if(type(p)==adjust_node)
{link(adjust_tail)= adjust_ptr(p);
while(link(adjust_tail)!=null)adjust_tail= link(adjust_tail);
p= link(p);free_node(link(q),small_node_size);
}
else{link(adjust_tail)= p;adjust_tail= p;p= link(p);
}
link(q)= p;p= q;
}

/*:673*/
#line 12988 ".\\dummy.w"
break;
case whatsit_node:/*1395:*/
#line 25013 ".\\dummy.w"
do_nothing

/*:1395*/
#line 12989 ".\\dummy.w"
;break;
case glue_node:/*674:*/
#line 13048 ".\\dummy.w"

{g= glue_ptr(p);x= x+width(g);
o= stretch_order(g);total_stretch[o]= total_stretch[o]+stretch(g);
o= shrink_order(g);total_shrink[o]= total_shrink[o]+shrink(g);
if(subtype(p)>=a_leaders)
{g= leader_ptr(p);
if(height(g)> h)h= height(g);
if(depth(g)> d)d= depth(g);
}
}

/*:674*/
#line 12990 ".\\dummy.w"
break;
case kern_node:case math_node:x= x+width(p);break;
case ligature_node:/*670:*/
#line 13000 ".\\dummy.w"

{mem[lig_trick]= mem[lig_char(p)];link(lig_trick)= link(p);
p= lig_trick;goto reswitch;
}

/*:670*/
#line 12992 ".\\dummy.w"

default:do_nothing;
}
p= link(p);
}
}


/*:669*/
#line 12963 ".\\dummy.w"
;
if(adjust_tail!=null)link(adjust_tail)= null;
height(r)= h;depth(r)= d;
/*675:*/
#line 13062 ".\\dummy.w"

if(m==additional)w= x+w;
width(r)= w;x= w-x;
if(x==0)
{glue_sign(r)= normal;glue_order(r)= normal;
set_glue_ratio_zero(glue_set(r));
goto end;
}
else if(x> 0)/*676:*/
#line 13074 ".\\dummy.w"

{/*677:*/
#line 13085 ".\\dummy.w"

if(total_stretch[filll]!=0)o= filll;
else if(total_stretch[fill]!=0)o= fill;
else if(total_stretch[fil]!=0)o= fil;
else o= normal

/*:677*/
#line 13075 ".\\dummy.w"
;
glue_order(r)= o;glue_sign(r)= stretching;
if(total_stretch[o]!=0)glue_set(r)= unfloat(x/(double)total_stretch[o]);

else{glue_sign(r)= normal;
set_glue_ratio_zero(glue_set(r));
}
goto end;
}

/*:676*/
#line 13071 ".\\dummy.w"

else/*682:*/
#line 13130 ".\\dummy.w"

{/*683:*/
#line 13143 ".\\dummy.w"

if(total_shrink[filll]!=0)o= filll;
else if(total_shrink[fill]!=0)o= fill;
else if(total_shrink[fil]!=0)o= fil;
else o= normal

/*:683*/
#line 13131 ".\\dummy.w"
;
glue_order(r)= o;glue_sign(r)= shrinking;
if(total_shrink[o]!=0)glue_set(r)= unfloat((-x)/(double)total_shrink[o]);

else{glue_sign(r)= normal;
set_glue_ratio_zero(glue_set(r));
}
if((total_shrink[o]<-x)&&(o==normal)&&(list_ptr(r)!=null))
set_glue_ratio_one(glue_set(r));
goto end;
}

/*:682*/
#line 13072 ".\\dummy.w"


/*:675*/
#line 12967 ".\\dummy.w"
;
end:return r;
}

/*:667*//*686:*/
#line 13178 ".\\dummy.w"

#define vpack(...) vpackage(__VA_ARGS__, max_dimen)


pointer vpackage(pointer p,scaled h,small_number m,scaled l)
{
pointer r;
scaled w,d,x;
scaled s;
pointer g;
glue_ord o;
r= get_node(box_node_size);type(r)= vlist_node;
subtype(r)= min_quarterword;shift_amount(r)= 0;
list_ptr(r)= p;
w= 0;/*668:*/
#line 12971 ".\\dummy.w"

d= 0;x= 0;
total_stretch[normal]= 0;total_shrink[normal]= 0;
total_stretch[fil]= 0;total_shrink[fil]= 0;
total_stretch[fill]= 0;total_shrink[fill]= 0;
total_stretch[filll]= 0;total_shrink[filll]= 0

/*:668*/
#line 13192 ".\\dummy.w"
;
while(p!=null)/*687:*/
#line 13205 ".\\dummy.w"

{if(is_char_node(p))QUIT("Char node in vlist");

else switch(type(p)){
case hlist_node:case vlist_node:case rule_node:case unset_node:
/*688:*/
#line 13220 ".\\dummy.w"

{x= x+d+height(p);d= depth(p);
if(type(p)>=rule_node)s= 0;else s= shift_amount(p);
if(width(p)+s> w)w= width(p)+s;
}

/*:688*/
#line 13210 ".\\dummy.w"
break;
case whatsit_node:/*1394:*/
#line 25011 ".\\dummy.w"
do_nothing

/*:1394*/
#line 13211 ".\\dummy.w"
;break;
case glue_node:/*689:*/
#line 13226 ".\\dummy.w"

{x= x+d;d= 0;
g= glue_ptr(p);x= x+width(g);
o= stretch_order(g);total_stretch[o]= total_stretch[o]+stretch(g);
o= shrink_order(g);total_shrink[o]= total_shrink[o]+shrink(g);
if(subtype(p)>=a_leaders)
{g= leader_ptr(p);
if(width(g)> w)w= width(g);
}
}

/*:689*/
#line 13212 ".\\dummy.w"
break;
case kern_node:{x= x+d+width(p);d= 0;
}break;
default:do_nothing;
}
p= link(p);
}

/*:687*/
#line 13194 ".\\dummy.w"
;
width(r)= w;
if(d> l)
{x= x+d-l;depth(r)= l;
}
else depth(r)= d;
/*690:*/
#line 13240 ".\\dummy.w"

if(m==additional)h= x+h;
height(r)= h;x= h-x;
if(x==0)
{glue_sign(r)= normal;glue_order(r)= normal;
set_glue_ratio_zero(glue_set(r));
goto end;
}
else if(x> 0)/*691:*/
#line 13252 ".\\dummy.w"

{/*677:*/
#line 13085 ".\\dummy.w"

if(total_stretch[filll]!=0)o= filll;
else if(total_stretch[fill]!=0)o= fill;
else if(total_stretch[fil]!=0)o= fil;
else o= normal

/*:677*/
#line 13253 ".\\dummy.w"
;
glue_order(r)= o;glue_sign(r)= stretching;
if(total_stretch[o]!=0)glue_set(r)= unfloat(x/(double)total_stretch[o]);

else{glue_sign(r)= normal;
set_glue_ratio_zero(glue_set(r));
}
goto end;
}

/*:691*/
#line 13249 ".\\dummy.w"

else/*694:*/
#line 13288 ".\\dummy.w"

{/*683:*/
#line 13143 ".\\dummy.w"

if(total_shrink[filll]!=0)o= filll;
else if(total_shrink[fill]!=0)o= fill;
else if(total_shrink[fil]!=0)o= fil;
else o= normal

/*:683*/
#line 13289 ".\\dummy.w"
;
glue_order(r)= o;glue_sign(r)= shrinking;
if(total_shrink[o]!=0)glue_set(r)= unfloat((-x)/(double)total_shrink[o]);

else{glue_sign(r)= normal;
set_glue_ratio_zero(glue_set(r));
}
if((total_shrink[o]<-x)&&(o==normal)&&(list_ptr(r)!=null))
set_glue_ratio_one(glue_set(r));
goto end;
}

/*:694*/
#line 13250 ".\\dummy.w"


/*:690*/
#line 13201 ".\\dummy.w"
;
end:return r;
}

/*:686*/
