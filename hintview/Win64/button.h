#ifndef _BUTTON_H_
#define _BUTTON_H_

#define BUTTON_MENU 0
#define BUTTON_SETTINGS 1
#define BUTTON_NIGHT 2
#define BUTTON_ZOOM 3
#define BUTTON_PREV 4
#define BUTTON_NEXT 5
#define BUTTON_HELP 6
#define BUTTON_SEARCH 7 
#define BUTTON_NAVIGATE 8
#define BUTTON_HOME 9

extern void init_button_class(void);
extern void show_buttons(int cmd);
extern void buttons_change(void);
extern void button_pos(int i, POINT *p);
#endif