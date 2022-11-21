#include <stdio.h>
#include <string.h>

//08048e20
char out[] = {0x48, 0x48, 0x48, 0x48, 
              0x48, 0x48, 0x48, 0x48,
              0x48, 0x48, 0x48, 0x48, 
              0x08, 0xb8, 0xff, 0xff, 
              0x20, 0x8e, 0x04, 0x08, 0x03, 0x00};

int out2[] = {0x48, 0x48, 0x48, 0x48, 
              0x48, 0x48, 0x48, 0x48,
              0x48, 0x48, 0x48, 0x48, 
              0x08, 0xb8, 0xff, 0xff, 
              0x20, 0x8e, 0x04, 0x08, 0x03, 0x00};

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