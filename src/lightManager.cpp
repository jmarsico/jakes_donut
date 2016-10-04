//
//  lightMananger.cpp
//  abstractions
//
//  Created by Jakob Marsico on 7/12/16.
//
//

#include "lightManager.h"

//--------------------------------------------------------------
void LightManager::init(){
    
    ofFloatColor c0 = ofColor::fromHex(0xE77D6E);
    
    ////////////LIGHTING////////////////
    // turn on smooth lighting //
    ofSetSmoothLighting(true);
    
    lightGui.add(bShowLightdebug.set("Debug", false));
    lightGui.add(ambient.set("ambient", 0.0, 0.0, 1.0));
    
    for(size_t i = 0; i < 2; i++){
        GenerativeLight l;
        l.init(i);
        lights.push_back(l);
        
        lightGui.add(lights[i].params);
        
    }
//    ambientLight.enable();
//    ambientLight.setAmbientColor(ofFloatColor(0.1));
    
}

//--------------------------------------------------------------
void LightManager::update(){
    for(auto & l : lights){
        l.update();
    }
//    ambientLight.setAmbientColor(ofFloatColor(ambient));
}

//--------------------------------------------------------------
void LightManager::draw(){
    if(bShowLightdebug){
        for(auto & l : lights){
            ofSetColor(l.chooseColor(l.col));
            l.light.draw();
            ofDrawArrow(l.light.getPosition(), ofVec3f(l.lookAtX, l.lookAtY, l.lookAtZ));
        }
    }
    
}

//--------------------------------------------------------------
ofFloatColor LightManager::chooseColor(int color){
    
    
    ofFloatColor c;
    switch (color) {
        case 0:
            c.set(1.0, 1.0, 1.0);
            break;
        case 1:
            c = ofColor::fromHex(0xE77D6E);
            break;
        case 2:
            c = ofColor::fromHex(0x3DEBBD);
            break;
        case 3:
            c = ofColor::fromHex(0x3C5F95);
            break;
        case 4:
            c = ofColor::fromHex(0xA453AE);
            break;
        case 5:
            c = ofColor::fromHex(0x162365);
            break;
    }
    
    return c;
}


//--------------------------------------------------------------
void LightManager::enableLights(){
    ofEnableDepthTest();
    ofEnableLighting();
    
    for(auto & l : lights){
        l.light.enable();
    }
    
//    ambientLight.enable();
    
}

//--------------------------------------------------------------
void LightManager::disableLights(){
    ofDisableLighting();
}
