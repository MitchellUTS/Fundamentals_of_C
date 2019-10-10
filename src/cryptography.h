/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * 
 * Author(s):      Mitchell Lee, ...
 *  
 * Date of creation: 18/09/2019
 * 
 * Purpose: To provide all required crypographic functions
 * 
*******************************************************************************/

struct byte_node {
    struct byte_node* next;
    char byte;
};
typedef struct byte_node byte_node_t;

char* mask_block_length(char* key, char* data, int length);

void mask_file(char* input_name, char* output_name, char* key);

char mask_byte(char key, char data, char* result);

void byte_list(byte_node_t* head, char byte);
byte_node_t* byte_node_add(byte_node_t* position, char byte);
byte_node_t* byte_node_delete_next(byte_node_t* position);

void create_circular_byte_stream_length(byte_node_t* head, char* data, int size);

