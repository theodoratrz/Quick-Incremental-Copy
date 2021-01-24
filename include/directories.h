#ifndef DIRECTORIES_H
#define DIRECTORIES_H

#include "files.h"

// a struct for statistics
struct statistics
{
    int sum;
    int entities;
    int flag;
};

// function that compares 2 directories and copies from source to dest
// (every file/directory that doesn't already exists)
struct statistics copy_directory(char* dest, char* source, int lnk, int del);

// function that creates a directory
int create_directory(char*);

// function that deletes a directory and all of it content, recursively
int remove_directory(char*);

// function that returns 1 if the given file is a directory
int is_directory(char*);

#endif