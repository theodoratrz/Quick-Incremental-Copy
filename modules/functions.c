#include "functions.h"

/*char* search_dest_directory(char* name, struct dirent* dirent_dest)
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
}*/


int copy_directory(char* dest, char* source)
{
    DIR *origin, *destination;
    struct dirent *dirent_org, *dirent_des;
    struct stat buf_org, buf_des;

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

    //int i = 0;
    int flag = 0;
    int not_same = 0;
    while( (dirent_org = readdir(origin)) )
    {
        printf("org name: %s\n", dirent_org->d_name);
        if(!(strcmp(dirent_org->d_name, ".")))
        {
            continue;
        }
        flag = 0;
        while( (dirent_des = readdir(destination)) ) 
        {
            if(!(strcmp(dirent_des->d_name, ".")))
            {
                continue;
            }
            int c = compare_files(dirent_des->d_name, dirent_org->d_name);
            if(c)
            {
                printf("comparison: %d flag: %d\n", c, flag);
                //continue;
            }
            else
            {
                flag = 1;
                printf("flag: %d\n", flag);
                //break;
            }
            if(flag == 0)
            {
                not_same = 1;
                char* name = malloc(strlen(dest)+strlen(dirent_org->d_name) + 2);
                //strcpy(name, dirent_org->d_name);
                //newname=(char *)malloc(strlen(name)+strlen(dir->d_name)+2);
                strcpy(name,dest);
                strcat(name,"/");
                strcat(name, dirent_org->d_name);
                printf("name: %s\n", name);
                printf("org name: %s\n", dirent_org->d_name);
                create_file(name);
                copy_files(name, dirent_org->d_name, 256);
                break;
            }
        }
    }

    closedir(origin);
    closedir(destination);
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
	else 	
    { 
		return 0; 
	}
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

	while ( (nread=read(infile, buffer, BUFFSIZE) ) > 0 ){
		if ( write(outfile,buffer,nread) < nread ){
			close(infile); close(outfile); return(-3);
			}
		}
	close(infile); close(outfile);

	if (nread == -1 ) return(-4);
	else	return(0);
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

    if(strcmp(dest, source))
    {
        return 1;
    }
    if(buf_des.st_size == buf_org.st_size)
    {
        if(difftime(buf_des.st_mtime , buf_org.st_mtime) > 0)   // source time 
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