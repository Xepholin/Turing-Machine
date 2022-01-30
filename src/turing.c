#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "utilities.h"
#include "turing.h"

/*
 * Initialise un état S
 * La fonction retourne 0 si l'initialisation c'est bien passé, 1 si l'allocation
 * n'a pas fonctionnée
*/
int init_state(STATE* S) {
  S->read = malloc(3*sizeof(char));
  S->next_state_name = malloc(3*sizeof(50*sizeof(char)));
  S->replace = malloc(3*sizeof(char));
  S->direction = malloc(3*sizeof(enum direction));

  if (S->read && S->next_state_name && S->replace && S->direction)
    return 0;
    
  return 1;
}

// Initialise une machine de Turing
int init_mt (MT* turing, STATE * S, size_t state_nbr, char* accept, char* init) {
  turing->states = S;
  turing->state_nbr = state_nbr;
  turing->accept = accept;
  turing->init = init;

  if (turing->states && turing->state_nbr && turing->accept)
    return 0;

  return 1;
}

// Initialise le ruban en mettant a ruban[0] un caractère blanc pour indiquer le bout gauche du mot
// et met que des _ vers la droite.
char* init_ruban(char* w) {
  char* ruban = malloc(9999 * sizeof(char));
  ruban[0] = '_';

  for (size_t i=1; i<9999-1; i++) {
    if (i<=strlen(w)) ruban[i] = w[i-1];
    else ruban[i] = '_';
  }

  return ruban;
}

// Boucle qui calcule la mt
int calc_mt(char* w, MT mt) {
  char* ruban = init_ruban(w);

  int rank = 1;
  STATE actual_state;
  find_state(&actual_state, mt.states, mt.init, mt.state_nbr);

  while(1) {
    display_tape(ruban, actual_state, rank);

    switch (one_step(&actual_state, mt, ruban, &rank)) {
    case 1:
      printf("Mot accepté ruban final :\n");
      for (size_t i=0; i<30; i++)
        printf("%c", ruban[i]);
      printf("\n");
      return 0;
      break;

    case -1:
      printf("Mot rejeté\n");
      return 1;
      break;
    default:
      break;
    }
  }
}

//
int one_step(STATE* actual_state, MT mt, char* ruban, int* rank) {
  int rank_replace = -1;

  if(ruban[*rank] == '_') rank_replace = 2;
  else rank_replace = ruban[*rank] - '0';

  int rank_etat = search_state_pos(mt.states, actual_state->name, mt.state_nbr);

  // On remplace la tête de lecture par l'état
  ruban[*rank] = mt.states[rank_etat].replace[rank_replace];

  switch (mt.states[rank_etat].direction[rank_replace]) {
  case right:
    *rank = *rank+1;
    break;
  case left:
    *rank = *rank-1;
    break;
  case hold:
    *rank = *rank;
    break;
  }


  if (!actual_state->next_state_name[rank_replace]
      && !strcmp(actual_state->name, mt.accept))
    return 1; // Accepté car l'état suivant n'existe pas mais on se situe sur l'état acceptant

  if (!actual_state->next_state_name[rank_replace])
    return -1; // Rejet car la transition n'existe pas
  
  if (!strcmp(actual_state->next_state_name[rank_replace], mt.accept))
    return 1; // Accepté car l'état suivant est qAccept

  if(!find_state(actual_state, mt.states, actual_state->next_state_name[rank_replace], mt.state_nbr))
    return -1; // Rejet car l'état suivant n'existe pas

  return 0;
}
