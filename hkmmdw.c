//Hopcroft Karp Mahajan (Karpinsky-Rytter ?? )
#include<stdlib.h>
#include<stdio.h>
#include"global.h"
#include<assert.h>

int *stack;
int *queue;
int head,tail;
int s_top;
int *visited;
int *levels;
int *lastrow;
int max_level;
int queue_len;

inline void push_stack(int k){
  s_top++;
  stack[s_top]=k;
  lastrow[k]=cptrs[k]-1;
}
inline void pop_stack(){
  s_top--;
}
inline void clear_stack(){
  s_top=-1;
}

inline void enqueue(int k){
  queue[tail]=k;
  tail=(tail!=0)?tail-1:ncells-1;
  queue_len++;
}
inline void dequeue(){
  head=(head!=0)?head-1:ncells-1;
  queue_len--;
}
inline void clear_queue(){
  head=tail=ncells-1;
  queue_len=0;
}
inline int empty_queue(){
  return (queue_len==0);

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

int bfs_combined(int n_phase){
  int rctr,row;
  int col;
  int level=0;
  int bfs_succ=0;
  int temp_tail;
  clear_queue();
  clear_stack();
  for(col=0;col<ncells;col++){
      levels[col]=-1;
    if(cmatch[col]==-1){
      enqueue(col);
    }
  }
  level=0;
  while(!empty_queue()){
    col=queue[head];
    dequeue();
    level=(cmatch[col]!=-1)?levels[cmatch[col]]:-1;
    for(rctr=cptrs[col]; rctr<cptrs[col+1]; rctr++){
      row=rids[rctr];
      if(visited[row]<n_phase){
        visited[row]=n_phase;
        levels[row]=level+1;
        if(rmatch[row]==-1){
          bfs_succ=1;
          max_level=levels[row];
        }
        else if(!bfs_succ) 
          enqueue(rmatch[row]);
      }
    }
  }
  return bfs_succ;  //no augmenting path
}

int dfs_phase(int col,int n_phase){
  int rctr,row,level;
  push_stack(col);
  int path_exists;
  while(s_top>=0){
    col=stack[s_top];
    level=(cmatch[col]!=-1)?levels[cmatch[col]]:-1;
    path_exists=0;
    for(rctr=lastrow[col]+1; rctr<cptrs[col+1]; rctr++){
      row=rids[rctr];
      lastrow[col]=rctr;
      if((visited[row]<n_phase)&&(levels[row]==level+1)){
        path_exists=1;
        break;
      }
    }
    if(path_exists){
      visited[row]=n_phase;
      if((rmatch[row]==-1)&&(levels[row]==max_level)){
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
int dfs_phase2(int col,int n_phase){
  int rctr,row,level;
  push_stack(col);
  int path_exists;
  while(s_top>=0){
    col=stack[s_top];
    path_exists=0;
    for(rctr=lastrow[col]+1; rctr<cptrs[col+1]; rctr++){
      row=rids[rctr];
      lastrow[col]=rctr;
      if(visited[row]<n_phase){
        path_exists=1;
        break;
      }
    }
    if(path_exists){
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


int hkmm(){
  int col,i;
  queue=(int*)malloc(ncells*sizeof(int));
  stack=(int*)malloc(ncells*sizeof(int));
  visited=(int*)malloc(ncells*sizeof(int));
  levels=(int*)malloc(ncells*sizeof(int));
  lastrow=(int*)malloc(ncells*sizeof(int));
  int matching=0;
  for(col=0;col<ncells;col++)
    visited[col]=-1;

  int n_phase=0;
  while(bfs_combined(n_phase)){
    n_phase++;
    for(col=0;col<ncells;col++){
      clear_stack();
      if(cmatch[col]==-1)
        matching+=dfs_phase(col,n_phase);
    }
    n_phase++;
    for(col=0;col<ncells;col++){
      clear_stack();
      if(cmatch[col]==-1)
        matching+=dfs_phase2(col,n_phase);
    }
    //printf ( "%d \n",matching );
    n_phase++;
  }
  free(queue);
  free(stack);
  free(visited);
  free(levels);
  free(lastrow);
  return matching;
}
