#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofSetupOpenGL(975,500,OF_WINDOW);			// <-------- setup the GL context
  //ofSetupOpenGL(75,55,OF_WINDOW);
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
  //ofRunApp(new ofAppNoWindow()); // won't work with fbo
  
}
