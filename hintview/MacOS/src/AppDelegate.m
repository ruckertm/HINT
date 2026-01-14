#import "AppDelegate.h"
#import "HintOpenGLView.h"
#import "SectionsController.h"
#include "error.h"
#include "basetypes.h"
#include "format.h"
#include "get.h"
#include "hint.h"
#include "main.h"

#define GL_SILENCE_DEPRECATION 1

@implementation AppDelegate

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication
{
	return YES;
}

- (IBAction)openPreferencesPane:(NSMenuItem *)sender {
    NSLog(@"open Preferences");
    [_thePrefPanel makeKeyAndOrderFront:sender];
}

- (IBAction)showOutlinePane:(id)sender{
    NSLog(@"open Outline");
    [_theOutlineView setHeaderView:nil];
    [_theOutline makeKeyAndOrderFront:sender];
}

extern char*hin_name; /* from get.c */


int set_hin_name(const char *fn)
{ /* check for extension, keep a copy of fn in hurl_name */
  size_t sl;
  if (hin_name!=NULL) { free(hin_name); hin_name=NULL; }
  { hin_name=malloc(strlen(fn)+1);
    if (hin_name==NULL)
    { hint_error("Out of memory for file name", fn);
      return 0;
    }
    strcpy(hin_name,fn);
  }
  sl=strlen(hin_name);
  if (sl>4 && strncmp(hin_name+sl-4,".hnt",4)!=0)
  { hint_error("File Extension '.hnt' expected. I dont know how to open this file", hin_name);
    return 0;
  }
  return 1;

}


- (BOOL) openFile: (NSURL *) url
{ if (!set_hin_name(url.path.UTF8String))
    return NO;
  hint_end();
  if (!hint_begin())
      return NO;
  NSLog(@"file opend");
  if (start_home)
     hint_page_home();
  else
     hint_page_top(0);
  [_thePreferences setDocumentBookmark: url];
  [_theMainView.window setTitleWithRepresentedFilename:url.path];
  [[SectionsController  sectionOutlines] setSectionTree];
  //NSLog(@"Open %s",fn);
  [_theOutlineView reloadData];
  [_theMainView setNeedsDisplay: YES];
  return YES;
}




- (void)applicationWillFinishLaunching:(NSNotification *)notification
{ // Called after the main run loop has been started before files are opened
    [_thePreferences loadPreferences];
    NSLog(@"loading preferences done");
}



- (BOOL)application:(NSApplication *)sender openFile:(NSString *)filename
{ NSURL *url = [NSURL fileURLWithPath:filename];
  if (hin_name!=NULL && start_newwindow)
  { int err;
    LSLaunchURLSpec launchSpec;
    CFArrayRef itemURLs;
    //hint_message("New application:openFile: %s", filename.UTF8String);
    launchSpec.appURL = NULL;
    itemURLs = CFArrayCreate(NULL, (const void **)&url, 1, &kCFTypeArrayCallBacks);
    launchSpec.itemURLs = itemURLs; // CFBridgingRetain([NSURL fileURLWithPath: filename]);
    launchSpec.asyncRefCon = NULL;
    launchSpec.launchFlags = kLSLaunchAsync|kLSLaunchNewInstance;
    launchSpec.passThruParams = NULL;
    err = LSOpenFromURLSpec(&launchSpec, NULL);
    return err!=0;
  }
  else
  {  if ([self openFile:url])
       return YES;
  }
  return NO;
}



extern NSString * DocumentBookmark;

- (void) applicationDidFinishLaunching:(NSNotification *) notification
{// Called after main run loop has started before processing events
    // Called after application:openFile (above) if the app was launched by opening a file
    bool open=NO;    
    NSLog(@"App finished launching");
    if (hin_name==NULL)
    { if (DocumentBookmark!=nil && DocumentBookmark.length>0)
      { NSData *bookmk = [ [NSData alloc] initWithBase64EncodedString:DocumentBookmark options:NSDataBase64DecodingIgnoreUnknownCharacters];
        BOOL isStale=NO;
        NSError *err=nil;
        NSURL* bookmarkUrl = [NSURL URLByResolvingBookmarkData: bookmk
                                options:NSURLBookmarkResolutionWithSecurityScope
                                relativeToURL:nil
                                bookmarkDataIsStale:&isStale
                                error:&err];
        if (err!= nil)
            NSLog(@"Error reading file: %@", [err localizedDescription]);
        else
        {
            [bookmarkUrl startAccessingSecurityScopedResource];
            open= [self openFile: bookmarkUrl];
            [bookmarkUrl stopAccessingSecurityScopedResource];
        }
      }
        
      if (!open)
      { // hint_error("Opening file","failed");
          [_theMainView openFile:self];
      }
    }
}


- (void)applicationWillTerminate:(NSNotification *)notification
{
    [_thePreferences storePreferences];
    NSLog(@"storing preferences done");}
@end
