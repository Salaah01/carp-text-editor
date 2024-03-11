
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

void editorOpen()
{
  char *line = "Hello, world!";
  ssize_t line_len = 13;

  editorConfig.row.size = line_len;
  editorConfig.row.chars = malloc(line_len + 1);
  memcpy(editorConfig.row.chars, line, line_len);
  editorConfig.row.chars[line_len] = '\0';
  editorConfig.num_rows = 1;
}
