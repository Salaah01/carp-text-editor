// Module helps setup the terminal with the correct configuration.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "about.h"
#include "config.h"
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
    *rows = ws.ws_row;
    *cols = ws.ws_col;
    return 0;
  }
}

void initEditor()
{

  editorConfig.cursor_x = 0;
  editorConfig.cursor_y = 0;
  editorConfig.num_rows = 0;

  if (getWindowSize(&editorConfig.screen_rows, &editorConfig.screen_cols) == -1)
    die("getWindowSize");
}

void disableRawMode()
{
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &editorConfig.orig_termios) == -1)
    die("ttcsetattr");
}

void enableRawMode()
{
  if (tcgetattr(STDIN_FILENO, &editorConfig.orig_termios) == -1)
    die("ttcgetattr");

  atexit(disableRawMode);

  struct termios raw = editorConfig.orig_termios;

  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
    die("tcsetattr");
}

/**
 * @brief Displays the welcome message.
 * @param abuf String buffer
 * @param cols Number of columns on the screen.
 * @returns `void`
 */
void displayWelcomeMessage(struct ABuf *abuf, int cols)
{

  char welcome[80];
  int welcome_len = snprintf(
      welcome,
      sizeof(welcome),
      "%s -- %s",
      PROGRAM_NAME,
      PROGRAM_VERSION);

  if (welcome_len > cols)
    welcome_len = cols;

  int padding = (cols - welcome_len) / 2;

  if (padding)
  {
    abufAppend(abuf, "-", 1);
    padding--;
  }
  while (padding--)
    abufAppend(abuf, " ", 1);

  abufAppend(abuf, welcome, welcome_len);
}

void editorDrawRows(struct ABuf *abuf)
{
  for (int y = 0; y < editorConfig.screen_rows; y++)
  {
    if (y >= editorConfig.num_rows)
    {

      if (y == editorConfig.screen_rows / 3)
      {
        displayWelcomeMessage(abuf, editorConfig.screen_cols);
      }
      else
      {
        abufAppend(abuf, "~", 1);
      }
    }
    else
    {
      int len = editorConfig.row.size;
      if (len > editorConfig.screen_cols)
        len = editorConfig.screen_cols;
      abufAppend(abuf, editorConfig.row.chars, len);
    }

    abufAppend(abuf, "\x1b[K", 3); // Clears each line we draw.
    if (y < editorConfig.screen_rows - 1)
    {
      abufAppend(abuf, "\r\n", 2);
    }
  }
}
void editorRefreshScreen()
{
  struct ABuf abuf = ABUF_INIT;

  abufAppend(&abuf, "\x1b[?251", 6);
  abufAppend(&abuf, "\x1b[H", 3);

  editorDrawRows(&abuf);

  char buf[32];
  snprintf(
      buf,
      sizeof(buf),
      "\x1b[%d;%dH",
      editorConfig.cursor_y + 1,
      editorConfig.cursor_x + 1);
  abufAppend(&abuf, buf, strlen(buf));

  abufAppend(&abuf, "\x1b[?25h", 6);

  write(STDOUT_FILENO, abuf.buf, abuf.len);
  abufFree(&abuf);
}