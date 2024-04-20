#include "RSA.h"
#include <string.h>
#include <stdio.h>

void getKey(uint32_t& decryption_key)
{
    uint32_t phiOfModulus = (PRIME1 - 1) * (PRIME2 - 1); 
    decryption_key = extendedEuclidean(ENCRYPTION_KEY, phiOfModulus);
}

/*
we know ecryption key and phi(n) are coprime -> gcd(e, phi(n)) = 1
this means d = e^-1 mod phi(n) and de = 1 mod phi(n)
solve the equation de + k*phi(n) = 1 to obtain bezouts coefficient d
*/
uint32_t extendedEuclidean(uint32_t e, uint32_t phiOfn)
{
    uint32_t decryption_key;

    //equation gakesd the form ye + xphi(n) = 1
    int x1 = 1, x2 = 0;
    int y1 = 0, y2 = 1;
    int q, r;

    while(e != 0)
    {
        q = phiOfn / e;
        r = phiOfn % e;
        // phiOfn = q * e + r
        // r = phiOfn - q * e
        // r2 = e - q2 * r
        // r3 = r - q3 * r2

        uint32_t tmp = x2;
        x2 = x1 - q * x2;
        x1 = tmp;

        tmp = y2;
        y2 = y1 - q * y2;
        y1 = tmp;

        phiOfn = e;
        e = r;
    }
    if (y1 < 0)
    {
        y1 = MODULUS + y1;
    }
    decryption_key = y1;
    return decryption_key;
}

int powerModN(uint32_t base, uint64_t power, uint32_t modulus)
{
    uint64_t result = 1;
    uint64_t base64b = (uint64_t) base;
    for (uint64_t i = 0; i < power; i++)
    {
        result *= base64b;
        result = result % modulus;
    }
    return result;
    //return (char) result & 0xFF; //since de = 1 mod phi(n) this regenerates the original message (which was 1 byte char)
}

char decryptMessage(const char* message, uint16_t strlen, uint32_t decryptionKey, uint32_t modulus)
{
    uint32_t* encrypted_message = (uint32_t*) message;
    return powerModN(*encrypted_message, decryptionKey, modulus); 
}
