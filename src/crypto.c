#include "../inc/crypto.h"
#include <math.h>
#include <stdlib.h>

static const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                   "abcdefghijklmnopqrstuvwxyz"
                                   "0123456789+/";

char* base64_encode(const unsigned char* data, size_t input_length, size_t* output_length) {
    *output_length = 4 * ((input_length + 2) / 3);
    char* encoded_data = malloc(*output_length + 1);

    if (encoded_data == NULL)
        return NULL;

    for (size_t i = 0, j = 0; i < input_length;) {
        uint32_t octet_a = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_b = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_c = i < input_length ? (unsigned char)data[i++] : 0;

        uint32_t triple = (octet_a << 16) | (octet_b << 8) | octet_c;

        encoded_data[j++] = base64_table[(triple >> 18) & 0x3F];
        encoded_data[j++] = base64_table[(triple >> 12) & 0x3F];
        encoded_data[j++] = base64_table[(triple >> 6) & 0x3F];
        encoded_data[j++] = base64_table[triple & 0x3F];
    }

    // int padding;
    if (input_length % 3 == 1) {
        // padding = 2;
        encoded_data[*output_length - 1] = '=';
        encoded_data[*output_length - 2] = '=';
    } else if (input_length % 3 == 2) {
        // padding = 1;
        encoded_data[*output_length - 1] = '=';
    }

    encoded_data[*output_length] = '\0';
    return encoded_data;
}

bool is_prime(int n) {
    if (n < 2)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;

    int limit = (int)sqrt(n);
    for (int i = 3; i <= limit; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

int nth_prime(int i) {
    static const int primes[] = {2,  3,  5,  7,  11, 13, 17, 19, 23, 29,
                                 31, 37, 41, 43, 47, 53, 59, 61, 67, 71};
    if (i < 0 || i >= 20)
        return -1;
    return primes[i];
}
