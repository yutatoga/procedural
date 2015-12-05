#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//    ofSetVerticalSync(false);
//    ofSetFrameRate(0);
//    ofBackground(0, 0, 0, 0);
    
    if(enableTest){
        test = new Test();
        testDataVector = test->readTextData("data.txt");
        testAttractorPosition = test->readTextData("data2.txt");
        testDVector = test->readTextData("d.txt");
    }
    
    generatePointsDefault();
    //generatePointsAlternate1();
    
    seed();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    if(enableTest){
        test->testSegmentHelperDrawLine(testDataVector);
    }
    
    ofEnableDepthTest();{
        ofPushMatrix();{
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2+(camHeight), 0);
            if (enableRotate) {
               ofRotateY(ofGetFrameNum());
            }
            if (drawAttractors) {
                for (int i = 0; i < (int)attractors.size(); i++) {
                    attractors[i]->draw();
                }
            }
            for (int i = (int)segmentHelpers.size()-1; i > 0; i--) {
                segmentHelpers[i]->draw(drawBranches, drawLeaves);
            }
        }ofPopMatrix();
    }ofDisableDepthTest();
    
    /*
     * This is where most of the magic starts happening.
     */
    
    if (!finished) {
        //first we'll iterate through all the attractors
        for (int ai = 0; ai < (int)attractors.size(); ai++) {
            //then, compare it to all the segments, and find the direction and distance
            float leastDist = max_attract_dist;
            ofVec3f closestDir(0, 0, 0);
            Segment *closest = new Segment(ofVec3f(0, 0, 0));
            for (int si = 0; si < (int)segmentHelpers.size(); si++) {
                Segment *s = segmentHelpers[si]->currentSegment;
                ofVec3f dir = attractors[ai]->attractionPoint - s->loc;
                float d;
                if (enableTest) {
                    d = testDVector[testDCounter][0];
                    testDCounter++;
                }else{
                    d = ofDist(0, 0, 0, dir.x, dir.y, dir.z);
                }
                //if d > max_attract_dist then continue, we don't care about this one
                if (d > max_attract_dist) continue;

                //if d < min_attract_dist, then this branch has arrived, and this node is taken
                if (d < min_attract_dist && ai < (int)attractors.size()) attractors.erase(attractors.begin()+ai);
                
                //keep track of the closest segment, and direction + distance to it
                if (closest->loc.length() == 0 || d <= leastDist) closest = s;
                if (closestDir.length() == 0 || d <= leastDist) closestDir = dir;
                if (d <= leastDist) leastDist = d;
                
            }
            //now that we have the closest, tell it to grow towards us
            if (closest->loc.length() != 0) {
                closest->grow_count++; //mark the segment for growth
                closestDir.normalize();
                closest->growDir += closestDir;
            }
        }
        
        //now we can iterate through each segment, and update it
        finished = true;
        int s_len = segmentHelpers.size();
        
        for (int si = s_len-1; si > 0; si--) {
            Segment *s = segmentHelpers[si]->currentSegment;
            if (s->grow_count > 0) { //grow a new branch
                finished = false;
                s->growDir /= s->grow_count;
                s->growDir.normalize();
                // s.growDir.limit(growth_distance);
                s->growDir *= growth_distance;
                ofVec3f newBranchLoc = s->loc + s->growDir;
                SegmentHelper *newSegmentHelper = new SegmentHelper(new Segment(newBranchLoc), s);
                segmentHelpers.push_back(newSegmentHelper);
                
                s->growDir.set(0, 0, 0);
                s->grow_count = 0;
                s->area = 0;
            }
        }
    }
}

//--------------------------------------------------------------
//this is the method to place the attractor points,
//it can be replaced by others easily to quickly create
//different types of tree
void ofApp::generatePointsDefault(){
    //create the attractors
    ofVec3f volumeCenter(200, 200, 0);
    float volumeRadius = 155;
    
    if (enableTest){
        for (int i = 0; i < (int)testAttractorPosition.size(); i++){
            attractors.push_back(new Attractor(ofVec3f(testAttractorPosition[i][0], testAttractorPosition[i][1], testAttractorPosition[i][2])));
        }
    } else {
        for (int i = 0; i < num_attractors; i++) {
            
            ofVec3f p((float) ofRandom(0, ofGetWidth()-50)+25,
                      (float) ofRandom(0, ofGetHeight()-200)+25,
                      (float) ofRandom(-200, 200));
            if (ofDist(p.x, p.y, p.z, volumeCenter.x, volumeCenter.y, volumeCenter.z) < volumeRadius){
                attractors.push_back(new Attractor(p));
            }
        }
        
        //also add a few attractors for roots
        ofVec3f rootCenter(ofGetWidth()/2.0, 545, 0);
        attractors.push_back(new Attractor(rootCenter));
        for (int i = 0; i < 500; i++) {
            ofVec3f p(ofRandom(0, 500), ofRandom(490, 590), ofRandom(-300, 300));
            if(ofDist(p.x, p.y, p.z, rootCenter.x, rootCenter.y, rootCenter.z) < 200){
                attractors.push_back(new Attractor(p));
            }
        }
    }
}

//--------------------------------------------------------------
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
            ofDist(p.x, p.y, p.z, volumeCenter3.x, volumeCenter3.y, volumeCenter3.z) < volumeRadius3){
            attractors.push_back(new Attractor(p));
        }
    }
    //also add a few attractors for roots
    ofVec3f rootCenter(ofGetWidth()/2, 545, 0);
    attractors.push_back(new Attractor(rootCenter));
    for (int i = 0; i < 500; i++) {
        ofVec3f p(ofRandom(0, 500), ofRandom(490, 590), ofRandom(-300, 300));
        if(ofDist(p.x, p.y, p.z, rootCenter.x, rootCenter.y, rootCenter.z) < 200){
            attractors.push_back(new Attractor(p));
        }
    }
}

//--------------------------------------------------------------
void ofApp::seed() {
    //create root segment
    Segment *root = new Segment(ofVec3f(200, 500));
    segmentHelpers.push_back(new SegmentHelper(root, nullptr));
    
    //create initial trunk
    for (int i = 1; i < trunk_min_len+1; i++) {
        Segment *s = new Segment(ofVec3f(200, 500-(i*growth_distance)));
        segmentHelpers.push_back(new SegmentHelper(s, segmentHelpers[i-1]->currentSegment));
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'a':
            drawAttractors = !drawAttractors;
            break;
        case 'b':
            drawBranches = !drawBranches;
            break;
        case 'l':
            drawLeaves = !drawLeaves;
            break;
        case ' ':
            finished = !finished;
            break;
        case 'n':
            clear();
            setup();
            finished = false;
            break;
        case 'r':
            enableRotate = !enableRotate;
            break;
        default:
            break;
    }
}

void ofApp::clear(){
    segmentHelpers.clear();
    attractors.clear();
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
