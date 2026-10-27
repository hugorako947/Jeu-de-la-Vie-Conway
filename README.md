# 🧬 Jeu de la Vie de Conway — C++ / SFML

![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=cplusplus&logoColor=white)
![SFML](https://img.shields.io/badge/SFML-2.5%20%2F%202.6-8CC445?logo=sfml&logoColor=white)
![Build](https://img.shields.io/badge/Build-Makefile-427819)
![Licence](https://img.shields.io/badge/Licence-MIT-informational)

Implémentation en C++ du **Jeu de la Vie de John Conway**, un automate cellulaire célèbre. À partir d'une grille initiale, les cellules naissent, survivent ou meurent au fil des générations selon quatre règles simples, et font émerger des motifs étonnamment complexes.

Le projet propose deux modes d'affichage (console ASCII ou fenêtre graphique SFML), charge la grille de départ depuis un fichier texte, sauvegarde chaque génération, détecte automatiquement la stabilisation, et embarque une suite de tests unitaires.

---

## 📑 Sommaire

1. [Qu'est-ce que le Jeu de la Vie ?](#-quest-ce-que-le-jeu-de-la-vie-)
2. [Aperçu](#-aperçu)
3. [Architecture du code](#-architecture-du-code)
4. [Prérequis](#-prérequis)
5. [Compilation](#-compilation)
6. [Utilisation](#-utilisation)
7. [Format des fichiers de grille](#-format-des-fichiers-de-grille)
8. [Tests unitaires](#-tests-unitaires)
9. [Problèmes connus et corrections](#-problèmes-connus-et-corrections)
10. [Pistes d'amélioration](#-pistes-damélioration)
11. [Auteur](#-auteur)

---

## 🔬 Qu'est-ce que le Jeu de la Vie ?

Le Jeu de la Vie est un **automate cellulaire** imaginé par le mathématicien John Conway en 1970. Ce n'est pas un jeu au sens habituel : il n'y a pas de joueur. On place des cellules vivantes sur une grille, puis on observe leur évolution, génération après génération, dictée uniquement par les règles suivantes.

Pour chaque cellule, on compte ses **8 voisines** (horizontales, verticales et diagonales) :

| Situation de la cellule | Nombre de voisines vivantes | Résultat |
|---|---|---|
| Vivante | 2 ou 3 | Elle **survit** |
| Vivante | 0, 1, ou 4 et plus | Elle **meurt** (isolement ou surpopulation) |
| Morte | exactement 3 | Elle **naît** |
| Morte | autre | Elle **reste morte** |

Toutes les cellules évoluent simultanément : le calcul d'une génération se fait à partir de l'état précédent, jamais de l'état en cours de modification. Malgré leur simplicité, ces règles produisent des motifs remarquables : structures stables (le « bloc »), oscillateurs (le « clignotant »), et vaisseaux qui se déplacent sur la grille (le « planeur »).

---

## 👁 Aperçu

La grille d'exemple fournie (`grille.txt`) contient un **planeur** (glider), le motif mobile le plus connu du Jeu de la Vie. En mode console, les premières générations s'affichent ainsi (`1` = cellule vivante, `0` = morte) :

```
ÉTAT INITIAL        ITÉRATION 1         ITÉRATION 2         ITÉRATION 3
0 0 1 0 0 . . .     0 0 0 0 0 . . .     0 0 0 0 0 . . .     0 0 0 0 0 . . .
0 0 0 1 0 . . .     0 1 0 1 0 . . .     0 0 0 1 0 . . .     0 0 1 0 0 . . .
0 1 1 1 0 . . .     0 0 1 1 0 . . .     0 1 0 1 0 . . .     0 0 0 1 1 . . .
0 0 0 0 0 . . .     0 0 1 0 0 . . .     0 0 1 1 0 . . .     0 0 1 1 0 . . .
0 0 0 0 0 . . .     0 0 0 0 0 . . .     0 0 0 0 0 . . .     0 0 0 0 0 . . .
```

Le motif se déplace en diagonale tout en se reconstituant toutes les 4 générations : c'est la signature du planeur.

En mode graphique, la même simulation s'ouvre dans une fenêtre SFML où chaque cellule est un carré, avec une touche pour mettre en pause.

---

## 🏗 Architecture du code

Le projet est écrit en **C++ orienté objet** et illustre notamment le **patron de conception État (State pattern)** : l'état d'une cellule (vivante ou morte) est un objet à part entière, ce qui évite les conditions à rallonge et rend les règles faciles à faire évoluer.

| Fichier(s) | Rôle |
|---|---|
| `main.cpp` | Point d'entrée : menu interactif (simulation ou tests, console ou graphique, choix de la grille et de la vitesse) |
| `Cellule.hpp` / `.cpp` | Une cellule, qui délègue son comportement à son état courant (via `std::unique_ptr`, sémantique de déplacement, pas de copie) |
| `Etat_cellule.hpp` | Classe abstraite : interface commune à tous les états |
| `EtatVivant.hpp` / `.cpp` | État « vivante » et calcul de son état suivant |
| `EtatMorte.hpp` / `.cpp` | État « morte » et calcul de son état suivant |
| `Regles.hpp` / `.cpp` | Les règles de Conway isolées (`survie` : 2 ou 3 voisines ; `naissance` : exactement 3). Les isoler permet de les tester et d'en créer des variantes |
| `Grille.hpp` / `.cpp` | La grille de cellules : comptage des voisines, mise à jour d'une génération, affichage texte |
| `Fichier.hpp` / `.cpp` | Lecture de la grille initiale et écriture de chaque génération dans un fichier |
| `Jeu.hpp` / `.cpp` | Chef d'orchestre : boucle de simulation, détection de stabilité, lancement des tests |
| `Graphique.hpp` / `.cpp` | Rendu graphique avec SFML (fenêtre, horloge, pause) |
| `Tests.hpp` / `.cpp` | Suite de tests unitaires vérifiant les règles sur des motifs connus |
| `Makefile` | Compilation, détection automatique de la version de SFML |
| `grille.txt` | Exemple de grille de départ (un planeur) |

**Flux général :** `Fichier` lit le fichier → la `Grille` est peuplée de `Cellule`s → à chaque tour, `Jeu` appelle `Grille::mettreAJour()`, qui pour chaque cellule compte ses voisines vivantes, interroge `Regles` via l'état courant, puis applique le nouvel état à toutes les cellules en même temps → le résultat est affiché (console ou SFML) et sauvegardé par `Fichier`.

---

## 🛠 Prérequis

- Un compilateur C++ supportant **C++14 ou C++17** (par exemple **g++** 7 ou plus récent).
- **make** (GNU Make).
- **SFML 2.5 ou 2.6** (bibliothèque graphique), nécessaire même pour le mode console car `Graphique.cpp` est toujours compilé.

### Installation des dépendances

**Linux (Debian / Ubuntu)** — une cible du Makefile est prévue :
```bash
make install-deps
# équivaut à : sudo apt update && sudo apt install -y build-essential g++ libsfml-dev
```

**macOS** (avec [Homebrew](https://brew.sh/)) :
```bash
brew install sfml make
```

**Windows :** le plus simple est d'utiliser **MSYS2 / MinGW-w64** :
```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-sfml make
```
Alternativement, [SFML pour Visual Studio](https://www.sfml-dev.org/download.php) avec le compilateur MSVC, en configurant un projet manuellement (le Makefile fourni cible `g++`).

---

## ⚙ Compilation

Depuis la racine du projet :

```bash
git clone https://github.com/hugorako947/Jeu-de-la-Vie-Conway.git
cd Jeu-de-la-Vie-Conway
make
```

Le Makefile détecte automatiquement la version de SFML installée et produit un exécutable nommé **`Jeu`**.

Autres commandes disponibles :

```bash
make          # Compile le projet
make clean    # Supprime l'exécutable et les fichiers objets
make rebuild  # Nettoie puis recompile entièrement
make help     # Affiche l'aide
```

> [!WARNING]
> **La compilation échoue en l'état sur Linux et macOS**, à cause d'incohérences entre les noms de fichiers du dépôt et les noms utilisés dans les `#include`. Ces systèmes distinguent les majuscules des minuscules. Voir [Problèmes connus et corrections](#-problèmes-connus-et-corrections) pour la marche à suivre (quelques renommages). Sous Windows, qui ignore la casse, le problème ne se pose pas.

---

## ▶ Utilisation

Lancez l'exécutable :

```bash
./Jeu          # Linux / macOS
Jeu.exe        # Windows
```

Le programme pose une série de questions :

1. **Simulation ou tests unitaires ? (s/t)** — tapez `s` pour lancer une simulation.
2. **Chemin de la grille initiale** — par exemple `grille.txt`.
3. **Mode console ou graphique ? (c/g)** — `c` affiche le résultat en texte dans le terminal, `g` ouvre une fenêtre SFML.
4. **Vitesse de lecture (secondes par itération)** — par exemple `0.5`. Mettez `0` pour un défilement immédiat.

Exemple complet en mode console :

```
------------------JEU DE LA VIE------------------
Voulez-vous lancer la simulation ou les tests unitaires ? (s/t): s
Chemin de la grille initiale: grille.txt
Mode console ou graphique ? (c/g): c
Vitesse de lecture (seconde(s) par iterations): 0.5
```

La simulation s'arrête automatiquement lorsque la grille **se stabilise** (deux générations identiques), lorsqu'elle devient vide, ou au bout du nombre maximal d'itérations (1000 par défaut).

> [!IMPORTANT]
> Le programme écrit chaque génération dans un dossier **`output/`**. Celui-ci n'existe pas dans le dépôt : **créez-le avant de lancer la simulation**, sinon la sauvegarde échoue.
> ```bash
> mkdir output
> ```

---

## 📄 Format des fichiers de grille

Un fichier de grille est un simple fichier texte :

- **première ligne** : deux entiers, le nombre de lignes puis le nombre de colonnes ;
- **lignes suivantes** : la grille, chaque cellule valant `0` (morte) ou `1` (vivante), séparées par des espaces.

Exemple (`grille.txt`, un planeur sur une grille de 5 × 10) :

```
5 10
0 0 1 0 0 0 0 0 0 0
0 0 0 1 0 0 0 0 0 0
0 1 1 1 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
```

Vous pouvez créer vos propres grilles en respectant ce format : un bloc stable, un clignotant, un canon à planeurs, etc.

---

## 🧪 Tests unitaires

Le mode tests (`t` au lancement, ou le code de `Tests.cpp`) vérifie que les règles de Conway sont correctement implémentées sur des motifs de référence : grille vide, bloc stable, clignotant (oscillateur de période 2) et planeur. Pour chaque cas, il compare l'état obtenu après un certain nombre d'itérations à l'état attendu.

> [!IMPORTANT]
> Les tests lisent des fichiers situés dans un dossier **`tests/`** (`tests/planeur_depart.txt`, `tests/clignotant_attendu.txt`, etc.) **qui n'est pas présent dans le dépôt**. En l'état, tous les tests échouent avec « Impossible d'ouvrir le fichier ». Pour les faire fonctionner, créez le dossier `tests/` et les fichiers de grille correspondants (voir la liste dans `Jeu.cpp`), au format décrit ci-dessus.

---

## 🐛 Problèmes connus et corrections

Le projet a été testé avec g++ et SFML 2.6. Voici les points à corriger pour qu'il compile et s'exécute partout.

### 1. Noms de fichiers incohérents (bloque la compilation sous Linux / macOS)

Plusieurs `#include` ne correspondent pas aux noms réels des fichiers. Sous Windows la casse est ignorée, mais sous Linux et macOS la compilation s'arrête. Il faut aligner les noms :

| Nom réel dans le dépôt | Nom attendu par le code | Action conseillée |
|---|---|---|
| `Etat_cellule.hpp` | `Etat_Cellule.hpp` (dans les `#include`) | Renommer le fichier en `Etat_Cellule.hpp` |
| `EtatMorte.hpp` / `EtatMorte.cpp` | `EtatMort.hpp` (dans les `#include`) | Renommer en `EtatMort.hpp` / `EtatMort.cpp` |

Et deux ajustements de texte :
- dans le `Makefile`, remplacer `EtatMort.cpp` par le nom de fichier choisi (ou renommer le fichier comme ci-dessus) ;
- dans `Cellule.cpp`, un `#include "Etatvivant.hpp"` doit devenir `#include "EtatVivant.hpp"`.

Après ces quelques renommages, `make` compile sans erreur et la simulation fonctionne. Le plus propre est de fixer définitivement une convention de noms (par exemple tout en `EtatMort` / `Etat_Cellule`) et de committer les fichiers renommés.

### 2. Dossiers `output/` et `tests/` manquants

- `output/` doit exister avant une simulation (voir [Utilisation](#-utilisation)).
- `tests/` et ses fichiers de grille doivent être créés pour que le mode tests fonctionne (voir [Tests unitaires](#-tests-unitaires)).

Astuce : committer ces dossiers avec un fichier `.gitkeep` à l'intérieur permet à Git de les conserver même vides.

---

## 💡 Pistes d'amélioration

- Fournir les fichiers du dossier `tests/` pour que la suite de tests passe au vert.
- Créer automatiquement le dossier `output/` au lancement s'il n'existe pas.
- Ajouter une bibliothèque de motifs classiques (canon à planeurs de Gosper, vaisseaux, etc.).
- Gérer une grille torique (les bords se rejoignent) en option.
- Permettre de dessiner la grille de départ directement à la souris en mode graphique.

---

## 👤 Auteur

Projet réalisé par **Hugo Rakotonanahary** — [@hugorako947](https://github.com/hugorako947)

Un projet d'automate cellulaire en C++ mettant en pratique la programmation orientée objet, le patron de conception État, la gestion de la mémoire moderne (pointeurs intelligents) et le rendu graphique avec SFML.
