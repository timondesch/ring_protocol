#include <assert.h>
//#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "primitives.h"

/* emetteur (ma machine) ---> recepteur (machine suivante) */

#define ADRESSE_EMETTEUR	"127.0.0.1"
#define ADRESSE_RECEPTEUR	"127.0.0.1"
#define PORT_RECEPTION		1920
#define PORT_EMISSION		1990
#define LONGUEUR_ADRESSE	16
#define LONGUEUR_MESSAGE	121

typedef struct paquet
{
	char adresse[LONGUEUR_ADRESSE];
	char source[LONGUEUR_ADRESSE];
	int type;
	int index;
	char message[LONGUEUR_MESSAGE];
} Paquet;
/* Paquet <=> struct paquet */  

void traitePaquet(Paquet *p)
{
	char buffer[LONGUEUR_MESSAGE];

	if (strcmp(ADRESSE_EMETTEUR, p->adresse) == 0)
	/* si je suis le destinataire du paquet */
	{
		printf("message : ");
		scanf("%120s", buffer);
		sprintf(p->message, "%120s", buffer);
		printf("\n");
	}
	else
		/* sinon */
		printf("message de %16s : %120s\n", p->adresse, p->message);
}

int main (int argc, char **argv)
{
	int    	priseEmission, priseReception;
	char   	buffer[LONGUEUR_ADRESSE + LONGUEUR_MESSAGE];
	Paquet 	p;
	
	int		sizeofbuffer;

	priseEmission  = creePriseEmission(ADRESSE_RECEPTEUR, PORT_EMISSION);
	priseReception = creePriseReception(PORT_RECEPTION);

	printf("J'envoie le 1er paquet \n");
	printf("Touche d pour demarrer...\n");
  	while (getchar() != 'd'); /* temporisation */

	sprintf(buffer, "%15s%120s", ADRESSE_RECEPTEUR, "blablabla");
	envoie(priseEmission, buffer, strlen(buffer));
	/* ex. remplissage 1er paquet puis emission */

	printf("PC1 demarre ...\n\n");

	/* boucle en emission */
	
	sizeofbuffer = (LONGUEUR_ADRESSE + LONGUEUR_MESSAGE)*sizeof(char);
	
	do
	{
		printf("Envoyer un autre paquet ? \n");
		printf("Touche e pour continuer...\n");
  		while (getchar() != 'e'); /* temporisation */

		memset (buffer, '\0', sizeofbuffer);

		sprintf(buffer, "%15s%120s", ADRESSE_RECEPTEUR, "nouveauBlabla");

		envoie(priseEmission, buffer, strlen(buffer));

	} while (1); /* boucle infinie */

  return 0;
}

