#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "convert.h"

int size_file (char * path) {
    FILE * file = fopen(path, "r");
    int count = 0;

    if (file == NULL)   {
        printf("Error file cannot be open");
        exit(EXIT_FAILURE);
    }
    else    {
        for (char c = fgetc(file); c != EOF; c = fgetc(file))
            count++;

        return count;
    }
    fclose(file);
}

char * convert (char * path)    {
    FILE * file = fopen(path, "r");

    if (file == NULL)   {
        printf("Error file cannot be open");
        exit(EXIT_FAILURE);
    }
    else    {
        int nb_size = size_file(path);
        char * tab = malloc(nb_size * sizeof(char *));

        if (tab == NULL)    {
            printf("Error convert allocation failed");
            exit(EXIT_FAILURE);
        }
        else    {
            for (int i = 0; i <= nb_size; i++)
                tab[i] = fgetc(file);
            return tab;
        }
    }

    fclose(file);
}