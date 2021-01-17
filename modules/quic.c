#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "search_and_compare.h"

int main(int argc, char* argv[])
{
    int verbose = 0, lnk = 0, del = 0, dest;
    DIR *origin, *destination;
    struct dirent *dirent_org, *dirent_des;
    struct stat buf_org, buf_des;

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
    stat(argv[argc-2], &buf_org);
    stat(argv[argc-1], &buf_des);
    
    //search_and_compare(origin, destination, dirent_org, buf_org, dirent_des, buf_des);

    if ((buf_org.st_mode & S_IFMT) == S_IFDIR )
    {
        list(argv[argc-2]);      /* directory encountered */
    }
    else 
    {
        printout(argv[argc-2]);  /* file encountered */    
    }	

    if ((buf_des.st_mode & S_IFMT) == S_IFDIR )
    {
        list(argv[argc-1]);      /* directory encountered */
    }
    else
    {
        printout(argv[argc-1]);  /* file encountered      */
    }	

    closedir(origin);
    closedir(destination);

    return 0;
}