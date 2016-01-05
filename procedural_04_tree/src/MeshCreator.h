#pragma once

#include "ofMain.h"

#define DIV_CYLINDER 64

typedef struct
{
    ofVec3f point;
    float size;
}Branch_Data;

typedef struct
{
    ofVec3f vert;
    ofVec3f norm;
    ofVec2f tex;
    ofFloatColor color;
}Polygon_Data;

class MeshCreator{
public:
    MeshCreator();
    
    void setMode(ofPrimitiveMode _mode);
    void draw();
    
    void addSmoothBranch(vector<Branch_Data>_data,ofVec2f _beginTex,ofVec2f _endTex,float _size);
    
    void clear();
    void save(string _name);
    
    ofVec3f normal(ofVec3f _a,ofVec3f _b,ofVec3f _c);
    
    int divide = DIV_CYLINDER;
    
    ofMesh mesh;
    
protected:
    
    int header = 0;
    
};