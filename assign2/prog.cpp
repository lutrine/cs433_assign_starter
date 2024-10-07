/**
 * Assignment 2: Simple UNIX Shell
 * @file prog.cpp
 * @author Caden Jamason, Adrian Reyes
 * @brief This is the main function of a simple UNIX Shell. You may add
 * additional functions in this file for your implementation
 * @version 0.1
 */

// You must complete the all parts marked as "TODO". Delete "TODO" after you are
// done. Remember to add sufficient and clear comments to your code

#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

#define MAX_LINE 80 // The maximum length command

/**
 * @brief parse out the command and arguments from the input command separated
 * by spaces
 *
 * @param command The input command
 * @param args The array of arguments parsed from the input command
 * @return int – The number of arguments
 */
int parse_command(char command[], char *args[]) {
  // TODO: implement this function
  char *token = strtok(command, " \n"); // Scans command for first space
  int i = 0;                            // Counter for the number of arguments

  while (token != NULL) {        // While the token isn't NULL...
    args[i] = token;             // Add the token to the args array
    token = strtok(NULL, " \n"); // Scan for the next space
    i++;                         // Increment the counter
  }

  args[i] = NULL; // Set the last argument to NULL to mark end of array
  return i;       // Return the number of arguments
}

// TODO: Add additional functions if you need

/**
 * @brief The main function of a simple UNIX Shell. You may add additional
 * functions in this file for your implementation
 * @param argc The number of arguments
 * @param argv The array of arguments
 * @return The exit status of the program
 */
int main(int argc, char *argv[]) {
  char command[MAX_LINE];       // the command that was entered
  char *args[MAX_LINE / 2 + 1]; // hold parsed out command line arguments
  int should_run = 1;           /* flag to determine when to exit program */

  // TODO: Add additional variables for the implementation.
  pid_t pid; // Process ID
  char last_command[MAX_LINE]; // Store the last command entered by the user

  while (should_run) {
    printf("osh> ");
    fflush(stdout);
    // Read the input command
    fgets(command, MAX_LINE, stdin);
    // Parse the input command
    int num_args = parse_command(command, args);

    // TODO: Add your code for the implementation

    // If no arguments, continue to next iteration
    if (num_args == 0) {
      continue;
    }

    // Compare first argument to "exit" to determine if shell should exit
    if (strcmp(args[0], "exit") == 0) {
      should_run = 0;
      continue;
    }

    // Compare first argument to "!!" to execute the last command
    if (strcmp(args[0], "!!") == 0) {
      if (strlen(last_command) > 0) {
        // Execute the last command
        printf("Executing last command: %s\n", last_command);
        parse_command(last_command, args);
      } else {
        printf("No prior history.\n");
      }
      continue;
    }

    // Store the current command as the last command
    strcpy(last_command, command);

    /**
     * After reading user input, the steps are:
     * (1) fork a child process using fork()
     * (2) the child process will invoke execvp()
     * (3) parent will invoke wait() unless command included &
     */

    pid = fork();
    if (pid < 0) {
      cerr << "Fork failed" << endl; // Print an error message
      exit(EXIT_FAILURE);            // Exit the program
    } else if (pid == 0) {           // Child process
      // If the last argument is "&"...
      if (num_args > 0 && strcmp(args[num_args - 1], "&") == EXIT_SUCCESS) {
        // Remove the "&" from the arguments so it doesn't get passed to execvp
        args[num_args - 1] = NULL;
      }
      // Execute the command
      if (args[0] != nullptr && execvp(args[0], args) == EXIT_SUCCESS) {
        // If the command fails to execute, print an error message
        cerr << "Execution failed" << endl;
        return 1;
      }
    } else { // Parent process
      // If the last argument is not "&"...
      if (strcmp(args[num_args - 1], "&") != EXIT_SUCCESS) {
        // Wait for the child process to finish
        wait(NULL);
      }
    }
  }

  return 0;
}
