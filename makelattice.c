#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#define  next_nbr(ii,jj,xx,yy)  ((xx+ii+lx)%lx + ((yy+jj+ly)%ly)*lx)
/* ********************************** 
1  2
\ /
 B 
 |
 0

 0
 |
 A
/ \
2  1

Edges are marked as 3*cell+j,j={0,1,2}, with reference being on A sublattice


* *********************************** */
void remove_site(int site);
void make_lattice(){
  int i,j,k;
  int cell;
  int x,y;
  for(cell=0;cell<ncells;cell++){
    y=cell/lx;
    x=cell%lx;
    neigh[2*cell][0]=2*cell+1;
    neigh[2*cell][1]=2*next_nbr(x,y,0,-1)+1;
    neigh[2*cell][2]=2*next_nbr(x,y,-1,-1)+1;

    neigh[2*cell+1][0]=2*cell;
    neigh[2*cell+1][1]=2*next_nbr(x,y,0,1);
    neigh[2*cell+1][2]=2*next_nbr(x,y,1,1);
  
  
  }
  int ifvac[NSITES];
  for(i=0;i<NSITES;i++)
    ifvac[i]=0;
  int num_vacs=nc*ncells;
  int sitea,siteb;

  for(i=0;i<num_vacs;i++){
    sitea=(int)((rand()/(RAND_MAX+1.0))*ncells)*2;
    if(ifvac[sitea]==0){
      ifvac[sitea]=1;
      remove_site(sitea);
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
      ifvac[siteb]=1;
      remove_site(siteb);
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


}

void remove_site(int site){
  int nbr;
//  printf("%d\n",site);
  if(site%2){
   nbr=neigh[site][0];
   capacity[3*nbr/2]=0;
   nbr=neigh[site][1];
   capacity[3*nbr/2+1]=0;
   nbr=neigh[site][2];
   capacity[3*nbr/2+2]=0;
  }
  else{
    capacity[3*site/2]=0;
    capacity[3*site/2+1]=0;
    capacity[3*site/2+2]=0;
  }
}
