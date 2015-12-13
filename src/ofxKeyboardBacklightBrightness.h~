#pragma once

#include "ofMain.h"

class ofxKeyboardBacklightBrightness {
public:
	string fTs;
    int ret;
	void keyboardBacklightBrightness(float kbbLevel) {

		fTs = ofToString(kbbLevel);
    	stringstream s;
    	s << "../../../../../../../addons/ofxKeyboardBacklightBrightness/src/keyboardBacklightBrightness " << kbbLevel;
    	ret = system(s.str().c_str());
	}
};
