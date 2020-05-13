#include "util.h"
#include "data.h"
#include "read_data.h"
#include "runtime.h"
#include "average.h"
#include "logging.h"
#include "display.h"
#include "check_connection.h"

#ifdef TESTING
#include "./tests/testing.h"
#endif

static int sensor_count = 0;            //this variable keep track on how many set of sensor data was read

static int sensor_total = 6;      			//total sensors that we are reading from

static int connection = 1;              //this variable keep track on connection

static LogBuffer *logging_buffer;       //buffer for logging to make sure all data passed in calculate were logged

pthread_t thread_RCD;                   //thread for read, calculate and display
pthread_t thread_log;                   //thread for logging
pthread_t thread_con;                   //thread for checking connection to the sensors

pthread_mutex_t mutex_logging_buffer;   //mutex to make sure only one thread accessing logging_buffer at a time

void *
thread_read_cal_dis(void *arg);         //worker function for thread_RCD

void *
thread_logging(void *arg);              //worker function for thread_log

void *
thread_check_connection(void *arg);     //worker function for thread_con

void
init_logging_buffer();                  //function for alloc memory for logging buffer, set it's logged(start point), size to 0, set capacity


int
main(int argc, char const *argv[])
{

  int ret;                  //check if the pthread_create success

  init_logging_buffer();    //alloc memory for logging buffer, set it's logged(start point), size to 0, capacity

  pthread_mutex_init(&mutex_logging_buffer, NULL);                      //init mutex

  ret = pthread_create(&thread_RCD, NULL, thread_read_cal_dis, NULL);   //launch thread_RCD

  if(ret != 0){                                                         //make sure thread_RCD launch sucessfully
    printf("Fail to create the RCD thread\n");
    exit(EXIT_FAILURE);
  }

  ret = pthread_create(&thread_log, NULL, thread_logging, NULL);        //launch thread_log

  if(ret != 0){                                                         //make sure thread_log launch sucessfully
    printf("Fail to create logging thread\n");
    exit(EXIT_FAILURE);
  }

  ret = pthread_create(&thread_con, NULL, thread_check_connection, NULL);        //launch thread_con

  if(ret != 0){                                                         //make sure thread_con launch sucessfully
    printf("Fail to create connection checking thread\n");
    exit(EXIT_FAILURE);
  }

  pthread_join(thread_con, NULL);              //join thread_con, close thread_con
  if(connection == 0)
    printf("Connection lost. Terminating program...\n");

  pthread_join(thread_RCD, NULL);                   //join thread_RCD, close thread_RCD
  pthread_join(thread_log, NULL);                   //join thread_log, close thread_log
  pthread_mutex_destroy(&mutex_logging_buffer);     //destroy mutex

  free(logging_buffer);                             //free memory alloc by logging_buffer

  return 0;
}

/*
 *  Function: thread_read_cal_dis
 *
 *  Params:
 *    -None
 *
 *  Description:
 *    Read data from the sensors, calculate the average cords for each
 *    sensors type (fix!!!!! need to averaging for each type of sensors),
 *    display the result from the calculate function and add a copy to
 *    the logging_buffer for logging function
 *
 */
void *
thread_read_cal_dis(void *arg)
{
    SensorConfig *sensor_readings = NULL;                     //pointer points to the sensor data array read from the read_sensors function
    ReadBuffer *read_buffer = malloc(sizeof(ReadBuffer));     //pointer points to the ReadBuffer with contains all the sensor data set

	  SensorData *result = malloc(sizeof(SensorData));          //pointer points to the result from calculate function (fix!!!! need to be an array)

    DisplayBuffer *display_buffer = malloc(NUM_OF_SENSOR_TYPE*NUM_OF_TYPE*sizeof(DisplayBuffer));

    init_displaybuffer(display_buffer);

    while(1){
      if(connection == 0){
        free(result);                                            //free memory
        free(read_buffer);

        pthread_exit(EXIT_SUCCESS);
      }


      if(logging_buffer->capacity - logging_buffer->size <= MIN_FREE_SPACE){    //make sure this thread will not overflow the logging_buffer, call yield to
                                                                                //let the logging thread clear more space for logging_buffer
        sched_yield();

      }

      start_time();
                                              //start counting runtime, unit: 10^-6s
#ifndef TESTING
      sensor_readings = read_sensors(&sensor_count);         //read from the api, store the result to sensor_readings array
#endif

#ifdef TESTING
      sensor_readings =testing_cases_generator(&sensor_count);
#endif

      GetData(sensor_count, sensor_readings, read_buffer);   //grab the x, y, z, time and sensor_type from the sensor_readings and store them to read_buffer

      free(sensor_readings);                                 //free the memory allocated when calling the read_sensors function (need to be change when we have the actual api)

      reset_displaybuffer(display_buffer);

      average(result, display_buffer, read_buffer);          //averaging each cords for each type of sensors and store them to result(fix!!! need to averaging for each type of sensors)

#ifndef TESTING
      display(result, display_buffer, 1);                       //display the result (fix!!! need to display for each type of sensors)
#endif

#ifdef TESTING
      display(result, display_buffer, 0);                       //display the result (fix!!! need to display for each type of sensors)
#endif

      pthread_mutex_lock(&mutex_logging_buffer);             //lock the logging_buffer so the logging thread won't be able to access it

      add_to_buffer(read_buffer, result, logging_buffer);    //add a copy to the logging_buffer for logging

      pthread_mutex_unlock(&mutex_logging_buffer);           //unlock the mutex

    }

    free(result);                                            //free memory
    free(read_buffer);
    free(display_buffer);

    pthread_exit(EXIT_SUCCESS);                              //exit
}

/*
 *  Function: thread_logging
 *
 *  Params:
 *    -None
 *
 *  Description:
 *    Log the data set from the read function and result to a text
 *    file call log.txt
 */
void *
thread_logging(void *arg)
{
  int i;
  static FILE *fp;                                            //init the file pointer and open it

  fp = fopen("log.txt", "a");
  fprintf(fp, "\n\n");

  while(1){

    if (connection == 0) {
      fclose(fp);                                                 //close the file pointer
      pthread_exit(EXIT_SUCCESS);
    }

    pthread_mutex_lock(&mutex_logging_buffer);                //lock the logging_buffer so the RCD thread won't be able to access it

    for(i = 0; i < LOG_RATE; i++){                            //log LOG_RATE sets of data in to log.txt
      if(logging_buffer->size <= 0)                           //if all data in buffer is logged, break out of loop and let the RCD thread run
        break;
      logging(fp, &logging_buffer->sensor_data[logging_buffer->logged]);        //logged one set of data in the logging_buffer to the log.txt
      logging_buffer->logged++;                                                 //increase the entry point for next log
      logging_buffer->size--;                                                   //decrease the size of the buffer
      if(logging_buffer->logged == logging_buffer->capacity)                    //make the logging_buffer a circle array, head to tail to head
        logging_buffer->logged = 0;
    }

    pthread_mutex_unlock(&mutex_logging_buffer);              //unlock the mutex

  }

  fclose(fp);                                                 //close the file pointer
  pthread_exit(EXIT_SUCCESS);                                 //exit
}

/*
 *  Function: thread_check_connection
 *
 *  Params:
 *    -None
 *
 *  Description:
 *    Check the connection with sensors by checking if the sensor_count
 *    is updated, if the sensor_count stays 0 for the MAX_LOST_DURATION_IN_SEC
 *    defined in check_connection.h, the program will exit
 */
void *
thread_check_connection(void *arg)
{
  if(check_connection(sensor_count)){                         //check connection
    connection = 0;
  }
  pthread_exit(EXIT_SUCCESS);                                 //exit
}


/*
 *  Function: init_logging_buffer
 *
 *  Params:
 *    -None
 *
 *  Description:
 *    Alloc memory for logging_buffer, set logged, size and capacity
 */
void
init_logging_buffer()
{
  logging_buffer = malloc(sizeof(LogBuffer));

  logging_buffer->logged = 0;

  logging_buffer->size = 0;

  logging_buffer->capacity = LOGGING_BUFFER_SIZE;

  return;
}
