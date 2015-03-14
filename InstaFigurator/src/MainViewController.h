//
//  EmailViewController.h
//  ScenesSetup_Nick
//
//  Created by Nick Hardeman on 8/26/14.
//
//

#include "ofMain.h"
#include "KSImageView.h"
#include <map>

@interface MainViewController : NSViewController {
    
    IBOutlet NSImageView* desktopImageWell;
    IBOutlet NSImageView* loginImageWell;
    IBOutlet KSImageView* appImageWell;
    
    IBOutlet NSTextField* appname_lb;
    IBOutlet NSTextField* appstatus_tf;
    
//    IBOutlet NSTableView* networkTableView;
    IBOutlet NSTextView* consoleTextView;
    
    map< string, NSButton* > buttonMap;
    ofParameterGroup buttonParamsGroup;
    
    map< string, NSTextField* > textfieldMap;
    map< int, string > textfieldTagToNameMap;
    ofParameterGroup textfieldParamsGroup;
    
}

- (void)update;

- (void)receiveNotification:(NSNotification *)notification;

- (bool)setupCheckBoxesForParams:(ofParameterGroup&)aParamsGroup;
- (IBAction)buttonPressed:(id)sender;
- (void)setCheckBox:(ofParameter<bool>)aParam;
- (void)setCheckBoxEnabled:(ofParameter<bool>)aParam enabled:(bool)bEnabled;

- (bool)setupTextfieldsForParams:(ofParameterGroup&)aParamsGroup;
- (void)updateAllTextfieldParams;
- (IBAction)textfieldChange:(id)sender;
- (bool)setTextfieldText:(ofParameter<string>)aParam;
- (string)getTextfieldText:(ofParameter<string>)aParam;

- (void)setDeskTopBgImagePath:(string)aPath;
- (void)setLoginImagePath:(string)aPath;
- (void)setAppImagePath:(string)aPath;

- (void)setAppName:(string)aAppName;

- (IBAction)applyAllSettings:(id)sender;

- (IBAction)deskTopBgImageSelected:(id)sender;
- (IBAction)loginImageSelected:(id)sender;

-(void)addToConsoleLog:(string)aLogMessage bScroll:(bool)aBScroll;
-(void)trimConsoleString:(int)aNumLines;

@end
