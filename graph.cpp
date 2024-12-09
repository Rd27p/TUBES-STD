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
    adrGedung TEMP = firstVertex(G);
    adrGedung prev = NULL;

    while (TEMP != NULL && infoVertex(TEMP) != vertexID) {
        prev = TEMP;
        TEMP = nextVertex(TEMP);
    }

    if (TEMP == NULL) {
        cout << "Vertex tidak ada." << endl;
        return;
    }

    adrGedung tempVertex = firstVertex(G);
    while (tempVertex != NULL) {
        deleteEdge(G, infoVertex(tempVertex), vertexID);
        tempVertex = nextVertex(tempVertex);
    }

    // Hapus vertex dari graph
    if (prev == NULL) {
        firstVertex(G) = nextVertex(TEMP);
    } else {
        nextVertex(prev) = nextVertex(TEMP);
    }

    // Hapus semua edge dari vertex
    adrJalur tempEdge;
    while (firstEdge(TEMP) != NULL) {
        tempEdge = firstEdge(TEMP);
        firstEdge(TEMP) = nextEdge(tempEdge);
        delete tempEdge;
    }

    TEMP = NULL;
    cout << "Vertex " << vertexID << " berhasil dihapus." << endl;
}

void deleteEdge(graph &G, string sourceVertexID, string destVertexID) {
    /* I.S. Terdefinisi Graph G, adrNode P_NODE, adrEdge P_EDGE
    F.S. Procedure menghapus jalur atau edge dari graph */
    adrGedung sourceVertex = findVertex(G, sourceVertexID);
    if (sourceVertex == NULL) {
        cout << "Vertex sumber tidak ada." << endl;
        return;
    }

    adrJalur TEMP = firstEdge(sourceVertex);
    adrJalur prev = NULL;
    
    // mencari edge yang akan dihapus
    while (TEMP != NULL && destvertexID(TEMP) != destVertexID) {
        prev = TEMP;
        TEMP = nextEdge(TEMP);
    }

    if (TEMP == NULL) {
        cout << "Edge tidak ada." << endl;
        return;
    }

    // hapus edge
    if (prev == NULL) {
        firstEdge(sourceVertex) = nextEdge(TEMP);
    } else {
        nextEdge(prev) = nextEdge(TEMP);
    }

    TEMP = NULL;
    cout << "Edge dari " << sourceVertexID << " ke " << destVertexID << " berhasil dihapus." << endl;
}

// yang belum dikerjakan
int shortestPath(graph G, string startID, string endID){
    /* I.S. Terdefinisi Graph G
    F.S. Mengembalikan nilai yang merupakan jalur yang terpendek yang ada di graph */
}
int longestPath(graph G, string startID, string endID){
    // Mengembalikan nilai yang merupakan jalur yang terpanjang yang ada di graph
}
int alternativePath(graph G, string startID, string endID){
    // Mengembalikan nilai yang merupakan jalur alternative yang ada di graph
    // gunakan shortest dan delete sementara gedung
}
int calculatePathTaken(graph G){
    // Mengembalikan nilai yang merupakan jumlah jalur yang ada di graph
}
void buildGraph(graph &G){
    /* I.S. Terdapat file yang berisi data-data gedung dan jalur yang terhubung
    F.S. Graph G terbentuk */
    initGraph(G);
}
void showVertex(){
    /* I.S. Terdefinisi Graph G
    F.S. Menampilkan semua nama gedung / vertex yang ada di graph */
    adrGedung TEMP = firstVertex(G);

    // mengecek jika graph kosong
    if (TEMP == NULL) {
        cout << "Graph kosong." << endl;
        return;
    }
    cout << "Daftar Gedung:" << endl;
    while (TEMP != NULL) {
        cout << infoVertex(TEMP) << ", ";
        TEMP = nextVertex(TEMP);
    }
}
void showEdge(){
    /* I.S. Terdefinisi Graph G
    F.S. Menampilkan semua jalur yang ada di graph */
    adrGedung TEMP = firstVertex(G);

    // mengecek jika graph kosong
    if (TEMP == NULL) {
        cout << "Graph kosong." << endl;
        return;
    }
    cout << "Daftar Jalur:" << endl;
    while (TEMP != NULL) {
        adrJalur TEMP = firstEdge(TEMP);
        while (TEMP != NULL) {
            cout << Vertex(TEMP) << " ke " << destvertexID(TEMP) << " berbobot " << edgeWeight(TEMP) << endl;
            TEMP = nextEdge(TEMP);
        }
        TEMP = nextVertex(TEMP);
    }
}
void showGraph(){
    /* I.S. Terdefinisi Graph G
    F.S. Menampilkan semua data-data gedung dan jalur yang ada di graph */
    adrGedung TEMP = firstVertex(G);

    // mengecek jika graph kosong
    if (TEMP == NULL) {
        cout << "Graph kosong." << endl;
        return;
    }
    cout << "Graph:" << endl;
    while (TEMP != NULL) {
        cout << "Gedung: " << infoVertex(TEMP) << endl;
        adrJalur TEMP_EDGE = firstEdge(TEMP);
        if (TEMP_EDGE == NULL) {
            cout << "Tidak ada jalur." << endl;
        } else {
            cout << "Jalur:" << endl;
            while (TEMP_EDGE != NULL) {
                cout << " ke " << destvertexID(TEMP_EDGE) << " berbobot " << edgeWeight(TEMP_EDGE) << endl;
                TEMP_EDGE = nextEdge(TEMP_EDGE);
            }
        }
        TEMP = nextVertex(TEMP);
    }
}
