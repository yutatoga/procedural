#include "ofApp.h"
// http://wowdev.jp/?p=1199

void ofApp::makeTree(){
    if(!tree){
        // 木の初期化
        // 0番目なので、親と自分をマニュアルで設定
        tree = new Branch(50, ofVec3f(0,0,0), ofVec3f(0,-1,0) ,10,0,0);
    }
    else{
        // keyPressedで木を再度作りなおすとき
        // いったん木を全削除
        tree->deleteTree();
        // 木の初期化
        // 0番目なので、親と自分をマニュアルで設定
        tree = new Branch(50, ofVec3f(0,0,0), ofVec3f(0,-1,0), 10,0,0);
    }
    // 木の構築(再帰)
    tree->grow();
}

//--------------------------------------------------------------
void ofApp::setup(){
    // 木を構築
    makeTree();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0);
    cam.begin();
    ofTranslate(0, -200);
    if(tree)tree->draw();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // 木を再構築
    makeTree();
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
