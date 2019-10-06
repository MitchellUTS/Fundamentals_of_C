/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * 
 * Author(s):      Mitchell Lee, ...
 *  
 * Date of creation: 18/09/2019
 * 
 * Purpose: Provide a variety of core/basic functions
 * 
*******************************************************************************/

/* I have defined booleans: true and false to further increase readability */
#define false 0
#define true  1

void print_byte_as_bits(char val);
void print_bits(char * ty, char * val, unsigned char * bytes, size_t num_bytes);

#define SHOW(T,V) do { T x = V; print_bits(#T, #V, (unsigned char*) &x, sizeof(x)); } while(0)

int between(int value, int min, int max);
void loginFunction();
