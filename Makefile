CC=gcc
CFLAGS=-I.
#DEPS = picomenso.h
OBJ = evoluchine.o\
      test.o
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -ggdb -fpermissive

tester: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -lm -ggdb -lpthread
.PHONY: clean

clean:
	rm -f *.o
	rm -rf bin/* 
