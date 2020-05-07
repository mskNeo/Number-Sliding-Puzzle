/*
 * Code to test hash table
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOAD_FACTOR 8

#include "Hash.h"

int main()
{
    unsigned long tableSize = 1024;
    Table test = createTable(tableSize);    // make a table

    printf("Address of test table: %p\n", test); // print address of table
    
    // insert these pieces of data into table
    Data* node1 = malloc(sizeof(Data));
    node1->position = "hello";
    node1->from = NULL;
    node1->steps = 0;

    Data* node2 = malloc(sizeof(Data));
    node2->position = "hello";
    node2->from = "cool";
    node2->steps = 1;

    Data* node3 = malloc(sizeof(Data));
    node3->position = "yo";
    node3->from = "hello";
    node3->steps = 1;

    Data* node4 = malloc(sizeof(Data));
    node4->position = "yo";
    node4->from = "cool";
    node4->steps = 2;
    
    insert(test, tableSize, node1);
    insert(test, tableSize, node2);
    insert(test, tableSize, node3); 
    insert(test, tableSize, node4); 

    // print out data from insert
    printf("Test Table\n");
    printTable(test, tableSize);

    test = tableResize(test, tableSize, tableSize * LOAD_FACTOR);
    tableSize *= LOAD_FACTOR;

    // test search
    Data* testNode1 = search(test, tableSize, "hello");    // get the hashkey to print out data
    Data* testNode2 = search(test, tableSize, "yo");    // get the hashkey to print out data

    if (strcmp(testNode1->position, "hello") == 0 && strcmp(testNode2->position, "yo") == 0)
    {
        printf("\nSearch in original table works!\n");
    }

    printf("\n=======================================\n");  // divider for output

    printf("\nAddress of newTest table: %p\n", test); // print address of table

    printf("\nNew Test Table\n");
    printTable(test, tableSize);

    // test search
    Data* testNode3 = search(test, tableSize, "hello");    // get the hashkey to print out data
    Data* testNode4 = search(test, tableSize, "yo");    // get the hashkey to print out data

    if (strcmp(testNode3->position, "hello") == 0 && strcmp(testNode4->position, "yo") == 0)
    {
        printf("\nSearch in new table works!\n");
    }


    tableDestroy(test, tableSize);  // destroy test table

    exit(EXIT_SUCCESS);
}
