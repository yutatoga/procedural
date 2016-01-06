#include "Leaf.hpp"

void Leaf::display(){
    ofSetColor(255, 255, 0, 127);
    ofDrawEllipse(loc.x, loc.y, 4, 4);
    ofSetColor(255);
}