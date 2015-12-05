#pragma once

#include "ofMain.h"
#include "SegmentHelper.h"

class Test{
public:
    Test(){};

    vector<vector<float> > readTextData(string fileName);
    void testSegmentHelperDrawLine(vector<vector<float> > testDataVector, ofColor color);
    void testSegmentHelperDrawLine(vector<vector<float> > testDataVector);
    void testSegmentHelperDrawLine(string fileName);
};