#include <iostream>
#include <vector>
#include <stdlib.h>     // srand y rand
#include <time.h>
#include <math.h>

using namespace std;

// Estructura para representar una solucion
struct solucion{
  vector<bool> v;   // Vector de 1's y 0's donde 1 en la posicion i significa
                    // que pertenece el elemento i a la solucion.
  double diversidad;     // Diversidad de la solucion
  bool evaluada;    // Flag que comprueba si esta o no evaluada la solucion
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


/* Rellena una solucion con valores aletorios

Parametros:
  - s = solucion a rellenar
  - n = numero de elementos a seleccionar para la solucion
  - m = número de elementos posibles del dominio
*/
void solucionAleatoria(solucion &s, int n, int m){
  int n_elegidos = 0, numero_aleatorio;
  s.evaluada = false;
  s.diversidad = 0;
  s.v = vector<bool>(m, false);
  while (n_elegidos < n){
    numero_aleatorio = rand() % m;
    if(!s.v[numero_aleatorio]){
      s.v[numero_aleatorio] = true;
      n_elegidos++;
    }
  }
}


void enfriamientoSimulado(int n_sel, vector<vector<double>> &m, const int MAX_EVALUACIONES){
  int evaluaciones = 0, max_vecinos = n_sel, n_enfriamientos = 0, exitos = 1, max_exitos = n_sel * 0.1;
  double mejor_diversidad = 0, alpha = 0.9315, temperatura_actual, temperatura_inicial, temperatura_final = 0.001, delta; //delta = diferencia de costes entre soluciones vecinas
  clock_t t_total, t_inicio;
  solucion solucion_actual, solucion_guardada;

  // Inicialización
  t_inicio = clock();
  solucionAleatoria(solucion_actual, n_sel, m.size());

  
  evaluateSolution(solucion_actual);
  solucion_guardada = solucion_actual;
  mejor_diversidad = solucion_actual.diversidad;
  temperatura_inicial = 50000;
  temperatura_actual = temperatura_inicial;

  while(exitos > 0 && temperatura_actual > temperatura_final && evaluaciones < MAX_EVALUACIONES){
    exitos = 0;
    for(int i = 0; i < max_vecinos && exitos < max_exitos; i++){
      mutateSolution(solucion_actual);
      ++evaluaciones;
      delta = solucion_actual.diversidad - solucion_guardada.diversidad;
      if(delta > 0 || randD(generator) < exp(delta/temperatura_actual)){
        solucion_guardada = solucion_actual;
        exitos++;
        if(solucion_actual.diversidad > mejor_diversidad)
          mejor_diversidad = solucion_actual.diversidad;
      } else
        solucion_actual = solucion_guardada;
    }
    temperatura_actual = temperatura_actual * alpha;
    ++n_enfriamientos;
  }
  t_total = clock() - t_inicio;
  cout << mejor_diversidad << "\t" << (double) t_total / CLOCKS_PER_SEC << "\t" << evaluaciones << endl;
}

/* --------------------------- MAIN ---------------------------*/

int main(int argc, char *argv[]){
  int n_total, n_sel; // n_total = número de elementos &&
                      // n_sel = el número de elementos a seleccionar del problema
  const int MAX_EVALUACIONES = 50000;

  int semilla = atoi(argv[1]);
  // Fijamos la semilla
  srand(semilla);

  cin >> n_total >> n_sel; // inicializo los valores con la primera línea del fichero
  vector<double> v(n_total, 0);
  vector<vector<double>> m(n_total, v); // m = matriz de entradas
  leerDatos(m); // inicializo la matriz de entradas

  enfriamientoSimulado(n_sel, m, MAX_EVALUACIONES);
}
