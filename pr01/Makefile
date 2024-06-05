# FLAGS=-g -Wall -fdiagnostics-color=always
FLAGS=-O3 -Wall -fdiagnostics-color=always

EXECS = trigrec_escr trigrec_temps_err

trigrec.o : trigrec.c
	gcc -c $(FLAGS) trigrec.c

temps.o : temps.c
	gcc -c $(FLAGS) temps.c

trigrec_escr.o : trigrec_escr.c
	gcc -c $(FLAGS) trigrec_escr.c

trigrec_escr : trigrec_escr.o trigrec.o
	gcc -o trigrec_escr $(FLAGS) trigrec_escr.o trigrec.o -lm

trigrec_temps_err.o : trigrec_temps_err.c
	gcc -c $(FLAGS) trigrec_temps_err.c

trigrec_temps_err : trigrec_temps_err.o trigrec.o temps.o
	gcc -o trigrec_temps_err $(FLAGS) trigrec_temps_err.o trigrec.o temps.o -lm

clean :
	rm -f *.o

realclean : clean
	rm -f $(EXECS)