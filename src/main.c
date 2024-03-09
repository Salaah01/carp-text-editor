#include <stdio.h>
#include "cli.h"

int main(int argc, char *argv[])
{
  char *filename = cli(argc, argv);
  printf("filename is %s\n", filename);

  FILE* file_ptr;
  file_ptr = fopen(filename, "a+");
  fclose(file_ptr);
}
