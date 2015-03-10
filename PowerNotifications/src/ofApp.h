#pragma once

#include "ofMain.h"
#include "ofxMacUtils.h"

class ofApp : public ofBaseApp, public ofxMacUtilsWorkpaceNotificationsListener {
	public:
		void setup();
		void update();
		void draw();
    void exit();
    
    void ofxMacUtilsWorkpaceNotificationReceived( int aEvent );
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    vector< string > messages;
};
