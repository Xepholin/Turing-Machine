#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "turing.h"
#include "convert.h"
#include "utilities.h"

/*
 * Convertit un fichier en une liste d'arguments.
*/
void file_to_state (char * path, STATE* S, size_t* state_nbr) {
    FILE * file = fopen(path, "r");

    if (!file) {
        printf("Error file cannot be open\n");
        exit(EXIT_FAILURE);
    }

    if (!export(file, S, state_nbr)) {
        printf("Error, Export function failed\n");
        exit(EXIT_FAILURE);
    }

    fclose(file);
}

/*
 * Insert un état dans la MT, Renvoie 0 si l'état a été inséré ou 1 si l'état existe déjà
 */
int insert_state(int rank_tok, STATE* S, char* tok, size_t* state_nbr, size_t* read_buf, size_t* temp) {
    switch (rank_tok) {
    case 0:
        // Si l'état n'est pas dans la liste d'état
        if (!state_in_list(S, tok, *state_nbr) && (tok != "q0")) {
            init_state(&S[*state_nbr]);
            S[*state_nbr].name = strdup(tok);
            *temp = *state_nbr;
            *state_nbr = *state_nbr+1;
        }
        else {
            *temp = search_state_pos(S, tok, *state_nbr);
        }
        break;

    case 1:
        if (!strcmp("_", tok)) {
            if (S[*temp].read[2]) return 1;

            S[*temp].read[2] = tok[0];
            *read_buf = 2;
        }
        else {
            if (S[*temp].read[atoi(tok)]) return 1;

            S[*temp].read[atoi(tok)] = tok[0];
            *read_buf = atoi(tok);
        }
    }

    return 0;
}

/*
 * Ajoute une transition à un état, Retourne 0 si la transition a été ajoutée, 1 si la transtion est incorrect
*/
int insert_transition(int rank_tok, STATE* S, char* tok, size_t* state_nbr, size_t* read_buf, size_t* temp) {
    // Dans le cas d'une ligne pair, on insere le reste de la transition
    switch (rank_tok) {
    case 0:
        if (!state_in_list(S, tok, *state_nbr) && (tok != "q0")) {
            init_state(&S[*state_nbr]);
            S[*temp].next_state_name[*read_buf] = strdup(tok);
        }
        else {
            STATE buf;
            if(!find_state(&buf, S, tok, *state_nbr))
                return 1;;
            S[*temp].next_state_name[*read_buf] = buf.name;
        }
        break;

    case 1:
        if (tok[0] == '0' || tok[0] == '1' || tok[0] == '_')
            S[*temp].replace[*read_buf] = tok[0];
        else
            return 1;
        break;

    case 2:
        if (!strcmp(tok, ">"))
            S[*temp].direction[*read_buf] = right;
        else if (!strcmp(tok, "<"))
            S[*temp].direction[*read_buf] = left;
        else if (!strcmp(tok, "-"))
            S[*temp].direction[*read_buf] = hold;
        else
            return 1;
        break;
    }

    return 0;
}

/*
 * Exporte les états d'un fichier pour les mettre dans une liste d'états
 * Retourne 0 si l'exportation c'est bien passé, 1 sinon avec un message d'erreur
*/
int export(FILE * file, STATE * S, size_t* state_nbr) {
    if (!file) {
        printf("Error, file cannot be open\n");
        return 1;
    }
    else if (!S)    {
        printf("Error, State is empty\n");
        return 1;
    }
    
    char line[1024];
    char* tok;
    size_t read_buf = 0;
    size_t temp = 0;

    // Dans la boucle, i est aussi utilisé pour savoir sur quelle ligne on se situe.
    // i%2==0 indique que la ligne est impair
    // i%2==1 indique que la ligne est pair
    for (size_t i=0; fgets(line, 1024, file); i++) {
        int rank_tok = 0; // Variable qui stocke là ou on est sur la ligne (q0,1,> => q0=0, 1=1, >=2)

        if (!strcmp(line, "\n")) {
            printf("Le fichier contient des lignes vides.\n");
            return 1;
        }

        for (tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",\n")) {
            // Dans le cas d'une ligne impair, on insere le read
            if (i%2 == 0) { 
                // Si l'état n'est pas dans la liste d'état
                if(insert_state(rank_tok, S, tok, state_nbr, &read_buf, &temp)) {
                    printf("Error: Transition in line %ld is already defined\n", i+1);
                    return 1;
                }
            }
            
            // Dans le cas d'une ligne pair, on insere le reste
            if (i%2 == 1) {
                if(insert_transition(rank_tok, S, tok, state_nbr, &read_buf, &temp)) {
                    printf("Error: Incorrect transition in line %ld. Movements must be left (<), right (>) or center (-)\n", i+1);
                    return 1;
                }
            }
            rank_tok++;
        }
    }

    return 1;
}
