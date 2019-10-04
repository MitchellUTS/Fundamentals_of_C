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
/*#include "core.h"*/
#include "compression.h"
#include "limits.h"
#include <time.h>

#define SetBit(block, byte, bit) ( block[byte] |= (1 << bit) )
#define ClearBit(block, byte, bit) ( block[byte] &= ~(1 << bit) )
#define CheckBit(block, byte, bit) ( block[byte] & (1 << bit) )

/*
void SetBit(char* block, my_uint_t byte, my_uint_t bit) {
    block[byte] |= (1 << bit); 
}

void ClearBit(char* block, my_uint_t byte, my_uint_t bit) {
    block[byte] &= ~(1 << bit); 
}

int CheckBit(char* block, my_uint_t byte, my_uint_t bit) {
    return block[byte] & (1 << bit); 
}
*/
int testBitField(my_uint_t block_size);

int main() {

    my_uint_t block_size = 1073741824;
    /*my_uint_t block_display_size = 10;block_size;*/
    if (UINT_MAX < block_size) {
        printf("ERROR: The block size of %d is too big.\n", block_size);    
    }

    float sum = 0, count = 0;
    int i;
    float result;
    for (i = 0; i < 10; i++) {
        result = testBitField(block_size);
        if (result != 0) {
            count++;
            sum += result;
        }
    }
    printf("The average time was %f seconds.\nOver %d successful executions.\n", sum/count, (int) count);

    /*print_bits("block_t", "block", (unsigned char*) block, block_size);*/
    /*print_bits("block_t", "block", (unsigned char*) block, block_display_size);*/

    return 0;
}

int testBitField(my_uint_t block_size) {
    char* block = (char*) calloc(block_size, 1);

    if (block == NULL) {
        printf("Block allocation failed.\n");
        return 0;
    } else {
        /*printf("Block allocation successful, %d bytes allocated.\n", block_size);*/
    }

    time_t start_time = time(NULL);

    int byte, bit;
    for (byte = 0; byte < block_size; byte++) {
        for (bit = 0; bit < 8; bit++) {
            SetBit(block, byte, bit);
        }
    }

    time_t end_time   = time(NULL);
    

    free(block);

    if (start_time != -1 && end_time != -1) {
        printf("That operation took %ld seconds.\n", end_time - start_time);
        return (end_time - start_time);
    }
    return 0;
}

void testByteShift() {
    char a = 'a';
    char b = 0;
    char c = 0;

    SHOW(char, a);
    SHOW(char, b);
    SHOW(char, c);
    
    char* code = "011";
    huffman_code_t hCode = huffman_code_create(code);    
    printf("The decimal value of %s is %d.\n", code, hCode.code);
    c = (c >> hCode.length) | (hCode.code << (8 - hCode.length));
    SHOW(char, c);
}

huffman_code_t huffman_code_create(char* code) {
    huffman_code_t new_huffman_code;
    new_huffman_code.length = strlen(code);
    new_huffman_code.code = code_to_binary(code, new_huffman_code.length);
    return new_huffman_code;
}

my_uint_t code_to_binary(char* string, my_uint_t size) {
    int i;
    int power;
    my_uint_t sum = 0;    
    /*printf("String:\t%s\n", string);*/
    for (i = size-1, power = 1; i >= 0; i--, power*=2) {
        /*printf("Size:\t%d\nIndex:\t%d\nLetter:\t%c\nPower:\t%d\n", 
            size, i, string[i], power);*/
        if (string[i] == '1')
            sum += power;
    }
    return sum;
}