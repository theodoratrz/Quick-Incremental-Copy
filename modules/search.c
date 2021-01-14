#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "search.h"

int search_and_compare(DIR* org, DIR* dest, struct dirent * direntptr, struct stat buf)
{
    while(( direntptr=readdir(org) ) != NULL )
    {
        while(( direntptr=readdir(dest) ) != NULL )
        {
            
        }
        /*printf("inode %d of the  entry %s \n", (int)direntptr->d_ino , direntptr->d_name);
        printf(" ---------------------------------\n");
        printf("Time/Date: %s",ctime(&buf.st_atime));
        printf(" ---------------------------------\n");
        printf("entity name: %s \n",direntptr->d_name);
        printf("accessed: %s", ctime(&buf.st_atime)+4);
        printf("modified: %s  \n", ctime(&buf.st_mtime));*/


    }
    return 1;
}