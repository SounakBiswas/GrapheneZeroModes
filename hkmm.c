//Hopcroft Karp Mahajan (Karpinsky-Rytter ?? )
#include<stdlib.h>
#include"global.h"

int *stack;
int *queue;
int head,tail;
int s_top;
int *visited;
int *parent;
int *levels;
int *lastrow;
int max_level;

inline void push_stack(int k){
  s_top++;
  stack[s_top]=k;
}
inline void pop_stack(){
  s_top--;
}
inline void clear_stack(){
  s_top=-1;
}

inline void enqueue(int k){
  tail=(tail!=0)?tail-1:ncells-1;
  queue[tail]=k;
}
inline void dequeue(){
  head=(head!=0)?head-1:ncells-1;
}
inline void clear_queue(){
  head=ncells-1;
  tail=0;
}
inline int empty_queue(){
  return (tail!=0)?(head==tail-1):(head==ncells-1);

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
      push(col);
    }
  }
  level=0;
  while(!empty_queue()){
    col=queue[head];
    dequeue();
    level=(cmatch[col]!=-1)?level[cmatch[col]]:-1;
    for(rctr=cptrs[col]; rctr<cptrs[col+1]; rctr++){
      row=rids[rctr];
      if(visited[row]<n_phase){
        visited[row]=n_phase;
        levels[row]=level+1;
        if(rmatch[row]==-1)
          return 1;
        else
          enqueue(rmatch[row]);
      }
    }

  }
  return 0;  //no augmenting path
}

int dfs_phase(int n_phase){
  int rctr,row;
  int col;
  level=-1;
  while(s_top>=0){
    col=stack[s_top];
    for(rctr=cptrs[col]; rctr<cptrs[col+1]; rctr++){
      row=rids[rctr];
      if((visited[row]<n_phase))
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



int hkmm(){
  int col,i;
  queue=(int*)malloc(ncells*sizeof(int));
  stack=(int*)malloc(ncells*sizeof(int));
  visited=(int*)malloc(ncells*sizeof(int));
  parent=(int*)malloc(ncells*sizeof(int));
  levels=(int*)malloc(ncells*sizeof(int));
  lastrow=(int*)malloc(ncells*sizeof(int));
  int matching=0;

  for(col=0;col<ncells;col++)
    visited[col]=-1;
  int n_phase=0;
  while(bfs_combined(n_phase)){
    n_phase++;
    matching+=dfs_phase(n_phase);
    n_phase++;
  }
  free(queue);
  free(stack);
  free(visited);
  free(parent);
  free(levels);
  free(lastrow);
  return matching;
}
