#include "../inc/crypto.h"
#include <string.h>

char *base64_encode(const unsigned char *data, size_t input_length, size_t *output_length)
{
    *output_length = 4 * ((input_length + 2) / 3);
    char *encoded_data = malloc(*output_length + 1);

    if ((encoded_data = NULL))
        return NULL;

    for (size_t i = 0, j = 0; i < input_length;)
    {
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
    if (input_length % 3 == 1)
    {
        // padding = 2;
        encoded_data[*output_length - 1] = '=';
        encoded_data[*output_length - 2] = '=';
    }
    else if (input_length % 3 == 2)
    {
        // padding = 1;
        encoded_data[*output_length - 1] = '=';
    }

    encoded_data[*output_length] = '\0';
    return encoded_data;
}

bool isPrime(int n)
{
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    int limit = (int)sqrt(n);
    for (int i = 3; i <= limit; i += 2)
    {
        if (n % i == 0)
        {
            return false;
        }
    }

    return true;
}

int getPrime(int i)
{
    int count = 0;
    int num = 2;
    int primes[20];

    while (count < 20)
    {
        if (isPrime(num))
        {
            primes[count] = num;
            count++;
        }
        num++;
    }

    return primes[i];
}

/*

void xxtea_encrypt(uint32_t *data, uint32_t len, uint32_t const key[4]) {
    uint32_t n = len - 1;
    uint32_t z = data[n], y = data[0], sum = 0, e;
    uint32_t p, q;
    
    if (len < 1) return;
    
    q = 6 + 52 / len;
    while (q-- > 0) {
        sum += DELTA;
        e = (sum >> 2) & 3;
        for (p = 0; p < n; p++) {
            y = data[p + 1];
            z = data[p] += MX;
        }
        y = data[0];
        z = data[n] += MX;
    }
}

void xxtea_decrypt(uint32_t *data, uint32_t len, uint32_t const key[4]) {
    uint32_t n = len - 1;
    uint32_t z = data[n], y = data[0], sum, e;
    uint32_t p, q;
    
    if (len < 1) return;
    
    q = 6 + 52 / len;
    sum = q * DELTA;
    while (sum != 0) {
        e = (sum >> 2) & 3;
        for (p = n; p > 0; p--) {
            z = data[p - 1];
            y = data[p] -= MX;
        }
        z = data[n];
        y = data[0] -= MX;
        sum -= DELTA;
    }
}

// 辅助函数：处理字节数组（自动填充）
void xxtea_encrypt_bytes(uint8_t *data, uint32_t len, uint32_t const key[4]) {
    // 填充到 8 字节的倍数
    uint32_t pad = 8 - (len % 8);
    uint32_t new_len = len + pad;
    uint8_t *padded_data = malloc(new_len);
    
    memcpy(padded_data, data, len);
    memset(padded_data + len, pad, pad);  // PKCS#7 风格填充
    
    xxtea_encrypt((uint32_t*)padded_data, new_len/4, key);
    memcpy(data, padded_data, new_len);
    free(padded_data);
}

void xxtea_decrypt_bytes(uint8_t *data, uint32_t len, uint32_t const key[4]) {
    if (len % 8 != 0) return;  // 长度必须是 8 的倍数
    
    xxtea_decrypt((uint32_t*)data, len/4, key);
    
    // 移除填充
    uint8_t pad = data[len-1];
    if (pad < 1 || pad > 8) return;
    data[len-pad] = '\0';
}

*/
