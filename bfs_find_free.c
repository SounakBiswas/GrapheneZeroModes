#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "assert.h"
int *queue;
int head,tail;
int *visited;
int *parent;
int queue_len;

int heur_sgm();
int heur_mdm();
int bfs_phase();
int bfs();
static inline void enqueue(int k){
  queue[tail]=k;
  tail=(tail!=0)?tail-1:ncells-1;
  queue_len++;
}
static inline void dequeue(){
  head=(head!=0)?head-1:ncells-1;
  queue_len--;
}
static inline void clear_queue(){
  head=tail=ncells-1;
  queue_len=0;
}
static inline int empty_queue(){
  return (queue_len==0);

}


int bfs_find_c(int col,int n_phase){
  int rctr,row;
  enqueue(col);
  while(!empty_queue()){
    col=queue[head];
    ifvac[2*col]=4;
    dequeue();
    for(rctr=cptrs[col]; rctr<cptrs[col+1]; rctr++){
      row=rids[rctr];
      ifvac[2*row+1]=5;
      if(visited[row]<n_phase){
        visited[row]=n_phase;
	if(rmatch[row]!=-1)
          enqueue(rmatch[row]);
      }
    }

  }
  return 0;  //no augmenting path
}
int bfs_find_r(int col,int n_phase){
  int rctr,row;
  enqueue(col);
  while(!empty_queue()){
    col=queue[head];
    ifvac[2*col+1]=4;
    dequeue();
    for(rctr=cptrs[col]; rctr<cptrs[col+1]; rctr++){
      row=rids[rctr];
      ifvac[2*row]=5;
      if(visited[row]<n_phase){
        visited[row]=n_phase;
	if(rmatch[row]!=-1)
        enqueue(rmatch[row]);
      }
    }

  }
  return 0;  //no augmenting path
}

int calc_loc_c(){
  int col,i;
  queue=(int*)malloc(ncells*sizeof(int));
  visited=(int*)malloc(ncells*sizeof(int));
  parent=(int*)malloc(ncells*sizeof(int));
  for(col=0;col<ncells;col++)
    visited[col]=-1;
  int n_phase=0;
  int matching=0;
  clear_queue();
  for(col=0;col<ncells;col++){
    if(cmatch[col]==-1){
       bfs_find_c(col,n_phase);
    }
    n_phase++;
  }
  free(queue);
  free(visited);
  free(parent);
  return matching;
}
int calc_loc_r(){
  int col,i;
  queue=(int*)malloc(ncells*sizeof(int));
  visited=(int*)malloc(ncells*sizeof(int));
  parent=(int*)malloc(ncells*sizeof(int));
  for(col=0;col<ncells;col++)
    visited[col]=-1;
  int n_phase=0;
  int matching=0;
  clear_queue();
  for(col=0;col<ncells;col++){
    if(cmatch[col]==-1)
       bfs_find_r(col,n_phase);
    n_phase++;
  }
  free(queue);
  free(visited);
  free(parent);
  return matching;
}
