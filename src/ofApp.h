//The General concept behind this project is to create a playful scene between human in real-life and virtual objects on the screen. Imagine if you can control and make effect on objects on computer, that is power and innovation. I used machine learning from Runway ML to do the object perfectly.

// I also purposely play the audio at the beginning of the file as a way to make this file kinda playful to the users. And the idea behind it is that when the lines take up the shape of the person, it keep appearing and disappearing per frame, so it makes me thinking about the resemblance of this project and a audio player, so I thought to myself, why don't I add some music to it.

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
    
        //this is the runway
        ofxRunway runway;
        //this is the image from the runway
        ofImage runwayResult;
        //this is the webcam
        ofVideoGrabber cam;
    
        //this is the audio
        ofSoundPlayer mySound;
        
        // Callback functions that process what Runway sends back
        void runwayInfoEvent(ofJson& info);
        void runwayErrorEvent(string& message);
        ofxRunwayData::SegmentationMap segmentationMap;
        
    
        //all of this help create a interactivity in the box2d world
        ofxBox2d  box2d;
        ofxBox2dEdge   line;
        vector    <shared_ptr<ofxBox2dCircle> > circles;
    
    
    
       
        
};
