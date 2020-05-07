
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define LOAD_MAX 8

#include "Hash.h"
#include "error.h"
#include "Deque.h"
#include "Nine20.h"


/*
 * About Program:
 * Solve a number puzzle using Breadth First Search and a Hash Table
 * Usage: ./Nine20 [HEIGHT WIDTH] MAXSTEPS INITIAL GOAL
 * 
 * 
 * Things to check in arguments
 * 
 * default height and width: 3 and 3
 * if specifying, you need both or none. Can't specify one without the other
 * height and width must be between 2 and 5 inclusive (2 ≤ height, width ≤ 5)
 * 
 * maxsteps is limit
 * - must be positive number
 * - use for loop for program up to maxsteps
 * 
 * initial and goal
 * - must contain exactly one dash, no more and no less
 * - initial and goal can contain all other printing characters including duplicates
 * -- isprint
 * - chars in initial and goal must be same (len of initial should be len of goal and should = height x width)
 * 
 * Special Cases Checks
 * - infinite loops?
 */

int main(int argc, char* argv[])
{
    char* initial;
    char* goal;
    int maxsteps, height, width;

    // start of error checking

    // must be 4 or 6 arguments in this implementation
    if (argc != 4 && argc != 6)
    {
        fprintf(stderr, "Usage: ./Nine20 [HEIGHT WIDTH] MAXSTEPS INITIAL GOAL\n");
        exit(EXIT_FAILURE);
    }

    // if 4 arguments, then height and width unspecified
    if (argc == 4)
    {
        height = 3;
        width = 3;

        // check if all chars in maxsteps are digits
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (isdigit(argv[1][i]) == 0)
            {
                fprintf(stderr, "MAXSTEPS can only contain digits\n");
                exit(EXIT_FAILURE);
            }
        }
        
        maxsteps = atoi(argv[1]);
        initial = strdup(argv[2]);
        goal = argv[3];
    }

    // if 6 arguments, then height and width have been specified
    if (argc == 6)
    {
        // check if all chars in height are digits
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (isdigit(argv[1][i]) == 0)
            {
                fprintf(stderr, "height must be a positive integer\n");
                exit(EXIT_FAILURE);
            }
        }

        height = atoi(argv[1]);

        // check if all chars in width are digits
        for (int i = 0; i < strlen(argv[2]); i++)
        {
            if (isdigit(argv[2][i]) == 0)
            {
                fprintf(stderr, "height must be a positive integer\n");
                exit(EXIT_FAILURE);
            }
        }
        width = atoi(argv[2]);

        // check if all chars in maxsteps are digits
        for (int i = 0; i < strlen(argv[3]); i++)
        {
            if (isdigit(argv[3][i]) == 0)
            {
                fprintf(stderr, "maxsteps must be a positive integer\n");
                exit(EXIT_FAILURE);
            }
        }
        maxsteps = atoi(argv[3]);
        
        initial = strdup(argv[4]);
        goal = argv[5];
    }

    errorCheck(height, width, maxsteps, initial, goal); // check out all inputs to ensure that they are in accordance to specs

    // if initial and goal are same, then just output the string
    if (strcmp(initial, goal) == 0)
    {
        printf("%s\n", initial);
        exit(EXIT_SUCCESS);
    }
    
    // create hashTable
    Table hashTable;
    unsigned long tableSize = 1024;
    hashTable = createTable(tableSize);

    int count = 0;  // keep track of nodes inputted

    // start of breadth first search algorithm
    // make a Queue
    Deque Q;
    char* orig_pos;
    createD(&Q);

    addD(&Q, strdup(initial));   // add initial to queue

    // insert first node (INITIAL, NULL, 0)
    Data* node = malloc(sizeof(Data));
    node->position = strdup(initial);
    node->from = NULL;
    node->steps = 0;

    insert(hashTable, tableSize, node);
    count++;

    free(initial);

    // while Queue is not empty
    while (!isEmptyD(&Q))
    {
        remD(&Q, &orig_pos);  // dequeue string from Queue
        Data* orig_pos_data = search(hashTable, tableSize, orig_pos);   // get data from hash table
        int N = orig_pos_data->steps; // let N be steps taken to position

        // find dash location and coordinates in string
        char* dash = strchr(orig_pos, '-');
        int dash_index = dash - orig_pos;
        int dash_column = dash_index % width;
        int dash_row = dashRow(dash_index, width, height);

        char* up = moveUp(orig_pos, dash_index, dash_row, dash_column, height, width);
        char* down = moveDown(orig_pos, dash_index, dash_row, dash_column, height, width);
        char* left = moveLeft(orig_pos, dash_index, dash_row, dash_column, height, width);
        char* right = moveRight(orig_pos, dash_index, dash_row, dash_column, height, width);


        // put all moves into an array for easier parsing
        char* moves[4];
        moves[0] = up;
        moves[1] = down;
        moves[2] = left;
        moves[3] = right;

        if (N < maxsteps)
        {
            // go through all possible moves
            for (int i = 0; i < 4; i++)
            {
                // found goal
                if (strcmp(moves[i], goal) == 0)
                {
                    Data* from = search(hashTable, tableSize, orig_pos);

                    if (from == NULL)   {   break;  }

                    printRecursion(hashTable, tableSize, from);
                    printf("%s\n", moves[i]);

                    exit(EXIT_SUCCESS);
                }

                // else if current position is not in the hash table
                else if (search(hashTable, tableSize, moves[i]) == NULL)
                {
                    if (count / tableSize > LOAD_MAX)
                    {
                        hashTable = tableResize(hashTable, tableSize, tableSize * LOAD_MAX);
                        tableSize *= LOAD_MAX;
                    }

                    Data* triple = malloc(sizeof(Data));
                    triple->position = strdup(moves[i]);
                    triple->from = strdup(orig_pos);
                    triple->steps = N + 1;

                    insert(hashTable, tableSize, triple);    // insert new position into hash table
                    count++;    // increment count of nodes
                    addD(&Q, strdup(moves[i])); // add new position to Queue
                    free(moves[i]);
                }
                
                // free if not original string
                else if (strcmp(moves[i], orig_pos) != 0)
                {
                    free(moves[i]);
                }
            }
            free(orig_pos);
        }
    }

    tableDestroy(hashTable, tableSize); // destroy table
    destroyD(&Q);   // destroy Q

    exit(EXIT_SUCCESS);
}


char* moveUp(char* orig, int dash_index, int dash_row, int dash_column, int height, int width)
{
    if (dash_row - 1 < 0)
    {
        return orig;
    }

    int switch_char_index =  ((dash_row - 1) * width) + dash_column;
    char* switched = strdup(orig);
    swap(switched, dash_index, switch_char_index);

    return switched;
}

char* moveDown(char* orig, int dash_index, int dash_row, int dash_column, int height, int width)
{
    if (dash_row + 1 >= height)
    {
        return orig;
    }

    int switch_char_index =  ((dash_row + 1) * width) + dash_column;
    char* switched = strdup(orig);
    swap(switched, dash_index, switch_char_index);

    return switched;
}

char* moveLeft(char* orig, int dash_index, int dash_row, int dash_column, int height, int width)
{
    if (dash_column - 1 < 0)
    {
        return orig;
    }

    int switch_char_index =  (dash_row * width) + dash_column - 1;
    char* switched = strdup(orig);
    swap(switched, dash_index, switch_char_index);

    return switched;
}

char* moveRight(char* orig, int dash_index, int dash_row, int dash_column, int height, int width)
{
    if (dash_column + 1 >= width)
    {
        return orig;
    }

    int switch_char_index =  (dash_row * width) + dash_column + 1;
    char* switched = strdup(orig);
    swap(switched, dash_index, switch_char_index);

    return switched;
}

void swap(char* orig, int dash, int swap_index)
{
    char temp = orig[swap_index];
    orig[swap_index] = orig[dash];
    orig[dash] = temp;
}

void printRecursion(Table table, long size, Data* triple)
{
    if (triple->from == NULL)
    {
        printf("%s\n", triple->position);
        return;
    }

    printRecursion(table, size, search(table, size, triple->from));
    printf("%s\n", triple->position);
}

int dashRow(int dash, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        if (width * (i + 1) > dash)
        {
            return i;
        }
    }

    return dash;
}
