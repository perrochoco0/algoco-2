#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <filesystem>
using namespace std;
namespace fs = filesystem;

// ── Prototipos ───────────────────────────────────────────────────────────
vector<int> mergesortArray(vector<int>& arr);
vector<int> quicksortArray(vector<int>& arr);
vector<int> patiencesortArray(vector<int>& arr);
vector<int> sortArray(vector<int>& arr);

// ── Lectura de arreglo ───────────────────────────────────────────────────
vector<int> leerArreglo(const string& path) {
    ifstream file(path);
    vector<int> arr;
    int val;
    while (file >> val)
        arr.push_back(val);
    return arr;
}

// ── Medición de memoria RAM ──────────────────────────────────────────────
long leerMemoriaKB() {
    ifstream file("/proc/self/status");
    string linea;
    while (getline(file, linea)) {
        if (linea.rfind("VmRSS:", 0) == 0) {
            long kb;
            sscanf(linea.c_str(), "VmRSS: %ld kB", &kb);
            return kb;
        }
    }
    return -1;
}

// ── Struct y función de medición ─────────────────────────────────────────
struct Medicion {
    double tiempo_ms;
    long   memoria_kb;
};

Medicion medir(vector<int> arr, vector<int> (*algoritmo)(vector<int>&)) {
    long mem_antes = leerMemoriaKB();
    auto inicio    = chrono::high_resolution_clock::now();

    vector<int> resultado = algoritmo(arr);

    auto fin         = chrono::high_resolution_clock::now();
    long mem_despues = leerMemoriaKB();

    return {
        chrono::duration<double, milli>(fin - inicio).count(),
        mem_despues - mem_antes
    };
}

// ── Parsear nombre de archivo ─────────────────────────────────────────────
struct InfoArchivo {
    int    n;
    string tipo;
    string dominio;
    string muestra;
};

InfoArchivo parsearNombre(const string& nombre) {
    string base = nombre.substr(0, nombre.rfind(".txt"));
    istringstream ss(base);
    string token;
    vector<string> partes;
    while (getline(ss, token, '_'))
        partes.push_back(token);
    return {stoi(partes[0]), partes[1], partes[2], partes[3]};
}

// ── Escribir medición en CSV ──────────────────────────────────────────────
void escribir(ofstream& csv, InfoArchivo& info,const string& alg, Medicion& m) {
    csv << info.n       << ","
        << info.tipo    << ","
        << info.dominio << ","
        << info.muestra << ","
        << alg          << ","
        << m.tiempo_ms  << ","
        << m.memoria_kb << "\n";
}

// Main
int main() {
    string inputDir  = "data/array_input";
    string outputDir = "data/measurements";
    string outputCSV = outputDir + "/resultados.csv";

    ofstream csv(outputCSV);
    csv << "n,tipo,dominio,muestra,algoritmo,tiempo_ms,memoria_kb\n";

    for (auto& entry : fs::directory_iterator(inputDir)) {
        string filename = entry.path().filename().string();
        if (filename.find(".txt") == string::npos) continue;

        InfoArchivo info = parsearNombre(filename);
        vector<int> arr  = leerArreglo(entry.path().string());

        cout << "Procesando n=" << info.n
             << " tipo="     << info.tipo
             << " dominio="  << info.dominio
             << " muestra="  << info.muestra << "\n";

        Medicion mq = medir(arr, quicksortArray);
        escribir(csv, info, "quicksort", mq);

        Medicion mm = medir(arr, mergesortArray);
        escribir(csv, info, "mergesort", mm);

        Medicion mp = medir(arr, mergesortArray);
        escribir(csv, info, "patiencesort", mp);

        Medicion ms = medir(arr, sortArray);
        escribir(csv, info, "sort", ms);


        string outputPath = "data/array_output/" + filename;
        ofstream outFile(outputPath);
        vector<int> ordenado = sortArray(arr);  // usar sort para el output final
        for (int i = 0; i < ordenado.size(); i++) {
            outFile << ordenado[i];
            if (i < ordenado.size() - 1) outFile << " ";
        }
        outFile << "\n";




    }

    csv.close();
    cout << "Resultados guardados en " << outputCSV << "\n";
    return 0;
}
