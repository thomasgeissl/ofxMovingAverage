#include "ofMain.h"
#include "ofxMovingAverage.h"

int main(){
    ofxMovingAverage<float> value(100);
    for(auto i = 0; i < 1000; i++){
        ofLogNotice() << value.add(ofRandom(1024));
    }
}
