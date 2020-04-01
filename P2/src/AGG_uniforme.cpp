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
  // ganador_torneo 'n' elements
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
    suma += v[i]*m[elemento][i];
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
    if(v[i])
      coste += distanciaAUnConjunto(i, conjunto, m);
  return coste /= 2;
}

double evaluarSolucion(solucion &s, vector<vector<double>> &m){
  s.coste = costeSolucion(s.v, m);
  s.evaluada = true;
  return s.coste;
}

void evaluarPoblacion(poblacion &p, int &iteraciones, vector<vector<double>> &m){
  for(int i = 0; i < p.n_individuos; ++i){
    if(!p.v[i].evaluada){
      evaluarSolucion(p.v[i], m);
      ++iteraciones;
    }
    if(p.v[i].coste > p.max_coste){
      p.mejor_solucion = i;
      p.max_coste = p.v[i].coste;
    }
  }
}

int torneoBinario(poblacion &p){
  int r1 = random(0, p.n_individuos);
  int r2 = random(0, p.n_individuos);
  if(p.v[r1].coste > p.v[r2].coste)
    return r1;
  else
    return r2;
}

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
      poblacion_nueva.max_coste = poblacion_actual.v[i].coste;
    }
  }
}

void repararSolucion(solucion &s, int n_sel) {
  int seleccionados = 0, n_aleatorio;

  for(unsigned i=0; i<s.v.size(); ++i)
    if(s.v[i])
      seleccionados++;

  while(seleccionados > n_sel){
    n_aleatorio = random(0, s.v.size());
    if(s.v[n_aleatorio]){
      s.v[n_aleatorio] = !s.v[n_aleatorio];
      --seleccionados;
    }
  }

  while(seleccionados < n_sel){
    n_aleatorio = random(0, s.v.size());
    if(!s.v[n_aleatorio]){
      s.v[n_aleatorio] = !s.v[n_aleatorio];
      ++seleccionados;
    }
  }
}

// Operador de cruce uniforme
solucion cruceUniforme(solucion &p1, solucion &p2) {
  solucion hijo = p1;
  hijo.evaluada = false;
  int n_sel = 0;

  for(unsigned i = 0; i < p1.v.size(); ++i){
    if(p1.v[i])
      n_sel++;
    if(p1.v[i] && p2.v[i]){
      hijo.v[i] = true;
    } else if(!p1.v[i] && !p2.v[i]){
      hijo.v[i] = false;
    } else{
      hijo.v[i] = random(0,2) == 0;
    }
  }

  repararSolucion(hijo, n_sel);
  return hijo;
}

void cruce(poblacion &p, double probabilidad_cruce){
  int n_cruces = probabilidad_cruce * p.n_individuos / 2 ;
  int p1, p2;
  solucion ch1, ch2;

  for (int i = 0; i < n_cruces; ++i){
    p1 = random(0, p.n_individuos);
    do{
      p2 = random(0, p.n_individuos);
    } while (p1 == p2);
    ch1 = cruceUniforme(p.v[p1], p.v[p2]);
    ch2 = cruceUniforme(p.v[p1], p.v[p2]);
    p.v[p1] = ch1;
    p.v[p2] = ch2;
  }
}


// Computes the local search algorithm for a random starting solucion
// This implementation doesn't assume the pop is ordered
double AGGu(vector<vector<double>> &m, int n, int MAX_EVALUACIONES){
  int evaluaciones = generaciones = 0, n_individuos = 50;
  double p_mutacion = 0.001, p_cruce = 0.7;
  clock_t t_total, t_inicio;
  poblacion poblacion_nueva, poblacion_actual;

  t_inicio = clock();
  inicializarPoblacion(m, poblacion_actual, n_individuos, n);
  evaluarPoblacion(poblacion_actual, evaluaciones, m);

  while (evaluaciones < MAX_EVALUACIONES) {
    generaciones++;
    seleccionarIndividuos(poblacion_actual, poblacion_nueva);
    cruce(poblacion_nueva, p_cruce);


    
    mutatePop(poblacion_nueva, p_mutacion, n, evaluaciones);
    evaluarPoblacion(poblacion_nueva, evaluaciones);
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
