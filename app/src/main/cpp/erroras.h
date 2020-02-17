#include <android/log.h>
#include <stdio.h>
#include <setjmp.h>
#ifdef __cplusplus
extern "C" {
#endif
jmp_buf error_exit;
#define MAX_HERROR 1024
char herror_string[MAX_HERROR];
#ifdef __cplusplus
}
#endif
#if 1
#define MESSAGE(...)  __android_log_print(ANDROID_LOG_INFO,__FILE__,__VA_ARGS__)
#else
#define MESSAGE(...) ((void)0)
#endif
#define  QUIT(...)    (hbase=NULL,snprintf(herror_string,MAX_HERROR-1,__VA_ARGS__),MESSAGE("ERROR: %s",herror_string),longjmp(error_exit,1))
