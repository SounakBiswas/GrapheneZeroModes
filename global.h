#define LX 100
#define LY 100
#define NCELLS LX*LY
#define NEDGES 5*NCELLS
#define NSITES 2*NCELLS
#define NLINKS 3*NCELLS
#define NC 0.08

int lx,ly,ncells,nsites,nedges,nlinks;
double nc;
int neigh[NSITES][3];
int ifvac[NSITES];
int num_vacs;
int dfs_success;
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
