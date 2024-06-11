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

extern "C" {
    #include <libc/string.h>
}

void itoa(char *buf, int base, int d) {
    char *p = buf;
    char *p1, *p2;
    unsigned long ud = d;
    int divisor = 10;

    /* If %d is specified and D is minus, put ‘-’ in the head. */
    if (base == 'd' && d < 0) {
        *p++ = '-';
        buf++;
        ud = -d;
    } else if (base == 'x')
        divisor = 16;

    /* Divide UD by DIVISOR until UD == 0. */
    do {
        int remainder = ud % divisor;
        *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
    } while (ud /= divisor);

    /* Terminate BUF. */
    *p = 0;

    /* Reverse BUF. */
    p1 = buf;
    p2 = p - 1;
    while (p1 < p2) {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }
}

void debugf(const char *format, ...) {
    char **arg = (char **)&format;
    int c;
    char buf[32];

    arg++;

    memset(buf, 0, sizeof(buf));
    while ((c = *format++) != 0) {
        if (c != '%')
            E9Driver.send(c);
        else {
            char *p, *p2;
            int pad0 = 0, pad = 0;

            c = *format++;
            if (c == '0') {
                pad0 = 1;
                c = *format++;
            }

            if (c >= '0' && c <= '9') {
                pad = c - '0';
                c = *format++;
            }

            switch (c) {
                case 'd':
                case 'u':
                case 'x':
                    itoa(buf, c, *((int *)arg++));
                    p = buf;
                    goto string;
                    break;

                case 's':
                    p = *arg++;
                    if (!p)
                        p = "(null)";

                string:
                    for (p2 = p; *p2; p2++)
                        ;
                    for (; p2 < p + pad; p2++)
                        E9Driver.send(pad0 ? '0' : ' ');
                    while (*p)
                        E9Driver.send(*p++);
                    break;

                default:
                    E9Driver.send(*((int *)arg++));
                    break;
            }
        }
    }
}

logger Logger;