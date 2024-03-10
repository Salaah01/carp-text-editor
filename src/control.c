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


enum EditorKey {
  ARROW_LEFT = 'a',
  ARROW_RIGHT = 'd',
  ARROW_UP = 'w',
  ARROW_DOWN = 's'
};

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
        return ARROW_UP;
      case 'B':
        return ARROW_DOWN;
      case 'C':
        return ARROW_RIGHT;
      case 'D':
        return ARROW_LEFT;
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
  case ARROW_LEFT:
    editorConfig.cursor_x--;
    break;
  case ARROW_RIGHT:
    editorConfig.cursor_x++;
    break;
  case ARROW_UP:
    editorConfig.cursor_y--;
    break;
  case ARROW_DOWN:
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

  case ARROW_UP:
  case ARROW_LEFT:
  case ARROW_RIGHT:
  case ARROW_DOWN:
    editorMoveCursor(c);
    break;
  }
}
