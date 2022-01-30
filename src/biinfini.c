#include "biinfini.h"
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>


// Ruban bi infinie vers infini à droite
int infinite_right(char* path) {
  char* res_file_name = "res_file";
  if(copy_file(path, res_file_name)) return 1;

  FILE* origin_file = fopen(path, "r");
  FILE* res_file = fopen(res_file_name, "r+");

  char line[1024];
  char* tok;
  int state_rep_num = 101; // State replace name

  for (size_t ligne=1; fgets(line, 1024, origin_file); ligne++) {
    char buf_state_act[1024]; // Nom de l'état actuel
    int rank_read = 1; // Rang de lecture

    // Lit une ligne sur 2
    for (tok = strtok(line, ","); (tok && *tok) && (ligne%2 == 0); tok = strtok(NULL, ",\n")) {
      if (rank_read == 1)
        strcpy(buf_state_act, tok);

      if ((rank_read == 3) && !strcmp(tok,"<")) {
        if(read_state_nullable(res_file_name, buf_state_act)) {
          char* new_state_name = new_trans_state_name(state_rep_num);
          change_line(res_file, buf_state_act, new_state_name);
          add_new_state(res_file_name, state_rep_num, res_file);
          state_rep_num++;
        }
      }
      rank_read++;
    }
  }

  fclose(origin_file);
  fclose(res_file);
  return 0;
}


// Retourne 0 si l'opération c'est bien passée, 1 sinon
int copy_file(char* path, char* name) {
  FILE* file = fopen(path, "r");
  FILE* res_file = fopen(name, "w");

  if (!file || !res_file) {
    fprintf(stderr, "[ERR] Problème à l'ouverture du fichier\n");
    return 1;
  }

  char line[1024];
  for (size_t i=1; fgets(line, 1024, file); i++)
    fputs(line, res_file);

  fclose(file);
  fclose(res_file);
  return 0;
}

// Renvoie la position de l'état où il faut changer la transition
int pos_change(char* path, char* state) {
  FILE* file = fopen(path, "r");
  char line[1024];
  char* tok;
  int is_state = 0; // 1 si l'état recherché a été trouvé, 0 sinon

  for (size_t i=1; fgets(line, 1024, file); i++) {
    for (tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",")) {
      if (i%2!=0) {
        if (is_state && !strcmp("_\n", tok))
          return SEEK_CUR;
        else if ((i%2 != 0) && !strcmp(tok, state))
          is_state = 1;
      }
      else continue;
    }
  }

  return -1;
}

// Indique si l'état peut lire un caractère null
int read_state_nullable(char* path, char* state) {
  FILE* file = fopen(path, "r");
  char line[1024];
  char* tok;
  int is_state = 0; // 1 si l'état recherché a été trouvé, 0 sinon

  for (size_t ligne=1; fgets(line, 1024, file); ligne++) {
    for (tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",")) {
      if (ligne%2!=0) {
        if (is_state && !strcmp("_\n", tok)){
          fclose(file);
          return 1;
        }
        else if ((ligne%2 != 0) && !strcmp(tok, state))
          is_state = 1;
      }
      else continue;
    }
  }

  return 0;
}

// Remplace une ligne dans un fichier
void replace_line(FILE* file, char* replace) {
  char line[1024];
  int cur_pos = ftell(file);

  fgets(line, 1024, file);

  char* buf = malloc(1000*sizeof(char));
  buf[0] = '\0';

  for (size_t ligne=1; fgets(line, 1024, file); ligne++)
    strcat(buf, line);

  fseek(file, cur_pos, SEEK_SET);
  fputs(replace, file);

  for (size_t i=0; buf[i] != '\0'; i++)
    fputc(buf[i], file);
}

// Change la ligne à changer
void change_line(FILE* file, char* state, char* new_state) {
  int cur_pos = ftell(file);
  char line[1024];
  char* tok;
  int is_state = 0; // 1 si l'état recherché a été trouvé, 0 sinon

  for (size_t ligne=1; fgets(line, 1024, file); ligne++) {
    for (tok = strtok(line, ","); (tok && *tok) && (ligne%2!=0); tok = strtok(NULL, ",\n")) {
      if (is_state && !strcmp("_", tok)){
        replace_line(file, new_state);
        fseek(file, cur_pos, SEEK_SET);
      }
      if(!strcmp(tok, state)){
        is_state = 1;
        continue;
      }
    }
  }

  fprintf(stderr, "[ERR] L'état %s n'a pas été trouvé dans la fonction change_line\n", state);
  exit(EXIT_FAILURE);
}

// Nouveau nom d'état d'un état de transition pour décaler le mot
char* new_trans_state_name(int state_rep_num) {
  char* state_rep_name = malloc(30*sizeof(char));
  memset(state_rep_name, '\0', 30);
  char buf_rep_num[3];

  sprintf(buf_rep_num, "%d", state_rep_num);
  state_rep_name[0] = 'q';
  strncat(state_rep_name, buf_rep_num, 3);
  strcat(state_rep_name, "0,_,>");
  strcat(state_rep_name, "\n");

  return state_rep_name;
}

// Ajoute à la fin du fichier la machine de turing adéquate
int add_new_state(char* path, int state_rep_num, FILE* next_state_file) {
  char line[1024];
  fgets(line, 1024, next_state_file);

  FILE* file = fopen(path, "a");
  char num[3];
  sprintf(num, "%d", state_rep_num);

  char* q0 = malloc(30*sizeof(char)); memset(q0, '\0', 30);
  q0[0] = 'q'; strncat(q0,num,3); strcat(q0, "0");

  char* q1 = malloc(30*sizeof(char)); memset(q1, '\0', 30);
  q1[0] = 'q'; strncat(q1,num,3); strcat(q1, "1");

  char* q2 = malloc(30*sizeof(char)); memset(q2, '\0', 30);
  q2[0] = 'q'; strncat(q2,num,3);  strcat(q2, "2");

  char* q3 = malloc(30*sizeof(char)); memset(q3, '\0', 30);
  q3[0] = 'q'; strncat(q3,num,3); strcat(q3, "3");

  char* q4 = malloc(30*sizeof(char)); memset(q4, '\0', 30);
  q4[0] = 'q'; strncat(q4,num,3); strcat(q4, "4");

  char* qw = malloc(30*sizeof(char)); memset(qw, '\0', 30);
  qw[0] = 'q'; qw[1] = 'w'; strncat(qw, num, 3);

  char* new_states = malloc(500*sizeof(char));
  memset(new_states, '\0', 500);

  strcat(new_states, q0); strcat(new_states, ",0\n");
  strcat(new_states, q0); strcat(new_states, ",0,>\n");
  strcat(new_states, q0); strcat(new_states, ",1\n");
  strcat(new_states, q0); strcat(new_states, ",1,>\n");
  strcat(new_states, q0); strcat(new_states, ",_\n");
  strcat(new_states, q1); strcat(new_states, ",_,<\n");
  strcat(new_states, q1); strcat(new_states, ",0\n");
  strcat(new_states, q2); strcat(new_states, ",_,>\n");
  strcat(new_states, q2); strcat(new_states, ",_\n");
  strcat(new_states, q4); strcat(new_states, ",0,<\n");
  strcat(new_states, q4); strcat(new_states, ",_\n");
  strcat(new_states, q1); strcat(new_states, ",_,<\n");
  strcat(new_states, q1); strcat(new_states, ",1\n");
  strcat(new_states, q3); strcat(new_states, ",_,>\n");
  strcat(new_states, q3); strcat(new_states, ",_\n");
  strcat(new_states, q4); strcat(new_states, ",1,<\n");
  strcat(new_states, q1); strcat(new_states, ",_\n");
  strcat(new_states, qw); strcat(new_states, ",_,>\n");
  strcat(new_states, qw); strcat(new_states, ",_\n");

  fprintf(file,new_states);

  fprintf(file, line);

  fclose(file);
  return 0;
}
