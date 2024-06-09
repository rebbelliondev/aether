#ifndef STRING_H_IMPORT
#define STRING_H_IMPORT

#include <stddef.h>
#include <stdint.h>

#include <stddef.h>

#ifndef _STRING_H
#define _STRING_H

size_t strlen( char* str);
int memcmp( void* aptr,  void* bptr, size_t size);
void* memset(void* bufptr, int value, size_t size);
char* strcat(char* d,  char* s);
char* strcpy(char* d,  char* s);
int strcmp( char *s1,  char *s2);
char *strstr(char*s1,  char *s2);
char *strchr( char *s, int c);
int strncmp(char* s1,  char* s2, size_t n);
int isSupper(char c);
int isLower(char c);
int isAlpha(char c);
int isSpace(char c);
int isDigit(char c);
char *ltrim(char *s);
char *rtrim(char *s);
char *trim(char *s);
void memcpy(char *dest, char *source, int nbytes);

#endif

#endif