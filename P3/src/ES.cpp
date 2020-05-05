#include <iostream>
#include <vector>
#include <stdlib.h>     // srand y rand
#include <time.h>
#include <random>       // uniform_real_distribution
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
    // TODO:iterations++; AQUI (mirar la nota importante en el main)
  }
}


/* Metodo de general del algoritmo

Parametros:
  - n_sel = numero de elementos a seleccionar
  - m = matriz de distancias
  - MAX_EVALUACIONES = numero de evaluaciones maximo permitido
*/
void enfriamientoSimulado(int n_sel, vector<vector<double>> &m, const int MAX_EVALUACIONES){
  int evaluaciones = 0, max_vecinos = m.size(), exitos = 1, max_exitos = m.size()*0.1;
  double mejor_diversidad = 0, temperatura_actual, temperatura_inicial, temperatura_final = 0.001, delta; //delta = diferencia de costes entre soluciones vecinas
  clock_t t_total, t_inicio;
  solucion solucion_actual, solucion_guardada;
  double numero_aleatorio;
  int n_enfriamientos = 100000 / max_vecinos;
  double beta;

  t_inicio = clock();
  solucionAleatoria(solucion_actual, n_sel, m.size());
  evaluarSolucion(solucion_actual, m);
  solucion_guardada = solucion_actual;
  mejor_diversidad = solucion_actual.diversidad;
  temperatura_inicial = solucion_actual.diversidad*0.3/-log(0.3);
  beta = (temperatura_inicial - temperatura_final)/(n_enfriamientos * temperatura_inicial * temperatura_final);


  temperatura_actual = temperatura_inicial;

  while(exitos > 0 && evaluaciones < MAX_EVALUACIONES && temperatura_actual > temperatura_final){
    exitos = 0;
    for(int i = 0; i < max_vecinos && exitos < max_exitos; i++){
      mutarSolucion(solucion_actual, m);
      ++evaluaciones;
      delta = solucion_actual.diversidad - solucion_guardada.diversidad;
      numero_aleatorio = (rand() % 100)/100;
      if(delta > 0 || numero_aleatorio < exp(delta / temperatura_actual)){
        solucion_guardada = solucion_actual;
        exitos++;
        if(solucion_actual.diversidad > mejor_diversidad)
          mejor_diversidad = solucion_actual.diversidad;
      } else
        solucion_actual = solucion_guardada;
    }
    temperatura_actual = temperatura_actual / (1 + beta*temperatura_actual);
    ++n_enfriamientos;
  }
  t_total = clock() - t_inicio;
  cout << mejor_diversidad << "\t" << (double) t_total / CLOCKS_PER_SEC << "\t" << evaluaciones << endl;
}

/* --------------------------- MAIN ---------------------------*/

int main(int argc, char *argv[]){
  int n_total, n_sel; // n_total = número de elementos &&
                      // n_sel = el número de elementos a seleccionar del problema
  const int MAX_EVALUACIONES = 100000;

  int semilla = atoi(argv[1]);
  // Fijamos la semilla
  srand(semilla);

  cin >> n_total >> n_sel; // inicializo los valores con la primera línea del fichero
  vector<double> v(n_total, 0);
  vector<vector<double>> m(n_total, v); // m = matriz de entradas
  leerDatos(m); // inicializo la matriz de entradas

  enfriamientoSimulado(n_sel, m, MAX_EVALUACIONES);
  //TODO:Informacion importante mutaxcion
}
