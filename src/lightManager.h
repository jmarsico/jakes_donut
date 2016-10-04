//
//  lightMananger.h
//  abstractions
//
//  Created by Jakob Marsico on 7/12/16.
//
//

#ifndef __abstractions__lightMananger__
#define __abstractions__lightMananger__

#include <stdio.h>
#include "ofMain.h"
#include "generativeLight.h"

class LightManager {
public:
    LightManager(){};
    void init();
    void update();
    void draw();
    void enableLights();
    void disableLights();
    ofFloatColor chooseColor(int color);
    
    
    
    vector<GenerativeLight> lights;
    
//    ofLight ambientLight;
    
    
    //lightGui
    ofParameterGroup lightGui;
    ofParameter<float> ambient;
    ofParameter<bool> bShowLightdebug;

    
};

#endif /* defined(__abstractions__lightMananger__) */
