#include <stdio.h>
#include "fonctionsListe.h"

//Structure des logements
typedef struct{
  // Forme de idLogement : 'L00001','L00002'...
  char idLogement[7];
  char * nom;
  Typelog type;
  Booleen dispo;
  Booleen handicap;
  // Forme de idEtud : 'E00001','E00002'...
  char idEtud[7];
}Logement;

//Structure des étudiants
typedef struct{
  // Forme de idEtud : 'E00001','E00002'...
  char idEtud[7];
  Civilite civilite;
  char *nom;
  char *prenom;
  Booleen bourse;
  int echelon;
  Booleen handicap;
}Etudiant;

//Structure des Demandes en Attente
typedef struct{
  // Forme de idDemande : 'D00001','D00002'...
  char idDemande[7];
  // Forme de idEtud : 'E00001','E00002'...
  char idEtud[7];
  int echelon;
  char *nomCite;
  Typelog type;
}DemandeA;

void global(void);
//Q1
Liste chargeLogement();
Logement *lectureLogement(FILE *flot);
void AffichLog(Liste logement);
Liste insertionLog(Liste l, void* data);
Liste chargeEtud(void);
Etudiant* lectureEtud(FILE *flot);
Liste insertionEtud(Liste l, void* data);
Liste chargeDemande(void);
DemandeA* lectureDemande(FILE *flot);
Liste insertionDemande(Liste l, void* data);

void AffichLog(Liste logement);
void AffichLogOcup(Liste logement,Liste etud);
void nomEtPrenom(Liste logement, Liste etud);
void AffichDemande(Liste demande);
//Q5
Liste fTraitementDem(Liste demande,Liste logement,Liste etud);
Booleen existeNom(Liste l, void* data);
Booleen existeType(Liste l, void* data);
Booleen existeDispo(Liste l, void* data);
Booleen existeHandic(Liste l, void* data);
Liste existeEtud(Liste l, void* data);
Liste repDemande(Liste l,void* dataNom,void* dataType,void* dataDispo, void* dataHandi);
Booleen saisieBooleen(void);
//Q6
Liste fAddDemandeLog(Liste demande,Liste *etud,Liste logement);
Liste supprimerDemande(Liste l, Liste *data);
Liste fAddEtud(Liste etud, char* idEtud);
Booleen testId(char* id);
void choixIdDemande(Liste demande, char tab2[]);
Booleen existeNomCite(Liste l, void* data);
//Q7
void fAnnulDemande(Liste demande);
//Q8
void fDepartEtud(Liste logement);
//Q9
void fSauvegarde(Liste demande, Liste logement, Liste etud);