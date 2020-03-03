#include <iostream>
#include <vector>
#include <set>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

using namespace std;

/* Rellena la matriz de distancias

Parametros:
  - m = matriz de distancias
*/

void leerDatos(vector<vector<double>> &m){
  double distancia;
  for (unsigned i = 1; i < m.size(); i++) {
    for (unsigned j = i + 1; j < m.size(); j++) {
      cin >> distancia >> distancia >> distancia;
      m[i][j] = m[j][i] = distancia;
    }
  }
}


/* Dado un conjunto de elementos y un elemento concreto, calcula la distancia
acumulada entre el elemento y el conjunto de elementos.

Parametros:
  - elemento = elemento a calcular la distancia con los demás
  - conjunto = conjunto de elementos a contar su distancia
  - m = matriz de distancias
*/
double distanciaAUnConjunto(int elemento, set<int> &conjunto, vector<vector<double>> &m) {
  set<int>::iterator it;
  double suma = 0;

  for(it = conjunto.begin(); it != conjunto.end(); ++it)
    suma += m[elemento][*it];

  return suma;
}

/* Dado dos conjuntos de elementos calcula el elemento entre los del primer conjunto
(el de seleccionados) cuya distancia acumulada al otro conjunto es mayor.

Parametros:
  - seleccionados = conjunto de elementos entre los que se elige el elemento más lejano
  - no_seleccionados = conjunto de elementos a calcular la distancia
  - m = matriz de distancias
*/

int masLejanoEntreSeleccionados(set<int> &seleccionados, set<int> &no_seleccionados, vector<vector<double>> &m) {
  int solucion;
  double distancia_maxima, distancia_actual;
  set<int>::iterator it;

  it = no_seleccionados.begin();
  solucion = *it;
  distancia_maxima = distanciaAUnConjunto(solucion, seleccionados, m);

  for(; it != no_seleccionados.end(); ++it){
    distancia_actual = distanciaAUnConjunto(*it, seleccionados, m);
    if(distancia_actual > distancia_maxima){
      distancia_maxima = distancia_actual;
      solucion = *it;
    }
  }
  return solucion;
}

/* Aplica el algoritmo greedy

Parametros:
  - m = matriz de distancias
  - n_a_seleccionar = numero de elementos a seleccionar
*/
void greedy(vector<vector<double>> &m, unsigned n_a_seleccionar){
  set<int> seleccionados, no_seleccionados;
  int elem_lejano;
  clock_t t_total, t_inicio;

  t_inicio = clock();
  for(unsigned i = 0; i < m.size(); i++)
    no_seleccionados.insert(i);

  // Calculo el elemento de mayor distancia entre todos
  elem_lejano = masLejanoEntreSeleccionados(no_seleccionados, no_seleccionados, m);
  seleccionados.insert(elem_lejano);
  no_seleccionados.erase(elem_lejano);

  while(seleccionados.size() < n_a_seleccionar){
    elem_lejano = masLejanoEntreSeleccionados(seleccionados, no_seleccionados, m);
    seleccionados.insert(elem_lejano);
    no_seleccionados.erase(elem_lejano);
  }

  t_total = clock() - t_inicio;
  cout << "Tiempo consumido: " << (double) t_total / CLOCKS_PER_SEC << endl;
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
