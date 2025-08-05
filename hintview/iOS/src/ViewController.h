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
@property (weak, nonatomic) IBOutlet UIMenu *theOptions;




- (void) setSize: (CGSize)size;
- (void) setDarkMode;
- (void) getPreferences;
@end

extern void redisplay(void);
extern BOOL open_file(NSURL *url);
extern void set_preferences(void);
