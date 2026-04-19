/**
 * @file parser.h
 * @brief Fichier d'en-tête principal pour l'analyseur d'expressions arithmétiques.
 * @author Maïmouna DIALLO
 *
 * Ce fichier contient les déclarations des variables globales, des fonctions
 * d'analyse syntaxique (basées sur la grammaire BNF) et des utilitaires lexicaux.
 *
 * @note CONTRAT D'ÉQUIPE : Ce fichier est le point central du projet.
 * Toute modification de ce fichier doit être validée par Maïmouna.
 *
 * Grammaire BNF complète :
 *   expression → terme opérateur-additif expression | terme
 *   terme      → facteur opérateur-multiplicatif terme | facteur
 *   facteur    → nombre | '(' expression ')'
 *   nombre     → chiffre nombre | chiffre
 *   chiffre    → '0' | '1' | ... | '9'
 */

#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* VARIABLES GLOBALES */

/**
 * @brief Caractère actuellement examiné par l'analyseur.
 *
 * Propriété invariante maintenue en permanence :
 * calu = premier caractère non encore examiné par l'analyseur.
 * Déclaré dans lexique.c (Boubacar).
 */
extern char calu;

/**
 * @brief Drapeau d'erreur syntaxique.
 *
 * 0 = aucune erreur, 1 = erreur détectée.
 * Déclaré dans erreurs.c (Alhousseynou).
 * Remis à 0 dans main.c avant chaque nouvelle expression.
 */
extern int erreur_syntaxe;

/* UTILITAIRES LEXICAUX (Module Lexique — Boubacar) */

/**
 * @brief Lit le prochain caractère brut depuis stdin et le stocke dans calu.
 *
 * N'effectue aucun filtrage des blancs.
 * Utilisé à l'intérieur des nombres pour détecter les espaces (interdits).
 */
void lire_brut();

/**
 * @brief Fonction de lecture "améliorée".
 *
 * Réitère l'appel à getchar() jusqu'à obtenir un caractère non blanc
 * (ignore les espaces, tabulations, sauts de ligne) et stocke le résultat
 * dans la variable globale calu.
 */
void lire_utile();

/* ANALYSE HAUTE (Module — Cécile) */

/**
 * @brief Analyse et évalue la règle BNF :
 *        <expression> -> <terme> <op-add> <expression> | <terme>
 *
 * Lit un terme, et s'il est suivi d'un opérateur additif ('+' ou '-'),
 * lit l'expression suivante.
 *
 * @warning D'après le sujet, entre opérateurs de même priorité, l'évaluation
 * se fait de la DROITE vers la GAUCHE. (ex: 5-3+2 est évalué comme 5-(3+2)).
 *
 * @return int La valeur numérique calculée de l'expression.
 */
int expression();

/**
 * @brief Analyse et évalue la règle BNF :
 *        <terme> -> <facteur> <op-mult> <terme> | <facteur>
 *
 * Lit un facteur, et s'il est suivi d'un opérateur multiplicatif ('*' ou '/'),
 * lit le terme suivant.
 *
 * @warning L'évaluation se fait de la DROITE vers la GAUCHE.
 *
 * @return int La valeur numérique calculée du terme.
 */
int terme();

/* ANALYSE BASSE (Module — Abib) */

/**
 * @brief Analyse et évalue la règle BNF :
 *        <facteur> -> <nombre> | '(' <expression> ')'
 *
 * Détermine si le caractère courant correspond au début d'un nombre ou à une
 * parenthèse ouvrante. S'il s'agit d'une parenthèse, appelle expression()
 * puis vérifie la présence de la parenthèse fermante.
 *
 * @return int La valeur numérique du facteur.
 */
int facteur();

/**
 * @brief Analyse et évalue la règle BNF :
 *        <nombre> -> <chiffre> <nombre> | <chiffre>
 *
 * Accumule les chiffres successifs pour former un entier complet.
 * Utilise lire_brut() pour interdire les espaces à l'intérieur d'un nombre.
 *
 * @return int La valeur entière du nombre reconnu.
 */
int nombre();

/**
 * @brief Analyse et évalue la règle BNF :
 *        <chiffre> -> '0' | '1' | ... | '9'
 *
 * Vérifie si calu est un chiffre. Si oui, retourne sa valeur numérique et
 * avance la lecture. Sinon, déclenche une erreur de syntaxe.
 *
 * @return int La valeur du chiffre (entre 0 et 9).
 */
int chiffre();

/* GESTION DES ERREURS (Module — Alhousseynou) */

/**
 * @brief Signale une erreur syntaxique avec un message explicatif.
 *
 * Affiche le message sur stderr, indique le caractère fautif (calu),
 * et positionne erreur_syntaxe à 1.
 *
 * @param message Description de l'erreur détectée.
 */
void signaler_erreur(const char *message);

/**
 * @brief Procédure de récupération après une erreur.
 *
 * Consomme tous les caractères jusqu'au prochain '=' ou '.',
 * permettant de relancer l'analyse sur la prochaine expression.
 */
void retablissement();

#endif /* PARSER_H */