/**
 * @file test-particle.c
 *
 * @brief Program to test the 
 *        functions coded in particle.c 
 *
 * @author adrien.m
 *
 */


#include "particle.h"
#include <stdio.h>
#include <math.h>


/* On teste les fonctions du fichier particle.c */
int main(){

    /* On introduit la particule 1 du sujet */
    particle particule_1;
    particule_1.x = 0.25;
    particule_1.y = 0.25;
    particule_1.vx = 0.5;
    particule_1.vy = 0.0;
    particule_1.mass = 0.5;
    particule_1.radius = 0.01;
    particule_1.color = 2;

    particle *p1 = &particule_1;


    /* On calcule les temps de collision avec les murs pour la particule 1 */
    double time_collision_wall_v = expected_time_collision_vertical_wall(particule_1);
    double time_collision_wall_h = expected_time_collision_horizontal_wall(particule_1);

    /* On  vérifie que l'actualisation des vitesses et positions fonctionne */ 
    update_particle(p1, 0.82);
    velocity_collision_vertical_wall(p1);
    velocity_collision_horizontal_wall(p1);
    printf("temps de collision avec un mur vertical: %f\n", time_collision_wall_v);
    printf("temps de collision avec un mur horizontal: %f\n", time_collision_wall_h);


    /* On réinitialise les paramètres de la particule 1 */
    particule_1.x = 0.25;
    particule_1.y = 0.25;
    particule_1.vx = 0.5;
    particule_1.vy = 0.0;
    particule_1.mass = 0.5;
    particule_1.radius = 0.01;
    particule_1.color = 2;

    /* On introduit la particule 8 du sujet */
    particle particule_8;
    particule_8.x = 0.6;
    particule_8.y = 0.8;
    particule_8.vx = 0.25;
    particule_8.vy = -0.4;
    particule_8.mass = 0.8;
    particule_8.radius = 0.005;
    particule_8.color = 4;

    particle *p8 = &particule_8;
 

    /* On calcule les temps de collision entre les deux particules */
    double time_collision_two_particles = expected_time_collision_between_particles(particule_1, particule_8);


    /* On actualise les vitesse des deux particules après leur choc */
    velocity_collision_between_particles(p1, p8);
    printf("temps de collision entre deux particules: %f\n", time_collision_two_particles);

    return 0;
}