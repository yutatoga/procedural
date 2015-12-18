#include "Branch.h"

void Branch::deleteTree(){
    if(left)left->deleteTree();
    if(right)right->deleteTree();
    
    left=NULL;
    right=NULL;
    
    delete this;
}

void Branch::grow(){
    if(size > 5){
        // 固定角度
        randomAngle = ofRandom(360);
        
        // 分岐 (prob_branchの確立で分岐する)
        if(!left && ofRandomuf() < prob_branch)
        {
            left = new Branch(size * 0.96* 0.7,
                              newPosAnimation(45),
                              pos,
                              branch_len * 0.7,
                              0,
                              0);
            left->grow();
        }
        
        // 幹
        if(!right ){
            right = new Branch(size * 0.96,
                               newPosAnimation(5),
                               pos,
                               branch_len,
                               branch_depth +1,
                               prob_branch + 200 / 5000.0);
            
            right->grow();
        }
    }
}

void Branch::draw(){
    ofDrawLine(parentPos,pos);
    if(left)
        left->draw();
    
    if(right)
        right->draw();
}

ofVec3f Branch::newPosAnimation(float _angle){
    // 枝のベクトル
    ofVec3f V = (pos - parentPos);
    
    // 次の枝の長さの基準
    float L = branch_len;
    
    // 枝のベクトルに垂直なベクトル
    ofVec3f N = V.getCrossed(ofVec3f(1,1,1));
    
    // 各点の位置
    ofVec3f P = (V.getNormalized() * L);
    ofVec3f Q = P.getRotated(_angle, N);
    
    ofVec3f R = Q.getRotated(fmod(randomAngle,360), V);
    ofVec3f O = pos;
    
    return O + R;
}