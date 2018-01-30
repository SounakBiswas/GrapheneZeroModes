#include "global.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
void makelattice();
void initialize();
void make_sparse();
void main(){
  initialize();
  make_lattice();
  make_sparse();
  aug=0;
  printf("free sites=%d\n",ncells-(int)(nc*ncells)-dfs());
  free(cmatch);
  free(rmatch);
  free(rids);
  free(cptrs);
}
