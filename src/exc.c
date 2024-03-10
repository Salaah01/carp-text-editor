// Module contains exception handling.

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
 * @brief function clears the screen and exists the program.
 * @param s Contains information about the error caused.
 * @returns void
 */
void die(const char *s)
{
  write(STDOUT_FILENO, "\x1b[2J", 4);
  write(STDOUT_FILENO, "\x1b[H", 3);

  perror(s);
  exit(1);
}