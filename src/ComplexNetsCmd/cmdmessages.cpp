// This toolbox is licensed under the Academic Free License 3.0.
// Instituto Tecnológico de Buenos Aires (ITBA).
// Last modification: December 19th, 2012.

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
void errorMessage(const char *message)
{
    fprintf(stderr, "ERROR: ");
    fprintf(stderr, "%s", message);
    fprintf(stderr, "\n");
}

/**
 * Prints an error message in the standard error output and a usage message.
 */
void usageErrorMessage(const char *message)
{
    fprintf(stderr, "ERROR: ");
    fprintf(stderr, "%s", message);
    fprintf(stderr, "\nType 'complexnets --help' to see the available options.\n");
}