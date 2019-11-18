/*
 *  Programacion Paralela con OpenMP
 *
 * Parrado Arribas, Alejandro
 * Romera Gomez, Alicia
 * Sanchez Cerro, Laura
 * Vinagre Blanco, Andres
 *
 * Arquitectura de Computadores, Grupo 81, 2019 - 2020
 */


/*Librerias a incluir*/
#include <iostream> /*Libreria para leer e imprimir datos en la terminal*/
#include <math.h> /*Libreria para operaciones matematicas*/
#include <string> /*Libreria para trabajar con strings*/
#include <fstream> /*Libreria para manejo de archivos del sistema*/
#include <random> /*Libreria para generar numeros aleatorios*/
#include <chrono> /*Libreria para llevar un timer*/
#include <iomanip> /*Libreria para ajustar la precision*/
#include <vector> /*Libreria para vectores*/
#include <omp.h> /*Librería OPENMP*/



/*Clase a incluir*/
/*Clase de los cuerpos celestiales*/
#include "object.cpp"

/*Constantes*/
const double GRAVITY = 6.674*pow(10,-5); //Constante de gravitación
const double T = 0.1; //Intervalo de tiempo
const double DMIN = 5.0; //Distancia mínima
const double WIDHT = 200; //Anchura del espacio
const double HEIGHT = 200; //Altura del espacio
const double M = 1000; //Media para la distribución normal
const double SDM = 50; //Desviación estándar para la distribución normal


using namespace std;
using namespace std::chrono; //Para medir el tiempo
using clk = chrono::high_resolution_clock;

int main(int argc, char const *argv[]) {

        /*CONTADOR DE TIEMO DE EJECUCION DEL PROGRAMA*/

        auto timer_1 = clk :: now();


        /*VARIABLES INICIALES*/
        //Comprobación de que se han introducido los argumentos pedidos
        if(argc != 5) {
                cerr <<"nasteroids-seq: Wrong arguments.\nCorrect use:\nnasteroids-seq num_asteroides num_iteraciones num_planetas semilla\n";
                return -1;
        }

        double arg1 = stof(argv[1]);
        double arg2 = stof(argv[2]);
        double arg3 = stof(argv[3]);
        double arg4 = stof(argv[4]);

        //Comprobación de que los argumentos cumplen los requisitos del enunciado
        //Deben ser enteros y positivos
        if( arg1 < 0 || arg2 < 0 || arg3 < 0 || arg4 < 0
            || arg1 - (int)arg1 != 0 || arg2 - (int)arg2 != 0 || arg3 - (int)arg3 != 0 || arg4 - (int)arg4 != 0) {
                cerr <<"nasteroids-seq: Wrong arguments.\nCorrect use:\nnasteroids-seq num_asteroides num_iteraciones num_planetas semilla\n";
                return -1;
        }

        //Casting a integer (enteros)
        int num_asteroids = (int)arg1;
        int iterations = (int)arg2;
        int num_planets = (int)arg3;
        int seed = (int)arg4;
        //Creamos el array de asteroides y planetas cuya longitud es la suma de ambos
        int num_objects = num_planets + num_asteroids;
        //object objects[num_objects];
        vector<object> objects(num_objects);


        /*Generar coordenadas aleatorias*/
        default_random_engine re{seed};
        uniform_real_distribution<double> xdist{0.0, std::nextafter(WIDHT, std :: numeric_limits<double>::max())};
        uniform_real_distribution<double> ydist{0.0, std::nextafter(HEIGHT,std :: numeric_limits<double>::max())};
        normal_distribution<double> mdist{M, SDM};

        //Generacion del  fichero de configuracion inicial
        std::ofstream file_init;
        file_init.open("init_conf.txt");
        file_init << num_asteroids << " " << iterations << " " << num_planets << " " << seed << "\n";

        /*CREA LOS ASTEROIDES Y DESPUES LOS PLANETAS*/
        for (int i = 0, j = 0; i < num_objects; i++) {

          if( i < num_asteroids) { //Colocamos asteroides.
              objects[i].position_x = xdist(re);
              objects[i].position_y = ydist(re);
              objects[i].weight = mdist(re);
              objects[i].speed_x = 0;
              objects[i].speed_y = 0;
              objects[i].force_x = 0;
              objects[i].force_y = 0;
          }
          else{ //Colocamos los planetas en los ejes
              //Cada vez que se crea un planeta, se coloca en un eje empezando por el eje x=0 y la y=aleatoria
              //Para avanzar al siguiente eje se hace con el movimiento de las agujas del reloj
              //Cuando coloca los cuatro ejes, vuelve a empezar. Para ello, utilizamos el módulo 4
              if(j%4 == 0) {
                  objects[i].position_x = 0;
                  objects[i].position_y = ydist(re);
              }
              if(j%4 == 1) {
                  objects[i].position_x = xdist(re);
                  objects[i].position_y = 0;
              }
              if(j%4 == 2) {
                  objects[i].position_x = WIDHT;
                  objects[i].position_y = ydist(re);
              }
              if(j%4 == 3) {
                  objects[i].position_x = xdist(re);
                  objects[i].position_y = HEIGHT;
              }

              objects[i].weight = mdist(re)*10;
              j++; //Avanza de eje
          }

          //Fijamos la precisión a 3 decimales e imprimimos el objeto generado
          file_init << fixed << setprecision(3) << objects[i].position_x << " " << objects[i].position_y << " "<< objects[i].weight << "\n";
        }
        //Cerramos el fichero
        file_init.close();
        
        omp_set_num_threads(4);


        //BUCLE DE LAS ITERACIONES PEDIDAS POR EL USUARIO
        for (int i = 0; i < iterations; i++) {

            #pragma omp parallel
            {


            #pragma omp for
            for (int j = 0; j < num_asteroids; j++) {
                for (int k = j + 1; k < num_objects; k++) {

                  /*CALCULO DE LA DISTANCIA*/
                  double distance = sqrt(pow(objects[j].position_x - objects[k].position_x, 2) + pow(objects[j].position_y - objects[k].position_y, 2));

                  if (distance > DMIN) {
                      double pending = (objects[j].position_y - objects[k].position_y) / (objects[j].position_x - objects[k].position_x);

                      /*Corrección de la pendiente*/
                      if (pending > 1) {
                          pending = 1;
                      }

                      if(pending < -1) {
                          pending = -1;
                      }

                      //Ángulo
                      double angles = atan(pending);

                      /*CALCULO DE FUERZAS ENTRE UN ASTEROIDE J Y UN OBJETO K*/
                      double force= GRAVITY*objects[j].weight*objects[k].weight/pow(distance, 2);
                      if (force > 100){ //Si la fuerza es mayor que 100, se truncará a 100
                        force = 100;
                      }
                      double force_x = force*cos(angles);
                      double force_y = force*sin(angles);
                      
                      //Acumuamos las fuerzas calculadas al asteroide j
                      objects[j].force_x += force_x;
                      objects[j].force_y += force_y;

                      //El objeto k puede ser asteroide o planeta. Si es asteroide, actualizamos su fuerza con signo negativo
                      if (k < num_asteroids) {
                              objects[k].force_x += -force_x;
                              objects[k].force_y += -force_y;
                      }
                  }
              }
          }
        }

          /*MOVIMIENTO DE ASTEROIDES*/
          for (int j = 0; j < num_asteroids; j++) {
              //ACELERACION
              double x= objects[j].force_x/objects[j].weight;
              double y= objects[j].force_y/objects[j].weight;

              //VELOCIDAD
              objects[j].speed_x += x * T;
              objects[j].speed_y += y * T;

              //POSICION
              objects[j].position_x += objects[j].speed_x * T;
              objects[j].position_y += objects[j].speed_y * T;

              /*REINICIA EL VALOR DE LAS FUERZAS*/
              objects[j].force_x = 0;
              objects[j].force_y = 0;
          }


          /*REBOTE DE ASTEROIDES CONTRA BORDES DEL GRID*/
          //Si el asteroide rebota con un eje modificamos su posición y la velocidad cambia de signo

         #pragma omp parallel
         {

        #pragma omp for
          for (int j = 0; j < num_asteroids; j++) {
              if( objects[j].position_x <= 0) {
                      objects[j].position_x = DMIN;
                      objects[j].speed_x = objects[j].speed_x * (-1);
              }
              if (objects[j].position_y <= 0) {
                      objects[j].position_y = DMIN;
                      objects[j].speed_y = objects[j].speed_y * (-1);
              }

              if(objects[j].position_x >= WIDHT) {
                      objects[j].position_x = WIDHT - DMIN;
                      objects[j].speed_x = objects[j].speed_x * (-1);
              }
              if(objects[j].position_y >= HEIGHT) {
                      objects[j].position_y = HEIGHT - DMIN;
                      objects[j].speed_y = objects[j].speed_y * (-1);
              }
          }
         }

          /*REBOTE ENTRE PARES DE ASTEROIDES*/
          int taken = 0;
          int last = 0;
          double first_auxSpeedX;
          double first_auxSpeedY;
          int loop1 = 0;
          int loop2 = 1;

          while (loop1 < num_asteroids) {
                  while (loop2 < num_asteroids) {

                          double distance = sqrt(pow(objects[loop1].position_x - objects[loop2].position_x, 2) + pow(objects[loop1].position_y - objects[loop2].position_y, 2));

                          //RESERVO EL PRIMER ASTEROIDE
                          if(distance <= DMIN && taken == 0) {
                                  taken = 1;
                                  first_auxSpeedX = objects[loop1].speed_x;
                                  first_auxSpeedY = objects[loop1].speed_y;
                          }

                          //CAMBIO LA VELOCIDAD DE UN ASTEROIDE
                          if (distance <= DMIN) {
                                  objects[loop1].speed_x = objects[loop2].speed_x;
                                  objects[loop1].speed_y = objects[loop2].speed_y;
                                  last = loop2;
                                  loop2 = num_asteroids;
                          }
                          loop2++;
                  }
                  loop1++;
                  loop2=loop1 + 1;
          }
          //EL ULTIMO ASTEROIDE RECIBE LA VELOCIDAD DEL PRIMER ASTEROIDE
          if(taken == 1) {
                  objects[last].speed_x = first_auxSpeedX;
                  objects[last].speed_y = first_auxSpeedY;
          }

  }//FIN DE LAS ITERACIONES

  /*RESULTADOS*/
  ofstream file_out;
  file_out.open("out.txt");

  //Se guardan las nuevas posiciones, velocidades y masa de los asteroides fijando los decimales a 3
  for(int i=0; i<num_asteroids; i++) {
      file_out << fixed << setprecision(3) << objects[i].position_x << " ";
      file_out << fixed << setprecision(3) << objects[i].position_y << " ";
      file_out << fixed << setprecision(3) << objects[i].speed_x << " ";
      file_out << fixed << setprecision(3) << objects[i].speed_y << " ";
      file_out << fixed << setprecision(3) << objects[i].weight << "\n";
  }

  //Cerramos el fichero
  file_out.close();

  auto timer_2 = clk :: now();
  //Restamos los tiempos para calcular la duración
  auto final_timer = duration_cast<microseconds>(timer_2-timer_1);
  std::cout << final_timer.count() <<  "\n";

  return 0;
  }
