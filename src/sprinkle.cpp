#include "sprinkle.h"

//--------------------------------------------------------------
// Generate the sprinkle with random parameters
Sprinkle::Sprinkle(float maxVel, float maxAcc) {
    width = ofGetWidth();
    height = ofGetHeight();

    maxY = float(height) / float(width);

    loc.x = ofRandomuf();
    loc.y = ofMap(ofRandomuf(),0.0,1.0,0.0,maxY);
    loc.z = ofRandom(1.);
    xVel = ofRandomf() * maxVel;
    yVel = ofRandomf() * maxVel;
    xAcc = ofRandomf() * maxAcc;
    yAcc = ofRandomf() * maxAcc;
    free1 = ofRandomuf();
    free2 = ofRandomuf();

    
    
}

//--------------------------------------------------------------
// Generate the sprinkle from an OSC message
Sprinkle::Sprinkle(const ofxOscMessage &m) {
    width = ofGetWidth();
    height = ofGetHeight();

  maxY = float(height) / float(width);

  loc.x = 0;
  loc.y = m.getArgAsFloat(0);
  xVel = m.getArgAsFloat(1);
  yVel = m.getArgAsFloat(2);
  xAcc = m.getArgAsFloat(3);
  yAcc = m.getArgAsFloat(4);
  free1 = m.getArgAsFloat(5);
  free2 = m.getArgAsFloat(6);
  loc.z = free1;

  // Handle starting on the right
  if (xVel < 0 ) { loc.x = 1.0;}
}

//--------------------------------------------------------------
void Sprinkle::update(float maxVel, float maxAcc) {
  
  // bounce off top and bottom
  if (loc.y >= maxY || loc.y <= 0.0) {
    yVel *= -1.0;
    yAcc *= -1.0;
  }

    
  
    
  loc.x += xVel;
  loc.y += yVel;
  xVel += xAcc;
  xVel += yAcc;
  xVel = ofClamp(xVel,-maxVel, maxVel);
  yVel = ofClamp(yVel, -maxVel, maxVel);
//  xAcc = maxAcc*ofRandomf();
//  yAcc = maxAcc*ofRandomf();
}

//--------------------------------------------------------------
void Sprinkle::draw() {
  ofFill();
  ofSetColor(0);
    ofVec3f tempLoc;
  tempLoc.x = ofMap(loc.x,0.0, 1.0, 0.0, width);
  tempLoc.y = ofMap(loc.y,0.0, maxY, 0.0, height);
    
  ofDrawSphere(tempLoc, 10);
}

//--------------------------------------------------------------
bool Sprinkle::isOffScreen() {
  return loc.x > 1 || loc.x < 0;
}

//--------------------------------------------------------------
ofxOscMessage Sprinkle::createOSCMessage() const {

  ofxOscMessage m;
  m.addFloatArg(loc.y);
  m.addFloatArg(xVel);
  m.addFloatArg(yVel);
  m.addFloatArg(xAcc);
  m.addFloatArg(yAcc);
  m.addFloatArg(free1);
  m.addFloatArg(free2);
  return m;
}
