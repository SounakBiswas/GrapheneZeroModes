
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
    for(rctr=cptrs[col]; rctr<cptrs[col+1]; rctr++){
      row=rids[rctr];
      
      if(visited[row]<n_phase){
        visited[row]=n_phase;
        if(rmatch[row]==-1){
          max_level=levels[col];
          return 1;
        }
        else{
          enqueue(rmatch[row]);
          levels[rmatch[row]]=levels[col]+1;
        }
      }
    }

  }
  return 0;  //no augmenting path
}
