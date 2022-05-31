/**
* Projet final :: INF1015 :: Livrable 3. Fichier qui d�finit les fonctions pour les pi�ces.
* \file   Case.cpp
* \author Charles De Lafontaine & Benoit Dambrine & al.
* \date   9 mai 2021
* Cr�� le 31 mars 2021
*/


#include "Modele.h"


/**
*  Une pi�ce.
*  \param	[const Couleur&]	couleur		<La couleur de la pi�ce � instancier.>
*/
modele::Piece::Piece(const Couleur& couleur) :
	couleur_(couleur)
{}


/**
*  Ajoute un mouvement � une pi�ce.
*  \param	[const pair<int, int>&]		nouveauMouvement	<Le mouvement � ajouter.>
*/
void modele::Piece::ajouterMouvement(const std::pair<int, int>& nouveauMouvement)
{
	mouvementsPossibles_.push_back(nouveauMouvement);
}


/**
*  Efface tous les mouvements possibles d'une pi�ce.
*/
void modele::Piece::effacerMouvements()
{
	mouvementsPossibles_.clear();
}


/**
*  Renvoie les mouvements possibles d'une pi�ce.
*  \return	[vector<pair<int, int>>]	<Les mouvements possibles d'une pi�ce.>
*/
std::vector<std::pair<int, int>> modele::Piece::getMouvementsPossibles() const
{
	return mouvementsPossibles_;
}


/**
*  Retourne la couleur d'une pi�ce.
*  \return	[Couleur]	<La couleur de la pi�ce.>
*/
modele::Couleur modele::Piece::getCouleur() const
{
	return couleur_;
}


/**
*  V�rifie si un mouvement de la pi�ce se situe � l'int�rieur des bornes du jeu d'�checs.
*  \param	[const pair<int, int>&]		mouvementPossible	<Le mouvement � �valuer.>
*  \return	[bool]											<Vrai si le mouvement est valide, faux autrement.>
*/
bool modele::Piece::estInterieurBornes(const std::pair<int, int>& mouvementPossible) const
{
	//? V�rifier qu'on se situe dans les bornes de l'�chiquier
	if (mouvementPossible.first >= 0 && mouvementPossible.first <= (DIMENSION_PLATEAU_X - 1) && mouvementPossible.second >= 0 && mouvementPossible.second <= (DIMENSION_PLATEAU_Y - 1))
		return true;

	return false;
}


/**
*  Permet de changer la couleur d'une pi�ce.
*  \param	[const Couleur&]	couleur		<La nouvelle couleur de la pi�ce.>
*/
void modele::Piece::setCouleur(const Couleur& couleur)
{
	couleur_ = couleur;
}
