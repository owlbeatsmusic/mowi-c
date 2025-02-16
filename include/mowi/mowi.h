#ifndef MOWI_H_
#define MOWI_H_

#include "common/color.h"

#define SCREEN_COLUMNS 111
#define SCREEN_ROWS 36

typedef struct {
    char symbol;
    Color color;
} Pixel;

extern Pixel screen_grid[SCREEN_ROWS][SCREEN_COLUMNS];

void mowi_set_pixel(int x, int y, char symbol, Color color);   
void mowi_redraw_tick(void);
void mowi_tick(void);
void mowi_create(void);

#endif
