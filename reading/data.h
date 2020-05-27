#ifndef SENSOR_DATA_TYPE
#define SENSOR_DATA_TYPE
#include "../unity/util.h"

/*
 *  Object: SensorData
 *
 *  Params:
 *    - x: x axis value of hw sensor read
 *    - y: y axis value of hw sensor read
 *    - z: z axis value of hw sensor read
 *    - time: epoch time (ms since epoch)
 *    - sensor_type: acc, gyr or mag type
 *
 *  Description:
 *    This object contains information for logging and calculation
 */

typedef struct SensorData {
  double x;
  double y;
  double z;
	unsigned int time;
  unsigned int valid;
  struct timespec system_time;
  SensorType sensor_type;
  DriverLibrary driver_library;
} SensorData;

/*
 *  Object: ReadBuffer
 *
 *  Params:
 *    - i: number of data read
 *    - sensor_data: array of SensorData from one read
 *
 *  Description:
 *    This object contains all the data from one read
 */

typedef struct ReadBuffer {
	int num;
	SensorData sensor_data[18];
} ReadBuffer;

#define NUM_OF_SENSOR_TYPE 3
#define NUM_OF_TYPE 3

typedef struct DisplayBuffer {
  int valid;
  double num_read;
  double x;
  double y;
  double z;
  SensorType sensor_type;
  DriverLibrary driver_library;
} DisplayBuffer;

/*
 *  Object: LogBuffer
 *
 *  Params:
 *    - logged: the start of sensor_data array, entry point for logging
 *    - size: the size of the sensor_data array
 *    - capacity: the capacity of the sensor_data array
 *    - sensor_data: array of SensorData for logging
 *
 *  Description:
 *    This object is an sensor_data array object used for logging function
 */

#define LOGGING_BUFFER_SIZE 1000

/* capacity of the LogBuffer */

typedef struct LogBuffer {
	int logged;
	int size;
	int capacity;
	SensorData sensor_data[LOGGING_BUFFER_SIZE];
} LogBuffer;

#endif
