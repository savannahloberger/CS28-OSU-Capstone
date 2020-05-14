#include "testing.h"

//black box testing
int case_num = 0;
int total_cases = 3;

SensorConfig *
testing_cases_generator(int *count)
{

  if (case_num == total_cases){

    printf("\n");
    printf("----------------------------------\n");
    printf("End of testing. Waiting for logging to complete.\n");
    printf("----------------------------------\n");
    sleep(2);
    exit(EXIT_SUCCESS);
  }

  int num_of_read;
  int i;
  SensorConfig *sensor_readings;

  srand(time(NULL));

// case one : checking if only the valid read is used
//            return 10 read with 8 valid data and 2 unvalid data

  if (case_num == 0) {
    printf("\n");
    printf("----------------------------------\n");
    printf("Test case 1, checking if only the valid read is used.\n");

    *count = 10;

    sensor_readings = malloc(10 * sizeof(SensorConfig));

    for(i = 0; i < 8; i++){
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

    for(i = 8; i < 10; i++){
      sensor_readings[i].command = rand()%3+1;
      sensor_readings[i].valid = 0;
      sensor_readings[i].index = 0;
      sensor_readings[i].addr = 0;
      sensor_readings[i].fd = 0;
      sensor_readings[i].sensor_type = i%3+1;
      sensor_readings[i].driver_library = (i%9)/3+1;
      sensor_readings[i].x_offset = 0;
      sensor_readings[i].y_offset = 0;
      sensor_readings[i].z_offset = 0;
    }

    for(i = 0; i < 8; i++){
      sensor_readings[i].last_read.x = 10;
      sensor_readings[i].last_read.y = 10;
      sensor_readings[i].last_read.z = 10;
      clock_gettime(CLOCK_REALTIME, &(sensor_readings[i].last_read.time));
    }

    for(i = 8; i < 10; i++){
      sensor_readings[i].last_read.x = -10;
      sensor_readings[i].last_read.y = -10;
      sensor_readings[i].last_read.z = -10;
      clock_gettime(CLOCK_REALTIME, &(sensor_readings[i].last_read.time));
    }

    printf("The average should be all 10 for x,y,z\n");
    printf("----------------------------------\n");
    printf("\n");
  }

  if (case_num == 1) {
    printf("\n");
    printf("----------------------------------\n");
    printf("Test case 2, checking if the result is correct with all valid data.\n");

    *count = 15;

    sensor_readings = malloc(15 * sizeof(SensorConfig));

    for(i = 0; i < 15; i++){
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

    for(i = 0; i < 15; i++){
      sensor_readings[i].last_read.x = 10;
      sensor_readings[i].last_read.y = 10;
      sensor_readings[i].last_read.z = 10;
      clock_gettime(CLOCK_REALTIME, &(sensor_readings[i].last_read.time));
    }

    printf("All result and the overall average should be all 10 for x,y,z\n");
    printf("----------------------------------\n");
    printf("\n");
  }

  if (case_num == 2) {
    printf("\n");
    printf("----------------------------------\n");
    printf("Test case 3, passing all invalid data.\n");

    *count = 15;

    sensor_readings = malloc(15 * sizeof(SensorConfig));

    for(i = 0; i < 15; i++){
      sensor_readings[i].command = rand()%3+1;
      sensor_readings[i].valid = 0;
      sensor_readings[i].index = 0;
      sensor_readings[i].addr = 0;
      sensor_readings[i].fd = 0;
      sensor_readings[i].sensor_type = i%3+1;
      sensor_readings[i].driver_library = (i%9)/3+1;
      sensor_readings[i].x_offset = 0;
      sensor_readings[i].y_offset = 0;
      sensor_readings[i].z_offset = 0;
    }

    for(i = 0; i < 15; i++){
      sensor_readings[i].last_read.x = 10;
      sensor_readings[i].last_read.y = 10;
      sensor_readings[i].last_read.z = 10;
      clock_gettime(CLOCK_REALTIME, &(sensor_readings[i].last_read.time));
    }

    printf("All result and the overall average should be all 0 for x,y,z\n");
    printf("----------------------------------\n");
    printf("\n");
  }

  case_num++;
  sleep(1);
  return sensor_readings;
}
