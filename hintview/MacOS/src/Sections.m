//
//  Sections.m
//  hintview
//
//  Created by Martin Ruckert on 27.06.22.
//

#import "Sections.h"

@implementation Section

- (id) init {
    return [self initWithName:@"Unknown" item:0];
}

- (void) clear {
    _children = nil;
}

- (id) initWithName: (NSString *) name item: (int) itemno
{   self = [super init];
    if (self) {
        _name = [name copy];
        _itemno = itemno;
        _children = nil;
    }
    return self;
}

- (void) addChild: (Section *) child
{
    if (_children==nil) _children=[[NSMutableArray alloc] init];
    [_children addObject: child];
}

- (BOOL) isExpandable{
    return _children!=nil;
}

- (NSInteger) numberOfChildren{
    if (_children==nil) return 0;
    else return [_children count];
}

- (Section *) childAtIndex: (NSInteger) index{
  if (_children==nil) return nil;
  else return [_children objectAtIndex: index];
}


@end
