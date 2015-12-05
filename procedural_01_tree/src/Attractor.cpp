#include "Attractor.h"

int Attractor::getClosestSegmentIndex(){
    return closestSegment;
}

void Attractor::draw(float radius, ofColor color){
    ofPushStyle();{
        ofSetColor(color);
        ofPushMatrix();{
            ofTranslate(attractionPoint.x-ofGetWidth()/2, attractionPoint.y-ofGetHeight()/2, attractionPoint.z);
            ofDrawBox(radius);
        }ofPopMatrix();
    }ofPopStyle();
}

void Attractor::draw(ofColor color){
    draw(5, color);
}

void Attractor::draw(){
    draw(5, ofColor(0, 200, 0));
}