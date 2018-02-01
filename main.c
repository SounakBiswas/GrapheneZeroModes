#include "global.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
void make_lattice();
void initialize();
void make_sparse();
int potfan();
int bfs();
int hkmm();
void main(){
  initialize();
  make_lattice();
  make_sparse();
  //printf("free sites=%d\n",ncells-(int)(nc*ncells)-hkmm());
  //printf("free sites=%d\n",ncells-(int)(nc*ncells)-bfs());
  printf("free sites=%d\n",ncells-(int)(nc*ncells)-potfan());
  free(cmatch);
  free(rmatch);
  free(rids);
  free(cptrs);
  free(cdegree);
  free(rdegree);
}
