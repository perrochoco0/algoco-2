#include <vector>
#include <queue>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<vector<int>> generarPilas(const vector<int>& arr) {
    vector<vector<int>> pilas;
    vector<int> tops;

    for (int x : arr) {
        auto it = lower_bound(tops.begin(), tops.end(), x);

        if (it == tops.end()) {
            pilas.push_back(vector<int>{x});
            tops.push_back(x);
        } else {
            int idx = distance(tops.begin(), it);
            pilas[idx].push_back(x);
            *it = x;
        }
    }

    return pilas;
}

vector<int> fusionarPilas(vector<vector<int>>& pilas, int n) {
    vector<int> arr_ordenado;
    arr_ordenado.reserve(n);

    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > min_heap;

    for (int i = 0; i < pilas.size(); i++) {
        if (!pilas[i].empty()) {
            min_heap.push({pilas[i].back(), i});
        }
    }

    while (!min_heap.empty()) {
        auto [valor, indice_pila] = min_heap.top();
        min_heap.pop();

        arr_ordenado.push_back(valor);
        pilas[indice_pila].pop_back();

        if (!pilas[indice_pila].empty()) {
            min_heap.push({pilas[indice_pila].back(), indice_pila});
        }
    }

    return arr_ordenado;
}


/*
Patiencesort:
Aplica un separamiento Patience en el arreglo para generar
pilas k pilas (k <= n). Luego recorre los tops de las pilas
buscando siempre el top menor para ir armando el arreglo final
ordenado de forma ascendente.
Complejidad: O(n log(k))
*/

vector<int> patiencesortArray(const vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) return arr;

    vector<vector<int>> pilas = generarPilas(arr);

    return fusionarPilas(pilas, n);
}
