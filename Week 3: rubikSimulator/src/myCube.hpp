//
//  myCube.hpp
//  rubikSimulator
//
//  Created by NYUAD on 11/04/2021.
//

#ifndef myCube_hpp
#define myCube_hpp

#include <stdio.h>
#include <ofMain.h>

class myCube{
public:
    
    void setup();
    void draw();
    
    void rotateMe();
    // dummy constructor
    myCube() {}
    
    

    
    
    // variables
    float x;
    float y;
    float z;
    
    float constx;
    float consty;
    float constz;
    
    float anchorx;
    float anchory;
    float anchorz;
    
    float size;
    int color;

    myCube(float _x, float _y, float _z, float _size, int _color){
        constx = _x;
        consty = _y;
        constz = _z;
        x = _x;
        y = _y;
        z = _z;
        size = _size;
        color = _color;
    };
};

#endif /* myCube_hpp */
