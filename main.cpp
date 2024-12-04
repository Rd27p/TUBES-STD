#include "graph.h"

int main() {
    graph G = {NULL};
    int choice;

    do {
        menu();
        cout << "Masukkan pilihan: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string newVertexID;
            cout << "Masukkan ID vertex: ";
            cin >> newVertexID;
            addVertex(G, newVertexID);
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
            string vertexID;
            cout << "Masukkan ID vertex yang akan dihapus: ";
            cin >> vertexID;
            deleteVertex(G, vertexID);
            break;
        }
        case 4: {
            string source, destination;
            cout << "Masukkan ID vertex sumber: ";
            cin >> source;
            cout << "Masukkan ID vertex tujuan: ";
            cin >> destination;
            deleteEdge(G, source, destination);
            break;
        }
        case 8:
            cout << "Keluar dari program." << endl;
            break;
        default:
            cout << "Pilihan tidak valid. Coba lagi." << endl;
        }
    } while (choice != 8);

    return 0;
}
