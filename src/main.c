/* WIN32
cl -I./include -I./lib .\src\main.c .\src\mowi\mowi.c .\src\mowi\window.c .\src\mowi\input.c .\src\mowi\renderer.c .\src\common\color.c /link opengl32.lib gdi32.lib user32.lib
*/

/* APPLE
clang -I./include -I./lib ./src/main.c ./src/mowi/mowi.c ./src/mowi/window.c ./src/mowi/input.c ./src/mowi/renderer.c ./src/common/color.c 
*/

#include  <stdio.h>

#include "mowi/mowi.h"

int main(void) {
    mowi_create();
}
