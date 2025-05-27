CC = gcc
CFLAGS = -Wall -g

all: supplier smoker_tobacco smoker_paper smoker_glue

supplier: supplier.o ipc.o
	$(CC) $(CFLAGS) -o $@ $^

smoker_tobacco: smoker.o ipc.o
	$(CC) $(CFLAGS) -o $@ $^
	ln -sf smoker_tobacco smoker

smoker_paper: smoker.o ipc.o
	$(CC) $(CFLAGS) -o $@ $^

smoker_glue: smoker.o ipc.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c ipc.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f supplier smoker smoker_tobacco smoker_paper smoker_glue *.o
