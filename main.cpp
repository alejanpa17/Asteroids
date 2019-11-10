
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
#include <stdlib.h> /*Libreria para manejo de archivos del sistema*/
#include <random> /*Libreria para generar numeros aleatorios*/


/*Clases a incluir*/
#include "object.cpp"
#include "functions.cpp"




/*DUDAS*/
/*UNIFICAMOS ASTEROID Y PLANET ???*/
/*DAR EL ATRIBUTO DE FUERZAS A ASTEROIDS ???, sería una variable que se actualizaria cada iteracion*/


using namespace std;

int main(int argc, char const *argv[]) { /*ALEJAN*/

        /*Variables iniciales*/
        //HAY QUE CAMBIAR ESTO PARA LEER LO QUE SE INTRODUCE EN LA CMD
        int num_planets = 1;
        int num_asteroids = 2;
        int num_objects = num_planets + num_asteroids;
        int seed = 100;
        int iterations = 2;
        object objects[num_asteroids+num_planets];

        //SACAR A FUNCION ?
        /*Generar coordenadas aleatorias*/
        default_random_engine re{seed};
        uniform_real_distribution<double> xdist{0.0, std::nextafter(WIDHT, std :: numeric_limits<double>::max())};
        uniform_real_distribution<double> ydist{0.0, std::nextafter(HEIGHT,std :: numeric_limits<double>::max())};
        normal_distribution<double> mdist{M, SDM};


        //SACAR A FUNCION
        /*CREA LOS ASTEROIDES Y DESPUES LOS PLANETAS*/
        for (int i = 0; i < num_objects; i++) {

                if( i < num_asteroids) {
                        objects[i].position_x = xdist(re);
                        objects[i].position_y = ydist(re);
                        objects[i].weight = mdist(re);
                }
                else{ //LA POSICION DE LOS PLANETAS COMO SE DECIDEN???
                        objects[i].position_x = 0;
                        objects[i].position_y = 0;
                        objects[i].weight = mdist(re)*10;
                }

                //METEMOS ESTO EN EL IF DE num_asteroids ??
                objects[i].speed_x = 0;
                objects[i].speed_y = 0;
                objects[i].force_x = 0;
                objects[i].force_y = 0;

        }

        //BUCLE DE LAS ITERACIONES PEDIDAS POR EL USUARIO
        for (int i = 0; i < iterations; i++) {


                /*CALCULO DE FUERZAS*/
                //Calcula las fuerzas de un asterio
                //AHORRAR ITERACIONES AL BUCLE CON EL ANGULO COMPLEMENTARIO???
                for (int j = 0; j < num_asteroids; j++) {
                        for (int k = 0; k < num_objects; k++) {
                                if(j != k) { //Evita que compares un asteroide con sigo mismo
                                        double distance = dist(objects[j], objects[k]);
                                        double angles = angle(objects[j], objects[k]);
                                        forces(distance,objects[j], objects[k], angles, GRAVITY);
                                }
                        }
                }


                /*MOVIMIENTO DE ASTEROIDES*/
                for (int j = 0; j < num_asteroids; j++) {

                        double x = acceleration(objects[j].weight, objects[j].force_x);
                        double y = acceleration(objects[j].weight, objects[j].force_y);
                        speed(objects[j], x, y);
                        position(objects[j], T);
                }


                /*REBOTE DE ASTEROIDES CONTRA BORDES DEL GRID*/
                for (int j = 0; j < num_asteroids; j++) {

                        bounce_border(objects[j], WIDHT, HEIGHT, DMIN);
                }


                /*REBOTE ENTRE PARES DE ASTEROIDES*/
                /*FALTA VER QUE PASA SI REBOTAN MAS DE 2*/
                for (int j = 0; j < num_asteroids; j++) {
                        for (int k = j + 1; k < num_asteroids; k++) {

                                bounce_asteroids(objects[j], objects[k]);
                        }
                }


                /*Se deben reiniciar las fuerzas porque son diferentes entre cada iteracion,
                 por ej cambian drásticamente si dos asteroides chocan*/
                for (int j = 0; j < num_asteroids; j++) {
                        objects[j].force_x = 0;
                        objects[j].force_y = 0;

                }

        }


        return 0;
}
