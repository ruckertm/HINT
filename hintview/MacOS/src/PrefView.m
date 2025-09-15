//
//  PrefView.m
//  hintview
//
//  Created by Martin Ruckert on 23.06.22.
//

#import "PrefView.h"
#import <Foundation/Foundation.h>

#import "HintOpenGLView.h"
#import "SectionsController.h"
#include "basetypes.h"
#include "format.h"
#include "get.h"
#include "main.h"

@implementation PrefView
{
    
}

static NSString * const HomeKey =@"HintviewHome";
static NSString * const AutoreloadKey =@"HintviewAutoreload";
static NSString * const ShowSearchKey =@"HintviewShowSearch";
static NSString * const NewWindowKey =@"HintviewNewWindow";
static NSString * const DarkKey =@"HintviewDark";
static NSString * const GammaKey =@"HintviewGamma";
static NSString * const ScaleKey =@"HintviewScale";
static NSString * const DocumentKey =@"HintviewDocument";



- (IBAction)switchHome:(NSButton *)sender {
    if ([sender state]) start_home=1; else start_home=0;
}

- (IBAction)switchNewWindow:(NSButton *)sender {
    if ([sender state]) start_newwindow=1; else start_newwindow=0;
}

- (IBAction)switchShowSearchField:(NSButton *)sender {
    if ([sender state]) start_showsearch=1; else start_showsearch=0;
}

- (IBAction)switchAutoreload:(NSButton *)sender {
    if ([sender state]) start_autoreload=1; else start_autoreload=0;
}

- (void) setGammaText: (double) g
{ static char str[5];
  sprintf(str,"%.2f",g);
 [_theGammaValue setStringValue: [[NSString alloc] initWithCString:str encoding:NSASCIIStringEncoding]];
    [[HintOpenGLView mainView] setGamma: g];
}

- (void) setGammaSlider: (double) g
{      /* Initialize the Slider with values from 0 to 100*/
    g = 100.0*(g-GAMMA_MIN)/(GAMMA_MAX-GAMMA_MIN);
    if (g<0.0) g=0.0; else if (g>100.0) g=100.0;
    [_theGammaSlider setDoubleValue:g];
    
}
- (IBAction)slideGamma:(NSSlider *)sender {
    hgamma =GAMMA_MIN+(GAMMA_MAX-GAMMA_MIN)*[sender integerValue]/100.0;
    [self setGammaText: hgamma];
}

- (BOOL)acceptsFirstResponder {  return YES; }

-(void)keyDown:(NSEvent *)theEvent
{   NSString *characters = [theEvent characters];
    if ([characters length]) {
        double delta =[theEvent modifierFlags]&NSEventModifierFlagShift?0.1:0.01;
        unichar character = [characters characterAtIndex:0];
        switch (character) {
            case NSLeftArrowFunctionKey:
                hgamma=hgamma-delta;
                if (hgamma<GAMMA_MIN) hgamma=GAMMA_MIN;
                [self setGammaSlider:hgamma];
                [self setGammaText:hgamma];
                return;
            case NSRightArrowFunctionKey:
                hgamma=hgamma+delta;
                if (hgamma>GAMMA_MAX) hgamma=GAMMA_MAX;
                [self setGammaSlider:hgamma];
                [self setGammaText:hgamma];
                return;
         }
        NSLog(@"Pref Char 0x%x (%c)",character,character);
    }
    [super keyDown:theEvent];
}



-(void) setPreferences
{   NSInteger i;
    Boolean b;
    Boolean exists;
    double g;
    //NSLog(@"set Preferences");
    
        /* Initialize the Checkboxes */
    [_theHomeBox setState:start_home];
    [_theAutoreloadBox setState:start_autoreload];
    [_theShowSearchBox setState:start_showsearch];
    [_theNewWindowBox setState:start_newwindow];
 
    [self setGammaSlider:hgamma];
    [self setGammaText: hgamma];

}

extern int set_hin_name(const char *fn);
extern NSString * DocumentName;

- (void) loadPreferences
{   NSDictionary *appDefaults = @{
        HomeKey : @YES,
        AutoreloadKey : @NO,
        ShowSearchKey: @NO,
        NewWindowKey: @YES,
        DarkKey: @NO,
        GammaKey : @GAMMA_NORMAL,
        ScaleKey : @SCALE_NORMAL,
        DocumentKey : [NSString string]
    };
    NSUserDefaults *appPreferences = [NSUserDefaults standardUserDefaults];
    [appPreferences registerDefaults:appDefaults];
    
    start_home = [appPreferences boolForKey: HomeKey ];
    autoreload= start_autoreload = [appPreferences boolForKey:AutoreloadKey ];
    showsearch =start_showsearch = [appPreferences boolForKey:ShowSearchKey];
    start_newwindow = [appPreferences boolForKey:NewWindowKey ];
    dark = [appPreferences boolForKey:DarkKey ];
    hgamma = [appPreferences doubleForKey:GammaKey];
    if (hgamma==0.0) hgamma=GAMMA_NORMAL;
    if (hgamma<GAMMA_MIN) hgamma=GAMMA_MIN;
    else if (hgamma>GAMMA_MAX) hgamma=GAMMA_MAX;
     scale = [appPreferences doubleForKey:ScaleKey ];
    if (scale==0.0) scale=SCALE_NORMAL;
    if (scale < SCALE_MIN) scale=SCALE_MIN;
    else if (scale > SCALE_MAX) scale=SCALE_MAX;
    
    DocumentName = [appPreferences stringForKey: DocumentKey];
    
    [self setPreferences];
}
- (void) storePreferences
{   NSUserDefaults *appPreferences = [NSUserDefaults standardUserDefaults];
    [appPreferences setBool: start_home forKey: HomeKey ];
    [appPreferences setBool: start_autoreload forKey:AutoreloadKey ];
    [appPreferences setBool: start_showsearch forKey:ShowSearchKey];
    [appPreferences setBool: start_newwindow forKey:NewWindowKey];
    [appPreferences setBool: dark forKey:DarkKey ];
    [appPreferences setDouble:hgamma forKey:GammaKey];
    [appPreferences setDouble:scale forKey:ScaleKey];
    if (DocumentName!=nil && DocumentName.length>0)
      [appPreferences setObject: DocumentName forKey:DocumentKey];
}

- (void) setDocumentName: (NSString *) doc
{ DocumentName= [doc copy] ;
}

- (NSString *) documentName
{ return DocumentName;
}

- (void)resignKeyWindow
{  NSLog(@"resign key settings");
   [self storePreferences];
}
@end
