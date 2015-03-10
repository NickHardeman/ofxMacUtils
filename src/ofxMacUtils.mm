//
//  MacUtils.cpp
//  ScenesSetup_Nick
//
//  Created by Nick Hardeman on 8/26/14.
//

#include "ofxMacUtils.h"
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <sys/socket.h>

bool ofxMacUtils::bPrintToConsole = false;
#ifdef OFX_MAC_UTILS_USE_OBJ_C
list< ofxMacUtilsWorkpaceNotificationsListener* > ofxMacUtils::wsListeners;
ofxMacUtilsWorkspaceResponder* ofxMacUtils::nsWSResponder = nil;
#endif

//----------------------------------------
string ofxMacUtils::executeSystemCommand(string cmd) {
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return "ERROR";
    char buffer[2048];
    string result = "";
    while(!feof(pipe)) {
        if(fgets(buffer, 2048, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    if( isPrintToConsoleEnabled() ) {
        cout << result << endl;
    }
    return result;
}

//----------------------------------------
string ofxMacUtils::executeSystemCommand(string cmd, string aSystemPassword ) {
    if( aSystemPassword != "" ) {
        string command = "echo "+aSystemPassword+" | sudo -S "+cmd;
        return executeSystemCommand( command );
    }
    
    string result = "ERROR :: executeSystemCommand : password is empty";
    if( isPrintToConsoleEnabled() ) {
        cout << result << endl;
    }
    return result;
}

//----------------------------------------------------------
vector< ofxMacUtils::NetworkDeviceInfo > ofxMacUtils::getNetworkDeviceInfos() {
    vector< ofxMacUtils::NetworkDeviceInfo > infos;
#ifdef TARGET_OSX
    struct ifaddrs* interfaces = NULL;
    struct ifaddrs* temp_addr = NULL;
    
    // retrieve the current interfaces - returns 0 on success
    int success = getifaddrs(&interfaces);
    if (success == 0) {
        // Loop through linked list of interfaces
        temp_addr = interfaces;
        while (temp_addr != NULL) {
            // internetwork only
            if (temp_addr->ifa_addr->sa_family == AF_INET) {
                string name = temp_addr->ifa_name;
                string address = inet_ntoa(((struct sockaddr_in *)temp_addr->ifa_addr)->sin_addr);
                string subnet = inet_ntoa(((struct sockaddr_in *)temp_addr->ifa_netmask)->sin_addr);

                unsigned int flags = temp_addr->ifa_flags;
                infos.push_back( ofxMacUtils::NetworkDeviceInfo( name, address, subnet ) );
                
//                cout << "name :: address " << name << " : " << address << endl;
            }
            temp_addr = temp_addr->ifa_next;
        }
    }
    
    // Free memory
    freeifaddrs(interfaces);
#endif
    return infos;
}

//----------------------------------------------------------
string ofxMacUtils::getIpAddress() {
    string tipAddres = "1.1.1.1";
    vector< ofxMacUtils::NetworkDeviceInfo > infos = getNetworkDeviceInfos();
    for( int i = 0; i < infos.size(); i++ ) {
        if( infos[i].name.find( "en" ) != string::npos ) {
            tipAddres = infos[i].address;
            break;
        }
    }
    return tipAddres;
}

//----------------------------------------------------------
string ofxMacUtils::getSubnet() {
    string subnet = "255.255.255.0";
    vector< ofxMacUtils::NetworkDeviceInfo > infos = getNetworkDeviceInfos();
    for( int i = 0; i < infos.size(); i++ ) {
        if( infos[i].name.find( "en" ) != string::npos ) {
            subnet = infos[i].subnet;
            break;
        }
    }
    return subnet;
}

// http://stackoverflow.com/questions/13279220/how-do-i-get-the-currently-connected-network-interface-name-using-cocoa-or-found
//----------------------------------------------------------
bool ofxMacUtils::isNetworkAvailable() {
    bool bRet = false;
    vector< ofxMacUtils::NetworkDeviceInfo > infos = getNetworkDeviceInfos();
    for( int i = 0; i < infos.size(); i++ ) {
        if( infos[i].name.find( "en" ) != string::npos ) {
            bRet = true;
            break;
        }
    }
    
    return bRet;
}

// http://www.dgkapps.com/blog/osx-tips/osx-tips-turn-off-wifi-from-the-command-line/
//----------------------------------------------------------
string ofxMacUtils::getCurrentWifiPort() {
    //    CURRENT_DEVICE=$(networksetup -listallhardwareports | awk '$3=="Wi-Fi" {getline; print $2}')
    string command = "networksetup -listallhardwareports | awk '$3==\"Wi-Fi\" {getline; print $2}'";
    string res = executeSystemCommand( command );
    ofStringReplace( res, "\r", "");
    ofStringReplace( res, "\n", "");
    return res;
}

//----------------------------------------------------------
void ofxMacUtils::setWifiPower( bool bOn ) {
    //    networksetup -setairportpower en1 off
    string command = "networksetup -setairportpower "+getCurrentWifiPort()+" "+ofToString( bOn?"on":"off" );
    cout << "isWifi On: " << getWifiPower() << endl;
    string res = executeSystemCommand( command );
}

//----------------------------------------------------------
bool ofxMacUtils::getWifiPower() {
    string command = "networksetup -getairportpower "+getCurrentWifiPort();
    string res = executeSystemCommand( command );
    ofStringReplace( res, "\r", "");
    ofStringReplace( res, "\n", "");
    res = ofToLower(res);
    return ofIsStringInString( res, "on");
}

//----------------------------------------------------------
void ofxMacUtils::setComputerName( string aSystemPassword, string aName ) {
//    ofStringReplace( aName, " ", "\n");
//    ofStringReplace( aName, " ", "\r");
    ofStringReplace( aName, " ", "\\ ");
    ofStringReplace( aName, "'", "\\'");
    cout << "Trying to set the computer name " << aName << endl;
    string command = "scutil --set ComputerName "+aName;
    string res = executeSystemCommand( command, aSystemPassword );
}

//----------------------------------------------------------
void ofxMacUtils::setComputerLocalHostName( string aSystemPassword, string aName ) {
    ofStringReplace( aName, " ", "-");
    ofStringReplace( aName, "'", "");
    ofStringReplace( aName, "+", "-");
    string command = "scutil --set LocalHostName "+aName;
    string res = executeSystemCommand( command, aSystemPassword );
}

//----------------------------------------------------------
void ofxMacUtils::setComputerHostName( string aSystemPassword, string aName ) {
//    ofStringReplace( aName, " ", "\ ");
    string command = "scutil --set HostName "+aName;
    string res = executeSystemCommand( command, aSystemPassword );
}

//----------------------------------------------------------
string ofxMacUtils::getComputerName() {
    string command = "scutil --get ComputerName";
    string res = executeSystemCommand( command );
    ofStringReplace( res, "\r", "");
    ofStringReplace( res, "\n", "");
    return res;
}

//----------------------------------------------------------
string ofxMacUtils::getComputerLocalHostName() {
    string command = "scutil --get LocalHostName";
    string res = executeSystemCommand( command );
    ofStringReplace( res, "\r", "");
    ofStringReplace( res, "\n", "");
    return res;
}

//----------------------------------------------------------
string ofxMacUtils::getComputerHostName() {
    string command = "scutil --get HostName";
    string res = executeSystemCommand( command );
    ofStringReplace( res, "\r", "");
    ofStringReplace( res, "\n", "");
    return res;
}

// http://apple.stackexchange.com/questions/47503/how-to-control-bluetooth-wireless-radio-from-the-command-line
//----------------------------------------------------------
void ofxMacUtils::setBluetooth( string aSystemPassword, bool bEnable ) {
    //    sudo defaults write /Library/Preferences/com.apple.Bluetooth ControllerPowerState -bool FALSE
    //    sudo launchctl unload /System/Library/LaunchDaemons/com.apple.blued.plist
    //    sudo launchctl load /System/Library/LaunchDaemons/com.apple.blued.plist
    string command;
    if( bEnable ) {
        command = "defaults write /Library/Preferences/com.apple.Bluetooth ControllerPowerState -bool TRUE";
    } else {
        command = "defaults write /Library/Preferences/com.apple.Bluetooth ControllerPowerState -bool FALSE";
    }
    string res = executeSystemCommand( command, aSystemPassword );
    command = "launchctl unload /System/Library/LaunchDaemons/com.apple.blued.plist";
    executeSystemCommand( command, aSystemPassword );
    command = "launchctl load /System/Library/LaunchDaemons/com.apple.blued.plist";
    res += executeSystemCommand( command, aSystemPassword );
}

// http://alblue.bandlem.com/2013/10/disabling-osx-bluetooth.html
//----------------------------------------------------------
void ofxMacUtils::setBluetoothSeupAssistant( string aSystemPassword, bool bEnable ) {
    string command = "defaults write /Library/Preferences/com.apple.Bluetooth BluetoothAutoSeekKeyboard '"+ofToString(bEnable?"1":"0")+"'";
    string res = executeSystemCommand( command, aSystemPassword );
    
    command = "defaults write /Library/Preferences/com.apple.Bluetooth BluetoothAutoSeekPointingDevice '"+ofToString(bEnable?"1":"0")+"'";
    res += executeSystemCommand( command, aSystemPassword );
}

// http://thisiskindagood.hatenablog.com/entry/2014/07/03/120036
// requires reboot //
//----------------------------------------------------------
void ofxMacUtils::setSendDiagInfo( string aSystemPassword, bool bEnable ) {
    string command = "";
    if( bEnable ) {
        command = "launchctl load -w /System/Library/LaunchDaemons/com.apple.DiagnosticReportCleanUpDaemon.plist";
    } else {
        command = "launchctl unload -w /System/Library/LaunchDaemons/com.apple.DiagnosticReportCleanUpDaemon.plist";
    }
    string res = executeSystemCommand( command, aSystemPassword );
}

#ifdef OFX_MAC_UTILS_USE_OBJ_C
// crashes every once in a while when calling every frame, supposed to register for events //
//--------------------------------------------------------------
NSRunningApplication* ofxMacUtils::getRunningProcess( string aProcessName ) {
    for(NSRunningApplication *currApp in [[NSWorkspace sharedWorkspace] runningApplications]) {
        if( !currApp || currApp == nil ) continue;
        NSString* localString = [currApp localizedName];
        if( [localString isEqual:[NSNull null]] ) continue;
        
        string cappName = [localString UTF8String];
        
        if( cappName == aProcessName ) {
//            NSLog(@"debugdescription: %@", [currApp _activeSeed] );
            return currApp;
        }
    }
    return nil;
}
#endif

//--------------------------------------------------------------
bool ofxMacUtils::isProcessRunning( string aAbsPath ) {
    string command = "ps aux | grep '"+aAbsPath+"' | wc -l";
    string execres = executeSystemCommand( command );
    int numInstances = ofToInt( execres );
    return numInstances > 2;
}

//--------------------------------------------------------------
void ofxMacUtils::openProcess( string aAbsPath ) {
    string command = "open "+aAbsPath+" &";
    system( command.c_str() );
}

//--------------------------------------------------------------
string ofxMacUtils::getProcessId( string aProcessName ) {
    string command = "pgrep "+aProcessName;
    string execres = executeSystemCommand( command );
    ofStringReplace( execres, "\n", "" );
    ofStringReplace( execres, "\r", "" );
    return execres;
}

//--------------------------------------------------------------
bool ofxMacUtils::isApplicationRunning( string aAppName ) {
    string command = "osascript -e 'tell application \"System Events\"' -e 'count (every process whose displayed name is \""+aAppName+"\")' -e 'end tell'";
    string execres = executeSystemCommand( command );
    int res = ofToInt( execres );
    return res > 0;
}

//--------------------------------------------------------------
void ofxMacUtils::runApplication( string aAppName ) {
    string command = "osascript -e 'tell application \""+aAppName+"\" to activate'";
    string execres = executeSystemCommand( command );
}

#ifdef OFX_MAC_UTILS_USE_OBJ_C
// not very efficient //
//--------------------------------------------------------------
string ofxMacUtils::getProcessStatus( string aProcessName ) {
    
    // TODO: Find faster / more reliable way for getting the process ID //
    NSRunningApplication* papp = getRunningProcess( aProcessName );
    if( papp == nil || !papp ) return "terminated";
    
    pid_t pid = [papp processIdentifier];
    
    //    top -l1 -n 1 -pid 48929 -stats "STATE" | tail -n 1 | head -n 1
    string command = "top -l1 -n 1 -pid "+ofToString(pid,0)+" -stats \"STATE\" | tail -n 1 | head -n 1";
    string execres = executeSystemCommand( command );
//    string execres = system( command.c_str() );
    ofStringReplace( execres, "\n", "" );
    ofStringReplace( execres, "\r", "" );
    return execres;
}
#endif

//--------------------------------------------------------------
void ofxMacUtils::setScreenSaverStartTime( float aTimeInSeconds ) {
    //    defaults -currentHost write com.apple.screensaver idleTime 0
    string command = "defaults -currentHost write com.apple.screensaver idleTime "+ofToString( aTimeInSeconds, 0);
    string execres = executeSystemCommand( command );
}

//--------------------------------------------------------------
bool ofxMacUtils::isApplicationALoginItem( string aAppName ) {
    string command = "osascript -e 'tell application \"System Events\" to get the name of every login item'";
    string execres = executeSystemCommand( command );
    //    cout << "isApplicationLoginItem: " << execres << endl;
    return ofIsStringInString( execres, aAppName );
}

//--------------------------------------------------------------
void ofxMacUtils::addApplicationToLoginItems( string aPathToApp, bool bHide ) {
    // osascript -e 'tell application "System Events" to make login item at end with properties {path:"/Users/NickHardeman/Documents/ProjectsDev/ConnectedWorlds/of_v0.8.0_osx_release/apps/Experiments/WatchDog/bin/ScenesSetup_NickDebug.app", hidden:false}'
    string hstr = (bHide ? "true" : "false");
    string command = "osascript -e 'tell application \"System Events\" to make login item at end with properties {path:\""+aPathToApp+"\", hidden:"+hstr+"}'";
    string execres = executeSystemCommand( command );
}

// http://stackoverflow.com/questions/5468074/programmatically-changing-desktop-image
//--------------------------------------------------------------
void ofxMacUtils::setDesktopImage( string aAbsPath ) {
    // defaults write com.apple.desktop Background “{default = {ImageFilePath=’$WLPR’; };}”; killall Dock
    //    string command = "defaults write com.apple.desktop Background \"{default = {ImageFilePath='"+aAbsPath+"'; };}\"; killall Dock";
    //    string execres = exec( command.c_str() );
    
    NSURL* newImageURL = [NSURL fileURLWithPath:[NSString stringWithUTF8String:aAbsPath.c_str()] ];
    
    NSInteger count = [[NSScreen screens] count];
    for( int i = 0; i < count; i++ ) {
        NSScreen* curScreen = [[NSScreen screens] objectAtIndex:i];
        NSMutableDictionary *screenOptions = [[[NSWorkspace sharedWorkspace] desktopImageOptionsForScreen:curScreen] mutableCopy];
        
        //        NSURL* currentImageURL = [[NSWorkspace sharedWorkspace] desktopImageURLForScreen:curScreen];
//        desktopImageURLForScreen
        // setDesktopImageURL:(NSURL *)url forScreen:(NSScreen *)screen options:(NSDictionary *)options error:(NSError **)error 
        NSError *error = nil;
        if (![[NSWorkspace sharedWorkspace] setDesktopImageURL:newImageURL
                                                     forScreen:curScreen
                                                       options:screenOptions
                                                         error:&error]) {
            NSLog(@"Error: %@ %@", error, [error userInfo]);
        }
        
        [screenOptions release];
    }
    
    
    
}

//--------------------------------------------------------------
void ofxMacUtils::setLoginImage( string aAbsPath ) {
    // defaults write /Library/Preferences/com.apple.loginwindow DesktopPicture "/System/Library/CoreServices/Finder.app/Contents/Resources/vortex.png"
    string command = "defaults write /Library/Preferences/com.apple.loginwindow DesktopPicture \""+aAbsPath+"\"";
    string res = executeSystemCommand( command );
}

//--------------------------------------------------------------
void ofxMacUtils::setSoftwareUpdates( string aRootPassword, bool bOn ) {
    // sudo softwareupdate --schedule off
//        string command = "echo "+rootPassword+" | sudo -S softwareupdate --schedule off";
//        system( command.c_str() );
    string command = "softwareupdate --schedule "+ofToString( bOn ? "on":"off");
    string res = executeSystemCommand( command, aRootPassword );
}

//--------------------------------------------------------------
void ofxMacUtils::setSleep( string aRootPassword, bool bOn ) {
//    string command = "echo "+rootPassword+" | sudo -S systemsetup -setsleep off";
//    system( command.c_str() );
    string command = "systemsetup -setsleep "+ofToString(bOn?"on":"off");
    string res = executeSystemCommand( command, aRootPassword );
}

// http://www.cnet.com/news/how-to-manage-os-x-gatekeeper-from-the-command-line/
//--------------------------------------------------------------
void ofxMacUtils::setGateKeeper( string aRootPassword, bool bOn ) {
    // spctl --add --label "MyLabel" /Path/To/program
        //        string command = "echo "+rootPassword+" | sudo -S spctl --add --label \""+aAppFile.getBaseName()+"\" "+aAppFile.getAbsolutePath();
        // spctl --master-disable
//    string command = "echo "+rootPassword+" | sudo -S spctl --master-disable";
//    system( command.c_str() );
    string command = "spctl --master-"+ofToString( bOn?"enable":"disable");
    string res = executeSystemCommand( command, aRootPassword );
}

//--------------------------------------------------------------
void ofxMacUtils::setCrashReporterDialog( bool bEnable ) {
    //    defaults write com.apple.CrashReporter DialogType none
    string cstr = bEnable ? "prompt" : "none";
    string command = "defaults write com.apple.CrashReporter DialogType "+cstr;
    system( command.c_str() );
}

// https://developer.apple.com/library/mac/documentation/Darwin/Reference/Manpages/man8/systemsetup.8.html
//--------------------------------------------------------------
void ofxMacUtils::restartOnPowerFailure( string aRootPassword, bool aYes ) {
    //    setrestartpowerfailure
        //        string command = "echo "+rootPassword+" | sudo -S spctl --add --label \""+aAppFile.getBaseName()+"\" "+aAppFile.getAbsolutePath();
        // spctl --master-disable
    string cstr = aYes ? "on" : "off";
//    string command = "echo "+rootPassword+" | sudo -S systemsetup -setrestartpowerfailure "+cstr;
//    system( command.c_str() );
    string command = "systemsetup -setrestartpowerfailure "+cstr;
    string res = executeSystemCommand( command, aRootPassword );
}

//--------------------------------------------------------------
void ofxMacUtils::setNotificationCenter( bool bEnable ) {
    // http://www.tuaw.com/2014/03/18/how-to-permanently-remove-notification-center-from-os-x/
    // launchctl unload -w /System/Library/LaunchAgents/com.apple.notificationcenterui.plist
    string command;
    if( bEnable ) {
        command = "launchctl load -w /System/Library/LaunchAgents/com.apple.notificationcenterui.plist; killall NotificationCenter; ";
        // might need to open manually open /System/Library/CoreServices/NotificationCenter.app
    } else {
        command = "launchctl unload -w /System/Library/LaunchAgents/com.apple.notificationcenterui.plist";
    }
    system( command.c_str() );
}

//--------------------------------------------------------------
void ofxMacUtils::setScreenSharing( string aRootPassword, bool bEnable ) {
    // http://pivotallabs.com/enabling-os-x-screen-sharing-from-the-command-line/
    string command;
    if( bEnable ) {
        command = "defaults write /var/db/launchd.db/com.apple.launchd/overrides.plist com.apple.screensharing -dict Disabled -bool false";
    } else {
        command = "defaults write /var/db/launchd.db/com.apple.launchd/overrides.plist com.apple.screensharing -dict Disabled -bool true";
    }
    string res = executeSystemCommand( command, aRootPassword );
    if( bEnable ) {
        command = "launchctl load /System/Library/LaunchDaemons/com.apple.screensharing.plist";
    } else {
        command = "launchctl unload /System/Library/LaunchDaemons/com.apple.screensharing.plist";
    }
    res += executeSystemCommand( command, aRootPassword );
    
}

//--------------------------------------------------------------
void ofxMacUtils::setFireWall( string aRootPassword, bool bEnable ) {
    string command = "defaults write /Library/Preferences/com.apple.alf globalstate -int "+ofToString(bEnable?1:0);
    string res = executeSystemCommand( command, aRootPassword );
    command = "launchctl unload /System/Library/LaunchDaemons/com.apple.alf.agent.plist";
    res = executeSystemCommand( command, aRootPassword );
    command = "sudo launchctl load /System/Library/LaunchDaemons/com.apple.alf.agent.plist";
    res = executeSystemCommand( command, aRootPassword );
}

//--------------------------------------------------------------
int ofxMacUtils::getNumMonitors() {
//     string ncommand = "system_profiler SPDisplaysDataType | grep 'Online: Yes' | wc -l";
//    int numMonitors = ofToInt( MacUtils::executeSystemCommand( ncommand ));
    return [[NSScreen screens] count];
}

//--------------------------------------------------------------
int ofxMacUtils::screenCapture( vector<string> aScreenCaptureSavePaths ) {
    string command = "screencapture";
    int screenCaptureStatus = 0;
    if( aScreenCaptureSavePaths.size() ) {
        int numMonitors = getNumMonitors();
        for( int i = 0; i < aScreenCaptureSavePaths.size(); i++ ) {
            if( i >= numMonitors ) break;
            command += " "+aScreenCaptureSavePaths[i];
        }
        screenCaptureStatus = ofToInt(executeSystemCommand( command ));
    }
    return screenCaptureStatus;
}

#ifdef OFX_MAC_UTILS_USE_OBJ_C
//--------------------------------------------------------------
bool ofxMacUtils::saveNsImage( NSImage* aImage, string aSavePath, bool bMakeAbsolute, float aWidth, float aHeight, bool bProportional ) {
    
    string path = aSavePath;
    
    if( aWidth == 0 && aHeight == 0 ) {
        aWidth  = [aImage size].width;
        aHeight = [aImage size].height;
    }
    
    CGImageRef imgRef = resizeNSImageToCGRef( aImage, aWidth, aHeight, bProportional );
    if( imgRef == nil ) return false;
    
    
    NSBitmapImageRep *newRep = [[NSBitmapImageRep alloc] initWithCGImage:imgRef];
//    [newRep setSize:NSMakeSize(256, 256)];
    NSData *pngData = [newRep representationUsingType:NSPNGFileType properties:nil];
    
    if(bMakeAbsolute) path = ofToDataPath( path, true );
    
    cout << "Going to save to path: " << path << endl;
    
    NSString* iconPath = [NSString stringWithUTF8String:path.c_str()];
    [pngData writeToFile:iconPath atomically:NO];
    [newRep autorelease];
    return true;
}

//--------------------------------------------------------------
CGImageRef ofxMacUtils::resizeNSImageToCGRef( NSImage* aImage, float aWidth, float aHeight, bool bProportional ) {
    CGImageRef cgRef = [aImage CGImageForProposedRect:nil
                                              context:nil
                                                hints:nil];
    
    ofRectangle trect( 0, 0, aWidth, aHeight );
    if( bProportional ) {
        ofRectangle srect( 0, 0, [aImage size].width, [aImage size].height );
        srect.scaleTo( trect );
        trect = srect;
    }
    
    
    // create context, keeping original image properties
    CGColorSpaceRef colorspace = CGImageGetColorSpace(cgRef);
    CGContextRef context = CGBitmapContextCreate(NULL, trect.width, trect.height,
                                                 CGImageGetBitsPerComponent(cgRef),
                                                 CGImageGetBytesPerRow(cgRef),
                                                 colorspace,
                                                 CGImageGetAlphaInfo(cgRef));
    CGColorSpaceRelease(colorspace);
    
    
    if(context == NULL)
        return nil;
    
    
    // draw image to context (resizing it)
    CGContextDrawImage(context, CGRectMake(0, 0, trect.width, trect.height), cgRef);
    // extract resulting image from context
    CGImageRef imgRef = CGBitmapContextCreateImage(context);
    CGContextRelease(context);
    return imgRef;
}
#endif

//--------------------------------------------------------------
void ofxMacUtils::enablePrintToConsole() {
    bPrintToConsole = true;
}

//--------------------------------------------------------------
void ofxMacUtils::disablePrintToConsole() {
    bPrintToConsole = false;
}

//--------------------------------------------------------------
bool ofxMacUtils::isPrintToConsoleEnabled() {
    return bPrintToConsole;
}

#ifdef OFX_MAC_UTILS_USE_OBJ_C
//--------------------------------------------------------------
void ofxMacUtils::addWorkspaceNotificationsListener( ofxMacUtilsWorkpaceNotificationsListener* aListener ) {
    if( nsWSResponder == nil ) {
        nsWSResponder = [[ofxMacUtilsWorkspaceResponder alloc] init];
    }
    wsListeners.push_back( aListener );
}

//--------------------------------------------------------------
void ofxMacUtils::removeAllNotificationsListeners() {
    wsListeners.clear();
    if( nsWSResponder != nil ) {
        [nsWSResponder dealloc];
        nsWSResponder = nil;
    }
}

//--------------------------------------------------------------
void ofxMacUtils::receivedNotificationFromResponder( int aEvent ) {
    list<ofxMacUtilsWorkpaceNotificationsListener*>::iterator it;
    for ( it = wsListeners.begin(); it != wsListeners.end(); ++it) {
        (*it)->ofxMacUtilsWorkpaceNotificationReceived( aEvent );
    }
}
#endif





