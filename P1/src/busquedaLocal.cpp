#include <iostream>
#include <vector>
#include <unordered_set>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <stdlib.h>     /* srand, rand */
#include <algorithm>    // sort

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

struct solucion {
  vector<int> v;
  double evaluacion;
};

/* Dado un conjunto de elementos y un elemento concreto, calcula la distancia
acumulada entre el elemento y el conjunto de elementos.

Parametros:
  - elemento = elemento a calcular la distancia con los demás
  - conjunto = conjunto de elementos a contar su distancia
  - m = matriz de distancias
*/
double distanciaAUnConjunto(int elemento, vector<int> &conjunto, vector<vector<double>> &m){
  vector<int>::iterator it;
  double suma = 0;

  for(it = conjunto.begin(); it != conjunto.end(); ++it)
    suma += m[elemento][*it];

  return suma;
}

// Returns the fitness of the whole solution
double evaluacionSolucion(vector<int> &conjunto, vector<vector<double>> &m) {
  double evaluacion = 0;
  vector<int>::iterator it;
  for(it = conjunto.begin(); it != conjunto.end(); ++it)
    evaluacion += distanciaAUnConjunto(*it, conjunto, m);
  // Counting twice all the possible distances
  return evaluacion /= 2;
}

// Creates a random solution
// Prec.: Random seed already set
void solucionRandom(solucion &sol, int tam, int n_a_seleccionar){
  int seleccionados = 0, random;
  unordered_set<int> s;

  // Select 'n_a_seleccionar' elements
  while(seleccionados < n_a_seleccionar){
    random = rand() % tam;
    if(s.find(random) == s.end()){
      s.insert(random);
      seleccionados++;
    }
  }
  // Dump the set into the solution
  int i = 0;
  sol.v.resize(seleccionados);
  for(auto it : s){
    sol.v[i] = it;
    ++i;
  }
}

double actualizamosSolucion(solucion &s, vector<vector<double>> &m){
  s.evaluacion = evaluacionSolucion(s.v, m);
  return s.evaluacion;
}




// Comparison operator for ordering the solution vector
// Keeps at the front the element with less contribution to the fitness
bool operator <(const pair<int,double> &p1, const pair<int,double> &p2){
    return p1.second < p2.second;
}

// Order sol.v by conribution to the solution in ascending order
void ordenaSolucionPorContribucion(solucion &s, vector<vector<double>> &m){
  pair<int, double> p(0, 0.0);
  vector<pair<int, double>> pairs_v(s.v.size(), p);

  // Initialize the auxiliar vector
  for(unsigned i = 0; i < pairs_v.size(); ++i){
    pairs_v[i].first = s.v[i];
    pairs_v[i].second = distanciaAUnConjunto(pairs_v[i].first, s.v, m);
  }

  // Order the vector by contribution
  sort(pairs_v.begin(), pairs_v.end());

  // Save the ordering
  for(unsigned i = 0; i < pairs_v.size(); ++i)
    s.v[i] = pairs_v[i].first;
}



// Computes a single step in the exploration, changing "sol"
bool pasoDelAlgoritmo(solucion &sol, vector<vector<double>> &m){
  double porcentaje_estudiado;
  unsigned i = 0, j, elemento_fuera, intentos_totales, max_i, max_randoms, k;
  double nueva_contribucion, antigua_contribucion;

  ordenaSolucionPorContribucion(sol, m);

  porcentaje_estudiado = 1;
  intentos_totales = 100000;

  max_i = max(porcentaje_estudiado * sol.v.size(), 1.0);
  max_randoms = intentos_totales / max_i;

  // Fill hash with our used values
  unordered_set<int> s;
  for(unsigned i=0; i<sol.v.size(); ++i)
    s.insert(sol.v[i]);

  // Explore the neighbourhood and return the firstly found better option
  while(i < max_i){
    // Save data of the element we are trying to swap
    elemento_fuera = sol.v[i];
    antigua_contribucion = distanciaAUnConjunto(elemento_fuera, sol.v, m);

    k = 0;
    j = rand() % m.size();
    while(j < m.size() && k < max_randoms){
      // Try the swap if the element 'j' is not in the current solution
      if(s.find(j) == s.end()){
        nueva_contribucion = distanciaAUnConjunto(j, sol.v, m) - m[j][elemento_fuera];
        if(nueva_contribucion > antigua_contribucion){
          sol.v[i] = j;
          sol.evaluacion = sol.evaluacion + nueva_contribucion - antigua_contribucion;
          return false;
        }
        k++;
      }
      j = rand() % m.size();
    }
    i++;
  }
  return true;
}


// Computes the local search algorithm for a random starting solution
double busquedaLocal(vector<vector<double>> &m, unsigned n_a_seleccionar){
  solucion s;
  bool parada = false;
  unsigned iteraciones = 0;
  clock_t t_total, t_inicio;

  srand(time(NULL));
  solucionRandom(s, m.size(), n_a_seleccionar);
  actualizamosSolucion(s, m);

  t_inicio = clock();
  while (!parada /*&& iteraciones < 10000*/) {
    parada = pasoDelAlgoritmo(s, m);
    iteraciones++;
  }
  t_total = clock() - t_inicio;

  cout << s.evaluacion << "\t" << (double) t_total / CLOCKS_PER_SEC << "\t" << iteraciones << endl;
  return s.evaluacion;
}

int main(){
  int n_total, n_sel; // n_total = número de elementos &&
                      // n_sel = el número de elementos a seleccionar del problema
  cin >> n_total >> n_sel; // inicializo los valores con la primera línea del fichero
  vector<double> v(n_total, 0);
  vector<vector<double>> m(n_total, v); // m = matriz de entradas

  leerDatos(m); // inicializo la matriz de entradas
  busquedaLocal(m, n_sel); // aplico el algoritmo greedy
}
