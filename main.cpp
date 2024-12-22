#include "graph.h"

int main() {
    graph G;
    int choice = 0;
    initGraph(G);
    buildGraph(G);

    string vertexIDs[MAX_BUILDINGS];
    int n = 0;

    do {
        menu();
        cout << "Masukkan pilihan: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Masukkan jumlah gedung yang akan ditambah (max 100): ";
            cin >> n;

            if (n <= 0 || n > MAX_BUILDINGS) {
                cout << "Jumlah gedung harus lebih dari 0 dan tidak lebih dari " << MAX_BUILDINGS << "!" << endl;
                break;
            }

            cout << "Masukkan ID gedung (pisahkan dengan spasi): ";
            for (int i = 0; i < n; i++) {
                cin >> vertexIDs[i];
                addVertex(G, vertexIDs[i]);
                cout << "Vertex '" << vertexIDs[i] << "' berhasil ditambahkan." << endl;
            }
            break;
        }
        case 2: {
            string source, destination;
            int weight;
            cout << "Masukkan ID vertex sumber: ";
            cin >> source;
            cout << "Masukkan ID vertex tujuan: ";
            cin >> destination;
            cout << "Masukkan bobot edge: ";
            cin >> weight;
            addEdge(G, source, destination, weight);
            break;
        }
        case 3: {
            string vertexToDelete;
            cout << "Masukkan nama gedung yang akan dihapus: ";
            cin >> vertexToDelete;
            deleteVertex(G, vertexToDelete);
            break;
        }
        case 4: {
            string source, destination;
            cout << "Masukkan nama gedung sumber dan tujuan yang akan dihapus: ";
            cin >> source >> destination;
            deleteEdge(G, source, destination);
            break;
        }
        case 5: {
            string start, end;
            cout << "Masukkan ID gedung awal: ";
            cin >> start;
            cout << "Masukkan ID gedung tujuan: ";
            cin >> end;
            int shortest = shortestPath(G, start, end);
            if (shortest != -1) {
                cout << "Dengan total jarak: " << shortest << " Meter " << endl;
            }
            break;
        }
        case 6: {
            string start, end;
            cout << "Masukkan ID gedung awal: ";
            cin >> start;
            cout << "Masukkan ID gedung tujuan: ";
            cin >> end;
            int longest = longestPath(G, start, end);
            if (longest != -1) {
                cout << "Dengan total jarak: " << longest << " Meter " << endl;
            }
            break;
        }

        case 7: {
            string start, End, avoid;
            cout << "Masukkan ID gedung yang ingin dihindari: ";
            cin >> avoid;
            cout << "Masukkan ID gedung awal: ";
            cin >> start;
            cout << "Masukkan ID gedung tujuan: ";
            cin >> End;
            alternativePath(G, start, End, avoid);
            break;
        }
        case 8:
            showVertexEdge(G);
            break;
        case 9:
            showGraph(G);
            break;
        case 10:
            cout << "Terima kasih! Program selesai." << endl;
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
        }
    } while (choice != 11);

    return 0;
}
