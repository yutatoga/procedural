#include "ofMain.h"

class Branch{
public:
    Branch(){}
    
    // 各種設定
    // 太さ , 開始位置 , 親の位置 , 節の長さ,
    void make(float _size,ofVec3f _pos,ofVec3f _pPos,float _len,int _depth,float _prob);
    
    // 再帰で枝を生成する
    void grow();
    
    // 描画
    void draw();
    
    // 消去
    void deleteTree();
    
protected:
    float randomAngle = 0;
    ofVec3f newPosAnimation(float _angle);
    float branch_len;
    float prob_branch; // 枝の分岐確率 (rightが進むごとに上昇)
    int branch_depth; // 分岐箇所から何番目に位置するか
    ofVec3f pos;
    float size;
    ofVec3f parentPos;
    Branch *left=NULL,*right=NULL;
};
