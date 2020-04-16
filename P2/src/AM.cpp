#include <iostream>
#include <vector>
#include <unordered_set>
#include <stdlib.h>     // srand y rand
#include <algorithm>    // sort y random_shuffle
#include <time.h>

using namespace std;

////////////////// LOCAL SEARCH ///////////////////////

// Estructura para representar una solucion en representacion entera
struct solucion_ints{
  vector<int> v;  // Vector de enteros donde cada entero indica que punto del
                  // dominio pertenece a la solucion.
  double coste;   // Diversidad de la solucion
};

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

/* Sobrecargamos el operador "menor que" entre dos parejas.
Así una pareja p1 será menor que otra p2 (p1 < p2) si y solo si la segunda
componente (el coste) de p1 es menor al de p2.

Parametros:
  - p1 = pareja (índice-coste)
  - p2 = pareja (índice-coste)
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

/* Actualizamos el coste de la solucion.

Parametros:
  - s = solucion en representacion de ints.
*/
double actualizarSolucion(solucion_ints &s, vector<vector<double>> &m) {
  s.coste = costeSolucion(s.v, m);
  return s.coste;
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

///////////////////////////// GENETIC ///////////////////////////////////////

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

/* Torneo entre dos individuos de la poblacion

Parametros:
  - p = poblacion
*/
int torneoBinario(poblacion &p){
  int r1 = rand() % p.n_individuos, r2 = rand() % p.n_individuos;

  if(p.v[r1].coste > p.v[r2].coste)
    return r1;
  else
    return r2;
}

/* Metodo de seleccion de individuos de la poblacion

Parametros:
  - poblacion_actual = poblacion donde elegiremos los individuos
  - poblacion_nueva = poblacion resultante
*/
void seleccionarIndividuos(poblacion &poblacion_actual, poblacion &poblacion_nueva){
  int ganador_torneo;
  poblacion_nueva.n_individuos = poblacion_actual.n_individuos;
  poblacion_nueva.max_coste = 0;
  poblacion_nueva.v.resize(poblacion_nueva.n_individuos);
  for(int i = 0; i < poblacion_actual.n_individuos; ++i){
    ganador_torneo = torneoBinario(poblacion_actual);
    poblacion_nueva.v[i] = poblacion_actual.v[ganador_torneo];
    if(poblacion_nueva.v[i].coste > poblacion_nueva.max_coste){
      poblacion_nueva.mejor_solucion = i;
      poblacion_nueva.max_coste = poblacion_nueva.v[i].coste;
    }
  }
}

/* Metodo de reparacion de la solucion

Parametros:
  - s = solucion a reparar
  - n_sel = numero de elementos que formaran la solucion
*/
void repararSolucion(solucion &s, int n_sel) {
  int seleccionados = 0, n_aleatorio;

  for(unsigned i = 0; i < s.v.size(); ++i)
    if(s.v[i])
      seleccionados++;
  while(seleccionados > n_sel){
    n_aleatorio = rand() % s.v.size();
    if(s.v[n_aleatorio]){
      s.v[n_aleatorio] = !s.v[n_aleatorio];
      --seleccionados;
    }
  }
  while(seleccionados < n_sel){
    n_aleatorio = rand() % s.v.size();
    if(!s.v[n_aleatorio]){
      s.v[n_aleatorio] = !s.v[n_aleatorio];
      ++seleccionados;
    }
  }
}

/* Metodo de cruce entre soluciones

Parametros:
  - padre1 = una solucion a cruzar
  - padre2 = la otra solucion a cruzar
*/
solucion cruceUniforme(solucion &padre1, solucion &padre2) {
  solucion hijo = padre1;
  hijo.evaluada = false;
  int n_sel = 0, n_aleatorio;

  for(unsigned i = 0; i < padre1.v.size(); ++i){
    if(padre1.v[i])
      ++n_sel;
    if(padre1.v[i] && padre2.v[i]){
      hijo.v[i] = true;
    } else if(!padre1.v[i] && !padre2.v[i]){
      hijo.v[i] = false;
    } else{
      n_aleatorio = rand() % 2;
      hijo.v[i] = (n_aleatorio == 0);
    }
  }
  repararSolucion(hijo, n_sel);
  return hijo;
}

/* Metodo de cruce entre la poblacion

Parametros:
  - p = poblacion a cruzar
  - probabilidad_cruce = probabilidad de dos individuos de cruzarse
*/
void cruce(poblacion &p, double probabilidad_cruce){
  int n_cruces = probabilidad_cruce * p.n_individuos / 2 ;
  int i1, i2;
  solucion hijo1, hijo2;

  for (int i = 0; i < n_cruces; ++i){
    i1 = rand() % p.n_individuos;
    do{
      i2 = rand() % p.n_individuos;
    } while (i1 == i2);
    hijo1 = cruceUniforme(p.v[i1], p.v[i2]);
    hijo2 = cruceUniforme(p.v[i1], p.v[i2]);
    p.v[i1] = hijo1;
    p.v[i2] = hijo2;
  }
}


/* Metodo de mutacion entre la solucion

Parametros:
  - s = solucion a mutar
  - evaluaciones = numero de evaluaciones de la funcion objetivo hechas actualmente
  - m = matriz de distancias
*/
void mutarSolucion(solucion &s, int &evaluaciones, vector<vector<double>> &m){
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

/* Metodo de mutacion de la poblacion

Parametros:
  - p = poblacion a mutar
  - p_mutacion = probabilidad de un gen de mutar.
  - evaluaciones = numero de evaluaciones de la funcion objetivo hechas actualmente
  - m = matriz de distancias
*/
void mutarPoblacion(poblacion &p, double &p_mutacion, int &evaluaciones, vector<vector<double>> &m){
  int numero_aleatorio = 0, n_mutaciones = p_mutacion * p.n_individuos * m.size();
  for(int i = 0; i < n_mutaciones; ++i){
    numero_aleatorio = rand() % p.n_individuos;
    mutarSolucion(p.v[numero_aleatorio], evaluaciones, m);
  }
  if(p.max_coste < p.v[numero_aleatorio].coste){
    p.mejor_solucion = numero_aleatorio;
    p.max_coste = p.v[numero_aleatorio].coste;
  }
}

/* Metodo de reemplazamiento de individuos de la poblacion

Parametros:
  - poblacion_actual = poblacion a actualizar
  - poblacion_nueva = poblacion de hijos que pasara a ser poblacion_actual
*/
void reemplazarPoblacion(poblacion &poblacion_actual, poblacion &poblacion_nueva){
  solucion mejor_solucion;
  int indice_peor_solucion = poblacion_nueva.mejor_solucion;
  int coste_minimo = poblacion_nueva.max_coste;
  int i;

  if(poblacion_nueva.max_coste < poblacion_actual.max_coste){
    for(int j = 0; j < poblacion_nueva.n_individuos; ++j){
      if(poblacion_nueva.v[j].coste < coste_minimo){
        indice_peor_solucion = j;
        coste_minimo = poblacion_nueva.v[j].coste;
      }
    }
    i = poblacion_actual.mejor_solucion;
    mejor_solucion = poblacion_actual.v[i];
    poblacion_actual.v.swap(poblacion_nueva.v);
    poblacion_actual.v[indice_peor_solucion] = mejor_solucion;
  } else{
    poblacion_actual.v.swap(poblacion_nueva.v);
    poblacion_actual.max_coste = poblacion_nueva.max_coste;
    poblacion_actual.mejor_solucion = poblacion_nueva.mejor_solucion;
  }
}

// Tipo 0 = Poblacion entera cada 10 iteraciones
// Tipo 1 = Cada elemento con probabilidad p_busqueda_local
// Tipo 2 = Unicamente el mejor de la pob
void memetizar(poblacion &poblacion, int tipo, int max_evaluaciones, int &evaluaciones, double p_busqueda_local, vector<vector<double>> &m) {
  if(tipo == 0){
    for(int i = 0; i < poblacion.n_individuos; ++i){
      evaluaciones += busquedaLocal(m, poblacion.v[i], max_evaluaciones);
      evaluarSolucion(poblacion.v[i], m);
      if(poblacion.v[i].coste > poblacion.max_coste){
        poblacion.max_coste = poblacion.v[i].coste;
        poblacion.mejor_solucion = i;
      }
    }
  } else if(tipo == 1){
    int numero_memetizaciones = poblacion.n_individuos * p_busqueda_local;
    for(int i = 0; i < numero_memetizaciones; ++i){
      int numero_aleatorio = rand() % poblacion.n_individuos;
      evaluaciones += busquedaLocal(m, poblacion.v[numero_aleatorio], max_evaluaciones);
      evaluarSolucion(poblacion.v[numero_aleatorio], m);
      if(poblacion.v[numero_aleatorio].coste > poblacion.max_coste){
        poblacion.max_coste = poblacion.v[numero_aleatorio].coste;
        poblacion.mejor_solucion = numero_aleatorio;
      }
    }
  } else if(tipo == 2){
    //ARREGLAR
    cout << "\nNO HECHO" << endl;
    evaluaciones += busquedaLocal(m, poblacion.v[poblacion.mejor_solucion], max_evaluaciones);
    evaluarSolucion(poblacion.v[ poblacion.mejor_solucion], m);
    poblacion.max_coste = poblacion.v[poblacion.mejor_solucion].coste;
  }
}

/* Metodo de general del algoritmo

Parametros:
  - m = matriz de distancias
  - n = numero de elementos a seleccionar
  - MAX_EVALUACIONES = numero de evaluaciones maximo permitido
  - tipo = tipo de la memetizacion
*/
double AM(vector<vector<double>> &m, int n, int MAX_EVALUACIONES, int tipo){
  int evaluaciones = 0, generaciones = 0, n_individuos = 50, max_evaluaciones_bl = 400;
  double p_mutacion = 0.001, p_cruce = 0.7, p_busqueda_local = 0.1;
  clock_t t_total, t_inicio;
  poblacion poblacion_actual, poblacion_nueva;

  t_inicio = clock();
  inicializarPoblacion(m, poblacion_actual, n_individuos, n);
  evaluarPoblacion(poblacion_actual, evaluaciones, m);

  while (evaluaciones < MAX_EVALUACIONES) {
    generaciones++;
    seleccionarIndividuos(poblacion_actual, poblacion_nueva);
    cruce(poblacion_nueva, p_cruce);
    mutarPoblacion(poblacion_nueva, p_mutacion, evaluaciones, m);
    evaluarPoblacion(poblacion_nueva, evaluaciones, m);
    reemplazarPoblacion(poblacion_actual, poblacion_nueva);
    if((generaciones % 10) == 0)
      memetizar(poblacion_actual, tipo, max_evaluaciones_bl, evaluaciones, p_busqueda_local, m);
  }

  t_total = clock() - t_inicio;
  solucion resultado = poblacion_actual.v[poblacion_actual.mejor_solucion];

  cout << resultado.coste << "\t" << (double) t_total / CLOCKS_PER_SEC << "\t" << generaciones << "\t" << evaluaciones << endl;
  return resultado.coste;
}

/* --------------------------- MAIN ---------------------------*/

int main(int argc, char *argv[]){
  int n_total, n_sel; // n_total = número de elementos &&
                      // n_sel = el número de elementos a seleccionar del problema
  const int MAX_EVALUACIONES = 50000;
  if(argc != 3) {
    cout << "No ha introducido los parametros correctos.\nRecuerde: ./AM semilla tipo" << endl;
    exit(1);
  }
  int semilla = atoi(argv[1]);
  int tipo = atoi(argv[2]);
  // Fijamos la semilla
  srand(semilla);

  if(tipo != 0 && tipo != 1 && tipo != 2){
    cout << "El tipo debe ser un valor de entre {0, 1, 2}" << endl;
    exit(1);
  }
  cin >> n_total >> n_sel; // inicializo los valores con la primera línea del fichero
  vector<double> v(n_total, 0);
  vector<vector<double>> m(n_total, v); // m = matriz de entradas
  leerDatos(m); // inicializo la matriz de entradas

  AM(m, n_sel, MAX_EVALUACIONES, tipo); // aplico el algoritmo AGGuniforme
}
