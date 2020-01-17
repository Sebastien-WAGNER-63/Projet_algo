//Structure d'un maillon de la liste
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

//Type booleen
typedef enum{
	faux,vrai
}Booleen;

//X
typedef enum{
	carac,entier,flotant,booleen,typeLog,civilite
}Type;

//Fonctions de liste
Liste listenouv(void);
Liste insererEnTete(Liste l, void *data);
//X
Liste insertion(Liste l, void* data, Type type);
Liste supprimerEnTete(Liste l);
//X
void supprimerListe(Liste l);
Booleen vide(Liste l);
//X
int longueurIt(Liste l);
//X
Liste insertionEnQueu(Liste l, void* data);
//X
void affichageListeIt(Liste l,Type type);
void *tete(Liste l);
//X
Booleen existe(Liste l, void* data, Type type);
//X
Liste supprimer(Liste l, void* data,Type type);
