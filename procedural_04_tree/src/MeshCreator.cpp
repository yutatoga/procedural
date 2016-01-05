#include "MeshCreator.h"

MeshCreator::MeshCreator()
{
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    mesh.enableTextures();
    header = 0;
}

void MeshCreator::setMode(ofPrimitiveMode _mode)
{
    mesh.setMode(_mode);
}

ofVec3f MeshCreator::normal(ofVec3f _a,ofVec3f _b,ofVec3f _c)
{
    ofVec3f v1 = _b - _a;
    ofVec3f v2 = _c - _a;
    ofVec3f cross = v1.getCrossed(v2);
    return cross.getNormalized();
}

void MeshCreator::save(string _name)
{
    
}

void MeshCreator::draw()
{
    mesh.draw();
}

void MeshCreator::clear()
{
    mesh.clear();
    header = 0;
}

void MeshCreator::addSmoothBranch(vector<Branch_Data> _data,ofVec2f _beginTex,ofVec2f _endTex,float _size)
{
    vector< vector < Polygon_Data > > polygon;
    vector< int > index;
    
    ofVec3f O(1000,1000,1000);
    float V;
    ofColor color(255, 255, 255);
    vector<Branch_Data> line = _data;
    float incAngle = 360.0 / (divide+1);
    if(line.size() < 1)return;
    int lineID = 0;
    
    // Mesh Dataの作成
    for (float angle = 0; angle <= 360.0; angle += incAngle) {
        header+=2;
        V = 0;
        vector<Polygon_Data> linePoly;
        ofVec3f lastN;
        
        for(int i = 0;i < line.size()-1;i ++)
        {
            Polygon_Data dataA;
            Polygon_Data dataB;
            
            if(line[i].size*_size < 1)break;
            
            ofVec3f current = line[i].point;
            ofVec3f next = line[i+1].point;
            ofVec3f dir = (next-current).getNormalized();
            ofVec3f unit = O - current;
            ofVec3f N = dir.getCrossed(unit);
            float length =  line[i].size*_size;
            ofVec3f P = N.getNormalized() * length;
            
            ofVec3f A = P.getRotated(angle, dir);
            ofVec3f B = P.getRotated(angle+incAngle, dir);
            
            dataA.vert = A + current;
            dataB.vert = B + current;
            
            if(i != 0){
                index.push_back(header-1);
                index.push_back(header-2);
                index.push_back(header++);
                index.push_back(header-1);
                index.push_back(header-2);
                index.push_back(header++);
            }
            
            ofVec3f triN = normal(A + current, B + current, A + current + (next-current));
            dataA.norm = triN;
            dataB.norm = triN;
            
            float U1 = lineID / (float)(divide+1);
            float U2 = (lineID +1)/(float)(divide+1);
            float a_tex_u = ofMap(U1, 0, 1, _beginTex.x, _endTex.x);
            float a_tex_v = ofMap(V, 0, 1, _beginTex.y, _endTex.y);
            float b_tex_u = ofMap(U2, 0, 1, _beginTex.x, _endTex.x);
            float b_tex_v = ofMap(V, 0, 1, _beginTex.y, _endTex.y);
            ofVec2f a_tex(a_tex_u,a_tex_v);
            ofVec2f b_tex(b_tex_u,b_tex_v);
            dataA.tex = a_tex;
            dataB.tex = b_tex;
            
            dataA.color = color;
            dataB.color = color;
            
            linePoly.push_back(dataA);
            linePoly.push_back(dataB);
            
            V+=1 / (float)(line.size()-1);
        }
        polygon.push_back(linePoly);
        lineID++;
    }
    
    // Meshの追加
    for (int k = 0; k < polygon.size(); k++) {
        vector<Polygon_Data> &line = polygon[k];
        for (int l = 0;  l< line.size(); l++) {
            
            mesh.addVertex(line[l].vert);
            mesh.addNormal(line[l].norm);
            mesh.addTexCoord(line[l].tex);
            mesh.addColor(line[l].color);
        }
    }
    
    // Indexの追加
    for (int k = 0; k < index.size(); k++) {
        mesh.addIndex(index[k]);
    }
    
}