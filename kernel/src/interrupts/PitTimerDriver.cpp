#include "PitTimerDriver.hpp"
#include "pic8259.hpp"
#include "idt.hpp"


#include <Logger.hpp>

extern "C" {
   void pit_irq_handler() {
      Logger.error("todo!");

      pic.eoi(0);
   }
}

PitTimerDriver::PitTimerDriver() {}

void PitTimerDriver::init() {
    IoDriver.outb(PIT_CMD, 0b00110110); // Square wave mode
    this->set_pit_count(10000); //100 KHz (each 1us)

    pic.activate(0);
    registerHandler(32, (uint64_t)pit_irq_handler);

}

void PitTimerDriver::set_pit_count(uint32_t count) {
    asm volatile("cli");

    IoDriver.outb(PIT_CHANNEL_0_DATA, count & 0xFF);
    IoDriver.outb(PIT_CHANNEL_0_DATA, (count && 0xFF00) >> 8);
}

timerFunc functions[MAX_TIMER_FUNCTIONS];


void PitTimerDriver::registerTimerFunction(timerFunc func) {
    Logger.error("todo!");
}

extern PitTimerDriver pit = PitTimerDriver();
