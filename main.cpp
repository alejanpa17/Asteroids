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



/*Clases a incluir*/
//#include "object.cpp"
#include "functions.cpp"




/*DUDAS*/
/*UNIFICAMOS ASTEROID Y PLANET ???*/ /*Solved*/
/*DAR EL ATRIBUTO DE FUERZAS A ASTEROIDS ???, sería una variable que se actualizaria cada iteracion*/ /*Solved*/

/*FUNCIONES QUE SE PUEDEN JUNTAR*/
/*DISTANCE, ANGLE Y FORCES*/
/*ACCELERATION, SPEED Y POSITION*/

using namespace std;
using namespace std::chrono;


int main(int argc, char const *argv[]) { /*ALEJAN*/

        /*CONTADOR DE TIEMO DE EJECUCION DEL PROGRAMA*/
        using clk = chrono::high_resolution_clock;
        auto timer_1 = clk :: now();


        /*VARIABLES INICIALES*/
        //Comprobacion de que se han introducido los argumentos pedidos
        if(argc != 5) {
                cerr <<"nasteroids-seq: Wrong arguments.\nCorrect use:\nnasteroids-seq num_asteroides num_iteraciones num_planetas semilla\n";
                return -1;
        }

        double arg1 = stof(argv[1]);
        double arg2 = stof(argv[2]);
        double arg3 = stof(argv[3]);
        double arg4 = stof(argv[4]);
        //cout << arg1 << " " << (int)arg1 << " " << arg1 - (int)arg1 << endl;

        //Comprobacion los argumentos cumplen los requisitos del enunciado
        if( arg1 < 0 || arg2 < 0 || arg3 < 0 || arg4 < 0
            || arg1 - (int)arg1 != 0 || arg2 - (int)arg2 != 0 || arg3 - (int)arg3 != 0 || arg4 - (int)arg4 != 0) {
                cerr <<"nasteroids-seq: Wrong arguments.\nCorrect use:\nnasteroids-seq num_asteroides num_iteraciones num_planetas semilla\n";
                return -1;
        }

        int num_asteroids = (int)arg1;
        int iterations = (int)arg2;
        int num_planets = (int)arg3;
        int seed = (int)arg4;
        int num_objects = num_planets + num_asteroids;
        object objects[num_objects];

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
                file_init << fixed << setprecision(3) << objects[i].position_x << " " << objects[i].position_y << " "<< objects[i].weight << "\n";
        }

        file_init.close();


        //BUCLE DE LAS ITERACIONES PEDIDAS POR EL USUARIO
        for (int i = 0; i < iterations; i++) {


                /*CALCULO DE FUERZAS*/
                //Calcula las fuerzas de un asteroide respecto a los demas cuerpos celestes
                //AHORRAR ITERACIONES AL BUCLE CON EL ANGULO COMPLEMENTARIO??? /*SOLVED*/
                for (int j = 0; j < num_asteroids; j++) {
                        for (int k = j + 1; k < num_objects; k++) {

                                double distance = sqrt(pow(objects[j].position_x - objects[k].position_x, 2) + pow(objects[j].position_y - objects[k].position_y, 2));
                                double pending = (objects[j].position_y - objects[k].position_y) / (objects[j].position_x - objects[k].position_x);

                                /*CORRECCION DE LA PENDIENTE*/
                                if (pending > 1) {
                                        pending = 1;
                                }

                                if(pending < -1) {
                                        pending = -1;
                                }

                                double angles = atan(pending);

                                /*CORRECCION DEL ANGULO*/
                                /*if(objects[j].position_x > objects[k].position_x) {
                                        angles += PI;
                                }*/
                                objects[j].force_x += GRAVITY*objects[j].weight*objects[k].weight*cos(angles)/pow(distance, 2);
                                objects[j].force_y += GRAVITY*objects[j].weight*objects[k].weight*sin(angles)/pow(distance, 2);

                                if (k < num_asteroids) {
                                        objects[k].force_x += -objects[j].force_x;
                                        objects[k].force_y += -objects[j].force_y;
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
                for (int j = 0; j < num_asteroids; j++) {
                        /*Creo que se podria meter lo que tiene este for en el anterior*/

                        //bounce_border(objects[j], WIDHT, HEIGHT, DMIN);
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


                /*IMPRESIONES PARA PRUEBAS*//*BORRAR*/
                /*for (int j = 0; j < num_objects; j++) {

                        if (j < num_asteroids) {
                                std::cout << "Asteroid: "<< j << " Pos x: " << objects[j].position_x << " Pos y:" << objects[j].position_y << "\n";
                        }
                        else{
                                std::cout << "Planet: "<< j << " Pos x: " << objects[j].position_x << " Pos y:" << objects[j].position_y << "\n";
                        }
                   }*/

        }

        /*RESULTADOS*/
        ofstream file_out;
        file_out.open("out.txt");

        for(int i=0; i<num_asteroids; i++) {
                file_out << fixed << setprecision(3) << objects[i].position_x << " ";
                file_out << fixed << setprecision(3) << objects[i].position_y << " ";
                file_out << fixed << setprecision(3) << objects[i].speed_x << " ";
                file_out << fixed << setprecision(3) << objects[i].speed_y << " ";
                file_out << fixed << setprecision(3) << objects[i].weight << "\n";
        }

        file_out.close();

        auto timer_2 = clk :: now();
        auto final_timer = duration_cast<microseconds>(timer_2-timer_1);
        std::cout << final_timer.count() <<  "\n";

        return 0;
}
