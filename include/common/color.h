#ifndef COLOR_H_
#define COLOR_H_

#include <stdint.h>

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} Color;

extern const Color WHITE;
extern const Color FADED_WHITE;
extern const Color RED;
extern const Color FADED_RED;
extern const Color GREEN;
extern const Color FADED_GREEN;
extern const Color BLUE;
extern const Color FADED_BLUE;

#endif
