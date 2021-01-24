#ifndef FILES_H
#define FILES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include "List.h"

#define  PERM 	0644
#define SIZE 256

int copy_files(char* , char*, int);

int compare_files(char* , char*);

int create_file(char*);

#endif