/*575:*/
#line 10953 ".\\dummy.w"

#include "htex.h"
#include "texdef.h"

/*564:*/
#line 10760 ".\\dummy.w"

memory_word font_info[font_mem_size+1];

font_index fmem_ptr= 0;
internal_font_number font_ptr;
four_quarters font_check0[font_max-font_base+1],*const font_check= font_check0-font_base;
scaled font_size0[font_max-font_base+1],*const font_size= font_size0-font_base;
scaled font_dsize0[font_max-font_base+1],*const font_dsize= font_dsize0-font_base;
font_index font_params0[font_max-font_base+1],*const font_params= font_params0-font_base;

char*font_name0[font_max-font_base+1],**const font_name= font_name0-font_base;
eight_bits font_bc0[font_max-font_base+1],*const font_bc= font_bc0-font_base;

eight_bits font_ec0[font_max-font_base+1],*const font_ec= font_ec0-font_base;

pointer font_glue0[font_max-font_base+1],*const font_glue= font_glue0-font_base;

bool font_used0[font_max-font_base+1],*const font_used= font_used0-font_base;

int hyphen_char0[font_max-font_base+1],*const hyphen_char= hyphen_char0-font_base;

int skew_char0[font_max-font_base+1],*const skew_char= skew_char0-font_base;

font_index bchar_label0[font_max-font_base+1],*const bchar_label= bchar_label0-font_base;


uint16_t font_bchar0[font_max-font_base+1],*const font_bchar= font_bchar0-font_base;

uint16_t font_false_bchar0[font_max-font_base+1],*const font_false_bchar= font_false_bchar0-font_base;


/*:564*//*565:*/
#line 10800 ".\\dummy.w"

int char_base0[font_max-font_base+1],*const char_base= char_base0-font_base;

int width_base0[font_max-font_base+1],*const width_base= width_base0-font_base;

int height_base0[font_max-font_base+1],*const height_base= height_base0-font_base;

int depth_base0[font_max-font_base+1],*const depth_base= depth_base0-font_base;

int italic_base0[font_max-font_base+1],*const italic_base= italic_base0-font_base;

int lig_kern_base0[font_max-font_base+1],*const lig_kern_base= lig_kern_base0-font_base;

int kern_base0[font_max-font_base+1],*const kern_base= kern_base0-font_base;

int exten_base0[font_max-font_base+1],*const exten_base= exten_base0-font_base;

int param_base0[font_max-font_base+1],*const param_base= param_base0-font_base;


/*:565*/
#line 10957 ".\\dummy.w"


void read_font_info(int f,char*nom,scaled s)
{
font_index k;
bool file_opened;
halfword lf,lh,bc,ec,nw,nh,nd,ni,nl,nk,ne,np;

eight_bits a,b,c,d;
four_quarters qw;scaled sw;
int bch_label;
uint16_t bchar;
scaled z;
int alpha;uint8_t beta;

/*577:*/
#line 11007 ".\\dummy.w"

/*578:*/
#line 11019 ".\\dummy.w"

file_opened= true

/*:578*/
#line 11008 ".\\dummy.w"
;
/*580:*/
#line 11043 ".\\dummy.w"

{read_sixteen(lf);
fget;read_sixteen(lh);
fget;read_sixteen(bc);
fget;read_sixteen(ec);
if((bc> ec+1)||(ec> 255))abort;
if(bc> 255)
{bc= 1;ec= 0;
}
fget;read_sixteen(nw);
fget;read_sixteen(nh);
fget;read_sixteen(nd);
fget;read_sixteen(ni);
fget;read_sixteen(nl);
fget;read_sixteen(nk);
fget;read_sixteen(ne);
fget;read_sixteen(np);
if(lf!=6+lh+(ec-bc+1)+nw+nh+nd+ni+nl+nk+ne+np)abort;
if((nw==0)||(nh==0)||(nd==0)||(ni==0))abort;
}

/*:580*/
#line 11009 ".\\dummy.w"
;
/*581:*/
#line 11070 ".\\dummy.w"

lf= lf-6-lh;
if(np<7)lf= lf+7-np;
if((font_ptr==font_max)||(fmem_ptr+lf> font_mem_size))
QUIT("Not enough room left for font %s\n",nom);
char_base[f]= fmem_ptr-bc;
width_base[f]= char_base[f]+ec+1;
height_base[f]= width_base[f]+nw;
depth_base[f]= height_base[f]+nh;
italic_base[f]= depth_base[f]+nd;
lig_kern_base[f]= italic_base[f]+ni;
kern_base[f]= lig_kern_base[f]+nl-kern_base_offset;
exten_base[f]= kern_base[f]+kern_base_offset+nk;
param_base[f]= exten_base[f]+ne

/*:581*/
#line 11010 ".\\dummy.w"
;
/*583:*/
#line 11098 ".\\dummy.w"

{if(lh<2)abort;
store_four_quarters(font_check[f]);
fget;read_sixteen(z);
fget;z= z*0400+fbyte;fget;z= (z*020)+(fbyte/020);
if(z<unity)abort;
while(lh> 2)
{fget;fget;fget;fget;decr(lh);
}
font_dsize[f]= z;
if(s!=-1000)
if(s>=0)z= s;
else z= xn_over_d(z,-s,1000);
font_size[f]= z;
}

/*:583*/
#line 11011 ".\\dummy.w"
;
/*584:*/
#line 11114 ".\\dummy.w"

for(k= fmem_ptr;k<=width_base[f]-1;k++)
{store_four_quarters(font_info[k].qqqq);
if((a>=nw)||(b/020>=nh)||(b%020>=nd)||
(c/4>=ni))abort;
switch(c%4){
case lig_tag:if(d>=nl)abort;break;
case ext_tag:if(d>=ne)abort;break;
case list_tag:/*585:*/
#line 11135 ".\\dummy.w"

{check_byte_range(d);
while(d<current_character_being_worked_on)
{qw= char_info(f)(d);

if(char_tag(qw)!=list_tag)goto not_found;
d= qo(rem_byte(qw));
}
if(d==current_character_being_worked_on)abort;
not_found:;}

/*:585*/
#line 11122 ".\\dummy.w"
break;
default:do_nothing;
}
}

/*:584*/
#line 11012 ".\\dummy.w"
;
/*586:*/
#line 11170 ".\\dummy.w"

{/*587:*/
#line 11180 ".\\dummy.w"

{alpha= 16;
while(z>=040000000)
{z= z/2;alpha= alpha+alpha;
}
beta= 256/alpha;alpha= alpha*z;
}

/*:587*/
#line 11171 ".\\dummy.w"
;
for(k= width_base[f];k<=lig_kern_base[f]-1;k++)
store_scaled(font_info[k].sc);
if(font_info[width_base[f]].sc!=0)abort;
if(font_info[height_base[f]].sc!=0)abort;
if(font_info[depth_base[f]].sc!=0)abort;
if(font_info[italic_base[f]].sc!=0)abort;
}

/*:586*/
#line 11013 ".\\dummy.w"
;
/*588:*/
#line 11194 ".\\dummy.w"

bch_label= 077777;bchar= 256;
if(nl> 0)
{for(k= lig_kern_base[f];k<=kern_base[f]+kern_base_offset-1;k++)
{store_four_quarters(font_info[k].qqqq);
if(a> 128)
{if(256*c+d>=nl)abort;
if(a==255)if(k==lig_kern_base[f])bchar= b;
}
else{if(b!=bchar)check_existence(b);
if(c<128)check_existence(d)
else if(256*(c-128)+d>=nk)abort;
if(a<128)if(k-lig_kern_base[f]+a+1>=nl)abort;
}
}
if(a==255)bch_label= 256*c+d;
}
for(k= kern_base[f]+kern_base_offset;k<=exten_base[f]-1;k++)
store_scaled(font_info[k].sc);

/*:588*/
#line 11014 ".\\dummy.w"
;
/*589:*/
#line 11214 ".\\dummy.w"

for(k= exten_base[f];k<=param_base[f]-1;k++)
{store_four_quarters(font_info[k].qqqq);
if(a!=0)check_existence(a);
if(b!=0)check_existence(b);
if(c!=0)check_existence(c);
check_existence(d);
}

/*:589*/
#line 11015 ".\\dummy.w"
;
/*590:*/
#line 11226 ".\\dummy.w"

{for(k= 1;k<=np;k++)
if(k==1)
{fget;sw= fbyte;if(sw> 127)sw= sw-256;
fget;sw= sw*0400+fbyte;fget;sw= sw*0400+fbyte;
fget;font_info[param_base[f]].sc= 
(sw*020)+(fbyte/020);
}
else store_scaled(font_info[param_base[f]+k-1].sc);
if(hpos>=hend)abort;
for(k= np+1;k<=7;k++)font_info[param_base[f]+k-1].sc= 0;
}

/*:590*/
#line 11016 ".\\dummy.w"
;
/*591:*/
#line 11246 ".\\dummy.w"

if(np>=7)font_params[f]= np;else font_params[f]= 7;
hyphen_char[f]= skew_char[f]= -1;
if(bch_label<nl)bchar_label[f]= bch_label+lig_kern_base[f];
else bchar_label[f]= non_address;
font_bchar[f]= qi(bchar);
font_false_bchar[f]= qi(bchar);
if(bchar<=ec)if(bchar>=bc)
{qw= char_info(f)(bchar);
if(char_exists(qw))font_false_bchar[f]= non_char;
}
font_name[f]= nom;
font_bc[f]= bc;font_ec[f]= ec;font_glue[f]= null;
decr(param_base[f]);
fmem_ptr= fmem_ptr+lf;goto done

/*:591*/
#line 11017 ".\\dummy.w"


/*:577*/
#line 10974 ".\\dummy.w"
;
bad_tfm:QUIT("Bad tfm file: %s\n",nom);
done:;
}

/*:575*/
