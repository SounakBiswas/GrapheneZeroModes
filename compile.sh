#gcc main_viz.c makelattice.c heuristics.c pothenfan.c initialize.c bfs_find_free.c -g
gcc main_viz.c makelattice.c heuristics.c bfs.c initialize.c bfs_find_free.c -g
#gcc main_viz.c makelattice.c heuristics.c pothenfan.c initialize.c bfs_find_free.c -g
rm free_sitesA.dat
rm free_sitesB.dat
./a.out
python visualize.py
