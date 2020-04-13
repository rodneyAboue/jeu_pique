#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include "carte.h"
#include <time.h>
/*--------------------------------------------*/


/*--------------------------------------------*/
int main(int argc, char **argv)
{
	
	int sock_partie,sock_accueil, envoye, recu;
	struct sockaddr_in adresseClient;
	int lgadresseClient;
	struct hostent *hote;	
	struct sockaddr_in adresseLocale;
	struct sockaddr_in adresseLocale2;
	int lgadresseLocale;
	int lgadresseLocale2;
	//struct sigaction action;
	char message[5000];
	struct sockaddr_in tabAdresseClient[100];

	/* cr'eation de la socket */
	if ((sock_accueil = socket( AF_INET, SOCK_DGRAM, 0 )) == -1) 
  	{
	    perror("socket accueil"); 
 	   	exit(1);
    }

	adresseLocale.sin_family = AF_INET;
	adresseLocale.sin_port = htons(atoi(argv[1]));
	adresseLocale.sin_addr.s_addr = htonl(INADDR_ANY);

	/* attachement de la socket a` l'adresse locale */
	lgadresseLocale = sizeof(adresseLocale);
	
	if ((bind( sock_accueil, (struct sockaddr *) &adresseLocale, lgadresseLocale )) == -1) 
	{
  		perror("bind"); 
  		exit(1);
  	}
  
  	int i=0; 
  	int nbClient=0;
  	printf("Je commence a recuperer les joueurs\n" );
  	while(nbClient!=2)/***********/
  	{
  		//printf("ok\n");
  		lgadresseClient = sizeof(adresseClient);
  		if ((recu = recvfrom( sock_accueil, message, sizeof(message), 0, (struct sockaddr *)&tabAdresseClient[i], &lgadresseClient )) == -1) 
		{
			perror("recvfrom un message"); 
			close(sock_accueil); 
			exit(1);
		}
		
		printf("message envoye par joueur n°%d %s\n",nbClient,message );
		if (strcmp(message,"Demande")==0)
		{
			printf("ok\n");

			strcpy(message,"oui");
			printf("ok\n");
			if ((envoye = sendto( sock_accueil, message, strlen(message)+1, 0, (struct sockaddr *) &tabAdresseClient[nbClient], lgadresseClient )) != strlen(message)+1) 
			{
	  			perror("sendto un message"); 
  				close(sock_accueil); 
  				exit(1);
			}
			nbClient++;
			for (int i = 0; i < nbClient; ++i)
			{
				/***********/
				if (nbClient==2)
				{
					sprintf(message,"Debut de la partie");
				}
				else
				{
					sprintf(message,"Connexion %d/4 joueurs\n \tattente",nbClient);
				}

				if ((envoye = sendto( sock_accueil, message, strlen(message)+1, 0, (struct sockaddr *)&tabAdresseClient[i], lgadresseClient )) != strlen(message)+1) 
				{
					perror("sendto message"); 
  					close(sock_accueil); 
  					exit(1);
				}
			}		
		}
		else
		{
			perror("recvfrom un message"); 
			close(sock_accueil); 
			exit(1);	
		}

  	}
  	/*-------------------------------------------------------------------------------------------------------------------*/
	//
	/* cr'eation de la socket */
	if ((sock_partie = socket( AF_INET, SOCK_DGRAM, 0 )) == -1) 
  	{
	    perror("socket vente"); 
 	   	exit(1);
    }


  	/*-------------------------------------------------------------------------------------------------------------------*/

  	/*-------------------------------------------------------------------------------------------------------------------*/
	srand(time(NULL));
    unemain joueur1,joueur2,joueur3,joueur4;
    joueur1.id=0;
    joueur2.id=1;
    joueur3.id=2;
    joueur4.id=3;
    initjeu(jeu);
    melange(jeu);
	//printf("Envoie du message\n%s\n",message);
	strcpy(message,"Distribution des cartes");
	distribution(jeu,&joueur1,&joueur2,&joueur3,&joueur4);
	lgadresseClient = sizeof(adresseClient);
	for (int i = 0; i < nbClient; ++i)
	{
		//printf("%d\n",i);	
		if ((envoye = sendto( sock_accueil, message, strlen(message)+1, 0, (struct sockaddr *)&tabAdresseClient[i], lgadresseClient )) != strlen(message)+1) 
		{
			perror("sendto message"); 
  			close(sock_accueil); 
  			exit(1);
		}

		if (i==0)
		{
			if ((envoye = sendto( sock_partie, &joueur1, sizeof(joueur1), 0, (struct sockaddr *)&tabAdresseClient[i], lgadresseClient )) != sizeof(joueur1)) 
			{
				perror("sendto prix"); 
  				close(sock_partie); 
  				exit(1);
			}
		}
		if (i==1)
		{
			if ((envoye = sendto( sock_partie, &joueur2, sizeof(joueur2), 0, (struct sockaddr *)&tabAdresseClient[i], lgadresseClient )) != sizeof(joueur2)) 
			{
				perror("sendto prix"); 
  				close(sock_partie); 
  				exit(1);
			}
		}
		if (i==2)
		{
			if ((envoye = sendto( sock_partie, &joueur3, sizeof(joueur3), 0, (struct sockaddr *)&tabAdresseClient[i], lgadresseClient )) != sizeof(joueur3)) 
			{
				perror("sendto prix"); 
  				close(sock_partie); 
  				exit(1);
			}
		}
		if (i==3)
		{
			if ((envoye = sendto( sock_partie, &joueur4, sizeof(joueur4), 0, (struct sockaddr *)&tabAdresseClient[i], lgadresseClient )) != sizeof(joueur4)) 
			{
				perror("sendto prix"); 
  				close(sock_partie); 
  				exit(1);
			}
		}
	}
/*
	int parties=0
	while (parties=<3)
	{
		for (int i = 0; i < nbClient; ++i)
		{
			printf("Envoie des prix \n");
			lgadresseClient = sizeof(adresseClient); 
			if ((envoye = sendto( sock_vente, &offreMax, sizeof(offreMax), 0, (struct sockaddr *)&tabAdresseClient[i], lgadresseClient )) != sizeof(prixCourant)) 
			{
				perror("sendto prix"); 
  				close(sock_vente); 
  				exit(1);
			}
		}

		if ((recu = recvfrom( sock_vente, &prixCourant, sizeof(prixCourant), 0, (struct sockaddr *) &adresseClient, &lgadresseClient )) == -1) 
		{
			perror("recvfrom un prixCourant"); 
			close(sock_vente); 
			exit(1);
		}

		if (prixCourant>offreMax)
		{
			printf(" Prix courant %d\n",prixCourant);
			offreMax=prixCourant;
		}
			printf("Souhaitez vous continuer? Si oui entrez un nombre different de 0 \n");
			scanf("%d",&cont);


		if (cont==0)
		{
			continuation=false;
			for (int i = 0; i < nbClient; ++i)
			{
				lgadresseClient=sizeof(tabAdresseClient[i]); 
				if ((envoye = sendto( sock_vente, &cont, sizeof(cont), 0, (struct sockaddr *)&tabAdresseClient[i], lgadresseClient )) != sizeof(cont)) 
				{
					perror("sendto prix"); 
  					close(sock_vente); 
  					exit(1);
				}
			}

		}
		else
		{
			continuation=true;
			for (int i = 0; i < nbClient; ++i)
			{
				lgadresseClient=sizeof(tabAdresseClient[i]); 
				if ((envoye = sendto( sock_vente, &cont, sizeof(cont), 0, (struct sockaddr *)&tabAdresseClient[i], lgadresseClient )) != sizeof(cont)) 
				{
					perror("sendto prix"); 
  					close(sock_vente); 
  					exit(1);
				}
			}
		}

	}

	for (int i = 0; i < nbClient; ++i)
	{
		lgadresseClient=sizeof(tabAdresseClient[i]); 
		if ((envoye = sendto( sock_vente, &offreMax, sizeof(offreMax), 0, (struct sockaddr *)&tabAdresseClient[i], lgadresseClient )) != sizeof(prixCourant)) 
		{
			perror("sendto prix"); 
  			close(sock_vente); 
  			exit(1);
		}
	}

/*-------------------------------------------------------------------------------------------------------------------*/
  	close(sock_partie);
  	close(sock_accueil);

	return 0;
}
