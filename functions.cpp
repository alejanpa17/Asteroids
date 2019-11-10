/*Hola estoy probando*/
/*Sigo probando*/

/*Librerias*/
#include <iostream>
#include <math.h> /*Libreria para operaciones matematicas*/
#include <stdlib.h>
#include <stdio.h>
using namespace std;

/*Clase de los cuerpos celestiales*/
#include "object.cpp"


/*Constantes*/
const double GRAVITY = 6.674*pow(10,-5);
const double T = 0.1;
const double DMIN = 5.0;
const double WIDHT = 200;
const double HEIGHT = 200;
const double M = 1000;
const double SDM = 50;
const double PI = 3.14159265;


/*COMENTARIOS: si vais a cambiar los atributos que recibe la funcion decidmelo porque
   lo necesito saber para el MAIN
   Ali: he añadido el atributo time a la funcion speed q decias q no pusiesemos constantes
   */


/*Calcula la distancia entre dos elementos*/ /*LAURA*/
double dist(object asteroid, object element){

        return 0;

}


/*Calculo de angulo de incidencia, corresponde a "Movimiento Normal" de la memoria, usar función floor...*/ /*ANDRES*/
double angle(object asteroid, object element){

    double pending = (asteroid.position_y - element.position_y) / (asteroid.position_x - element.position_x);

    if (pending > 1){
        pending = 1;
    }

    if(pending < -1){
        pending = -1;
    }

    double angle = atan(pending);

        return angle;

}

/*Calculo de fuerzas entre dos masas*/ /*ALEJAN*/
void forces(double distance, object asteroid, object element, double angle, double gravity_constant){


        asteroid.force_x = gravity_constant*asteroid.weight*element.weight*cos(angle)/pow(distance, 2);
        asteroid.force_y = gravity_constant*asteroid.weight*element.weight*sin(angle)/pow(distance, 2);
        return;

}

/*Calcula la aceleracion de un asteroide para un eje,
debe de valer para cualquier eje y sumar la force que ya tiene el asteroide mas la que calculemos*/ /*ALICIA*/
double acceleration(double weight, double force){
        double acceleration= (1/weight)*force;
        return acceleration;

}

/*Calcula la velocidad de un asteroide para un eje, debe de valer para ambos ejes a la vez*/ /*ALICIA*/
void speed(object asteroid, double acceleration_x, double acceleration_y, int time){

        double n_speed_x = asteroid.speed_x + acceleration_x* time;
        double n_speed_y = asteroid.speed_y + acceleration_y* time;
        asteroid.speed_x = n_speed_x;
        asteroid.speed_y = n_speed_y;

        return;

}

/*Actualiza la posicion de un asteroide para un eje, debe de valer para ambos ejes a la vez*/ /*ANDRES*/
void position(object asteroid, int time){

    asteroid.position_x = asteroid.position_x + asteroid.speed_x * time;
    asteroid.position_y = asteroid.position_y + asteroid.speed_y * time;



        return;

}

/*Rebote de un asteroide con el borde del grid*/ /*ANDRES*/
void bounce_border (object asteroid_a, int width, int height, int dmin){

    if( asteroid_a.position_x <= 0){
        asteroid_a.position_x = asteroid_a.position_x + dmin;
        asteroid_a.speed_x = asteroid_a.speed_x * (-1);
    }
    if (asteroid_a.position_y <= 0){
        asteroid_a.position_y = asteroid_a.position_y + dmin;
        asteroid_a.speed_y = asteroid_a.speed_y * (-1);
    }

    if(asteroid_a.position_x >= width){
        asteroid_a.position_x = asteroid_a.position_x - dmin;
        asteroid_a.speed_x = asteroid_a.speed_x * (-1);
    }
    if(asteroid_a.position_y >= height){
        asteroid_a.position_y = asteroid_a.position_y - dmin;
        asteroid_a.speed_y = asteroid_a.speed_y * (-1);
    }


        return;
}

/*Rebote de un asteroide con otro asteroide*/ /*LAURA*/
void bounce_asteroids (object asteroid_a, object asteroid_b){

        return;
}
