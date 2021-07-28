#ifndef LIST_H
#define LIST_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// virtual nodes before first node and after last node
#define BLIST_BOF (BListNode)1
#define BLIST_EOF (BListNode)0

typedef struct blist* BList;
typedef struct blist_node* BListNode;
typedef void* Pointer;

// creates and returns a list
BList blist_create();

// number of elements in the list
int blist_size(BList blist);

// Add a new node before node
BListNode blist_insert(BList blist, BListNode node, Pointer value);

// removes node
void blist_remove(BList blist, BListNode node);

// free memory , deletes list
void blist_destroy(BList blist);

// returns the first/last node of the list
BListNode blist_first(BList blist);
BListNode blist_last(BList blist);

// returns next/previous node from node
BListNode blist_next(BList blist, BListNode node);
BListNode blist_previous(BListNode node);

// returns the content of node
Pointer blist_node_value(BList blist, BListNode node);

// finds the node with content=value and returns it. 
// if doesn't exist returns BLIS_EOF
BListNode blist_find_node(BList blist, Pointer value);

#endif