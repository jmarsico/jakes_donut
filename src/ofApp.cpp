#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofBackground(0);

    makeLights();
//    makeShapes();

    
    rotatingLight = std::make_shared<ofx::Light2D>();
    rotatingLight->setPosition(ofVec3f(2.0f * ofGetWidth() / 3, 2.0f * ofGetHeight() / 3));
    rotatingLight->setViewAngle(ofDegToRad(120));
    rotatingLight->setColor(ofColor(255));
    lightSystem.add(rotatingLight);

};

//--------------------------------------------------------------
void ofApp::update(){

    donutCop.update(sprinkles.size());

    // Update the sprinkle system
    for (auto& p : sprinkles) {
        p.update(donutCop.maxVelocity(),donutCop.maxAcceleration());
    }

    // add new sprinkles from messages
    while (donutCop.hasNewSprinkles()) {
    sprinkles.push_back(donutCop.getSprinkle());
    }
    

    
    
    lightSystem.clearShapes();
    
    for(auto& s : sprinkles){
        ofPath p;
        ofVec2f temp(ofMap(s.loc.x, 0., 1., 0., ofGetWidth()), ofMap(s.loc.y, 0., 1., 0, ofGetHeight()));
//        temp.x = ofMap(s.loc.x, 0., 1., 0, ofGetWidth());
//        temp.y = ofMap(s.loc.y, 0.f, 1.f, 0, ofGetHeight());
        p.setMode(ofPath::POLYLINES);
        p.circle(temp, 2);
        
        ofx::Shape2D::SharedPtr shape = std::make_shared<ofx::Shape2D>();
        shape->setShape(p.getOutline()[0]);
        lightSystem.add(shape);

    }
    
    rotatingLight->setAngle(ofWrapRadians(rotatingLight->getAngle() + (PI / 360.0f)));
    rotatingLight->setPosition(ofVec3f(ofGetMouseX(),
                                       ofGetMouseY(),
                                       rotatingLight->getPosition().z));
    

    createSprinkles();
    removeSprinkles();
}

//--------------------------------------------------------------
void ofApp::draw(){
//    for (auto& p : sprinkles) { p.draw();}
    ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, 10);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){}
void ofApp::keyPressed(int key) {
    
    if (key == 32){donutCop.setId(1);}
    
    if(key == 'l'){makeLights();}

}

//--------------------------------------------------------------
void ofApp::createSprinkles() {

    // Check with the donut cop if you're allowed to create a new sprinkle
    if (donutCop.allowedToCreateSprinkle(sprinkles.size())) {

        // Create a new sprinkle
        Sprinkle p(donutCop.maxVelocity(), donutCop.maxAcceleration());

        // Add it to the sprinkles list
        sprinkles.push_back(p);
        lightSystem.add(p.shape);

        // Tell the cop that we created one, so it can keep track
        // of how many have been created. 
        donutCop.mentionNewSprinkle();
        
        
  }
}

//--------------------------------------------------------------
void ofApp::removeSprinkles() {

    // Loop through and broadcast offscreen sprinkles
    for (auto& p : sprinkles) {
        if (p.isOffScreen()){
          donutCop.broadcastSprinkle(p);
        }
    }

    
    
    // Loop through and remove offscreen sprinkles 
    sprinkles.erase(
        remove_if(sprinkles.begin(), sprinkles.end(), [](Sprinkle p) { return p.isOffScreen();}),
        sprinkles.end());
}


void ofApp::makeLights()
{
    for (int i = 0; i < 2; ++i)
    {
        ofx::Light2D::SharedPtr light = std::make_shared<ofx::Light2D>();
        
        ofVec3f position(ofRandomWidth(), ofRandomHeight(), 0);
        ofFloatColor color(ofRandomuf(), ofRandomuf(), ofRandomuf(), 1);
        
        float radius = ofRandom(300, 1000);
        
        light->setPosition(position);
        light->setRadius(radius);
        light->setColor(color);
        
        
        lightSystem.add(light);
    }
}


void ofApp::makeShapes()
{
    for (int i = 0; i < 4; ++i)
    {
        ofx::Shape2D::SharedPtr shape = std::make_shared<ofx::Shape2D>();
        
        ofRectangle rect;
        rect.setFromCenter(ofRandomWidth(),
                           ofRandomHeight(),
                           ofRandom(10, 20),
                           ofRandom(10, 20));
        
        shape->setShape(ofPolyline::fromRectangle(rect));
        lightSystem.add(shape);
    }
}

