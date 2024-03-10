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
#include "control.h"

struct ABuf
{
  char *buf;
  int len;
};

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