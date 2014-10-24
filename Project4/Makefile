cal.out : calendar.o year.o day.o appointment.o time.o dayofweek.o
	g++ -g -Wall -ansi -o cal.out calendar.o year.o day.o appointment.o time.o dayofweek.o

calendar.o : calendar.cpp year.h
	g++ -g -Wall -ansi -c calendar.cpp

year.o : year.cpp year.h day.h
	g++ -g -Wall -ansi -c year.cpp

day.o : day.cpp day.h appointment.h dayofweek.h
	g++ -g -Wall -ansi -c day.cpp

appointment.o : appointment.cpp appointment.h time.h
	g++ -g -Wall -ansi -c appointment.cpp

time.o : time.cpp time.h
	g++ -g -Wall -ansi -c time.cpp

dayofweek.o: dayofweek.cpp dayofweek.h
	g++ -g -Wall -ansi -c dayofweek.cpp

clean:
	rm -rf cal.out calendar.o year.o day.o appointment.o time.o dayofweek.o
