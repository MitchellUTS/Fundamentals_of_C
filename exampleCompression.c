// File: huffman.c
// Author: iBug

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef unsigned char byte;

typedef struct _HuffNode {
    unsigned data;
    struct _HuffNode *left, *right, *parent;
} HuffNode;

void count_frequency(FILE* fp, unsigned* freq) {
    size_t orig_pos = ftell(fp);
    int ch;
    while (1) {
        ch = fgetc(fp);
        if (ch < 0)
            break;
        freq[ch]++;
    }
    fseek(fp, orig_pos, SEEK_SET);
}

void construct_huffman(unsigned* freq_in, HuffNode* tree) {
    int count = 256;
    unsigned freq[256];
    HuffNode *node[256];

    // Initialize data
    for (int i = 0; i < 256; i++) {
        freq[i] = freq_in[i];
        tree[i].data = i;
        tree[i].left = tree[i].right = NULL;
        node[i] = &tree[i];
    }

    // Sort by frequency, decreasing order
    /* WARNING: Although this Quick Sort is an unstable sort,
     * it should at least give the same result for the same input frequency table,
     * therefore I'm leaving this code here
     */
    {
        unsigned lower[256], upper[256], top = 1;
        lower[0] = 0, upper[0] = 256;
        while (top > 0) {
            top--;
            int left = lower[top], right = upper[top];
            int i = left, j = right - 1, flag = 0;
            if (i >= j) // Nothing to sort
                continue;
            while (i < j) {
                if (freq[i] < freq[j]) {
                    unsigned t = freq[i]; freq[i] = freq[j]; freq[j] = t;
                    HuffNode *p = node[i]; node[i] = node[j]; node[j] = p;
                    flag = !flag;
                }
                flag ? i++ : j--;
            }
            lower[top] = left, upper[top] = i;
            lower[top + 1] = i + 1, upper[top + 1] = right;
            top += 2;
        }
    }

    // Construct tree
    while (count > 1) {
        int pos = 512 - count;
        HuffNode *parent = &tree[pos];
        // Select lowest 2 by freq
        int i = count - 2, j = count - 1;
        // Create tree, lower freq left
        parent->left = node[j]; parent->right = node[i];
        node[j]->parent = node[i]->parent = parent;
        node[i] = parent;
        freq[i] += freq[j];
        // Insert
        for (; i > 0 && freq[i] > freq[i - 1]; i--) {
            unsigned t = freq[i]; freq[i] = freq[i - 1]; freq[i - 1] = t;
            HuffNode *p = node[i]; node[i] = node[i - 1]; node[i - 1] = p;
        }
        count--;
    }
    // Now HEAD = node[0] = tree[511]
    node[0]->parent = NULL;
}

void encode_stream(FILE* fin, FILE* fout, HuffNode* tree, unsigned* padding) {
    int n;
    byte ch;
    byte buf = 0, nbuf = 0;
    HuffNode *p;
    byte code[256];
    while (1) {
        n = fgetc(fin);
        if (n < 0)
            break;
        ch = n;

        // Encode
        p = &tree[ch];
        n = 0;
        while (p->parent) {
            if (p == p->parent->left) {
                // Left is 0
                code[n] = 0;
            } else if (p == p->parent->right) {
                code[n] = 1;
            }
            p = p->parent;
            n++;
        }

        // Write
        for (int i = n - 1; i >= 0; i--) {
            buf |= code[i] << nbuf;
            nbuf++;
            if (nbuf == 8) {
                fputc(buf, fout);
                nbuf = buf = 0;
            }
        }
    }
    fputc(buf, fout);
    *padding = 8 - nbuf;
}

void decode_stream(FILE* fin, FILE* fout, HuffNode* tree, unsigned padding) {
    size_t startpos = ftell(fin); // should be 1028
    fseek(fin, 0L, SEEK_END);
    size_t endpos = ftell(fin); // last byte handling
    fseek(fin, startpos, SEEK_SET);
    int count = endpos - startpos;

    byte buf = 0, nbuf = 0, bit;
    HuffNode *p;
    while (count > 0 || nbuf > 0) {
        // Start from tree top
        p = tree + 510;
        while (p->left || p->right) {
            // Prepare next bit if needed
            if (nbuf == 0) {
                if (count <= 0)
                    return;

                buf = fgetc(fin);
                if (count == 1) {
                    // Last bit
                    nbuf = 8 - padding;
                    if (nbuf == 0) {
                        return;
                    }
                } else {
                    nbuf = 8;
                }
                count--;
            }
            // p has child
            bit = buf & 1;
            buf >>= 1;
            nbuf--;
            if (bit == 0)
                p = p->left;
            else
                p = p->right;
        }
        fputc(p->data, fout);
    }
}

void compress_file(const char* filename, const char* newname) {
    FILE *fin = fopen(filename, "rb"),
         *fout = fopen(newname, "wb");

    unsigned freq[256], padding;
    HuffNode tree[512];
    size_t padding_pos;
    count_frequency(fin, freq);
    construct_huffman(freq, tree);
    rewind(fin);
    for (int i = 0; i < 256; i++)
        fwrite(freq + i, 4, 1, fout);
    // Write a placeholder for the padding
    padding_pos = ftell(fout);
    fwrite(&padding, 4, 1, fout);
    encode_stream(fin, fout, tree, &padding);
    // Write the padding to the placeholder
    fseek(fout, padding_pos, SEEK_SET);
    fwrite(&padding, 4, 1, fout);
    fclose(fin);
    fclose(fout);
}

void uncompress_file(const char* filename, const char* newname) {
    FILE *fin = fopen(filename, "rb"),
         *fout = fopen(newname, "wb");

    unsigned freq[256], padding;
    HuffNode tree[512];
    for (int i = 0; i < 256; i++) {
        fread(&padding, 4, 1, fin);
        freq[i] = padding;
    }
    fread(&padding, 4, 1, fin);
    construct_huffman(freq, tree);
    decode_stream(fin, fout, tree, padding);
    fclose(fin);
    fclose(fout);
}

void print_help(void) {
    puts("Usage: huffman (-c|-d) input output");
    puts("  -c    Compress file from input to output");
    puts("  -d    Uncompress file from input to output");
    puts("\nCreated by iBug");
}

int main(int argc, char** argv) {
    if (argc != 4) {
        print_help();
        return 1;
    }
    if (!strcmp(argv[1], "-c")) {
        compress_file(argv[2], argv[3]);
    } else if (!strcmp(argv[1], "-d")) {
        uncompress_file(argv[2], argv[3]);
    } else {
        print_help();
        return 1;
    }
    return 0;
}