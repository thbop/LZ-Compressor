#include "stdio.h"
#include "lz.h"

int main() {
    // char buf[27] = "AABABBABBAABAAABABBABBAABA";
    u8 dest[100] = { 0 };
    // if ( LZ_compress(buf, buf, 100) ) printf("Error!\n");

    u16 unpacked[7] = { 0x123, 0x456, 0x789, 0xABC, 0xDEF, 0x654, 0 };
    LZ_pack(unpacked, dest, 100);

    for ( int i = 0; i < 28; i++ )
        printf("%02X ", dest[i]);

    return 0;
}