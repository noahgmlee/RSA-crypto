#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include "RSA.h"

#define PORT 3434 //Auston Matthews
int main()
{
#ifdef TEST
    // int temp = powerModN(12, (uint64_t)ENCRYPTION_KEY, MODULUS);
    // int check = powerModN(temp, (uint64_t)516348961, MODULUS);
    // printf("put in 12, received %d\n", check);

    // uint32_t decryptionKey;
    // getKey(decryptionKey);

    extendedEuclidean(221, 299);

    return 0;
#else
    int status, valread, client_fd;
    struct sockaddr_in serv_addr;
    char buffer[1024 * 4] = { 0 };
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
 
    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "10.0.0.216", &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }
 
    if ((status
         = connect(client_fd, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr)))
        < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    uint32_t decryption_key;
    getKey(decryption_key);
    printf("secret decryption key returned = %d\n", decryption_key);
    
    //share public key
    uint64_t publicKey = (uint64_t) ((uint64_t) ENCRYPTION_KEY << 32 | (uint64_t) MODULUS);
    send(client_fd, &publicKey, 8, 0); //8 byte (2 x 32 bit) public key
    printf("Public Key Sent\n");

    char decrypted_message = '.';
    while (decrypted_message != '!') //poll socket for server message
    {
        valread = read(client_fd, buffer,
                    1024 - 1); // subtract 1 for the null
                                // terminator at the end
        decrypted_message = decryptMessage(buffer, decryption_key, MODULUS);
        printf("%c\n", decrypted_message);
    }
 
    // closing the connected socket
    close(client_fd);
    return 0;
#endif
}