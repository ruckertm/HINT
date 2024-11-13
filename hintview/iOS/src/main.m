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
//  main.m
//  iOSHintView
//
//  Created by Martin Ruckert on 10.10.22.
//

#import <UIKit/UIKit.h>
#include <stdarg.h>
#import "AppDelegate.h"
#include "error.h"
#include "basetypes.h"
#include "format.h"
#include "get.h"
#include "main.h"

int dark = 0, loading=0, drag=0, autoreload=0, start_autoreload=0, start_home=1, start_showsearch, showsearch=0, start_newwindow=1;
double scale=SCALE_NORMAL, hgamma=GAMMA_NORMAL;
uint64_t pos; /* position of current page */

UIViewController *theViewControler=nil;


bool hint_map(void) /* open hurl_name and map to memory */
{ return hget_map();
}

void hint_unmap(void) /* unmap */
{ hget_unmap();
}


int hint_log(const char * fmt, ... )
{
  va_list  ap;
  va_start( ap, fmt );
    NSLogv([NSString stringWithUTF8String:fmt],ap);
  //vfprintf( stderr, fmt, ap );
  va_end( ap );
    return 0;
}


void hint_message(const char*format,...)
{ va_list vargs;
  va_start(vargs,format);
  NSLogv([NSString stringWithUTF8String: format], vargs);
}

int hint_error(const char*title,const char*msg){
    if (theViewControler!=nil)
    {  static int presenting=0;
        UIAlertController* alert = [UIAlertController alertControllerWithTitle:[NSString stringWithUTF8String: title]
                                       message:[NSString stringWithUTF8String: msg]
                                       preferredStyle:UIAlertControllerStyleAlert];
         
        UIAlertAction* defaultAction = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault
                                                              handler:^(UIAlertAction * action) {
            //NSLog(@"hint_error: Default Action");
            presenting=0;
        }];
       
        [alert addAction:defaultAction];
        if (presenting==0)
        {  presenting =1;
          [theViewControler presentViewController:alert animated:YES completion:nil];
        }
    }
    return 0;
}


int main(int argc, char * argv[]) {
    NSString * appDelegateClassName;
    @autoreleasepool {
        // Setup code that might create autoreleased objects goes here.
        appDelegateClassName = NSStringFromClass([AppDelegate class]);
    }
    hlog=stderr;
    HINT_TRY
    { return UIApplicationMain(argc, argv, nil, appDelegateClassName); }
    else
      hint_error("Error in HintView", hint_error_string);
}
