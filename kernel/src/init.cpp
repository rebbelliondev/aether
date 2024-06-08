#include <Logger.hpp>

extern "C" {
    void init() {
        Logger.info("Inited kernl");
    }
}