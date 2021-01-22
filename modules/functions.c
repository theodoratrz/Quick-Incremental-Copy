#include "functions.h"

int copy_directory(char* dest_directory, char* source_directory)
{
    DIR *origin, *destination;
    struct dirent *dirent_org, *dirent_des;
    struct stat buf_org, buf_des;
    char* dfile_name, *sfile_name, *to_be_copied, *curr_file, *to_be_deleted;
    int flag = 0;
    List source_files = list_create();
    List dest_files = list_create();

    origin = opendir(source_directory);
    if(origin == NULL)
    {
        perror("Opening directory");
        exit(1);
    }
    destination = opendir(dest_directory);
    if(destination == NULL)
    {
        int f = create_directory(dest_directory);
        destination = opendir(dest_directory);
        if(f == -1)
        {
            perror("Creating directory");
            exit(1);
        }
        
    }
    
    stat(source_directory, &buf_org);
    stat(dest_directory, &buf_des);

    while( (dirent_org = readdir(origin)) )
    {
        if(!(strcmp(dirent_org->d_name, ".")))
        {
            continue;
        }
        else if(!(strcmp(dirent_org->d_name, "..")))
        {
            continue;
        }
        else
        {
            sfile_name = malloc(strlen(dirent_org->d_name)+1);
            strcpy(sfile_name, dirent_org->d_name);
            list_insert(source_files, NULL, sfile_name);
        }
        
    }

    while( (dirent_des = readdir(destination)) )
    {
        if(!(strcmp(dirent_des->d_name, ".")))
        {
            continue;
        }
        else if(!(strcmp(dirent_des->d_name, "..")))
        {
            continue;
        }
        else
        {
            dfile_name = malloc(strlen(dirent_des->d_name)+1);
            strcpy(dfile_name, dirent_des->d_name);
            list_insert(dest_files, NULL, dfile_name);
        }
    }

    for(LNode node = list_first_node(source_files); node != NULL; node = list_node_next(source_files, node))
    {
        LNode temp = list_find(dest_files, list_get_value(source_files, node)); // change list find
        if( temp != NULL )
        {
            list_remove(dest_files, temp);  //already exists
        }
        else    // copy to destination
        {
            char* str1 = (char*)list_get_value(source_files, node);
            to_be_copied = malloc(strlen(dest_directory)+strlen(str1)+2);
            strcpy(to_be_copied, dest_directory);
            strcat(to_be_copied, "/");
            strcat(to_be_copied, str1);

            char* str2 = (char*)list_get_value(source_files, node);
            curr_file = malloc(strlen(source_directory)+strlen(str2)+2);
            strcpy(curr_file, source_directory);
            strcat(curr_file, "/");
            strcat(curr_file, str2);
            
            if(get_list_size(dest_files))
            {
                if(is_directory(curr_file))
                {
                    if(copy_directory(to_be_copied, curr_file))
                    {
                        flag = 1;
                    }
                }
                else if(is_file(curr_file))
                {
                    if(compare_files(to_be_copied, curr_file))
                    {
                        flag = 1;
                        create_file(to_be_copied);
                        copy_files(to_be_copied, curr_file, 256);
                    }
                }
            }
            else
            {
                flag = 1;
                create_file(to_be_copied);
                copy_files(to_be_copied, curr_file, 256);
            }
            
            free(to_be_copied);
            free(curr_file);
        }
        
    }
   
   for(LNode node = list_first_node(dest_files); node != NULL; node = list_node_next(dest_files, node))
   {
        flag = 1;
        char* str1 = (char*)list_get_value(dest_files, node);
        to_be_deleted = malloc(strlen(dest_directory)+strlen(str1)+2);
        strcpy(to_be_deleted, dest_directory);
        strcat(to_be_deleted, "/");
        strcat(to_be_deleted, str1);

        remove(to_be_deleted);
        free(to_be_deleted);
   }

    closedir(origin);
    closedir(destination);

    return flag;

    list_delete(source_files);
    list_delete(dest_files);
    
    /*while( (dirent_org = readdir(origin)) )
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
            if(!(strcmp(dirent_des->d_name, ".")))
            {
                continue;
            }
            if(!(strcmp(dirent_des->d_name, "..")))
            {
                continue;
            }

            copy++;
            if(first == 0)
            {
                file_names[copy] = malloc(strlen(dirent_des->d_name)+1);
                strcpy(file_names[copy] , dirent_des->d_name);
                sum++;
            }

            strcpy(name,dest);
            strcat(name,"/");
            strcat(name, dirent_org->d_name);

            source_has_dir = is_directory(old);
            dest_has_dir = is_directory(name);

            if( (source_has_dir) && (dest_has_dir) )
            {
                int n = copy_directory(name, old);
                if( n == -1)
                {
                    perror("copying sub-directory");
                    exit(1);
                }
                else if(n == 0)
                {
                    //if(copy < sum)
                    //{
                        strcpy(file_names[copy-1], " ");
                        flag = 1;
                    //}
                    
                }   
            }
            else if( (is_file(name)) && (is_file(old)))
            {
                if( !(strcmp(dirent_org->d_name, dirent_des->d_name)) )
                {
                    int c = compare_files(name, old);
                    if(!c)
                    {
                        strcpy(file_names[copy-1], " ");
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
            printf("&&&&&&& %s\n", name);
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
        if( !(strcmp(file_names[i], " ")))
        {
            continue;
        }
        else
        {
            name = malloc(strlen(dest)+strlen(file_names[i]) + 2);
            strcpy(name, dest);
            strcat(name, "/");
            strcat(name, file_names[i]);
            if(is_directory(name))
            {
                remove_directory(name);
            }
            else
            {
                remove(name);
            }
            
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
    return 0;*/
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

int create_directory(char* name)
{
    int dp = mkdir(name, 0777);
    if(dp == -1)
    {
        return -1;
    }
    else
    {
        printf("Directory created : %s\n", name);
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
    {
        printf("File copied: %s\n", dest);
        return(0);
    }
        
} 

int remove_directory(char *path) {
   DIR *d = opendir(path);
   size_t path_len = strlen(path);
   int r = -1;

   if (d) {
      struct dirent *p;

      r = 0;
      while (!r && (p=readdir(d))) {
          int r2 = -1;
          char *buf;
          size_t len;

          /* Skip the names "." and ".." as we don't want to recurse on them. */
          if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
             continue;

          len = path_len + strlen(p->d_name) + 2; 
          buf = malloc(len);

          if (buf) {
             struct stat statbuf;

             snprintf(buf, len, "%s/%s", path, p->d_name);
             if (!stat(buf, &statbuf)) {
                if (S_ISDIR(statbuf.st_mode))
                   r2 = remove_directory(buf);
                else
                   r2 = unlink(buf);
             }
             free(buf);
          }
          r = r2;
      }
      closedir(d);
   }

   if (!r)
   {
       r = rmdir(path);
       printf("Directory removed: %s\n", path);
   }
      

   return r;
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

