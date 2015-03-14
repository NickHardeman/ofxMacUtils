//
//  KSImageView.m
//  ScenesSetup_Nick
//
//  Created by Nick Hardeman on 8/26/14.
//
//

#import "KSImageView.h"

@interface KSImageView ()

@end

@implementation KSImageView

- (NSDragOperation)draggingEntered:(id <NSDraggingInfo>)sender
{
    if ((NSDragOperationGeneric & [sender draggingSourceOperationMask]) == NSDragOperationGeneric)
    {
        //this means that the sender is offering the type of operation we want
        //return that we want the NSDragOperationGeneric operation that they
        //are offering
        return NSDragOperationGeneric;
    }
    else
    {
        //since they aren't offering the type of operation we want, we have
        //to tell them we aren't interested
        return NSDragOperationNone;
    }
}

- (NSDragOperation)draggingUpdated:(id <NSDraggingInfo>)sender
{
    if ((NSDragOperationGeneric & [sender draggingSourceOperationMask]) == NSDragOperationGeneric)
    {
        //this means that the sender is offering the type of operation we want
        //return that we want the NSDragOperationGeneric operation that they
        //are offering
        return NSDragOperationGeneric;
    }
    else
    {
        //since they aren't offering the type of operation we want, we have
        //to tell them we aren't interested
        return NSDragOperationNone;
    }
}


- (BOOL)prepareForDragOperation:(id <NSDraggingInfo>)sender {
    return YES;
}

- (BOOL)performDragOperation:(id <NSDraggingInfo>)sender {
    BOOL acceptsDrag = [super performDragOperation:sender];
    
	if (acceptsDrag) {
		NSPasteboard *pboard = [sender draggingPasteboard];
		NSString *plist = [pboard stringForType:NSFilenamesPboardType];
		
		if (plist) {
			
			NSArray *files = [NSPropertyListSerialization propertyListFromData:[plist dataUsingEncoding:NSUTF8StringEncoding]
                                                              mutabilityOption:NSPropertyListImmutable
                                                                        format:nil
                                                              errorDescription:nil];
            
			if ([files count] == 1) {
//				NSDictionary *userInfo = @{@"imageFileName" : [[files objectAtIndex: 0] lastPathComponent]};
                NSDictionary *userInfo = @{@"imageFileName" : [files objectAtIndex: 0]};
                
                NSLog(@"dropped file: %@ ", (NSString*)[userInfo objectForKey:@"imageFileName"] );
                
				[[NSNotificationCenter defaultCenter] postNotificationName:@"KSImageDroppedNotification"
																	object:nil
																  userInfo:userInfo];
			}
		}
	}
	
	return acceptsDrag;
}

- (void) delete:(id)sender {
    
}

- (void) cut:(id)sender {
    
}

@end
