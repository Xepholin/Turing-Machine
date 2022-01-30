#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <unistd.h>
#include "turing.h"


/*
 * BUT
 * Affiche l'utilisation du programme
*/
void print_usage();

/*
 * BUT
 * Permet de respecter la notation des directions lors d'un affichage dans le terminal de celle ci
 *
 * ARGUMENTS
 *  - enum direction dir : direction à afficher
 *
 * RENVOIE
 * Renvoie le caractère correspondant donc right = '>' ; left = '<' ; hold = '-'
*/
char getDirName(enum direction dir);

/*
 * BUT
 * Indiquer si un état existe dans la MT selon son nom.
 *
 * ARGUMENTS
 *  - STATE* S         : Liste des états de la MT.
 *  - char* tok        : Le nom de l'état a chercher dans la MT.
 *  - size_t state_nbr : Nombre d'états dans la machine de Turing.
 *
 * RENVOIE
 * Renvoie 1 si le nom correspond à un nom d'état dans la MT, 0 sinon
*/
int state_in_list(STATE *S, char* tok, size_t state_nbr);


/*
 * BUT
 * Donner la position d'un état dans la MT. On part du principe que l'état est dans la MT.
 *
 * ARGUMENTS
 *  - STATE* S         : Liste des états de la MT.
 *  - char* tok        : Le nom de l'état dont il faut trouver la position
 *  - size_t state_nbr : Le nombre d'état de la MT.
 *
 * RENVOIE
 * Renvoie la position de l'état dans la MT.
*/
int search_state_pos(STATE *S, char* tok, size_t state_nbr);


/*
 * BUT
 * Trouver un token d'un MT selon un nom.
 *
 * ARGUMENTS
 *  - STATE* state     : Pointeur permettant de stocker l'état trouvé
 *  - STATE *S         : Liste d'état de la MT.
 *  - char* tok        : Nom de l'état à trouver.
 *  - size_t state_nbr : Nombre d'état de la MT.
 *
 * RENVOIE
 * Renvoie 1 si l'état a été trouvé, 0 sinon. Renvoie via un pointeur l'état trouvé
*/
int find_state(STATE* state, STATE *S, char* tok, size_t state_nbr);


/*
 * BUT
 * Afficher dans le terminal le ruban, l'état das lequel on est et la tête de lecture
 *
 * ARGUMENTS
 *  - char* ruban : Le ruban à afficher
 *  - STATE state : Etat actuel
 *  - size_t rank : Rang sur le ruban
*/
void display_tape(char* tape, STATE state, size_t rank);

#endif // UTILITIES_H_
