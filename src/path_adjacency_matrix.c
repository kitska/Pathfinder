#include "../inc/pathfinder.h"

int** create_adjacency_matrix(char* str, int matrix_size) {
    int **adjacency_matrix = (int **)malloc(matrix_size * sizeof(int *));
    for (int i = 0; i < matrix_size; i++) {
        adjacency_matrix[i] = (int *)malloc(matrix_size * sizeof(int));
        for (int j = 0; j < matrix_size; j++) {
            adjacency_matrix[i][j] = INF;
        }
    }

    char cities[100][100];
    int cityCount = 0;

    char *line = mx_strtok((char *)str, "\n");
    while ((line = mx_strtok(NULL, "\n")) != NULL) {
        if (line[0] == '\0') {
            continue; 
        }

        char city1[100];
        char city2[100];
        int distance;

        int result = mx_sscanf(line, "%s-%s,%d", city1, city2, &distance);

        if (result != 3) {
            continue;
        }

        int city1Index = -1;
        for (int i = 0; i < cityCount; i++) {
            if (mx_strcmp(cities[i], city1) == 0) {
                city1Index = i;
                break;
            }
        }

        if (city1Index == -1) {
            mx_strcpy(cities[cityCount], city1);
            city1Index = cityCount;
            cityCount++;
        }

        int city2Index = -1;
        for (int i = 0; i < cityCount; i++) {
            if (mx_strcmp(cities[i], city2) == 0) {
                city2Index = i;
                break;
            }
        }

        if (city2Index == -1) {
            mx_strcpy(cities[cityCount], city2);
            city2Index = cityCount;
            cityCount++;
        }

        adjacency_matrix[city1Index][city2Index] = distance;
        adjacency_matrix[city2Index][city1Index] = distance;
    }
    return adjacency_matrix;
}





