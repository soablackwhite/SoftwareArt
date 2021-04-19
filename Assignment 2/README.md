# Assignment 2: Constellation Pipe

## Color
The user can use the triad slider to change the hue of the particles. The user essentially only changes the color of the core, and the other orbits are automatically adapted as the corresponding triadic colors. Considering the hue is up to 360, I basically increment 120 twice for each color, and map it to the 255 value.

## Shape
I chose spheres because spheres look cool, and it just seemed more consistent with all the trigonometry I was using for this.

## Code
I used for loops and polar coordinates to position particles in 2 different orbits around the core, and applied rotation on the appropriate axes to move them. The size of the core pulses in a sine wave, while its skeleton pulses in a cosine wave, and so they meet periodically.
```C++
    //orbiting particles
    for(int i=0; i<particles; i++){
        float angle = ofMap(i, 0, particles, -PI, PI);
        
        //vertical orbit
        ofPushMatrix();
        ofRotateZDeg(rotate); //rotation on the null component
        ofSetColor(vertColor);
        ofDrawSphere(radius*cos(angle), radius*sin(angle), 0, size);
        ofPopMatrix();
        
        //horizontal orbit
        ofPushMatrix();
        ofRotateYDeg(rotate); //rotation on the null component
        ofSetColor(horColor);
        ofDrawSphere(radius*cos(angle), 0, radius*sin(angle), size);
        ofPopMatrix();
    }
```

## Process
I got done faster than I thought and it was relatively easy so I didn't know what to do to make my project more elaborate/aesthetically pleasing. Then I realized that it wasn't the best concept for a still image as orbitals have very few non-dynamic properties. The hardest part was making a triad of colors. One thing I failed at and which I still don't understand is coming up with an elegant way of coding the cycling 360 degree color rotation (so it doesn't go beyond 360 degrees). At some point my frustration with trig functions and the fact that OF uses 255 for HSV resulted in this:
```C++
void convertMe(float myColor){
    myColor=ofMap(ofRadToDeg(asin(sin(ofDegToRad(myColor)))), 0, 360, 0, 255);
    return(myColor);
}
```
I also wanted to use classes and parameters but the way I coded my application before the realization made it very difficult to convert.

## Images:
![img1](https://github.com/soablackwhite/SoftwareArt/blob/main/Assignment%202/neonTunnel.gif)
