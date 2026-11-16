#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <filesystem>
#include <algorithm>

using namespace std;
namespace fs = filesystem;

typedef vector<vector<int>> Matrix;

// ── Prototipos (implementados en sus respectivos .cpp) ──────────────────
Matrix naive(Matrix& A, Matrix& B);
Matrix strassen(Matrix& A, Matrix& B);

// ── Lectura de matriz desde archivo ─────────────────────────────────────
Matrix leerMatriz(const string& path) {
    ifstream file(path);
    Matrix M;
    string linea;
    while (getline(file, linea)) {
        vector<int> fila;
        istringstream ss(linea);
        int val;
        while (ss >> val)
            fila.push_back(val);
        if (!fila.empty())
            M.push_back(fila);
    }
    return M;
}

// ── Medición de memoria RAM (Linux) ─────────────────────────────────────
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

// ── Ejecutar y medir un algoritmo ───────────────────────────────────────
struct Medicion {
    double tiempo_ms;
    long memoria_kb;
};

Medicion medir(Matrix& A, Matrix& B, Matrix (*algoritmo)(Matrix&, Matrix&)) {
    long mem_antes = leerMemoriaKB();

    auto inicio = chrono::high_resolution_clock::now();
    Matrix C = algoritmo(A, B);
    auto fin   = chrono::high_resolution_clock::now();

    long mem_despues = leerMemoriaKB();

    double tiempo = chrono::duration<double, milli>(fin - inicio).count();
    long   memoria = mem_despues - mem_antes;

    return {tiempo, memoria};
}

// ── Parsear nombre de archivo ────────────────────────────────────────────
// Formato: {n}_{tipo}_{dominio}_{muestra}_1.txt
struct InfoArchivo {
    int    n;
    string tipo;
    string dominio;
    string muestra;
};

InfoArchivo parsearNombre(const string& nombre) {
    // Quitar extensión
    string base = nombre.substr(0, nombre.rfind(".txt"));
    // Quitar sufijo _1 o _2
    base = base.substr(0, base.rfind("_"));

    istringstream ss(base);
    string token;
    vector<string> partes;
    while (getline(ss, token, '_'))
        partes.push_back(token);

    // partes = [n, tipo, dominio, muestra]
    return {stoi(partes[0]), partes[1], partes[2], partes[3]};
}

// ── Main ─────────────────────────────────────────────────────────────────
int main() {
    string inputDir  = "data/matrix_input";
    string outputDir = "data/measurements";
    string outputCSV = outputDir + "/resultados.csv";

    fs::create_directories(outputDir);
    fs::create_directories("data/matrix_output");

    ofstream csv(outputCSV);
    csv << "n,tipo,dominio,muestra,algoritmo,tiempo_ms,memoria_kb\n";

    for (auto& entry : fs::directory_iterator(inputDir)) {
        string filename = entry.path().filename().string();
        if (filename.find("_1.txt") == string::npos) continue;

        string path1 = entry.path().string();
        string path2 = path1;
        path2.replace(path2.rfind("_1.txt"), 6, "_2.txt");

        if (!fs::exists(path2)) {
            cerr << "No se encontró el par: " << path2 << "\n";
            continue;
        }

        InfoArchivo info = parsearNombre(filename);
        Matrix A = leerMatriz(path1);
        Matrix B = leerMatriz(path2);

        cout << "Procesando n=" << info.n
             << " tipo="    << info.tipo
             << " dominio=" << info.dominio
             << " muestra=" << info.muestra << "\n";

        // Medir Naive
        Medicion m_naive = medir(A, B, naive);
        csv << info.n << "," << info.tipo << "," << info.dominio << ","
            << info.muestra << ",naive,"
            << m_naive.tiempo_ms << "," << m_naive.memoria_kb << "\n";

        // Medir Strassen
        Medicion m_strassen = medir(A, B, strassen);
        csv << info.n << "," << info.tipo << "," << info.dominio << ","
            << info.muestra << ",strassen,"
            << m_strassen.tiempo_ms << "," << m_strassen.memoria_kb << "\n";

        // Guardar matriz resultado en matrix_output
        string outputName = filename;
        outputName.replace(outputName.rfind("_1.txt"), 6, "_out.txt");
        string outputPath = "data/matrix_output/" + outputName;
        ofstream outFile(outputPath);
        Matrix C = naive(A, B);
        for (auto& fila : C) {
            for (int i = 0; i < fila.size(); i++) {
                outFile << fila[i];
                if (i < (int)fila.size() - 1) outFile << " ";
            }
            outFile << "\n";
        }
    }

    csv.close();
    cout << "Resultados guardados en " << outputCSV << "\n";
    return 0;
}
