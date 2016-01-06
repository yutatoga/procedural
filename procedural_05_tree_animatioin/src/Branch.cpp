#include "Branch.hpp"

void Branch::update(){
    if (growing){
        end += velocity;
    }
}

void Branch::render(){
    ofSetColor(ofColor::darkGreen);
    ofDrawLine(start, end);
    ofSetColor(255);
}

bool Branch::timeToBranch(){
    timer--;
    if(timer < 0 && growing){
        growing = false;
        return true;
    }else{
        return false;
    }
}

float heading2D(ofVec2f v) {
    // radian
    return (float)-v.angleRad(ofVec2f(1,0));
}

Branch* Branch::branch(float angle){
    // What is my current heading
    float theta = heading2D(velocity);
    // What is my current speed
    float mag = velocity.length();
    // Turn me
    theta += angle * DEG_TO_RAD;
    // Look, polar coordinates to cartesian!!
    ofVec2f newVel(mag*cos(theta), mag*sin(theta));
    // Return a new Branch
    return new Branch(end, newVel, timerStart*0.66f);
}