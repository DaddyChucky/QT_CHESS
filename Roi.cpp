/**
* Projet final :: INF1015 :: Livrable 3. Fichier qui définit les fonctions pour le roi.
* \file   Roi.cpp
* \author Charles De Lafontaine & Benoit Dambrine & al.
* \date   9 mai 2021
* Créé le 31 mars 2021
*/


#include "Modele.h"


/**
*  La pièce roi.
*  \param	[const Couleur&]	couleur		<La couleur de la pièce à instancier.>
*/
modele::Roi::Roi(const Couleur& couleur) :
	Piece(couleur)
{
	if (couleur == Couleur::Blanc)
		caracterePiece_ = CARACTERE_ROI_BLANC;

	else
		caracterePiece_ = CARACTERE_ROI_NOIR;
}


/**
*  Vérifie si un roi est en confrontation avec le roi adverse.
*  \param	[const pair<int, int>&]		mouvementPossible	<Le mouvement à évaluer.>
*  \param	[const pair<int, int>&]		positionRoiAdverse	<La position du roi adverse.>
*  \return	[bool]											<Vrai si le mouvement est non conflictuel, faux autrement.>
*/
bool modele::Roi::estConfrontationRoiAdverse(const std::pair<int, int>& mouvementPossible, const std::pair<int, int>& positionRoiAdverse) const
{
	//? Vérifier que notre mouvement ne rentre pas en confrontation avec l'autre roi (Pythagore entre la position des deux rois)
	if (sqrt(pow(abs(mouvementPossible.first - positionRoiAdverse.first), FACTEUR_RACINE) + pow(abs(mouvementPossible.second - positionRoiAdverse.second), FACTEUR_RACINE)) >= LIMITE_CONFRONTATIONS_ROIS)
		return false;

	return true;
}


/**
*  Calcule les mouvements possibles pour le roi.
*  \param	[const pair<int, int>&]		positionInitiale	<La position initiale du roi.>
*  \param	[Plateau*]					plateau				<L'échiquier.>
*/
void modele::Roi::calculerMouvementsPossibles(const std::pair<int, int>& positionInitiale, Plateau* plateau)
{
	calculerMouvementsPossiblesSimples(positionInitiale, plateau);
}


/**
*  Calcule les mouvements possibles simples pour le roi.
*  \param	[const pair<int, int>&]		positionInitiale	<La position initiale du roi.>
*  \param	[Plateau*]					plateau				<L'échiquier.>
*/
void modele::Roi::calculerMouvementsPossiblesSimples(const std::pair<int, int>& positionInitiale, Plateau* plateau)
{
	using namespace std;

	const vector<pair<const int, const int>> MOUVEMENTS_POSSIBLES = {
			{ positionInitiale.first + 1,	positionInitiale.second },
			{ positionInitiale.first - 1,	positionInitiale.second },
			{ positionInitiale.first,		positionInitiale.second + 1 },
			{ positionInitiale.first,		positionInitiale.second - 1 },
			{ positionInitiale.first + 1,	positionInitiale.second + 1 },
			{ positionInitiale.first + 1,	positionInitiale.second - 1 },
			{ positionInitiale.first - 1,	positionInitiale.second + 1 },
			{ positionInitiale.first - 1,	positionInitiale.second - 1 }
	};

	for (const pair<int, int>& mouvement : MOUVEMENTS_POSSIBLES) {
		const pair<Case*, pair<int, int>> ROI_ADVERSE = plateau->trouverCase(CARACTERE_ROI_NOIR, true);

		if (!estConfrontationRoiAdverse(mouvement, ROI_ADVERSE.second)) {
			if (estInterieurBornes(mouvement)) {
				if (plateau->getEtatEchec() == false) {
					if (plateau->testEchecAuRoi(positionInitiale, mouvement)) {
						//? Vérifier que nous ne mangeons pas nos propres pièces
						if (plateau->trouverCase(mouvement)->getOccupation()) {
							if (plateau->trouverCase(mouvement)->getPieceOccupante()->getCouleur() != plateau->getTour()) {
								ajouterMouvement(mouvement);
							}
						}

						else {
							ajouterMouvement(mouvement);
						}
					}
				}

				else {
					if (plateau->testEchecProtection(positionInitiale, mouvement)) {
						ajouterMouvement(mouvement);
					}
				}
			}
		}	
	}
}


/**
*  Définit le nom du roi sous forme d'un caractère.
*  \return	[char]	<Le nom du roi lorsqu'il n'est pas initialisé.>
*/
char modele::Roi::getNom() const
{
	return CARACTERE_ROI_NOIR;
}


/**
*  Retourne le nom du roi sous forme d'un caractère.
*  \return	[char]	<Le nom du roi lorsqu'il est initialisé.>
*/
char modele::Roi::getCaractere() const
{
	return caracterePiece_;
}
