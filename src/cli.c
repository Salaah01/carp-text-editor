
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief CLI function to check that exactly 1 argument is provided (filename)
 *  and then to return that argument.
 * @param argc Number of CLI arguments provided.
 * @param argv Array of points to the CLI arguments.
 * @returns Returns the first element from the CLI arguments.
*/

char *cli(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Invalid number of arguments\n");
    printf("Usage: ./carp-editor <filename>\n");
    exit(1);
  }

  return argv[1];
}
