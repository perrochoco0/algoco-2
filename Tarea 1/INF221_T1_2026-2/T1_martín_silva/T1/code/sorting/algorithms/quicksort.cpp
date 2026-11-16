#include <vector>
#include <random>
using namespace std;

static mt19937 rng(random_device{}());

void quicksortArray(vector<int>& arr, int low, int high) {
    if (low >= high) return;

    // pivote aleatorio
    uniform_int_distribution<int> dist(low, high);
    int pivot = arr[dist(rng)];

    int lt = low;
    int i  = low;
    int gt = high;

    while (i <= gt) {
        if (arr[i] < pivot) {
            swap(arr[lt++], arr[i++]);
        }
        else if (arr[i] > pivot) {
            swap(arr[i], arr[gt--]);
        }
        else {
            i++;
        }
    }

    quicksortArray(arr, low, lt - 1);
    quicksortArray(arr, gt + 1, high);
}


/*
Quicksort:
Elige un pivote según la regla de elegir 3 números al azar
y elegir la meidana de los 3. Luego utiliza el pivote para
ir comparando los elementos del arreglo y dejar los menores
a la izquierda del pivote, y los mayores a la derecha.
Al comparar todos "divide" el arreglo y repite los pases hasta
ordenar el arreglo.
Complejidad: O(n log (n))
*/
vector<int> quicksortArray(vector<int>& arr) {
    if (arr.empty()) return arr;
    quicksortArray(arr, 0, arr.size() - 1);
    return arr;
}
