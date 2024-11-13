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
//  main.h
//  iOSHintView
//
//  Created by Martin Ruckert on 27.10.22.
//

#ifndef main_h
#define main_h

#define VERSION 1
#define REVISION 3
#define PATCHLEVEL 0


extern int dark, loading, drag, start_autoreload, autoreload, start_home,
           start_showsearch, showsearch, start_newwindow;

#define SCALE_MIN 0.2
#define SCALE_NORMAL 1.0
#define SCALE_MAX 5.0
#define GAMMA_MIN 0.4
#define GAMMA_NORMAL 1.8
#define GAMMA_MAX 4.0



extern double scale, hgamma;
extern uint64_t pos; /* position of current page */


extern int hint_log(const char *fmt, ... );
extern void hint_message(const char*format,...);
extern int hint_error(const char*title,const char*msg);

extern UIViewController *theViewControler;

#endif /* main_h */
