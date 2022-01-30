#include <string.h>
#include <stdlib.h>
#include "utilities.h"


/*
 * Affiche l'utilisation du programme dans le terminl
*/
void print_usage() {
  printf("# USAGE\n"
         "Réduction abcd :\n"
         "./turing -t <Nom du fichier>\n"
         "Réduction bifini vers infini\n"
         "./turing -b <Nom du fichier>\n"
         "Simulateur de mt\n"
         "./turing -d <Nom du fichier> <Entrée> <État initial> <État acceptant>\n");
}

/*
 * Fonction permettant de respecter la synthaxe à propos des directions lors de l'affichage de celle ci dans
 * le terminal
*/
char getDirName(enum direction dir)
{
   switch (dir)
   {
      case right:
        return '>';
      case left:
        return '<';
      case hold:
        return '-';
   }

   char null = ' ';
   return null;
}

/*
 * Renvoie 1 si le token correspond à un nom d'état dans la MT, 0 sinon
*/
int state_in_list(STATE *S, char* tok, size_t state_nbr) {
    for (size_t i = 0; i < state_nbr ; i++)
        if (strcmp(S[i].name,tok) == 0)
            return 1;

    return 0;
}

/*
 * Renvoie la position de l'état si le token a été trouvé, -1 sinon
*/
int search_state_pos(STATE *S, char* tok, size_t state_nbr) {
    for (size_t i = 0; i < state_nbr ; i++)
        if (strcmp(S[i].name,tok) == 0)
            return i;

    return -1;
}

/*
 * Retourne 1 si l'état a été trouvé, 0 sinon
*/
int find_state(STATE* state, STATE *S, char* tok, size_t state_nbr) {
    for (size_t i=0; i<state_nbr ; i++) {
        if (strcmp(S[i].name, tok) == 0) {
          *state = S[i];
          return 1;
        }
    }

    return 0;
}

// Affiche dans le terminal le ruban
void display_tape(char* tape, STATE state, size_t rank) {
  printf("%s\n", state.name);
  for (size_t i=0; i < 30; i++)
    printf("%c", tape[i]);

  printf("\n");

  if (rank == 0) printf("^");
  else {
    for (size_t k=0; k<30; k++) {
      if (rank !=0 ) printf(" ");
      if (k == rank-1) printf("^");
    }
  }

  printf("\n");
}
