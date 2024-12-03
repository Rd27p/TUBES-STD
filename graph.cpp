#include "graph.h"#include "graph.h"

void createVertex_103022300088(char newVertex, adrVertex &v){
    v = new vertex;
    infoVertex(v) = newVertex;
    nextVertex(v) = NULL;
    firstEdge(v) = NULL;
}

void initGraph_103022300088(graph &G){
    firstVertex(G) = NULL;
}

void addVertex_103022300088(graph &G, char newVertexID){
    adrVertex newVertex;
    createVertex_103022300088(newVertexID, newVertex);

    if(firstVertex(G) == NULL){
        firstVertex(G) = newVertex;
    } else {
        adrVertex temp = firstVertex(G);
        while(nextVertex(temp) != NULL){
            temp = nextVertex(temp);
        }
        nextVertex(temp) = newVertex;
    }
}

void buildGraph_103022300088(graph &G) {
    initGraph_103022300088(G);
    char v;
    cout << "Masukkan ID Vertex (dari A-Z, ketik '.' untuk berhenti): " << endl;
    while (true) {
        cout << "ID Vertex: ";
        cin >> v;
        if (v == '.') {
            break;
        } else if (v < 'A' || v > 'Z') {
            cout << "Harap masukkan karakter (A-Z)." << endl;
        }
        addVertex_103022300088(G, v);
    }

    if (firstVertex(G) == NULL) {
        cout << "Graf Kosong" << endl;
    } else {
        cout << endl;
        cout << "Vertex graf MLL: " << endl;
        adrVertex tempVertex = firstVertex(G);
        while (tempVertex != NULL) {
            cout << "Vertex " << infoVertex(tempVertex) <<endl;
            tempVertex = nextVertex(tempVertex);
        }
        cout << endl;
        cout << "Vertex berhasil di buat" << endl;
    }
}
