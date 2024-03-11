#ifndef _TERMINAL_CONFIG_H
#define _TERMINAL_CONFIG_H

#include <termios.h>
#include "dyn_str.h"

/**
 * @brief Struct to represent a row of text in the editor.
 */
typedef struct EditorRow
{
  int size;
  char *chars;
} e_row;

/**
 * @brief Contains information about the terminal configuration.
 */
struct EditorConfig
{
  int cursor_x;
  int cursor_y;
  int screen_rows;
  int screen_cols;
  int num_rows;
  e_row row;
  struct termios orig_termios;
};

int getWindowSize(int *rows, int *cols);

void initEditor();

void disableRawMode();

void enableRawMode();

extern struct EditorConfig editorConfig;

void editorDrawRows(struct ABuf *abuf);

void editorRefreshScreen();

#endif