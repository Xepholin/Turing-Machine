#ifndef CODAGE_H_
#define CODAGE_H_

/*
 * BUT
 * Convertit le fichier donné en argument, qui travaille sur l'alphabet {a,b,c,d},
 * en un code de machine de turing équivalent qui travaille sur l'alphabet {0,1}.
 *
 * ARGUMENTS
 *  - char * path : chemin du fichier à convertir
 *
 * RENVOIE
 * Retourne 1 en cas de réussite, 0 sinon.
*/
int new_codage(char * path);

/*
 * BUT
 * Prend en compte les valeurs passées en argument afin de les convertir en une
 * suite de transition travaillant sur l'alphabet {0,1}.
 * Cette fonction est utilisée pour la 2e ligne d'une transition.
 *          q0,1    -> 1ere ligne
 *          q1,0,>  -> 2e ligne
 *
 * ARGUMENTS
 *  - char * etat      : nom de l'état pour construire la base du nom pour les nouveaux états (1ere ligne)
 *  - char * read      : caractère lu (1ere ligne)
 *  - char * suiv      : état suivant (2e ligne)
 *  - char * replace   : caractère qui remplace le précédent (2e ligne)
 *  - char * direction : caractère qui donne la direction à prendre (2e ligne)
 *  - char * buff      : Tableau utilisé pour inséré le résultat de la conversion
 *  - size_t * count   : Compteur utilisé pour construire la base du nom des nouveaux états
 *
 * RENVOIE
 * Retourne 1 en cas de réussite, 0 sinon. Le tableau est renvoyé par le pointeur buff.
*/
int new_transition(char * etat, char * read, char * suiv, char * replace, char * direction, char * buff, size_t * count);

/*
 * BUT
 * Prend en compte les valeurs passées en argument afin de les convertir en une
 * suite de transition travaillant sur l'alphabet {0,1}.
 * Cette fonction est utilisée pour la 1ere ligne d'une transition.
 *          q0,1    -> 1ere ligne
 *          q1,0,>  -> 2e ligne
 *
 * ARGUMENTS
 *  - char * etat      : nom de l'état pour construire la base du nom pour les nouveaux états (1ere ligne)
 *  - char * read      : caractère lu (1ere ligne)
 *  - char * replace   : caractère qui remplace le précédent (2e ligne)
 *  - char * buff      : Tableau utilisé pour inséré le résultat de la conversion
 *  - size_t * count   : Compteur utilisé pour construire la base du nom des nouveaux états
 *
 * RENVOIE
 * Retourne 1 en cas de réussite, 0 sinon. Le tableau est renvoyé par le pointeur buff.
*/
int new_read(char * etat, char * read, char * replace, char * buff, size_t * count);

#endif // CODAGE_H_
