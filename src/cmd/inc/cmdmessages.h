// This toolbox is licensed under the Academic Free License 3.0.
// Instituto Tecnológico de Buenos Aires (ITBA).
// Last modification: December 19th, 2012.

/*
 * cmdmessages.h
 *
 * Functions that displays messages to the user related with the command line
 * options.
 */

/**
 * Prints an error message in the standard error output.
 */
void errorMessage(const char *message);

/**
 * Prints an error message in the standard error output.
 * It automatically includes a message to tell the user how to read the help
 * of the program.
 */
void usageErrorMessage(const char *message);