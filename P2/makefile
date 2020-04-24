# Variables
SRC=./src
BIN=./bin
ENTRADA=./entrada
# Compilamos con: -Wall (para mostrar todos los warnings) -O2 (para optimizar el código)
OPT=-Wall -O2
SEMILLA=1234567

all: clean P2AGGuniformeEjemplos P2AGGposicionEjemplos P2AGEuniformeEjemplos P2AGEposicionEjemplos P2AMTipo0Ejemplos P2AMTipo1Ejemplos P2AMTipo2Ejemplos

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

# Compilación
$(BIN)/AGE_posicion:
	g++ $(OPT) $(SRC)/AGE_posicion.cpp -o $(BIN)/AGE_posicion

# Ejemplo
P2AGEposicionEjemplos: $(BIN)/AGE_posicion $(SRC)/AGE_posicion.cpp
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/MDG-a_31_n2000_m200.txt

# Compilación
$(BIN)/AM:
	g++ $(OPT) $(SRC)/AM.cpp -o $(BIN)/AM

# Ejemplo TIPO 0
P2AMTipo0Ejemplos: $(BIN)/AM $(SRC)/AM.cpp
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/MDG-a_31_n2000_m200.txt

# Ejemplo TIPO 1
P2AMTipo1Ejemplos: $(BIN)/AM $(SRC)/AM.cpp
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/MDG-a_31_n2000_m200.txt

# Ejemplo TIPO 2
P2AMTipo2Ejemplos: $(BIN)/AM $(SRC)/AM.cpp
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/MDG-a_31_n2000_m200.txt

P2AGGuniformeResultados: $(BIN)/AGG_uniforme $(SRC)/AGG_uniforme.cpp
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/GKD-c_12_n500_m50.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/GKD-c_13_n500_m50.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/GKD-c_14_n500_m50.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/GKD-c_15_n500_m50.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/GKD-c_16_n500_m50.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/GKD-c_17_n500_m50.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/GKD-c_18_n500_m50.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/GKD-c_19_n500_m50.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/GKD-c_20_n500_m50.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/MDG-b_2_n500_m50.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/MDG-b_3_n500_m50.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/MDG-b_4_n500_m50.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/MDG-b_5_n500_m50.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/MDG-b_6_n500_m50.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/MDG-b_7_n500_m50.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/MDG-b_8_n500_m50.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/MDG-b_9_n500_m50.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/MDG-b_10_n500_m50.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/MDG-a_31_n2000_m200.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/MDG-a_32_n2000_m200.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/MDG-a_33_n2000_m200.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/MDG-a_34_n2000_m200.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/MDG-a_35_n2000_m200.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/MDG-a_36_n2000_m200.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/MDG-a_37_n2000_m200.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/MDG-a_38_n2000_m200.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/MDG-a_39_n2000_m200.txt
	$(BIN)/AGG_uniforme $(SEMILLA) < $(ENTRADA)/MDG-a_40_n2000_m200.txt

P2AGGposicionResultados: $(BIN)/AGG_posicion $(SRC)/AGG_posicion.cpp
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/GKD-c_12_n500_m50.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/GKD-c_13_n500_m50.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/GKD-c_14_n500_m50.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/GKD-c_15_n500_m50.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/GKD-c_16_n500_m50.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/GKD-c_17_n500_m50.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/GKD-c_18_n500_m50.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/GKD-c_19_n500_m50.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/GKD-c_20_n500_m50.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/MDG-b_2_n500_m50.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/MDG-b_3_n500_m50.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/MDG-b_4_n500_m50.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/MDG-b_5_n500_m50.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/MDG-b_6_n500_m50.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/MDG-b_7_n500_m50.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/MDG-b_8_n500_m50.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/MDG-b_9_n500_m50.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/MDG-b_10_n500_m50.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/MDG-a_31_n2000_m200.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/MDG-a_32_n2000_m200.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/MDG-a_33_n2000_m200.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/MDG-a_34_n2000_m200.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/MDG-a_35_n2000_m200.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/MDG-a_36_n2000_m200.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/MDG-a_37_n2000_m200.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/MDG-a_38_n2000_m200.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/MDG-a_39_n2000_m200.txt
	$(BIN)/AGG_posicion $(SEMILLA) < $(ENTRADA)/MDG-a_40_n2000_m200.txt

P2AGEuniformeResultados: $(BIN)/AGE_uniforme $(SRC)/AGE_uniforme.cpp
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/GKD-c_12_n500_m50.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/GKD-c_13_n500_m50.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/GKD-c_14_n500_m50.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/GKD-c_15_n500_m50.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/GKD-c_16_n500_m50.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/GKD-c_17_n500_m50.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/GKD-c_18_n500_m50.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/GKD-c_19_n500_m50.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/GKD-c_20_n500_m50.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/MDG-b_2_n500_m50.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/MDG-b_3_n500_m50.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/MDG-b_4_n500_m50.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/MDG-b_5_n500_m50.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/MDG-b_6_n500_m50.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/MDG-b_7_n500_m50.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/MDG-b_8_n500_m50.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/MDG-b_9_n500_m50.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/MDG-b_10_n500_m50.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/MDG-a_31_n2000_m200.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/MDG-a_32_n2000_m200.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/MDG-a_33_n2000_m200.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/MDG-a_34_n2000_m200.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/MDG-a_35_n2000_m200.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/MDG-a_36_n2000_m200.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/MDG-a_37_n2000_m200.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/MDG-a_38_n2000_m200.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/MDG-a_39_n2000_m200.txt
	$(BIN)/AGE_uniforme $(SEMILLA) < $(ENTRADA)/MDG-a_40_n2000_m200.txt

P2AGEposicionResultados: $(BIN)/AGE_posicion $(SRC)/AGE_posicion.cpp
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/GKD-c_12_n500_m50.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/GKD-c_13_n500_m50.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/GKD-c_14_n500_m50.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/GKD-c_15_n500_m50.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/GKD-c_16_n500_m50.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/GKD-c_17_n500_m50.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/GKD-c_18_n500_m50.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/GKD-c_19_n500_m50.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/GKD-c_20_n500_m50.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/MDG-b_2_n500_m50.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/MDG-b_3_n500_m50.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/MDG-b_4_n500_m50.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/MDG-b_5_n500_m50.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/MDG-b_6_n500_m50.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/MDG-b_7_n500_m50.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/MDG-b_8_n500_m50.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/MDG-b_9_n500_m50.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/MDG-b_10_n500_m50.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/MDG-a_31_n2000_m200.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/MDG-a_32_n2000_m200.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/MDG-a_33_n2000_m200.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/MDG-a_34_n2000_m200.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/MDG-a_35_n2000_m200.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/MDG-a_36_n2000_m200.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/MDG-a_37_n2000_m200.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/MDG-a_38_n2000_m200.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/MDG-a_39_n2000_m200.txt
	$(BIN)/AGE_posicion $(SEMILLA) < $(ENTRADA)/MDG-a_40_n2000_m200.txt


P2AMTipo0Resultados: $(BIN)/AM $(SRC)/AM.cpp
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/GKD-c_12_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/GKD-c_13_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/GKD-c_14_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/GKD-c_15_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/GKD-c_16_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/GKD-c_17_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/GKD-c_18_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/GKD-c_19_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/GKD-c_20_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/MDG-b_2_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/MDG-b_3_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/MDG-b_4_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/MDG-b_5_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/MDG-b_6_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/MDG-b_7_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/MDG-b_8_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/MDG-b_9_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/MDG-b_10_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/MDG-a_31_n2000_m200.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/MDG-a_32_n2000_m200.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/MDG-a_33_n2000_m200.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/MDG-a_34_n2000_m200.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/MDG-a_35_n2000_m200.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/MDG-a_36_n2000_m200.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/MDG-a_37_n2000_m200.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/MDG-a_38_n2000_m200.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/MDG-a_39_n2000_m200.txt
	$(BIN)/AM $(SEMILLA) 0 < $(ENTRADA)/MDG-a_40_n2000_m200.txt

P2AMTipo1Resultados: $(BIN)/AM $(SRC)/AM.cpp
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/GKD-c_12_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/GKD-c_13_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/GKD-c_14_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/GKD-c_15_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/GKD-c_16_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/GKD-c_17_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/GKD-c_18_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/GKD-c_19_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/GKD-c_20_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/MDG-b_2_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/MDG-b_3_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/MDG-b_4_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/MDG-b_5_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/MDG-b_6_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/MDG-b_7_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/MDG-b_8_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/MDG-b_9_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/MDG-b_10_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/MDG-a_31_n2000_m200.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/MDG-a_32_n2000_m200.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/MDG-a_33_n2000_m200.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/MDG-a_34_n2000_m200.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/MDG-a_35_n2000_m200.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/MDG-a_36_n2000_m200.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/MDG-a_37_n2000_m200.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/MDG-a_38_n2000_m200.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/MDG-a_39_n2000_m200.txt
	$(BIN)/AM $(SEMILLA) 1 < $(ENTRADA)/MDG-a_40_n2000_m200.txt

P2AMTipo2Resultados: $(BIN)/AM $(SRC)/AM.cpp
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/GKD-c_12_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/GKD-c_13_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/GKD-c_14_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/GKD-c_15_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/GKD-c_16_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/GKD-c_17_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/GKD-c_18_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/GKD-c_19_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/GKD-c_20_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/MDG-b_2_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/MDG-b_3_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/MDG-b_4_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/MDG-b_5_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/MDG-b_6_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/MDG-b_7_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/MDG-b_8_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/MDG-b_9_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/MDG-b_10_n500_m50.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/MDG-a_31_n2000_m200.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/MDG-a_32_n2000_m200.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/MDG-a_33_n2000_m200.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/MDG-a_34_n2000_m200.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/MDG-a_35_n2000_m200.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/MDG-a_36_n2000_m200.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/MDG-a_37_n2000_m200.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/MDG-a_38_n2000_m200.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/MDG-a_39_n2000_m200.txt
	$(BIN)/AM $(SEMILLA) 2 < $(ENTRADA)/MDG-a_40_n2000_m200.txt

Resultados: clean P2AGGuniformeResultados P2AGGposicionResultados P2AGEuniformeResultados P2AGEposicionResultados P2AMTipo0Resultados P2AMTipo1Resultados P2AMTipo2Resultados


clean:
	rm -f $(BIN)/*
