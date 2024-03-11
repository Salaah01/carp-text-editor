
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "exc.h"

void editorOpen(char *filename)
{

  FILE *file_ptr = fopen(filename, "r");
  if (!file_ptr)
    die("fopen");

  char *line = NULL;

  size_t line_cap = 0;
  ssize_t line_len;
  line_len = getline(&line, &line_cap, file_ptr);
  if (line_len != -1)
  {
    while (
        line_len > 0 && (line[line_len - 1] == '\n' || line[line_len - 1] == '\r'))
      line_len--;
  }

  editorConfig.row.size = line_len;
  editorConfig.row.chars = malloc(line_len + 1);
  memcpy(editorConfig.row.chars, line, line_len);
  editorConfig.row.chars[line_len] = '\0';
  editorConfig.num_rows = 1;

  free(line);
  fclose(file_ptr);
}
