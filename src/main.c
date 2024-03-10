#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#include "cli.h"
#include "exc.h"
#include "config.h"

#define CTRL_KEY(k) ((k) & 0x1f)

struct ABuf
{
  char *buf;
  int len;
};

#define ABUF_INIT \
  {               \
    NULL, 0       \
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