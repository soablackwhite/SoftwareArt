#include "ofApp.h"
float h; //center x coord
float k; //center y coord

float r1; //radius of the bend
float r2; //radius of the bend
float radius; //of the tunnel

//noise step
float step = 0;
string myColor="grayscale";


//dimensions HARDCODED FOR NOW
float rows = 40;
float cols=40;
float angles[40*40];
float angles2[40*40];
//--------------------------------------------------------------
void ofApp::setup(){
    r1=ofGetHeight()/2;
    r2=ofGetHeight()/8;
    
    ofBackground(228); //silver
    //ofBackground(28); //light black
    
    
    //GUI
    gui.setup();
    gui.add(noise.set("noise", 0.0034, 0, 0.01));
    gui.add(threshold.set("threshold", 137, 0, 200));
    gui.add(lightPos.set("light position", ofVec3f(-816, -448, -2367), ofVec3f(-2000, -2000, -4000), ofVec3f(2000, 2000, 4000)));
    //transforms

    
    
    
    transform.setName("Transform");
    transform.add(zoom.set("zoom", 300, -1000, 1000));
    transform.add(rotate.set("rotation", ofVec3f(180, 0, 0), ofVec3f(0, 0, 0), ofVec3f(360, 360, 360)));
    transform.add(translate.set("translate", ofVec3f(0, 0, 0), ofVec3f(-500, -500, -500), ofVec3f(500, 500, 500)));
    transform.add(radii.set("radii", ofVec3f(ofGetHeight()/2, 522, 1000), ofVec3f(0, 0, 0), ofVec3f(ofGetHeight(), 1000, 1000)));
    gui.add(transform);
    gui.add(neon.setup("neon"));
    gui.add(blackwhite2.setup("grayscale"));
    gui.add(techblue.setup("techblue"));
    gui.add(quicksilver.setup("quicksilver"));
    gui.add(nyu.setup("nyu"));
    
    //radii
    radius = radii -> x;
    r1 = radii -> y;
    r2 = radii -> z;
    
    for(int i=0; i<=rows; i++){
        //define centers of circles, this is the bending of the tunnel
        for (int j=0; j<=cols; j++){
            
            angles[i*j+j] = ofRandom(135); //store angular positions
            float angle = ofDegToRad(angles[i*j+j]);
            
            //parametric equation of ellipse
            float cx = 0;
            float cy = r1*cos(angle);
            float cz = r2*sin(angle);
            
            //draw circles
            angles2[i*j+j] = ofRandom(360); //store angular positions
            float angle2 = ofDegToRad(angles2[i*j+j]);
            
            //parametric equation of circle
            float x = cx + radius*cos(angle2);
            float y = cy + radius*sin(angle2);
            float z = 2*cz;
            mesh.addVertex(ofPoint(x,y,z));
            if ((int)((i))%2==0){
                mesh.addColor(ofFloatColor(1,.3)); //black
            } else {
                mesh.addColor(ofFloatColor(1,.7)); //white
            }
        }
    }
}


//--------------------------------------------------------------
void ofApp::update(){
    //colors
    if (neon) {
        myColor="neon";
        ofBackground(28);
      }
    
    else if (blackwhite2) {
        myColor="grayscale";
        ofBackground(228);
      }
    
    else if (techblue) {
        myColor="techblue";
        ofBackground(2,21,38);
      }
    
    else if (quicksilver) {
        myColor="quicksilver";
        ofBackground(228);
      }
    
    else if (nyu) {
        myColor="nyu";
        //ofBackground(20,1,34);
        ofBackground(228);
      }
    
    
    
    light.setPosition(lightPos->x, lightPos->y, lightPos->z);
    radius = radii -> x;
    r1 = radii -> y;
    r2 = radii -> z;
    glEnable(GL_POINT_SMOOTH);
    //glPointSize(1.0);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    //mesh.clear();
    int count=0;
    for(int i=0; i<=rows; i++){
        for (int j=0; j<=cols; j++){
            ofVec3f position = mesh.getVertex(count); //get pos
            
            //noise to move stuff
            float noiseBend = ofMap(ofNoise(count, 3*ofGetElapsedTimef()), 0, 1, 0, noise*135);
            float noiseCircle = ofMap(ofNoise(count, .1*ofGetElapsedTimef()), 0, 1, 0, noise*360);
            float angle;
            
            //reset evertime it goes past 135, i couldnt use modulo cuz the nbrs are floats and casting to ints made the animation cranky
            if (step + noiseBend + angles[i*j+j] >= 135){
                angle = ofDegToRad((step + angles[i*j+j] + noiseBend)-135);
            } else {
                angle = ofDegToRad(step + angles[i*j+j] + noiseBend);
            }
            
            //parametric equation of ellipse
            float cx = 0;
            float cy = r1*cos(angle);
            float cz = r2*sin(angle);
            
            float angle2 = ofDegToRad(angles2[i*j+j]);
            //parametric equation of circle
            position.x = cx + radius*cos(angle2 + noiseCircle);
            position.y = cy + radius*sin(angle2 + noiseCircle);
            position.z = 2*cz;
            
            //assign value and increment noise position
            mesh.setVertex(count, position);
            count++;
        }
    }
    if (step>=135){
        step=0;
    } else{
        step+=1;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    //ofEnableDepthTest();
    light.enable();
    ofSetColor(255,20);
    //ofDrawSphere(lightPos->x, lightPos->y, lightPos->z, 150);
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2 + (radii -> y ), zoom);
    //ofRotateXDeg(90);
    ofTranslate(translate->x,translate->y,translate->z);
    ofRotateXDeg(rotate->x);
    ofRotateYDeg(rotate->y);
    ofRotateZDeg(rotate->z);
    
    for (int i = 0; i < mesh.getNumVertices()/2; i++){ //big circle
            //get position
            ofVec3f pos1 = mesh.getVertex(i);
        for(int j = mesh.getNumVertices()/2; j< mesh.getNumVertices(); j++){
            ofVec3f pos2 = mesh.getVertex(j);
            float distance = ofDist(pos1.x, pos1.y, pos1.z, pos2.x, pos2.y, pos2.z);
            if (distance <= threshold){
                
                //colors for lines
                if (myColor=="neon") {
                    if ((int)((i))%2==0){
                        ofSetColor(5, 226,215, ofMap(-distance, -threshold, 0, 0, 255)); //light neon blue
                    } else {
                        ofSetColor(250, 38, 160, ofMap(-distance, -threshold, 0, 0, 255));//light neon pink
                    }
                  }
                
                else if (myColor=="grayscale") {
                    if ((int)((i))%2==0){
                        ofSetColor(78, ofMap(-distance, -threshold, 0, 0, 255)); //black
                    } else {
                        ofSetColor(255, ofMap(-distance, -threshold, 0, 0, 255)); //white
                    }
                  }
                
                else if (myColor=="techblue") {
                    if ((int)((i))%2==0){
                        ofSetColor(46, 206, 242, ofMap(-distance, -threshold, 0, 0, 255)); //energy blue
                    } else {
                        ofSetColor(35, 165, 217, ofMap(-distance, -threshold, 0, 0, 255)); //dark energy blue
                    }
                  }
                
                else if (myColor=="quicksilver") {
                    if ((int)((i))%2==0){
                        ofSetColor(5, 50,89, ofMap(-distance, -threshold, 0, 0, 255)); //dark marine
                    } else {
                        ofSetColor(10, 93,166, ofMap(-distance, -threshold, 0, 0, 255)); //lighter marine
                    }
                  }
                
                else if (myColor=="nyu") {
                    if ((int)((i))%2==0){
                        ofSetColor(255, 0.9*ofMap(-distance, -threshold, 0, 0, 255)); //white
                    }
                    else {
                        ofSetColor(123, 10,203, ofMap(-distance, -threshold, 0, 0, 255)); //nyu purple
                    }
                }
                ofDrawLine(pos1, pos2);
            }
        }
    }
    
    //mesh.drawVertices();
    light.disable();
    //ofDisableDepthTest();
    //camera.end();
    ofPopMatrix();
    
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
