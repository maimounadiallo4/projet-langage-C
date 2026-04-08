# 📐 Projet C — Analyse et Évaluation d'Expressions Arithmétiques
**DIC1 — ESP/UCAD | Année 2025–2026**

---

## 👥 Équipe et Responsabilités

| Membre | Branche | Fichier(s) |
|---|---|---|
| Maïmouna DIALLO | `branch-maimouna` | `parser.h`, `main.c` |
| Boubacar LY | `branch-boubacar` | `lexique.c` |
| Cécile Anta NGOM | `branch-cecile` | `analyse_haute.c` |
| Mouhamadou Abib DRAME | `branch-abib` | `analyse_basse.c` |
| Alhousseynou AGNE | `branch-alhousseynou` | `erreurs.c` |
| Ousmane FAYE | `branch-ousmane` | `Makefile`, `tests/` |

---

## 🌿 Structure des Branches

```
main              ← code stable et validé uniquement
└── dev           ← branche d'intégration (jamais cassée)
    ├── branch-maimouna
    ├── branch-boubacar
    ├── branch-cecile
    ├── branch-abib
    ├── branch-alhousseynou
    └── branch-ousmane
```

> ⚠️ **Personne ne push directement sur `main` ou `dev`.** Tout passe par une Pull Request.

---

## 🚀 Setup Initial (une seule fois)

```bash
# 1. Cloner le dépôt
git clone <url-du-repo>
cd projet_c

# 2. Se positionner sur dev
git checkout dev

# 3. Créer et basculer sur ta branche personnelle
git checkout -b branch-tonprenom

# 4. Pousser la branche sur GitHub
git push origin branch-tonprenom
```

---

## 🔄 Routine Quotidienne (à suivre CHAQUE JOUR)

### ① Avant de commencer à coder — Synchroniser

```bash
# Se placer sur ta branche
git checkout branch-tonprenom

# Récupérer les dernières mises à jour de dev
git fetch origin
git merge origin/dev

# Résoudre les conflits si besoin, puis continuer
```

> 💡 Faire cette étape chaque matin évite 90% des conflits de merge.

### ② Pendant le travail — Sauvegarder régulièrement

```bash
# Voir ce qui a changé
git status

# Ajouter ton fichier (et UNIQUEMENT le tien)
git add mon_fichier.c

# Commiter avec un message clair (voir convention ci-dessous)
git commit -m "feat(lexique): implémente lire_utile et lire_brut"

# Pousser sur ta branche
git push origin branch-tonprenom
```

### ③ Quand un module est terminé — Créer une Pull Request(a ne pas oublier )

1. Aller sur GitHub → onglet **Pull Requests** → **New Pull Request**
2. Choisir : `branch-tonprenom` → `dev`
3. Titre : `[NOM] Module lexique terminé`
4. Demander une review à **Maïmouna** (responsable intégration)
5. Attendre la validation avant de merger

---

## ✍️ Convention de Commits

Format : `type(module): description courte en français`

| Type | Usage | Exemple |
|---|---|---|
| `feat` | Nouvelle fonctionnalité | `feat(lexique): ajoute lire_brut` |
| `fix` | Correction de bug | `fix(erreurs): corrige division par zéro` |
| `test` | Ajout de tests | `test: ajoute cas 12 à 15` |
| `docs` | Documentation | `docs: met à jour parser.h` |
| `refactor` | Réécriture sans changement de comportement | `refactor(facteur): simplifie la boucle` |

> ✅ Un bon commit = **une seule chose faite** + message qui explique **pourquoi**, pas juste **quoi**.

---

## 🚫 Règles Anti-Conflits (Obligatoires)

| Règle | Explication |
|---|---|
| **Toucher uniquement son fichier `.c`** | Chacun a son domaine, on ne modifie pas le fichier d'un autre |
| **`parser.h` = Maïmouna uniquement** | C'est le contrat commun, toute modif passe par elle |
| **Ne merger sur `dev` que si ça compile** | Tester avec `gcc *.c -o test` avant toute PR |
| **Un seul fichier par commit** | Facilite la relecture et la détection d'erreurs |
| **Jamais de `git push --force`** | Interdit sur `dev` et `main`, cela écrase le travail des autres |

---

## ⚙️ Tester avant de Pusher

Avant chaque `git push`, vérifier que le code compile :

```bash
# Depuis la racine du projet
gcc -Wall -Wextra -c mon_fichier.c -o mon_fichier.o

# Quand tous les modules sont prêts, test complet :
make
```

> Si `gcc` signale des warnings, les corriger avant de pusher.

---

## 🆘 Résolution de Conflits

Si Git signale un conflit après un `git merge` :

```bash
# 1. Voir les fichiers en conflit
git status

# 2. Ouvrir le fichier concerné — chercher les marqueurs :
# <<<<<<< HEAD
#   (ton code)
# =======
#   (code de dev)
# >>>>>>> origin/dev

# 3. Garder la bonne version, supprimer les marqueurs

# 4. Marquer le conflit comme résolu
git add fichier_en_conflit.c
git commit -m "fix: résolution conflit merge avec dev"
```

> 💡 En cas de doute, appeler Maïmouna la goat avant de résoudre un conflit dans un fichier qui n'est pas le tien.

---

## 📅 Planning de Livraison

| Phase | Quoi | Qui | Deadline |
|---|---|---|---|
| J1–J2 | `parser.h` + stubs vides | Maïmouna | **Priorité absolue** |
| J2–J3 | `lexique.c` + `erreurs.c` | Boubacar + Alhousseynou | En parallèle |
| J3–J4 | `analyse_haute.c` + `analyse_basse.c` | Cécile + Abib | En parallèle |
| J4–J5 | `Makefile` + 20 cas de test | Ousmane | Après les modules |
| J5–J6 | `main.c` + intégration finale | Maïmouna | Avant soutenance |
| **20 avril** | **Rendu + Présentation** | **Tout le groupe** | ⚠️ |

---

## 📁 Structure du Projet

```
projet_c/
├── parser.h          ← Maïmouna — Contrat commun (NE PAS MODIFIER sans elle)
├── main.c            ← Maïmouna — Boucle principale
├── lexique.c         ← Boubacar  — lire_utile(), lire_brut(), calu
├── analyse_haute.c   ← Cécile    — expression(), terme()
├── analyse_basse.c   ← Abib      — facteur(), nombre()
├── erreurs.c         ← Alhousseynou — erreur_syntaxe, signaler_erreur()
├── Makefile          ← Ousmane
├── tests/
│   └── cas_de_test.txt ← Ousmane — 20+ expressions correctes et fausses
├── .gitignore
└── CONTRIBUTING.md   ← Ce fichier
```

---

## 🔧 Fichier `.gitignore`

S'assurer que ce fichier est à la racine du projet :

```gitignore
# Binaires compilés
*.o
*.out
projet_c
a.out

# Fichiers système
.DS_Store
Thumbs.db

# Fichiers IDE
.vscode/
.idea/
```

---

Aythia niou dem 