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

struct solucion{
  vector<int> v;
  double coste;
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


/* Calcula una solucion del problema de forma aleatoria
Para ello debemos de haber creado la semilla anteriormente

Parametros:
  - s = solucion que se rellenará
  - n_a_seleccionar = número de elementos que incluirá la solucion
  - m = matriz de distancias
*/
void solucionAleatoria(solucion &s, int n_a_seleccionar, vector<vector<double>> &m){
  int seleccionados = 0, indice_aleatorio;
  unordered_set<int> conjunto;

  // Seleccionamos tantos elementos como indique n_a_seleccionar
  while(seleccionados < n_a_seleccionar){
    indice_aleatorio = rand() % m.size();
    if(conjunto.find(indice_aleatorio) == conjunto.end()){
      conjunto.insert(indice_aleatorio);
      seleccionados++;
    }
  }
  int i = 0;
  s.v.resize(seleccionados);
  for(auto it : conjunto){
    s.v[i] = it;
    ++i;
  }
  s.coste = costeSolucion(s.v, m);
}

/* sobrecargamos el operador "menor que" entre dos parejas.
Así una pareja p1 será menor que otra p2 (p1 < p2) si y solo si la segunda
componente (el coste) de p1 es menor al de p2.

Parametros:
  - p1 = pareja (índice-coste)
  - p2 = pareja (índice-coste)
*/
bool operator <(const pair<int,double> &p1, const pair<int,double> &p2){
    return p1.second < p2.second;
}

/* Ordena el vector de índices de la solución de menor a mayor por la contribution
de éstos elementos al coste

Parametros:
  - s = solucion a actualizar
  - m = matriz de distancias
*/
void ordenaSolucionPorContribucion(solucion &s, vector<vector<double>> &m){
  // Creamos un vector de parejas (indice_solución-distancia_al_resto (o coste))
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
bool exploracionVecindario(solucion &s, vector<vector<double>> &m){
  unsigned i = 0, j, k, elemento_auxiliar, limite_iteraciones, iteraciones_totales = 100000;
  double antigua_contribucion, nueva_contribucion;
  unordered_set<int> conjunto;

  // Ordenamos la solución por contribución
  ordenaSolucionPorContribucion(s, m);

  // Igualamos el número de iteraciones que comprobaremos para cada índice de la
  // solución
  limite_iteraciones = iteraciones_totales / s.v.size();

  // Rellenamos la estructura auxiliar conjunto con los elementos de la solución
  for(unsigned z=0; z<s.v.size(); ++z)
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

    // Comprobamos que no nos pasemos del límite de iteraciones.
    while(k < limite_iteraciones){
      // Comprobamos que el elemento no pertenezca a la solución
      if(conjunto.find(j) == conjunto.end()){
        // Calculamos la nueva contribución que generaría dicho elemento al
        // hacer el intercambio con el elemento anterior.
        nueva_contribucion = distanciaAUnConjunto(j, s.v, m) - m[j][elemento_auxiliar];
        // Comprobamos si la nueva contribución mejora a la anterior
        if(nueva_contribucion > antigua_contribucion){
          // Realizamos el intercambio y pasamos a la siguiente iteracion.
          s.v[i] = j;
          s.coste = s.coste + nueva_contribucion - antigua_contribucion;
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


/* Aplicamos el algoritmo de Búsqueda local para la obtención de la solución.

Parametros:
  - m = matriz de distancias
  - n_a_seleccionar = número de elementos de los que constará la solución.
*/
double busquedaLocal(vector<vector<double>> &m, unsigned n_a_seleccionar){
  solucion s;
  bool parada = false;
  clock_t t_total, t_inicio;

  // Calcula una solucion del problema de forma aleatoria
  solucionAleatoria(s, n_a_seleccionar, m);

  t_inicio = clock();
  while (!parada)
    parada = exploracionVecindario(s, m);
  t_total = clock() - t_inicio;

  cout << "Tiempo consumido: " << (double) t_total / CLOCKS_PER_SEC << endl;
  cout << "Coste de la solucion: " << s.coste << endl;
  return s.coste;
}

int main(int argc, char *argv[]){
  int n_total, n_sel; // n_total = número de elementos &&
                      // n_sel = el número de elementos a seleccionar del problema
  cin >> n_total >> n_sel; // inicializo los valores con la primera línea del fichero
  vector<double> v(n_total, 0);
  vector<vector<double>> m(n_total, v); // m = matriz de entradas

  leerDatos(m); // inicializo la matriz de entradas

  int semilla = atoi(argv[1]);
  // Fijamos la semilla
  srand(semilla);

  busquedaLocal(m, n_sel); // aplico el algoritmo greedy
}
