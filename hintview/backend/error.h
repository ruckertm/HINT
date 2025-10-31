/*674:*/
#line 14487 "hint.w"

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
#endif

#ifdef __ANDROID__ 
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



#ifdef HAVE_HINT_LOG
#ifdef DEBUG
extern void hint_log(const char*format,...);
#define LOG(...) hint_log(__VA_ARGS__)
#else
#define LOG(...) 
#endif
#endif

#ifdef HAVE_HINT_MESSAGE
extern void hint_message(char*title,char*format,...);
#define MESSAGE(...)  hint_message("HINT",__VA_ARGS__)
#endif

#ifdef HAVE_HINT_ERROR
extern int hint_error(const char*title,const char*msg);
#define ERROR_MESSAGE  hint_error("HINT ERROR",hint_error_string)
#endif



#ifndef LOG
#ifdef DEBUG
#define LOG(...) (fprintf(hlog,__VA_ARGS__),fflush(hlog))
#else
#define LOG(...) 
#endif
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
#define HINT_TRY if ((hint_error_string[0]= 0,setjmp(hint_error_exit)==0))
#endif

#endif
/*:674*/
