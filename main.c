#include "global.h"
#include <stdlib.h>
#include <stdio.h>
int ford_fulkerson();
void makelattice();
void initialize();

void main(){
  initialize();
  make_lattice();
  printf("maximum matching is %d \n",ford_fulkerson());



}
