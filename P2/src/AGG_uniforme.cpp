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

void solucionAleatoria(vector<vector<double>> &m, solucion &s, int n){
  int n_elegidos = 0, numero_aleatorio;
  // Set the flag and clear the solution
  s.evaluada = false;
  s.v = vector<bool>(m.size(), false);
  // ganador_torneo 'n' elements
  while (n_elegidos < n){
    numero_aleatorio = rand() % m.size();
    if(!s.v[numero_aleatorio]){
      s.v[numero_aleatorio] = true;
      n_elegidos++;
    }
  }
}

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
  int r1 = rand() % p.n_individuos, r2 = rand() % p.n_individuos;

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
      poblacion_nueva.max_coste = poblacion_nueva.v[i].coste;
    }
  }
}

void repararSolucion(solucion &s, int n_sel) {
  int seleccionados = 0, n_aleatorio;

  for(unsigned i=0; i<s.v.size(); ++i)
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

// Operador de cruce uniforme
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

// Mutate the solution by swapping two random elements
void mutarSolucion(solucion &s, int &iteraciones, vector<vector<double>> &m){
  int n_aleatorio1, n_aleatorio2;
  // Find elements to swap
  do {
    n_aleatorio1 = rand() % s.v.size();
  } while(s.v[n_aleatorio1]);
  do{
    n_aleatorio2 = rand() % s.v.size();;
  } while(!s.v[n_aleatorio2]);

  // Swap elements
  s.v[n_aleatorio1] = true;
  s.v[n_aleatorio2] = false;

  // Update the fitness if possible
  if(s.evaluada){
    double antiguo_coste = distanciaAUnConjunto(n_aleatorio2, s.v, m) - m[n_aleatorio2][n_aleatorio1];
    double nuevo_coste = distanciaAUnConjunto(n_aleatorio1, s.v, m);
    s.coste = s.coste + nuevo_coste - antiguo_coste;
    ++iteraciones;
  }
}

void mutarPoblacion(poblacion &p, double &p_mutacion, int &iteraciones, vector<vector<double>> &m){
  int numero_aleatorio = 0, n_mutaciones = p_mutacion * p.n_individuos * m.size();
  for(int i = 0; i < n_mutaciones; ++i){
    numero_aleatorio = rand() % p.n_individuos;
    mutarSolucion(p.v[numero_aleatorio], iteraciones, m);
  }
  if(p.max_coste < p.v[numero_aleatorio].coste){
    p.mejor_solucion = numero_aleatorio;
    p.max_coste = p.v[numero_aleatorio].coste;
  }
}


void reemplazarPoblacion(poblacion &poblacion_actual, poblacion &poblacion_nueva){
  solucion mejor_solucion;
  int i;

  if(poblacion_nueva.max_coste < poblacion_actual.max_coste){
    i = poblacion_actual.mejor_solucion;
    mejor_solucion = poblacion_actual.v[i];
    poblacion_actual.v.swap(poblacion_nueva.v);
    poblacion_actual.v[i] = mejor_solucion;
  } else{
    poblacion_actual.v.swap(poblacion_nueva.v);
    poblacion_actual.max_coste = poblacion_nueva.max_coste;
    poblacion_actual.mejor_solucion = poblacion_nueva.mejor_solucion;
  }
}


// Computes the local search algorithm for a random starting solucion
// This implementation doesn't assume the pop is ordered
double AGGuniforme(vector<vector<double>> &m, int n, int MAX_EVALUACIONES){
  int evaluaciones = 0, generaciones = 0, n_individuos = 50;
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
    mutarPoblacion(poblacion_nueva, p_mutacion, evaluaciones, m);
    evaluarPoblacion(poblacion_nueva, evaluaciones, m);
    reemplazarPoblacion(poblacion_actual, poblacion_nueva);
  }

  t_total = clock() - t_inicio;
  solucion resultado = poblacion_actual.v[poblacion_actual.mejor_solucion];

  // output: coste - Time - Iterations
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
  // Fijamos la semilla
  srand(semilla);

  AGGuniforme(m, n_sel, MAX_EVALUACIONES); // aplico el algoritmo AGGuniforme
}
