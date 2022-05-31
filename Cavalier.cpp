/**
* Projet final :: INF1015 :: Livrable 3. Fichier qui d�finit les fonctions pour le cavalier.
* \file   Cavalier.cpp
* \author Charles De Lafontaine & Benoit Dambrine & al.
* \date   9 mai 2021
* Cr�� le 31 mars 2021
*/


#include "Modele.h"


/**
*  La pi�ce cavalier.
*  \param	[const Couleur&]	couleur		<La couleur de la pi�ce � instancier.>
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
*  \param	[Plateau*]					plateau				<L'�chiquier.>
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
		//? V�rifier qu'on se situe dans les bornes de l'�chiquier
		if (estInterieurBornes(mouvement))
			//? V�rifier que la case et livre et que nous ne mangeons pas nos propres pi�ces
			if (!plateau->trouverCase(mouvement)->getOccupation() || plateau->trouverCase(mouvement)->getPieceOccupante()->getCouleur() != plateau->getTour())
				//? Si nous ne sommes pas en �chec
				if (plateau->getEtatEchec() == false) {
					//? Est-ce que le mouvement ajoute l'�chec ?
					if (!plateau->testEchecADecouvert(positionInitiale, mouvement))
						ajouterMouvement(mouvement);
				}

				else {
					//? nous sommes en �chec :: est-ce que le mouvement enl�ve l'�chec ?
					if (plateau->testEchecProtection(positionInitiale, mouvement))
						ajouterMouvement(mouvement);
				}
}


/**
*  Calcule les mouvements possibles pour le cavalier.
*  \param	[const pair<int, int>&]		positionInitiale	<La position initiale du cavalier.>
*  \param	[Plateau*]					plateau				<L'�chiquier.>
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
		//? V�rifier qu'on se situe dans les bornes de l'�chiquier
		if (estInterieurBornes(mouvement))
			//? V�rifier que la case et livre et que nous ne mangeons pas nos propres pi�ces
			if (plateau->trouverCase(mouvement)->getOccupation() == false || plateau->trouverCase(mouvement)->getPieceOccupante()->getCouleur() != plateau->getTour())
				ajouterMouvement(mouvement);
}


/**
*  D�finit le nom du cavalier sous forme d'un caract�re.
*  \return	[char]	<Le nom du cavalier lorsqu'il n'est pas initialis�.>
*/
char modele::Cavalier::getNom() const
{
	return CARACTERE_CAVALIER_NOIR;
}


/**
*  Retourne le nom du cavalier sous forme d'un caract�re.
*  \return	[char]	<Le nom du cavalier lorsqu'il est initialis�.>
*/
char modele::Cavalier::getCaractere() const
{
	return caracterePiece_;
}
