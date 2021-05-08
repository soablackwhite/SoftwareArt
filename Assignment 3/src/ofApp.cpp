#include "ofApp.h"


//MOVEMENT
bool mRight = false;
bool mLeft = false;
bool mUp = false;
bool mDown = false;
float rotate2;
float counter=1;

//trails
//vector<trail> trails;

//sphere
float cx;
float cy;
float radius;
float rad; //radius of smaller sphere

//tracer
ofColor tColor;
ofVec3f pos;
ofVec3f pos2;
float u; //latitude
float v; //longitude
float u2; //latitude
float v2; //longitude
float x; // noise position X
float y; // noise position Y
float stepU; //increment
float stepV; //increment
float speedU; //
float speedV; //
float noiseU;
float noiseV;

//--------------------------------------------------------------
void ofApp::setup(){
    //GUI
    gui.setup();
    transform.setName("Transform");
    transform.add(zoom.set("zoom", 0, -1000, 1000));
    transform.add(rotate.set("rotation", ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(360, 360, 360)));
    transform.add(translate.set("translate", ofVec3f(0, 0, 0), ofVec3f(-500, -500, -500), ofVec3f(500, 500, 500)));
    gui.add(transform);
    
    //Sound
    sound.load("audio2.wav");
    sound.setLoop(false);
    sound.play();
    fft = new float[521];
    
    for (int i=0; i<512; i++){
        fft[i]=0;
    }
    bands = 512;
    
    //settings
    ofSetFrameRate(60);
    ofSetLineWidth(2);
    glEnable(GL_POINT_SMOOTH);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    cx = ofGetWidth()/2;
    cy = ofGetHeight()/2;
    
    //start position
    radius = 500;
    u = 0;
    v = 0;
    stepU = PI/100;
    stepV = PI/100;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    //sound stuff
    rad=0;
    if (sound.getPosition()>0.85){
        rotate2+=counter;
        counter*=0.99;
    }
    else if(!sound.isPlaying()){
        
    }else {
        rotate2++;
    }
    speedU=0;
    speedV=0;
    ofSoundUpdate();
    spectrum = ofSoundGetSpectrum(bands);
    for (int i=0; i<bands; i++){
        fft[i] *= .9;
        if (fft[i]<spectrum[i]){
            fft[i] = spectrum[i];
        }
    }
    
    for (int i=0; i<bands/2; i+=4){
        float avg = bands/2;
        if(i<avg/5){
            speedU+=2*fft[i]/avg;
        }
        else if(i<2*avg/5) {
            rad+=200*fft[i]/avg;
        }
        else if(i<3*avg/5){
            speedV+=2*fft[i]/avg;
        }
        else if(i<4*avg/5){
            speedU-=4*fft[i]/avg;
            noiseU+=fft[i]/avg;
        } else{
            speedV-=4*fft[i]/avg;
            noiseV+=fft[i]/avg;
        }
    }
    
    //increment movement
    if (mRight){
        u2+=stepV;
    }
    if (mLeft){
        u2-=stepV;
    }
    if (mUp){
        v2+=stepV;
    }
    if (mDown){
        v2-=stepV;
    }
    v+=5*PI*speedV + 0.01*ofNoise(noiseV*0.01*ofGetElapsedTimef());
    u+=5*PI*speedU + 0.01*ofNoise(noiseU*0.01*ofGetElapsedTimef());
    
    
    //converting from angular to planar coordinates
    pos.x = radius * sin(u) * cos(v);
    pos.y = radius * sin(u) * sin(v);
    pos.z = radius * cos(u);
    
    pos2.x = radius * sin(u2) * cos(v2);
    pos2.y = radius * sin(u2) * sin(v2);
    pos2.z = radius * cos(u2);
    
    //adding trail
    //trail _trail = trail(pos,20,u,v);
    //trails.push_back(_trail);
    
    
    if(!sound.isPlaying()){
        pos.x = ofLerp(pos.x, 0, 0.25);
        pos.y = ofLerp(pos.y, 0, 0.25);
        pos.z = ofLerp(pos.z, 0, 0.25);
        
    }
    
    if(zoom>-180){
        zoom-=1;
    }
    if (nPts < MAXPOINTS) {
        pts[nPts].x = pos.x;
        pts[nPts].y = pos.y;
        pts[nPts].z = pos.z;
        nPts++;
    } else {
        nPts=0;
    }
    if (nPts2 < MAXPOINTS) {
        pts2[nPts2].x = pos2.x;
        pts2[nPts2].y = pos2.y;
        pts2[nPts2].z = pos2.z;
        nPts2++;
    } else {
        nPts2=0;
    }
    polyline.addVertex(ofPoint(pos.x, pos.y, pos.z));
    polyline2.addVertex(ofPoint(pos2.x, pos2.y, pos2.z));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(2,21,38);
    ofPushMatrix();
    //translate to center
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, zoom);
    //ofTranslate(pos.x, pos.y, pos.z);
    ofTranslate(translate->x,translate->y,translate->z);
    ofRotateXDeg(rotate2);
    ofRotateYDeg(rotate2/2);
    ofRotateZDeg(rotate2/4);
    
    
    ofSetColor(46, 206, 242,100); //energy blue
    ofDrawCircle(pos,5);
    polyline.draw();
    
    ofSetColor(227, 227, 227,175); //energy white
    polyline2.draw();

    ofSetColor(35, 165, 217, 150);
    ofDrawSphere(0, 0, 15 + 10*rad);
    ofSetColor(227, 227, 227, 1);
    ofSpherePrimitive sphere = ofSpherePrimitive(50+50*rad,64);
    sphere.drawWireframe();
    
    /*ofPolyline test;
    for (int i=0; i<bands/2; i++){
        test.addVertex(i, -fft[i]*150);
    }*/
    //test.draw();
    ofPopMatrix();
    //gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == OF_KEY_RIGHT){
        mRight=true;
    }
    if (key == OF_KEY_LEFT){
        mLeft=true;
    }
    if (key == OF_KEY_UP){
        mUp=true;
    }
    if (key == OF_KEY_DOWN){
        mDown=true;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == OF_KEY_RIGHT){
        mRight=false;
    }
    if (key == OF_KEY_LEFT){
        mLeft=false;
    }
    if (key == OF_KEY_UP){
        mUp=false;
    }
    if (key == OF_KEY_DOWN){
        mDown=false;
    }
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
