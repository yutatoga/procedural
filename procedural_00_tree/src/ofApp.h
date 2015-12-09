#pragma once

#include "ofMain.h"
#include "Segment.h"
#include "AttractionPoint.h"

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
		
    void generatePointsDefault();
    void generatePointsAlternate1();
    void seed();
    
    vector<Segment*> segments;
    vector<AttractionPoint*> attractors;
    
    int num_attractors = 1000;
    int trunk_min_len = 50;
    
    float growth_distance  = 4;//1.6;
    float max_attract_dist = 200;
    float min_attract_dist = 20;
    
    float randLeafRed = 211;//232;
    float randLeafGreen = 216;//96;
    float randLeafBlue = 27;//74;
    float randLeafProb = 101;
    float winter = 0;
    
    bool finished = false;
    bool drawAttractors = false;
    bool drawBranches = true;
    bool drawLeaves = true;
    
    int groundSeed = 0;
    long treeSeed = (long) ofRandom(0, 10000);
};
