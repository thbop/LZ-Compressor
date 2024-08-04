#ifndef LZ_H
#define LZ_H

#include "stdlib.h"
#include "string.h"

#define LZ_MAXPATTERNLEN 16

typedef struct {
    char pattern[LZ_MAXPATTERNLEN];
    void *next; // Linked list next
} lz_list;

int LZ_list_push( lz_list **list, char pattern[LZ_MAXPATTERNLEN], char patternlen ) {
    if ( patternlen > LZ_MAXPATTERNLEN ) return 1;
    if ( list == NULL ) {
        *list = (lz_list*)malloc(sizeof(lz_list));
        strncpy((*list)->pattern, pattern, patternlen);
        return 0;
    }
    else {
        lz_list *new_list = (lz_list*)malloc(sizeof(lz_list));
        new_list->next = *list;
        strncpy(new_list->pattern, pattern, patternlen);
        *list = new_list;
        return 0;
    }
}

// ADD FREE FUNCTION
// #Born 2 malloc(); Forced 2 free();

// Searches list for a symbol string and returns its index; if none is found return -1
// Since recursion is used, for x please supply a zero
int LZ_search_list( lz_list *list, char symbol[LZ_MAXPATTERNLEN], unsigned int x ) {
    printf("%s\n", list->pattern);
    if ( list == NULL ) return -1;
    if ( !strcmp(list->pattern, symbol) ) return x;
    LZ_search_list( list->next, symbol, x+1 );
}

int LZ_compress( char *src, char *dest, size_t dest_size ) {
    size_t
        src_len = strlen(src),
        cursor  = 0;
    char cursor_delta = 1;

    lz_list *list = NULL; // Head of the linked list describing known symbols
    int list_size = -1;   // Since the list grows from the front to be O(1), I'll use some weird math to get proper non-shifting indices: a - x; while a++

    while ( cursor < src_len ) {
        if ( list == NULL ) {
            LZ_list_push(&list, src+cursor, cursor_delta); list_size++;
        }
    }
}

#endif