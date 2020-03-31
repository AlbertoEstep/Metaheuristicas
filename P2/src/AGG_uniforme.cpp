#include <iostream>
#include <vector>
#include <set>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

using namespace std;

struct solucion{
  vector<bool> v;
  double coste;
  bool evaluada;
};

class poblacion{
  public:
    vector<solucion> v;
    double max_coste;
    int mejor_solucion;
    int n_individuos;

    poblacion(){
      mejor_solucion = 0;
      n = 0;
      max_coste = 0;
    }
};

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

void solucionAleatoria(vector<vector<double>> &m, solucion &s, int n){
  int n_elegidos = 0, numero_aleatorio;
  // Set the flag and clear the solution
  s.evaluada = false;
  s.v = vector<bool>(m.size(), false);
  // Select 'n' elements
  while (n_elegidos < n){
    numero_aleatorio = random(0, m.size());
    if(!s.v[numero_aleatorio]){
      s.v[numero_aleatorio] = true;
      n_elegidos++;
    }
  }
}

void inicializarPoblacion(vector<vector<double>> &m, poblacion &p, int n_individuos, int n){
  p.v.resize(n_individuos);
  for(int i = 0; i < n_individuos; ++i)
    solucionAleatoria(p.v[i], n);
  p.n_individuos = p.v.size();
}


// Computes the local search algorithm for a random starting solucion
// This implementation doesn't assume the pop is ordered
double AGGu(vector<vector<double>> &m, int n, int MAX_EVALUACIONES){
  int evaluaciones = generaciones = 0, n_individuos = 50;
  double p_mutacion = 0.001, p_cruce = 0.7;
  clock_t t_total, t_inicio;
  poblacion poblacion_nueva, poblacion_actual;

  t_inicio = clock();
  inicializarPoblacion(vector<vector<double>> &m, poblacion_actual, n_individuos, n);






  evaluatePop(poblacion_actual, evaluaciones);

  while (evaluaciones < MAX_EVALUACIONES) {
    generaciones++;
    selection(poblacion_actual, poblacion_nueva);
    cross(poblacion_nueva, p_cruce);
    mutatePop(poblacion_nueva, p_mutacion, n, evaluaciones);
    evaluatePop(poblacion_nueva, evaluaciones);
    replace(poblacion_actual, poblacion_nueva);
  }
  t_total = clock() - t_inicio;

  solucion sol = poblacion_actual.v[ poblacion_actual.mejor_solucion ];

  // output: coste - Time - Iterations
  cout << sol.coste << "\t" << (double) t_total / CLOCKS_PER_SEC << "\t" << generaciones << endl;
  return sol.coste;
}


/* --------------------------- MAIN ---------------------------*/

int main(int argc, char *argv[]){
  int n_total, n_sel; // n_total = número de elementos &&
                      // n_sel = el número de elementos a seleccionar del problema
  const int MAX_EVALUACIONES = 50000;

  cin >> n_total >> n_sel; // inicializo los valores con la primera línea del fichero
  vector<double> v(n_total, 0);
  vector<vector<double>> m(n_total, v); // m = matriz de entradas
  leerDatos(m); // inicializo la matriz de entradas

  int semilla = atoi(argv[1]);
  // Fijamos la semilla
  srand(semilla);

  AGGuniforme(m, n_sel, MAX_EVALUACIONES); // aplico el algoritmo AGGuniforme
}
