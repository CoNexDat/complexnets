/*
 * cmdmessages.c
 * 
 * Functions that displays messages to the user related with the command line
 * options.
 */

 #include <stdio.h>

/**
 * Prints an error message in the standard error output.
 */
void
errorMessage(const char *message) {
	fprintf(stderr, "ERROR: ");
 	fprintf(stderr, message);
 	fprintf(stderr, "\nType 'complexnets --help' to see the available \
options.\n");
}