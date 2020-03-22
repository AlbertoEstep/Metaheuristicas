# Variables
SRC=./src
BIN=./bin
ENTRADA=./entrada
# Compilamos con: -Wall (para mostrar todos los warnings) -O2 (para optimizar el código)
OPT=-Wall -O2

all: clean P1GreedyEjemplos P1busquedaLocalEjemplos

# Compilación
$(BIN)/greedy:
	g++ $(OPT) $(SRC)/greedy.cpp -o $(BIN)/greedy

$(BIN)/busquedaLocal:
	g++ $(OPT) $(SRC)/busquedaLocal.cpp -o $(BIN)/busquedaLocal

# Ejemplo
P1GreedyEjemplos: $(BIN)/greedy $(SRC)/greedy.cpp
	$(BIN)/greedy < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/greedy < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/greedy < $(ENTRADA)/MDG-a_31_n2000_m200.txt

P1busquedaLocalEjemplos: $(BIN)/busquedaLocal $(SRC)/busquedaLocal.cpp
	$(BIN)/busquedaLocal < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/MDG-a_31_n2000_m200.txt

ResultadosGreedy: $(BIN)/greedy $(SRC)/greedy.cpp $(BIN)/busquedaLocal $(SRC)/busquedaLocal.cpp
	$(BIN)/greedy < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/greedy < $(ENTRADA)/GKD-c_12_n500_m50.txt
	$(BIN)/greedy < $(ENTRADA)/GKD-c_13_n500_m50.txt
	$(BIN)/greedy < $(ENTRADA)/GKD-c_14_n500_m50.txt
	$(BIN)/greedy < $(ENTRADA)/GKD-c_15_n500_m50.txt
	$(BIN)/greedy < $(ENTRADA)/GKD-c_16_n500_m50.txt
	$(BIN)/greedy < $(ENTRADA)/GKD-c_17_n500_m50.txt
	$(BIN)/greedy < $(ENTRADA)/GKD-c_18_n500_m50.txt
	$(BIN)/greedy < $(ENTRADA)/GKD-c_19_n500_m50.txt
	$(BIN)/greedy < $(ENTRADA)/GKD-c_20_n500_m50.txt
	$(BIN)/greedy < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/greedy < $(ENTRADA)/MDG-b_2_n500_m50.txt
	$(BIN)/greedy < $(ENTRADA)/MDG-b_3_n500_m50.txt
	$(BIN)/greedy < $(ENTRADA)/MDG-b_4_n500_m50.txt
	$(BIN)/greedy < $(ENTRADA)/MDG-b_5_n500_m50.txt
	$(BIN)/greedy < $(ENTRADA)/MDG-b_6_n500_m50.txt
	$(BIN)/greedy < $(ENTRADA)/MDG-b_7_n500_m50.txt
	$(BIN)/greedy < $(ENTRADA)/MDG-b_8_n500_m50.txt
	$(BIN)/greedy < $(ENTRADA)/MDG-b_9_n500_m50.txt
	$(BIN)/greedy < $(ENTRADA)/MDG-b_10_n500_m50.txt
	$(BIN)/greedy < $(ENTRADA)/MDG-a_31_n2000_m200.txt
	$(BIN)/greedy < $(ENTRADA)/MDG-a_32_n2000_m200.txt
	$(BIN)/greedy < $(ENTRADA)/MDG-a_33_n2000_m200.txt
	$(BIN)/greedy < $(ENTRADA)/MDG-a_34_n2000_m200.txt
	$(BIN)/greedy < $(ENTRADA)/MDG-a_35_n2000_m200.txt
	$(BIN)/greedy < $(ENTRADA)/MDG-a_36_n2000_m200.txt
	$(BIN)/greedy < $(ENTRADA)/MDG-a_37_n2000_m200.txt
	$(BIN)/greedy < $(ENTRADA)/MDG-a_38_n2000_m200.txt
	$(BIN)/greedy < $(ENTRADA)/MDG-a_39_n2000_m200.txt
	$(BIN)/greedy < $(ENTRADA)/MDG-a_40_n2000_m200.txt

ResultadosBusquedaLocal: $(BIN)/greedy $(SRC)/greedy.cpp $(BIN)/busquedaLocal $(SRC)/busquedaLocal.cpp
	$(BIN)/busquedaLocal < $(ENTRADA)/GKD-c_11_n500_m50.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/GKD-c_12_n500_m50.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/GKD-c_13_n500_m50.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/GKD-c_14_n500_m50.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/GKD-c_15_n500_m50.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/GKD-c_16_n500_m50.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/GKD-c_17_n500_m50.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/GKD-c_18_n500_m50.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/GKD-c_19_n500_m50.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/GKD-c_20_n500_m50.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/MDG-b_1_n500_m50.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/MDG-b_2_n500_m50.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/MDG-b_3_n500_m50.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/MDG-b_4_n500_m50.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/MDG-b_5_n500_m50.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/MDG-b_6_n500_m50.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/MDG-b_7_n500_m50.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/MDG-b_8_n500_m50.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/MDG-b_9_n500_m50.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/MDG-b_10_n500_m50.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/MDG-a_31_n2000_m200.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/MDG-a_32_n2000_m200.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/MDG-a_33_n2000_m200.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/MDG-a_34_n2000_m200.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/MDG-a_35_n2000_m200.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/MDG-a_36_n2000_m200.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/MDG-a_37_n2000_m200.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/MDG-a_38_n2000_m200.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/MDG-a_39_n2000_m200.txt
	$(BIN)/busquedaLocal < $(ENTRADA)/MDG-a_40_n2000_m200.txt

clean:
	rm -f $(BIN)/*
