CXX      = g++
CXXFLAGS = -std=c++17 -O2

# Archivos fuente
SRCS =  sorting.cpp \
		algorithms/mergesort.cpp \
		algorithms/quicksort.cpp \
		algorithms/patiencesort.cpp \
		algorithms/sort.cpp

TARGET = sorting

# Instrucciones
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
	rm -f data/measurements/*
	rm -f data/array_input/*
	rm -f data/array_output/*
	rm -f data/plots/*

generate:
	python3 scripts/array_generator.py

plot:
	python3 scripts/plot_generator.py
