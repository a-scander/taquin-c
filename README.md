Jeu de Taquin en C avec MLV 

1.Présentation générale

Ce TP implémente un jeu de Taquin en langage C, avec affichage graphique via la bibliothèque MLV. Le joueur doit reconstituer une image découpée en tuiles en déplaçant les pièces vers la case vide, en cliquant dessus.



2.Arborescence du projet

Le projet est organisé de manière modulaire autour de cinq fichiers répartis à la racine du répertoire. On y trouve le point d'entrée du programme main.c, ainsi que deux modules : le module graphique (graphique.c / graphique.h) chargé de la gestion de la fenêtre, et le module plateau (plateau.c / plateau.h) qui concentre toute la logique du jeu. Un Makefile assure la compilation du projet en dirigeant les fichiers objets .o vers un dossier dédié out/, ce qui maintient la racine propre. Enfin, un dossier image/ contient les images .jpg utilisées comme support visuel du puzzle ; celles-ci ne sont pas nécessairement au bon format et sont redimensionnées dynamiquement à 512×512 pixels directement dans le code lors du chargement.



3.Description des modules

3.1.graphique.c / graphique.h

Ce module assure la gestion de la fenêtre d'affichage. Il expose deux fonctions simples : open_window() qui crée une fenêtre de dimensions 512×512 pixels intitulée "Taquin" via la bibliothèque MLV, et close_window() qui libère proprement cette fenêtre en fin de programme. 

3.2.plateau.c / plateau.h

Le fichier d'en-tête centralise les définitions structurelles du projet : la structure Carre représente une tuile avec ses coordonnées d'origine et son image MLV associée, tandis que la structure Plateau agrège l'ensemble des tuiles dans un tableau bidimensionnel avec une référence à la case vide. Il y sont également définies les constantes globales NB_LIG, NB_COL, TILE_SIZE, WINDOW_WIDTH et WINDOW_HEIGHT. Le fichier source constitue quant à lui le cœur du projet : InitialisationPlateau() charge et découpe l'image en tuiles, AfficherPlateau() redessine le plateau en laissant une case vide, Deplacer() et MelangerPlateau() gèrent les mouvements et le mélange initial, et JouerPlateau() forme la boucle principale qui attend les clics du joueur, effectue les déplacements et détecte la victoire via EstGagne().

3.3.main.c

Ce fichier constitue le point d'entrée du programme et orchestre les appels aux deux modules. Il commence par vérifier qu'un argument (le chemin vers l'image) a bien été fourni au lancement, puis enchaîne les étapes dans l'ordre logique : ouverture de la fenêtre, initialisation du plateau, mélange, affichage initial, boucle de jeu, libération de la mémoire et fermeture de la fenêtre. 

3.4.Makefile

Le Makefile assure la compilation du projet avec gcc en activant les warnings, la norme ANSI et le mode debug. Les fichiers objets sont isolés dans le dossier out/ pour garder la racine propre, et une cible clean permet de tout supprimer en une commande.



4.Points forts

Le projet présente une architecture bien découpée en modules distincts (graphique, plateau, main) qui respecte le principe de séparation des responsabilités. La gestion mémoire est rigoureuse, chaque image MLV étant systématiquement libérée dans LibererPlateau() en fin de partie. La logique de jeu repose sur une détection fiable des cases adjacentes par calcul de différence de coordonnées, et la condition de victoire est vérifiée en comparant la position courante de chaque tuile à ses coordonnées d'origine stockées dans la structure Carre. Enfin, le mélange initial garantit une configuration toujours atteignable car il n'effectue que des mouvements légaux, évitant ainsi les configurations insolubles.



5.Conclusion

Ce TP a permis de mettre en pratique la programmation modulaire en C avec affichage graphique via MLV. Le jeu est fonctionnel et jouable, et pourrait être enrichi par d'autres fonctionnalités.

