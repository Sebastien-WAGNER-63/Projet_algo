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

//Liste de Logement
typedef struct maillLog{
  Logement logement;
  struct maillLog *suiv;
}MaillLog, *ListLog;

//Liste d'étudiant
typedef struct maillEtud{
  Etudiant etudiant;
  struct maillEtud *suiv;
}MaillEtud, *ListEtud;

//Liste de demande
typedef struct maillDemande{
  DemandeA demande;
  struct maillDemande *suiv;
}MaillDemande, *ListDemande;

void global(void);
//Q1
void fChargementFic(Liste logement, Liste etud, Liste demande);
//Q2
void fAffichageLogTri(Liste logement);
//Q3
void fAffichageLogOcc(Liste logement);
//Q4
void fAffichageLogAtt(Liste demande);
//Q5
void fTraitementDem(Liste demande,Liste logement,Liste etud);
Booleen existeNom(Liste l, void* data);
Booleen existeType(Liste l, void* data);
Booleen existeDispo(Liste l, void* data);
Booleen existeHandic(Liste l, void* data);
Liste existeEtud(Liste l, void* data);
Liste repDemande(Liste l,void* dataNom,void* dataType,void* dataDispo, void* dataHandi);
//Q6
void fAddDemandeLog(Liste demande,Liste etud);
void fAddEtud(Liste etud);
void fEnregGemande(Liste demande,DemandeA demandeA);
//Q7
void fAnnulDemande(Liste demande);
//Q8
void fDepartEtud(Liste logement);
//Q9
void fSauvegarde(Liste demande, Liste logement, Liste etud);
