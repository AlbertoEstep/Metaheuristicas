#include <iostream>
#include <vector>
#include <set>

using namespace std;

// Computes the contribution of the element "elem" for the solution "sol" given
// AKA, the sum of the distances from elemet "elem" to each other element in sol

double singleContribution(set<int> &contenedor, vector<vector<double>> &m, int elemento) {
  double resultado = 0;
  set<int>::iterator it;
  for (it = contenedor.begin(); it != contenedor.end(); it++) {
    resultado += m[elemento][*it];
  }
  return resultado;
}

// Returns the element from "non_selected" that is the farthest from "selected"
int masLejanoEntreSeleccionados(set<int> &no_seleccionados, set<int> &seleccionados, vector<vector<double>> &m) {
  int elem_lejano;
  double max_sum_dist, actual_sum_dist;
  set<int>::iterator it;

  it = no_seleccionados.begin();
  elem_lejano = *it;
  max_sum_dist = singleContribution(seleccionados, m, elem_lejano);

  for (; it!=no_seleccionados.end(); it++) {
    actual_sum_dist = singleContribution(seleccionados, m, *it);
    if (actual_sum_dist > max_sum_dist) {
      max_sum_dist = actual_sum_dist;
      elem_lejano = *it;
    }
  }
  return elem_lejano;
}

// Returns the element that is the farthest from the rest of elements
int masLejanoDeTodos(vector<vector<double>> &m) {
  set<int> elementos;
  for (unsigned i = 0; i < m.size(); i++) {
    elementos.insert(i);
  }
  return masLejanoEntreSeleccionados(elementos, elementos, m);
}


void greedy(vector<vector<double>> &m, unsigned n_a_seleccionar){
  set<int> seleccionados, no_seleccionados;
  int elem_lejano;
  clock_t t_total, t_inicio;

  t_inicio = clock();
  for(unsigned i = 0; i < m.size(); i++){
    no_seleccionados.insert(i);
  }
  elem_lejano = masLejanoDeTodos(m);
  no_seleccionados.erase(elem_lejano);
  seleccionados.insert(elem_lejano);

  while(seleccionados.size() < n_a_seleccionar) {
    elem_lejano = masLejanoEntreSeleccionados(no_seleccionados, seleccionados, m);
    no_seleccionados.erase(elem_lejano);
    seleccionados.insert(elem_lejano);
  }
  t_total = clock() - t_inicio;
  cout << "\t" << (double) t_total / CLOCKS_PER_SEC << endl;
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


int main(){
  int n_total, n_sel; // n_total = número de elementos &&
                      // n_sel = el número de elementos a seleccionar del problema
  cin >> n_total >> n_sel; // inicializo los valores con la primera línea del fichero
  vector<double> v(n_total, 0);
  vector<vector<double>> m(n_total, v); // m = matriz de entradas

  leerDatos(m); // inicializo la matriz de entradas
  greedy(m, n_sel); // aplico el algoritmo greedy
}
