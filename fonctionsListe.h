typedef struct maillon
{	void *data;
	struct maillon * suiv;
} Maillon, *Liste;

//Different types de logements
typedef enum{
  chambre, studio, T1, T2
}Typelog;

//Different types de civilité
typedef enum{
  Mr, Mme
}Civilite;

typedef enum{
	faux,vrai
}Booleen;

typedef enum{
	carac,entier,flotant,booleen,typeLog,civilite
}Type;


Liste listenouv(void);
Liste insererEnTete(Liste l, void *data);
Liste insertion(Liste l, void* data, Type type);
Liste supprimerEnTete(Liste l);
void supprimerListe(Liste l);
Booleen vide(Liste l);
int longueurIt(Liste l);
// int longueurRec(Liste l);
Liste insertionEnQueu(Liste l, void* data);
void affichageListeIt(Liste l,Type type);
// void affichageListeRec(Liste l,Type type);
void *tete(Liste l);
Booleen existe(Liste l, void* data, Type type);
Liste supprimer(Liste l, void* data,Type type);
