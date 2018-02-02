#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "assert.h"
int *stack;
int s_top;
int *visited;
int *lookahead;

int heur_sgm();
int heur_mdm();
int potfan_phase(int);
int pf_dfs(int,int);
int potfan();
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
void shuffle_unmatched(){
  int temp;
  int k1,k2;
  int i;
  for(i=0;i<freecol;i++){
    k1=rand()%freecol;
    k2=rand()%freecol;
    temp=unmatched[k1];
    unmatched[k1]=unmatched[k2];
    unmatched[k2]=temp;
  }

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


int pf_dfs(int col,int n_phase){
  int rctr,row,i;
  push_stack(col);
  while(s_top>=0){
    col=stack[s_top];
    for(i=0;i<cdegree[col];i++){
      if(rmatch[rids[cptrs[col]+i]]==-1){
        lookahead[col]=i;
        break;
      }
      else lookahead[col]=cdegree[col];
    }
    if(lookahead[col]<cdegree[col]) row=rids[cptrs[col]+lookahead[col]];
    else{
      if(n_phase/2){
        for(rctr=cptrs[col]; rctr<cptrs[col+1]; rctr++){
          row=rids[rctr];
          if(visited[row]<n_phase)
            break;
        }
      }
      else{
        for(rctr=cptrs[col+1]-1; rctr>=cptrs[col]; rctr--){
          row=rids[rctr];
          if(visited[row]<n_phase)
            break;
        }
      }
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


int potfan_phase(int n_phase){
  int i,k,col,temp;
  int aug=0;
  clear_stack();
  for(i=0;i<freecol;i++){
    col=unmatched[i];
    aug+=pf_dfs(col,n_phase);
  }
  k=0;
  for(i=0;i<freecol;i++){
    col=unmatched[i];
    if(cmatch[col]==-1){
      unmatched[k]=col;
      k++;
    }
  }
  freecol-=aug;
  //assert(k==freecol);
  return aug;
}


int potfan(){
  int i,col,aug;
  int n_phase=0;
  int matching=0;
  stack=(int*)malloc(ncells*sizeof(int));
  visited=(int*)malloc(ncells*sizeof(int));
  lookahead=(int*)malloc(ncells*sizeof(int));

  //matching=heur_mdm();
  freecol=ncells-(int)(num_vacs)-matching;
  unmatched=(int*)malloc(freecol*sizeof(int));
  i=0;
  for(col=0;col<ncells;col++){
    visited[col]=-1;
    lookahead[col]=0;
    if(cmatch[col]==-1){
      unmatched[i]=col;
      i++;
    }
  }
  shuffle_unmatched();
  printf("%d %d \n",i,freecol);
  assert(i==freecol);
  do{
    aug=potfan_phase(n_phase);
    matching+=aug;  
    n_phase++;
  }while(aug>0);
  
  free(stack);
  free(visited);
  free(lookahead);
 
  return matching;
}
