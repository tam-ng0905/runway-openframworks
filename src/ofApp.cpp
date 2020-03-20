#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(513,385);
    
    //set up the yellow background
    ofBackgroundHex(0xf0eec2);
    
    
    ofSetVerticalSync(true);
    
    //setup the runway
    runway.setup(this, "http://localhost:8000");
    runway.start();
    //setup the camera grabber and play audio
    cam.setup(640,480);
    mySound.load("audio.mp3");
    mySound.play();
    
    
    ofSetLogLevel(OF_LOG_NOTICE);
    
    
    //set up box2d environment
    box2d.init();
    box2d.setGravity(0, 10);
    box2d.createGround();
    box2d.setFPS(60.0);
    box2d.registerGrabbing();

    //create lines to interact with circle
    line.setPhysics(0.0, 0.5, 0.5);
    line.create(box2d.getWorld());
}

//--------------------------------------------------------------
void ofApp::update(){
    //update camera per frame
    cam.update();
   
    //if the frame is new, erase the old human shape so that the fill won't take up too much space of memory
    //and also send new frame to runway
    if(cam.isFrameNew()){
        runway.send("image", cam, OFX_RUNWAY_JPG);
        if(line.isBody()){
            line.destroy();
        }
    }
    
    //get result from runway
    runway.get("image",runwayResult);
    
    //update box2d every frame
    box2d.update();
    
    //remove circles if it goes out of the screen
    ofRemove(circles, ofxBox2dBaseShape::shouldRemoveOffScreen);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    if(runwayResult.isAllocated()){
        
        //get the label for every 5 pixels so that the application knows where is the person
        for (int i = 0; i < runwayResult.getWidth(); i+= 5) {
          for (int j = 0; j < runwayResult.getHeight(); j+= 5) {
              ofColor color = runwayResult.getPixels().getColor(i, j);
              auto label = ofxRunwayData::findSegmentationLabel(segmentationMap, runwayResult, i , j);
              if(label == "person"){
                  //if that "5 pixels" belong to a person, add vertex at the cordinate i, j to the line
                  line.addVertex(i,j);
              }
          }
        }
        
        
    }
    
    
    //draw line and create it in the box2d world
    line.draw();
    line.setPhysics(0.0, 0.5, 0.5);
    line.create(box2d.getWorld());
    
    
    //draw circles
    ofNoFill();
    ofSetHexColor(0x444342);
    for(auto &circle : circles) {
        ofFill();
        ofSetHexColor(0x90d4e3);
        circle->draw();
    }
   
}
void ofApp::keyPressed(int key) {
    
    //if the user press the key "c" draw circles at the mouse position.
    if(key == 'c') {
        auto circle = make_shared<ofxBox2dCircle>();
        circle->setPhysics(3.0, 0.53, 0.1);
        circle->setup(box2d.getWorld(), mouseX, mouseY, ofRandom(4, 20));
        circles.push_back(circle);
    }
}

void ofApp::mousePressed(int x, int y, int button) {
    
    //or if the user click the mouse, instantly draw circles
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

