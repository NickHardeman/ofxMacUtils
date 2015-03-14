//
//  ClickToResignView.m
//  WatchDog
//
//  Created by Nick Hardeman on 8/29/14.
//
//

#import "ClickToResignView.h"

@implementation ClickToResignView


- (void)mouseDown:(NSEvent *)event{
    NSLog(@"We have a mouse down event");
    [self.window makeFirstResponder:nil];
}

@end
