
#include <stdlib.h>
#include <stdio.h>

// CLI function to check that exactly 1 argument is provided (filename) and
// then to return that argument.
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
