CFLAGS = -g -Wall -Wno-unused-result -O3
LDLIBS = -l hiredis -l readline

all:   jogo

# exemplo1: tabuleiro.h tabuleiro.c exemplo1.c

jogo: tabuleiro.h tabuleiro.c jogo.c

clean:
	rm -f  exemplo1 jogo 

start:
	(redis-server redis.conf & ); ./ r 50 5