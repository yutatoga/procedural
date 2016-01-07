#include "ofMain.h"

class Branch{
public:
    // コンストラクタ
    Branch(float _size, ofVec3f _pos, ofVec3f _pPos, float _len, int _depth, float _prob):size(_size), pos(_pos), parentPos(_pPos), branch_len(_len),
    branch_depth(_depth), prob_branch(_prob){};
    
    // 再帰で枝を生成する
    void grow();
    
    // 描画
    void draw();
    
    // 消去
    void deleteTree();
    
protected:
    // 関数
    ofVec3f newPosAnimation(float _angle);
    
    // 変数
    float randomAngle = 0;
    float branch_len; // 枝の長さ
    float prob_branch; // 枝の分岐確率 (rightが進むごとに上昇)
    int branch_depth; // (今回は未使用)分岐箇所から何番目に位置するか
    ofVec3f pos; // 自分の枝の位置
    float size; // 太さ(今回は成長を止めるための指標として使用(成長に従って細くなり、ある程度で停止。)
    ofVec3f parentPos; // 親の枝の位置
    Branch *left=nullptr, *right=nullptr; // 子をnullptrで初期化(無限定義でメモリーを無限に使用しないようにする)
};
