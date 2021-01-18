#include "is_directory.h"

int is_directory(struct stat buf)
{
    if ((buf.st_mode & S_IFMT) == S_IFDIR )
    {
        return 1;
    }
    return 0;
}