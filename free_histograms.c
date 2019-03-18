#include<stdio.h>
#include<stdlib.h>
#include "global.h"
#include "math.h"
void init_histvars(){
  freebw=0.00001;
  double maxlen=0.005;
  freebins=floor(maxlen/freebw);
  histper=(double *)calloc(freebins , sizeof(double)); errper=(double *)calloc(freebins , sizeof(double));
  histrgyr=(double *)calloc(freebins , sizeof(double));
  errrgyr=(double *)calloc(freebins , sizeof(double));
  bincounts=(double *)calloc(freebins , sizeof(double));
}

void histogram_freestats(double cvol, double cper, double crgyr){
  int i;
  int bin;
  bin=floor((1.0*cvol)/(1.0*lx*lx*freebw));
  if(bin<freebins){
    histper[bin]+=(1.0*cper);
    errper[bin]+=((double)cper*(double)cper);
    histrgyr[bin]+=crgyr;
    errrgyr[bin]+=crgyr*crgyr;
    bincounts[bin]+=1.0;
  }
  else 
    unbinned_frac+=1.0;

}
void write_freehists(){
  char fname[300];
  sprintf(fname,"./histograms/freehist_Lx%dnc%.3fSEED%d.dat",lx,nc,NUM);
  FILE *fp;
  fp=fopen(fname,"w");
  double temp,temperr;
  int i;
  printf("freebins %d\n",freebins);
  for(i=0;i<freebins;i++){
	  if(bincounts[i]>0){
    histper[i]=histper[i]/(1.0*bincounts[i]);
    errper[i]=errper[i]/(1.0*bincounts[i]);
    errper[i]=sqrt((errper[i]-histper[i]*histper[i])/(1.0*bincounts[i]));

    histrgyr[i]=histrgyr[i]/(1.0*bincounts[i]);
    errrgyr[i]=errrgyr[i]/(1.0*bincounts[i]);
    errrgyr[i]=sqrt((errrgyr[i]-histrgyr[i]*histrgyr[i])/(1.0*bincounts[i]));

    temp=bincounts[i]/(1.0*totfree);
    temperr=sqrt((temp-temp*temp)/(1.0*totfree));
    double frac=freebw/2.0+freebw*i;


    //getchar();
    fprintf(fp, "%d %f %f %f %f %f %f %f %f\n",i,freebw/2.0+freebw*i,frac*lx*lx, histper[i],errper[i],histrgyr[i],errrgyr[i],temp,temperr);
	  }
  }
  fclose(fp);

}
