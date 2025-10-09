CC=gcc
CFLAGS=-O2 -std=c11 -Wall

all: mochila make_csv

mochila: mochila.c
	$(CC) $(CFLAGS) -o mochila mochila.c

make_csv: make_csv.c mochila.c
	$(CC) $(CFLAGS) -Dmake_csvMARK_MODE -o make_csv make_csv.c mochila.c

clean:
	rm -f mochila make_csv *.o timings.csv
