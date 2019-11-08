
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

/*Clases a incluir*/
#include "asteroid.cpp"
#include "planet.cpp"
#include "functions.cpp"

/*Constantes*/
#define GRAVITY 6.674e - 5;
#define T 0.1;
#define DMIN 5.0;
#define WIDHT 200;
#define HEIGHT 200;
#define M 1000;
#define SDM 50;


/*DUDAS*/
/*UNIFICAMOS ASTEROID Y PLANET ???*/
/*DAR EL ATRIBUTO DE FUERZAS A ASTEROIDS ???, sería una variable que se actualizaria cada iteracion*/


using namespace std;

int main(int argc, char const *argv[]) {

        /*Variables que son generadas aleatoriamente*/
        int num_planets;
        int num_asteroids;
        int seed;
        int iterations;

        /*Objetos del grid*/
        asteroid asteroids[num_asteroids];
        planet planets[num_planets];


        return 0;
}
