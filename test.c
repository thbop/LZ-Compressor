#include "stdio.h"
#include "lz.h"

int main() {
    char buf[14] = "AABABBABBAABA";
    lz_list *list = NULL;
    size_t list_size = 255;


    LZ_next_two(buf, 0, &list, &list_size);
    long res = LZ_next_two(buf, 1, &list, &list_size);
    printf("%X\n", res);
    printf("%s\n", list->pattern);
    return 0;
}