

/*Librerias*/
#include <iostream>
#include <math.h> /*Libreria para operaciones matematicas*/
#include <stdlib.h>
#include <stdio.h>
using namespace std;

/*Clase de los cuerpos celestiales*/
#include "object.cpp"


/*Constantes*/
#define GRAVITY 6.674*pow(10,-5);
#define T 0.1;
#define DMIN 5.0;
#define WIDHT 200;
#define HEIGHT 200;
#define M 1000;
#define SDM 50;
const double PI = 3.14159265;


/*COMENTARIOS: si vais a cambiar los atributos que recibe la funcion decidmelo porque
   lo necesito saber para el MAIN*/


/*Calcula la distancia entre dos elementos*/ /*LAURA*/
double dist(object asteroid, object element){

        return 0;

}


/*Calculo de angulo de incidencia, corresponde a "Movimiento Normal" de la memoria, usar función floor...*/ /*ANDRES*/
double angle(object asteroid, object element){

        return 0;

}

/*Calculo de fuerzas entre dos masas*/ /*ALEJAN*/
void forces(double distance, object asteroid, object element, double angle, double gravity_constant){

        return;

}

/*Calcula la aceleracion de un asteroide para un eje,
debe de valer para cualquier eje y sumar la force que ya tiene el asteroide mas la que calculemos*/ /*ALICIA*/
// double acceleration(double weight, double force){
//
//         return 0;
//
// }

double acceleration(object asteroid, double force, double angle){
        //la fuerza cuando se aplica con un angulo tiene componente de coseno y seno
        double sin_angle = sin(angle*PI/180);
        double cos_angle = cos(angle*PI/180);

        double sum_forces_x = asteroid.force_x + (force*cos_angle);
        double sum_forces_y = asteroid.force_y + (force*sin_angle);

        double acceleration_x = (1/asteroid.weight)*sum_forces_x;
        double acceleration_y = (1/asteroid.weight)*sum_forces_y;

        //imprimir para comprobar los valores
        cout<<"aceleration x: "<<acceleration_x<< "\n" <<"aceleration y: "<<acceleration_y<< endl;

        return 0;

}

/*Calcula la velocidad de un asteroide para un eje, debe de valer para ambos ejes a la vez*/ /*ALICIA*/
void speed(object asteroid, double acceleration_x, double acceleration_y ){
  //no se si está bien hecho, no se a que se refiere con "debe de valer para ambos ejes a la vez"
        double n_speed_x = asteroid.speed_x + acceleration_x*T;
        double n_speed_y = asteroid.speed_y + acceleration_y*T;
        asteroid.speed_x = n_speed_x;
        asteroid.speed_y = n_speed_y;

        return;

}

/*Actualiza la posicion de un asteroide para un eje, debe de valer para ambos ejes a la vez*/ /*ANDRES*/
void position(object asteroid){

        return;

}

/*Rebote de un asteroide con el borde del grid*/ /*ANDRES*/
void bounce_border (object asteroid_a, int width, int height){

        return;
}

/*Rebote de un asteroide con otro asteroide*/ /*LAURA*/
void bounce_asteroids (object asteroid_a, object asteroid_b){

        return;
}
