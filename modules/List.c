#include <stdlib.h>
#include "List.h"


int compare(Pointer p1, Pointer p2)
{
    return strcmp(p1,p2);
}

// BList is a pointer to this struct

struct blist {
	BListNode dummy;				// χρησιμοποιούμε dummy κόμβο, ώστε ακόμα και η κενή λίστα να έχει έναν κόμβο.
	BListNode last;					// δείκτης στον τελευταίο κόμβο, ή στον dummy (αν η λίστα είναι κενή)
	int size;						// μέγεθος, ώστε η list_size να είναι Ο(1)
};

struct blist_node {
	BListNode next;					// Δείκτης στον επόμενο
	BListNode prev;					// Δείκτης στον προηγούμενο	
	Pointer value;					// Η τιμή που αποθηκεύουμε στον κόμβο
};

BList blist_create() 
{
	BList blist = malloc(sizeof(*blist));			// allocate memory for struct
	blist->size = 0;								// initialize variables
	blist->dummy = malloc(sizeof(*blist->dummy));	// create a dummy node
	blist->dummy->next = NULL;
	blist->dummy->prev = NULL;
	blist->last = blist->dummy;						// empty list => last node points to dummy
	return blist;
}

int blist_size(BList blist) 
{
	return blist->size;
}

// insert before node
BListNode blist_insert(BList blist, BListNode node, Pointer value) 
{
	BListNode new = malloc(sizeof(*new));
	BListNode dummy; 
	if(node == BLIST_BOF)						// node points at the beginning of the list
	{
		dummy = blist->dummy;					
		new->value = value;						
		new->next = dummy->next;				
		dummy->next = new;						// insert new node after dummy node
		new->prev = dummy;
		if(blist->size == 0)
		{
			blist->last = new;					// if list is empty, last node points to new node
		}
		else
		{
			dummy->next->prev = new;			// else, after dummy
		}
		
		blist->size++;							// increase size
	}
	else if(node == BLIST_EOF)					// node points at the end of the list
	{
		if(blist->size == 0)					// if list is empty
		{
			dummy = blist->dummy;
			new->value = value;
			new->next = dummy->next;			// add new node after dummy
			dummy->next = new;
			new->prev = dummy;
			blist->last = new;					// last node points to new node
		}
		else									
		{
			new->value = value;
			new->prev = blist->last;	
			blist->last->next = new;			// add new node after last node of the list
			blist->last = new;					// last node points to new node
			new->next = NULL;					// next of new is NULL
		}
		
		blist->size++;							// increase size
	} 
	else										// random insert in the list
	{
		new->value = value;
		new->next = node;						// link new node with current node
		new->prev = node->prev;					// link new node with current's previous
		node->prev->next = new;					// add new node before current
		node->prev = new;						// link node with current node
		blist->size++;							// increase size
	}
	return new;
	
}

// remove node
void blist_remove(BList blist, BListNode node) 
{
	BListNode previous = node->prev;
	if( previous == NULL)						// if node's previous is NULL, node is at the beginning of the list
	{
		previous = blist->dummy;				// previous node is dummy
	}
	else
	{
		previous = node->prev;					// keep previous node
	}
	
	if( node->next ==NULL)						// if node's next is NULL, node is at the end of the list
	{
		previous->next = NULL;					// node's previous points to NULL
		blist->last = previous;					// last node updated
	}
	else										// else, link node's previous with node's next
	{
		previous->next = node->next;
		node->next->prev = node->prev;			// and node's next with node's previous
	}
	
	blist->size--;								// decrease size
	free(node);									// delete node
}

void blist_destroy(BList blist) 
{
	// Iterate tthrough list and remove every node(including dummy)
	BListNode node = blist->dummy;
	while (node != NULL) {			
		BListNode next = node->next;	

		free(node);
		node = next;
	}

	// free the struct
	free(blist);
}

BListNode blist_first(BList blist) 
{
	return blist->dummy->next;
}

BListNode blist_last(BList blist) 
{
	if(blist->last == blist->dummy)					// empty list=>last node = dummy
	{
		return BLIST_EOF;							// we don't return dummy(user doesn't know about dummy)
	}
	else
	{
		return blist->last;
	}
}


BListNode blist_next(BList blist, BListNode node) 
{
	if(node->next == BLIST_EOF)
	{
		return BLIST_EOF;
	}

	return node->next;
}

BListNode blist_previous(BListNode node) 
{
	if(node->next == BLIST_BOF)
	{
		return BLIST_BOF;
	}
	return node->prev;
}

Pointer blist_node_value(BList blist, BListNode node) 
{
	if(node == NULL)
	{
		return NULL;
	}
	return node->value;
}

BListNode blist_find_node(BList blist, Pointer value) 
{
	for (BListNode node = blist->dummy->next; node != NULL; node = node->next)
		if (compare(value, node->value) == 0)									// iterate list, call compare till it returns 0
			return node;		
	return NULL;
}

