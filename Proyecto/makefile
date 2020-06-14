# Variables
SRC=./src
BIN=./bin
ENTRADA=./entrada
# Compilamos con: -Wall (para mostrar todos los warnings) -O2 (para optimizar el código)
OPT=-Wall -O2
SEMILLA=1234567

all: clean CSEjemplos CS_MEJORAEjemplos

# Compilación
$(BIN)/CS:
	g++ $(OPT) $(SRC)/CS.cpp -o $(BIN)/CS

# Ejemplo
CSEjemplos: $(BIN)/CS $(SRC)/CS.cpp
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/MDG-a_31_n2000_m200.txt

# Compilación
$(BIN)/CS_MEJORA:
	g++ $(OPT) $(SRC)/CS_MEJORA.cpp -o $(BIN)/CS_MEJORA

# Ejemplo
CS_MEJORAEjemplos: $(BIN)/CS_MEJORA $(SRC)/CS_MEJORA.cpp
	$(BIN)/CS_MEJORA $(SEMILLA) < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/CS_MEJORA $(SEMILLA) < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/CS_MEJORA $(SEMILLA) < $(ENTRADA)/MDG-a_31_n2000_m200.txt

CSResultados: $(BIN)/CS $(SRC)/CS.cpp
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/GKD-c_12_n500_m50.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/GKD-c_13_n500_m50.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/GKD-c_14_n500_m50.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/GKD-c_15_n500_m50.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/GKD-c_16_n500_m50.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/GKD-c_17_n500_m50.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/GKD-c_18_n500_m50.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/GKD-c_19_n500_m50.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/GKD-c_20_n500_m50.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/MDG-b_2_n500_m50.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/MDG-b_3_n500_m50.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/MDG-b_4_n500_m50.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/MDG-b_5_n500_m50.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/MDG-b_6_n500_m50.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/MDG-b_7_n500_m50.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/MDG-b_8_n500_m50.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/MDG-b_9_n500_m50.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/MDG-b_10_n500_m50.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/MDG-a_31_n2000_m200.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/MDG-a_32_n2000_m200.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/MDG-a_33_n2000_m200.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/MDG-a_34_n2000_m200.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/MDG-a_35_n2000_m200.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/MDG-a_36_n2000_m200.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/MDG-a_37_n2000_m200.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/MDG-a_38_n2000_m200.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/MDG-a_39_n2000_m200.txt
	$(BIN)/CS $(SEMILLA) < $(ENTRADA)/MDG-a_40_n2000_m200.txt

Resultados: clean CSResultados


clean:
	rm -f $(BIN)/*
