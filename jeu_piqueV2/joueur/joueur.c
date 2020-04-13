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

int main(int argc, char **argv)
{
	
	int sock, envoye, recu;
	struct sockaddr_in adresseServeur;
	int lgadresseServeur;
	struct hostent *hote;	
	struct sockaddr_in adresseLocale;
	int lgadresseLocale;
	//struct sigaction action;
	int prix=0;
	int unEntier;
	char message[5000];
	

	/* cr'eation de la socket */
	if ((sock = socket( AF_INET, SOCK_DGRAM, 0 )) == -1) 
  	{
	    perror("socket accueil"); 
 	   	exit(1);
    }

	/* recherche de l'@ IP de la machine distante */
	if ((hote = gethostbyname(argv[2])) == NULL)
	{
    	perror("gethostbyname"); 
    	close(sock); 
    	exit(2);
    }

	/* pr'eparation de l'adresse distante : port + la premier @ IP */
	adresseServeur.sin_family = AF_INET;
	adresseServeur.sin_port = htons(atoi(argv[1]));
	bcopy(hote->h_addr, &adresseServeur.sin_addr, hote->h_length);
	printf("L'adresse en notation pointee %s\n", inet_ntoa(adresseServeur.sin_addr));

	/* attachement de la socket a` l'adresse locale */
	lgadresseLocale = sizeof(adresseServeur);
	

  	strcpy(message,"Demande");
 
	/* envoi de la demande*/
	lgadresseServeur = sizeof(adresseServeur);
	if ((envoye = sendto( sock, message, strlen(message)+1, 0, (struct sockaddr *) &adresseServeur, lgadresseServeur )) != strlen(message)+1) 
	{
	  	perror("sendto un message"); 
  		close(sock); 
  		exit(1);
	}
	printf("message envoye: %s \n",message);
	if ((recu = recvfrom( sock, message, sizeof(message), 0, (struct sockaddr *) &adresseServeur, &lgadresseServeur )) == -1) 
	{
		perror("recvfrom un message"); 
		close(sock); 
		exit(1);
	}
	printf("j'ai recu le message : .%s.\n", message);

	if ( (strcmp(message,"oui") )!=0 )
	{
		/*confirmation rejete*/ 
		close(sock); 
		return 0;
	}
    else
    {
      //printf("Vous avez ete accepte dans la vente \n");
    }

	/*-------------------------------------------------------------------------------------------------------------------*/
	

	//printf("Description : attente\n");
	if ((recu = recvfrom(sock, message, sizeof(message),0, (struct sockaddr *) &adresseServeur, &lgadresseServeur )) == -1) 
	{
		perror("recvfrom un message"); 
		close(sock); 
		exit(1);
	}
	printf("\n%s\n",message);
	/*********************************************************/

	if ((recu = recvfrom(sock, message, sizeof(message),0, (struct sockaddr *) &adresseServeur, &lgadresseServeur )) == -1) 
	{
		perror("recvfrom un message"); 
		close(sock); 
		exit(1);
	}
	printf("\n%s\n",message);

	unemain mamain;
	
	if ((recu = recvfrom(sock, &mamain, sizeof(mamain), 0, (struct sockaddr *) &adresseServeur, &lgadresseServeur )) == -1) 
	{
		perror("recvfrom un message"); 
		close(sock); 
		exit(1);
	}
	affichemain(mamain,message);
    printf("%s\n",message );

	/*int vrai =1;
	int enchere=0;
	int choice=-1;
	while(vrai==1)
	{
		if ((recu = recvfrom(sock, &prix, sizeof(prix), 0, (struct sockaddr *) &adresseServeur, &lgadresseServeur )) == -1) 
		{
			perror("recvfrom un message"); 
			close(sock); 
			exit(1);
		}
		printf("Prix actuel: %d\n", prix);
		do
		{
			printf("Voulez vous faire une offre? si oui 1 sinon 0\n");
			scanf("%d",&choice);
			if (choice == 0 || choice<0 || choice>1)
			{
					//on ne fait rien 	
			}
			else
			{
				do
				{
					printf("Faites une offre superieur a %d \n",prix);
					scanf("%d",&enchere);
				} while (enchere<prix);
				
				lgadresseServeur = sizeof(adresseServeur);
				if ((envoye = sendto( sock, &enchere, sizeof(enchere), 0, (struct sockaddr *) &adresseServeur, lgadresseServeur )) != sizeof(enchere)) 
				{
				 	perror("sendto un message"); 
					close(sock); 
					exit(1);
				}	
			}	
		} while (choice<0 || choice>1);	
		printf("Attente de la continuation...\n");
		if ((recu = recvfrom( sock, &vrai, sizeof(vrai), 0, (struct sockaddr *) &adresseServeur, &lgadresseServeur )) == -1) 
		{
			perror("recvfrom un message"); 
			close(sock); 
			exit(1);
		}
		if (vrai!=0)
		{
			vrai=1;
		}
	}
	
	if ((recu = recvfrom( sock, &prix, sizeof(prix), 0, (struct sockaddr *) &adresseServeur, &lgadresseServeur )) == -1) 
	{
		perror("recvfrom un message"); 
		close(sock); 
		exit(1);
	}
		printf("Prix vendu : %d\n", prix);
		printf("Merci d'avoir participe\nAu revoir \n");

	*/
	close(sock);

	return 0;
}
