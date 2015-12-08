#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    if(enableTest){
        test = new Test();
        testDataVector = test->readTextData("data.txt");
        testAttractorPosition = test->readTextData("data2.txt");
        testDVector = test->readTextData("d.txt");
    }
    
    generatePointsDefault(ofVec3f(ofGetWidth()/2.0, 200, 0), 155, 300, ofVec3f(ofGetWidth()/2.0, 500, 0), 200, 40, 100);
    seed(ofVec2f(ofGetWidth()/2.0, 500));
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
void ofApp::generatePointsDefault(ofVec3f volumeCenter, float volumeRadius, int volumeAttractorNumber, ofVec3f rootCenter, float rootRadius, float rootHeight, int rootAttractorNumber){
    //create the attractors
    if (enableTest){
        for (int i = 0; i < (int)testAttractorPosition.size(); i++){
            attractors.push_back(new Attractor(ofVec3f(testAttractorPosition[i][0], testAttractorPosition[i][1], testAttractorPosition[i][2])));
        }
    } else {
        for (int i = 0; i < volumeAttractorNumber; i++) {
            ofVec3f position = randomSphereInside(volumeRadius, volumeCenter);
            attractors.push_back(new Attractor(position));
        }
        
        //also add a few attractors for roots
        attractors.push_back(new Attractor(rootCenter));
        for (int i = 0; i < rootAttractorNumber; i++) {
            ofVec3f position = randomEllipsoidInside(rootRadius, 40, rootRadius, rootCenter);
            attractors.push_back(new Attractor(position));
        }
    }
}

ofVec3f ofApp::randomEllipsoidInside(float half_width, float half_height, float half_depth, ofVec3f center){
    float u = ofRandom(0, TWO_PI);
    float v = acos(1-2*ofRandom(0, 1));
    float radiusRate = sqrt(ofRandom(0, 1));
    float x = radiusRate*half_width*cos(u)*sin(v);
    float y = radiusRate*half_height*sin(u)*sin(v);
    float z = radiusRate*half_depth*cos(v);
    ofVec3f position(x, y, z);
    position += center;
    return position;
}

ofVec3f ofApp::randomSphereInside(float radius, ofVec3f center){
    float theta = acos(1-2*ofRandom(0, 1));
    float r0 = sqrt(ofRandom(0, 1)) * radius;
    float r = r0*sin(theta);
    float n = ofRandom(0, 1)*TWO_PI;
    float x = r0*cos(theta);
    float y = r*sin(n);
    float z = r*cos(n);
    ofVec3f position(x, y, z);
    position += center;
    return position;
}

//--------------------------------------------------------------
void ofApp::seed(ofVec3f position) {
    //create root segment
    Segment *root = new Segment(position);
    segmentHelpers.push_back(new SegmentHelper(root, nullptr));
    
    //create initial trunk
    for (int i = 1; i < trunk_min_len+1; i++) {
        Segment *s = new Segment(ofVec3f(position.x, position.y-(i*growth_distance)));
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
