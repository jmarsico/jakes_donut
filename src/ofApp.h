#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "sprinkle.h"
#include "donut_cop.h"
#include "ofxGui.h"
#include "ofxColorGradient.h"


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
//    ofParameter<float>;

    ofMesh mesh;

    float width, height;


    ofxColorGradient<ofColor> gradient;
};
