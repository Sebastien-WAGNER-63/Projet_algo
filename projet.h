#include <stdio.h>

//Different types de logements
typedef enum{
  chambre, studio, T1, T2
}Typelog;

//Type Booléen
typedef enum{
  false, true
}Booleen;

//Different types de civilité
typedef enum{
  Mr, Mme
}Civilite;

//Structure des logements
typedef struct{
  // Forme de idLogement : 'L00001','L00002'...
  char idLogement[6];
  char * nom;
  Typelog type;
  Booleen dispo;
  Booleen handicap;
  // Forme de idEtud : 'E00001','E00002'...
  char idEtud[6];
}Logement;

//Structure des étudiants
typedef struct{
  // Forme de idEtud : 'E00001','E00002'...
  char idEtud[6];
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
  char idDemande[6];
  // Forme de idEtud : 'E00001','E00002'...
  char idEtud[6];
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
//1
void fChargementFic(ListLog logement, ListEtud etud, ListDemande demande);
//2
void fAffichageLogTri(ListLog logement);
//3
void fAffichageLogOcc(ListLog logement);
//4
void fAffichageLogAtt(ListDemande demande);
//5
void fTraitementDem(ListDemande demande,ListLog logement,ListEtud etud);
//6
void fAddDemandeLog(ListDemande demande,ListEtud etud);
void fAddEtud(ListEtud etud);
void fEnregGemande(ListDemande demande,DemandeA demandeA);
//7
void fAnnulDemande(ListDemande demande);
//8
void fDepartEtud(ListLog logement);
//9
void fSauvegarde(ListDemande demande, ListLog logement, ListEtud etud);
