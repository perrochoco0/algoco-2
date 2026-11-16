## Entrega
La entrega se realiza vía **aula.usm.cl** en formato `.zip`.

## Multiplicación de matrices

### Programa principal
`matrix_multiplication.cpp` lee los pares de matrices desde `data/matrix_input/`,
ejecuta los algoritmos Naive y Strassen, mide tiempo de ejecución y uso de memoria RAM,
y guarda los resultados en `data/measurements/resultados.csv`.

### Algoritmos
- **Naive** : multiplicación clásica $O(n^3)$ mediante tres
  loops anidados. Referencia: Cormen et al., *Introduction to Algorithms*, 4ª ed., MIT Press, 2022.
- **Strassen** : algoritmo recursivo $O(n^{2.807})$ basado en
  7 multiplicaciones de submatrices. Referencia: Cormen et al., *Introduction to Algorithms*,
  4ª ed., MIT Press, 2022.

### Scripts
- `matrix_generator.py`: genera los pares de matrices de entrada con los parámetros
  $n \in \{2^4, 2^6, 2^8, 2^{10}\}$, tipos (dispersa, diagonal, densa) y dominios (D0, D10).
- `plot_generator.py`: lee `data/measurements/resultados.csv` y genera gráficos PNG
  en `data/plots/`.

---

## Ordenamiento de arreglo unidimensional

### Programa principal
`sorting.cpp` lee los arreglos desde `data/array_input/`, ejecuta los tres algoritmos
de ordenamiento, mide tiempo de ejecución y uso de memoria RAM, y guarda los resultados
en `data/measurements/resultados.csv`.

### Algoritmos
- **QuickSort** (: implementación recursiva con selección de
  pivote por mediana de tres (primer, central y último elemento) y partición de Lomuto.
  Referencia: Cormen et al., *Introduction to Algorithms*, 4ª ed., MIT Press, 2022.
- **MergeSort** : implementación recursiva con subdivisión
  por mitades y fusión mediante dos punteros.
  Referencia: Cormen et al., *Introduction to Algorithms*, 4ª ed., MIT Press, 2022.
- **PatienceSort** : Implementeación modificada de dos fases.
  Referencia: https://leetcode.com/discuss/post/1129459/patience-sorting-dp-optimisation-by-praj-ecnm/
- **std::sort** : algoritmo Introsort de la librería estándar de C++.
  Referencia: Musser, D.R., *Introspective Sorting and Selection Algorithms*,
  Software: Practice and Experience, 27(8), 1997.

### Scripts
- `array_generator.py`: genera los arreglos de entrada con los parámetros
  $n \in \{10^1, 10^3, 10^5, 10^7\}$, tipos (ascendente, descendente, aleatorio)
  y dominios (D1, D7).
- `plot_generator.py`: lee `data/measurements/resultados.csv` y genera gráficos PNG
  en `data/plots/`.

---

## Ejecución makefile

Las reglas del makefile son iguales para ambas implementaciones.
Ejecutar desde el directorio respectivo (`sorting/` o `matrix_multiplication/`):

Las reglas del makefiles son iguales para ambas implementaciones.
Ubicado en el respectivo directorio de cada implementación:

* make: compila el codigo
* make run: ejecuta el programa principal de cada implementacion
* make generate: ejecuta el generator.py respectivo 
* make plot: ejecuta el plot_generator.py respectivo
* make clean: limpia los arreglos, matrices, los resultados y los plots de cada implementacion

---

## Mediciones
- **Tiempo**: medido con `chrono::high_resolution_clock` de C++17.
- **Memoria**: medido leyendo el campo `VmRSS` de `/proc/self/status` (Linux),
  que reporta la memoria física residente del proceso en kilobytes.
