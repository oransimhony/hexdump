#include <stdio.h>
#include <stdlib.h>

#define RESET "\033[0m" 
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"

void printHex(unsigned char buffer[], size_t length) {
    size_t i;
    for(i = 0; i < 16; i++) {
        if(i < length) {
            // Check if buffer[i] is printable
            if(buffer[i] > 32 && buffer[i] < 128)
                printf(YELLOW);
            else
                printf(BLUE);
            printf("%02X", buffer[i]);
            printf(RESET);
        }
        else
            printf("  ");

        putchar(' ');
    }
    putchar(' ');
        
}

void printText(unsigned char buffer[], size_t length) {
    size_t i;
    printf("|");
    for(i = 0; i < length; i++) {
        // Check if buffer[i] is printable
        if(buffer[i] > 32 && buffer[i] < 128) {
            printf(YELLOW);
            printf("%c", buffer[i]);
        }
        // Else print a '.'
        else {
            printf(BLUE);
            printf(".");
        }
        printf(RESET);
    }
    printf("|");
}

int main(int argc, char* argv[]) {
    // Initializing variables
    FILE *fp = NULL;
    size_t length;
    unsigned int offset = 0x0;
    unsigned char buffer[16];

    // Checking if the user specified a filename
    if(argc < 2) {
        fprintf(stderr, "You must specify a filename.\n");
        return -1;
    }

    // Trying to open the file stream
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return -2;
    }

    // Looping over the file stream 16 bytes at a time
    while ((length = fread(buffer, 1, 16, fp)) > 0) {
        // Printing the offset
        printf(GREEN "0x%08X  " RESET, offset);
        // Printing the hex codes for the 16 bytes
        printHex(buffer, length);
        // Printing the ascii values for the 16 bytes
        printText(buffer, length);
        putchar('\n');
        offset += 0x10;
    }

    // Closing the file stream
    fclose(fp);
    return 0;
}
