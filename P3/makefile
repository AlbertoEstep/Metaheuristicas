# Variables
SRC=./src
BIN=./bin
ENTRADA=./entrada
# Compilamos con: -Wall (para mostrar todos los warnings) -O2 (para optimizar el código)
OPT=-Wall -O2
SEMILLA=1234567

all: clean P3ESEjemplos P3BMBEjemplos P3ILSEjemplos P3ILSESEjemplos
Resultados: clean P3ESResultados P3BMBResultados P3ILSResultados P3ILSESResultados


# Compilación
$(BIN)/ES:
	g++ $(OPT) $(SRC)/ES.cpp -o $(BIN)/ES

# Ejemplo
P3ESEjemplos: $(BIN)/ES $(SRC)/ES.cpp
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/MDG-a_31_n2000_m200.txt

# Compilación
$(BIN)/BMB:
	g++ $(OPT) $(SRC)/BMB.cpp -o $(BIN)/BMB

# Ejemplo
P3BMBEjemplos: $(BIN)/BMB $(SRC)/BMB.cpp
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/MDG-a_31_n2000_m200.txt

# Compilación
$(BIN)/ILS:
	g++ $(OPT) $(SRC)/ILS.cpp -o $(BIN)/ILS

# Ejemplo
P3ILSEjemplos: $(BIN)/ILS $(SRC)/ILS.cpp
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/MDG-a_31_n2000_m200.txt

# Compilación
$(BIN)/ILS-ES:
	g++ $(OPT) $(SRC)/ILS-ES.cpp -o $(BIN)/ILS-ES

# Ejemplo
P3ILSESEjemplos: $(BIN)/ILS-ES $(SRC)/ILS-ES.cpp
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/MDG-a_31_n2000_m200.txt

P3ESResultados: $(BIN)/ES $(SRC)/ES.cpp
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/GKD-c_12_n500_m50.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/GKD-c_13_n500_m50.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/GKD-c_14_n500_m50.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/GKD-c_15_n500_m50.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/GKD-c_16_n500_m50.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/GKD-c_17_n500_m50.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/GKD-c_18_n500_m50.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/GKD-c_19_n500_m50.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/GKD-c_20_n500_m50.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/MDG-b_2_n500_m50.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/MDG-b_3_n500_m50.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/MDG-b_4_n500_m50.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/MDG-b_5_n500_m50.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/MDG-b_6_n500_m50.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/MDG-b_7_n500_m50.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/MDG-b_8_n500_m50.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/MDG-b_9_n500_m50.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/MDG-b_10_n500_m50.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/MDG-a_31_n2000_m200.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/MDG-a_32_n2000_m200.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/MDG-a_33_n2000_m200.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/MDG-a_34_n2000_m200.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/MDG-a_35_n2000_m200.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/MDG-a_36_n2000_m200.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/MDG-a_37_n2000_m200.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/MDG-a_38_n2000_m200.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/MDG-a_39_n2000_m200.txt
	$(BIN)/ES $(SEMILLA) < $(ENTRADA)/MDG-a_40_n2000_m200.txt

P3BMBResultados: $(BIN)/BMB $(SRC)/BMB.cpp
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/GKD-c_12_n500_m50.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/GKD-c_13_n500_m50.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/GKD-c_14_n500_m50.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/GKD-c_15_n500_m50.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/GKD-c_16_n500_m50.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/GKD-c_17_n500_m50.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/GKD-c_18_n500_m50.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/GKD-c_19_n500_m50.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/GKD-c_20_n500_m50.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/MDG-b_2_n500_m50.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/MDG-b_3_n500_m50.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/MDG-b_4_n500_m50.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/MDG-b_5_n500_m50.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/MDG-b_6_n500_m50.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/MDG-b_7_n500_m50.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/MDG-b_8_n500_m50.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/MDG-b_9_n500_m50.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/MDG-b_10_n500_m50.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/MDG-a_31_n2000_m200.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/MDG-a_32_n2000_m200.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/MDG-a_33_n2000_m200.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/MDG-a_34_n2000_m200.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/MDG-a_35_n2000_m200.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/MDG-a_36_n2000_m200.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/MDG-a_37_n2000_m200.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/MDG-a_38_n2000_m200.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/MDG-a_39_n2000_m200.txt
	$(BIN)/BMB $(SEMILLA) < $(ENTRADA)/MDG-a_40_n2000_m200.txt

P3ILSResultados: $(BIN)/ILS $(SRC)/ILS.cpp
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/GKD-c_12_n500_m50.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/GKD-c_13_n500_m50.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/GKD-c_14_n500_m50.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/GKD-c_15_n500_m50.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/GKD-c_16_n500_m50.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/GKD-c_17_n500_m50.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/GKD-c_18_n500_m50.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/GKD-c_19_n500_m50.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/GKD-c_20_n500_m50.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/MDG-b_2_n500_m50.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/MDG-b_3_n500_m50.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/MDG-b_4_n500_m50.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/MDG-b_5_n500_m50.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/MDG-b_6_n500_m50.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/MDG-b_7_n500_m50.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/MDG-b_8_n500_m50.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/MDG-b_9_n500_m50.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/MDG-b_10_n500_m50.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/MDG-a_31_n2000_m200.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/MDG-a_32_n2000_m200.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/MDG-a_33_n2000_m200.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/MDG-a_34_n2000_m200.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/MDG-a_35_n2000_m200.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/MDG-a_36_n2000_m200.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/MDG-a_37_n2000_m200.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/MDG-a_38_n2000_m200.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/MDG-a_39_n2000_m200.txt
	$(BIN)/ILS $(SEMILLA) < $(ENTRADA)/MDG-a_40_n2000_m200.txt

P3ILSESResultados: $(BIN)/ILS-ES $(SRC)/ILS-ES.cpp
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/GKD-c_12_n500_m50.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/GKD-c_13_n500_m50.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/GKD-c_14_n500_m50.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/GKD-c_15_n500_m50.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/GKD-c_16_n500_m50.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/GKD-c_17_n500_m50.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/GKD-c_18_n500_m50.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/GKD-c_19_n500_m50.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/GKD-c_20_n500_m50.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/MDG-b_2_n500_m50.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/MDG-b_3_n500_m50.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/MDG-b_4_n500_m50.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/MDG-b_5_n500_m50.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/MDG-b_6_n500_m50.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/MDG-b_7_n500_m50.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/MDG-b_8_n500_m50.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/MDG-b_9_n500_m50.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/MDG-b_10_n500_m50.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/MDG-a_31_n2000_m200.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/MDG-a_32_n2000_m200.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/MDG-a_33_n2000_m200.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/MDG-a_34_n2000_m200.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/MDG-a_35_n2000_m200.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/MDG-a_36_n2000_m200.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/MDG-a_37_n2000_m200.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/MDG-a_38_n2000_m200.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/MDG-a_39_n2000_m200.txt
	$(BIN)/ILS-ES $(SEMILLA) < $(ENTRADA)/MDG-a_40_n2000_m200.txt

clean:
	rm -f $(BIN)/*
