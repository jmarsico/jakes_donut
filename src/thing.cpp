//
//  thing.cpp
//  jakes_donut
//
//  Created by Jakob Marsico on 10/3/16.
//
//

#include "thing.h"

void Thing::init(string fileName, int ID){
    
    width = ofGetWidth();
    height = ofGetHeight();
    
    model.loadModel(fileName);
    mesh.getMesh() = model.getMesh(0);
    mesh.setScale(1.6);
    ofLog() << "num verts: " << model.getMesh(0).getNumVertices();
    mesh.getMesh().setMode(OF_PRIMITIVE_TRIANGLES);
    mesh.getMesh().enableColors();
    mesh.setPosition(width/2, height/2, 0.f);
    mesh.pan(180);
    mesh.tilt(90);
    
    string name = "nose ";
    name += ofToString(ID);
    gui.setName(name);
    gui.add(bSetNoise.set("noise motion", false));
    gui.add(scale.set("scale", 1.5, 1.0, 40.0));
    gui.add(xRot.set("xRot", 0.0, 0.0, 0.1f));
    gui.add(yRot.set("yRot", 0.0, 0.0, 0.1f));
    gui.add(zRot.set("zRot", 0.0, 0.0, 0.1f));
    gui.add(xPos.set("xPos", 0.0, 0.0, 0.1f));
    gui.add(yPos.set("yPos", 0.0, 0.0, 0.1f));
    gui.add(zPos.set("zPos", 0.0, 0.0, 0.1f));
    roll = 0.f;
    pan = 0.f;
    tilt = 0.f;
    
}

void Thing::update(){
    
    mesh.setScale(scale);
    if(bSetNoise){
        mesh.roll(3.f * ofSignedNoise(ofGetElapsedTimef() * xRot));
        mesh.pan(3.f * ofSignedNoise(ofGetElapsedTimef() * yRot));
        mesh.tilt(3.f * ofSignedNoise(ofGetElapsedTimef() * zRot));
        mesh.setPosition(width * ofNoise(ofGetElapsedTimef() * xPos),
                         height * ofNoise(ofGetElapsedTimef() * yPos),
                         20 * ofSignedNoise(ofGetElapsedTimef() * zPos)
                         );
    }
}

void Thing::draw(){
    mesh.drawFaces();
//    mesh.drawAxes(1.f);
}