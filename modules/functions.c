#include "functions.h"

int search_inode()
{

}

int copy_files()
{

}

int copy_directory(char* dest, char* source)
{
    DIR *origin, *destination;
    struct dirent *dirent_org, *dirent_des;
    struct stat buf_org, buf_des;

    origin = opendir(source);
    if(origin == NULL)
    {
        perror("Origin directory doesn't exist");
        return -1;
    }

    destination = opendir(dest);
    if(destination == NULL)
    {
        dest = mkdir(dest, 0777);
        if(dest == -1)
        {
            perror("Directory not created");
            return -1;
        }
        else
        {
            printf("Directory created!\n");
        }
        
    }
    stat(source, &buf_org);
    stat(dest, &buf_des);

    while ((dirent_org = readdir(origin)) != NULL )
    {
        if (dirent_org->d_ino == 0 ) continue;
        
    }

    closedir(origin);
    closedir(destination);
}