#include <vector>
using namespace std;

typedef vector<vector<int>> Matrix;

/*
Funciones auxiliares: suma y resta de matrices
*/
Matrix addMatrix(Matrix& A, Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

Matrix subMatrix(Matrix& A, Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

/*
Funciones auxiliares: extraer y escribir submatrices
*/
Matrix getSubMatrix(Matrix& A, int rowStart, int colStart, int size) {
    Matrix sub(size, vector<int>(size, 0));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            sub[i][j] = A[rowStart + i][colStart + j];
    return sub;
}

void setSubMatrix(Matrix& C, Matrix& sub, int rowStart, int colStart) {
    int size = sub.size();
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[rowStart + i][colStart + j] = sub[i][j];
}

/*
Strassen:
Divide cada matriz en 4 submatrices y realiza
7 multiplicaciones recursivas en vez de 8.
Complejidad: O(n^2.807)
Asume que n es potencia de 2.
*/
Matrix strassen(Matrix& A, Matrix& B) {
    int n = A.size();

    // Caso base
    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    int half = n / 2;

    // Extraer submatrices
    Matrix A11 = getSubMatrix(A, 0,    0,    half);
    Matrix A12 = getSubMatrix(A, 0,    half, half);
    Matrix A21 = getSubMatrix(A, half, 0,    half);
    Matrix A22 = getSubMatrix(A, half, half, half);

    Matrix B11 = getSubMatrix(B, 0,    0,    half);
    Matrix B12 = getSubMatrix(B, 0,    half, half);
    Matrix B21 = getSubMatrix(B, half, 0,    half);
    Matrix B22 = getSubMatrix(B, half, half, half);

    // 7 productos de Strassen
    auto tmp1 = addMatrix(A11, A22);
    auto tmp2 = addMatrix(B11, B22);
    Matrix M1 = strassen(tmp1, tmp2);        // (A11+A22)(B11+B22)

    auto tmp3 = addMatrix(A21, A22);
    Matrix M2 = strassen(tmp3, B11);         // (A21+A22)B11

    auto tmp4 = subMatrix(B12, B22);
    Matrix M3 = strassen(A11, tmp4);         // A11(B12-B22)

    auto tmp5 = subMatrix(B21, B11);
    Matrix M4 = strassen(A22, tmp5);         // A22(B21-B11)

    auto tmp6 = addMatrix(A11, A12);
    Matrix M5 = strassen(tmp6, B22);         // (A11+A12)B22

    auto tmp7 = subMatrix(A21, A11);
    auto tmp8 = addMatrix(B11, B12);
    Matrix M6 = strassen(tmp7, tmp8);        // (A21-A11)(B11+B12)

    auto tmp9  = subMatrix(A12, A22);
    auto tmp10 = addMatrix(B21, B22);
    Matrix M7 = strassen(tmp9, tmp10);       // (A12-A22)(B21+B22)

    // Combinar resultados en C
    Matrix C(n, vector<int>(n, 0));

    auto c11_tmp1 = addMatrix(M1, M4);
    auto c11_tmp2 = subMatrix(M7, M5);
    auto C11 = addMatrix(c11_tmp1, c11_tmp2); // M1+M4-M5+M7

    auto C12 = addMatrix(M3, M5);             // M3+M5

    auto C21 = addMatrix(M2, M4);             // M2+M4

    auto c22_tmp1 = addMatrix(M1, M3);
    auto c22_tmp2 = subMatrix(M6, M2);
    auto C22 = addMatrix(c22_tmp1, c22_tmp2); // M1+M3-M2+M6

    setSubMatrix(C, C11, 0,    0);
    setSubMatrix(C, C12, 0,    half);
    setSubMatrix(C, C21, half, 0);
    setSubMatrix(C, C22, half, half);

    return C;
}
