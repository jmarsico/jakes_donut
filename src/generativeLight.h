//
//  generativeLight.h
//  abstractions
//
//  Created by Jakob Marsico on 7/12/16.
//
//

#ifndef __abstractions__generativeLight__
#define __abstractions__generativeLight__

#include <stdio.h>
#include "ofMain.h"

class GenerativeLight{
public:
    GenerativeLight(){};
    void init(int ID);
    void update();
    ofFloatColor chooseColor(int color);
    
    
    ofLight light;
    
    ofParameterGroup params;
    ofParameter<bool> bNoiseMotion;
    ofParameter<float> noiseSpeed;
    ofParameter<float> transX;
    ofParameter<float> transY;
    ofParameter<float> transZ;
    ofParameter<float> lookAtX;
    ofParameter<float> lookAtY;
    ofParameter<float> lookAtZ;
    ofParameter<float> spec;
    ofParameter<float> att;
    ofParameter<float> diff;
    ofParameter<float> amb;
    ofParameter<int> col;
    
    
    float xNoiseCounter;
    float yNoiseCounter;
    float zNoiseCounter;
    
    int width,height;
    

};



#endif /* defined(__abstractions__generativeLight__) */
