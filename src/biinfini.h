#ifndef TRANSFO_H_
#define TRANSFO_H_

#include <stdio.h>

/*
 * BUT
 * Traduire un fichier contenant le code d'une mt à ruban bi infini en une mt avec ruban
 * infini vers la droite
 *
 * ARGUMENTS
 * - char* path : Chemin vers le fichier à changer
 *
 * RETOUR
 * 1 si l'opération c'est bien passée, 0 sinon
*/
int infinite_right(char* path);

/*
 * BUT
 * Copie un fichier
 *
 * ARGUMENTS
 * char* path : chemin du fichier à copier
 * char* name : Nom du nouveau fichier
 *
 * RETOUR
 * 1 si l'opération c'est bien passée, 0 sinon
*/
int copy_file(char* path, char* name);

/*
 * BUT
 * Renvoyer la position de l'état où il faut changer la transition
 *
 * ARGUMENTS
 * char* path : chemin du fichier ou il faut changer la transition
 * char* state : état à changer
 *
 * RETOUR
 * Position de la transition à changer
*/
int pos_change(char* path, char* state);

/*
 * BUT
 * Savoir si un état peut être null après un retour arrière sur la bande
 *
 * ARGUMENTS
 * char* path : chemin du fichier
 * char* state : état en question
 *
 * RETOUR
 * Renvoie 1 si l'état peut lire un caractère null, 0 sinon
*/
int read_state_nullable(char* path, char* state);

/*
 * BUT
 * Remplacer une ligne
 *
 * ARGUMENTS
 * FILE* file : Fichier à changer
 * char* replace : Chaîne de caractères à mettre à la place
 *
*/
void replace_line(FILE* file, char* replace);

/*
 * BUT
 * Changer une ligne indiqué par un état
 *
 * ARGUMENTS
 * FILE* file : fichier à changer
 * char* state : Etat à changer
 * char* new_state : chaîne de caractères à mettre à la place
 *
*/
void change_line(FILE* file, char* state, char* new_state);

/*
 * BUT
 * Calcul un nouveau nom pour l'ajout d'un état pour décaler le mot  à droite
 *
 * ARGUMENTS
 * int state_rep_num : Indique quel numéro doit avoir l'état
 *
 * RETOUR
 * Retourne la nom crée
*/
char* new_trans_state_name(int state_rep_num);

/*
 * BUT
 * Ajouter les état nécessaire pour décaler le mot à droite
 *
 * ARGUMENTS
 * char* path : Chemin d'accés au fichier
 * int state_rep_num : Numéro des états de décalage
 * FILE* next_state_file : Fichier permettant d'insérer la derniere transition
*/
int add_new_state(char* path, int state_rep_num, FILE* next_state_file);


#endif // TRANSFO_H_
