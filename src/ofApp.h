#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "sprinkle.h"
#include "donut_cop.h"
#include "ofxGui.h"
#include "ofxColorGradient.h"
#include "ofxAssimpModelLoader.h"

#include "lightManager.h"

#include "thing.h"


class ofApp : public ofBaseApp{

public:

    // Generic OF functions
    void setup();
    void update();
    void draw();

    // OF Events
    void windowResized(int w, int h);
    void keyPressed(int key);

    ofVec3f mapToScreen(ofVec3f input);



    DonutCop donutCop;

    // Sprinkle functions
    std::vector<Sprinkle> sprinkles;  // The vector of sprinkles
    void createSprinkles();
    void removeSprinkles();
    

    ofxPanel params;
    ofParameter<bool> bEnableIndices;
    ofParameter<int> connectionDistance;
    ofParameter<bool> bDebug;
    
    ofxPanel lightGuiMain;
    ofParameter<bool> bShowLights;
    
    
    ofxPanel camGui;
    ofParameter<float> fps;
    ofParameter<bool> bCamDebug;
    ofParameter<float> fov;
    ofParameter<bool> centerCam;
    ofParameter<bool> sideCam;
    ofParameter<float> camPosX;
    ofParameter<float> camPosY;
    ofParameter<float> camPosZ;
    ofParameter<float> lookAtX;
    ofParameter<float> lookAtY;
    ofParameter<float> lookAtZ;
    

    
    ofxPanel objectGui;
    
    
    bool bShowGui;
//    ofParameter<float>;

    ofMesh mesh;
    of3dPrimitive noseMesh;

    float width, height;
    ofxAssimpModelLoader model;
    int numModelVerts;

    ofCamera cam;
    
    
    LightManager lights;

    vector<Thing> things;


    ofxColorGradient<ofColor> gradient;
};
