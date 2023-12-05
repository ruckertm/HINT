/* This file is part of HINT
 * Copyright 2017-2021 Martin Ruckert, Hochschule Muenchen, Lothstrasse 64, 80336 Muenchen
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
 * OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * Except as contained in this notice, the name of the copyright holders shall
 * not be used in advertising or otherwise to promote the sale, use or other
 * dealings in this Software without prior written authorization from the
 * copyright holders.
 */
//
//  ViewController.m
//  iOSHintView
//
//  Created by Martin Ruckert on 10.10.22.
//

#import "ViewController.h"
#import "AppDelegate.h"
#import "UniformTypeIdentifiers/UniformTypeIdentifiers.h"
#include "error.h"
#include "rendernative.h"
#include "hint.h"
#include "hrender.h"
#include "main.h"

@interface ViewController ()

@end

@implementation ViewController
static int x_pt, y_pt; /* for debugging used in drawRect*/

static int px_x=1024, px_y=768, px_scale=2; /* size in pixel */
static int x_dpi, y_dpi;     /* resolution in dpi */

- (void) setSize: (CGSize)size
{   UIScreen *screen = [UIScreen mainScreen];
    // UIScreenMode *mode=[screen currentMode];
   // CGFloat aspect = [mode pixelAspectRatio];
    
  
    CGSize pt;
    px_scale = screen.scale;
    px_x=size.width*px_scale;
    px_y=size.height*px_scale;
    // this is the dpi setting for the iPadPro 9.7in
    //x_dpi=264.0; //72.0*sc;
    //y_dpi=264.0; //72.0*sc;

    // this is the dpi setting for the iPhone XR 6,1in
    //x_dpi=326;
    //y_dpi=326;

    pt.width=72.0*px_x/x_dpi;
    pt.height=72.0*px_y/y_dpi;

    x_pt=pt.width;
    y_pt=pt.height;
    HINT_TRY
    { hint_resize(px_x,px_y,scale*x_dpi,scale*y_dpi);
      hint_page();
    }
    [_theView setNeedsDisplay];
}

int dpi_default(void)
/* It seems that Apple does not want the tprogrammer to determine the screen resolution so we guess.
   If you know a better solution, let me know. You can set the exact dpi values on the apps property page.
 */
{ double s =[UIScreen mainScreen].scale;
    if (s<=1) return 132;
    if (s<=2) return 326;
    if (s<=3) return 460;
    return 512;
}

- (void) setDarkMode /* set the mode based on the dark variale*/
{ if (dark)
  { [_theToolbar setTintColor: [UIColor colorWithRed: 0.0 green: 0.0 blue:0.0 alpha:1.0] ];
    [_theToolbar setBackgroundColor: [UIColor colorWithRed: 1.0 green: 1.0 blue:1.0 alpha:1.0]];
  }
  else
  { [_theToolbar setTintColor: [UIColor colorWithRed: 0.0 green:0.0 blue:0.0 alpha:1.0] ];
    [_theToolbar setBackgroundColor: [UIColor colorWithRed: 0.0 green: 0.0 blue:0.0 alpha:1.0]];
  }
  nativeSetDark(dark);
}

// Handling Preferences
static void setScale(void)
{ NSUserDefaults *pref = [NSUserDefaults standardUserDefaults];
  [pref setDouble:scale forKey:@"Scale"];
}

static void setDark(void)
{ NSUserDefaults *pref = [NSUserDefaults standardUserDefaults];
  [pref setBool: dark forKey:@"DarkMode"];
}

static void setXdpi(void)
{ NSUserDefaults *pref = [NSUserDefaults standardUserDefaults];
  [pref setInteger:x_dpi forKey:@"xDPI"];
}
static void setYdpi(void)
{ NSUserDefaults *pref = [NSUserDefaults standardUserDefaults];
  [pref setInteger:y_dpi forKey:@"yDPI"];
}
static void setGamma(void)
{ NSUserDefaults *pref = [NSUserDefaults standardUserDefaults];
  [pref setDouble:hgamma forKey:@"Gamma"];
}

static void setFileFPos(void)
{ NSUserDefaults *pref = [NSUserDefaults standardUserDefaults];
  double fpos=hint_get_fpos();
  [pref setDouble:fpos forKey:@"FPos"];
}

static void setFileURL(NSURL *url)
{ NSUserDefaults *pref = [NSUserDefaults standardUserDefaults];
    NSError *e;
  NSData *bookmark = [url
                      bookmarkDataWithOptions:  0
                      includingResourceValuesForKeys:nil
                      relativeToURL:nil error: nil];
 
  [pref setObject:bookmark forKey:@"URL"];
  LOG("Saving URL");
}

void set_preferences(void)
{   setScale();
    setDark();
    setXdpi();
    setYdpi();
    setGamma();
    setFileFPos();
    LOG("Saving Preferences");
}

- (void) getPreferences
{   NSUserDefaults *pref = [NSUserDefaults standardUserDefaults];
    hgamma = [pref doubleForKey:@"Gamma"];
    if (hgamma < GAMMA_MIN || hgamma> GAMMA_MAX)
    { hgamma=GAMMA_NORMAL; setGamma(); }
    start_home = (int)[pref boolForKey:@"StartHome"];
    dark = (int)[pref boolForKey:@"DarkMode"];
    [self setDarkMode];
    scale = [pref doubleForKey:@"Scale"];
    if (scale < SCALE_MIN|| scale> SCALE_MAX)
    { scale=SCALE_NORMAL;
      [pref setDouble: scale forKey:@"Scale"];
    }
    x_dpi = (int)[pref integerForKey:@"xDPI"];
    if (x_dpi<70 || x_dpi>1000)
    { x_dpi=dpi_default(); setXdpi();}
    y_dpi = (int)[pref integerForKey:@"yDPI"];
    if (y_dpi<70 || y_dpi>1000)
    { y_dpi=x_dpi; setYdpi(); }
    [self setSize: _theView.bounds.size]; /* sets needsDisplay */
    

    if (hin_name==NULL) // in case a file was aleady opended by scene openURLContexts:
    { NSData *bookmark= [pref objectForKey:@"URL"];
      double fpos = [pref doubleForKey:@"FPos"];
      if (fpos<0.0||fpos>1.0) fpos=0.0;
      if (bookmark!=nil)
      { BOOL stale;
        NSURL *url = [NSURL URLByResolvingBookmarkData:bookmark options: NSURLBookmarkResolutionWithoutMounting  relativeToURL:nil bookmarkDataIsStale: &stale error: nil];
        if (url!=nil)
        { HINT_TRY  { open_file(url); hint_set_fpos(fpos); }
          else hint_error("Error opening file", hint_error_string);
        }
      }
    }
}






static UIView *TopView=nil;

void redisplay(void)
{  if (TopView!=nil)
    dispatch_async(dispatch_get_main_queue(), ^{
        [TopView setNeedsDisplay]; // openFile might be on another thread
    });
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    //NSLog(@"View loaded");
    TopView=_theView;
    
    theViewControler = self;
    _theView.delegate=self;
    _theSearchBar.delegate=self;
   // [_theToolbar setAlpha:0.6];

    EAGLContext * context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    _theView.context = context;
     [EAGLContext setCurrentContext: context];


    nativeInit();
    [self getPreferences];
   
    [_theView addInteraction:[[UIDropInteraction alloc] initWithDelegate:self]];
}

- (void)viewWillTransitionToSize:(CGSize)size
       withTransitionCoordinator:(id<UIViewControllerTransitionCoordinator>)coordinator
{  [super viewWillTransitionToSize:size withTransitionCoordinator:coordinator];
  //NSLog(@"Transition to x= %f y=%f", size.width, size.height);
    [self setSize: size] ;
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    HINT_TRY hint_render();
#if 0
    if (dark)
      nativeRule(20.0,40.0, x_pt-40.0,20.0);
    else
      nativeRule(20.0,y_pt-10.0, x_pt-40.0,20.0);
#endif
}


- (IBAction)theTap:(UITapGestureRecognizer *)sender
{
    if (sender.state == UIGestureRecognizerStateEnded)
    { CGPoint location = [sender locationInView: _theView];
      double x,y;
      int link;
      x=72.27*location.x*px_scale/(x_dpi*scale);
      y=72.27*location.y*px_scale/(y_dpi*scale);
      //NSLog(@"xy= %fx%f\n", x,y);
      HINT_TRY {
        link=hint_find_link(x*(1<<16), y*(1<<16),4<<16);
        //Touch is less precise than mouse input
        if (link>=0)
        { hint_link_page(link);
          [_theView setNeedsDisplay];
          //NSLog(@"following link");
          //clearCursor();
        }
      }
    }
   
}

-(IBAction)theNextPage:(UISwipeGestureRecognizer *)sender
{
  hint_page_next();
  [_theView setNeedsDisplay];
}

-(IBAction)thePrevPage:(UISwipeGestureRecognizer *)sender
{
    hint_page_prev();
  [_theView setNeedsDisplay];
}

- (IBAction)theUpSwipe:(UISwipeGestureRecognizer *)sender
{
    [_theToolbar setHidden:NO];
}

- (IBAction)theDownSwipe:(UISwipeGestureRecognizer *)sender
{ [_theToolbar setHidden:YES];
    
}
- (IBAction)theScale:(UIPinchGestureRecognizer *)sender {
    static double start_scale;
    if (sender.state==UIGestureRecognizerStateBegan)
        start_scale=scale;
    else if (sender.state==UIGestureRecognizerStateEnded)
    {  setScale();
       hint_clear_fonts(true);
       [_theView setNeedsDisplay];
    }
    else
    { scale=start_scale*sender.scale;
      hint_resize(px_x,px_y,scale*x_dpi,scale*y_dpi);
      hint_page();
      [_theView setNeedsDisplay];
    }
}


- (IBAction)theDarkButton:(UIBarButtonItem *)sender {
    
    dark=!dark;
    [self setDarkMode];
    [_theView setNeedsDisplay];
    setDark();
}

- (IBAction)theZoom1:(UIBarButtonItem *)sender {
    scale=1;
    hint_resize(px_x,px_y,scale*x_dpi,scale*y_dpi);
    hint_page();
    [_theView setNeedsDisplay];
}

- (IBAction)theHome:(UIBarButtonItem *)sender {
    hint_page_home();
  [_theView setNeedsDisplay];
}

- (IBAction)theMenuButton:(UIBarButtonItem *)sender {
    
     
}



- (IBAction)theOpenButton:(UIBarButtonItem *)sender {
    UTType *hint =  [UTType typeWithIdentifier:@"edu.hm.cs.hint.hintview.hnt"]; // defined in Info.plist
    UIDocumentPickerViewController *pick =[[UIDocumentPickerViewController alloc]
    initForOpeningContentTypes: @[hint]];
    pick.delegate = self;
    pick.allowsMultipleSelection = NO;
    pick.modalPresentationStyle = UIModalPresentationFullScreen;
    [self presentViewController:pick animated: YES completion: nil];
}





- (void)documentPicker:(UIDocumentPickerViewController *)controller
didPickDocumentsAtURLs:(NSArray<NSURL *> *)urls
{ NSURL *url=[urls firstObject];
  { NSLog(@"Url picked");
    open_file(url);
  }
}


extern char*hin_name; /* from get.c */

static int set_hin_name(const char *fn)
{ /* check for extension, keep a copy of fn in hurl_name */
  size_t sl;
  if (hin_name!=NULL) { free(hin_name); hin_name=NULL; }
  { hin_name=malloc(strlen(fn)+1);
    if (hin_name==NULL)
    { //herror("Out of memory for file name", fn);
      return 0;
    }
    strcpy(hin_name,fn);
  }
  sl=strlen(hin_name);
  if (sl>4 && strncmp(hin_name+sl-4,".hnt",4)!=0)
  {  //herror("Unknown File Type,I dont know how to open this file", hin_name);
    return 0;
  }
  return 1;

}


BOOL open_file(NSURL *url)
{ if (![url isFileURL]) return NO;
  if (![url startAccessingSecurityScopedResource])
  { hint_error("Access NOT granted", [url path].UTF8String); return NO; }
  if (!set_hin_name([url path].UTF8String))
  { [url stopAccessingSecurityScopedResource]; return NO; }
  hint_clear_fonts(true);
  //NSLog(@"hint begin %s",hin_name);
  if (!hint_begin()) /* this reads the file */
  {  hint_error("Error opening file","This is not a HINT file");
      [url stopAccessingSecurityScopedResource]; return NO; }
  setFileURL(url);
  [url stopAccessingSecurityScopedResource];
  
  if (start_home)
     hint_page_home();
  else
     hint_page_top(0);
  //[[HintOpenGLView mainView].window setTitleWithRepresentedFilename:filename];
  //[[SectionsController  sectionOutlines] setSectionTree];
  //[_theOutlineView reloadData];
  redisplay();
  return YES;
}

/* Droping Files */
- (BOOL)dropInteraction:(UIDropInteraction *)interaction canHandleSession:(id<UIDropSession>)session {
    BOOL ok= [session hasItemsConformingToTypeIdentifiers:@[@"edu.hm.cs.hint.hintview.hnt"]];
    //NSLog(@"session: %d",ok);
    return ok;
}

- (UIDropProposal *)dropInteraction:(UIDropInteraction *)interaction
                   sessionDidUpdate:(id<UIDropSession>)session
{   UIDropProposal *p =[[UIDropProposal alloc] initWithDropOperation: UIDropOperationCopy];
    //NSLog(@"proposal: %@",p);
    return p;
}

- (void)dropInteraction:(UIDropInteraction *)interaction
            performDrop:(id<UIDropSession>)session
{ //Used when dropping a file onto HintView
    if (session.items.count == 0) return;
    NSItemProvider *p = [session.items firstObject].itemProvider;
    [p loadInPlaceFileRepresentationForTypeIdentifier:@"edu.hm.cs.hint.hintview.hnt"
        completionHandler:^(NSURL * _Nullable url, BOOL isInPlace, NSError * _Nullable error) {
        NSLog(@"Drop Path %@",url);
        open_file(url);
    }];
}


/* Searching Text */

- (IBAction)theSearchButton:(id)sender {
    if ([_theSearchBar isHidden])
      [_theSearchBar setHidden:NO];
    else
    {   hint_next_mark();
        [_theView setNeedsDisplay];
        
    }
}

#define MAX_SEARCH 256
static char search_string[MAX_SEARCH];
static int search_length;
- (void) searchBar:(UISearchBar *)searchBar textDidChange:(NSString *)searchText
{  [searchText getCString: search_string maxLength: MAX_SEARCH encoding:NSUTF8StringEncoding];
    search_length=(int)strlen(search_string);
    hint_set_mark(search_string,search_length);
    [_theView setNeedsDisplay];
    //NSLog(@"Search: %@",searchText);
}

- (void)searchBarSearchButtonClicked:(UISearchBar *)searchBar
{
    //NSLog(@"Search: %@ !",searchBar.text);
    [_theSearchBar  endEditing:YES];
    hint_next_mark();
    [_theView setNeedsDisplay];
}
-(void) searchBarCancelButtonClicked:(UISearchBar *)searchBar
{
    [_theSearchBar  endEditing:YES];
    [_theSearchBar setHidden:YES];
}

- (void) showAlert: (NSString *) msg {
    UIAlertController* alert = [UIAlertController alertControllerWithTitle:@"HINT"
                                   message: msg
                                   preferredStyle:UIAlertControllerStyleAlert];
     
    UIAlertAction* defaultAction = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault
                                                          handler:^(UIAlertAction * action) { //NSLog(@"showAlert: Default Action");
        
    }];
     
    [alert addAction:defaultAction];
    [self presentViewController:alert animated:YES completion:nil];
}

@end
