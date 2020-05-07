
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h> 

#include "Hash.h"

struct node {
    struct data** array;
    int size;
};

/*
 * Credits:
 * - Will be using staff hash function to make my hash table
 * - https://www.tutorialspoint.com/data_structures_algorithms/hash_table_program_in_c.htm
 * - the above link also helped me understand hash functions as well
 */

/* borrowed this function from hashFunction.c in /c/cs223/Hwk5 from Stan
 * Return hash of string S into [0,SIZE)
 * SIZE would be equal to TABLE_SIZE
 */
long hash(char *s, long size)
{
    unsigned long sum;
    int shift;
    const unsigned long prime = 3141592653589793239L;

    for (sum = 0, shift = 0; *s; s++) {         // Compress string to long
	sum ^= *s<<shift;
	shift += 4;
	if (shift >= 57)
	    shift -= 57;
    }
    sum += sum >> 33;                           // Condition the bits
    sum *= prime;
    sum += sum >> 33;

    return (sum % size);                        // Reduce to [0,SIZE)
}

// create a table of an array of hash nodes (array of pointers to data structs)
Table createTable(long size)
{
    Table table = malloc(sizeof(hashNode) * size);

    // initialize table pointers
    for (int i = 0; i < size; i++)
    {
        table[i].array = malloc(sizeof(Data*));
        table[i].size = 0;
    }

    return table;
}

void insert(Table table, long size, Data* node)
{
    // hash based on position string
    long hashIndex = hash(node->position, size);

    // no collisions
    if (table[hashIndex].size == 0)
    {
        table[hashIndex].array[0] = node;
        table[hashIndex].size = 1;
    }

    // handle collisions with chaining by resizing
    else
    {   
        int new_size = table[hashIndex].size + 1;   // increase size by one
        table[hashIndex].array = realloc(table[hashIndex].array, sizeof(Data) * new_size);  // realloc array to incorporate new size
        table[hashIndex].size = new_size;   // update size
        table[hashIndex].array[new_size - 1] = node;   // put node at end of array

        for (int i = table[hashIndex].size - 1; i > 0; i--)
        {
            while (strcmp(table[hashIndex].array[i]->position, table[hashIndex].array[i - 1]->position) < 0)
            {
                Data* temp = table[hashIndex].array[i];
                table[hashIndex].array[i] = table[hashIndex].array[i - 1];
                table[hashIndex].array[i - 1] = temp;
            }
        }
    }   
}

Data* search(Table table, long size, char* key)
{
    // get hash    
    long hashKey = hash(key, size);

    // look through all triples in array at index
    for (int i = 0; i < table[hashKey].size; i++)
    {
        if (strcmp(table[hashKey].array[i]->position, key) == 0)
        {
            return table[hashKey].array[i];
        }
    }

    return NULL;
}

Table tableResize(Table table, long old_size, long new_size)
{
    Table newTable = createTable(new_size);

    // move contents from old table to new table
    for (int i = 0; i < old_size; i++)
    {
        // skip over empty hash indexes
        if (table[i].size == 0)
        {
            continue;
        }

        // reinsert all triples stored in table into new table
        for (int j = table[i].size - 1; j >= 0; j--)
        {
            insert(newTable, new_size, table[i].array[j]);
        }
    }

    tableDestroy(table, old_size);
    return newTable;
}

void tableDestroy(Table table, long size)
{
    // go through all columns of hash table
    for (int i = 0; i < size; i++)
    {
        free(table[i].array);   // free array
    }

    free(table);    // free table
}

void printTable(Table test, long tableSize)
{
    for (int i = 0; i < tableSize; i++)
    {
        if (test[i].size == 0)
        {
            continue;
        }

        printf("\nSize of node: %i\n", test[i].size);

        for (int j = 0; j < test[i].size; j++)
        {
            printf("Position string: %s\n", test[i].array[j]->position);
            printf("From string: %s\n", test[i].array[j]->from);
            printf("Number of steps: %i\n", test[i].array[j]->steps);
        }
    }
}
