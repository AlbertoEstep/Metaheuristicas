#include <iostream>
#include <vector>
#include <set>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <algorithm>

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

/* Sobrecargamos el operador < entre soluciones para poder ordenar la poblacion.
Solucion1 < Solucion2 <=> Diversidad de Solucion1 > Diversidad de Solucion2
*/
bool operator < (const solucion &s1, const solucion &s2) {
    return s1.coste > s2.coste;
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
  - p = poblacion donde elegiremos los individuos
  - padre1 = primera solucion seleccionada
  - padre2 = segunda solucion seleccionada
*/
void seleccionarIndividuos(poblacion &p, solucion &padre1, solucion &padre2){
  int hijo1, hijo2;

  hijo1 = torneoBinario(p);
  do{
    hijo2 = torneoBinario(p);
  } while (hijo2 == hijo1);

  padre1 = p.v[hijo1];
  padre2 = p.v[hijo2];
}

/* Metodo de reparacion de la solucion

Parametros:
  - s = solucion a reparar
  - n_sel = numero de elementos que formaran la solucion
*/
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
  - padre1 = primer padre a cruzar
  - padre2 = segundo padre a cruzar
  - hijo1 = solucion obtenida al cruzar padre1 y padre2 la primera vez
  - hijo2 = solucion obtenida al cruzar padre1 y padre2 la segunda vez
*/
void cruce(solucion &padre1, solucion &padre2, solucion &hijo1, solucion &hijo2){
  hijo1 = cruceUniforme(padre1, padre2);
  hijo2 = cruceUniforme(padre1, padre2);
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
void mutarPoblacion(solucion &hijo1, solucion &hijo2, double &p_mutacion, int &evaluaciones, vector<vector<double>> &m){
  int n_mutaciones = p_mutacion * m.size();
  if(n_mutaciones == 0) // Si n_mutaciones = 0, le damos la probabilidad del 50% a un gen a mutar
    n_mutaciones = rand() % 2;
  for(int i = 0; i < n_mutaciones; ++i){
    mutarSolucion(hijo1, evaluaciones, m);
    mutarSolucion(hijo2, evaluaciones, m);
  }
}

/* Metodo de reemplazamiento de individuos de la poblacion

Parametros:
  - p = poblacion a actualizar
  - hijo1 = nuevo individuo a introducir
  - hijo2 = nuevo individuo a introducir
*/
void reemplazarPoblacion(poblacion &p, solucion &hijo1, solucion &hijo2){
  p.v.push_back(hijo1);
  p.v.push_back(hijo2);
  sort(p.v.begin(), p.v.end());
  p.v.resize(p.v.size() - 2);
  p.max_coste = p.v[0].coste;
}

/* Metodo de general del algoritmo

Parametros:
  - m = matriz de distancias
  - n = numero de elementos a seleccionar
  - MAX_EVALUACIONES = numero de evaluaciones maximo permitido
*/
double AGGuniforme(vector<vector<double>> &m, int n, int MAX_EVALUACIONES){
  int evaluaciones = 0, generaciones = 0, n_individuos = 50;
  double p_mutacion = 0.001;
  clock_t t_total, t_inicio;
  poblacion poblacion;
  solucion padre1, padre2, hijo1, hijo2;

  t_inicio = clock();
  inicializarPoblacion(m, poblacion, n_individuos, n);
  evaluarPoblacion(poblacion, evaluaciones, m);
  sort(poblacion.v.begin(), poblacion.v.end());
  poblacion.mejor_solucion = 0;

  while(evaluaciones < MAX_EVALUACIONES){
    generaciones++;
    seleccionarIndividuos(poblacion, padre1, padre2);
    cruce(padre1, padre2, hijo1, hijo2);
    mutarPoblacion(hijo1, hijo2, p_mutacion, evaluaciones, m);
    evaluarSolucion(hijo1, m);
    evaluarSolucion(hijo2, m);
    evaluaciones += 2;
    reemplazarPoblacion(poblacion, hijo1, hijo2);
  }

  t_total = clock() - t_inicio;
  solucion resultado = poblacion.v[poblacion.mejor_solucion];

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
