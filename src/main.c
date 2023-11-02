#include "../inc/pathfinder.h"

static void catch_errors(int argc, char *argv[]) {
    catch_usage_error(argc);
    catch_file_not_found_error(argv[1]);
    catch_empty_file_error(argv[1]);
    catch_invalid_first_line_error(argv[1]);
    catch_invalid_line_error(argv[1]);
    catch_invalid_islands_error(argv[1]);
    catch_duplicate_bridges_error(argv[1]);
    catch_sum_of_lengths_error(argv[1]);
}

int main(int argc, char *argv[]) {
    catch_errors(argc, argv);

    const char* filename = argv[1];

    char *str1 = mx_file_to_str(filename);
    char *str2 = mx_file_to_str(filename);

    int matrix_size = size_extraction(str1);

    char **cities = vertex_extraction(str1, matrix_size);
    int **path = create_adjacency_matrix(str1, matrix_size);
    int **adjacency_matrix = create_adjacency_matrix(str2, matrix_size);

    algorithm(path, matrix_size);
    
    path_output(adjacency_matrix, path, matrix_size, cities);

    mx_strdel(&str1);
    mx_strdel(&str2);
    mx_del_strarr(&cities);

    for (int i = 0; i < matrix_size; i++) {
        free(path[i]);
        free(adjacency_matrix[i]);
    }

    free(path);
    free(adjacency_matrix);
    return 0;
}
