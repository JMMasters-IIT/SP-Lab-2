#include "readfile.h"
#include <stdio.h>

// Static file pointer to manage file operations within this library
static FILE *file = NULL;

//Opens specific file, returns 0 if successful, -1 if unable to open
int open_file(const char *filename) {
    file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }
    return 0;
}

//Closes whatever file is open
void close_file() {
    if (file != NULL) {
        fclose(file);
        file = NULL;  //Set to NULL to avoid accidental reuse
    }
}

//Reads int from the file and stores it. Returns 0 on success, -1 if end of the file or error
int read_int(int *value) {
    if (file == NULL) {
        fprintf(stderr, "File is not open.\n");
        return -1;
    }
    if (fscanf(file, "%d", value) == 1) {
        return 0;
    }
    return -1;
}

//Reads a string from the file (the name) into the character array. Returns 0 on success, -1 if end of the file or error
int read_string(char *str, int max_len) {
    if (file == NULL) {
        return -1;
    }
    if (fscanf(file, "%63s", str) == 1) {
        return 0;
    }
    return -1; 
}

//reads float (salary) from the file and stores it. Returns 0 on success, -1 if end of the file or error
int read_float(float *value) {
    if (file == NULL) {
        fprintf(stderr, "File is not open.\n");
        return -1;
    }
    if (fscanf(file, "%f", value) == 1) {
        return 0;
    }
    return -1; 
}
