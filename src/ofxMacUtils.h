//
//  MacUtils.h
//  ScenesSetup_Nick
//
//  Created by Nick Hardeman on 8/26/14.
//

#pragma once
#include "ofMain.h"

#ifdef OFX_MAC_UTILS_USE_OBJ_C
    #include "ofxMacUtilsWorkspaceResponder.h"
#endif
#include "ofxMacUtilsWorkpaceNotificationsListener.h"


class ofxMacUtils {
public:
    
    struct NetworkDeviceInfo {
        NetworkDeviceInfo( string aName, string aAddress, string aSubnet) {
            name = aName; address = aAddress;
            subnet = aSubnet;
        }
        string name;
        string address;
        string subnet;
    };
    
    enum NS_WorkspaceNotificationTypes {
        NS_WS_EVENT_POWER_DOWN = 0,
        NS_WS_EVENT_SLEEP,
        NS_WS_EVENT_WAKE,
        NS_WS_EVENT_TOTAL
    };
    
    static string executeSystemCommand(string cmd);
    static string executeSystemCommand(string cmd, string aSystemPassword );
    
    static bool isNetworkAvailable();
    static vector< NetworkDeviceInfo > getNetworkDeviceInfos();
    static string getIpAddress();
    static string getSubnet();

    static string getCurrentWifiPort();
    static void setWifiPower( bool bOn );
    static bool getWifiPower();
    
    static void setComputerName( string aSystemPassword, string aName );
    static void setComputerLocalHostName( string aSystemPassword, string aName );
    static void setComputerHostName( string aSystemPassword, string aName );
    
    static string getComputerName();
    static string getComputerLocalHostName();
    static string getComputerHostName();
    
#ifdef OFX_MAC_UTILS_USE_OBJ_C
    static string getCurrentUsername();
#endif
    
    static void setBluetooth( string aSystemPassword, bool bEnable );
    static void setBluetoothSeupAssistant( string aSystemPassword, bool bEnable );
    
    static void setSendDiagInfo( string aSystemPassword, bool bEnable );
    
#ifdef OFX_MAC_UTILS_USE_OBJ_C
    static NSRunningApplication* getRunningProcess( string aProcessName );
#endif
    static bool isProcessRunning( string aAbsPath );
    static void openProcess( string aAbsPath );
    static string getProcessId( string aProcessName );
    static bool isApplicationRunning( string aAppName );
    static void runApplication( string aAppName );
#ifdef OFX_MAC_UTILS_USE_OBJ_C
    static string getProcessStatus( string aProcessName );
#endif
    
    
    // pass in zero to disable screen saver //
    static void setScreenSaverStartTime( float aTimeInSeconds );
    
    static bool isApplicationALoginItem( string aAppName );
    static void addApplicationToLoginItems( string aPathToApp, bool bHide );
    
    static void setDesktopImage( string aAbsPath );
    static void setLoginImage( string aAbsPath );
    
    static void setSoftwareUpdates( string aRootPassword, bool bOn );
    static void setSleep( string aRootPassword, bool bOn );
    
    static void setGateKeeper( string aRootPassword, bool bOn );
    static void setCrashReporterDialog( bool bEnable );
    static void restartOnPowerFailure( string aRootPassword, bool aYes );
    
    static void setNotificationCenter( bool bEnable );
    
    static void setScreenSharing( string aRootPassword, bool bEnable );
    static void setFireWall( string aRootPassword, bool bEnable );
    
    static int getNumMonitors();
    static int screenCapture( vector<string> aScreenCaptureSavePaths );
    
#ifdef OFX_MAC_UTILS_USE_OBJ_C
        static bool saveNsImage( NSImage* aImage, string aSavePath, bool bMakeAbsolute=true, float aWidth=0, float aHeight=0, bool bProportional=true );
        static CGImageRef resizeNSImageToCGRef( NSImage* aImage, float aWidth=0, float aHeight=0, bool bProportional=true );
#endif
    
    static bool bPrintToConsole;
    static void enablePrintToConsole();
    static void disablePrintToConsole();
    static bool isPrintToConsoleEnabled();
    
#ifdef OFX_MAC_UTILS_USE_OBJ_C
    static list< ofxMacUtilsWorkpaceNotificationsListener* > wsListeners;
    // notifications //
    static void addWorkspaceNotificationsListener( ofxMacUtilsWorkpaceNotificationsListener* aListener );
    static void removeAllNotificationsListeners();
    static void receivedNotificationFromResponder( int aEvent );
#endif
    
    
protected:
#ifdef OFX_MAC_UTILS_USE_OBJ_C
    static ofxMacUtilsWorkspaceResponder* nsWSResponder;
#endif
};







