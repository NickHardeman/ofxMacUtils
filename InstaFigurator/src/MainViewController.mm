//
//  MainViewController.m
//  ScenesSetup_Nick
//
//  Created by Nick Hardeman on 8/26/14.
//
//

#import "MainViewController.h"
#include "ofApp.h"

@implementation MainViewController

- (void)awakeFromNib {
    
    [super awakeFromNib];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(receiveNotification:)
                                                 name:@"KSImageDroppedNotification"
                                               object:nil];
    
    
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [super dealloc];
}

- (void)update {
//    [networkTableView reloadData];
}

#pragma mark - Notifications
- (void)receiveNotification:(NSNotification *)notification {
    // [notification name] should always be @"TestNotification"
    // unless you use this method for observation of other notifications
    // as well.
    
    if ([[notification name] isEqualToString:@"KSImageDroppedNotification"]) {
        NSLog (@"Successfully received the test notification!");
        NSDictionary *userInfo = (NSDictionary *)[notification userInfo];//@{@"imageFileName" : [files objectAtIndex: 0]};
        NSString* absFilePath = (NSString*)[userInfo objectForKey:@"imageFileName"];
        NSLog(@"dropped file: %@ ", absFilePath );
        NSURL* url = [NSURL fileURLWithPath:absFilePath ];
        NSString* path = [url path];
        NSString* extension = [path pathExtension];
        string extStr = [extension UTF8String];
        
        NSLog(@"extension: %@", extension );
        
        if( extStr == "app" ) {
            ofApp* appPtr = (ofApp*)ofGetAppPtr();
            appPtr->appSelected( [absFilePath UTF8String] );
        }
        
    }
}

- (bool)setupCheckBoxesForParams:(ofParameterGroup&)aParamsGroup {
    for( NSObject* subview in [self.view subviews] ) {
        if( [subview isKindOfClass:[NSButton class]] ) {
            NSButton* button = (NSButton*)subview;
            NSLog(@"Found button with title: %@", [button title] );
            for( int j = 0; j < aParamsGroup.size(); j++ ) {
                if( [[button title] UTF8String] == aParamsGroup.getName(j) ) {
                    if( buttonMap.count(aParamsGroup.getName(j)) == 0 ) {
                        buttonMap[ aParamsGroup.getName(j) ] = button;
                        
                        bool bShouldCheck = false;
                        if( aParamsGroup.get(j).type() == typeid(ofParameter<int>).name() ) {
                            bShouldCheck = aParamsGroup.getInt(j) > 0;
                        } else if( aParamsGroup.get(j).type() == typeid(ofParameter<bool>).name() ) {
                            bShouldCheck = aParamsGroup.get<bool>(j);
                        }
                        
                        if(bShouldCheck) {
                            [button setState:NSOnState];
                        } else {
                            [button setState:NSOffState];
                        }
                        
                        [button setTarget:self];
                        [button setAction:@selector(buttonPressed:)];
                        // only add to the watching params if we found the button //
                        buttonParamsGroup.add( aParamsGroup.get(j) );
                    }
                    break;
                }
            }
        }
    }
    return (buttonParamsGroup.size() == aParamsGroup.size());
}

- (IBAction)buttonPressed:(id)sender {
    [[[ self view] window ] makeFirstResponder: nil];
    [self updateAllTextfieldParams];
    
    NSLog(@"Button has been pressed");
    NSButton* button = (NSButton*)sender;
    string title = [[button title] UTF8String];
    for( int i = 0; i < buttonParamsGroup.size(); i++ ) {
        if( buttonParamsGroup.getName(i) == title ) {
            buttonParamsGroup.get<bool>(i) = [button state];
            NSLog(@"Found the button with name: %@, setting to: %d", [button title], [button state] );
            break;
        }
    }
}

- (void)setCheckBox:(ofParameter<bool>)aParam {
    
    string pName = aParam.getName();
    if( buttonMap.count(pName) > 0 ) {
        NSButton* button = buttonMap[ pName ];
        bool pValue = aParam.get();
//        [textfield setStringValue:[NSString stringWithUTF8String:pValue.c_str()]];
        if(pValue) {
            [button setState:NSOnState];
        } else {
            [button setState:NSOffState];
        }
    }
}

- (void)setCheckBoxEnabled:(ofParameter<bool>)aParam enabled:(bool)bEnabled {
    string pName = aParam.getName();
    if( buttonMap.count(pName) > 0 ) {
        NSButton* button = buttonMap[ pName ];
        if( bEnabled ) {
            [button setEnabled:YES];
        } else {
            [button setEnabled:NO];
        }
    }
}

- (IBAction)selectAppDestButtonPressed:(id)sender {
    ofApp* appPtr = (ofApp*)ofGetAppPtr();
//    appPtr->selectCopyDestinationButtonPressed();
}

- (bool)setupTextfieldsForParams:(ofParameterGroup&)aParamsGroup {
    int tagNum = 1000;
    for( NSObject* subview in [self.view subviews] ) {
        if( [subview isKindOfClass:[NSTextField class]] ) {
            NSTextField* textfield = (NSTextField*)subview;
            NSLog(@"Found textfield with title: %@", [textfield stringValue] );
            for( int j = 0; j < aParamsGroup.size(); j++ ) {
                if( [[textfield stringValue] UTF8String] == aParamsGroup.getName(j) ) {
                    if( textfieldMap.count(aParamsGroup.getName(j)) == 0 ) {
                        textfieldMap[ aParamsGroup.getName(j) ] = textfield;
                        
                        string text = "";
                        if( aParamsGroup.get(j).type() == typeid(ofParameter<string>).name() ) {
                            text = aParamsGroup.get<string>(j);
                        }
                        
                        textfield.tag = tagNum;
                        
                        textfieldTagToNameMap[ tagNum ] = aParamsGroup.getName(j);
                        
                        [textfield setStringValue:[NSString stringWithUTF8String:text.c_str()]];
                        
                        [textfield setTarget:self];
                        [textfield setAction:@selector(textfieldChange:)];
                        
                        textfieldParamsGroup.add( aParamsGroup.get(j) );
                        
                        tagNum++;
                    }
                    
                    break;
                }
            }
        }
    }
    
    return (textfieldParamsGroup.size() == aParamsGroup.size());
}

- (void)updateAllTextfieldParams {
    for( int i = 0; i < textfieldParamsGroup.size(); i++ ) {
        string svalue = textfieldParamsGroup.get<string>(i);
        [textfieldMap[ textfieldParamsGroup.getName(i) ] setStringValue:[NSString stringWithUTF8String:svalue.c_str()]];
    }
}

- (IBAction)textfieldChange:(id)sender {
    NSLog(@"textfield has been pressed");
    NSTextField* textfield = (NSTextField*)sender;
    if( textfieldTagToNameMap.count(textfield.tag) == 0 ) return;
    string pName = textfieldTagToNameMap[ textfield.tag ];
    for( int i = 0; i < textfieldParamsGroup.size(); i++ ) {
        if( textfieldParamsGroup.getName(i) == pName ) {
            textfieldParamsGroup.get<string>(i) = [[textfield stringValue] UTF8String];
            NSLog(@"Found the textfield with name: %@, setting to: %@", [NSString stringWithUTF8String:pName.c_str()], [textfield stringValue] );
            break;
        }
    }
}

- (bool)setTextfieldText:(ofParameter<string>)aParam {
    string pName = aParam.getName();
    if( textfieldMap.count(pName) > 0 ) {
        NSTextField* textfield = textfieldMap[ pName ];
        string pValue = aParam.get();
        [textfield setStringValue:[NSString stringWithUTF8String:pValue.c_str()]];
        return true;
    }
    return false;
}

- (string)getTextfieldText:(ofParameter<string>)aParam {
    string pName = aParam.getName();
    if( textfieldMap.count(pName) > 0 ) {
        NSTextField* textfield = textfieldMap[ pName ];
        return [[textfield stringValue] UTF8String];
    }
    return "";
}



#pragma mark - Setters
- (void)setAppName:(string)aAppName {
    [appname_lb setStringValue:[NSString stringWithUTF8String:aAppName.c_str()] ];
}



#pragma mark - Getters

- (void)setDeskTopBgImagePath:(string)aPath {
    NSString* spath = [NSString stringWithUTF8String:aPath.c_str()];
    NSImage* timage = [[NSImage alloc] initWithContentsOfFile:spath];
    [desktopImageWell setImage:timage];
}
- (void)setLoginImagePath:(string)aPath {
    NSString* spath = [NSString stringWithUTF8String:aPath.c_str()];
    NSImage* timage = [[NSImage alloc] initWithContentsOfFile:spath];
    [loginImageWell setImage:timage];
}

- (void)setAppImagePath:(string)aPath {
    NSString* spath = [NSString stringWithUTF8String:aPath.c_str()];
    NSImage* timage = [[NSImage alloc] initWithContentsOfFile:spath];
    [appImageWell setImage:timage];
}

- (IBAction)applyAllSettings:(id)sender {
    ofApp* appPtr = (ofApp*)ofGetAppPtr();
    appPtr->applySettings();
}

- (IBAction)deskTopBgImageSelected:(id)sender {
//    NSLog(@"Dragged an image into the sender ");
    NSImageView* imageWell = (NSImageView*)sender;
    ofApp* appPtr = (ofApp*)ofGetAppPtr();
    appPtr->desktopImageSelected( [imageWell image] );
}

- (IBAction)loginImageSelected:(id)sender {
    NSImageView* imageWell = (NSImageView*)sender;
    ofApp* appPtr = (ofApp*)ofGetAppPtr();
    appPtr->loginImageSelected( [imageWell image] );
}

-(void)addToConsoleLog:(string)aLogMessage bScroll:(bool)aBScroll {
    NSString *tMess = [NSString stringWithCString:aLogMessage.c_str() encoding:[NSString defaultCStringEncoding]];
    NSMutableAttributedString* attr = [[NSMutableAttributedString alloc] initWithString:tMess];
    
    [attr beginEditing];
    [attr addAttribute:NSForegroundColorAttributeName
                  value:[NSColor lightGrayColor]
                  range:NSMakeRange(0, attr.string.length)];
    [attr endEditing];
    
    [[consoleTextView textStorage] appendAttributedString:attr];
//    [[consoleTextView textStorage] setAttributedString:attr];
    if(aBScroll) {
        [consoleTextView scrollRangeToVisible:NSMakeRange([[consoleTextView string] length], 0)];
    }
}

-(void)trimConsoleString:(int)aNumLines {
    
    NSString* consoleStr = [consoleTextView string];
    NSMutableArray *data = [[consoleStr componentsSeparatedByCharactersInSet: [NSCharacterSet newlineCharacterSet]] mutableCopy];
    
//    NSArray *brokenByLines=[consoleStr componentsSeparatedByString:@"\n"];
    NSString* outStr = @"";
    NSAttributedString* attr = [[NSAttributedString alloc] initWithString:outStr];
    [[consoleTextView textStorage] setAttributedString:attr];
    
    int startIndex = [data count] - aNumLines;
    if( startIndex < 0 ) startIndex = 0;
    for (int i = startIndex; i < [data count]; i++) {
//        if( i >= aNumLines ) break;
        int index = [data count]-1-i;
//        NSAttributedString* attr = [[NSAttributedString alloc] initWithString:outStr];
        NSString* newStr = [data objectAtIndex:i];
        newStr = [newStr stringByAppendingString:@"\n"];
        
        if( [newStr length] > 4 ) {
            NSMutableAttributedString* tattr = [[NSMutableAttributedString alloc] initWithString:newStr];
            [tattr beginEditing];
            [tattr addAttribute:NSForegroundColorAttributeName
                           value:[NSColor lightGrayColor]
                           range:NSMakeRange(0, tattr.string.length)];
            [tattr endEditing];
            [[consoleTextView textStorage] appendAttributedString:tattr];
        }
//        newStr = [newStr stringByAppendingString:@"\n"];
//        outStr = [outStr stringByAppendingString:newStr];
//        outStr = [outStr stringByAppendingString:@"\n"];
    }
    
//    NSAttributedString* attr = [[NSAttributedString alloc] initWithString:outStr];
//    [[consoleTextView textStorage] setAttributedString:attr];
    [consoleTextView scrollRangeToVisible:NSMakeRange([[consoleTextView string] length], 0)];
}


@end
