#include "global.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
void make_lattice();
void initialize();
void make_sparse();
int potfan();
int bfs();
int hkmm();
int calc_loc();
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
  fp=fopen("free_sitesA.dat","a");
  for(i=0;i<2*ncells;i+=2){
    if(ifvac[i]==4)
      fprintf(fp,"%d\n",i);
  }
  fclose(fp);
  fp=fopen("free_sitesB.dat","a");
  for(i=1;i<2*ncells;i+=2){
    if(ifvac[i]==4)
      fprintf(fp,"%d\n",i);
  }
  fclose(fp);
}
void write_edgelist(){
  FILE *fp;
  int i;
  fp=fopen("edgelist.dat","w");
  for(i=0;i<2*ncells;i+=1){
    if(ifvac[i]==5){
      if(ifvac[neigh[i][0]]!=4 && ifvac[neigh[i][0]]!=1)
	fprintf(fp,"%d %d\n",i,neigh[i][0]);
      if(ifvac[neigh[i][1]]!=4 && ifvac[neigh[i][1]]!=1)
	fprintf(fp,"%d %d\n",i,neigh[i][1]);
      if(ifvac[neigh[i][2]]!=4 && ifvac[neigh[i][2]]!=1)
	fprintf(fp,"%d %d\n",i,neigh[i][2]);
    }
  }
  fclose(fp);
}
void write_free_site(){
  FILE *fp;
  int i;
  fp=fopen("unmatched.dat","a");
  for(i=0;i<ncells;i++){
    if(cmatch[i]==-1)
      fprintf(fp,"%d\n",2*i);
    if(rmatch[i]==-1)
      fprintf(fp,"%d\n",2*i+1);
  }
  fclose(fp);
}
void main(){
  initialize();
  make_lattice();
  make_sparse();
  int i;
  int m1,m2;
  write_vacancies();
  printf("free sites=%d\n",ncells-(int)(num_vacs)-bfs());
  //printf("free sites=%d\n",ncells-(int)(num_vacs)-potfan());
  calc_loc_c();
  //getchar();
  transpose();
  printf("free sites=%d\n",ncells-(int)(num_vacs)-bfs());
  printf("free sites=%d\n",ncells-(int)(num_vacs)-potfan());
  calc_loc_r();
  write_free();
  write_edgelist();
//  for(i=0;i<100;i++){
//    clear_match();
//    write_free();
//  }
  //clear_match();
  //transpose();
  //clear_match();
  free(cmatch);
  free(rmatch);
  free(rids);
  free(cptrs);
  free(cdegree);
  free(rdegree);
}
