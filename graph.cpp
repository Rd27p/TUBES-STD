#include "graph.h"

void menu() {
    cout << "===== PENCARI JALUR TELKOM UNIVERSITY =====" << endl;
    cout << "1. Tambah Nama Gedung" << endl;
    cout << "2. Tambah Koneksi Antar Gedung" << endl;
    cout << "3. Hapus Gedung" << endl;
    cout << "4. Hapus Koneksi Antar Gedung" << endl;
    cout << "5. Cari Jalur Terpendek" << endl;
    cout << "6. Cari Jalur Terpanjang" << endl;
    cout << "7. Cari Jalur Altern atif" << endl;
    cout << "8. Lihat Gedung" << endl;
    cout << "9. Lihat Jalur" << endl;
    cout << "10. Lihat Graph" << endl;
    cout << "11. Keluar" << endl;
    cout << "===========================================" << endl;
}

adrGedung createVertex(string newVertex) {
    /* Mengembalikan nilai dari V */
    adrGedung V = new gedung;
    infoVertex(V) = newVertex;
    nextVertex(V) = NULL;
    firstEdge(V) = NULL;
    return V;
}

adrJalur createEdge(string destVertexID, int weight) {
    /* Mengembalikan nilai dari E */
    adrJalur E = new jalur;
    destvertexID(E) = destVertexID;
    edgeWeight(E) = weight;
    nextEdge(E) = NULL;
    return E;
}

void initGraph(graph &G) {
    /* I.S. -
        F.S. firstVertex telah terisi nilai NIL*/
    firstVertex(G) = NULL;
}

void addVertex(graph &G, string newVertexID) {
    /* I.S. Graph G mungkin kosong atau sudah berisi beberapa Gedung
        F.S. Sebuah Gedung baru dengan ID newVertexID telah ditambahkan ke dalam Graph G */
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
}

void addEdge(graph &G, string sourceVertexID, string destVertexID, int weight) {
    /* I.S. Graph G mungkin kosong atau sudah berisi beberapa Gedung. sourceVertexID ke destVertexID yang akan ditambahkan
        F.S. Sebuah jalur dengan bobot (weight) telah ditambahkan dari sourceVertexID ke destVertexID */
    adrGedung sourceVertex = findVertex(G, sourceVertexID);
    if (sourceVertex == NULL) {
        cout << "Gedung asal tidak ada!" << endl;
        return;
    }

    adrJalur newEdge = createEdge(destVertexID, weight);
    nextEdge(newEdge) = firstEdge(sourceVertex);
    firstEdge(sourceVertex) = newEdge;

    adrGedung destVertex = findVertex(G, destVertexID);
    if (destVertex != NULL) {
        adrJalur reverseEdge = createEdge(sourceVertexID, weight);
        nextEdge(reverseEdge) = firstEdge(destVertex);
        firstEdge(destVertex) = reverseEdge;
    }
}

adrGedung findVertex(graph G, string vertexID) {
    /* Mengembalikan nama gedung yang ada di Graph G */
    adrGedung currentVertex = firstVertex(G);
    while (currentVertex != NULL) {
        if (infoVertex(currentVertex) == vertexID) {
            return currentVertex;
        }
        currentVertex = nextVertex(currentVertex);
    }
    return NULL;
}

adrJalur findEdge(graph G, string sourceVertexID, string destVertexID) {
    /* Mengembalikan jalur beserta dengan asal gedung dan gedung tujuan di Graph G */
    adrGedung sourceVertex = findVertex(G, sourceVertexID);
    if (sourceVertex == NULL) {
        return NULL;
    }

    adrJalur currentEdge = firstEdge(sourceVertex);
    while (currentEdge != NULL) {
        if (destvertexID(currentEdge) == destVertexID) {
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

int shortestPath(graph G, string startID, string endID) {
    adrGedung startVertex = findVertex(G, startID);
    adrGedung endVertex = findVertex(G, endID);

    if (startVertex == NULL && endVertex == NULL) {
        cout << "Error: Nama gedung tidak ditemukan" << endl;
        return -1;
    }

    const int MAX_VERTICES = MAX_BUILDINGS;
    int distance[MAX_VERTICES];
    bool visited[MAX_VERTICES];
    adrGedung vertexArray[MAX_VERTICES];
    int predecessor[MAX_VERTICES];
    int startIdx = -1, endIdx = -1;

    int vertexCount = 0;
    adrGedung current = firstVertex(G);
    while (current != NULL) {
        vertexArray[vertexCount] = current;
        distance[vertexCount] = INT_MAX;
        visited[vertexCount] = false;
        predecessor[vertexCount] = -1;
        if (current == startVertex) startIdx = vertexCount;
        if (current == endVertex) endIdx = vertexCount;
        vertexCount++;
        current = nextVertex(current);
    }

    if (startIdx == -1 || endIdx == -1) {
        cout << "Error: Start or end vertex not found in the graph." << endl;
        return -1;
    }

    distance[startIdx] = 0;

    for (int i = 0; i < vertexCount; ++i) {
        int minDistance = INT_MAX;
        int currentIdx = -1;

        for (int j = 0; j < vertexCount; ++j) {
            if (!visited[j] && distance[j] < minDistance) {
                minDistance = distance[j];
                currentIdx = j;
            }
        }

        if (currentIdx == -1) break;
        visited[currentIdx] = true;

        adrJalur edge = firstEdge(vertexArray[currentIdx]);
        while (edge != NULL) {
            int neighborIdx = -1;
            for (int k = 0; k < vertexCount; ++k) {
                if (vertexArray[k]->infoVertex == destvertexID(edge)) {
                    neighborIdx = k;
                    break;
                }
            }
            if (neighborIdx != -1 && !visited[neighborIdx]) {
                int newDistance = distance[currentIdx] + edgeWeight(edge);
                if (newDistance < distance[neighborIdx]) {
                    distance[neighborIdx] = newDistance;
                    predecessor[neighborIdx] = currentIdx;
                }
            }
            edge = nextEdge(edge);
        }
    }

    if (distance[endIdx] == INT_MAX) {
        cout << "No path from " << startID << " to " << endID << "." << endl;
        return -1;
    }

    cout << "Shortest Path from " << startID << " to " << endID << ": ";
    int path[MAX_VERTICES];
    int pathIdx = 0;
    for (int idx = endIdx; idx != -1; idx = predecessor[idx]) {
        path[pathIdx++] = idx;
    }
    for (int i = pathIdx - 1; i >= 0; --i) {
        cout << vertexArray[path[i]]->infoVertex;
        if (i > 0) cout << " -> ";
    }
    cout << endl;

    cout << "Total distance: " << distance[endIdx] << endl;
    return distance[endIdx];
}

int longestPath(graph G, string startID, string endID) {
    adrGedung startVertex = findVertex(G, startID);
    adrGedung endVertex = findVertex(G, endID);

    if (startVertex == NULL || endVertex == NULL) {
        cout << "Error: Start or end vertex not found." << endl;
        return -1;
    }

    const int MAX_VERTICES = MAX_BUILDINGS;
    int distance[MAX_VERTICES];
    bool visited[MAX_VERTICES];
    adrGedung vertexArray[MAX_VERTICES];
    int predecessor[MAX_VERTICES];
    int startIdx = -1, endIdx = -1;

    int vertexCount = 0;
    adrGedung current = firstVertex(G);
    while (current != NULL) {
        vertexArray[vertexCount] = current;
        distance[vertexCount] = INT_MIN;
        visited[vertexCount] = false;
        predecessor[vertexCount] = -1;
        if (current == startVertex) startIdx = vertexCount;
        if (current == endVertex) endIdx = vertexCount;
        vertexCount++;
        current = nextVertex(current);
    }

    if (startIdx == -1 || endIdx == -1) {
        cout << "Error: Start or end vertex not found in the graph." << endl;
        return -1;
    }

    distance[startIdx] = 0;

    for (int i = 0; i < vertexCount; ++i) {
        int maxDistance = INT_MIN;
        int currentIdx = -1;

        for (int j = 0; j < vertexCount; ++j) {
            if (!visited[j] && distance[j] > maxDistance) {
                maxDistance = distance[j];
                currentIdx = j;
            }
        }

        if (currentIdx == -1) break;
        visited[currentIdx] = true;

        adrJalur edge = firstEdge(vertexArray[currentIdx]);
        while (edge != NULL) {
            int neighborIdx = -1;
            for (int k = 0; k < vertexCount; ++k) {
                if (vertexArray[k]->infoVertex == destvertexID(edge)) {
                    neighborIdx = k;
                    break;
                }
            }
            if (neighborIdx != -1 && !visited[neighborIdx]) {
                int newDistance = distance[currentIdx] + edgeWeight(edge);
                if (newDistance > distance[neighborIdx]) {
                    distance[neighborIdx] = newDistance;
                    predecessor[neighborIdx] = currentIdx;
                }
            }
            edge = nextEdge(edge);
        }
    }

    if (distance[endIdx] == INT_MIN) {
        cout << "No path from " << startID << " to " << endID << "." << endl;
        return -1;
    }


    cout << "Longest Path from " << startID << " to " << endID << ": ";
    int path[MAX_VERTICES];
    int pathIdx = 0;
    for (int idx = endIdx; idx != -1; idx = predecessor[idx]) {
        path[pathIdx++] = idx;
    }
    for (int i = pathIdx - 1; i >= 0; --i) {
        cout << vertexArray[path[i]]->infoVertex;
        if (i > 0) cout << " -> ";
    }
    cout << endl;

    cout << "Total distance: " << distance[endIdx] << endl;
    return distance[endIdx];
}

int alternativePath(graph G, string startID, string endID) {
    //???
}

void showVertex(graph G) {
    /* I.S. -
        F.S. nama-nama gedung yang ada di Graph G dapat terlihat*/
    adrGedung currentVertex = firstVertex(G);
    cout << "Daftar Gedung:" << endl;
    while (currentVertex != NULL) {
        cout << "- " << infoVertex(currentVertex) << endl;
        currentVertex = nextVertex(currentVertex);
    }
}

void showEdge(graph G) {
    /* I.S. -
        F.S. bobot jalur yang ada di Graph G dapat terlihat*/
    adrGedung currentVertex = firstVertex(G);
    cout << "Daftar Jalur:" << endl;
    while (currentVertex != NULL) {
        adrJalur currentEdge = firstEdge(currentVertex);
        while (currentEdge != NULL) {
            cout << infoVertex(currentVertex) << " -> " << destvertexID(currentEdge) << " (Weight: " << edgeWeight(currentEdge) << ")" << endl;
            currentEdge = nextEdge(currentEdge);
        }
        currentVertex = nextVertex(currentVertex);
    }
}

void showGraph(graph G) {
    /* I.S. -
        F.S. nama gedung beserta dengan bobot dari semua jalur Graph G dapat terlihat*/
    cout << "Graph:" << endl;
    adrGedung currentVertex = firstVertex(G);
    while (currentVertex != NULL) {
        cout << infoVertex(currentVertex) << ": ";
        adrJalur currentEdge = firstEdge(currentVertex);
        while (currentEdge != NULL) {
            cout << destvertexID(currentEdge) << "(" << edgeWeight(currentEdge) << ") ";
            currentEdge = nextEdge(currentEdge);
        }
        cout << endl;
        currentVertex = nextVertex(currentVertex);
    }
}

void buildGraph(graph &G) {
    /* I.S. Graph G diinisialisasi terlebih dahulu
        F.S. Graph G telah dibuat */

    //Inisiasi graph
    initGraph(G);

    //Menambahkan Gedung
    addVertex(G, "GKU1");
    addVertex(G, "GKU2");
    addVertex(G, "GKU3");
    addVertex(G, "GSG");
    addVertex(G, "TUCH");
    addVertex(G, "TULT");

    //Menambahkan jalur antar gedung
    addEdge(G, "GKU1", "GKU2", 50);
    addEdge(G, "GKU1", "GKU3", 150);
    addEdge(G, "GKU1", "TULT", 800);
    addEdge(G, "GKU2", "GSG", 100);
    addEdge(G, "GKU3", "TUCH", 200);
    addEdge(G, "GKU3", "GSG", 350);
    addEdge(G, "TUCH", "TULT", 300);
}
