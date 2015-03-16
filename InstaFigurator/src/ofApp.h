#pragma once

#include "ofMain.h"
#include "ofxMacUtils.h"
#include "ofxMacUtilsEncryption.h"
#include "ofxMacUtilsSimpleSettings.h"
#include "MainViewController.h"

class ofApp : public ofBaseApp, public ofThread {
public:
    
    void setup();
    void update();
    void draw();
    void exit();
    
    void applySettings();
    void saveIconImageForApp( string aAppPath, string aIconPath, int aSize=0 );
    
    void desktopImageSelected( NSImage* aImage );
    void loginImageSelected( NSImage* aImage );
    void appSelected( string aAbsPath );
    
    void createDesktopImageFromWithString( string aString );
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
    MainViewController* mainViewController;
    
    ofParameter<string> appToMonitor;
    ofFile appToMonitorFile;
    ofParameter<bool> bAddAsLoginItem;
    ofParameter<string> rootPassword;
    
    ofParameter<string> appIconImagePath;
    ofParameter<string> desktopImagePath;
    ofParameter<string> loginImagePath;
    
    ofParameter<bool> bDisableScreenSaver;
    ofParameter<bool> bDisableSoftwareUpdates;
    ofParameter<bool> bDisableGateKeeper;
    ofParameter<bool> bDisableSleepSettings;
    ofParameter<bool> bDisableSendDiagnostics;
    
    ofParameter<bool> bSetDesktopImage;
    ofParameter<bool> bSetLoginImage;
    ofParameter<bool> bScreenSharing;
    ofParameter<bool> bDisableFirewall;
    ofParameter<bool> bDisableWIFI;
    
    ofParameter<bool> bDisableNotificationCenter;
    ofParameter<bool> bDisableCrashReporterDialog;
    ofParameter<bool> bDisableBluetooth;
    ofParameter<bool> bDisableBluetoothAssistant;
    ofParameter<bool> bRestartOnPowerFailure;
    
    ofParameter<string> mostRecentCrashReportPath;
    ofParameter<string> mostRecentCrashReportDateFormatted;
    ofParameter<string> ipAddress;
    
    ofParameter<string> computerName;
    ofParameter<bool> bSetComputerName;
    ofParameter<string> computerLocalHostname;
    ofParameter<string> currentUserName;
    
    ofParameter<bool> bGenerateDesktopImage;
    
    ofParameterGroup paramsGroup;
    
    stringstream ourCoutIn;
    static ostream ourCoutOut;
    
    ofxMacUtilsEncryption encryption;
    
};





