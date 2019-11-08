
#include "asteroid.cpp"
#include "planet.cpp"



/*Calcula la distancia entre dos elementos*/
double dist(double asteroid_xa, double asteroid_ya, double asteroid_xb, double asteroid_yb){

        return 0;

}


/*Calculo de incidencia*/
double angle(double asteroid_xa, double asteroid_ya, double asteroid_xb, double asteroid_yb){

        return 0;

}

/*Calculo de fuerzas entre dos masas*/
void forces(double distance, double weight_a, double weight_b, double angle, double gravity_constant){

  return;

}

/*Calcula la aceleracion de un asteroide para un eje*/
double acceleration( asteroid asteroid_a){

        return 0;

}

/*Calcula la velocidad de un asteroide para un eje*/
double speed(asteroid asteroid_a, double acceleration_a){

        return 0;

}

/*Actualiza la posicion de un asteroide para un eje*/
void position(asteroid asteroid_a, double speed_a){

        return;

}

/*Movimiento de los asteroides*/
void move (){

        int example = 0;
        asteroid as;
        example++;
        /*Calcula la distancia entre dos elementos*/
              example = dist(0,0,0,0);
        /*Calculo de fuerzas*/
              /*Calculo del angulo*/
              example =  angle(0,0,0,0);
              /*Calculo de fuerzas*/
              forces(0,0,0,0,0);
        /*Movimiento de asteroides*/
              /*Calculo de la Aceleracion*/
                double x = acceleration(as);
                double y = acceleration(as);

              /*Calculo de la Velocidad*/
                x = speed(as, x);
                y = speed(as, y);

              /*Calculo de la Posicion*/
                position(as, x);
                position(as, y);

}


/*Rebote de un asteroide con el borde del grid*/
void bounce_border (asteroid asteroid_a, int width, int height){

        return;
}

/*Rebote de un asteroide con otro asteroide*/
void bounce_asteroids (asteroid asteroid_a, asteroid asteroid_b){

        return;
}
