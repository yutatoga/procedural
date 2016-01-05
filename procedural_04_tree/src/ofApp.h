#pragma once

#include "ofMain.h"
#include "MeshCreator.h"

// http://wowdev.jp/?p=1212

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
		
    MeshCreator *branch;
    ofVec3f center;
    ofCamera camera;
    bool isMesh = false;
    vector<Branch_Data>branch_data;
    bool usecamera;
    ofLight light;
    ofImage image;
};
