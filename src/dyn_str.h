
#ifndef _DYN_STRING_H
#define _DYN_STRING_H

/**
 * @brief A struct to help keep a track of a dynamically sized string.
 */
struct ABuf
{
  char *buf;
  int len;
};

void abAppend(struct ABuf *abuf, const char *s, int c_len);

#endif