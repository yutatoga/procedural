#pragma once

#include "ofMain.h"
#include "Segment.h"
#include "Attractor.h"
#include "SegmentHelper.h"
#include "Test.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    void generatePointsDefault(ofVec3f volumeCenter, float volumeRadius, int volumeAttractorNumber, ofVec3f rootCenter, float rootRadius, float rootHeight, int rootAttractorNumber);
    void generatePointsDefault();
    void generatePointsAlternate1();
    void seed(ofVec3f position);
    void clear();
    ofVec3f randomSphereInside(float radius, ofVec3f center = ofVec3f(0, 0, 0));
    ofVec3f randomEllipsoidInside(float half_width, float half_height, float half_depth, ofVec3f center = ofVec3f(0, 0, 0));
    
    vector<SegmentHelper*> segmentHelpers;
    vector<Attractor*> attractors;
    
    int trunk_min_len = 50;
    
    float growth_distance  = 4;//1.6;
    float max_attract_dist = 200;
    float min_attract_dist = 20;
    
    float randLeafRed = 211;//232;
    float randLeafGreen = 216;//96;
    float randLeafBlue = 27;//74;
    float randLeafProb = 101;
    float winter = 0;
    
    float camRotY = 0;
    float camHeight = 0;
    float camScale = 1;
    
    bool finished = false;
    bool drawAttractors = true;
    bool drawBranches = true;
    bool drawLeaves = true;
    bool enableRotate = true;
    
    int groundSeed = 0;
    long treeSeed = (long) ofRandom(0, 10000);
    
    // test
    bool enableTest = false;
    Test *test;
    vector<vector<float> > testDataVector;
    vector<vector<float> > testAttractorPosition;
    vector<vector<float> > testDVector;
    int testDCounter=0;
};
