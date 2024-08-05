#ifndef LZ_H
#define LZ_H

#include "stdlib.h"
#include "string.h"

#define LZ_MAXPATTERNLEN 16

typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct {
    u8 pattern[LZ_MAXPATTERNLEN];
    void *next; // Linked list next
} lz_list;

int LZ_list_push( lz_list **list, u8 pattern[LZ_MAXPATTERNLEN] ) {
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

// #Born 2 malloc(); Forced 2 free();
void LZ_list_free( lz_list *list ) {
    if ( list != NULL ) {
        if ( list->next != NULL ) LZ_list_free( list->next );
        free(list);
    }
}

// Searches list for a symbol string and returns its index; if none is found return -1
// Since recursion is used, for x please supply a zero
int LZ_search_list( lz_list *list, u8 symbol[LZ_MAXPATTERNLEN], unsigned int x ) {
    if ( list == NULL ) return -1;
    if ( !strcmp(list->pattern, symbol) ) return x;
    LZ_search_list( list->next, symbol, x+1 );
}

size_t LZ_str16len( u16* str ) {
    size_t i = 0;
    while ( str[i] ) i++;
    return i;
}


// Finds the next two u16s and returns them packed as a long
// u8 *src_loc       = src+cursor
// u8 loc_d          = src+cursor delta; init as 0
// int previous_search = -1
long _LZ_next_two( u8 *src_loc, u8 loc_d, u8 *pattern, lz_list **list, size_t *list_size, int previous_search ) {
    u8 p_len     = strlen(pattern);
    pattern[p_len] = src_loc[loc_d];
    
    int search = LZ_search_list( *list, pattern, 0 );
    if ( search == -1 ) {                                     // If pattern not found
        LZ_list_push(list, pattern); (*list_size)++;          // Push new pattern
        if ( previous_search == -1 ) return (long)pattern[0]; // One u8 pattern / No previous searches
        else return (long)( ((*list_size-previous_search-1)<<16) | pattern[loc_d] );
    }
    else _LZ_next_two( src_loc, loc_d+1, pattern, list, list_size, search );
}

long LZ_next_two( u8 *src, size_t *cursor, lz_list **list, size_t *list_size ) {
    u8 pattern[LZ_MAXPATTERNLEN] = { 0 };
    long two = _LZ_next_two( src+*cursor, 0, pattern, list, list_size, -1 );
    *cursor += strlen(pattern);
    return two;
}

int LZ_pack( u16 *unpacked, u8* dest, size_t dest_size ) {
    size_t len = LZ_str16len(unpacked);
    if ( len % 2 ) len++; // If odd, un-odd

    size_t dx = 0, ux = 0;

    while ( ux < len ) {
        dest[dx  ]  =  unpacked[ux  ] >> 4;        // 0xFF0 -> 0xFF
        dest[dx+1]  = (unpacked[ux  ] & 0xF) << 4; // 0x00F -> 0xF0
        dest[dx+1] |=  unpacked[ux+1] >> 8;        // 0xF00 -> 0x0F
        dest[dx+2]  =  unpacked[ux+1] & 0xFF;      // 0x0FF -> 0xFF
        dx += 3; ux += 2;
        if ( dx > dest_size ) return 1;
    }
    return 0;

}

int LZ_compress( u8 *src, u8 *dest, size_t dest_size ) {
    size_t
        src_len = strlen(src),
        cursor  = 0;
    u8 cursor_delta;

    u16 *unpacked_dest = (u16*)calloc(dest_size, sizeof(u16)); // Remember to pack and free

    lz_list *list = NULL;        // Head of the linked list describing known symbols
    size_t list_size = 255;      // Since the list grows from the front to be O(1), I'll use some weird math to get proper non-shifting indices: a=list_size; a - x; while a++
    
    
    while ( cursor < src_len ) {
        long two          = LZ_next_two( src, &cursor, &list, &list_size );
        size_t append_loc = LZ_str16len(unpacked_dest);
        if ( list_size > 0xFFF ) return 2;

        u16
            A = (u16)(two >> 16),
            B = (u16)(two & 0xFFF); // Intentionally 0xFFF not 0xFFFF

        if ( !A ) {
            if ( append_loc > dest_size ) return 1;
            unpacked_dest[append_loc] = B;
        }
        else {
            if ( append_loc+1 > dest_size ) return 1;
            unpacked_dest[append_loc  ] = A;
            unpacked_dest[append_loc+1] = B;
        }
    }
    LZ_list_free(list);


    // for ( int i = 0; i < 28; i++ )
    //     printf("%d ", unpacked_dest[i]);
    
    free(unpacked_dest);

    return 0;
}

#endif