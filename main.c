#include "global.h"
#include <stdlib.h>
#include <stdio.h>
int ford_fulkerson();
void makelattice();
void initialize();

void main(){
  initialize();
  make_lattice();
  aug=0;
  printf("maximum matching is %d \n",ford_fulkerson());
  int i;
  printf("naugs %d \n",aug);
 // for(i=3*ncells;i<4*ncells;i++){
  //if(flow[i]==0)
  //  printf("%d\n",i-3*ncells);
 // }



}
