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

void augment(int row){
  int temp;
  int col;
  while(1){
    col=parent[row];
    temp=cmatch[col];
    cmatch[col]=row;
    rmatch[row]=col;
    row=temp;
    if(temp==-1)
      break;
  }
  clear_queue();
}


int bfs_phase(int col,int n_phase){
  int rctr,row;
  enqueue(col);
  while(!empty_queue()){
    col=queue[head];
    dequeue();
    for(rctr=cptrs[col]; rctr<cptrs[col+1]; rctr++){
      row=rids[rctr];
      if(visited[row]<n_phase){
        visited[row]=n_phase;
        parent[row]=col;
        if(rmatch[row]==-1){
          augment(row);
          return 1;
        }
        else
          enqueue(rmatch[row]);
      }
    }

  }
  return 0;  //no augmenting path
}

int bfs(){
  int col,i;
  queue=(int*)malloc(ncells*sizeof(int));
  visited=(int*)malloc(ncells*sizeof(int));
  parent=(int*)malloc(ncells*sizeof(int));
  for(col=0;col<ncells;col++)
    visited[col]=-1;
  int n_phase=0;
  int matching=0;
  matching=heur_mdm();
  clear_queue();
  for(col=0;col<ncells;col++){
    if(cmatch[col]==-1)
      matching+=bfs_phase(col,n_phase);
    n_phase++;
  }
  free(queue);
  free(visited);
  free(parent);
  return matching;
}
