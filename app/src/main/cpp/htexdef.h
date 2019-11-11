/*196:*/
#line 2898 ".\\hint.w"

/*37:*/
#line 620 ".\\hint.w"

#define null 0
/*:37*//*74:*/
#line 1149 ".\\hint.w"

#define is_char_node(X) (X >= hi_mem_min)   
#define disc_node 7 
#define glue_node 10 
#define kern_node 11 
#define penalty_node 12 
#define empty_flag 0xFFFF
/*:74*//*103:*/
#line 1492 ".\\hint.w"

#define before 0
#define after 1
/*:103*//*112:*/
#line 1568 ".\\hint.w"

#define null_flag -010000000000 
#define prev_depth aux.sc 
#define ignore_depth -65536000 
/*:112*//*113:*/
#line 1576 ".\\hint.w"

#ifdef DEBUG
#define incr_dyn_used (dyn_used++)
#define decr_dyn_used (dyn_used--)
#else
#define incr_dyn_used
#define decr_dyn_used
#endif
#define width_offset 1
#define depth_offset 2
#define height_offset 3
#define sc i  
#define width(X) mem[X+width_offset].i
#define depth(X) mem[X+depth_offset].i
#define height(X) mem[X+height_offset].i


/*:113*//*118:*/
#line 1642 ".\\hint.w"

#define glue_order(X) subtype(X+list_offset) 
#define glue_sign(X) type(X+list_offset) 
#define glue_spec_size 4
#define normal 0 
#define stretching 1 
#define shrinking 2 
/*:118*//*122:*/
#line 1706 ".\\hint.w"

#define glue_spec_size 4

#define type(X) mem[X].hh.b0
#define subtype(X) mem[X].hh.b1

#define stretch(X) mem[X+2].i
#define shrink(X) mem[X+3].i
#define stretch_order type
#define shrink_order subtype
/*:122*//*136:*/
#line 2055 ".\\hint.w"

#define vlist_node 1

#define link(X) mem[X].hh.rh 

#define shift_amount(X) mem[X+4].i
#define list_offset 5
#define list_ptr(X) link(X+list_offset)
#define glue_offset 6
#define glue_set(X) mem[X+glue_offset].gr
#define glue_order(X) subtype(X+list_offset)
#define glue_sign(X) type(X+list_offset)
/*:136*//*147:*/
#line 2265 ".\\hint.w"

#define exactly 0
#define additional 1
/*:147*//*153:*/
#line 2325 ".\\hint.w"

#define explicit 1
/*:153*//*159:*/
#line 2370 ".\\hint.w"

#define a_leaders 100
#define leader_ptr(X) link(X+1)
/*:159*//*164:*/
#line 2413 ".\\hint.w"

#define zero_glue 0
/*:164*//*176:*/
#line 2549 ".\\hint.w"

#define set_replace_count(X,Y) (mem[X].hh.b1=  (Y) &0x7F)
#define replace_count(X)   (mem[X].hh.b1&0x7F)
#define set_auto_disc(X) (mem[X].hh.b1|=  0x80)
#define is_auto_disc(X)  (mem[X].hh.b1 & 0x80)
#define pre_break llink
#define post_break rlink
#define info(X) mem[X].hh.lh
#define llink(X) info(X+1)
#define rlink(X) link(X+1)
extern pointer new_disc(void);
/*:176*//*183:*/
#line 2731 ".\\hint.w"

#define math_node 9 
#define non_discardable(X) (type(X) < math_node)
/*:183*//*189:*/
#line 2808 ".\\hint.w"

#define adjust_node 5
#define adjust_ptr(X) mem[X+1].i
#define small_node_size 2 
/*:189*//*195:*/
#line 2868 ".\\hint.w"

#define whatsit_node 8 
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
/*:195*//*197:*/
#line 2919 ".\\hint.w"

#define inf_bad 10000
#define odd(X)       ((X)&1)
#define chr(X)       ((unsigned char)(X))
#define ord(X)       ((int)(X))
#define abs(X)       ((X)> -(X)?(X):-(X))
#define round(X)     ((int)((X)>=0.0?floor((X)+0.5):ceil((X)-0.5)))
/*:197*//*205:*/
#line 3049 ".\\hint.w"

#define mode cur_list.mode_field 
#define head cur_list.head_field 
#define tail cur_list.tail_field 
#define prev_graf cur_list.pg_field 
#define aux cur_list.aux_field 
#define cur_bs  cur_list.bs_field.bs
#define cur_ls  cur_list.bs_field.ls
#define cur_lsl cur_list.bs_field.lsl
#define needs_bs cur_list.insert_bs
#define node_pos cur_list.np_field
#define node_pos1 (nest_ptr==0?0:nest[nest_ptr-1].np_field)
#define tail_append(X) {link(tail)= X;tail= link(tail); }
/*:205*//*212:*/
#line 3143 ".\\hint.w"


#define mem_top 30000
#define contrib_head mem_top-1
#define page_head mem_top-2 
#define vmode 1 
#define empty 0 
#define contrib_tail nest[0].tail_field 
#define max_depth      dimen_par(max_depth_code)
/*:212*/
#line 2899 ".\\hint.w"

/*:196*/
