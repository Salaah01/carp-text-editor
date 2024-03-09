#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#include "cli.h"

#define CTRL_KEY(k) ((k) & 0x1f)

struct EditorConfig
{
  int screen_rows;
  int screen_cols;
  struct termios orig_termios;
};

struct EditorConfig editorConfig;

void die(const char *s)
{
  write(STDOUT_FILENO, "\x1b[2J", 4);
  write(STDOUT_FILENO, "\x1b[H", 3);

  perror(s);
  exit(1);
}

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

void editorDrawRows()
{
  int y;
  for (y = 0; y < editorConfig.screen_rows; y++)
  {
    write(STDOUT_FILENO, "~", 1);
    if (y < editorConfig.screen_rows - 1) {
      write(STDOUT_FILENO, "\r\n", 2);
    }

  }
}
void editorRefreshScreen()
{
  write(STDOUT_FILENO, "\x1b[2J", 4);
  write(STDOUT_FILENO, "\x1b[H", 3);

  editorDrawRows();

  write(STDOUT_FILENO, "\x1b[H", 3);
}

int main(int argc, char *argv[])
{
  enableRawMode();
  initEditor();

  char *filename = cli(argc, argv);
  printf("filename is %s\r\n", filename);

  FILE *file_ptr;
  file_ptr = fopen(filename, "a+");
  fclose(file_ptr);

  while (1)
  {
    editorRefreshScreen();
    editorProcessKeypress();
  }

  return 0;
}