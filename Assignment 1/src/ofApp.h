#pragma once

#include "ofMain.h"
#include "ofxGui.h"
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    float rotate; //animation variable
    
    //GUI
    ofxPanel gui;
    
    ofParameterGroup sliderGroup;
    ofParameterGroup sliderGroup2;
    
    ofParameter<int> intSlider;
    ofParameter<int> intSlider2;
    ofParameter<float> floatSlider;
    ofParameter<float> floatSlider2;
    ofParameter<float> floatSlider3;
    ofParameter<float> floatSlider4;
    ofParameter<float> floatSlider5;
    ofParameter<float> floatSlider6;
    ofParameter<float> floatSlider7;
    
    
};


