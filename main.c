#include "global.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
void makelattice();
void initialize();
void make_sparse();
int count_free(){
  int i,count;
  count=0;
  for(i=0;i<ncells;i++){
    if(rmatch[i]==-1)
      count++;
    if(cmatch[i]==-1)
      count++;
    if(cmatch[i]>=0)
      assert(rmatch[cmatch[i]]==i);
  
  }
  return count;
}
void main(){
  initialize();
  make_lattice();
  make_sparse();
  aug=0;
  dfs();
  printf("maximum matching is %d i %d\n",count_free()/2+(int)(nc*ncells),aug);
  free(cmatch);
  free(rmatch);
  free(rids);
  free(cptrs);
  int i;
  //for(i=0;i<ncells;i++)
  //printf("rm %d  cm %d \n",rmatch[i],cmatch[i]);



}
