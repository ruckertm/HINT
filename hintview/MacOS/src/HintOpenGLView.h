#import <Cocoa/Cocoa.h>

@interface HintOpenGLView : NSOpenGLView

{
    @private
    BOOL ready;
}

+ (HintOpenGLView *)  mainView;

@property (strong) IBOutlet NSMenuItem *autoReloadItem;
@property (strong) IBOutlet NSMenuItem *nightModeItem;
@property (strong) IBOutlet NSMenuItem *showSearchItem;
@property (strong) IBOutlet NSSearchFieldCell *searchField;
@property (strong) IBOutlet NSToolbar *theToolbar;



- (IBAction) zoom100: (id) sender;
- (IBAction) homePage: (id) sender;
- (IBAction) nightMode: (id) sender;
- (IBAction) openFile: (id) sender;
- (IBAction) reloadFile:(id)sender;
- (IBAction) autoReloadFile:(id)sender;
- (IBAction) showSearch:(id)sender;
- (IBAction) findNextText:(id)sender;
- (IBAction) findPrevText:(id)sender;
- (IBAction)findSearchText:(NSSearchFieldCell *)sender;

- (void) setDpi;
- (void) setGamma: (double) g;
- (void) setScale: (double) s;

- (void) keyDown:(NSEvent *)theEvent;

- (void) mouseDown:(NSEvent *)theEvent;
- (void) mouseUp:(NSEvent *)theEvent;
- (void) mouseDragged:(NSEvent *)theEvent;
- (void) mouseMoved:(NSEvent *)theEvent;
- (void) scrollWheel:(NSEvent *)theEvent;
- (void) mouseEntered:(NSEvent *) theEvent;
- (void) mouseExited:(NSEvent *) theEvent;

- (BOOL) acceptsFirstMouse:(NSEvent *)event;
- (BOOL) acceptsFirstResponder;
- (BOOL) becomeFirstResponder;
- (BOOL) resignFirstResponder;

- (id)   initWithFrame: (NSRect) frameRect;
- (void) awakeFromNib;

- (void) reshape;
- (void) update;        // moved or resized
- (void) prepareOpenGL;
- (void) drawRect:(NSRect)rect;
- (void) performTextFinderAction:(id)sender;
- (NSDragOperation)draggingEntered:(id <NSDraggingInfo>)sender;
- (BOOL)performDragOperation:(id <NSDraggingInfo>)sender;
- (IBAction)print:(id)sender;
@end
