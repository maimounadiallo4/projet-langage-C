/**
 * @file main.c
 * @brief Point d'entrée du programme — Boucle principale d'analyse
 *        et d'évaluation d'expressions arithmétiques.
 *
 * @author Maïmouna DIALLO (intégration)
 *
 * Ce fichier orchestre les modules développés par chaque membre de l'équipe :
 *   - lexique.c    (Boubacar)  : lecture de caractères (lire_utile, lire_brut, calu)
 *   - analyse_haute.c (Cécile) : reconnaissance de expression() et terme()
 *   - analyse_basse.c (Abib)   : reconnaissance de facteur(), nombre(), chiffre()
 *   - erreur.c (Alhousseynou)  : signaler_erreur(), retablissement(), erreur_syntaxe
 *
 * === Fonctionnement général ===
 *
 * Le programme affiche une invite ("A toi : ") puis lit une expression
 * arithmétique terminée par le caractère '='.
 *   - Si la syntaxe est correcte, il affiche la valeur calculée.
 *   - Si la syntaxe est erronée, il l'indique à l'utilisateur.
 *   - Le caractère '.' met fin à la session (affiche "Au revoir...").
 *
 * Grammaire BNF reconnue :
 *   expression → terme opérateur-additif expression | terme
 *   terme      → facteur opérateur-multiplicatif terme | facteur
 *   facteur    → nombre | '(' expression ')'
 *   nombre     → chiffre nombre | chiffre
 *   chiffre    → '0' | '1' | ... | '9'
 *
 * L'évaluation entre opérateurs de même priorité se fait de la DROITE
 * vers la GAUCHE (cf. cahier des charges).
 *
 * Exemple de session :
 *   A toi : 2 * 2 =
 *   la syntaxe de l'expression est correcte
 *   sa valeur est 4
 *   A toi : (2 + 3) * (10 - 2) - 12 * (1000 + 15) =
 *   la syntaxe de l'expression est correcte
 *   sa valeur est -12140
 *   A toi : 2 ++ 3 =
 *   la syntaxe de l'expression est erronee
 *   A toi : .
 *   Au revoir...
 */

#include "parser.h"

/* ========================================================================= */
/* FONCTION PRINCIPALE                                                        */
/* ========================================================================= */

/**
 * @brief Point d'entrée du programme.
 *
 * Boucle principale :
 *   1. Affiche l'invite "A toi : "
 *   2. Appelle lire_utile() pour obtenir le premier caractère significatif.
 *   3. Si ce caractère est '.', on sort de la boucle → fin de session.
 *   4. Sinon, on lance l'analyse/évaluation de l'expression via expression().
 *   5. On vérifie que l'expression se termine bien par '='.
 *   6. On affiche le résultat ou le diagnostic d'erreur.
 *   7. On réinitialise le drapeau d'erreur et on recommence.
 *
 * @return int Code de retour (EXIT_SUCCESS).
 */
int main(void)
{
    int valeur;  /* Valeur calculée de l'expression courante */

    /* ------------------------------------------------------------------ */
    /* Boucle infinie : on traite les expressions une par une              */
    /* jusqu'à ce que l'utilisateur tape '.'                               */
    /* ------------------------------------------------------------------ */
    while (1)
    {
        /* ── Étape 1 : Afficher l'invite ────────────────────────────── */
        printf("A toi : ");
        fflush(stdout);  /* Force l'affichage immédiat (stdout peut être bufferisé) */

        /* ── Étape 2 : Lire le premier caractère utile ──────────────── */
        /*    lire_utile() saute les espaces/tabulations/sauts de ligne   */
        /*    et place le premier caractère significatif dans calu.        */
        lire_utile();

        /* ── Étape 3 : Tester la fin de session ────────────────────── */
        /*    Le caractère '.' indique que l'utilisateur veut quitter.    */
        if (calu == '.')
        {
            printf("Au revoir...\n");
            break;  /* Sort de la boucle while → fin du programme */
        }

        /* ── Étape 4 : Réinitialiser le drapeau d'erreur ───────────── */
        /*    Avant chaque nouvelle expression, on remet erreur_syntaxe   */
        /*    à 0 pour repartir sur une base propre.                      */
        erreur_syntaxe = 0;

        /* ── Étape 5 : Analyser et évaluer l'expression ─────────────── */
        /*    expression() est la fonction racine de notre analyseur       */
        /*    récursif descendant. Elle appelle terme(), qui appelle       */
        /*    facteur(), qui appelle nombre()/chiffre(), etc.              */
        /*    Si tout va bien, elle retourne la valeur numérique.          */
        /*    En cas d'erreur, signaler_erreur() est appelée en interne   */
        /*    et erreur_syntaxe passe à 1.                                 */
        valeur = expression();

        /* ── Étape 6 : Vérifier le '=' final ────────────────────────── */
        /*    Après avoir reconnu l'expression, le caractère courant      */
        /*    (calu) doit être '='. S'il ne l'est pas et qu'aucune        */
        /*    erreur n'a encore été détectée, c'est une erreur de syntaxe. */
        if (!erreur_syntaxe)
        {
            if (calu != '=')
            {
                signaler_erreur("'=' attendu en fin d'expression");
            }
        }

        /* ── Étape 7 : Afficher le résultat ─────────────────────────── */
        if (erreur_syntaxe)
        {
            /* L'expression contenait une erreur syntaxique.              */
            printf("la syntaxe de l'expression est erronee\n");

            /* Appel à retablissement() pour consommer tous les           */
            /* caractères restants jusqu'au prochain '=' ou '.'.          */
            /* Cela permet de reprendre proprement l'analyse de la        */
            /* prochaine expression sans être perturbé par les résidus    */
            /* de l'expression erronée.                                   */
            retablissement();

            /* Cas spécial : si retablissement() s'est arrêté sur '.',   */
            /* cela signifie que l'utilisateur veut quitter. On sort.     */
            if (calu == '.')
            {
                printf("Au revoir...\n");
                break;
            }
        }
        else
        {
            /* L'expression est syntaxiquement correcte.                  */
            printf("la syntaxe de l'expression est correcte\n");
            printf("sa valeur est %d\n", valeur);
        }
    }

    return EXIT_SUCCESS;
}
