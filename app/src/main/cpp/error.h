	/*365:*/
	#line 7311 "format.w"

#ifndef _ERROR_H
#define _ERROR_H
#ifdef _MSC_VER 
#include "error32vc.h"
#else
#ifdef __ANDROID__ 
#include "erroras.h"
#else 
#include <stdlib.h>
#include <stdio.h>
extern FILE*hlog;
#define MESSAGE(...) (fprintf(hlog,__VA_ARGS__),fflush(hlog))
#define QUIT(...)   (fprintf(hlog,"ERROR: "),\
              MESSAGE(__VA_ARGS__),fprintf(hlog,"\n"),exit(1))
#endif
#endif
#define RNG(S,N,A,Z) \
  if ((int)(N)<(int)(A)||(int)(N)>(int)(Z)) QUIT(S " %d out of range [%d - %d]",N,A,Z)

#define TAGERR(A) QUIT("Unknown tag [%s,%d] at " SIZE_F "\n",NAME(A),INFO(A),hpos-hstart)
#define TAGSERR(A,Z) QUIT("Tag mismatch [%s,%d]!=[%s,%d] at 0x%x to " SIZE_F "\n",NAME(A),INFO(A),NAME(Z),INFO(Z),node_pos, hpos-hstart-1)
#endif
	/*:365*/
