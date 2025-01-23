/**
 * @file events.h
 *
 * @brief Program to define the
 *        events particules can encounter 
 *
 * @author adrien.m
 *
 */



#ifndef EVENTS_H
#define EVENTS_H


/* attribution d'un entier entre 0 et 3 pour les 4 types d'événements possibles */
enum type_of_event { REFRESH, COLLISION_HORIZONTAL_WALL, COLLISION_VERTICAL_WALL, COLLISION_TWO_PARTICLES};


/* definition de la structure d'un événement */
typedef struct events  events;
struct events{
    double time;
    particle *p_particle_a;
    particle *p_particle_b;
    int nb_coll_particle_a;
    int nb_coll_particle_b;

};


/* Déclaration des fonctions utilisées */
enum type_of_event code_evenement(particle *p_particle_a, particle *p_particle_b);

events create_event(double time, particle *p_particle_a, particle *p_particle_b);

int verify_event(events evenement);

#endif