# Analyseur et Evaluateur d'Expressions Arithmetiques

**Projet de Langage C — DIC1 | ESP Dakar / UCAD | Annee 2025–2026**

Programme en C qui lit des expressions arithmetiques, verifie leur syntaxe selon une grammaire BNF, et calcule leur valeur numerique a l'aide d'un analyseur recursif descendant.

---

## Table des matieres

- [Fonctionnalites](#fonctionnalites)
- [Prerequis](#prerequis)
- [Compilation et lancement](#compilation-et-lancement)
- [Tests automatisés](#tests-automatisés)
- [Utilisation](#utilisation)
- [Grammaire BNF](#grammaire-bnf)
- [Architecture du projet](#architecture-du-projet)
- [Equipe](#equipe)

---

## Fonctionnalites

- **Analyse syntaxique** : verifie qu'une expression respecte la grammaire BNF definie
- **Evaluation** : calcule la valeur numerique des expressions correctes
- **Gestion des priorites** : `*` et `/` sont prioritaires sur `+` et `-`
- **Parentheses** : permettent de modifier l'ordre d'evaluation
- **Evaluation droite vers gauche** : entre operateurs de meme priorite (conforme au cahier des charges)
- **Gestion des erreurs** : messages explicites en cas de syntaxe incorrecte, avec recuperation automatique
- **Espaces toleres** : partout sauf a l'interieur d'un nombre
- **Session interactive** : traitement de plusieurs expressions, terminees par `=`, jusqu'au caractere `.`

---

## Prerequis

- **GCC** (ou tout compilateur C compatible C99)
- **Make** (optionnel, pour utiliser le Makefile)

### Verifier l'installation

```bash
gcc --version
make --version
```

---

## Compilation et lancement

### Option 1 : Avec Make

```bash
make
```

Cela produit l'executable `analyseur` (ou `analyseur.exe` sous Windows).

### Option 2 : Compilation manuelle

```bash
gcc -Wall -Wextra -o analyseur main.c lexique.c analyse_haute.c analyse_basse.c erreur.c
```

### Lancer le programme

```bash
./analyseur
```

Sous Windows :

```bash
.\analyseur.exe
```

### Nettoyer les fichiers compiles

```bash
make clean
```

---

## Tests automatisés

Le projet inclut un système de tests automatisés pour vérifier que l'analyseur respecte toujours la grammaire et les règles d'évaluation.

### Exécuter les tests

Lancez simplement la commande suivante :

```bash
make test
```

### Fonctionnement
1. Le projet compile un petit programme **universel** en C (`tests/tester.c`).
2. Ce programme parcourt le fichier `tests/cas_de_test.txt`.
3. Il compare les résultats obtenus avec les résultats attendus et affiche un compte rendu stylisé directement dans votre terminal.

## Utilisation

Le programme fonctionne en mode interactif. A chaque invite `A toi :`, entrez une expression arithmetique terminee par `=`. Tapez `.` pour quitter.

### Exemple de session

```
A toi : 2 * 2 =
la syntaxe de l'expression est correcte
sa valeur est 4

A toi : (2 + 3) * (10 - 2) - 12 * (1000 + 15) =
la syntaxe de l'expression est correcte
sa valeur est -12140

A toi : 5 - 3 + 2 =
la syntaxe de l'expression est correcte
sa valeur est 0

A toi : 2 ++ 3 =
la syntaxe de l'expression est erronee

A toi : .
Au revoir...
```

### Regles a connaitre

| Regle | Exemple | Resultat |
|---|---|---|
| Priorite `*` `/` sur `+` `-` | `2 + 3 * 4 =` | `14` |
| Evaluation droite vers gauche | `5 - 3 + 2 =` | `0` (= 5 - (3+2)) |
| Evaluation droite vers gauche | `100 / 10 / 2 =` | `20` (= 100 / (10/2)) |
| Parentheses modifient la priorite | `(2 + 3) * 4 =` | `20` |
| Espaces autorises entre elements | `2  +  3 =` | `5` |
| Espaces interdits dans un nombre | `1 23 + 4 =` | **ERREUR** |

---

## Grammaire BNF

La syntaxe reconnue est definie par la grammaire non contextuelle suivante :

```
expression              -> terme operateur-additif expression | terme
terme                   -> facteur operateur-multiplicatif terme | facteur
facteur                 -> nombre | '(' expression ')'
nombre                  -> chiffre nombre | chiffre
chiffre                 -> '0' | '1' | ... | '9'
operateur-additif       -> '+' | '-'
operateur-multiplicatif -> '*' | '/'
```

L'analyseur est construit par **descente recursive** : chaque non-terminal de la grammaire correspond a une fonction C du meme nom.

---

## Architecture du projet

```
projet-langage-C/
├── parser.h           <- En-tete commun : declarations de toutes les fonctions et variables globales
├── main.c             <- Boucle principale : invite, analyse, affichage des resultats
├── lexique.c          <- Lecture de caracteres : calu, lire_utile(), lire_brut()
├── analyse_haute.c    <- Regles de haut niveau : expression(), terme()
├── analyse_basse.c    <- Regles de bas niveau : facteur(), nombre(), chiffre()
├── erreur.c           <- Gestion des erreurs : signaler_erreur(), retablissement()
├── Makefile           <- Automatisation de la compilation
├── tests/
│   ├── cas_de_test.txt <- Case de test (expressions correctes et erronées)
│   └── tester.c        <- Programme C de test universel (remplace le script .sh)
├── CONTRIBUTING.md    <- Guide de contribution et conventions de l'equipe
└── README.md          <- Ce fichier
```

### Dependances entre modules

```
main.c
  ├── lexique.c          (lire_utile, lire_brut, calu)
  ├── analyse_haute.c    (expression, terme)
  │     └── analyse_basse.c  (facteur, nombre, chiffre)
  │           └── analyse_haute.c  (expression — appel recursif via parentheses)
  └── erreur.c           (erreur_syntaxe, signaler_erreur, retablissement)
```

---

## Equipe

| Membre | Role | Fichier(s) |
|---|---|---|
| **Maimouna DIALLO** | Integration et coordination | `parser.h`, `main.c` |
| **Boubacar LY** | Module lexique | `lexique.c` |
| **Cecile Anta NGOM** | Analyse de haut niveau | `analyse_haute.c` |
| **Mouhamadou Abib DRAME** | Analyse de bas niveau | `analyse_basse.c` |
| **Alhousseynou AGNE** | Gestion des erreurs | `erreur.c` |
| **Ousmane FAYE** | Build et tests | `Makefile`, `tests/` |

---

*Projet realise dans le cadre du module de Langage C, Departement Genie Informatique, ESP Dakar (UCAD).*
