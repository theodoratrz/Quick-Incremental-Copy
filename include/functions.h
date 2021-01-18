#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <sys/types.h>
#include "is_directory.h"

int search_inode();

int copy_files();

int copy_directory(char* dest, char* source);
