//
//  DragItem.h
//  ScenesSetup_Nick
//
//  Created by Nick Hardeman on 8/25/14.
//

#pragma once
#include "ofMain.h"

class DragItem {
public:
    DragItem();
    DragItem( string aName, string aDisplayName );
    
    void setup( string aName, string aDisplayName );
    void setFile( string aPathToFile );
    bool isValidFile( string aPathToFile );
    void draw();
    
    // returns true when the item can be accepted //
    bool dragEvent( ofDragInfo dragInfo );
    void acceptAllFileTypes();
    void acceptImages();
    void acceptTypesText();
    void acceptApps();
    bool loadIcon( string aPath );
    bool isFileImage();
    bool isFileApp();
    
    string getFormattedAcceptedFileTypesString();
    
    string name;
    string displayName;
    ofRectangle rect;
    ofColor bgColor, outlineColor;
    float padding;
    
    ofFile file;
    
protected:
    vector<string> acceptedExts;
    ofImage icon;
};




