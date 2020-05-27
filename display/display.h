#ifndef DISPLAY
#define DISPLAY

#include "../unity/util.h"
#include "../reading/data.h"

void
display(SensorData *result, DisplayBuffer *display_buffer, int regex);

void
init_displaybuffer(DisplayBuffer *display_buffer);

void
reset_displaybuffer(DisplayBuffer *display_buffer);

#endif
