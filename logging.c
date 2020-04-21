#include "logging.h"
#include "util.h"

void
logging(FILE *fp, SensorData *sensor_data)
{
  switch (sensor_data->sensor_type) {
    case 3:
      fprintf(fp, "[GYR] ");
      break;
    case 1:
      fprintf(fp, "[ACC] ");
      break;
    case 2:
      fprintf(fp, "[MAG] ");
      break;
    default:
      fprintf(fp, "[Tru]: ");
  }

  if (sensor_data->sensor_type != 0){
    switch (sensor_data->driver_library) {
      case 3:
        fprintf(fp, "[BSH]: ");
        break;
      case 1:
        fprintf(fp, "[LSM]: ");
        break;
      default:
        fprintf(fp, "[NXP]: ");
    }
  }

  fprintf(fp, "x: %lf\t", sensor_data->x);
  fprintf(fp, "y: %lf\t", sensor_data->y);
  fprintf(fp, "z: %lf\t", sensor_data->z);

  fprintf(fp, "time: %u\n", sensor_data->time);
}

void
add_to_buffer(ReadBuffer *read_buffer, SensorData *result, LogBuffer *logging_buffer)
{
  int i;
  int next;

  for(i = 0; i < read_buffer->num; i++){
    next = (logging_buffer->logged + logging_buffer->size)%LOGGING_BUFFER_SIZE;
    copy_sensor_data(&read_buffer->sensor_data[i], &logging_buffer->sensor_data[next]);
    logging_buffer->size++;
  }

  next = (logging_buffer->logged + logging_buffer->size)%LOGGING_BUFFER_SIZE;
  copy_sensor_data(result, &logging_buffer->sensor_data[next]);
  logging_buffer->size++;
}

void
copy_sensor_data(SensorData *src, SensorData *des){
  des->x = src->x;
  des->y = src->y;
  des->z = src->z;
  des->time = src->time;
  des->sensor_type = src->sensor_type;
  des->driver_library = src->driver_library;
}
