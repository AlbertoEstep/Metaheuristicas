# Variables
SRC=./src
BIN=./bin
ENTRADA=./entrada
# Compilamos con: -Wall (para mostrar todos los warnings) -O2 (para optimizar el código)
OPT=-Wall -O2

all: clean P1Greedy P1busquedaLocal

# Compilación
$(BIN)/greedy:
	g++ $(OPT) $(SRC)/greedy.cpp -o $(BIN)/greedy

$(BIN)/busquedaLocal:
	g++ $(OPT) $(SRC)/busquedaLocal.cpp -o $(BIN)/busquedaLocal

# Ejemplo
P1Greedy: $(BIN)/greedy $(SRC)/greedy.cpp
	$(BIN)/greedy < $(ENTRADA)/GKD-c_11_n500_m50.txt

P1busquedaLocal: $(BIN)/busquedaLocal $(SRC)/busquedaLocal.cpp
	$(BIN)/busquedaLocal < $(ENTRADA)/GKD-c_11_n500_m50.txt

clean:
	rm -f $(BIN)/*
