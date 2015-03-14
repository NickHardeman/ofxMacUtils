#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
    
    ofAppGLFWWindow* win = new ofAppGLFWWindow();
//	ofSetupOpenGL(1200, 760, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofSetupOpenGL(win, 1300, 800, OF_WINDOW);
	ofRunApp( new ofApp() );

}
