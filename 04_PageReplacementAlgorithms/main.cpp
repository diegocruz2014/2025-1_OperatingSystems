#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

// Algoritmo LRU
int lru(const vector<int>& pages, int frames) {
    list<int> memory; // Lista que almacenará las páginas en memoria
    unordered_map<int, list<int>::iterator> pagesMap;
    int pagesFaults = 0; // contador de fallos de páginas

    // Ciclo para elaborar el proceso con cada página
    for (int page : pages) {
        // Si la página ya está en memoria, se elimina de su posición actual
        if (pagesMap.find(page) != pagesMap.end()) {
            memory.erase(pagesMap[page]);
        }
        // Si la página no se encuentra en memoria, se almacenará
        else {
            // Si la memoria está llena, se elimina la página menos utilizada; es
            // decir, la última en la lista
            if (memory.size() >= frames) {
                int lruPage = memory.back();
                memory.pop_back();
                pagesMap.erase(lruPage);
            }
            pagesFaults++;
        }
        // Se adiciona la nueva página al inicio de la lista
        memory.push_front(page);
        pagesMap[page] = memory.begin();

        // Mostrar el estado actual de la memoria caché
        cout << "Estado actual de la memoria caché: ";
        for (int p : memory) cout << p << " ";
        cout << "| Fallos: " << pagesFaults << endl;
    }
    // Retornar la cantidad de fallos de páginas
    return pagesFaults;
}

// Algoritmo FIFO
int fifo(const vector<int>& pages, int frames) {
    queue<int> memory; // Se utiliza una cola para almacenar el orden de llegada de las páginas en memoria
    unordered_map<int, bool> inMemory; // Se usa un mapa para saber qué páginas están en memoria
    bool found; // Bandera para señalar que se encontró una página en memoria
    int pageFaults = 0; // Contador de fallos de página

    // Elaborar el proceso para cada una de las páginas
    for (int page : pages) {
        found = false;
        if(!inMemory[page]) { // Si no se encuentra una página en memoria
            pageFaults++;
            if (memory.size() == frames) {
                // Si la memoria caché está llena se elimina la primera página en la memoria
                int removed = memory.front();
                memory.pop();
                inMemory[removed] = false;
            }
            memory.push(page);
            inMemory[page] = true;
        }
        else found = true;

        // Mostramos el estado actual de la memoria caché
        cout << "Estado actual de la memoria caché: ";
        queue<int> copy = memory;
        while(!copy.empty()) {
            cout << copy.front() << " ";
            copy.pop();
        }
        cout << "| Fallos: " << pageFaults;
        if(found) cout << " | La página " << page << " ya está en memoria.";
        cout << endl;
    }
    return pageFaults;
}


// Función principal
int main() {
    // Crear las variables para la memoria caché y la cantidad de
    // páginas que se obtendrá
    int frames, numPages;
    cout << "Ingrese el tamaño de la memoria caché: ";
    cin >> frames;
    cout << "Ingrese la cantidad de páginas que se procesará: ";
    cin >> numPages;

    // Crear un arreglo que almacene las páginas ingresadas
    vector<int> pages(numPages);

    // Ingresar las páginas para almacenarlas en el arreglo creado
    cout << "Ingrese " << numPages << " números enteros separados por espacios para simular las páginas: ";
    for (int i = 0; i < numPages; i++) cin >> pages[i];

    // Crear cuatro valores enteros para recibir las fallas de cada
    // algoritmo procesado
    int f1, f2, f3, f4;

    cout << "Algoritmo LRU: " << endl;
    f1 = lru(pages, frames);

    cout << "\nAlgoritmo FIFO: " << endl;
    f2 = fifo(pages, frames);

    cout << "\nCantidad de fallos de página en cada algoritmo: " << endl;
    cout << "LRU: " << f1 << endl;
    cout << "FIFO: " << f2 << endl;
    return 0;
}

