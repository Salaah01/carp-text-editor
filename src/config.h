#ifndef _TERMINAL_CONFIG_H
#define _TERMINAL_CONFIG_H

#include <termios.h>
#include "dyn_str.h"

/**
 * @brief Contains information about the terminal configuration.
 */
struct EditorConfig
{
  int cursor_x;
  int cursor_y;
  int screen_rows;
  int screen_cols;
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