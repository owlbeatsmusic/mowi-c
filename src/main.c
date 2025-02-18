/* WIN32
cl -I./include -I./lib .\src\main.c .\src\mowi\mowi.c .\src\mowi\window.c .\src\mowi\input.c .\src\mowi\widget\widget-input.c .\src\mowi\renderer.c .\src\mowi\widget\widget-renderer.c .\src\mowi\widget\widget.c .\src\common\color.c .\src\common\print.c .\src\mowi\widget\widgets\action-button.c .\src\mowi\widget\widgets\toggle-button.c /link opengl32.lib gdi32.lib user32.lib
*/

/* APPLE
clang -I./include -I./lib ./src/main.c ./src/mowi/mowi.c ./src/mowi/window.c ./src/mowi/input.c ./src/mowi/window.m ./src/mowi/renderer.c ./src/common/color.c ./src/common/print.c -framework Cocoa -o mowi*/

#include  <stdio.h>

#include "mowi/mowi.h"

int main(void) {
    mowi_create();
}
