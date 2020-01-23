#include <android/log.h>

#define  MESSAGE(...)  __android_log_print(ANDROID_LOG_INFO,__FILE__,__VA_ARGS__)
#define  QUIT(...)    (__android_log_print(ANDROID_LOG_ERROR,__FILE__,__VA_ARGS__), exit(1))
