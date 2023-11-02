#include "../inc/pathfinder.h"

static void print_separator(void) {
    for (int i = 0; i < 40; i++) {
        mx_printchar('=');
    }
    mx_printchar('\n');
}

static void print_path_info(int *way, int way_count, char **cities, int **adjacency_matrix) {
    mx_printstr("Path: ");
    mx_printstr(cities[way[1]]);
    mx_printstr(" -> ");
    mx_printstr(cities[way[0]]);
    mx_printchar('\n');
    mx_printstr("Route: ");

    for (int i = 1; i < way_count + 1; i++) {
        mx_printstr(cities[way[i]]);
        if (i < way_count) {
            mx_printstr(" -> ");
        }
    }

    mx_printstr("\nDistance: ");
    int path_dist = 0;

    for (int i = 1; i < way_count; i++) {
        int between = adjacency_matrix[way[i]][way[i + 1]];
        mx_printint(between);
        path_dist += between;
        if (i < way_count - 1) {
            mx_printstr(" + ");
        }
    }

    if (way_count != 2) {
        mx_printstr(" = ");
        mx_printint(path_dist);
    }

    mx_printchar('\n');
}

static void find_paths_recursive(int **adjacency_matrix, int **path, int *way, int way_count, int size, char **cities) {
    int from = way[0];
    int to = way[way_count];

    for (int i = 0; i < size; i++) {
        if ((adjacency_matrix[to][i] == path[to][from] - path[i][from]) && i != way[way_count]) {
            way_count += 1;
            way[way_count] = i;
            find_paths_recursive(adjacency_matrix, path, way, way_count, size, cities);
            way_count -= 1;
        }
    }

    if (way[way_count] != from) {
        return;
    }

    print_separator();
    print_path_info(way, way_count, cities, adjacency_matrix);
    print_separator();
}

void path_output(int **adjacency_matrix, int **path, int size, char **cities) {
    int *way = (int*)malloc((size + 1) * sizeof(int));
    int way_count = 1;

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            way[1] = i;
            way[0] = j;
            find_paths_recursive(adjacency_matrix, path, way, way_count, size, cities);
        }
    }

    free(way);
}
