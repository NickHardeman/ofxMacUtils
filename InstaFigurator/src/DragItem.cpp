//
//  DragItem.cpp
//  ScenesSetup_Nick
//
//  Created by Nick Hardeman on 8/25/14.
//

#include "DragItem.h"

//--------------------------------------------------------------
DragItem::DragItem() {
    setup( ofGetTimestampString(), "Default" );
}

//--------------------------------------------------------------
DragItem::DragItem( string aName, string aDisplayName ) {
    setup( aName, aDisplayName );
}

//--------------------------------------------------------------
void DragItem::setup( string aName, string aDisplayName ) {
    bgColor.set(30, 30, 30);
    outlineColor.set(200, 200, 200);
    padding = 4;
    
    acceptAllFileTypes();
    name = aName;
    displayName = aDisplayName;
}

//--------------------------------------------------------------
void DragItem::setFile( string aPathToFile ) {
    if( isValidFile( aPathToFile ) ) {
        file = aPathToFile;
    } else {
        file.close();
    }
}

//--------------------------------------------------------------
bool DragItem::isValidFile( string aPathToFile ) {
    ofFile tfile = aPathToFile;
    bool bGoodToGo = false;
    string fileExtension = tfile.getExtension();
    fileExtension = ofToLower( fileExtension );
    for( int i = 0; i < acceptedExts.size(); i++ ) {
        if( fileExtension == acceptedExts[i] ) {
            bGoodToGo = true;
            break;
        }
    }
    return bGoodToGo;
}

//--------------------------------------------------------------
void DragItem::draw() {
    
    ofSetColor( bgColor );
    ofRect( rect );
    
    if( icon.isAllocated() ) {
        ofSetColor( 255, 255, 255 );
        ofRectangle paddedRect( rect.x + padding, rect.y + padding, rect.width - padding*2, rect.height - padding * 2 );
        icon.draw( paddedRect );
    }
    
    ofSetColor( outlineColor );
    ofNoFill();
    ofRect( rect );
    ofFill();
    
    // ofDrawBitmapStringHighlight(string text, const ofPoint& position, const ofColor& background, const ofColor& foreground)
    ofDrawBitmapStringHighlight( displayName, rect.x + 4, rect.y + 22 + rect.height, bgColor, outlineColor );
}

//--------------------------------------------------------------
bool DragItem::dragEvent( ofDragInfo dragInfo ) {
    if( !dragInfo.files.size() ) return false;
    
    if( !rect.inside( dragInfo.position ) ) return false;
    
    bool bHasCorrectExtension = false;
    if( !acceptedExts.size() ) bHasCorrectExtension = true;
    
    bHasCorrectExtension = isValidFile( dragInfo.files[0] );
    
    if( bHasCorrectExtension ) {
        file = dragInfo.files[0];
    } else {
        ofSystemAlertDialog( "Only accepts file types: "+getFormattedAcceptedFileTypesString()+".");
    }
    return bHasCorrectExtension;
}

//--------------------------------------------------------------
void DragItem::acceptAllFileTypes() {
    acceptedExts.clear();
}

//--------------------------------------------------------------
void DragItem::acceptImages() {
    acceptedExts.push_back("png");
    acceptedExts.push_back("jpeg");
    acceptedExts.push_back("jpg");
    acceptedExts.push_back("gif");
}

//--------------------------------------------------------------
void DragItem::acceptTypesText() {
    acceptedExts.push_back("txt");
    acceptedExts.push_back("log");
}

//--------------------------------------------------------------
void DragItem::acceptApps() {
    acceptedExts.push_back( "app" );
}

//--------------------------------------------------------------
bool DragItem::loadIcon( string aPath ) {
    return icon.loadImage( aPath );
}

//--------------------------------------------------------------
bool DragItem::isFileImage() {
    if( !file.exists() ) return false;
    string text = file.getExtension();
    text = ofToLower( text );
    if( text == "jpg" ) return true;
    if( text == "jpeg" ) return true;
    if( text == "png" ) return true;
    if( text == "gif" ) return true;
    return false;
}

//--------------------------------------------------------------
bool DragItem::isFileApp() {
    if( !file.exists() ) return false;
    string text = file.getExtension();
    text = ofToLower( text );
    if( text == "app" ) return true;
    return false;
}

//--------------------------------------------------------------
string DragItem::getFormattedAcceptedFileTypesString() {
    string tstr = "";
    if( !acceptedExts.size() ) return "All";
    
    for( int i = 0; i < acceptedExts.size(); i++ ) {
        tstr += acceptedExts[i];
        if( i != acceptedExts.size()-1 ) tstr += ", ";
    }
    return tstr;
}








