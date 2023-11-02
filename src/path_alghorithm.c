#include "../inc/pathfinder.h"

void algorithm(int **way, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (way[i][j] != INF) {
                for (int k = 0; k < size; k++) {
                    if ((way[i][k] > way[i][j] + way[j][k] || way[i][k] == INF) && way[j][k] != INF && (i != k)) {
                        way[i][k] = way[i][j] + way[j][k];
                    }
                }
            }
        }
    }
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if (way[i][j] == INF) {
                way[i][j] = 0;
            }
        }
    }
}
