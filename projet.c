#include<stdio.h>
#include<stdlib.h>
#include "projet.h"
#include <math.h>
#include <string.h>


/*
Nom : global
Finalité : séléctionner les différentes fonctions du programme

Description Général :
	Charge les fichiers dans des listes
	Traite les demandent
	Menu pour choisir l'action a éffectuer

Variables :
	choix 		La fonction séléctionné dans le menu
	logement 	Liste de logement
	etud 		Liste d'étudiant
	demande 	Liste de demande en attente
*/
void global(void){
	Liste logement,etud,demande;
	int choix;
	logement=chargeLogement();
	etud=chargeEtud();
	demande=chargeDemande();
	demande=fTraitementDem(demande,logement,etud);
	while(1){
		printf("\n0/\tQUITTER\n");
		printf("1/\tCharger les dernier paramètres enregistrés\n");
		printf("2/\tAfficher les logements disponibles\n");
		printf("3/\tAfficher les logements occupés\n");
		printf("4/\tAfficher les demandes de logement\n");
		printf("5/\tTraitement des demandes en attente\n");
		printf("6/\tSaisie d'une nouvelle demande de logement\n");
		printf("7/\tAnnulation d'une demande de logement\n");
		printf("8/\tLiberation logement\n");
		printf("9/\tSauvegarde\n");
		scanf("%d%*c",&choix);
		switch(choix){
			case 1 : logement=chargeLogement();etud=chargeEtud();demande=chargeDemande();break;
			case 2 : AffichLog(logement);break;
			case 3 : AffichLogOcup( logement, etud);break;
			case 4 : AffichDemande( demande);break;
			case 5 : demande=fTraitementDem(demande,logement,etud);break;
			case 6 : demande=fAddDemandeLog( demande, &etud, logement);break;
			case 7 : demande=fAnnulDemande(demande);break;
			default : exit(1); 
		}
	}

}

/*
Nom : fTraitementDem
Finalité : Traiter les demandes en attente

Description Général :
	Parcour la liste de demande
	Teste si l'étudiant existe
	Teste si un logement compatible est disponible
		Affiche un message, rend le logement occupé et suprime la demande si validé

Variables :
	logement 	Liste de logement
	etud 		Liste d'étudiant
	demande 	Liste de demande en attente
	etudTmp 	Liste d'un étudiant utilisé temporairement
	logTmp 		Liste d'un logement utilisé temporairement
	demTmp	 	Liste d'une demande utilisée etemporairement
*/
Liste fTraitementDem(Liste demande,Liste logement,Liste etud){
	Liste etudTmp, logTmp, demTmp;
	demTmp=demande;
	while(!vide(demTmp)){
		etudTmp=existeEtud(etud,((DemandeA*)demTmp->data)->idEtud);
		if(etudTmp==NULL){
			printf("La demande n°%s, L'étudiant n°%s n'existe pas\n",((DemandeA*)demTmp->data)->idDemande,((DemandeA*)demande->data)->idEtud);
			demTmp=demTmp->suiv;
			continue;
		}
		logTmp=repDemande(logement,((DemandeA*)demTmp->data)->nomCite, &((DemandeA*)demTmp->data)->type, &((Etudiant*)etudTmp->data)->handicap);
		if(logTmp!=NULL){
			((Logement*)logTmp->data)->dispo=faux;
			strcpy(((Logement*)logTmp->data)->idEtud,((DemandeA*)demTmp->data)->idEtud);
			printf("La demande n°%s a été validée le logement est n°%s\n",((DemandeA*)demTmp->data)->idDemande,((Logement*)logTmp->data)->idLogement);
			demande = supprimerDemande(demande, &demTmp);		
		}
		else{
			printf("La demande n°%s ne peut pas aboutir. Aucun logement valable\n",((DemandeA*)demTmp->data)->idDemande);
			demTmp=demTmp->suiv;
		}
	}
	return demande;
}

/*
Nom : supprimerDemande
Finalité : Supprimer une demande en attente

Description Général :
	Teste si la liste est vide
	Teste si l'identifiant de la demande est celui que l'on veut supprimer
		Supprime le maillon

Variables :
	l 			Liste de toute les demande en attente
	data 		Liste d'une demande en attente à supprimer
*/
Liste supprimerDemande(Liste l, Liste *data){
	if(vide(l)){
		printf("vide\n");
		return l;
	}
	if(strcmp(((DemandeA*)(*data)->data)->idDemande,((DemandeA*)l->data)->idDemande)==0){
		l=supprimerEnTete(l);
		*data=l;
		return l;
	}
	l->suiv=supprimerDemande(l->suiv,data);
	return l;
}

/*
Nom : repDemande
Finalité : Verrifier si un logement est compatible

Description Général :
	Parcour la liste de logement
	Teste si il est vide, dans la bonne cité, le bon type, handicapé ou non
	Retourne le logement valide ou NULL

Variables :
	l 			Liste de demande
	dataNom 	Nom de la cité voulu
	dataType	Type de logement voulu
	dataHandi	Handicapé ou pas
*/
Liste repDemande(Liste l,void* dataNom,void* dataType, void* dataHandi){
	while(!vide(l)){
		if(strcmp(((Logement*)l->data)->nom, dataNom)==0 && ((Logement*)l->data)->type==*(Typelog*)dataType && ((Logement*)l->data)->dispo==vrai && ((Logement*)l->data)->handicap==*(Booleen*)dataHandi)
			return l;
		l=l->suiv;
	}
	return NULL;
}

/*
Nom : existeEtud
Finalité : Chercher si un étudiant existe

Description Général :
	Teste si la liste est vide
	Teste si l'identifiant de l'etudient est plus petit que celui que l'on cherche
	Teste si l'identifiant de l'etudient est egal à celui que l'on cherche
		Retourne la Le maillon de la liste de l'étudiant cherché

Variables :
	l 			Liste d'étudiant
	data 		Identifiant de l'étudiant recherché
*/
Liste existeEtud(Liste l, void* data){
	if(vide(l))
		return NULL;
	if(strcmp((char*)data,((Etudiant*)tete(l))->idEtud)<0) //que si la liste est triée
		return NULL;
	if(strcmp((char*)data,((Etudiant*)tete(l))->idEtud)==0)
		return l;
	return existeEtud(l->suiv,data);
}

/*
Nom : existeNomCite
Finalité : Chercher si une cité universitaire existe

Description Général :
	Teste si la liste est vide
	Teste si le nom de la cité est plus petit que celui que l'on cherche
	Teste si le nom de la cité est egal à celui que l'on cherche
		Retourne vrai ou faux

Variables :
	l 			Liste de Logement
	data 		Identifiant de la cité universitaire recherchée
*/
Booleen existeNomCite(Liste l, void* data){
	if(vide(l)){
		return faux;
	}
	if(strcmp((char*)data,((Logement*)tete(l))->nom)<0){ //que si la liste est triée
		return faux;
	}
	if(strcmp((char*)data,((Logement*)tete(l))->nom)==0){
		return vrai;
	}
	return existeNomCite(l->suiv,data);
}

/*
Nom : fAddDemandeLog
Finalité : Ajouter une demande de logement et un étudiant si il n'existe pas encore

Description Général :
	Création de la demande
	Saisie de l'identifiant del'étudiant
		Si inexistant appel de la fonction de création de l'étudiant
	Saisie du reste des informations de la demande
	Insertion de la demande dans la liste

Variables :
	demande		Liste de demande en attente
	etud 		Liste d'étudiants
	logement 	Liste de logement
	demandeA 	Nouvelle demande
	charTmp 	Chaîne de caractères temporaire pour les saisies
	etudTmp		Liste d'étudiant temporaire
*/
Liste fAddDemandeLog(Liste demande,Liste *etud,Liste logement){
	DemandeA *demandeA;
	char charTmp[100];
	Liste etudTmp;
	demandeA=(DemandeA*)malloc(sizeof(DemandeA));
	if(demandeA==NULL){
		printf("erreur malloc\n");
		exit(1);
	}
	choixIdDemande(demande,demandeA->idDemande);
	printf("Saisir l'identifiant de l'étudiant :\n");
	scanf("%s%*c",demandeA->idEtud);
	while(!testId(demandeA->idEtud)){
		printf("Saisir l'identifiant de l'étudiant :\n");
		scanf("%s%*c",demandeA->idEtud);
	}
	etudTmp=existeEtud(*etud,demandeA->idEtud);
	if(etudTmp==NULL){
		printf("L'étudiant n°%s n'existe pas encore\n",demandeA->idEtud);
		*etud=fAddEtud(*etud, demandeA->idEtud);
	}
	etudTmp=existeEtud(*etud,demandeA->idEtud);
	if(((Etudiant*)etudTmp->data)->bourse==vrai)
		demandeA->echelon=((Etudiant*)etudTmp->data)->echelon;
	else
		demandeA->echelon=0;
	printf("Saisir la cité :\n");
	fgets(charTmp,99,stdin);
	charTmp[strlen(charTmp)-1]='\0';
	while(!existeNomCite(logement,charTmp)){
		printf("test2\n");
		printf("Cité invalide, Saisir la cité :\n");
		fgets(charTmp,99,stdin);
		charTmp[strlen(charTmp)-1]='\0';
	}
	demandeA->nomCite=(char*)malloc(strlen(charTmp)*sizeof(char));
	if(demandeA->nomCite==NULL){
		printf("erreur malloc\n");
		exit(1);
	}
	strcpy(demandeA->nomCite,charTmp);
	printf("Saisir type de logement (chambre/studio/T1/T2) :\n");
	scanf("%s%*c",charTmp);
	while(strcmp(charTmp,"chambre")!=0 && strcmp(charTmp,"studio")!=0 && strcmp(charTmp,"T1")!=0 && strcmp(charTmp,"T2")!=0){
		printf("Type logement invalide. Saisir type de logement (chambre/studio/T1/T2) :\n");
		scanf("%s%*c",charTmp);
	}
	if(strcmp(charTmp,"chambre")==0)
		demandeA->type=chambre;
	else {
		if(strcmp(charTmp,"studio")==0)
			demandeA->type=studio;
		else{
			if(strcmp(charTmp,"T1")==0)
				demandeA->type=T1;
			else
				demandeA->type=T2;
		}
	}
	demande = insertionDemande(demande,demandeA);
	return demande;
}

/*
Nom : choixIdDemande
Finalité : Choisir un identifiant pour la nouvelle demande de manière automatique

Description Général :
	Parcour des demandes
	Récupération de l'identifiant de la demande
	Test si l'identifiant est different du précedent +1
	attribué celui-ci à la nouvelle demande

Variables :
	demande		Liste de demande en attente
	tab2	 	Identifiant de la nouvelle demande
	i 		 	Compteur
	tab 		Identifiant de la demande déja utilisé
*/
void choixIdDemande(Liste demande, char tab2[]){
	int i=1;
	char tab[6];
	while(!vide(demande)){
		strcpy(tab,((DemandeA*)demande->data)->idDemande+1);
		if((((int)tab[0]-48)*10000+((int)tab[1]-48)*1000+((int)tab[2]-48)*100+((int)tab[3]-48)*10+((int)tab[4]-48))!=i){
			break;
		}
		i++;
		demande=demande->suiv;
	}
	tab2[0]='D';
	sprintf (tab2+1, "%d", i/10000) ;
	i=i-i/10000;
	sprintf (tab2+2, "%d", i/1000) ;
	i=i-i/1000;
	sprintf (tab2+3, "%d", i/100) ;
	i=i-i/100;
	sprintf (tab2+4, "%d", i/10) ;
	i=i-i/10;
	sprintf (tab2+5, "%d", i) ;
	tab2[6]='\0';
}

/*
Nom : fAddEtud
Finalité : Ajouter un étudiant

Description Général :
	Création de l'étudiant'
	Saisie des informations de l'étudiant
	Insertion de l'étudiant dans la liste

Variables :
	etud		Liste d'étudiants
	etudtmp	 	Nouvel étudiant
	idEtud 		Identifiant du nouvel étudiant
	charTmp 	Chaîne de caractères temporaire pour les saisies
*/
Liste fAddEtud(Liste etud, char* idEtud){
	Etudiant *etudTmp;
	char charTmp[100];
	etudTmp=(Etudiant*)malloc(sizeof(Etudiant));
	if(etudTmp==NULL){
		printf("erreur malloc\n");
		exit(1);
	}
	printf("Ajout de l'étudiant n°%s :\n",idEtud);
	strcpy(etudTmp->idEtud,idEtud);
	printf("Saisir sa civilité (Mr/Mme) :\n");
	scanf("%s%*c",charTmp);
	while(strcmp(charTmp,"Mr")!=0 && strcmp(charTmp,"Mme")!=0){
		printf("Civilité invalide. Saisir sa civilité (Mr/Mme) :\n");
		scanf("%s%*c",charTmp);
	}
	if(strcmp(charTmp,"Mr")==0)
		etudTmp->civilite=Mr;
	else
		etudTmp->civilite=Mme;
	printf("Saisir son Nom :\n");
	fgets(charTmp,99,stdin);
	charTmp[strlen(charTmp)-1]='\0';
	etudTmp->nom=(char*)malloc(strlen(charTmp)*sizeof(char));
	if(etudTmp->nom==NULL){
		printf("erreur malloc\n");
		exit(1);
	}
	strcpy(etudTmp->nom,charTmp);
	printf("Saisir son prénom :\n");
	fgets(charTmp,99,stdin);
	charTmp[strlen(charTmp)-1]='\0';
	etudTmp->prenom=(char*)malloc(strlen(charTmp)*sizeof(char));
	strcpy(etudTmp->prenom,charTmp);
	printf("Est-il boursier ? (oui/non)\n");
	etudTmp->bourse=saisieBooleen();
	if(etudTmp->bourse==vrai){
		printf("Saisir l'échelon de bourse : (1-7)\n");
		scanf("%d",&etudTmp->echelon);
		while(etudTmp->echelon<1 || etudTmp->echelon>7){
			printf("Echelon invalide. Saisir l'échelon de bourse : (1-7)\n");
			scanf("%d",&etudTmp->echelon);
		}
	}
	printf("Est-il handicapé ? (oui/non)\n");
	etudTmp->handicap=saisieBooleen();
	etud=insertionEtud(etud,etudTmp);
	return etud;
}

/*
Nom : testId
Finalité :Tester si le format de l'identifiant est correcte

Description Général :
	Teste de la taille de l'identifiant
	Teste de son contenue

Variables :
	id 			Identifiant
*/
Booleen testId(char* id){
	if(strlen(id)!=6){
		printf("Identifiant invalide. Il doit contenir 6 caractères de la forme (L00000/E00000/D00000)\n");
		return faux;
	}
	if(id[0]!='D' && id[0]!='L' && id[0]!='E'){
		printf("Identifiant invalide. Le premier caractère doit être L/E/D\n");
		return faux;
	}
	return vrai;
}

/*
Nom : saisieBooleen
Finalité : Saisir une information de type oui ou non

Description Général :
	Saisie de la réponse
	Teste de son contenue

Variables :
	charTmp 		Chaîne de caractères temporaire pour les saisies
*/
Booleen saisieBooleen(void){
	char charTmp[100];
	scanf("%s%*c",charTmp);
	while(strcmp(charTmp,"oui")!=0 && strcmp(charTmp,"non")!=0){
		printf("Réponse invalide. Est-il handicapé ? (oui/non)\n");
		scanf("%s%*c",charTmp);
	}
	if(strcmp(charTmp,"oui")==0)
		return vrai;
	else
		return faux;
}

//Sebastien

/*
Nom : chargeLogement
Finalité : Charger le tableau logement

Description Général :
	crée une nouvelle liste
	charge la liste logement depuis le fichier correspondant
	retourne la liste

Variables :
	l		liste logement
	log		variable de type logement
*/

Liste chargeLogement(void)
{
	Liste l=listenouv();
	Logement *log; 
	FILE *flot;
	flot=fopen("fichiers/logement.fic","r");
	if (flot == NULL)
	{
		printf("Problème ouverture logement\n");
		exit(1);
	}
	log = lectureLogement(flot);
	while(!feof(flot))
	{
		l=insertionLog(l,log);
		log = lectureLogement(flot);
	}
	fclose(flot);
	return l;
}

/*
Nom : lectureLogement
Finalité : lire un logement

Description Général :
	fait la lecture d'un logement
	depuis le fichier donner en argument
	et retourne le logement

Variables :
	log		variable de type logement
*/

Logement* lectureLogement(FILE *flot)
{
	Logement *log;
	log=(Logement*)malloc(sizeof(Logement));
	char tab[50];
	fscanf(flot,"%s%*c",log->idLogement);
	fgets(tab,49,flot);
	tab[strlen(tab)-1]='\0';
	log->nom = (char*) malloc ((strlen(tab)+1)*sizeof(char));
	if (log->nom == NULL)
	{
		printf("Erreur malloc nom\n");
		exit(1);
	}
	strcpy(log->nom,tab);
	fscanf(flot,"%d%*c",&log->type);
	fscanf(flot,"%d%*c",&log->dispo);
	fscanf(flot,"%d%*c",&log->handicap);
	if (log->dispo == faux)
		fscanf(flot,"%s%*c",log->idEtud);
	return log;
}

/*
Nom : insertionLog
Finalité : inserre les logment dans la liste

Description Général :
	inserre par ordre alphabétique les logements
*/

Liste insertionLog(Liste l, void* data){
	if(vide(l))
		return insererEnTete(l,data);
	if(strcmp(((Logement*)data)->nom,((Logement*)l->data)->nom)<0)
		return insererEnTete(l,data);
	if(strcmp(((Logement*)data)->nom,((Logement*)l->data)->nom)==0)
		return insererEnTete(l,data);
	l->suiv=insertionLog(l->suiv,data);
	return l;
}

/*
Nom : chargeEtud
Finalité : Charger le tableau etudiant

Description Général :
	crée une nouvelle liste
	charge la liste etudiant depuis le fichier correspondant
	retourne la liste

Variables :
	l		liste etudiant
	log		variable de type etudiant
*/

Liste chargeEtud(void)
{
	Liste l=listenouv();
	Etudiant *log; 
	FILE *flot;
	flot=fopen("fichiers/etudiants.fic","r");
	if (flot == NULL)
	{
		printf("Problème ouverture logement\n");
		exit(1);
	}
	log = lectureEtud(flot);
	while(!feof(flot))
	{
		l=insertionEtud(l,log);
		log = lectureEtud(flot);
	}
	fclose(flot);
	return l;
}

/*
Nom : lectureEtud
Finalité : lire un étudiant

Description Général :
	fait la lecture d'un étudiant
	depuis le fichier donné en argument
	retourne l'étudiant

Variables :
	etud		variable de type etudiant
*/

Etudiant* lectureEtud(FILE *flot)
{
	Etudiant *etud;
	etud=(Etudiant*)malloc(sizeof(Etudiant));
	char tab[50];
	fscanf(flot,"%s%*c",etud->idEtud);
	fscanf(flot,"%d%*c",&etud->civilite);
	fgets(tab,49,flot);
	tab[strlen(tab)-1]='\0';
	etud->nom = (char*) malloc ((strlen(tab)+1)*sizeof(char));
	if (etud->nom == NULL)
	{
		printf("Erreur malloc nom\n");
		exit(1);
	}
	strcpy(etud->nom,tab);
	fgets(tab,49,flot);
	tab[strlen(tab)-1]='\0';
	etud->prenom = (char*) malloc ((strlen(tab)+1)*sizeof(char));
	if (etud->prenom == NULL)
	{
		printf("Erreur malloc nom\n");
		exit(1);
	}
	strcpy(etud->prenom,tab);
	fscanf(flot,"%d%*c",&etud->bourse);
	if(etud->bourse==vrai){
		fscanf(flot,"%d%*c",&etud->echelon);
	}
	fscanf(flot,"%d%*c",&etud->handicap);
	return etud;
}

/*
Nom : insertionEtud
Finalité : inserre les étudiant dans la liste

Description Général :
	inserre les l'étudiant dans la liste
	par ordre alphabétique
*/

Liste insertionEtud(Liste l, void* data){
	if(vide(l)){
		return insererEnTete(l,data);
	}
	if(strcmp(((Etudiant*)data)->idEtud,((Etudiant*)l->data)->idEtud)<0){
		return insererEnTete(l,data);
	}
	if(strcmp(((Etudiant*)data)->idEtud,((Etudiant*)l->data)->idEtud)==0){
		return insererEnTete(l,data);
	}
	l->suiv=insertionEtud(l->suiv,data);
	return l;
}

/*
Nom : chargeDemande
Finalité : Charger le tableau demande

Description Général :
	crée une nouvelle liste
	charge la liste demande depuis le fichier correspondant
	retourne la liste

Variables :
	l		liste demande
	demande		variable de type demande
*/

Liste chargeDemande(void)
{
	Liste l=listenouv();
	DemandeA *demande; 
	FILE *flot;
	flot=fopen("fichiers/demandesEnAttente.fic","r");
	if (flot == NULL)
	{
		printf("Problème ouverture logement\n");
		exit(1);
	}
	demande = lectureDemande(flot);
	while(!feof(flot))
	{
		l=insertionDemande(l,demande);
		demande = lectureDemande(flot);
	}
	// l=insertionDemande(l,demande);
	fclose(flot);
	return l;
}

/*
Nom : lectureDemande
Finalité : lire une demande

Description Général :
	fait la lecture d'une demande
	depuis le fichier donné en argument
	retourne la demande

Variables :
	demande		variable de type demande
*/

DemandeA* lectureDemande(FILE *flot)
{
	DemandeA *demande;
	demande=(DemandeA*)malloc(sizeof(DemandeA));
	char tab[50];
	fscanf(flot,"%s%*c",demande->idDemande);
	fscanf(flot,"%s%*c",demande->idEtud);
	fscanf(flot,"%d%*c",&demande->echelon);
	fgets(tab,49,flot);
	tab[strlen(tab)-1]='\0';
	demande->nomCite = (char*) malloc ((strlen(tab)+1)*sizeof(char));
	if (demande->nomCite == NULL)
	{
		printf("Erreur malloc nom\n");
		exit(1);
	}
	strcpy(demande->nomCite,tab);
	fscanf(flot,"%d%*c",&demande->type);
	return demande;
}

/*
Nom : insertionDemmande
Finalité : inserre les demandes dans la liste

Description Général :
	inserre les demandes dans la liste
	par ordre alphabétique
	
Variables :
	l		liste des demandes
	data		la demande à inserer
*/

Liste insertionDemande(Liste l, void* data){
	if(vide(l)){
		return insererEnTete(l,data);
	}
	if(((DemandeA*)data)->echelon>((DemandeA*)l->data)->echelon){
		return insererEnTete(l,data);
	}
	if(((DemandeA*)data)->echelon==((DemandeA*)l->data)->echelon){
		return insererEnTete(l,data);
	}
	l->suiv=insertionDemande(l->suiv,data);
	return l;
}

/*
Nom : Affichlog
Finalité : afficher la liste logement

Description Général :
	afficher les logements innocupés
	depuis la liste donné en argument
	
Variables :
	logement		liste logement a afficher
*/

void AffichLog(Liste logement)
{
	printf("idLogement\ttype logement\thandicap\tnom\n");
	printf("------------------------------------------------------------------\n");
	while(vide(logement)==faux)
	{
		if (((Logement*)logement->data)->dispo==vrai){
			printf("%s\t\t",((Logement*)logement->data)->idLogement);
			if (((Logement*)logement->data)->type==0)
				printf("chambre\t\t");
			if (((Logement*)logement->data)->type==1)
				printf("studio\t\t");
			if (((Logement*)logement->data)->type==2)
				printf("T1\t\t");
			if (((Logement*)logement->data)->type==3)
				printf("T2\t\t");
			if (((Logement*)logement->data)->handicap==vrai)
				printf("oui\t\t");
			else
				printf("non\t\t");
			printf("%s\n",((Logement*)logement->data)->nom);
		}
		logement=logement->suiv;
	}
}

/*
Nom : AffichlogOcup
Finalité : afficher la liste logement occupé

Description Général :
	afficher les logements occupé
	avec le nom de l'ocupant
	
Variables :
	logement		liste logement a afficher
	etud			liste des etudiants
*/

void AffichLogOcup(Liste logement,Liste etud)
{
	printf("idEtud\ttype\tnom\t\tprenom\t\tidLogement\tnom logement\n");
	printf("---------------------------------------------------------------\n");
	while(vide(logement)==faux)
	{
		if (((Logement*)logement->data)->dispo==faux){
			printf("%s",((Logement*)logement->data)->idEtud);
			if (((Logement*)logement->data)->type==0)
				printf("\tchambre\t");
			if (((Logement*)logement->data)->type==1)
				printf("\tstudio\t");
			if (((Logement*)logement->data)->type==2)
				printf("\tT1\t");
			if (((Logement*)logement->data)->type==3)
				printf("\tT2\t");
			nomEtPrenom(logement,etud);
			printf("%s\t\t%s\n",((Logement*)logement->data)->idLogement,((Logement*)logement->data)->nom);
		}
		logement=logement->suiv;
	}
	printf("\n");
}

/*
Nom : nomEtPrenom
Finalité : trouver l'étudiant qui occupe le logement

Description Général :
	parcour la liste étudiant pour trouver
	l'étudiant qui correspond au logement
	et affiche son nom et son prénom
	
Variables :
	logement		liste logement
	etud			liste des etudiants
*/

void nomEtPrenom(Liste logement, Liste etud)
{
	while(vide(etud)==faux)
	{
		if (strcmp(((Logement*)logement->data)->idEtud,((Etudiant*)etud->data)->idEtud)==0){
			printf("%s\t",((Etudiant*)etud->data)->nom);
			if(strlen(((Etudiant*)etud->data)->nom)<8)
				printf("\t");
			printf("%s\t",((Etudiant*)etud->data)->prenom);
			if(strlen(((Etudiant*)etud->data)->prenom)<8)
				printf("\t");
			return;
		}
		etud=etud->suiv;
	}
	printf("\tEtudiant inconnu\n");
	printf("ERREUR\n");
	exit(1);
}

/*
Nom : AffichDemande
Finalité : afficher la liste demande

Description Général :
	affiche l'intégralité de la liste des demandes
	
Variables :
	demande		liste des demandes
*/

void AffichDemande(Liste demande)
{
	printf("idDemande\tidEtud\techelon\ttype\tnom de cité\n");
	printf("--------------------------------------------------------------\n");
	while(vide(demande)==faux)
	{
		printf("%s\t\t%s\t%d",((DemandeA*)demande->data)->idDemande,((DemandeA*)demande->data)->idEtud,((DemandeA*)demande->data)->echelon);
		if (((DemandeA*)demande->data)->type==0)
			printf("\tchambre\t");
		if (((DemandeA*)demande->data)->type==1)
			printf("\tstudio\t");
		if (((DemandeA*)demande->data)->type==2)
			printf("\tT1\t");
		if (((DemandeA*)demande->data)->type==3)
			printf("\tT2\t");
		printf("%s\n",((DemandeA*)demande->data)->nomCite);
		demande=demande->suiv;
	}
}

/*
Nom : fAnnulDemande
Finalité : Annulation d'une demande de logement

Description Général :
	demande à l'utilisateur l'identifiant de la demande à annuler
	cherche cette demande dans la liste demande
	supprimer la demande si présente dans la liste demande

Variables :
	demande 	liste des demandes
*/

Liste fAnnulDemande(Liste demande){
	char idDemandeSup[7]={0};
	Liste demBis = demande;
	if(vide(demBis))
	{
		printf("Aucune demandes à supprimer\n");
		return demande;
	}
	printf("Tapez l'identifiant de la demande à supprimer\n");
	scanf("%s",idDemandeSup);
	
	while(vide(demBis)==faux)
	{
		if(strcmp(idDemandeSup, ((DemandeA*)demBis->data)->idDemande)==0)
		{
			demande=supprimerDemande(demande, &demBis);
			return demande;
		}
		demBis=demBis->suiv;
	}
	printf("Demande non existante\n");
	return demande;
}
