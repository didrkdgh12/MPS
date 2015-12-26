# ray-trace
Basic ray tracing program designed as a class project

Supports four kinds of surface primitives:
* Sphere defined by a center and radius
* Frustum defined by two centers and two radii
* Circle defined by a center, radius, and normal vector
* Parallelogram "quad" defined by three vertices

Surfaces support three kinds of ray manipulations:
* A diffuse color for light-source based cosine shading
* A specular color for reflection
* A transmission color and refaction index for refraction

Scenes are defined by input files with a hierarchically parsed format, containing:
* Camera position, resolution, and field of view
* Lights with positions and colors
* Surface primitives with their ray manipulation characteristics

The project is strucured as follows:
*bin- after runnign the command make, this folder will be populated with the compiled code. This folder should be empty when you get the project. The project can be run as
./bin/ray_trace input_file output_file
The random scene generation is run as
./bin/random_ray_trace output_file
*ppm_compare- a small project with an image comparison utility that will be useful. Run make in the ppm_compare folder to generate the executable.
*scenes- this folder contains text files which define scenes
*src - this folder contains all the source code for this MP. This contains the files where you will write your code
*tests- contains testing files. These will be compiled when "make test" is run in the directory. Running ./test_ray_trace will run a series of tests

