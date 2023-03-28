//
//  ViewController.h
//  iOSHintView
//
//  Created by Martin Ruckert on 10.10.22.
//

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>

@interface ViewController : UIViewController <GLKViewDelegate, UIDocumentPickerDelegate, UISearchBarDelegate, UIDropInteractionDelegate>

@property (weak, nonatomic) IBOutlet GLKView *theView;
@property (weak, nonatomic) IBOutlet UIToolbar *theToolbar;
@property (weak, nonatomic) IBOutlet UISearchBar *theSearchBar;

- (IBAction)theTap:(UITapGestureRecognizer *)sender;
- (IBAction)theUpSwipe:(UISwipeGestureRecognizer *)sender;
- (IBAction)theDownSwipe:(UISwipeGestureRecognizer *)sender;
- (IBAction)theNextPage:(UISwipeGestureRecognizer *)sender;

- (IBAction)thePrevPage:(UISwipeGestureRecognizer *)sender;
- (IBAction)theScale:(UIPinchGestureRecognizer *)sender;
- (IBAction)theOpenButton:(UIBarButtonItem *)sender;
- (IBAction)theMenuButton:(UIBarButtonItem *)sender;
- (IBAction)theDarkButton:(UIBarButtonItem *)sender;
- (IBAction)theHome:(UIBarButtonItem *)sender;
- (IBAction)theZoom1:(UIBarButtonItem *)sender;
- (IBAction)theSearchButton:(id)sender;


- (void) setSize: (CGSize)size;
- (void) setDarkMode;
- (void) showAlert;
- (void) getPreferences;
@end

extern void redisplay(void);
extern BOOL open_file(NSURL *url);
extern void set_preferences(void);
