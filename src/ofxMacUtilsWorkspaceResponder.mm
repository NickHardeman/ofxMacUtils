//
//  ofxMacUtilsWorkspaceResponder.m
//  emptyExample
//
//  Created by Nick Hardeman on 3/10/15.
//
//

#import "ofxMacUtilsWorkspaceResponder.h"
#include "ofxMacUtils.h"

@implementation ofxMacUtilsWorkspaceResponder

- (id) init {
    self = [super init]; //calls init because UIResponder has no custom init methods
    if (self){
        NSNotificationCenter *nc = [[NSWorkspace sharedWorkspace] notificationCenter];
        
        //register for shutdown notications
        [nc addObserver:self
               selector:@selector(computerWillPowerOffotification:)
                   name:NSWorkspaceWillPowerOffNotification object:nil];
        
        
        [nc addObserver:self
               selector:@selector(computerWillSleepNotification:)
                   name:NSWorkspaceWillSleepNotification object:nil];
        
        NSLog(@"ofxMacUtilsWorkspaceResponder :: init ");
        bHasListeners = true;
    }
    
    return self;
}

- (void)dealloc {
    if( bHasListeners ) {
        NSNotificationCenter *nc = [[NSWorkspace sharedWorkspace] notificationCenter];
        [nc removeObserver:self];
        NSLog(@"ofxMacUtilsWorkspaceResponder :: dealloc ");
        bHasListeners = false;
    }
    [super dealloc];
}

- (void)computerWillSleepNotification:(NSNotification *)notification {
    NSLog(@"computerWillSleepNotification name: %@ print out: %@", [notification name], notification );
#ifdef OFX_MAC_UTILS_USE_OBJ_C
    ofxMacUtils::receivedNotificationFromResponder( ofxMacUtils::NS_WS_EVENT_SLEEP );
#endif
}

- (void) computerWillPowerOffotification:(NSNotification *)notification {
    NSLog(@"receiveLogOutShutDownNote name: %@ print out: %@", [notification name], notification );
#ifdef OFX_MAC_UTILS_USE_OBJ_C
    ofxMacUtils::receivedNotificationFromResponder( ofxMacUtils::NS_WS_EVENT_POWER_DOWN );
#endif
}

@end
