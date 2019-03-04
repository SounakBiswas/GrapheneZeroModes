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
  n_nonzeros=3*(ncells)-ly -6*num_vacs;
  srand(SEED);
  int i,j;
}
void allocate_arrays(){
  ifvac=(int*)malloc(nsites*sizeof(int));
  burn=(int*)malloc(nsites*sizeof(int));
  neigh=(int**)malloc(nsites*sizeof(int*));
  int i;
  for(i=0;i<nsites;i++)
    neigh[i]=(int*)malloc(3*sizeof(int));
  cdegree=(int*)malloc(ncells*sizeof(int));
  rdegree=(int*)malloc(ncells*sizeof(int));
  rids=(int *)malloc(n_nonzeros*sizeof(int));
  cptrs=(int *)malloc((ncells+1)*sizeof(int));
  rmatch=(int*)malloc(ncells*sizeof(int));
  cmatch=(int*)malloc(ncells*sizeof(int));
}
void free_arrays(){
  free(ifvac);
  free(burn);
  free(cmatch);
  free(rmatch);
  free(rids);
  free(cptrs);
  free(cdegree);
  free(rdegree);
  int i;
  for(i=0;i<nsites;i++)
    free(neigh[i]);
  free(neigh);
}
void make_sparse(){
  int i,j;
  int x,y;
  int cell1,cell2;
  for(i=0;i<NSITES;i++)
    ifvac[i]=0;
  int sitea,siteb;

  for(i=0;i<ncells;i++){
    cdegree[i]=3;
    rdegree[i]=3;
  }
  for (y=0;y<ly;y++){
    cell1=y*lx;
    cell2=y*lx+(lx-1);
    cdegree[cell1]=cdegree[cell2]=2;
    rdegree[cell1]=rdegree[cell2]=2;
    ifvac[2*cell1]=ifvac[2*cell1+1]=-1;
    ifvac[2*cell2]=ifvac[2*cell2+1]=-1;
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

      siteb=neigh[sitea][1];
      rdegree[siteb/2]--;
      ifvac[siteb]=-1;
      ifvac[neigh[siteb][0]]=-1;
      ifvac[neigh[siteb][2]]=-1;

      siteb=neigh[sitea][2];
      rdegree[siteb/2]--;
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
      x=(siteb/2)%lx;
      y=(siteb/2)/lx;
      ifvac[siteb]=1;
      rdegree[siteb/2]=0;

      sitea=neigh[siteb][0];
      cdegree[sitea/2]--;
      ifvac[sitea]=-1;
      ifvac[neigh[sitea][1]]=-1;
      ifvac[neigh[sitea][2]]=-1;

      sitea=neigh[siteb][1];
      cdegree[sitea/2]--;
      ifvac[sitea]=-1;
      ifvac[neigh[sitea][0]]=-1;
      ifvac[neigh[sitea][2]]=-1;

      sitea=neigh[siteb][2];
      cdegree[sitea/2]--;
      ifvac[sitea]=-1;
      ifvac[neigh[sitea][1]]=-1;
      ifvac[neigh[sitea][0]]=-1;
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
  int flagn1,flagn2;
  for(i=0;i<ncells;i++){
    cptrs[c_ctr]=rid_ctr;
    c_ctr++;
    x=(i)%lx;
    y=(i)/lx;
    flagn1= (x==lx-1)&&(y%2==0);
    flagn2= (x==0)&&(y%2==1);
    if(ifvac[2*i]!=1){
      siteb=neigh[2*i][0];
      if(ifvac[siteb]!=1){
        rids[rid_ctr]=siteb/2;
        rid_ctr++;
      }
      if(!flagn1 ){
      siteb=neigh[2*i][1];
      if(ifvac[siteb]!=1){
        rids[rid_ctr]=siteb/2;
        rid_ctr++;
      }
      }
      if(!flagn2){
        siteb=neigh[2*i][2];
        if(ifvac[siteb]!=1){
          rids[rid_ctr]=siteb/2;
          rid_ctr++;
        }
      }

    }

  }
  printf("nz %d  tot %d\n",n_nonzeros,rid_ctr);
  cptrs[ncells]=n_nonzeros;
  printf("initialized\n");

}
void transpose(){
  int i;
  int rid_ctr,c_ctr;
  int x,y;
  int j,sitea,siteb;
  int flagn1,flagn2;
  n_nonzeros=3*ncells -ly -6*num_vacs;
  int temp;
  for(i=0;i<ncells;i++){
    //cmatch[i]=rmatch[i]=-1;
    //if(ifvac[2*i+1]==1)
    //  cmatch[i]=-2;   // -2 : impossible to match.
    //else if(ifvac[2*i]==1)
    //  rmatch[i]=-2;

    temp=cmatch[i];
    cmatch[i]=rmatch[i];
    rmatch[i]=temp;
  }
  rid_ctr=c_ctr=0;
  for(i=0;i<ncells;i++){
    cptrs[c_ctr]=rid_ctr;
    c_ctr++;
    if(ifvac[2*i+1]!=1){
      x=(i)%lx;
      y=(i)/lx;
      flagn1= (x==0)&&(y%2==1);
      flagn2= (x==lx-1)&&(y%2==0);
      sitea=neigh[2*i+1][0];
      if(ifvac[sitea]!=1){
        rids[rid_ctr]=sitea/2;
        rid_ctr++;
      }
      if(!flagn1){
      sitea=neigh[2*i+1][1];
      if(ifvac[sitea]!=1){
        rids[rid_ctr]=sitea/2;
        rid_ctr++;
      }
      }

      if(!flagn2){
        sitea=neigh[2*i+1][2];
        if(ifvac[sitea]!=1){
          rids[rid_ctr]=sitea/2;
          rid_ctr++;
        }
      }
    }
  }
  cptrs[ncells]=n_nonzeros;
}
