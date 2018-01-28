#include "global.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
void depth_first_visit(int i);
int depth_first();
void augment_flow();
int ford_fulkerson();

void depth_first_visit(int node){
  int next_node,edge;
  int i;
  int cell;
  color[node]=1;
//  printf("node=%d \n",node);
  if(node==nsites+1){
    color[node]=2;
    return;

  }

  if(node==nsites){
    for(cell=0;cell<ncells;cell++){
      edge=3*ncells+cell;
  //    printf("cell=%d \n",cell);
      next_node=2*cell;
      if((capacity[edge]-flow[edge])&&(color[next_node]==0)){
        depth_first_visit(next_node);
        pred[next_node]=node;
      }
      if(color[nsites+1]==2)
        return;
    }
    color[node]=2;
  }
  else if(node%2==0){
    int n1,n2,n3;
    for(i=0;i<3;i++){
      cell=node/2;
      edge=3*cell+i;
      next_node=neigh[node][i];
      //printf("c %d n %d nc %d nn %d \n",cell,node,next_node/2,next_node);
    //  printf("c %d n %d  \n",cell,next_node/2);
    //  printf("%d  %d  %d \n",capacity[edge],flow[edge],color[next_node]);
    //  printf("nb %d %d %d\n",neigh[node][0]/2,neigh[node][1]/2,neigh[node][2]/2);

      if((capacity[edge]-flow[edge])&&(color[next_node]==0)){
        depth_first_visit(next_node);
        pred[next_node]=node;
      }
      if(color[nsites+1]==2)
        return;
    }
   // printf("done\n");
    color[node]=2;
  }
  else if(node%2==1){
    edge=4*ncells+node/2;
    next_node=nsites+1;
    if((capacity[edge]-flow[edge])&&(color[next_node]==0)){
      depth_first_visit(next_node);
      pred[next_node]=node;
    }
    if(color[nsites+1]==2)
      return;
    for(i=0;i<3;i++){
      cell=neigh[node][i]/2;
      edge=3*cell+i;
      next_node=neigh[node][i];
     // printf("oc %d n %d  \n",node/2,next_node/2);
     // printf("o%d  %d  %d \n",capacity[edge],flow[edge],color[next_node]);
     // printf("onb %d %d %d\n",neigh[node][0]/2,neigh[node][1]/2,neigh[node][2]/2);
      if((flow[edge])&&(color[next_node]==0)){
        depth_first_visit(next_node);
        pred[next_node]=node;

      }
      if(color[nsites+1]==2)
        return;
    }
    color[node]=2;
  }

  return;

}

int depth_first(){
  int i;
  dfs_success=0;
  for(i=0;i<nsites+2;i++){
    color[i]=0;
    pred[i]=-1;
  }
  depth_first_visit(nsites);
  return color[nsites+1];
}

void augment_flow(){
  int current,prev,diff,edge;
  int xc,yc,xp,yp;
  aug++;
  current=nsites+1;
  prev=pred[current];
  edge=4*ncells+prev/2;
  flow[edge]+=1;
  current=prev;
  while(current!=nsites){
    prev=pred[current];
    if(neigh[prev][0]==current)
      diff=0;
    else if(neigh[prev][1]==current)
      diff=1;
    else diff=2;
    if(prev==nsites){
      edge=3*ncells+current/2;
      flow[edge]+=1;
    }
    else if(current%2){
      edge=3*(prev/2)+diff;       
      assert(flow[edge]==0);
      flow[edge]+=1;
    }
    else{
      edge=3*(current/2)+diff;   
      assert(flow[edge]==1);
      flow[edge]-=1;
    }
    current=prev;
  }
 // printf("\n");
 // getchar();

}

int ford_fulkerson(){
  int i;
  int j;
  int max_match=0;
  while(depth_first()==2){
    augment_flow();
   max_match=0;
  for(i=3*ncells;i<4*ncells;i++)
    max_match+=flow[i];
  }

  max_match=0;
  for(i=0;i<3*ncells;i++)
    max_match+=flow[i];
  return max_match;
}

