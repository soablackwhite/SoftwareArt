# Interlaced Circles

## Concept
I am thinking of the canvas as a 3x3 grid, where I pick a random x,y pair of coordinates as the center of my interlaced circles. From there on I use polar coordinates and increment by 120 degrees to find the 3 centers of my drawn circles. I think equilateral triangles are very aesthetic and so I linked the 3 centers together with lines, the color of which is the sum of the 2 circles it is linking.
```C++
//choose center of equilateral triangle
    xCenter = ofRandom(ofGetWidth()/3,2*ofGetWidth()/3);
    yCenter = ofRandom(ofGetHeight()/3,2*ofGetHeight()/3);
    
    //first point
    x1 = xCenter+ r*cos(0);
    y11 = yCenter+ r*sin(0);
    
    //second point
    x2 = xCenter+ r*cos(2*PI/3);
    y2 = yCenter+ r*sin(2*PI/3);
    
    //third point
    x3 = xCenter+ r*cos(4*PI/3);
    y3 = yCenter+ r*sin(4*PI/3);

```

## Colors
The circles are  variations of red, green, and blue, with half opacity, and the color of the lines is the average of the color of the two circles they link.
![img2](https://github.com/soablackwhite/SoftwareArt/blob/main/Week%201:%20Circles/Screen%20Shot%202021-04-06%20at%2012.57.14%20PM.png)
