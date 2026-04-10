/**
 * @file analyse_basse.c
 * @brief Grammaire de Bas Niveau  Facteurs, Nombres, Chiffres
 * @author Mouhamadou Abib DRAME
 */

#include "parser.h"

/*
 * chiffre
 * Précondition  : calu est un chiffre ('0'..'9').
 * Postcondition : calu est le caractère suivant (lu via lire_brut).
 * Retourne      : la valeur numérique du chiffre (0 à 9).
 */
int chiffre()
{
    int valeur;

    if (!isdigit((unsigned char)calu)) {
        signaler_erreur("chiffre ('0'..'9') attendu");
        return 0;
    }

    valeur = calu - '0';

    /* On lit le suivant en brut : les espaces dans un nombre sont interdits */
    lire_brut();

    return valeur;
}

/*
 * nombre
 * Précondition  : calu est un chiffre ('0'..'9').
 * Postcondition : calu est le premier caractère NON-chiffre suivant.
 *                 Si ce caractère est un blanc, lire_utile() est appelé
 *                 pour avancer jusqu'au prochain caractère utile.
 * Retourne      : la valeur numérique entière du nombre lu.
 *
 * Implémentation de la règle BNF :
 *   nombre → chiffre nombre | chiffre
 */
int nombre()
{
    int valeur = 0;

    if (!isdigit((unsigned char)calu)) {
        signaler_erreur("nombre : chiffre attendu");
        return 0;
    }

    /* Accumulation chiffre par chiffre */
    while (isdigit((unsigned char)calu)) {
        valeur = valeur * 10 + chiffre();
        if (erreur_syntaxe) return 0;
    }

    /*
     * calu est maintenant le premier caractère NON-chiffre
     * S'il est blanc, on avance jusqu'au prochain caractère utile
     * (opérateur, ')', '=', '.') pour que le reste de l'analyseur
     * puisse continuer normalement.
     */
    if (calu == ' ' || calu == '\t' || calu == '\n' || calu == '\r') {
        lire_utile();
    }

    return valeur;
}

/*
 * facteur
 * Précondition  : calu est le premier caractère du facteur (chiffre ou '(').
 * Postcondition : calu est le premier caractère suivant le facteur.
 * Retourne      : la valeur numérique du facteur évalué.
 *
 * Deux cas selon la grammaire BNF :
 *   facteur → nombre(si calu est un chiffre)
 *   facteur → '(' expression ')'  (si calu == '(')
 */
int facteur()
{
    int valeur;

    if (calu == '(') {
        /* Cas : facteur → '(' expression ')' */
        lire_utile();          /* consomme '(' → avance dans l'expression interne */
        valeur = expression();

        if (erreur_syntaxe) return 0;

        if (calu == ')') {
            lire_utile();      /* consomme ')' → avance au caractère suivant */
        } else {
            signaler_erreur("')' attendu pour fermer la parenthese");
        }

    } else if (isdigit((unsigned char)calu)) {
        /*Cas : facteur nombre*/
        valeur = nombre();

    } else {
        /*Cas d'erreur : ni chiffre ni '('*/
        signaler_erreur("nombre ou '(' attendu");
        valeur = 0;
    }

    return valeur;
}

