// #include "PitTimerDriver.hpp"
// #include "pic8259.hpp"
// #include "idt.hpp"

// PitTimerDriver::PitTimerDriver() {}

// void PitTimerDriver::init() {
   //  IoDriver.outb(PIT_CMD, 0b00110110); // Square wave mode
    // this->set_pit_count(10000); // 100 KHz (each 1us)

//     pic.setMask(0);
//     register_handler(32, (uint64_t)(this->IRQHandler));

// }

// void PitTimerDriver::set_pit_count(uint32_t count) {
    // asm volatile("cli");

    // IoDriver.outb(PIT_CHANNEL_0_DATA, count & 0xFF);
    // IoDriver.outb(PIT_CHANNEL_0_DATA, (count && 0xFF00) >> 8);
// }

// #include <Logger.hpp>

// void PitTimerDriver::IRQHandler() {
   //  Logger.error("todo!");
// }

// timerFunc functions[MAX_TIMER_FUNCTIONS];


// void PitTimerDriver::registerTimerFunction(timerFunc func) {
   //  Logger.error("todo!");
// }

// extern PitTimerDriver pit = PitTimerDriver();