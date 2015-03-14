//
//  ofxMacUtilsSimpleSettings.cpp
//  WatchDog
//
//  Created by Nick Hardeman on 3/13/15.
//

#include "ofxMacUtilsSimpleSettings.h"

bool ofxMacUtilsSimpleSettings::bSettingsLoadedOk       = false;
ofxXmlSettings ofxMacUtilsSimpleSettings::appSettings;
map<string, string> settings;

//--------------------------------------------------------------
void ofxMacUtilsSimpleSettings::addAppSetting(string aXmlName, int aVal) {
    settings[aXmlName] = ofToString(aVal,0);
}

//--------------------------------------------------------------
void ofxMacUtilsSimpleSettings::addAppSetting(string aXmlName, string aVal) {
    settings[aXmlName] = aVal;
}

//--------------------------------------------------------------
void ofxMacUtilsSimpleSettings::addAppSetting(string aXmlName, float aVal) {
    settings[aXmlName] = ofToString(aVal, 20);
}

//--------------------------------------------------------------
void ofxMacUtilsSimpleSettings::addAppSetting( ofParameter<int>& aParam ) {
    addAppSetting( aParam.getName(), (int)aParam.get() );
}

//--------------------------------------------------------------
void ofxMacUtilsSimpleSettings::addAppSetting( ofParameter<string>& aParam ) {
    addAppSetting( aParam.getName(), (string)aParam.get() );
}

//--------------------------------------------------------------
void ofxMacUtilsSimpleSettings::addAppSetting( ofParameter<float>& aParam ) {
    addAppSetting( aParam.getName(), (float)aParam.get() );
}

//--------------------------------------------------------------
void ofxMacUtilsSimpleSettings::addAppSetting( ofParameter<bool>& aParam ) {
    addAppSetting( aParam.getName(), (int)aParam.get() );
}

//--------------------------------------------------------------
void ofxMacUtilsSimpleSettings::addAppSettings( ofParameterGroup &aGroup ) {
    for( int i = 0; i < aGroup.size(); i++ ) {
        if( aGroup.get(i).type() == typeid(ofParameter<int>).name() ) {
            addAppSetting( aGroup.getName(i), aGroup.getInt(i) );
        } else if( aGroup.get(i).type() == typeid(ofParameter<bool>).name() ) {
            addAppSetting( aGroup.getName(i), aGroup.getBool(i) );
        } else if( aGroup.get(i).type() == typeid(ofParameter<string>).name() ) {
            addAppSetting( aGroup.getName(i), aGroup.getString(i) );
        } else {
            addAppSetting( aGroup.getName(i), aGroup.getFloat(i) );
        }
    }
}

//--------------------------------------------------------------
string ofxMacUtilsSimpleSettings::getAppSettingS(string aXmlName) {
    if(settings.find(aXmlName) == settings.end()) return "";
    return settings[aXmlName];
}

//--------------------------------------------------------------
float ofxMacUtilsSimpleSettings::getAppSettingF(string aXmlName) {
    if(settings.find(aXmlName) == settings.end()) return 0.f;
    return ofToFloat(settings[aXmlName]);
}

//--------------------------------------------------------------
int ofxMacUtilsSimpleSettings::getAppSettingI(string aXmlName) {
    if(settings.find(aXmlName) == settings.end()) return 0;
    return ofToInt(settings[aXmlName]);
}

//--------------------------------------------------------------
int ofxMacUtilsSimpleSettings::getAppSetting( ofParameter<int>& aParam ) {
    return getAppSettingI( aParam.getName() );
}

//--------------------------------------------------------------
string ofxMacUtilsSimpleSettings::getAppSetting( ofParameter<string>& aParam ) {
    return getAppSettingS( aParam.getName() );
}

//--------------------------------------------------------------
float ofxMacUtilsSimpleSettings::getAppSetting( ofParameter<float>& aParam ) {
    return getAppSettingF( aParam.getName() );
}

//--------------------------------------------------------------
bool ofxMacUtilsSimpleSettings::getAppSetting( ofParameter<bool>& aParam ) {
    return (bool)getAppSettingI( aParam.getName() );
}

//--------------------------------------------------------------
void ofxMacUtilsSimpleSettings::getAppSettings( ofParameterGroup& aGroup ) {
    for( int i = 0; i < aGroup.size(); i++ ) {
        if( aGroup.get(i).type() == typeid(ofParameter<int>).name() ) {
            aGroup.getInt(i) = getAppSettingI( aGroup.getName(i) );
        } else if( aGroup.get(i).type() == typeid(ofParameter<bool>).name() ) {
            aGroup.getBool(i) = getAppSettingI( aGroup.getName(i) );
        } else if( aGroup.get(i).type() == typeid(ofParameter<string>).name() ) {
            aGroup.getString(i) = getAppSettingS( aGroup.getName(i) );
        } else {
            aGroup.getFloat(i) = getAppSettingF( aGroup.getName(i) );
        }
    }
}

//--------------------------------------------------------------
void ofxMacUtilsSimpleSettings::saveAppSettings( string aXmlName ) {
    appSettings.clear();
    int stagNum = appSettings.addTag("window");
    
    if( ofGetWindowMode() != OF_FULLSCREEN ) {
        appSettings.setAttribute("window", "x", ofGetWindowPositionX(), stagNum);
        appSettings.setAttribute("window", "y", ofGetWindowPositionY(), stagNum);
        
        appSettings.setAttribute("window", "width", ofGetWidth(), stagNum);
        appSettings.setAttribute("window", "height", ofGetHeight(), stagNum);
    }
    
    map<string, string>::iterator it;
    for(it = settings.begin(); it != settings.end(); ++it ) {
        int tnum = appSettings.addTag("setting");
        appSettings.setAttribute("setting", "name", it->first, tnum );
        appSettings.setAttribute("setting", "value", it->second, tnum );
        appSettings.popTag();
    }
    
    appSettings.saveFile( aXmlName );
}

//--------------------------------------------------------------
bool ofxMacUtilsSimpleSettings::loadAppSettings( string aXmlName ) {
    settings.clear();
    bSettingsLoadedOk = appSettings.loadFile(aXmlName);
    if(bSettingsLoadedOk) {
        int ttags = appSettings.getNumTags("setting");
        for(int i = 0; i < ttags; i++ ) {
            string name     = appSettings.getAttribute("setting", "name", "", i);
            string value    = appSettings.getAttribute("setting", "value", "", i);
            //cout << "Utils :: loadAppSettings : name = " << name << " value = " << value << endl;
            settings[name] = value;
        }
    } else {
        ofLogWarning("yq::Utils :: loadAppSettings : unable to load "+aXmlName);
    }
    return bSettingsLoadedOk;
}

//--------------------------------------------------------------
void ofxMacUtilsSimpleSettings::loadWindowPosition() {
    if(!bSettingsLoadedOk) {
        loadAppSettings();
    }
    if(bSettingsLoadedOk) {
        int winx = appSettings.getAttribute("window", "x", 0, 0);
        int winy = appSettings.getAttribute("window", "y", 0, 0);
        ofSetWindowPosition( winx, winy );
    }
}

//--------------------------------------------------------------
void ofxMacUtilsSimpleSettings::loadWindowShape() {
    if(!bSettingsLoadedOk) {
        loadAppSettings();
    }
    if(bSettingsLoadedOk) {
        int winx = appSettings.getAttribute("window", "width", 1024, 0);
        int winy = appSettings.getAttribute("window", "height", 768, 0);
        ofSetWindowShape( winx, winy );
    }
}










