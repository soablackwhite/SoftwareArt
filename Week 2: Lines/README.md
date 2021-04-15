# Wobbly lines

## Concept & Code
Points are scattered throughout the canvas, and lines are drawn for points that are close enough to each other. The GUI allows the user to vary line width and the distance threshold for drawing the line. An uncertainty factor can also be modified to make the structure look like it's shaking.

```C++
    for(int i=0; i<total/2; i++){ //we stop at total/2 to avoid double counting
        for(int j=total/2; j<total; j++){
            if (ofDist(points[j].x, points[j].y,points[i].x, points[i].y)<=minDist){
                ofDrawLine(points[i].x, points[i].y, points[j].x+ofRandom(-shake,shake), points[j].y+ofRandom(-shake,shake));
                }
        }
    }
```

## Colors & GIF
I'm sticking with black and white for this assignment. I have a minimalist approach to aesthetics, and I can't think of an interesting color variation that would look better than good old black and white.


![img2](https://github.com/soablackwhite/SoftwareArt/blob/main/Week%202:%20Lines/ezgif-4-57d55c655f92.gif)

