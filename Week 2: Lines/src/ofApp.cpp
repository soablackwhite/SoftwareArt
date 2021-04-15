#include "ofApp.h"
int size = 4; //total nbr
float minDist = 50;
float shake = 0.5;
//--------------------------------------------------------------
void ofApp::setup(){
    //GUI
  sliderGroup.setName("sliders");
  sliderGroup.add(floatSlider.set("shake", 0, 0, 10));
  sliderGroup.add(floatSlider2.set("thickness", 0, 0, 5));
  sliderGroup.add(intSlider.set("range", 0, 0, 200));
  mainGroup.add(sliderGroup);
  gui.setup(mainGroup);
    
    ofBackground(28);
    //creating points
    ofSeedRandom(); //randomize the seed
    for(int i=0; i<total; i++){
        points[i].x=ofRandom(0,ofGetWidth());
        points[i].y=ofRandom(0,ofGetHeight());
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    shake = floatSlider;
    minDist = intSlider;
    ofSetLineWidth(floatSlider2);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255, 255, 255);
    for(int i=0; i<total/2; i++){
        //ofDrawCircle(points[i].x, points[i].y, size);
        for(int j=total/2; j<total; j++){
            if (ofDist(points[j].x, points[j].y,points[i].x, points[i].y)<=minDist){
                ofDrawLine(points[i].x, points[i].y, points[j].x+ofRandom(-shake,shake), points[j].y+ofRandom(-shake,shake));
                
                }
        }
    }
  gui.draw();
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
