#include <stdlib.h>
#include "List.h"

int compare(Pointer p1, Pointer p2)
{
    return strcmp(p1,p2);
}

// Ενα BList είναι pointer σε αυτό το struct

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
	BList blist = malloc(sizeof(*blist));			// δημιουργούμε το struct
	blist->size = 0;								// αρχικοποιούμε τις μεταβλητές
	blist->dummy = malloc(sizeof(*blist->dummy));	// φτιάχνουμε τον dummy
	blist->dummy->next = NULL;
	blist->dummy->prev = NULL;
	blist->last = blist->dummy;						// εφόσον η λίστα είναι άδεια, ο τελευταίος κόμβος δείχνει στο dummy
	return blist;
}

int blist_size(BList blist) 
{
	return blist->size;
}

BListNode blist_insert(BList blist, BListNode node, Pointer value) 
{
	//Εισάγουμε πριν τον node
	BListNode new = malloc(sizeof(*new));
	BListNode dummy; 
	if(node == BLIST_BOF)						// αν ο node δείχνει στην αρχή της λίστας
	{
		dummy = blist->dummy;					
		new->value = value;						
		new->next = dummy->next;				
		dummy->next = new;						// εισάγουμε τον καινούριο κόμβο μετά τον dummy
		new->prev = dummy;
		if(blist->size == 0)
		{
			blist->last = new;					// αν η λίστα ήταν άδεια, ο τελευταίος κόμβος δείχνει στον κόμβο που προσθέσαμε
		}
		else
		{
			dummy->next->prev = new;			// αλλιώς μεταξύ του dummy και του πρώτου κόμβου
		}
		
		blist->size++;							// ενημέρωση του size
	}
	else if(node == BLIST_EOF)					// αν ο δείκτης δείχνει στο τέλος της λίστας
	{
		if(blist->size == 0)					// αν η λίστα είναι άδεια
		{
			dummy = blist->dummy;
			new->value = value;
			new->next = dummy->next;			// προσθέτουμε τον καινούριο κόμβο μετά τον dummy
			dummy->next = new;
			new->prev = dummy;
			blist->last = new;					// ο τελευταίος κόμβος δείχνει στον κόμβο που προσθέσαμε
		}
		else									// αν δεν είναι άδεια
		{
			new->value = value;
			new->prev = blist->last;	
			blist->last->next = new;			// προσθέτουμε τον καινούριο κόμβο μετά τον τελευταίο κόμβο
			blist->last = new;					// ο τελευταίος κόμβος δείχνει στον κόμβο που προσθέσαμε
			new->next = NULL;					// αφού ο καινούριος κόμβος μπήκε στο τέλος, ο επόμενος είναι NULL
		}
		
		blist->size++;							// ενημέρωση του size
	} 
	else										// αν η εισαγωγή θα γίνει σε τυχαία θέση μέσα στη λίστα
	{
		new->value = value;
		new->next = node;						// συνδέουμε τον καινούριο κόμβο με τον node
		new->prev = node->prev;					// συνδέουμε τον καινούριο κόμβο με τον προηγούμενο του node
		node->prev->next = new;					// προσθέτουμε τον καινούριο κόμβο πριν τον node
		node->prev = new;						// συνδέουμε τον node με τον καινούριο κόμβο
		blist->size++;							// ενημέρωση του size
	}
	return new;
	
}

void blist_remove(BList blist, BListNode node) 
{
	// αφαιρούμε τον node
	BListNode previous = node->prev;
	if( previous == NULL)						// αν ο προηγούμενος του node είναι NULL, σημαίνει ότι βρίσκεται στην αρχή της λίστας
	{
		previous = blist->dummy;				// άρα ο προηγούμενός του είναι ο dummy
	}
	else
	{
		previous = node->prev;					// αλλιώς, κρατάμε τον προηγούμενο κόμβο από το node
	}
	
	if( node->next ==NULL)						// αν ο επόμενος του node είναι NULL, σημαίνει ότι βρίσκεται στο τέλος της λίστας 
	{
		previous->next = NULL;					// ο προηγούμενος του node θα δείχνει τώρα NULL
		blist->last = previous;					// ο τελευταίος κόμβος αλλάζει
	}
	else										// αλλιώς, συνδέουμε τον προηγούμενο του node με τον επόμενό του node
	{
		previous->next = node->next;
		node->next->prev = node->prev;			// και τον επόμενο του node με τον προηγούμενο του node
	}
	
	blist->size--;								// ενημέρωση του size
	free(node);									// διαγράφουμε τον κόμβο
}

void blist_destroy(BList blist) 
{
	// Διασχίζουμε όλη τη λίστα και κάνουμε free όλους τους κόμβους,
	// συμπεριλαμβανομένου και του dummy
	//
	BListNode node = blist->dummy;
	while (node != NULL) {			
		BListNode next = node->next;		// το node->next _πριν_ κάνουμε free

		free(node);
		node = next;
	}

	// Τέλος free το ίδιο το struct
	free(blist);
}


// Διάσχιση της λίστας /////////////////////////////////////////////

BListNode blist_first(BList blist) 
{
	// Ο πρώτος κόμβος είναι ο επόμενος του dummy.
	return blist->dummy->next;
}

BListNode blist_last(BList blist) 
{
	if(blist->last == blist->dummy)					// αν η λίστα είναι κενή το last δείχνει στον dummy
	{
		return BLIST_EOF;							// αλλά εμείς επιστρέφουμε EOF
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
		if (compare(value, node->value) == 0)									// διάσχιση όλης της λίστας, καλούμε την compare μέχρι να επιστρέψει 0
			return node;		
	return NULL;
}

