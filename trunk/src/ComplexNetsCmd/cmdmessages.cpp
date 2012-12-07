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
void errorMessage(const char *message) {
	fprintf(stderr, "ERROR: ");
 	fprintf(stderr, "%s", message);
 	fprintf(stderr, "\n");
}

/**
 * Prints an error message in the standard error output and a usage message.
 */
void usageErrorMessage(const char *message) {
	fprintf(stderr, "ERROR: ");
 	fprintf(stderr, "%s", message);
 	fprintf(stderr, "\nType 'complexnets --help' to see the available options.\n");
}