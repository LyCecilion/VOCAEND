#ifndef CRYPTO_H
#define CRYPTO_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

char* base64_encode(const unsigned char* data, size_t input_length, size_t* output_length);
bool is_prime(int n);
int nth_prime(int i);

#endif
