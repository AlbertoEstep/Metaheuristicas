#include <iostream>
#include <vector>
#include <set>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

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

/* Elegir el elemento de los seleccionados que aporta mayor diversidad

Parametros:
  - s = solucion
  - m = matriz de distancias
*/
int elegirMayorContribucionSeleccionados(solucion &s, vector<vector<double>> &m){
  int i_max_coste = 0, n_solucion = s.v.size();
  double max_aportacion = 0, aportacion_diversidad;
  for(int i = 0; i < n_solucion; ++i){
    if(s.v[i]){
      aportacion_diversidad = distanciaAUnConjunto(i, s.v, m);
      if(aportacion_diversidad > max_aportacion){
        i_max_coste = i;
        max_aportacion = aportacion_diversidad;
      }
    }
  }
  return i_max_coste;
}

/* Elegir el elemento de los no seleccionados que aporta mayor diversidad

Parametros:
  - s = solucion
  - m = matriz de distancias
*/
int elegirMayorContribucionNoSeleccionados(solucion &s, vector<vector<double>> &m) {
  int i_max_coste = 0, n_solucion = s.v.size();
  double max_aportacion = 0, aportacion_diversidad;
  for(int i = 0; i < n_solucion; ++i){
    if(!s.v[i]){
      aportacion_diversidad = distanciaAUnConjunto(i, s.v, m);
      if(aportacion_diversidad > max_aportacion){
        i_max_coste = i;
        max_aportacion = aportacion_diversidad;
      }
    }
  }
  return i_max_coste;
}

/* Metodo de reparacion de la solucion

Parametros:
  - s = solucion a reparar
  - n_sel = numero de elementos que formaran la solucion
  - m = matriz distancias
*/
void repararSolucion(solucion &s, int n_sel, vector<vector<double>> &m) {
  int seleccionados = 0, i_max_coste;

  for(unsigned i=0; i<s.v.size(); ++i)
    if(s.v[i])
      seleccionados++;

  while(seleccionados > n_sel){
    i_max_coste = elegirMayorContribucionSeleccionados(s, m);
    if(s.v[i_max_coste]){
      s.v[i_max_coste] = false;
      --seleccionados;
    }
  }
  while(seleccionados < n_sel){
    i_max_coste = elegirMayorContribucionNoSeleccionados(s, m);
    if(!s.v[i_max_coste]){
      s.v[i_max_coste] = true;
      ++seleccionados;
    }
  }
}

/* Metodo de cruce entre soluciones

Parametros:
  - padre1 = una solucion a cruzar
  - padre2 = la otra solucion a cruzar
*/
solucion cruceUniforme(solucion &padre1, solucion &padre2, vector<vector<double>> &m) {
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
  repararSolucion(hijo, n_sel, m);
  return hijo;
}

/* Metodo de cruce entre la poblacion

Parametros:
  - p = poblacion a cruzar
  - probabilidad_cruce = probabilidad de dos individuos de cruzarse
*/
void cruce(poblacion &p, double probabilidad_cruce, vector<vector<double>> &m){
  int n_cruces = probabilidad_cruce * p.n_individuos / 2 ;
  int i1, i2;
  solucion hijo1, hijo2;

  for (int i = 0; i < n_cruces; ++i){
    i1 = rand() % p.n_individuos;
    do{
      i2 = rand() % p.n_individuos;
    } while (i1 == i2);
    hijo1 = cruceUniforme(p.v[i1], p.v[i2], m);
    hijo2 = cruceUniforme(p.v[i1], p.v[i2], m);
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

  // Si la población nueva es peor que la anterior
  if(poblacion_nueva.max_coste < poblacion_actual.max_coste){
    // Busco el peor elemento de la poblacion nueva
    for(int j = 0; j < poblacion_nueva.n_individuos; ++j){
      if(poblacion_nueva.v[j].coste < coste_minimo){
        indice_peor_solucion = j;
        coste_minimo = poblacion_nueva.v[j].coste;
      }
    }
    // Guardo la mejor solución de la poblacion actual
    i = poblacion_actual.mejor_solucion;
    mejor_solucion = poblacion_actual.v[i];
    // Intercambio la soluciones
    poblacion_actual.v.swap(poblacion_nueva.v);
    // Guardo la mejor solucion anterior en la poblacion nueva.
    poblacion_actual.v[indice_peor_solucion] = mejor_solucion;
  } else{
    poblacion_actual.v.swap(poblacion_nueva.v);
    poblacion_actual.max_coste = poblacion_nueva.max_coste;
    poblacion_actual.mejor_solucion = poblacion_nueva.mejor_solucion;
  }
}



/* Metodo de general del algoritmo

Parametros:
  - m = matriz de distancias
  - n = numero de elementos a seleccionar
  - MAX_EVALUACIONES = numero de evaluaciones maximo permitido
*/
double AGGuniforme(vector<vector<double>> &m, int n, int MAX_EVALUACIONES){
  int evaluaciones = 0, generaciones = 0, n_individuos = 50;
  double p_mutacion = 0.001, p_cruce = 0.7;
  clock_t t_total, t_inicio;
  poblacion poblacion_nueva, poblacion_actual;

  t_inicio = clock();
  inicializarPoblacion(m, poblacion_actual, n_individuos, n);
  evaluarPoblacion(poblacion_actual, evaluaciones, m);

  while (evaluaciones < MAX_EVALUACIONES){
    generaciones++;
    seleccionarIndividuos(poblacion_actual, poblacion_nueva);
    cruce(poblacion_nueva, p_cruce, m);
    mutarPoblacion(poblacion_nueva, p_mutacion, evaluaciones, m);
    evaluarPoblacion(poblacion_nueva, evaluaciones, m);
    reemplazarPoblacion(poblacion_actual, poblacion_nueva);
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
  // Fijamos la semilla
  srand(semilla);

  AGGuniforme(m, n_sel, MAX_EVALUACIONES); // aplico el algoritmo AGGuniforme
}
