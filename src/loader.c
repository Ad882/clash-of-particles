/**
 * @file loader.c
 *
 * @brief Program to stock initial parameters
 *        contained in a file 
 *
 * @author adrien.m
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include "particle.h"
#include "loader.h"


/* programme qui lit et stocke dans un tableau une liste de particule contenue dans un fichier*/
particle *loader(int *nb_particles, char *link_file){
    FILE *p_file = NULL;

    p_file = fopen(link_file, "r");  /* ouverture du fichier donné en paramètre */

    /* si le fichier est vide on quitte le programme */
    if (p_file == NULL) {
        fprintf(stderr, "Cannot read file %s!\n", link_file);
        exit(EXIT_FAILURE);
    }


    
    char line_result[81]; /* on initialise la variable qui va lire chaque ligne */

    fgets(line_result, 80, p_file); /* on retire la première ligne du fichier car
    elle correspond à la description du fichier */

    /* on retire et on stocke la seconde dans la variable nb_particles */
    fgets(line_result, 80, p_file);
    sscanf(line_result, "%d", nb_particles);

    particle *file_content = malloc(*nb_particles*sizeof(particle));  /* on initialise
    la variable qui va contenir les nb_particles particules du fichier */

    /* Chaque ligne du fichier est retirée et stockée dans file_content */
    for (int i = 0; i < *nb_particles ; i++){

        fgets(line_result, 80, p_file);

        sscanf(line_result, "%lf,%lf,%lf,%lf,%lf,%lf,%d", \
        &file_content[i].x, &file_content[i].y, &file_content[i].vx, \
        &file_content[i].vy, &file_content[i].mass, &file_content[i].radius, \
        &file_content[i].color);
        
    }        

    fclose(p_file);
    return file_content;
}



