#include "ofxKeyboardBacklightBrightness.h"

void ofxKeyboardBacklightBrightness::setup() {
    kern_return_t kr;
    io_service_t serviceObject;

    serviceObject = IOServiceGetMatchingService(kIOMasterPortDefault,
    IOServiceMatching("AppleLMUController"));

    if (!serviceObject) {
        fprintf(stderr, "Failed to find service matching \"AppleLMUController\".\
        Ending program.");
        exit(1);
    }

    kr = IOServiceOpen(serviceObject, mach_task_self(), 0, &connect);

    IOObjectRelease(serviceObject);
    if(kr != KERN_SUCCESS) {
        mach_error("IOServiceOpen: ", kr);
        exit(kr);
    }
}

unsigned long ofxKeyboardBacklightBrightness::getBrightness() {
    kern_return_t kr;
    IOItemCount inputCount = 1;
    uint32_t outputCount = 1;
    uint64_t outValue = 5;
    const uint64_t fakeInput = 0;

    kr = IOConnectCallMethod(connect, kGetLEDBrightnessID, &fakeInput, inputCount, nil, 0, &outValue, &outputCount, nil, 0);
    if (kr != KERN_SUCCESS) {
        mach_error("IOConnectCallMethod: ", kr);
    }
    return outValue;
}

void ofxKeyboardBacklightBrightness::setBrightness(uint64_t ledValue) {
    if (ledValue > 0xfff) {
        fprintf(stderr, "ledValue is higher than the maximum value, 0xfff. Ending\
        program to avoid hardware funkiness.");
        exit(1);
    }
    kern_return_t kr;
    IOItemCount inputCount = 2;
    uint32_t outputCount = 1;
    uint64_t fakeOutput = 0;
    uint64_t inValues[2];
    inValues[0] = 0;
    inValues[1] = ledValue;
    kr = IOConnectCallMethod(connect, kSetLEDBrightnessID, inValues, inputCount, nil, 0, &fakeOutput, &outputCount, nil, 0);
    if (kr != KERN_SUCCESS) {
        mach_error("IOConnectCallMethod: ", kr);
    }
}


void ofxKeyboardBacklightBrightness::setBrightnessFade(uint64_t ledValue, uint64_t time_ms) {
    if (ledValue > 0xfff) {
        fprintf(stderr, "ledValue is higher than the maximum value, 0xfff. Ending\
        program to avoid hardware funkiness.");
        exit(1);
    }
    kern_return_t kr;
    IOItemCount inputCount = 3;
    uint32_t  outputCount = 1;
    uint64_t fakeOutput = 0;
    uint64_t inValues[3];
    inValues[0] = 0;
    inValues[1] = ledValue;
    inValues[2] = time_ms;

    kr = IOConnectCallMethod(connect, kSetLEDFadeID, inValues, inputCount, nil, 0, &fakeOutput, &outputCount, nil, 0);
    if (kr != KERN_SUCCESS) {
        mach_error("IOConnectCallMethod: ", kr);
    }
}
