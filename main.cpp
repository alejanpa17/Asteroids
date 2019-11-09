
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

        /*Variables que son generadas aleatoriamente*/
        int num_planets;
        int num_asteroids;
        int seed;
        int iterations;

        /*Objetos del grid*/
        default_random_engine re{seed};
        uniform_real_distribution<double> xdist{0.0, std::nextafter(WIDHT, std :: numeric_limits<double>::max())};
        uniform_real_distribution<double> ydist{0.0, std::nextafter(HEIGHT,std :: numeric_limits<double>::max())};
        normal_distribution<double> mdist{M, SDM};


        return 0;
}
