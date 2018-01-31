#define LX 1000
#define LY 1000
#define NCELLS LX*LY
#define NEDGES 5*NCELLS
#define NSITES 2*NCELLS
#define NLINKS 3*NCELLS
#define NC 0.1

int lx,ly,ncells,nsites,nedges,nlinks;
double nc;
int neigh[2*NCELLS][3];
int dfs_success;
int *rids;
int *cptrs;
int *rmatch;
int *cmatch;
int n_nonzeros;
int aug;
int *cdegree;
int *rdegree;
int *unmatched;
int freecol;
