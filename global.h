#define LX 200
#define LY 200
#define NCELLS LX*LY
#define NEDGES 5*NCELLS
#define NSITES 2*NCELLS
#define NLINKS 3*NCELLS
#define NC 0.02

int lx,ly,ncells,nsites,nedges,nlinks;
double nc;
int capacity[NEDGES];
int flow[NEDGES];
int neigh[2*NCELLS][3];
int pred[NSITES+2];
int color[NSITES+2];
int dfs_success;
int *rids;
int *cptrs;
int *rmatch;
int *cmatch;
int n_nonzeros;
int aug;
