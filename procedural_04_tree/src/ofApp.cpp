#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableLighting();
    ofEnableDepthTest();
    ofEnableAlphaBlending();
    
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(255);
    
    usecamera = false;
    branch = new MeshCreator();
    
    image.load("image.jpg");
}

//--------------------------------------------------------------
void ofApp::update(){
    if(!usecamera){
        ofVec3f sumOfAllPoints(0,0,0);
        for(unsigned int i = 0; i < branch_data.size(); i++){
            branch_data[i].point.z -= 4;
            sumOfAllPoints += branch_data[i].point;
        }
        center = sumOfAllPoints / branch_data.size();
        ofVec3f mousePoint(ofGetMouseX(),ofGetMouseY(),0);
        Branch_Data d;
        d.point = mousePoint;
        d.size = 50;
        branch_data.push_back(d);
        if(branch_data.size() > 300){
            vector<Branch_Data>::iterator it = branch_data.begin();
            it = branch_data.erase( it );
        }
    }
    
    branch->clear();
    branch->addSmoothBranch(branch_data, ofVec2f(0, 0), ofVec2f(image.getWidth(),image.getHeight()), 1.0);
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(usecamera)
        camera.begin();
    
    light.enable();
    
    if(!isMesh)
        branch->setMode(OF_PRIMITIVE_TRIANGLES);
    else
        branch->setMode(OF_PRIMITIVE_LINES);
    
    image.getTexture().bind();
    branch->draw();
    image.getTexture().unbind();
    
    if(usecamera)
        camera.end();
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
