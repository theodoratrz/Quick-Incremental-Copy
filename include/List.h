#ifndef LIST_H
#define LIST_H

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

typedef struct list* List;
typedef struct list_node* LNode;
typedef void* ptr;

//creates and returns a list
List list_create();

// returns the size of the list
int get_list_size(List);

// inserts a new element(ptr) in the list, after the node
void list_insert(List, LNode, ptr);

// compares two nodes
int compare_nodes(LNode, LNode);

// removes the given's next node from the list
void list_remove(List, LNode);

// returns the first node of the list
LNode list_first_node(List);

// returns the last node of the list
LNode list_last_node(List);

//returns the next node of the given one
LNode list_node_next(List, LNode);

// returns the ginen's node value
ptr list_get_value(List, LNode);

// find the element that is equal to ptr, returns the node
LNode list_find(List, ptr);

// free memory
void list_delete(List);


#endif