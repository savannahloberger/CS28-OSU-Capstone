#include "check_connection.h"


int
check_connection(int sc)
{
  struct timeval st_con, et_con;
  uint lost_timestamp;
  int lost = 0;
  int lost_duration = 0;

  while(1){
    if(sc == 0){
      if(lost == 0){
        gettimeofday(&st_con, NULL);
        lost = 1;
      }
      else {
        gettimeofday(&et_con, NULL);
        lost_duration = et_con.tv_sec - st_con.tv_sec;
        if(lost_duration >= MAX_LOST_DURATION_IN_SEC){
          return 1;
        }
      }
    }
    else{
      lost = 0;
      lost_duration = 0;
    }
  }
}
