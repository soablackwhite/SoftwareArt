#include "ofApp.h"
float xCenter;
float yCenter;
float r;

//point coordinates
float x1;
float x2;
float x3;
float y11; //named differently as y1 is predefined in openframeworks
float y2;
float y3;
//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(20);
    
    //choose center of equilateral triangle
    xCenter = ofRandom(ofGetWidth()/3,2*ofGetWidth()/3);
    yCenter = ofRandom(ofGetHeight()/3,2*ofGetHeight()/3);
    
    //distance between points, or radius
    r = 150;
    
    //first point
    x1 = xCenter+ r*cos(0);
    y11 = yCenter+ r*sin(0);
    
    //second point
    x2 = xCenter+ r*cos(2*PI/3);
    y2 = yCenter+ r*sin(2*PI/3);
    
    //third point
    x3 = xCenter+ r*cos(4*PI/3);
    y3 = yCenter+ r*sin(4*PI/3);
    ofSetCircleResolution(64);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //center
    ofSetColor(226);
    ofDrawCircle(xCenter,yCenter,1);
    
    //red+green
    ofSetColor(152.5, 152.5, 80);
    ofDrawLine(x1, y11, x2, y2);
    //red+blue
    ofSetColor(152.5, 80, 152.5);
    ofDrawLine(x1, y11, x3, y3);
    //green+blue
    ofSetColor(80, 152.5, 152.5);
    ofDrawLine(x2, y2, x3, y3);
    
    //red circle
    ofSetColor(225, 80, 80,90);
    ofDrawCircle(x1, y11, 200);
    //green circle
    ofSetColor(80, 225, 80,90);
    ofDrawCircle(x2, y2, 200);
    //blue circle
    ofSetColor(80, 80, 225,90);
    ofDrawCircle(x3, y3, 200);
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
