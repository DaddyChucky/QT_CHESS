/**
* Projet final :: INF1015 :: Livrable 3. Fichier qui définit les fonctions pour les pièces.
* \file   Case.cpp
* \author Charles De Lafontaine & Benoit Dambrine & al.
* \date   9 mai 2021
* Créé le 31 mars 2021
*/


#include "Modele.h"


/**
*  Une pièce.
*  \param	[const Couleur&]	couleur		<La couleur de la pièce à instancier.>
*/
modele::Piece::Piece(const Couleur& couleur) :
	couleur_(couleur)
{}


/**
*  Ajoute un mouvement à une pièce.
*  \param	[const pair<int, int>&]		nouveauMouvement	<Le mouvement à ajouter.>
*/
void modele::Piece::ajouterMouvement(const std::pair<int, int>& nouveauMouvement)
{
	mouvementsPossibles_.push_back(nouveauMouvement);
}


/**
*  Efface tous les mouvements possibles d'une pièce.
*/
void modele::Piece::effacerMouvements()
{
	mouvementsPossibles_.clear();
}


/**
*  Renvoie les mouvements possibles d'une pièce.
*  \return	[vector<pair<int, int>>]	<Les mouvements possibles d'une pièce.>
*/
std::vector<std::pair<int, int>> modele::Piece::getMouvementsPossibles() const
{
	return mouvementsPossibles_;
}


/**
*  Retourne la couleur d'une pièce.
*  \return	[Couleur]	<La couleur de la pièce.>
*/
modele::Couleur modele::Piece::getCouleur() const
{
	return couleur_;
}


/**
*  Vérifie si un mouvement de la pièce se situe à l'intérieur des bornes du jeu d'échecs.
*  \param	[const pair<int, int>&]		mouvementPossible	<Le mouvement à évaluer.>
*  \return	[bool]											<Vrai si le mouvement est valide, faux autrement.>
*/
bool modele::Piece::estInterieurBornes(const std::pair<int, int>& mouvementPossible) const
{
	//? Vérifier qu'on se situe dans les bornes de l'échiquier
	if (mouvementPossible.first >= 0 && mouvementPossible.first <= (DIMENSION_PLATEAU_X - 1) && mouvementPossible.second >= 0 && mouvementPossible.second <= (DIMENSION_PLATEAU_Y - 1))
		return true;

	return false;
}


/**
*  Permet de changer la couleur d'une pièce.
*  \param	[const Couleur&]	couleur		<La nouvelle couleur de la pièce.>
*/
void modele::Piece::setCouleur(const Couleur& couleur)
{
	couleur_ = couleur;
}
