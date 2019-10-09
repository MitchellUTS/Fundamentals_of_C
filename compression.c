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
#include "core.h"
/*#include "compression.h"*/

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

void write_headers(FILE* out, ubig_t* frequencies) {
    

    fseek(out, 1, SEEK_SET);

    fwrite(frequencies, sizeof(ubig_t), 256, out);

}

void decompress_data(FILE* in, FILE* out) {
    short extra_bits = fgetc(in);
    ubig_t frequencies[256];
    init_frequencies(frequencies);
    fread(frequencies, sizeof(ubig_t), 256, in);

    huffman_tree_node_t* root = build_huffman_tree(frequencies);

    fseek(in, 0, SEEK_END);
    ubig_t length = ftell(in);
    fseek(in, 1 + sizeof(ubig_t) * 256, SEEK_SET);
    huffman_tree_node_t* current = root;
    byte buffer = fgetc(in);
    short bit_position = 0;
    
    while (ftell(in) < length || extra_bits != 8 - bit_position) {
        current = root;
        while (current->left != NULL || current->right != NULL) {
            /*SHOW(byte, buffer);*/
            if (buffer & 128) {
                current = current->right;
            } else {
                current = current->left;
            }
            buffer <<= 1;
            bit_position++;
            if (bit_position == 8) {
                buffer = fgetc(in);
                bit_position = 0;
            }
        }
        if ((ftell(in) == length && extra_bits == 8 - bit_position)) {
            break;
        }
        fputc(current->code, out);
    }
}

void compress_data(/*huffman_tree_node_t* root,*/ FILE* out, char* code_array, byte* data, ubig_t length) {
    short bit_position = 8;
    byte buffer = 0;
    int i, j;
    fseek(out, 1 + sizeof(ubig_t) * 256, SEEK_SET);
    /*printf("Original Data:\t\t%s\n", data);

    printf("Compressed Data:\t");*/
    for (i = 0; i < length; i++) {
        for (j = 0; j < 11 && code_array[11*data[i]+j] != '\0'; j++) {
            bit_position--;
            if (code_array[11*data[i]+j] == '1') {
                buffer |= (1 << bit_position);
            }

            if (bit_position == 0) {
                fputc(buffer, out);
                /*printf("%c", buffer);*/
                /*SHOW(byte, buffer);*/
                buffer = 0;
                bit_position = 8;
            }
        }
    }
    fputc(buffer, out);
    /*printf("%c", buffer);*/
    byte extra_bits = (byte) bit_position;
    fseek(out, 0, SEEK_SET);
    if (extra_bits == 8) {
        extra_bits = 0;
    }
    fputc(extra_bits, out);
    /*printf("\n");*/

}

/*int main() {

    
    *//*char* string = "aaaaabbbbbbbbbccccccccccccdddddddddddddeeeeeeeeeeeeeeeefffffffffffffffffffffffffffffffffffffffffffff";*/
    /*string = "Huffman coding is a data compression algorithm.";*//*

    ubig_t frequencies[256];
    init_frequencies(frequencies);

    FILE* in = fopen("test.mp4", "rb");
    FILE* out = fopen("test2.cmp", "wb");
    FILE* ind = fopen("test2.cmp", "rb");
    FILE* outd = fopen("test2.mp4", "wb");

    fseek(in, 0, SEEK_END);
    ubig_t length = ftell(in);
    fseek(in, 0, SEEK_SET);

    byte* data = malloc(length);
    if (data == NULL) {
        printf("Interal buffer could not be allocated.\n");
        return 0;
    }
    fread(data, 1, length, in);
    fclose(in);

    count_frequencies(data, length, frequencies);

    *//*int i;
    for (i = 0; i < 256; i++) {
        if (frequencies[i] != 0) {
            printf("%c: %ld\n", i, frequencies[i]);
        }
    }*//*

    huffman_tree_node_t* root = build_huffman_tree(frequencies);

    char* code_array = (char*) calloc(11 * 256, sizeof(char));
    traverse_tree(root, code_array);

    write_headers(out, frequencies);
    compress_data(out, code_array, data, length);
    fclose(out);
    decompress_data(ind, outd);

    *//*print_bits("block_t", "block", (byte*) block, block_size);*/
    /*print_bits("block_t", "block", (byte*) block, block_display_size);*//*

    fclose(ind);
    fclose(outd);

    return 0;
}*/

int testBitField(my_uint_t block_size) {
    byte* block = (byte*) calloc(block_size, 1);

    if (block == NULL) {
        printf("Block allocation failed.\n");
        return 0;
    } else {
        /*printf("Block allocation successful, %d bytes allocated.\n", block_size);*/
    }

    /*time_t start_time = time(NULL);*/

    int byte, bit;
    for (byte = 0; byte < block_size; byte++) {
        for (bit = 0; bit < 8; bit++) {
            SetBit(block, byte, bit);
        }
    }

    /*time_t end_time   = time(NULL);*/
    

    free(block);

    /*if (start_time != -1 && end_time != -1) {
        printf("That operation took %ld seconds.\n", end_time - start_time);
        return (end_time - start_time);
    }*/
    return 0;
}

/*void testByteShift() {
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
}*/

/*huffman_code_t huffman_code_create(byte code) {
    huffman_code_t new_huffman_code;
    new_huffman_code.length = 0;
    new_huffman_code.code = code;*//*code_to_binary(code, new_huffman_code.length);*//*
    return new_huffman_code;
}*/

/*my_uint_t code_to_binary(char* string, my_uint_t size) {
    int i;
    int power;
    my_uint_t sum = 0;    
    *//*printf("String:\t%s\n", string);*//*
    for (i = size-1, power = 1; i >= 0; i--, power*=2) {
        *//*printf("Size:\t%d\nIndex:\t%d\nLetter:\t%c\nPower:\t%d\n", 
            size, i, string[i], power);*//*
        if (string[i] == '1')
            sum += power;
    }
    return sum;
}*/

huffman_tree_node_t huffman_tree_node_create(ubig_t frequency, int code, huffman_tree_node_t* left, huffman_tree_node_t* right, huffman_tree_node_t* parent) {
    huffman_tree_node_t new_huffman_tree_node;
    new_huffman_tree_node.left = left;
    new_huffman_tree_node.right = right;
    new_huffman_tree_node.parent = parent;
    new_huffman_tree_node.code = code;
    new_huffman_tree_node.frequency = frequency;
    return new_huffman_tree_node;
}

huffman_tree_node_t* build_huffman_tree(ubig_t* frequencies) {
    huffman_tree_node_t* root = NULL;
    byte sort_order[256];
 
    sort_frequencies(sort_order, frequencies);
 
    huffman_node_t* head;
    int i;
    for (i = 0; i < 256 && frequencies[sort_order[i]] == 0; i++) {}

    if (i > 255) {
        printf("No data detected to build a Huffman Tree with.\n");
        return root;
    }

    huffman_tree_node_t* new_node = malloc(sizeof(huffman_tree_node_t));
    if(new_node == NULL) {
        printf("Tree Node Allocation failed.\n");
        return root;
    }

    *new_node = huffman_tree_node_create(frequencies[sort_order[i]], sort_order[i], NULL, NULL, NULL);
    huffman_list(&head, new_node);

    huffman_node_t* current = head;
    for (i++; i < 256; i++) {
        new_node = malloc(sizeof(huffman_tree_node_t));
        if(new_node == NULL) {
            printf("Tree Node Allocation failed.\n");
            return root;
        }
        *new_node = huffman_tree_node_create(frequencies[sort_order[i]], sort_order[i], NULL, NULL, NULL);
        current = huffman_node_add(current, new_node);
    }

    /*print_node_list(head);*/

    while (head->next != NULL) {
        head = squash_tree(head);
        /*print_node_list(head);*/
    }
    
    if (head->node != NULL) {
        root = head->node;
    }

    while ((head = huffman_node_delete_next(head)) != NULL) {}
 
    return root;
}


void init_frequencies(ubig_t* frequencies) {
    memset(frequencies, 0, 256 * sizeof(ubig_t));
}

void count_frequencies(byte* data, ubig_t len, ubig_t* frequencies) {
    int i;
    /*printf("Character\t\tFrequency\n");*/
    for (i = 0; i < len; i++) {
        /*printf("%c\t%I64u\n", string[i], frequencies[(byte) string[i]]);*/
        frequencies[data[i]]++;
    } 
}

void sort_frequencies(byte* sort_order, ubig_t* frequencies) {
    byte sorted_end = 1;
    int i;
    byte temp;
    int has_swapped;

    for (i = 0; i < 256; i++) {
        sort_order[i] = i;
    }

    while (true) {
        has_swapped = false;
        for (i = sorted_end; i < 256; i++) {
            if (frequencies[sort_order[i-1]] > frequencies[sort_order[i]]) {
                /*printf("Swapped i:%d f:%ld with i:%d f:%ld\n", sort_order[i], frequencies[sort_order[i]], sort_order[i-1], frequencies[sort_order[i-1]]);*/
                temp = sort_order[i];
                sort_order[i] = sort_order[i-1];
                sort_order[i-1] = temp;
                has_swapped = true;
            }
        }
        if (!has_swapped) {
            break;
        }
    }
}

void huffman_list(huffman_node_t** head, huffman_tree_node_t* node) {
    *head = (huffman_node_t*) malloc(sizeof(huffman_node_t));
    (*head)->node = node;
    (*head)->next = NULL;
}

huffman_node_t* huffman_node_add(huffman_node_t* position, huffman_tree_node_t* node) {
    huffman_node_t* new_node = (huffman_node_t*) malloc(sizeof(huffman_node_t));
    new_node->node = node;
    new_node->next = position->next;
    position->next = new_node;
    return new_node;
}

huffman_node_t* huffman_node_delete_next(huffman_node_t* position) {
    if (position->next == NULL){
        free(position);
        return NULL;
    }
    huffman_node_t* to_delete = position->next;
    position->next = to_delete->next;
    free(to_delete);
    return position->next;
}

huffman_node_t* squash_tree(huffman_node_t* head) {
    huffman_tree_node_t* new_node;
    new_node = malloc(sizeof(huffman_tree_node_t));
    if(new_node == NULL) {
        printf("Tree Node Allocation failed.\n");
        return NULL;
    }

    head->node->parent = head->next->node->parent = new_node;
    *new_node = huffman_tree_node_create(head->node->frequency + head->next->node->frequency, -1, head->node, head->next->node, NULL);

    huffman_node_t* temp = head->next->next;
    free(head->next);
    free(head);
    head = temp;
    
    head = add_prority_node(head, new_node);
    return head;
}

huffman_node_t* add_prority_node(huffman_node_t* head, huffman_tree_node_t* node) {
    if (head == NULL) {
        huffman_node_t* new_node = (huffman_node_t*) malloc(sizeof(huffman_node_t));
        if(new_node == NULL) {
            printf("List Node Allocation failed.\n");
            return NULL;
        }
        new_node->node = node;
        new_node->next = head;
        return new_node;
    }

    if (node->frequency <= head->node->frequency) {
        huffman_node_t* new_node = (huffman_node_t*) malloc(sizeof(huffman_node_t));
        if(new_node == NULL) {
            printf("List Node Allocation failed.\n");
            return NULL;
        }
        new_node->node = node;
        new_node->next = head;
        return new_node;
    }
    
    huffman_node_t* current = head;
    huffman_node_t* last    = NULL;

    while (current != NULL) {
        if (current->next == NULL) {
            huffman_node_add(current, node);
            return head;
        }

        last    = current;
        current = current->next;

        if (current->node->frequency >= node->frequency) {
            huffman_node_add(last, node);
            /*printf("Code\tFrequency\tNext\n%c:\t%I64u\t\t%p\n\n", current->node->code, current->node->frequency, current->next);*/
            return head;
        }
    }

    huffman_node_add(current, node);
    return head;

}

void print_node_list(huffman_node_t* start) {
    int i = 0;
    printf("Index\tCode\tFrequency\tNext\n");
    while (start != NULL) {
        printf("%d\t%c:\t%I64u\t\t%p\n", i, start->node->code, start->node->frequency, start->next);
        start = start->next; i++;
    }
    printf("\n");
}

void traverse_tree_recursive(huffman_tree_node_t* root, char* code, unsigned short length, char* code_array) {
    if (root == NULL) {
        return;
    }

    if (root->code > -1) {
        /*printf("%c:\t%s\n", (byte) root->code, code);*/
        memcpy(code_array + (11 * root->code), code, 11);
        /*printf("%c: %s\n", root->code, code_array + (11 * root->code));*/
    }

    code[length+1] = '\0';
    code[length] = '0';
    traverse_tree_recursive(root->left, code, length+1, code_array);

    code[length+1] = '\0';
    code[length] = '1';
    traverse_tree_recursive(root->right, code, length+1, code_array);
}

void traverse_tree(huffman_tree_node_t* root, char* code_array) {
    /*printf("\nPrinting Huffman Tree\n");*/
    if (root == NULL) {
        return;
    }

    if (root->code > -1) {
        printf("%c:\t%s\n", (byte) root->code, "The root node has no code.");
    }

    char code[11];
    memset(code, '\0', 11);
    code[0] = '0';
    code[1] = '\0';
    traverse_tree_recursive(root->left, code, 1, code_array);
    code[0] = '1';
    code[1] = '\0';
    traverse_tree_recursive(root->right, code, 1, code_array);
    /*printf("Huffman Tree Printed\n\n");*/
}