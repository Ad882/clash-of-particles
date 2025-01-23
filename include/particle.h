/**
 * @file particle.h
 *
 * @brief Program to define functions
 *        about particles and their environment 
 *
 * @author adrien.m
 *
 */



#ifndef PARTICLE_H
#define PARTICLE_H


/* definition du vecteur position d'une particule */
typedef struct position_particle  position_particle;
struct position_particle{
    float x;
    float y;
};

/* definition du vecteur vitesse d'une particule */
typedef struct velocity_particle  velocity_particle;
struct velocity_particle{
    float vx;
    float vy;
};

/* definition de la structure d'une particule */
typedef struct particle particle;
struct particle{
    double x;
    double y;
    double vx;
    double vy;
    double mass;
    double radius;
    int color;
    int nb_collision; 
};
 

/* Déclaration des fonctions utilisées */
void update_particle(particle *p, double amount_of_time); 

double expected_time_collision_vertical_wall(particle p);

double expected_time_collision_horizontal_wall(particle p);

void velocity_collision_vertical_wall(particle *p);

void velocity_collision_horizontal_wall(particle *p);

double expected_time_collision_between_particles(particle p_1, particle p_2);

void velocity_collision_between_particles(particle *p_1, particle *p_2);

void print_particle(particle *p, int size);

#endif