#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "assert.h"
int take_stats(){
  int pocket[NSITES];
  int cluster[NSITES];
  int i,site,site2,sublat,cell,x;
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
  int num_clusts[3]={0,0,0};
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
        int i1;
      while(pck_counter!=-1){
        site=pocket[pck_counter];
        pck_counter--;
        sublat=site%2;
        cell=site/2;
        x=cell%lx;
        bflag=0;
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
          if((ifvac[site2]<=0) &&(burn[site2]==-1)){
            pck_counter++;
            pocket[pck_counter]=site2;
            clust_counter++;
            burn[site2]=n_clust;
          }
          else 
            bflag= bflag||(ifvac[site2]!=1)&&(burn[site2]!=n_clust);
        if(n_clust==5)

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
      if(ctype!=0)
      fprintf(statf,"%d %d %d %d\n",n_clust,ctype,clust_counter+1,boundary_counter+1);
      n_clust++;

    }
  }
  printf("cluster counts :total %d,free %d, RA=%d, RB=%d\n",n_clust,num_clusts[0],num_clusts[1],num_clusts[2]);
  printf("total sites %d %d lx=%d\n ",2*(ncells-num_vacs),testcsize,lx);
  assert(2*(ncells-num_vacs)==testcsize);
  fclose(statf);
  return n_clust;
}
