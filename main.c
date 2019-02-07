#include "global.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
void make_lattice();
void initialize();
void make_sparse();
int potfan();
int bfs();
int hkmm();
void write_vacancies(){
  FILE *fp;
  int i;
  fp=fopen("vacancies.dat","w");
  for(i=0;i<2*ncells;i++)
    if(ifvac[i]==1)
    fprintf(fp,"%d\n",i);
  fclose(fp);
}
void write_free(){
  FILE *fp;
  int i;
  fp=fopen("free_sites.dat","a");
  for(i=0;i<ncells;i++){
    if(rmatch[i]==-1)
      fprintf(fp,"%d\n",2*i+1);
  }
  for(i=0;i<ncells;i++){
    if(cmatch[i]==-1)
      fprintf(fp,"%d\n",2*i);
  }
  fclose(fp);
}
void main(){
  initialize();
  make_lattice();
  make_sparse();
  clock_t start,end;
  int i;
  write_vacancies();
  start=clock();
  printf("free sites=%d\n",ncells-(int)(num_vacs)-bfs());
  end=clock();
  printf("time taken: %lf",(double)(end-start)/(1.0*CLOCKS_PER_SEC));
  write_free();
  free(cmatch);
  free(rmatch);
  free(rids);
  free(cptrs);
  free(cdegree);
  free(rdegree);
}
