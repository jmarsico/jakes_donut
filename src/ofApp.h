#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "sprinkle.h"
#include "donut_cop.h"
#include "LightSystem2D.h"


class ofApp : public ofBaseApp{

public:

    // Generic OF functions
    void setup();
    void update();
    void draw();

    // OF Events
    void windowResized(int w, int h);
    void keyPressed(int key);

    void makeLights();
    void makeShapes();

    DonutCop donutCop;

    // Sprinkle functions
    std::vector<Sprinkle> sprinkles;  // The vector of sprinkles
    void createSprinkles();
    void removeSprinkles();
    
    ofx::LightSystem2D lightSystem;
    ofx::Light2D::SharedPtr rotatingLight;


};
