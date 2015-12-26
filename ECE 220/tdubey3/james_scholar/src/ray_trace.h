#pragma once

#include "scene.h"

/*Linked List node for tracking path of rays*/
typedef struct ray_node{
	int cur_depth;
	vector origin;
	vector ray;
	struct ray_node* next;
}raynode;

color cast_ray (scene * scene, vector origin, vector ray, int depth, int debug, raynode* list_pointer);
