PROJ = bf
OBJ = bf.o
CC = gcc
INCLUDE = -I/usr/include/gc/
CFLAGS = -W -Wall -D_REEENTRANT -DGC_LINUX_THREADS $(INCLUDE)
LIB = -lgc

.PHONY:clean

$(PROJ):$(OBJ)
	$(CC) -o $@ $? $(LIBDIR) $(LIB)

all:$(PORJ)

clean:
	rm -f $(PROJ) $(OBJ)
