#include "files.h"

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
    {
        printf("File copied: %s\n", dest);
        return(0);
    }
        
} 

int create_file(char* name)
{
    int fd;
	
	if ( (fd=open(name, O_CREAT|O_RDWR, PERM)) == -1)
    {
		return -1;
	}
	
    printf("File created: %s\n", name);
	return 0; 
}

int is_file(char* name)
{
    struct stat buf;
    stat(name, &buf);
    if ((buf.st_mode & S_IFMT) == S_IFREG )
    {
        return 1;
    }
    return 0;
}

int compare_files(char* dest,char* source)
{
    struct stat buf_org, buf_des;
    stat(dest, &buf_des);
    stat(source, &buf_org);

    if( (buf_des.st_size) == (buf_org.st_size) )
    {
        if( (difftime(buf_des.st_mtime , buf_org.st_mtime)) > 0.0)   // source time 
        {
            return 0;
        }

        return 1;
    }
    
    return 1;   
}