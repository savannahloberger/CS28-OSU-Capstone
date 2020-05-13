#ifndef DISPLAY
#define DISPLAY

#include "util.h"
#include "data.h"

void
display(SensorData *result, DisplayBuffer *display_buffer, int regex);

void
init_displaybuffer(DisplayBuffer *display_buffer);

void
reset_displaybuffer(DisplayBuffer *display_buffer);

#endif
