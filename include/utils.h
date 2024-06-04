#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cstdlib>

extern short charsToShort(char* data, int size, int startIndex);
extern int charsToInt(char* data, int size, int startIndex);
extern char* spliceChars(char* data, int size, int startIndex, int length);

#endif // UTILS_H