CXX      = g++
CXXFLAGS = -std=c++17 -O2

# Archivos fuente
SRCS =  matrix_multiplication.cpp \
        algorithms/naive.cpp \
    	algorithms/strassen.cpp

TARGET = matrix_multiplication

# ── Reglas ────────────────────────────────────────────────────────────────
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
	rm -f data/measurements/*
	rm -f data/matrix_input/*
	rm -f data/matrix_output/*
	rm -f data/plots/*

generate:
	python3 scripts/matrix_generator.py

plot:
	python3 scripts/plot_generator.py
