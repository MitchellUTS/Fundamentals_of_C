/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * 
 * Author(s):      Mitchell Lee, ...
 *  
 * Date of creation: 18/09/2019
 * 
 * Purpose: To provide all required compression functions
 * 
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef unsigned int my_uint_t;

struct huffman_code {
    my_uint_t length;
    my_uint_t code;
};
typedef struct huffman_code huffman_code_t;

huffman_code_t huffman_code_create(char* code);
my_uint_t code_to_binary(char* string, my_uint_t size);

void testByteShift();

void print_byte_as_bits(char val) {
    int i = 0;
    for (i = 7; 0 <= i; i--) {
        printf("%c", (val & (1 << i)) ? '1' : '0');
    }
}

void print_bits(char * ty, char * val, unsigned char * bytes, size_t num_bytes) {
    printf("(%s) %s = [ ", ty, val);

    int i;
    for (i = 0; i < num_bytes; i++) {
        print_byte_as_bits(bytes[i]);
        printf(" ");
    }
    printf("]\n");
}

#define SHOW(T,V) do { T x = V; print_bits(#T, #V, (unsigned char*) &x, sizeof(x)); } while(0)