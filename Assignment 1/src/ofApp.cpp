#include "ofApp.h"

float particles; //nbr of particules
float radius; //radius of the atom
float size; //radius of the particles
float coreSize;

//color variables
float hue = 55.12;
float sat = 122.24;
float bri = 255;
ofColor coreColor;
ofColor horColor;
ofColor vertColor;

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(226);
    
    //initiate general GUI
    sliderGroup.setName("Parameters");
    sliderGroup.add(intSlider.set("resolution", 32, 8, 64));
    sliderGroup.add(floatSlider4.set("radius", 150, 0, 500));
    sliderGroup.add(intSlider2.set("background",226,0,255));
    //initiate color GUI
    sliderGroup.add(floatSlider.set("triad", 55.12, 0, 255));
    sliderGroup.add(floatSlider2.set("saturation", 122.24, 0, 255));
    sliderGroup.add(floatSlider3.set("brightness", 255, 0, 255));
    sliderGroup.add(floatSlider5.set("particle size", 3, 0, 25));
    sliderGroup.add(floatSlider6.set("particles", 40, 0, 200));
    sliderGroup.add(floatSlider7.set("coreSize", 50, 0, 300));
    
    //setup
    gui.setup(sliderGroup);
    
    
    
    //initiate variables
    /*
    //convert to OF colors
    hue = ofMap(hue, 0, 360, 0, 255);
    sat = ofMap(sat, 0, 100, 0, 255);
    bri = ofMap(bri, 0, 100, 0, 255);
    */
    //set hsv colors
    /*coreColor.setHsb(floatSlider, sat, bri);
    horColor.setHsb(floatSlider+ofMap(120, 0, 360, 0, 255), sat, bri);
    vertColor.setHsb(floatSlider+ofMap(240, 0, 360, 0, 255), sat, bri);*/
}

//--------------------------------------------------------------
void ofApp::update(){
    rotate++;
    
    //color updates
    ofBackground(intSlider2);
    hue = floatSlider;
    sat = floatSlider2;
    bri = floatSlider3;
    radius = floatSlider4;
    particles = floatSlider6;
    size = floatSlider5;
    coreSize = floatSlider7;
    float hue2;
    float hue3;
    
    //loop through values
    if (hue+ofMap(120, 0, 360, 0, 255)>255){
        hue2 = hue+ofMap(120, 0, 360, 0, 255)-255;
    } else {
        hue2 = hue+ofMap(120, 0, 360, 0, 255);
    }
    if (hue+ofMap(240, 0, 360, 0, 255)>255){
        hue3 = hue+ofMap(240, 0, 360, 0, 255)-255;
    } else {
        hue3 = hue+ofMap(240, 0, 360, 0, 255);
    }
    
    //assign colors
    coreColor.setHsb(hue, sat, bri);
    horColor.setHsb(hue2, sat, bri);
    vertColor.setHsb(hue3, sat, bri);
    ofLog(OF_LOG_NOTICE, "the number is " + ofToString(hue2));
}


//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2); //center
    ofPushMatrix();
    ofRotateXRad(ofDegToRad(rotate/10));
    ofRotateYDeg(rotate/10);
    ofRotateZRad(ofDegToRad(rotate/10));
    
    //core
    ofNoFill();
    ofSetColor(coreColor);
    ofDrawSphere(0, 0, coreSize-coreSize/10+abs((coreSize/10)*sin(rotate/100)));
    
    //squeleton
    ofNoFill();
    ofSetColor(255, 4);
    ofDrawSphere(0, 0, coreSize+abs(coreSize*cos(rotate/100)));
    
    //orbiting particles
    for(int i=0; i<particles; i++){
        float angle = ofMap(i, 0, particles, -PI, PI);
        
        //vertical orbit
        ofPushMatrix();
        ofRotateZDeg(rotate);
        ofSetColor(vertColor);
        ofDrawSphere(radius*cos(angle), radius*sin(angle), 0, size);
        ofPopMatrix();
        
        //horizontal orbit
        ofPushMatrix();
        ofRotateYDeg(rotate);
        ofSetColor(horColor);
        ofDrawSphere(radius*cos(angle), 0, radius*sin(angle), size);
        ofPopMatrix();
    }
    
    ofPopMatrix();
}

//--------------------------------------------------------------
void convertMe(float myColor){
    myColor=ofMap(ofRadToDeg(asin(sin(ofDegToRad(myColor)))), 0, 360, 0, 255);
    return(myColor);
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
