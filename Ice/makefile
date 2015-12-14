CC=g++
COPTS=-I.


mon_serveur: mon_serveur.cc annuaire.o
$(CC) $(COPTS) mon_serveur.cc -o mon_serveur annuaire.o -lIce -lIceUtil

    annuaire.cpp annuaire.h: annuaire.ice
	slice2cpp annuaire.ice

	annuaire.o: annuaire.cpp annuaire.h
	    $(CC) $(COPTS) -c annuaire.cpp

