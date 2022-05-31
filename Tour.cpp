/**
* Projet final :: INF1015 :: Livrable 3. Fichier qui d�finit les fonctions pour la tour.
* \file   Tour.cpp
* \author Charles De Lafontaine & Benoit Dambrine & al.
* \date   9 mai 2021
* Cr�� le 31 mars 2021
*/


#include "Modele.h"


/**
*  La pi�ce tour.
*  \param	[const Couleur&]	couleur		<La couleur de la pi�ce � instancier.>
*/
modele::Tour::Tour(const Couleur& couleur) :
	Piece(couleur)
{
	if (couleur == Couleur::Blanc)
		caracterePiece_ = CARACTERE_TOUR_BLANCHE;

	else
		caracterePiece_ = CARACTERE_TOUR_NOIRE;
}


/**
*  Calcule les mouvements possibles pour la tour.
*  \param	[const pair<int, int>&]		positionInitiale	<La position initiale de la tour.>
*  \param	[Plateau*]					plateau				<L'�chiquier.>
*/
void modele::Tour::calculerMouvementsPossibles(const std::pair<int, int>& positionInitiale, Plateau* plateau)
{
	using namespace std;

	const vector<pair<const int, const int>> MOUVEMENTS_POSSIBLES_AVANTS_X = {
		{positionInitiale.first + 1, positionInitiale.second},
		{positionInitiale.first + 2, positionInitiale.second},
		{positionInitiale.first + 3, positionInitiale.second},
		{positionInitiale.first + 4, positionInitiale.second},
		{positionInitiale.first + 5, positionInitiale.second},
		{positionInitiale.first + 6, positionInitiale.second},
		{positionInitiale.first + 7, positionInitiale.second}
	};

	const vector<pair<const int, const int>> MOUVEMENTS_POSSIBLES_AVANTS_Y = {
		{positionInitiale.first,	positionInitiale.second + 1},
		{positionInitiale.first,	positionInitiale.second + 2},
		{positionInitiale.first,	positionInitiale.second + 3},
		{positionInitiale.first,	positionInitiale.second + 4},
		{positionInitiale.first,	positionInitiale.second + 5},
		{positionInitiale.first,	positionInitiale.second + 6},
		{positionInitiale.first,	positionInitiale.second + 7}
	};

	const vector<pair<const int, const int>> MOUVEMENTS_POSSIBLES_ARRIERES_X = {
		{positionInitiale.first - 1, positionInitiale.second},
		{positionInitiale.first - 2, positionInitiale.second},
		{positionInitiale.first - 3, positionInitiale.second},
		{positionInitiale.first - 4, positionInitiale.second},
		{positionInitiale.first - 5, positionInitiale.second},
		{positionInitiale.first - 6, positionInitiale.second},
		{positionInitiale.first - 7, positionInitiale.second}
	};

	const vector<pair<const int, const int>> MOUVEMENTS_POSSIBLES_ARRIERES_Y = {
		{positionInitiale.first,	positionInitiale.second - 1},
		{positionInitiale.first,	positionInitiale.second - 2},
		{positionInitiale.first,	positionInitiale.second - 3},
		{positionInitiale.first,	positionInitiale.second - 4},
		{positionInitiale.first,	positionInitiale.second - 5},
		{positionInitiale.first,	positionInitiale.second - 6},
		{positionInitiale.first,	positionInitiale.second - 7}
	};

	const vector<vector<pair<const int, const int>>> MOUVEMENTS_POSSIBLES = {
		MOUVEMENTS_POSSIBLES_AVANTS_X, MOUVEMENTS_POSSIBLES_ARRIERES_X,
		MOUVEMENTS_POSSIBLES_AVANTS_Y, MOUVEMENTS_POSSIBLES_ARRIERES_Y
	};

	for (const auto& vectorMouvement : MOUVEMENTS_POSSIBLES)
		for (const auto& mouvement : vectorMouvement)
			//? V�rifier qu'on se situe dans les bornes de l'�chiquier
			if (estInterieurBornes(mouvement)) {
				//? V�rifier que la case n'est pas occup�
				if (!plateau->getCase(mouvement.first, mouvement.second)->getOccupation()) {
					//? nous sommes pas en echec
					if (plateau->getEtatEchec() == false) {
						//? est-ce que le mouvement cause un echec ?
						if (!plateau->testEchecADecouvert(positionInitiale, mouvement)) {
							ajouterMouvement(mouvement);
							continue;
						}
					}

					else {
						//? nous sommes en �chec :: est-ce que le mouvement enl�ve l'�chec ?
						if (plateau->testEchecProtection(positionInitiale, mouvement) == true) {
							ajouterMouvement(mouvement);
							continue;
						}
					}
				}

				//? Verifier que nous ne mangeons pas notre propre piece
				else if (plateau->getCase(mouvement.first, mouvement.second)->getPieceOccupante()->getCouleur() == plateau->getTour())
					break;

				//? Verifier si la piece de la case est couleur ennemi
				else if (plateau->getCase(mouvement.first, mouvement.second)->getPieceOccupante()->getCouleur() != plateau->getTour()) {
					//? nous sommes pas en echec
					if (plateau->getEtatEchec() == false) {
						//? est-ce que le mouvement cause un echec ?
						if (!plateau->testEchecADecouvert(positionInitiale, mouvement)) {
							ajouterMouvement(mouvement);
							break;
						}
					}

					if (plateau->testEchecProtection(positionInitiale, mouvement) == true) {
						ajouterMouvement(mouvement);
						break;
					}
				}
			}
}


/**
*  Calcule les mouvements possibles pour la tour.
*  \param	[const pair<int, int>&]		positionInitiale	<La position initiale de la tour.>
*  \param	[Plateau*]					plateau				<L'�chiquier.>
*/
void modele::Tour::calculerMouvementsPossiblesSimples(const std::pair<int, int>& positionInitiale, Plateau* plateau)
{
	using namespace std;

	const vector<pair<const int, const int>> MOUVEMENTS_POSSIBLES_AVANTS_X = {
		{positionInitiale.first + 1, positionInitiale.second},
		{positionInitiale.first + 2, positionInitiale.second},
		{positionInitiale.first + 3, positionInitiale.second},
		{positionInitiale.first + 4, positionInitiale.second},
		{positionInitiale.first + 5, positionInitiale.second},
		{positionInitiale.first + 6, positionInitiale.second},
		{positionInitiale.first + 7, positionInitiale.second}
	};

	const vector<pair<const int, const int>> MOUVEMENTS_POSSIBLES_AVANTS_Y = {
		{positionInitiale.first , positionInitiale.second + 1},
		{positionInitiale.first , positionInitiale.second + 2},
		{positionInitiale.first , positionInitiale.second + 3},
		{positionInitiale.first , positionInitiale.second + 4},
		{positionInitiale.first , positionInitiale.second + 5},
		{positionInitiale.first , positionInitiale.second + 6},
		{positionInitiale.first , positionInitiale.second + 7}
	};

	const vector<pair<const int, const int>> MOUVEMENTS_POSSIBLES_ARRIERES_X = {
		{positionInitiale.first - 1, positionInitiale.second},
		{positionInitiale.first - 2, positionInitiale.second},
		{positionInitiale.first - 3, positionInitiale.second},
		{positionInitiale.first - 4, positionInitiale.second},
		{positionInitiale.first - 5, positionInitiale.second},
		{positionInitiale.first - 6, positionInitiale.second},
		{positionInitiale.first - 7, positionInitiale.second}
	};

	const vector<pair<const int, const int>> MOUVEMENTS_POSSIBLES_ARRIERES_Y = {
		{positionInitiale.first , positionInitiale.second - 1},
		{positionInitiale.first , positionInitiale.second - 2},
		{positionInitiale.first , positionInitiale.second - 3},
		{positionInitiale.first , positionInitiale.second - 4},
		{positionInitiale.first , positionInitiale.second - 5},
		{positionInitiale.first , positionInitiale.second - 6},
		{positionInitiale.first , positionInitiale.second - 7}
	};

	const vector<vector<pair<const int, const int>>> MOUVEMENTS_POSSIBLES = {
		MOUVEMENTS_POSSIBLES_AVANTS_X, MOUVEMENTS_POSSIBLES_ARRIERES_X,
		MOUVEMENTS_POSSIBLES_AVANTS_Y, MOUVEMENTS_POSSIBLES_ARRIERES_Y
	};

	for (const auto vectorMouvement : MOUVEMENTS_POSSIBLES)
		for (auto mouvement : vectorMouvement)
			//? V�rifier qu'on se situe dans les bornes de l'�chiquier
			if (estInterieurBornes(mouvement))
				//? V�rifier que la case n'est pas occup�
				if (!plateau->getCase(mouvement.first, mouvement.second)->getOccupation()) {
					ajouterMouvement(mouvement);
					continue;
				}

				//? Verifier que nous ne mangeons pas notre propre piece
				else if (plateau->getCase(mouvement.first, mouvement.second)->getPieceOccupante()->getCouleur() == plateau->getTour())
					break;

				//? Verifier si la piece de la case est couleur ennemi
				else if (plateau->getCase(mouvement.first, mouvement.second)->getPieceOccupante()->getCouleur() != plateau->getTour()) {
					ajouterMouvement(mouvement);
					break;
				}
}


/**
*  D�finit le nom de la tour sous forme d'un caract�re.
*  \return	[char]	<Le nom de la tour lorsqu'elle n'est pas initialis�e.>
*/
char modele::Tour::getNom() const
{
	return CARACTERE_TOUR_NOIRE;
}


/**
*  Retourne le nom de la tour sous forme d'un caract�re.
*  \return	[char]	<Le nom de la tourlorsqu'elle est initialis�e.>
*/
char modele::Tour::getCaractere() const
{
	return caracterePiece_;
}
