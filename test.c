#include "stdio.h"
#include "lz.h"

int main() {
    short buf16[7] = { 'H', 'e', 'l', 'l', 'o', ' ', 0 };
    char buf[6] = "World";
    LZ_append_str16(buf16, buf, 6, 7);
    
    for ( int i = 0; i < 7; i++ ) printf("%c", buf16[i]);
    return 0;
}