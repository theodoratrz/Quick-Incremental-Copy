#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "search_and_compare.h"
#include "is_dir.h"
#define  SIZE 		30
#define  PERM 		0644
char *modes[]={"---","--x","-w-","-wx","r--","r-x","rw-","rwx"}; 

int mycopyfile(char *name1, char *name2, int BUFFSIZE){
	int infile, outfile;
	ssize_t nread;
	char buffer[BUFFSIZE];
	
	if ( (infile=open(name1,O_RDONLY)) == -1 )
		return(-1);

	if ( (outfile=open(name2, O_WRONLY|O_CREAT|O_TRUNC, PERM)) == -1){
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

void list(DIR* dp, struct dirent *dir){
    char *newname;

	while ((dir = readdir(dp)) != NULL ) {
  		if (dir->d_ino == 0 ) continue;
  		
  		}

}

void printout(char *name){
    struct stat 	mybuf;
    char 		type, perms[10];
    int 		i,j;

	stat(name, &mybuf);
	switch (mybuf.st_mode & S_IFMT){
  	case S_IFREG: type = '-'; break;
  	case S_IFDIR: type = 'd'; break;
  	default:      type = '?'; break;
  	}

	*perms='\0';

	for(i=2; i>=0; i--){
   		j = (mybuf.st_mode >> (i*3)) & 07;
   		strcat(perms,modes[j]); 
		}

	printf("%c%s%3d %5d/%-5d %7d %.12s %s \n", \
                type, perms, (int)mybuf.st_nlink, mybuf.st_uid, \
                mybuf.st_gid, (int)mybuf.st_size, \
                ctime(&mybuf.st_mtime)+4, name); /* try without 4 */
}
