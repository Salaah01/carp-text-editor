#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include "exc.h"
#include "config.h"
#include "control.h"
#include "editor_io.h"

int main(int argc, char *argv[])
{
  enableRawMode();
  initEditor();
  if (argc >= 2)
  {
    editorOpen(argv[1]);
  }

  while (1)
  {
    editorRefreshScreen();
    editorProcessKeypress();
  }

  return 0;
}