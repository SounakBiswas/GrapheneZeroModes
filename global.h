#define LX 30
#define LY LX
#define NCELLS LX*LY
#define NEDGES 5*NCELLS
#define NSITES 2*NCELLS
#define NLINKS 3*NCELLS
#define NC 0.12
#define NR 1
#define SEED 2289
int lx,ly,ncells,nsites,nedges,nlinks;
double nc;
int neigh[NSITES][3];
int ifvac[NSITES];
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
