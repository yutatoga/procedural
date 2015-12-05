#pragma once

#include "ofMain.h"

class Attractor {
public:
    Attractor(ofVec3f point):attractionPoint(point){};
    
    int getClosestSegmentIndex();
    void draw(float radius, ofColor color);
    void draw(ofColor color);
    void draw();
    
    float radius = 5;
    int closestSegment;
    ofVec3f attractionPoint;
};