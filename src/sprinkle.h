#pragma once
#include "ofMain.h"
#include "ofxOsc.h"
#include "LightSystem2D.h"


class Sprinkle{
  public:
 
    // Constructors
    Sprinkle(const ofxOscMessage &m);
    Sprinkle(float maxVel, float maxAcc);
    
    // Standard OF functions
    void draw();
    void update(float maxVel, float maxAcc);
    
    // Custom functions
    ofxOscMessage createOSCMessage() const;
    bool isOffScreen();
    
    float getX() const {return loc.x;};
    float getY() const {return loc.y;};
    ofVec2f getLoc() { return loc;};
    float getfree1() const { return free1;};
    float getfree2() const { return free2;};
    
    ofx::Shape2D::SharedPtr shape = std::make_shared<ofx::Shape2D>();
    
    ofPath p;
    ofVec2f loc;


  protected:
    
    
    float maxY;
    float xVel;
    float yVel;
    float xAcc;
    float yAcc;
    float free1;
    float free2;
};
