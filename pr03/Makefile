CFLAGS=-g -Wall -fdiagnostics-color=always -Wno-misleading-indentation

TOT=intaimg intext valida_intnev

tot : $(TOT)

horizons.txt : horizons-raw.txt Makefile
	awk '$$0~/\$$EOE/ { iout=0 } first { t0=$$1 ; first=0 } iout { print $$1-t0,$$3 } $$0~/\$$SOE/ { iout=1; first=1 }' $< > $@

intaimg : intaimg.c intnev.o
	gcc -o $@ $(CFLAGS) intaimg.c intnev.o -lm

intnev.o : intnev.c
	gcc -c $(CFLAGS) $<

valida_intnev : valida_intnev.c intnev.o
	gcc -o $@ $(CFLAGS) valida_intnev.c intnev.o -lm

intext : intext.c intnev.o zeros.o
	gcc -o $@ $(CFLAGS) intext.c intnev.o zeros.o -lm

zeros.o : zeros.c
	gcc -c $(CFLAGS) zeros.c

clean :
	rm -f *.o

realclean : clean
	rm -f $(TOT)