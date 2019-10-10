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

/*******************************************************************************
 * This function decompresses a data stream.
 * inputs:
 * - The input stream to decompress and the output stream to write the orignal 
 *   contents to.
 * outputs:
 * - A stream of decompressed data.
*******************************************************************************/
void decompress_data(FILE* in, FILE* out) {
    short extra_bits = fgetc(in);
    ubig_t frequencies[256];
    memset(frequencies, 0, 256 * sizeof(ubig_t));

    /* Load file and process the headers */
    fread(frequencies, sizeof(ubig_t), 256, in);

    huffman_tree_node_t* root = build_huffman_tree(frequencies);

    fseek(in, 0, SEEK_END);
    ubig_t length = ftell(in);
    fseek(in, 1 + sizeof(ubig_t) * 256, SEEK_SET);
    huffman_tree_node_t* current = root;
    byte buffer = fgetc(in);
    short bit_position = 0;
    
    /* Process until the end of the file is reached. */
    while (ftell(in) < length || extra_bits != 8 - bit_position) {
        current = root;
        
        /* Navigate the tree until a character is matched to the binary string */
        while (current->left != NULL || current->right != NULL) {
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
        fputc(current->code, out);
    }
}


/*******************************************************************************
 * This function decompresses a data stream.
 * inputs:
 * - The input stream to compress and the output stream to write the compressed 
 *   contents to.
 * outputs:
 * - A stream of compressed data.
*******************************************************************************/
void compress_data(FILE* out, char* code_array, byte* data, ubig_t length) {
    short bit_position = 8;
    byte buffer = 0;
    int i, j;
    fseek(out, 1 + sizeof(ubig_t) * 256, SEEK_SET);

    /* Encode every byte from the input */
    for (i = 0; i < length; i++) {

        /* Write all the binary data for the current byte */
        for (j = 0; j < 11 && code_array[11*data[i]+j] != '\0'; j++) {
            bit_position--;
            if (code_array[11*data[i]+j] == '1') {
                buffer |= (1 << bit_position);
            }

            /* Write out a byte once its full. */
            if (bit_position == 0) {
                fputc(buffer, out);
                /*printf("%c", buffer);*/
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


/*******************************************************************************
 * This function compresses a file.
 * inputs:
 * - The input file to compress and the output file to hold the compressed data
 * outputs:
 * - A compressed file.
*******************************************************************************/
void compress_file(char* input_name, char* output_name) {
    ubig_t frequencies[256];
    memset(frequencies, 0, 256 * sizeof(ubig_t));

    FILE* in = fopen(input_name, "rb");
    FILE* out = fopen(output_name, "wb");

    if (in == NULL || out == NULL) {
        printf("Compression Files could not be opened.\nSource: %s\nDestination: %s\n", input_name, output_name);
        return;
    }

    /* Load file contents */
    fseek(in, 0, SEEK_END);
    ubig_t length = ftell(in);
    fseek(in, 0, SEEK_SET);

    byte* data = malloc(length);
    if (data == NULL) {
        printf("Interal buffer could not be allocated.\n");
        return;
    }
    fread(data, 1, length, in);
    fclose(in);

    /* Create huffman codes */
    count_frequencies(data, length, frequencies);

    huffman_tree_node_t* root = build_huffman_tree(frequencies);

    char code_array[11 * 256];
    memset(code_array, '\0', 11 * 256);

    /* Assign Codes*/
    traverse_tree(root, code_array);

    /* Write to File */
    fseek(out, 1, SEEK_SET);
    fwrite(frequencies, sizeof(ubig_t), 256, out);

    compress_data(out, code_array, data, length);

    fclose(out);
}


/*******************************************************************************
 * This function decompresses a file.
 * inputs:
 * - The input file to decompress and the output file to write the orignal 
 *   contents to.
 * outputs:
 * - A file with the decompressed data.
*******************************************************************************/
void decompress_file(char* input_name, char* output_name) {
    FILE* in = fopen(input_name, "rb");
    FILE* out = fopen(output_name, "wb");

    if (in == NULL || out == NULL) {
        printf("Compression Files could not be opened.\nSource: %s\nDestination: %s\n", input_name, output_name);
        return;
    }

    decompress_data(in, out);

    fclose(in);
    fclose(out);
}

/*******************************************************************************
 * This function contructs a huffman tree node
 * inputs:
 * - The members for the new huffman tree node
 * outputs:
 * - A new huffman tree node.
*******************************************************************************/
huffman_tree_node_t huffman_tree_node_create(ubig_t frequency, int code, huffman_tree_node_t* left, huffman_tree_node_t* right, huffman_tree_node_t* parent) {
    huffman_tree_node_t new_huffman_tree_node;
    new_huffman_tree_node.left = left;
    new_huffman_tree_node.right = right;
    new_huffman_tree_node.parent = parent;
    new_huffman_tree_node.code = code;
    new_huffman_tree_node.frequency = frequency;
    return new_huffman_tree_node;
}

/*******************************************************************************
 * This function builds the huffman analysis tree
 * inputs:
 * - The frequenices of each byte
 * outputs:
 * - The root node of the huffman tree.
*******************************************************************************/
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

    /* Add the first node and put it add the start of the prority queue */
    *new_node = huffman_tree_node_create(frequencies[sort_order[i]], sort_order[i], NULL, NULL, NULL);
    huffman_list(&head, new_node);

    /* Add all the different byte frequenices to the prority queue. */
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

    /* Keep adding internal node until there is only a root node left */
    while (head->next != NULL) {
        head = squash_tree(head);
        /*print_node_list(head);*/
    }
    
    if (head->node != NULL) {
        root = head->node;
    }

    /* Delete the prority queue */
    while ((head = huffman_node_delete_next(head)) != NULL) {}
 
    return root;
}

/*******************************************************************************
 * This function parses the input data and records the frequenices of each byte
 * inputs:
 * - The data and data length as well as the location to store the frequencies 
 * outputs:
 * - The frequncies of each byte to the provided array
*******************************************************************************/
void count_frequencies(byte* data, ubig_t len, ubig_t* frequencies) {
    int i;
    for (i = 0; i < len; i++) {
        frequencies[data[i]]++;
    } 
}

/*******************************************************************************
 * This function sorts the frequenices using a bubble sort
 * inputs:
 * - The location to store the sorted order and the frequency table 
 * outputs:
 * - The sort order to an array
*******************************************************************************/
void sort_frequencies(byte* sort_order, ubig_t* frequencies) {
    byte sorted_end = 1;
    int i;
    byte temp;
    int has_swapped;

    /* Inital array to being in alphabetical order */
    for (i = 0; i < 256; i++) {
        sort_order[i] = i;
    }

    /* Bubble sort */
    while (true) {
        has_swapped = false;
        for (i = sorted_end; i < 256; i++) {
            if (frequencies[sort_order[i-1]] > frequencies[sort_order[i]]) {
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

/*******************************************************************************
 * This function creates a linked list of huffman tree nodes
 * inputs:
 * - The location the store the array and the first node.
 * outputs:
 * - None
*******************************************************************************/
void huffman_list(huffman_node_t** head, huffman_tree_node_t* node) {
    *head = (huffman_node_t*) malloc(sizeof(huffman_node_t));
    (*head)->node = node;
    (*head)->next = NULL;
}

/*******************************************************************************
 * This function add a new node after the specificed element
 * inputs:
 * - The position to insert at and the element for it huffman node for it 
 *   to contain 
 * outputs:
 * - The location of the new node
*******************************************************************************/
huffman_node_t* huffman_node_add(huffman_node_t* position, huffman_tree_node_t* node) {
    huffman_node_t* new_node = (huffman_node_t*) malloc(sizeof(huffman_node_t));
    new_node->node = node;
    new_node->next = position->next;
    position->next = new_node;
    return new_node;
}

/*******************************************************************************
 * This function deletes the next node after the given element
 * inputs:
 * - The position to delete from
 * outputs:
 * - The next element in the list
*******************************************************************************/
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

/*******************************************************************************
 * This function add one new node to the huffman tree to reduce the number of 
 *  root nodes.
 * inputs:
 * - The head of the prority queue
 * outputs:
 * - The new head of the prority queue.
*******************************************************************************/
huffman_node_t* squash_tree(huffman_node_t* head) {
    /* Create the new node */
    huffman_tree_node_t* new_node;
    new_node = malloc(sizeof(huffman_tree_node_t));
    if(new_node == NULL) {
        printf("Tree Node Allocation failed.\n");
        return NULL;
    }

    /* Populate the new node with data */
    head->node->parent = head->next->node->parent = new_node;
    *new_node = huffman_tree_node_create(head->node->frequency + head->next->node->frequency, -1, head->node, head->next->node, NULL);

    /* Remove the old elements from the tree */
    huffman_node_t* temp = head->next->next;
    free(head->next);
    free(head);
    head = temp;
    
    /* Put the new node on the queue */
    head = add_prority_node(head, new_node);
    return head;
}

/*******************************************************************************
 * This function adds a new item to the prority queue
 * inputs:
 * - The head of the prority queue and the node to add
 * outputs:
 * - The new head of the prority queue.
*******************************************************************************/
huffman_node_t* add_prority_node(huffman_node_t* head, huffman_tree_node_t* node) {

    /* Allocate memory for the new node */
    huffman_node_t* new_node = (huffman_node_t*) malloc(sizeof(huffman_node_t));
    if(new_node == NULL) {
        printf("List Node Allocation failed.\n");
        return NULL;
    }
    new_node->node = node;

    /* Handle Edge cases */
    if (head == NULL) {        
        new_node->node = node;
        new_node->next = head;
        return new_node;
    } else if (node->frequency <= head->node->frequency) {
        new_node->node = node;
        new_node->next = head;
        return new_node;
    }
    
    huffman_node_t* current = head;
    huffman_node_t* last    = NULL;

    /* Loop until the end of the array */
    while (current != NULL) {
        if (current->next == NULL) {
            huffman_node_add(current, node);
            return head;
        }

        last    = current;
        current = current->next;

        /* Place the value if this is the correct position */
        if (current->node->frequency >= node->frequency) {
            new_node->next = last->next;
            last->next = new_node;
            return head;
        }
    }

    /* Add it to the end of the list if it didn't fit anywhere else */
    new_node->next = current->next;
    current->next = new_node;
    return head;

}

/*******************************************************************************
 * This function recursiving builds the huffman codes from the tree
 * inputs:
 * - The root of the tree, the place to save the codes, the current 
 *     code and its length
 * outputs:
 * - It saves the current byte's code to memory if applicable 
*******************************************************************************/
void traverse_tree_recursive(huffman_tree_node_t* root, char* code, unsigned short length, char* code_array) {
    if (root == NULL) {
        return;
    }

    /* Save the code to memory */
    if (root->code > -1) {
        memcpy(code_array + (11 * root->code), code, 11);
    }

    /* Call for the left and right nodes */
    code[length+1] = '\0'; code[length] = '0';
    traverse_tree_recursive(root->left, code, length+1, code_array);

    code[length+1] = '\0'; code[length] = '1';
    traverse_tree_recursive(root->right, code, length+1, code_array);
}

/*******************************************************************************
 * This function recursiving builds the huffman codes from the tre
 * inputs:
 * - The root of the tree, the place to save the codes
 * outputs:
 * - None
*******************************************************************************/
void traverse_tree(huffman_tree_node_t* root, char* code_array) {
    if (root == NULL) {
        return;
    }

    if (root->code > -1) {
        printf("%c:\t%s\n", (byte) root->code, "The root node has no code.");
    }

    char code[11];
    memset(code, '\0', 11);
    code[0] = '0'; code[1] = '\0';
    traverse_tree_recursive(root->left, code, 1, code_array);
    code[0] = '1'; code[1] = '\0';
    traverse_tree_recursive(root->right, code, 1, code_array);
}