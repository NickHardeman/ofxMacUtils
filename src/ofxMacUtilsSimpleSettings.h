//
//  ofxMacUtilsSimpleSettings.h
//  WatchDog
//
//  Created by Nick Hardeman on 3/13/15.
//

#pragma once
#include "ofxXmlSettings.h"
#include <map>

class ofxMacUtilsSimpleSettings {
public:
    static ofxXmlSettings appSettings;
    
    static void addAppSetting(string aXmlName, int aVal);
    static void addAppSetting(string aXmlName, string aVal);
    static void addAppSetting(string aXmlName, float aVal);
    static void addAppSetting( ofParameter<int>& aParam );
    static void addAppSetting( ofParameter<string>& aParam );
    static void addAppSetting( ofParameter<float>& aParam );
    static void addAppSetting( ofParameter<bool>& aParam );
    static void addAppSettings( ofParameterGroup& aGroup );
    
    static string getAppSettingS(string aXmlName);
    static float getAppSettingF(string aXmlName);
    static int getAppSettingI(string aXmlName);
    static int getAppSetting( ofParameter<int>& aParam );
    static string getAppSetting( ofParameter<string>& aParam );
    static float getAppSetting( ofParameter<float>& aParam );
    static bool getAppSetting( ofParameter<bool>& aParam );
    static void getAppSettings( ofParameterGroup& aGroup );
    
    static void saveAppSettings( string aXmlName = "app_settings.xml" );
    static bool loadAppSettings( string aXmlName = "app_settings.xml" );
    static void loadWindowPosition();
    static void loadWindowShape();
    
private:
    static bool bSettingsLoadedOk;
};
