//Hopcroft Karp Mahajan (Karpinsky-Rytter ?? )
#include<stdlib.h>
#include<stdio.h>
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
  for(col=0;col<2*ncells;col++)
      levels[col]=-1;
  for(col=0;col<ncells;col++){
    //printf("%d %d\n",col,cmatch[col]);
    if(cmatch[col]==-1){
      enqueue(col);
      levels[2*col]=0;
    }
  }
  level=0;
  printf("hte %d %d %d\n",head,tail,queue_len);
  while(!empty_queue()){
    col=queue[head];
    dequeue();
    level=(cmatch[col]!=-1)?(levels[2*cmatch[col]+1]+1):0;
    //printf("level=%d\n",level);
    levels[2*col]=level;
    //printf("levelcol=%d\n",levels[col]);
    for(rctr=cptrs[col]; rctr<cptrs[col+1]; rctr++){
      row=rids[rctr];
      if(visited[row]<n_phase){
        visited[row]=n_phase;
        levels[2*row+1]=levels[2*col]+1;
       //printf("col row levels  %d %d %d %d %d %d\n",col, row,level,levels[col],levels[row],rmatch[row]);
        if(rmatch[row]==-1)
          bfs_succ=1;
        //else if(!bfs_succ)
        else 
          enqueue(rmatch[row]);
      }
    }

  }
  //getchar();
  return bfs_succ;  //no augmenting path
}

int dfs_phase(int col,int n_phase){
  int rctr,row,level;
  //level=-1;
  push_stack(col);
  //printf("col %d\n",col);
  //getchar();
  while(s_top>=0){
    col=stack[s_top];
    //level=(cmatch[col]!=-1)?levels[cmatch[col]]:-1;
    level=levels[2*col];
    for(rctr=lastrow[col]+1; rctr<cptrs[col+1]; rctr++){
      row=rids[rctr];
      if((visited[row]<n_phase))
        break;
    }
    lastrow[col]=rctr;
    if((visited[row]<n_phase)&&(abs(levels[2*row+1]-(levels[2*col])==1) )){
    //if((visited[row]<n_phase)&&(1 )){
      visited[row]=n_phase;
      if(rmatch[row]==-1){
        augment(row);
        return 1; //success
      }
      else{
        push_stack(rmatch[row]);
      }
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
  levels=(int*)malloc(2*ncells*sizeof(int));
  lastrow=(int*)malloc(ncells*sizeof(int));
  int matching=0;
  int temp;

  for(col=0;col<ncells;col++)
    visited[col]=-1;

  int n_phase=0;
  while(bfs_combined(n_phase)){
    n_phase++;
    for(col=0;col<ncells;col++)
      if(cmatch[col]==-1)
        matching+=dfs_phase(col,n_phase);
    printf("%d \n",matching);
    getchar();
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
