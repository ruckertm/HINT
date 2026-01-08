#import <Cocoa/Cocoa.h>
#import "PrefView.h"
#import "SectionsController.h"
#import "HintOpenGLView.h"
@interface AppDelegate : NSObject
{
    
    
}
@property (assign) IBOutlet HintOpenGLView *theMainView;
@property (assign) IBOutlet NSOutlineView *theOutlineView;
@property (assign) IBOutlet NSPanel *thePrefPanel;
@property (assign) IBOutlet PrefView *thePreferences;
@property (assign) IBOutlet NSPanel *theOutline;
@property (assign) IBOutlet SectionsController *theSectionsController;

- (IBAction)openPreferencesPane:(NSMenuItem *)sender;
- (IBAction)showOutlinePane:(id)sender;

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication;

- (BOOL)application:(NSApplication *)sender openFile:(NSString *)filename;

- (void)applicationWillFinishLaunching:(NSNotification *)notification;
- (void) applicationDidFinishLaunching:(NSNotification *) notification;
- (void)applicationWillTerminate:(NSNotification *)notification;

- (BOOL) openFile: (NSString *) filename;

@end
