#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <iostream>
#define firstVertex(G) G.firstVertex
#define nextVertex(V) V->nextVertex
#define infoVertex(V) V->infoVertex
#define firstEdge(V) V->firstEdge
#define destvertexID(E) E->destvertexID
#define nextEdge(E) E->nextEdge
#define edgeWeight(E) E->edgeWeight
using namespace std;

const int MAX_BUILDINGS = 20;
typedef struct gedung *adrGedung;
typedef struct jalur *adrJalur;

struct gedung {
    string infoVertex;
    adrGedung nextVertex;
    adrJalur firstEdge;
};

struct jalur {
    string destvertexID;
    int edgeWeight;
    adrJalur nextEdge;
};

struct graph {
    adrGedung firstVertex;
};

void menu();
adrGedung createVertex(string newVertex);
adrJalur createEdge(string destVertexID, int weight);
void initGraph(graph &G);
void addVertex(graph &G, string newVertexID);
void addEdge(graph &G, string sourceVertexID, string destVertexID, int weight);
adrGedung findVertex(graph G, string vertexID);
adrJalur findEdge(graph G, string sourceVertexID, string destVertexID);
void deleteVertex(graph &G, string vertexID);
void deleteEdge(graph &G, string sourceVertexID, string destVertexID);
int shortestPath(graph G, string startID, string endID);
int longestPath(graph G, string startID, string endID);
void alternativePath(graph G, string startID, string endID, string avoidID);
void buildGraph(graph &G);
void showVertexEdge(graph G);
void showGraph(graph G);
void buildGraph(graph &G);
#endif // GRAPH_H_INCLUDED
