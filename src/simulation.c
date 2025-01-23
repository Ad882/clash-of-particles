/**
 * @file simulation.c
 *
 * @brief Program that define the main
 *        loop of the program clash-of-particle 
 *
 * @author adrien.m
 *
 */


#include "particle.h"
#include "loader.h"
#include "disc.h"
#include "events.h"
#include "simulation.h"
#include "stddef.h"
#include <math.h>
#include <stdio.h>


/*programme qui permet de dessiner les particules grâce à SDL */
void draw_particles(int nb, particle cloud[nb]){

    EmptySpace();
    for (int i = 0; i < nb; i++)
        DrawDISC(cloud[i].x *900, cloud[i].y *900, cloud[i].radius *900, cloud[i].color);
    UpdateScreen();
}

/* programme qui retourne le minimum de deux nombres réels */
double min(double a, double b){
    if (a < b){
        return a;
    } else {
        return b;
    }
}

 
/* programme qui correspond à la boucle principale du programme clash-of-particles */
 void clash_of_particles(int nb_particles, particle list_particles[nb_particles], double time_limit, double refresh_time){

    /* initialisation des variables */
    double time = 0;
    double time_next_draw = refresh_time;
    events next_event;


    /* Première boucle: le programme s'execute jusqu'à une certaine limite temporelle */
    while(time < time_limit){

        draw_particles(nb_particles, list_particles); /* A chaque actualisation 
                                                        (événement), on dessine la liste 
                                                        des nouvelles particles */
        
        /* Deuxième boucle: on détermine "l'événement limintant", i.e l'événement qui va arriver
        en premier et qu'il faudra traiter en premier */
        while (time < time_next_draw){
            /* initialisation de "l'événement limitant" */
            next_event.p_particle_a = NULL;
            next_event.p_particle_b = NULL;
            next_event.time = time_next_draw - time;

 
            /* On parcourt la liste des particules pour savoir quel est événement est le plus
            suceptible d'arriver en premier */ 
            for (int i = 0; i < nb_particles; i++){

                /* On calcule le temps de collision attendu entre les murs et la particule i */
                double time_wall_h = expected_time_collision_horizontal_wall(list_particles[i]);
                double time_wall_v = expected_time_collision_vertical_wall(list_particles[i]);

                /* Si le temps de collision avec un mur horizontal est plus petit que le temps
                d'arrivée du prochain événement, alors on actualise le prochain événement, qui
                devient alors une collision avec un mur horizontal */
                if (time_wall_h < next_event.time){

                    /* On actualise l'événement selon la convention choisie dans le sujet i.e,
                    la particule b nulle et la particule a corespondant à la particule qui subit
                    la collision */
                    next_event.p_particle_a = &list_particles[i];
                    next_event.p_particle_b = NULL;
                    next_event.time = time_wall_h;
                }

                /* Si le temps de collision avec un mur vertical est plus petit que le temps
                d'arrivée du prochain événement, alors on actualise le prochain événement, qui
                devient alors une collision avec un mur vertical */
                if (time_wall_v < next_event.time){
                    
                    /* On actualise l'événement selon la convention choisie dans le sujet i.e,
                    la particule a nulle et la particule b corespondant à la particule qui subit
                    la collision */
                    next_event.p_particle_a = NULL;
                    next_event.p_particle_b = &list_particles[i];
                    next_event.time = time_wall_v;
                }

                /* on teste maintenant si la particule i peut rentrer en collision avec une autre particule j
                avant tout autre événement */
                for (int j = i + 1; j < nb_particles; j++){
                     
                    /* Si le temps de collision entre deux particules est plus petit que le temps
                    d'arrivée du prochain événement, alors on actualise le prochain événement, qui
                    devient alors une collision entre deux particules */
                    double time_particles = expected_time_collision_between_particles(list_particles[i], list_particles[j]);
                    if (time_particles < next_event.time){
                        next_event.time = time_particles;
                        next_event.p_particle_a = &list_particles[i];
                        next_event.p_particle_b = &list_particles[j];
                    }    
                }
            }



            /* Maintenant que l'on a déterminé l'événement limitant, on a le plus petit temps possible
            avant le prochain événement. On peut donc actualiser la position de toutes les particules
            au temps next_event.time */
            for (int i = 0; i < nb_particles; i++){
                update_particle(&list_particles[i], next_event.time);
            }


            /* Ensuite on détermine le type de l'événement, on actualise la vitesse de la ou des
            particules impliquées dans l'événement */
            int type_event = code_evenement(next_event.p_particle_a, next_event.p_particle_b);
            if (type_event == 1){
                velocity_collision_horizontal_wall(next_event.p_particle_a);
            }
            if (type_event == 2){
                velocity_collision_vertical_wall(next_event.p_particle_b);
            }
            if (type_event == 3){
                velocity_collision_between_particles(next_event.p_particle_a, next_event.p_particle_b);
            }

            /* On actualise le temps qui s'est écoulé */
            time = time + next_event.time;
        }

        /* On actualise le temps du prochain refresh s'il n'y a pas d'événement */
        time_next_draw = time + refresh_time;
    }
}

