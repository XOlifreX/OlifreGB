#include "utils.h"

u16 charsToU16(const char* data, u32 size, u32 startIndex) {
    if (startIndex >= (size - 2) || 0 > startIndex) {
        std::cerr << "Trying to read a short from data that goes out of bounds." << std::endl;
        std::cerr << "Size: 0x" << std::hex << size << ", index: 0x" << startIndex;
        exit(1);
    }

    return (short)(
        (0xFF00 & (data[startIndex] << 8 )) |
        (0x00FF & (data[++startIndex]))
    );
}

u32 charsToU32(const char* data, u32 size, u32 startIndex) {
    if (startIndex >= (size - 4) || 0 > startIndex) {
        std::cerr << "Trying to read an int from data that goes out of bounds." << std::endl;
        std::cerr << "Size: 0x" << std::hex << size << ", index: 0x" << startIndex;
        exit(1);
    }

    return (int)(
        (0xFF000000 & (data[startIndex]   << 24)) |
        (0x00FF0000 & (data[++startIndex] << 16)) |
        (0x0000FF00 & (data[++startIndex] << 8 )) |
        (0x000000FF & (data[++startIndex]))
    );
}

std::string charsToString(const char* data, u32 size, u32 startIndex, u32 length) {
    if (startIndex >= (size - length) || 0 > startIndex) {
        std::cerr << "Trying slice data that goes out of bounds." << std::endl;
        std::cerr << "Size: 0x" << std::hex << size << ", index: 0x" << startIndex;
        exit(1);
    }

    char buffer[sizeof(char) * (length + 1)];

    for (int i = 0; i < length; i++)
        buffer[i] = data[startIndex + i];

    buffer[length + 1] = '\0';

    std::string temp(buffer);

    return temp;
}