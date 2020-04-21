#include "runtime.h"

void
start_time()
{

    gettimeofday(&st, NULL);

}

/* Return microseconds */
unsigned int
get_runtime()
{

  gettimeofday(&et, NULL);

  unsigned int elapsed = ((et.tv_sec - st.tv_sec) * 1000000) + (et.tv_usec - st.tv_usec);

  return elapsed;

}
