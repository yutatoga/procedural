#include "ofApp.h"
// http://www.processing.org/examples/tree.html

//--------------------------------------------------------------
void ofApp::setup(){
    counter = 0;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::branch(float h) {
    // Each branch will be 2/3rds the size of the previous one
    h *= 0.66;
    
    // All recursive functions must have an exit condition!!!!
    // Here, ours is when the length of the branch is 2 pixels or less
    if (h > 2) {
        ofPushMatrix();    // Save the current state of transformation (i.e. where are we now)
        ofRotateZ(theta);   // Rotate by theta
        ofDrawLine(0, 0, 0, -h);  // Draw the branch
        ofTranslate(0, -h); // Move to the end of the branch
        branch(h);       // Ok, now call myself to draw two new branches!!
        ofPopMatrix();     // Whenever we get back here, we "pop" in order to restore the previous matrix state
        
        // Repeat the same thing, only branch off to the "left" this time!
        ofPushMatrix();
        ofRotateZ(-theta);
        ofDrawLine(0, 0, 0, -h);
        ofTranslate(0, -h);
        branch(h);
        ofPopMatrix();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Let's pick an angle 0 to 90 degrees based on the mouse position
    theta = (mouseX / (float) ofGetWidth()) * 90;
    // Start the tree from the bottom of the screen
    ofTranslate(ofGetWidth()/2, ofGetHeight());
    // Draw a line 120 pixels
    ofDrawLine(0, 0, 0, -120);
    // Move to the end of that line
    ofTranslate(0, -120);
    // Start the recursive branching!
    branch(120);
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
