#include <Logger.hpp>
#include <drivers/E9Driver.hpp>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

void logger::log(char *str) {
    E9Driver.send(str);
    E9Driver.send("\n");
}

void logger::info(char *str) {
    E9Driver.send("[");
    E9Driver.send(ANSI_COLOR_BLUE);
    E9Driver.send(" INFO    ");
    E9Driver.send(ANSI_COLOR_RESET);
    E9Driver.send("] ");
    this->log(str);
}

void logger::sucess(char *str) {
    E9Driver.send("[");
    E9Driver.send(ANSI_COLOR_GREEN);
    E9Driver.send(" SUCESS  ");
    E9Driver.send(ANSI_COLOR_RESET);
    E9Driver.send("] ");
    this->log(str);
}

void logger::ok(char* str) {
    E9Driver.send("[");
    E9Driver.send(ANSI_COLOR_GREEN);
    E9Driver.send(" OK      ");
    E9Driver.send(ANSI_COLOR_RESET);
    E9Driver.send("] ");
    this->log(str);
}

void logger::warning(char *str) {
    E9Driver.send("[");
    E9Driver.send(ANSI_COLOR_MAGENTA);
    E9Driver.send(" WARNING ");
    E9Driver.send(ANSI_COLOR_RESET);
    E9Driver.send("] ");
    this->log(str);
}

void logger::error(char *str) {
    E9Driver.send("[");
    E9Driver.send(ANSI_COLOR_RED);
    E9Driver.send(" ERROR   ");
    E9Driver.send(ANSI_COLOR_RESET);
    E9Driver.send("] ");
    this->log(str);
}

void logger::failed(char* str) {
    E9Driver.send("[");
    E9Driver.send(ANSI_COLOR_RED);
    E9Driver.send(" FAILED  ");
    E9Driver.send(ANSI_COLOR_RESET);
    E9Driver.send("] ");
    this->log(str);
}

logger Logger;