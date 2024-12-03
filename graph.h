#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#define firstVertex(G) G.firstVertex
#define firstEdge(V) V->firstEdge
#define nextVertex(V) V->nextVertex
#define infoVertex(V) V->idVertex
#include <iostream>

using namespace std;

typedef struct vertex *adrVertex;
typedef struct edge *adrEdge;

struct vertex {
    char idVertex;
    adrVertex nextVertex;
    adrEdge firstEdge;
};

struct edge {
    char destvertexID;
    int weight;
    adrEdge nextEdge;
};

struct graph {
    adrVertex firstVertex;
};

void createVertex_103022300088(char newVertex, adrVertex &v);
void initGraph_103022300088(graph &G);
void addVertex_103022300088(graph &G, char newVertexID);
void buildGraph_103022300088(graph &G);
#endif // GRAPH_H_INCLUDED
