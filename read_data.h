#ifndef READ_DATA
#define READ_DATA

#include "data.h"

/*
 *  Function: read_sensors
 *
 *  Params:
 *    - sensor_count: int pointer that will be updated to the number of
 *                    sensors currently configured in the HW setup
 *    - sensor_readings: SensorRead array pointer populated to size
 *                    sensor_count of most recent SensorRead for each
 *                    HW sensor
 *
 *  Description:
 *    Takes in two pointer references and assigns them accordingly. Read
 *    parameter descriptions for each to see how the references are
 *    populated.
 *
 */
SensorConfig *
read_sensors(int *count);

void
GetData(int count, SensorConfig *sensor_readings, ReadBuffer* read_buffer);

#endif
