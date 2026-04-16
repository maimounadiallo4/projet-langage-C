/**
 * @file analyse_haute.c
 * @brief Implémentation des règles BNF de haut niveau :
 *        expression et terme.
 *
 * @author Cécile
 * @note L'évaluation se fait de la DROITE vers la GAUCHE
 *       pour les opérateurs de même priorité.
 */

#include "parser.h"

/**
 * @brief Analyse et évalue :
 *        <terme> -> <facteur> <op-mult> <terme> | <facteur>
 *
 * Évaluation droite-gauche par récursion directe.
 */
int terme() {
    int gauche = facteur();

    if (erreur_syntaxe) return 0;

    if (calu == '*' || calu == '/') {
        char op = calu;
        lire_utile();          /* consommer l'opérateur, passer au suivant */
        int droite = terme();  /* récursion → droite vers gauche */

        if (erreur_syntaxe) return 0;

        if (op == '*') {
            return gauche * droite;
        } else {
            if (droite == 0) {
                signaler_erreur("Division par zéro");
                return 0;
            }
            return gauche / droite;
        }
    }

    return gauche;
}

/**
 * @brief Analyse et évalue :
 *        <expression> -> <terme> <op-add> <expression> | <terme>
 *
 * Évaluation droite-gauche par récursion directe.
 */
int expression() {
    int gauche = terme();

    if (erreur_syntaxe) return 0;

    if (calu == '+' || calu == '-') {
        char op = calu;
        lire_utile();               /* consommer l'opérateur */
        int droite = expression();  /* récursion → droite vers gauche */

        if (erreur_syntaxe) return 0;

        if (op == '+') {
            return gauche + droite;
        } else {
            return gauche - droite;
        }
    }

    return gauche;
}
