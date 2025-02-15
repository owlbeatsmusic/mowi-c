/*
cl -I./include -I./lib .\src\main.c .\src\mowi\mowi.c .\src\mowi\window.c .\src\common\color.c /link opengl32.lib gdi32.lib user32.lib
*/

#include  <stdio.h>

#include "mowi/mowi.h"

int main(void) {
    mowi_create();
}
