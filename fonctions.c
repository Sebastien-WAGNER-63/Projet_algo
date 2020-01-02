Liste listenouv (void){
	Liste l;
	l=NULL;
	return l;
}

Liste insererEnTete (Liste l, int x){
	maillon *m;
	m=(maillon *) malloc (sizeof(maillon));
	if(m==NULL){
		printf("Pb malloc\n");
		exit(1);
	}
	m->v=x;
	m->suiv=l;
	return m;
}

Booleen vide (Liste l){
	if(l==NULL)
		return vrai;
	return faux;
}

//version it
void affichageListeIt (Liste l){
	while(!vide(l)){
		printf("%d",l->v);
		l=l->suiv;
	}
	printf("\n");
}

//version rec
void affichageListeRec (Liste l){
	if(vide(l)){
		printf("\n");
		return;
	}
	printf("%d",l->v);
	affichageListeRec(l->suiv);
}

int tete (Liste l){
	if(vide(l)){
		printf("opperation interdite\n");
		exit(1);
	}
	return l->v;
}

//version it
int longueurIt (Liste l){
	int cpt=0;
	while(!vide(l)){
		cpt++;
		l=l->suiv;
	}
	return cpt;
}

//version rec
int longueurRec (Liste l){
	if(vide(l))
		return 0;
	return 1 + longueurRec(l->suiv);
}

Booleen existe (Liste l, int x){
	if(vide(l))
		return faux;
	if(x<tete(l)) //que si la liste est triée
		return faux;
	if (x==tete(l))
		return vrai;
	return existe(l->suiv,x);
}

Liste supprimerEnTete (Liste l){
	maillon *m;
	if(vide(l)){
		printf("opération interdite\n");
		exit(0);
	}
	m=l;
	l=l->suiv;
	free(m);
	return l;
}

Liste insertion (Liste l, int x){
	if(vide(l))
		return insererEnTete(l,x);
	if(x<tete(l))
		return insererEnTete(l,x);
	if(x==tete(l))
		return l;
	l->suiv=insertion(l->suiv,x);
	return l;
}

Liste supprimer (Liste l, int x){
	if(vide(l))
		return l;
	if(x<tete(l))
		return l;
	if(x==tete(l))
		return supprimerEnTete(l):
	l->suiv=supprimer(l->suiv,x);
	return l;
}

liste insertionEnQueu (Liste l, int x){
	if(vide(l))
		return insererEnTete(l,x);
	l->suiv=insertionEnQueu(l->suiv,x);
	return l;
}

void supprimerListe(Liste l){
	while(!vide(l))
		l=supprimerEnTete(l);
}
