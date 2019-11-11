/*142:*/
#line 2980 ".\\dummy.w"

#include "htex.h"
#include "texdef.h"

extern void free_node(pointer p,halfword s);

pointer new_null_box(void)
{pointer p;
p= get_node(box_node_size);type(p)= hlist_node;
subtype(p)= min_quarterword;
width(p)= 0;depth(p)= 0;height(p)= 0;shift_amount(p)= 0;list_ptr(p)= null;
glue_sign(p)= normal;glue_order(p)= normal;set_glue_ratio_zero(glue_set(p));
return p;
}

/*:142*//*145:*/
#line 3016 ".\\dummy.w"
pointer new_rule(void)
{pointer p;
p= get_node(rule_node_size);type(p)= rule_node;
subtype(p)= 0;
width(p)= null_flag;depth(p)= null_flag;height(p)= null_flag;
return p;
}

/*:145*//*150:*/
#line 3085 ".\\dummy.w"
pointer new_ligature(quarterword f,quarterword c,pointer q)
{pointer p;
p= get_node(small_node_size);type(p)= ligature_node;
font(lig_char(p))= f;character(lig_char(p))= c;lig_ptr(p)= q;
subtype(p)= 0;return p;
}

pointer new_lig_item(quarterword c)
{pointer p;
p= get_node(small_node_size);character(p)= c;lig_ptr(p)= null;
return p;
}

/*:150*//*151:*/
#line 3123 ".\\dummy.w"
pointer new_disc(void)
{pointer p;
p= get_node(small_node_size);type(p)= disc_node;
subtype(p)= 0;pre_break(p)= null;post_break(p)= null;
return p;
}

/*:151*//*153:*/
#line 3157 ".\\dummy.w"
pointer new_math(scaled w,small_number s)
{pointer p;
p= get_node(small_node_size);type(p)= math_node;
subtype(p)= s;width(p)= w;return p;
}

/*:153*//*157:*/
#line 3239 ".\\dummy.w"
pointer new_spec(pointer p)
{pointer q;
q= get_node(glue_spec_size);
mem[q]= mem[p];glue_ref_count(q)= null;
width(q)= width(p);stretch(q)= stretch(p);shrink(q)= shrink(p);
return q;
}

/*:157*//*159:*/
#line 3265 ".\\dummy.w"
pointer new_glue(pointer q)
{pointer p;
p= get_node(small_node_size);type(p)= glue_node;subtype(p)= normal;
leader_ptr(p)= null;glue_ptr(p)= q;incr(glue_ref_count(q));
return p;
}

/*:159*//*162:*/
#line 3303 ".\\dummy.w"
pointer new_kern(scaled w)
{pointer p;
p= get_node(small_node_size);type(p)= kern_node;
subtype(p)= normal;
width(p)= w;
return p;
}

/*:162*//*164:*/
#line 3326 ".\\dummy.w"
pointer new_penalty(int m)
{pointer p;
p= get_node(small_node_size);type(p)= penalty_node;
subtype(p)= 0;
penalty(p)= m;return p;
}

/*:164*//*214:*/
#line 3970 ".\\dummy.w"
void delete_glue_ref(pointer p)
fast_delete_glue_ref(p)

/*:214*//*218:*/
#line 4039 ".\\dummy.w"

pointer copy_node_list(pointer p)

{pointer h;
pointer q;
pointer r;
uint8_t words;
h= get_avail();q= h;
while(p!=null)
{/*219:*/
#line 4055 ".\\dummy.w"

words= 1;
if(is_char_node(p))r= get_avail();
else/*220:*/
#line 4064 ".\\dummy.w"

switch(type(p)){
case hlist_node:case vlist_node:case unset_node:{r= get_node(box_node_size);
mem[r+6]= mem[p+6];mem[r+5]= mem[p+5];
list_ptr(r)= copy_node_list(list_ptr(p));
words= 5;
}break;
case rule_node:{r= get_node(rule_node_size);words= rule_node_size;
}break;
case ins_node:{r= get_node(ins_node_size);mem[r+4]= mem[p+4];
add_glue_ref(split_top_ptr(p));
ins_ptr(r)= copy_node_list(ins_ptr(p));
words= ins_node_size-1;
}break;
case whatsit_node:/*1392:*/
#line 24911 ".\\dummy.w"

switch(subtype(p)){
case open_node:{r= get_node(open_node_size);words= open_node_size;
}break;
case write_node:case special_node:{r= get_node(write_node_size);
add_token_ref(write_tokens(p));words= write_node_size;
}break;
case close_node:case language_node:{r= get_node(small_node_size);
words= small_node_size;
}break;
case par_node:
{r= get_node(par_node_size);
if(par_type(p)==glue_type)add_glue_ref(par_value(p).i);
words= par_node_size;
}break;
case graf_node:
{r= get_node(graf_node_size);
graf_params(r)= copy_node_list(graf_params(p));
graf_list(r)= copy_node_list(graf_list(p));
words= graf_node_size-1;
}break;
case disp_node:
{r= get_node(disp_node_size);
display_left(r)= display_left(p);
display_eqno(r)= copy_node_list(display_eqno(p));
display_formula(r)= copy_node_list(display_formula(p));
display_params(r)= copy_node_list(display_params(p));
words= disp_node_size-2;
}break;
case baseline_node:
{r= get_node(baseline_node_size);
words= baseline_node_size;
}break;
case hpack_node:case vpack_node:
{r= get_node(pack_node_size);
pack_m(r)= pack_m(p);
list_ptr(r)= copy_node_list(list_ptr(p));
pack_extent(r)= pack_extent(p);
pack_limit(r)= pack_limit(p);
words= pack_node_size-3;
}break;
case hset_node:case vset_node:
{r= get_node(set_node_size);
mem[r+8]= mem[p+8];mem[r+7]= mem[p+7];mem[r+6]= mem[p+6];mem[r+5]= mem[p+5];
list_ptr(r)= copy_node_list(list_ptr(p));
words= 5;
}break;
case image_node:
r= get_node(image_node_size);
words= image_node_size;
break;
case align_node:
{r= get_node(align_node_size);
align_preamble(r)= copy_node_list(align_preamble(p));
align_list(r)= copy_node_list(align_list(p));
words= align_node_size-1;
}break;
default:QUIT("Error when copying a whatsit node");

}

/*:1392*/
#line 4079 ".\\dummy.w"
break;
case glue_node:{r= get_node(small_node_size);add_glue_ref(glue_ptr(p));
glue_ptr(r)= glue_ptr(p);leader_ptr(r)= copy_node_list(leader_ptr(p));
}break;
case kern_node:case math_node:case penalty_node:{r= get_node(small_node_size);
words= small_node_size;
}break;
case ligature_node:{r= get_node(small_node_size);
mem[lig_char(r)]= mem[lig_char(p)];
lig_ptr(r)= copy_node_list(lig_ptr(p));
}break;
case disc_node:{r= get_node(small_node_size);
pre_break(r)= copy_node_list(pre_break(p));
post_break(r)= copy_node_list(post_break(p));
}break;
case mark_node:{r= get_node(small_node_size);add_token_ref(mark_ptr(p));
words= small_node_size;
}break;
case adjust_node:{r= get_node(small_node_size);
adjust_ptr(r)= copy_node_list(adjust_ptr(p));
}break;
default:QUIT("Error in copying a node list");

}

/*:220*/
#line 4059 ".\\dummy.w"
;
while(words> 0)
{decr(words);mem[r+words]= mem[p+words];
}

/*:219*/
#line 4048 ".\\dummy.w"
;
link(q)= r;q= r;p= link(p);
}
link(q)= null;q= link(h);free_avail(h);
return q;
}

/*:218*//*597:*/
#line 11347 ".\\dummy.w"

pointer new_character(internal_font_number f,eight_bits c)
{pointer p;
if(font_bc[f]> c||font_ec[f]<c||!char_exists(char_info(f)(c)))
MESSAGE("Warning: Character 0x%0X in font %d does not exist\n",c,f);
p= get_avail();font(p)= f;character(p)= c;
return p;
}

/*:597*/
