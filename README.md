# Quick Incremental Copy
Implementation of "cp -I" linux command

**Goals/Tasks**

The goal of this project is to copy directories/files quicker than the simple `cp` command. 

**Summary**

The programm has two arguments: the source (A) file/directory and the destination (T) file/directory. The programm traverses through A, reads the info of the i-nodes and for every `a i-node` in A it searces the equivalent `t i-node` in T.
We distinguish 4 cases: 
1. The `t` doesn't exist in T: in this case the `t` has to be created in the right place inside T and the `a` to be copied in the `t`. If the i-node refers to a file, we also have to copy the data of the file. 
2. The `t` exists in T and is the same as the `a` in A: in this case we do nothing. This is the case where the quick incremental copy "wins" the simple `cp`.
3. The `t` exists in T, but there is no equivelant in `a` in A: in this case the file from A was deleted and we have to update the T. 
4. The `t` exists in T and it's not the same as the `a` in A: in this case we have to copy the content of the `a i-node` to `t i-node`.
  When 2 files are not the same:
  - obviously, we don't read the content of the files, because this is time-consuming.
  - if a is a file and t is a directory
  - if 
If the i-nodes `a` and `t` are referring to directories, we have to recursively do the above steps.
