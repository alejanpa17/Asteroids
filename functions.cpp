/*Hola estoy probando*/

/*Librerias*/
#include <math.h> /*Libreria para operaciones matematicas*/


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
double acceleration(double weight, double force){

        return 0;

}

/*Calcula la velocidad de un asteroide para un eje, debe de valer para ambos ejes a la vez*/ /*ALICIA*/
void speed(object asteroid, double acceleration_x, double acceleration_y ){

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
