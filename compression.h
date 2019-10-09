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

#define false 0
#define true  1

typedef unsigned int my_uint_t;
typedef unsigned long long ubig_t;
typedef unsigned char byte;

struct huffman_tree_node {
    struct huffman_tree_node *left, *right, *parent;
    int code;
    ubig_t frequency;
};
typedef struct huffman_tree_node huffman_tree_node_t;

struct huffman_node {
    struct huffman_node* next;
    struct huffman_tree_node* node;
};
typedef struct huffman_node huffman_node_t;

void count_frequencies(byte* data, ubig_t len, ubig_t* frequencies);
void init_frequencies(ubig_t* frequencies);
void sort_frequencies(byte* sort_order, ubig_t* frequencies);

huffman_tree_node_t* build_huffman_tree(ubig_t* frequencies);
huffman_tree_node_t huffman_tree_node_create(ubig_t frequency, int code, huffman_tree_node_t* left, huffman_tree_node_t* right, huffman_tree_node_t* parent);
my_uint_t code_to_binary(char* string, my_uint_t size);
huffman_node_t* squash_tree(huffman_node_t* head);

void traverse_tree_recursive(huffman_tree_node_t* root, char* code, unsigned short length, char* code_array);
void traverse_tree(huffman_tree_node_t* root, char* code_array);

void huffman_list(huffman_node_t** head, huffman_tree_node_t* node);
huffman_node_t* huffman_node_add(huffman_node_t* position, huffman_tree_node_t* node);
huffman_node_t* huffman_node_delete_next(huffman_node_t* position);
void print_node_list(huffman_node_t* start);

huffman_node_t* add_prority_node(huffman_node_t* head, huffman_tree_node_t* node);

void testByteShift();

void print_byte_as_bits(char val) {
    int i;
    for (i = 7; 0 <= i; i--) {
        printf("%c", (val & (1 << i)) ? '1' : '0');
    }
}

void print_bits(char * ty, char * val, byte * bytes, size_t num_bytes) {
    printf("(%s) %s = [ ", ty, val);

    int i;
    for (i = 0; i < num_bytes; i++) {
        print_byte_as_bits(bytes[i]);
        printf(" ");
    }
    printf("]\n");
}

#define SHOW(T,V) do { T x = V; print_bits(#T, #V, (byte*) &x, sizeof(x)); } while(0)