#Modelo para bi-particao de grafos

param n >= 1, integer; #numero de vertices
param m >= 1, integer; #numero de arestas
set V := 1..n; #conjunto de vertices
set A within {V,V}; #conjunto de arestas

param arestas_inclusas{A}; #inclusao de arestas

#variaveis do problema
var x{V} binary; #x = 1 => vertice pertence ao subgrafo 1, 0 caso contrario.

#arestas internas, i.e, arestas tais que u e v pertencem ao mesmo subgrafo
var f{V,V} binary; #f = 1 => se u e v nao pertencem ao mesmo subgrafo, zero caso u ou v sao do mesmo subgrafo.

#funcao objetivo
minimize arestas_corte : sum{(u,v) in A} arestas_inclusas[u,v] * f[u,v];

#restricoes
subject to cardinalidade : sum{v in V} x[v] = floor(card({V})/2); #a cardinalidade de cada subgrafo tem que ser igual a metade do numero de vertices

#restricoes para calcular o numero de arestas fora de um subgrafo
subject to contador1 {u in V, v in V : (u,v) in A} : f[u,v] >= x[u] - x[v];
subject to contador2 {u in V, v in V : (u,v) in A} : f[u,v] >= - x[u] + x[v];

data;
