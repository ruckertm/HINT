//
//  Sections.h
//  hintview
//
//  Created by Martin Ruckert on 27.06.22.
//

#import <Foundation/Foundation.h>



@interface Section : NSObject

@property (copy) NSString *name;
@property int itemno;
@property (copy) NSMutableArray *children;

- (id) init;
- (id) initWithName: (NSString *) name item: (int) itemno;
- (void) addChild: (Section *) child;
- (BOOL) isExpandable;
- (NSInteger) numberOfChildren;
- (Section *) childAtIndex: (NSInteger) index;
- (void) clear;

@end


