#include<stdio.h>
#include<stdlib.h>
#include "projet.h"
#include <math.h>
#include <string.h>

void global(void){
	Liste demande,logement,etud;
	demande=listenouv();
	logement=listenouv();
	etud=listenouv();

	DemandeA l={"D00001","E00001",0,"Cité des Cézaux",studio};
	DemandeA q={"D00002","E00001",0,"Cité des Cépaux",studio};
	DemandeA r={"D00003","E00001",0,"Cité des Cépaux",studio};
	DemandeA s={"D00004","E00001",0,"Cité des Cézaux",studio};
	Logement m={"L00001","Cité des Cépaux",studio,vrai,vrai};
	Logement n={"L00002","Cité des Cépaux",chambre,vrai,vrai};
	Logement o={"L00003","Cité des Cézaux",studio,vrai,vrai};
	Etudiant p={"E00001",Mr,"Jean","Eude",faux,0,vrai};

	demande=insererEnTete(demande, &s);
	demande=insererEnTete(demande, &r);
	demande=insererEnTete(demande, &q);
	demande=insererEnTete(demande, &l);
	logement=insererEnTete(logement, &m);
	logement=insererEnTete(logement, &n);
	logement=insererEnTete(logement, &o);
	etud=insererEnTete(etud, &p);
	
	fTraitementDem(demande,logement,etud);
}

void fTraitementDem(Liste demande,Liste logement,Liste etud){
	Booleen bool=vrai;
	Liste etudTmp, logTmp;
	while(!vide(demande)){
		etudTmp=existeEtud(etud,((DemandeA*)demande->data)->idEtud);
		if(etudTmp==NULL){
			printf("L'étudiant n°%s n'éxiste pas\n",((DemandeA*)demande->data)->idEtud);
			demande=demande->suiv;
			continue;
		}
		logTmp=repDemande(logement,((DemandeA*)demande->data)->nomCite, &((DemandeA*)demande->data)->type, &bool, &((Etudiant*)etudTmp->data)->handicap);
		if(logTmp!=NULL){
			((Logement*)logTmp->data)->dispo=faux;
			strcpy(((Logement*)logTmp->data)->idEtud,((DemandeA*)demande->data)->idEtud);
			printf("La demande n°%s à été validée le logement est n°%s\n",((DemandeA*)demande->data)->idDemande,((Logement*)logTmp->data)->idLogement);
			demande=supprimerEnTete(demande);
		}
		else{
			printf("La demande n°%s ne peut pas aboutir. Aucun logement valable\n",((DemandeA*)demande->data)->idDemande);
			demande=demande->suiv;
		}
	}
}

Liste repDemande(Liste l,void* dataNom,void* dataType,void* dataDispo, void* dataHandi){
	while(!vide(l)){
		if(existeNom(l, dataNom) && existeType(l, dataType) && existeDispo(l, dataDispo) && existeHandic(l, dataHandi))
			return l;
		l=l->suiv;
	}
	return NULL;
}


Liste existeEtud(Liste l, void* data){
	if(vide(l))
		return NULL;
	if(strcmp((char*)data,((Etudiant*)tete(l))->idEtud)<0) //que si la liste est triée
		return NULL;
	if(strcmp((char*)data,((Etudiant*)tete(l))->idEtud)==0)
		return l;
	return existeEtud(l->suiv,data);
}

Booleen existeNom(Liste l, void* data){
	if(vide(l))
		return faux;
	if(strcmp((char*)data,((Logement*)tete(l))->nom)==0)
		return vrai;
	return faux;
}

Booleen existeType(Liste l, void* data){
	if(vide(l))
		return faux;
	if(*(Typelog*)data==((Logement*)tete(l))->type)
		return vrai;
	return faux;
}

Booleen existeDispo(Liste l, void* data){
	if(vide(l))
		return faux;
	if(*(Booleen*)data==((Logement*)tete(l))->dispo)
		return vrai;
	return faux;
}

Booleen existeHandic(Liste l, void* data){
	if(vide(l))
		return faux;
	if(*(Booleen*)data==((Logement*)tete(l))->handicap)
		return vrai;
	return faux;
}