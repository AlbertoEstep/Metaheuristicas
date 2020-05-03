# Variables
SRC=./src
BIN=./bin
ENTRADA=./entrada
# Compilamos con: -Wall (para mostrar todos los warnings) -O2 (para optimizar el código)
OPT=-Wall -O2
SEMILLA=1234567

all: clean P3ESEjemplos

# Compilación
$(BIN)/ES:
	g++ $(OPT) $(SRC)/ES.cpp -o $(BIN)/ES

# Ejemplo
P3ESEjemplos: $(BIN)/ES $(SRC)/ES.cpp
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/MDG-a_31_n2000_m200.txt

clean:
	rm -f $(BIN)/*
