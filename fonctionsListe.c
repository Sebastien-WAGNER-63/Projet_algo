#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <string.h>
#include "fonctionsListe.h"

Liste listenouv(void){
	Liste l;
	l=NULL;
	return l;
}

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

Booleen vide(Liste l){
	if(l==NULL)
		return vrai;
	return faux;
}


//X
//version it
void affichageListeIt(Liste l,Type type){
	while(!vide(l)){
		if(type==entier)
			printf("%d\n",*(int*)l->data);
		if(type==flotant)
			printf("%.2f\n",*(float*)l->data);
		if(type==carac)
			printf("%s\n",(char*)l->data);
		if(type==booleen)
			printf("%d\n",*(Booleen*)l->data);
		if(type==typeLog)
			printf("%d\n",*(Typelog*)l->data);
		if(type==civilite)
			printf("%d\n",*(Civilite*)l->data);
		l=l->suiv;
	}
}


void *tete (Liste l){
	if(vide(l)){
		printf("opperation interdite\n");
		exit(1);
	}
	return l->data;
}


//X
//version it
int longueurIt(Liste l){
	int cpt=0;
	while(!vide(l)){
		cpt++;
		l=l->suiv;
	}
	return cpt;
}

//X
Booleen existe(Liste l, void* data, Type type){
	if(vide(l))
		return faux;
	if(type==entier){
		if(*(int*)data<*(int*)tete(l)) //que si la liste est triée
			return faux;
		if (*(int*)data==*(int*)tete(l))
			return vrai;
	}
	if(type==flotant){
		if(*(float*)data<*(float*)tete(l)) //que si la liste est triée
			return faux;
		if (*(float*)data==*(float*)tete(l))
			return vrai;
	}
	if(type==carac){
		if(strcmp((char*)data,(char*)tete(l))<0) //que si la liste est triée
			return faux;
		if (strcmp((char*)data,(char*)tete(l))==0)
			return vrai;
	}
	if(type==booleen){
		if(*(Booleen*)data<*(Booleen*)tete(l)) //que si la liste est triée
			return faux;
		if (*(Booleen*)data==*(Booleen*)tete(l))
			return vrai;
	}
	if(type==typeLog){
		if(*(Typelog*)data<*(Typelog*)tete(l)) //que si la liste est triée
			return faux;
		if (*(Typelog*)data==*(Typelog*)tete(l))
			return vrai;
	}
	if(type==civilite){
		if(*(Civilite*)data<*(Civilite*)tete(l)) //que si la liste est triée
			return faux;
		if (*(Civilite*)data==*(Civilite*)tete(l))
			return vrai;
	}
	return existe(l->suiv,data,type);
}

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

//X
Liste insertion(Liste l, void* data, Type type){
	if(vide(l))
		return insererEnTete(l,data);
	if(type==entier){
		if(*(int*)data<*(int*)tete(l))
			return insererEnTete(l,data);
		if(*(int*)data==*(int*)tete(l))
			return l;
	}
	if(type==flotant){
		if(*(float*)data<*(float*)tete(l))
			return insererEnTete(l,data);
		if(*(float*)data==*(float*)tete(l))
			return l;
	}
	if(type==carac){
		if(strcmp((char*)data,(char*)tete(l))<0)
			return insererEnTete(l,data);
		if(strcmp((char*)data,(char*)tete(l))==0)
			return l;
	}
	if(type==booleen){
		if(*(Booleen*)data<*(Booleen*)tete(l))
			return insererEnTete(l,data);
		if(*(Booleen*)data==*(Booleen*)tete(l))
			return l;
	}
	if(type==typeLog){
		if(*(Typelog*)data<*(Typelog*)tete(l))
			return insererEnTete(l,data);
		if(*(Typelog*)data==*(Typelog*)tete(l))
			return l;
	}
	if(type==civilite){
		if(*(Civilite*)data<*(Civilite*)tete(l))
			return insererEnTete(l,data);
		if(*(Civilite*)data==*(Civilite*)tete(l))
			return l;
	}
	l->suiv=insertion(l->suiv,data,type);
	return l;
}

//X
Liste supprimer(Liste l, void* data,Type type){
	if(vide(l))
		return l;
	if(type==entier){
		if(*(int*)data<*(int*)tete(l))
			return l;
		if(*(int*)data==*(int*)tete(l))
			return supprimerEnTete(l);
	}
	if(type==flotant){
		if(*(float*)data<*(float*)tete(l))
			return l;
		if(*(float*)data==*(float*)tete(l))
			return supprimerEnTete(l);
	}
	if(type==carac){
		if(strcmp((char*)data,(char*)tete(l))<0)
			return l;
		if(strcmp((char*)data,(char*)tete(l))==0)
			return supprimerEnTete(l);
	}
	if(type==booleen){
		if(*(Booleen*)data<*(Booleen*)tete(l))
			return l;
		if(*(Booleen*)data==*(Booleen*)tete(l))
			return supprimerEnTete(l);
	}
	if(type==typeLog){
		if(*(Typelog*)data<*(Typelog*)tete(l))
			return l;
		if(*(Typelog*)data==*(Typelog*)tete(l))
			return supprimerEnTete(l);
	}
	if(type==civilite){
		if(*(Civilite*)data<*(Civilite*)tete(l))
			return l;
		if(*(Civilite*)data==*(Civilite*)tete(l))
			return supprimerEnTete(l);
	}
	l->suiv=supprimer(l->suiv,data,type);
	return l;
}

//X
Liste insertionEnQueu(Liste l, void* data){
	if(vide(l))
		return insererEnTete(l,data);
	l->suiv=insertionEnQueu(l->suiv,data);
	return l;
}

//X
void supprimerListe(Liste l){
	while(!vide(l))
		l=supprimerEnTete(l);
}
