#include "stdio.h"
#include "lz.h"

int main() {
    char buf[14] = "AABABBABBAABA";
    if ( LZ_compress(buf, buf, 20) ) printf("Error!\n");

    return 0;
}