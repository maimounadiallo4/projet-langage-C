/**
 * @file parser.h
 * @brief Fichier d'en-tête principal pour l'analyseur d'expressions arithmétiques.
 * * Ce fichier contient les déclarations des variables globales, des fonctions 
 * d'analyse syntaxique (basées sur la grammaire BNF) et des utilitaires lexicaux.
 * * @note CONTRAT D'ÉQUIPE : Ce fichier est le point central du projet. 
 * Toute modification de ce fichier doit être validée par Maïmouna.
 */

#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* ========================================================================= */
/* VARIABLES GLOBALES (Module Lexique - Boubacar)                            */
/* ========================================================================= */

/**
 * @brief Caractère actuellement examiné par l'analyseur.
 * * Cette variable doit toujours contenir le premier caractère non encore traité 
 * du flux d'entrée. Elle est mise à jour par la fonction lire_utile().
 */
extern char calu; 

/* ========================================================================= */
/* ANALYSE HAUTE (Module - Cécile)                                           */
/* ========================================================================= */

/**
 * @brief Analyse et évalue la règle BNF : <expression> -> <terme> <op-add> <expression> | <terme>
 * * Lit un terme, et s'il est suivi d'un opérateur additif ('+' ou '-'), lit 
 * l'expression suivante.
 * * @warning D'après le sujet, entre opérateurs de même priorité, l'évaluation 
 * se fait de la DROITE vers la GAUCHE. (ex: 5-3+2 est évalué comme 5-(3+2)).
 * * @return int La valeur numérique calculée de l'expression.
 */
int expression();

/**
 * @brief Analyse et évalue la règle BNF : <terme> -> <facteur> <op-mult> <terme> | <facteur>
 * * Lit un facteur, et s'il est suivi d'un opérateur multiplicatif ('*' ou '/'), 
 * lit le terme suivant.
 * * @warning L'évaluation se fait de la DROITE vers la GAUCHE.
 * * @return int La valeur numérique calculée du terme.
 */
int terme();

/* ========================================================================= */
/* ANALYSE BASSE (Module - Abib)                                             */
/* ========================================================================= */

/**
 * @brief Analyse et évalue la règle BNF : <facteur> -> <nombre> | '(' <expression> ')'
 * * Détermine si le caractère courant correspond au début d'un nombre ou à une 
 * parenthèse ouvrante. S'il s'agit d'une parenthèse, appelle expression() puis 
 * vérifie la présence de la parenthèse fermante.
 * * @return int La valeur numérique du facteur.
 */
int facteur();

/**
 * @brief Analyse et évalue la règle BNF : <nombre> -> <chiffre> <nombre> | <chiffre>
 * * Accumule les chiffres successifs pour former un entier complet.
 * * @return int La valeur entière du nombre reconnu.
 */
int nombre();

/**
 * @brief Analyse et évalue la règle BNF : <chiffre> -> '0' | '1' | ... | '9'
 * * Vérifie si calu est un chiffre. Si oui, retourne sa valeur numérique et 
 * avance la lecture. Sinon, déclenche une erreur de syntaxe.
 * * @return int La valeur du chiffre (entre 0 et 9).
 */
int chiffre();

/* ========================================================================= */
/* UTILITAIRES ET GESTION DES ERREURS (Modules - Boubacar & Alhousseynou)    */
/* ========================================================================= */

/**
 * @brief Fonction de lecture "améliorée".
 * * Réitère l'appel à getchar() jusqu'à obtenir un caractère non blanc 
 * (ignore les espaces, tabulations, sauts de ligne) et stocke le résultat 
 * dans la variable globale 'calu'.
 */
void lire_utile();

/**
 * @brief Gère les cas où la chaîne n'appartient pas à la grammaire.
 * * Affiche le message "la syntaxe de l'expression est erronée", vide le 
 * buffer restant si nécessaire, et permet au programme de se préparer pour 
 * la ligne suivante.
 */
void signaler_erreur();

#endif /* PARSER_H */