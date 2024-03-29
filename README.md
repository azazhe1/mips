# Projet CS351 (2022-2023): Émulateur MIPS

---
title: Projet CS351 (2022-2023): Émulateur MIPS
author: [CASARRUBIOS_VINCENT]
date: [18/10/22]
---

## Rendu 1

* Cochez (en remplaçant `[ ]` par `[x]`) si vous avez :
  - [X] Vérifié que `make test-cli` ne renvoie pas d'erreur. 
  `pb avec le makefile, cela crée bien les fichiers mais nous avons quand même les erreurs`
  - [X] Vérifié que `make tests` se plaint sur le nombre d'instructions et pas
      sur l'existence des fichiers de sortie.
  - [X] Vu que les soumissions se font avec `make tar`.


## Rendu 2

(Une dizaine de lignes devrait suffire à chaque fois)

* Comment avez-vous choisi de programmer l'analyse de texte (dont la lecture
des opérandes entières) ?

[Pour l'analyse de texte nous avons choisi de coder une fonction qui récupère le nom de l'opérateur et une fonction qui récupère les opérandes (les registres ou les valeurs d'offset selon le type de l'instruction). Nous avons réalisé une fonction de lecture d'opérande par type d'instruction. Au début nous récupérons le nom de l'instruction puis regardons le type de l'instruction (R, I ou J) afin d'appeler la bonne fonction.]

* Avez-vous vu des motifs récurrents émerger ? Avez-vous "factorisé" ces motifs
pour éviter de les répéter ? Si non, serait-ce difficile ?

[Pour chaque type nous avons des motifs récurrents. Pour le type R nous avons le registre OPCODE qui vaut 0 et c'est le registre fonction qui change. De plus l'odre des registres est toujours le même dans l'appel de la fonction. Par exemple si une commande possède les registres rs et rt en argument il faudra toujours placer rs avant rt; exemple : AND rd , rs, rt rt BEQ rs, rt offset]

* Comment avez-vous procédé pour écrire les tests ? Étes-vous confiant·e·s que
toutes les instructions gérées sont couvertes ? 

[Nous avons écrit les tests à la main de manière intelligente, nous avons testé toutes les commande sauf LR. Nous avons essayé de combler tous les cas possibles, pour le type R les registres sont compris entre 0 et 31 nous avons donc testé avec 0 et 31. Pour le type I la valeur immédiate est comprise entre -32768 et 32757, nous avons donc testé avec ces 2 valeurs. Pour le type J nous avons testé avec la valeur 0 (qui est le min) et la valeur 67108863( qui est le max)]

* Quelle a été votre expérience avec l'utilisation et la compréhension de la
documentation (ie. des annexes) ?

[L'annexe nous permet facilement de coder les instructions, cepandant la compréhension des commandes en elle même est plutôt difficile]

* Cochez (en remplaçant `[ ]` par `[x]`) si vous avez :
  - [X] Implémenté la traduction pour des instructions de toutes les catégories
      (calcul, comparaisons, sauts, HI/LO, mémoire)
  - [X] Implémenté la traduction pour toutes les instructions de l'annexe 2
  - [X] Pris en compte les cas particuliers : valeurs négatives, hors limites,
      noms d'instructions ou opérandes invalides...


## Rendu 3

(10/15 lignes devrait suffire à chaque fois)

* Quelle structure en modules planifiez-vous d'utiliser pour l'émulateur ?

[Pour l'émulateur, nous planifions d'utiliser 5 modules : 
 - Le module "header" permet d'afficher l'ensemble des erreurs, comme le nombre d'arguments incorrects d'une fonction, la non création du fichier demandé...
 - Le module "lecture_instructions" permet de lire l'instruction rentrée en paramètre et de récupérer le nom de l'instruction ainsi que les valeurs passées en paramètres (registres, valeurs immédiates, offset).
 - Le module "convert_hexa" est utilisé pour réaliser des conversions en décimal vers binaire ainsi qu'en binaire vers héxadécimal.
 - Le module "traduction_hexa_instructions" permet de traduire les instructions en hexadécimal.
 - Le module "instructions" comportera l'ensemble des fonctions propres aux instructions.]

* Quelles seront les fonctions principales de chaque module ?

[La fonction principale du module "header" est la fonction "fatal".
Toutes les fonctions du module "lecture_instructions" sont des fonctions principales.
La fonction principale du module "convert_hexa" est la fonction "gotohexa".
La fonction principale du module "traduction_hexa_instructions" est la fonction "fonctions".
La fonction principale du module "instructions" est la fonction "application".]

* Quels avantages voyez vous à cette structure (à comparer à un unique fichier)?

[Nous avons donc ici un module par fonctionnalité principale du programme.
C'est une option plus optimisée que d'avoir un unique fichier pour coder l'ensemble de notre programme. En effet, le code sera plus "facile" à relire et à débugger en cas de problème. Il sera surtout plus aéré et nous permettra de nous y retrouver plus facilement.]


## Rendu 4

* Avez-vous réussi à suivre la structure prévue au rendu 3 ? Quelles
modifications ont été nécessaires ? Rétrospectivement, est-ce que cette
structure était bien prévue ?

[Nous n'avons pas exactement suivis la structure du rendu3, nous avons séparé la mémoire de l'exécution des fonctions, il n'y a que le fichier mémoire.c qui fait des opérations sur la mémoire, les autres fichier appellent seulement les fonctions dans ce fichier]

* Avez-vous compris le fonctionnement de chaque instruction à partir de la
documentation fournie ? Si non, quels sont les points obscurs ?

[Nous n'avons pas tout compris grâce a la doc. C'est surtout quoi faire en cas d'erreur qui est compliqué a comprendre( quoi faire quand il y a un overflow, division par 0)]

* Quels exemples de programmes avez-vous choisi pour tester le calcul ? Les
comparaisons et sauts ? La mémoire ?

[Pour tester les calcul nous avons créée un fichier qui font seulement des somme/soustraction (ADDI.s et ADD_SUB.s), des opérations bit à bit (XOR_OR_AND.s, SLL_SRL_ROTR.s). Pour les comparaison et les saut nous avons le fichier jump.obs.s, JUMP.s et test_all_inst.s. Pour la mémoire nous avons le fichier SW_LW.s qui simule un tableau et des opération sur ce même tableau].

* Le sujet spécifie-t-il tous les détails nécessaires pour bien implémenter la
mémoire ? Quels choix avec-vous faits ?

[Le sujet nous indique tout ce qu'il faut, l'écart entre les adresse (+4) et l'adresse max.Nous avons choisi de faire une liste chainée pour la mémoire et un tableau de 35 int pour les registres]

* Reste-t-il des bugs que vous avez découverts et pas corrigés ?

[Nous avons beug majeur, si il y a plus d'un espace entre les instructions (dans notre fichier.s) la dernière instruction lut va être "compilé et exécuté" n fois (avec n= nb de lignes entre notre instruction et la "prochaine instruction/fin du fichier/#" -1)]

* D'autres remarques sur votre programme ?

[COMPLÉTER ICI]

* Cochez (en remplaçant `[ ]` par `[x]`) si vous avez :**
  - [x] Implémenté l'émulation de toutes les instructions gérées par le rendu 2.
  - [ ] Implémenté l'émulation de toutes les instructions.
  - [x] Tous vos tests qui passent.
  - [x] Vérifié que vous tests couvrent toutes les instructions émulées.
  - [x] Testé les cas particuliers : valeurs négatives, overflows...
  - [x] Testé les cas d'erreur : division par zéro, sauts invalides...
  - [ ] Un port fonctionnel de DOOM pour votre émulateur.

* Des retours sur le projet en général ?

[Nous avons bien aimé le projet et apris pas mal de chose]
