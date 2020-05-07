
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Deque.h"


// The internal representation of the Deque ADT is a pair of stacks (the H
// stack and the T stack), each implemented using a headless, singly-linked
// list.  To add an item to the tail (head) of the Deque, push it onto the
// top of the T (H) stack.  To remove an item from the head of the Deque,
// pop it off the top of the H stack (but if the H stack is empty, first
// move items one at a time from the top of the T stack to the top of the H
// stack until the T stack is empty).
//
// This data structure requires one link per item rather than two as in the
// doubly-linked list implementation given in Aspnes' notes.  But while
// removing an item may not take constant time when the H stack is empty,
// the average time per operation for a sequence of operations that begins
// and ends with an empty Deque is constant. 


typedef struct node {
    struct node *next;
    char* line;
} Node;

struct deque {
    Node *head;     // pointer to head deque
    Node *tail;     // pointer to tailious dequq
};

// Implementation of createD()
bool createD (Deque *d)
{
    *d = malloc(sizeof(struct deque));
    
    // failed to malloc deque
    if (*d == NULL)  
    { 
        fprintf(stderr, "could not create deque\n");
        return false; 
    }

    (*d)->head = NULL;  
    (*d)->tail = NULL;

    return true;           
}


// Implementation of isEmptyD()
bool isEmptyD (Deque *d)
{
    if ((*d)->head == NULL && (*d)->tail == NULL) {   return true;  }   // return true if deque points to nothing

    return false;           // else deque points to a different deque, meaning nonempty
}


// Implementation of addD()
bool addD (Deque *d, char *s)
{
    Node *e = malloc(sizeof(Node));

    // if malloc fails, could not add node
    if (e == NULL)  
    {   
        fprintf(stderr, "could not add Node to deque\n");
        return false;   
    }

    e->line = s;    // put s into line

    // go to tail, make tail point to new node
    // make head pointer point to new deque as tail
    if ((*d)->tail != NULL)
    {
        e->next = (*d)->tail;
        (*d)->tail = e; 
    }
    
    // if deque is empty, add node to tail of deque
    if ((*d)->tail == NULL)
    {
        e->next = NULL;
        (*d)->tail = e;
    }

    return true;
}


// Implementation of remD()
bool remD (Deque *d, char **s)
{
    // if deque is empty, make *s NULL;
    if (isEmptyD(d))
    {
        *s = NULL;
        fprintf(stderr, "deque is empty, cannot remove\n");
        return false;
    }


    // if head is empty, then move all nodes from tail stack to head stack
    if ((*d)->head == NULL)
    {
        while ((*d)->tail != NULL)
        {
            Node *f = (*d)->tail;
            pushD(d, f->line);
            (*d)->tail = f->next;
            free(f);
        }
    }

    Node *e = (*d)->head;

    *s = e->line;   // copy line from head to *s
    
    (*d)->head = e->next;  // make the pointer point to the next node after head
    free(e);    // free head node
    return true;    
}


// Implementation of headD()
bool headD (Deque *d, char **s)
{
    if (isEmptyD(d))
    {
        *s = NULL;
        fprintf(stderr, "no head in deque because it is empty\n");
        return false;
    }

    // if head is empty, then move all nodes from tail stack to head stack
    if ((*d)->head == NULL)
    {
        while ((*d)->tail != NULL)
        {
            Node *f = (*d)->tail;
            pushD(d, f->line);
            (*d)->tail = f->next;
            free(f);
        }
    }

    Node *e = (*d)->head;

    *s = e->line;   // get line from head and store into *s

    return true;
}


// Implementation of pushD()
bool pushD (Deque *d, char *s)
{
    Node *e = malloc(sizeof(Node));

    if (e == NULL)  
    {   
        fprintf(stderr, "could not push onto deque\n");
        return false;   
    }   // if malloc fails, could not add

    e->line = s;    // store string into node

    // check to see if head stack is nonempty
    // if empty
    if ((*d)->head != NULL)
    {
        e->next = (*d)->head; // make node point to null
    }

    if ((*d)->head == NULL)
    {
        e->next = NULL;
    }

    (*d)->head = e;
    return true;
}


// Implementation of destroyD()
bool destroyD (Deque *d)
{
     // if d doesn't exist, then can't destroy it
    if (!d) 
    {   
        fprintf(stderr, "cannot destroy deque\n");
        return false;   
    }

    char *s = NULL;    // make a string pointer for remD

    while (!isEmptyD(d))
    {
        remD(d, &s); // remove deque and free it
    }

    free(*d);   // free the deque
    *d = NULL;  // deque points to nothing now

    return true;
}
