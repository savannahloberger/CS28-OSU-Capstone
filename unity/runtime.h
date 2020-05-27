#ifndef RUNTIME
#define RUNTIME

#include "../unity/util.h"

static struct timeval st, et;

void
start_time();

unsigned int
get_runtime();

#endif
