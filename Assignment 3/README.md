# Assignment 3: Music Vis

## Concept
4 Walkers are scattered around the surface of a sphere and navigate it based on a noise function that fluctuates with the beat of the music.

## Process
I think this was my most disappointing project in this semester, I really wanted to make a spherical grid of hexagons, but I really couldn't make it work on time. 

My second idea was the walkersm where the thickness of the brush would vary with the music and new shapes could be drawn based on the beat. However that proved to be extremely difficult, because the brush would have to map into the spherical surface of a brush so drawing a circle at point X would just draw a flat brush stroke that will not stick to the spherical surface. That was an oversight on my part and something I spent a lot of time trying to remedy but couldn't. 

Another thing I wanted to do was having the camera view follow the brush. That turned out horrible and stretched into 6 hours of notebook scribbling that ended in vain. The camera follow the position of the 'walker' brush but never rotate with it the way I wanted it to. So basically the camera always looked at the same direction no matter what, even if its position corresponded to the walker's position. With some tinkering I managed to create something sort of working but really it looked awful and wasn't the smooth 1st POV vision I had. So instead I just kept a fixed POV while rotating the sphere to give a nice aesthetic effect.

These 2 failures greatly limited me in my direction because I no longer could find something that depended on the music, as my objective was to map the music as POSITIONS on the sphere, and make shapes spawn on it based on the note played. But since the shapes were flat and wouldn't map to the sphere, not having a variable POV made it look very ugly. I completely changed my idea and added an interactive drawing element where the user could have their own walker, alongside the 3 others that interact with the music.

The end note lerps the rotation, the zoom out, and the positions of the walkers towards the center. This assignment is very hard coded and I am truly disappointed in it. But I learned a lot from my hexagon sphere research so I don't regret not dropping the idea, as I will further research approximations during the summer.

## Code
This part is how the 3 scripted walker brushes move
```C++
        v+=5*PI*speedV + 0.01*ofNoise(noiseV*0.01*ofGetElapsedTimef());
        u+=5*PI*speedU + 0.01*ofNoise(noiseU*0.01*ofGetElapsedTimef());
        
        v4+=5*PI*speedV + 0.01*ofNoise(0.1+noiseV*0.016*ofGetElapsedTimef());
        u4+=5*PI*speedU + 0.01*ofNoise(0.3+noiseU*0.09*ofGetElapsedTimef());
        
        v3+=5*PI*speedV + 0.01*ofNoise(0.05+noiseV*0.02*ofGetElapsedTimef());
        u3+=5*PI*speedU + 0.01*ofNoise(0.009+noiseU*0.015*ofGetElapsedTimef());
```
And this is how I do the final moments' animation
```C++
        if (sound.getPosition()>0.7 || !sound.isPlaying()){
            counter*=0.995;
            if(zoom>-800 && counter>0.001){
                zoom-=sound.getPosition()*sound.getPosition();
            }
        }
        rotate2+=counter;
        
        ///some other messy code
        else {
                pos.x = ofLerp(pos.x, 0, 0.01);
                pos.y = ofLerp(pos.y, 0, 0.01);
                pos.z = ofLerp(pos.z, 0, 0.01);
        }
```


# Image & Video
https://vimeo.com/547149242
![img1](https://github.com/soablackwhite/SoftwareArt/blob/main/Assignment%202/mysphere.png)
