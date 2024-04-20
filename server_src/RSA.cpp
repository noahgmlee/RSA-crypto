#include "RSA.h"
#include <math.h>
#include <string.h>
#include <stdio.h>

char globalEncryptionBuffer[1024 * 4] = {0};

uint32_t powerModN(uint32_t base, uint32_t power, uint32_t modulus)
{
    uint64_t result = 1;
    uint64_t base64b = (uint64_t) base;
    for (int i = 0; i < power; i++)
    {
        result *= base64b;
        result = result % modulus;
    }
    return (uint32_t) result;
}

char* encrypt(const char* message, uint16_t strlen, uint32_t encryptionKey, uint32_t modulus)
{
    memset(globalEncryptionBuffer, 0, 1024 * 4); //clear buffer
    for (int i = 0; i < strlen; i++)
    {
        int offset = 4*i;
        uint32_t encryptedChar = powerModN(message[i], encryptionKey, modulus);
        printf("encrypting %c as %d\n", message[i], encryptedChar);
        globalEncryptionBuffer[offset] = (uint8_t) encryptedChar & 0xFF; //keep little endian
        globalEncryptionBuffer[offset + 1] = (uint8_t) (encryptedChar >> 8) & 0xFF; //keep little endian
        globalEncryptionBuffer[offset + 2] = (uint8_t) (encryptedChar >> 16) & 0xFF; //keep little endian
        globalEncryptionBuffer[offset + 3] = (uint8_t) (encryptedChar >> 24) & 0xFF; //keep little endian     
    }
    return globalEncryptionBuffer;
}
