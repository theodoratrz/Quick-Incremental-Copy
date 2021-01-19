#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "is_directory.h"
#define  PERM 		0644
#define SIZE 256

char* search_dest_directory(char* , struct dirent*);

int copy_files(char* , char*, int);

int copy_directory(char* dest, char* source);

int compare_inodes(char* , char*);

int compare_files(char* , char*);

int compare_directories(DIR* , DIR*);

int create_file(char*);

int create_directory(char*);