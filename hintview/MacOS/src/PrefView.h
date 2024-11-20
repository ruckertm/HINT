//
//  PrefView.h
//  hintview
//
//  Created by Martin Ruckert on 23.06.22.
//

#import <Cocoa/Cocoa.h>


@interface PrefView : NSView
{
   NSInteger GammaValue;
}

@property (weak) IBOutlet NSButton *theHomeBox;
@property (weak) IBOutlet NSButton *theAutoreloadBox;
@property (weak) IBOutlet NSButton *theShowSearchBox;
@property (weak) IBOutlet NSButton *theNewWindowBox;
@property (weak) IBOutlet NSSlider *theGammaSlider;
@property (weak) IBOutlet NSTextField *theGammaValue;


- (IBAction)switchHome:(NSButton *)sender;
- (IBAction)switchAutoreload:(NSButton *)sender;
- (IBAction)switchShowSearchField:(NSButton *)sender;
- (IBAction)switchNewWindow:(NSButton *)sender;

- (IBAction)slideGamma:(NSSlider *)sender;

- (void) setGammaText: (double) g;
- (void) setGammaSlider: (double) g;

- (BOOL) acceptsFirstResponder;

-(void)keyDown:(NSEvent *)theEvent;

-(void) loadPreferences;
- (void) storePreferences;
- (void) resignKeyWindow;
@end

