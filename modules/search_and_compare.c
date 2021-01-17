#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "search_and_compare.h"
#include "is_dir.h"

int search_and_compare(DIR* org, DIR* dest, struct dirent * dirent_org, struct stat buf_org, struct dirent* dirent_des, struct stat buf_des)
{
    while(( dirent_org=readdir(org) ) != NULL )
    {
        printf("######");
        /*if (is_dir(dirent_des->d_name)) 
        {
            printf("Directory %s exists.\n", dirent_des->d_name);
            continue;
        }
        else 
        {
            printf("Directory %s does not exist.\n", dirent_des->d_name);
        }*/

        printf("inode %d of the  entry %s \n", (int)dirent_org->d_ino , dirent_org->d_name);
        printf(" ---------------------------------\n");
        printf("Time/Date: %s",ctime(&buf_org.st_atime));
        printf(" ---------------------------------\n");
        printf("entity name: %s \n",dirent_org->d_name);
        printf("accessed: %s", ctime(&buf_org.st_atime)+4);
        printf("modified: %s  \n", ctime(&buf_org.st_mtime));
        printf("TYPE: %d \n", dirent_org->d_type);

    }
    while(( dirent_des=readdir(dest) ) != NULL )
    {
        /*if (is_dir(dirent_des->d_name)) 
        {
            printf("Directory %s exists.\n", dirent_des->d_name);
            continue;
        }
        else 
        {
            printf("Directory %s does not exist.\n", dirent_des->d_name);
        }*/

        printf("inode %d of the  entry %s \n", (int)dirent_des->d_ino , dirent_des->d_name);
        printf(" ---------------------------------\n");
        printf("Time/Date: %s",ctime(&buf_des.st_atime));
        printf(" ---------------------------------\n");
        printf("entity name: %s \n",dirent_des->d_name);
        printf("accessed: %s", ctime(&buf_des.st_atime)+4);
        printf("modified: %s  \n", ctime(&buf_des.st_mtime));
    }
    return 1;
}