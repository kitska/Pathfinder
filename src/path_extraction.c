#include "../inc/pathfinder.h"

int size_extraction(const char *str) {
    char **arr = mx_strsplit(str, '\n');
    int size = mx_atoi(arr[0]);
    mx_del_strarr(&arr);
    return size;
}

char **vertex_extraction(char *str, int size) {
    char *buff = mx_strnew(200);

    int i = 0;
    while (str[i] != '\n') {
        i++;
    }

    char **vertex_array = (char**) malloc((size * sizeof(char*)) + 1);
    for(int i = 0; i < size; i++) {
        vertex_array[i] = NULL;
    }


    int counter = 0;
    int buff_counter = 0;
    int flag = 0;

    for (; i < mx_strlen(str); i++) {
        if (str[i] != '-' && str[i] != ',' && str[i] != '\n' && !mx_isdigit(str[i])) {
            buff[buff_counter] = str[i];
            buff_counter++;
        }
        if (str[i] == '-') {
            for (int j = 0; j < counter; j++) {
                if (mx_strcmp(vertex_array[j], mx_strdup(buff)) == 0) {
                    flag = 1;
                    for (int j = 0; j < buff_counter; j++) {
                        buff[j] = '\0';
                    }
                    buff_counter = 0;
                }
                
            }
            if (flag != 1) {
                vertex_array[counter] = mx_strdup(buff);
                for (int j = 0; j < buff_counter; j++) {
                    buff[j] = '\0';
                }
                buff_counter = 0;
                counter++;
            }
        }
        if (str[i] == ',') {
            for (int j = 0; j < counter; j++) {
                if (mx_strcmp(vertex_array[j], mx_strdup(buff)) == 0) {
                    flag = 1;
                    for (int j = 0; j < buff_counter; j++) {
                        buff[j] = '\0';
                    }
                    buff_counter = 0;
                }
            }
            if (flag != 1) {
                vertex_array[counter] = mx_strdup(buff);
                for (int j = 0; j < buff_counter; j++) {
                    buff[j] = '\0';
                }
                buff_counter = 0;
                counter++;
            }
        }
        flag = 0;
    }

    mx_strdel(&buff);

    return vertex_array;
}
