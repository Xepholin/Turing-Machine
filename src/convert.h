#include <stddef.h>
#include "turing.h"

/*
 * BUT
 * Fonction permettant de traduire un fichier en une liste d'états
 *
 * ARGUMENTS
 *  - char* path       : Fichier contenant la machine de turing (écrit au bon format)
 *  - STATE* S         : Liste des états
 *  - size_t nbr_state : Nombre d'états de la machine de turing
 *
 * RENVOIE
 * Renvoie via des pointeurs la liste d'états et le nombre d'état
*/
void file_to_state (char * path, STATE *S, size_t* nbr_state);


/*
 * BUT
 * Fonction utile pour la fonction export. insert_read permet de traduire la lecture dans le fichier par un état
 * dans notre strucure. Cette fonction ne lit que les lignes de lecture c'est à dire "q0, 1" par exemple (et pas
 * "q0,1,>").
 *
 * ARGUMENTS
 *  - int rank_tok      : Rang de lecture. Par exemple pour "q0,1", si on lit "q0", rank_tok = 0 et si on lit
 *                        "1", rank_tok = 1.
 *  - STATE* S          : Contient tous les états de la MT.
 *  - char* tok         : Lecture du fichier. Par exemple pour "q0,1", le token est soit "q0" soit "1".
 *  - size_t* state_nbr : Stocke le nombre d'état de la machine. Ajoute 1 à chaque nouvel état rencontré.
 *  - size_t* read_buf  : Permet d'insérer au bon rang le prochaine état. Ne sert que pour la fonction
 *                        insert_transition qui vient obligatoirement après cette fonction.
 *  - size_t* temp      : Variable stockant le rang temporaire de l'état dans la MT.
 *
 * RENVOIE
 * Renvoie via des pointeurs les variables state_nbr, read_buf, temp et S.
*/
int insert_read(int rank_tok, STATE* S, char* tok, size_t* state_nbr, size_t* read_buf, size_t* temp);


/*
 * Fonction utile pour la fonction export. insert_transition permet d'ajouter la transtion dans le fichier par une
 * transition associé à un état dans notre structure. Cette fonction ne lit que les lignes de transition, c'est à
 * dire "q0,1,>" par exemple (et pas "q0,1").
 *
 * ARGUMENTS
 *  - int rank_tok      : Rang de lecture. Par exemple pour "q0,1,>", "q0" est au rank_tok 0, "1" au rank_tok "1"
 *                        et ">", au rank_tok 2.
 *  - STATE* S          : Contient tous les états de la MT.
 *  - char* tok         : Lecture du fichier. Par exemple pour "q0,1,>", le token est soit "q0" soit "1" soit ">".
 *  - size_t* state_nbr : Stocke le nombre d'état de la machine. Ajoute 1 à chaque nouvel état rencontré.
 *  - size_t* read_buf  : Permet d'insérer au bon rang le prochaine état. Ne sert que pour la fonction
 *                        insert_transition qui vientobligatoirement après cette fonction.
 *  - size_t* temp      : Variable stockant le rang temporaire de l'état dans la MT.
 *
 *  RENVOIE
 *  Renvoie via des pointeurs les variables S, state_nbr, read_buf et temp.
 */
int insert_transition(int rank_tok, STATE* S, char* tok, size_t* state_nbr, size_t* read_buf, size_t* temp);


/*
 * BUT
 * Exporter les états d'un fichier vers une liste d'états avec leurs transitions.
 *
 * ARGUMENTS
 *  - FILE* file       : Fichier contenant les instructions de la MT.
 *  - STATE* S         : Liste des états
 *  - size_t state_nbr : Nombre d'état de la MT
 *
 * RENVOIE
 * Renvoie 0 si la fonction n'a pas rencontrée de problème, 1 sinon avec un mesage d'erreur.
 * La fonction renvoie via des pointeurs la liste des états et le nombre d'états qu'il y a dans le fichier
 * d'instructions.
*/
int export (FILE * file, STATE * S, size_t* state_nbr);
