#ifndef CRYPTO_H
#define CRYPTO_H

#include <math.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                   "abcdefghijklmnopqrstuvwxyz"
                                   "0123456789+/";

char *base64_encode(const unsigned char *data, size_t input_length, size_t *output_length);
bool isPrime(int n);
int getPrime(int i);

#define DELTA 0x9e3779b9
#define MX (((z>>5^y<<2) + (y>>3^z<<4)) ^ ((sum^y) + (key[(p&3)^e] ^ z)))

// void xxtea_encrypt(uint32_t *data, uint32_t len, uint32_t const key[4]);
// void xxtea_decrypt(uint32_t *data, uint32_t len, uint32_t const key[4]);
// void xxtea_encrypt_bytes(uint8_t *data, uint32_t len, uint32_t const key[4]);
// void xxtea_decrypt_bytes(uint8_t *data, uint32_t len, uint32_t const key[4]);

#endif