//
//  SectionsController.h
//  hintview
//
//  Created by Martin Ruckert on 27.06.22.
//

#import <Cocoa/Cocoa.h>
#import "Sections.h"



@interface SectionsController : NSTreeController <NSOutlineViewDataSource>

@property (copy) Section *root;

+ (SectionsController *) sectionOutlines;

- (IBAction)showSection:(id)sender;

- (Section *) addItem: (NSInteger) i withName: (NSString*) name toTree: (Section*) parent;

-(void) newSubTreeWithParent: (Section *) parent depth: (NSInteger) depth;

- (void) clearSectionTree;

- (void) setSectionTree;
@end


