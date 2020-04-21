#include "read_data.h"
#include "util.h"
#include "dummy.h"


SensorConfig *
read_sensors(int *count)
{
  /* dummy generator*/

  *count = 0;
  return dummy_generator(count);

}


void
GetData (int count, SensorConfig *sensor_readings, ReadBuffer* read_buffer)
{
  int i;

  if(count <= 0){
    read_buffer->num = 0;
    return;
  }

  read_buffer->num = count;

  for(i = 0; i < count; i++){
    read_buffer->sensor_data[i].x = sensor_readings[i].last_read.x;
    read_buffer->sensor_data[i].y = sensor_readings[i].last_read.y;
    read_buffer->sensor_data[i].z = sensor_readings[i].last_read.z;
    read_buffer->sensor_data[i].time = 0;
    read_buffer->sensor_data[i].system_time = sensor_readings[i].last_read.time;
    read_buffer->sensor_data[i].sensor_type = sensor_readings[i].sensor_type;
    read_buffer->sensor_data[i].driver_library = sensor_readings[i].driver_library;
  }

  return;
}
