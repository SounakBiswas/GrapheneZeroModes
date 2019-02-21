import matplotlib.pyplot as plt
import math
import csv
import networkx as nx
import numpy as np
import sys
factor=(1.0+0.5*(3**0.5))
G=nx.Graph()
lx=30;
ly=30;
ctr=0;
posx=0;
posy=0;
l=0.5
remove_edges=False
lattice='honeycomb'
#lattice='brickwall'
def nbr(x,y,i,j) :
  return (x+i)+(y+j)*lx
for x in range (0,lx) :
  for y in range(0,ly) :
    cell=x+y*lx
    posx=(3**0.5)*(x-y/2.0)
    if(lattice=='brickwall') :
      posy=y*0.5
      G.add_node(2*cell,pos=(posx,posy))
      G.add_node(2*cell+1,pos=(posx,posy+0.5))
    if(lattice=='honeycomb') :
      posy=(1.5)*y
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
f=open("free_sitesA.dat","r");
remove=f.read().splitlines();
f.close();
free_sitesA=map(int,remove)
f=open("free_sitesB.dat","r");
remove=f.read().splitlines();
f.close();
free_sitesB=map(int,remove)
f=open("edgelist.dat","r");
remove=f.read().splitlines();
f.close();
redges=[tuple(map(int,i.split())) for i in remove]
redgesn=[]
pos=nx.get_node_attributes(G,'pos')
print redges
for i in range(len(redges)) :
    p0=pos[redges[i][0]]
    p1=pos[redges[i][1]]
    #print p0,p1
    #sys.stdin.read(1)
    if math.sqrt((p0[0]-p1[0])**2+(p0[1]-p1[1])**2)<4.0 :
        redgesn.append(redges[i])
    else :
        print redges[i]


remove=vacancies+free_sitesA+free_sitesB
#redgesn=redges

for i in vacancies :
  G.remove_edges_from(G.edges(i))

pos=nx.get_node_attributes(G,'pos')
if(remove_edges==True):
  G.remove_edges_from(redges)

#nx.draw_networkx_nodes(G,pos,node_color='#636363',nodelist=nprime,node_size=0,linewidths=0.2)
nx.draw_networkx_nodes(G,pos,node_color='#3182bd',nodelist=free_sitesA,node_size=8,linewidths=0.2)
nx.draw_networkx_nodes(G,pos,node_color='y',nodelist=free_sitesB,node_size=8,linewidths=0.2)
#nx.draw_networkx_nodes(G,pos,node_color='#f03b20',nodelist=vacancies,node_size=2,linewidths=0.2)
#nx.draw_networkx_nodes(G,pos,node_color='y',nodelist=unmatched,node_size=16,linewidths=0.2)
nx.draw_networkx_edges(G,pos,width=0.2)
nx.draw_networkx_edges(G,pos,edgelist=redgesn,width=1.5)
#nx.draw_networkx_edges(G,pos,edgelist=redges,edge_color='r',width=0.2)
plt.axis('off')
plt.axes().set_aspect('equal')
fig=plt.gcf()
#plt.savefig("test.pdf",format='pdf')
fig.savefig("test.pdf",format='pdf' )
#fig.savefig("test.svg",format='svg' )
#fig.savefig("test.png",dpi=300,bbox_inches='tight' )
