# Assignment 2: Constellation Pipe

## Concept
An animated pipe where the user is surrounded by constellations of different colors.

## Color
I’m using five color schemes: grayscale, neon, tech blue, quicksilver, and NYU. Disregard the names, I’ve made them up. I'll need to figure out a way to recode this into something that isn't a series of if statements. I chose my color couplings based on intuition, and varied the background accordingly. I’ve read a lot about color theory but I’ve found that it manifests in my work more as intuition than a conscious decision-making process.

![img1](https://github.com/soablackwhite/SoftwareArt/blob/main/Assignment%202/Screen%20Shot%202021-04-19%20at%201.05.45%20PM.png)
![img1](https://github.com/soablackwhite/SoftwareArt/blob/main/Assignment%202/Screen%20Shot%202021-04-19%20at%201.03.40%20PM.png)

## Code
This project is four-fold: cylinder, parabola, noise, and constellations. First, the cylinder. I knew for a fact that I wanted a sort of tube/tunnel, so in order to build that I drew circles throughout the length of a line to make the cylinder. Next, I wanted the cylinder to bend. This was the hard part. I found many works involving a torus so I thought I'd do the same thing, and maybe put the camera in the middle of a torus to simulate the tube. But that took too much processing power (I wanted this process to be an interactive application rather than just a gif). So instead I thought I'd just make a parabola, with modifiable variables. But again, understanding the effects of variables in standard quadratic equation was too cumbersome to be practical in parametric GUI incorporation. So I ended up taking the parametric equation of an ellipse, and limiting it to one quadrant (0, PI/2). Along the curve of that ellipse, I basically place the centers of each circle, thus making a bent cylinder. For motion and placement of points, I first scatter them randomly around the surface area equation I wrote in the setup, then I use noise to move them around based on that same equation by varying the angles. Finally, for each point in our mesh, we calculate the distance with other points and trace lines of corresponding opacity. 

```C++
        for(int i=0; i<=rows; i++){
                //define centers of circles, this is the bending of the tunnel
                for (int j=0; j<=cols; j++){

                    angles[i*j+j] = ofRandom(135); //store angular positions
                    float angle = ofDegToRad(angles[i*j+j]);

                    //parametric equation of ellipse
                    float cx = 0;
                    float cy = r1*cos(angle);
                    float cz = r2*sin(angle);

                    //drawing the circles
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
```

# Optimization:
I use noise for the movement but I think this isn't the right code/nature analogy to use for the phenomenon my project describes. The best way to do this would probably be through OOP, creating objects with random speed properties that travel through the length of the equation. I'm also thinking about making this a GIF-making program, which would allow for a perfect loop and enhanced quality without giving up performance (though it'd suck that I can't run it live).


## Images:
![img1](https://github.com/soablackwhite/SoftwareArt/blob/main/Assignment%202/neonTunnel.gif)
![img1](https://github.com/soablackwhite/SoftwareArt/blob/main/Assignment%202/loko-min.gif)
