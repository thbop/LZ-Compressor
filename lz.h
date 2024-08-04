#ifndef LZ_H
#define LZ_H

#include "stdlib.h"
#include "string.h"

#define LZ_MAXPATTERNLEN 16

typedef struct {
    char pattern[LZ_MAXPATTERNLEN];
    void *next; // Linked list next
} lz_list;

int LZ_list_push( lz_list **list, char pattern[LZ_MAXPATTERNLEN] ) {
    size_t patternlen = strlen(pattern);
    if ( patternlen > LZ_MAXPATTERNLEN ) return 1;
    if ( list == NULL ) {
        *list = (lz_list*)malloc(sizeof(lz_list));
        strncpy((*list)->pattern, pattern, LZ_MAXPATTERNLEN);
        return 0;
    }
    else {
        lz_list *new_list = (lz_list*)malloc(sizeof(lz_list));
        new_list->next = *list;
        strncpy(new_list->pattern, pattern, LZ_MAXPATTERNLEN);
        *list = new_list;
        return 0;
    }
}

// ADD FREE FUNCTION
// #Born 2 malloc(); Forced 2 free();

// Searches list for a symbol string and returns its index; if none is found return -1
// Since recursion is used, for x please supply a zero
int LZ_search_list( lz_list *list, char symbol[LZ_MAXPATTERNLEN], unsigned int x ) {
    if ( list == NULL ) return -1;
    if ( !strcmp(list->pattern, symbol) ) return x;
    LZ_search_list( list->next, symbol, x+1 );
}

size_t LZ_str16len( short* str ) {
    size_t i = 0;
    while ( str[i] ) i++;
    return i-1;
}


// Finds the next two shorts and returns them packed as a long
// char *src_loc       = src+cursor
// char loc_d          = src+cursor delta; init as 0
// int previous_search = -1
long _LZ_next_two( char *src_loc, char loc_d, char *pattern, lz_list **list, size_t *list_size, int previous_search ) {
    char p_len     = strlen(pattern);
    pattern[p_len] = src_loc[loc_d];
    
    int search = LZ_search_list( *list, pattern, 0 );
    if ( search == -1 ) {                                     // If pattern not found
        LZ_list_push(list, pattern); (*list_size)++;          // Push new pattern
        if ( previous_search == -1 ) return (long)pattern[0]; // One char pattern / No previous searches
        else return (long)( ((*list_size-previous_search-1)<<16) | pattern[loc_d] );
    }
    else _LZ_next_two( src_loc, loc_d+1, pattern, list, list_size, search );
}

long LZ_next_two( char *src, size_t cursor, lz_list **list, size_t *list_size ) {
    char pattern[LZ_MAXPATTERNLEN] = { 0 };
    return _LZ_next_two( src+cursor, 0, pattern, list, list_size, -1 );
}

int LZ_compress( char *src, char *dest, size_t dest_size ) {
    size_t
        src_len = strlen(src),
        cursor  = 0;

    size_t unpacked_dest_size = dest_size>>1;
    short *unpacked_dest      = (short*)calloc(unpacked_dest_size, sizeof(short)); // Remember to pack and free

    lz_list *list = NULL;     // Head of the linked list describing known symbols
    size_t list_size = 255;   // Since the list grows from the front to be O(1), I'll use some weird math to get proper non-shifting indices: a=list_size; a - x; while a++
    
    
    while ( cursor < src_len ) {
    }

    return 0;
}

#endif