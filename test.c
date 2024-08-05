#include "stdio.h"
#include "lz.h"

int main() {
    char buf[400] = "bubblebubblebubblebubblebubblebubblebubblebubblebubblebubblebubblebubblebubblebubblebubblebubblebubblebubblebubble";
    u8 dest[500] = { 0 };
    if ( LZ_compress(buf, dest, 500) ) printf("Error!\n");


    for ( int i = 0; i < 500; i++ )
        printf("%02X ", dest[i]);

    return 0;
}