
// Header file entailing the additional functions made for the Nine20 puzzle

// creates a string where the dash was swapped with the element above it
// by using the equation ((dash_row - 1) * width) + dash_column to find the
// above element
char* moveUp(char* orig, int dash_index, int dash_row, int dash_column, int height, int width);

// creates a string where the dash was swapped with the element below it
// by using the equation ((dash_row + 1) * width) + dash_column to find the
// below element
char* moveDown(char* orig, int dash_index, int dash_row, int dash_column, int height, int width);

// creates a string where the dash was swapped with the element to the left it
// by using the equation (dash_row * width) + dash_column - 1 to find the
// left element
char* moveLeft(char* orig, int dash_index, int dash_row, int dash_column, int height, int width);

// creates a string where the dash was swapped with the element to the right it
// by using the equation (dash_row * width) + dash_column + 1 to find the
// right element
char* moveRight(char* orig, int dash_index, int dash_row, int dash_column, int height, int width);

// swaps the dash with another element in the string by indexing
void swap(char* orig, int dash, int swap_index);

// prints the path of strings that lead to the goal by searching for the from
// string in the hash table and using recursion to print them all out, including
// the initial string, so that they can print out in order.
void printRecursion(Table table, long size, Data* triple);

// finds the row number of the dash with a for loop since division of
// the height and the index can get undesirable numbers in certain cases
int dashRow(int dash, int width, int height);
