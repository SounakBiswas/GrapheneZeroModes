#include "global.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
void make_lattice();
void initialize();
void make_sparse();
int potfan();
//int dfs();
void main(){
  initialize();
  make_lattice();
  make_sparse();
  aug=0;
  //printf("free sites=%d\n",ncells-(int)(nc*ncells)-dfs());
  printf("free sites=%d\n",ncells-(int)(nc*ncells)-potfan());
  free(cmatch);
  free(rmatch);
  free(rids);
  free(cptrs);
  free(cdegree);
  free(rdegree);
}
