#include "average.h"
#include "../unity/util.h"

int display_buffer_len = NUM_OF_TYPE * NUM_OF_SENSOR_TYPE;

int
get_index(int type, int sensor_type)
{
  return type%NUM_OF_TYPE*3 + sensor_type%NUM_OF_SENSOR_TYPE;
}

void
average(SensorData *result, DisplayBuffer *display_buffer, ReadBuffer *read_buffer)
{
  int i;
  double avgx;
  double avgy;
  double avgz;

  DriverLibrary type;
  SensorType sensor_type;
  int index;
  int valid_read = 0;

  for(i = 0; i < read_buffer->num; i++){

//result
    if(read_buffer->sensor_data[i].valid == 1){
      avgx += read_buffer->sensor_data[i].x;
      avgy += read_buffer->sensor_data[i].y;
      avgz += read_buffer->sensor_data[i].z;
      valid_read++;
    }
    else {
      avgx += 0;
      avgy += 0;
      avgz += 0;
    }

//display_buffer
      type = read_buffer->sensor_data[i].driver_library;
      sensor_type = read_buffer->sensor_data[i].sensor_type;
      index = get_index((int)type, (int)sensor_type);

      display_buffer[index].valid = 1;
      if(read_buffer->sensor_data[i].valid == 1){
      display_buffer[index].num_read++;
      display_buffer[index].x += read_buffer->sensor_data[i].x;
      display_buffer[index].y += read_buffer->sensor_data[i].y;
      display_buffer[index].z += read_buffer->sensor_data[i].z;
    }
    else {
      display_buffer[index].x += 0;
      display_buffer[index].y += 0;
      display_buffer[index].z += 0;
    }
  }

  result->x = 0;
  result->y = 0;
  result->z = 0;
//result
  if(valid_read > 0) {
    result->x = avgx / (double) (valid_read);
    result->y = avgy / (double) (valid_read);
    result->z = avgz / (double) (valid_read);
    result->sensor_type = Tru;
    result->valid = 1;
  }
  else{
    result->sensor_type = Tru;
    result->valid = 0;
  }

//display_buffer
  for(i = 0; i < display_buffer_len; i++){
    if(display_buffer[i].num_read > 0){
      display_buffer[i].x = display_buffer[i].x / (double) display_buffer[i].num_read;
      display_buffer[i].y = display_buffer[i].y / (double) display_buffer[i].num_read;
      display_buffer[i].z = display_buffer[i].z / (double) display_buffer[i].num_read;
    }
  }

  return;


}
