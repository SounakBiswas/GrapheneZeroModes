#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "assert.h"
int *stack;
int s_top;
int s_end;
int *visited;

int dfs_phase();
int dfs();
int heur_mdm();

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


int dfs_phase(int col2,int n_phase){
  int rctr,row;
  int col;
  int dfs_succ=0;
  s_top++;
  stack[s_top]=col2;
  assert(cmatch[col2]!=-2);


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
        dfs_succ=1;
        augment(row);
        break;
      }
      else{
        s_top++;
        stack[s_top]=rmatch[row];
      }
    }
    else{
      //if(cmatch[s_top]>=0)
      //visited[cmatch[s_top]]=ncells+1;
      s_end--;
      stack[s_end]=stack[s_top];
      s_top--;

    }

  }
  return dfs_succ;
}

int dfs(){
  int col,i;
  stack=(int*)malloc(ncells*sizeof(int));
  visited=(int*)malloc(ncells*sizeof(int));
  for(col=0;col<ncells;col++)
    visited[col]=-1;

  int n_phase=0;
  int matching=0;
  matching=heur_mdm();

  for(col=0;col<ncells;col++){
    s_top=-1;
    s_end=ncells;
    if(cmatch[col]==-1){
      if(dfs_phase(col,n_phase))
        matching++;
      else{
        for(i=s_end;i<ncells;i++)
          visited[cmatch[stack[i]]]=ncells;
      }
    }
    n_phase++;
  }
  return matching;
}
