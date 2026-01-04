#ifndef Jeu_de_2048
#define Jeu_de_2048

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>

// variables
extern int jeuencourt;
extern int n;
extern int **tableau;
extern int **tableau1;
extern int **tableau2;
extern int gamemode;

// console
void clear_screen();

// tableaux
void generetableau();
void generetableau_duo();
void charger_puzzle(char *nom_fichier);
void liberer_tableau();
void liberer_tableaux_duo();
void clean(int **tableau);

// affichages
void afficher(int **tableau);
void afficher_double(int **tableau1, int **tableau2);
void afficher_puzzle(int **tableau);

// deplacements
int deplacementgauche(int **tableau);
int deplacementdroite(int **tableau);
int deplacementhaut(int **tableau);
int deplacementbas(int **tableau);
int deplacementgauche_puzzle(int **tableau);
int deplacementdroite_puzzle(int **tableau);
int deplacementhaut_puzzle(int **tableau);
int deplacementbas_puzzle(int **tableau);

// creation + input
void generer(int **tableau);
void generer_puzzle(int **tableau);
int input(int **tableau, int mode);

// score + verifications
int calculer_score(int **tableau);
void Verifier();
void Verifier_duo();
void Verifier_puzzle();

// principal
void Start();

#endif
