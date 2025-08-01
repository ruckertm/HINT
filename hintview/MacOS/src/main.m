#import <Cocoa/Cocoa.h>
#import "HintOpenGLView.h"
#import "SectionsController.h"

#if 0
#include "rendernative.h" /* rendernative needs gcache_s */
#else
extern void nativeInit(void);
extern void nativeClear(void);
extern void nativeSetDark(int dark);
#endif
#include "error.h"
#include "basetypes.h"
#include "format.h"
#include "get.h"
#include "hint.h"
#include "hrender.h"
#include "main.h"

int dark = 0, loading=0, drag=0, autoreload=0, start_autoreload=0, start_home=1, start_showsearch, showsearch=0, start_newwindow=1;
double scale=SCALE_NORMAL, hgamma=GAMMA_NORMAL;
uint64_t pos; /* position of current page */



bool hint_map(void) /* open hurl_name and map to memory */
{ return hget_map();
}

void hint_unmap(void) /* unmap */
{ hget_unmap();
}



void hint_log(const char*format,...)
{
  va_list vargs;
  va_start(vargs,format);
  NSLogv([NSString stringWithUTF8String: format], vargs);
}



void hint_message(const char*format,...)
{ va_list vargs;
  va_start(vargs,format);
  NSLogv([NSString stringWithUTF8String: format], vargs);
}

int hint_error(const char*title,const char*msg){
    NSAlert *alert = [[NSAlert alloc] init];
    [alert setMessageText: [NSString stringWithUTF8String: title]];
   // [alert setAlertStyle:NSAlertStyleCritical];
    [alert setInformativeText:[NSString stringWithUTF8String: msg]];
    [alert runModal];
    [alert release];
    return 0;
}

int open_help_file(void)
{   // use URLForResource:withExtension:subdirectory:localization:
    // or URLsForResourcesWithExtension:subdirectory:
    // or resourcePath    The full pathname of the bundle’s subdirectory containing resources.
    // The file calibartion is now in the Assets.xcassets/callibration.dataset/ folder
    //     possibly there is a better place.
    return 0;
}

int main(int argc, char *argv[])
{ int i;
    //for (i=0; i<argc;i++)
    //  hint_log("Start '%s'",argv[i]);
    return NSApplicationMain(argc,  (const char **) argv);
}
