
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "exc.h"

/**
 * @brief Appends a row to the editor.
 * @param str The string to append.
 * @param len The size of the string.
 * @returns `void`
 */
void editorAppendRow(char *str, size_t len)
{
  editorConfig.row = realloc(editorConfig.row, sizeof(e_row) * (editorConfig.num_rows + 1));

  int at = editorConfig.num_rows;

  editorConfig.row[at].size = len;
  editorConfig.row[at].chars = malloc(len + 1);
  memcpy(editorConfig.row[at].chars, str, len);
  editorConfig.row[at].chars[len] = '\0';
  editorConfig.num_rows++;
}

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

  while ((line_len = getline(&line, &line_cap, file_ptr)) != -1)
  {

    while (
        line_len > 0 && (line[line_len - 1] == '\n' || line[line_len - 1] == '\r'))
      line_len--;

    editorAppendRow(line, line_len);
  }
  free(line);
  fclose(file_ptr);
}
