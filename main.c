#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256

char** citations = NULL;       // Tableau dynamique de pointeurs vers les citations
int nbCitations = 0;           // Nombre de citations stockées

// Fonction pour afficher le menu
void afficherMenu() {
    printf("\n--- Menu ---\n");
    printf("1. Afficher les citations\n");
    printf("2. Ajouter une citation\n");
    printf("3. Supprimer une citation\n");
    printf("4. Charger les citations depuis un fichier\n");
    printf("0. Quitter\n");
    printf("Votre choix : ");
}

// Fonction pour afficher les citations
void afficherCitations() {
    if (nbCitations == 0) {
        printf("Aucune citation disponible.\n");
        return;
    }

    for (int i = 0; i < nbCitations; i++) {
        printf("%d. %s\n", i + 1, citations[i]);
    }
}

// Fonction pour ajouter une citation
void ajouterCitation() {
    char buffer[MAX_LINE];
    printf("Entrez la citation : ");
    getchar(); // Pour consommer le \n résiduel
    fgets(buffer, MAX_LINE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Supprimer le \n

    citations = realloc(citations, (nbCitations + 1) * sizeof(char*));
    citations[nbCitations] = strdup(buffer);
    nbCitations++;
    printf("Citation ajoutée !\n");
}

// Fonction pour charger les citations depuis un fichier
void chargerDepuisFichier(const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    if (!fichier) {
        perror("Erreur ouverture fichier");
        return;
    }

    char ligne[MAX_LINE];
    while (fgets(ligne, MAX_LINE, fichier)) {
        ligne[strcspn(ligne, "\n")] = '\0'; // Supprimer \n
        citations = realloc(citations, (nbCitations + 1) * sizeof(char*));
        citations[nbCitations] = strdup(ligne);
        nbCitations++;
    }

    fclose(fichier);
    printf("Citations chargées depuis %s.\n", nomFichier);
}

// Fonction pour libérer la mémoire
void libererMemoire() {
    for (int i = 0; i < nbCitations; i++) {
        free(citations[i]);
    }
    free(citations);
}

int main() {
    int choix;

    do {
        afficherMenu();
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                afficherCitations();
                break;
            case 2:
                ajouterCitation();
                break;
            case 3:
                printf("Suppression non encore implémentée.\n");
                break;
            case 4:
                chargerDepuisFichier("citations.txt");
                break;
            case 0:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide.\n");
        }

    } while (choix != 0);

    libererMemoire();
    return 0;
}
