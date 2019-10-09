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
#include "core.h"

/*******************************************************************************
 * This function encrypts a whole file
 * inputs:
 * - The source and destination file names, as well as a password to 
 *    secure the data with.
 * outputs:
 * - It saves the current byte's code to memory if applicable 
*******************************************************************************/
void mask_file(char* input_name, char* output_name, char* key) {
    
    FILE* input_file_stream;
    /* Open data file the file for reading data */ 
    input_file_stream = fopen(input_name, "rb");

    FILE* output_file_stream;
    /* Open data file the file for writing data */ 
    output_file_stream = fopen(output_name, "wb");

    if (input_file_stream == NULL || output_file_stream == NULL) {
        printf("Fail to open files for encryption.\n");
        return;
    }

    fseek(input_file_stream, 0, SEEK_END);
    long file_size = ftell(input_file_stream);
    rewind(input_file_stream);

    /* Load the file into memory */
    char* buffer;
    buffer = (char*) malloc(file_size);
    if (buffer == NULL) {
        printf("Fail to allocate memory for encryption.\n");
        return;
    }
    
    fread(buffer, 1, file_size, input_file_stream);

    /* Encrypt the data and return it */
    char* result1 = mask_block_length(key, buffer, file_size);

    /* Write it out to the file */
    fwrite(result1, 1, file_size, output_file_stream);
    
    free(result1);
    free(buffer);

    fclose(input_file_stream);
    fclose(output_file_stream);
}

/*******************************************************************************
 * This function applys the bit mask to a block of data
 * inputs:
 * - The key to encrypt with, data to encrypt and the length of data to encrypt
 * outputs:
 * - A pointer to the encrypted data
*******************************************************************************/
char* mask_block_length(char* key, char* data, int length) {
    byte_node_t* current = (byte_node_t*) malloc(sizeof(byte_node_t));
    create_circular_byte_stream_length(current, key, strlen(key));
    char* result = (char*) malloc(sizeof(char) * length);
    
    int i;
    for (i = 0; i < length; i++) {
        mask_byte(current->byte, data[i], result + i);
        current->next;
    }
    return result;
}

/*******************************************************************************
 * This function applys the bit mask to a byte
 * inputs:
 * - The key for the byte and the byte to encrypt.
 * outputs:
 * - The encrypted byte
*******************************************************************************/
char mask_byte(char key, char data, char* result) {
    return *result = (key|data) ^ (key&data);
};

/*******************************************************************************
 * This function create as circular linked list
 * inputs:
 * - The head of the list, data to populate the list with and the 
 *    length of the data.
 * outputs:
 * - None
*******************************************************************************/
void create_circular_byte_stream_length(byte_node_t* head, char* data, int size) {
    if(size > 0) {
        byte_node_t* current = head;
        int i;
        byte_list(head, data[0]);
        for(i = 1; i < size; i++) {
            current = byte_node_add(current, data[i]);
        }
    } else {
        printf("Error a circular byte stream could not be create because there was %d bytes of data\n", size);
    }
}

/*******************************************************************************
 * This function creates a new circular linked list
 * inputs:
 * - The location of the first node and the contents for the first node
 * outputs:
 * - None
*******************************************************************************/
void byte_list(byte_node_t* head, char byte) {
    head->byte = byte;
    head->next = head;
}

/*******************************************************************************
 * This function adds a node to a circular linked list
 * inputs:
 * - The position to add the node at and the data to put at that location
 * outputs:
 * - The location of the new node
*******************************************************************************/
byte_node_t* byte_node_add(byte_node_t* position, char byte) {
    byte_node_t* new_node = (byte_node_t*) malloc(sizeof(byte_node_t));
    new_node->byte = byte;
    new_node->next = position->next;
    position->next = new_node;
    return new_node;
}

/*******************************************************************************
 * This function delete an element from a circular linked list
 * inputs:
 * - The position to delete after
 * outputs:
 * - The next item in the list
*******************************************************************************/
byte_node_t* byte_node_delete_next(byte_node_t* position) {
    if (position == position->next){
        free(position);
        return NULL;
    }
    byte_node_t* to_delete = position->next;
    position->next = to_delete->next;
    free(to_delete);
    return position->next;
}
