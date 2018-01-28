#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "time.h"
void initialize(){
  lx=LX;
  ly=LY;
  ncells=NCELLS;
  nlinks=NLINKS;
  nedges=NEDGES;
  nsites=NSITES;
  nc=NC;
  srand(25);
  int i;
  
  //initialize capacity and flow;
  for(i=0;i<nedges;i++){
    capacity[i]=1;
    flow[i]=0;
  }


}
