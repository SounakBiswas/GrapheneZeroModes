#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "time.h"
#include <stdlib.h>
void initialize(){
  lx=LX;
  ly=LY;
  ncells=NCELLS;
  nlinks=NLINKS;
  nedges=NEDGES;
  nsites=NSITES;
  nc=NC;
  srand(22);
  int i,j;
  
  //initialize capacity and flow;



}
void make_sparse(){
  int i,j;
  int ifvac[NSITES];
  for(i=0;i<NSITES;i++)
    ifvac[i]=0;
  int num_vacs=nc*ncells;
  n_nonzeros=3*ncells-6*num_vacs;
  int sitea,siteb;

  for(i=0;i<num_vacs;i++){
    sitea=(int)((rand()/(RAND_MAX+1.0))*ncells)*2;
    if(ifvac[sitea]==0){
      //printf("%d\n",sitea);
      ifvac[sitea]=1;
      siteb=neigh[sitea][0];
      ifvac[siteb]=-1;
      ifvac[neigh[siteb][1]]=-1;
      ifvac[neigh[siteb][2]]=-1;

      siteb=neigh[sitea][1];
      ifvac[siteb]=-1;
      ifvac[neigh[siteb][0]]=-1;
      ifvac[neigh[siteb][2]]=-1;

      siteb=neigh[sitea][2];
      ifvac[siteb]=-1;
      ifvac[neigh[siteb][1]]=-1;
      ifvac[neigh[siteb][0]]=-1;

    }
    else
      i--;
  }
  for(i=0;i<num_vacs;i++){
    siteb=(int)((rand()/(RAND_MAX+1.0))*ncells)*2+1;
    if(ifvac[siteb]==0){
      //printf("%d\n",siteb);
      ifvac[siteb]=1;
      sitea=neigh[siteb][0];
      ifvac[sitea]=-1;
      ifvac[neigh[sitea][1]]=-1;
      ifvac[neigh[sitea][2]]=-1;

      sitea=neigh[siteb][1];
      ifvac[sitea]=-1;
      ifvac[neigh[sitea][0]]=-1;
      ifvac[neigh[sitea][2]]=-1;

      sitea=neigh[siteb][2];
      ifvac[sitea]=-1;
      ifvac[neigh[sitea][1]]=-1;
      ifvac[neigh[sitea][0]]=-1;
    }
    else
      i--;
  }
  // Make sparse structures
  rids=(int *)malloc(n_nonzeros*sizeof(int));
  cptrs=(int *)malloc((ncells+1)*sizeof(int));
  rmatch=(int*)malloc(ncells*sizeof(int));
  cmatch=(int*)malloc(ncells*sizeof(int));

  for(i=0;i<ncells;i++){
    cmatch[i]=rmatch[i]=-1;
    if(ifvac[2*i]==1)
      cmatch[i]=-2;   // -2 : impossible to match.
    if(ifvac[2*i+1]==1)
      rmatch[i]=-2;
  }

  int rid_ctr,c_ctr;
  rid_ctr=c_ctr=0;
  for(i=0;i<ncells;i++){
    cptrs[c_ctr]=rid_ctr;
    c_ctr++;
    if(ifvac[2*i]!=1){
      for(j=0;j<3;j++){
        siteb=neigh[2*i][j];
        if(ifvac[siteb]!=1){
          rids[rid_ctr]=siteb/2;
          rid_ctr++;
        }
      }
    }
  }
  cptrs[ncells]=n_nonzeros;
  //for(i=0;i<ncells;i++)
  //printf("rm %d  cm %d \n",rmatch[i],cmatch[i]);
  //for(i=0;i<ncells+1;i++)
  //printf(" %d  %d \n",i,cptrs[i]);

}
