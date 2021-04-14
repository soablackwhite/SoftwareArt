## Rubik's cube simulator

I guess the only thing special about this is it's 100% original code. I saw an instagram motion artist make this and I thought I'd try to do the same. I love black and white aesthetics so I sticked to that and only added one color for the wireframes.

Here I'm using an array of objects 'myCube'.
```C++

//create our big boi
for (int i=0; i<total; i++){
        for (int j=0; j<total; j++){
            for (int k=0; k<total; k++){
                cubes[total*total*i+total*j+k]= myCube((i-1)*offset, (j-1)*offset, (k-1)*offset, size, 255);
            }
        }
    }
```

Here I'm randomizing the shuffling (alignment, direction, column, etc) everytime the remainder of the count divided by PI/4 is 0.
```C++
void ofApp::shuffleMe(){
    indice=(int)ofRandom(0,3);
    alignement=ofRandom(0,2);
    if (ofRandom(10)>5){
        sens=1;
    } else{
        sens=-1;
    }
}
```

The rotation code is messy and while it's not hardcoded it could've been more elegant. 
![GIF](https://github.com/soablackwhite/SoftwareArt/blob/main/Week%203:%20rubikSimulator/Kapture%202021-04-12%20at%2014.56.33-min.gif)
