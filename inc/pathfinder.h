#ifndef PATHFINDER_H
#define PATHFINDER_H

#define DELIM_LINE "========================================\n"
#define INF 9999999
#define MAX_CITIES 100

#include "../libmx/inc/libmx.h"
#include <stdlib.h>

int size_extraction(const char *str);
char** vertex_extraction(char *str, int size);
int** create_adjacency_matrix(char* str, int matrix_size);
void algorithm(int **w, int size);
void path_output(int **adjacency_matrix, int **path, int size, char **cities);

void catch_usage_error(int argc);
void catch_file_not_found_error(const char *filename);
void catch_empty_file_error(const char *filename);
void catch_invalid_first_line_error(const char *filename);
void catch_invalid_line_error(const char *filename);
void catch_invalid_islands_error(const char *filename);
void catch_sum_of_lengths_error(const char *filename);
void catch_duplicate_bridges_error(const char *filename);

#endif
