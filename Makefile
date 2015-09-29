CC = gcc
CFLAGS = -W -Wall -pedantic
CFLAGS += -D_XOPEN_SOURCE=500
CFLAGS += -g -m32

all:

swtch_ctx : swtch_ctx.c
	$(CC) $(CFLAGS) -o swtch_ctx swtch_ctx.c

main : swtch_ctx.o main.c
	$(CC) $(CFLAGS) -o main swtch_ctx.o main.c

clean:
	-rm *.o main  .#* *~
