#include <stdlib.h>
#include <string.h>
#include "dyn_str.h"

#define ABUF_INIT {NULL, 0};

/**
 * @brief Appends a string to a string. This is done by increasing the size of
 * the buffer, and copying the new contents to the now increased buffer.
 * @param abuf ABuf struct for containing the string.
 * @param c_len Length of the new string.
 * @return `void`
 */
void abufAppend(struct ABuf *abuf, const char *s, int c_len)
{
  char *new = realloc(abuf->buf, abuf->len + c_len);

  if (new == NULL)
    return;
  memcpy(&new[abuf->len], s, c_len);
  abuf->buf = new;
  abuf->len += c_len;
}

/**
 * @brief Frees buffer memory.
 * @param abuf An `ABuf` struct representing a dynamically sized stirng.
 * @return `void`
 */
void abufFree(struct ABuf *abuf)
{
  free(abuf->buf);
}
