#include "global.h"
#include <stdlib.h>
#include <stdio.h> 
#include <assert.h>
#include <time.h>
#include <math.h> 
void make_lattice(); 
void initialize();
void make_sparse();
int potfan();
int bfs();
int hkmm();
void transpose();
int calc_loc_c();
int calc_loc_r();
int take_stats();
int dfs();
void allocate_arrays();
void free_arrays();
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
  double av_fs,av_fs2,sfree,sfree2;
  av_fs=av_fs2=sfree=sfree2=0;
  initialize();
  allocate_arrays();
  make_lattice();
  sprintf(outloc,"./outfiles/");
  char fname[200];
  sprintf(fname,"%sLx%dnc%.3fSEED%d.dat",outloc,LX,NC,NUM);
  char gname[200];
  sprintf(gname,"%sslinesLx%dnc%.3fSEED%d.dat",outloc,LX,NC,NUM);
  clock_t start,end;
  int i;
  int temp;
  FILE *fp;
  start=clock();
  for (i=0;i<n_realizations;i++){
    make_sparse();
    temp=ncells-(int)(num_vacs)-bfs();
    printf("free: %d\n",temp);
    calc_loc_c();
    transpose();
    calc_loc_r();
    statlines[i]=take_stats();
    av_fs+=temp;
    av_fs2+=(temp*temp);
    sfree+=size_free;
    sfree2+=(size_free*size_free);
    printf("realization=%d time taken: %lf\n",i,(double)(clock()-start)/(1.0*CLOCKS_PER_SEC));
  }
  free_arrays();
  end=clock();
  printf("time taken: %lf\n",(double)(end-start)/(1.0*CLOCKS_PER_SEC));

  av_fs2=av_fs2/(1.0*ncells*ncells*n_realizations);
  av_fs=av_fs/(1.0*ncells*n_realizations);
  sfree2=sfree2/(1.0*ncells*ncells*n_realizations);
  sfree=sfree/(1.0*ncells*n_realizations);
  fp=fopen(fname,"w");
  fprintf(fp,"%d %.16f %.16f %.16f %.16f %.16f",lx,nc,av_fs,sqrt((av_fs2-av_fs*av_fs)/(1.0*n_realizations)),sfree,sqrt((sfree2-sfree*sfree)/(1.0*n_realizations)));
  fclose(fp);
  fp=fopen(gname,"w");
  for(i=0;i<NR;i++)
    fprintf(fp,"%d \n",statlines[i]);
  fclose(fp);
}
