#ifndef CRC32LIB_H
#define CRC32LIB_H

#include <stdint.h>

enum statusCode {SUCCESS, ERROR};

#ifdef __cplusplus
extern "C" {
#endif

enum statusCode crc32EncodeFile(const char *inputFileName,
                                int version,
                                uint32_t *result);

#ifdef __cplusplus
}
#endif

#endif // CRC32LIB_H
