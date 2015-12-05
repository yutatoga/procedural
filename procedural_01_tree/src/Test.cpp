#include "Test.h"

vector<vector<float> > Test::readTextData(string fileName){
    vector<vector<float> > testDataVector;
    ofBuffer buffer = ofBufferFromFile(fileName);
    if(buffer.size()) {
        for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
            string line = *it;
            if(line.empty() == false) {
                vector<string> words = ofSplitString(line, ",");
                vector<float> numbers;
                for (int i = 0; i < (int)words.size(); i++) {
                    numbers.push_back(ofToFloat(words[i]));
                }
                testDataVector.push_back(numbers);
            }
        }
        return testDataVector;
    }else{
        ofLogError("can't open "+fileName);
    }
}

void Test::testSegmentHelperDrawLine(vector<vector<float> > testDataVector, ofColor color){
    SegmentHelper *sh;
    for (int i = 0; i < testDataVector.size(); i++) {
        sh->drawLine(testDataVector[i][0], testDataVector[i][1], testDataVector[i][2], testDataVector[i][3], testDataVector[i][4], testDataVector[i][5], testDataVector[i][6], color);
    }
}

void Test::testSegmentHelperDrawLine(vector<vector<float> > testDataVector){
    testSegmentHelperDrawLine(testDataVector , ofColor::red);
}

void Test::testSegmentHelperDrawLine(string fileName){
    vector<vector<float> > testDataVector = this->readTextData(fileName);
    testSegmentHelperDrawLine(testDataVector);
}

