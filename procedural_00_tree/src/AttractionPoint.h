#pragma once

#include "ofMain.h"

class AttractionPoint:public ofVec3f{
public:
    AttractionPoint(float x, float y, float z=0):ofVec3f(x, y, z){};
    AttractionPoint(ofVec3f point):ofVec3f(point){};
    
    int radius = 5;
    int closestSegment;
    
    int getClosestSegmentIndex() {
        return closestSegment;
    }
    
    void draw() {
        ofSetColor(0, 200, 0);
        ofPushMatrix();
        ofTranslate(this->x-ofGetWidth()/2.0, this->y-ofGetHeight()/2.0, this->z);
        ofDrawBox(radius);
        ofPopMatrix();
        ofSetColor(255);
    }
};
