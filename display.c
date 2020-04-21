#include "display.h"
#include "runtime.h"

void
init_displaybuffer(DisplayBuffer *display_buffer)
{
  int i;
  int j;
  int index = 0;

  for (i = 0; i < NUM_OF_TYPE; i++){
    for (j = 0; j < NUM_OF_SENSOR_TYPE; j++){
      display_buffer[index].valid = 0;
      display_buffer[index].num_read = 0;
      display_buffer[index].x = 0;
      display_buffer[index].y = 0;
      display_buffer[index].z = 0;
      display_buffer[index].sensor_type = i%NUM_OF_TYPE+1;
      display_buffer[index].driver_library = j%NUM_OF_SENSOR_TYPE+1;
      index++;
    }
  }
}

void
reset_displaybuffer(DisplayBuffer *display_buffer)
{
  int i;
  int j;
  int index = 0;

  for (i = 0; i < NUM_OF_TYPE; i++){
    for (j = 0; j < NUM_OF_SENSOR_TYPE; j++){
      display_buffer[index].valid = 0;
      display_buffer[index].num_read = 0;
      display_buffer[index].x = 0;
      display_buffer[index].y = 0;
      display_buffer[index].z = 0;
      index++;
    }
  }
}

void
display(SensorData *result, DisplayBuffer *display_buffer)
{
  int i;
  result->time = get_runtime();            //get the runtime, unit: 10^-6s

  // Clear screen
  printf("\e[1;1H\e[2J"); // using regex - too fast??
  // system("clear"); seg fault for some reasom??
  //
  // printf("x:%lf\t",result->x);
  // printf("y:%lf\t",result->y);
  // printf("z:%lf\t",result->z);
  // printf("time:%d\t",result->time);
  // printf("\n");

  //Header
  printf("####################################################################\n");
  printf("|Sensor		| Board	|	X	|	Y	|	Z	|\n");
  printf("\n");

  for(i = 0; i < NUM_OF_TYPE*NUM_OF_SENSOR_TYPE; i++){
    switch (display_buffer[i].sensor_type) {
      case 1:
        printf("|Accelerator 	");
        break;
      case 3:
        printf("|Gyro 		");
        break;
      default:
        printf("|Magnetometer	");
    }
    switch (display_buffer[i].driver_library) {
      case 3:
        printf("|  BSH	");
        break;
      case 1:
        printf("|  LSM	");
        break;
      default:
        printf("|  NXP	");
    }
    if(display_buffer[i].valid)
      printf("| %lf	| %lf	| %lf	|\n", display_buffer[i].x, display_buffer[i].y, display_buffer[i].z);
    else
      printf("| NA	| NA	| NA	|\n" );
  }

  // printf("|Accelerator 	|  LSM	| %lf	| %lf	| %lf	|\n", result->x, result->y, result->z);
  // printf("|Accelerator 	|  NXP	| %lf	| %lf	| %lf	|\n", result->x, result->y, result->z);
  // printf("|Gyro 		|  BSH	| %lf	| %lf	| %lf	|\n", result->x, result->y, result->z);
  // printf("|Gyro 		|  LSM	| %lf	| %lf	| %lf	|\n", result->x, result->y, result->z);
  // printf("|Gyro 		|  NXP	| %lf	| %lf	| %lf	|\n", result->x, result->y, result->z);
  // printf("|Magnetometer	|  BSH	| %lf	| %lf	| %lf	|\n", result->x, result->y, result->z);
  // printf("|Magnetometer	|  LSM	| %lf	| %lf	| %lf	|\n", result->x, result->y, result->z);
  // printf("|Magnetometer	|  NXP	| %lf	| %lf	| %lf	|\n", result->x, result->y, result->z);
  printf("\n");
  printf("| Average	|    	| %lf	| %lf	| %lf	|\n", result->x, result->y, result->z);
  //Sensor Data
  // (fix!!!!! change to reading the values from the correct sensors)
}
