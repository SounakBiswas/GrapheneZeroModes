#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "assert.h"
void take_stats(){
  int pocket[NSITES];
  int cluster[NSITES];
  int i,site,site2,sublat,cell,x;
  FILE * fp;
  fp=fopen("log.dat","w");
  int il;
  
  for (il=0;il<nsites;il++){
    fprintf(fp,"%d\n",il);
    burn[il]=-1;
  }

  int count_free,count_ra,count_rb;
  count_free=count_ra=count_rb=0;
  int n_clust=0;
  int pck_counter,clust_counter;
  for(i=0;i<nsites;i++){
    if(   (ifvac[i]!=1) && (burn[i]==-1)){
      pck_counter=clust_counter=-1;
      if(ifvac[i]<=0)
        count_free++;
      else if(ifvac[i]==2){
        if(i%2)
          count_rb++;
        else
          count_ra++;
      }
      else if(ifvac[i]==3){
        if(i%2)
          count_ra++;
        else
          count_rb++;
      }

      pck_counter++;
      pocket[pck_counter]=i;
      //getchar();
      //printf("started %d %d %d\n",n_clust,i,ifvac[i]);
      while(pck_counter!=-1){
        site=pocket[pck_counter];
        pck_counter--;
        clust_counter++;
        burn[site]=n_clust;
        sublat=site%2;
        cell=site/2;
        x=cell%lx;
        //getchar();
        if(ifvac[site]<=0){  //free clusters
          site2=neigh[site][0];
          if( (ifvac[site2]<=0) &&(burn[site2]==-1)){
            pck_counter++;
            pocket[pck_counter]=site2;
          }

          site2=neigh[site][1];
          if((ifvac[site2]<=0) &&(burn[site2]==-1)){
            pck_counter++;
            pocket[pck_counter]=site2;
          }

          site2=neigh[site][2];
          if( (ifvac[site2]<=0) &&(burn[site2]==-1)){
            pck_counter++;
            pocket[pck_counter]=site2;
          }

        }

        if(ifvac[site]==2){  //free clusters
          site2=neigh[site][0];
          if( (ifvac[site2]==3) &&(burn[site2]==-1)){
            pck_counter++;
            pocket[pck_counter]=site2;
          }

          site2=neigh[site][1];
          if((ifvac[site2]==3) &&(burn[site2]==-1)){
            pck_counter++;
            //printf("padd\n");
            pocket[pck_counter]=site2;
          }

          site2=neigh[site][2];
          if( (ifvac[site2]==3) &&(burn[site2]==-1)){
            pck_counter++;
            //printf("padd\n");
            pocket[pck_counter]=site2;
          }

        }

        if(ifvac[site]==3){  //free clusters
          site2=neigh[site][0];
          if( (ifvac[site2]==2) &&(burn[site2]==-1)){
            pck_counter++;
            //printf("padd\n");
            pocket[pck_counter]=site2;
          }

          site2=neigh[site][1];
          if((ifvac[site2]==2) &&(burn[site2]==-1)){
            pck_counter++;
            //printf("padd\n");
            pocket[pck_counter]=site2;
          }

          site2=neigh[site][2];
          if( (ifvac[site2]==2) &&(burn[site2]==-1)){
            pck_counter++;
            pocket[pck_counter]=site2;
          }

        }

      }
      //printf("clust size \t%d \t%d \t%d \t%d\n",clust_counter+1,count_ra,count_rb,count_free);

      n_clust++;
    }
  }
  printf("cluster counts :total %d,free %d, RA=%d, RB=%d\n",n_clust,count_free,count_ra,count_rb);
  printf("total sites =%d\n",(ncells-num_vacs));

}
