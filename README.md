Lucas Deletang

J'ai suivi les grandes lignes données sur moodle. 
-Une classe Square pour simplifier le passage d'arguments
-Une classe abstraite Piece avec ses déclinaisons en sous-classes Pawn, Rook, Bishop, Knight, Queen, King 
-Une classe Game, gérant l'alternance des coups, l'affichage et la validité des commandes
-Une classe Board gérant le plateau, les déplacements et la vérification de la légalité des déplacements
Aucune difficulté notable.

Pour compiler : make, puis ./bin/echecs

Tous les tests passent.
