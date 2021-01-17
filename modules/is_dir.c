#include "is_dir.h"

int is_dir(char *file)
{
    struct stat file_stat;

    // if an error occurs, we return 0 for false
    if (stat(file, &file_stat) < 0) {
        return 0;
    }

    // otherwise we return whatever the S_ISDIR returns
    return S_ISDIR(file_stat.st_mode);
}
