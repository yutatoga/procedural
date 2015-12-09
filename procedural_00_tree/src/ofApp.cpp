#include "ofApp.h"
// http://www.openprocessing.org/sketch/31620

//this is the method to place the attractor points,
//it can be replaced by others easily to quickly create
//different types of tree
void ofApp::generatePointsDefault() {
    //create the attractors
    ofVec3f volumeCenter(200, 200, 0);
    float volumeRadius = 155;
    for (int i = 0; i < num_attractors; i++) {
        ofVec3f p((int)ofRandom(ofGetWidth()-50)+25, (int)ofRandom(ofGetHeight()-200)+25, (int)ofRandom(-200, 200));
        if (ofDist(p.x, p.y, p.z, volumeCenter.x, volumeCenter.y, volumeCenter.z) < volumeRadius)
            attractors.push_back(new AttractionPoint(p.x, p.y, p.z));
    }
    //also add a few attractors for roots
    ofVec3f rootCenter(ofGetWidth()/2.0, 545, 0);
    attractors.push_back(new AttractionPoint(rootCenter));
    for (int i = 0; i < 500; i++) {
        ofVec3f p(ofRandom(0, 500), ofRandom(490, 590), ofRandom(-300, 300));
        if(ofDist(p.x, p.y, p.z, rootCenter.x, rootCenter.y, rootCenter.z) < 200)
            attractors.push_back(new AttractionPoint(p.x, p.y, p.z));
    }
}

void ofApp::generatePointsAlternate1() {
    //create the attractors
    ofVec3f volumeCenter((ofGetWidth()/2)-ofRandom(-50,50), ofRandom(250, 400), ofRandom(-100, 100));
    ofVec3f volumeCenter2((ofGetWidth()/2)-ofRandom(-50,50), ofRandom(150, 300), ofRandom(-100, 100));
    ofVec3f volumeCenter3((ofGetWidth()/2)-ofRandom(-50,50), ofRandom(150, 300), ofRandom(-100, 100));
    float volumeRadius = ofRandom(50, 200);
    float volumeRadius2 = ofRandom(50, 200);
    float volumeRadius3 = ofRandom(50, 200);
    for (int i = 0; i < num_attractors; i++) {
        ofVec3f p((int) ofRandom(0, ofGetWidth()), (int) ofRandom(0, ofGetHeight()), (int) ofRandom(-500, 500));
        if (ofDist(p.x, p.y, p.z, volumeCenter.x, volumeCenter.y, volumeCenter.z) < volumeRadius ||
            ofDist(p.x, p.y, p.z, volumeCenter2.x, volumeCenter2.y, volumeCenter2.z) < volumeRadius2 ||
            ofDist(p.x, p.y, p.z, volumeCenter3.x, volumeCenter3.y, volumeCenter3.z) < volumeRadius3)
            attractors.push_back(new AttractionPoint(p.x, p.y, p.z));
    }
    //also add a few attractors for roots
    ofVec3f rootCenter(ofGetWidth()/2,545,0);
    attractors.push_back(new AttractionPoint(rootCenter));
    for (int i = 0; i < 500; i++) {
        ofVec3f p(ofRandom(500), ofRandom(490, 590), ofRandom(-300, 300));
        if(ofDist(p.x, p.y, p.z, rootCenter.x, rootCenter.y, rootCenter.z) < 200)
            attractors.push_back(new AttractionPoint(p.x, p.y, p.z));
    }
}

void ofApp::seed() {
    //create root segment
    Segment *root = new Segment(ofVec3f(200, 500), NULL);
    segments.push_back(root);
    
    //create initial trunk
    for (int i = 0; i < (int)100/growth_distance; i++) {
        Segment *s = new Segment(ofVec3f(200, 500-(i*growth_distance)), segments[segments.size()-1]);
        segments.push_back(s);
    }
}

//--------------------------------------------------------------
void ofApp::setup(){
    generatePointsDefault();
    //generatePointsAlternate2();
    
    //create root segment
    Segment *root = new Segment(ofVec3f(200, 500), NULL);
    segments.push_back(root);
    
    //create initial trunk
    for (int i = 1; i < trunk_min_len+1; i++) {
        Segment *s = new Segment(ofVec3f(200, 500-(i*growth_distance)), segments[segments.size()-1]);
        segments.push_back(s);
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);
    ofRotateY(ofGetFrameNum());
    
    //draw tree elements
    for (int i = 0; i < attractors.size(); i++) {
        AttractionPoint *p = attractors[i];
        p->draw();
    }
    
    for (int i = segments.size()-1; i > 0; i--) {
        Segment *s = segments[i];
        s->draw(drawBranches, drawLeaves);
    }
    if (drawLeaves) {
        for (int i = segments.size()-1; i > 0; i--) {
            Segment *s = segments[i];
            s->drawLeaves();
        }
    }
    
    ofPopMatrix();
    
    /*
     * This is where most of the magic starts happening.
     */
    
    if (!finished) {
        //first we'll iterate through all the attractors
        for (int ai = 0; ai < attractors.size(); ai++) {
            AttractionPoint *ap = attractors[ai];
            //then, compare it to all the segments, and find the direction and distance
            float leastDist = max_attract_dist;
            ofVec3f closestDir;
            Segment *closest;
            for (int si = 0; si < segments.size(); si++) {
                Segment *s = segments[si];
                ofVec3f dir = ofVec3f(ap->x, ap->y, ap->z)-s->loc;
                float d = ofDist(0, 0, 0, dir.x, dir.y, dir.z);
                
                //if d > max_attract_dist then continue, we don't care about this one
                if (d > max_attract_dist) continue;
                //if d < min_attract_dist, then this branch has arrived, and this node is taken
                if (d < min_attract_dist && ai < (int)attractors.size()) attractors.erase(attractors.begin()+ai);
                
                //keep track of the closest segment, and direction + distance to it
                if (closest == NULL || d <= leastDist) closest = s;
                if (closestDir.length() == 0 || d <= leastDist) closestDir = dir;
                if (d <= leastDist) leastDist = d;
            }
            
            //now that we have the closest, tell it to grow towards us
            if (closest != NULL) {
                closest->grow_count++; //mark the segment for growth
                closestDir.normalize();
                closest->growDir += closestDir;
            }
        }
        
        //now we can iterate through each segment, and update it
        finished = true;
        int s_len = segments.size();
        for (int si = s_len-1; si > 0; si--) {
            Segment *s = segments[si];
            if (s->grow_count > 0) { //grow a new branch
                finished = false;
                s->growDir /= s->grow_count;
                
                s->growDir.normalize();
                // s.growDir.limit(growth_distance);
                s->growDir *= growth_distance;
                ofVec3f newBranchLoc = s->loc + s->growDir;
                Segment *newSegment = new Segment(newBranchLoc, s);
                segments.push_back(newSegment);
                
                s->growDir.set(0, 0, 0);
                s->grow_count = 0;
                s->area = 0;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
