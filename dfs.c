#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "assert.h"
int *stack;
int s_top;
int *visited;

void dfs_phase();
void dfs();

void augment(int row){
  int temp;
  aug++;
  //  printf("augment path :");
  while(s_top>=0){
  //  printf("%d %d ",row,stack[s_top]);
    temp=cmatch[stack[s_top]];
    cmatch[stack[s_top]]=row;
    rmatch[row]=stack[s_top];
    row=temp;
    s_top--;
  }
 // printf("\n ");
//  getchar();
 // int i;
  //for(i=0;i<ncells;i++)
  //printf("%d rm %d  cm %d \n",i,rmatch[i],cmatch[i]);
  //getchar();
}


void dfs_phase(int col2,int n_phase){
  int rctr,row;
  int col;
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
   // printf("%d %d %d %d %d %d\n",col2,col,row,visited[row],n_phase,s_top);
    //getchar();
    if(visited[row]<n_phase){
      visited[row]=n_phase;
      if(rmatch[row]==-1){
        //printf("augment %d \n",row);
        augment(row);
        break;
      }
      else{
        s_top++;
        stack[s_top]=rmatch[row];
      }
    }
    else{
      s_top--;

    }

  }
}

void dfs(){
  int col,i;
  stack=(int*)malloc(ncells*sizeof(int));
  visited=(int*)malloc(ncells*sizeof(int));
  for(col=0;col<ncells;col++)
    visited[col]=-1;

  int n_phase=0;

  for(col=0;col<ncells;col++){
  s_top=-1;
    //printf("called col=%d \n",col);
    if(cmatch[col]==-1){
      dfs_phase(col,n_phase);
    }
    n_phase++;
  }
  //for(i=0;i<ncells;i++)
  //printf("%d rm %d  cm %d \n",i,rmatch[i],cmatch[i]);
  //getchar();
}
