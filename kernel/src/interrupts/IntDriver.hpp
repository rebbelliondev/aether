#pragma once

#include <stddef.h>
#include <stdint.h>

enum INT_FEATURE {
    Pic8259,
    PitTimer,
};

class IntDriver {
private:
    bool pic8259_inited;
    bool pit_timer_inited;
public:
    IntDriver();

    void init();
    void setHandler(int n, uint64_t handler);
    void activate(INT_FEATURE feature);
};

extern IntDriver IntDrivr;