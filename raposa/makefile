CFLAGS = -g -Wall -Wno-unused-result -O3
LDLIBS = -l hiredis -l readline

all:  exemplo1 jogo

# controlador: controlador.c

exemplo1: tabuleiro.h tabuleiro.c exemplo1.c

jogo: tabuleiro.h tabuleiro.c jogo.c

clean:
	rm -f controlador exemplo1 jogo 

start:
	(redis-server redis.conf & ); ./controlador r 50 5