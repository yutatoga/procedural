#include "Segment.h"

string Segment::toString(){
    return "Segment@"+ofToString(loc.x)+","+ofToString(loc.y)+":"+ofToString(grow_count)+"\n\t  "+ofToString(growDir);
}