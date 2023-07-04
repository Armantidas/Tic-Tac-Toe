#include <stdio.h>
#include <stdlib.h>
#include "dataFile.h"

#define FILENAME "savefile.bin"
#define error "Error opening file"

void saveState(char** state, char* filename)
{
    FILE * fp;
    fp = fopen(filename, "wb");
    if(!fp)
    {
        printf(error);
    }
    fprintf(fp, "%c%c%c%c%c%c%c%c%c", &state[0][0], &state[0][1], &state[0][2], &state[1][0], &state[1][1], &state[1][2], &state[2][0], &state[2][1], &state[2][2]);
}

int readState(char** state, char *filename)
{
    FILE * fp;
    fp = fopen(filename, "rb");
    if (!fp)
    {
        return 0;
    }
    fscanf(fp, "%c%c%c%c%c%c%c%c%c", &state[0][0], &state[0][1], &state[0][2], &state[1][0], &state[1][1], &state[1][2], &state[2][0], &state[2][1], &state[2][2]);
    return 1;
    fclose(fp);
}

