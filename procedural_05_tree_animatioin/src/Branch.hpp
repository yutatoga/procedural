// The Nature of Code
// Daniel Shiffman
// http://natureofcode.com

// Recursive Tree

// A class for one branch in the system

#pragma once
#include "ofMain.h"

class Branch{
public:
    Branch(ofVec2f _start, ofVec2f _velocity, float _timer):
    start(_start),
    end(_start),
    velocity(_velocity),
    timer(_timer),
    timerStart(_timer)
    {};
    
    // Move location
    void update();
    
    // Draw a dot at location
    void render();
    
    // Did the timer run out?
    bool timeToBranch();
    
    // Create a new branch at the current location, but change direction by a given angle
    Branch* branch(float angle);
    
    ofVec2f start;
    ofVec2f end;
    ofVec2f velocity;
    float timer;
    float timerStart;
    
    bool growing = true;
};