#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Opening files with error checking
    FILE *input = fopen("input.wav", "rb");
    if (input == NULL)
    {
        fprintf(stderr, "Could not open input file\n");
        return 1;
    }
    FILE *output = fopen("output.wav", "wb");
    if (output == NULL)
    {
        fprintf(stderr, "Could not open output file\n");
        fclose(input);
        return 1;
    }
    
    float change = 5.0;
    uint8_t headerbuffer[HEADER_SIZE];
    
    // Read and write the header
    if (fread(headerbuffer, sizeof(uint8_t), HEADER_SIZE, input) != HEADER_SIZE)
    {
        fprintf(stderr, "Error reading header\n");
        fclose(input);
        fclose(output);
        return 1;
    }
    if (fwrite(headerbuffer, sizeof(uint8_t), HEADER_SIZE, output) != HEADER_SIZE)
    {
        fprintf(stderr, "Error writing header\n");
        fclose(input);
        fclose(output);
        return 1;
    }
    
    int16_t buffer;
    
    // Audio data processing
    while (fread(&buffer, sizeof(int16_t), 1, input) == 1)
    {
        buffer = (int16_t)(buffer * change);
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }
    
    fclose(input);
    fclose(output);
    return 0;
}
