#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct { float x, y, z, vx, vy, vz; } Body;

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s <number_of_bodies> <output_file>\n", argv[0]);
        return 1;
    }

    int nbodies = atoi(argv[1]);
    const char *outfile = argv[2];
    
    // Inicializar gerador de números aleatórios
    srand(time(NULL));
    
    // Alocar memória para os corpos
    Body *bodies = (Body *)malloc(nbodies * sizeof(Body));
    
    // Gerar dados aleatórios para cada corpo
    for (int i = 0; i < nbodies; i++) {
        bodies[i].x = (float)rand() / RAND_MAX * 100.0f - 50.0f;  // [-50, 50]
        bodies[i].y = (float)rand() / RAND_MAX * 100.0f - 50.0f;
        bodies[i].z = (float)rand() / RAND_MAX * 100.0f - 50.0f;
        bodies[i].vx = (float)rand() / RAND_MAX * 2.0f - 1.0f;    // [-1, 1]
        bodies[i].vy = (float)rand() / RAND_MAX * 2.0f - 1.0f;
        bodies[i].vz = (float)rand() / RAND_MAX * 2.0f - 1.0f;
    }
    
    // Abrir arquivo para escrita
    FILE *file = fopen(outfile, "wb");
    if (!file) {
        printf("Erro ao abrir arquivo %s para escrita\n", outfile);
        free(bodies);
        return 1;
    }
    
    // Escrever número de corpos
    fwrite(&nbodies, sizeof(nbodies), 1, file);
    
    // Escrever dados dos corpos
    fwrite(bodies, sizeof(Body), nbodies, file);
    
    // Limpar
    fclose(file);
    free(bodies);
    
    printf("Arquivo de teste gerado com %d corpos: %s\n", nbodies, outfile);
    return 0;
} 