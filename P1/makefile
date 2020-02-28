# Variables
SRC=./src
BIN=./bin
ENTRADA=./entrada
# Compilamos con: -Wall (para mostrar todos los warnings) -O2 (para optimizar el código)
OPT=-Wall -O2

all: P1greedy

# Compilación
$(BIN)/greedy:
	g++ $(OPT) $(SRC)/greedy.cpp -o $(BIN)/greedy

# Ejemplo
P1greedy: $(BIN)/greedy $(SRC)/greedy.cpp
	$(BIN)/greedy < $(ENTRADA)/GKD-c_11_n500_m50.txt

clean:
	rm -f $(BIN)/*
