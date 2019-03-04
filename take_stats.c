#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "assert.h"
#include "math.h"
void getr(int x,int y,int sublat,int x0,int y0,int sublat0,double *rx,double *ry){
  double minr=4.0*lx;
  int i,j;
  int signx=(x0>=x)-(x>=x0);
  int signy=(y0>=y)-(y>=y0);
  int xd[2]={x-x0,signx*lx+(x-x0)};
  int yd[2]={y-y0,signy*ly+(y-y0)};
  double xdis,ydis;
  double r;
  for(i=0;i<=2;i++)
  for(j=0;j<=2;i++){
     ydis=yd[j]*1.5 +sublat-sublat0;
     xdis=sqrt(3)*(xd[i]-yd[j]/2.0);
     r=(xdis*xdis+ydis*ydis);
     if(r<minr){
       *rx=xdis;
       *ry=ydis;
     }
  }
}
int take_stats(){
  int *pocket;
  pocket=(int*)malloc(nsites*sizeof(int));
  int i,site,site2,sublat,cell,x,y;
  int il;
  char fname[200];
  sprintf(fname,"./outfiles/cstats_Lx%dnc%.3fSEED%d.dat",LX,NC,NUM);
  FILE *statf=fopen(fname,"a");

  il=0;
  for (il=0;il<nsites;il++){
    burn[il]=-1;
  }

  int count_free,count_ra,count_rb;
  count_free=count_ra=count_rb=0;
  int n_clust=0;
  int ctype=0;
  int pck_counter,clust_counter,boundary_counter;
  int bflag;
  int testcsize=0;
  int sumi=0;
  int num_clusts[3]={0,0,0};
  int slat_imbalance;
  size_free=0.0;
  double rgyr;
  double rx,ry,r2;
  int x0,y0,sublat0;
  double posx,posy;

  for(i=0;i<nsites;i++){
    if(   (ifvac[i]!=1) && (burn[i]==-1)){
      pck_counter=clust_counter=-1;
      boundary_counter=-1;
      if(ifvac[i]<=0)
        ctype=0;
      else if(ifvac[i]==2){
        if(i%2)
          ctype=2;
        else
          ctype=1;
      }
      else if(ifvac[i]==3){
        if(i%2)
          ctype=1;
        else
          ctype=2;
      }
      num_clusts[ctype]+=1;
      pck_counter++;
      pocket[pck_counter]=i;
      clust_counter++;
      burn[i]=n_clust;
      slat_imbalance=0;
      rx=ry=r2=0;
      x0=(i/2)%lx;
      y0=(i/2)/lx;
      sublat0=i%2;
      while(pck_counter!=-1){
        site=pocket[pck_counter];
        pck_counter--;
        sublat=site%2;
        cell=site/2;
        x=cell%lx;
        y=cell/lx;
        bflag=0;
        slat_imbalance+= (2*sublat-1);
        getr(x,y,sublat,x0,y0,sublat0,&posx,&posy);
        rx+=posx;
        ry+=posy;
        r2+= posx*posx+posy*posy;
        if(ifvac[site]<=0){  //free clusters
          site2=neigh[site][0];
          if( (ifvac[site2]<=0) &&(burn[site2]==-1)){
            pck_counter++;
            pocket[pck_counter]=site2;
            clust_counter++;
            burn[site2]=n_clust;
          }
          else 
            bflag= bflag||(ifvac[site2]!=1)&&(burn[site2]!=n_clust);

          site2=neigh[site][1];
          if((ifvac[site2]<=0) &&(burn[site2]==-1)){
            pck_counter++;
            pocket[pck_counter]=site2;
            clust_counter++;
            burn[site2]=n_clust;
          }
          else 
            bflag= bflag||(ifvac[site2]!=1)&&(burn[site2]!=n_clust);

          site2=neigh[site][2];
          if( (ifvac[site2]<=0) &&(burn[site2]==-1)){
            pck_counter++;
            pocket[pck_counter]=site2;
            clust_counter++;
            burn[site2]=n_clust;
          }
          else 
            bflag= bflag||(ifvac[site2]!=1)&&(burn[site2]!=n_clust);

        }

        if(ifvac[site]==2){  //R-motifs
          site2=neigh[site][0];
          if( (ifvac[site2]==3) &&(burn[site2]==-1)){
            pck_counter++;
            pocket[pck_counter]=site2;
            clust_counter++;
            burn[site2]=n_clust;
          }
          else 
            bflag= bflag||(ifvac[site2]!=1)&&(burn[site2]!=n_clust);

          site2=neigh[site][1];
          if((ifvac[site2]==3) &&(burn[site2]==-1)){
            pck_counter++;
            //printf("padd\n");
            pocket[pck_counter]=site2;
            clust_counter++;
            burn[site2]=n_clust;
          }
          else 
            bflag= bflag||(ifvac[site2]!=1)&&(burn[site2]!=n_clust);

          site2=neigh[site][2];
          if( (ifvac[site2]==3) &&(burn[site2]==-1)){
            pck_counter++;
            //printf("padd\n");
            pocket[pck_counter]=site2;
            clust_counter++;
            burn[site2]=n_clust;
          }
          else 
            bflag= bflag||(ifvac[site2]!=1)&&(burn[site2]!=n_clust);

        }

        if(ifvac[site]==3){  //R-motifs
          site2=neigh[site][0];
          if( (ifvac[site2]==2) &&(burn[site2]==-1)){
            pck_counter++;
            pocket[pck_counter]=site2;
            clust_counter++;
            burn[site2]=n_clust;
          }
          else 
            bflag= bflag||(ifvac[site2]!=1)&&(burn[site2]!=n_clust);

          site2=neigh[site][1];
          if((ifvac[site2]==2) &&(burn[site2]==-1)){
            pck_counter++;
            pocket[pck_counter]=site2;
            clust_counter++;
            burn[site2]=n_clust;
          }
          else 
            bflag= bflag||(ifvac[site2]!=1)&&(burn[site2]!=n_clust);

          site2=neigh[site][2];
          if( (ifvac[site2]==2) &&(burn[site2]==-1)){
            pck_counter++;
            pocket[pck_counter]=site2;
            clust_counter++;
            burn[site2]=n_clust;
          }
          else 
            bflag= bflag||(ifvac[site2]!=1)&&(burn[site2]!=n_clust);

        }
        boundary_counter+=bflag;

      }
      testcsize+= (clust_counter+1);
      rx=rx/(clust_counter+1.0);
      ry=ry/(clust_counter+1.0);
      r2=r2/(clust_counter+1.0);
      rgyr=sqrt(r2-rx*rx-ry*ry);
      if(ctype!=0)
        fprintf(statf,"%d %d %d %d %d %f\n",n_clust,ctype,clust_counter+1,boundary_counter+1,slat_imbalance,rgyr);
      else
        size_free+=(clust_counter+1.0);
      n_clust++;
      sumi+=abs(slat_imbalance);

    }
  }
  printf("cluster counts :total %d,free %d, RA=%d, RB=%d\n",n_clust,num_clusts[0],num_clusts[1],num_clusts[2]);
  printf("total sites %d %d lx=%d simb %d\n ",2*(ncells-num_vacs),testcsize,lx,sumi);
  assert(2*(ncells-num_vacs)==testcsize);
  fclose(statf);
  free(pocket);
  return n_clust;
}
