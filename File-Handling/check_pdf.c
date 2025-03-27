#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb"); // Open the file in binary mode
    if (!file)
    {
        perror("Error opening file");
        return 1;
    }

    unsigned char header[4]; // buffer to hold the first four bytes of the file

    if (fread(header, 1, 4, file) < 4)
    {
        printf("File too small to be a valid PDF\n");
        fclose(file);
        return 1;
    }

    if (header[0] != 0x25 || header[1] != 0x50 || header[2] != 0x44 || header[3] != 0x46) // %PDF -> 0x25 0x50 0x44 0x46
    {
        printf("Not a valid PDF file\n");
        fclose(file);
        return 1;
    }

    printf("Valid PDF file\n");

    fclose(file);
    return 0;
}

/*
    THis program checks if a file is a valid PDF by checking the first four bytes of the file.
    A valid PDF file should start with the bytes %PDF (0x25 0x50 0x44 0x46).

    Usage:
    Compile the code using: gcc check_pdf.c -o check_pdf
    Run the program with a file name as an argument:
        ./check_pdf example.pdf

    - If the file is a valid PDF, it will print "Valid PDF file".
    - If the file is not a valid PDF, it will print "Not a valid PDF file".
    - If the file is too small to be a valid PDF, it will print "File too small to be a valid PDF".
    - If the file cannot be opened, it will print an error message.
    - If no file name is provided, it will print usage instructions.
*/