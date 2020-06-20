#include <iostream>
#include <vector>
#include <set>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <stdlib.h>							// rand()
#include <random>								// normal_distribution()
#include <algorithm> // sort()
#include <unordered_set>


using namespace std;

// Estructura para representar una solucion
struct solucion{
  vector<bool> v;   // Vector de 1's y 0's donde 1 en la posicion i significa
                    // que pertenece el elemento i a la solucion.
  double coste;     // Diversidad de la solucion
  bool evaluada;    // Flag que comprueba si esta o no evaluada la solucion
};

// Estructura para representar una poblacion
class poblacion{
  public:
    vector<solucion> v;   // Vector de soluciones
    double max_coste;     // Diversidad de la solucion con mayor diversidad
    int mejor_solucion;   // Indice en el vector con la mejor solucion
    int n_individuos;     // Numero de individuos de la solucion

    poblacion(){
      mejor_solucion = 0;
      n_individuos = 0;
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

/* Rellena una solucion con valores aletorios

Parametros:
  - m = matriz de distancias
  - s = solucion a rellenar
  - n = numero de elementos a seleccionar para la solucion
*/
void solucionAleatoria(vector<vector<double>> &m, solucion &s, int n){
  int n_elegidos = 0, numero_aleatorio;
  s.evaluada = false;
  s.v = vector<bool>(m.size(), false);
  while (n_elegidos < n){
    numero_aleatorio = rand() % m.size();
    if(!s.v[numero_aleatorio]){
      s.v[numero_aleatorio] = true;
      n_elegidos++;
    }
  }
}

/* Iniciamos la poblacion con soluciones aleatorias

Parametros:
  - m = matriz de distancias
  - p = poblacion a inicializar
  - n_individuos = numero de elementos que perteneceran a la poblacion
  - n = numero de elementos a seleccionar para la solucion
*/
void inicializarPoblacion(vector<vector<double>> &m, poblacion &p, int n_individuos, int n){
  p.v.resize(n_individuos);
  for(int i = 0; i < n_individuos; ++i)
    solucionAleatoria(m, p.v[i], n);
  p.n_individuos = p.v.size();
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
  s.coste = costeSolucion(s.v, m);
  s.evaluada = true;
  return s.coste;
}

/* Dado una poblacion, calculamos la diversidad de cada individuo y actualiza
los valores de control de la poblacion

Parametros:
  - p = piblacion a calcular su diversidad
  - evaluaciones = numero de evaluaciones de la funcion objetivo hechas actualmente
  - m = matriz de distancias
*/
void evaluarPoblacion(poblacion &p, int &evaluaciones, vector<vector<double>> &m){
  for(int i = 0; i < p.n_individuos; ++i){
    if(!p.v[i].evaluada){
      evaluarSolucion(p.v[i], m);
      ++evaluaciones;
      if(p.v[i].coste > p.max_coste){
        p.mejor_solucion = i;
        p.max_coste = p.v[i].coste;
      }
    }
  }
}


/* Rellena una solucion con valores aletorios

Parametros:
  - m = matriz de distancias
  - n = numero de elementos a seleccionar para la solucion
*/
solucion obtenerCuckooPorLevy(vector<vector<double>> &m, int n){
  solucion s;
  int n_elegidos = 0, numero_aleatorio;
  s.evaluada = false;
  s.v = vector<bool>(m.size(), false);
  while (n_elegidos < n){
    numero_aleatorio = rand() % m.size();
    if(!s.v[numero_aleatorio]){
      s.v[numero_aleatorio] = true;
      n_elegidos++;
    }
  }
  return s;
}

/* Obtiene un nido de la poblacion de forma aleatoria

Parametros:
  - p = poblacion
  - cuco = solucion a reemplazar, si procede
*/
void reemplazarNido(poblacion &p, solucion &cuco){
  int numero_aleatorio = rand() % p.n_individuos;
  if(cuco.coste > p.v[numero_aleatorio].coste){
    p.v[numero_aleatorio] = cuco;
    if(p.v[numero_aleatorio].coste > p.max_coste){
      p.mejor_solucion = numero_aleatorio;
      p.max_coste = p.v[numero_aleatorio].coste;
    }
  }
}

/* Sobrecargamos el operador < entre soluciones para poder ordenar la poblacion.
Solucion1 < Solucion2 <=> Diversidad de Solucion1 > Diversidad de Solucion2
*/
bool operator < (const solucion &s1, const solucion &s2){
    return s1.coste > s2.coste;
}

/* Metodo de mutacion entre la solucion

Parametros:
  - s = solucion a mutar
  - evaluaciones = numero de evaluaciones de la funcion objetivo hechas actualmente
  - m = matriz de distancias
*/
void alterarSolucion(solucion &s, int &evaluaciones, vector<vector<double>> &m){
  int n_aleatorio1, n_aleatorio2;

  do {
    n_aleatorio1 = rand() % s.v.size();
  } while(s.v[n_aleatorio1]);
  do{
    n_aleatorio2 = rand() % s.v.size();;
  } while(!s.v[n_aleatorio2]);

  s.v[n_aleatorio1] = true;
  s.v[n_aleatorio2] = false;

  if(s.evaluada){
    double antiguo_coste = distanciaAUnConjunto(n_aleatorio2, s.v, m) - m[n_aleatorio2][n_aleatorio1];
    double nuevo_coste = distanciaAUnConjunto(n_aleatorio1, s.v, m);
    s.coste = s.coste + nuevo_coste - antiguo_coste;
    ++evaluaciones;
  }
}


/* Metodo de reemplazamiento de nidos de la poblacion

Parametros:
  - p = poblacion a actualizar
  - p_a = porcentaje de nidos a tirar.
  - m = matriz de distancias
  - n = numero de elementos a seleccionar para la solucion
*/
void reemplazarPoblacion(poblacion &p, double p_a, vector<vector<double>> &m, int n, int &evaluaciones){
  int n_original = p.n_individuos;
  int n_reemplazar = n_original*p_a;
  poblacion poblacion_aux = p;
  poblacion_aux.v.resize(n_reemplazar);
  for(int i = 0; i < n_reemplazar; ++i){
    alterarSolucion(poblacion_aux.v[i], evaluaciones, m);
    p.v.push_back(poblacion_aux.v[i]);
  }
  sort(p.v.begin(), p.v.end());
  p.v.resize(p.v.size() - n_reemplazar);
  p.max_coste = p.v[0].coste;
  p.mejor_solucion = 0;
}

// Estructura para representar una solucion en representacion entera
struct solucion_ints{
  vector<int> v;  // Vector de enteros donde cada entero indica que punto del
                  // dominio pertenece a la solucion.
  double coste;   // Diversidad de la solucion
};

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

/* Actualizamos el coste de la solucion.

Parametros:
  - s = solucion en representacion de ints.
*/
double actualizarSolucion(solucion_ints &s, vector<vector<double>> &m) {
  s.coste = costeSolucion(s.v, m);
  return s.coste;
}

/* Ordena el vector de índices de la solución de menor a mayor por la contribution
de éstos elementos al coste

Parametros:
  - s = solucion a actualizar
  - m = matriz de distancias
*/
void ordenaSolucionPorContribucion(solucion_ints &s, vector<vector<double>> &m){
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
          s.coste = s.coste + nueva_contribucion - antigua_contribucion;
          return false;
        }
        ++k;
        ++evaluaciones_reales;
        if (evaluaciones_reales % s.v.size() == 0) {
          ++evaluaciones;
          evaluaciones_reales = 0;
        }
      }
      j = rand() % m.size();
    }
    i++;
  }
  return true;
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

void hibridar(poblacion &poblacion, int max_evaluaciones, int &evaluaciones, vector<vector<double>> &m){
  evaluaciones += busquedaLocal(m, poblacion.v[poblacion.mejor_solucion], max_evaluaciones);
  evaluarSolucion(poblacion.v[ poblacion.mejor_solucion], m);
  poblacion.max_coste = poblacion.v[poblacion.mejor_solucion].coste;
}

/* Metodo de general del algoritmo

Parametros:
  - m = matriz de distancias
  - n = numero de elementos a seleccionar
  - MAX_EVALUACIONES = numero de evaluaciones maximo permitido
*/
double CS_hibrido(vector<vector<double>> &m, int n, int MAX_EVALUACIONES){
  double p_a = 0.25;
  clock_t t_total, t_inicio;
  poblacion poblacion;
  int n_nidos = 50;
  int max_evaluaciones_bl = 1200;
  int evaluaciones = 0;
  int generaciones = 0;
  solucion cuco;

  t_inicio = clock();
  inicializarPoblacion(m, poblacion, n_nidos, n);
  evaluarPoblacion(poblacion, evaluaciones, m);

  while (evaluaciones < MAX_EVALUACIONES){
    generaciones++;
    cuco = obtenerCuckooPorLevy(m, n);
    evaluaciones += busquedaLocal(m, cuco, max_evaluaciones_bl);
    evaluarSolucion(cuco, m);
    ++evaluaciones;
    reemplazarNido(poblacion, cuco);
    reemplazarPoblacion(poblacion, p_a, m, n, evaluaciones);
    if((generaciones % 10) == 0)
      hibridar(poblacion, max_evaluaciones_bl, evaluaciones, m);
  }

  t_total = clock() - t_inicio;
  solucion resultado = poblacion.v[poblacion.mejor_solucion];

  cout << resultado.coste << "\t" << (double) t_total / CLOCKS_PER_SEC << "\t" << "\t" << evaluaciones << endl;
  return resultado.coste;
}


/* --------------------------- MAIN ---------------------------*/

int main(int argc, char *argv[]){
  int n_total, n_sel; // n_total = número de elementos &&
                      // n_sel = el número de elementos a seleccionar del problema
  const int MAX_EVALUACIONES = 100000;

  cin >> n_total >> n_sel; // inicializo los valores con la primera línea del fichero
  vector<double> v(n_total, 0);
  vector<vector<double>> m(n_total, v); // m = matriz de entradas
  leerDatos(m); // inicializo la matriz de entradas

  int semilla = atoi(argv[1]);
  // Fijamos la semilla
  srand(semilla);

  CS_hibrido(m, n_sel, MAX_EVALUACIONES); // aplico el algoritmo AGGuniforme
}
