/**
 * @file events.c
 *
 * @brief Program to define the
 *        events particules can encounter 
 *
 * @author adrien.m
 *
 */



#include "particle.h"
#include "events.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>


/* programme qui retourne un int correspondant à un événement */ 
enum type_of_event code_evenement(particle *p_particle_a, particle *p_particle_b){

    if (p_particle_a == NULL){
        if (p_particle_b == NULL){
            return REFRESH; /* par convention, on refresh, le programme renvoit 0 */
        } else {
            return COLLISION_VERTICAL_WALL; /* par convention, c'est une collision avec
            un mur vertical, le programme renvoit 1 */
        }
    } else {
        if (p_particle_b == NULL){
            return COLLISION_HORIZONTAL_WALL; /* par convention, c'est une collision avec
            un mur horizontal, le programme renvoit 2 */
        } else {
            return COLLISION_TWO_PARTICLES;  /* par convention, c'est une collision entre
            les deux particules, le programme renvoit 3 */
        }
    }
}

/* programme qui crée un événement à partir de deux particules et un temps donné */ 
events create_event(double time, particle *p_particle_a, particle *p_particle_b){
    events evenement;
    evenement.time = time;


    /* disjonction de cas, si les particules sont nulles */
    if (p_particle_a == NULL){
        evenement.p_particle_a = NULL;
        evenement.nb_coll_particle_a = 0;
        
    } else {
        evenement.p_particle_a = p_particle_a;
        evenement.nb_coll_particle_a = p_particle_a -> nb_collision;
    }

    if (p_particle_b == NULL){
        evenement.p_particle_b = NULL;
        evenement.nb_coll_particle_b = 0;
    } else {
        evenement.p_particle_b = p_particle_b;
        evenement.nb_coll_particle_b = p_particle_b -> nb_collision;
    }

    return evenement;
}


/* programme qui vérifie que l'événement qui arrive n'a pas été précédé par un autre événement */
int verify_event(events evenement){

    particle *pa = evenement.p_particle_a ;
    particle *pb = evenement.p_particle_b ;

    /* le programme renvoit 0 si l'événement est valide et 1 sinon */

    /* on vérifie que le nombre de collision d'une particule correspond au nombre de collisions
    enregistrées dans l'événement (pour savoir si la particule a rencontré un choc entre temps) */

    if (pa == NULL){     
        if (pb ==NULL){   
            return 0;      /* disjonction de cas, si les particules sont nulles */
        } else {     
            if (pb -> nb_collision == evenement.nb_coll_particle_b){ 
            } else {
                return 1;
            } 
        }
    } else {
        if (pb ==NULL){
            if (pa -> nb_collision == evenement.nb_coll_particle_a){
            } else {
                return 1;
            }
        } else {
            if (pa -> nb_collision == evenement.nb_coll_particle_a){
            if (pb -> nb_collision == evenement.nb_coll_particle_b){
            } else {
                return 1;
        }
    } else {
        return 1;    
    }
        }
    }
    return 0;
}

