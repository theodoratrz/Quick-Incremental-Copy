#include "functions.h"
#include "is_directory.h"

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

    int flag = copy_directory();
    if(flag == -1)
    {
        printf("error copying files\n");
    }
    else if(flag == 0)
    {
        printf("Directories are the same, no need for copying\n");
    }
    else
    {
        printf("Copied Succesfully\n");
    }
    
    closedir(origin);
    closedir(destination);

    return 0;
}