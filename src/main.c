/* WIN32
cl -I./include -I./lib .\src\main.c .\src\mowi\mowi.c .\src\mowi\window.c .\src\mowi\input.c .\src\mowi\renderer.c .\src\mowi\widget.c .\src\common\color.c .\src\common\print.c .\src\mowi\widgets\text.c .\src\mowi\widgets\rect.c .\src\mowi\widgets\half-rect.c .\src\mowi\widgets\action-button.c .\src\mowi\widgets\toggle-button.c .\src\mowi\widgets\list-box.c .\src\mowi\widgets\radial-box.c .\src\mowi\widgets\slider.c .\src\mowi\widgets\text-box.c /link opengl32.lib gdi32.lib user32.lib
*/

/* APPLE
clang -I./include -I./lib ./src/main.c ./src/mowi/mowi.c ./src/mowi/window.c ./src/mowi/input.c ./src/mowi/window.m ./src/mowi/renderer.c ./src/common/color.c ./src/common/print.c -framework Cocoa -o mowi*/

#include  <stdio.h>

#include "mowi/mowi.h"

int main(void) {
    mowi_create();
}
