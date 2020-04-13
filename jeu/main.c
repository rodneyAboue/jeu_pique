#include <stdio.h>
#include "carte.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
int main()
{   
   // carte jeu[NBCARTES];
    srand(time(NULL));
    unemain main1,main2,main3,main4;
    main1.id=1;
    main2.id=2;
    main3.id=3;
    main4.id=4;
    char message[5000];
    initjeu(jeu);
    //printf("afficher avant melange\n\n");
    //affichejeu(jeu);
    for (int i = 0; i < 5; ++i)
    {      
        melange(jeu);
        //printf("afficher apres melange\n\n");
        //affichejeu(jeu);
        printf("distribution\n");
        distribution(jeu,&main1,&main2,&main3,&main4);
        affichemain(main1,message);
        printf("%s\n",message );
        affichemain(main2,message);
        printf("%s\n",message );
        affichemain(main3,message);
        printf("%s\n",message );
        affichemain(main4,message);
        printf("%s\n",message );
        // printf("%d",randome());
    }
 return 0;
}