
#include <stdio.h>
#include <stdlib.h>


// Header file containing functions needed for hash table


// define data struct
// position is the current string/move the program is analyzing
// from is the move that came before the position string
// steps is the number of steps taken to get to the position string
// from the original
struct data {
    char* position;
    char* from;
    int steps;
};

typedef struct data Data;
typedef struct node hashNode;  // array of data structs is a node in hash
typedef hashNode* Table;

// a hash function that generates a hash index based on the string
// and the table size
// this hash function was borrowed from Stanley Eisenstat of Yale University
long hash (char *s, long size);

// a function that creates a hash table using the size as a way of
// determining how big the hash table will be (how many indexes it has)
Table createTable(long size);

// add a triple (string position, string from, string)
void insert(Table table, long size, Data* triple);

Data* search(Table table, long size, char* key);

char* searchPos(Table table, long size, char* key);

char* searchFrom(Table table, long size, char* key);

int searchSteps(Table table, long size, char* key);

Table tableResize(Table table, long old_size, long new_size);

void tableDestroy(Table table, long size);

void printTable(Table test, long tableSize);
