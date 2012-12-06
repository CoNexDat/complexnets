/*
 * cmdmessages.h
 * 
 * Functions that displays messages to the user related with the command line
 * options.
 */

/**
 * Prints an error message in the standard error output.
 * It automatically includes a message to tell the user how to read the help
 * of the program.
 */
void errorMessage(const char *message);