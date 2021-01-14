#include <dirent.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

int search_and_compare(DIR* org, DIR* dest, struct dirent*, struct stat);