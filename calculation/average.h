#ifndef AVERAGE
#define AVERAGE

#include "../unity/util.h"
#include "../reading/data.h"

int
get_index(int type, int sensor_type);

void
average(SensorData *result, DisplayBuffer *display_buffer, ReadBuffer *read_buffer);

#endif
