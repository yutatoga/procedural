#include "Branch.h"

void Branch::deleteTree(){
    // 再帰的に全部の木を消す
    if(left)left->deleteTree();
    if(right)right->deleteTree();
    
    left = nullptr;
    right = nullptr;

    delete this; // オブジェクト開放
}

void Branch::grow(){
    // 再帰的に成長
    if(size > 5){ // 幹の太さが5より小さいと、成長を止める
        // 固定角度
        randomAngle = ofRandom(360);
        
        // 分岐 (prob_branchの確立で分岐する)
        // 子(左)をつくる
        if(!left && ofRandomuf() < prob_branch)
        {
            left = new Branch(size * 0.96* 0.7, // 太さの設定
                              newPosAnimation(45), // 子の枝位置の設定 (大きい角度=分岐)
                              pos,//　親(今の枝位置)の設定
                              branch_len * 0.7, // 枝の長さ
                              0, // 今回は無視
                              0 // 分岐から分岐は起こさないので0に設定
                              );
            // leftの成長
            left->grow();
        }
        
        // 幹
        if(!right )
        {
            // 幹の初期化
            right = new Branch(size * 0.96, // 太さの設定
                               newPosAnimation(5), // 子の枝位置の設定(小さい角度 = ゆがみ)
                               pos, // 親(今の枝位置)の設定
                               branch_len, // 枝の長さ
                               branch_depth +1, // 今回は無視
                               prob_branch + 200 / 5000.0); // 分岐確立 (今の確立から徐々に上がっていく(分岐が進むほど分岐しやすい))
            // rightの成長(成長)
            right->grow(); //
        }
    }
}

void Branch::draw(){
    // 再帰的に描画
    // int instantSize = ofMap(size, 5*0.96* 0.7, 50, 1, 50); // ofSetLineWidth()には上限があって、とても太い値は反映しない。ofDrawLineだけでは表現力に限界がある。 https://forum.openframeworks.cc/t/ofsetlinewidth-maximum-value/3751
    // ofSetLineWidth(instantSize);
    ofDrawLine(parentPos,pos); // 自分の枝 (太さは使わずに単純にofLineWidth(1))で描画。
    if(left)
        left->draw(); // 子の枝 = recursive (再帰)
    
    if(right)
        right->draw(); // 子の枝 = recursive (再帰)
}

ofVec3f Branch::newPosAnimation(float _angle){
    // grow()時に子の、枝位置を計算するのに、使用する関数
    // 枝のベクトル
    ofVec3f V = (pos - parentPos);
    
    // 次の枝の長さの基準
    float L = branch_len;
    // 枝のベクトルに垂直なベクトル
    ofVec3f N = V.getCrossed(ofVec3f(1,1,1));
    
    // 各点の位置
    ofVec3f P = (V.getNormalized() * L); // P + O はぶれない成長
    ofVec3f Q = P.getRotated(_angle, N); // Qはぶれてる。だた、一軸でしかぶれてない。
    ofVec3f R = Q.getRotated(randomAngle, V); // Rで3Dにぶれる。
    ofVec3f O = pos; // いまいるところ。
    
    return O + R;
}