#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "assert.h"
int *stack;
int s_top;
int *visited;

int heur_mdm();
int dfs_phase();
int dfs();
static inline void push_stack(int k){
  s_top++;
  stack[s_top]=k;
}
static inline void pop_stack(){
  s_top--;
}
static inline void clear_stack(){
  s_top=-1;
}

void augment(int row){
  int temp;
  while(s_top>=0){
    temp=cmatch[stack[s_top]];
    cmatch[stack[s_top]]=row;
    rmatch[row]=stack[s_top];
    row=temp;
    s_top--;
  }
}


int dfs_phase(int col,int n_phase){
  int rctr,row;
  push_stack(col);
  while(s_top>=0){
    col=stack[s_top];
    for(rctr=cptrs[col]; rctr<cptrs[col+1]; rctr++){
      row=rids[rctr];
      if(visited[row]<n_phase)
        break;
    }
    if(visited[row]<n_phase){
      visited[row]=n_phase;
      if(rmatch[row]==-1){
        augment(row);
        return 1; //success
      }
      else
        push_stack(rmatch[row]);
      
    }
    else
      pop_stack();

  }
  return 0;  //no augmenting path
}

int dfs(){
  int col,i;
  stack=(int*)malloc(ncells*sizeof(int));
  visited=(int*)malloc(ncells*sizeof(int));
  for(col=0;col<ncells;col++)
    visited[col]=-1;
  int n_phase=0;
  int matching=0;
  clear_stack();
  //matching=heur_sgm();
  matching=heur_mdm();
  printf("heuristic match= %d\n",matching);
  for(col=0;col<ncells;col++){
    if(cmatch[col]==-1)
      matching+=dfs_phase(col,n_phase);
    n_phase++;
  }
  return matching;
}
