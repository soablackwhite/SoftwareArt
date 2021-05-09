#include "ofApp.h"


//MOVEMENT
bool pauseB = true;
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
ofVec3f pos3;
ofVec3f pos4;

float u; //latitude
float v; //longitude
float u2; //latitude
float v2; //longitude
float u3; //latitude
float v3; //longitude
float u4; //latitude
float v4; //longitude

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
    
    u2 = ofRandom(2*PI);
    v2 = ofRandom(PI);
    
    u3 = ofRandom(2*PI);
    v3 = ofRandom(PI);
    
    u4 = ofRandom(2*PI);
    v4 = ofRandom(PI);
    
    stepU = PI/50;
    stepV = PI/50;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    if (pauseB==true){
        
    }
    else{
        //sound stuff
        rad=0;
        if (sound.getPosition()>0.7 || !sound.isPlaying()){
            counter*=0.995;
            if(zoom>-800 && counter>0.001){
                zoom-=sound.getPosition()*sound.getPosition();
            }
        }
        rotate2+=counter;

        
        
        
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
        
        v4+=5*PI*speedV + 0.01*ofNoise(0.1+noiseV*0.016*ofGetElapsedTimef());
        u4+=5*PI*speedU + 0.01*ofNoise(0.3+noiseU*0.09*ofGetElapsedTimef());
        
        v3+=5*PI*speedV + 0.01*ofNoise(0.05+noiseV*0.02*ofGetElapsedTimef());
        u3+=5*PI*speedU + 0.01*ofNoise(0.009+noiseU*0.015*ofGetElapsedTimef());
        
        
        //converting from angular to planar coordinates
        if(sound.getPosition()<0.8 && sound.isPlaying()){
            pos.x = radius * sin(u) * cos(v);
            pos.y = radius * sin(u) * sin(v);
            pos.z = radius * cos(u);
            
            pos2.x = radius * sin(u2) * cos(v2);
            pos2.y = radius * sin(u2) * sin(v2);
            pos2.z = radius * cos(u2);
            
            pos3.x = radius * sin(u3) * cos(v3);
            pos3.y = radius * sin(u3) * sin(v3);
            pos3.z = radius * cos(u3);
            
            pos4.x = radius * sin(u4) * cos(v4);
            pos4.y = radius * sin(u4) * sin(v4);
            pos4.z = radius * cos(u4);
        } else{
            pos.x = ofLerp(pos.x, 0, 0.01);
            pos.y = ofLerp(pos.y, 0, 0.01);
            pos.z = ofLerp(pos.z, 0, 0.01);
            
            pos2.x = ofLerp(pos2.x, 0, 0.01);
            pos2.y = ofLerp(pos2.y, 0, 0.01);
            pos2.z = ofLerp(pos2.z, 0, 0.01);
            
            pos3.x = ofLerp(pos3.x, 0, 0.01);
            pos3.y = ofLerp(pos3.y, 0, 0.01);
            pos3.z = ofLerp(pos3.z, 0, 0.01);
            
            pos4.x = ofLerp(pos4.x, 0, 0.01);
            pos4.y = ofLerp(pos4.y, 0, 0.01);
            pos4.z = ofLerp(pos4.z, 0, 0.01);
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
        if (nPts3 < MAXPOINTS) {
            pts3[nPts3].x = pos3.x;
            pts3[nPts3].y = pos3.y;
            pts3[nPts3].z = pos3.z;
            nPts3++;
        } else {
            nPts3=0;
        }
        if (nPts4 < MAXPOINTS) {
            pts4[nPts4].x = pos4.x;
            pts4[nPts4].y = pos4.y;
            pts4[nPts4].z = pos4.z;
            nPts4++;
        } else {
            nPts4=0;
        }
        
        polyline.addVertex(ofPoint(pos.x, pos.y, pos.z));
        polyline2.addVertex(ofPoint(pos2.x, pos2.y, pos2.z));
        polyline3.addVertex(ofPoint(pos3.x, pos3.y, pos3.z));
        polyline4.addVertex(ofPoint(pos4.x, pos4.y, pos4.z));
    }
    
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
    
    
    ofSetColor(46, 206, 242,75); //energy blue
    ofDrawCircle(pos,5);
    polyline.draw();
    
    ofSetColor(46, 206, 242,75); //energy blue
    ofDrawCircle(pos3,5);
    polyline3.draw();
    
    ofSetColor(46, 206, 242,75); //energy blue
    ofDrawCircle(pos4,5);
    polyline4.draw();
    
    ofSetColor(227, 227, 227,75); //energy white
    ofDrawCircle(pos2,5);
    polyline2.draw();

    ofSetColor(35, 165, 217, 150);
    //ofDrawSphere(0, 0, 15 + 10*rad);
    ofSetColor(227, 227, 227, 3);
    ofSpherePrimitive sphere = ofSpherePrimitive(25+100*rad,64);
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
    if (key == OF_KEY_RETURN){
        pauseB=!pauseB;
        sound.setLoop(false);
        sound.play();
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
