#include <iostream>
#include <vector>

using namespace std;

void resolverCaso() {
    int k;
    cin >> k; // Ignoroar

    vector<int> estudiantes(20);
    for (int i = 0; i < 20; i++) {
        cin >> estudiantes[i];
    }

    vector<int> fila;
    int total_pasos = 0;

    for (int i = 0; i < 20; i++) {
        int altura = estudiantes[i];
        int j = 0;

        while (j < fila.size() && fila[j] <= altura) {
            j++;
        }

        total_pasos += (fila.size() - j);

        fila.insert(fila.begin() + j, altura);
    }

    cout << k << " " << total_pasos <<endl;
}

int main() {

    int p;
    if (cin >> p) {
        while (p--) {
            resolverCaso();
        }
    }

    return 0;
}
