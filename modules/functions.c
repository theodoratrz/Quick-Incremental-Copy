#include "functions.h"


int copy_directory(char* dest, char* source)
{
    DIR *origin, *destination;
    struct dirent *dirent_org, *dirent_des;
    struct stat buf_org, buf_des;
    char* file_names[10];
    int copy = -1, source_has_dir = 0, dest_has_dir = 0;

    origin = opendir(source);
    if(origin == NULL)
    {
        perror("Opening directory");
        exit(1);
    }
    destination = opendir(dest);
    if(destination == NULL)
    {
        if(!(create_directory(dest)))
        {
            perror("Creating directory");
            exit(1);
        }
        
    }
    
    stat(source, &buf_org);
    stat(dest, &buf_des);

    int flag = 0, first = 0;
    int not_same = 0, sum = 0;
    char* name, *old;
    while( (dirent_org = readdir(origin)) )
    {
        if(!(strcmp(dirent_org->d_name, ".")))
        {
            continue;
        }
        if(!(strcmp(dirent_org->d_name, "..")))
        {
            continue;
        }

        old = malloc(strlen(source)+strlen(dirent_org->d_name)+2);
        name = malloc(strlen(dest)+strlen(dirent_org->d_name) + 2);
        strcpy(old, source);
        strcat(old, "/");
        strcat(old, dirent_org->d_name);
        
        not_same = 0;
        flag = 0;

        while( (dirent_des = readdir(destination)) ) 
        {
            copy++;
            if(first == 0)
            {
                file_names[copy] = malloc(strlen(dirent_des->d_name)+1);
                strcpy(file_names[copy] , dirent_des->d_name);
                sum++;
            }
            
            if(!(strcmp(dirent_des->d_name, ".")))
            {
                continue;
            }
            if(!(strcmp(dirent_org->d_name, "..")))
            {
                continue;
            }

            strcpy(name,dest);
            strcat(name,"/");
            strcat(name, dirent_org->d_name);

            source_has_dir = is_directory(old);
            dest_has_dir = is_directory(name);

            if( (source_has_dir) && (dest_has_dir) )
            {
                if( (copy_directory(name, old)) == -1)
                {
                    perror("copying sub-directory");
                    exit(1);
                }
            }
            else if( (is_file(name)) && (is_file(old)))
            {
                if( !(strcmp(dirent_org->d_name, dirent_des->d_name)) )
                {
                    int c = compare_files(name, old);
                    if(!c)
                    {
                        strcpy(file_names[copy], " ");
                        flag = 1;
                    }
                }
            }
            else
            {
                continue;
            }
            
        }
        if(flag == 0)
        {
            not_same = 1;
            create_file(name);
            copy_files(name, old, 256);
        }
        copy = -1;
        first = 1;
        free(old);
        free(name);
        closedir(destination);
        destination = opendir(dest);
    }

    
    closedir(origin);
    closedir(destination);

    for(int i = 0; i < sum; i++)
    {
        if( !(strcmp(file_names[i], ".")))
        {
            continue;
        }
        else if( !(strcmp(file_names[i], "..")))
        {
            continue;
        }
        else if( !(strcmp(file_names[i], " ")))
        {
            continue;
        }
        else
        {
            name = malloc(strlen(dest)+strlen(file_names[i]) + 2);
            strcpy(name, dest);
            strcat(name, "/");
            strcat(name, file_names[i]);
            remove(name);
            free(name);
        }
        
    }
    for(int i = 0; i < sum; i++)
    {
        free(file_names[i]);
    }

    if(not_same)
    {
        return 1;
    }
    return 0;
}

int create_file(char* name)
{
    int fd;
	
	if ( (fd=open(name, O_CREAT|O_RDWR, PERM)) == -1)
    {
		return -1;
	}
	
	return 0; 
}

int create_directory(char* name)
{
    int dp = mkdir(name, 0777);
    if(dp == -1)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int copy_files(char* dest, char* source, int BUFFSIZE)
{
    int infile, outfile;
	ssize_t nread;
	char buffer[BUFFSIZE];
	
	if ( (infile=open(source,O_RDONLY)) == -1 )
		return(-1);

	if ( (outfile=open(dest, O_WRONLY|O_CREAT|O_TRUNC, PERM)) == -1){
		close(infile);
		return(-2);
		}

	while ( (nread=read(infile, buffer, BUFFSIZE) ) > 0 )
    {
		if ( write(outfile,buffer,nread) < nread )
        {
			close(infile); 
            close(outfile); 
            return(-3);
		}
	}
	close(infile); 
    close(outfile);

	if (nread == -1 ) 
        return(-4);
	else	
        return(0);
} 

/*int compare_inodes(char* dest,char* source)
{
    if(is_directory(dest) && is_directory(source))
    {
        compare_directories(dest, source);
    }
    else if(is_file(dest) && is_file(source))
    {
        if(compare_files(dest, source))
        {
            copy_files(dest, source, SIZE);
        }
        else
        {
            return 0;   // same files , no copy
        }
        
    }
    else
    {
        return 1;       // dir and file
    }
    
}
*/
int compare_files(char* dest,char* source)
{
    struct stat buf_org, buf_des;
    stat(dest, &buf_des);
    stat(source, &buf_org);

    if( (buf_des.st_size) == (buf_org.st_size) )
    {
        printf("dest modified   : %s", ctime(&buf_des.st_mtime));
        printf("source modified   : %s", ctime(&buf_org.st_mtime));
        if( (difftime(buf_des.st_mtime , buf_org.st_mtime)) > 0.0)   // source time 
        {
            return 0;
        }

        return 1;
    }
    
    return 1;   
}

/*int compare_directories(DIR* destination,DIR* origin)
{
    struct dirent* dirent_org, *dirent_dest;
    while(dirent_org = readdir(origin))
    {
        while(dirent_dest = readdir(destination))
        {
        }
    }
}*/

/*void RecDir(char *path, int flag) {
    DIR *dp = opendir(path);
    if(!dp) {
        perror(path);
        return;
    }
    struct dirent *ep;
    char newdir[512];
    //printf(BLUE "\n%s :\n" WHITE, path);
    while((ep = readdir(dp)))
        if(strncmp(ep->d_name, ".", 1))
            //printf(GREEN "\t%s\n" WHITE, ep->d_name);
    closedir(dp);
    dp = opendir(path);
    while((ep = readdir(dp))) if(strncmp(ep->d_name, ".", 1)) {
        if(flag && ep->d_type == 4) {
            sprintf(newdir, "%s/%s", path, ep->d_name);
            RecDir(newdir, 1);
        }
    }
    closedir(dp);
}*/