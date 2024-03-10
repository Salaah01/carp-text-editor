#ifndef _TERMINAL_CONFIG_H
#define _TERMINAL_CONFIG_H

#include <termios.h>

struct EditorConfig
{
  int screen_rows;
  int screen_cols;
  struct termios orig_termios;
};

int getWindowSize(int *rows, int *cols);

void initEditor();

void disableRawMode();

void enableRawMode();

extern struct EditorConfig editorConfig;

#endif