#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
    int verbose = 0, lnk = 0, del = 0, dest;
    DIR *origin, *destination;
    struct dirent *direntptr;
    struct stat buf;

    if(argc < 3)
    {
        perror("Not enough arguments");
        return 1;
    }
    

    if(argc > 3)
    {
        for(int i = 1; i < argc; i++)
        {
            if(!(strcmp(argv[i], "-v")))
            {
                verbose = 1;
            }
            else if(!strcmp(argv[i], "-l"))
            {
                lnk = 1;
            }
            else if(!strcmp(argv[i], "-d"))
            {
                del = 1;
            }
        }
    }
    
    origin = opendir(argv[argc-2]);
    if(origin == NULL)
    {
        perror("Origin directory doesn't exist");
        return 1;
    }

    destination = opendir(argv[argc-1]);
    if(destination == NULL)
    {
        dest = mkdir(argv[argc-1], 0777);
        if(dest == -1)
        {
            perror("Directory not created");
        }
        else
        {
            printf("Directory created!\n");
        }
        
    }
    while(( direntptr=readdir(origin) ) != NULL )
    {
        printf("inode %d of the  entry %s \n", (int)direntptr->d_ino , direntptr->d_name);
        printf(" ---------------------------------\n");
        stat(direntptr->d_name, &buf);
        printf("Time/Date: %s",ctime(&buf.st_atime));
        printf(" ---------------------------------\n");
        printf("entity name: %s \n",direntptr->d_name);
        printf("accessed: %s", ctime(&buf.st_atime)+4);
        printf("modified: %s  \n", ctime(&buf.st_mtime));
    }
    closedir(origin);
    closedir(destination);

    return 0;
}