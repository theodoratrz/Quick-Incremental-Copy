#include "functions.h"

char* search_dest_directory(char* name, struct dirent* dirent_dest)
{
    char* newname;
    while ((dirent_dest = readdir(name)) != NULL )
    {
        if (dirent_dest->d_ino == 0 ) continue;

        newname=(char *)malloc(strlen(name)+strlen(dirent_dest->d_name)+2);
  		strcpy(newname,name);
  		strcat(newname,"/");
  		strcat(newname,dirent_dest->d_name);
        if(is_directory(newname))
        {

        }
        else
        {
            
        }
        
    }
}


int copy_directory(char* dest, char* source)
{
    DIR *origin, *destination;
    struct dirent *dirent_org, *dirent_des;
    struct stat buf_org, buf_des;
    char* newname;

    origin = opendir(source);
    if(origin == NULL)
    {

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

        newname=(char *)malloc(strlen(source)+strlen(dirent_org->d_name)+2);
  		strcpy(newname,source);
  		strcat(newname,"/");
  		strcat(newname,dirent_org->d_name);
        
        
        free(newname);
    }

    closedir(origin);
    closedir(destination);
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

	while ( (nread=read(infile, buffer, BUFFSIZE) ) > 0 ){
		if ( write(outfile,buffer,nread) < nread ){
			close(infile); close(outfile); return(-3);
			}
		}
	close(infile); close(outfile);

	if (nread == -1 ) return(-4);
	else	return(0);
} 

int compare_inodes(char* dest,char* source)
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

int compare_files(char* dest,char* source)
{
    struct stat buf_org, buf_des;
    stat(dest, &buf_des);
    stat(source, &buf_org);

    if(buf_des.st_size == buf_org.st_size)
    {
        if( strcmp(ctime(&buf_des.st_mtim), ctime(&buf_org.st_mtim)) > 0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
        
    }
    
    return 1;   
}

int compare_directories(char* dest,char* source)
{
    //anadromi
}