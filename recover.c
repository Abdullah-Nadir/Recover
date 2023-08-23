#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

#define BLOCK_SIZE 512
#define FILENAME_MEM 8

int main(int argc, char *argv[])
{
    // Checking for correct usage
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    // Opening the forensic Image file
    FILE *forensicImg = fopen(argv[1], "r");
    if (forensicImg == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 2;
    }

    BYTE buffer[BLOCK_SIZE];
    FILE *jpeg = NULL;
    int imgCounter = 0;

    while (fread(buffer, 1, BLOCK_SIZE, forensicImg) == BLOCK_SIZE)
    {
        // Checking first three bytes of buffer
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (jpeg != NULL)
            {
                fclose(jpeg);
            }

            char filename[FILENAME_MEM];
            sprintf(filename, "%03i.jpg", imgCounter);

            jpeg = fopen(filename, "w");
            if (jpeg == NULL)
            {
                return 3;
            }
            fwrite(buffer, 1, BLOCK_SIZE, jpeg);
            imgCounter++;
        }
        else
        {
            if (jpeg != NULL)
            {
                fwrite(buffer, 1, BLOCK_SIZE, jpeg);
            }
        }
    }

    if (jpeg != NULL)
    {
        fclose(jpeg);
    }

    fclose(forensicImg);
    return 0;
}

