/*
 * errorCheck is a function that goes through the arguments passed through
 * Nine20 call to ensure that they are valid according to the following specifications:
 * 
 * - HEIGHT and WIDTH (if present) are sequences of digits
 * - HEIGHT and WIDTH (if present) are positive integers between 2 and 5
 * - MAXSTEPS is a sequence of digits
 * - INITIAL and GOAL have the correct number of characters for the tray size
 * - the characters appearing in INITIAL include precisely one -
 * - the same characters (counting multiplicities) appear in GOAL
 * and write a one-line error message to stderr and immediately exit otherwise.
 */

void errorCheck(int height, int width, int maxsteps, char* initial, char* goal);
