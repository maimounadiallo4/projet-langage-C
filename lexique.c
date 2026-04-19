/**
 * @file lexique.c
 * @brief Module Lexique — Implémenté par Boubacar Ly
 *
 * Contient la variable globale `calu` et les deux fonctions de lecture
 * utilisées par tout l'analyseur.
 *
 * Invariant maintenu en permanence :
 *   calu = premier caractère non encore examiné par l'analyseur.
 */

#include "parser.h"
#include <stdio.h>

/**
 * @brief Caractère actuellement examiné par l'analyseur.
 *
 * Initialisé dans main.c avant chaque expression via un premier appel
 * à lire_utile(). Toutes les fonctions d'analyse lisent calu pour savoir
 * quel caractère est en attente de traitement.
 */
char calu;

/**
 * @brief Lit le prochain caractère brut depuis stdin et le stocke dans calu.
 *
 * Aucun filtrage : les espaces, tabulations et sauts de ligne sont conservés
 * tels quels dans calu. Utilisée à l'intérieur de nombre() pour détecter
 * qu'un espace a été inséré au milieu d'un nombre (ce qui est interdit).
 */
void lire_brut() { calu = getchar(); }

/**
 * @brief Lit le prochain caractère utile depuis stdin et le stocke dans calu.
 *
 * Réitère getchar() tant que le caractère lu est un blanc (espace, tabulation,
 * saut de ligne). Garantit que calu contient toujours un caractère significatif
 * après l'appel. Utilisée partout sauf à l'intérieur des nombres.
 */
void lire_utile() {
  do {
    calu = getchar();
  } while (calu == ' ' || calu == '\t' || calu == '\n');
}
