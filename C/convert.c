#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N_ITER 10 // number of simulation iterations
#define DT 0.01f // time step
#define SOFTENING 1e-9f // to avoid zero divisors

/*
 * Each body holds coordinate positions (i.e., x, y, and z) and
 * velocities (i.e., vx, vy, and vz).
 */
typedef struct { float x, y, z, vx, vy, vz; } Body;

/*
 * Compute the gravitational impact among all pairs of bodies in 
 * the system.
 */
void body_force(Body *p, float dt, int n) {
  for (int i = 0; i < n; ++i) {
    float fx = 0.0f; 
    float fy = 0.0f; 
    float fz = 0.0f;

    for (int j = 0; j < n; j++) {
      float dx = p[j].x - p[i].x;
      float dy = p[j].y - p[i].y;
      float dz = p[j].z - p[i].z;
      float sqrd_dist = dx*dx + dy*dy + dz*dz + SOFTENING;
      float inv_dist = 1 / sqrt(sqrd_dist);
      float inv_dist3 = inv_dist * inv_dist * inv_dist;

      fx += dx * inv_dist3; 
      fy += dy * inv_dist3; 
      fz += dz * inv_dist3;
    }

    p[i].vx += dt*fx; 
    p[i].vy += dt*fy; 
    p[i].vz += dt*fz;
  }
}

/*
 * Display command usage instructions.
 */
void usage(char **argv) {
  printf("usage: %s [NUM_BODIES] [IN_DATASET] [OUT_DATASET]\n\n", *argv);
  exit(EXIT_FAILURE);
}

/*
 * Read a binary dataset with initilized bodies.
 */
void read_dataset(const int nbodies, const char *filepath, Body *bodies) {
  FILE *file = fopen(filepath, "r");

  if(file == NULL) {
    printf("\nError opening file: %s\n", filepath);
    exit(EXIT_FAILURE);
  }

  int b = fread(bodies, nbodies * sizeof(Body), 1, file);
  if (b != 1) {
    printf("\nError reading from file: %s\n", filepath);
    exit(EXIT_FAILURE);
  }

  fclose(file);
}

/*
 * Write simulation results into a binary dataset.
 */
void write_dataset(int nbodies, const char *filepath, Body *bodies) {
  FILE *file = fopen(filepath, "w");

  if(file == NULL) {
    printf("\nError opening file: %s\n", filepath);
    exit(EXIT_FAILURE);
  }

  fprintf(stderr,"%f %f\n", bodies[0].x, bodies[0].vz);
  fwrite(&nbodies, sizeof(nbodies), 1, file);
  int b = fwrite(bodies, nbodies * sizeof(Body), 1, file);
  if (b != 1) {
    printf("\nError writing to file: %s\n", filepath);
    exit(EXIT_FAILURE);
  }

  fclose(file);
}

int main(int argc,char **argv) {
  int nbodies;
  char *in_path;
  char *out_path;

  if (argc < 4) {
    usage(argv);
  }

  nbodies = atoi(argv[1]);
  in_path = argv[2];
  out_path = argv[3];

  Body *bodies = (Body *)malloc(nbodies * sizeof(Body));
  read_dataset(nbodies, in_path, bodies);

  write_dataset(nbodies, out_path, bodies);

  printf("%.0f Billion Interactions simulated per iteration\n",
    ((double) nbodies) * nbodies);
  
  exit(EXIT_SUCCESS);
}
