#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <stdlib.h>     // srand y rand
#include <algorithm>    // sort y random_shuffle
#include <time.h>

using namespace std;

////////////////// LOCAL SEARCH ///////////////////////

template <class T>
double singleContribution(T &container, int elem) {
  double result = 0;
  typename T::iterator it;
  for (it = container.begin(); it != container.end(); it++) {
    result += MAT[ elem ][ *it ];
  }
  return result;
}

// Returns the fitness of the whole solution
template <class T>
double evaluateSolution(T &container) {
  double fitness = 0;
  typename T::iterator it;
  for (it = container.begin(); it != container.end(); it++) {
    fitness += singleContribution(container, *it);
  }
  // Counting twice all the possible distances
  return fitness /= 2;
}

// Comparison operator for ordering the solution vector
// Keeps at the front the element with less contribution to the fitness
bool operator < (const pair<int,double> &p1, const pair<int,double> &p2) {
    return p1.second < p2.second;
}

struct solution_int {
  vector<int> v;
  double fitness;
};

double updateSolution(solution_int &sol) {
  sol.fitness = evaluateSolution(sol.v);
  return sol.fitness;
}

// Order sol.v by conribution to the solution in ascending order
void orderSolutionByContribution(solution_int &sol) {
  pair<int, double> p (0, 0.0);
  vector< pair<int, double> > pairs_v ( sol.v.size(), p);

  // Initialize the auxiliar vector
  for (unsigned i=0; i< pairs_v.size(); i++) {
    pairs_v[i].first = sol.v[i];
    pairs_v[i].second = singleContribution(sol.v, pairs_v[i].first);
  }

  // Order the vector by contribution
  sort(pairs_v.begin(), pairs_v.end());

  // Save the ordering
  for (unsigned i=0; i< pairs_v.size(); i++) {
    sol.v[i] = pairs_v[i].first;
  }
}

// Computes a single step in the exploration, changing "sol"
bool stepInNeighbourhood (solution_int &sol, int &evaluations, int MAX) {
  double percentage_studied;
  unsigned i = 0, j, element_out, total_tries, max_i, max_randoms, k;
  double newContribution, oldContribution;
  int real_evaluations = 0;

  orderSolutionByContribution(sol);

  // percentage_studied = 0.1;
  // total_tries = 50000;

  percentage_studied = 0.1;
  total_tries = MAX;

  max_i = max(percentage_studied * sol.v.size(), 1.0);
  max_randoms = total_tries / max_i;

  // Fill hash with our used values
  unordered_set<int> s;
  for (unsigned i=0; i<sol.v.size(); i++) {
    s.insert( sol.v[i] );
  }

  // Explore the neighbourhood and return the firstly found better option
  while (i < max_i) {
    // Save data of the element we are trying to swap
    element_out = sol.v[i];
    oldContribution = singleContribution(sol.v, element_out);

    k = 0;
    j = rand() % MAT.size();
    while (j < MAT.size() && k < max_randoms) {
      // Try the swap if the element 'j' is not in the current solution
      if ( s.find(j) == s.end() ) {
        newContribution = singleContribution(sol.v, j) - MAT[j][element_out];
        if ( newContribution > oldContribution ) {
          sol.v[i] = j;
          sol.fitness = sol.fitness + newContribution - oldContribution;
          return false;
        }
        k++;

        real_evaluations++;
        if (real_evaluations % sol.v.size() == 0) {
          evaluations++;
          real_evaluations = 0;
        }
      }
      j = rand() % MAT.size();
    }
    i++;
  }
  return true;
}

void BitsToInt(solution &sol_bits, solution_int &sol) {
  sol.v.clear();
  for(unsigned i=0; i<sol_bits.v.size(); i++) {
    if ( sol_bits.v[i] ) {
      sol.v.push_back(i);
    }
  }
}

void IntToBits(solution_int &sol, solution &sol_bits, int tam) {
  sol_bits.v = vector<bool> (tam, false);
  for(unsigned i=0; i<sol.v.size(); i++) {
    sol_bits.v[ sol.v[i] ] = true;
  }
}

// Computes the local search algorithm for a random starting solution
int localSearch(solution &sol_bits, int MAX_EVALUATIONS) {
  int tam_sol_bits = sol_bits.v.size();
  solution_int sol;
  bool stop = false;
  int evaluations = 0;

  BitsToInt(sol_bits, sol);
  updateSolution(sol);

  while (!stop && evaluations < MAX_EVALUATIONS) {
    stop = stepInNeighbourhood(sol, evaluations, MAX_EVALUATIONS-evaluations);
    // cout << sol.fitness << "\t" << iterations << endl;
  }

  // output: Fitness - Time - Iterations
  // cout << sol.fitness << "\t" << (double) t_total / CLOCKS_PER_SEC << "\t" << iterations<< endl;
  IntToBits(sol, sol_bits, tam_sol_bits);
  return evaluations;
}

///////////////////////////// GENETIC ///////////////////////////////////////

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
void evaluarPoblacion(poblacion &p, int &iteraciones, vector<vector<double>> &m){
  for(int i = 0; i < p.n_individuos; ++i){
    if(!p.v[i].evaluada){
      evaluarSolucion(p.v[i], m);
      ++iteraciones;
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
void memetizar(poblacion &poblacion, int tipo, int max_evaluaciones, int &evaluaciones, double p_busqueda_local) {
  if(tipo == 0){
    for(int i = 0; i < poblacion.n_individuos; ++i){
      evaluaciones += localSearch(poblacion.v[i], max_evaluaciones);
      evaluarSolucion(poblacion.v[i]);
      if(poblacion.v[i].coste > poblacion.max_coste){
        poblacion.max_coste = poblacion.v[i].coste;
        poblacion.mejor_solucion = i;
      }
    }
  } else if(tipo == 1){
    int numero_memetizaciones = poblacion.n_individuos * p_busqueda_local;
    for(int i = 0; i < numero_memetizaciones; ++i){
      int numero_aleatorio = rand() % poblacion.n_individuos;
      evaluaciones += localSearch(poblacion.v[numero_aleatorio], max_evaluaciones);
      evaluarSolucion(poblacion.v[numero_aleatorio]);
      if(poblacion.v[numero_aleatorio].coste > poblacion.max_coste){
        poblacion.max_coste = poblacion.v[numero_aleatorio].coste;
        poblacion.mejor_solucion = numero_aleatorio;
      }
    }
  } else if(tipo == 2){
    //ARREGLAR
    cout << "\nNO HECHO" << endl;
    evaluaciones += localSearch(poblacion.v[poblacion.mejor_solucion], max_evaluaciones);
    evaluarSolucion(poblacion.v[ poblacion.mejor_solucion]);
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
  inicializarPoblacion(m, poblacion, n_individuos, n);
  evaluarPoblacion(poblacion, evaluaciones, m);

  while (evaluaciones < MAX_EVALUACIONES) {
    generaciones++;
    seleccionarIndividuos(poblacion_actual, poblacion_nueva);
    cruce(poblacion_nueva, p_cruce);
    mutarPoblacion(poblacion_nueva, p_mutacion, n, evaluaciones, m);
    evaluarPoblacion(poblacion_nueva, evaluaciones);
    reemplazarPoblacion(poblacion_actual, poblacion_nueva);
    if((generaciones % 10) == 0)
      memetizar(poblacion_actual, tipo, max_evaluaciones_bl, evaluaciones, p_busqueda_local);
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

  cin >> n_total >> n_sel; // inicializo los valores con la primera línea del fichero
  vector<double> v(n_total, 0);
  vector<vector<double>> m(n_total, v); // m = matriz de entradas
  leerDatos(m); // inicializo la matriz de entradas

  int semilla = atoi(argv[1]);
  int tipo = atoi(argv[2]);
  cout << "\n\nCOMPROBACIONES TIPO\n" << endl;
  // Fijamos la semilla
  srand(semilla);

  AM(m, n_sel, MAX_EVALUACIONES, tipo); // aplico el algoritmo AGGuniforme
}
