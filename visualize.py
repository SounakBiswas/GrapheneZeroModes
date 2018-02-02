import matplotlib.pyplot as plt
import networkx as nx

G=nx.Graph()
lx=40;
ly=40;
ctr=0;
posx=0;
posy=0;
l=0.5
def nbr(x,y,i,j) :
  return (x+i)+(y+j)*lx
for x in range (0,lx) :
  for y in range(0,ly) :
    cell=x+y*lx
    posx=x-y/(2.0)
    posy=y
    G.add_node(2*cell,pos=(l*posx,l*posy))
    #G.add_edge(ctr,ctr+1)
    ctr+=1;
    G.add_node(2*cell+1,pos=(l*posx,l*(posy+1.0)))
    ctr+=1;
ctr=0;
for x in range (0,lx) :
  for y in range(0,ly) :
    cell=x+y*lx
    G.add_edge(2*cell,2*cell+1)
    if(y!=0):
      G.add_edge(2*cell,2*nbr(x,y,0,-1)+1)
      if(x!=0):
        G.add_edge(2*cell,2*nbr(x,y,-1,-1)+1)
    

remove=[1,10,78,151]
nprime=set(G.nodes())-set(remove)

for i in remove :
  G.remove_edges_from(G.edges(i))
  #G.remove_node(i)

pos=nx.get_node_attributes(G,'pos')
nx.draw_networkx_nodes(G,pos,node_color='#a6611a',nodelist=nprime,node_size=4,linewidths=0.2)
nx.draw_networkx_edges(G,pos,)
nx.draw_networkx_nodes(G,pos,node_color='#018571',nodelist=remove,node_size=2,linewidths=0.2)
plt.axis('off')
plt.savefig("test.pdf",format='pdf')
#plt.savefig("test.png",bbox_inches='tight' )
