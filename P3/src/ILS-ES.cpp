#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <stdlib.h>     // srand y rand
#include <algorithm>    // sort y random_shuffle
#include <time.h>
#include <math.h>
#include <random>       // uniform_real_distribution

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

// Estructura para representar una solucion
struct solucion{
  vector<bool> v;   // Vector de 1's y 0's donde 1 en la posicion i significa
                    // que pertenece el elemento i a la solucion.
  double diversidad;     // Diversidad de la solucion
  bool evaluada;    // Flag que comprueba si esta o no evaluada la solucion
};

/* Dado un conjunto de elementos y un elemento concreto, calcula la distancia
acumulada entre el elemento y el conjunto de elementos.

Parametros:
  - elemento = elemento a calcular la distancia con los demás
  - conjunto = conjunto de elementos a contar su distancia
  - m = matriz de distancias
*/
double distanciaAUnConjunto(int elemento, vector<bool> &conjunto, vector<vector<double>> &m){
  double suma = 0;
  for(unsigned i = 0; i < conjunto.size(); ++i)
    if(conjunto[i])
      suma += conjunto[i]*m[elemento][i];
  return suma;
}

/* Dado un conjunto de elementos que forma la solucion, calcula la distancia entre
los elementos del conjunto, es decir, el coste de la solución

Parametros:
  - conjunto = conjunto de elementos a contar su distancia
  - m = matriz de distancias
*/
double costeSolucion(vector<bool> &conjunto, vector<vector<double>> &m){
  double coste = 0;
  for(unsigned i = 0; i < conjunto.size(); ++i)
    if(conjunto[i])
      coste += distanciaAUnConjunto(i, conjunto, m);
  return coste /= 2;
}


/* Dado un conjunto de elementos que forma la solucion, calcula la distancia entre
los elementos del conjunto, es decir, el coste de la solución y pone el Flag
evaluada a true,

Parametros:
  - s = solucion a calcular su diversidad
  - m = matriz de distancias
*/
double evaluarSolucion(solucion &s, vector<vector<double>> &m){
  s.diversidad = costeSolucion(s.v, m);
  s.evaluada = true;
  return s.diversidad;
}

/* Rellena una solucion con valores aletorios

Parametros:
  - m = matriz de distancias
  - s = solucion a rellenar
  - n = numero de elementos a seleccionar para la solucion
*/
void solucionAleatoria(vector<vector<double>> &m, solucion &s, int n){
  int n_elegidos = 0, numero_aleatorio;
  s.evaluada = false;
  s.diversidad = 0;
  s.v = vector<bool>(m.size(), false);
  while (n_elegidos < n){
    numero_aleatorio = rand() % m.size();
    if(!s.v[numero_aleatorio]){
      s.v[numero_aleatorio] = true;
      n_elegidos++;
    }
  }
}

void mutarSolucion(solucion &sol, vector<vector<double>> &m) {
  int n_aleatorio1, n_aleatorio2;

  do{
    n_aleatorio1 = rand() % sol.v.size();
  } while(!sol.v[n_aleatorio1]);
  do{
    n_aleatorio2 = rand() % sol.v.size();
  } while(sol.v[n_aleatorio2]);

  sol.v[n_aleatorio1] = false;
  sol.v[n_aleatorio2] = true;

  if(sol.evaluada){
    double antigua_contribucion = distanciaAUnConjunto(n_aleatorio1, sol.v, m) - m[n_aleatorio1][n_aleatorio2];
    double nueva_contribucion = distanciaAUnConjunto(n_aleatorio2, sol.v, m);
    sol.diversidad = sol.diversidad + nueva_contribucion - antigua_contribucion;
  }
}

/* Provoca una perturbación en la solución. Se usará un valor de t=0.1·m para
el número de elementos seleccionados distintos a modificar en la mutación.

Parametros:
  - s = solucion a perturbar
  - m = matriz de distancias
  - n = número de elementos a escoger en una solución
*/
void perturbacionBrusca(solucion &s, vector<vector<double>> &m, int n){
  int t = n * 0.1;
  for(int i = 0; i < t; ++i)
    mutarSolucion(s, m);
}

/* Metodo de general del algoritmo

Parametros:
  - solucion_inicial = solucion sobre la que se aplica el enfriamiento simulado
  - MAX_EVALUACIONES = numero de evaluaciones maximo permitido
  - n_sel = numero de elementos a seleccionar
  - m = matriz de distancias
*/
int enfriamientoSimulado(solucion &solucion_inicial, const int MAX_EVALUACIONES, int n_sel, vector<vector<double>> &m){
  int evaluaciones = 0, max_vecinos = n_sel, exitos = 1, max_exitos = n_sel * 0.1;
  double mejor_diversidad = 0, alpha = 0.95, numero_aleatorio;
  double temperatura_actual, temperatura_inicial, temperatura_final = 0.001, delta;
  solucion solucion_actual, solucion_guardada, mejor_solucion;

  solucion_actual = solucion_inicial;
  solucion_guardada = solucion_inicial;
  mejor_solucion = solucion_inicial;
  mejor_diversidad = solucion_inicial.diversidad;
  temperatura_inicial = solucion_actual.diversidad*0.3/-log(0.3);
  temperatura_actual = temperatura_inicial;

  while(exitos > 0 && temperatura_actual > temperatura_final && evaluaciones < MAX_EVALUACIONES){
    exitos = 0;
    for(int i = 0; i < max_vecinos && exitos < max_exitos; ++i){
      mutarSolucion(solucion_actual, m);
      ++evaluaciones;
      delta = solucion_actual.diversidad - solucion_guardada.diversidad;
      numero_aleatorio = (rand() % 100)/100;
      if(delta > 0 || numero_aleatorio < exp(delta / temperatura_actual)){
        solucion_guardada = solucion_actual;
        ++exitos;
        if(solucion_actual.diversidad > mejor_diversidad){
          mejor_diversidad = solucion_actual.diversidad;
          mejor_solucion = solucion_actual;
        }
      } else
        solucion_actual = solucion_guardada;
    }
    temperatura_actual = temperatura_actual * alpha;
  }
  solucion_inicial = mejor_solucion;
  return evaluaciones;
}

/* Metodo de general del algoritmo

Parametros:
  - m = matriz de distancias
  - n = numero de elementos a seleccionar
  - MAX_EVALUACIONES = numero de evaluaciones maximo permitido
*/

void ILS_ES(vector<vector<double>> &m, int n_sel, const int MAX_EVALUACIONES){
  int evaluaciones = 0, iteraciones = 10;
  double mejor_diversidad = 0;
  clock_t t_total, t_inicio;
  solucion solucion_actual, solucion_guardada;
  t_inicio = clock();

  solucionAleatoria(m, solucion_actual, n_sel);
  evaluarSolucion(solucion_actual, m);
  solucion_guardada = solucion_actual;
  mejor_diversidad = solucion_actual.diversidad;
  evaluaciones += 1 + enfriamientoSimulado(solucion_actual, MAX_EVALUACIONES, n_sel, m);
  if(solucion_guardada.diversidad > solucion_actual.diversidad)
    solucion_actual = solucion_guardada;
  else{
    solucion_guardada = solucion_actual;
    if(solucion_actual.diversidad > mejor_diversidad)
      mejor_diversidad = solucion_actual.diversidad;
  }

  for(int i = 1; i < iteraciones; ++i){
    perturbacionBrusca(solucion_actual, m, n_sel);
    evaluaciones += 1 + enfriamientoSimulado(solucion_actual, MAX_EVALUACIONES, n_sel, m);
    if(solucion_guardada.diversidad > solucion_actual.diversidad)
      solucion_actual = solucion_guardada;
    else {
      solucion_guardada = solucion_actual;
      if(solucion_actual.diversidad > mejor_diversidad)
        mejor_diversidad = solucion_actual.diversidad;
    }
  }
  t_total = clock() - t_inicio;
  cout << mejor_diversidad << "\t" << (double) t_total / CLOCKS_PER_SEC << "\t" << evaluaciones << endl;
}

/* --------------------------- MAIN ---------------------------*/

int main(int argc, char *argv[]){
  int n_total, n_sel; // n_total = número de elementos &&
                      // n_sel = el número de elementos a seleccionar del problema
  const int MAX_EVALUACIONES = 10000;
  int semilla = atoi(argv[1]);

  // Fijamos la semilla
  srand(semilla);

  cin >> n_total >> n_sel; // inicializo los valores con la primera línea del fichero
  vector<double> v(n_total, 0);
  vector<vector<double>> m(n_total, v); // m = matriz de entradas
  leerDatos(m); // inicializo la matriz de entradas

  ILS_ES(m, n_sel, MAX_EVALUACIONES);
}
