#ifndef LOGGING
#define LOGGING

#include "../unity/util.h"
#include "../reading/data.h"

#define LOG_RATE 50
#define MIN_FREE_SPACE 20

void
logging(FILE *fp, SensorData *sensor_data);

void
add_to_buffer(ReadBuffer *read_buffer, SensorData *result, LogBuffer *logging_buffer);

void
copy_sensor_data(SensorData *src, SensorData *des);

#endif
