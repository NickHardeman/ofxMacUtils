#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetLogLevel( OF_LOG_VERBOSE );
    ofxMacUtils::addWorkspaceNotificationsListener( this );
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetColor( 60, 60, 60 );
    for( int i = 0; i < messages.size(); i++ ) {
        ofDrawBitmapString( messages[i], 30, 46 + (float)i * 30 );
    }
}

//--------------------------------------------------------------
void ofApp::exit() {
    cout << "ofApp :: exit " << endl;
    messages.push_back( "Exit "+ofToString( ofGetElapsedTimef(), 0));
    ofxMacUtils::removeAllNotificationsListeners();
}

//--------------------------------------------------------------
void ofApp::ofxMacUtilsWorkpaceNotificationReceived( int aEvent ) {
    cout << "ofApp :: received a notification " << ofGetFrameNum() << endl;
    if( aEvent == ofxMacUtils::NS_WS_EVENT_POWER_DOWN ) {
        messages.push_back( "power down notification: " + ofToString( ofGetElapsedTimef(), 0) );
        ofExit();
    }
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 'e' ) {
        ofExit();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}