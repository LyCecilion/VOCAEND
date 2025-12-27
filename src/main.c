#include "../inc/common.h"
#include "../inc/crypto.h"

char encoded_flag[] = "Z2BqZGdtYGZ6RHdkb15oZ152aW5tZF52bnNtZV5nYGVkcl5gdmB4fA==";

int main(void)
{
    setup_io();
    // check_sight();

    lyrics_intro();

    char input[INPUT_LIMIT], processed[INPUT_LIMIT];

    fgets(input, sizeof(input), stdin);

    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n')
        input[len-- - 1] = '\0';

    for (int i = 0; i < len; ++i)
        processed[i] = input[i] ^ 0x01;

    processed[len] = '\0';

    size_t original_len = strlen(processed);
    size_t encoded_len;

    char *encoded = base64_encode((const unsigned char *)processed, original_len, &encoded_len);

    if (strcmp(encoded, encoded_flag) == 0)
    {
        printf("\n\33[5m[FLAG IS CORRECT.]\33[0m Thank you. Good bye.\n");
        exit(0);
    }
    else
    {
        printf("\n[OLD TUNES ARE INCORRECT.]\n");
        exit(0);
    }

    return 0;
}