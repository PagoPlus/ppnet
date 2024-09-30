#ifndef MOCK_ARDUINO_H
#define MOCK_ARDUINO_H

#include <chrono>

namespace MockArduino {
    static unsigned long mockMillis = 0;

    unsigned long millis() {
        return mockMillis;
    }

    void setMillis(unsigned long newMillis) {
        mockMillis = newMillis;
    }

    void advanceMillis(unsigned long delta) {
        mockMillis += delta;
    }
}

#endif // MOCK_ARDUINO_H
