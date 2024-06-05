CFLAGS=-g -Wall -fdiagnostics-color=always -Wno-misleading-indentation
UTILS=rtbp_sim proves_bis_exp proves_nwt_exp rtbp_lyap_csig rtbp_lyap_ref

tot : $(UTILS)

# Biblioteques
rtbp.o : rtbp.c
	gcc -c $(CFLAGS) $<
zeros.o : zeros.c
	gcc -c $(CFLAGS) $<

# Utilitats
rtbp_sim : rtbp_sim.c rtbp.o
	gcc -o $@ $(CFLAGS) $^ -lm
proves_bis_exp : proves_bis_exp.c zeros.o
	gcc -o $@ $(CFLAGS) $^ -lm
proves_nwt_exp : proves_nwt_exp.c zeros.o
	gcc -o $@ $(CFLAGS) $^ -lm
rtbp_lyap_csig : rtbp_lyap_csig.c rtbp.o
	gcc -o $@ $(CFLAGS) $^ -lm
rtbp_lyap_ref : rtbp_lyap_ref.c rtbp.o zeros.o
	gcc -o $@ $(CFLAGS) $^ -lm
exercici7 : exercici7.c rtbp.o zeros.o
	gcc -o $@ $(CFLAGS) $^ -lm

# Neteja
clean :
	rm -f *.o
realclean : clean
	rm -f $(UTILS)