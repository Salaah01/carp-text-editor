#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "config.h"
#include "exc.h"
#include "dyn_str.h"
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

  if (c == '\x1b')
  {
    char seq[3];

    if (read(STDIN_FILENO, &seq[0], 1) != 1)
      return '\x1b';
    if (read(STDIN_FILENO, &seq[1], 1) != 1)
      return '\x1b';

    if (seq[0] == '[')
    {
      switch (seq[1])
      {
      case 'A':
        return 'w';
      case 'B':
        return 's';
      case 'C':
        return 'd';
      case 'D':
        return 'a';
      }
    }

    return '\x1b';
  }
  else
  {
    return c;
  }
}

void editorMoveCursor(char key)
{
  switch (key)
  {
  case 'a':
    editorConfig.cursor_x--;
    break;
  case 'd':
    editorConfig.cursor_x++;
    break;
  case 'w':
    editorConfig.cursor_y--;
    break;
  case 's':
    editorConfig.cursor_y++;
    break;
  }
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
    break;

  case 'w':
  case 'a':
  case 's':
  case 'd':
    editorMoveCursor(c);
    break;
  }
}
