// The Nature of Code
// Daniel Shiffman
// http://natureofcode.com

// Recursive Tree

// A class for a leaf that gets placed at the end of
// the last branches

#pragma once
#include "ofMain.h"
class Leaf{
public:
    Leaf(ofVec3f _loc):loc(_loc){};

    void display();
    
    ofVec3f loc;
};