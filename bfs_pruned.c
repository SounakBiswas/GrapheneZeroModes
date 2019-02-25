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
static void enqueue(int k){
  queue[tail]=k;
  tail=(tail!=0)?tail-1:ncells-1;
  queue_len++;
}
static void dequeue(){
  head=(head!=0)?head-1:ncells-1;
  queue_len--;
}
static void clear_queue(){
  head=tail=ncells-1;
  queue_len=0;
}
static int empty_queue(){
  return (queue_len==0);

}
void prune(int init_head){
  int i;
  if(head<init_head)
    for(i=head+1;i<init_head;i++)
      visited[cmatch[queue[i]]]=ncells;
  else{
    for(i=head+1;i<ncells;i++)
      visited[cmatch[queue[i]]]=ncells;
    for(i=0;i<init_head;i++)
      visited[cmatch[queue[i]]]=ncells;
  }
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
  int init_head;
  clear_queue();
  //matching=heur_mdm();
  for(col=0;col<ncells;col++){
    if(cmatch[col]==-1){
      init_head=head;
      if(bfs_phase(col,n_phase))
        matching++;
      else
        prune(init_head);
    }
    n_phase++;
  }
  free(queue);
  free(visited);
  free(parent);
  return matching;
}
