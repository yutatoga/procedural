#pragma once

#include "ofMain.h"

class Segment {
public:
    Segment(ofVec3f loc):loc(loc){};

    string toString();

    ofVec3f loc;
    ofVec3f growDir;
    int grow_count = 0;
    float area = 0;
};
