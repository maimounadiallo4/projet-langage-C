/**
 * @file tester.c
 * @brief Programme de tests automatisés pour l'analyseur
 *
 * @author Ousmane
 */

#include <stdio.h>
#include <string.h>

/*
 * Configuration multiplateforme pour la création de processus (popen/pclose)
 * et le nom de l'exécutable à tester.
 */
#ifdef _WIN32
#include <io.h>
#define popen _popen
#define pclose _pclose
#define EXECUTABLE "analyseur.exe"
#else
#include <unistd.h>
#define EXECUTABLE "./analyseur"
#endif

/* Configuration des couleurs ANSI (Styles du terminal) */
#define GRAS "\033[1m"
#define VERT "\033[32m"
#define ROUGE "\033[31m"
#define JAUNE "\033[33m"
#define BLEU "\033[34m"
#define CYAN "\033[36m"
#define RESET "\033[0m"

/**
 * @brief Affiche une belle bannière d'accueil pour les tests.
 */
void afficher_entete() {
  printf(CYAN GRAS
         "┌────────────────────────────────────────────────────────┐\n");
  printf("│           🚀  ANALYSEUR D'EXPRESSIONS C                │\n");
  printf("│              Lancement des tests...                    │\n");
  printf(
      "└────────────────────────────────────────────────────────┘\n\n" RESET);
}

/**
 * @brief Point d'entrée du programme de test.
<<<<<<< HEAD
 *
 * Ce programme lit un fichier de scénarios de tests (`tests/cas_de_test.txt`),
 * exécute l'analyseur en lui envoyant chaque expression, et vérifie si le
 * résultat produit (sortie standard) correspond à ce qui est attendu.
 *
=======
 * 
 * Ce programme lit un fichier de scénarios de tests (`tests/cas_de_test.txt`), 
 * exécute l'analyseur en lui envoyant chaque expression, et vérifie si le
 * résultat produit (sortie standard) correspond à ce qui est attendu.
 * 
>>>>>>> 1ebea7bc64162936c5abb2af66958a9e86056fc3
 * @return 0 si tous les tests ont réussi, 1 si au moins un test a échoué.
 */
int main() {
  FILE *fichier_tests = fopen("tests/cas_de_test.txt", "r");
  if (!fichier_tests) {
    perror("Impossible d'ouvrir tests/cas_de_test.txt");
    return 1;
  }

  afficher_entete();

  char ligne[256];
  int reussis = 0, total_tests = 0, echecs = 0;

  while (fgets(ligne, sizeof(ligne), fichier_tests)) {
    /* Ignorer les lignes vides ou les retours chariot */
    if (ligne[0] == '\n' || ligne[0] == '\r')
      continue;

    /* Découpage de la ligne : Expression | Résultat Attendu */
    char *expression_str = strtok(ligne, "|");
    char *attendu = strtok(NULL, "|");
    if (!expression_str || !attendu)
      continue;

    /* Nettoyage des espaces pour l'expression */
    while (*expression_str == ' ' || *expression_str == '\t')
      expression_str++;
    char *fin = expression_str + strlen(expression_str) - 1;
    while (fin > expression_str &&
           (*fin == ' ' || *fin == '\t' || *fin == '\n' || *fin == '\r'))
      *fin-- = '\0';

    /* Nettoyage des espaces pour le résultat attendu */
    while (*attendu == ' ' || *attendu == '\t' || *attendu == '\n' ||
           *attendu == '\r')
      attendu++;
    fin = attendu + strlen(attendu) - 1;
    while (fin > attendu &&
           (*fin == ' ' || *fin == '\t' || *fin == '\n' || *fin == '\r'))
      *fin-- = '\0';

    total_tests++;

    /* Construction de la commande shell pour tester l'analyseur */
    char commande[512];
    /* On envoie l'expression suivie d'un '.' pour quitter proprement, entre
     * guillemets pour le shell */
    sprintf(commande, "echo \"%s .\" | %s", expression_str, EXECUTABLE);

    FILE *flux = popen(commande, "r");
    if (!flux) {
      printf(ROUGE "[ ERREUR ] Impossible d'exécuter l'analyseur\n" RESET);
      continue;
    }

    /* Capture de la sortie du programme */
    char sortie_programme[1024] = {0};
    char tampon[128];
    while (fgets(tampon, sizeof(tampon), flux)) {
      strcat(sortie_programme, tampon);
    }
    pclose(flux);

    int succes = 0;
    /* Cas 1 : On attend une erreur de syntaxe */
    if (strcmp(attendu, "ERREUR") == 0) {
      if (strstr(sortie_programme, "erronee") ||
          strstr(sortie_programme, "Erreur")) {
        succes = 1;
        printf(" [ " VERT "✔" RESET " ] %-32s " BLEU "→" RESET " " VERT
               "Erreur détectée" RESET "\n",
               expression_str);
      } else {
        printf(" [ " ROUGE "✘" RESET " ] %-32s " BLEU "→" RESET " " ROUGE
               "Erreur ATTENDUE" RESET "\n",
               expression_str);
      }
    }
    /* Cas 2 : On attend une valeur numérique précise */
    else {
      char chaine_recherche[64];
      sprintf(chaine_recherche, "sa valeur est %s", attendu);
      if (strstr(sortie_programme, chaine_recherche)) {
        succes = 1;
        printf(" [ " VERT "✔" RESET " ] %-32s " BLEU "→" RESET " " VERT
               "%-10s" RESET "\n",
               expression_str, attendu);
      } else {
        printf(" [ " ROUGE "✘" RESET " ] %-32s " BLEU "→" RESET " " ROUGE
               "Attendu: %-10s" RESET "\n",
               expression_str, attendu);
      }
    }

    if (succes)
      reussis++;
    else
      echecs++;
  }

  fclose(fichier_tests);

  /* Affichage du résumé final */
  printf("\n" GRAS "RÉSUMÉ DU TEST" RESET "\n");
  if (echecs == 0) {
    printf(
        CYAN
        "──────────────────────────────────────────────────────────\n" RESET);
    printf(" " VERT GRAS "BRAVO !" RESET
           " Tous les tests ont été validés avec succès.\n");
    printf(" Score final : " GRAS VERT "%d" RESET "/" GRAS "%d" RESET " [" VERT
           "100%%" RESET "]\n",
           reussis, total_tests);
    printf(
        CYAN
        "──────────────────────────────────────────────────────────\n" RESET);
  } else {
    printf(
        ROUGE
        "──────────────────────────────────────────────────────────\n" RESET);
    printf(" " ROUGE GRAS "ATTENTION !" RESET " Certains tests ont échoué.\n");
    printf(" Réussis : " VERT "%d" RESET " | Échecs : " ROUGE "%d" RESET
           " | Total : %d\n",
           reussis, echecs, total_tests);
    printf(
        ROUGE
        "──────────────────────────────────────────────────────────\n" RESET);
  }

  return echecs > 0 ? 1 : 0;
}
