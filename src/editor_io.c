
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "exc.h"

/**
 * @brief Opens a file and updates the editor config with the contents of the
 *  file.
 * @param filename The file to read from.
 */
void editorOpen(char *filename)
{

  FILE *file_ptr = fopen(filename, "r");
  if (!file_ptr)
    die("fopen");

  char *line = NULL;

  size_t line_cap = 0;
  ssize_t line_len;

  // `getline` reads in a line, allocates as much memory is needed to `line`
  // and updates `line_cap` with the amount of memory that was allocated.
  // `file_ptr` here is what we're using as the `stdin`.
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
