#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofEnableDepthTest();
    ofSetFrameRate(60);

    mesh.setMode(OF_PRIMITIVE_LINES);
    mesh.enableIndices();
    mesh.enableColors();
    width = ofGetWidth();
    height= ofGetHeight();
    
    cam.setupPerspective();
    cam.setNearClip(10.f);
    cam.setFarClip(6000.0f);


    gradient.addColor( ofColor::fromHex(0xaed9da) );
    gradient.addColor( ofColor::fromHex(0x3ddad7) );
    gradient.addColor( ofColor::fromHex(0x135589) );


    lights.init();
    
    
    for(size_t i = 0; i < 4; i++){
        Thing t;
        t.init("nose.3ds", i);
        things.push_back(t);
    }


    params.setup("params");
    params.add(bDebug.set("debug", false));
    params.add(bEnableIndices.set("indices", true));
    params.add(connectionDistance.set("conn dist", 100, 10, 500));
    params.loadFromFile("settings.xml");
    params.setPosition(10,10);
    
    lightGuiMain.setup("lightGuiMain", "lightGui.xml");
    lightGuiMain.add(bShowLights.set("show lights", true));
    lightGuiMain.add(lights.lightGui);
    lightGuiMain.setPosition(params.getWidth() + 20, 10);
    lightGuiMain.loadFromFile("lightGui.xml");
    
    camGui.setup("camera", "cameraGui.xml");
    camGui.add(fps.set("FPS", 0, 0, 90));
    camGui.add(centerCam.set("center", false));
    camGui.add(sideCam.set("side", false));
    camGui.add(bCamDebug.set("cam debug", false));
    camGui.add(fov.set("FOV", 90, 0, 180));
    camGui.add(camPosX.set("cam X", 500.f, -4000.f, 4000.f));
    camGui.add(camPosY.set("cam Y", 500.f, -4000.f, 4000.f));
    camGui.add(camPosZ.set("cam Z", 3000, 0, 4000));
    camGui.add(lookAtX.set("look at X", 600, 0, 2000));
    camGui.add(lookAtY.set("look at Y", 500, 0, 2000));
    camGui.add(lookAtZ.set("look at Z", 0, -200, 2000));
    camGui.setPosition(lightGuiMain.getPosition().x + lightGuiMain.getWidth() + 10, 10);
    camGui.loadFromFile("cameraGui.xml");
    

    
    objectGui.setup("objects", "objectGui.xml");
    for(auto & t : things){
        objectGui.add(t.gui);
    }
    objectGui.loadFromFile("objectGui.xml");
    objectGui.setPosition(10, params.getHeight() + 10);
    
    
    
    bShowGui = false;
    
    donutCop.setId(1);

};

//--------------------------------------------------------------
void ofApp::update(){

    donutCop.update(sprinkles.size());
  //  createSprinkles();
    removeSprinkles();
    fps = (int)ofGetFrameRate();    
    
    if(centerCam){
        camPosX = width/2;
        camPosY = height/2;
        camPosZ = 4000;
        fov = 17.1;
        lookAtX = camPosX;
        lookAtY = camPosY;
        lookAtZ = 0;
        centerCam = false;
    } else if(sideCam) {
        camPosX = -4000;
        camPosZ = 0;
        camPosY = height/2;
        sideCam = false;
    }

    cam.setPosition(camPosX, camPosY, camPosZ);
    cam.lookAt(ofVec3f(width/2, height/2, 0.f));
    cam.setFov(fov);
    
    for(auto& t : things){
        t.update();
    }
    
    
    // Update the sprinkle system
    for (auto& p : sprinkles) {
        p.update(0.1,donutCop.maxAcceleration());
    }

    // add new sprinkles from messages
    while (donutCop.hasNewSprinkles()) {
        sprinkles.push_back(donutCop.getSprinkle());
        mesh.addVertex(sprinkles.back().loc);
        ofColor c = gradient.getColorAtPercent(ofMap(sprinkles.back().getfree2(), 0., 1., 0., 100.));
        mesh.addColor(c);    }
    
    //update the
    for(size_t i = 0; i < mesh.getNumVertices(); i++){
        mesh.setVertex(i, mapToScreen(sprinkles[i].loc));

    }

    model.setPosition(ofGetMouseX(), ofGetMouseY(),0);


    mesh.enableIndices();
    

    if(bEnableIndices){

        mesh.clearIndices();
        int numVerts = mesh.getNumVertices();
        for (int a=0; a<numVerts; ++a) {
            ofVec3f verta = mesh.getVertex(a);
            for (int b=a+1; b<numVerts; ++b) {
                ofVec3f vertb = mesh.getVertex(b);
                int distance = (int)verta.distance(vertb);
                if (distance <= connectionDistance) {
//                    ofLog() << distance;
                    mesh.addIndex(a);
                    mesh.addIndex(b);
                }
            }
        }

        if(mesh.getIndices().size() <= 0) {
            mesh.addIndex(0);
        }

    } else {
        mesh.clearIndices();
        mesh.addIndex(0);
    }

    



}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableLighting();
    
    if(bShowLights){
        lights.enableLights();
        ofSetSmoothLighting(true);
    }
    
    lights.update();
    lights.draw();

    ofBackground(ofColor::fromHex(0x2a93d5));
    
    
    ofEnableDepthTest();
//    for (auto& p : sprinkles) { p.draw();}
    //ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, 10);
    mesh.draw();
    
    if(bDebug){
        for(size_t i = 0; i < mesh.getNumVertices(); i++){
            ofSetColor(mesh.getColor(i));
            ofDrawSphere(mesh.getVertex(i), 10);
        }
    }
    ofSetColor(255);
    
    
    cam.begin();
    for(auto& t : things){
        t.draw();
    }
    ofSetColor(255, 50, 20);
    ofRectangle r;
    r.setFromCenter(ofPoint(width/2, height/2, 0), width, height);
    ofNoFill();
    ofDrawRectangle(r);
    
    cam.end();
    
    
    if(bShowLights) {
        lights.disableLights();
        ofSetSmoothLighting(false);
    }
    
    if(bShowGui){
        ofDisableDepthTest();
        params.draw();
        lightGuiMain.draw();
        camGui.draw();
        objectGui.draw();

    }
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){}
void ofApp::keyPressed(int key) {
    
    if (key == 32){donutCop.setId(1);}
    if (key == 'g'){bShowGui = !bShowGui;}
    

}

//--------------------------------------------------------------
ofVec3f ofApp::mapToScreen(ofVec3f input){
    ofVec3f output;
    output.x = ofMap(input.x, 0., 1., 0, width);
    output.y = ofMap(input.y, 0., 1., 0, height);
    output.z = ofMap(input.z, 0., 1., 0, 1.);

    return output;
}

//--------------------------------------------------------------
void ofApp::createSprinkles() {

    // Check with the donut cop if you're allowed to create a new sprinkle
    if (donutCop.allowedToCreateSprinkle(sprinkles.size())) {

        // Create a new sprinkle
        Sprinkle p(donutCop.maxVelocity(), donutCop.maxAcceleration());


        // Add it to the sprinkles list
        sprinkles.push_back(p);
        mesh.addVertex(sprinkles.back().loc);
        ofColor c = gradient.getColorAtPercent(ofMap(sprinkles.back().getfree2(), 0., 1., 0., 100.));
        mesh.addColor(c);
        // Tell the cop that we created one, so it can keep track
        // of how many have been created. 
        donutCop.mentionNewSprinkle();
        
        
  }
}

//--------------------------------------------------------------
void ofApp::removeSprinkles() {

    // Loop through and broadcast offscreen sprinkles
    for (size_t i = 0; i < sprinkles.size(); i++) {
        if (sprinkles[i].isOffScreen()){
          donutCop.broadcastSprinkle(sprinkles[i]);
          mesh.removeVertex(i);
            mesh.removeColor(i);
        }

    }

    
    
    // Loop through and remove offscreen sprinkles 
    sprinkles.erase(
        remove_if(sprinkles.begin(), sprinkles.end(), [](Sprinkle p) { return p.isOffScreen();}),
        sprinkles.end());
}

