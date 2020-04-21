// typedef enum DriverLibrary {
// 	BSH = 0,
// 	LSM = 1,
// 	NXP = 2
// } DriverLibrary;
//
// typedef enum SensorType {
// 	Gyr = 0,
// 	Acc = 1,
// 	Mag = 2
// } SensorType;

typedef struct SensorData {
  double x;
  double y;
  double z;
  unsigned int time;
  int sensor_type;
  int driver_library;
} SensorData;
