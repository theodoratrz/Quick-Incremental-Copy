#include "functions.h"
#include "is_directory.h"

int main(int argc, char* argv[])
{
    int verbose = 0, lnk = 0, del = 0, dest;
 
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
    
    
    int flag = copy_directory( argv[argc-1], argv[argc-2]);
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
    
    return 0;
}