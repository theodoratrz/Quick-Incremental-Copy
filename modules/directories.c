#include "directories.h"

int copy_directory(char* dest_directory, char* source_directory)
{
    DIR *origin, *destination;
    struct dirent *dirent_org, *dirent_des;
    struct stat buf_org, buf_des;
    char* dfile_name, *sfile_name, *to_be_copied, *curr_file, *to_be_deleted;
    int flag = 0;
    BList source_files = blist_create();
    BList source_dir = blist_create();
    BList dest_files = blist_create();
    BList dest_dir = blist_create();

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
            sfile_name = malloc(strlen(source_directory)+strlen(dirent_org->d_name)+2);
            strcpy(sfile_name, source_directory);
            strcat(sfile_name, "/");
            strcat(sfile_name, dirent_org->d_name);
            if(is_directory(sfile_name))
            {
               blist_insert(source_dir, BLIST_EOF, dirent_org->d_name);
            }
            else
            {
                blist_insert(source_files, BLIST_EOF, dirent_org->d_name);
            }
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
            dfile_name = malloc(strlen(dest_directory)+strlen(dirent_des->d_name)+2);
            strcpy(dfile_name, dest_directory);
            strcat(dfile_name, "/");
            strcat(dfile_name, dirent_des->d_name);
            if(is_directory(dfile_name))
            {
                blist_insert(dest_dir, BLIST_EOF, dirent_des->d_name);          
            }
            else
            {
                blist_insert(dest_files, BLIST_EOF, dirent_des->d_name);           
            }
        }
    }

    for(BListNode node = blist_first(source_files); node != BLIST_EOF; node = blist_next(source_files, node))
    {
        BListNode temp = blist_find_node(dest_files, blist_node_value(source_files, node)) ;
       //BListNode prev = blist_previous(node);
       char* str1 = (char*)blist_node_value(source_files, node);
        to_be_copied = malloc(strlen(dest_directory)+strlen(str1)+2);
        strcpy(to_be_copied, dest_directory);
        strcat(to_be_copied, "/");
        strcat(to_be_copied, str1);

        char* str2 = (char*)blist_node_value(source_files, node);
        curr_file = malloc(strlen(source_directory)+strlen(str2)+2);
        strcpy(curr_file, source_directory);
        strcat(curr_file, "/");
        strcat(curr_file, str2);
            
        if( temp != NULL )
        {
            if(compare_files(to_be_copied, curr_file))
            {
                flag = 1;
                copy_files(to_be_copied, curr_file, 256);
            }
            
            blist_remove(dest_files, temp);  //already exists
            
        }
        else    // copy to destination
        {
            flag = 1;
            create_file(to_be_copied);
            copy_files(to_be_copied, curr_file, 256);
            
        }
            free(to_be_copied);
            free(curr_file);    
    }

    for(BListNode node = blist_first(source_dir); node != BLIST_EOF; node = blist_next(source_dir, node))
    {
        BListNode temp = blist_find_node(dest_dir, blist_node_value(source_dir, node)) ;

        char* str1 = (char*)blist_node_value(source_dir, node);
        to_be_copied = malloc(strlen(dest_directory)+strlen(str1)+2);
        strcpy(to_be_copied, dest_directory);
        strcat(to_be_copied, "/");
        strcat(to_be_copied, str1);

        char* str2 = (char*)blist_node_value(source_dir, node);
        curr_file = malloc(strlen(source_directory)+strlen(str2)+2);
        strcpy(curr_file, source_directory);
        strcat(curr_file, "/");
        strcat(curr_file, str2);
        if( temp != NULL )
        {
            if(copy_directory(to_be_copied, curr_file))
            {
                flag = 1;
            }
            blist_remove(dest_dir, temp);
        }
        else    // copy to destination
        {
            copy_directory(to_be_copied, curr_file);
            flag =1;
        }

            free(to_be_copied);
            free(curr_file);   
    }
   
   for(BListNode node = blist_first(dest_files); node != BLIST_EOF; node = blist_next(dest_files, node))
   {
        if( !(blist_size(dest_files) ) )
        {
            break;
        }
        char* str1 = (char*)blist_node_value(dest_files, node);
        to_be_deleted = malloc(strlen(dest_directory)+strlen(str1)+2);
        strcpy(to_be_deleted, dest_directory);
        strcat(to_be_deleted, "/");
        strcat(to_be_deleted, str1);

        remove(to_be_deleted);
        
        free(to_be_deleted);
   }

    for(BListNode node = blist_first(dest_dir); node != BLIST_EOF; node = blist_next(dest_dir, node))
   {
        if( !(blist_size(dest_dir) ) )
        {
            break;
        }
        char* str1 = (char*)blist_node_value(dest_dir, node);
        to_be_deleted = malloc(strlen(dest_directory)+strlen(str1)+2);
        strcpy(to_be_deleted, dest_directory);
        strcat(to_be_deleted, "/");
        strcat(to_be_deleted, str1);

        remove_directory(to_be_deleted);
        
        free(to_be_deleted);
   }

    closedir(origin);
    closedir(destination);

    blist_destroy(source_files);
    blist_destroy(dest_files);
    blist_destroy(source_dir);
    blist_destroy(dest_dir);

    return flag;
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

int is_directory(char* name)
{
    struct stat buf;
    stat(name, &buf);
    if ((buf.st_mode & S_IFMT) == S_IFDIR )
    {
        return 1;
    }
    return 0;
}