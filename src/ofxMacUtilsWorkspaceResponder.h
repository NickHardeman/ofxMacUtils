//
//  ofxMacUtilsWorkspaceResponder.h
//  emptyExample
//
//  Created by Nick Hardeman on 3/10/15.
//
//

#include <CoreFoundation/CoreFoundation.h>
#ifdef NOT_IN_OF
    #import <Cocoa/Cocoa.h>
#else 
    #include "ofMain.h"
#endif


@interface ofxMacUtilsWorkspaceResponder : NSObject {
    BOOL bHasListeners;
}

- (id)init;
- (void)dealloc;

- (void)computerWillSleepNotification:(NSNotification *)notification;
- (void)computerWillPowerOffotification:(NSNotification *)notification;

@end
