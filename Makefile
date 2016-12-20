CC=gcc

CFLAGS = -O3
LFLAGS = 

all: md5

md5: md5.lo main.lo
	$(CC) $(LFLAGS) -o $@ $?

%.lo: %.c
	$(CC) $(CFLAGS) -o $@ -c $?

clean:
	@rm -f *.lo md5

