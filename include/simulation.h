/**
 * @file simulation.h
 *
 * @brief Program that define the main
 *        loop of the program clash-of-particle 
 *
 * @author adrien.m
 *
 */


#ifndef SIMULATION_H
#define SIMULATION_H


/* Déclaration des fonctions utilisées */
void draw_particles(int nb, particle cloud[nb]);

double min(double a, double b);

void clash_of_particles(int nb_particles, particle list_particles[nb_particles], double time_limit, double refresh_time);

#endif