#define LX 2000
#define LY LX
#define NCELLS LX*LY
#define NEDGES 5*NCELLS
#define NSITES 2*NCELLS
#define NLINKS 3*NCELLS
#define NC 0.05
#define NR 20
#define SEED 11
#define NUM 1
int lx,ly,ncells,nsites,nedges,nlinks;
double nc;
int **neigh;
int *ifvac;
int *burn;
int statlines[NR];
//int *burn;
int num_vacs;
int dfs_success;
int n_realizations;
int *rids;
int *cids;
int *cptrs;
int *rptrs;
int *rmatch;
int *cmatch;
int n_nonzeros;
int *cdegree;
int *rdegree;
int *unmatched;
int freecol;
double size_free;
