#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    // A branch has a starting location, a starting "velocity", and a starting "timer"
    Branch* b = new Branch(ofVec2f(ofGetWidth()/2, ofGetHeight()), ofVec2f(0, -1), 100);
    // Add to arraylist
    tree.push_back(b);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    // Let's stop when the arraylist gets too big
    // For every branch in the arraylist
    for (int i = tree.size()-1; i >= 0; i--) {
        // Get the branch, update and draw it
        tree[i]->update();
        tree[i]->render();
        // if it's ready to split
        if (tree[i]->timeToBranch()) {
            if (tree.size() < 1024) {
                tree.push_back(tree[i]->branch(30));
                tree.push_back(tree[i]->branch(-25));
            }else{
                leaves.push_back(new Leaf(tree[i]->end));
            }
        }
    }
    
    for (int i = 0; i < (int)leaves.size(); i++) {
        leaves[i]->display();
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
