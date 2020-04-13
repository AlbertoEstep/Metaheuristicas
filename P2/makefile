# Variables
SRC=./src
BIN=./bin
ENTRADA=./entrada
# Compilamos con: -Wall (para mostrar todos los warnings) -O2 (para optimizar el código)
OPT=-Wall -O2
SEMILLA=1234567

all: clean P2AGGuniformeEjemplos P2AGGposicionEjemplos P2AGEuniformeEjemplos

# Compilación
$(BIN)/AGG_uniforme:
	g++ $(OPT) $(SRC)/AGG_uniforme.cpp -o $(BIN)/AGG_uniforme

# Ejemplo
P2AGGuniformeEjemplos: $(BIN)/AGG_uniforme $(SRC)/AGG_uniforme.cpp
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/MDG-a_31_n2000_m200.txt

# Compilación
$(BIN)/AGG_posicion:
	g++ $(OPT) $(SRC)/AGG_posicion.cpp -o $(BIN)/AGG_posicion

# Ejemplo
P2AGGposicionEjemplos: $(BIN)/AGG_posicion $(SRC)/AGG_posicion.cpp
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/MDG-a_31_n2000_m200.txt

# Compilación
$(BIN)/AGE_uniforme:
	g++ $(OPT) $(SRC)/AGE_uniforme.cpp -o $(BIN)/AGE_uniforme

# Ejemplo
P2AGEuniformeEjemplos: $(BIN)/AGE_uniforme $(SRC)/AGE_uniforme.cpp
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/MDG-a_31_n2000_m200.txt


clean:
	rm -f $(BIN)/*
