#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "time.h"
#include <stdlib.h>
#define  next_nbr(ii,jj,xx,yy)  ((xx+ii+lx)%lx + ((yy+jj+ly)%ly)*lx)
void clear_match(){
  int i;
  for(i=0;i<ncells;i++){
    if(cmatch[i]!=-2)
      cmatch[i]=-1;
    if(rmatch[i]!=-2)
      rmatch[i]=-1;
  
  }
}
void initialize(){
  lx=LX;
  ly=LY;
  ncells=NCELLS;
  nlinks=NLINKS;
  nedges=NEDGES;
  nsites=NSITES;
  nc=NC;
  srand(32);
  int i,j;
  cdegree=(int*)malloc(ncells*sizeof(int));
  rdegree=(int*)malloc(ncells*sizeof(int));
}
static inline void knocka(int sitea){
  int siteb;
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
static inline void knockb(int siteb){
  int sitea;
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

void make_sparse(){
  int i,j;
  for(i=0;i<NSITES;i++)
    ifvac[i]=0;
  num_vacs=6;
  n_nonzeros=3*ncells-6*num_vacs;
  int sitea,siteb;

  for(i=0;i<ncells;i++){
    cdegree[i]=3;
    rdegree[i]=3;
  }
  int posx=0;
  int posy=0;
  int site;
  site=2*(posx+lx*posy)+1;
  knockb(site);
  site=2*(next_nbr(posx,posy,2,0))+1;
  knockb(site);
  site=2*(next_nbr(posx,posy,-2,0))+1;
  knockb(site);
  site=2*(next_nbr(posx,posy,0,2))+1;
  knockb(site);
  site=2*(next_nbr(posx,posy,2,2))+1;
  knockb(site);
  site=2*(next_nbr(posx,posy,2,4))+1;
  knockb(site);

  posx=lx/2;
  posy=ly/2;
  site=2*(posx+lx*posy);
  knocka(site);
  site=2*(next_nbr(posx,posy,2,0));
  knocka(site);
  site=2*(next_nbr(posx,posy,-2,0));
  knocka(site);
  site=2*(next_nbr(posx,posy,0,-2));
  knocka(site);
  site=2*(next_nbr(posx,posy,-2,-2));
  knocka(site);
  site=2*(next_nbr(posx,posy,-2,-4));
  knocka(site);


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
  printf("initialized\n");

}
