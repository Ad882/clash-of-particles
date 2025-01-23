/**
 * @file particle.c
 *
 * @brief Program to define functions
 *        about particles and their environment 
 *
 * @author adrien.m
 *
 */


#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "particle.h"

/* programme qui actualise la position d'un particule qui ne rencontre aucun obstacle pendant
un temps amount_of time */
void update_particle(particle *p, double amount_of_time){

    p -> x = p -> x + p -> vx * amount_of_time;    /* application de la formule */
    p -> y = p -> y + p -> vy * amount_of_time;    /* application de la formule */

    /* printf("coordonnées x de la particule: %f %f\n", p -> x, p -> y);  , ligne utilisée
    lors du test-particle */

}


/* programme qui détermine le temps attendu pour une collision entre un mur vertical et une particule */
double expected_time_collision_vertical_wall(particle p){

    double x_velocity = p.vx;
    double x_position = p.x;
    double epsilon = 1E-16;
    double r = p.radius;


    if (x_velocity < epsilon){       /* les lignes 28 et 30 permettent de déterminer si
    la vitesse est nulle ou non (car elle peut être négative) */
        if (x_velocity > -epsilon){
            return INFINITY;
            } else {
                return (r - x_position)/x_velocity;    /* application de la formule 
                pour un vitesse négative */
            }
    } else {
        return (1 - x_position - r )/x_velocity;    /* application de la formule
        pour un vitesse positive */
    }    
}

/* programme qui détermine le temps attendu pour une collision entre un mur horizontal et une particule */
double expected_time_collision_horizontal_wall(particle p){

    /* même prince que pour le code précédent */ 

    double y_velocity = p.vy;
    double y_position = p.y;
    double epsilon = 1E-16;
    double r = p.radius;


    if (y_velocity < epsilon){
        if (y_velocity > -epsilon){
            return INFINITY;
            } else {
                return (r - y_position)/y_velocity;
            }
    } else {
        return (1 - y_position - r )/y_velocity;
    }    
}



/* programme qui actualise la vitesse d'une particule après une collision avec un mur vertical*/
void velocity_collision_vertical_wall(particle *p){

    particle *new_p = p;
    (new_p -> vx) = - (p -> vx);   /* la nouvelle vitesse selon x est l'opposée de la 
                                    vitesse avant la colision */

    /* printf("vitesse après collision mur vertical de la particule: %f %f\n",
     new_p -> vx, p -> vy);    , ligne utilisée lors du test-particle */
}


/* programme qui actualise la vitesse d'une particule après une collision avec un mur horizontal*/
void velocity_collision_horizontal_wall(particle *p){

    particle *new_p = p;
    (new_p -> vy) = - (p -> vy);   /* la nouvelle vitesse selon y est l'opposée de la 
                                    vitesse avant la colision */

    /* printf("vitesse après collision mur horizontal de la particule: %f %f\n", 
    p -> vx, new_p -> vy);    , ligne utilisée lors du test-particle  */
}



/* programme qui détermine le temps attendu pour une collision entre deux particules */
double expected_time_collision_between_particles(particle p_1, particle p_2){


    double epsilon = 1E-16;
    double time;

    position_particle delta_p;  /* calcul de vecteur différence de position entre
    les deux particules */
    delta_p.x = (p_2.x) - (p_1.x); 
    delta_p.y = (p_2.y) - (p_1.y);

    velocity_particle delta_v;  /* calcul de vecteur différence de vitesse entre
    les deux particules */
    delta_v.vx = (p_2.vx) - (p_1.vx);
    delta_v.vy = (p_2.vy) - (p_1.vy);

    /* calcul de produits scalaires intermédiaires */
    double delta_p_delta_p = pow(delta_p.x, 2) + pow(delta_p.y, 2);
    double delta_p_delta_v = delta_p.x * delta_v.vx + delta_p.y * delta_v.vy;
    double delta_v_delta_v = pow(delta_v.vx, 2) + pow(delta_v.vy, 2);

    double r1 = p_1.radius;
    double r2 = p_2.radius;

    /* calcul du discriminant */
    double discriminant = 4 * pow(delta_p_delta_v, 2) - 4 * delta_v_delta_v * (delta_p_delta_p - pow(r1 + r2, 2));
    time = - (2 * delta_p_delta_v + sqrt(discriminant)) / (2 * delta_v_delta_v);

    if (discriminant < epsilon){ /* Si le discriminant est nul, on renvoit INFINITY */
        return INFINITY; 
    } else {
        return fabs(time); /* dans le cas contraire on retourne le temps calculé */

    }    

}


/* programme qui actualise la vitesse de deux particules après une collision entre elles*/
void velocity_collision_between_particles(particle *p_1, particle *p_2){

    velocity_particle delta_v;/* calcul de vecteur différence de vitesse entre les deux particules */
    delta_v.vx = (p_2 -> vx) - (p_1 -> vx);
    delta_v.vy = (p_2 -> vy) - (p_1 -> vy);

    double m1 = p_1 -> mass;
    double m2 = p_2 -> mass;
 
    /* on stocke les anciennes vitesses dans des variables */
    velocity_particle old_velocity_vector_1;
    old_velocity_vector_1.vx = p_1 -> vx;
    old_velocity_vector_1.vy = p_1 -> vy;
    velocity_particle old_velocity_vector_2;
    old_velocity_vector_2.vx = p_2 -> vx;
    old_velocity_vector_2.vy = p_2 -> vy;

    double time = expected_time_collision_between_particles(*p_1, *p_2);


    /* si les particles ne se touchent pas on retourne les anciennes vitesses */
    if ( time == INFINITY ){

        /* printf("vitesses de la particule 1 %f%f\n vitesses de la particule 2 selon y: %f%f\n ", 
        old_velocity_vector_1.vx, old_velocity_vector_1.vy, old_velocity_vector_2.vx, 
        old_velocity_vector_2.vy);  , ligne utilisée lors du test-particle  */
    } else {

        /* Sinon on détermine alors les nouvelles positions */
        position_particle new_position_vector_1;
        new_position_vector_1.x = p_1 -> x + p_1 -> vx * time;
        new_position_vector_1.y = p_1 -> y + p_1 -> vy * time;
        position_particle new_position_vector_2;
        new_position_vector_2.x = p_2 -> x + p_2 -> vx * time;
        new_position_vector_2.y = p_2 -> y + p_2 -> vy * time;

        /* on calcule le delta_p */
        position_particle new_delta_p;
        new_delta_p.x = (new_position_vector_2.x) - (new_position_vector_1.x);
        new_delta_p.y = (new_position_vector_2.y) - (new_position_vector_1.y);

        /* on calcule des produits scalaires intermédiaires */
        double new_delta_p_delta_p =  pow((new_delta_p.x), 2) + pow((new_delta_p.y), 2);
        double new_delta_p_delta_v = ((new_delta_p.x)*(delta_v.vx) + (new_delta_p.y)*(delta_v.vy));

        /*on utilise les formules pour calculer les nouvelles vitesses */ 
        velocity_particle new_velocity_vector_1;
        new_velocity_vector_1.vx = old_velocity_vector_1.vx + ( (2 * m2 * new_delta_p_delta_v) / ((m1 + m2) * new_delta_p_delta_p )*new_delta_p.x) ;
        new_velocity_vector_1.vy = old_velocity_vector_1.vy + ( (2 * m2 * new_delta_p_delta_v) / ((m1 + m2) * new_delta_p_delta_p )*new_delta_p.y) ;

        velocity_particle new_velocity_vector_2; 
        new_velocity_vector_2.vx = old_velocity_vector_2.vx - ( (2 * m1 * new_delta_p_delta_v) / ((m1 + m2) * new_delta_p_delta_p )*new_delta_p.x) ;
        new_velocity_vector_2.vy = old_velocity_vector_2.vy - ( (2 * m1 * new_delta_p_delta_v) / ((m1 + m2) * new_delta_p_delta_p )*new_delta_p.y) ;


        /* on stocke les nouvelles vitesses dans les particules associées */
        p_1 -> vx = new_velocity_vector_1.vx;
        p_1 -> vy = new_velocity_vector_1.vy;

        p_2 -> vx = new_velocity_vector_2.vx;
        p_2 -> vy = new_velocity_vector_2.vy;   


        /* printf("vitesses de la particule 1: %f%f\n vitesses de la particule 2: %f%f\n ", 
        new_velocity_vector_1.vx, new_velocity_vector_1.vy, new_velocity_vector_2.vx, 
        new_velocity_vector_2.vy);    , ligne utilisée lors du test-particle  */
    
    }
}



/* programme qui affiche les différents paramètres contenus dans une particule */
void print_particle(particle *p, int size){

    for (int i = 0; i < size; i++){
        printf("Particule %d: %f %f %f %f %f %f %d\n", i, p[i].x, p[i].y, p[i].vx, p[i].vy, p[i].mass, p[i].radius, p[i].color);
    }
}


