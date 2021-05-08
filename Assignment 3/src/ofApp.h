#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#define MAXPOINTS 1000
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

    //trail
    ofPoint pts[MAXPOINTS];
    int nPts = 0;
    ofPoint pts2[MAXPOINTS];
    int nPts2 = 0;
    ofPolyline polyline;
    ofPolyline polyline2;
    
    //gui
    ofxPanel gui;
    ofParameter <float> noise;
    ofParameter <float> threshold;
    ofParameter <float> zoom;
    ofParameterGroup transform;
    ofParameter <ofVec3f> rotate;
    ofParameter <ofVec3f> translate;
    
    //camera
    ofNode baseNode;
    ofNode childNode;
    ofNode grandChildNode;
    ofEasyCam cam;
    
    //audio
    ofSoundPlayer sound;
    float *fft;
    float *spectrum;
    int bands;
};
