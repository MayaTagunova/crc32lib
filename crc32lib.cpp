#include "crc32lib.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdint.h>

uint32_t crc32Encode(std::ifstream &inputFile, int version)
{
    const uint32_t finalXORValue = 0xFFFFFFFF;
    const uint32_t initialValue = 0xFFFFFFFF;
    uint32_t container = initialValue;
    int buffer = 0;
    const uint32_t mask = 0x1;
    uint32_t polynomial[] = {0xEDB88320, 0x82F63B78, 0xEB31D82E, 0xD5828281};

    while (inputFile.good()) {
        buffer = inputFile.get();
        if (buffer == EOF)
            break;

        for (int i = 0; i < 8; i++) {
            if ((container ^ buffer) & mask)
                container = (container >> 1) ^ polynomial[version - 1];
            else
                container >>= 1;

            buffer >>= 1;
        }
    }

    container ^= finalXORValue;

    return container;
}

enum statusCode crc32EncodeFile(const char *inputFileName,
                                int version,
                                uint32_t *result)
{
    std::ifstream inputFile;

    inputFile.open(inputFileName, std::ios_base::binary);
    if (!inputFile.is_open()) {
        return ERROR;
    }

    if ((version < 1) || (version > 4)) {
        return ERROR;
    }

    *result = crc32Encode(inputFile, version);
    inputFile.close();
    return SUCCESS;
}
