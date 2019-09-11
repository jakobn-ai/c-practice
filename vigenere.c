#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void stripLast(char* txt) {
    for (int i = 0; txt[i];)
        if (!txt[++i])
            txt[i - 1] = 0;
}

int encOrDec(char* txt, char* key, int* encBit) {
    int keyLength = 0;
    for (; key[keyLength]; ++keyLength);
    if (!keyLength) {
        fprintf(stderr, "Empty key. Aborting.\n");
        return EINVAL;
    }

    if (*encBit) {
        for (int i = 0; txt[i]; i++)
            txt[i] = (txt[i] + key[i % keyLength] - 64) % 95 + 32;
    } else {
        for (int i = 0; txt[i]; i++)
            txt[i] = ((txt[i] - key[i % keyLength]) % 95 + 95) % 95 + 32;
    }
    return 0;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "No encrypt (1) or decrypt (0) specified. Aborting.\n");
        return EINVAL;
    }

    char txt[_POSIX2_LINE_MAX];
    fprintf(stderr, "Enter txt: ");
    fgets(txt, _POSIX2_LINE_MAX, stdin);
    stripLast(txt);
    fprintf(stderr, "Enter key: ");
    char* key = getpass("");
    int encBit = atoi(argv[1]);

    int ret = encOrDec(txt, key, &encBit);
    if (!ret) {
        printf("%s\n", txt);
    }
    return ret;
}

