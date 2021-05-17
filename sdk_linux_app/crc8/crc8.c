#include "crc8.h"

uint8_t crc8(uint8_t *ptr, uint32_t len)
{
    uint8_t i = 0;
    uint8_t crc = 0;

    while (len--) {
        crc ^= *ptr++;
        for (i = 0; i < 8; i++) {
            if (crc & 0x01) {
                crc = (crc >> 1) ^ 0x8C;
            } else {
                crc >>= 1;
            }
        }
    }

    return crc;
}