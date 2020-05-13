all: main.c dummy.o read_data.o runtime.o display.o logging.o check_connection.o average.o
	gcc -g -pthread -o tracker main.c dummy.o read_data.o runtime.o display.o logging.o check_connection.o average.o

testing: main.c dummy.o read_data.o runtime.o display.o logging.o check_connection.o average.o
	make tests
	gcc -g -pthread -DTESTING -o testing main.c dummy.o read_data.o runtime.o display.o logging.o check_connection.o average.o testing.o

runtime: runtime.c runtime.h util.h

dummy: dummy.c dummy.h data.h util.h
	gcc -g -c dummy.c

read_data: read_data.c read_data.h util.h data.h dummy.h
	gcc -g -c read_data.c

display: display.c display.h util.h data.h
	gcc -g -c display.c

logging: logging.c logging.h util.h data.h
	gcc -g -c logging.c

check_connection: check_connection.c check_connection.h util.h
	gcc -g -c check_connection.c

average: average.c average.h util.h
	gcc -g -c average.c

tests: ./tests/testing.c ./tests/testing.h util.h
	gcc -g -c ./tests/testing.c

clean:
	rm -f *.o ./tracker ./testing ./log.txt
