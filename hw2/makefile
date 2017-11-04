CC = g++
CFLAGS = -g

all: PolygonTest

point.o:	point.h point.cc
	$(CC) $(CFLAGS) -c point.cc

rectangle.o:	rectangle.h rectangle.cc
	$(CC) $(CFLAGS) -c rectangle.cc

triangle.o:	triangle.h triangle.cc
	$(CC) $(CFLAGS) -c triangle.cc

PolygonTest:	point.o rectangle.o triangle.o
	$(CC) $(CFLAGS) point.o rectangle.o triangle.o polygon_test.cc -o polytest

clean:
	rm -f *.o *~
	rm polytest
