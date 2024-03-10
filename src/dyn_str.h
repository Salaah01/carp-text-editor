
#ifndef _DYN_STRING_H
#define _DYN_STRING_H

#define ABUF_INIT {NULL, 0};

/**
 * @brief A struct to help keep a track of a dynamically sized string.
 */
struct ABuf
{
  char *buf;
  int len;
};

void abufAppend(struct ABuf *abuf, const char *s, int c_len);

void abufFree(struct ABuf *abuf);

#endif