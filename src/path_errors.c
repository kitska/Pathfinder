#include "../inc/pathfinder.h"

void catch_usage_error(int argc) {
    if (argc != 2) {
        mx_printerr("usage: ./pathfinder [filename]\n");
        exit(1);
    }
}

void catch_file_not_found_error(const char *filename) {
    int fd = open(filename, O_RDONLY);

    if (fd == -1) {
        mx_printerr("error: file ");
        mx_printerr(filename);
        mx_printerr(" does not exist\n"); 
        exit(1);
    }

    close(fd);
}

void catch_empty_file_error(const char *filename) {
    int fd = open(filename, O_RDONLY);

    char strfer[1];
    size_t bytes_read = read(fd, strfer, sizeof(strfer));

    if (bytes_read <= 0) {
        mx_printerr("error: file ");
        mx_printerr(filename);
        mx_printerr(" is empty\n");
        exit(1);
    }

    close(fd); 

}

void catch_invalid_first_line_error(const char *filename) {
    char *str = mx_file_to_str(filename);
    char **strarr = mx_strsplit(str, '\n');

    int strarr_size = 0;

    for (int i = 0; strarr[i]; i++) {
        strarr_size++;
    }

    for (int i = 0; i < mx_strlen(strarr[0]); i++) {
        if (!mx_isdigit(strarr[0][i])) {
            mx_printerr("error: line 1 is not valid\n");
            exit(1);
        }
    }
    if (mx_atoi(strarr[0]) <= 0) {
        mx_printerr("error: line 1 is not valid\n");
        exit(1); 
    }

    mx_strdel(&str);
    mx_del_strarr(&strarr);

}

static void check_line(char *str, int index) {
    for (int i = 0; i < mx_strlen(str); i++) {
        if (!mx_isalpha(str[i])) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(index + 1));
            mx_printerr(" is not valid\n");
            exit(1);
        }
    }
}

void catch_invalid_line_error(const char *filename) {
    char *str = mx_file_to_str(filename);
    char **strarr = mx_strsplit(str, '\n');

    for (int i = 1; strarr[i]; i++) {
        if (mx_get_char_index(strarr[i], '-') < 0 || mx_get_char_index(strarr[i], ',') < 0) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i + 1));
            mx_printerr(" is not valid\n");
            exit(1);
        }
        if (mx_count_substr(strarr[i], "-") > 1 || mx_count_substr(strarr[i], ",") > 1) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i + 1));
            mx_printerr(" is not valid\n");
            exit(1);
        }

        char **str_arr = mx_strsplit(strarr[i], '-');

        check_line(str_arr[0], i);
        
        check_line(mx_strndup(str_arr[1], mx_get_char_index(str_arr[1] ,',')), i);

        for (int j = mx_get_char_index(str_arr[1] ,',') + 1; j < mx_strlen(str_arr[1]); j++) {
            if(!mx_isdigit(str_arr[1][j])) {
                mx_printerr("error: line ");
                mx_printerr(mx_itoa(i + 1));
                mx_printerr(" is not valid\n");
                exit(1);
            }
        }

        if (mx_strcmp(str_arr[0], mx_strndup(str_arr[1], mx_get_char_index(str_arr[1] ,','))) == 0) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i + 1));
            mx_printerr(" is not valid\n");
            exit(1);
        }

        mx_strdel(&str);
        mx_del_strarr(&str_arr);
    }
}

static int size_strarr(char **strarr) {
    int size = 0;
    for (int i = 0; strarr[i]; i++) {
        size++;
    }
    return size;
}

void catch_invalid_islands_error(const char *filename) {;
    char *str = mx_file_to_str(filename);
    char **strarr = mx_strsplit(str, '\n');
    char **check_arr = vertex_extraction(str, (size_strarr(strarr) * 2));

    if (size_strarr(check_arr) != mx_atoi(strarr[0])) {
        mx_printerr("error: invalid number of islands\n");
        exit(-1);
    }

    mx_strdel(&str);
    mx_del_strarr(&strarr);
    mx_del_strarr(&check_arr);
}

void catch_duplicate_bridges_error(const char *filename) {
    char *str = mx_file_to_str(filename);
    int size = size_extraction(str);
    char **vertex_arr = vertex_extraction(str, size);
    int **test_m = (int **) malloc((size + 1) * sizeof(int *));
    for(int i = 0; i < size; i++) {
        test_m[i] = (int*)malloc(size * sizeof(int));
    }

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            test_m[i][j] = 0;
        }
    }

    char **strarr = mx_strsplit(str, '\n');
    for (int i = 1; strarr[i]; i++) {
        char *from = mx_strndup(strarr[i], mx_get_char_index(strarr[i], '-'));
        strarr[i] += mx_get_char_index(strarr[i], '-') + 1;
        
        char *to = mx_strndup(strarr[i], mx_get_char_index(strarr[i], ','));
        strarr[i] += mx_get_char_index(strarr[i], ',') + 1;
        

        if (test_m[mx_get_index(vertex_arr, from)][mx_get_index(vertex_arr, to)] == 1 && test_m[mx_get_index(vertex_arr, to)][mx_get_index(vertex_arr, from)] == 1) {
            mx_printerr("error: duplicate bridges\n");
            exit(-1);
        }

        test_m[mx_get_index(vertex_arr, from)][mx_get_index(vertex_arr, to)] = 1;
        test_m[mx_get_index(vertex_arr, to)][mx_get_index(vertex_arr, from)] = 1;
        mx_strdel(&from);
        mx_strdel(&to);
    }
    for(int i = 0; i < size; i++){
        free(test_m[i]);
    }
    free(test_m);
}

void catch_sum_of_lengths_error(const char *filename) {
    char *str = mx_file_to_str(filename);;
    long long int sum = 0;
    long long int max_length = __INT_MAX__;

    char* token = mx_strtok(str, ",");
    int first = 1;

    while(token != NULL) {
        if(first) {
            first = 0;
        } else {
            sum += mx_atoll(token);
        }

        token = mx_strtok(NULL, ",\n");
    }
    
    if (sum > max_length) {
        mx_printerr("error: sum of bridges lengths is too big");
        exit(1);
    }
}
