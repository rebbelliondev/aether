#pragma once
#include <drivers/IoDriver.hpp>

#define PIT_CHANNEL_0_DATA  0x40
#define PIT_CHANNEL_1_DATA  0x41
#define PIT_CHANNEL_2_DATA  0x42
#define PIT_CMD             0x43

#define MAX_TIMER_FUNCTIONS 32

typedef struct {
    uint32_t timeout;
    void* addr;
} timerFunc;

class PitTimerDriver {
public:
    PitTimerDriver();

    void registerTimerFunction(timerFunc func);

    void init();
    void set_pit_count(uint16_t count);
};

extern PitTimerDriver pit;