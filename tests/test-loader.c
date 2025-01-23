/**
 * @file test-loader.c
 *
 * @brief Program to test the 
 *        functions coded in loader.c 
 *
 * @author adrien.m
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "particle.h"
#include "loader.h"


/* On teste la fonction du fichier loader.c */
int main(){
    int nb_particles;

    /* On stocke le résultat de la fonction loader dans un pointeur vers une particule */
    particle *p = loader(&nb_particles, "data/random-100.txt");

    /* On affiche les valeurs stockées dans le pointeur */
    for (int i = 0; i < nb_particles; i++){
        printf("%f %f %f %f %f %f %d\n", p[i].x, p[i].y, p[i].vx, p[i].vy, p[i].mass, p[i].radius, p[i].color);
    }
    
    /* On libère la mémoire allouée pour le stockage du contenu du fihier (ligne 30 du fichier loader.c) */
    free(p);

    return 0;
}

