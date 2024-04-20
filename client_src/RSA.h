#include <stdint.h>

// https://asecuritysite.com/encryption/nprimes?y=16 - generate primes
#define PRIME1 36209 //16b
#define PRIME2 42797 //16b
#define ENCRYPTION_KEY 33377 //16b
#define MODULUS PRIME1 * PRIME2 //32b

int powerModN(uint32_t base, uint64_t power, uint32_t modulus);

void getKey(uint32_t& decryption_key);

uint32_t extendedEuclidean(uint32_t n, uint32_t phiOfn);

char decryptMessage(const char* message, uint16_t strlen, uint32_t decryptionKey, uint32_t modulus);