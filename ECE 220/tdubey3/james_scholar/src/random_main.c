#include "input_file.h"
#include "output_file.h"
#include "ray_trace.h"
#include "surface.h"
#include "vector.h"
#include "scene.h"
#include "color.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <time.h>

const int depth = 8;

void render (scene * scene, color image_out[])
{
    vector ray;
    int x, y;
    float theta, phi;
    color pixel_color;
    resolution * res = &scene->camera.resolution;
    direction * dir = &scene->camera.direction;

    float h_angle = scene->camera.view_angle;
    float v_angle = h_angle * (float)res->height / (float)res->width;

    for (y = 0; y < res->height; y++)
    {
        phi = v_angle * ((float)y / (float)(res->height - 1) - 0.5f);
        for (x = 0; x < res->width; x++)
        {
            theta = h_angle * -((float)x / (float)(res->width - 1) - 0.5f);

            ray = vector_rotate(vector_theta_phi(theta, phi), dir->theta, dir->phi);
            pixel_color = cast_ray(scene, scene->camera.position, ray, depth, 0, NULL);

            image_out[(res->height - y - 1) * res->width + x] = pixel_color;
        }
    }
}
void print_scene(scene* cur_scene, FILE * outfile){
    /*This function should write the contents of the scene to the outfile. 
      Each object (camera, surface, background, light) should be printed to a seperate line.

      Be sure to format the output correctly, so it can be parsed using load_scene. 
      See the documentation in input_file.c for details on the output format.*/
    /*YOUR CODE HERE*/
}
int main ()
{
    /*main function for random image generation. Here, you should create a scene struct called cur_scene, and populate it with random objects as described on the wiki. You can find some examples of creating a scene in the ./tests/test_ray_trace.c program*/
    FILE * scene_file;
    FILE * image_file;
    /*for random generation*/
    time_t t;
    
    /*fill scene object here*/
    srand((unsigned) time(&t));/*initialized for you*/
    scene cur_scene = {};/*You may modify this if you wish*/
    
    /*Create scene object here, fill its values
      YOUR CODE HERE*/
    
    /*END YOUR CODE*/
    /*allocate space for the image, open output files*/
    color * image;
    resolution * res = &cur_scene.camera.resolution;
    /*output files*/
    scene_file = fopen("./random_scene.txt", "w");
    
    image_file = fopen("./random_image.ppm", "w");
    image = malloc(sizeof(color) * res->width * res->height);

    /*generate image using render function*/
    render(&cur_scene, image);
    

    /*Write scene object to file*/
    print_scene(&cur_scene,scene_file);
    fclose(scene_file);
    free(cur_scene.light_sources);
    free(cur_scene.surfaces);
    /*Print image*/
    if (save_image(image, res->width, res->height, image_file))
    {
        perror("Image save");
        return -1;
    }
    fclose(image_file);
    free(image);
    
    return 0;
}

