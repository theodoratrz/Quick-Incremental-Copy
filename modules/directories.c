#include "directories.h"

struct statistics copy_directory(char* dest_directory, char* source_directory, int lnk, int del)
{
    DIR *origin, *destination;
    struct dirent *dirent_org, *dirent_des;
    struct stat buf_org, buf_des;
    char* dfile_name, *sfile_name, *to_be_copied, *curr_file, *to_be_deleted;
    struct statistics s;

    // create bi-directional lists and store the files/directories names
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

    s.sum = 1;
    s.entities = 0;
    s.flag = 0;

    // if the destination doesn't exist, create a new directory
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

    // read all the source directory and store the files/directories names in a list
    while( (dirent_org = readdir(origin)) )
    {
        // skip "." and ".."
        if(!(strcmp(dirent_org->d_name, ".")) || !(strcmp(dirent_org->d_name, "..")))
        {
            continue;
        }
        else
        {
            s.sum++;    // keep record of how many files/directories are being explored
            // allocate enough space for the whole path
            sfile_name = malloc(strlen(source_directory)+strlen(dirent_org->d_name)+2);
            // create the path
            strcpy(sfile_name, source_directory);
            strcat(sfile_name, "/");
            strcat(sfile_name, dirent_org->d_name);
            // directories are stored in a different list from files
            if(is_directory(sfile_name))
            {
                // keep only the name not the path
                // the path is easy to find 
               blist_insert(source_dir, BLIST_EOF, dirent_org->d_name);
            }
            else
            {
                blist_insert(source_files, BLIST_EOF, dirent_org->d_name);
            }
        }
        
    }

    // read all the source directory and store the files/directories names in a list
    while( (dirent_des = readdir(destination)) )
    {
        // skip "." and ".."
        if(!(strcmp(dirent_des->d_name, ".")) || !(strcmp(dirent_des->d_name, "..")))
        {
            continue;
        }
        else
        {
            // allocate enough space for the whole path
            dfile_name = malloc(strlen(dest_directory)+strlen(dirent_des->d_name)+2);
            // create the path
            strcpy(dfile_name, dest_directory);
            strcat(dfile_name, "/");
            strcat(dfile_name, dirent_des->d_name);
            // directories are stored in a different list from files
            if(is_directory(dfile_name))
            {
                // keep only the name not the path
                // the path is easy to find
                blist_insert(dest_dir, BLIST_EOF, dirent_des->d_name);          
            }
            else
            {
                blist_insert(dest_files, BLIST_EOF, dirent_des->d_name);           
            }
        }
    }

    // loop through source files and compare them to destination files
    for(BListNode node = blist_first(source_files); node != BLIST_EOF; node = blist_next(source_files, node))
    {
        BListNode temp = blist_find_node(dest_files, blist_node_value(source_files, node));

        // create the paths
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
        
        // if the file exists in the destination directory
        if( temp != NULL )
        {
            // compare the files
            if(compare_files(to_be_copied, curr_file))
            {
                // if they are not the same, copy again
                s.flag = 1;
                copy_files(to_be_copied, curr_file, 256);
                s.entities++;   // increase the sum of copied files
            }
            
            blist_remove(dest_files, temp);  //already exists
            
        }
        else    // copy to destination
        {
            s.flag = 1;
            create_file(to_be_copied);
            copy_files(to_be_copied, curr_file, 256);
            s.entities++;   // increase the sum of copied files
            
        }
            free(to_be_copied);
            free(curr_file);    
    }

    // loop through source directories and compare them to destination directories
    // if a file/directory exists in source and destination remove it from destination's list
    for(BListNode node = blist_first(source_dir); node != BLIST_EOF; node = blist_next(source_dir, node))
    {
        BListNode temp = blist_find_node(dest_dir, blist_node_value(source_dir, node));

        // create the path
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

        // if the directory exists in the destination directory
        if( temp != NULL )
        {
            // recursive
            // explore all the files of the directories
            struct statistics t = copy_directory(to_be_copied, curr_file, lnk, del);
            // increase the total sum of files explored
            s.sum += t.sum;
            if(t.flag)
            {
                s.entities += t.entities;   // if the directories were not same, increease the num of copied files
                s.flag = 1;
            }
            blist_remove(dest_dir, temp);   // remove it from the list
        }
        else   // copy to destination
        {
            // recursive
            // explore all the files of the directories
            struct statistics t = copy_directory(to_be_copied, curr_file, lnk, del);
            s.sum += t.sum; // increase the total sum of files explored
            s.flag =1;
        }

            free(to_be_copied);
            free(curr_file);   
    }
   
   if(del)  // if the flag delete == 1 => delete the files of destination that does not exist in source
   {
       // loop through destination files and delete them(everything left doesn't exist in source)
       for(BListNode node = blist_first(dest_files); node != BLIST_EOF; node = blist_next(dest_files, node))
        {
            if( !(blist_size(dest_files) ) )    // if there is nothing left , break
            {
                break;
            }

            // create the path
            char* str1 = (char*)blist_node_value(dest_files, node);
            to_be_deleted = malloc(strlen(dest_directory)+strlen(str1)+2);
            strcpy(to_be_deleted, dest_directory);
            strcat(to_be_deleted, "/");
            strcat(to_be_deleted, str1);

            // remove the file
            remove(to_be_deleted);
            
            free(to_be_deleted);
        }

        // loop through destination directories and delete them(everything left doesn't exist in source)
        for(BListNode node = blist_first(dest_dir); node != BLIST_EOF; node = blist_next(dest_dir, node))
        {
            if( !(blist_size(dest_dir) ) )  // if there is nothing left , break
            {
                break;
            }

            // create the path
            char* str1 = (char*)blist_node_value(dest_dir, node);
            to_be_deleted = malloc(strlen(dest_directory)+strlen(str1)+2);
            strcpy(to_be_deleted, dest_directory);
            strcat(to_be_deleted, "/");
            strcat(to_be_deleted, str1);

            // remove directory recursively
            remove_directory(to_be_deleted);
            
            free(to_be_deleted);
        }
   }
   

    closedir(origin);
    closedir(destination);

    blist_destroy(source_files);
    blist_destroy(dest_files);
    blist_destroy(source_dir);
    blist_destroy(dest_dir);

    return s;
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

int remove_directory(char *name) 
{
    DIR *origin;
    struct dirent *p;
    int i;
    origin = opendir(name);
    if(origin == NULL)
    {
        perror("Opening directory");
        exit(1);
    }

    i = 0;

    // loop through the directory
    while (!i && (p=readdir(origin))) 
    {
        int r = -1;
        char *buffer;
   
        // skip "." and ".."
        if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
            continue;

        // create the path
        buffer = malloc(strlen(name)+ strlen(p->d_name) + 2);
        strcpy(buffer, name);
        strcat(buffer, "/");
        strcat(buffer, p->d_name);

        //if it is a directory
        if(is_directory(buffer)) 
        {
            // recursive
            r = remove_directory(buffer);
        }
        else
        {
            // remove the file
            r = unlink(buffer);
        }

        free(buffer);

        i = r;
    }
    closedir(origin);

        
    if (!i)
    {
        // remove the directory
        i = rmdir(name);
        printf("Directory removed: %s\n", name);
    }
      

   return i;
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