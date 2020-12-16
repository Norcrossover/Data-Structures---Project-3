CC = g++
CFLAGS = -g -Wall -std=c++11
OBJS = app.o mgr.o hash.o data.o

app: $(OBJS)

app.o: mgr.h hash.o

mgr.o: hash.h data.h

hash.o: hash.h data.h

data.o: data.h

clean:
	rm app *.o
