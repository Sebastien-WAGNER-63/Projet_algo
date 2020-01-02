typedef struct maillon
{	int v
	struct maillon * suiv;
} maillon;


typedef enum
{
	faux,vrai
}Booleen;


Liste listenouv (void);
Liste insererEnTete (Liste l, int x);
Liste insertion (Liste l, int x);
Liste supprimerEnTete (Liste l);
Liste supprimer (Liste l, int x);
Booleen vide (Liste l);
int longueurIt (Liste l);
int longueurRec (Liste l)
liste insertionEnQueu (Liste l, int x);
void affichageListeIt (Liste l);
void affichageListeRec (Liste l);
int tete (Liste l);
Booleen existe (Liste l, int x);
void supprimerListe(Liste l);
