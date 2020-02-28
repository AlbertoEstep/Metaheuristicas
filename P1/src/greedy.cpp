#include <iostream>
#include <vector>

using namespace std;

void greedy(vector<vector<double>> &m, unsigned n_a_seleccionar) {
  cout << "IMPLEMENTAR \n";
}

void leerDatos(vector<vector<double>> &m){
  unsigned i, j;
  double distancia;
  for (i = 1; i < m.size(); i++) {
    for (j = i + 1; j < m.size(); j++) {
      cin >> distancia >> distancia >> distancia;
      m[i][j] = m[j][i] = distancia;
    }
  }
}


int main(int argc, char *argv[]){
  int n_total, n_sel; // n_total = número de elementos &&
                      // n_sel = el número de elementos a seleccionar del problema
  cin >> n_total >> n_sel; // inicializo los valores con la primera línea del fichero
  vector<double> v(n_total, 0);
  vector<vector<double>> m(n_total, v); // m = matriz de entradas

  leerDatos(m); // inicializo la matriz de entradas
  greedy(m, n_sel); // aplico el algoritmo greedy
}
