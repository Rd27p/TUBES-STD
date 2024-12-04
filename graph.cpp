#include "graph.h"

void menu() {
    /* I.S. menu belum dibuat
    F.S. Menu telah dibuat */
    cout << "===== PENCARI JALUR TELKOM UNIVERSITY =====" << endl;
    cout << "1. Tambah Nama Gedung" << endl;
    cout << "2. Tambah Koneksi Antar Gedung" << endl;
    cout << "3. Hapus Gedung" << endl;
    cout << "4. Hapus Koneksi Antar Gedung" << endl;
    cout << "5. Cari Jalur Terpendek" << endl;
    cout << "6. Cari Jalur Terpanjang" << endl;
    cout << "7. Cari Jalur Alternatif" << endl;
    cout << "8. Keluar" << endl;
    cout << "===========================================" << endl;
}

adrGedung createVertex(string newVertex) {
    /* I.S. Vertex belum dibuat, parameter newVertex telah siap dimasukkan
    F.S. Vertex baru telah dibuat dengan infoVertex = newVertex, nextVertex = NULL, dan firstEdge = NULL */
    adrGedung V = new gedung;
    infoVertex(V) = newVertex;
    nextVertex(V) = NULL;
    firstEdge(V) = NULL;
    return V;
}

adrJalur createEdge(string destVertexID, int weight) {
    /* I.S. Edge belum dibuat, parameter destVertexID, weight telah siap dimasukkan
    F.S. Edge baru telah dibuat dengan destVertexID = destVertexID, edgeWeight = weight, nextEdge = NULL */
    adrJalur E = new jalur;
    destvertexID(E) = destVertexID;
    edgeWeight(E) = weight;
    nextEdge(E) = NULL;
    return E;
}

void initGraph(graph &G){
    firstVertex(G) = NULL;
}

void addVertex(graph &G, string newVertexID) {
    /* I.S. Isi dari vertex mungkin saja kosong, parameter newVertexID sudah siap dimasukkan
    F.S. Vertex baru berhasil ditambahkan */
    adrGedung newVertex = createVertex(newVertexID);
    if (firstVertex(G) == NULL) {
        firstVertex(G) = newVertex;
    } else {
        adrGedung temp = firstVertex(G);
        while (nextVertex(temp) != NULL) {
            temp = nextVertex(temp);
        }
        nextVertex(temp) = newVertex;
    }
    cout << "Vertex telah dibuat: " << newVertexID << endl;
}

void addEdge(graph &G, string sourceVertexID, string destVertexID, int weight) {
    /* I.S. nilai dari edge mungkin saja kosong, parameter sourceVertexID, destVertexID, weight sudah siap dimasukkan
    F.S. jalur / edge baru berhasil ditambahkan */
    adrGedung sourceVertex = firstVertex(G);
    while (sourceVertex != NULL && infoVertex(sourceVertex) != sourceVertexID) {
        sourceVertex = nextVertex(sourceVertex);
    }

    if (sourceVertex == NULL) {
        cout << "Nama Gedung tidak ditemukan" << endl;
        return;
    }

    adrJalur newEdge = createEdge(destVertexID, weight);
    if (firstEdge(sourceVertex) == NULL) {
        firstEdge(sourceVertex) = newEdge;
    } else {
        adrJalur tempEdge = firstEdge(sourceVertex);
        while (nextEdge(tempEdge) != NULL) {
            tempEdge = nextEdge(tempEdge);
        }
        nextEdge(tempEdge) = newEdge;
    }
}

adrGedung findVertex(graph G, string vertexID){
/*
{I.S. Terdefinisi Graph G, dan string vertexID
F.S. Mengembalikan pointer vertex jika ditemukan dan NULL jika tidak ditemukan}
*/
    adrGedung currentVertex = firstVertex(G);
    while (currentVertex != NULL) { //Melakukan pengecekan dari vertex ke-1 hingga akhir
        if (infoVertex(currentVertex) == vertexID) {
            return currentVertex;
        }
        currentVertex = nextVertex(currentVertex);
    }
    return NULL;
}
adrJalur findEdge(graph G, string sourceVertexID, string destVertexID){
/*
[I.S. Terdefinisi graph G, string sourceVertexID, dan string destVertexID
F.S. Mengembalikan pointer edge jika ditemukan dan NULL jika tidak ditemukan}
*/

    adrGedung sourceVertex = findVertex(G, sourceVertexID);
    if (sourceVertex == NULL) {
        return NULL;
    }

    adrJalur currentEdge = firstEdge(sourceVertex);
    while (currentEdge != NULL) {
        if (destvertexID(currentEdge) == destVertexID) { //Melakukan pengecekan dari vertex ke-1 hingga akhir
            return currentEdge;
        }
        currentEdge = nextEdge(currentEdge);
    }
    return NULL;
}

void deleteVertex(graph &G, string vertexID) {
    /* I.S. Terdefinisi Graph G, adrNode P_NODE, adrEdge P_EDGE
    F.S. Procedure menghapus nama gedung / vertex dari graph */
    adrGedung prevVertex = NULL;
    adrGedung currentVertex = firstVertex(G);

    while (currentVertex != NULL && infoVertex(currentVertex) != vertexID) {
        prevVertex = currentVertex;
        currentVertex = nextVertex(currentVertex);
    }

    if (currentVertex == NULL) {
        cout << "Nama Gedung tidak ditemukan" << endl;
        return;
    }

    adrJalur currentEdge = firstEdge(currentVertex);
    while (currentEdge != NULL) {
        adrJalur nextEdgeToDelete = nextEdge(currentEdge);
        delete currentEdge;
        currentEdge = nextEdgeToDelete;
    }

    if (prevVertex == NULL) {
        firstVertex(G) = nextVertex(currentVertex);
    } else {
        nextVertex(prevVertex) = nextVertex(currentVertex);
    }
    cout << "Gedung " << vertexID << " telah dihapus" << endl;
}

void deleteEdge(graph &G, string sourceVertexID, string destVertexID) {
    /* I.S. Terdefinisi Graph G, adrNode P_NODE, adrEdge P_EDGE
    F.S. Procedure menghapus jalur atau edge dari graph */
    adrGedung sourceVertex = firstVertex(G);
    while (sourceVertex != NULL && infoVertex(sourceVertex) != sourceVertexID) {
        sourceVertex = nextVertex(sourceVertex);
    }

    if (sourceVertex == NULL) {
        cout << "Vertex awal tidak ditemukan" << endl;
        return;
    }

    adrJalur prevEdge = NULL;
    adrJalur currentEdge = firstEdge(sourceVertex);
    while (currentEdge != NULL && destvertexID(currentEdge) != destVertexID) {
        prevEdge = currentEdge;
        currentEdge = nextEdge(currentEdge);
    }

    if (currentEdge == NULL) {
        cout << "Edge tidak ditemukan" << endl;
        return;
    }

    if (prevEdge == NULL) {
        firstEdge(sourceVertex) = nextEdge(currentEdge);
    } else {
        nextEdge(prevEdge) = nextEdge(currentEdge);
    }
    cout << "Jalur dari " << sourceVertexID << " ke " << destVertexID << " telah dihapus" << endl;
}

// yang belum dikerjakan
int shortestPath(graph G, string startID, string endID){
    
}
int longestPath(graph G, string startID, string endID);
int alternativePath(graph G, string startID, string endID);
int calculatePathTaken(graph G);
void buildGraph(graph &G);
void showVertex();
void showEdge();
void showGraph();
