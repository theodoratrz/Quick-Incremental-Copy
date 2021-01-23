#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Οι σταθερές αυτές συμβολίζουν εικονικούς κόμβους _πριν_ τον πρώτο και _μετά_ τον τελευταίο
#define BLIST_BOF (BListNode)1
#define BLIST_EOF (BListNode)0

typedef struct blist* BList;
typedef struct blist_node* BListNode;
typedef void* Pointer;


// Δημιουργεί και επιστρέφει μια νέα λίστα.
// Αν destroy_value != NULL, τότε καλείται destroy_value(value) κάθε φορά που αφαιρείται ένα στοιχείο.

BList blist_create();

// Επιστρέφει τον αριθμό στοιχείων που περιέχει η λίστα.

int blist_size(BList blist);

// Προσθέτει έναν νέο κόμβο __πριν__ τον node (δηλαδή αν ο node είχε θέση i στη λίστα, o νέος κόμβος
// παίρνει τη θέση i και ο node πηγαίνει στην i+1), ή στo τέλος αν node == BLIST_EOF, με περιεχόμενο value.

BListNode blist_insert(BList blist, BListNode node, Pointer value);

// Αφαιρεί τον κόμβο node (πρέπει να υπάρχει στη λίστα).

void blist_remove(BList blist, BListNode node);

// Ελευθερώνει όλη τη μνήμη που δεσμεύει η λίστα blist.
// Οποιαδήποτε λειτουργία πάνω στη λίστα μετά το destroy είναι μη ορισμένη.

void blist_destroy(BList blist);

// Επιστρέφουν τον πρώτο και τον τελευταίο κομβο της λίστας, ή BLIST_BOF / BLIST_EOF αντίστοιχα αν η λίστα είναι κενή

BListNode blist_first(BList blist);
BListNode blist_last(BList blist);

// Επιστρέφουν τον επόμενο και τον προηγούμενο κομβο του node, ή BLIST_EOF / BLIST_BOF
// αντίστοιχα αν ο node δεν έχει επόμενο / προηγούμενο.

//BListNode blist_next(BList blist, BListNode node);
//BListNode blist_previous(BList blist, BListNode node);
BListNode blist_next(BList blist, BListNode node);
BListNode blist_previous(BListNode node);

// Επιστρέφει το περιεχόμενο του κόμβου node

//Pointer blist_node_value(BList blist, BListNode node);
Pointer blist_node_value(BList blist, BListNode node);

// Βρίσκει τo πρώτo στοιχείο που είναι ισοδύναμο με value (με βάση τη συνάρτηση compare).
// Επιστρέφει τον κόμβο του στοιχείου, ή BLIST_EOF αν δεν βρεθεί.

//BListNode blist_find_node(BList blist, Pointer value, CompareFunc compare);
BListNode blist_find_node(BList blist, Pointer value);


#endif