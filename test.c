#include "stdio.h"
#include "lz.h"

int main() {
    lz_list* list = NULL;
    char str[LZ_MAXPATTERNLEN] = "abs";
    char str1[LZ_MAXPATTERNLEN] = "ffs";
    LZ_list_push(&list, str, 3);
    LZ_list_push(&list, str1, 3);
    // printf("%p\n", list);

    printf("%d\n", LZ_search_list(list, str1, 0));
    return 0;
}