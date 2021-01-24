#include "directories.h"

int main(int argc, char* argv[])
{
    int hours, mins, secs;
    struct timeval  now;
	struct tm* old, *current;

	gettimeofday(&now, NULL);			
	old = localtime(&now.tv_sec);

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
    
    struct statistics f = copy_directory( argv[argc-1], argv[argc-2], lnk, del);
    if(f.flag == 0)
    {
        printf("Directories are the same, no need for copying\n");
    }
    else
    {
        printf("Copied Succesfully\n");
    }

    // print statistics
    if(verbose)
    {
        printf("Total files/directories checked: %d\n", f.sum);
        printf("Total entities copied: %d\n", f.entities);
    }
    
    gettimeofday(&now, NULL);			
	current = localtime(&now.tv_sec);

    hours = (current->tm_hour) - (old->tm_hour);
    mins = (current->tm_min) - (old->tm_min);
    secs = (current->tm_sec) - (old->tm_sec);
    printf("Total time: %02d:%02d:%02d\n", hours, mins, secs);

    return 0;
}