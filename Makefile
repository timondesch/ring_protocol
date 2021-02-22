# Makefile
# Compilation des primitives UDP
#

#CFLAGS	+= -Wall -Wmissing-prototypes -Werror

CC = gcc

SOURCES_ALL	= \
	creePriseReception.c\
	creePriseEmission.c\
	recoit.c\
	envoie.c\
	\
	exempleCOMPLET-PC1.c\
	\
	exempleCOMPLET-PC2.c\
	\
	primitives.h\
	\
	Makefile

ARCHIVE_NAME = Exemple-2proc-UDP-structPaquet.tgz

all: exempleCOMPLET-PC1 exempleCOMPLET-PC2 primitives.a $(ARCHIVE_NAME)

clean:
	rm -f *.a *.o core

$(ARCHIVE_NAME): $(SOURCES_ALL)
	tar zcf $@ $(SOURCES_ALL)

exempleCOMPLET-PC1: exempleCOMPLET-PC1.o primitives.a
	$(CC) -o $@ $^

exempleCOMPLET-PC2: exempleCOMPLET-PC2.o primitives.a
	$(CC) -o $@ $^

primitives.a: envoie.o recoit.o creePriseEmission.o creePriseReception.o
	ar rv $@ $^
	ranlib $@

