#ifndef __CARTE__
#define __CARTE__
#define NBCARTES 52
//programe n°1 jeu de pique
enum carte_valeur {
  deux,
  trois,
  quatre,
  cinq,
  six,
  sept,
  huit,
  neuf, 
  dix,
  vallet,
  reine,
  roi,
  as,
};
typedef enum carte_valeur carte_valeur;


enum carte_couleur {
  carreau = 0,
  trefle = 1,
  coeur = 2,
  pique = 3,
};
typedef enum carte_couleur carte_couleur;


typedef enum bool {
  faux = 0,
  vrai = 1,
}bool;

struct carte {
  carte_couleur couleur;
  carte_valeur valeur;
};
typedef struct carte carte;
carte jeu[NBCARTES];

typedef struct 
{
  carte tab[13];
  bool presence[13];
  int id;
}unemain;



void initjeu(carte jeu[]);
void affichecarte(carte c,char message[]);
void affichejeu(carte jeu[],char message []);
void affichemain(unemain tmp, char message[]);
int randome(void);
void permute(carte *c1,carte *c2);
void melange(carte jeu[]);
void distribution(carte jeu[],unemain *main1,unemain *main2,unemain *main3 ,unemain *main4);

#endif

