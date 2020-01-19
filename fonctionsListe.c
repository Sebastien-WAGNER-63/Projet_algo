#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <string.h>
#include "fonctionsListe.h"

/*
Nom : listenouv
Finalité : Créer une nouvelle liste vide

Description Général :
	Créer un pointeur sur un mailon
	L'initialise a NULL

Variables :
	l 			Nouvelle liste
*/
Liste listenouv(void){
	Liste l;
	l=NULL;
	return l;
}

/*
Nom : insererEnTete
Finalité : Inserer un maillon au début d'une liste

Description Général :
	Créer un mailon
	Lui atribué les valeurs voulus
	Lui donnée comme maillon suivant le premier de la liste

Variables :
	l 			Liste dans laquelle inserer la valeur
	m 			Nouveau maillon
	data		Valeur a inserer
*/
Liste insererEnTete(Liste l, void *data){
	Maillon *m;
	m=(Maillon *) malloc (sizeof(Maillon));
	if(m==NULL){
		printf("Pb malloc\n");
		exit(1);
	}
	m->data=data;
	m->suiv=l;
	return m;
}

/*
Nom : vide
Finalité : Tester si la liste est vide

Description Général :
	Tester si le premier maillon de la liste est nul

Variables :
	l 			Liste à tester
*/
Booleen vide(Liste l){
	if(l==NULL)
		return vrai;
	return faux;
}

/*
Nom : tete
Finalité : Retourner la valeur de tête de la liste

Description Général :
	Retourner la valeur du premier maillon de la liste

Variables :
	l 			Liste dans laquelle se trouve la valeur a retourner
*/
void *tete (Liste l){
	if(vide(l)){
		printf("opperation interdite\n");
		exit(1);
	}
	return l->data;
}


/*
Nom : supprimerEnTete
Finalité : Supprimer le maillon de début de liste

Description Général :
	Créer un nouveau maillon
	attribuer la valeur du premier maillon au nouveauu
	Attribuer la valeur du maillon suivant au premier
	Supprimer le maillon temporaire
	Retourner la liste

Variables :
	l 			Liste dans laquelle on veut supprimer le début
	m 			Maillon temporaire pour supprimer définitivement le premier maillon
*/
Liste supprimerEnTete(Liste l){
	Maillon *m;
	if(vide(l)){
		printf("opération interdite\n");
		exit(0);
	}
	m=l;
	l=l->suiv;
	free(m);
	return l;
}