#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(513,385);
    ofBackgroundHex(0xf0eec2);
    ofSetVerticalSync(true);
    
    runway.setup(this, "http://localhost:8000");
    runway.start();
    
    cam.setup(640,480);
    mySound.load("audio.mp3");
    mySound.play();
    
    
    ofSetLogLevel(OF_LOG_NOTICE);
    
    box2d.init();
    box2d.setGravity(0, 10);
    box2d.createGround();
    box2d.setFPS(60.0);
    box2d.registerGrabbing();

    
    line.setPhysics(0.0, 0.5, 0.5);
    line.create(box2d.getWorld());
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
   
    if(cam.isFrameNew()){
        runway.send("image", cam, OFX_RUNWAY_JPG);
        if(line.isBody()){
            line.destroy();
        }
    }
    runway.get("image",runwayResult);
    box2d.update();
    ofRemove(circles, ofxBox2dBaseShape::shouldRemoveOffScreen);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if(runwayResult.isAllocated()){
        for (int i = 0; i < runwayResult.getWidth(); i+= 5) {
          for (int j = 0; j < runwayResult.getHeight(); j+= 5) {
              ofColor color = runwayResult.getPixels().getColor(i, j);
              auto label = ofxRunwayData::findSegmentationLabel(segmentationMap, runwayResult, i , j);
              if(label == "person"){
                  line.addVertex(i,j);
              }
          }
        }
        
        
    }
    
    
    
    line.draw();
    line.setPhysics(0.0, 0.5, 0.5);
    line.create(box2d.getWorld());
    
    
    ofNoFill();
    ofSetHexColor(0x444342);
    for(auto &circle : circles) {
        ofFill();
        ofSetHexColor(0x90d4e3);
        circle->draw();
    }
   
}
void ofApp::keyPressed(int key) {

    if(key == 'c') {
        auto circle = make_shared<ofxBox2dCircle>();
        circle->setPhysics(3.0, 0.53, 0.1);
        circle->setup(box2d.getWorld(), mouseX, mouseY, ofRandom(4, 20));
        circles.push_back(circle);
    }
}

void ofApp::mousePressed(int x, int y, int button) {
        auto circle = make_shared<ofxBox2dCircle>();
        circle->setPhysics(3.0, 0.53, 0.1);
        circle->setup(box2d.getWorld(), x, y, ofRandom(4, 20));
        circles.push_back(circle);
}
//--------------------------------------------------------------
void ofApp::runwayInfoEvent(ofJson& info){
    ofxRunwayData::getSegmentationMap(segmentationMap, info);
}
void ofApp::runwayErrorEvent(string& message){
    ofLogNotice("ofApp::runwayErrorEvent") << message;
}

