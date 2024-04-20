#include "RSA.h"
#include <math.h>
#include <string.h>
#include <stdio.h>

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

char* encrypt(const char* message, uint32_t encryptionKey, uint32_t modulus)
{
    char encryptedMsg[4] = {0};
    uint32_t encryptedChar = powerModN(message[0], encryptionKey, modulus);
    printf("encrypting %c as %d\n", message[0], encryptedChar);
    encryptedMsg[0] = (uint8_t) encryptedChar & 0xFF; //keep little endian
    encryptedMsg[1] = (uint8_t) (encryptedChar >> 8) & 0xFF; //keep little endian
    encryptedMsg[2] = (uint8_t) (encryptedChar >> 16) & 0xFF; //keep little endian
    encryptedMsg[3] = (uint8_t) (encryptedChar >> 24) & 0xFF; //keep little endian     
    return encryptedMsg;
}
