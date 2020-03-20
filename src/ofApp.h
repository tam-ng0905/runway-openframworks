
#pragma once

#include "ofMain.h"
#include "ofxRunway.h"
#include "ofxBox2d.h"



class ofApp : public ofBaseApp, public ofxRunwayListener{

    public:
        void setup();
        void update();
        void draw();
        void keyPressed(int key);
    void mousePressed(int x, int y,int button);
    ofxRunway runway;
        
        ofImage runwayResult;
        
        ofVideoGrabber cam;
        ofSoundPlayer mySound;
        
        // Callback functions that process what Runway sends back
        void runwayInfoEvent(ofJson& info);
        void runwayErrorEvent(string& message);
        
        
        ofxBox2d  box2d;
        ofxBox2dEdge   line;
        vector    <shared_ptr<ofxBox2dCircle> > circles;
    
    
    
        ofxRunwayData::SegmentationMap segmentationMap;
        
};
