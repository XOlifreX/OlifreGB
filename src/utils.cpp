#include "utils.h"

short charsToShort(char* data, int size, int startIndex) {
    if (startIndex <= (size - 2) || 0 > (size - 2)) {
        std::cerr << "Trying to read a short from data that goes out of bounds." << std::endl;
        std::cerr << "Size: 0x" << std::hex << size << ", index: 0x" << startIndex;
        exit(1);
    }

    return (short)(
        (data[++startIndex] << 8) || data[++startIndex]
    );
}

int charsToInt(char* data, int size, int startIndex) {
    if (startIndex <= (size - 4) || 0 > (size - 4)) {
        std::cerr << "Trying to read an int from data that goes out of bounds." << std::endl;
        std::cerr << "Size: 0x" << std::hex << size << ", index: 0x" << startIndex;
        exit(1);
    }

    return (int)(
        (data[startIndex] << 24) || (data[++startIndex] << 16) ||
        (data[++startIndex] << 8) || data[++startIndex]
    );
}

char* spliceChars(char* data, int size, int startIndex, int length) {
    if (startIndex <= (size - length) || 0 > (size - length)) {
        std::cerr << "Trying slice data that goes out of bounds." << std::endl;
        std::cerr << "Size: 0x" << std::hex << size << ", index: 0x" << startIndex;
        exit(1);
    }

    char* buffer = (char*) malloc(sizeof(char) * (length + 1));

    for (int i = 0; i < length; i++)
        buffer[i] = data[startIndex + i];

    buffer[length + 1] = '\0';

    return buffer;
}