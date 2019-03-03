#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "assert.h"
#include "math.h"
int take_stats(){
  int *pocket;
  pocket=(int*)malloc(nsites*sizeof(int));
  int i,site,site2,sublat,cell,x,y;
  int il;
  int flagn1,flagn2,flaglb,flagrb;
  char fname[200];
  char gname[200];
  sprintf(fname,"./outfiles/cstats_Lx%dnc%.3fSEED%d.dat",LX,NC,NUM);
  sprintf(gname,"./outfiles/nperc_Lx%dnc%.3fSEED%d.dat",LX,NC,NUM);
  FILE *statf=fopen(fname,"a");
  FILE *percf=fopen(gname,"a");
  
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
  size_free=0;
  int num_percolating=0;
  double rx,ry,r2,rgyr;

  for(i=0;i<nsites;i++){
    if(   (ifvac[i]!=1) && (burn[i]==-1)){
      pck_counter=clust_counter=-1;
      boundary_counter=-1;
      r2=rx=ry=0;
      flaglb=flagrb=0;
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
      int i1;
      double posx,posy;
      slat_imbalance=0;
      while(pck_counter!=-1){
        site=pocket[pck_counter];
        pck_counter--;
        sublat=site%2;
        cell=site/2;
        x=cell%lx;
        y=cell/lx;
        posx=sqrt(3)*(x-(y%2)/2.0);
        posy=1.5*y+(y%2);
        rx+= posx;
        ry+= posy;
        r2+= (posx*posx+posy*posy);
        bflag=0;
        flaglb=flaglb||((x==0));
        flagrb=flagrb||(x==(lx-1));
        flagn1=((sublat==0)&&(x==lx-1)&&(y%2==0)) || ((sublat==1)&&(x==0)&&(y%2==1));
        flagn2=((sublat==0)&&(x==0)&&(y%2==1)) || ((sublat==1)&&(x==lx-1)&&(y%2==0));
        slat_imbalance+= (2*sublat-1);
        //getchar();
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
          if((ifvac[site2]<=0) &&(burn[site2]==-1) && (!flagn1)){
            pck_counter++;
            pocket[pck_counter]=site2;
            clust_counter++;
            burn[site2]=n_clust;
          }
          else 
            bflag= bflag||(ifvac[site2]!=1)&&(burn[site2]!=n_clust);

          site2=neigh[site][2];
          if( (ifvac[site2]<=0) &&(burn[site2]==-1) && (!flagn2)){
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
          if((ifvac[site2]==3) &&(burn[site2]==-1)&& (!flagn1)){
            pck_counter++;
            //printf("padd\n");
            pocket[pck_counter]=site2;
            clust_counter++;
            burn[site2]=n_clust;
          }
          else 
            bflag= bflag||(ifvac[site2]!=1)&&(burn[site2]!=n_clust);

          site2=neigh[site][2];
          if( (ifvac[site2]==3) &&(burn[site2]==-1)&& (!flagn2)){
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
          if((ifvac[site2]==2) &&(burn[site2]==-1)&& (!flagn1)){
            pck_counter++;
            pocket[pck_counter]=site2;
            clust_counter++;
            burn[site2]=n_clust;
          }
          else 
            bflag= bflag||(ifvac[site2]!=1)&&(burn[site2]!=n_clust);

          site2=neigh[site][2];
          if( (ifvac[site2]==2) &&(burn[site2]==-1)&& (!flagn2)){
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
      num_percolating+= (flaglb&&flagrb);
      rx=rx/(1.0+clust_counter);
      ry=ry/(1.0+clust_counter);
      r2=r2/(1.0+clust_counter);
      rgyr=sqrt(r2-(rx*rx+ry*ry));

      //if(flaglb&&flagrb)
      //  printf("percolating; type: %d %d\n",ctype,n_clust);
      
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
  fprintf(percf,"%d\n",num_percolating);
  printf("percolating clusts: %d\n",num_percolating);
  assert(2*(ncells-num_vacs)==testcsize);
  fclose(statf);
  fclose(percf);
  free(pocket);
  return n_clust;
}
