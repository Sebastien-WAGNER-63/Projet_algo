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

void global(void);

