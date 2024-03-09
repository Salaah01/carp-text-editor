#include <stdio.h>

int main(int argc, char *argv[])

{
  if (argc != 2)
  {
    printf("Invalid number of arguments\n");
    printf("Usage: ./carp-editor <filename>\n");
    return 1;
  }

  char *filename = argv[1];
}
