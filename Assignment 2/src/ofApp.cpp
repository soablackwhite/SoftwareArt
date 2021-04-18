#include "ofApp.h"
float h; //center x coord
float k; //center y coord
float r1; //radius of the bend
float r2; //radius of the bend
float radius; //of the tunnel
float d = 0.08; //density of particles
float step = 0;
int cols = 50;
int rows = 50;
float angles[50*50];
float angles2[50*50];
//--------------------------------------------------------------
void ofApp::setup(){
    r1=ofGetHeight()/2;
    r2=ofGetHeight()/8;
    
    ofBackground(28); //silver
    //ofBackground(28); //light black
    
    
    //GUI
    gui.setup();
    gui.add(noise.set("noise", 0.0034, 0, 0.01));
    gui.add(threshold.set("threshold", 137, 0, 200));
    gui.add(speedX.set("horizontal speed", 0, 0, 1));
    gui.add(speedY.set("vertical speed", 0, 0, 1));
    gui.add(speedZ.set("depth speed", 0, 0, 1));
    gui.add(lightPos.set("light position", ofVec3f(-816, -448, -2367), ofVec3f(-2000, -2000, -4000), ofVec3f(2000, 2000, 4000)));
    //transforms
    transform.setName("Transform");
    transform.add(zoom.set("zoom", 300, -1000, 1000));
    transform.add(rotate.set("rotation", ofVec3f(180, 0, 0), ofVec3f(0, 0, 0), ofVec3f(360, 360, 360)));
    transform.add(translate.set("translate", ofVec3f(0, 0, 0), ofVec3f(-500, -500, -500), ofVec3f(500, 500, 500)));
    transform.add(radii.set("radii", ofVec3f(ofGetHeight()/2, 522, 1000), ofVec3f(0, 0, 0), ofVec3f(ofGetHeight(), 1000, 1000)));
    gui.add(transform);
    
    //radii
    radius = radii -> x;
    r1 = radii -> y;
    r2 = radii -> z;
    
    for(int i=0; i<=50; i++){
        
        //define centers of circles, this is the bending of the tunnel
        for (int j=0; j<=50; j++){
            
            angles[i*j+j] = ofRandom(135);
            float angle = ofDegToRad(angles[i*j+j]);
            float cx = 0;
            float cy = r1*cos(angle);
            float cz = r2*sin(angle);
            
            //draw circles
            angles2[i*j+j] = ofRandom(360);
            float angle2 = ofDegToRad(angles2[i*j+j]);
            float x = cx + radius*cos(angle2);
            float y = cy + radius*sin(angle2);
            float z = 2*cz;
            mesh.addVertex(ofPoint(x,y,z));
            if ((int)((i))%2==0){
                mesh.addColor(ofFloatColor(1,.5)); //neon blue
                //mesh.addColor(ofFloatColor(.04,.97,1,1)); //neon blue
            } else {
                //mesh.addColor(ofFloatColor(1,.325,.73,1));
                mesh.addColor(ofFloatColor(1,.5)); //neon blue
            }
            
        }
    }
    
    // now it's important to make sure that each vertex is correctly connected with the
    // other vertices around it. This is done using indices, which you can set up like so:
}


//--------------------------------------------------------------
void ofApp::update(){
    light.setPosition(lightPos->x, lightPos->y, lightPos->z);
    radius = radii -> x;
    r1 = radii -> y;
    r2 = radii -> z;
    glEnable(GL_POINT_SMOOTH);
    //glPointSize(1.0);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    //mesh.clear();
    int count=0;
    for(int i=0; i<=50; i++){
        for (int j=0; j<=50; j++){
            ofVec3f position = mesh.getVertex(count); //get pos
            
            //noise to move stuff
            float noiseBend = ofMap(ofNoise(count, 3*ofGetElapsedTimef()), 0, 1, 0, noise*135);
            float noiseCircle = ofMap(ofNoise(count, .1*ofGetElapsedTimef()), 0, 1, 0, noise*360);
            float angle;
            if (step + noiseBend + angles[i*j+j] >= 135){
                angle = ofDegToRad((step + angles[i*j+j] + noiseBend)-135);
            } else {
                angle = ofDegToRad(step + angles[i*j+j] + noiseBend);
            }
            float cx = 0;
            float cy = r1*cos(angle);
            float cz = r2*sin(angle);
            
            //draw circles
            float angle2 = angles2[i*j+j];
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
    /*for (int i = 0; i < l; i++){ //big circle
        for (int j=0; j<360*d+1; j++){
            
            float angle = ofDegToRad(j/d);
            ofVec3f position = mesh.getVertex(count); //get pos
            
            //noise to move stuff
            float noiseX = ofMap(ofNoise(count, ofGetElapsedTimef()), 0, 1, 0, 360*noise);
            float noiseY = ofMap(ofNoise(count, ofGetElapsedTimef()), 0, 1, 0, 360*noise);
            
            //parametric torus equation
            position.x =  r*cos(angle+noiseX);
            position.y =  r*sin(angle+noiseY);
            position.z +=1;
            
            //assign value and increment noise position
            mesh.setVertex(count, position);
            count++;
        }
    }*/
}

//--------------------------------------------------------------
void ofApp::draw(){
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
                if ((int)((i))%2==0){
                    //ofSetColor(0, ofMap(-distance, -threshold, 0, 0, 255));
                    ofSetColor(8, 247,254, ofMap(-distance, -threshold, 0, 0, 255)); //neon blue
                    //ofSetColor(5, 226,215, ofMap(-distance, -threshold, 0, 0, 255)); //light neon blue
                    //ofSetColor(151, 228, 235, ofMap(-distance, -threshold, 0, 0, 255)); // super light neon blue
                    //ofSetColor(215, 215, 215, ofMap(-distance, -threshold, 0, 0, 255)); //light silver
                    //ofSetColor(211, 174, 54, ofMap(-distance, -threshold, 0, 0, 255));//dark silver
                    //ofSetColor(211, 174, 54, ofMap(-distance, -threshold, 0, 0, 255)); //dark gold
                    
                    

                } else {
                    //ofSetColor(0, ofMap(-distance, -threshold, 0, 0, 255));
                    //ofSetColor(254, 83, 187, ofMap(-distance, -threshold, 0, 0, 255));//neon pink
                    ofSetColor(250, 38, 160, ofMap(-distance, -threshold, 0, 0, 255));//light neon pink
                    //ofSetColor(239, 168, 235, ofMap(-distance, -threshold, 0, 0, 255)); // super light neon pink
                    //ofSetColor(201, 176, 55, ofMap(-distance, -threshold, 0, 0, 255)); //light gold
                    //ofSetColor(211, 174, 54, ofMap(-distance, -threshold, 0, 0, 255)); //dark gold
                    //ofSetColor(249,224,82, ofMap(-distance, -threshold, 0, 0, 255));//high energy yellow
                    
                    
                }
                ofDrawLine(pos1, pos2);
            }
        }
    }
    //mesh.drawVertices();
    ofSetColor(255,5);
    //camera.end();
    ofPopMatrix();
    //gui.draw();
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
