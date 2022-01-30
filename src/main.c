#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "turing.h"
#include "convert.h"
#include "utilities.h"
#include "biinfini.h"
#include "codage.h"

int main(int argc, char ** argv) {
  char * mode = argv[1];

  if (!strcmp(mode, "-d"))  {
    if (argc != 6) {
      fprintf(stderr, "[ERR] Le programme prend 5 arguments.\n");
      print_usage();
      return 1;
    }
  }

  if (!strcmp(mode, "-t") || !strcmp(mode, "-b"))  {
    if (argc != 3) {
      fprintf(stderr, "[ERR] Le programme prend 2 arguments.\n");
      print_usage();
      return 1;
    }
  }


  char* file = argv[2];
  char* entry = argv[3];
  char* init = argv[4];
  char* accept = argv[5];

  // # Initialisation des états de la MT à partir d'un fichier
  STATE* S;
  size_t state_nbr = 0;
  S = malloc(255*sizeof(STATE));

  // test de la  réduction abcd
  if (!strcmp(mode, "-t")) {
    if (!new_codage(file))
      return 1;
  }

  // test de la  réduction biinfini
  if (!strcmp(mode, "-b")) {
    if ((file))
      return 1;
  }

  else if (!strcmp(mode, "-d")) {
    file_to_state(file, S, &state_nbr);

    // # Initialisation de la mt à partir des états
    MT mt;
    init_mt(&mt, S, state_nbr, accept, init);

    calc_mt(entry, mt);
  }

  free(S);

  return 0;
}
