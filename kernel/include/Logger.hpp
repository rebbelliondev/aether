#pragma once

class logger {
public:
    void log(char* str);
    void info(char* str);
    void sucess(char* str);
    void ok(char* str);
    void warning(char* str);
    void error(char* str);
    void failed(char* str);
};

extern logger Logger;