#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>

#include "global.h"

extern u16          charsToU16(const char* data, u32 size, u32 startIndex);
extern u32          charsToU32(const char* data, u32 size, u32 startIndex);
extern std::string  charsToString(const char* data, u32 size, u32 startIndex, u32 length);

#endif // UTILS_H