#include <stdlib.h>
#include <stdio.h>
#include "global.h"
void initialize(){
  lx=LX;
  ly=LY;
  ncells=NCELLS;
  nlinks=NLINKS;
  nedges=NEDGES;
  nsites=NSITES;
  int i;
  
  //initialize capacity and flow;
  for(i=0;i<nedges;i++){
    capacity[i]=1;
    flow[i]=0;
  }


}
