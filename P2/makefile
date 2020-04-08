# Variables
SRC=./src
BIN=./bin
ENTRADA=./entrada
# Compilamos con: -Wall (para mostrar todos los warnings) -O2 (para optimizar el código)
OPT=-Wall -O2
SEMILLA=1234567

all: clean P2AGGuniformeEjemplos

# Compilación
$(BIN)/AGG_uniforme:
	g++ $(OPT) $(SRC)/AGG_uniforme.cpp -o $(BIN)/AGG_uniforme

# Ejemplo
P2AGGuniformeEjemplos: $(BIN)/AGG_uniforme $(SRC)/AGG_uniforme.cpp
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/MDG-a_31_n2000_m200.txt


# Compilación
#$(BIN)/AGG_uniforme:
#	g++ $(OPT) $(SRC)/AGGu.cpp -o $(BIN)/AGG_uniforme
# Ejemplo

#P2AGGuniformeEjemplos: $(BIN)/AGG_uniforme $(SRC)/AGGu.cpp
#	$(BIN)/AGG_uniforme < $(ENTRADA)/GKD-c_11_n500_m50.txt
#	$(BIN)/AGG_uniforme < $(ENTRADA)/MDG-b_1_n500_m50.txt
#	$(BIN)/AGG_uniforme < $(ENTRADA)/MDG-a_31_n2000_m200.txt

clean:
	rm -f $(BIN)/*
