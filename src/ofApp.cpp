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



    gradient.addColor( ofColor::black );
    gradient.addColor( ofColor::pink );
    gradient.addColor( ofColor::aquamarine );

    model.loadModel("nose.3ds");
    model.setScale(0.5,0.5,0.5);
    model.setPosition(ofGetWidth()/2,ofGetHeight()/2 , 0);
    noseMesh = model.getMesh(0);
    
    ofLog() << "num verts: " << model.getMesh(0).getNumVertices();
    
    noseMesh.setMode(OF_PRIMITIVE_TRIANGLES);
    noseMesh.enableColors();
    
    float scale = 1.f/noseMesh.getNumVertices();

    for(size_t i = 0; i < noseMesh.getNumVertices(); i++){
        noseMesh.addColor(gradient.getColorAtPercent(i * scale ));
    }




    params.setup("params");
    params.add(bDebug.set("debug", false));
    params.add(bEnableIndices.set("indices", false));
    params.add(connectionDistance.set("conn dist", 100, 10, 500));
    params.setPosition(10,20);

    
    bShowGui = false;

};

//--------------------------------------------------------------
void ofApp::update(){

    donutCop.update(sprinkles.size());
    createSprinkles();
    removeSprinkles();

    // Update the sprinkle system
    for (auto& p : sprinkles) {
        p.update(donutCop.maxVelocity(),donutCop.maxAcceleration());
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
    ofBackgroundGradient(ofColor(50,50,50), ofColor(0,0,0), OF_GRADIENT_CIRCULAR);

    ofEnableDepthTest();
//    for (auto& p : sprinkles) { p.draw();}
    ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, 10);
    mesh.draw();
    
    if(bDebug){
        for(size_t i = 0; i < mesh.getNumVertices(); i++){
            ofSetColor(255,0,0);
            ofDrawSphere(mesh.getVertex(i), 20);
        }
    }
    ofSetColor(255);
    cam.lookAt(noseMesh.getCentroid());
    cam.roll(cam.getRoll() + 1.f);
    cam.begin();
    
//    noseMesh.draw();
    noseMesh.drawFaces();
    cam.end();
    
    if(bShowGui){
        ofDisableDepthTest();
        params.draw();
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

