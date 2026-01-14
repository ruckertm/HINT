#define GL_SILENCE_DEPRECATION 1

#import <Foundation/Foundation.h>
#import <ApplicationServices/ApplicationServices.h>
#import "HintOpenGLView.h"
#import "SectionsController.h"
#import "AppDelegate.h"
#import "PrintView.h"
#define DEBUG
#define GL_SILENCE_DEPRECATION 1
#include <OpenGL/gl3.h>
#include "hint.h"
#include "rendernative.h"
#include "main.h"

@implementation HintOpenGLView

static HintOpenGLView * main_view=nil;

+ (HintOpenGLView *)  mainView
{ return main_view; }

- (void) drawRect:(NSRect)rect
{// [[self openGLContext] makeCurrentContext];
    if(!self->ready)
        return;
    hint_render();
    [[self openGLContext] flushBuffer];
    //NSLog(@"OGL drawRect:\n");
}


-(id) initWithFrame: (NSRect) frameRect
{ NSOpenGLPixelFormatAttribute pixelFormatAttributes[] ={
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAColorSize    , 24                           ,
            NSOpenGLPFAAlphaSize    , 8                            ,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleBuffers, (NSOpenGLPixelFormatAttribute)1,
            NSOpenGLPFASamples, (NSOpenGLPixelFormatAttribute)4,
            NSOpenGLPFADoubleBuffer ,
            NSOpenGLPFAAccelerated  ,
            NSOpenGLPFANoRecovery   ,
            0
            };
  NSOpenGLPixelFormat* format = [[NSOpenGLPixelFormat alloc]initWithAttributes:pixelFormatAttributes];
    self->ready=NO;
  self = [super initWithFrame:frameRect pixelFormat:format];
  [[self window] setAcceptsMouseMovedEvents:YES];
  [[self openGLContext] makeCurrentContext];
    NSTrackingArea *ta = [NSTrackingArea alloc];
    [ta initWithRect: frameRect
        options: (NSTrackingMouseEnteredAndExited | NSTrackingInVisibleRect|  NSTrackingActiveAlways )
        owner:self userInfo:nil];
    [self addTrackingArea:ta];
    [self registerForDraggedTypes:@[NSPasteboardTypeURL]];
    [format release];
  return self;
}



- (void) prepareOpenGL
{   
    const GLint  swapInt = 1;
    [super prepareOpenGL];
    [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval]; // set to vbl sync
    nativeInit();
    hint_clear_fonts(false);
    main_view=self;
    [self nightMode:nil];
    [self autoReloadFile:nil];
    [self showSearch:nil];
    [self setScale: scale];
   
    self->ready=YES;
}

- (void) awakeFromNib
{
    NSLog(@"awakeFromNib done");
  
}

static int px_x=1024, px_y=768; /* size in pixel */
static double x_dpi, y_dpi;     /* resolution in dpi */

- (void) setDpi
{ NSRect w = [[self window] frame];
  NSRect v = [self convertRectToBacking:[self bounds]];
  CGDirectDisplayID dspys[1];
  CGDisplayCount dCnt;
  CGGetDisplaysWithPoint (w.origin,1, dspys, &dCnt);
  CGRect px = CGDisplayBounds (dspys[0]);
  NSSize pz = [self convertSizeToBacking:px.size];
  CGSize mm = CGDisplayScreenSize(dspys[0]);
  x_dpi= pz.width*25.4f/mm.width;
  y_dpi= pz.height*25.4f/mm.height;
  px_x = v.size.width;
  px_y = v.size.height;
  NSLog(@"DPI: %3f x %3f for %d x %d\n", x_dpi, y_dpi, px_x, px_y);
}

- (void) setGamma: (double) g
{ hint_gamma(g);
  [self setNeedsDisplay: YES];
    NSLog(@"setGamma");
}

- (void) setScale:(double)s
{   NSRect baseRect = [self convertRectToBacking:[self bounds]];
    scale=s;
    px_x = baseRect.size.width;
    px_y = baseRect.size.height;
    hint_resize(px_x,px_y,scale*x_dpi,scale*y_dpi);
    hint_clear_fonts(false);
    hint_page();
    [self setNeedsDisplay: YES];
}

- (void)reshape
{
    [super reshape];
    NSRect baseRect = [self convertRectToBacking:[self bounds]];
    px_x = baseRect.size.width;
    px_y = baseRect.size.height;
    hint_resize(px_x,px_y,scale*x_dpi,scale*y_dpi);
    hint_page();
    [self setNeedsDisplay: YES];
    //NSLog(@"reshaping: %d %d\n", px_x, px_y);
}

- (void) update // window resizes, moves, display change, display config change
{
    [super update];
    if (![self inLiveResize])  {// if not doing live resize eg moving to new monitor
        [self setDpi];
        hint_resize(px_x,px_y,scale*x_dpi,scale*y_dpi);
        hint_clear_fonts(false);
        if (!self->ready) return;
        hint_page();
        [self setNeedsDisplay: YES];
        
    }
   
}


- (BOOL)acceptsFirstResponder {  return YES; }
- (BOOL)becomeFirstResponder  {  return YES; }
- (BOOL)resignFirstResponder  {  return YES; }

// Menu items

-(IBAction) nightMode:(NSMenuItem *) sender
{
    if (sender!=nil) dark = !dark;
    if (dark)
        [_nightModeItem setState:NSControlStateValueOn];
    else
        [_nightModeItem setState: NSControlStateValueOff];
    hint_dark(dark);
    [self setNeedsDisplay: YES];
}

-(IBAction) homePage:(id)sender
{ hint_page_home();
  [self setNeedsDisplay: YES];
}

static void clearCursor(void)
{  [[NSCursor arrowCursor] set];
}
static NSCursor *theResizeCursor=nil;
static void setResizeCursor(void)
{ if (theResizeCursor==nil)
  { NSString *cursorName = @"resizenorthwestsoutheast";
    NSString *cursorPath = [@"/System/Library/Frameworks/ApplicationServices.framework/Versions/A/Frameworks/HIServices.framework/Versions/A/Resources/cursors" stringByAppendingPathComponent:cursorName];
    NSImage *image = [[NSImage alloc] initByReferencingFile:[cursorPath stringByAppendingPathComponent:@"cursor.pdf"]];
    NSDictionary *info = [NSDictionary dictionaryWithContentsOfFile:[cursorPath stringByAppendingPathComponent:@"info.plist"]];
    theResizeCursor = [[NSCursor alloc] initWithImage:image hotSpot:NSMakePoint([[info valueForKey:@"hotx"] doubleValue], [[info valueForKey:@"hoty"] doubleValue])];
    if (theResizeCursor==nil)
        theResizeCursor=[NSCursor crosshairCursor]; // fall back
  }
  [theResizeCursor set];
}

-(IBAction) zoom100:(id)sender
{ scale=SCALE_NORMAL;
  hint_resize(px_x,px_y,scale*x_dpi,scale*y_dpi);
  hint_clear_fonts(false);
  hint_page();
 
  clearCursor();
  [self setNeedsDisplay: YES];
}

extern NSString *DocumentBookmark;

- (IBAction)openFile:(id)sender {
   NSOpenPanel* panel = [NSOpenPanel openPanel];
#if 0
    UTType *hnt;
    [hnt init(@"hnt")];
    [hnt ar aUTType init];
    NSArray<UTType*>* hnt = @[@"hnt"]; // see "Info".plist for URL types
    [panel setAllowedContentTypes: hnt;
#endif
   // This method displays the panel and returns immediately.
   // The completion handler is called when the user selects an
   // item or cancels the panel.
   [panel beginWithCompletionHandler:^(NSInteger result){
        if (result == NSModalResponseOK) {
         NSURL*  url = [[panel URLs] objectAtIndex:0];
          if ([url isFileURL]) {
              [(AppDelegate*)sender openFile: url];
        }
      }
   }];
}
#define MAX_SEARCH 256
static char search_string[MAX_SEARCH];
static int search_length;
- (IBAction)findSearchText:(NSSearchFieldCell *)sender
{  [[sender stringValue] getCString: search_string maxLength: MAX_SEARCH encoding:NSUTF8StringEncoding];
    search_length=(int)strlen(search_string);
    hint_set_mark(search_string,search_length);
    [self setNeedsDisplay: YES];
    NSLog(@"SearchField %s",search_string);
}
- (IBAction)findPrevText:(id)sender {
    NSLog(@"SearchPrev %s",search_string);
    hint_prev_mark();
    [self setNeedsDisplay: YES];
}

- (IBAction)findNextText:(id)sender {
    NSLog(@"SearchNext %s",search_string);
    hint_next_mark();
    [self setNeedsDisplay: YES];
}



- (IBAction)showSearch:(id)sender {
    //NSLog(@"FindText");
       
    if (sender!=nil) showsearch=!showsearch;
    if (showsearch)
        [_showSearchItem setState:NSControlStateValueOn];
    else
        [_showSearchItem setState: NSControlStateValueOff];
    [[self theToolbar] setVisible:showsearch];
}

- (IBAction)autoReloadFile:(id)sender {
    if (sender!=nil) autoreload = !autoreload;
    if (autoreload)
        [_autoReloadItem setState:NSControlStateValueOn];
    else
        [_autoReloadItem setState: NSControlStateValueOff];
}

- (IBAction)reloadFile:(id)sender {
    double fpos;
    if (!loading)
    { loading=1;
      NSLog(@"reload File");
      fpos=hint_get_fpos();
      hint_end();
      hint_begin();
      pos=hint_set_fpos(fpos);
      clearCursor();
      loading=0;
      [self setNeedsDisplay: YES];
    }
}


- (void) mouseEntered:(NSEvent *) theEvent
{   if (autoreload)
    { [self reloadFile: nil];
       
    }
}

- (void) mouseExited:(NSEvent *) theEvent
{
}


-(void)keyDown:(NSEvent *)theEvent
{   NSString *characters = [theEvent characters];
    if ([characters length]) {
        unichar character = [characters characterAtIndex:0];
        switch (character) {
            case NSHomeFunctionKey:
                [self homePage:nil];
                return;
            case NSPageUpFunctionKey:
            case NSUpArrowFunctionKey:
                hint_page_prev();
                [self setNeedsDisplay: YES];
                return;
            case NSPageDownFunctionKey:
            case NSDownArrowFunctionKey:
                hint_page_next();
                [self setNeedsDisplay: YES];
                return;
            case 'n':
            case 0x0E: /* Ctrl-N */
                dark = !dark;
                [self nightMode:nil];
                return;
            case 'z':
            case 0x1A: /* Ctrl-Z */
                [self zoom100: nil];
                return;
            case '?':
                [NSApp showHelp:nil];
                return;
         }
        NSLog(@"Char 0x%x (%c)",character,character);
    }
    [super keyDown:theEvent];
}


- (BOOL)acceptsFirstMouse:(NSEvent *)event
{ return YES; } /* otherwise the first mouse event makes the window the "key window" and is discarded*/

static int mouse_down=0, on_link=0;
static double x_start, y_start, xy_start, scale_start, time_start;
#define DELTA_T 0.4
#define DELTA_XY 16.0


- (void)mouseDown:(NSEvent *)theEvent // trackball
{
    NSPoint location = [self convertPointToBacking:[theEvent locationInWindow]];
    x_start = location.x; y_start=px_y-location.y;
    xy_start=x_start*x_start+y_start*y_start;
    time_start=[theEvent timestamp];
    scale_start=scale;
    drag=0;
    mouse_down=1;
    //NSLog(@"mouse down");
}

- (void)mouseUp:(NSEvent *)theEvent
{  //NSLog(@"mouse up");
    if (drag) {
        drag=0;
        clearCursor();
        hint_clear_fonts(false);
        [self setNeedsDisplay: YES];
    }
    else
    { NSPoint location = [self convertPointToBacking:[theEvent locationInWindow]];
      int x,y;
      int link;
      x=location.x;
      y=px_y-location.y;
      NSLog(@"xy= %dx%d\n", x,y);
//          HINT_TRY {
      link=hint_find_link(x,y,y_dpi/36);
            if (link>=0)
            { hint_link_page(link);
              [self setNeedsDisplay: YES];
              NSLog(@"following link");
              clearCursor();
            }
  //        }
    }
    mouse_down=0;
    
}

- (void)mouseDragged:(NSEvent *)theEvent
{ double x,y,f;
    NSPoint location = [self convertPointToBacking:[theEvent locationInWindow]];
    x=location.x; y=px_y-location.y;
    drag=1;
    /* possibly set round_to_pixel to 0 while dragging */
    f=(x_start*x+y_start*y)/xy_start; /* projection of (x,y) on (x_start,y_start) */
    scale=scale_start*f;
    if (scale < SCALE_MIN) scale=SCALE_MIN;
    if (scale > SCALE_MAX) scale=SCALE_MAX;
    hint_resize(px_x,px_y,scale*x_dpi,scale*y_dpi);
    hint_page();
    [self setNeedsDisplay: YES];
    setResizeCursor();
//    NSLog(@"drag: %f + %f\n",x,y);
}

- (void) mouseMoved:(NSEvent *)theEvent
{  NSLog(@"mouse move not imlemented");
   [super mouseMoved:theEvent];
}

- (void)scrollWheel:(NSEvent *)theEvent
{   NSLog(@"mouse wheel not implemented");
    float wheelDelta = [theEvent deltaX] +[theEvent deltaY] + [theEvent deltaZ];
    if (wheelDelta>0.0)
    {
        [self setNeedsDisplay: YES];
    }
}

- (void) performTextFinderAction:(id)sender
{ NSLog(@"text finder not yet implemented");
    
}

- (NSDragOperation)draggingEntered:(id <NSDraggingInfo>)sender
{
    // HACK: We don't know what to say here because we don't know what the
    //       application wants to do with the paths
    return NSDragOperationGeneric;
}

- (BOOL)performDragOperation:(id <NSDraggingInfo>)sender
{
    const NSRect contentRect = [self frame];
    // NOTE: The returned location uses base 0,1 not 0,0
    const NSPoint pos = [sender draggingLocation];
    //_glfwInputCursorPos(window, pos.x, contentRect.size.height - pos.y);

    NSPasteboard* pasteboard = [sender draggingPasteboard];
    NSDictionary* options = @{NSPasteboardURLReadingFileURLsOnlyKey:@YES};
    NSArray* urls = [pasteboard readObjectsForClasses:@[[NSURL class]]
                                              options:options];
    const NSUInteger count = [urls count];
    if (count)
    {
        if ([urls[0] isFileURL]) {
            [(AppDelegate*)[NSApp delegate] openFile: urls[0] ];

          //open_file([urls[0] path]);
          [self.window setTitleWithRepresentedFilename: [urls[0] path]];
        }
    }

    return YES;
}

//import <ApplicationServices.framework/Framework/PrintCore.framework/Headers/PMCore.h>

- (IBAction)print:(id)sender
{   uint64_t pos=hint_page_get();
    NSPrintOperation *op;
    NSPrintInfo *pInfo;
    pInfo=[NSPrintInfo sharedPrintInfo];
    NSRect pr;
    pr.origin.x=pr.origin.y=0;
    pr.size =[pInfo paperSize];
    
    PrintView *pv = [[PrintView alloc] initWithFrame:pr];
    op = [NSPrintOperation printOperationWithView:pv];
   // [op setCanSpawnSeparateThread:YES];
    /* do not useg the OpenGL context or the TeX rendering system in two threads */

      if (op)
      {
        [op runOperation];
        hint_resize(px_x,px_y,scale*x_dpi,scale*y_dpi);
        hint_clear_fonts(false);
        hint_page_top(pos);
      }
      else
          NSLog(@"print error");
   
}


@end
