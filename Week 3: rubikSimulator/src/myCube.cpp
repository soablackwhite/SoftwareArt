//
//  myCube.cpp
//  rubikSimulator
//
//  Created by NYUAD on 11/04/2021.
//

#include "myCube.hpp"

void myCube::setup(){
    
}

void myCube::draw(){
    
    //wireframe
    ofSetColor(196, 184, 132);
    ofNoFill();
    ofDrawBox(x, y, z, size);
    
    //fill
    ofFill();
    ofSetColor(255,90);
    ofDrawBox(x, y, z, size);
}

void myCube::rotateMe(){
    //rotate2++;
    //z=constz*cos(rotate2/100);
    //y=consty*sin(rotate2/100);

}
