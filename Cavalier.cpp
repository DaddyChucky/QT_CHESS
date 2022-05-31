/**
* Projet final :: INF1015 :: Livrable 3. Fichier qui définit les fonctions pour le cavalier.
* \file   Cavalier.cpp
* \author Charles De Lafontaine & Benoit Dambrine & al.
* \date   9 mai 2021
* Créé le 31 mars 2021
*/


#include "Modele.h"


/**
*  La pièce cavalier.
*  \param	[const Couleur&]	couleur		<La couleur de la pièce à instancier.>
*/
modele::Cavalier::Cavalier(const Couleur& couleur) :
	Piece(couleur)
{
	if (couleur == Couleur::Blanc)
		caracterePiece_ = CARACTERE_CAVALIER_BLANC;

	else
		caracterePiece_ = CARACTERE_CAVALIER_NOIR;
}


/**
*  Calcule les mouvements possibles pour le cavalier.
*  \param	[const pair<int, int>&]		positionInitiale	<La position initiale du cavalier.>
*  \param	[Plateau*]					plateau				<L'échiquier.>
*/
void modele::Cavalier::calculerMouvementsPossibles(const std::pair<int, int>& positionInitiale, Plateau* plateau)
{
	using namespace std;

	const vector<pair<const int, const int>> MOUVEMENTS_POSSIBLES = {
			{positionInitiale.first + 2, positionInitiale.second + 1},
			{positionInitiale.first + 2, positionInitiale.second - 1},
			{positionInitiale.first - 2, positionInitiale.second + 1},
			{positionInitiale.first - 2, positionInitiale.second - 1},
			{positionInitiale.first + 1, positionInitiale.second + 2},
			{positionInitiale.first - 1, positionInitiale.second + 2},
			{positionInitiale.first + 1, positionInitiale.second - 2},
			{positionInitiale.first - 1, positionInitiale.second - 2}
	};

	for (const pair<const int, const int>& mouvement : MOUVEMENTS_POSSIBLES)
		//? Vérifier qu'on se situe dans les bornes de l'échiquier
		if (estInterieurBornes(mouvement))
			//? Vérifier que la case et livre et que nous ne mangeons pas nos propres pièces
			if (!plateau->trouverCase(mouvement)->getOccupation() || plateau->trouverCase(mouvement)->getPieceOccupante()->getCouleur() != plateau->getTour())
				//? Si nous ne sommes pas en échec
				if (plateau->getEtatEchec() == false) {
					//? Est-ce que le mouvement ajoute l'échec ?
					if (!plateau->testEchecADecouvert(positionInitiale, mouvement))
						ajouterMouvement(mouvement);
				}

				else {
					//? nous sommes en échec :: est-ce que le mouvement enlève l'échec ?
					if (plateau->testEchecProtection(positionInitiale, mouvement))
						ajouterMouvement(mouvement);
				}
}


/**
*  Calcule les mouvements possibles pour le cavalier.
*  \param	[const pair<int, int>&]		positionInitiale	<La position initiale du cavalier.>
*  \param	[Plateau*]					plateau				<L'échiquier.>
*/
void modele::Cavalier::calculerMouvementsPossiblesSimples(const std::pair<int, int>& positionInitiale, Plateau* plateau)
{
	using namespace std;

	const vector<pair<const int, const int>> MOUVEMENTS_POSSIBLES = {
			{positionInitiale.first + 2, positionInitiale.second + 1},
			{positionInitiale.first + 2, positionInitiale.second - 1},
			{positionInitiale.first - 2, positionInitiale.second + 1},
			{positionInitiale.first - 2, positionInitiale.second - 1},
			{positionInitiale.first + 1, positionInitiale.second + 2},
			{positionInitiale.first - 1, positionInitiale.second + 2},
			{positionInitiale.first + 1, positionInitiale.second - 2},
			{positionInitiale.first - 1, positionInitiale.second - 2}
	};

	for (const pair<const int, const int>& mouvement : MOUVEMENTS_POSSIBLES)
		//? Vérifier qu'on se situe dans les bornes de l'échiquier
		if (estInterieurBornes(mouvement))
			//? Vérifier que la case et livre et que nous ne mangeons pas nos propres pièces
			if (plateau->trouverCase(mouvement)->getOccupation() == false || plateau->trouverCase(mouvement)->getPieceOccupante()->getCouleur() != plateau->getTour())
				ajouterMouvement(mouvement);
}


/**
*  Définit le nom du cavalier sous forme d'un caractère.
*  \return	[char]	<Le nom du cavalier lorsqu'il n'est pas initialisé.>
*/
char modele::Cavalier::getNom() const
{
	return CARACTERE_CAVALIER_NOIR;
}


/**
*  Retourne le nom du cavalier sous forme d'un caractère.
*  \return	[char]	<Le nom du cavalier lorsqu'il est initialisé.>
*/
char modele::Cavalier::getCaractere() const
{
	return caracterePiece_;
}
