#include "Header_Projet_IF2B_RHYWNP.h"

// Fonction pour effacer l'écran (trouvé sur Stack Overflow)
void clear_screen() {
    printf("\033[2J\033[H");
    fflush(stdout);
}

int jeuencourt = 0;
int n;
int **tableau, **tableau1, **tableau2;
int gamemode = 0;

// === Fonction de preparation des Terrains de Jeux

// Fonction pour creer le tableau necessaire au mode Classic
void generetableau() {
    tableau = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        tableau[i] = malloc(n * sizeof(int));
}

// Fonction pour creer les deux tableau necessaire au mode Duo
void generetableau_duo() {
    tableau1 = malloc(n * sizeof(int*));
    tableau2 = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        tableau1[i] = malloc(n * sizeof(int));
        tableau2[i] = malloc(n * sizeof(int));
    }
}

// Charge un puzzle depuis un fichier texte
void charger_puzzle(char *nom_fichier) {
    FILE *f = fopen(nom_fichier, "r");
    if (f == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s\n", nom_fichier);
        Sleep(2000);
        return;
    }

    fscanf(f, "%d", &n);
    generetableau();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char val[10];
            fscanf(f, "%s", val);

            if (val[0] == 'X' || val[0] == 'x') {
                tableau[i][j] = -1;
            } else {
                tableau[i][j] = atoi(val);
            }
        }
    }

    fclose(f);
}

// === Fonctions de liberation d'espace

// Fonction pour liberer l'espace dans le cas d'une seconde partie (Memory Leak)
void liberer_tableau() {
    if (tableau != NULL) {
        for (int i = 0; i < n; i++)
            free(tableau[i]);
        free(tableau);
        tableau = NULL;
    }
}

// Fonction pour liberer l'espace dans le cas d'une seconde partie (Memory Leak)
void liberer_tableaux_duo() {
    if (tableau1 != NULL) {
        for (int i = 0; i < n; i++) {
            free(tableau1[i]);
            free(tableau2[i]);
        }
        free(tableau1);
        free(tableau2);
        tableau1 = NULL;
        tableau2 = NULL;
    }
}

// fonction qui nettoie le terrain de jeu
void clean(int **tableau) {
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            tableau[i][j] = 0;
        }
    }
}

// === Fonctions d'affichages ===

// Fonction qui affiche le terrain du mode de jeu en Solo
void afficher(int **tableau){
    clear_screen();  // AJOUT : effacer l'écran

    // Ligne du haut
    printf("\n┌─────");
    for (int j = 1; j < n; j++) printf("┬─────");
    printf("┐\n");

    for (int i = 0; i < n; i++){
        // Contenu des cases
        for (int j = 0; j < n; j++){
            int val = tableau[i][j];

            if (val == 0) {
                printf("│     ");
            } else {
                switch(val) {
                    case 2:
                        printf("│\033[97m%5d\033[0m", val);
                        break;
                    case 4:
                        printf("│\033[37m%5d\033[0m", val);
                        break;
                    case 8:
                        printf("│\033[93m%5d\033[0m", val);
                        break;
                    case 16:
                        printf("│\033[33m%5d\033[0m", val);
                        break;
                    case 32:
                        printf("│\033[91m%5d\033[0m", val);
                        break;
                    case 64:
                        printf("│\033[31m%5d\033[0m", val);
                        break;
                    case 128:
                        printf("│\033[95m%5d\033[0m", val);
                        break;
                    case 256:
                        printf("│\033[35m%5d\033[0m", val);
                        break;
                    case 512:
                        printf("│\033[34m%5d\033[0m", val);
                        break;
                    case 1024:
                        printf("│\033[94m%5d\033[0m", val);
                        break;
                    case 2048:
                        printf("│\033[36m%5d\033[0m", val);
                        break;
                    case 4096:
                        printf("│\033[96m%5d\033[0m", val);
                        break;
                    case 8192:
                        printf("│\033[92m%5d\033[0m", val);
                        break;
                    default:
                        printf("│\033[32m%5d\033[0m", val);
                        break;
                }
            }
        }
        printf("│\n");

        // Séparateur entre les lignes
        if (i < n - 1) {
            printf("├─────");
            for (int j = 1; j < n; j++) {
                printf("┼─────");
            }
            printf("┤\n");
        }
    }

    // Ligne du bas
    printf("└─────");
    for (int j = 1; j < n; j++) {
        printf("┴─────");
    }
    printf("┘\n");

    printf("Z (Haut), Q (Gauche), S (Bas), D (Droite) - E pour quitter\n");
}

void afficher_double(int **tableau1, int **tableau2) {
    clear_screen();

    printf("\n┌─────");
    for (int j = 1; j < n; j++) {
        printf("┬─────");
    }
    printf("┐    ");

    printf("┌─────");
    for (int j = 1; j < n; j++) {
        printf("┬─────");
    }
    printf("┐\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int val = tableau1[i][j];
            if (val == 0) {
                printf("│     ");
            }
            else {
                switch(val) {
                    case 2:
                        printf("│\033[97m%5d\033[0m", val);
                        break;
                    case 4:
                        printf("│\033[37m%5d\033[0m", val);
                        break;
                    case 8:
                        printf("│\033[93m%5d\033[0m", val);
                        break;
                    case 16:
                        printf("│\033[33m%5d\033[0m", val);
                        break;
                    case 32:
                        printf("│\033[91m%5d\033[0m", val);
                        break;
                    case 64:
                        printf("│\033[31m%5d\033[0m", val);
                        break;
                    case 128:
                        printf("│\033[95m%5d\033[0m", val);
                        break;
                    case 256:
                        printf("│\033[35m%5d\033[0m", val);
                        break;
                    case 512:
                        printf("│\033[34m%5d\033[0m", val);
                        break;
                    case 1024:
                        printf("│\033[94m%5d\033[0m", val);
                        break;
                    case 2048:
                        printf("│\033[36m%5d\033[0m", val);
                        break;
                    case 4096:
                        printf("│\033[96m%5d\033[0m", val);
                        break;
                    case 8192:
                        printf("│\033[92m%5d\033[0m", val);
                        break;
                    default:
                        printf("│\033[32m%5d\033[0m", val);
                        break;
                }
            }
        }
        printf("│    ");

        for (int j = 0; j < n; j++) {
            int val = tableau2[i][j];
            if (val == 0) {
                printf("│     ");
            }
            else {
                switch(val) {
                    case 2:
                        printf("│\033[97m%5d\033[0m", val);
                        break;
                    case 4:
                        printf("│\033[37m%5d\033[0m", val);
                        break;
                    case 8:
                        printf("│\033[93m%5d\033[0m", val);
                        break;
                    case 16:
                        printf("│\033[33m%5d\033[0m", val);
                        break;
                    case 32:
                        printf("│\033[91m%5d\033[0m", val);
                        break;
                    case 64:
                        printf("│\033[31m%5d\033[0m", val);
                        break;
                    case 128:
                        printf("│\033[95m%5d\033[0m", val);
                        break;
                    case 256:
                        printf("│\033[35m%5d\033[0m", val);
                        break;
                    case 512:
                        printf("│\033[34m%5d\033[0m", val);
                        break;
                    case 1024:
                        printf("│\033[94m%5d\033[0m", val);
                        break;
                    case 2048:
                        printf("│\033[36m%5d\033[0m", val);
                        break;
                    case 4096:
                        printf("│\033[96m%5d\033[0m", val);
                        break;
                    case 8192:
                        printf("│\033[92m%5d\033[0m", val);
                        break;
                    default:
                        printf("│\033[32m%5d\033[0m", val);
                        break;
                }
            }
        }
        printf("│\n");

        // Séparateur entre les lignes
        if (i < n - 1) {
            printf("├─────");
            for (int j = 1; j < n; j++) {
                printf("┼─────");
            }
            printf("┤    ");

            printf("├─────");
            for (int j = 1; j < n; j++) {
                printf("┼─────");
            }
            printf("┤\n");
        }
    }

    printf("└─────");
    for (int j = 1; j < n; j++) {
        printf("┴─────");
    }
    printf("┘    ");

    printf("└─────");
    for (int j = 1; j < n; j++) printf("┴─────");
    printf("┘\n");
    printf("Z (Haut), Q (Gauche), S (Bas), D (Droite) - ESC pour quitter\n");
}

// Affiche le terrain de Puzzle
void afficher_puzzle(int **tableau) {
    clear_screen();

    printf("\n┌─────");
    for (int j = 1; j < n; j++) printf("┬─────");
    printf("┐\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int val = tableau[i][j];

            if (val == -1) {
                printf("│  X  ");
            } else if (val == 0) {
                printf("│     ");
            } else {
                switch(val) {
                    case 2:
                        printf("│\033[97m%5d\033[0m", val);
                        break;
                    case 4:
                        printf("│\033[37m%5d\033[0m", val);
                        break;
                    case 8:
                        printf("│\033[93m%5d\033[0m", val);
                        break;
                    case 16:
                        printf("│\033[33m%5d\033[0m", val);
                        break;
                    case 32:
                        printf("│\033[91m%5d\033[0m", val);
                        break;
                    case 64:
                        printf("│\033[31m%5d\033[0m", val);
                        break;
                    case 128:
                        printf("│\033[95m%5d\033[0m", val);
                        break;
                    case 256:
                        printf("│\033[35m%5d\033[0m", val);
                        break;
                    case 512:
                        printf("│\033[34m%5d\033[0m", val);
                        break;
                    case 1024:
                        printf("│\033[94m%5d\033[0m", val);
                        break;
                    case 2048:
                        printf("│\033[36m%5d\033[0m", val);
                        break;
                    case 4096:
                        printf("│\033[96m%5d\033[0m", val);
                        break;
                    case 8192:
                        printf("│\033[92m%5d\033[0m", val);
                        break;
                    default:
                        printf("│\033[32m%5d\033[0m", val);
                        break;
                }
            }
        }
        printf("│\n");

        if (i < n - 1) {
            printf("├─────");
            for (int j = 1; j < n; j++) {
                printf("┼─────");
            }
            printf("┤\n");
        }
    }

    printf("└─────");
    for (int j = 1; j < n; j++) {
        printf("┴─────");
    }
    printf("┘\n");

    printf("Z (Haut), Q (Gauche), S (Bas), D (Droite) - E pour quitter\n");
}

// === Déplacements sans prendre en compte les obstacles

int deplacementgauche(int **tableau) {
    int changed = 0;

    for (int i = 0; i < n; i++) {
        int merged[n];
        for (int k = 0; k < n; k++) {
            merged[k] = 0;
        }

        //Déplacer
        for (int j = 1; j < n; j++) {
            if (tableau[i][j] != 0) {
                int k = j;
                while (k > 0 && tableau[i][k - 1] == 0) {
                    tableau[i][k - 1] = tableau[i][k];
                    tableau[i][k] = 0;
                    k--;
                    changed = 1;
                }
            }
        }

        //Fusionner
        for (int j = 0; j < n - 1; j++) {
            if (tableau[i][j] != 0 && tableau[i][j] == tableau[i][j + 1] && !merged[j]) {
                tableau[i][j] *= 2;
                tableau[i][j + 1] = 0;
                merged[j] = 1;
                changed = 1;
            }
        }

        //Replacer
        for (int j = 1; j < n; j++) {
            if (tableau[i][j] != 0) {
                int k = j;
                while (k > 0 && tableau[i][k - 1] == 0) {
                    tableau[i][k - 1] = tableau[i][k];
                    tableau[i][k] = 0;
                    k--;
                }
            }
        }
    }

    return changed;
}

int deplacementdroite(int **tableau) {
    int changed = 0;

    for (int i = 0; i < n; i++) {
        int merged[n];
        for (int k = 0; k < n; k++) merged[k] = 0;

        //Déplacer vers la droite
        for (int j = n - 2; j >= 0; j--) {
            if (tableau[i][j] != 0) {
                int k = j;
                while (k < n - 1 && tableau[i][k + 1] == 0) {
                    tableau[i][k + 1] = tableau[i][k];
                    tableau[i][k] = 0;
                    k++;
                    changed = 1;
                }
            }
        }

        //Fusionner
        for (int j = n - 1; j > 0; j--) {
            if (tableau[i][j] != 0 &&
                tableau[i][j] == tableau[i][j - 1] &&
                !merged[j]) {
                tableau[i][j] *= 2;
                tableau[i][j - 1] = 0;
                merged[j] = 1;
                changed = 1;
            }
        }

        //Replacer
        for (int j = n - 2; j >= 0; j--) {
            if (tableau[i][j] != 0) {
                int k = j;
                while (k < n - 1 && tableau[i][k + 1] == 0) {
                    tableau[i][k + 1] = tableau[i][k];
                    tableau[i][k] = 0;
                    k++;
                }
            }
        }
    }

    return changed;
}

int deplacementhaut(int **tableau) {
    int changed = 0;

    for (int j = 0; j < n; j++) {
        int merged[n];
        for (int k = 0; k < n; k++) merged[k] = 0;

        //Déplacer vers le haut
        for (int i = 1; i < n; i++) {
            if (tableau[i][j] != 0) {
                int k = i;
                while (k > 0 && tableau[k - 1][j] == 0) {
                    tableau[k - 1][j] = tableau[k][j];
                    tableau[k][j] = 0;
                    k--;
                    changed = 1;
                }
            }
        }

        // Phase 2 : Fusionner
        for (int i = 0; i < n - 1; i++) {
            if (tableau[i][j] != 0 && tableau[i][j] == tableau[i + 1][j] && !merged[i]) {
                tableau[i][j] *= 2;
                tableau[i + 1][j] = 0;
                merged[i] = 1;
                changed = 1;
            }
        }

        //Replacer
        for (int i = 1; i < n; i++) {
            if (tableau[i][j] != 0) {
                int k = i;
                while (k > 0 && tableau[k - 1][j] == 0) {
                    tableau[k - 1][j] = tableau[k][j];
                    tableau[k][j] = 0;
                    k--;
                }
            }
        }
    }

    return changed;
}

int deplacementbas(int **tableau) {
    int changed = 0;

    for (int j = 0; j < n; j++) {
        int merged[n];
        for (int k = 0; k < n; k++) merged[k] = 0;

        //Déplacer vers le bas
        for (int i = n - 2; i >= 0; i--) {
            if (tableau[i][j] != 0) {
                int k = i;
                while (k < n - 1 && tableau[k + 1][j] == 0) {
                    tableau[k + 1][j] = tableau[k][j];
                    tableau[k][j] = 0;
                    k++;
                    changed = 1;
                }
            }
        }

        //Fusionner
        for (int i = n - 1; i > 0; i--) {
            if (tableau[i][j] != 0 && tableau[i][j] == tableau[i - 1][j] && !merged[i]) {
                tableau[i][j] *= 2;
                tableau[i - 1][j] = 0;
                merged[i] = 1;
                changed = 1;
            }
        }

        //Replacer
        for (int i = n - 2; i >= 0; i--) {
            if (tableau[i][j] != 0) {
                int k = i;
                while (k < n - 1 && tableau[k + 1][j] == 0) {
                    tableau[k + 1][j] = tableau[k][j];
                    tableau[k][j] = 0;
                    k++;
                }
            }
        }
    }

    return changed;
}

// === Deplacements prenant en compte les obstacles ===
int deplacementgauche_puzzle(int **tableau) {
    int changed = 0;

    for (int i = 0; i < n; i++) {
        int merged[n];
        for (int k = 0; k < n; k++) {
            merged[k] = 0;
        }

        // Déplacer
        for (int j = 1; j < n; j++) {
            if (tableau[i][j] != 0 && tableau[i][j] != -1) {
                int k = j;
                while (k > 0 && tableau[i][k - 1] == 0) {
                    tableau[i][k - 1] = tableau[i][k];
                    tableau[i][k] = 0;
                    k--;
                    changed = 1;
                }
            }
        }

        //Fusionner
        for (int j = 0; j < n - 1; j++) {
            if (tableau[i][j] != 0 && tableau[i][j] != -1 &&
                tableau[i][j] == tableau[i][j + 1] &&
                !merged[j]) {
                tableau[i][j] *= 2;
                tableau[i][j + 1] = 0;
                merged[j] = 1;
                changed = 1;
            }
        }

        //Replacer
        for (int j = 1; j < n; j++) {
            if (tableau[i][j] != 0 && tableau[i][j] != -1) {
                int k = j;
                while (k > 0 && tableau[i][k - 1] == 0) {
                    tableau[i][k - 1] = tableau[i][k];
                    tableau[i][k] = 0;
                    k--;
                }
            }
        }
    }

    return changed;
}

int deplacementdroite_puzzle(int **tableau) {
    int changed = 0;

    for (int i = 0; i < n; i++) {
        int merged[n];
        for (int k = 0; k < n; k++) merged[k] = 0;

        //Déplacer vers la droite
        for (int j = n - 2; j >= 0; j--) {
            if (tableau[i][j] != 0 && tableau[i][j] != -1) {
                int k = j;
                while (k < n - 1 && tableau[i][k + 1] == 0) {
                    tableau[i][k + 1] = tableau[i][k];
                    tableau[i][k] = 0;
                    k++;
                    changed = 1;
                }
            }
        }

        //Fusionner
        for (int j = n - 1; j > 0; j--) {
            if (tableau[i][j] != 0 && tableau[i][j] != -1 &&
                tableau[i][j] == tableau[i][j - 1] &&
                !merged[j]) {
                tableau[i][j] *= 2;
                tableau[i][j - 1] = 0;
                merged[j] = 1;
                changed = 1;
            }
        }

        //Replacer
        for (int j = n - 2; j >= 0; j--) {
            if (tableau[i][j] != 0 && tableau[i][j] != -1) {
                int k = j;
                while (k < n - 1 && tableau[i][k + 1] == 0) {
                    tableau[i][k + 1] = tableau[i][k];
                    tableau[i][k] = 0;
                    k++;
                }
            }
        }
    }

    return changed;
}

int deplacementhaut_puzzle(int **tableau) {
    int changed = 0;

    for (int j = 0; j < n; j++) {
        int merged[n];
        for (int k = 0; k < n; k++) merged[k] = 0;

        //Déplacer vers le haut
        for (int i = 1; i < n; i++) {
            if (tableau[i][j] != 0 && tableau[i][j] != -1) {
                int k = i;
                while (k > 0 && tableau[k - 1][j] == 0) {
                    tableau[k - 1][j] = tableau[k][j];
                    tableau[k][j] = 0;
                    k--;
                    changed = 1;
                }
            }
        }

        //Fusionner
        for (int i = 0; i < n - 1; i++) {
            if (tableau[i][j] != 0 && tableau[i][j] != -1 &&
                tableau[i][j] == tableau[i + 1][j] &&
                !merged[i]) {
                tableau[i][j] *= 2;
                tableau[i + 1][j] = 0;
                merged[i] = 1;
                changed = 1;
            }
        }

        //Replacer
        for (int i = 1; i < n; i++) {
            if (tableau[i][j] != 0 && tableau[i][j] != -1) {
                int k = i;
                while (k > 0 && tableau[k - 1][j] == 0) {
                    tableau[k - 1][j] = tableau[k][j];
                    tableau[k][j] = 0;
                    k--;
                }
            }
        }
    }

    return changed;
}

int deplacementbas_puzzle(int **tableau) {
    int changed = 0;

    for (int j = 0; j < n; j++) {
        int merged[n];
        for (int k = 0; k < n; k++) merged[k] = 0;

        //Déplacer
        for (int i = n - 2; i >= 0; i--) {
            if (tableau[i][j] != 0 && tableau[i][j] != -1) {
                int k = i;
                while (k < n - 1 && tableau[k + 1][j] == 0) {
                    tableau[k + 1][j] = tableau[k][j];
                    tableau[k][j] = 0;
                    k++;
                    changed = 1;
                }
            }
        }

        //Fusionner
        for (int i = n - 1; i > 0; i--) {
            if (tableau[i][j] != 0 && tableau[i][j] != -1 &&
                tableau[i][j] == tableau[i - 1][j] &&
                !merged[i]) {
                tableau[i][j] *= 2;
                tableau[i - 1][j] = 0;
                merged[i] = 1;
                changed = 1;
            }
        }

        //Replacer
        for (int i = n - 2; i >= 0; i--) {
            if (tableau[i][j] != 0 && tableau[i][j] != -1) {
                int k = i;
                while (k < n - 1 && tableau[k + 1][j] == 0) {
                    tableau[k + 1][j] = tableau[k][j];
                    tableau[k][j] = 0;
                    k++;
                }
            }
        }
    }

    return changed;
}

// === Fonction pour les Inputs et les Blocs nouveaux ===

// fonction qui génère les nouveaux numéros
void generer(int **tableau) {
    int x = rand() % n;
    int y = rand() % n;

    int emptyCheck = 0;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(tableau[i][j] == 0) emptyCheck++;
        }
    }
    if(emptyCheck == 0) return;

    while (tableau[x][y] != 0) {
        x = rand() % n;
        y = rand() % n;
    }
    if (rand() % 10 == 7) tableau[x][y] = 4;
    else tableau[x][y] = 2;
}

// Génère un nouveau bloc en évitant les obstacles
void generer_puzzle(int **tableau) {
    int emptyCheck = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(tableau[i][j] == 0) emptyCheck++;  // Seulement les cases vides
        }
    }
    if(emptyCheck == 0) return;

    int x = rand() % n;
    int y = rand() % n;

    while (tableau[x][y] != 0) { // prends aussi en compte les obstacles car -1 != 0 => True
        x = rand() % n;
        y = rand() % n;
    }

    if (rand() % 10 == 7) tableau[x][y] = 4;
    else tableau[x][y] = 2;
}

int input(int **tableau, int mode) {
    int c = getch();
    switch(c) {
        case 'z':
            if (mode == 3) return deplacementhaut_puzzle(tableau);
            else return deplacementhaut(tableau);
        case 's':
            if (mode == 3) return deplacementbas_puzzle(tableau);
            else return deplacementbas(tableau);
        case 'q':
            if (mode == 3) return deplacementgauche_puzzle(tableau);
            else return deplacementgauche(tableau);
        case 'd':
            if (mode == 3) return deplacementdroite_puzzle(tableau);
            else return deplacementdroite(tableau);
        case 'e':
            jeuencourt = 0;
            return 0;
    }
    return 0;
}

// Fonction pour calculer le score
int calculer_score(int **tableau) {
    int score = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (tableau[i][j] > 0) {  // Pour éviter de calculer les obstacles dans les score final
                score += tableau[i][j];
            }
        }
    }
    return score;
}

// Fonction pour vérifier qu'il y a toujours une option de mouvement
void Verifier() {
    int checklist = 0;
    // Compter les cases non vides
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (tableau[i][j] != 0) {
                checklist++;
            }
        }
    }

    // Si toutes les cases sont pleines
    if (checklist == n * n) {
        int merge_possible = 0;

        // Vérifier s'il existe encore des fusions possibles
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // Vérifier fusion horizontale
                if (j < n - 1 && tableau[i][j] == tableau[i][j + 1]) {
                    merge_possible = 1;
                    break;
                }
                // Vérifier fusion verticale
                if (i < n - 1 && tableau[i][j] == tableau[i + 1][j]) {
                    merge_possible = 1;
                    break;
                }
            }
            if (merge_possible) break;
        }

        // Si aucune fusion n'est possible, le jeu est terminé
        if (!merge_possible) {
            int score = calculer_score(tableau);

            printf("\n========== FIN DU JEU ==========\n");
            printf("Aucun mouvement possible !\n");
            printf("Votre score final : %d\n", score);
            printf("================================\n");
            printf("\nAppuyez sur une touche pour continuer...\n");

            getch();
            jeuencourt = 0;
        }
    }
}

// Vérifier fin de jeu pour mode duo
void Verifier_duo() {
    // Vérifier le tableau 1
    int full1 = 1, merge1 = 0;
    for (int i = 0; i < n && full1; i++) {
        for (int j = 0; j < n; j++) {
            if (tableau1[i][j] == 0) {
                full1 = 0;
                break;
            }
        }
    }

    if (full1) {
        for (int i = 0; i < n && !merge1; i++) {
            for (int j = 0; j < n; j++) {
                if ((j < n - 1 && tableau1[i][j] == tableau1[i][j + 1]) || (i < n - 1 && tableau1[i][j] == tableau1[i + 1][j])) { // Verification de possiblité de merge (hor puis vert)
                    merge1 = 1;
                    break;
                }
            }
        }
    }

    // Vérifier le tableau 2
    int full2 = 1, merge2 = 0;
    for (int i = 0; i < n && full2; i++) {
        for (int j = 0; j < n; j++) {
            if (tableau2[i][j] == 0) {
                full2 = 0;
                break;
            }
        }
    }

    if (full2) {
        for (int i = 0; i < n && !merge2; i++) {
            for (int j = 0; j < n; j++) {
                if ((j < n - 1 && tableau2[i][j] == tableau2[i][j + 1]) || (i < n - 1 && tableau2[i][j] == tableau2[i + 1][j])) { // Verification de possiblité de merge (hor puis vert)
                    merge2 = 1;
                    break;
                }
            }
        }
    }

    // Si les deux tableaux sont bloqués
    if (full1 && !merge1 && full2 && !merge2) {
        int score1 = calculer_score(tableau1);
        int score2 = calculer_score(tableau2);

        printf("\n========== FIN DU JEU ==========\n");
        printf("Aucun mouvement possible !\n");
        printf("Score Joueur : %d\n", score1+score2);
        printf("====================================\n");
        printf("\nAppuyez sur une touche pour continuer...\n");

        getch();
        jeuencourt = 0;
    }
}

// Vérifie s'il reste des mouvements possibles en mode Puzzle
void Verifier_puzzle() {
    int checklist = 0;

    // Compter les cases non vides
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (tableau[i][j] != 0 && tableau[i][j] != -1) {
                checklist++;
            }
        }
    }

    // Compter le nombre total de cases jouables
    int total_jouable = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (tableau[i][j] != -1) {
                total_jouable++;
            }
        }
    }

    if (checklist == total_jouable) {
        int merge_possible = 0;

        // Vérifier s'il existe encore des fusions possibles
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (tableau[i][j] > 0) {
                    // Vérifier fusion horizontale (droite)
                    if (j < n - 1 && tableau[i][j] == tableau[i][j + 1]) {
                        merge_possible = 1;
                        break;
                    }
                    // Vérifier fusion verticale (bas)
                    if (i < n - 1 && tableau[i][j] == tableau[i + 1][j]) {
                        merge_possible = 1;
                        break;
                    }
                }
            }
            if (merge_possible) break;
        }

        if (!merge_possible) {
            int score = calculer_score(tableau);

            printf("\n========== FIN DU JEU PUZZLE ==========\n");
            printf("Aucun mouvement possible !\n");
            printf("Votre score final : %d\n", score);
            printf("=======================================\n");
            printf("\nAppuyez sur une touche pour continuer...\n");

            getch();
            jeuencourt = 0;
        }
    }
}

void Start(){
    clear_screen();
    printf(
"                                          ,---.-,    \n"
"                                   ,--,  '   ,'  '.  \n"
"      ,----,     ,----..         ,--.'| /   /      \\ \n"
"    .'   .' \\   /   /   \\     ,--,  | :.   ;  ,/.  : \n"
"  ,----,'    | /   .     : ,---.'|  : ''   |  | :  ; \n"
"  |    :  .  ;.   /   ;.  \\;   : |  | ;'   |  ./   : \n"
"  ;    |.'  /.   ;   /  ` ;|   | : _' ||   :       , \n"
"  `----'/  ; ;   |  ; \\ ; |:   : |.'  | \\   \\     /  \n"
"    /  ;  /  |   :  | ; | '|   ' '  ; :  ;   ,   '\\  \n"
"   ;  /  /-, .   |  ' ' ' :\\   \\  .'. | /   /      \\ \n"
"  /  /  /.`| '   ;  \\; /  | `---`:  | '.   ;  ,/.  : \n"
"./__;      :  \\   \\  ',  /       '  ; |'   |  | :  ; \n"
"|   :    .'    ;   :    /        |  : ;'   |  ./   : \n"
";   | .'        \\   \\ .'         '  ,/ |   :      /  \n"
"`---'            `---`           '--'   \\   \\   .'   \n"
"                                         `---`-'      \n"
    );
    printf("\n\n===== | Selectionnez votre mode de jeu |=====\n\n1 : Classic (de 4 par 4 a 9 par 9)\n2 : Duo, deux tableaux\n3 : Puzzle\n");
    scanf("%d",&gamemode);
    while (getchar() != '\n'); // Vider le buffer après un scanf

    if (gamemode == 1) {
        do{
            printf("\nTaille du tableau : ");
            scanf("%d", &n);
            if (n<4) {
                printf("\nTerrain trop petit");
            }
            else if (n>9) {
                printf("\nTerrain trop grand");
            }
        } while (n<4 || n>9);
        while (getchar() != '\n'); // Vider le buffer après un scanf

        generetableau();
        clean(tableau);
        generer(tableau);
        generer(tableau);
        afficher(tableau);
        jeuencourt = 1;

        do {
            int moved = input(tableau, 1);
            if (moved) {
                generer(tableau);
                afficher(tableau);
                Verifier();
            }
        } while (jeuencourt == 1);
    }
    else if (gamemode == 2) {
        n = 4;
        generetableau_duo();
        clean(tableau1);
        clean(tableau2);
        generer(tableau1);
        generer(tableau1);
        generer(tableau2);
        generer(tableau2);

        afficher_double(tableau1, tableau2);
        jeuencourt = 1;

        while (jeuencourt) {
            int c = getch();
            int m1 = 0, m2 = 0;

            if(c == 'z') {
                m1 = deplacementhaut(tableau1);
                m2 = deplacementhaut(tableau2);
            }
            if(c == 's') {
                m1 = deplacementbas(tableau1);
                m2 = deplacementbas(tableau2);
            }
            if(c == 'q') {
                m1 =deplacementgauche(tableau1);
                m2 = deplacementgauche(tableau2); }
            if(c == 'd') {
                m1 = deplacementdroite(tableau1);
                m2 = deplacementdroite(tableau2);
            }
            if(c == 'e') break;

            if (m1 || m2) {
                if (m1) generer(tableau1);
                if (m2) generer(tableau2);
                afficher_double(tableau1, tableau2);
                Verifier_duo();
            }
        }
    }
    else if (gamemode == 3) {
        char filename[100];
        printf("\nNom du fichier puzzle (Puzzle.txt pour la démo) : ");
        scanf("%s", filename);
        while (getchar() != '\n');  // Vider le buffer

        charger_puzzle(filename);

        if (tableau == NULL) {
            printf("Erreur lors du chargement du puzzle.\n");
            Sleep(2000);
            return;
        }

        afficher_puzzle(tableau);
        jeuencourt = 1;

        do {
            int moved = input(tableau, 3);
            if (moved) {
                generer_puzzle(tableau);
                afficher_puzzle(tableau);
                Verifier_puzzle();
            }
        } while (jeuencourt == 1);
    }
    else {
        printf("\n\nMode de jeu invalide\n\n");
        Sleep(2000);
        Start();
    }
}

int main() {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hConsole, &mode);
    SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    srand(time(NULL));

    int continuer = 1;
    while (continuer) {
        Start();

        if (gamemode == 1) {
            liberer_tableau();
        }
        else if (gamemode == 2) {
            liberer_tableaux_duo();
        }
        else if (gamemode == 3) {
            liberer_tableau();
        }

        printf("\n\nVoulez-vous rejouer ? (O/N) : ");
        char choix;
        do {
            choix = getch();
            choix = tolower(choix);
        } while (choix != 'o' && choix != 'n');

        printf("%c\n", choix);

        if (choix == 'n') {
            continuer = 0;
            printf("\nMerci d'avoir joué !\n");
        }
    }

    return 0;
}
