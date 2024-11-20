//
//  SectionsController.m
//  hintview
//
//  Created by Martin Ruckert on 27.06.22.
//

#import "SectionsController.h"
#import "HintOpenGLView.h"
#import "AppDelegate.h"
#include "basetypes.h"
#include "error.h"
#include "hint.h"
#include "main.h"

@implementation SectionsController

static SectionsController *section_outlines=nil;

+ (SectionsController *) sectionOutlines
{return section_outlines; }

- (id) init {
    self = [super init];
    if (self) {
      _root = [[Section alloc] initWithName:@"ROOT" item:0];
    }
    section_outlines=self;
    return self;
}


- (NSInteger) outlineView: (NSOutlineView*) outlineView numberOfChildrenOfItem:(Section*) item
{
    return [(!item? _root: item) numberOfChildren];
}

- (BOOL) outlineView: (NSOutlineView *) outlineView isItemExpandable: (Section *) item
{
    return [(!item? _root: item)  isExpandable];
}

- (Section*) outlineView: (NSOutlineView *) outlineView child: (NSInteger) index ofItem: (Section*) item
{
    return [(!item? _root: item) childAtIndex:index];
    
}
- (id) outlineView: (NSOutlineView *) outlineView objectValueForTableColumn:(nullable NSTableColumn *)tableColumn byItem:(nullable id)item
{
    if ([[tableColumn identifier]isEqualToString:@"name"])
        return [item name];
    else
        return @([item itemno]);
}

- (IBAction)showSection:(NSOutlineView *)sender {
    int i = [[sender itemAtRow:[sender selectedRow]] itemno];
    hint_outline_page(i);
    [[(AppDelegate *)[NSApp delegate] theMainView] setNeedsDisplay:YES];
    //NSLog(@"row %ld",[sender selectedRow]);
    //NSLog(@"name %@", [[sender itemAtRow:[sender selectedRow]] name]);
    //NSLog(@"itemno %d", [[sender itemAtRow:[sender selectedRow]] itemno]);
}

- (Section *) addItem: (NSInteger) itemno withName: (NSString*) name toTree: (Section*) parent
{ Section * child = [[Section alloc] initWithName: name item: (int)itemno ];
  [parent addChild: child];
  return child;
}

static NSInteger currentItem;
static hint_Outline *t;
static int t_max;

-(void) newSubTreeWithParent: (Section *) parent depth: (NSInteger) depth
{ Section * prev= _root;
    while (currentItem<=t_max)
    { if (t[currentItem].depth==depth)
      { prev=[self addItem: currentItem withName: @(t[currentItem].title) toTree: parent];
        currentItem++;
      }
      else if (t[currentItem].depth>depth)
      { [self newSubTreeWithParent:prev depth:t[currentItem].depth];
      }
      else
        break;
    }
    
}

- (void) setSectionTree{
    [self clearSectionTree];

    t_max = hint_get_outline_max();
    if (t_max<0) return;
    t=hint_get_outlines();
    if (t==NULL) return;
    currentItem=0;
    [self newSubTreeWithParent:_root depth:0];
 
}

- (void) clearSectionTree{
    [_root clear];
}



@end
