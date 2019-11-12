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
/*SE PASA POR PARAMETRO O POR REFERENCIA*/
/*UNIFICAMOS ASTEROID Y PLANET ???*/ /*Solved*/
/*DAR EL ATRIBUTO DE FUERZAS A ASTEROIDS ???, sería una variable que se actualizaria cada iteracion*/ /*Solved*/

/*FUNCIONES QUE SE PUEDEN JUNTAR*/
/*DISTANCE, ANGLE Y FORCES*/
/*ACCELERATION, SPEED Y POSITION*/

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

        /*Necesario para generar coordenadas aleatorias*/
        default_random_engine re{seed};
        uniform_real_distribution<double> xdist{0.0, std::nextafter(WIDHT, std :: numeric_limits<double>::max())};
        uniform_real_distribution<double> ydist{0.0, std::nextafter(HEIGHT,std :: numeric_limits<double>::max())};
        normal_distribution<double> mdist{M, SDM};


        /*CREA LOS ASTEROIDES Y DESPUES LOS PLANETAS*/
        for (int i = 0, j = 0; i < num_objects; i++) {

                if( i < num_asteroids) {
                        objects[i].position_x = xdist(re);
                        objects[i].position_y = ydist(re);
                        objects[i].weight = mdist(re);
                        objects[i].speed_x = 0;
                        objects[i].speed_y = 0;
                        objects[i].force_x = 0;
                        objects[i].force_y = 0;
                }
                else{ //LA POSICION DE LOS PLANETAS COMO SE DECIDEN??? /*SOLVED*/

                        objects[i].weight = mdist(re)*10;

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

                        j++;

                }
        }

        //BUCLE DE LAS ITERACIONES PEDIDAS POR EL USUARIO
        for (int i = 0; i < iterations; i++) {


                /*CALCULO DE FUERZAS*/
                //Calcula las fuerzas de un asteroide respecto a los demas cuerpos celestes
                //AHORRAR ITERACIONES AL BUCLE CON EL ANGULO COMPLEMENTARIO??? /*SOLVED*/
                for (int j = 0; j < num_asteroids-1; j++) {
                        for (int k = j + 1; k < num_objects; k++) {

                                double distance = dist(objects[j], objects[k]);
                                double angles = angle(objects[j], objects[k]);
                                forces(distance,objects[j], objects[k], angles, GRAVITY);

                                if (k < num_asteroids) {

                                        forces(distance, objects[k], objects[j], angles + PI, GRAVITY);
                                }

                        }
                }


                /*MOVIMIENTO DE ASTEROIDES*/
                for (int j = 0; j < num_asteroids; j++) {

                        double x = acceleration(objects[j].weight, objects[j].force_x);
                        double y = acceleration(objects[j].weight, objects[j].force_y);
                        speed(objects[j], x, y, T);
                        position(objects[j], T);
                }


                /*REBOTE DE ASTEROIDES CONTRA BORDES DEL GRID*/
                for (int j = 0; j < num_asteroids; j++) {

                        bounce_border(objects[j], WIDHT, HEIGHT, DMIN);
                }


                /*REBOTE ENTRE PARES DE ASTEROIDES*/
                /*FALTA VER QUE PASA SI REBOTAN MAS DE 2*/
                /*for (int j = 0; j < num_asteroids-1; j++) {
                        for (int k = j + 1; k < num_asteroids; k++) {
                        //preguntar por la distancia
                                bounce_asteroids(objects[j], objects[k]);
                        }
                }*/


                /*Se deben reiniciar las fuerzas porque son diferentes entre cada iteracion,
                   por ej cambian drásticamente si dos asteroides chocan*/

                /*CREO QUE NOS PODRIAMOS AHORRAR ITERACIONES METIENDO ESTO EN ALGUN FOR DE ANTES*/
                for (int j = 0; j < num_asteroids; j++) {
                        objects[j].force_x = 0;
                        objects[j].force_y = 0;
                        std::cout << "Asteroid: "<< j << " Pos x: " << objects[j].position_x << " Pos y:" << objects[j].position_y ;
                }

        }


        return 0;
}
