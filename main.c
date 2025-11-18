#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif
#define n 4
int jeuencourt = 0;
int tableau[n][n];

// fonction qui nettoie le terrain de jeu
void clean(int tableau[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            tableau[i][j] = 0;
}

//fonction qui affiche le terrain de jeu
void afficher(int tableau[n][n])
{
    // Ligne du haut
    printf("┌────");
    for (int j = 1; j < n; j++) printf("┬────");
    printf("┐\n");

    for (int i = 0; i < n; i++)
    {
        // Contenu des cases
        for (int j = 0; j < n; j++)
        {
            int val = tableau[i][j];

            if (val == 0) {
                printf("│    ");
            } else {
                switch(val) {
                    case 2:
                        printf("│ \033[32m%2d\033[0m ", val);
                        break;
                    case 4:
                        printf("│ \033[33m%2d\033[0m ", val);
                        break;
                    case 8:
                        printf("│ \033[31m%2d\033[0m ", val);
                        break;
                    case 16:
                        printf("│ \033[36m%2d\033[0m ", val);
                        break;
                    case 32:
                        printf("│ \033[35m%2d\033[0m ", val);
                        break;
                    case 64:
                        printf("│ \033[34m%2d\033[0m ", val);
                        break;
                    default:
                        printf("│ \033[1;37m%2d\033[0m ", val);
                        break;
                }
            }
        }
        printf("│\n");

        // Séparateur entre les lignes
        if (i < n - 1) {
            printf("├────");
            for (int j = 1; j < n; j++) printf("┼────");
            printf("┤\n");
        }
    }

    // Ligne du bas
    printf("└────");
    for (int j = 1; j < n; j++) printf("┴────");
    printf("┘\n");
}

// fonction qui gère le déplacement vers la gauche
void deplacementgauche(int tableau[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (tableau[i][j] != 0) {
                int k = j;
                while (k > 0 && tableau[i][k - 1] == 0) {
                    tableau[i][k - 1] = tableau[i][k];
                    tableau[i][k] = 0;
                    k--;
                }
                if (k > 0 && tableau[i][k - 1] == tableau[i][k]) {
                    tableau[i][k - 1] *= 2;
                    tableau[i][k] = 0;
                }
            }
        }
    }
}

// fonction qui gère le déplacement vers la droite
void deplacementdroite(int tableau[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = n - 2; j >= 0; j--) {
            if (tableau[i][j] != 0) {
                int k = j;
                while (k < n - 1 && tableau[i][k + 1] == 0) {
                    tableau[i][k + 1] = tableau[i][k];
                    tableau[i][k] = 0;
                    k++;
                }
                if (k < n - 1 && tableau[i][k + 1] == tableau[i][k]) {
                    tableau[i][k + 1] *= 2;
                    tableau[i][k] = 0;
                }
            }
        }
    }
}

// fonction qui gère le déplacement vers le haut
void deplacementhaut(int tableau[n][n]) {
    for (int j = 0; j < n; j++) { // colonne par colonne
        for (int i = 1; i < n; i++) {
            if (tableau[i][j] != 0) {
                int k = i;
                while (k > 0 && tableau[k - 1][j] == 0) {
                    tableau[k - 1][j] = tableau[k][j];
                    tableau[k][j] = 0;
                    k--;
                }
                if (k > 0 && tableau[k - 1][j] == tableau[k][j]) {
                    tableau[k - 1][j] *= 2;
                    tableau[k][j] = 0;
                }
            }
        }
    }
}

// fonction qui gère le déplacement vers le bas
void deplacementbas(int tableau[n][n]) {
    for (int j = 0; j < n; j++) {
        for (int i = n - 2; i >= 0; i--) {
            if (tableau[i][j] != 0) {
                int k = i;
                while (k < n - 1 && tableau[k + 1][j] == 0) {
                    tableau[k + 1][j] = tableau[k][j];
                    tableau[k][j] = 0;
                    k++;
                }
                if (k < n - 1 && tableau[k + 1][j] == tableau[k][j]) {
                    tableau[k + 1][j] *= 2;
                    tableau[k][j] = 0;
                }
            }
        }
    }
}

//fonction pour recuperer les direction joueurs
void input() {
    char c;
    printf("\nVers où souhaitez-vous faire glisser le tableau ? ");
    scanf(" %c", &c);

    switch(c) {
        case 'z':
            deplacementhaut(tableau);
            printf("\n");
            break;
        case 's':
            deplacementbas(tableau);
            printf("\n");
            break;
        case 'q':
            deplacementgauche(tableau);
            printf("\n");
            break;
        case 'd':
            deplacementdroite(tableau);
            printf("\n");
            break;
        default:
            printf("Touche non valide\n");
            break;
    }
}

// fonction qui génère les petits blocs
void generer(int tableau[n][n]) {
    int x = rand() % n;
    int y = rand() % n;
    while (tableau[x][y] != 0) {  // ne place que sur une case vide
        x = rand() % n;
        y = rand() % n;
    }
    if (rand() % 10 == 7) {
        tableau[x][y] = 4;
    } else {
        tableau[x][y] = 2;
    }
}

//fonction pour verifier qu'il y ai toujours une option de mouvement
void Verifier() {
    int checklist = 0;

    // compter les cases non vides
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (tableau[i][j] != 0) {
                checklist++;
            }
        }
    }

    // si toutes les cases sont pleines
    if (checklist == n * n) {

        int merge_possible = 0;

        // vérifier les merges possibles
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {

                // case de droite (si elle existe)
                if (j < n - 1 && tableau[i][j] == tableau[i][j + 1]) {
                    merge_possible = 1;
                    break;
                }

                // case du bas (si elle existe)
                if (i < n - 1 && tableau[i][j] == tableau[i + 1][j]) {
                    merge_possible = 1;
                    break;
                }
            }

            if (merge_possible) break;
        }

        if (!merge_possible) {
            printf("Toutes les cases sont pleines et aucun merge n'est possible. Fin du jeu !\n");
            jeuencourt = 0;
        }
        else {
            printf("Toutes les cases sont pleines mais un merge est encore possible.\n");
        }
    }
}



int main() {

    #ifdef _WIN32 //pour afficher correctement dans le terminale les couleures
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hConsole, &mode);
    SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    #endif
    SetConsoleOutputCP(CP_UTF8); // pour afficher correctement les caracteres speciaux (le tableau)
    SetConsoleCP(CP_UTF8);

    srand(time(NULL)); // preparer l'aleatoire et le tableau
    clean(tableau);
    generer(tableau);
    generer(tableau);
    afficher(tableau); //lancer le jeu
    jeuencourt = 1;
    do {
        input(tableau);
        generer(tableau);
        afficher(tableau);
        Verifier();
    } while (jeuencourt == 1);

    return 0;
}