#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "exc.h"

#define CTRL_KEY(k) ((k) & 0x1f)

/**
 * @brief Reads and returns a key from stdin.
 * @return The key entered in the terminal (stdin).
 */
char editorReadKey()
{
  int nread;
  char c;
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1)
  {
    if (nread == -1 && errno != EAGAIN)
      die("read");
  }
  return c;
}

/**
 * @brief Main logic on what to do when a user presses a key.
 * @return void
 */
void editorProcessKeypress()
{
  char c = editorReadKey();

  switch (c)
  {
  case CTRL_KEY('q'):
    write(STDERR_FILENO, "\x1b[2J", 4);
    write(STDERR_FILENO, "\x1b[H", 3);
    exit(0);
  default:
    if (iscntrl(c))
    {
      // printf("%d\r\n", c);
    }
    else
    {
      printf("%d ('%c')\r\n", c, c);
    }
  }
}
