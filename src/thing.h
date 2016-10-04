//
//  thing.h
//  jakes_donut
//
//  Created by Jakob Marsico on 10/3/16.
//
//

#ifndef __jakes_donut__thing__
#define __jakes_donut__thing__

#include <stdio.h>
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class Thing {
public:
    Thing(){};
    void init(string fileName, int ID);
    void update();
    void draw();
    
    ofxAssimpModelLoader model;
    of3dPrimitive mesh;
    
    
    ofParameterGroup gui;
    ofParameter<bool> bSetNoise;
    ofParameter<float> scale;
    ofParameter<float> xRot;
    ofParameter<float> yRot;
    ofParameter<float> zRot;
    ofParameter<float> xPos;
    ofParameter<float> yPos;
    ofParameter<float> zPos;


    float roll;
    float pan;
    float tilt;
    
    int width, height;
    
    
};

#endif /* defined(__jakes_donut__thing__) */
