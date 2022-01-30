#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "codage.h"

/*
 * Ecrit dans un nouveau fichier texte "new.txt" le code d'une machine de turing avec l'alphabet {a, b, c, d}
 * Retourne 1 si l'écriture s'est bien passée, 0 sinon
*/

int new_codage(char * path) {
    FILE * file = fopen(path, "r");
    FILE * new = fopen("MT/new", "w");

    if (!file || !new)  {
        printf("Error, fopen failed in function new_codage\n");
        return 0;
    }

    char buff[1024] = "";
    char line[1024];
    char* tok;
    size_t count = 1;   //Compteur pour différencier les états pour l'écriture

    char * etat = malloc(sizeof(char));
    char * read = malloc(sizeof(char));
    char * suiv = malloc(sizeof(char));
    char * replace = malloc(sizeof(char));
    char * direction = malloc(sizeof(char));

    // Transition dans les cas généraux, pour passer d'une transition à l'autre
    strcat(buff, "A,0\nA7,0,>\nA7,0\nA0,0,<\nA7,1\nA1,1,<\nA,1\nA8,1,>\nA8,0\nA2,0,<\nA8,1\nA3,1,<\nA,_\nA4,_,-\n");
    strcat(buff, "B,0\nB7,0,>\nB7,0\nB0,0,<\nB7,1\nB1,1,<\nB,1\nB8,1,>\nB8,0\nB2,0,<\nB8,1\nB3,1,<\nB,_\nB4,_,-\n");
    strcat(buff, "C,0\nC7,0,>\nC7,0\nC0,0,<\nC7,1\nC1,1,<\nC,1\nC8,1,>\nC8,0\nC2,0,<\nC8,1\nC3,1,<\nC,_\nC4,_,-\n");
    strcat(buff, "D,0\nD7,0,>\nD7,0\nD0,0,<\nD7,1\nD1,1,<\nD,1\nD8,1,>\nD8,0\nD2,0,<\nD8,1\nD3,1,<\nD,_\nD4,_,-\n");

    // Dans la boucle, i est aussi utilisé pour savoir sur quelle ligne on se situe.
    // i%2==0 indique que la ligne est impair
    // i%2==1 indique que la ligne est pair
    for (size_t i=0; fgets(line, 1024, file); i++) {
        int rank_tok = 0;   // Variable qui stocke là ou on est sur la ligne (q0,1,> => q0=0, 1=1, >=2)

        if (!strcmp(line, "\n")) {
            printf("Le fichier contient des lignes vides.\n");
            return 1;
        }

        // Pour chaque cas, on enregistre le token dans les variables qui correspond
        for (tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",\n")) {

            if (i%2 == 0) {
                if (rank_tok == 0)
                    strcpy(etat, tok);
                else if (rank_tok == 1)
                    strcpy(read, tok);
                else
                    return 0;
            }

            if (i%2 == 1) {
                if (rank_tok == 0)
                    strcpy(suiv, tok);
                else if (rank_tok == 1)
                    strcpy(replace, tok);
                else if (rank_tok == 2)
                    strcpy(direction, tok);
                else
                    return 0;
            }
            rank_tok++;
        }

        // Ecriture après avoir récupéré tous les variables pour une transition
        if (i%2 == 1)   {
            if (!new_read(etat, read, replace, buff, &count))   {
                printf("Error, new_read in function new_codage\n");
                return 0;
            }

            if(!new_transition(etat, read, suiv, replace, direction, buff, &count))  {
                printf("Error, new_transition in function new_codage\n");
                return 0;
            }

            count = 1;
        }
    }

    // Suppression du dernier retour chariot
    int lengh = strlen(buff);
    buff[lengh-1] = '\0';

    fputs(buff, new);

    free(etat);
    free(read);
    free(suiv);
    free(replace);
    free(direction);

    fclose(file);
    fclose(new);

    return 1;
}

/*
 * Insère dans un buffer la conversion de la 1ere ligne d'une transition
 * Retourne 1 en cas de réussite, 0 sinon
*/

int new_read(char * etat, char * read, char * replace, char * buff, size_t * count)  {

    switch (*read)    {
    case 'a':
        strcat(buff, etat);
        strcat(buff, "0,0\n");
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "0,0,>\n");
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "0,0\n");
        *count = *count + 1;
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "0,0,-\n");
        break;

    case 'b':
        strcat(buff, etat);
        strcat(buff, "1,0\n");
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "1,0,>\n");
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "1,1\n");
        *count = *count + 1;
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "1,1,-\n");
        break;

    case 'c':
        strcat(buff, etat);
        strcat(buff, "2,1\n");
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "2,1,>\n");
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "2,0\n");
        *count = *count + 1;
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "2,0,-\n");
        break;

    case 'd':
        strcat(buff, etat);
        strcat(buff, "3,1\n");
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "3,1,>\n");
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "3,1\n");
        *count = *count + 1;
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "3,1,-\n");
        break;
    case '_':
        strcat(buff, etat);
        strcat(buff, "4,_\n");
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "4,_,>\n");
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "4,_\n");
        *count = *count + 1;
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "4,_,-\n");
        break;
    default:
        printf("Error, incorrect read in function new_read\n");
        return 0;
        break;
    }

    return 1;
}


/*
 * Insère dans un buffer la conversion de la 2e ligne d'une transition
 * Retourne 1 en cas de réussite, 0 sinon
*/
int new_transition(char * etat, char * read, char * suiv, char * replace, char * direction, char * buff, size_t * count)    {
    char * temp1;   //Variable afin de stocker la conversion de l'alphabet
    char * temp2;

    if (!strcmp(replace, "a"))  {
        temp1 = "0";
        temp2 = "0";
    }
    else if (!strcmp(replace, "b"))  {
        temp1 = "0";
        temp2 = "1";
    }
    else if (!strcmp(replace, "c"))  {
        temp1 = "1";
        temp2 = "0";
    }
    else if (!strcmp(replace, "d"))  {
        temp1 = "1";
        temp2 = "1";
    }
    else if (!strcmp(replace, "_"))  {
        temp1 = "_";
    }
    else    {
        printf("Error, invalid replace in function new_transition\n");
        return 0;
    }


    if (!strcmp(read, "a")) {
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "0,0\n");
        *count = *count + 1;
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "0,0,<\n");
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "0,0\n");
        *count = *count + 1;
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "0,0,-\n");
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "0,0\n");
        *count = *count + 1;
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "0,");
        strcat(buff, temp1);
        strcat(buff, ",>\n");
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "0,0\n");
        *count = *count + 1;
        strcat(buff, suiv);
        strcat(buff, ",");
        strcat(buff, temp2);
        strcat(buff, ",");
        strcat(buff, direction);
        strcat(buff, "\n");
    }
    else if (!strcmp(read, "b")) {
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "1,1\n");
        *count = *count + 1;
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "1,1,<\n");
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "1,0\n");
        *count = *count + 1;
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "1,0,-\n");
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "1,0\n");
        *count = *count + 1;
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "1,");
        strcat(buff, temp1);
        strcat(buff, ",>\n");
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "1,1\n");
        *count = *count + 1;
        strcat(buff, suiv);
        strcat(buff, ",");
        strcat(buff, temp2);
        strcat(buff, ",");
        strcat(buff, direction);
        strcat(buff, "\n");
    }
    else if (!strcmp(read, "c")) {
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "2,0\n");
        *count = *count + 1;
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "2,0,<\n");
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "2,1\n");
        *count = *count + 1;
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "2,1,-\n");
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "2,1\n");
        *count = *count + 1;
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "2,");
        strcat(buff, temp1);
        strcat(buff, ",>\n");
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "2,0\n");
        *count = *count + 1;
        strcat(buff, suiv);
        strcat(buff, ",");
        strcat(buff, temp2);
        strcat(buff, ",");
        strcat(buff, direction);
        strcat(buff, "\n");
    }
    else if (!strcmp(read, "d")) {
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "3,1\n");
        *count = *count + 1;
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "3,1,<\n");
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "3,1\n");
        *count = *count + 1;
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "3,1,-\n");
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "3,1\n");
        *count = *count + 1;
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "3,");
        strcat(buff, temp1);
        strcat(buff, ",>\n");
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "3,1\n");
        *count = *count + 1;
        strcat(buff, suiv);
        strcat(buff, ",");
        strcat(buff, temp2);
        strcat(buff, ",");
        strcat(buff, direction);
        strcat(buff, "\n");
    }
    else if (!strcmp(read, "_")) {
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "4,_\n");
        *count = *count + 1;
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "4,_,<\n");
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "4,_\n");
        *count = *count + 1;
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "4,_,-\n");
        strcat(buff, etat);
        sprintf(buff, "%s%ld", buff, *count);
        strcat(buff, "4,_\n");
        *count = *count + 1;
        strcat(buff, suiv);
        strcat(buff, ",");
        strcat(buff, temp1);
        strcat(buff, ",");
        strcat(buff, direction);
        strcat(buff, "\n");
    }
    else    {
        printf("Error, invalid read in function new_transition\n");
        return 0;
    }

    return 1;
}
