//Structure d'un maillon de la liste
typedef struct maillon
{	void *data;
	struct maillon * suiv;
} Maillon, *Liste;

//Différents types de logements
typedef enum{
  chambre, studio, T1, T2
}Typelog;

//Différents types de civilités
typedef enum{
  Mr, Mme
}Civilite;

//Type booleen
typedef enum{
	faux,vrai
}Booleen;


//Fonctions de liste
Liste listenouv(void);
Liste insererEnTete(Liste l, void *data);
Liste supprimerEnTete(Liste l);
Booleen vide(Liste l);
void *tete(Liste l);