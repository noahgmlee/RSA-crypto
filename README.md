# RSA-crypto
client (my laptop) server (my raspberry pi) RSA exchange for message encryption

# client
BUILD: g++ -o client client.cpp RSA.cpp
RUN: ./client

# server
BUILD: g++ -o server server.cpp RSA.cpp
RUN: ./server
