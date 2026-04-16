/**
 * @file erreurs.c
 * @brief Gestion des erreurs syntaxiques — Alhousseynou AGNE
 *
 * Ce fichier contient :
 *   - La variable globale erreur_syntaxe
 *   - La fonction signaler_erreur() qui affiche un message d'erreur
 *   - La fonction retablissement() qui reprend la lecture après une erreur
 */

/* On inclut parser.h pour avoir accès à toutes les déclarations communes */
#include "parser.h"

/* =========================================================================
   VARIABLE GLOBALE
   =========================================================================
   "erreur_syntaxe" est un drapeau (un interrupteur) :
     - 0 = tout va bien, pas d'erreur
     - 1 = une erreur a été détectée
   Cette variable est utilisée par tous les autres modules du projet.
   C'est pourquoi elle est déclarée ici mais visible partout (extern dans parser.h).
*/
int erreur_syntaxe = 0;

/* =========================================================================
   FONCTION : signaler_erreur
   =========================================================================
   But : afficher un message d'erreur quand l'utilisateur écrit
         une expression incorrecte, comme "2 ++ 3" ou "(2 + ".

   Paramètre : message — une phrase qui explique ce qui ne va pas.

   Exemple d'utilisation par les autres membres :
       signaler_erreur("parenthese fermante attendue");
       signaler_erreur("chiffre attendu");
*/
void signaler_erreur(const char *message)
{
    /*
     * "fprintf(stderr, ...)" affiche sur la sortie d'erreur (en rouge
     * dans certains terminaux). C'est mieux que printf pour les erreurs.
     *
     * On affiche :
     *   - le mot "Erreur"
     *   - le message reçu en paramètre
     *   - le caractère fautif contenu dans "calu"
     *     (calu = le caractère que le programme était en train de lire)
     */
    fprintf(stderr, "\nErreur : %s (caractere fautif : '%c')\n", message, calu);

    /*
     * On met erreur_syntaxe à 1 pour signaler qu'une erreur a eu lieu.
     * Le main.c de Maimouna va lire cette variable pour savoir
     * si l'expression était correcte ou non.
     */
    erreur_syntaxe = 1;
}

/* =========================================================================
   FONCTION : retablissement
   =========================================================================
   But : après une erreur, le programme ne s'arrête pas.
         Il faut "sauter" tout ce qui reste de l'expression incorrecte
         pour pouvoir analyser la prochaine expression proprement.

   Concrètement : on lit et on ignore tous les caractères
   jusqu'à trouver '=' (fin d'expression) ou '.' (fin du programme).

   Exemple :
     L'utilisateur tape "2 ++ 3 ="
     Après l'erreur sur "++", on saute jusqu'au '='
     Comme ça le programme peut repartir sur la prochaine expression.
*/
void retablissement()
{
    /*
     * Tant que le caractère courant (calu) n'est pas '=' ni '.'
     * on continue à lire le caractère suivant avec lire_brut()
     * pour avancer dans le texte.
     */
    while (calu != '=' && calu != '.')
    {
        lire_brut();
    }
}
