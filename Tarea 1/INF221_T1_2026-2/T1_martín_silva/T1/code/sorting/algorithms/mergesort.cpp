#include <vector>

using namespace std;

vector<int> mergear(vector<int>& izq, vector<int>& der) {
    vector<int> resultado;
    int i = 0, j = 0;

    while (i < izq.size() && j < der.size()) {
        if (izq[i] <= der[j]) {
            resultado.push_back(izq[i++]);
        } else {
            resultado.push_back(der[j++]);
        }
    }

    while (i < izq.size()) resultado.push_back(izq[i++]);
    while (j < der.size()) resultado.push_back(der[j++]);

    return resultado;
}


/*
Mergesort:
Divide el arreglo de forma recursiva, separando hasta
redur el arreglo a varios sub arreglos de tamaño 1,
luego reliza un "merge" hacia arriba por cada sub
arreglo hasta retornar el arreglo ordenado
Complejidad: O(n log(n))
*/
vector<int> mergesortArray(vector<int>& arr) {
    if (arr.size() <= 1) return arr;

    int mid = arr.size() / 2;

    vector<int> izq(arr.begin(), arr.begin() + mid);
    vector<int> der(arr.begin() + mid, arr.end());

    izq = mergesortArray(izq);
    der = mergesortArray(der);

    return mergear(izq, der);
}
