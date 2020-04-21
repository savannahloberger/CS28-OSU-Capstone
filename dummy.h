#ifndef DUMMY_HEADER
#define DUMMY_HEADER

#define INIT_X  0
#define INIT_Y  0
#define INIT_Z  0
#define INCREMENT 0.001
#define MOVINGING_PATTERN "RURURURURURURURU\0"  //R Y++ L Y-- U Z++ D Z-- F X-- B X++
#define ERROR_RATE 0.1
#define NUM_OF_READ 15

static double x = INIT_X;
static double y = INIT_Y;
static double z = INIT_Z;

static int i_pattern = -1;

static char pattern[] = MOVINGING_PATTERN;

static double prev_error = 0;

static int seed = 0;

double
random_error();

void
get_next_sensor_readings(SensorConfig *sensor_readings, int count);

SensorConfig *
dummy_generator(int *count);

#endif
