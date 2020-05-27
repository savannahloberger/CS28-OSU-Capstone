CC = gcc
FLAGS = -g
TESTING = -DTESTING
PTHREAD = -pthread

all: main.c dummy read_data runtime display logging check_connection average
	$(CC) $(FLAGS) $(PTHREAD) -o tracker main.c dummy.o read_data.o runtime.o display.o logging.o check_connection.o average.o

testing: main.c dummy read_data runtime display logging check_connection average blackbox
	$(CC) $(FLAGS) $(TESTING) $(PTHREAD) -o testing main.c dummy.o read_data.o runtime.o display.o logging.o check_connection.o average.o testing.o

runtime: ./unity/runtime.c ./unity/runtime.h ./unity/util.h
	$(CC) $(FLAGS) -c ./unity/runtime.c

dummy: ./reading/dummy.c ./reading/dummy.h ./reading/data.h ./unity/util.h
	$(CC) $(FLAGS) -c ./reading/dummy.c

read_data: ./reading/read_data.c ./reading/read_data.h ./unity/util.h ./reading/data.h ./reading/dummy.h
	$(CC) $(FLAGS) -c ./reading/read_data.c

display: ./display/display.c ./display/display.h ./unity/util.h ./reading/data.h
	$(CC) $(FLAGS) -c ./display/display.c

logging: ./logging/logging.c ./logging/logging.h ./unity/util.h ./reading/data.h
	$(CC) $(FLAGS) -c ./logging/logging.c

check_connection: ./connection_check/check_connection.c ./connection_check/check_connection.h ./unity/util.h
	$(CC) $(FLAGS) -c ./connection_check/check_connection.c

average: ./calculation/average.c ./calculation/average.h ./unity/util.h
	$(CC) $(FLAGS) -c ./calculation/average.c

blackbox: ./tests/testing.c ./tests/testing.h ./unity/util.h
	$(CC) $(FLAGS) -c ./tests/testing.c

clean:
	rm -f *.o ./tracker ./testing ./log.txt
