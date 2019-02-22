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
  n_realizations=NR;
  num_vacs=nc*ncells;
  n_nonzeros=3*ncells-6*num_vacs;
  srand(SEED);
  int i,j;
}
void allocate_arrays(){
  cdegree=(int*)malloc(ncells*sizeof(int));
  rdegree=(int*)malloc(ncells*sizeof(int));
  rids=(int *)malloc(n_nonzeros*sizeof(int));
  cptrs=(int *)malloc((ncells+1)*sizeof(int));
  rmatch=(int*)malloc(ncells*sizeof(int));
  cmatch=(int*)malloc(ncells*sizeof(int));
}
void free_arrays(){
  free(cmatch);
  free(rmatch);
  free(rids);
  free(cptrs);
  free(cdegree);
  free(rdegree);
}

void make_sparse(){
  int i,j;
  int x,y;
  for(i=0;i<NSITES;i++)
    ifvac[i]=0;
  int sitea,siteb;

  for(i=0;i<ncells;i++){
    cdegree[i]=3;
    rdegree[i]=3;
  }
  for (i=0;i<ly;i++){
    cdegree[i*lx]=cdegree[(lx-1)+i*lx]=2;
    rdegree[i*lx]=rdegree[(lx-1)+i*lx]=2;
    ifvac[2*i*lx]=ifvac[2*i*lx+1]=-1;
    ifvac[2*(i*lx+(lx-1))]=ifvac[2*(i*lx+(lx-1))]=-1;
  }

  for(i=0;i<num_vacs;i++){
    sitea=(int)((rand()/(RAND_MAX+1.0))*ncells)*2;
    if(ifvac[sitea]==0){
      x=(sitea/2)%lx;
      y=(sitea/2)/lx;
      ifvac[sitea]=1;
      cdegree[sitea/2]=0;
      siteb=neigh[sitea][0];
      rdegree[siteb/2]--;
      ifvac[siteb]=-1;
      ifvac[neigh[siteb][1]]=-1;
      ifvac[neigh[siteb][2]]=-1;

      if(x!=(lx-1)){
        siteb=neigh[sitea][1];
        rdegree[siteb/2]--;
        ifvac[siteb]=-1;
        ifvac[neigh[siteb][0]]=-1;
        ifvac[neigh[siteb][2]]=-1;
      }

      if(x!=0){
        siteb=neigh[sitea][2];
        rdegree[siteb/2]--;
        ifvac[siteb]=-1;
        ifvac[neigh[siteb][1]]=-1;
        ifvac[neigh[siteb][0]]=-1;
      }

    }
    else
      i--;
  }
  for(i=0;i<num_vacs;i++){
    siteb=(int)((rand()/(RAND_MAX+1.0))*ncells)*2+1;
    if(ifvac[siteb]==0){
      //printf("%d\n",siteb);
      x=(sitea/2)%lx;
      y=(sitea/2)/lx;
        ifvac[siteb]=1;
      rdegree[siteb/2]=0;

      sitea=neigh[siteb][0];
      cdegree[sitea/2]--;
      ifvac[sitea]=-1;
      ifvac[neigh[sitea][1]]=-1;
      ifvac[neigh[sitea][2]]=-1;

      if(x!=0){
        sitea=neigh[siteb][1];
        cdegree[sitea/2]--;
        ifvac[sitea]=-1;
        ifvac[neigh[sitea][0]]=-1;
        ifvac[neigh[sitea][2]]=-1;
      }

      if(x!=(lx-1)){
        sitea=neigh[siteb][2];
        cdegree[sitea/2]--;
        ifvac[sitea]=-1;
        ifvac[neigh[sitea][1]]=-1;
        ifvac[neigh[sitea][0]]=-1;
      }
    }
    else
      i--;
  }

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
    x=(i)%lx;
    y=(i)/lx;
      if(ifvac[2*i]!=1){
        siteb=neigh[2*i][0];
        if(ifvac[siteb]!=1){
          rids[rid_ctr]=siteb/2;
          rid_ctr++;
        }
        if(x!=(lx-1)){
          siteb=neigh[2*i][1];
          if(ifvac[siteb]!=1){
            rids[rid_ctr]=siteb/2;
            rid_ctr++;
          }
        }
        if(x!=0){
          siteb=neigh[2*i][2];
          if(ifvac[siteb]!=1){
            rids[rid_ctr]=siteb/2;
            rid_ctr++;
          }
        }

      }
  }
  cptrs[ncells]=n_nonzeros;
  printf("initialized\n");

}
void transpose(){
  int i;
  int rid_ctr,c_ctr;
  int x,y;
  int j,sitea,siteb;
  n_nonzeros=3*ncells-6*num_vacs;
  for(i=0;i<ncells;i++){
    cmatch[i]=rmatch[i]=-1;
    if(ifvac[2*i+1]==1)
      cmatch[i]=-2;   // -2 : impossible to match.
    if(ifvac[2*i]==1)
      rmatch[i]=-2;
  }
  rid_ctr=c_ctr=0;
  for(i=0;i<ncells;i++){
    cptrs[c_ctr]=rid_ctr;
    c_ctr++;
    if(ifvac[2*i+1]!=1){
      x=(i)%lx;
      y=(i)/lx;
        sitea=neigh[2*i+1][0];
      if(ifvac[sitea]!=1){
        rids[rid_ctr]=sitea/2;
        rid_ctr++;
      }
      if(x!=0){
        sitea=neigh[2*i+1][1];
        if(ifvac[sitea]!=1){
          rids[rid_ctr]=sitea/2;
          rid_ctr++;
        }
      }
      if(x!=(lx-1)){
        sitea=neigh[2*i+1][1];
        if(ifvac[sitea]!=1){
          rids[rid_ctr]=sitea/2;
          rid_ctr++;
        }
      }
    }
  }
  cptrs[ncells]=n_nonzeros;
}
