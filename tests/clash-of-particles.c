/**
 * @file test-events.c
 *
 * @brief Final program: showing
 *        a clash of particles
 *
 * @author adrien.m
 *
 */
 
#include "particle.h"
#include "loader.h"
#include "events.h"
#include "simulation.h"
#include "disc.h"
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
 


/* On teste la simulation  */ 
int main(int nombre, char **link_file){ /*on donne en paramètre
                                        le fichier des positions
                                        initiales des particules */

    /* On ouvre une fenêtre de dessin */ 
    CreateWindow("Clash of particles", 900, 900);
    
    int nb_particles;
    int *nb = &nb_particles;

    /* On stocke dans une variable les positions initiales des particules */ 
    particle *list_particles = loader(nb, link_file[1]);

    /* On effectue la boucle principale, avec une situation initiale,
    un temps limite et un temps de rafraichissement */ 
    clash_of_particles(nb_particles, list_particles, 50000, 2);

    /* On libère la mémoire allouée pour le stockagedes positions des particules */
    free(list_particles);

    /* On ferme la fenêtre de dessin */
    CloseWindow();

    return 0;
}

    