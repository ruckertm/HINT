#ifndef _DVI_H_
#define _DVI_H_

extern int dvi_open(char *filename);
extern int dvi_close(void);
extern int dvi_pages; /* toital number of pages */
extern int dvi_page(int n); /* parse page n with 0<= n<pages */

#endif
