#include "is_directory.h"

int is_directory(char* name)
{
    struct stat buf;
    stat(name, &buf);
    if ((buf.st_mode & S_IFMT) == S_IFDIR )
    {
        return 1;
    }
    return 0;
}

int is_file(char* name)
{
    struct stat buf;
    stat(name, &buf);
    if ((buf.st_mode & S_IFMT) == S_IFREG )
    {
        return 1;
    }
    return 0;
}