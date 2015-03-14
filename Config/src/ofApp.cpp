#include "ofApp.h"
#include "ofAppGLFWWindow.h"

ostream ofApp::ourCoutOut(NULL);

//--------------------------------------------------------------
void ofApp::setup() {
    
#ifdef OF_RELEASE
    ofSetDataPathRoot("../Resources/");
#endif
    
    ofxMacUtils::enablePrintToConsole();
    ourCoutOut.rdbuf(cout.rdbuf());
    cout.rdbuf( ourCoutIn.rdbuf() );
    cerr.rdbuf( ourCoutIn.rdbuf() );

    mainViewController = nil;
    
    
    ofSetFrameRate( 60 );
    ofBackground(60, 60, 60);
    
    paramsGroup.add( appToMonitor.set("Monitoring App", "None"));
    paramsGroup.add( bAddAsLoginItem.set("Add As Login Item", true));
    paramsGroup.add( bDisableScreenSaver.set("Screensaver", true ));
    paramsGroup.add( bDisableSoftwareUpdates.set("Software Updates", true ));
    paramsGroup.add( bDisableGateKeeper.set("Gate Keeper", true ));
    paramsGroup.add( bDisableSleepSettings.set("Sleep Settings", true));
    paramsGroup.add( bDisableSendDiagnostics.set("Send Diagnostics", true ));
    paramsGroup.add( bScreenSharing.set("Screen Sharing", true ));
    paramsGroup.add( bDisableFirewall.set( "Firewall", true ));
    paramsGroup.add( bDisableNotificationCenter.set("Notification Center", true ));
    paramsGroup.add( bDisableCrashReporterDialog.set("Crash Dialog", true ));
    paramsGroup.add( bDisableBluetooth.set("Bluetooth", true ));
    paramsGroup.add( bDisableBluetoothAssistant.set("Bluetooth Assist", true ));
    
    paramsGroup.add( bDisableWIFI.set("WIFI", false ));
    
    paramsGroup.add( bSetDesktopImage.set("Desktop Image", true ));
    paramsGroup.add( bSetLoginImage.set("Login Image", true ));

    paramsGroup.add( bRestartOnPowerFailure.set("Restart On Power Failure", true ));
    paramsGroup.add( bSetComputerName.set("Computer Name", false ));
    
    rootPassword.set( "RootPW", "" );
    
    // don't need to save this //
    ipAddress.set("Set IP Address", "1.1.1.1");
    computerName.set("Computers Name", ofxMacUtils::getComputerName() );
    computerLocalHostname.set("Computers Local Hostname", ofxMacUtils::getComputerLocalHostName() );
    currentUserName.set("Current Username", ofxMacUtils::getCurrentUsername() );
    
    
    paramsGroup.add( desktopImagePath.set("DesktopImagePath", "DesktopBgImage.png" ) );
    loginImagePath.set("LoginImagePath", "LoginImage.png" );
    
    bGenerateDesktopImage.set("Generate Desktop", false );
    
    appIconImagePath.set("AppToMonitorIcon", "AppToMonitorIcon.png" );
    ofFile tappIconFileTemp( appIconImagePath );
    if( !tappIconFileTemp.exists() || (tappIconFileTemp.getExtension() != "png" && tappIconFileTemp.getExtension() != "jpg") ) {
        appIconImagePath = "AppToMonitorIcon-Default.png";
    }
    
    
    ofxMacUtilsSimpleSettings::loadAppSettings("app_settings.xml");
    
    ofxMacUtilsSimpleSettings::getAppSettings( paramsGroup );
    
    rootPassword = ofxMacUtilsSimpleSettings::getAppSetting( rootPassword );
    if( rootPassword.get() != "" ) {
        rootPassword = encryption.getEncrypted( rootPassword, false );
        
    }
    
    // http://www.mactricksandtips.com/2008/02/top-50-terminal-commands.html
    // change the login image //
    // defaults write /Library/Preferences/com.apple.loginwindow DesktopPicture "/System/Library/CoreServices/Finder.app/Contents/Resources/vortex.png"
    
    // This disables the quit dialog box when an application crashes. Type prompt to enable again.
    // defaults write com.apple.CrashReporter DialogType none
    
    // change the background image
    // defaults write com.apple.desktop Background Ò{default = {ImageFilePath=Õ$WLPRÕ; };}Ó; killall Dock
    
    // http://www.macosxtips.co.uk/index_files/terminal-commands-for-hidden-mac-os-x-settings.php
    // defaults write com.apple.CrashReporter DialogType none
    
    // good system functions
    // https://developer.apple.com/library/mac/documentation/Darwin/Reference/Manpages/man8/systemsetup.8.html
    
    
    if( appToMonitor.get() != "" ) {
        appToMonitorFile = appToMonitor.get();
    } else {
        appToMonitorFile.close();
    }
    
    if( !appToMonitorFile.exists() ) {
        appToMonitorFile.close();
    }
    
    
    NSWindow* nswin =  (NSWindow*)((ofAppGLFWWindow*)ofGetWindowPtr())->getCocoaWindow();
    mainViewController = [[MainViewController alloc] initWithNibName:@"MainView" bundle:nil];
    
    if( mainViewController != nil ) {
        if( nswin != nil ) {
            NSSize size = [mainViewController view].frame.size;
            ofSetWindowShape( size.width, size.height );
            [nswin setContentView:[mainViewController view]];
        }
    }
    
    ofxMacUtilsSimpleSettings::loadWindowPosition();
    
    
    ofParameterGroup checkBoxGroup;
    checkBoxGroup.add( bAddAsLoginItem );
    checkBoxGroup.add( bDisableScreenSaver );
    checkBoxGroup.add( bDisableSoftwareUpdates );
    checkBoxGroup.add( bDisableGateKeeper );
    checkBoxGroup.add( bDisableSleepSettings );
    checkBoxGroup.add( bDisableSendDiagnostics );
    checkBoxGroup.add( bSetDesktopImage );
    checkBoxGroup.add( bSetLoginImage );
    checkBoxGroup.add( bDisableNotificationCenter );
    checkBoxGroup.add( bDisableCrashReporterDialog );
    checkBoxGroup.add( bDisableBluetoothAssistant );
    checkBoxGroup.add( bRestartOnPowerFailure );
    checkBoxGroup.add( bSetComputerName );
    checkBoxGroup.add( bScreenSharing );
    checkBoxGroup.add( bDisableFirewall );
    checkBoxGroup.add( bDisableBluetooth );
    checkBoxGroup.add( bDisableWIFI );
    checkBoxGroup.add( bGenerateDesktopImage );
    
    ofParameterGroup textfieldGroup;
    
    textfieldGroup.add( rootPassword );
    
    textfieldGroup.add( ipAddress );
    textfieldGroup.add( computerName );
    textfieldGroup.add( computerLocalHostname );
    textfieldGroup.add( currentUserName );
    
    if( mainViewController != nil ) {
        [mainViewController setupCheckBoxesForParams:checkBoxGroup];
        [mainViewController setupTextfieldsForParams:textfieldGroup];
    }
    
    ofFile dfile = desktopImagePath.get();
    if( dfile.exists() ) {
        if( mainViewController!= nil ) {
            [mainViewController setDeskTopBgImagePath:dfile.getAbsolutePath()];
        }
    }
    
    dfile.close();
    dfile = loginImagePath.get();
    if( dfile.exists() ) {
        if( mainViewController!= nil ) {
            [mainViewController setLoginImagePath:dfile.getAbsolutePath()];
        }
    }
    
    dfile.close();
    dfile = appIconImagePath.get();
    if( dfile.exists() ) {
        if( mainViewController!= nil ) {
            [mainViewController setAppImagePath:dfile.getAbsolutePath()];
        }
    }
    
    
    string tuser = ofxMacUtilsSimpleSettings::getAppSettingS("User");
    string cuser = getenv("USER");
    
    if( tuser != cuser ) {
        rootPassword = "";
    }
    
    
}

#pragma mark - Update
//--------------------------------------------------------------
void ofApp::update() {
    
    string curCoutBuffer = ourCoutIn.str();
    
    ofStringReplace(curCoutBuffer, "\r\n", "\n");
    vector <string> arr = ofSplitString(curCoutBuffer, "\n", true, true);
    
    for(int i = 0; i < arr.size(); i++){
        ourCoutOut << arr[i] << endl;
    }
    
//    string annoyingOSXBugStr = "dyld: DYLD_ environment variables being ignored because main executable (/bin/ps) is setuid or setgid\n";
    if( mainViewController != nil ) {
        if( curCoutBuffer.length() > 10 ) {
            bool bShouldScroll = ofGetFrameNum() % 4 == 0 ? true : false;
            [mainViewController addToConsoleLog:curCoutBuffer bScroll:true];
        }
        
        if( ofGetFrameNum() % (60 * 3) == 0 ) {
            [mainViewController trimConsoleString:400];
        }
    }
    
    
    ourCoutIn.str( std::string() );
    ourCoutIn.clear();

    
    if( appToMonitorFile.getExtension() != "app" ) {
        appToMonitorFile.close();
//        appToMonitor = "";
    }
    
    if( mainViewController != nil ) {
        
        if( ofGetFrameNum() % 30 == 0 ) {
            ipAddress = ofxMacUtils::getIpAddress();
        }
        
        [mainViewController setTextfieldText:ipAddress];
        
        if( ofGetFrameNum() % 10 == 0) [mainViewController update];
        
    }
    
    if(appToMonitorFile.exists() && ofGetFrameNum() % 60 == 0 ) {
        if( mainViewController != nil ) {
            [mainViewController setAppName:appToMonitorFile.getBaseName()];
        }
    }
    
    
    if( bGenerateDesktopImage ) {
        createDesktopImageFromWithString( ofxMacUtils::getComputerName() );
        bGenerateDesktopImage = false;
    }
    
    if( mainViewController != nil ) {
        [mainViewController setCheckBox:bGenerateDesktopImage];
    }
    
}

//--------------------------------------------------------------
void ofApp::draw() {
    
    
}

//--------------------------------------------------------------
void ofApp::exit() {
    
    string tuser = getenv("USER");
    ofxMacUtilsSimpleSettings::addAppSetting( "User", tuser );
    
    string tpw = encryption.getEncrypted( rootPassword, true );
    if( rootPassword.get() == "" ) {
        ofxMacUtilsSimpleSettings::addAppSetting( rootPassword.getName(), rootPassword );
    } else {
        ofxMacUtilsSimpleSettings::addAppSetting( rootPassword.getName(), tpw );
    }
    
    ofxMacUtilsSimpleSettings::addAppSettings( paramsGroup );
    ofxMacUtilsSimpleSettings::saveAppSettings( "app_settings.xml" );
    
    if( mainViewController != nil ) {
        [mainViewController release];
        mainViewController = nil;
    }
    
    cout << "xxxxxxxx Exit xxxxxxxxxxxxxxxxxxxxx " << endl;
}

//--------------------------------------------------------------
void ofApp::applySettings() {
    
    if( rootPassword.get() == "" ) {
        rootPassword = ofSystemTextBoxDialog("Enter root admin password for computer.");
        if( mainViewController != nil ) {
            [mainViewController setTextfieldText:rootPassword];
        }
    }
    
    ofFile tfile = desktopImagePath.get();
    if(tfile.exists() && bSetDesktopImage) ofxMacUtils::setDesktopImage( ofToDataPath(desktopImagePath, true) );
    
    tfile.close();
    tfile = loginImagePath.get();
    if(tfile.exists() && bSetLoginImage) ofxMacUtils::setLoginImage( ofToDataPath(loginImagePath,true) );
    
    
    
    
    
    if( bSetComputerName ) {
        if( mainViewController != nil ) {
            if( [mainViewController getTextfieldText:computerName] != "" ) {
                computerName = [mainViewController getTextfieldText:computerName];
                ofxMacUtils::setComputerName( rootPassword, computerName );
            }
        }
    }
    
    if( bDisableNotificationCenter ) ofxMacUtils::setNotificationCenter( false );
    if( bDisableCrashReporterDialog ) ofxMacUtils::setCrashReporterDialog( false );
    
    if( bDisableScreenSaver ) ofxMacUtils::setScreenSaverStartTime( 0 );
    if( bDisableSoftwareUpdates ) ofxMacUtils::setSoftwareUpdates( rootPassword, false );
    if( bDisableSleepSettings ) ofxMacUtils::setSleep( rootPassword, false );
    if( bDisableSendDiagnostics ) ofxMacUtils::setSendDiagInfo( rootPassword, false );
    if( bDisableGateKeeper ) ofxMacUtils::setGateKeeper( rootPassword, false );
    if( bDisableBluetooth ) ofxMacUtils::setBluetooth( rootPassword, false );
    if( bDisableBluetoothAssistant ) ofxMacUtils::setBluetoothSeupAssistant( rootPassword, false );
    if( bDisableFirewall ) ofxMacUtils::setFireWall( rootPassword, false );
    if( bDisableWIFI ) ofxMacUtils::setWifiPower( false );
    
    
    if( bScreenSharing ) ofxMacUtils::setScreenSharing( rootPassword, true );
    if( bRestartOnPowerFailure ) ofxMacUtils::restartOnPowerFailure( rootPassword, true );
    if( bAddAsLoginItem ) {
        if( appToMonitorFile.exists() ) {
            if( !ofxMacUtils::isApplicationALoginItem( appToMonitorFile.getBaseName() )) {
                ofxMacUtils::addApplicationToLoginItems( appToMonitorFile.getAbsolutePath(), false );
                
            }
        }
    }
    
    currentUserName = ofxMacUtils::getCurrentUsername();
    [mainViewController setTextfieldText:currentUserName];
    
    ofSystemAlertDialog("Settings Applied");
}

//--------------------------------------------------------------
void ofApp::saveIconImageForApp( string aAppPath, string aIconPath, int aSize ) {
    
    NSString *path = [NSString stringWithUTF8String:aAppPath.c_str()];
    NSImage *image = [[NSWorkspace sharedWorkspace] iconForFile:path];
    
    [image setSize:NSMakeSize(aSize, aSize)];
    
    CGImageRef cgRef = [image CGImageForProposedRect:NULL
                                             context:nil
                                               hints:nil];
    NSBitmapImageRep *newRep = [[NSBitmapImageRep alloc] initWithCGImage:cgRef];
    NSData *pngData = [newRep representationUsingType:NSPNGFileType properties:nil];
    
    string absIconPath = ofToDataPath( aIconPath, true );
    NSString* iconPath = [NSString stringWithUTF8String:absIconPath.c_str()];
    [pngData writeToFile:iconPath atomically:NO];
    [newRep autorelease];
}

//--------------------------------------------------------------
void ofApp::desktopImageSelected( NSImage* aImage ) {
    
    ofFile tfile = desktopImagePath.get();
    if( tfile.exists() && tfile.getExtension() == "png" && ofIsStringInString( desktopImagePath, "DesktopBgImage") ) {
        ofFile::removeFile( tfile.getAbsolutePath() );
    }
    
    desktopImagePath = "DesktopBgImage-"+ofGetTimestampString()+".png";
    ofxMacUtils::saveNsImage( aImage, desktopImagePath, true );
    if(bSetDesktopImage) ofxMacUtils::setDesktopImage( ofToDataPath(desktopImagePath, true) );
}

//--------------------------------------------------------------
void ofApp::loginImageSelected( NSImage* aImage ) {
    cout << "SHould be saving the login Image: " << loginImagePath << endl;
    ofxMacUtils::saveNsImage( aImage, loginImagePath, true, 512, 512 );
    if(bSetLoginImage) ofxMacUtils::setLoginImage( ofToDataPath(loginImagePath,true) );
}

//--------------------------------------------------------------
void ofApp::appSelected( string aAbsPath ) {
    // string aAppPath, string aIconPath, int aSize
    
    if( ofIsStringInString(appIconImagePath, "Default") ) {
        appIconImagePath = "AppToMonitorIcon.png";
    }
    
    saveIconImageForApp( aAbsPath, appIconImagePath, 256 );
    if( mainViewController != nil ) {
        [mainViewController setAppImagePath:ofToDataPath(appIconImagePath, true)];
    }
    appToMonitor        = aAbsPath;
    appToMonitorFile    = aAbsPath;
}

//--------------------------------------------------------------
void ofApp::createDesktopImageFromWithString( string aString ) {
    ofFbo tfbo;
    tfbo.allocate( 1920, 1200 );
    tfbo.begin();
    ofClear(0, 0, 0, 0);
    ofSetColor( 100, 100, 100 );
    ofRect(0, 0, tfbo.getWidth(), tfbo.getHeight() );
    ofSetColor( 200, 200, 200 );
    ofTrueTypeFont tfont;
    tfont.loadFont("frabk.ttf", 62 );
    tfont.drawString( aString, 100, 800 );
    tfbo.end();
    
    ofFile tfile = desktopImagePath.get();
    if( tfile.exists() && tfile.getExtension() == "png" && ofIsStringInString( desktopImagePath, "DesktopBgImage") ) {
        ofFile::removeFile( tfile.getAbsolutePath() );
    }
    
    desktopImagePath = "DesktopBgImage-"+ofGetTimestampString()+".png";
    ofTexture& ttex = tfbo.getTextureReference();
    ofPixels tpix;
    ttex.readToPixels( tpix );
    ofSaveImage( tpix, desktopImagePath );
    
    ofFile dfile = desktopImagePath.get();
    if( dfile.exists() ) {
        if( mainViewController!= nil ) {
            [mainViewController setDeskTopBgImagePath:dfile.getAbsolutePath()];
        }
    }
}

#pragma mark - Keyboard
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

#pragma mark - Mouse
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
    
}











