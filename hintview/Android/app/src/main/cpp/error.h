/*368:*/
#line 7241 "hint.w"

#ifndef _ERROR_H
#define _ERROR_H
#include <stdlib.h> 
#include <stdio.h> 
#include <setjmp.h> 
#define MAX_HINT_ERROR 1024
extern char hint_error_string[MAX_HINT_ERROR];
extern FILE*hlog;
extern void hint_end(void);
extern jmp_buf hint_error_exit;

#ifdef _MSC_VER 
#define snprintf(S,N,F,...) _snprintf(S,N,F,__VA_ARGS__)
#ifndef _CONSOLE
#pragma warning(disable : 4996)
extern void hint_message(char*title,char*format,...);
#define MESSAGE(...)  hint_message("HINT",__VA_ARGS__)

extern int hint_error(char*title,char*msg);
#define ERROR_MESSAGE  hint_error("HINT ERROR",hint_error_string)
#endif
#line 7263 "hint.w"
#endif
#line 7264 "hint.w"

#ifdef __ANDROID__ 
#include <android/log.h> 

#define LOG(...)      __android_log_print(ANDROID_LOG_DEBUG,__FILE__,__VA_ARGS__)
#define MESSAGE(...)  __android_log_print(ANDROID_LOG_INFO,__FILE__, __VA_ARGS__)
#define ERROR_MESSAGE __android_log_print(ANDROID_LOG_ERROR,__FILE__,"ERROR: %s\n", hint_error_string)

#endif
#line 7273 "hint.w"

#ifndef LOG
#define LOG(...) (fprintf(hlog,__VA_ARGS__),fflush(hlog))
#endif
#line 7277 "hint.w"

#ifndef MESSAGE
#define MESSAGE(...)  (fprintf(stderr,__VA_ARGS__),fflush(stderr))
#endif
#line 7281 "hint.w"

#ifndef ERROR_MESSAGE
#define ERROR_MESSAGE        fprintf(stderr,"ERROR: %s\n",hint_error_string)
#endif
#line 7285 "hint.w"

#ifndef QUIT
#define QUIT(...)    (snprintf(hint_error_string,MAX_HINT_ERROR-1,__VA_ARGS__),\
                     ERROR_MESSAGE,hint_end(),longjmp(hint_error_exit,1))
#endif
#line 7290 "hint.w"


#ifndef HINT_TRY
#define HINT_TRY if ((hint_error_string[0]= 0,setjmp(hint_error_exit)==0))
#endif
#line 7295 "hint.w"

#endif
#line 7297 "hint.w"
/*:368*/
