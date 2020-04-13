#include <stdio.h>
#include "carte.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
char *vcarte[]={"trois","quatre","cinq", "six" ,"sept","huit","neuf","dix","vallet","reine","roi","as","deux"};
char *ccarte[]={"carreau","treffle","coeur","pique"};


void initjeu(carte jeu[])
{
    int i,j,k=0;
    
    for(i=0;i<13;i++)
    {
        for(j=0;j<4;j++)
        {
            jeu[k].valeur=i;
            jeu[k].couleur=j;
            k++;
        }
    }

}

void affichecarte(carte c,char message[])
{
  sprintf(message,"\tvaleur: %s couleur: %s\n",vcarte[c.valeur],ccarte[c.couleur]);
}
void affichejeu(carte jeu[],char message [])
{
    int i;
    char tampon[100];
    for(i=0;i<NBCARTES;i++)
    {
      affichecarte(jeu[i],tampon);
      strcat(message,tampon) ;
    }
}

void affichemain(unemain tmp, char message[])
{
    int i;
    char tampon[100];
    sprintf(message,"Main n°:%d\n",tmp.id );
    for(i=0;i<13;i++)
    {
      if (tmp.presence[i]==1)
      {
        sprintf(tampon,"\tvaleur: %s couleur: %s\n",vcarte[tmp.tab[i].valeur],ccarte[tmp.tab[i].couleur]);
        strcat(message,tampon);
      }
      
    }
}



int randome(void)
{
    return(rand()%NBCARTES);
}

void permute(carte *c1,carte *c2)
{
    carte tmp;
    tmp=*c1,
    *c1=*c2;
    *c2=tmp;
}

void melange(carte jeu[])
{ 
    int i;
    for(i=0;i<=938;i++)
    {
        permute(&jeu[randome()],&jeu[randome()]);
    }
}

void distribution(carte jeu[],unemain *main1,unemain *main2,unemain *main3 ,unemain *main4)
{
    int i,tmp1=0,tmp2=0,tmp3=0,tmp4=0,k=0;
    for(i=0;i<NBCARTES;i++)
    {

        if(k==0)
        {
          //main 1
          (main1->tab[tmp1].valeur)=(jeu[i].valeur);
          main1->tab[tmp1].couleur=jeu[i].couleur;
          main1->presence[tmp1]=true;
          
          //printf("%d\n",tmp1 );
          //printf("\tvaleur: %d \n",main1->tab[tmp1].valeur);
          //printf("\tvaleur: %d \n",jeu[i].valeur);
          tmp1++;
        }
        if(k==1)
        {
          //main 2
          main2->tab[tmp2].valeur=jeu[i].valeur;
          main2->tab[tmp2].couleur=jeu[i].couleur;
          main2->presence[tmp2]=true;
          tmp2++;
         
        }
        if(k==2)
        {
          //main 3
          main3->tab[tmp3].valeur=jeu[i].valeur;
          main3->tab[tmp3].couleur=jeu[i].couleur;
          main3->presence[tmp3]=true;
          tmp3++;
         
        }
        if(k==3)
        {
          //main 4
          main4->tab[tmp4].valeur=jeu[i].valeur;
          main4->tab[tmp4].couleur=jeu[i].couleur;
          main4->presence[tmp4]=true;
          tmp4++;
          
        }
        k++;
        if (k==4)
        {
          k=0;
        }

    }

}
/*
void bataille(carte jeu1[],carte jeu2[])
{
      int i;
   for(i=0;i<32;i++)
    {
        if(d!=0 && e!=0)
        {
            if (d>0 || e >0)
     {



          if(jeu1[i].valeur>jeu2[i].valeur)
          {
              jeu1[i].valeur=jeu2[i].valeur;
              d++;
              e--;
              goto etiquette;
          }
          if(jeu1[i].valeur<jeu2[i].valeur)
          {
              jeu2[i].valeur=jeu1[i].valeur;
              e++;
              d--;
              goto etiquette;
          }
          if(jeu1[i].valeur==jeu2[i].valeur)
          {
              if(jeu1[i].couleur>jeu2[i].couleur)
              {
                  jeu1[i].couleur=jeu2[i].couleur;
                  d++;
                  e--;goto etiquette;
              }
              else
              {
                  jeu2[i]=jeu1[i];
                  e++;
                  d--;goto etiquette;
              }
          }
          }
          }etiquette:nimp=nimp1;


      }
       printf("%d\n",16+d);
      printf("%d",16+e);



}*/

