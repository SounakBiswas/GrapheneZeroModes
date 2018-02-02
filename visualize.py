import matplotlib.pyplot as plt
import csv
import networkx as nx
import numpy as np
root3by2=0.5*(3**0.5)
G=nx.Graph()
lx=40;
ly=40;
ctr=0;
posx=0;
posy=0;
l=0.5
lattice='brickwall'
lattice='honeycomb'
def nbr(x,y,i,j) :
  return (x+i)+(y+j)*lx
for x in range (0,lx) :
  for y in range(0,ly) :
    cell=x+y*lx
    posx=x-y/(2.0)
    if(lattice=='brickwall') :
      posy=y*0.5
      G.add_node(2*cell,pos=(posx,posy))
      G.add_node(2*cell+1,pos=(posx,posy+0.5))
    if(lattice=='honeycomb') :
      posy=(1.0+root3by2)*y
      G.add_node(2*cell,pos=(posx,posy))
      G.add_node(2*cell+1,pos=(posx,posy+1))
ctr=0;
for x in range (0,lx) :
  for y in range(0,ly) :
    cell=x+y*lx
    G.add_edge(2*cell,2*cell+1)
    if(y!=0):
      G.add_edge(2*cell,2*nbr(x,y,0,-1)+1)
      if(x!=0):
        G.add_edge(2*cell,2*nbr(x,y,-1,-1)+1)
    

f=open("vacancies.dat","r");
remove=f.read().splitlines();
f.close();
vacancies=map(int,remove)
f=open("free_sites.dat","r");
remove2=f.read().splitlines();
f.close();
free_sites=map(int,remove2)

remove=vacancies+free_sites

for i in vacancies :
  G.remove_edges_from(G.edges(i))

pos=nx.get_node_attributes(G,'pos')
nprime=G.nodes()

#nx.draw_networkx_nodes(G,pos,node_color='#636363',nodelist=nprime,node_size=0,linewidths=0.2)
nx.draw_networkx_nodes(G,pos,node_color='#3182bd',nodelist=free_sites,node_size=5,linewidths=0.2)
nx.draw_networkx_nodes(G,pos,node_color='#f03b20',nodelist=vacancies,node_size=2,linewidths=0.2)
nx.draw_networkx_edges(G,pos,width=0.2)
plt.axis('off')
plt.axes().set_aspect('equal')
plt.savefig("test.pdf",format='pdf')
#plt.savefig("test.png",bbox_inches='tight' )
