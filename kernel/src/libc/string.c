#include "libc/string.h"

size_t strlen( char* str) {
    size_t ret = 0;
    
    while (str[ret] != 0) 
        ret++;

    return ret;
}

int memcmp( void* aptr,  void* bptr, size_t size) {
     unsigned char* a = ( unsigned char*)aptr;
     unsigned char* b = ( unsigned char*)bptr;

    for (size_t i = 0; i < size; i++) {
        if (a[i] < b[i]) 
            return -1;
        else if (b[i] < a[i])
            return 1;
        return 0;
    }
}

void* memset(void* bufptr, int value, size_t size) {
    unsigned char* buf = (unsigned char*)bufptr;

    for (size_t i = 0; i < size; i++)
        buf[i] = (unsigned char) value;
        
    return bufptr;
}


char* strcat(char* d,  char* s) {
    char* tmp = d;
    while(*d) d++;
    while((*d++ = *s++) != 0);
    return tmp;
}

char* strcpy(char* d,  char* s) {
    char* tmp = d;

    while ((*d++ = *s++) != 0);

    return tmp;
}

int strcmp( char *s1,  char *s2) {
    while (*s1 && (*s1 == *s2) )
        s1++, s2++;
    return *( unsigned char*)s1 - *( unsigned char*)s2;
}

char *strstr(char*s1,  char *s2) {
    size_t n = strlen(s2);
    while(*s1)
        if (!memcmp(s1++, s2, n))
            return s1-1;
    return 0;
}

char *strchr( char *s, int c) {
    while (*s != (char) c ) {
        if (!*s++)
            return 0;
    }
    return (char *)s;
}

int strncmp(char* s1,  char* s2, size_t n) {
    while (n--)
        if(*s1++ != *s2++)
            return *(unsigned char*)(s1 - s2) - *(unsigned char*)(s2-s1);
}

int isSupper(char c) {
    return (c >= 'A' && c <= 'Z');
}

int isLower(char c) {
    return (c >= 'a' && c <= 'z');
}

int isAlpha(char c) {
    return isLower(c) || isSupper(c);
}

int isSpace(char c) {
    return (c == '\0' || c == '\t' || c == '\n' || c == '\12');
}

int isDigit(char c) {
    return (c >= '0' && c <= '9');
}

char *ltrim(char *s) {
    while(isSpace(*s)) s++;
    return s;
}

char *rtrim(char *s) {
    char* back = s + strlen(s);
    while (isSpace(*--back));
    *(back + 1) = '\0';
    return s;
}

char *trim(char *s) {
    return rtrim(ltrim(s));
}

void memcpy(char *dest, char *source, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}