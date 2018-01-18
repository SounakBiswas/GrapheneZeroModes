

#define LX 100
#define LY 100
#define NCELLS LX*LY
#define NEDGES 5*NCELLS
#define NSITES 2*NCELLS
#define NLINKS 3*NCELLS
#define NC 0.1

int lx,ly,ncells,nsites,nedges,nlinks;
double nc;
int capacity[NEDGES];
int flow[NEDGES];
int neigh[2*NCELLS][3];
int pred[NSITES+2];
int color[NSITES+2];
int dfs_success;
