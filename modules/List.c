#include "List.h"

struct list
{
    LNode dummy;            // we use an empty node to initialize the list
    LNode last;             // keep the last node of the list
    int size;               // size of the list
};

struct list_node            // a list node contains a value(of any type) and a pointer
{                           // to the next node
    LNode next;
    ptr value;
};

List list_create()
{
    List l = malloc(sizeof(*l));    // create the list
    if(l == NULL)                   // check if the memory was successfully allocated
    {
        printf("Memory not allocated\n");
        exit(1);
    }
    l->size = 0;                                // initialize the size
    l->dummy = malloc(sizeof( (*l->dummy)) );   // create the dummy node
    if(l->dummy == NULL)
    {
        printf("Memory not allocated\n");
        exit(1);
    }

    l->dummy->next = NULL;                      // list is empty so, dummy's next is NULL
    l->last = l->dummy;                         // and the last node is also dummy

    return l;
}

int get_list_size(List l)
{
    return l->size;
}

int compare_nodes(LNode n1, LNode n2)           // compare list nodes based on their values
{
    return (strcmp(n1->value, n2->value));
}

void list_insert(List l, LNode node, ptr v)
{
    // if node is NULL we just insert after the dummy node
    if(node == NULL)
    {
        node = l->dummy;
    }
    
    LNode NewNode = malloc(sizeof(*NewNode));   // create the new node
    if(NewNode == NULL)                         // check if the memory was successfully allocated
    {
        printf("Memory not allocated\n");
        exit(1);
    }

    NewNode->value = v;
    NewNode->next = node->next;             // connect newnode between the node and node->next
    node->next = NewNode;       
    if(l->last == node)                     // if node was the last
    {
        l->last = NewNode;                  // then new node will be the last now
    }

    l->size++;                              // increase the size

}

void list_remove(List l, LNode node)
{
    if(l->dummy->next == NULL)              // if list is empty, print a message
    {
        printf("List is empty\n");
    }
    else 
    {
        if(node == NULL)                    // if node is null, delete after dummy
        {
            node = l->dummy;
        }

        LNode toRemove = node->next;        // node to be removed is the next of node
        if(toRemove != NULL)                // check if it exists
        {
            node->next = toRemove->next;    // connect node with toremove's next node
            if(toRemove == l->last)         // if toRemove node is the last node of the list
            {   
                l->last = node;             // now node will be the last node of the list
            }

            l->size--;                      // decrease size of the list

            free(toRemove);                 // remove 
        }
        
    }
}

LNode list_first_node(List l)
{
    if(get_list_size(l))
        return l->dummy->next;                 // returns first node after the dummy node
    return NULL;
}

LNode list_last_node(List l)               // if the last node of the list is the dummy
{                                          // then the list is empty, so return NULL
    if (l->last == l->dummy)
    {
		return NULL;		
    }
	else
    {
        return l->last;
    }
		
    
}

// returns the next of node
LNode list_node_next(List l, LNode node)
{
    if(node != NULL)                    
    {
        return node->next;
    }

    return NULL;
}

// returns the value of the list node(if it exists)
ptr list_get_value(List l, LNode node)
{
    if(node != NULL)
    {
        return node->value;
    }

    return NULL;
}

// find the node with value "value"
LNode list_find(List l, ptr value)
{
    if(l->dummy->next != NULL)       //if list is not empty
    {                               // iterate all the list 
        for(LNode node = l->dummy->next; node != NULL; node = node->next)
        {
            if( !(strcmp(value, node->value)) )  
            {
                return node;                            // we found the node
            }
        }
    }

    return NULL;
}

void list_delete(List l)
{
    LNode node = l->dummy;          // iterate the list
    LNode next;                     // keep the next node 
    while(node != NULL)
    {
        next = node->next;
        if(node != l->dummy)    
        {
            free(node->value);      // free the content of the node
        }
        free(node);                 // free the node
        node = next;                
    }

    free(l);                        // free the list
}