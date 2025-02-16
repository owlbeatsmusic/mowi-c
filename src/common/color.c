
#include "common/color.h"

const Color WHITE       = { 255, 255, 255 };
const Color FADED_WHITE = { 70,  70,  70  };
const Color BLACK       = { 0,   0,   0   };
const Color FADED_BLACK = { 30,  30,  30  };
const Color RED         = { 255, 30,  30  };
const Color FADED_RED   = { 70,  0,   0,  };
const Color GREEN       = { 30,  255, 30  };
const Color FADED_GREEN = { 0,   70,  70  };
const Color BLUE        = { 100, 100, 255 };
const Color FADED_BLUE  = { 0,   0,   70  };

// set to value in mowi_create()
Color default_fg_color;
Color default_fg_faded_color;
Color default_bg_color;
Color default_bg_faded_color;
Color default_pop_color;
Color default_pop_faded_color;