#include <stdio.h>

#include "convert.h"

int main (int argc, char ** argv)   {
    char * path = argv[1];
    char * tab = convert(path);

    printf("%s", tab);

    return 0;
}