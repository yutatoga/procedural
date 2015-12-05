#pragma once

#include "ofMain.h"
#include "Segment.h"

class SegmentHelper{
public:
    SegmentHelper(Segment *currentSegment, Segment *parentSegment):currentSegment(currentSegment), parentSegment(parentSegment){};
    
    void draw(bool drawBranches, bool drawLeaves);
    void drawLeaves();
    //drawline method cribbed from the processing forums, by James Carruthers
    void drawLine(float x1, float y1, float z1, float x2, float y2, float z2, float weight, ofColor boxColor);
    void drawLine(ofVec3f p1, ofVec3f p2, float weight, ofColor boxColor);
    
    Segment *currentSegment;
    Segment *parentSegment;
};