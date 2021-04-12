#include "ofApp.h"
#include "myCube.hpp"

int total = 3;
float offset = 110;
float size = 90;
int len;
int indice;
int alignement;
int sens;
int rotate2;

myCube* cubes = new myCube[27];

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(35);
    
    for (int i=0; i<total; i++){
        for (int j=0; j<total; j++){
            for (int k=0; k<total; k++){
                cubes[total*total*i+total*j+k]= myCube((i-1)*offset, (j-1)*offset, (k-1)*offset, size, 255);
            }
        }
    }
    
    //shuffle and randomize
    shuffleMe();
    
    //len = sizeof(cubes)/sizeof(cubes[0]);
    for (int i=0; i<total*total*total; i++){
        cubes[i].setup();
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    rotate++;
    rotate2+=5;
    
    //if (ofRandom(10)>1){
        if (rotate2 % 90 == 0){
            shuffleMe();
        }
    //}
    
    /*int row = 1;
    for (int j=0; j<total; j++){
        for (int k=0; k<total; k++){
            cubes[total*total*row+total*j+k].rotateMe();
        }
    }*/
    
}
void ofApp::shuffleMe(){
    indice=(int)ofRandom(0,3);
    alignement=ofRandom(0,2);
    if (ofRandom(10)>5){
        sens=1;
    } else{
        sens=-1;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2); //center
    ofRotateXRad(ofDegToRad(rotate/2));
    ofRotateYDeg(rotate/2);
    ofRotateZRad(ofDegToRad(rotate/2));

    
    for (int i=0; i<total; i++){
        for (int j=0; j<total; j++){
            for (int k=0; k<total; k++){
                ofPushMatrix();
                //horizontal rotation
                if (i==indice && alignement>=1){
                    ofRotateXDeg(sens*rotate2);
                }
                //vertical rotation
                if (j==indice && alignement<1){
                    ofRotateYDeg(sens*rotate2);
                }
                cubes[total*total*i+total*j+k].draw();
                
                ofPopMatrix();
                
            }
        }
    }
    
    /*for (int i=0; i<27; i++){
        ofPushMatrix();
        if (i<total*total*1 && i>=total*total*0){
            ofRotateXDeg(rotate2);
        }
        
        if (i<total*total*1 && i>=total*total*0){
            ofRotateXDeg(rotate2);
        }
        
        cubes[i].draw();
        ofPopMatrix();
    }*/
    ofPopMatrix();
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
