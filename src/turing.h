#ifndef TURING_H_
#define TURING_H_

#include <stdio.h>

enum direction {right, left, hold};

/*
 * Les états sont stocké dans la structure state. read permet de stocké la lecture de l'état. Cette variable
 * peut être null, néanmoins si l'état lit 1 alors read aura la forme suivante :
 * read[0] = null ; read[1] = 1 ;  * read[2] = null
 *
 * Cette façon de procéder simplifie les transitions. De même pour replace, replace[0] correspond à un remplacement
 * si on lit un 0, replace[1] un 1 et enfin replace[2] si on lit un caractère vide _ . La même méthode est employé
 * pour la direction et la variable next_state_name.
*/
typedef struct state {
    char* name;
    char* read;
    char ** next_state_name;
    char* replace;
    enum direction* direction;
} STATE;

typedef struct machine_turing {
    size_t state_nbr;
    STATE *states;
    char* accept;
    char* init;
} MT;


/*
 * BUT
 * Initialise une mt
 *
 * ARGUMENTS
 *  - MT *mt           : Machine de Turing à initialiser
 *  - STATE* S         : Etat de la mt à initialiser
 *  - size_t state_nbr : Nombre d'états
 *
 * RETOUR
 * 0 si il y a eu un soucis lors de l'initialisation, 1 sinon. La mt est renvoyé par le pointeur mt.
*/
int init_mt (MT* turing, STATE * S, size_t state_nbr, char* accept, char* init);


/*
 * BUT
 * Initialiser un état de la mt
 *
 * ARGUMENTS
 *  - STAT* S : État à initialiser
 *
 * RETOUR
 * 0 si l'allocation à fonctionner, 1 sinon. L'état est renvoyer par le pointeur S.
*/
int init_state(STATE* S);


/*
 * BUT
 * Faire un pas dans la machine de turing
 *
 * ARGUMENTS
 *  - char* state_name   : Nom de l'état actuel
 *  - char read          : Lecture de la tête de lecture
 *  - MT* mt             : Machine de Turing
 *
 * RETOUR
 *
*/
int one_step(STATE* actual_state, MT mt, char* ruban, int* rank);


/*
 * BUT
 * Simule le calcul de la machine de turing sur le mot jusqu'à atteindre l'état final
 *
 * ARGUMENTS
 *  - char* w : Le mot à parcourir
 *  - MT mt   : La machine de Turing
 *
 * RETOUR
 * Retourne 1 si le mot est rejeté, 0 s'il est accepté
*/
int calc_mt(char* w, MT mt);

#endif // TURING_H_
