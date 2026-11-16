import pandas as pd
import matplotlib.pyplot as plt
import os

# ── Rutas ────────────────────────────────────────────────────────────────
INPUT_CSV  = "data/measurements/resultados.csv"
OUTPUT_DIR = "data/plots"
os.makedirs(OUTPUT_DIR, exist_ok=True)

# ── Cargar datos ─────────────────────────────────────────────────────────
df = pd.read_csv(INPUT_CSV)

# Promediar las 3 muestras (a, b, c)
df = df.groupby(["n", "tipo", "dominio", "algoritmo"], as_index=False).agg(
    tiempo_ms  = ("tiempo_ms",  "mean"),
    memoria_kb = ("memoria_kb", "mean")
)

ALGORITMOS = df["algoritmo"].unique()
COLORES    = {"quicksort": "#4C72B0", "mergesort": "#DD8452", "sort": "#55A868", "patiencesort": "#00CED1"}

# ── Gráfico 1: Tiempo vs N (líneas) ──────────────────────────────────────
def plot_tiempo_vs_n():
    data = df.groupby(["n", "algoritmo"], as_index=False)["tiempo_ms"].mean()

    plt.figure(figsize=(8, 5))
    for alg in ALGORITMOS:
        subset = data[data["algoritmo"] == alg].sort_values("n")
        plt.plot(subset["n"], subset["tiempo_ms"],
                 marker="o", label=alg, color=COLORES.get(alg))

    plt.xscale("log", base=10)
    plt.xlabel("n (tamaño del arreglo)")
    plt.ylabel("Tiempo promedio (ms)")
    plt.title("Tiempo de ejecución vs N")
    plt.legend()
    plt.tight_layout()
    plt.savefig(f"{OUTPUT_DIR}/tiempo_vs_n.png", dpi=150)
    plt.close()
    print("Guardado: tiempo_vs_n.png")

# ── Gráfico 2: Memoria vs N (líneas) ─────────────────────────────────────
def plot_memoria_vs_n():
    data = df.groupby(["n", "algoritmo"], as_index=False)["memoria_kb"].mean()

    plt.figure(figsize=(8, 5))
    for alg in ALGORITMOS:
        subset = data[data["algoritmo"] == alg].sort_values("n")
        plt.plot(subset["n"], subset["memoria_kb"],
                 marker="o", label=alg, color=COLORES.get(alg))

    plt.xscale("log", base=10)
    plt.xlabel("n (tamaño del arreglo)")
    plt.ylabel("Memoria promedio (KB)")
    plt.title("Uso de memoria vs N")
    plt.legend()
    plt.tight_layout()
    plt.savefig(f"{OUTPUT_DIR}/memoria_vs_n.png", dpi=150)
    plt.close()
    print("Guardado: memoria_vs_n.png")

# ── Gráfico 3: Tiempo por tipo de arreglo (barras) ───────────────────────
def plot_tiempo_por_tipo():
    data = df.groupby(["tipo", "algoritmo"], as_index=False)["tiempo_ms"].mean()
    tipos = data["tipo"].unique()

    x      = range(len(tipos))
    width  = 0.25
    fig, ax = plt.subplots(figsize=(8, 5))

    for i, alg in enumerate(ALGORITMOS):
        subset  = [
            data[(data["tipo"] == t) & (data["algoritmo"] == alg)]["tiempo_ms"].values
            for t in tipos
        ]
        valores = [v[0] if len(v) > 0 else 0 for v in subset]
        offset  = (i - len(ALGORITMOS) / 2 + 0.5) * width
        ax.bar([xi + offset for xi in x], valores,
               width=width, label=alg, color=COLORES.get(alg))

    ax.set_xticks(list(x))
    ax.set_xticklabels(tipos)
    ax.set_xlabel("Tipo de arreglo")
    ax.set_ylabel("Tiempo promedio (ms)")
    ax.set_title("Tiempo de ejecución por tipo de arreglo")
    ax.legend()
    plt.tight_layout()
    plt.savefig(f"{OUTPUT_DIR}/tiempo_por_tipo.png", dpi=150)
    plt.close()
    print("Guardado: tiempo_por_tipo.png")

# ── Gráfico 4: Tiempo por dominio (barras) ───────────────────────────────
def plot_tiempo_por_dominio():
    data     = df.groupby(["dominio", "algoritmo"], as_index=False)["tiempo_ms"].mean()
    dominios = data["dominio"].unique()

    x      = range(len(dominios))
    width  = 0.25
    fig, ax = plt.subplots(figsize=(8, 5))

    for i, alg in enumerate(ALGORITMOS):
        subset  = [
            data[(data["dominio"] == d) & (data["algoritmo"] == alg)]["tiempo_ms"].values
            for d in dominios
        ]
        valores = [v[0] if len(v) > 0 else 0 for v in subset]
        offset  = (i - len(ALGORITMOS) / 2 + 0.5) * width
        ax.bar([xi + offset for xi in x], valores,
               width=width, label=alg, color=COLORES.get(alg))

    ax.set_xticks(list(x))
    ax.set_xticklabels(dominios)
    ax.set_xlabel("Dominio")
    ax.set_ylabel("Tiempo promedio (ms)")
    ax.set_title("Tiempo de ejecución por dominio")
    ax.legend()
    plt.tight_layout()
    plt.savefig(f"{OUTPUT_DIR}/tiempo_por_dominio.png", dpi=150)
    plt.close()
    print("Guardado: tiempo_por_dominio.png")

# ── Gráfico 5: Tiempo por tipo separado por dominio (barras) ─────────────
def plot_tiempo_tipo_por_dominio():
    dominios = df["dominio"].unique()
    tipos    = df["tipo"].unique()

    fig, axes = plt.subplots(1, len(dominios), figsize=(14, 5), sharey=True)

    x     = range(len(tipos))
    width = 0.25

    for ax, dominio in zip(axes, dominios):
        data = df[df["dominio"] == dominio].groupby(
            ["tipo", "algoritmo"], as_index=False
        )["tiempo_ms"].mean()

        for i, alg in enumerate(ALGORITMOS):
            subset  = [
                data[(data["tipo"] == t) & (data["algoritmo"] == alg)]["tiempo_ms"].values
                for t in tipos
            ]
            valores = [v[0] if len(v) > 0 else 0 for v in subset]
            offset  = (i - len(ALGORITMOS) / 2 + 0.5) * width
            ax.bar([xi + offset for xi in x], valores,
                   width=width, label=alg, color=COLORES.get(alg))

        ax.set_xticks(list(x))
        ax.set_xticklabels(tipos, rotation=15)
        ax.set_title(f"Dominio: {dominio}")
        ax.set_xlabel("Tipo de arreglo")
        ax.legend()

    axes[0].set_ylabel("Tiempo promedio (ms)")
    fig.suptitle("Tiempo por tipo de arreglo separado por dominio")
    plt.tight_layout()
    plt.savefig(f"{OUTPUT_DIR}/tiempo_tipo_por_dominio.png", dpi=150)
    plt.close()
    print("Guardado: tiempo_tipo_por_dominio.png")

# ── Ejecutar todos ───────────────────────────────────────────────────────
if __name__ == "__main__":
    plot_tiempo_vs_n()
    plot_memoria_vs_n()
    plot_tiempo_por_tipo()
    plot_tiempo_por_dominio()
    plot_tiempo_tipo_por_dominio()
    print("Todos los gráficos generados.")
