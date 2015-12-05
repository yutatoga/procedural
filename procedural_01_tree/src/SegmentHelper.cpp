#include "SegmentHelper.h"

void SegmentHelper::draw(bool drawBranches, bool drawLeaves){
    if (parentSegment != NULL) {//null signals root
        ofVec3f ploc = parentSegment->loc;
        
        //trunk
        if (currentSegment->area == 0){
            currentSegment->area = 1.0f;
        }
        parentSegment->area += currentSegment->area;
        
        if (drawBranches) {
            ofPushMatrix();{
                ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2, 0);
                ofVec3f diff(currentSegment->loc - parentSegment->loc);
                drawLine(currentSegment->loc, parentSegment->loc, sqrt(currentSegment->area), ofColor(142,72,19));
            }ofPopMatrix();
        }
        
        if (drawLeaves){
            this->drawLeaves();
        } else {
            currentSegment->area = 0;
        }
    } else {
        ofSetColor(142, 72, 19);
        ofDrawCircle(currentSegment->loc.x, currentSegment->loc.y, 6);
    }
}

void SegmentHelper::drawLine(float x1, float y1, float z1, float x2, float y2, float z2, float weight, ofColor boxColor){
    ofVec3f p1(x1, y1, z1);
    ofVec3f p2(x2, y2, z2);
    ofVec3f v1(x2-x1, y2-y1, z2-z1);
    
    float rho = sqrt(pow(v1.x, 2)+pow(v1.y, 2)+pow(v1.z, 2));
    float phi = acos(v1.z/rho);
    float the = atan2(v1.y, v1.x);
    v1 *= 0.5;
    
    ofPushMatrix();{
        ofPushStyle();{
            ofTranslate(x1, y1, z1);
            ofTranslate(v1.x, v1.y, v1.z);
            ofRotateZ(the*RAD_TO_DEG);
            ofRotateY(phi*RAD_TO_DEG);
            ofSetColor(boxColor);
            ofDrawBox(0, 0, 0, weight, weight, ofDist(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z)*1.2);
        }ofPopStyle();
    }ofPopMatrix();
}

void SegmentHelper::drawLine(ofVec3f p1, ofVec3f p2, float weight, ofColor boxColor){
    drawLine(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, weight, boxColor);
}

float heading2D(ofVec2f v) {
    return (float)-v.angleRad(ofVec2f(1,0));
}

void SegmentHelper::drawLeaves(){
    ofColor randLeafColor(211, 216, 27);
    float randLeafProb = 101;
    //if this branch is small enough, draw leaves
    if (currentSegment->area <= 4 && currentSegment->loc.y < 400) {
        ofSeedRandom((int) (currentSegment->loc.x+currentSegment->loc.y)*1000);
        if (ofRandom(0, 100) < randLeafProb) {
            ofPushStyle();{
                ofSetColor(ofRandom(randLeafColor.r-50, randLeafColor.r+50),
                           ofRandom(randLeafColor.g-50, randLeafColor.g+50),
                           ofRandom(randLeafColor.b-50, randLeafColor.b+50),
                           ofRandom(60, 120));
                ofPushMatrix();{
                    ofTranslate(currentSegment->loc.x-(ofGetWidth()/2.0), currentSegment->loc.y-(ofGetHeight()/2.0), currentSegment->loc.z);
                    ofRotate(heading2D(currentSegment->loc - parentSegment->loc)*RAD_TO_DEG);
                    ofRotate((HALF_PI/2.0 - ofRandom(0, HALF_PI))*RAD_TO_DEG);
                    ofRotateY(ofRandom(PI)*RAD_TO_DEG);
                    float leafX = ofRandom(8, 20);
                    float leafY = ofRandom(10, 24);
                    ofDrawEllipse(0, 0, leafX, leafY);
                }ofPopMatrix();
            }ofPopStyle();
        }
        ofSeedRandom();
    }
    currentSegment->area = 0;
}