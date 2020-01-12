#include<stdio.h>
#include<stdlib.h>
#include "projet.h"
#include <math.h>
#include <string.h>

void global(void){
	Liste logement,etud,demande;
	int choix;
	logement=chargeLogement();
	etud=chargeEtud();
	demande=chargeDemande();
	demande=fTraitementDem(demande,logement,etud);
	while(1){
		printf("\n0/\tQUITTER\n");
		printf("1/\tCharger recharger les dernier paramètres enregistrés\n");
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
			default : exit(1); 
		}
	}

}

Liste fTraitementDem(Liste demande,Liste logement,Liste etud){
	Booleen bool=vrai;
	Liste etudTmp, logTmp, demTmp, demTst;
	demTmp=demande;
	while(!vide(demTmp)){
		etudTmp=existeEtud(etud,((DemandeA*)demTmp->data)->idEtud);
		if(etudTmp==NULL){
			printf("La demande n°%s, L'étudiant n°%s n'existe pas\n",((DemandeA*)demTmp->data)->idDemande,((DemandeA*)demande->data)->idEtud);
			demTmp=demTmp->suiv;
			continue;
		}
		logTmp=repDemande(logement,((DemandeA*)demTmp->data)->nomCite, &((DemandeA*)demTmp->data)->type, &bool, &((Etudiant*)etudTmp->data)->handicap);
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

Liste fAddDemandeLog(Liste demande,Liste *etud,Liste logement){
	DemandeA *demandeA;
	char charTmp[100];
	demandeA=(DemandeA*)malloc(sizeof(DemandeA));
	if(demandeA==NULL){
		printf("erreur malloc\n");
		exit(1);
	}
	Liste etudTmp;
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

Liste fAddEtud(Liste etud, char* idEtud){
	Etudiant *etudTmp;
	etudTmp=(Etudiant*)malloc(sizeof(Etudiant));
	if(etudTmp==NULL){
		printf("erreur malloc\n");
		exit(1);
	}
	char charTmp[100];
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
	l=insertionLog(l,log);
	fclose(flot);
	return l;
}

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
	l=insertionEtud(l,log);
	fclose(flot);
	return l;
}

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
	l=insertionDemande(l,demande);
	fclose(flot);
	return l;
}

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

void AffichLog(Liste logement)
{
	printf("idLogement\tnom\t\t\ttype logement\thandicap\n");
	printf("------------------------------------------------------------------\n");
	while(vide(logement)==faux)
	{
		if (((Logement*)logement->data)->dispo==vrai){
			printf("%s\t\t%s\t\t",((Logement*)logement->data)->idLogement,((Logement*)logement->data)->nom);
			if (((Logement*)logement->data)->type==0)
				printf("chambre\t");
			if (((Logement*)logement->data)->type==1)
				printf("studio\t");
			if (((Logement*)logement->data)->type==2)
				printf("T1\t");
			if (((Logement*)logement->data)->type==3)
				printf("T2\t");
			if (((Logement*)logement->data)->handicap==vrai)
				printf("\toui\n");
			else
				printf("\tnon\n");
		}
		logement=logement->suiv;
	}
}

void AffichLogOcup(Liste logement,Liste etud)
{
	printf("idLogement\tnom logement\tidEtud\ttype\tnom\tprenom\n");
	printf("---------------------------------------------------------------\n");
	while(vide(logement)==faux)
	{
		if (((Logement*)logement->data)->dispo==faux){
			printf("%s\t\t%s\t%s",((Logement*)logement->data)->idLogement,((Logement*)logement->data)->nom,((Logement*)logement->data)->idEtud);
			if (((Logement*)logement->data)->type==0)
				printf("\tchambre\t");
			if (((Logement*)logement->data)->type==1)
				printf("\tstudio\t");
			if (((Logement*)logement->data)->type==2)
				printf("\tT1\t");
			if (((Logement*)logement->data)->type==3)
				printf("\tT2\t");
			nomEtPrenom(logement,etud);
		}
		logement=logement->suiv;
	}
	printf("\n");
}

void nomEtPrenom(Liste logement, Liste etud)
{
	while(vide(etud)==faux)
	{
		if (strcmp(((Logement*)logement->data)->idEtud,((Etudiant*)etud->data)->idEtud)==0){
			printf("%s\t%s\n",((Etudiant*)etud->data)->nom,((Etudiant*)etud->data)->prenom);
			return;
		}
		etud=etud->suiv;
	}
	printf("\tEtudiant inconnu\n");
	printf("ERREUR\n");
	exit(1);
}

void AffichDemande(Liste demande)
{
	printf("idDemande\tidEtud\techelon\tnom de cité\t\ttype\n");
	printf("--------------------------------------------------------------\n");
	while(vide(demande)==faux)
	{
		printf("%s\t\t%s\t%d\t%s\t",((DemandeA*)demande->data)->idDemande,((DemandeA*)demande->data)->idEtud,((DemandeA*)demande->data)->echelon,((DemandeA*)demande->data)->nomCite);
		if (((DemandeA*)demande->data)->type==0)
			printf("\tchambre\n");
		if (((DemandeA*)demande->data)->type==1)
			printf("\tstudio\n");
		if (((DemandeA*)demande->data)->type==2)
			printf("\tT1\n");
		if (((DemandeA*)demande->data)->type==3)
			printf("\tT2\n");
		demande=demande->suiv;
	}
}