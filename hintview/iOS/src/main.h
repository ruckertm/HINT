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
