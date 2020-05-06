#include <iostream>
#include <vector>
#include <unordered_set>
#include <stdlib.h>     // srand y rand
#include <algorithm>    // sort y random_shuffle
#include <time.h>

using namespace std;

// Estructura para representar una solucion en representacion entera
struct solucion_ints{
  vector<int> v;  // Vector de enteros donde cada entero indica que punto del
                  // dominio pertenece a la solucion.
  double diversidad;   // Diversidad de la solucion
};

// Estructura para representar una solucion
struct solucion{
  vector<bool> v;   // Vector de 1's y 0's donde 1 en la posicion i significa
                    // que pertenece el elemento i a la solucion.
  double diversidad;     // Diversidad de la solucion
  bool evaluada;    // Flag que comprueba si esta o no evaluada la solucion
};

/* Sobrecargamos el operador "menor que" entre dos parejas.
Así una pareja p1 será menor que otra p2 (p1 < p2) si y solo si la segunda
componente (el diversidad) de p1 es menor al de p2.

Parametros:
  - p1 = pareja (índice-diversidad)
  - p2 = pareja (índice-diversidad)
*/
bool operator <(const pair<int,double> &p1, const pair<int,double> &p2){
    return p1.second < p2.second;
}

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

/* Dado un conjunto de elementos que forma la solucion, calcula la distancia entre
los elementos del conjunto, es decir, el coste de la solución

Parametros:
  - conjunto = conjunto de elementos a contar su distancia
  - m = matriz de distancias
*/
template <class T>
double costeSolucion(T &conjunto, vector<vector<double>> &m) {
  double coste = 0;
  typename T::iterator it;
  for(it = conjunto.begin(); it != conjunto.end(); ++it)
    coste += distanciaAUnConjunto(*it, conjunto, m);
  return coste /= 2;
}

/* Ordena el vector de índices de la solución de menor a mayor por la contribution
de éstos elementos al diversidad

Parametros:
  - s = solucion a actualizar
  - m = matriz de distancias
*/
void ordenaSolucionPorContribucion(solucion_ints &s, vector<vector<double>> &m){
  // Creamos un vector de parejas (indice_solución-distancia_al_resto (o diversidad))
  pair<int, double> p(0, 0.0);
  vector<pair<int, double>> parejas(s.v.size(), p);

  for(unsigned i = 0; i < parejas.size(); ++i){
    parejas[i].first = s.v[i];
    parejas[i].second = distanciaAUnConjunto(parejas[i].first, s.v, m);
  }
  // Ordenamos dichas parejas por la distribución, para ello necesitamos
  // sobrecargar el operador <
  sort(parejas.begin(), parejas.end());
  // Guardamos la solucion ordenada
  for(unsigned i = 0; i < parejas.size(); ++i)
    s.v[i] = parejas[i].first;
}

/* Explora el vecindario intercambiando puntos para ver si mejoramos la solución

Parametros:
  - s = solucion a mejorar
  - m = matriz de distancias
*/
bool exploracionVecindario(solucion_ints &s, int &evaluaciones, int max_evaluaciones, vector<vector<double>> &m){
  unsigned i = 0, j, k, elemento_auxiliar, limite_evaluaciones;
  double antigua_contribucion, nueva_contribucion;
  unordered_set<int> conjunto;
  int evaluaciones_reales = 0;

  // Ordenamos la solución por contribución
  ordenaSolucionPorContribucion(s, m);

  // Igualamos el número de evaluaciones que comprobaremos para cada índice de la
  // solución
  limite_evaluaciones = max_evaluaciones / s.v.size();

  // Rellenamos la estructura auxiliar conjunto con los elementos de la solución
  for(unsigned z = 0; z < s.v.size(); ++z)
    conjunto.insert(s.v[z]);

  // Para cada índice (elemento de la solución), buscamos elementos entre sus
  // vecinos que mejoren la solución.
  while(i < s.v.size()){
    // Guardamos el índice anterior y buscamos uno nuevo
    elemento_auxiliar = s.v[i];
    antigua_contribucion = distanciaAUnConjunto(elemento_auxiliar, s.v, m);
    k = 0;
    // Elegimos un índice aleatorio
    j = rand() % m.size();

    // Comprobamos que no nos pasemos del límite de evaluaciones.
    while(k < limite_evaluaciones){
      // Comprobamos que el elemento no pertenezca a la solución
      if(conjunto.find(j) == conjunto.end()){
        // Calculamos la nueva contribución que generaría dicho elemento al
        // hacer el intercambio con el elemento anterior.
        nueva_contribucion = distanciaAUnConjunto(j, s.v, m) - m[j][elemento_auxiliar];
        // Comprobamos si la nueva contribución mejora a la anterior
        if(nueva_contribucion > antigua_contribucion){
          // Realizamos el intercambio y pasamos a la siguiente evaluacion.
          s.v[i] = j;
          s.diversidad = s.diversidad + nueva_contribucion - antigua_contribucion;
          return false;
        }
        ++k;
        ++evaluaciones_reales;
        if(evaluaciones_reales % s.v.size() == 0){
          ++evaluaciones;
          evaluaciones_reales = 0;
        }
      }
      j = rand() % m.size();
    }
    ++i;
  }
  return true;
}

/* Actualizamos el coste de la solucion.

Parametros:
  - s = solucion en representacion de ints.
*/
double actualizarSolucion(solucion_ints &s, vector<vector<double>> &m) {
  s.diversidad = costeSolucion(s.v, m);
  return s.diversidad;
}

/* Pasar de una solucion es representacion en enteros a representacion en binaria.

Parametros:
  - s_ints = solucion en representacion de ints.
  - s_bits = solucion en representacion bits.
  - n_bits = tamaño del vector de la solucion en representacion binaria.
*/
void pasarDeIntsABits(solucion_ints &s_ints, solucion &s_bits, int n_bits){
  s_bits.v = vector<bool>(n_bits, false);
  for(unsigned i = 0; i < s_ints.v.size(); ++i)
    s_bits.v[s_ints.v[i]] = true;
  s_bits.diversidad = s_ints.diversidad;
}

/* Pasar de una solucion es representacion binaria a representacion en enteros.

Parametros:
  - s_bits = solucion en representacion bits.
  - s_ints = solucion en representacion de ints.
*/
void pasarDeBitsAInts(solucion &s_bits, solucion_ints &s_ints) {
  s_ints.v.clear();
  for(unsigned i = 0; i < s_bits.v.size(); ++i){
    if(s_bits.v[i])
      s_ints.v.push_back(i);
  }
  s_ints.diversidad = s_bits.diversidad;
}

/* Aplicamos el algoritmo de Búsqueda local.

Parametros:
  - m = matriz de distancias
  - s_bits = solucion en representacion bits.
  - max_evaluaciones = maximas evaluaciones de la busqueda local
*/
int busquedaLocal(vector<vector<double>> &m, solucion &s_bits, int max_evaluaciones){
  solucion_ints s_ints;
  bool parada = false;
  int evaluaciones = 0;

  pasarDeBitsAInts(s_bits, s_ints);
  actualizarSolucion(s_ints, m);

  while(!parada && evaluaciones < max_evaluaciones)
    parada = exploracionVecindario(s_ints, evaluaciones, max_evaluaciones - evaluaciones, m);

  pasarDeIntsABits(s_ints, s_bits, s_bits.v.size());
  return evaluaciones;
}


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
  double diversidad = 0;
  for(unsigned i = 0; i < conjunto.size(); ++i)
    if(conjunto[i])
      diversidad += distanciaAUnConjunto(i, conjunto, m);
  return diversidad /= 2;
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
  - m = matriz de distancias
  - n = numero de elementos a seleccionar
  - MAX_EVALUACIONES = numero de evaluaciones maximo permitido
*/

void ILS(vector<vector<double>> &m, int n, const int MAX_EVALUACIONES){
  int evaluaciones = 0, iteraciones = 10, evaluaciones_iteracion = 0;
  double mejor_diversidad = 0;
  clock_t t_total, t_inicio;
  solucion solucion_actual, solucion_guardada;
  t_inicio = clock();

  solucionAleatoria(m, solucion_actual, n);
  evaluarSolucion(solucion_actual, m);
  solucion_guardada = solucion_actual;
  mejor_diversidad = solucion_actual.diversidad;
  evaluaciones_iteracion = busquedaLocal(m, solucion_actual, MAX_EVALUACIONES);
  evaluaciones += 1 + evaluaciones_iteracion;
  //cout << "Iteración 0: evaluaciones: " << evaluaciones_iteracion << endl;
  if(solucion_guardada.diversidad > solucion_actual.diversidad)
    solucion_actual = solucion_guardada;
  else{
    solucion_guardada = solucion_actual;
    if(solucion_actual.diversidad > mejor_diversidad)
      mejor_diversidad = solucion_actual.diversidad;
  }

  for(int i = 1; i < iteraciones; ++i){
    perturbacionBrusca(solucion_actual, m, n);
    evaluaciones_iteracion = busquedaLocal(m, solucion_actual, MAX_EVALUACIONES);
    evaluaciones += 1 + evaluaciones_iteracion;
    //cout << "Iteración " << i << ": evaluaciones: " << evaluaciones_iteracion << endl;
    if(solucion_guardada.diversidad > solucion_actual.diversidad)
      solucion_actual = solucion_guardada;
    else{
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

  ILS(m, n_sel, MAX_EVALUACIONES);
}
