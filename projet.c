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
	fAddDemandeLog(demande,etud);
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

void fAddDemandeLog(Liste demande,Liste etud){
	DemandeA demandeA;
	Liste etudTmp;
	printf("Saisir l'identifiant de l'étudiant :\n");
	scanf("%s",demandeA.idEtud);
	while(!testId(demandeA.idEtud)){
		printf("Saisir l'identifiant de l'étudiant :\n");
		scanf("%s",demandeA.idEtud);
	}
	etudTmp=existeEtud(etud,demandeA.idEtud);
	if(etudTmp==NULL){
		printf("L'étudiant n°%s n'éxiste pas encore\n",demandeA.idEtud);
		fAddEtud(etud, demandeA.idEtud);
	}
}

void fAddEtud(Liste etud, char* idEtud){
	Etudiant etudTmp;
	Booleen continuer=faux;
	char charTmp[100];
	printf("Ajout de l'étudiant n°%s :\n",idEtud);
	strcpy(etudTmp.idEtud,idEtud);
	printf("Saisir sa civilité (Mr/Mme) :\n");
	scanf("%s%*c",charTmp);
	while(strcmp(charTmp,"Mr")!=0 && strcmp(charTmp,"Mme")!=0){
		printf("Civilité invalide. Saisir sa civilité (Mr/Mme) :\n");
		scanf("%s%*c",charTmp);
	}
	if(strcmp(charTmp,"Mr")==0)
		etudTmp.civilite=Mr;
	else
		etudTmp.civilite=Mme;
	printf("Saisir son Nom :\n");
	fgets(charTmp,99,stdin);
	charTmp[strlen(charTmp)-1]='\0';
	etudTmp.nom=(char*)malloc(strlen(charTmp)*sizeof(char));
	strcpy(etudTmp.nom,charTmp);
	printf("Saisir son prénom :\n");
	fgets(charTmp,99,stdin);
	charTmp[strlen(charTmp)-1]='\0';
	etudTmp.prenom=(char*)malloc(strlen(charTmp)*sizeof(char));
	strcpy(etudTmp.prenom,charTmp);
	printf("Est-il boursier ? (oui/non)\n");
	scanf("%s%*c",charTmp);
	while(strcmp(charTmp,"oui")!=0 && strcmp(charTmp,"non")!=0){
		printf("Réponse invalide. Est-il boursier ? (oui/non)\n");
		scanf("%s%*c",charTmp);
	}
	if(strcmp(charTmp,"oui")==0){
		etudTmp.bourse=vrai;
		printf("Saisir l'échelon de bourse : (1-7)\n");
		scanf("%d",&etudTmp.echelon);
		while(etudTmp.echelon<1 || etudTmp.echelon>7){
			printf("Echelon invalide. Saisir l'échelon de bourse : (1-7)\n");
			scanf("%d",&etudTmp.echelon);
		}
	}
	else
		etudTmp.bourse=faux;
	printf("Est-il handicapé ? (oui/non)\n");
	scanf("%s%*c",charTmp);
	while(strcmp(charTmp,"oui")!=0 && strcmp(charTmp,"non")!=0){
		printf("Réponse invalide. Est-il handicapé ? (oui/non)\n");
		scanf("%s%*c",charTmp);
	}
	if(strcmp(charTmp,"oui")==0)
		etudTmp.handicap=vrai;
	else
		etudTmp.handicap=faux;
}

Booleen testId(char* id){
	if(strlen(id)!=6){
		printf("identifiant invalide. Il doit contenir 6 caractère e la forme (L00000/E00000/D00000)\n");
		return faux;
	}
	if(id[0]!='D' && id[0]!='L' && id[0]!='E'){
		printf("identifiant invalide. Le premier caractère doit être L/E/D\n");
		return faux;
	}
	return vrai;
}