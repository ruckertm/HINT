//
//  PrintView.m
//  hintview
//
//  Created by Martin Ruckert on 04.07.22.
//

#import "PrintView.h"
#import "HintOpenGLView.h"
#include "rendernative.h"
#include "hrender.h"
#import "main.h"
@implementation PrintView

static NSBitmapImageRep *bits;
static double w_pt, h_pt, w_in, h_in, w_dpi, h_dpi;
static NSInteger w_px, h_px;
static int bpr, bpp;
static unsigned char *bitdata;
static int total_pages;

#define MAX_PAGES 1024

uint64_t page_tops[MAX_PAGES];

void pagination(void)
{ uint64_t pos;
  total_pages=0;
  hint_resize((int)w_px,(int)h_px,w_dpi,h_dpi);
  pos = hint_page_top(0);
  page_tops[total_pages++]=pos;
  while (1) {
    pos=hint_page_next();
    if (pos>page_tops[total_pages-1])
        page_tops[total_pages++]=pos;
    else break;
  }
}

- (id)initWithFrame:(NSRect)paperSize
{   self= [super initWithFrame: paperSize];
    
    //NSLog(@"Print view %fin x %fin",w_in,h_in);
    w_pt=paperSize.size.width;
    w_in=w_pt/72.0;
    h_pt=paperSize.size.height;
    h_in=h_pt/72.0;
    w_dpi=h_dpi=300.0;
    w_px=w_in*w_dpi+0.5;
    h_px=h_in*h_dpi+0.5;
    NSPoint o;
    o.x=0; o.y=0;
    NSSize s;
    s.width=w_pt; s.height=h_pt;
    [self setBoundsOrigin: o];
    [self setBoundsSize:s];
    
    bits= [NSBitmapImageRep alloc];
    [bits initWithBitmapDataPlanes:NULL
          pixelsWide:w_px
          pixelsHigh:h_px
          bitsPerSample:8 samplesPerPixel:4
          hasAlpha:YES isPlanar:NO
          colorSpaceName:NSDeviceRGBColorSpace
          bytesPerRow:w_px*4 bitsPerPixel:0];
    bitdata = [bits bitmapData];
    bpr=(int)[bits bytesPerRow];
    bpp=(int)[bits samplesPerPixel];
    w_px=bpr/bpp;  /* possible adjustment */

    pagination();
    return self;
}


- (void)drawRect:(NSRect)rect {
    if (bits!=nil)
    {   hint_render();
        nativePrint([bits bitmapData]);
        [bits drawInRect:rect];
    }
    //NSLog(@"PrintView drawRect:\n");
}


// Return the number of pages available for printing
- (BOOL)knowsPageRange:(NSRangePointer)range {
    range->location = 1;
    range->length = total_pages;
    return YES;
}


// Return the drawing rectangle for a particular page number
- (NSRect)rectForPage:(NSInteger)page {
    if (page>0 && page<=total_pages)
        hint_page_top(page_tops[page-1]);
    return NSMakeRect( 0, 0, w_pt, h_pt);
}
 
- (void) beginDocument
{ [super beginDocument];
  NSPrintOperation *op = [NSPrintOperation currentOperation];
  NSPrintInfo *pInfo = [op printInfo];
  [pInfo setHorizontalPagination:NSClipPagination];
  [pInfo setVerticalPagination:NSClipPagination];
    
#if 0 // runs but gives only 72x72 resolution
    PMResolution res;
    UInt32    countP;
    PMPrintSession printSession;
        PMPrinter printer;
    //int tag = 0;// kPMMaxSquareResolution;
    printSession=[pInfo PMPrintSession];
       //PMCreateSession(&printSession);
    PMSessionGetCurrentPrinter(printSession, &printer);
    PMPrinterGetPrinterResolutionCount(printer,&countP);
    int i;
    for (i=0;i<countP;i++)
    { PMPrinterGetIndexedPrinterResolution(printer, 0, &res);
        NSLog(@"resolution %d: %fx%f dpi", i, res.hRes, res.vRes);
    }
#endif
    
    [pInfo setTopMargin:0.0];
    [pInfo setLeftMargin:0.0];
    [pInfo setRightMargin:0.0];
    [pInfo setBottomMargin:0.0];
    NSRect r = [pInfo imageablePageBounds];
    

    nativePrintStart(bpr/bpp,(int)h_px, bpr, bpp, bitdata);
    nativeSetGamma(1.0);
    nativeSetDark(0);
    hint_clear_fonts(true);
    //NSLog(@"Begin print");
}

- (void) endPage
{ [super endPage];
  //  NSLog(@"end page");
}

- (void) endDocument
{  [super endDocument];
    nativePrintEnd();
    nativeSetDark(dark);
    nativeSetGamma(hgamma);
    //NSLog(@"End print");
}
@end
