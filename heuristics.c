#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "assert.h"

int heur_sgm();
int heur_mdm();
static inline void match(int col,int row){
  cmatch[col]=row;
  rmatch[row]=col;
}


int heur_sgm(){
  int i,col,row;
  int nmatch=0;

  for(col=0;col<ncells;col++){
    if(cdegree[col]>0 && cmatch[col]==-1){
      for(i=0; i<cdegree[col]; i++){
        row=rids[cptrs[col]+i];
        if(rmatch[row]==-1){
          match(col,row);
          nmatch++;
          break;
        }
      }
    }
  }
  return nmatch;
}


int heur_mdm(){
  int col,row;
  int nmatch=0;

  for(col=0;col<ncells;col++){
    if(cdegree[col]==1 && cmatch[col]==-1){
      row=rids[cptrs[col]];
      if(rmatch[row]==-1){
        match(col,row);
        nmatch++;
      }
    }
  }
  for(col=0;col<ncells;col++){
    if(cdegree[col]==2 && cmatch[col]==-1){
      row=(rdegree[rids[cptrs[col]]]>rdegree[rids[cptrs[col]+1]])? rids[cptrs[col]+1]:rids[cptrs[col]];
      if(rmatch[rids[cptrs[col]]]!=-1) row=rids[cptrs[col]+1];
      if(rmatch[rids[cptrs[col]+1]]!=-1) row=rids[cptrs[col]];      
      if(rmatch[row]==-1){
        match(col,row);
        nmatch++;
      }
    }
  }
  for(col=0;col<ncells;col++){
    if(cdegree[col]==3 && cmatch[col]==-1){
      row=(rdegree[rids[cptrs[col]]]>rdegree[rids[cptrs[col]+1]])? rids[cptrs[col]+1]:rids[cptrs[col]];
      row=(row>rdegree[rids[cptrs[col]+2]])? rids[cptrs[col]+2]:row;

      if(row==rids[cptrs[col]] && rmatch[rids[cptrs[col]]]!=-1){
        row=(rdegree[rids[cptrs[col]+1]]>rdegree[rids[cptrs[col]+2]])? rids[cptrs[col]+2]:rids[cptrs[col]+1];
        if(rmatch[rids[cptrs[col]+1]]!=-1) row=rids[cptrs[col]+2];
        if(rmatch[rids[cptrs[col]+2]]!=-1) row=rids[cptrs[col]+1];      
      } 

      if(row==rids[cptrs[col]+1] && rmatch[rids[cptrs[col]+1]]!=-1){
        row=(rdegree[rids[cptrs[col]]]>rdegree[rids[cptrs[col]+2]])? rids[cptrs[col]+2]:rids[cptrs[col]];
        if(rmatch[rids[cptrs[col]]]!=-1) row=rids[cptrs[col]+2];
        if(rmatch[rids[cptrs[col]+2]]!=-1) row=rids[cptrs[col]];      
      } 

      if(row==rids[cptrs[col]+2] && rmatch[rids[cptrs[col]+2]]!=-1){
        row=(rdegree[rids[cptrs[col]]]>rdegree[rids[cptrs[col]+1]])? rids[cptrs[col]+1]:rids[cptrs[col]];
        if(rmatch[rids[cptrs[col]]]!=-1) row=rids[cptrs[col]+1];
        if(rmatch[rids[cptrs[col]+1]]!=-1) row=rids[cptrs[col]];      
      } 

      if(rmatch[row]==-1){
        match(col,row);
        nmatch++;
      }
    }
  }

  return nmatch;
}
