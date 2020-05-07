/*
 * Name: Mahdeen (Neo) Khan
 * NetID: msk74
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "error.h"

void errorCheck(int height, int width, int maxsteps, char* initial, char* goal)
{
    // if maxsteps isn't a positive integer, print error
    if (maxsteps < 0)
    {
        fprintf(stderr, "MAXSTEPS must be a positive integer\n");
        exit(EXIT_FAILURE);
    }

    // if height and width are not within range of 2 to 5, then print error
    if (height < 2 || height > 5 || width < 2 || width > 5)
    {
        fprintf(stderr, "Height and width must be in the range of 2 to 5\n");
        exit(EXIT_FAILURE);
    }

    // make sure that intial and goal are same length
    if (strlen(initial) != strlen(goal))
    {
        fprintf(stderr, "Initial and Goal strings must be of equal length\n");
        exit(EXIT_FAILURE);
    }

    // make sure that intial and goal are within confines of width and height
    if (strlen(initial) != width * height || strlen(goal) != width * height)
    {
        fprintf(stderr, "Initial and Goal strings must be equal to width * height\n");
        exit(EXIT_FAILURE);
    }

    // check for dash in initial 
    char* first_init_dash = strchr(initial, '-');
    char* last_init_dash = strrchr(initial, '-');

    // if there are multiple or no dashes in the initial string
    if (initial - first_init_dash != initial - last_init_dash || first_init_dash == NULL)
    {
        fprintf(stderr, "There must be one dash in initial and goal\n");
        exit(EXIT_FAILURE);
    }

    // check for dash in goal
    char* first_goal_dash = strchr(goal, '-');
    char* last_goal_dash = strrchr(goal, '-');

    // if there are multiple or no dashes in the goal string
    if (goal - first_goal_dash != goal - last_goal_dash || first_goal_dash == NULL)
    {
        fprintf(stderr, "There must be one dash in initial and goal\n");
        exit(EXIT_FAILURE);
    }

    // make array of chars and array of occurrences of each char in initial to compare to goal
    long n = strlen(initial);
    char initial_chars[n];
    int initial_char_num[n];

    // initialize arrays
    for (int k = 0; k < n; k++)
    {
        initial_chars[k] = '\0';
        initial_char_num[k] = 0;
    }

    // loop through initial if chars are printable and store into arrays
    for (int i = 0; i < n; i++)
    {
        // check if everything is printable in input
        if (!isprint(initial[i]))
        {
            fprintf(stderr, "Nonprintable character in initial string\n");
            exit(EXIT_FAILURE);
        }

        // loop through initial_chars array to put in initial char
        for (int j = 0; j < n; j++)
        {
            // found duplicate, update arrays
            if (initial_chars[j] == initial[i])
            {
                initial_char_num[j] += 1;
                break;
            }

            // if reached null space, update arrays
            else if (initial_chars[j] == '\0')
            {
                initial_chars[j] = initial[i];
                initial_char_num[j] += 1;
                break;
            }
        }
    }

    // loop through goal to see if chars are printable and same as initial
    for (int i = 0; i < n; i++)
    {
        // check if everything is printable in input
        if (!isprint(goal[i]))
        {
            fprintf(stderr, "Nonprintable character in goal string\n");
            exit(EXIT_FAILURE);
        }

        // loop through initial_chars array to compare to goal chars
        for (int j = 0; j < n; j++)
        {
            if (initial_chars[j] == goal[i])
            {
                initial_char_num[j] -= 1;

                // more of one char in goal than in initial
                if (initial_char_num[j] < 0)
                {
                    fprintf(stderr, "Character in goal string not in initial string\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    // go back to see that all chars in initial are present in goal
    for (int i = 0; i < n; i++)
    {
        // char in initial not in goal
        if (initial_char_num[i] != 0)
        {
            fprintf(stderr, "Character in initial string not in goal string\n");
            exit(EXIT_FAILURE);
        }
    }

    // end of error checking
}
