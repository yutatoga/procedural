#pragma once

#include "ofMain.h"

class Segment{
public:
    Segment(){};
    
    ofVec3f loc;
    ofVec3f growDir;
    int grow_count = 0;
    float area = 0;
    Segment *parent;
    
    Segment(ofVec3f loc, Segment *parent) {
        this->parent = parent;
        this->loc = loc;
    };
    
    void draw(bool drawBranches, bool drawLeaves) {
        if (parent != NULL) {//null signals root
            ofVec3f ploc = parent->loc;
            
            //trunk
            if (area == 0)
                area = 1.0f;
            parent->area += area;
            
            if (drawBranches) {
                ofPushMatrix();
                ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2, 0);
                ofVec3f diff = loc - parent->loc;
                drawLine(loc.x,loc.y,loc.z,parent->loc.x,parent->loc.y,parent->loc.z, sqrt(area), ofColor(142,72,19));
                ofPopMatrix();
            }
            
            if (!drawLeaves)
                area = 0;
        }
        else {
            ofDrawEllipse(loc.x, loc.y, 6, 6);
        }
    }
    
    //drawline method cribbed from the processing forums, by James Carruthers
    void drawLine(float x1, float y1, float z1, float x2, float y2, float z2, float weight, ofColor strokeColour)
    {
        ofVec3f p1(x1, y1, z1);
        ofVec3f p2(x2, y2, z2);
        ofVec3f v1(x2-x1, y2-y1, z2-z1);
        float rho = sqrt(pow(v1.x, 2)+pow(v1.y, 2)+pow(v1.z, 2));
        float phi = acos(v1.z/rho);
        float the = atan2(v1.y, v1.x);
        v1 *= 0.5;
        
        ofPushMatrix();
        ofTranslate(x1, y1, z1);
        ofTranslate(v1.x, v1.y, v1.z);
        ofRotateZ(the*RAD_TO_DEG);
        ofRotateY(phi*RAD_TO_DEG);
        ofSetColor(strokeColour);
        ofDrawBox(0, 0, 0, weight, weight, ofDist(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z)*1.2);
        ofPopMatrix();
    }
    
    string toString() {
        return "Segment@"+ofToString(loc.x)+","+ofToString(loc.y)+":"+ofToString(grow_count)+"\n\t  "+ofToString(growDir);
    }
    
    float heading2D(ofVec2f v) {
        return (float)-v.angleRad(ofVec2f(1,0));
    }
    
    void drawLeaves() {
        ofColor randLeafColor(211, 216, 27);
        float randLeafProb = 101;
        //if this branch is small enough, draw leaves
        if (area <= 4 && loc.y < 400 && parent != NULL) {
            ofSeedRandom((int) (loc.x+loc.y)*1000);
            if (ofRandom(0, 100) < randLeafProb) {
                ofSetColor(ofRandom(randLeafColor.r-50, randLeafColor.r+50),
                           ofRandom(randLeafColor.g-50, randLeafColor.g+50),
                           ofRandom(randLeafColor.b-50, randLeafColor.b+50),
                           ofRandom(60, 120));
                ofPushMatrix();
                ofTranslate(loc.x-(ofGetWidth()/2), loc.y-(ofGetHeight()/2), loc.z);
                ofRotate(heading2D(loc-parent->loc));
                ofRotate((HALF_PI*0.5 - ofRandom(0, HALF_PI))*RAD_TO_DEG);
                ofRotateY(ofRandom(PI)*RAD_TO_DEG);
                float leafX = ofRandom(8, 20);
                float leafY = ofRandom(10, 24);
                ofDrawEllipse(0, 0, leafY, leafX);
                ofPopMatrix();
            }
            ofSeedRandom();
        }
        area = 0;
    }
};