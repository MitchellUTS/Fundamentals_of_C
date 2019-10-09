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

/*int main() {

    char key[256]  = "password";*/
    /*printf("Enter the text>");*/
    
    /*
    scanf("%255s", text);
    //scanf("%[^\n]", text);
    //fflush(stdin);
    printf("Enter the key/password>");
    //fflush(stdin);
    //scanf("%[^\n]", key);
    scanf("%255s", key);
    */

   /*FILE* input_file_stream;*/

    /* Open data file the file for reading data */ 
    /*input_file_stream = fopen("input.txt", "rb");*/

    /*FILE* output_file_stream;*/

    /* Open data file the file for writing data */ 
    /*output_file_stream = fopen("output.txt", "wb");

    FILE* output_file_stream2;*/

    /* Open data file the file for writing data */ 
    /*output_file_stream2 = fopen("output2.txt", "wb");

    if (input_file_stream == NULL || output_file_stream == NULL || output_file_stream2 == NULL)
        return 0;

    fseek(input_file_stream, 0, SEEK_END);
    long file_size = ftell(input_file_stream);
    rewind(input_file_stream);

    char* buffer;
    buffer = (char*) malloc(file_size);
    if (buffer == NULL) 
        return 0;
    
    fread(buffer, 1, file_size, input_file_stream);

    char* result1 = mask_block_length(key, buffer, file_size);
    char* result2 = mask_block_length(key, result1, file_size);

    fwrite(result1, 1, file_size, output_file_stream);
    fwrite(result2, 1, file_size, output_file_stream2);

    printf("String: %s\nString: %s\nString: %s\n", buffer, result1, result2);
    
    free(result1);
    free(result2);
    free(buffer);

    fclose(input_file_stream);
    fclose(output_file_stream);

    *//*
    
    char* result = mask_block_length(key, text, strlen(text));
    puts(result);
    char* result2 = mask_block_length(key, result, strlen(text));
    puts(result2);
    printf("text:\t%d\nresult\t%d\nresult2\t%d\n",
        strlen(text), strlen(result), strlen(result2));
    
    //test_byte_stream(text);
    //test_encryption();
    */
    
    /*return 0;
}*/

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

    char* buffer;
    buffer = (char*) malloc(file_size);
    if (buffer == NULL) {
        printf("Fail to allocate memory for encryption.\n");
        return;
    }
    
    fread(buffer, 1, file_size, input_file_stream);

    char* result1 = mask_block_length(key, buffer, file_size);

    fwrite(result1, 1, file_size, output_file_stream);
    
    free(result1);
    free(buffer);

    fclose(input_file_stream);
    fclose(output_file_stream);
}

void test_byte_stream(char* text) {
    byte_node_t head;
    byte_node_t* current = &head;
    create_circular_byte_stream(current, text);
    int i;
    for (i = 0; i < strlen(text) + 5; i++) {
        printf("%c", current->byte);
        current = current->next;
    }
    printf("\n");
}

void test_encryption(void) {
    char a = 7;
    char b = 'm';
    char c;
    char d;

    mask_byte(a, b, &c);
    mask_byte(a, c, &d);

    /*SHOW(char, a);
    SHOW(char, b);
    SHOW(char, c);
    SHOW(char, d);*/

    puts("");
    printf("Bytes:\n");
    printf("   Key:      %03d '%c'\n", a, a);
    printf("   Data:     %03d '%c'\n", b, b);
    printf("   Masked:   %03d '%c'\n", c, c);
    printf("   Unmasked: %03d '%c'\n", d, d);
    puts("");

    if (b == d) {
        puts("The mask worked correctly.\n");
    }

    /*int one = 174849;
    int two = 184894;
    int three = one ^ two;

    SHOW(int, one);
    SHOW(int, two);
    SHOW(int, three);*/
}

char* mask_block(char* key, char* data) {
    return mask_block_length(key, data, strlen(data));
}

char* mask_block_length(char* key, char* data, int length) {
    byte_node_t* current = (byte_node_t*) malloc(sizeof(byte_node_t));
    create_circular_byte_stream_length(current, key, length);
    char* result = (char*) malloc(sizeof(char) * length);
    
    int i;
    for (i = 0; i < length; i++) {
        if (mask_byte(current->byte, data[i], result + i) == '\0') {
            /*printf("\nRIP\n");*/
        }
    }
    return result;
}

char mask_byte(char key, char data, char* result) {
    return *result = (key|data) ^ (key&data);
};

void create_circular_byte_stream(byte_node_t* head, char* data) {
    create_circular_byte_stream_length(head, data, strlen(data));
}

void create_circular_byte_stream_length(byte_node_t* head, char* data, int size) {
    if(size > 0) {
        byte_node_t* current = head;
        int i;
        byte_list(head, data[0]);
        for(i = 1; i < size; i++) {
            /*current->byte = data[i];
            current->next = (byte_node_t*) malloc(sizeof(byte_node_t));
            current = current->next;*/
            current = byte_node_add(current, data[i]);
        }
        /*current->byte = data[i];
        current->next = head;*/
    } else {
        printf("Error a circular byte stream could not be create because there was %d bytes of data\n", size);
    }
}

void byte_list(byte_node_t* head, char byte) {
    head->byte = byte;
    head->next = head;
}

byte_node_t* byte_node_add(byte_node_t* position, char byte) {
    byte_node_t* new_node = (byte_node_t*) malloc(sizeof(byte_node_t));
    new_node->byte = byte;
    new_node->next = position->next;
    position->next = new_node;
    return new_node;
}

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
