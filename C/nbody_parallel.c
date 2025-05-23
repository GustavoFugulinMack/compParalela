#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h> // Adicionando suporte OpenMP

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
 * the system using OpenMP parallelization.
 */
void body_force(Body *p, float dt, int n) {
    #pragma omp parallel
    {
        #pragma omp for schedule(guided)
        for (int i = 0; i < n; ++i) {
            float fx = 0.0f; 
            float fy = 0.0f; 
            float fz = 0.0f;

            // Calculando forças para cada corpo
            for (int j = 0; j < n; j++) {
                float dx = p[j].x - p[i].x;
                float dy = p[j].y - p[i].y;
                float dz = p[j].z - p[i].z;
                float sqrd_dist = dx*dx + dy*dy + dz*dz + SOFTENING;
                float inv_dist = 1.0f / sqrtf(sqrd_dist);
                float inv_dist3 = inv_dist * inv_dist * inv_dist;

                fx += dx * inv_dist3; 
                fy += dy * inv_dist3; 
                fz += dz * inv_dist3;
            }

            // Atualizando velocidades
            p[i].vx += dt*fx; 
            p[i].vy += dt*fy; 
            p[i].vz += dt*fz;
        }
    }
}

/*
 * Read a binary dataset with initilized bodies.
 */
Body* read_dataset(int *nbodies) {
    int b = fread(nbodies, sizeof(*nbodies), 1, stdin);
    if (b != 1) {
        fprintf(stderr,"\nError reading nbodie value\n");
        exit(EXIT_FAILURE);
    }
    Body *bodies = (Body *)malloc(*nbodies * sizeof(Body));
    b = fread(bodies, *nbodies * sizeof(Body), 1, stdin);
    if (b != 1) {
        fprintf(stderr,"\nError reading input values\n");
        exit(EXIT_FAILURE);
    }

    return bodies;
}

/*
 * Write simulation results into a binary dataset.
 */
void write_dataset(const int nbodies, Body *bodies) {
    int b = fwrite(bodies, nbodies * sizeof(Body), 1, stdout);
    if (b != 1) {
        fprintf(stderr,"\nError writing to output\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv) {
    int nbodies;
    double start_time, end_time;

    // Lendo o número de threads da linha de comando (opcional)
    if (argc > 1) {
        int num_threads = atoi(argv[1]);
        omp_set_num_threads(num_threads);
    }

    Body *bodies = read_dataset(&nbodies);

    // Iniciando medição de tempo
    start_time = omp_get_wtime();

    /*
     * At each simulation iteration, interbody forces are computed,
     * and bodies' positions are integrated.
     */
    for (int iter = 0; iter < N_ITER; iter++) {
        body_force(bodies, DT, nbodies);

        // Paralelizando atualização das posições
        #pragma omp parallel for schedule(static)
        for (int i = 0; i < nbodies; i++) {
            bodies[i].x += bodies[i].vx * DT;
            bodies[i].y += bodies[i].vy * DT;
            bodies[i].z += bodies[i].vz * DT;
        }
    }

    // Finalizando medição de tempo
    end_time = omp_get_wtime();

    write_dataset(nbodies, bodies);

    // Imprimindo estatísticas
    fprintf(stderr, "Number of bodies: %d\n", nbodies);
    fprintf(stderr, "Number of iterations: %d\n", N_ITER);
    fprintf(stderr, "Execution time: %f seconds\n", end_time - start_time);
    fprintf(stderr, "%.0f Billion Interactions per second\n",
            (((double)nbodies * nbodies * N_ITER) / (end_time - start_time)) / 1e9);

    free(bodies);
    return 0;
} 