/*104:*/
#line 2192 ".\\dummy.w"

#include "htex.h"
#include "texdef.h"

typedef uint32_t nonnegative_integer;

bool arith_error;
scaled rem;

int half(int x)
{if(odd(x))return(x+1)/2;
else return x/2;
}

/*:104*//*111:*/
#line 2308 ".\\dummy.w"

scaled x_over_n(scaled x,int n)
{bool negative;
scaled x_over_n;negative= false;
if(n==0)
{arith_error= true;x_over_n= 0;rem= x;
}
else{if(n<0)
{negate(x);negate(n);negative= true;
}
if(x>=0)
{x_over_n= x/n;rem= x%n;
}
else{x_over_n= -((-x)/n);rem= -((-x)%n);
}
}
if(negative)negate(rem);
return x_over_n;}

/*:111*//*112:*/
#line 2334 ".\\dummy.w"

scaled xn_over_d(scaled x,int n,int d)
{bool positive;
nonnegative_integer t,u,v;
scaled xn_over_d;if(x>=0)positive= true;
else{negate(x);positive= false;
}
t= (x%0100000)*n;
u= (x/0100000)*n+(t/0100000);
v= (u%d)*0100000+(t%0100000);
if(u/d>=0100000)arith_error= true;
else u= 0100000*(u/d)+(v/d);
xn_over_d= u;rem= v%d;
if(!positive)
{xn_over_d= -xn_over_d;rem= -rem;}
return xn_over_d;}

/*:112*//*113:*/
#line 2371 ".\\dummy.w"

halfword badness(scaled t,scaled s)
{int r;

if(t==0)return 0;
else if(s<=0)return inf_bad;
else{if(t<=7230584)r= (t*297)/s;
else if(s>=1663497)r= t/(s/297);
else r= t;
if(r> 1290)return inf_bad;
else return(r*r*r+0400000)/01000000;
}
}

/*:113*/
