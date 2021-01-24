#include "files.h"

struct statistics
{
    int hours;
    int mins;
    int secs;
    int sum;
    int entities;
    int flag;
};

struct statistics copy_directory(char* dest, char* source, int lnk, int del);

int compare_directories(DIR* , DIR*);

int create_directory(char*);

int remove_directory(char*);

int is_directory(char*);