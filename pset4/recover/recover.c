#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    // check arguments validity : exactly one argument else return 1
    if (argc != 2)
    {
        printf("Usage: recover [file_name]\n");
        return 1;
    }

    // try to open file if fail return 1
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    // start reading : FAT32 -> data are by 512 Byte
    uint8_t buffer[512];
    int nbJpg = 0;
    FILE *outputFile = NULL;
    char outputFileName[8];
    uint16_t numberOfByteRead;
    while ((numberOfByteRead = fread(buffer, sizeof(uint8_t), 512, inputFile)))
    {
        // if the 3 first bytes are 0xff 0xd8 0xff and last BYTE & 0xf0 == 0xe0 then we assume it is a jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // close previous open file if any avoiding error
            if (outputFile != NULL)
            {
                fclose(outputFile);
            }
            // open a new file to write
            sprintf(outputFileName, "%03i.jpg", nbJpg++);
            outputFile = fopen(outputFileName, "w");
        }
        if (outputFile != NULL)
        {
            fwrite(buffer, sizeof(uint8_t), numberOfByteRead, outputFile);
        }
    }

    // close outputFile if any
    if (outputFile != NULL)
    {
        fclose(outputFile);
    }
    // close inputFile when done and return 0
    fclose(inputFile);
    return 0;
}
