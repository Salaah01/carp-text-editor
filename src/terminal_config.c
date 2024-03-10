// Module helps setup the terminal with the correct configuration.

#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "terminal_config.h"
#include "exc.h"

struct EditorConfig editorConfig;

/**
 * @brief Fetches the window size of the terminal.
 * @param rows Number of rows in the terminal.
 * @param cols Number of columns in the terminal.
 */
int getWindowSize(int *rows, int *cols)
{
  struct winsize ws;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
  {
    return -1;
  }
  else
  {
    *cols = ws.ws_col;
    *rows = ws.ws_row;
    return 0;
  }
}

void initEditor()
{
  if (getWindowSize(&editorConfig.screen_rows, &editorConfig.screen_rows) == 1)
    die("getWindowSize");
}

void disableRawMode()
{
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &editorConfig.orig_termios) == -1)
    die("ttcsetatt");
}

void enableRawMode()
{
  if (tcgetattr(STDIN_FILENO, &editorConfig.orig_termios) == -1)
    die("ttcgetatt");

  atexit(disableRawMode);

  struct termios raw = editorConfig.orig_termios;

  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_lflag &= ~(ECHO | ICANON | ISIG);
  raw.c_cflag &= ~(CS8);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
    die("tcsetattr");
}
