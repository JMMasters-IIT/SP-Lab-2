#ifndef READFILE_H
#define READFILE_H

#include <stdio.h>

int open_file(const char *filename); //Opens specific file, returns 0 if successful, -1 if unable to open

void close_file(); //Closes whatever file is open

int read_int(int *value); //Reads int from the file and stores it. Returns 0 on success, -1 if end of the file or error

int read_string(char *str, int max_len); //Reads a string from the file (the name) into the character array. Returns 0 on success, -1 if end of the file or error

int read_float(float *value); //reads float (salary) from the file and stores it. Returns 0 on success, -1 if end of the file or error

#endif /* READFILE_H */