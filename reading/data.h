#ifndef SENSOR_DATA_TYPE
#define SENSOR_DATA_TYPE
#include "../unity/util.h"
/*
 *  Specifies the driver library to be used,
 *  important to signify the HW model of sensor.
 *  (Bosch, LSM, NXP)
 */

 typedef enum DriverLibrary {
 	BSH = 3,
 	LSM = 1,
 	NXP = 2
 } DriverLibrary;

/*
 *  Specifies the type of sensor to be:
 *  Gyroscope, Magnetometer or Accelerometer
 *	True for final result
 */

 typedef enum SensorType {
 	Gyr = 3,
 	Acc = 1,
 	Mag = 2,
	Tru = 0
 } SensorType;

 typedef enum HTCommand {
 	HTC_WAIT = 4,
  HTC_READ = 1,
 	HTC_SETUP = 2,
 	HTC_DELETE = 3
 } HTCommand;

/*
 *  Object: SensorRead
 *
 *  Params:
 *    - x: x axis value of hw sensor read
 *    - y: y axis value of hw sensor read
 *    - z: z axis value of hw sensor read
 *    - time: epoch time (ms since epoch)
 *    - sensor: reference to sensor config that
 *    		has been read
 *
 *  Description:
 *    This object contains information regarding the reading of a specific
 *    hw sensor.
 */

typedef struct SensorRead {
	double x;
	double y;
	double z;
	struct timespec time;
} SensorRead;

/*
 *  Object: SensorConfig
 *
 *  Params:
 *    - id: unique number of sensor
 *    - fd: file descriptor
 *    - addr: I2C adress
 *    - sensor_type: specifies acc, gyr or mag type
 *    - driver_library: sensor manufacturer, for driver support
 *    - x_offset: degree tilt on x axis of hw sensor (+90, -90, 0, +180)
 *    - y_offset: degree tilt on y axis of hw sensor (+90, -90, 0, +180)
 *    - z_offset: degree tilt on z axis of hw sensor (+90, -90, 0, +180)
 *
 *  Description:
 *    Specifies HW config of sensor in SW.
 */

typedef struct SensorConfig {
	HTCommand command;
	unsigned int valid;
	unsigned int index;
	unsigned int addr;
	int fd;
	SensorType sensor_type;
	DriverLibrary driver_library;
	int x_offset;
	int y_offset;
	int z_offset;
	SensorRead last_read;
} SensorConfig;

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
