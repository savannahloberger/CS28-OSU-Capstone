#include "util.h"
#include "data.h"
#include "dummy.h"

double
random_error(){
  int coin;
  srand(seed++);
  coin = rand()%2;
  double err = (double)rand()/(double)RAND_MAX * INCREMENT * ERROR_RATE;
  while(err == prev_error){
    err = (double)rand()/(double)RAND_MAX * INCREMENT * ERROR_RATE;
  }
  prev_error = err;
  if (coin) {
    err = -err;
  }
  return err;
}

void
get_next_sensor_readings(SensorConfig *sensor_readings, int count)
{

  int i;
  int len = strlen(pattern);

  if(i_pattern == -1){
    for(i = 0; i < count; i++){
      sensor_readings[i].last_read.x = x;
      sensor_readings[i].last_read.y = y;
      sensor_readings[i].last_read.z = z;
      clock_gettime(CLOCK_REALTIME, &(sensor_readings[i].last_read.time));
    }
    i_pattern++;

    return;
  }

  if(i_pattern > len){
    i_pattern = i_pattern%len;
  }

  char drift = pattern[i_pattern];

  switch (drift) {
    case 'B':
      x += INCREMENT;
      break;
    case 'F':
      x -= INCREMENT;
      break;
    case 'R':
      y += INCREMENT;
      break;
    case 'L':
      y -= INCREMENT;
      break;
    case 'U':
      z += INCREMENT;
      break;
    default:
      z -= INCREMENT;
  }

  for(i = 0; i < count; i++){
    sensor_readings[i].last_read.x = x + random_error();
    sensor_readings[i].last_read.y = y + random_error();
    sensor_readings[i].last_read.z = z + random_error();
    clock_gettime(CLOCK_REALTIME, &(sensor_readings[i].last_read.time));
  }

  i_pattern++;
}

SensorConfig *
dummy_generator(int *count)
{

  int num_of_read;
  int i;
  SensorConfig *sensor_readings;

  srand(time(NULL));
  *count = NUM_OF_READ;

  sensor_readings = malloc(NUM_OF_READ * sizeof(SensorConfig));

  for(i = 0; i < NUM_OF_READ; i++){
    sensor_readings[i].command = rand()%3+1;
    sensor_readings[i].valid = 1;
    sensor_readings[i].index = 0;
    sensor_readings[i].addr = 0;
    sensor_readings[i].fd = 0;
    sensor_readings[i].sensor_type = i%3+1;
    sensor_readings[i].driver_library = (i%9)/3+1;
    sensor_readings[i].x_offset = 0;
    sensor_readings[i].y_offset = 0;
    sensor_readings[i].z_offset = 0;
  }

  get_next_sensor_readings(sensor_readings, *count);

  return sensor_readings;
}
