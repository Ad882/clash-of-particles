/**
 * @file test-events.c
 *
 * @brief Program to test the 
 *        functions coded in events.c 
 *
 * @author adrien.m
 *
 */



#include <stdio.h>
#include <stdlib.h>
#include "particle.h"
#include "events.h"
#include <string.h>

/* On teste les fonctions du fichier events.c */
int main(){



    particle particule_1;
    particule_1.x = 0.25;
    particule_1.y = 0.25;
    particule_1.vx = 0.5;
    particule_1.vy = 0.0;
    particule_1.mass = 0.5;
    particule_1.radius = 0.01;
    particule_1.color = 1;
    particule_1.nb_collision = 0; /* Nombre de collision à changer pour tester
                                    la fonction verify_event */

    particle *p1 = &particule_1;


    particle particule_2;
    particule_2.x = 0.25;
    particule_2.y = 0.25;
    particule_2.vx = -0.5;
    particule_2.vy = 0.0;
    particule_2.mass = 0.5;
    particule_2.radius = 0.01;
    particule_2.color = 2;
    particule_2.nb_collision = 1; /* Nombre de collision à changer pour tester
                                    la fonction verify_event, ici le nombre de
                                    collision pour la particule 2 ne correspond
                                    pas au nombre de collision stockée dans l'events
                                    evenement pour cette particule */

    particle *p2 = &particule_2;



    events evenement;
    evenement.p_particle_a = p1;
    evenement.p_particle_b = p2;
    evenement.nb_coll_particle_a = 0;  /* Nombre de collision à changer pour tester
                                        la fonction verify_event */
    evenement.nb_coll_particle_b = 0;  /* Nombre de collision à changer pour tester
                                        la fonction verify_event */



    int verif = verify_event(evenement);

    /* test de la fonction verify_event */
    if (verif == 0){
        char is_valid[4] = {'o', 'u', 'i', '\0'};
        printf("Evenement valide ? %s\n", is_valid);
    } else {
        char is_valid[4] = {'n', 'o', 'n', '\0'};
        printf("Evenement valide ? %s\n", is_valid);
    }

    /* test de la fonction create_event */
    events next_event = create_event(2, p1, p2);
    int verif_next_event = verify_event(next_event);
    if (verif_next_event == 0){
        char is_valid[4] = {'o', 'u', 'i', '\0'};
        printf("Evenement valide ? %s\n", is_valid);
    } else {
        char is_valid[4] = {'n', 'o', 'n', '\0'};
        printf("Evenement valide ? %s\n", is_valid);
    }

    return 0;
}

