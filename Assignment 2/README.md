# Assignment 2: Constellation Pipe

## Concept
The user can use the triad slider to change the hue of the particles. The user essentially only changes the color of the core, and the other orbits are automatically adapted as the corresponding triadic colors. Considering the hue is up to 360, I basically increment 120 twice for each color, and map it to the 255 value.

## Color
I chose spheres because spheres look cool, and it just seemed more consistent with all the trigonometry I was using for this.

## Code
This project is four-fold: cylinder, parabola, noise, and constellations. First, the cylinder. I knew for a fact that I wanted a sort of tube/tunnel, so in order to build that I drew circles throughout the length of a line to make the cylinder. Next, I wanted the cylinder to bend. This was the hard part. I found many works involving a torus so I thought I'd do the same thing, and maybe put the camera in the middle of a torus to simulate the tube. But that took too much processing power. So instead I thought I'd just make a parabola, with modifiable variables. But again, understanding the effects of variables in standard quadratic equation was too cumbersome to be practical in parametric GUI incorporation. So I ended up taking the parametric equation of an ellipse, and limiting it to one quadrant (0, PI/2). So along the curve of that ellipse, I basically place the centers of each circle, thus making a bent cylinder. For motion and placement of points, I first scatter them randomly around the surface area equation I wrote in the setup, then I use noise to move them around based on that same equation by varying the angles. Finally, for each point in our mesh, we calculate the distance with other points and trace lines of corresponding opacity. 

# Optimization:
I thought I'd somehow use the wireframe and vertex drawing properties of meshes, but I really didn't. I could optimize this by removing the mesh and making my project based on a position array that traces a line between close points.

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
