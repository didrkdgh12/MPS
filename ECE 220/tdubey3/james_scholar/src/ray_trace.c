#include "ray_trace.h"
#include "surface.h"
#include "vector.h"
#include "scene.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>




/* This module implements the core recursive ray tracing algorithm used to render a scene.

   It implements the cast_ray function which takes a ray and scene parameters and determines the
   color of that ray.  The ray tracing framework (in main.c) calls cast_ray for each pixel in the image,
   producing a rendering of the scene.

   The color of a ray is determined by recursively tracing the tree of paths it takes through a
   given scene as it reflects and refracts about surfaces, up to a recursion depth limit.  Light
   contributions from each branch of the tree are added together to determine the color of the ray
   in question.  Ray cast beyond the depth limit are simply given the color of the background to
   avoid infinite recursion.

   The recursive algorithm for computing the color of a ray is as follows:

   Determine first surface hit, and determine intersection point and normal.
   If no surface is hit, the ray color is the background color.
   Otherwise, depending on the properties of that surface, do some of the following:

   Use Fresnel's equations and Snell's law to determine reflection coefficient (c_reflected),
   transmission coefficient (c_transmitted), and refracted ray.  Determine transmission subtotal
   as follows:
   Transmission subtotal = c_transmitted * specular part * refracted ray color

   Calculate reflected ray and determine reflection subtotal as follows:
   Reflection subtotal = c_reflected * specular part * reflected ray color

   Test shadow rays to determine which lights are illiminating the intersection point.  Use the cosine
   shading model to calculate diffuse coefficients (c_diffuse) for each.  Calculate the diffuse subtotal
   as follows:
   Diffuse subtotal = diffuse part * (c_diffuse_1 * light_color_1 + c_diffuse_2 * light_color_2 + ...)

   Add the calculated subtotals together to determine the color of the ray: 
   ray color = transmitted + reflected + diffuse
*/

bool get_intersection (vector origin, vector ray, surface * test_surface,
                       vector * intersection_out, vector * normal_out)
/*! Determine if the ray with the given origin and direction intersects with the given surface.
    If it does, set the insersection_out parameter (if not NULL) to indicate the location of the
    first intersection, set the normal_out parameter (if not NULL) to indicate the normal of the
    surface at the intersection point, and return true.
    If the ray never intersects the surface, return false.
*/
{
    return test_surface->class->calculate_intersection(origin, ray, test_surface->geometry,
                                                       intersection_out, normal_out);
}

float fresnel_refraction (vector ray, vector normal, float refraction_index,
                          vector * refracted_ray_out)
/*! Determine how the given ray will refract through the surface with the given normal and
    relative refraction index using Fresnel's equations.  Due to the wave nature of light,
    tracing the reflection/refraction backward is conveniently equivalent to tracing it forward.

    A reflection coefficient is returned indicating how much of traced ray's power will come
    from reflection.  This value will be between 0 (no light reflects) and 1 (all light reflects).
    The remainder of the ray's power is transmitted (refracted).  In other words:
    c_reflected + c_transmitted = 1

    If the ray does refract (i.e. the reflection coefficient is not 1) then the
    refracted_ray_out parameter will be set to indicate the direction of the refracted ray.
*/
{
    float cos_i, cos_t, cos2_t;
    float n, r_s, r_p;

    if (refraction_index == .0f)
    {
        /* No refraction index means reflection only */
        return 1.0f;
    }

    /* Determine cosine of incident ray wrt normal */
    cos_i = -dot_product(ray, normal);
    if (cos_i < 0)
    {
        /* Reverse the normal and refraction index if we're inside a surface */
        n = refraction_index;
        normal = vector_negate(normal);
        cos_i = -cos_i;
    }
    else
    {
        n = 1.0f / refraction_index;
    }

    /* Snell's law + pythagorean trigonometric identity to determine cosine of
       transmitted ray wrt normal on the other side of the surface */
    cos2_t = 1.0f - square(n) * (1.0f - square(cos_i));
    if (cos2_t < 0)
    {
        /* Imaginary square root: total internal reflection */
        return 1.0f;
    }
    cos_t = sqrtf(cos2_t);

    /* Determine refracted ray 
       http://www.cs.unc.edu/~rademach/xroads-RT/RTarticle.html#reflection */
    *refracted_ray_out = vector_add(vector_multiply(n, ray), vector_multiply(n * cos_i - cos_t, normal));

    /* Fresnel's equations for reflection coefficient
       http://en.wikipedia.org/wiki/Fresnel_equations */
    r_s = square((n * cos_i - cos_t) / (n * cos_i + cos_t));
    r_p = square((n * cos_t - cos_i) / (n * cos_t + cos_i));

    return 0.5f * (r_s + r_p);
}

vector reflect_ray (vector ray, vector surface_normal)
/*! Determine the reflection of a given ray from a surface with the given
    normal vector */
{
    float scale = -2.0f * dot_product(ray, surface_normal);
    return vector_add(ray, vector_multiply(scale, surface_normal));
}

float get_diffuse_coefficient (vector point, vector normal, light_source * source)
/*! Determine the diffuse coefficient of a given point on a surface with a given normal
    being lit by the given light source according to the cosine shading model. */
{
    float cos_theta;
    cos_theta = dot_product(normal, vector_normalize(vector_sub(source->position, point)));
    return fmax(cos_theta, .0f);
}

surface * hit_surface (vector origin, vector ray, surface surfaces[],
                       vector * intersection_out, vector * normal_out)
/*! Given a ray with given origin and direction(vector ray) and surface array as defined in scene.h,
    determine the closest surface hit.  The vector_distance function (defined in vector.h)
    will be useful here.  Also look at the get_intersection function, which will be helpful here.
    Set the output parameters intersection_out and normal_out to
    the intersection location of the closest surface and surface normal at that intersection,
    respectively.  Return a pointer to the closest surface hit.
    
    If the ray intersects none of the given surfaces, return NULL
    INPUT: vector origin, indicating the origin of the ray
    vector ray, indicating the direction of the ray
    surface surfaces[], an array containing all surfaces in the scene
    OUTPUT: vector * intersection_out, set the value at this pointer to the point of intersection
    vector * normal_out, set the value equal to the normal vector of the surface at the point of intersection
    RETURN: Returns a pointer to the closest surface or NULL if no surfaces are hit.
*/
{
    /*Your Code Here, modify return value as necessary*/
    return NULL;
}

bool is_illuminated (light_source * source, vector point, surface surfaces[])
/*! Determine if a given point in space is in the light of the given light source,
    meaning none of the given surfaces are blocking the line from the point to
    the light source. Check whether or not there is a surface intersecting the line segment
    extending from the position of source to point.
    
    When trying to find the line segment between the point, consider how vector subtraction works. You may use the vector_sub function.
    Before using get_intersection, make sure any vectors representing a direction are normalized (use the vector_normalize function). 

    When testing if a surfaces is in between the source and a point, be sure to us a strictly less than or greater (< >) than 
    comparison, as it is possible the point is exactly on one of the surfaces.

    If there is a direct path between the light and the point which is not blocked by a surface,
    return true, otherwise return false.
    INPUT: light_source* source, which points to a light source in our scene
    vector point, the point to be tested
    surface surfaces[], an array with all surfaces in the scene
    RETURN: true if there is no surface in between the point and source, false otherwise
*/
{
    /*Your Code Here, modify return value as necessary*/
    return true;
}

color get_illumination (vector point, vector ray, vector normal,
                        light_source light_sources[], surface surfaces[])
/*! Determine the diffuse illumination of the given point on a surface with the given
    normal with incident ray given for reference.  The illumination is calculated by
    summing the contributions of each light source with a direct line of sight to the
    point (no surfaces blocking, determined with is_illuminated). Each contribution is calculated  
    multiplied by the source's color times the diffuse coefficient calculated by the get_diffuse_coefficient function.

    Be sure to use the color structure and color_add and color_scale functions.
    INPUT: vector point, indicating the intersection point
    vector ray, indicating the direction of the incident ray
    vector normal, indicating the direction of the normal vector of the surfaces at the point of intersection
    light_source light_sources[], an array containing all lights in the scene
    surface surfaces[], an array containing all surfaces in the scene
*/
{
    /* First the normal needs to be inverted if we're inside a surface before calculating
       illumination.  This is done for you below */
    if (dot_product(ray, normal) > 0)
    {
        normal = vector_negate(normal);
    }
    /*Your code here, modify the return as necessary*/
    return ((color){0,0,0});
}

color cast_ray (scene * scene, vector origin, vector ray, int depth, int debug, raynode* list_pointer)
/*! Determine the color of a ray with given origin and direction by recursively tracing the path
    it takes through a given scene with recursion depth limit "depth".  Once the depth limit is
    reached (remaining depth is 0), rays are assumed to have the color of the scene background.

    The algorithm for computing the ray color is documented above in the comments and in the wiki write-up.  
    Color multiplication, scaling, and addition functions defined in color.h will be useful here.

    Debug may be 0 or 1. If debug is 1, create a new raynode and store the current depth, origin, and ray. Insert this new node
    to the list after list_pointer. If Debug is 0, do nothing with list_pointer. 

    When calling cast_ray resursively, use the same value of debug as an argument for cast_ray.
    If debug is 1, use a pointer to the newly created node as an argument for cast_ray, otherwise use list_pointer

    Raynode is defined in ray_trace.h
    
    INPUT: scene* scene, containing the current scene
    vector origin, containing the origin point for the current ray
    vector ray, containing the direction of the current ray
    int depth, which is the current recursion depth
    int debug, 0 or 1, a flag to create a node to track the rays
    raynode* list_pointer, a pointer to the current node of the linked list, for debugging
*/
{
    /*Your Code Here, modify return value as necessary*/
    return ((color){0,0,0});
}


void print_list(raynode* start)
/*  This function prints the contents of a linked list for debugging purposes.
    The start of the linked list is given by "start".
    First printf "Path Tracking in Ray Trace: \n"
    Then for each node of the list, printf  
    "Depth: d, Origin: x y z, Ray: x y z\n", replacing d with the value of depth (as an integer), and x, y, and z with the values of 
    x, y, and z of origin and ray (as floats).

    INPUT:raynode* start, pointer to the start of the linked list
*/
{
    /*Your Code Here*/
}

void free_list(raynode* start)
/*  This function frees the memory allocated to the linked list.
    Free each node of the list

    INPUT: raynode* start, a pointer to the start of the linked list.    
*/
{
    /*Your code here*/
}


