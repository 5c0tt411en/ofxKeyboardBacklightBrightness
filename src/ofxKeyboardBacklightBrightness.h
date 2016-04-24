#pragma once

#include "ofMain.h"

class ofxKeyboardBacklightBrightness {

    public:
        void setup();
        unsigned long getBrightness();
        void setBrightness(uint64_t ledValue);
        void setBrightnessFade(uint64_t ledValue, uint64_t time_ms);
    
    io_connect_t connect;
    
    enum {
        kGetSensorReadingID   = 0,
        kGetLEDBrightnessID   = 1,
        kSetLEDBrightnessID   = 2,
        kSetLEDFadeID         = 3,
    };
};
